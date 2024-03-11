/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_SOCIALSLISTDLG_H__60223705_0AF0_11D2_A20B_0000B4595568__INCLUDED_)
#define AFX_SOCIALSLISTDLG_H__60223705_0AF0_11D2_A20B_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SocialsListDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSocialsListDlg dialog

class CSocialsListDlg : public CDialog
{
// Construction
public:
	CSocialsListDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSocialsListDlg)
	enum { IDD = IDD_SOCIALS_LIST };
	CListCtrl	m_ctlSocialsList;
	CString	m_strSocialsCount;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSocialsListDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

  void RedrawList (void);

	// Generated message map functions
	//{{AFX_MSG(CSocialsListDlg)
	afx_msg void OnAdd();
	afx_msg void OnDelete();
	afx_msg void OnEdit();
	afx_msg void OnDblclkSocialsList(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG    
  afx_msg LRESULT OnKickIdle(WPARAM, LPARAM);
  afx_msg void OnUpdateNeedSelection(CCmdUI* pCmdUI);

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOCIALSLISTDLG_H__60223705_0AF0_11D2_A20B_0000B4595568__INCLUDED_)
