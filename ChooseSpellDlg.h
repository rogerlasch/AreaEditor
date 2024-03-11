/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_CHOOSESPELLDLG_H__581F1493_0A26_11D2_A20B_0000B4595568__INCLUDED_)
#define AFX_CHOOSESPELLDLG_H__581F1493_0A26_11D2_A20B_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ChooseSpellDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChooseSpellDlg dialog

class CChooseSpellDlg : public CDialog
{
// Construction
public:
	CChooseSpellDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChooseSpellDlg)
	enum { IDD = IDD_CHOOSE_SPELL };
	CButton	m_ctlOK;
	CButton	m_ctlFindNext;
	CListBox	m_ctlSpellList;
	//}}AFX_DATA


  int m_iSelectedSpell;

  CString m_strFindString;
  int m_nFoundItem;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChooseSpellDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChooseSpellDlg)
	afx_msg void OnDblclkSpellList();
	afx_msg void OnOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnFind();
	afx_msg void OnFindNext();
	afx_msg void OnSelchangeSpellList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHOOSESPELLDLG_H__581F1493_0A26_11D2_A20B_0000B4595568__INCLUDED_)
