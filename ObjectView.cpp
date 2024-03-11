/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// ObjectView.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "AreaEditorDoc.h"

#include "ObjectView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define SUMMARY_PAGE 0

/////////////////////////////////////////////////////////////////////////////
// CObjectView

IMPLEMENT_DYNCREATE(CObjectView, CFormView)

CObjectView::CObjectView()
	: CFormView(CObjectView::IDD)
{
	//{{AFX_DATA_INIT(CObjectView)
	//}}AFX_DATA_INIT

  m_bEditingText = false;

}

CObjectView::~CObjectView()
{

	// Delete the memory space for the C++ dialog object.  The actual dialog
	// (or page) will be destroyed when tab control is destroyed because it
	// is the child window of the tab control (see code in CreatePages()).

	for (int i = 0; i < m_DlgArray.GetSize(); i++)
		delete m_DlgArray[i];

}

void CObjectView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CObjectView)
	DDX_Control(pDX, IDC_OBJECT_TABS, m_ctlTabControl);
	//}}AFX_DATA_MAP

  // send update to child pane

  if (pDX->m_bSaveAndValidate)
    {
    int sel_index = m_ctlTabControl.GetCurSel();
    if (sel_index != -1)
      {
      CDialog * dlg = m_DlgArray[sel_index]->m_pDlg;

      if (dlg->UpdateData (TRUE))
        m_object->m_pTreeCtrl->SetItemText (m_object->m_hdlTreeItem, m_object->Summary ());
      else
        {
        // *post* a message putting the focus back on the naughty control
        PostMessage (WM_SETFOCUS, 0, 0);   
        pDX->Fail();   // bad update - fail this one
        }
      }
    }   // end of saving and validating

}


BEGIN_MESSAGE_MAP(CObjectView, CFormView)
	//{{AFX_MSG_MAP(CObjectView)
	ON_NOTIFY(TCN_SELCHANGE, IDC_OBJECT_TABS, OnSelchangeObjectTabs)
	ON_NOTIFY(TCN_SELCHANGING, IDC_OBJECT_TABS, OnSelchangingObjectTabs)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CObjectView diagnostics

#ifdef _DEBUG
void CObjectView::AssertValid() const
{
	CFormView::AssertValid();
}

void CObjectView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CObjectView message handlers

void CObjectView::OnSelchangeObjectTabs(NMHDR* pNMHDR, LRESULT* pResult) 
{

	// Call GetCurSel() will return the index of the page that is newly
	// selected.  This page will be visible soon.
	int sel_index = m_ctlTabControl.GetCurSel();

  if (sel_index == -1)
    return;

  m_pDoc->m_iCurrentObjectTab = sel_index;

  if (!m_DlgArray[sel_index]->m_bCreated)
    {
  	VERIFY(m_DlgArray[sel_index]->m_pDlg->Create(m_DlgArray[sel_index]->m_DlgID, 
            this)); 
    m_DlgArray[sel_index]->m_bCreated = true;
    }


	// Get the rectangle size of the tab control so we know the position 
	// and size of the page that will be shown.
	RECT rc;
	m_ctlTabControl.GetItemRect (sel_index, &rc);

	m_DlgArray[sel_index]->m_pDlg->SetWindowPos (
		NULL, 
		5, rc.bottom + 5, 0, 0, 
		SWP_NOSIZE | SWP_NOZORDER | SWP_SHOWWINDOW | SWP_NOACTIVATE);


  CDialog * dlg = m_DlgArray[sel_index]->m_pDlg;
  if (dlg)
    dlg->UpdateData (FALSE);    // force reload of contents

//	*pResult = TRUE;	// no return value according to online documentation
	
}

// --------------------------------------------------------------------------
// CMobileView::OnTabSelChanging
//	
// This function will hide the currently visible page in the tab control
// (CTabCtrl) so the newly selected page can be shown in OnTabSelChange().
// --------------------------------------------------------------------------

