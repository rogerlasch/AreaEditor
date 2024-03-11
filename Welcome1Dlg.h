/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_WELCOME1DLG_H__5E528964_FC08_11D1_A20B_0000B4595568__INCLUDED_)
#define AFX_WELCOME1DLG_H__5E528964_FC08_11D1_A20B_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Welcome1Dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWelcome1Dlg dialog

class CWelcome1Dlg : public CDialog
{
// Construction
public:
	CWelcome1Dlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWelcome1Dlg)
	enum { IDD = IDD_WELCOME1 };
	CString	m_strChangeHistoryAddress;
	CString	m_strMessage1;
	CString	m_strMessage2;
	//}}AFX_DATA

 	// static controls with hyperlinks
	CStaticLink	m_ChangesLink;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWelcome1Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWelcome1Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnLicense();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WELCOME1DLG_H__5E528964_FC08_11D1_A20B_0000B4595568__INCLUDED_)
