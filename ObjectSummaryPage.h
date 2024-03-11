/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_OBJECTSUMMARYPAGE_H__FF49303A_F036_11D1_A20A_0000B4595568__INCLUDED_)
#define AFX_OBJECTSUMMARYPAGE_H__FF49303A_F036_11D1_A20A_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ObjectSummaryPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CObjectSummaryPage dialog

class CObjectSummaryPage : public CDialog
{
// Construction
public:
	CObjectSummaryPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CObjectSummaryPage)
	enum { IDD = IDD_OBJECT_SUMMARY };
	CEdit	m_ctlCondition;
	CEdit	m_ctlLevel;
	CStatic	m_ctlConditionLabel;
	CStatic	m_ctlLevelLabel;
	int		m_vnum;
	CString	m_type;
	CString	m_name;
	CString	m_short_descr;
	CString	m_description;
	CString	m_strExtraFlags;
	CString	m_strWearFlags;
	int		m_cost;
	int		m_layers;
	int		m_rent;
	int		m_value1;
	int		m_value2;
	int		m_value3;
	int		m_value4;
	int		m_value5;
	int		m_value6;
	int		m_weight;
	CString	m_strAffects;
	CString	m_strValueMeanings;
	int		m_iLevel;
	int		m_iCondition;
	//}}AFX_DATA

  CMUDObject * m_object;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CObjectSummaryPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CObjectSummaryPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OBJECTSUMMARYPAGE_H__FF49303A_F036_11D1_A20A_0000B4595568__INCLUDED_)
