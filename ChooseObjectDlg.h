/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_CHOOSEOBJECTDLG_H__0C836F94_FFEE_11D1_A20B_0000B4595568__INCLUDED_)
#define AFX_CHOOSEOBJECTDLG_H__0C836F94_FFEE_11D1_A20B_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ChooseObjectDlg.h : header file
//

// item types

typedef enum
  { eAny,         // any item
    eShopItem,    // must be non-zero cost
    eWearItem,    // must be able to be worn
    eTakeItem,   // must be able to be taken
    eContainerItem, // must be a container
  }
  tItemType;

/////////////////////////////////////////////////////////////////////////////
// CChooseObjectDlg dialog

class CChooseObjectDlg : public CDialog
{
// Construction
public:
	CChooseObjectDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChooseObjectDlg)
	enum { IDD = IDD_CHOOSE_OBJECT };
	CComboBox	m_ctlArea;
	CButton	m_ctlFindNext;
	CComboBox	m_ctlType;
	CButton	m_ctlOK;
	CEdit	m_ctlValues;
	CEdit	m_ctlStats;
	CEdit	m_ctlDescription;
	CListBox	m_ctlObjectList;
	CString	m_strConditions;
	//}}AFX_DATA

  CAreaEditorDoc * m_pDoc;

  int m_iSelectedObject;

  int m_iWantedType;      // type of item (eg. weapon, food) 0=all

  tItemType m_iItemType;  // only show items of nonzero cost

  CString m_strFindString;
  int m_nFoundItem;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChooseObjectDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

  void ReloadList (void);

	// Generated message map functions
	//{{AFX_MSG(CChooseObjectDlg)
	afx_msg void OnDblclkObjectList();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeObjectList();
	afx_msg void OnSelchangeObjectType();
	afx_msg void OnFind();
	afx_msg void OnFindNext();
	afx_msg void OnSelchangeArea();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHOOSEOBJECTDLG_H__0C836F94_FFEE_11D1_A20B_0000B4595568__INCLUDED_)
