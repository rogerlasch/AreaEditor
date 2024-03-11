/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// RoomExitView.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "AreaEditorDoc.h"

#include "RoomExitView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define SUMMARY_PAGE 0

/////////////////////////////////////////////////////////////////////////////
// CRoomExitView

IMPLEMENT_DYNCREATE(CRoomExitView, CFormView)

CRoomExitView::CRoomExitView()
	: CFormView(CRoomExitView::IDD)
{
	//{{AFX_DATA_INIT(CRoomExitView)
	//}}AFX_DATA_INIT

  m_exit = NULL;
  m_bEditingText = false;
  m_pLHview = NULL;

}

CRoomExitView::~CRoomExitView()
{

	// Delete the memory space for the C++ dialog object.  The actual dialog
	// (or page) will be destroyed when tab control is destroyed because it
	// is the child window of the tab control (see code in CreatePages()).

	for (int i = 0; i < m_DlgArray.GetSize(); i++)
		delete m_DlgArray[i];

}

void CRoomExitView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRoomExitView)
	DDX_Control(pDX, IDC_EXIT_TABS, m_ctlTabControl);
	//}}AFX_DATA_MAP

  // send update to child pane

  if (pDX->m_bSaveAndValidate)
    {
    int sel_index = m_ctlTabControl.GetCurSel();
    if (sel_index != -1)
      {
      CDialog * dlg = m_DlgArray[sel_index]->m_pDlg;

      if (dlg->UpdateData (TRUE))
        m_exit->m_pTreeCtrl->SetItemText (m_exit->m_hdlTreeItem, m_exit->Summary ());
      else
        {
        // *post* a message putting the focus back on the naughty control
        PostMessage (WM_SETFOCUS, 0, 0);   
        pDX->Fail();   // bad update - fail this one
        }
      }
    }   // end of saving and validating


}


BEGIN_MESSAGE_MAP(CRoomExitView, CFormView)
	//{{AFX_MSG_MAP(CRoomExitView)
	ON_NOTIFY(TCN_SELCHANGE, IDC_EXIT_TABS, OnSelchangeExitTabs)
	ON_NOTIFY(TCN_SELCHANGING, IDC_EXIT_TABS, OnSelchangingExitTabs)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRoomExitView diagnostics

#ifdef _DEBUG
void CRoomExitView::AssertValid() const
{
	CFormView::AssertValid();
}

void CRoomExitView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRoomExitView message handlers

void CRoomExitView::OnSelchangeExitTabs(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// Call GetCurSel() will return the index of the page that is newly
	// selected.  This page will be visible soon.
	int sel_index = m_ctlTabControl.GetCurSel();

  if (sel_index == -1)
    return;

  m_pDoc->m_iCurrentExitTab = sel_index;

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
// CRoomExitView::OnTabSelChanging
//	
// This function will hide the currently visible page in the tab control
// (CTabCtrl) so the newly selected page can be shown in OnTabSelChange().
// --------------------------------------------------------------------------


void CRoomExitView::OnSelchangingExitTabs(NMHDR* pNMHDR, LRESULT* pResult) 
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
    m_exit->m_pTreeCtrl->SetItemText (m_exit->m_hdlTreeItem, m_exit->Summary ());
    }
  else
    *pResult = TRUE;	    // bad update - cancel pane change
}

void CRoomExitView::OnSize(UINT nType, int cx, int cy) 
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


void CRoomExitView::ShowPages (CAreaEditorDoc * pDoc)
  {
  m_pDoc = pDoc;

  m_ctlTabControl.SetCurSel (m_pDoc->m_iCurrentExitTab);

	OnSelchangeExitTabs(NULL, NULL);
  }



#include "FlagsListPage.h"
#include "RoomExitDetails.h"

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
  dlg->m_exit = m_exit; 

#define AddFlag(dlg, name, flag, flagarray)  \
  AddPageHelper (dlg, name, CFlagsListPage, IDD_SELECT_FROM_LIST); \
  dlg->m_pFlags = &m_exit->flag;   \
  dlg->m_pFlagsArray = &flagarray;  \
  dlg->m_pDoc = pDoc;


void CRoomExitView::CreatePages()
{
CAreaEditorDoc* pDoc = (CAreaEditorDoc* ) GetDocument();
ASSERT_VALID(pDoc);


CTabPage * page;

// Add all pages to the dialog array.

// Warning - if you move the summary page, update SUMMARY_PAGE define

  AddPage (summarydlg,    "Details", CRoomExitDetails,       IDD_ROOM_EXIT_DETAILS);
  AddFlag (flagsdlg,      "Flags",  exit_info, ExitFlags);

// summarydlg->m_pDoc = pDoc;
// summarydlg->m_pLHview = m_pLHview;

  
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
