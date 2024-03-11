/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_CHOOSEROOMDLG_H__0C836F93_FFEE_11D1_A20B_0000B4595568__INCLUDED_)
#define AFX_CHOOSEROOMDLG_H__0C836F93_FFEE_11D1_A20B_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ChooseRoomDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChooseRoomDlg dialog

class CChooseRoomDlg : public CDialog
{
// Construction
public:
	CChooseRoomDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChooseRoomDlg)
	enum { IDD = IDD_CHOOSE_ROOM };
	CComboBox	m_ctlArea;
	CButton	m_ctlFindNext;
	CButton	m_ctlOK;
	CEdit	m_ctlFlags;
	CListBox	m_ctlRoomList;
	//}}AFX_DATA

//  CRoomList * m_RoomList;

  CAreaEditorDoc * m_pDoc;

  int m_iSelectedRoom;

  CString m_strFindString;
  int m_nFoundItem;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChooseRoomDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

  void ReloadList (void);

	// Generated message map functions
	//{{AFX_MSG(CChooseRoomDlg)
	afx_msg void OnDblclkRoomList();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeRoomList();
	afx_msg void OnFind();
	afx_msg void OnFindNext();
	afx_msg void OnSelchangeArea();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHOOSEROOMDLG_H__0C836F93_FFEE_11D1_A20B_0000B4595568__INCLUDED_)
