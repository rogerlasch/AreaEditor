/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// AreaEditorView.cpp : implementation of the CAreaEditorView class
//

#include "stdafx.h"
#include "AreaEditor.h"

#include "MainFrm.h"

#include "AreaEditorDoc.h"
#include "AreaEditorView.h"

#include "BlankView.h"
#include "AreaView.h"
#include "MobileView.h"
#include "ObjectView.h"
#include "RoomView.h"
#include "ResetView.h"
#include "ShopView.h"
#include "RepairView.h"
#include "HelpView.h"

#include "FindDlg.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WM_USER_PUT_FOCUS_BACK (WM_USER + 1003)

/////////////////////////////////////////////////////////////////////////////
// CAreaEditorView

IMPLEMENT_DYNCREATE(CAreaEditorView, CTreeView)

BEGIN_MESSAGE_MAP(CAreaEditorView, CTreeView)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(CAreaEditorView)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDING, OnItemexpanding)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	ON_NOTIFY_REFLECT(TVN_SELCHANGING, OnSelchanging)
	ON_NOTIFY_REFLECT(TVN_KEYDOWN, OnKeydown)
	ON_COMMAND(ID_AREA_DELETE_ITEM, OnAreaDeleteItem)
	ON_UPDATE_COMMAND_UI(ID_AREA_DELETE_ITEM, OnUpdateAreaDeleteItem)
	ON_COMMAND(ID_AREA_ADD_ITEM, OnAreaAddItem)
	ON_UPDATE_COMMAND_UI(ID_AREA_ADD_ITEM, OnUpdateAreaAddItem)
	ON_COMMAND(ID_AREA_FIND, OnAreaFind)
	ON_COMMAND(ID_AREA_FIND_NEXT, OnAreaFindNext)
	ON_UPDATE_COMMAND_UI(ID_AREA_FIND_NEXT, OnUpdateAreaFindNext)
	ON_WM_CONTEXTMENU()
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	ON_UPDATE_COMMAND_UI(ID_AREA_DUPLICATE_ITEM, OnUpdateAreaDuplicateItem)
	ON_COMMAND(ID_AREA_DUPLICATE_ITEM, OnAreaDuplicateItem)
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_COMMAND(ID_VIEW_REFRESH, OnViewRefresh)
	ON_COMMAND(ID_AREA_CHECKALLAREAS, OnAreaCheckallareas)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CTreeView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAreaEditorView construction/destruction

CAreaEditorView::CAreaEditorView()
{
  m_pSplitterWindow = NULL;
  m_hdlTreeArea = NULL;

  // TODO: add construction code here

}

CAreaEditorView::~CAreaEditorView()
{
}

BOOL CAreaEditorView::PreCreateWindow(CREATESTRUCT& cs)
{

  if (!CTreeView::PreCreateWindow (cs))
      return FALSE;

  cs.style |= TVS_HASLINES | TVS_LINESATROOT | 
              TVS_HASBUTTONS | TVS_SHOWSELALWAYS | TVS_DISABLEDRAGDROP;

	return true;
}

/////////////////////////////////////////////////////////////////////////////
// CAreaEditorView drawing

void CAreaEditorView::OnDraw(CDC* pDC)
{
	CAreaEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

// This is for adding a new item (mob, object, whatever) to a nominated branch

HTREEITEM CAreaEditorView::AddTreeItem (CMUDitem * pItem, 
                                        const HTREEITEM hdlBranch,
                                        const HTREEITEM hInsertAfter)
  {
	CAreaEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

  HTREEITEM hdlNewItem;

  hdlNewItem = GetTreeCtrl().InsertItem(pItem->Summary (), hdlBranch, hInsertAfter);
  GetTreeCtrl().SetItemData (hdlNewItem, (DWORD) pItem);
  pItem->m_hdlTreeItem = hdlNewItem;
  pItem->m_pTreeCtrl = &GetTreeCtrl();

  return hdlNewItem;
  }

void CAreaEditorView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	CAreaEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

  pDoc->m_leftview = this;

  Refresh ();

}

/////////////////////////////////////////////////////////////////////////////
// CAreaEditorView printing

