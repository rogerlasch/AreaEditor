/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#include "stdafx.h"
#include "AreaEditor.h"

#include "AreaEditorDoc.h"

#include "RoomView.h"
#include "AddToRoomDlg.h"
#include "AreaEditorView.h"
#include "defaults.h"

#include "MUDProgramView.h"
#include "ObjectExtraDescriptionView.h"
#include "RoomExitView.h"
#include "RoomMapView.h"
#include "DeleteXrefDlg.h"

// constructor
CRoom::CRoom (CRuntimeClass* pViewClass, CAreaEditorDoc * pDoc)
      : CMUDitem (pViewClass, pDoc) 
  {

    name = strRoomDefaultName;
    description = strRoomDefaultDescription;
    vnum = 0;
    room_flags = 0;
    sector_type = 0;    // inside
    tele_vnum = 0;
    tele_delay = 0;
    tunnel = 0;		 

    heal_rate = 0;    // ROM
    mana_rate = 0;    // ROM

  }  // end of constructor

void CRoom::ChangeRHview (CAreaEditorView * pLHview, CView * pwhichView)
  {
  CRoomView * pView = (CRoomView *) pwhichView;

	ASSERT(pView->IsKindOf(RUNTIME_CLASS(CRoomView)));

  pView->m_room = this;
  pView->m_pLHview = pLHview;

  pView->CreatePages ();   // add the tab control pages

  pView->ShowPages (m_pDoc);

  }

CString CRoom::Summary (void)
  {
  return CFormat ("#%i %s", 
                  vnum, 
                  (LPCTSTR) name);
  }

CRoom::~CRoom ()
  {
  // get rid of programs inside room

  for (POSITION progPos = programlist.GetHeadPosition (); progPos; )
    delete programlist.GetNext (progPos);

  programlist.RemoveAll ();  // pointers are deleted, remove list items

  // get rid of exits inside room

  for (POSITION exitPos = exitlist.GetHeadPosition (); exitPos; )
    delete exitlist.GetNext (exitPos);

  exitlist.RemoveAll ();  // pointers are deleted, remove list items

  // get rid of maps inside room

  for (POSITION mapPos = maplist.GetHeadPosition (); mapPos; )
    delete maplist.GetNext (mapPos);

  maplist.RemoveAll ();  // pointers are deleted, remove list items

  // get rid of extra descriptions inside room

  for (POSITION extraPos = extralist.GetHeadPosition (); extraPos; )
    delete extralist.GetNext (extraPos);

  extralist.RemoveAll ();  // pointers are deleted, remove list items
  }   // end of destructor


