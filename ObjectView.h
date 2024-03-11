/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_OBJECTVIEW_H__EBE07978_EF74_11D1_A20A_0000B4595568__INCLUDED_)
#define AFX_OBJECTVIEW_H__EBE07978_EF74_11D1_A20A_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ObjectView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CObjectView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CObjectView : public CFormView
{
protected:
	CObjectView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CObjectView)

// Form Data
public:
	//{{AFX_DATA(CObjectView)
	enum { IDD = IDD_OBJECT };
	CTabCtrl	m_ctlTabControl;
	//}}AFX_DATA

// Attributes
public:

  CMUDObject * m_object;

  CAreaEditorDoc * m_pDoc;

  bool m_bEditingText;

	// Array of all the property-page dialogs
  CTabPageArray m_DlgArray;

// Operations
public:


	// Call this function to create all pages for the tab view window.
	void CreatePages ();
  void ShowPages (CAreaEditorDoc * pDoc);
  BOOL HandleKeyDownMsg(MSG* pMsg);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CObjectView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CObjectView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CObjectView)
	afx_msg void OnSelchangeObjectTabs(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangingObjectTabs(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OBJECTVIEW_H__EBE07978_EF74_11D1_A20A_0000B4595568__INCLUDED_)
