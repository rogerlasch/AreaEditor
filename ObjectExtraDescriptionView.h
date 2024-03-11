/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_OBJECTEXTRADESCRIPTIONVIEW_H__EBE07977_EF74_11D1_A20A_0000B4595568__INCLUDED_)
#define AFX_OBJECTEXTRADESCRIPTIONVIEW_H__EBE07977_EF74_11D1_A20A_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ObjectExtraDescriptionView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CObjectExtraDescriptionView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CObjectExtraDescriptionView : public CFormView
{
protected:
	CObjectExtraDescriptionView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CObjectExtraDescriptionView)

// Form Data
public:
	//{{AFX_DATA(CObjectExtraDescriptionView)
	enum { IDD = IDD_OBJECT_EXTRA_DESCRIPTION };
	CEdit	m_ctlDescription;
	CString	m_keyword;
	CString	m_description;
	//}}AFX_DATA

// Attributes
public:

  CExtraDescription * m_extradescription;
  CFont * m_font;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CObjectExtraDescriptionView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CObjectExtraDescriptionView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CObjectExtraDescriptionView)
	afx_msg void OnEditDescription();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OBJECTEXTRADESCRIPTIONVIEW_H__EBE07977_EF74_11D1_A20A_0000B4595568__INCLUDED_)