BOOL CAreaEditorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CAreaEditorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CAreaEditorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CAreaEditorView diagnostics

#ifdef _DEBUG
void CAreaEditorView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CAreaEditorView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CAreaEditorDoc* CAreaEditorView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAreaEditorDoc)));
	return (CAreaEditorDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAreaEditorView message handlers


void CAreaEditorView::OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void CAreaEditorView::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
CAreaEditorDoc* pDoc = GetDocument();
ASSERT_VALID(pDoc);

NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

HTREEITEM hdlItem = pNMTreeView->itemNew.hItem;

	*pResult = 0;

  m_pSplitterWindow->SetActivePane(0, 0);	// make sure info view pane is not active
  m_pSplitterWindow->DeleteView (0, 1);   // delete RH column

  CMUDitem * pItem = (CMUDitem *) GetTreeCtrl().GetItemData (hdlItem);

  if (pItem)
    {
    
    // add back the second splitter pane - the area name view
	  if (!m_pSplitterWindow->CreateView(0, 1,
        pItem->m_pViewClass, CSize(0, 0), NULL))
		    return;

    pItem->ChangeRHview (this, (CView *) m_pSplitterWindow->GetPane(0,1));
    }
  else

// <no field>

    {

    // add the second splitter pane - a blank view in column 1
	  if (!m_pSplitterWindow->CreateView(0, 1,
		    RUNTIME_CLASS(CBlankView), CSize(0, 0), NULL))
		      return;
    }   // end of not being in any interesting tree item

  // force data to be copied from member variables to window  
  CView * pView = (CView *) m_pSplitterWindow->GetPane(0,1);
  pView->UpdateData (FALSE);
  // force splitter to redraw new pane
  m_pSplitterWindow->RecalcLayout ();

  pView = (CView *) m_pSplitterWindow->GetPane(0,0);
  pView->SetFocus ();   // keep focus on LH window for now

}

void CAreaEditorView::OnSelchanging(NMHDR* pNMHDR, LRESULT* pResult) 
{
CAreaEditorDoc* pDoc = GetDocument();
ASSERT_VALID(pDoc);

  *pResult = 0;   // good update

  // if we are in middle of deleting a tree item, don't bother syntax checking it
  if (pDoc->m_bDoingDelete)
    return;

	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
  
// update previous view in RH window

  CView * pView = (CView *) m_pSplitterWindow->GetPane(0,1);

  if (pView->UpdateData (TRUE))
    return;   // updated OK
  else
    {
    *pResult = 1;   // bad update
    // *post* a message putting the focus back on the naughty control
    PostMessage (WM_USER_PUT_FOCUS_BACK, 0, (UINT) pView->GetFocus ());   
    }
}


