/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_AUTHORNAMEVIEW_H__7DCA3917_EAB6_11D1_A20A_0000B4595568__INCLUDED_)
#define AFX_AUTHORNAMEVIEW_H__7DCA3917_EAB6_11D1_A20A_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AuthorNameView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAuthorNameView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CAuthorNameView : public CFormView
{
protected:
	CAuthorNameView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CAuthorNameView)

// Form Data
public:
	//{{AFX_DATA(CAuthorNameView)
	enum { IDD = IDD_AUTHOR_NAME };
	CString	m_strAuthorName;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAuthorNameView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CAuthorNameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CAuthorNameView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTHORNAMEVIEW_H__7DCA3917_EAB6_11D1_A20A_0000B4595568__INCLUDED_)
