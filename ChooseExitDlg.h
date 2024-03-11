/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_CHOOSEEXITDLG_H__0C836F95_FFEE_11D1_A20B_0000B4595568__INCLUDED_)
#define AFX_CHOOSEEXITDLG_H__0C836F95_FFEE_11D1_A20B_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ChooseExitDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChooseExitDlg dialog

class CChooseExitDlg : public CDialog
{
// Construction
public:
	CChooseExitDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChooseExitDlg)
	enum { IDD = IDD_CHOOSE_EXIT };
	CButton	m_ctlOK;
	CButton	m_ctlFindNext;
	CListBox	m_ctlExitList;
	//}}AFX_DATA

  CExitList * m_ExitList;

  int m_iSelectedExit;

  CAreaEditorDoc * m_pDoc;

  CString m_strFindString;
  int m_nFoundItem;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChooseExitDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChooseExitDlg)
	afx_msg void OnDblclkExitList();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnFind();
	afx_msg void OnFindNext();
	afx_msg void OnSelchangeExitList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHOOSEEXITDLG_H__0C836F95_FFEE_11D1_A20B_0000B4595568__INCLUDED_)
