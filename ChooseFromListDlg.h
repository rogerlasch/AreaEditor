/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_CHOOSEFROMLISTDLG_H__B17EA803_80D5_11D2_A270_0000B4595568__INCLUDED_)
#define AFX_CHOOSEFROMLISTDLG_H__B17EA803_80D5_11D2_A270_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ChooseFromListDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChooseFromListDlg dialog

class CChooseFromListDlg : public CDialog
{
// Construction
public:
	CChooseFromListDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChooseFromListDlg)
	enum { IDD = IDD_CHOOSE_FROM_LIST };
	CButton	m_ctlOK;
	CButton	m_ctlFindNext;
	CListBox	m_ctlItemList;
	//}}AFX_DATA

  // set these 3 things up before calling the dialog

  CConfigList * m_pList;    // which list to look at
  CString m_strTitle;       // what title to show
  int m_iSelectedItem;      // what item is initially (and finally) selected

protected:

  CString m_strFindString;
  int m_nFoundItem;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChooseFromListDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChooseFromListDlg)
	afx_msg void OnDblclkItemList();
	afx_msg void OnFind();
	afx_msg void OnFindNext();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeItemList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHOOSEFROMLISTDLG_H__B17EA803_80D5_11D2_A270_0000B4595568__INCLUDED_)