void CRoom::Delete (void)
  {

  // look for things that refer to *this* room and tell them about it

CDeleteXrefDlg dlg;

CMUDitemList xrefList;
CMUDitemList xrefOwnerList;
CRoom * room;
CExit * exit;
CMUDitem * noitem = NULL;

  dlg.m_pxrefList = &xrefList;
  dlg.m_pxrefOwnerList = &xrefOwnerList;
  dlg.m_strAboutToDelete = Summary ();

  for (POSITION RoomPos = m_pDoc->m_RoomList.GetHeadPosition (); RoomPos; )
    {
    room = m_pDoc->m_RoomList.GetNext (RoomPos);
    if (room == this)
      continue;   // don't delete ourselves twice!

    for (POSITION ExitPos = room->exitlist.GetHeadPosition (); ExitPos; )
      {
      exit = room->exitlist.GetNext (ExitPos);
      if (exit->vnum != vnum)
        continue;   // wrong vnum - keep going
      xrefOwnerList.AddTail (room);   // owner of room
      xrefList.AddTail (exit);        // which exit
      }   // end of checking each exit
    }   // end of checking each room

  for (POSITION ResetPos = m_pDoc->m_ResetList.GetHeadPosition (); ResetPos; )
    {
    CReset * reset = m_pDoc->m_ResetList.GetNext (ResetPos);

    switch (reset->command)
	    {
	    case 'M':     // this reset puts a mob in the room
          if (reset->arg3 == vnum)
            {
            xrefOwnerList.AddTail (noitem);   // no owner of reset
            xrefList.AddTail (reset);       // which reset
            }
	        break;

	    case 'O':   // this reset puts an object in the room
          if (reset->arg3 == vnum)
            {
            xrefOwnerList.AddTail (noitem);   // no owner of reset
            xrefList.AddTail (reset);       // which reset
            }
	        break;

	    case 'D':   // this reset opens/shuts a door in the room
          if (reset->arg1 == vnum) 
            {
            xrefOwnerList.AddTail (noitem);   // no owner of reset
            xrefList.AddTail (reset);       // which reset
            }
	        break;

	    case 'R': // randomize exits in the room
          if (reset->arg1 == vnum) 
            {
            xrefOwnerList.AddTail (noitem);   // no owner of reset
            xrefList.AddTail (reset);       // which reset
            }
	        break;
	    }   // end of switch
  }   // end of processing each reset
  
  if (!xrefList.IsEmpty ())   // don't bother if no references
    if (dlg.DoModal () != IDOK)
      return;   // they changed their mind (hope it works better!)

  // delete referencing items

  for (POSITION refPos = xrefList.GetHeadPosition (); refPos; )
    xrefList.GetNext (refPos)->Delete ();

  // delete programs inside room

  for (POSITION progPos = programlist.GetHeadPosition (); progPos; )
    programlist.GetNext (progPos)->Delete ();

  programlist.RemoveAll ();  // pointers are deleted, remove list items

  // delete exits inside room

  for (POSITION exitPos = exitlist.GetHeadPosition (); exitPos; )
    exitlist.GetNext (exitPos)->Delete ();

  exitlist.RemoveAll ();  // pointers are deleted, remove list items

  // delete maps inside room

  for (POSITION mapPos = maplist.GetHeadPosition (); mapPos; )
    maplist.GetNext (mapPos)->Delete ();

  maplist.RemoveAll ();  // pointers are deleted, remove list items

  // delete extra descriptions inside room

  for (POSITION extraPos = extralist.GetHeadPosition (); extraPos; )
    extralist.GetNext (extraPos)->Delete ();

  extralist.RemoveAll ();  // pointers are deleted, remove list items

  // delete from list of rooms

  m_pDoc->m_RoomList.RemoveAt (m_pDoc->m_RoomList.Find (this, NULL));

  CMUDitem::Delete ();

  } // end of CRoom::Delete 

CMUDitem * CRoom::Add (CAreaEditorView * pView, const bool bSelect)
  {
// add program, affect or extra to this room
CAddToRoomDlg dlg;

  dlg.m_iAddType = 0;

  if (dlg.DoModal () != IDOK)
    return NULL;   // they cancelled, the bastards!

CMUDprogram * prog;

HTREEITEM hdlItem;
CMUDitem * pItem = NULL;

  switch (dlg.m_iAddType)
    {
    case 0:   // Extra description

            pItem = AddDescription (pView);
            break;

    case 1:   // Exit

            pItem = AddExit (pView);
            break;

    case 2:   // Map

            pItem = AddMap (pView);
            break;

    case 3:   // Program
            
            prog = new CMUDprogram (RUNTIME_CLASS(CMUDProgramView), 
                                m_pDoc);
            programlist.AddHead (prog);    // and add it to our list
            hdlItem = pView->AddTreeItem (prog, m_hdlTreeItem);
            m_pDoc->SetModifiedFlag ();
            pItem = prog;
            break;

    }

  if (bSelect)
    pItem->GoTo ();

  return pItem;
  } // end of CRoom::Add 


CString CRoom::AddDescription (void)  // description of what add does
  {
  return "description/exit/map/program";
  }   // end of CRoom::AddDescription

void CRoom::SubItemDeleted (CMUDitem * pItem)
  {
POSITION pos;

 // a program has been deleted?

  if (pos = programlist.Find (pItem, NULL))
    programlist.RemoveAt (pos);

 // an exit has been deleted?

  if (pos = exitlist.Find (pItem, NULL))
    exitlist.RemoveAt (pos);

 // a map been deleted?

  if (pos = maplist.Find (pItem, NULL))
    maplist.RemoveAt (pos);

 // an extra description has been deleted?

  if (pos = extralist.Find (pItem, NULL))
    extralist.RemoveAt (pos);

  } // end of CRoom::SubItemDeleted 


