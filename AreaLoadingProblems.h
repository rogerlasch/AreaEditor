/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_AREALOADINGPROBLEMS_H__E4FA0811_F444_11D1_A20B_0000B4595568__INCLUDED_)
#define AFX_AREALOADINGPROBLEMS_H__E4FA0811_F444_11D1_A20B_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AreaLoadingProblems.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAreaLoadingProblems dialog

class CAreaLoadingProblems : public CDialog
{
// Construction
public:
	CAreaLoadingProblems(CWnd* pParent = NULL);   // standard constructor
  ~CAreaLoadingProblems ();   // destructor

// Dialog Data
	//{{AFX_DATA(CAreaLoadingProblems)
	enum { IDD = ID_PROBLEMS_LOADING_AREA };
	CEdit	m_ctlErrorList;
	CString	m_strErrors;
	//}}AFX_DATA

  CFont * m_font;

  bool m_first_time;

  CString m_strTitle;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAreaLoadingProblems)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

  virtual void OnOK (void);
  virtual void OnCancel (void);

	// Generated message map functions
	//{{AFX_MSG(CAreaLoadingProblems)
	afx_msg void OnSetfocusErrorList();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AREALOADINGPROBLEMS_H__E4FA0811_F444_11D1_A20B_0000B4595568__INCLUDED_)
