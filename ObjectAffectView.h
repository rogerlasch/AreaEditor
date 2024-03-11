/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_OBJECTAFFECTVIEW_H__EBE07976_EF74_11D1_A20A_0000B4595568__INCLUDED_)
#define AFX_OBJECTAFFECTVIEW_H__EBE07976_EF74_11D1_A20A_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ObjectAffectView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CObjectAffectView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CObjectAffectView : public CFormView
{
protected:
	CObjectAffectView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CObjectAffectView)

// Form Data
public:
	//{{AFX_DATA(CObjectAffectView)
	enum { IDD = IDD_OBJECT_AFFECT };
	CStatic	m_ctlWhatLabel;
	CStatic	m_ctlWhereLabel;
	CComboBox	m_ctlAffectWhere;
	CComboBox	m_ctlLocation;
	int		m_modifier;
	//}}AFX_DATA

// Attributes
public:

  CAffect * m_affect;
  tFlags * m_pFlagsArray;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CObjectAffectView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CObjectAffectView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CObjectAffectView)
	afx_msg void OnSelchangeAffectType();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OBJECTAFFECTVIEW_H__EBE07976_EF74_11D1_A20A_0000B4595568__INCLUDED_)
