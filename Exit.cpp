/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#include "stdafx.h"
#include "AreaEditor.h"

#include "AreaEditorDoc.h"
#include "defaults.h"

#include "RoomExitView.h"

// constructor

CExit::CExit (CRuntimeClass* pViewClass, CAreaEditorDoc * pDoc)
    : CMUDitem (pViewClass, pDoc) 
  {

  keyword = strExitDefaultKeywords;	/* Keywords for exit or door	*/
  description = strExitDefaultDescription;	/* Description of exit		*/
  vnum = -1;		/* Vnum of room exit leads to	*/
  exit_info = 0;	/* door states & other flags	*/
  key = 0;		/* Key vnum			*/
  vdir = 0;  // DIR_NORTH - Physical "direction"
  distance = 0;	/* how far to the next room	*/

  } // end of constructor


void CExit::ChangeRHview (CAreaEditorView * pLHview, CView * pwhichView)
  {
  CRoomExitView * pView = (CRoomExitView *) pwhichView;

	ASSERT(pView->IsKindOf(RUNTIME_CLASS(CRoomExitView)));

  pView->m_exit = this;

  pView->m_pLHview = pLHview;

  pView->CreatePages ();   // add the tab control pages

  pView->ShowPages (m_pDoc);

  }

CString CExit::Summary (void)
  {
CRoom * exitroom;
CString strExitName;
CString strExitDirection;

  strExitDirection = RoomDirectionList.ReturnName (vdir, false);

  if (exitroom = m_pDoc->get_room_index (vnum))
    strExitName = exitroom->name;
  else
  if (exitroom = FindRoom (vnum))
    strExitName = (FullRoomName (exitroom));
  else
    strExitName = "not in area";

  if (!keyword.IsEmpty ())
    strExitDirection += " (" + keyword + ")";

  return CFormat ("%s to #%i (%s)",
                  (LPCTSTR) strExitDirection,
                  vnum,
                  (LPCTSTR) strExitName);
  }



// do a search for this item
BOOL CExit::Search (const CString strWanted, 
                       const int iFindType,
                       const BOOL bMatchCase)
    {
CString strFound;
    
    // we only care about detailed searches here
    if (iFindType != eFindDetail)
      return CMUDitem::Search (strWanted, iFindType, bMatchCase);
  
    SEARCH (keyword);
    SEARCH (description);
    SEARCH (Summary ());
    SEARCH (RoomDirectionList.ReturnName (vdir, false));
    SEARCH (convert_exit_flags (exit_info));

    return FALSE;

    } // end of CExit::Search


#define DUPLICATE(arg) arg = RHside->arg

// copy function for duplicating exits
void CExit::Copy (const CExit * const RHside)
  {
  DUPLICATE (keyword);
  DUPLICATE (description);
  DUPLICATE (vnum);
  DUPLICATE (exit_info);
  DUPLICATE (key);
  DUPLICATE (vdir);
  DUPLICATE (distance);
  } // end of CExit::Copy


// clone this exit
void CExit::Duplicate (CAreaEditorView * pView)
  {

  HTREEITEM hdlItem = m_pTreeCtrl->GetParentItem (m_hdlTreeItem);

  if (!hdlItem)
    return;

  // find associated MUD item, if any
  CMUDitem * pItem = (CMUDitem *) m_pTreeCtrl->GetItemData (hdlItem);
  
  if (!pItem)
    return; 

  CExit * newexit = pItem->AddExit (pView);

  if (newexit)
    {
    newexit->Copy (this);    // copy existing exit over
    newexit->m_pTreeCtrl->SetItemText (newexit->m_hdlTreeItem, 
                                              newexit->Summary ());
    newexit->GoTo ();
    }

  } // end of CExit::Duplicate 