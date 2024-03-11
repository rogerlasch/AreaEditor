/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// ObjectResetsPage.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "AreaEditorDoc.h"
#include "ObjectResetsPage.h"
#include "defaults.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CObjectResetsPage dialog


CObjectResetsPage::CObjectResetsPage(CWnd* pParent /*=NULL*/)
	: CDialog(CObjectResetsPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CObjectResetsPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

  m_object = NULL;

}


void CObjectResetsPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CObjectResetsPage)
	DDX_Control(pDX, IDC_GOTO_RESET, m_ctlGoToReset);
	DDX_Control(pDX, IDC_LOADED, m_ctlLoadedList);
	//}}AFX_DATA_MAP

  if (!pDX->m_bSaveAndValidate)
    AddResets ();

}


BEGIN_MESSAGE_MAP(CObjectResetsPage, CDialog)
	//{{AFX_MSG_MAP(CObjectResetsPage)
	ON_BN_CLICKED(IDC_GOTO_RESET, OnGotoReset)
	ON_LBN_DBLCLK(IDC_LOADED, OnDblclkLoaded)
	ON_LBN_SELCANCEL(IDC_LOADED, OnSelcancelLoaded)
	ON_LBN_SELCHANGE(IDC_LOADED, OnSelchangeLoaded)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CObjectResetsPage message handlers

void CObjectResetsPage::AddResets (void)
  {

  POSITION resetPos;
  CReset * reset;

  CMUDObject * object;
  CRoom * room;
  CMobile * mob = NULL;
  CString strMob;
  CString strResult;

  m_ctlLoadedList.ResetContent ();

  // scan all open areas for resets

  for (POSITION docPos = App.m_pDocTemplate->GetFirstDocPosition();
      docPos != NULL; )
    {

    CAreaEditorDoc * pDoc = (CAreaEditorDoc *) App.m_pDocTemplate->GetNextDoc(docPos);

      // process each reset

    for (resetPos = pDoc->m_ResetList.GetHeadPosition (); resetPos; )
      {
      reset = pDoc->m_ResetList.GetNext (resetPos);

      switch (reset->command)
        {

        case 'M': // load mobile - remember for next Equip
          mob = pDoc->get_mob_index( reset->arg1);
          if (mob)
            strMob = mob->Summary ();
          else  
          if (mob = FindMob (reset->arg1))
            strMob = (FullMobName (mob));
          else
            strMob = CFormat ("#%i (not in area)", reset->arg1);

          break;

        case 'E': // equip
        case 'G': // equip
          if (reset->arg1 != m_object->vnum)
            break;    // wrong object - forget it
  
          reset->AddToListBox (m_ctlLoadedList, 
                              CFormat ("Mob %s: %s", 
                                      reset->command == 'E' ? "equip" : "give",
                                      (LPCTSTR) strMob));
          break;

        case 'O': // load object
          if (reset->arg1 != m_object->vnum)
            break;    // wrong object - forget it

          room = pDoc->get_room_index ( reset->arg3);

          if (room)
            strResult = room->Summary ();
          else
          if (room = FindRoom (reset->arg3))
            strResult = (FullRoomName (room));
          else
            strResult = CFormat ("#%i (not in area)", reset->arg3);

          reset->AddToListBox (m_ctlLoadedList, 
                                CFormat ("Room: %s",
                                (LPCTSTR) strResult));
          break;


        case 'P': // put object
          if (reset->arg1 == m_object->vnum)
            {

            object = pDoc->get_obj_index( reset->arg3);

            if (object)
              strResult = object->Summary ();
            else
            if (object = FindObj ( reset->arg3 ))
              strResult = FullObjName (object);
            else
              strResult = CFormat ("#%i (not in area)", reset->arg3);

            // aha! - add to list of resets
            reset->AddToListBox (m_ctlLoadedList, 
                                CFormat ("Put into object: %s",
                                (LPCTSTR) strResult));
            }   // end of match on arg1

          if (reset->arg3 != m_object->vnum)
            break;    // wrong object - forget it

          object = pDoc->get_obj_index( reset->arg1);

          if (object)
            strResult = object->Summary ();
          else
          if (object = FindObj ( reset->arg1 ))
            strResult = FullObjName (object);
          else
            strResult = CFormat ("#%i (not in area)", reset->arg1);

          // aha! - add to list of resets
          reset->AddToListBox (m_ctlLoadedList, 
                              CFormat ("Contains object: %s",
                              (LPCTSTR) strResult));

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

        for (pos = program->xref_objects.GetHeadPosition (); pos; )
          if (program->xref_objects.GetNext (pos) == m_object->vnum)
            program->AddToListBox (m_ctlLoadedList, 
                                  CFormat ("Mob prog: %s <%s>", 
                                            (LPCTSTR) mob->Summary (),
                                            (LPCTSTR) program->Summary ()));

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

        for (pos = program->xref_objects.GetHeadPosition (); pos; )
          if (program->xref_objects.GetNext (pos) == m_object->vnum)
            program->AddToListBox (m_ctlLoadedList,
              CFormat ("Room prog: %s <%s>", 
                        (LPCTSTR) room->Summary (),
                        (LPCTSTR) program->Summary ()));

        }   // end of each program

      // process each exit to see if it uses this object as a key

      CExit * exit;

      for (POSITION exitPos = room->exitlist.GetHeadPosition (); exitPos; )
        {
        exit = room->exitlist.GetNext (exitPos);

        // forget it, if the wrong object
        if (exit->key != m_object->vnum)
          continue;

        exit->AddToListBox (m_ctlLoadedList,
                             CFormat ("Key to %s from #%i (%s)", 
                                        (LPCTSTR) RoomDirectionList.ReturnName (exit->vdir, false),
                                        room->vnum, 
                                        (LPCTSTR) room->name));

        }

      } // end of each room

    // process each object

    for (POSITION ObjectPos = pDoc->m_ObjectList.GetHeadPosition (); ObjectPos; )
      {
      object = pDoc->m_ObjectList.GetNext (ObjectPos);
      for (POSITION progPos = object->programlist.GetHeadPosition (); progPos; )
        {
        POSITION pos;

        program = object->programlist.GetNext (progPos);

        for (pos = program->xref_objects.GetHeadPosition (); pos; )
          if (program->xref_objects.GetNext (pos) == m_object->vnum)
            program->AddToListBox (m_ctlLoadedList,
              CFormat ("Object prog: %s <%s>", 
                        (LPCTSTR) object->Summary (),
                        (LPCTSTR) program->Summary ()));
        }   // end of each program
    
      } // end of each object

    } // end of doing each document

  OnSelchangeLoaded ();

  }   // end of CObjectResetsPage::AddEntrances 

void CObjectResetsPage::OnGotoReset() 
{
// find which item they selected, and go to it

int nItem =  m_ctlLoadedList.GetCurSel( );

if (nItem != LB_ERR)
  ((CMUDitem *) m_ctlLoadedList.GetItemData (nItem))->GoTo ();
  
}

void CObjectResetsPage::OnSelchangeLoaded() 
{
  // find which item they selected

int nItem =  m_ctlLoadedList.GetCurSel( );
	
m_ctlGoToReset.EnableWindow (nItem != LB_ERR);

}

void CObjectResetsPage::OnDblclkLoaded() 
{
  OnGotoReset ();	
}

void CObjectResetsPage::OnSelcancelLoaded() 
{
  OnSelchangeLoaded ();
}
