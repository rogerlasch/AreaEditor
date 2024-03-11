/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_RESETVIEW_H__0E63EEF5_F38B_11D1_A20B_0000B4595568__INCLUDED_)
#define AFX_RESETVIEW_H__0E63EEF5_F38B_11D1_A20B_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ResetView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CResetView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CResetView : public CFormView
{
protected:
	CResetView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CResetView)

// Form Data
public:
	//{{AFX_DATA(CResetView)
	enum { IDD = IDD_RESETS };
	CStatic	m_ctlLabelArg4;
	CEdit	m_ctlDescArg4;
	CEdit	m_ctlArg4;
	CStatic	m_ctlWearLocationLabel;
	CComboBox	m_ctlWearLocation;
	CButton	m_ctlCommand;
	CEdit	m_ctlExtra;
	CEdit	m_ctlArg3;
	CEdit	m_ctlArg2;
	CEdit	m_ctlArg1;
	CStatic	m_ctlLabelExtra;
	CStatic	m_ctlLabelArg3;
	CStatic	m_ctlLabelArg2;
	CStatic	m_ctlLabelArg1;
	CEdit	m_ctlDescExtra;
	CEdit	m_ctlDescArg3;
	CEdit	m_ctlDescArg2;
	CEdit	m_ctlDescArg1;
	int		m_arg1;
	int		m_arg2;
	int		m_arg3;
	int		m_extra;
	int		m_command;
	int		m_arg4;
	//}}AFX_DATA

// Attributes
public:

  CReset * m_reset;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResetView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CResetView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CResetView)
	afx_msg void OnUpdateArg1();
	afx_msg void OnUpdateArg2();
	afx_msg void OnUpdateArg3();
	afx_msg void OnUpdateExtra();
	afx_msg void OnCommand();
	afx_msg void OnArg1Choose();
	afx_msg void OnArg1Goto();
	afx_msg void OnArg2Choose();
	afx_msg void OnArg2Goto();
	afx_msg void OnArg3Choose();
	afx_msg void OnArg3Goto();
	afx_msg void OnSelchangeWearLocation();
	afx_msg void OnUpdateArg4();
	//}}AFX_MSG
  afx_msg LRESULT OnKickIdle(WPARAM, LPARAM);
  afx_msg void OnUpdateGotoArg1(CCmdUI* pCmdUI);
  afx_msg void OnUpdateGotoArg2(CCmdUI* pCmdUI);
  afx_msg void OnUpdateGotoArg3(CCmdUI* pCmdUI);
  afx_msg void OnUpdateChooseArg1(CCmdUI* pCmdUI);
  afx_msg void OnUpdateChooseArg2(CCmdUI* pCmdUI);
  afx_msg void OnUpdateChooseArg3(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESETVIEW_H__0E63EEF5_F38B_11D1_A20B_0000B4595568__INCLUDED_)