void CAreaEditorView::OnKeydown(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_KEYDOWN* pTVKeyDown = (TV_KEYDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void CAreaEditorView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
CAreaEditorDoc* pDoc = GetDocument();
ASSERT_VALID(pDoc);
	
	if (bActivate)
	  {
    pDoc->m_active_view = this;
    Frame.FixUpTitleBar (pDoc);
	  }
	else
    {
    pDoc->m_active_view = NULL;
    }
	
	CTreeView::OnActivateView(bActivate, pActivateView, pDeactiveView);

}



void CAreaEditorView::OnAreaDeleteItem() 
{

// find which item is currently selected
HTREEITEM hdlItem = GetItem ();

  if (!hdlItem)
    return;

// get the CMUDitem from that item, if any

  CMUDitem * pItem = (CMUDitem *) GetTreeCtrl().GetItemData (hdlItem);

  if (!pItem)
    return;

  // can't delete if we can't update (sadly)

  CView * pView = (CView *) m_pSplitterWindow->GetPane(0,1);
  if (!pView->UpdateData (TRUE))
    return;

// ask if they want to delete it

  if (::AfxMessageBox (CFormat ("OK to delete %s %s?", 
                    pItem->Type (),
                    (LPCTSTR) pItem->Summary ()), 
                    MB_ICONQUESTION | MB_YESNO) != IDYES)
                    return;

  pItem->Delete ();

}

void CAreaEditorView::OnUpdateAreaDeleteItem(CCmdUI* pCmdUI) 
{
CMUDitem * pItem;

// find which item is currently selected
HTREEITEM hdlItem = GetItem ();

// get the CMUDitem from that item, if any

  if (hdlItem)
    pItem = (CMUDitem *) GetTreeCtrl().GetItemData (hdlItem);

  if (hdlItem && pItem)
    pCmdUI->SetText (CFormat ("&Remove %s\tDel", pItem->Type ()));

  pCmdUI->Enable ((hdlItem != NULL) &&    // must have a selection
                  (pItem != NULL) &&      // must be an item and not a header
                  (hdlItem != m_hdlTreeArea));    // can't delete the area itself
	
}


void CAreaEditorView::OnAreaAddItem () 
{
CAreaEditorDoc* pDoc = GetDocument();
ASSERT_VALID(pDoc);

// find which item is currently selected
HTREEITEM hdlItem = GetItem ();

  // no selected item - cannot add another one like it!
  if (!hdlItem)
    return;

  // cannot add anything other than an area and helps if we don't have an area
  if ((hdlItem != m_hdlTreeArea) && (hdlItem != m_hdlTreeHelps) && !pDoc->m_Area)
    return;

// ================== new AREA ================================================
  if (hdlItem == m_hdlTreeArea)
      {
      if (pDoc->m_Area)
        return;   // cannot add a second area
      pDoc->m_Area = new CArea (RUNTIME_CLASS(CAreaView), pDoc);
      pDoc->m_Area->strAreaName = "area name";
      pDoc->m_Area->obj_low_vnum = 9900;
      pDoc->m_Area->mob_low_vnum = 9900;
      pDoc->m_Area->room_low_vnum = 9900;
      pDoc->m_Area->obj_hi_vnum = 9950;
      pDoc->m_Area->mob_hi_vnum = 9950;
      pDoc->m_Area->room_hi_vnum = 9950;
      GetTreeCtrl().SetItemData (m_hdlTreeArea, (DWORD) pDoc->m_Area);
      pDoc->m_Area->m_hdlTreeItem = m_hdlTreeArea;
      pDoc->m_Area->m_pTreeCtrl = &GetTreeCtrl();
      GetTreeCtrl().Select (m_hdlTreeHelps, TVGN_CARET);  // select away from area
      GetTreeCtrl().Select (m_hdlTreeArea, TVGN_CARET);   // reselect to display it
      pDoc->SetModifiedFlag ();
      } // end of area being selected
// ================== new MOBILE ================================================
  else if (hdlItem == m_hdlTreeMobiles)
    pDoc->AddMobile (this, true);
// ================== new OBJECT ================================================
  else if (hdlItem == m_hdlTreeObjects)
    pDoc->AddObject (this, true);
// ================== new ROOM ================================================
  else if (hdlItem == m_hdlTreeRooms)
    pDoc->AddRoom (this, true);
// ================== new RESET ================================================
  else if (hdlItem == m_hdlTreeResets)
    {
    CReset * reset = new CReset (RUNTIME_CLASS(CResetView), pDoc);
    pDoc->m_ResetList.AddHead (reset);    // and add it to our list
    HTREEITEM hdlResetItem = AddTreeItem (reset, m_hdlTreeResets, TVI_FIRST);
    GetTreeCtrl().Select (hdlResetItem, TVGN_CARET);   // select it
    pDoc->SetModifiedFlag ();
    }   // end of new reset
// ================== new SHOP ================================================
  else if (hdlItem == m_hdlTreeShops)
    {
    CShop * shop = new CShop (RUNTIME_CLASS(CShopView), pDoc);
    pDoc->m_ShopList.AddTail (shop);    // and add it to our list
    HTREEITEM hdlShopItem = AddTreeItem (shop, m_hdlTreeShops);
    GetTreeCtrl().Select (hdlShopItem, TVGN_CARET);   // select it
    pDoc->SetModifiedFlag ();
    }   // end of new shop
// ================== new REPAIR ================================================
  else if (hdlItem == m_hdlTreeRepairs)
    {
    CRepair * repair = new CRepair (RUNTIME_CLASS(CRepairView), pDoc);
    pDoc->m_RepairList.AddTail (repair);    // and add it to our list
    HTREEITEM hdlRepairItem = AddTreeItem (repair, m_hdlTreeRepairs);
    GetTreeCtrl().Select (hdlRepairItem, TVGN_CARET);   // select it
    pDoc->SetModifiedFlag ();
    }   // end of new repair
// ================== new HELP ================================================
  else if (hdlItem == m_hdlTreeHelps)
    {
    CHelp * help = new CHelp (RUNTIME_CLASS(CHelpView), pDoc);
    pDoc->m_HelpList.AddTail (help);    // and add it to our list
    HTREEITEM hdlHelpItem = AddTreeItem (help, m_hdlTreeHelps);
    GetTreeCtrl().Select (hdlHelpItem, TVGN_CARET);   // select it
    pDoc->SetModifiedFlag ();
    }   // end of new help
  else
    {   // not a major heading - minor things (eg. mobs) handle their own adding
    CMUDitem * pItem = (CMUDitem *) GetTreeCtrl().GetItemData (hdlItem);

    // no item - give up
    if (!pItem)
      return;

    // cannot add - give up
    if (!pItem->CanAdd ())
      return;

    pItem->Add (this);    // add the new item

    }   // end of not being a major heading

}   // end of CAreaEditorView::OnAreaAddItem

void CAreaEditorView::OnUpdateAreaAddItem(CCmdUI* pCmdUI) 
{
CAreaEditorDoc* pDoc = GetDocument();
ASSERT_VALID(pDoc);

// find which item is currently selected
HTREEITEM hdlItem = GetItem ();

// set menu text
CString strAddType;

  if (hdlItem == m_hdlTreeArea)
    strAddType = "area";
  else if (hdlItem == m_hdlTreeMobiles)
    strAddType = "mobile";
  else if (hdlItem == m_hdlTreeObjects)
    strAddType = "object";
  else if (hdlItem == m_hdlTreeRooms)
    strAddType = "room";
  else if (hdlItem == m_hdlTreeResets)
    strAddType = "reset";
  else if (hdlItem == m_hdlTreeShops)
    strAddType = "shop";
  else if (hdlItem == m_hdlTreeRepairs)
    strAddType = "repair";
  else if (hdlItem == m_hdlTreeHelps)
    strAddType = "help";
  else
    {   // not a major heading - minor things (eg. mobs) handle their own adding
    CMUDitem * pItem = (CMUDitem *) GetTreeCtrl().GetItemData (hdlItem);

    // no item - give up
    if (pItem || pItem->CanAdd ())
      strAddType = pItem->AddDescription ();   // add the new item

    }   // end of not being a major heading


  if (strAddType.IsEmpty ())
    pCmdUI->SetText ("Cannot &Add\tCtrl+A");
  else
    pCmdUI->SetText ("&Add " + strAddType + "\tCtrl+A");

  // no selected item - cannot add another one like it!
  if (!hdlItem)
    {
    pCmdUI->Enable (false); 
    return;
    }

  // cannot add a second area
  if ((hdlItem == m_hdlTreeArea) && pDoc->m_Area)
    {
    pCmdUI->Enable (false); 
    return;
    }

  // cannot add anything other than an area and helps if we don't have an area
  if ((hdlItem != m_hdlTreeArea) && (hdlItem != m_hdlTreeHelps) && !pDoc->m_Area)
    {
    pCmdUI->Enable (false); 
    return;
    }

  // can add most other things

  CMUDitem * pItem = (CMUDitem *) GetTreeCtrl().GetItemData (hdlItem);

  // no item - we can probably add - it will be an area header
  if (!pItem)
    {
    pCmdUI->Enable (true); 
    return;
    }

  // let them know if we can add to it
  pCmdUI->Enable (pItem->CanAdd ()); 
	
}

// find does the dialog box, and then just calls "find next"
void CAreaEditorView::OnAreaFind() 
{
CAreaEditorDoc* pDoc = GetDocument();
ASSERT_VALID(pDoc);

CFindDlg dlg;

  if (!App.m_strFindText.IsEmpty ())
    dlg.m_strFindText = App.m_strFindText.GetTail ();  // default find text
  dlg.m_bMatchCase  = App.m_bMatchCase;   // default case
  dlg.m_iFindType   = App.m_iFindType;    // default find type
  dlg.m_bAllAreas   = App.m_bAllAreas;    // default all areas

  if (dlg.DoModal () != IDOK)
    return;

  // remember find text, if it wasn't the same as last time
  if (App.m_strFindText.IsEmpty () ||
      App.m_strFindText.GetTail () != dlg.m_strFindText)
    App.m_strFindText.AddTail (dlg.m_strFindText);   // save find text
  App.m_bMatchCase  = dlg.m_bMatchCase ;   // save case
  App.m_iFindType   = dlg.m_iFindType;    // default find type
  App.m_bAllAreas   = dlg.m_bAllAreas;    // default all areas

  OnAreaFindNext ();

}

// find next finds the next item *after* this one, matching the specified text
void CAreaEditorView::OnAreaFindNext() 
{

// start off with current document

CAreaEditorDoc* pDoc = GetDocument();
ASSERT_VALID(pDoc);

// start off with current tree control
CTreeCtrl * pTreeCtrl = & GetTreeCtrl ();

// find which item is currently selected
HTREEITEM hdlItem = GetItem ();

  // none selected - start at root
  if (!hdlItem)
    hdlItem = pTreeCtrl->GetNextItem (NULL, TVGN_ROOT);
	  
  if (!hdlItem)
    return;   // no root? strange

// remember where we started, for wrap around
HTREEITEM hdlStartPoint = hdlItem;

CString strWanted = App.m_strFindText.GetTail ();
CString strFound;

  // if not case-sensitive, make upper case
  if (!App.m_bMatchCase || (App.m_iFindType == eFindVnum))
    strWanted.MakeUpper ();

  // save some work later by fixing vnum field
  if (App.m_iFindType == eFindVnum)
    {
    strWanted.TrimLeft ();
    strWanted.TrimRight ();

    // vnum can be M1234 for mob 1234

    CString strRestOfVnum = strWanted.Mid (1);
    strRestOfVnum.TrimLeft ();

    strWanted = strWanted [0];    // first character
    strWanted += strRestOfVnum;   // rest with leading spaces removed
    }

  while (true)
    {

    // first look for children of the current item
    if (pTreeCtrl->ItemHasChildren (hdlItem))
      hdlItem = pTreeCtrl->GetChildItem (hdlItem);
    else
      {
      while (true)
        {
        HTREEITEM hdlCurrentItem = hdlItem;

      // next look for siblings of the current item
        hdlItem = pTreeCtrl->GetNextItem (hdlItem, TVGN_NEXT);
        if (hdlItem)
          break;    // found one - exit loop
        // no siblings - get parent - and then next sibling
        if (!hdlItem)
          {
          hdlItem = pTreeCtrl->GetParentItem (hdlCurrentItem);
          if (!hdlItem)
            break;    // no parent - must be at end of tree control
          } // end of no getting parent
        } // end of finding a sibling somewhere
      }

    // end of tree control - start at root (wrap around), or change areas
    if (!hdlItem)
      {
      if (App.m_bAllAreas)
        {    
        POSITION docPos;
        // find this area
         for (docPos = App.m_pDocTemplate->GetFirstDocPosition();
            docPos != NULL; )
          {

          CAreaEditorDoc * pThisDoc = (CAreaEditorDoc *) App.m_pDocTemplate->GetNextDoc(docPos);
          
          if (pThisDoc == pDoc)
            break;
          } // end of doing each document

        // now, docPos should be the position of the next area, or NULL if this was
        // the last one

        if (!docPos)    // wrap to first area
          docPos = App.m_pDocTemplate->GetFirstDocPosition();


        if (!docPos)
          return;   // no areas? very strange

        // now get next area
        pDoc = (CAreaEditorDoc *) App.m_pDocTemplate->GetNextDoc(docPos);

        // get new tree control
        pTreeCtrl = & pDoc->m_leftview->GetTreeCtrl ();
        }   // end of all areas wanted

      hdlItem = pTreeCtrl->GetNextItem (NULL, TVGN_ROOT);

      }
  
    if (hdlItem == hdlStartPoint)
      break;    // stop when we reach starting point again

    // find associated MUD item, if any
    CMUDitem * pItem = (CMUDitem *) pTreeCtrl->GetItemData (hdlItem);
    
    if (!pItem)
      continue;   // ignore those without it

    // do the appropriate sort of search
    if (pItem->Search (strWanted, App.m_iFindType, App.m_bMatchCase))
      {
      pItem->GoTo ();   // go to this item
//      pTreeCtrl->Select (hdlItem, TVGN_CARET);
      return;
      }   // end of found wanted string

    } // end of looking for an item


  CString strNotFoundType;

  switch (App.m_iFindType)
    {
    case eFindSummary:  strNotFoundType = " in item summaries"; break; 
    case eFindDetail:   strNotFoundType = " in item detail"; break; 
    case eFindProgram:  strNotFoundType = " in MUD programs"; break; 
    case eFindVnum:     
      switch (toupper (App.m_strFindText.GetTail () [0]))
        {
        case 'M':  strNotFoundType = " (mob vnum)"; break;
        case 'R':  strNotFoundType = " (room vnum)"; break;
        case 'O':  strNotFoundType = " (object vnum)"; break;
        default: strNotFoundType = " in item vnums"; break; 
        } // end of switching on 1st char of vnum
      break;

    } // end of switch

  ::AfxMessageBox (CFormat ("Could not find \"%s\"%s.", 
                  (LPCTSTR) App.m_strFindText.GetTail (),
                  (LPCTSTR) strNotFoundType),
                    MB_ICONINFORMATION);
	
}

void CAreaEditorView::OnUpdateAreaFindNext(CCmdUI* pCmdUI) 
{
CAreaEditorDoc* pDoc = GetDocument();
ASSERT_VALID(pDoc);

  pCmdUI->Enable (!App.m_strFindText.IsEmpty ());
	
}

void CAreaEditorView::OnContextMenu(CWnd*, CPoint point)
{

	// CG: This block was added by the Pop-up Menu component
	{
		if (point.x == -1 && point.y == -1){
			//keystroke invocation
			CRect rect;
			GetClientRect(rect);
			ClientToScreen(rect);

			point = rect.TopLeft();
			point.Offset(5, 5);
		}

		CMenu menu;
		VERIFY(menu.LoadMenu(CG_IDR_POPUP_AREA_EDITOR_VIEW));

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = this;

		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			pWndPopupOwner);
	}
}


