/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_FINDINDIALOGDLG_H__80E945D3_664D_11D2_AFA8_00A0247B3BFD__INCLUDED_)
#define AFX_FINDINDIALOGDLG_H__80E945D3_664D_11D2_AFA8_00A0247B3BFD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// FindInDialogDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFindInDialogDlg dialog

class CFindInDialogDlg : public CDialog
{
// Construction
public:
	CFindInDialogDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFindInDialogDlg)
	enum { IDD = IDD_FIND_IN_DIALOG };
	CString	m_strFindWhat;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFindInDialogDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFindInDialogDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FINDINDIALOGDLG_H__80E945D3_664D_11D2_AFA8_00A0247B3BFD__INCLUDED_)