void CObjectView::OnSelchangingObjectTabs(NMHDR* pNMHDR, LRESULT* pResult) 
{
  *pResult = FALSE;		// return FALSE to allow seletion to change

  // Call GetCurSel() here will return the index of the page that
	// will be hidden soon.  This is NOT the newly selected page when 
	// OnTabSelChange() is called.
	
  int sel_index = m_ctlTabControl.GetCurSel();
  if (sel_index == -1)
    return;


  CDialog * dlg = m_DlgArray[sel_index]->m_pDlg;

  if (dlg->UpdateData (TRUE))
    {
    dlg->ShowWindow(SW_HIDE);   // good update - hide window
    m_object->m_pTreeCtrl->SetItemText (m_object->m_hdlTreeItem, m_object->Summary ());
    }
  else
    *pResult = TRUE;	    // bad update - cancel pane change

}

void CObjectView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
  if (m_ctlTabControl.m_hWnd)
    {
	  m_ctlTabControl.MoveWindow(0, 0, cx, cy);

    int sel_index = m_ctlTabControl.GetCurSel();
    if (sel_index != -1)
      {

      // Get the rectangle size of the tab control so we know the position 
      // and size of the page that will be shown.
      RECT rc;
      m_ctlTabControl.GetItemRect (sel_index, &rc);

      m_DlgArray[sel_index]->m_pDlg->SetWindowPos (
	      NULL, 
	      5, rc.bottom + 5, 0, 0, 
	      SWP_NOSIZE | SWP_NOZORDER | SWP_SHOWWINDOW | SWP_NOACTIVATE);

      RECT rcclient;
      m_DlgArray[sel_index]->m_pDlg->GetClientRect (&rcclient);

      SetScrollSizes (MM_TEXT, 
                      CSize (rcclient.right, rcclient.bottom + rc.bottom + 5));

        }
    }
	
}


void CObjectView::ShowPages (CAreaEditorDoc * pDoc)
  {
  m_pDoc = pDoc;

  m_ctlTabControl.SetCurSel (m_pDoc->m_iCurrentObjectTab);

	OnSelchangeObjectTabs(NULL, NULL);
  }


// --------------------------------------------------------------------------
// CMobileView::HandleKeyDownMsg
//	
// This functin will handle the following keydown messages:
//
// CTRL+TAB			- used to activate the tab after the current selected tab
// SHIFT+CTRL+TAB	- used to activate the tab before the current selected tab
// ENTER			- OnOK() is called to dismiss the current selected tab 
// ESCAPE			- OnCancel() is called to dismiss the current selected tab
//
// Keystrokes messages are different from the mouse messages.  The former 
// will be sent to the window that has the input focus.  However, the 
// latter will be sent to the window in which the mouse is clicked on except in
// the case when SetCapture() is called.
//
// When those keys are pressed, the edit control inside the dialog box (or
// page) will have the input focus.  So, all keystrokes messages will be
// routed to the parent window i.e. the dialog box.  When dialog box receives
// the keystrokes messages, it will handle some of them (such as CTRL+TAB,
// TAB, arrow keys, etc.) and then forward unhandled ones to the edit control.
// Because of this, we need a way to trap those keystrokes messages before
// it gets routed to the dialog box.  The PreTranslateMessage() function
// in your CWinApp-derived class would be a good place for this.
//
// In the overriden CWinApp::PreTranslateMessage() function, all WM_KEYDOWN
// messages will be passed to the view window first.  So we have a chance 
// to handle the keystrokes messages that we are interested in.