static int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM 
                lParamSort)
  {
CMUDprogram * prog1 = (CMUDprogram *) lParam1;
CMUDprogram * prog2 = (CMUDprogram *) lParam2;

  if (prog1->iSortSeq < prog2->iSortSeq)
    return -1;
  else if (prog1->iSortSeq > prog2->iSortSeq)
    return 1;
  else
    return 0;

  } // end of CompareFunc

// add for a program adds one after the current one
CMUDprogram * CRoom::AddProgram (CAreaEditorView * pView, 
                                CMUDitem * pItem,
                                const bool bSelect)
  {
TV_SORTCB sortCB;
int iSeq = 0;
   
    CMUDprogram * prog = new CMUDprogram (RUNTIME_CLASS(CMUDProgramView), m_pDoc);
    if (pItem)
      {
      POSITION pos = programlist.Find (pItem, NULL);
      programlist.InsertAfter (pos, prog);    // and add it to our list
      }
    else
      programlist.AddHead (prog);    // add at head

    HTREEITEM hdlprogItem = pView->AddTreeItem (prog, m_hdlTreeItem);

    sortCB.hParent = m_hdlTreeItem;
    sortCB.lpfnCompare = CompareFunc;
    sortCB.lParam = 0;

    // give each prog a sequence so we can sort them into list order
    for (POSITION progPos = programlist.GetHeadPosition (); progPos; )
      programlist.GetNext (progPos)->iSortSeq = iSeq++;

    m_pTreeCtrl->SortChildrenCB (&sortCB);    // sort into proper order
    if (bSelect)
      m_pTreeCtrl->Select (hdlprogItem, TVGN_CARET);   // select it

    m_pDoc->SetModifiedFlag ();

    return prog;
  } // end of CRoom::AddProgram 

// add for a new exit
CExit * CRoom::AddExit (CAreaEditorView * pView)
  {

    CExit * exit = new CExit (RUNTIME_CLASS(CRoomExitView), m_pDoc);
    exitlist.AddTail (exit);    // and add it to our list
    pView->AddTreeItem (exit, m_hdlTreeItem);
    m_pDoc->SetModifiedFlag ();

    return exit;
  } // end of CRoom::AddExit 

// add for a new description
CExtraDescription * CRoom::AddDescription (CAreaEditorView * pView)
  {

    CExtraDescription * extra = new CExtraDescription 
                      (RUNTIME_CLASS(CObjectExtraDescriptionView), m_pDoc);
    extralist.AddHead (extra);    // and add it to our list
    pView->AddTreeItem (extra, m_hdlTreeItem);
    m_pDoc->SetModifiedFlag ();

    return extra;
  } // end of CRoom::AddDescription 

// add for a new map
CRoomMap * CRoom::AddMap (CAreaEditorView * pView)
  {

    CRoomMap * map = new CRoomMap (RUNTIME_CLASS(CRoomMapView), m_pDoc);
    maplist.AddHead (map);    // and add it to our list
    pView->AddTreeItem (map, m_hdlTreeItem);
    m_pDoc->SetModifiedFlag ();

    return map;
  } // end of CRoom::AddMap 

// do a search for this item
BOOL CRoom::Search (const CString strWanted, 
                       const int iFindType,
                       const BOOL bMatchCase)
    {
CString strFound;
 
    // switch on find type
    switch (iFindType)
      {
      case eFindVnum:
      
          if (isalpha (strWanted [0]))
            {
            if (strWanted [0] != 'R')
              return FALSE;   // they aren't looking for rooms
            return atoi (strWanted.Mid (1)) == vnum; 
            }

          return atoi (strWanted) == vnum; 

      case eFindDetail:
            
            SEARCH (name);
            SEARCH (description);
            SEARCH (convert_room_flags (room_flags));
            SEARCH (RoomSectorList.ReturnName (sector_type, false));

            return FALSE;

      default:

          return CMUDitem::Search (strWanted, iFindType, bMatchCase);

      }   // end of switch

    } // end of CRoom::Search


