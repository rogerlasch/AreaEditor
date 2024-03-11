/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_WEARFLAGSDLG_H__FA20E753_4BA7_11D2_AFA0_00A0247B3BFD__INCLUDED_)
#define AFX_WEARFLAGSDLG_H__FA20E753_4BA7_11D2_AFA0_00A0247B3BFD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// WearFlagsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWearFlagsDlg dialog

class CWearFlagsDlg : public CDialog
{
// Construction
public:
	CWearFlagsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWearFlagsDlg)
	enum { IDD = IDD_WEAR_FLAGS };
	CComboBox	m_ctlLocation;
	CString	m_strWearLocations;
	CString	m_strObject;
	//}}AFX_DATA

  int m_iWearLocation;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWearFlagsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWearFlagsDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WEARFLAGSDLG_H__FA20E753_4BA7_11D2_AFA0_00A0247B3BFD__INCLUDED_)
