/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_REPAIRVIEW_H__5E528977_FC08_11D1_A20B_0000B4595568__INCLUDED_)
#define AFX_REPAIRVIEW_H__5E528977_FC08_11D1_A20B_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RepairView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRepairView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CRepairView : public CFormView
{
protected:
	CRepairView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CRepairView)

// Form Data
public:
	//{{AFX_DATA(CRepairView)
	enum { IDD = IDD_REPAIR };
	CComboBox	m_ctlRepairType;
	CComboBox	m_ctlFixType1;
	CComboBox	m_ctlFixType3;
	CComboBox	m_ctlFixType2;
	CButton	m_ctlGoTo;
	CEdit	m_ctlKeeperDescription;
	CEdit	m_ctlKeeper;
	int		m_close_hour;
	int		m_keeper;
	int		m_open_hour;
	int		m_profit_fix;
	//}}AFX_DATA

// Attributes
public:

  CRepair * m_repair;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRepairView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CRepairView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CRepairView)
	afx_msg void OnChangeKeeper();
	afx_msg void OnChoose();
	afx_msg void OnGoto();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPAIRVIEW_H__5E528977_FC08_11D1_A20B_0000B4595568__INCLUDED_)
