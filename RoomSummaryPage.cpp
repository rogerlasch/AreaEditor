/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// RoomSummaryPage.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "AreaEditorDoc.h"
#include "defaults.h"

#include "RoomSummaryPage.h"

#include "ChooseMobDlg.h"
#include "ChooseObjectDlg.h"
#include "ChooseRoomDlg.h"
#include "WearFlagsDlg.h"
#include "AddExitDlg.h"

#include "AreaEditorView.h"
#include "ResetView.h"
#include "RoomView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRoomSummaryPage dialog


CRoomSummaryPage::CRoomSummaryPage(CWnd* pParent /*=NULL*/)
	: CDialog(CRoomSummaryPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRoomSummaryPage)
	m_name = _T("");
	m_sector_type = _T("");
	m_vnum = 0;
	m_strFlags = _T("");
	//}}AFX_DATA_INIT

  m_room = NULL;
  m_pDoc = NULL;

}

#undef LOAD_VALUE
#define LOAD_VALUE(field, value)  \
  field = m_room->value


void CRoomSummaryPage::DoDataExchange(CDataExchange* pDX)
{

  if (!pDX->m_bSaveAndValidate)
    {
    m_strFlags = convert_room_flags (m_room->room_flags);
    m_sector_type = RoomSectorList.ReturnName (m_room->sector_type, true);

    LOAD_VALUE (m_vnum, vnum);
	  LOAD_VALUE (m_name, name);
    }   // end of not saving and validating

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRoomSummaryPage)
	DDX_Control(pDX, IDC_REMOVE, m_ctlRemove);
	DDX_Control(pDX, IDC_GIVE, m_ctlGive);
	DDX_Control(pDX, IDC_EQUIP, m_ctlEquip);
	DDX_Control(pDX, IDC_OBJECTS, m_ctlObjects);
	DDX_Control(pDX, IDC_GOTO_OBJECT, m_ctlGoToObject);
	DDX_Control(pDX, IDC_GOTO_ENTRANCE, m_ctlGoToEntrance);
	DDX_Control(pDX, IDC_ENTRANCES, m_ctlEntrances);
	DDX_Text(pDX, IDC_NAME, m_name);
	DDX_Text(pDX, IDC_TYPE, m_sector_type);
	DDX_Text(pDX, IDC_VNUM, m_vnum);
	DDX_Text(pDX, IDC_FLAGS, m_strFlags);
	//}}AFX_DATA_MAP

  if (!pDX->m_bSaveAndValidate)
    AddEntrances ();

}


