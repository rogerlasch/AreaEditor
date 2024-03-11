/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_SHOPVIEW_H__5E528976_FC08_11D1_A20B_0000B4595568__INCLUDED_)
#define AFX_SHOPVIEW_H__5E528976_FC08_11D1_A20B_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ShopView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CShopView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CShopView : public CFormView
{
protected:
	CShopView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CShopView)

// Form Data
public:
	//{{AFX_DATA(CShopView)
	enum { IDD = IDD_SHOP };
	CButton	m_ctlAddItem;
	CButton	m_ctlRemoveItem;
	CButton	m_ctlGoToItem;
	CListBox	m_ctlSellingList;
	CComboBox	m_ctlBuyType5;
	CComboBox	m_ctlBuyType4;
	CComboBox	m_ctlBuyType3;
	CComboBox	m_ctlBuyType2;
	CComboBox	m_ctlBuyType1;
	CButton	m_ctlGoTo;
	CEdit	m_ctlKeeper;
	CEdit	m_ctlKeeperDescription;
	int		m_keeper;
	int		m_profit_buy;
	int		m_profit_sell;
	int		m_open_hour;
	int		m_close_hour;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

  CShop * m_shop;
  CAreaEditorView * m_pLHview;

  CMobile * m_KeeperMob;
  CReset * m_KeeperReset;

  void AddItems (void);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShopView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CShopView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CShopView)
	afx_msg void OnChangeKeeper();
	afx_msg void OnChoose();
	afx_msg void OnGoto();
	afx_msg void OnDblclkSelling();
	afx_msg void OnSelchangeSelling();
	afx_msg void OnGotoObject();
	afx_msg void OnAddItem();
	afx_msg void OnRemoveItem();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOPVIEW_H__5E528976_FC08_11D1_A20B_0000B4595568__INCLUDED_)
