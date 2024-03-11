/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_CHOOSEFLAGSDLG_H__B17EA804_80D5_11D2_A270_0000B4595568__INCLUDED_)
#define AFX_CHOOSEFLAGSDLG_H__B17EA804_80D5_11D2_A270_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ChooseFlagsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChooseFlagsDlg dialog

class CChooseFlagsDlg : public CDialog
{
// Construction
public:
	CChooseFlagsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChooseFlagsDlg)
	enum { IDD = IDD_CHOOSE_FLAGS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

  EXT_BV m_pFlags;           // the flags
  tFlags * m_pFlagsArray; // definition array
  t_areatype m_AreaType;  // what sort of area we are dealing with
  CString m_strTitle;     // what title to show

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChooseFlagsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChooseFlagsDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHOOSEFLAGSDLG_H__B17EA804_80D5_11D2_A270_0000B4595568__INCLUDED_)