void CAreaEditorView::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{

CPoint pt;

  GetCursorPos (&pt);

HTREEITEM hdlDropItem =  GetTreeCtrl().GetDropHilightItem( );

  if (hdlDropItem)
    if (GetTreeCtrl().Select (hdlDropItem, TVGN_CARET))
      OnContextMenu (this, pt);

	*pResult = 1;
}


//  return the selected item

HTREEITEM CAreaEditorView::GetItem (void) const
  {
  return GetTreeCtrl().GetNextItem (NULL, TVGN_CARET);
  }


void CAreaEditorView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
CAreaEditorDoc* pDoc = GetDocument();
ASSERT_VALID(pDoc);

    CString strOldTitle;
    CString strNewTitle = "Untitled area";

    // use area name for window name, otherwise document name, otherwise "untitled"
    /*
    if (pDoc->m_Area && !pDoc->m_Area->strAreaName.IsEmpty ())
      strNewTitle = pDoc->m_Area->strAreaName;
    else
    */

    // Show full pathname to area document in title
    if (!pDoc->GetPathName ().IsEmpty ())
      strNewTitle = pDoc->GetPathName ();

    GetParentFrame ()->GetWindowText (strOldTitle);

    // amend title if necessary (avoid flicker)
    if (strOldTitle != strNewTitle)
      GetParentFrame ()->SetWindowText (strNewTitle);
	
	
}


