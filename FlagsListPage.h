/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_FLAGSLISTPAGE_H__35B8FDE1_0439_11D4_BB06_0080AD7972EF__INCLUDED_)
#define AFX_FLAGSLISTPAGE_H__35B8FDE1_0439_11D4_BB06_0080AD7972EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FlagsListPage.h : header file
//

#include "defaults.h"

/////////////////////////////////////////////////////////////////////////////
// CFlagsListPage dialog

class CFlagsListPage : public CDialog
{
// Construction
public:
	CFlagsListPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFlagsListPage)
	enum { IDD = IDD_SELECT_FROM_LIST };
	CListBox	m_ctlSelectedList;
	CListBox	m_ctlAvailableList;
	//}}AFX_DATA

  EXT_BV * m_pFlags;   // pointer to where the flags are
  tFlags * m_pFlagsArray;
  CAreaEditorDoc * m_pDoc;  // document - so we can set modified flag

  EXT_BV m_NewFlags;   // new flags values

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlagsListPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

  void LoadLists (void);

	// Generated message map functions
	//{{AFX_MSG(CFlagsListPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnInsert();
	afx_msg void OnDelete();
	afx_msg void OnDblclkAvailableList();
	afx_msg void OnDblclkSelectedList();
	afx_msg void OnSelchangeAvailableList();
	afx_msg void OnSelchangeSelectedList();
	afx_msg void OnSelcancelAvailableList();
	afx_msg void OnSelcancelSelectedList();
	//}}AFX_MSG
  afx_msg LRESULT OnKickIdle(WPARAM, LPARAM);
  afx_msg void OnUpdateInsert(CCmdUI* pCmdUI);
  afx_msg void OnUpdateRemove(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLAGSLISTPAGE_H__35B8FDE1_0439_11D4_BB06_0080AD7972EF__INCLUDED_)
