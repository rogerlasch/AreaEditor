/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#include "stdafx.h"
#include "AreaEditor.h"

#include "AreaEditorDoc.h"

CMUDitem::CMUDitem (CRuntimeClass* pViewClass, CAreaEditorDoc * pDoc) 
                            
  { 
  m_pViewClass = pViewClass; 
  m_pDoc = pDoc;
  m_pTreeCtrl = NULL;
  m_hdlTreeItem = NULL;
  m_bReferenced = false;
  }   // end of constructor


void CMUDitem::Delete (void)
  {

  // find our tree control parent, if any
  HTREEITEM hdlParentItem = m_pTreeCtrl->GetParentItem(m_hdlTreeItem);

  // let our owner know that a sub-item (ie. us) was (about to be) deleted
  if (hdlParentItem)
    {
    CMUDitem * pItem = (CMUDitem *) m_pTreeCtrl->GetItemData (hdlParentItem);
    if (pItem)
      pItem->SubItemDeleted (this);
    }

  // we get into a recursive situation if there is an error in a MUD
  // program found whilst trying to delete a MUD program

  m_pDoc->m_bDoingDelete = true;
  m_pTreeCtrl->DeleteItem (m_hdlTreeItem);
  m_hdlTreeItem = NULL;
  m_pDoc->m_bDoingDelete = false;

  m_pDoc->SetModifiedFlag ();

  delete this;
  } // end of CMUDitem::Delete 

// go to this item in the tree control

void CMUDitem::GoTo (void)
  {

// new cross-area stuff - make sure correct document is visible

		POSITION pos = m_pDoc->GetFirstViewPosition();
		if (pos != NULL)
		{
			CView* pView = m_pDoc->GetNextView(pos); // get first one
			ASSERT_VALID(pView);
			CFrameWnd* pFrame = pView->GetParentFrame();
      // different frame? - activate it
			if (pFrame != (CFrameWnd*)AfxGetApp()->m_pMainWnd)
			{
				ASSERT_KINDOF(CFrameWnd, pFrame);
				pFrame->ActivateFrame();
			}
		}

  // now go to it
  if (m_pTreeCtrl && m_hdlTreeItem)
   m_pTreeCtrl->Select (m_hdlTreeItem, TVGN_CARET);

  }

// do a search for this item
BOOL CMUDitem::Search (const CString strWanted, 
                       const int iFindType,
                       const BOOL bMatchCase)
    {
    
    // the base class will only search summaries and same for detailed search
    if (iFindType != eFindSummary && iFindType != eFindDetail)
      return FALSE;

    CString strFound = Summary ();

    // if not case-sensitive, make upper case
    if (!bMatchCase)
      strFound.MakeUpper ();

    return strFound.Find (strWanted) != -1;

    }   // end of CMUDitem::Search 


void CMUDitem::AddToListBox (CListBox & ctlListBox, 
                             const char * strDescription,
                             const bool bSelectIt)
  {

int nItem;

  // no description supplied, take item summary
  if (strDescription [0] == 0)
    nItem = ctlListBox.AddString (Summary ());
  else
    nItem = ctlListBox.AddString (strDescription);

  // now set item data to this item, if we added it OK
  if (nItem != LB_ERR && nItem != LB_ERRSPACE)
    {
    ctlListBox.SetItemData (nItem, (DWORD) this);

    if (bSelectIt)
      ctlListBox.SetCurSel (nItem);

    }   // end of successful add

  } // end of CMUDitem::AddItemToListBox