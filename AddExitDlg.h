/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_ADDEXITDLG_H__68A3F686_4F56_11D2_AFA1_00A0247B3BFD__INCLUDED_)
#define AFX_ADDEXITDLG_H__68A3F686_4F56_11D2_AFA1_00A0247B3BFD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AddExitDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddExitDlg dialog

class CAddExitDlg : public CDialog
{
// Construction
public:
	CAddExitDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddExitDlg)
	enum { IDD = IDD_ADD_EXIT };
	CButton	m_ctlOK;
	CComboBox	m_ctlDirection;
	CListBox	m_ctlExitList;
	BOOL	m_bMakeReverse;
	//}}AFX_DATA

  CRoom * m_room;
  int m_iDirection;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddExitDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddExitDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeDirection();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDEXITDLG_H__68A3F686_4F56_11D2_AFA1_00A0247B3BFD__INCLUDED_)
