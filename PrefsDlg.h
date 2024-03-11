/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_PREFSDLG_H__73CBE363_0BDB_11D2_A20B_0000B4595568__INCLUDED_)
#define AFX_PREFSDLG_H__73CBE363_0BDB_11D2_A20B_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PrefsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPrefsDlg dialog

class CPrefsDlg : public CDialog
{
// Construction
public:
	CPrefsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPrefsDlg)
	enum { IDD = IDD_PREFERENCES };
	CEdit	m_ctlConfigFile;
	CEdit	m_ctlSocialsFile;
	CEdit	m_ctlSkillsFile;
	CEdit	m_ctlCommandsFile;
	CString	m_strCommandsFile;
	CString	m_strSkillsFile;
	CString	m_strSocialsFile;
	BOOL	m_bWarnVnumsOutOfRange;
	BOOL	m_bShowWarnings;
	CString	m_strConfigFile;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrefsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPrefsDlg)
	afx_msg void OnBrowseCommands();
	afx_msg void OnBrowseSkills();
	afx_msg void OnBrowseSocials();
	afx_msg void OnBrowseConfig();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PREFSDLG_H__73CBE363_0BDB_11D2_A20B_0000B4595568__INCLUDED_)
