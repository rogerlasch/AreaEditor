/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#include "stdafx.h"
#include "AreaEditor.h"

#include "AreaEditorDoc.h"

#include "RoomMapView.h"

// constructor
CRoomMap::CRoomMap (CRuntimeClass* pViewClass, CAreaEditorDoc * pDoc) 
    : CMUDitem (pViewClass, pDoc) 
  {
  vnum = 0;		/* which map this room belongs to */
  x = 0;		/* horizontal coordinate */
  y = 0;		/* vertical coordinate */
  entry = 'N';		/* code that shows up on map */ 
  } // end of constructor


void CRoomMap::ChangeRHview (CAreaEditorView * pLHview, CView * pwhichView)
  {
  CRoomMapView * pView = (CRoomMapView *) pwhichView;

	ASSERT(pView->IsKindOf(RUNTIME_CLASS(CRoomMapView)));

  pView->m_map = this;

  }

CString CRoomMap::Summary (void)
  {
  return CFormat ("#%i", 
                  vnum);
  }


#define DUPLICATE(arg) arg = RHside->arg

// copy function for duplicating maps
void CRoomMap::Copy (const CRoomMap * const RHside)
  {
  DUPLICATE (vnum);
  DUPLICATE (x);
  DUPLICATE (y);
  DUPLICATE (entry);
  } // end of CRoomMap::Copy


// clone this map
void CRoomMap::Duplicate (CAreaEditorView * pView)
  {

  HTREEITEM hdlItem = m_pTreeCtrl->GetParentItem (m_hdlTreeItem);

  if (!hdlItem)
    return;

  // find associated MUD item, if any
  CMUDitem * pItem = (CMUDitem *) m_pTreeCtrl->GetItemData (hdlItem);
  
  if (!pItem)
    return; 

  CRoomMap * newmap = pItem->AddMap (pView);

  if (newmap)
    {
    newmap->Copy (this);    // copy existing map over
    newmap->m_pTreeCtrl->SetItemText (newmap->m_hdlTreeItem, 
                                              newmap->Summary ());
    newmap->GoTo ();
    }

  } // end of CRoomMap::Duplicate 