/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_PREFSP1_H__FA20E754_4BA7_11D2_AFA0_00A0247B3BFD__INCLUDED_)
#define AFX_PREFSP1_H__FA20E754_4BA7_11D2_AFA0_00A0247B3BFD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PrefsP1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPrefsP1 dialog

class CPrefsP1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CPrefsP1)

// Construction
public:
	CPrefsP1();
	~CPrefsP1();

// Dialog Data
	//{{AFX_DATA(CPrefsP1)
	enum { IDD = IDD_PREFSP1 };
	CButton	m_ctlBrowseConfig;
	CEdit	m_ctlSocialsFile;
	CEdit	m_ctlSkillsFile;
	CEdit	m_ctlConfigFile;
	CEdit	m_ctlCommandsFile;
	CString	m_strCommandsFile;
	CString	m_strConfigFile;
	CString	m_strSkillsFile;
	CString	m_strSocialsFile;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPrefsP1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPrefsP1)
	afx_msg void OnBrowseCommands();
	afx_msg void OnBrowseSkills();
	afx_msg void OnBrowseSocials();
	afx_msg void OnBrowseConfig();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PREFSP1_H__FA20E754_4BA7_11D2_AFA0_00A0247B3BFD__INCLUDED_)