// NOTE:  We can't intercept those keydown messages in PreTranslateMessage()
// of either CView or CMainFrame class because they are being handled by 
// the dialog box (or page) before they get routed to the view or frame 
// window.  Refer to the code in CWnd::WalkPreTranslateTree() in wincore.cpp
// file.  CWnd::WalkPreTranslateTree() is called in thrdcore.cpp file.
//
// This fucntion will return TRUE if those keystroke messages are processed; 
// FALSE otherwise.
// --------------------------------------------------------------------------
BOOL CObjectView::HandleKeyDownMsg(MSG* pMsg)
{
	// Was the CTRL key pressed?  If not, we don't handle this keydown 
	// message here.
	if (pMsg->wParam == VK_TAB && GetKeyState(VK_CONTROL) < 0)
		{
			// Was the SHIFT key pressed?  If it was pressed, then we need
			// to activate the tab before the current selected tab.
			// Otherwise, the tab after the current selected tab will be
			// activated.  
			BOOL	shift_down	= GetKeyState(VK_SHIFT) < 0;
			int		old_sel		= m_ctlTabControl.GetCurSel();
			int		num			= m_ctlTabControl.GetItemCount() ;
			int		new_sel		= 
				shift_down ? (old_sel + (num -1)) % num
						   : (old_sel + 1) % num;

			// Okay, here is the trick...  Simulate a mouse click message
			// to fool tab control that one of its tab is selected.
			RECT	r;
			m_ctlTabControl.GetItemRect(new_sel, &r);
			m_ctlTabControl.SendMessage(WM_LBUTTONDOWN, MK_LBUTTON, MAKELONG(r.left, r.top));
			return TRUE;
		}

    // if we are editing the description, don't throw away return and escape
    if (m_bEditingText)
      return FALSE;

    // a child edit control with the focus will be given the return key

		TCHAR szClass[10];
		CWnd* pWndFocus;
		if ((pMsg->wParam == VK_RETURN) &&
			((pWndFocus = GetFocus()) != NULL) &&
			IsChild(pWndFocus) &&
			(pWndFocus->GetStyle() & ES_WANTRETURN) &&
			GetClassName(pWndFocus->m_hWnd, szClass, 10) &&
			(_tcsicmp(szClass, _T("EDIT")) == 0))
      return FALSE;

	// Trapping the ENTER and ESCAPE keys here so the current active page won't be 
	// dismissed.  In MFC, ENTER and ESCAPE keys will be routed to CDialog::OnOK() and 
	// CDialog::OnCancel() functions that will destroy the current active dialog (or 
	// the page).
	if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		return TRUE;

	// Unhandled keydown messages.
	return FALSE;
}


// --------------------------------------------------------------------------
// CMobileView::OnTabSelChange
//	
// This function will show the newly selected page in the tab control.  The
// page will be sized to the display rectangle of the tab control.
// --------------------------------------------------------------------------

#include "ObjectSummaryPage.h"
#include "ObjectNamePage.h"
#include "ObjectStatsPage.h"
#include "FlagsListPage.h"
#include "ObjectResetsPage.h"

#define AddPageHelper(dlg, name, dlgclass, dlgIDC)  \
  page = new CTabPage;  \
  m_DlgArray.Add(page); \
  dlgclass * dlg;      \
  dlg = new dlgclass;  \
 	page->m_pDlg = dlg;  \
	ASSERT(page->m_pDlg);         \
 	page->m_name = name;  \
  page->m_DlgID = dlgIDC;

#define AddPage(dlg, name, dlgclass, dlgIDC)  \
  AddPageHelper (dlg, name, dlgclass, dlgIDC); \
  dlg->m_object = m_object; 

#define AddFlag(dlg, name, flag, flagarray)  \
  AddPageHelper (dlg, name, CFlagsListPage, IDD_SELECT_FROM_LIST); \
  dlg->m_pFlags = &m_object->flag;   \
  dlg->m_pFlagsArray = &flagarray;  \
  dlg->m_pDoc = pDoc;

void CObjectView::CreatePages()
{
CAreaEditorDoc* pDoc = (CAreaEditorDoc* ) GetDocument();
ASSERT_VALID(pDoc);

CTabPage * page;

// Add all pages to the dialog array.

// Warning - if you move the summary page, update SUMMARY_PAGE define

  AddPage (summarydlg,    "Summary", CObjectSummaryPage,       IDD_OBJECT_SUMMARY);
  AddPage (namedlg,       "Name",    CObjectNamePage,          IDD_OBJECT_NAME);
  AddPage (statsdlg,      "Stats",   CObjectStatsPage,         IDD_OBJECT_STATS);
  AddFlag (extraflagsdlg, "Object Flags", extra_flags, ObjectFlags);
  AddFlag (wearflagsdlg,  "Wear Flags",   wear_flags, WearFlags);
  AddPage (resetsdlg,     "References",  CObjectResetsPage,     IDD_OBJECT_RESETS);

  resetsdlg->m_pDoc = pDoc;

	// Add the tabs 

	TC_ITEM tci;
	tci.mask	= TCIF_TEXT;
	tci.iImage	= -1;
	for (int i = 0; i < m_DlgArray.GetSize (); i++)
	  {	
		tci.pszText	= (char *) (const char *) m_DlgArray[i]->m_name;
		m_ctlTabControl.InsertItem(i, &tci);
	  }
  
 }
