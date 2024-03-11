/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_MOBILEVIEW_H__7DCA3919_EAB6_11D1_A20A_0000B4595568__INCLUDED_)
#define AFX_MOBILEVIEW_H__7DCA3919_EAB6_11D1_A20A_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MobileView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMobileView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CMobileView : public CFormView
{
protected:
	CMobileView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMobileView)

// Form Data
public:
	//{{AFX_DATA(CMobileView)
	enum { IDD = IDD_MOBILE };
	CTabCtrl	m_ctlTabControl;
	//}}AFX_DATA

// Attributes
public:

  CMobile * m_mob;    // which mobile we are displaying

	// Array of all the property-page dialogs
  CTabPageArray m_DlgArray;

  CAreaEditorDoc * m_pDoc;

  bool m_bEditingText;

// Operations
public:

	// Call this function to create all pages for the tab view window.
	void CreatePages ();
  void ShowPages (CAreaEditorDoc * pDoc);
  BOOL HandleKeyDownMsg(MSG* pMsg);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMobileView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMobileView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CMobileView)
	afx_msg void OnSelchangeMobileTabs(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangingMobileTabs(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOBILEVIEW_H__7DCA3919_EAB6_11D1_A20A_0000B4595568__INCLUDED_)