void CAreaEditorView::OnUpdateAreaDuplicateItem(CCmdUI* pCmdUI) 
{
CAreaEditorDoc* pDoc = GetDocument();
ASSERT_VALID(pDoc);

// find which item is currently selected
HTREEITEM hdlItem = GetItem ();

  // no selected item - cannot duplicate it!
  if (!hdlItem)
    {
    pCmdUI->Enable (false); 
    pCmdUI->SetText ("Cannot &Duplicate\tCtrl+D");
    return;
    }

  // can duplicate most other things

  CMUDitem * pItem = (CMUDitem *) GetTreeCtrl().GetItemData (hdlItem);

  // no item - we can't duplicate it
  if (!pItem)
    {
    pCmdUI->Enable (false); 
    pCmdUI->SetText ("Cannot &Duplicate\tCtrl+D");
    return;
    }

  // let them know if we can add to it
  pCmdUI->Enable (pItem->CanDuplicate ()); 

  pCmdUI->SetText (CFormat ("&Duplicate %s\tCtrl+D", pItem->Type ()));

	
}

void CAreaEditorView::OnAreaDuplicateItem() 
{
CAreaEditorDoc* pDoc = GetDocument();
ASSERT_VALID(pDoc);

// find which item is currently selected
HTREEITEM hdlItem = GetItem ();

  // no selected item - cannot add another one like it!
  if (!hdlItem)
    return;

  CMUDitem * pItem = (CMUDitem *) GetTreeCtrl().GetItemData (hdlItem);

  // no item - give up
  if (!pItem)
    return;

  // cannot duplicate - give up
  if (!pItem->CanDuplicate ())
    return;

  pItem->Duplicate (this);    // duplicate the item
  
}


