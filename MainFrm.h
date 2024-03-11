/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__30BE035B_E9F1_11D1_A20A_0000B4595568__INCLUDED_)
#define AFX_MAINFRM_H__30BE035B_E9F1_11D1_A20A_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CAreaEditorDoc;

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:

  int CreateProgressBar (const char * sMessage, const long maximum);
  int UpdateProgressBar (const long amount);
  int RemoveProgressBar (void);
  void SetStatusMessage(const CString& msg);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
  CProgressCtrl * m_wndProgress;

public:

  void FixUpTitleBar (CAreaEditorDoc* pDoc = NULL);

// Generated message map functions
protected:
	afx_msg void OnInitMenu(CMenu* pMenu);
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnUpdateStatusModified(CCmdUI* pCmdUI);
	afx_msg void OnEditGeneratename();
	afx_msg void OnEditReloadnames();
	afx_msg void OnFileOpenarealist();
	afx_msg void OnWindowCloseall();
	afx_msg void OnEditGotovnum();
	afx_msg void OnSocialsEdit();
	afx_msg void OnUpdateSocialsEdit(CCmdUI* pCmdUI);
	afx_msg void OnCommandsEdit();
	afx_msg void OnUpdateCommandsEdit(CCmdUI* pCmdUI);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__30BE035B_E9F1_11D1_A20A_0000B4595568__INCLUDED_)
