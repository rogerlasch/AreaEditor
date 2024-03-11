/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_SKILLSLISTDLG_H__581F1494_0A26_11D2_A20B_0000B4595568__INCLUDED_)
#define AFX_SKILLSLISTDLG_H__581F1494_0A26_11D2_A20B_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SkillsListDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSkillsListDlg dialog

class CSkillsListDlg : public CDialog
{
// Construction
public:
	CSkillsListDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSkillsListDlg)
	enum { IDD = IDD_SKILLS_LIST };
	CListCtrl	m_ctlSkillsList;
	CString	m_strSkillsCount;
	//}}AFX_DATA

  int m_last_col;
  BOOL m_reverse;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkillsListDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:


  void RedrawList (void);

	// Generated message map functions
	//{{AFX_MSG(CSkillsListDlg)
	afx_msg void OnDblclkSkillsList(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnAdd();
	afx_msg void OnEdit();
	afx_msg void OnDelete();
	afx_msg void OnColumnclickSkillsList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
  afx_msg LRESULT OnKickIdle(WPARAM, LPARAM);
  afx_msg void OnUpdateNeedSelection(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKILLSLISTDLG_H__581F1494_0A26_11D2_A20B_0000B4595568__INCLUDED_)