BOOL CAreaEditorView::PreTranslateMessage(MSG* pMsg) 
{
 if (pMsg->message == WM_USER_PUT_FOCUS_BACK)
   {
   CView * pView = (CView *) m_pSplitterWindow->GetPane(0,1);

   pView->PostMessage (WM_SETFOCUS, 0, 0);   

   CWnd * pNewFocusWindow = (CWnd *) pMsg->lParam;
   pNewFocusWindow->SetFocus ();


   return TRUE;   // message was handled
   }
	
	return CTreeView::PreTranslateMessage(pMsg);
}


void CAreaEditorView::Refresh (void)
  {
	CTreeView::OnInitialUpdate();

	CAreaEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

  SetStatusMsg ("Initialising view");

  if (m_hdlTreeArea)
    GetTreeCtrl().Select (m_hdlTreeArea, TVGN_CARET);

	CWaitCursor wait;

  GetTreeCtrl().DeleteAllItems ();
  m_hdlTreeArea = GetTreeCtrl().InsertItem("Area");
  m_hdlTreeHelps = GetTreeCtrl().InsertItem("Helps");
  m_hdlTreeMobiles = GetTreeCtrl().InsertItem("Mobiles");
//  m_hdlTreeMudprogs = GetTreeCtrl().InsertItem("Mudprogs");
  m_hdlTreeObjects = GetTreeCtrl().InsertItem("Objects");
//  m_hdlTreeObjprogs = GetTreeCtrl().InsertItem("Objprogs");
  m_hdlTreeResets = GetTreeCtrl().InsertItem("Resets");
  m_hdlTreeRooms = GetTreeCtrl().InsertItem("Rooms");
  m_hdlTreeShops = GetTreeCtrl().InsertItem("Shops");
  m_hdlTreeRepairs = GetTreeCtrl().InsertItem("Repairs");

  if (pDoc->m_Area)
    {
    GetTreeCtrl().SetItemData (m_hdlTreeArea, (DWORD) pDoc->m_Area);
    pDoc->m_Area->m_hdlTreeItem = m_hdlTreeArea;
    pDoc->m_Area->m_pTreeCtrl = &GetTreeCtrl();
    }


// ========================================================================

  SetStatusMsg ("Setting up mobiles");

  // add the mobiles list

CMobile * mob;
HTREEITEM hdlMobItem;

  for (POSITION mobPos = pDoc->m_MobList.GetHeadPosition (); mobPos; )
    {
    mob = pDoc->m_MobList.GetNext (mobPos);
    hdlMobItem = AddTreeItem (mob, m_hdlTreeMobiles);

// add programs to the mobile

    for (POSITION progPos = mob->programlist.GetHeadPosition (); progPos; )
      AddTreeItem (mob->programlist.GetNext (progPos), hdlMobItem);

    }   // end of adding each mob

// ========================================================================

  SetStatusMsg ("Setting up objects");

  // add the objects list

CMUDObject * obj;
HTREEITEM hdlObjItem;

  for (POSITION objPos = pDoc->m_ObjectList.GetHeadPosition (); objPos; )
    {
    obj = pDoc->m_ObjectList.GetNext (objPos);
    hdlObjItem = AddTreeItem (obj, m_hdlTreeObjects);

// add extra descriptions  to the object

    for (POSITION extraPos = obj->extralist.GetHeadPosition (); extraPos; )
      AddTreeItem (obj->extralist.GetNext (extraPos), hdlObjItem);

// add affects to the object

    for (POSITION affectPos = obj->affectlist.GetHeadPosition (); affectPos; )
      AddTreeItem (obj->affectlist.GetNext (affectPos), hdlObjItem);

    // add programs to the object

    for (POSITION progPos = obj->programlist.GetHeadPosition (); progPos; )
      AddTreeItem (obj->programlist.GetNext (progPos), hdlObjItem);

    }   // end of adding each object

// ========================================================================

  SetStatusMsg ("Setting up rooms");

// add the rooms list

CRoom * room;
HTREEITEM hdlRoomItem;

  for (POSITION roomPos = pDoc->m_RoomList.GetHeadPosition (); roomPos; )
    {
    room = pDoc->m_RoomList.GetNext (roomPos);
    hdlRoomItem = AddTreeItem (room, m_hdlTreeRooms);

// add extra descriptions to the room

    for (POSITION extraPos = room->extralist.GetHeadPosition (); extraPos; )
      AddTreeItem (room->extralist.GetNext (extraPos), hdlRoomItem);

// add exits to the room


    for (POSITION exitPos = room->exitlist.GetHeadPosition (); exitPos; )
      AddTreeItem (room->exitlist.GetNext (exitPos), hdlRoomItem);

    // add programs to the object

    for (POSITION progPos = room->programlist.GetHeadPosition (); progPos; )
      AddTreeItem (room->programlist.GetNext (progPos), hdlRoomItem);

    }   // end of adding each room

// ========================================================================

  SetStatusMsg ("Setting up resets");

  // add the resets list

  for (POSITION resetPos = pDoc->m_ResetList.GetHeadPosition (); resetPos; )
    AddTreeItem (pDoc->m_ResetList.GetNext (resetPos), m_hdlTreeResets);

// ========================================================================

  SetStatusMsg ("Setting up shops");

  // add the shops list

  for (POSITION shopPos = pDoc->m_ShopList.GetHeadPosition (); shopPos; )
    AddTreeItem (pDoc->m_ShopList.GetNext (shopPos), m_hdlTreeShops);


// ========================================================================

  SetStatusMsg ("Setting up repairs");

  // add the repairs list

  for (POSITION repairPos = pDoc->m_RepairList.GetHeadPosition (); repairPos; )
    AddTreeItem (pDoc->m_RepairList.GetNext (repairPos), m_hdlTreeRepairs);

// ========================================================================

  SetStatusMsg ("Setting up helps");

  // add the helps list

  for (POSITION helpPos = pDoc->m_HelpList.GetHeadPosition (); helpPos; )
    AddTreeItem (pDoc->m_HelpList.GetNext (helpPos), m_hdlTreeHelps);


// ========================================================================

// select "area" node

  GetTreeCtrl().Select (m_hdlTreeArea, TVGN_CARET);

  SetStatusMsg ("For Help, press F1");

  GetTreeCtrl().Select (m_hdlTreeArea, TVGN_CARET);

  }   // end of CAreaEditorView::Refresh 

void CAreaEditorView::OnViewRefresh() 
{
  Refresh ();	
}

void CAreaEditorView::OnAreaCheckallareas() 
{
  CheckAreas (NULL);	
}
