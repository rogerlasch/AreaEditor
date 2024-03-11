/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_HELPVIEW_H__FA114F03_FF3B_11D1_A20B_0000B4595568__INCLUDED_)
#define AFX_HELPVIEW_H__FA114F03_FF3B_11D1_A20B_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// HelpView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHelpView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CHelpView : public CFormView
{
protected:
	CHelpView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CHelpView)

// Form Data
public:
	//{{AFX_DATA(CHelpView)
	enum { IDD = IDD_HELP };
	CEdit	m_ctlHelp;
	int		m_level;
	CString	m_text;
	CString	m_keyword;
	//}}AFX_DATA

// Attributes
public:

  CHelp * m_help;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHelpView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CHelpView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CHelpView)
	afx_msg void OnEditHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HELPVIEW_H__FA114F03_FF3B_11D1_A20B_0000B4595568__INCLUDED_)