void CRoom::Duplicate (CAreaEditorView * pView)
  {
CRoom * room = m_pDoc->AddRoom (pView, false);

  if (!room)
    return;   // could not create a new room (no vnums available?)

  room->Copy (this);
  room->m_pTreeCtrl->SetItemText (room->m_hdlTreeItem, room->Summary ());

// now duplicate programs in the room

CMUDprogram * oldProg,
            * newProg;
CString strMessage;  

  for (POSITION progPos = programlist.GetHeadPosition (); progPos; )
    {
    oldProg = programlist.GetNext (progPos);  // get a program
    newProg = new CMUDprogram (RUNTIME_CLASS(CMUDProgramView), m_pDoc);   // make a new one
    room->programlist.AddTail (newProg);   // add to new room
    pView->AddTreeItem (newProg, room->m_hdlTreeItem); // add to room's tree item
    newProg->Copy (oldProg);
    // check syntax so cross-referencing will be correct
    CheckCommandSyntax (newProg->comlist, 
                        strMessage,
                        newProg->xref_rooms,
                        newProg->xref_objects,
                        newProg->xref_rooms);
    newProg->m_pTreeCtrl->SetItemText (newProg->m_hdlTreeItem, newProg->Summary ());
    }   // end of processing each program

// now duplicate extra descriptions for the room

CExtraDescription * oldDesc,
                  * newDesc;

  for (POSITION DescPos = extralist.GetHeadPosition (); DescPos; )
    {
    oldDesc = extralist.GetNext (DescPos);  // get a description
    newDesc = new CExtraDescription (RUNTIME_CLASS(CObjectExtraDescriptionView), m_pDoc);   // make a new one
    room->extralist.AddTail (newDesc);   // add to new room
    pView->AddTreeItem (newDesc, room->m_hdlTreeItem); // add to room's tree item
    newDesc->Copy (oldDesc);
    newDesc->m_pTreeCtrl->SetItemText (newDesc->m_hdlTreeItem, newDesc->Summary ());
    }   // end of processing each description

// now duplicate exits for the room

CExit * oldExit,
      * newExit;

  for (POSITION ExitPos = exitlist.GetHeadPosition (); ExitPos; )
    {
    oldExit = exitlist.GetNext (ExitPos);  // get an exit
    newExit = new CExit (RUNTIME_CLASS(CRoomExitView), m_pDoc);   // make a new one
    room->exitlist.AddTail (newExit);   // add to new room
    pView->AddTreeItem (newExit, room->m_hdlTreeItem); // add to room's tree item
    newExit->Copy (oldExit);
    newExit->m_pTreeCtrl->SetItemText (newExit->m_hdlTreeItem, newExit->Summary ());
    }   // end of processing each exit

// now duplicate maps for the room

CRoomMap * oldMap,
      * newMap;

  for (POSITION MapPos = maplist.GetHeadPosition (); MapPos; )
    {
    oldMap = maplist.GetNext (MapPos);  // get an Map
    newMap = new CRoomMap (RUNTIME_CLASS(CRoomMapView), m_pDoc);   // make a new one
    room->maplist.AddTail (newMap);   // add to new room
    pView->AddTreeItem (newMap, room->m_hdlTreeItem); // add to room's tree item
    newMap->Copy (oldMap);
    newMap->m_pTreeCtrl->SetItemText (newMap->m_hdlTreeItem, newMap->Summary ());
    }   // end of processing each Map

  room->GoTo ();    // select it now it has been set up

  } // end of CRoom::Duplicate 

#define DUPLICATE(arg) arg = RHside->arg

// copy function for duplicating rooms
void CRoom::Copy (const CRoom * const RHside)
  {
   DUPLICATE (name);
   DUPLICATE (description);
// nb - do not duplicate vnum! - that must be unique
   DUPLICATE (room_flags);
   DUPLICATE (sector_type);
   DUPLICATE (tele_vnum);
   DUPLICATE (tele_delay);
   DUPLICATE (tunnel);
  } // end of CRoom::Copy
