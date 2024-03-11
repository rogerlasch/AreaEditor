/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#include "stdafx.h"
#include "AreaEditor.h"

#include "AreaEditorDoc.h"

#include "ObjectExtraDescriptionView.h"

void CExtraDescription::ChangeRHview (CAreaEditorView * pLHview, CView * pwhichView)
  {
  CObjectExtraDescriptionView * pView = (CObjectExtraDescriptionView *) pwhichView;

	ASSERT(pView->IsKindOf(RUNTIME_CLASS(CObjectExtraDescriptionView)));

  pView->m_extradescription = this;

  }

CString CExtraDescription::Summary (void)
  {
  return CFormat ("Desc: %s", (LPCTSTR) keyword);
  }


// do a search for this item
BOOL CExtraDescription::Search (const CString strWanted, 
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

    return FALSE;

    } // end of CExtraDescription::Search


#define DUPLICATE(arg) arg = RHside->arg

// copy function for duplicating descriptions
void CExtraDescription::Copy (const CExtraDescription * const RHside)
  {
  DUPLICATE (keyword);
  DUPLICATE (description);
  }

// clone this description
void CExtraDescription::Duplicate (CAreaEditorView * pView)
  {

  HTREEITEM hdlItem = m_pTreeCtrl->GetParentItem (m_hdlTreeItem);

  if (!hdlItem)
    return;

  // find associated MUD item, if any
  CMUDitem * pItem = (CMUDitem *) m_pTreeCtrl->GetItemData (hdlItem);
  
  if (!pItem)
    return; 

  CExtraDescription * newdescription = pItem->AddDescription (pView);

  if (newdescription)
    {
    newdescription->Copy (this);    // copy existing description over
    newdescription->m_pTreeCtrl->SetItemText (newdescription->m_hdlTreeItem, 
                                              newdescription->Summary ());
    newdescription->GoTo ();
    }

  } // end of CExtraDescription::Duplicate 