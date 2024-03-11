/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_AREALOADPROBLEMSDLG_H__79013073_F425_11D1_A20B_0000B4595568__INCLUDED_)
#define AFX_AREALOADPROBLEMSDLG_H__79013073_F425_11D1_A20B_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AreaLoadProblemsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAreaLoadProblemsDlg dialog

class CAreaLoadProblemsDlg : public CDialog
{
// Construction
public:
	CAreaLoadProblemsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAreaLoadProblemsDlg)
	enum { IDD = IDD_PROBLEMS_LOADING_AREA };
	CEdit	m_ctlErrorList;
	CString	m_strErrorList;
	//}}AFX_DATA


    CFont * m_font;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAreaLoadProblemsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAreaLoadProblemsDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AREALOADPROBLEMSDLG_H__79013073_F425_11D1_A20B_0000B4595568__INCLUDED_)
