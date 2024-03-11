/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_ROOMSUMMARYPAGE_H__811BAEE3_F371_11D1_A20B_0000B4595568__INCLUDED_)
#define AFX_ROOMSUMMARYPAGE_H__811BAEE3_F371_11D1_A20B_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RoomSummaryPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRoomSummaryPage dialog

class CRoomSummaryPage : public CDialog
{
// Construction
public:
	CRoomSummaryPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRoomSummaryPage)
	enum { IDD = IDD_ROOM_SUMMARY };
	CButton	m_ctlRemove;
	CButton	m_ctlGive;
	CButton	m_ctlEquip;
	CListBox	m_ctlObjects;
	CButton	m_ctlGoToObject;
	CButton	m_ctlGoToEntrance;
	CListBox	m_ctlEntrances;
	CString	m_name;
	CString	m_sector_type;
	int		m_vnum;
	CString	m_strFlags;
	//}}AFX_DATA

  CRoom * m_room;
  CAreaEditorDoc * m_pDoc;
  CAreaEditorView * m_pLHview;

  void AddEntrances (void);

  void GiveOrEquip (const char cResetCommand);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRoomSummaryPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRoomSummaryPage)
	afx_msg void OnDblclkEntrances();
	afx_msg void OnGotoEntrance();
	afx_msg void OnSelchangeEntrances();
	afx_msg void OnSelcancelEntrances();
	afx_msg void OnGotoObject();
	afx_msg void OnDblclkObjects();
	afx_msg void OnSelchangeObjects();
	afx_msg void OnSelcancelObjects();
	afx_msg void OnAddMob();
	afx_msg void OnAddObject();
	afx_msg void OnRemove();
	afx_msg void OnEquip();
	afx_msg void OnGive();
	afx_msg void OnAddExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROOMSUMMARYPAGE_H__811BAEE3_F371_11D1_A20B_0000B4595568__INCLUDED_)
