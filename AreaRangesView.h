/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_AREARANGESVIEW_H__670FCF55_4EA7_11D2_AFA0_00A0247B3BFD__INCLUDED_)
#define AFX_AREARANGESVIEW_H__670FCF55_4EA7_11D2_AFA0_00A0247B3BFD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AreaRangesView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAreaRangesView dialog

class CAreaRangesView : public CDialog
{
// Construction
public:
	CAreaRangesView(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAreaRangesView)
	enum { IDD = IDD_AREA_RANGES };
	CEdit	m_ctlTotalEconomy;
	CEdit	m_ctlHighEconomy;
	CEdit	m_ctlLowEconomy;
	int		m_high_economy;
	int		m_low_economy;
	int		m_high_hard_range;
	int		m_high_soft_range;
	int		m_low_hard_range;
	int		m_low_soft_range;
	//}}AFX_DATA

  CArea * m_area;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAreaRangesView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAreaRangesView)
	afx_msg void OnChangeEconomy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AREARANGESVIEW_H__670FCF55_4EA7_11D2_AFA0_00A0247B3BFD__INCLUDED_)
