/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_CHOOSEMOBDLG_H__FA114F04_FF3B_11D1_A20B_0000B4595568__INCLUDED_)
#define AFX_CHOOSEMOBDLG_H__FA114F04_FF3B_11D1_A20B_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ChooseMobDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChooseMobDlg dialog

class CChooseMobDlg : public CDialog
{
// Construction
public:
	CChooseMobDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChooseMobDlg)
	enum { IDD = IDD_CHOOSE_MOB };
	CComboBox	m_ctlArea;
	CButton	m_ctlFindNext;
	CButton	m_ctlOK;
	CEdit	m_ctlStats;
	CEdit	m_ctlSummary;
	CEdit	m_ctlDescription;
	CListBox	m_ctlMobList;
	//}}AFX_DATA


  CAreaEditorDoc * m_pDoc;

  int m_iSelectedMob;

  CString m_strFindString;
  int m_nFoundItem;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChooseMobDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

  void ReloadList (void);

	// Generated message map functions
	//{{AFX_MSG(CChooseMobDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkMobList();
	virtual void OnOK();
	afx_msg void OnSelchangeMobList();
	afx_msg void OnFind();
	afx_msg void OnFindNext();
	afx_msg void OnSelchangeArea();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHOOSEMOBDLG_H__FA114F04_FF3B_11D1_A20B_0000B4595568__INCLUDED_)
