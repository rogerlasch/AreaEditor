/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_MOBILERESETSPAGE_H__B62F65B5_0703_11D2_A20B_0000B4595568__INCLUDED_)
#define AFX_MOBILERESETSPAGE_H__B62F65B5_0703_11D2_A20B_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MobileResetsPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMobileResetsPage dialog

class CMobileResetsPage : public CDialog
{
// Construction
public:
	CMobileResetsPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMobileResetsPage)
	enum { IDD = IDD_MOBILE_RESETS };
	CButton	m_ctlGoToReset;
	CListBox	m_ctlLoadedList;
	//}}AFX_DATA

  CMobile * m_mob;    // which mobile we are displaying

  CAreaEditorDoc * m_pDoc;
  void AddResets (void);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMobileResetsPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:


	// Generated message map functions
	//{{AFX_MSG(CMobileResetsPage)
	afx_msg void OnGotoReset();
	afx_msg void OnSelchangeLoaded();
	afx_msg void OnDblclkLoaded();
	afx_msg void OnSelcancelLoaded();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOBILERESETSPAGE_H__B62F65B5_0703_11D2_A20B_0000B4595568__INCLUDED_)
