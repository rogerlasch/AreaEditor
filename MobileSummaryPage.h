/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_MOBILESUMMARYPAGE_H__ACFBE915_EB82_11D1_A20A_0000B4595568__INCLUDED_)
#define AFX_MOBILESUMMARYPAGE_H__ACFBE915_EB82_11D1_A20A_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MobileSummaryPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMobileSummaryPage dialog

class CMobileSummaryPage : public CDialog
{

// Construction
public:
	CMobileSummaryPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMobileSummaryPage)
	enum { IDD = IDD_MOBILE_SUMMARY };
	CStatic	m_ctlSpeakingLabel;
	CEdit	m_ctlSpeaking;
	CEdit	m_ctlSpeaks;
	CStatic	m_ctlSpeaksLabel;
	CString	m_player_name;
	CString	m_short_descr;
	CString	m_long_descr;
	CString	m_strActions;
	int		m_vnum;
	CString	m_strAffectedBy;
	int		m_level;
	CString	m_strStats;
	CString	m_strBodyParts;
	CString	m_strAttacks;
	CString	m_strDefenses;
	CString	m_strResistant;
	CString	m_strImmune;
	CString	m_strSusceptible;
	CString	m_strSpeaks;
	CString	m_strSpeaking;
	CString	m_strDefensesLabel;
	CString	m_strSex;
	CString	m_strAverage;
	//}}AFX_DATA

  CMobile * m_mob;    // which mobile we are displaying

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMobileSummaryPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMobileSummaryPage)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOBILESUMMARYPAGE_H__ACFBE915_EB82_11D1_A20A_0000B4595568__INCLUDED_)
