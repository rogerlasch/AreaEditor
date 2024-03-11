/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_MUDPROGRAMVIEW_H__EBE07974_EF74_11D1_A20A_0000B4595568__INCLUDED_)
#define AFX_MUDPROGRAMVIEW_H__EBE07974_EF74_11D1_A20A_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MUDProgramView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMUDProgramView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CMUDProgramView : public CFormView
{
protected:
	CMUDProgramView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMUDProgramView)

// Form Data
public:
	//{{AFX_DATA(CMUDProgramView)
	enum { IDD = IDD_MUD_PROGRAM };
	CComboBox	m_ctlProgramType;
	CEdit	m_ctlcomlist;
	CString	m_comlist;
	CString	m_arglist;
	//}}AFX_DATA

// Attributes
public:

  CMUDprogram * m_program;
  CFont * m_font;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMUDProgramView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMUDProgramView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CMUDProgramView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEditProgram();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MUDPROGRAMVIEW_H__EBE07974_EF74_11D1_A20A_0000B4595568__INCLUDED_)
