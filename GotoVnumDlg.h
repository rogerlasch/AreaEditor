/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_GOTOVNUMDLG_H__7BD1AC47_23A8_11D4_BB0D_0080AD7972EF__INCLUDED_)
#define AFX_GOTOVNUMDLG_H__7BD1AC47_23A8_11D4_BB0D_0080AD7972EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GotoVnumDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGotoVnumDlg dialog

class CGotoVnumDlg : public CDialog
{
// Construction
public:
	CGotoVnumDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGotoVnumDlg)
	enum { IDD = IDD_GOTO_VNUM };
	int		m_iVnum;
	int		m_iVnumType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGotoVnumDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGotoVnumDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GOTOVNUMDLG_H__7BD1AC47_23A8_11D4_BB0D_0080AD7972EF__INCLUDED_)