BEGIN_MESSAGE_MAP(CRoomSummaryPage, CDialog)
	//{{AFX_MSG_MAP(CRoomSummaryPage)
	ON_LBN_DBLCLK(IDC_ENTRANCES, OnDblclkEntrances)
	ON_BN_CLICKED(IDC_GOTO_ENTRANCE, OnGotoEntrance)
	ON_LBN_SELCHANGE(IDC_ENTRANCES, OnSelchangeEntrances)
	ON_LBN_SELCANCEL(IDC_ENTRANCES, OnSelcancelEntrances)
	ON_BN_CLICKED(IDC_GOTO_OBJECT, OnGotoObject)
	ON_LBN_DBLCLK(IDC_OBJECTS, OnDblclkObjects)
	ON_LBN_SELCHANGE(IDC_OBJECTS, OnSelchangeObjects)
	ON_LBN_SELCANCEL(IDC_OBJECTS, OnSelcancelObjects)
	ON_BN_CLICKED(IDC_ADD_MOB, OnAddMob)
	ON_BN_CLICKED(IDC_ADD_OBJECT, OnAddObject)
	ON_BN_CLICKED(IDC_REMOVE, OnRemove)
	ON_BN_CLICKED(IDC_EQUIP, OnEquip)
	ON_BN_CLICKED(IDC_GIVE, OnGive)
	ON_BN_CLICKED(IDC_ADD_EXIT, OnAddExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRoomSummaryPage message handlers


void CRoomSummaryPage::AddEntrances (void)
  {

  CString strExitDirection;

  POSITION roomPos;
  CRoom * room;

  POSITION exitPos;
  CExit * exit;

  m_ctlEntrances.ResetContent ();
  m_ctlObjects.ResetContent ();

  // scan all open areas for exits and resets

  for (POSITION docPos = App.m_pDocTemplate->GetFirstDocPosition();
      docPos != NULL; )
    {

    CAreaEditorDoc * pDoc = (CAreaEditorDoc *) App.m_pDocTemplate->GetNextDoc(docPos);

    // scan each room

    for (roomPos = pDoc->m_RoomList.GetHeadPosition (); roomPos; )
      {
      room = pDoc->m_RoomList.GetNext (roomPos);


      // for each room see if we have an exit to *this* room

      for (exitPos = room->exitlist.GetHeadPosition (); exitPos; )
        {
        exit = room->exitlist.GetNext (exitPos);

        // forget it, if the wrong room
        if (exit->vnum != m_room->vnum)
          continue;

        strExitDirection = RoomDirectionList.ReturnName (exit->vdir, false);

        room->AddToListBox (m_ctlEntrances, 
                            CFormat ("%s from #%i (%s)", 
                                        (LPCTSTR) strExitDirection,
                                        room->vnum, 
                                        (LPCTSTR) room->name));


        }

      }


    POSITION resetPos;
    CReset * reset;

    CMobile * mob;
    CMUDObject * object;
    bool bThisRoom = false;

      // process each reset

    for (resetPos = pDoc->m_ResetList.GetHeadPosition (); resetPos; )
      {
      reset = pDoc->m_ResetList.GetNext (resetPos);

      switch (reset->command)
        {
        case 'M': // load mobile
          bThisRoom = reset->arg3 == m_room->vnum;

          if (!bThisRoom)
            break;    // wrong room - forget it

          if ((mob = FindMob ( reset->arg1)) == NULL)
            break;    // mob not found

          // aha! - add to list of references
          reset->AddToListBox (m_ctlObjects, 
                              CFormat ("Mobile: %s", (LPCTSTR) mob->Summary ()));

          break;

        case 'O': // load object
          if (reset->arg3 != m_room->vnum)
            break;    // wrong room - forget it

          if ((object = FindObj ( reset->arg1)) == NULL)
            break;    // object not found

          // aha! - add to list of objects
          reset->AddToListBox (m_ctlObjects, 
                              CFormat ("Object: %s", (LPCTSTR) object->Summary ()));

          break;

        case 'G': // give object
        case 'E': // equip object
          if (!bThisRoom)   // not given to a mob in this room
            break;    // wrong room - forget it

          if ((object = FindObj ( reset->arg1)) == NULL)
            break;    // object not found

          // aha! - add to list of objects
          reset->AddToListBox (m_ctlObjects, reset->Summary ());

          break;

        } // end of switch

      }   // end of processing each reset


    // now look for program cross-references

    // process each mob

    CMUDprogram * program;
    CString strErrorMessage;

    for (POSITION mobPos = pDoc->m_MobList.GetHeadPosition (); mobPos; )
      {
      mob = pDoc->m_MobList.GetNext (mobPos);
      for (POSITION progPos = mob->programlist.GetHeadPosition (); progPos; )
        {
        POSITION pos;

        program = mob->programlist.GetNext (progPos);

        for (pos = program->xref_rooms.GetHeadPosition (); pos; )
          if (program->xref_rooms.GetNext (pos) == m_room->vnum)
            {
            // aha! - add to list of resets
            program->AddToListBox (m_ctlObjects,
              CFormat ("Program: %s <%s>", 
                        (LPCTSTR) mob->Summary (),
                        (LPCTSTR) program->Summary ()));
          }   // end of cross-reference found

        }   // end of each program
    
      } // end of each mob

    // process each room

    for (POSITION RoomPos = pDoc->m_RoomList.GetHeadPosition (); RoomPos; )
      {
      room = pDoc->m_RoomList.GetNext (RoomPos);
      for (POSITION progPos = room->programlist.GetHeadPosition (); progPos; )
        {
        POSITION pos;

        program = room->programlist.GetNext (progPos);

        for (pos = program->xref_rooms.GetHeadPosition (); pos; )
          if (program->xref_rooms.GetNext (pos) == m_room->vnum)
            program->AddToListBox (m_ctlObjects,
              CFormat ("Room prog: %s <%s>", 
                        (LPCTSTR) room->Summary (),
                        (LPCTSTR) program->Summary ()));

        }   // end of each program
    
      } // end of each room

    // process each object

    for (POSITION ObjectPos = pDoc->m_ObjectList.GetHeadPosition (); ObjectPos; )
      {
      object = pDoc->m_ObjectList.GetNext (ObjectPos);
      for (POSITION progPos = object->programlist.GetHeadPosition (); progPos; )
        {
        POSITION pos;

        program = object->programlist.GetNext (progPos);

        for (pos = program->xref_rooms.GetHeadPosition (); pos; )
          if (program->xref_rooms.GetNext (pos) == m_room->vnum)
            program->AddToListBox (m_ctlObjects,
              CFormat ("Object prog: %s <%s>", 
                        (LPCTSTR) object->Summary (),
                        (LPCTSTR) program->Summary ()));
        }   // end of each program
    
      } // end of each object

    } // end of doing each document

  OnSelchangeEntrances ();
  OnSelchangeObjects ();

  }

void CRoomSummaryPage::OnDblclkEntrances() 
{
OnGotoEntrance ();
}


void CRoomSummaryPage::OnGotoEntrance() 
{
// find which item they selected, and go to it

int nItem =  m_ctlEntrances.GetCurSel( );

if (nItem != LB_ERR)
  ((CMUDitem *) m_ctlEntrances.GetItemData (nItem))->GoTo ();
	
}

void CRoomSummaryPage::OnSelchangeEntrances() 
{
// find which item they selected

int nItem =  m_ctlEntrances.GetCurSel( );
	
m_ctlGoToEntrance.EnableWindow (nItem != LB_ERR);

}

void CRoomSummaryPage::OnSelcancelEntrances() 
{
OnSelchangeEntrances ();	
}

void CRoomSummaryPage::OnGotoObject() 
{
// find which item they selected, and go to it

int nItem =  m_ctlObjects.GetCurSel( );

if (nItem != LB_ERR)
  ((CMUDitem *) m_ctlObjects.GetItemData (nItem))->GoTo ();
	
}

void CRoomSummaryPage::OnDblclkObjects() 
{
OnGotoObject ();
}

void CRoomSummaryPage::OnSelchangeObjects() 
{
// find which item they selected

int nItem =  m_ctlObjects.GetCurSel( );
	
m_ctlGoToObject.EnableWindow (nItem != LB_ERR);
m_ctlRemove.EnableWindow (nItem != LB_ERR);

if (nItem != LB_ERR)
  {
  CMUDitem * pItem =  (CMUDitem *) m_ctlObjects.GetItemData (nItem);
  CReset * pReset = (CReset *) pItem;
  // we can only equip or give if we have highlighted a mob reset
  if (pItem && strcmp (pItem->Type (), "reset") == 0 && pReset->command == 'M')
    {
    m_ctlGive.EnableWindow (TRUE);
    m_ctlEquip.EnableWindow (TRUE);
    }
  else
    {
    m_ctlGive.EnableWindow (FALSE);
    m_ctlEquip.EnableWindow (FALSE);
    }
  }
else
  {
  m_ctlGive.EnableWindow (FALSE);
  m_ctlEquip.EnableWindow (FALSE);
  }

}

void CRoomSummaryPage::OnSelcancelObjects() 
{
OnSelchangeObjects ();
}

void CRoomSummaryPage::OnAddMob() 
{
CChooseMobDlg mob_dlg;

  mob_dlg.m_pDoc = m_pDoc;
  
  CRoomView * wndParent = (CRoomView *) GetParent ();
  wndParent->m_bEditingText = true;

  if (mob_dlg.DoModal () == IDOK) 
    if (mob_dlg.m_iSelectedMob != -1)
      {
      CReset * reset = new CReset (RUNTIME_CLASS(CResetView), m_pDoc);
      m_pDoc->m_ResetList.AddTail (reset);    // and add it to our list
      m_pLHview->AddTreeItem (reset, m_pLHview->m_hdlTreeResets, TVI_LAST);
      m_pDoc->SetModifiedFlag ();

      reset->command = 'M';   // load mob
      reset->arg1 = mob_dlg.m_iSelectedMob;   // what what
      reset->arg2 = 1;    // limit
      reset->arg3 = m_room->vnum;   // which room (ie, this one)
      reset->m_pTreeCtrl->SetItemText (reset->m_hdlTreeItem, reset->Summary ());
      AddEntrances ();    // redraw list
      }

  wndParent->m_bEditingText = false;
    
}

void CRoomSummaryPage::OnAddObject() 
{
CChooseObjectDlg object_dlg;

  object_dlg.m_pDoc = m_pDoc;
  
  CRoomView * wndParent = (CRoomView *) GetParent ();
  wndParent->m_bEditingText = true;

  if (object_dlg.DoModal () == IDOK) 
    if (object_dlg.m_iSelectedObject != -1)
      {
      CReset * reset = new CReset (RUNTIME_CLASS(CResetView), m_pDoc);
      m_pDoc->m_ResetList.AddTail (reset);    // and add it to our list
      m_pLHview->AddTreeItem (reset, m_pLHview->m_hdlTreeResets, TVI_LAST);
      m_pDoc->SetModifiedFlag ();

      reset->command = 'O';   // load object
      reset->arg1 = object_dlg.m_iSelectedObject;   // what object
      reset->arg2 = 1;    // limit
      reset->arg3 = m_room->vnum;   // which room (ie, this one)
      reset->m_pTreeCtrl->SetItemText (reset->m_hdlTreeItem, reset->Summary ());
      AddEntrances ();    // redraw list
      }

  wndParent->m_bEditingText = false;
    
}

void CRoomSummaryPage::OnRemove() 
{
// find which item they selected, and remove it

int nItem =  m_ctlObjects.GetCurSel( );

if (nItem == LB_ERR)
  return;

 CMUDitem * pItem =  (CMUDitem *) m_ctlObjects.GetItemData (nItem);

// ask if they want to delete it

  if (::AfxMessageBox (CFormat ("OK to delete %s %s?", 
                    pItem->Type (),
                    (LPCTSTR) pItem->Summary ()), 
                    MB_ICONQUESTION | MB_YESNO) != IDYES)
                    return;

  pItem->Delete ();
  AddEntrances ();    // redraw list
	
}

#undef LOAD_FLAG
#define LOAD_FLAG(field, flag)  \
  field = IS_SET (arg3, flag);

#undef UNLOAD_FLAG
#define UNLOAD_FLAG(field, flag)  \
  if (field)                      \
    SET_BIT (arg3, flag);\
  else                            \
    REMOVE_BIT (arg3, flag)

void CRoomSummaryPage::GiveOrEquip (const char cResetCommand)
  {
int nItem =  m_ctlObjects.GetCurSel( );
	

if (nItem == LB_ERR)
return;

  CMUDitem * pItem =  (CMUDitem *) m_ctlObjects.GetItemData (nItem);
  CReset * pReset = (CReset *) pItem;

  if (!pItem || 
      strcmp (pItem->Type (), "reset") != 0 || 
      pReset->command != 'M')
    return;

  CChooseObjectDlg object_dlg;

  object_dlg.m_pDoc = m_pDoc;
  object_dlg.m_iItemType = cResetCommand == 'E' ? eWearItem : eTakeItem;
  
  CRoomView * wndParent = (CRoomView *) GetParent ();
  wndParent->m_bEditingText = true;

  if (object_dlg.DoModal () == IDOK) 
    if (object_dlg.m_iSelectedObject != -1)
      {

      int arg3 = WEAR_HOLD;

// for an equip, get the wear flags

      if (cResetCommand == 'E')
       {
        CWearFlagsDlg wear_dlg;

        EXT_BV iWearFlags = FindObj (object_dlg.m_iSelectedObject)->wear_flags;
        wear_dlg.m_strWearLocations = convert_wear_flags (iWearFlags);
        wear_dlg.m_strObject = FindObj (object_dlg.m_iSelectedObject)->Summary ();

        wear_dlg.m_iWearLocation = arg3;

        if (wear_dlg.DoModal () != IDOK)
          {
          wndParent->m_bEditingText = false;
          return;
          }

        arg3 = wear_dlg.m_iWearLocation;
   
       }    // end of an equip reset

      CReset * reset = (CReset *) pReset->Add (m_pLHview, false);
      reset->command = cResetCommand;
      reset->arg1 = object_dlg.m_iSelectedObject;   // what object
      reset->arg2 = 1;    // limit
      reset->arg3 = cResetCommand == 'E' ? arg3 : 0;    // wear flags
      reset->extra = 1;   // not sure what this does ...
      reset->m_pTreeCtrl->SetItemText (reset->m_hdlTreeItem, reset->Summary ());
      AddEntrances ();    // redraw list
      }

    wndParent->m_bEditingText = false;
  } // end of CRoomSummaryPage::GiveOrEquip

void CRoomSummaryPage::OnEquip() 
{
	GiveOrEquip ('E');
}

void CRoomSummaryPage::OnGive() 
{
	GiveOrEquip ('G');
}

// table to work out the reverse of a given direction
int iReverseDirections [] = 
  {
     DIR_SOUTH,     // from north
     DIR_WEST,      // from east
     DIR_NORTH,     // from south
     DIR_EAST,      // from west
     DIR_DOWN,      // from up
     DIR_UP,        // from down
     DIR_SOUTHWEST, // from ne
     DIR_SOUTHEAST, // from nw
     DIR_NORTHWEST, // from se
     DIR_NORTHEAST, // from sw
     DIR_SOMEWHERE  // from somewhere
  };


// have a static flag so we remember the "make reverse" switch
static BOOL bMakeReverse = FALSE;

void CRoomSummaryPage::OnAddExit() 
{

POSITION exitPos;
CExit * exit;

CRoomView * wndParent = (CRoomView *) GetParent ();

  wndParent->m_bEditingText = true;

// First, find which direction they want to go

CAddExitDlg directionDlg;

  directionDlg.m_room = m_room;
  directionDlg.m_bMakeReverse = bMakeReverse;

  if (directionDlg.DoModal () != IDOK)
    {
    wndParent->m_bEditingText = false;
    return;
    }

  // remember for next time if they wanted a reverse exit
  bMakeReverse = directionDlg.m_bMakeReverse;

  // warn if already an exit in that direction
  for (exitPos = m_room->exitlist.GetHeadPosition (); exitPos; )
    {
    exit = m_room->exitlist.GetNext (exitPos);

    if (exit->vdir == directionDlg.m_iDirection)
      {
      if (::AfxMessageBox (CFormat ("There is already an exit in the direction: %s\n\n"
                                "Do you want to add another \"%s\" exit?",
                                (LPCTSTR) exit->Summary (),
                                RoomDirectionList.ReturnName (directionDlg.m_iDirection, false)), 
                                MB_YESNO | MB_ICONQUESTION)
                                != IDYES)
                                {
                                wndParent->m_bEditingText = false;
                                return;
                                }
      break;    // don't query twice if they already have two exits in that direction
      }   // end of another exit in that direction
    }   // end of looping through exits

// Then, find which room they want to go to
CChooseRoomDlg roomDlg;

  roomDlg.m_pDoc = m_pDoc;
  roomDlg.m_iSelectedRoom = -1;
  if (roomDlg.DoModal () != IDOK) 
    {
    wndParent->m_bEditingText = false;
    return;
    }

  // if a reverse exit wanted, create that too

  if (directionDlg.m_bMakeReverse)
    {

    // look up room - make sure it exists
    CRoom * room = FindRoom (roomDlg.m_iSelectedRoom);

    if (!room)
      ::AfxMessageBox ("Cannot create reverse exit - destination room not selected",
                        MB_ICONEXCLAMATION);
    else
      {

      // warn if already an exit in that direction
      for (exitPos = room->exitlist.GetHeadPosition (); exitPos; )
        {
        exit = room->exitlist.GetNext (exitPos);

        if (exit->vdir == iReverseDirections [directionDlg.m_iDirection])
          {
          if (::AfxMessageBox (CFormat ("Room %s already has an exit in the direction: %s\n\n"
                                    "Do you want to add another \"%s\" exit?",
                                    (LPCTSTR) room->Summary (),
                                    (LPCTSTR) exit->Summary (),
                                    RoomDirectionList.ReturnName (iReverseDirections [directionDlg.m_iDirection], false)),
                                    MB_YESNO | MB_ICONQUESTION)
                                    != IDYES)
                                    {
                                    wndParent->m_bEditingText = false;
                                    return;
                                    }
          break;    // don't query twice if they already have two exits in that direction
          }   // end of another exit in that direction
        }   // end of looping through exits
      
      
      // If wanted, create the reverse exit

      exit = room->AddExit (m_pLHview);
      exit->vdir = iReverseDirections [directionDlg.m_iDirection];    // direction is reverse direction
      exit->vnum = m_room->vnum;    // exit to current room vnum
      exit->m_pTreeCtrl->SetItemText (exit->m_hdlTreeItem, exit->Summary ()); // amend description

      } // end of reverse room found
    } // end of reverse exit wanted

// If all went well, create the forwards exit

  exit = m_room->AddExit (m_pLHview);

// Fill in the answers from above
  exit->vdir = directionDlg.m_iDirection;   // direction is selected direction
  exit->vnum = roomDlg.m_iSelectedRoom;     // room to go to is selected room
  exit->m_pTreeCtrl->SetItemText (exit->m_hdlTreeItem, exit->Summary ()); // amend description

// And take them to the exit so they can fill in the description and keywords
  exit->GoTo ();
	
}
