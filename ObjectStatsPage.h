/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_OBJECTSTATSPAGE_H__42F26DF3_F10D_11D1_A20A_0000B4595568__INCLUDED_)
#define AFX_OBJECTSTATSPAGE_H__42F26DF3_F10D_11D1_A20A_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ObjectStatsPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CObjectStatsPage dialog

class CObjectStatsPage : public CDialog
{
// Construction
public:
	CObjectStatsPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CObjectStatsPage)
	enum { IDD = IDD_OBJECT_STATS };
	CStatic	m_ctlMaterialLabel;
	CEdit	m_ctlMaterial;
	CStatic	m_ctlLevelLabel;
	CEdit	m_ctlLevel;
	CStatic	m_ctlConditionLabel;
	CEdit	m_ctlCondition;
	CButton	m_ctlChoose6;
	CButton	m_ctlChoose5;
	CButton	m_ctlChoose4;
	CButton	m_ctlChoose3;
	CButton	m_ctlChoose2;
	CButton	m_ctlChoose1;
	CEdit	m_ctlValue6;
	CEdit	m_ctlValue5;
	CEdit	m_ctlValue4;
	CEdit	m_ctlValue3;
	CEdit	m_ctlValue2;
	CEdit	m_ctlValue1;
	CStatic	m_ctlLabelValue6;
	CStatic	m_ctlLabelValue5;
	CStatic	m_ctlLabelValue4;
	CStatic	m_ctlLabelValue3;
	CStatic	m_ctlLabelValue2;
	CEdit	m_ctlDescValue6;
	CEdit	m_ctlDescValue5;
	CEdit	m_ctlDescValue3;
	CEdit	m_ctlDescValue4;
	CEdit	m_ctlDescValue2;
	CEdit	m_ctlDescValue1;
	CStatic	m_ctlLabelValue1;
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
	CString	m_type;
	int		m_iCondition;
	int		m_iLevel;
	CString	m_strMaterial;
	CString	m_strUnits;
	//}}AFX_DATA

  CMUDObject * m_object;

  void UpdateLabels (void);  
  void UpdateDescriptions (void);

  void ChooseItem (const int iItem);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CObjectStatsPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CObjectStatsPage)
	afx_msg void OnChangeValue();
	afx_msg void OnChoose1();
	afx_msg void OnChoose2();
	afx_msg void OnChoose3();
	afx_msg void OnChoose4();
	afx_msg void OnChoose5();
	afx_msg void OnChoose6();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OBJECTSTATSPAGE_H__42F26DF3_F10D_11D1_A20A_0000B4595568__INCLUDED_)
