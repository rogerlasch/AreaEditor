/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_OBJECTRESETSPAGE_H__B62F65B6_0703_11D2_A20B_0000B4595568__INCLUDED_)
#define AFX_OBJECTRESETSPAGE_H__B62F65B6_0703_11D2_A20B_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ObjectResetsPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CObjectResetsPage dialog

class CObjectResetsPage : public CDialog
{
// Construction
public:
	CObjectResetsPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CObjectResetsPage)
	enum { IDD = IDD_OBJECT_RESETS };
	CButton	m_ctlGoToReset;
	CListBox	m_ctlLoadedList;
	//}}AFX_DATA

  CMUDObject * m_object;    // which object we are displaying

  CAreaEditorDoc * m_pDoc;
  void AddResets (void);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CObjectResetsPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CObjectResetsPage)
	afx_msg void OnGotoReset();
	afx_msg void OnDblclkLoaded();
	afx_msg void OnSelcancelLoaded();
	afx_msg void OnSelchangeLoaded();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OBJECTRESETSPAGE_H__B62F65B6_0703_11D2_A20B_0000B4595568__INCLUDED_)
