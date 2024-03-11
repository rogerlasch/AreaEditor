/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_PREFSP2_H__FA20E755_4BA7_11D2_AFA0_00A0247B3BFD__INCLUDED_)
#define AFX_PREFSP2_H__FA20E755_4BA7_11D2_AFA0_00A0247B3BFD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PrefsP2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPrefsP2 dialog

class CPrefsP2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CPrefsP2)

// Construction
public:
	CPrefsP2();
	~CPrefsP2();

// Dialog Data
	//{{AFX_DATA(CPrefsP2)
	enum { IDD = IDD_PREFSP2 };
	CStatic	m_ctlFontName;
	BOOL	m_bShowWarnings;
	BOOL	m_bWarnVnumsOutOfRange;
	BOOL	m_bShowFlagNumbers;
	CString	m_strFontName;
	BOOL	m_bSaveROMPrograms;
	int		m_iDefaultAreaType;
	//}}AFX_DATA

  int m_iScreenFontSize;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPrefsP2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPrefsP2)
	afx_msg void OnFont();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PREFSP2_H__FA20E755_4BA7_11D2_AFA0_00A0247B3BFD__INCLUDED_)
