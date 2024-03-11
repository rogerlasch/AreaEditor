/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_PREFSP3_H__FA20E756_4BA7_11D2_AFA0_00A0247B3BFD__INCLUDED_)
#define AFX_PREFSP3_H__FA20E756_4BA7_11D2_AFA0_00A0247B3BFD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PrefsP3.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPrefsP3 dialog

class CPrefsP3 : public CPropertyPage
{
	DECLARE_DYNCREATE(CPrefsP3)

// Construction
public:
	CPrefsP3();
	~CPrefsP3();

// Dialog Data
	//{{AFX_DATA(CPrefsP3)
	enum { IDD = IDD_PREFSP3 };
	CStatic	m_ctlFontName;
	CString	m_strFontName;
	int		m_iLinesPerPage;
	int		m_iTopMargin;
	int		m_iLeftMargin;
	BOOL	m_bPrintToFile;
	BOOL	m_bShowPrograms;
	//}}AFX_DATA


  int m_iPrinterFontSize;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPrefsP3)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPrefsP3)
	afx_msg void OnFont();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PREFSP3_H__FA20E756_4BA7_11D2_AFA0_00A0247B3BFD__INCLUDED_)
