/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_AREAVIEW_H__670FCF53_4EA7_11D2_AFA0_00A0247B3BFD__INCLUDED_)
#define AFX_AREAVIEW_H__670FCF53_4EA7_11D2_AFA0_00A0247B3BFD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AreaView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAreaView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CAreaView : public CFormView
{
protected:
	CAreaView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CAreaView)

// Form Data
public:
	//{{AFX_DATA(CAreaView)
	enum { IDD = IDD_AREA };
	CTabCtrl	m_ctlTabControl;
	//}}AFX_DATA

// Attributes
public:

  CArea * m_area;

  CAreaEditorDoc * m_pDoc;
  CAreaEditorView * m_pLHview;

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
	//{{AFX_VIRTUAL(CAreaView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CAreaView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CAreaView)
	afx_msg void OnSelchangeAreaTabs(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangingAreaTabs(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AREAVIEW_H__670FCF53_4EA7_11D2_AFA0_00A0247B3BFD__INCLUDED_)
