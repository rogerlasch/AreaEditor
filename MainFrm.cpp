/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/


// MainFrm.cpp : implementation of the CMainFrame class
//
#include <winuser.h>

#include "stdafx.h"
#include "AreaEditor.h"
#include "AreaEditorDoc.h"

#include "GeneratedNameDlg.h"
#include "MainFrm.h"
#include "ProgDlg.h"
#include "AreaTypeDlg.h"
#include "GotoVnumDlg.h"
#include "winplace.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static TCHAR BASED_CODE szCtrlBars[] = _T("CtrlBars");

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_UPDATE_COMMAND_UI(ID_STATUS_MODIFIED, OnUpdateStatusModified)
	ON_COMMAND(ID_EDIT_GENERATENAME, OnEditGeneratename)
	ON_COMMAND(ID_EDIT_RELOADNAMES, OnEditReloadnames)
	ON_COMMAND(ID_FILE_OPENAREALIST, OnFileOpenarealist)
	ON_COMMAND(ID_WINDOW_CLOSEALL, OnWindowCloseall)
	ON_COMMAND(ID_EDIT_GOTOVNUM, OnEditGotovnum)
	ON_COMMAND(ID_SOCIALS_EDIT, OnSocialsEdit)
	ON_UPDATE_COMMAND_UI(ID_SOCIALS_EDIT, OnUpdateSocialsEdit)
	ON_COMMAND(ID_COMMANDS_EDIT, OnCommandsEdit)
	ON_UPDATE_COMMAND_UI(ID_COMMANDS_EDIT, OnUpdateCommandsEdit)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, CMDIFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, CMDIFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CMDIFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CMDIFrameWnd::OnHelpFinder)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
  ID_STATUS_MODIFIED,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

  FixUpTitleBar ();

  CRect rect;

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{

  cs.style |= WS_MAXIMIZE;
	cs.style &= ~FWS_ADDTOTITLE;
		
	return CMDIFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

int CMainFrame::CreateProgressBar (const char * sMessage, const long maximum)
  {
RECT rc;

  if (maximum <= 0)
    return 1;

  m_wndStatusBar.GetItemRect (0, &rc);

  // find width of message we will be writing
  CDC * pDC = m_wndStatusBar.GetWindowDC ();
  CFont * pFont = m_wndStatusBar.GetFont ();
  pDC->SelectObject(pFont);
  CSize size = pDC->GetTextExtent (sMessage);
  ReleaseDC (pDC);

  rc.left += size.cx + 10;
  rc.right = ((rc.right - rc.left) / 4) + rc.left;

  m_wndProgress = new CProgressCtrl;
  if (!m_wndProgress)
    return 1;   // could not create, return error status

  if (!m_wndProgress->Create(WS_CHILD | WS_VISIBLE, rc,
                                            &m_wndStatusBar, 1))
    {
    delete m_wndProgress;
    m_wndProgress = NULL;
    return 1;   // could not create child window
    }

  m_wndProgress->SetRange(0, (short) maximum);
  m_wndProgress->SetStep(1);
 
  SetStatusMessage (sMessage);

  return 0;
  }

int CMainFrame::UpdateProgressBar (const long amount)
  {
  if (m_wndProgress)
    m_wndProgress->SetPos (amount);
  return 0;
  }

int CMainFrame::RemoveProgressBar (void)
  {
  delete m_wndProgress;
  m_wndProgress = NULL;

  SetStatusMessage (READY);

  return 0;

  }

void CMainFrame::SetStatusMessage(const CString& msg)
{
  if (App.m_pMainWnd)
    {
    m_wndStatusBar.SetWindowText(msg);
    m_wndStatusBar.UpdateWindow ();   // draw now
    }
  }


void CMainFrame::FixUpTitleBar (CAreaEditorDoc* pDoc)
  {

  if (AfxGetMainWnd () && AfxGetMainWnd ()->IsIconic ())
    return; 
  
  CString strTitle = "Area Editor - ";

  if (pDoc && pDoc->m_Area)
    {
    strTitle += pDoc->m_Area->strAreaName;
    }

  CString strOldTitle;

  GetWindowText (strOldTitle);

  // only change title if necessary, to avoid flicker
  if (strTitle != strOldTitle)
    SetWindowText (strTitle);

  } // end of FixUpTitleBar


void CMainFrame::OnUpdateStatusModified(CCmdUI* pCmdUI) 
{
  pCmdUI->SetText ("");
	  
  pCmdUI->Enable (true);
	
}


void CMainFrame::OnEditGeneratename() 
{
CString strName = GenerateName ();

  if (strName.IsEmpty ())
    return;   // no names.txt file?

CGeneratedNameDlg dlg;

  dlg.m_strName = strName;
  
  dlg.DoModal ();

}

void CMainFrame::OnEditReloadnames() 
{
  ReadNames ();	
}

void CMainFrame::OnFileOpenarealist() 
{

CProgressDlg * pProgressDlg = NULL;

t_areatype iAreaType = (t_areatype) App.GetProfileInt 
          (sProfilePreferences, sProfileDefaultAreaType, eSMAUG);

int iOldProblemsFlag = App.GetProfileInt (sProfilePreferences, sProfileShowWarnings, 1);

  // ask for area type once, not for each area file
  if (iAreaType == eAsk)
    {
    CAreaTypeDlg dlg;

    if (dlg.DoModal () != IDOK)
      return;   // cancelled so can't open document

    // add 1, as 0 is "ask", 1 = SMAUG (response zero) and so on
    iAreaType = (t_areatype) (dlg.m_iAreaType + 1);

    }

	try
	  {

    CString sBuf;
    BOOL bOK;
    int iTotal = 0,
        iCount = 0;


	  CFileDialog	dlg(TRUE,						// TRUE for FileOpen
					  "lst",						// default extension
					  "area.lst",						// initial file name
					  OFN_HIDEREADONLY|OFN_FILEMUSTEXIST,
					  "Area list files (*.lst)|*.lst|All files (*.*)|*.*||");
	  dlg.m_ofn.lpstrTitle = "Select area list file";
	  if (dlg.DoModal() != IDOK)
		  return;

    CStdioFile f (dlg.GetPathName(), CFile::modeRead|CFile::shareDenyNone|CFile::typeText);
  
    // count lines with area file names in them
    while (bOK = f.ReadString (sBuf))
      {
      sBuf.TrimRight ();
      sBuf.TrimLeft ();
      if (sBuf == "$")
        break;    // end of list 

      sBuf.MakeLower ();

      // ignore lines that don't refer to area files
      if (sBuf.Find (".are") == -1)
        continue;
      iTotal ++;

      }   // end of read loop

    if (iTotal == 0)
      {
      ::AfxMessageBox ("No lines with area file names (*.are) in them");
      return;
      } // end of no areas

    // don't show warnings for now, or the automated process will be a bit useless
    App.WriteProfileInt     (sProfilePreferences, sProfileShowWarnings, 0);

    pProgressDlg = new CProgressDlg;
    pProgressDlg->Create ();
    pProgressDlg->SetRange (0, iTotal);     
    pProgressDlg->SetWindowText ("Loading areas ...");                              
  	CWaitCursor wait;

    f.SeekToBegin ();  // rewind to start again

    while (bOK = f.ReadString (sBuf))
      {
      sBuf.TrimRight ();
      sBuf.TrimLeft ();
      if (sBuf == "$")
        break;    // end of list 

      sBuf.MakeLower ();

      // ignore lines that don't refer to area files
      if (sBuf.Find (".are") == -1)
        continue;
      iCount ++;

      // if they cancel, exit read loop
      if (pProgressDlg->CheckCancelButton())
        break;

      // don't open it twice
      bool bAlreadyOpen = false;

      for (POSITION docPos = App.m_pDocTemplate->GetFirstDocPosition();
          docPos != NULL; )
        {

        CAreaEditorDoc * pDoc = (CAreaEditorDoc *) App.m_pDocTemplate->GetNextDoc(docPos);

        if (pDoc->GetTitle ().CompareNoCase (sBuf) == 0)
          {
          bAlreadyOpen = true;    // same file name - don't open it twice
          break;
          }

        } // end of doing each document

      if (bAlreadyOpen)
        continue;

      pProgressDlg->SetStatus (CFormat ("Loading %s ...", (LPCTSTR) sBuf));    // area name
      pProgressDlg->SetPos (iCount);   // which one

    	App.Import (iAreaType, sBuf);

      }   // end of read loop


    }
	catch (CException* e)
	  {
		e->ReportError();
		e->Delete();
	  }

  delete pProgressDlg;

  // reset warnings flag
  App.WriteProfileInt     (sProfilePreferences, sProfileShowWarnings, iOldProblemsFlag);
  
}


void CMainFrame::OnWindowCloseall() 
{

  for (POSITION docPos = App.m_pDocTemplate->GetFirstDocPosition();
      docPos != NULL; )
    {

    CAreaEditorDoc * pDoc =  (CAreaEditorDoc *) App.m_pDocTemplate->GetNextDoc(docPos);

    // see if they want to save it
	  if (!pDoc->MySaveModified())
		  return;

    // saved OK, let's close it
    pDoc->OnCloseDocument ();
 
    } // end of doing each document

	
}

void CMainFrame::OnEditGotovnum() 
{
CGotoVnumDlg dlg;

  dlg.m_iVnumType = 0;
  
  if (dlg.DoModal () != IDOK)
    return;

  CMobile * mob;
  CMUDObject * object;
  CRoom * room;

  switch (dlg.m_iVnumType)
    {

    case 0: // mob
            mob = FindMob (dlg.m_iVnum);
            if (mob)
              mob->GoTo ();
            else
              ::AfxMessageBox (CFormat ("Mobile %i not in any open area", dlg.m_iVnum));
            break;

    case 1: // object
            object = FindObj (dlg.m_iVnum);
            if (object)
              object->GoTo ();
            else
              ::AfxMessageBox (CFormat ("Object %i not in any open area", dlg.m_iVnum));
            break;

    case 2: // room
            room = FindRoom (dlg.m_iVnum);
            if (room)
              room->GoTo ();
            else
              ::AfxMessageBox (CFormat ("Room %i not in any open area", dlg.m_iVnum));
            break;

    default: ::AfxMessageBox ("Unknown type of vnum");
             break;
    } // end of switch
}


void CMainFrame::OnClose() 
{
  SaveBarState(szCtrlBars);

  // remember the current window position

  CWindowPlacement wp;
  wp.Save ("Main window", this);
	
	CMDIFrameWnd::OnClose();
}
