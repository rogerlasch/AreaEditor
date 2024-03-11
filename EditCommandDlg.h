/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_EDITCOMMANDDLG_H__60223704_0AF0_11D2_A20B_0000B4595568__INCLUDED_)
#define AFX_EDITCOMMANDDLG_H__60223704_0AF0_11D2_A20B_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// EditCommandDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditCommandDlg dialog

class CEditCommandDlg : public CDialog
{
// Construction
public:
	CEditCommandDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEditCommandDlg)
	enum { IDD = IDD_EDIT_COMMAND };
	CComboBox	m_ctlFunction;
	int		m_level;
	int		m_log;
	CString	m_name;
	int		m_position;
	CString	m_do_fun;
	BOOL	m_possessed;
	BOOL	m_polymorphed;
	BOOL	m_watch;
	//}}AFX_DATA

  bool m_bAdd;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditCommandDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEditCommandDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITCOMMANDDLG_H__60223704_0AF0_11D2_A20B_0000B4595568__INCLUDED_)
