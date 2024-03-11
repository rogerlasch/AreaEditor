/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_ROOMEXITDETAILS_H__413CED75_7E78_11D2_A26F_0000B4595568__INCLUDED_)
#define AFX_ROOMEXITDETAILS_H__413CED75_7E78_11D2_A26F_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RoomExitDetails.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRoomExitDetails dialog

class CRoomExitDetails : public CDialog
{
// Construction
public:
	CRoomExitDetails(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRoomExitDetails)
	enum { IDD = IDD_ROOM_EXIT_DETAILS };
	CButton	m_ctlGoToKey;
	CEdit	m_ctlKeyDescription;
	CButton	m_ctlGoTo;
	CComboBox	m_ctlDirection;
	CEdit	m_ctlExitTo;
	CEdit	m_ctlExitDescription;
	CEdit	m_ctlKey;
	CEdit	m_ctlDescription;
	CString	m_description;
	CString	m_keyword;
	int		m_vnum;
	int		m_key;
	int		m_distance;
	CString	m_strFlags;
	//}}AFX_DATA

  CExit * m_exit;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRoomExitDetails)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRoomExitDetails)
	afx_msg void OnUpdateExitTo();
	afx_msg void OnChoose();
	afx_msg void OnGoto();
	afx_msg void OnEdit();
	afx_msg void OnChooseKey();
	afx_msg void OnUpdateKey();
	afx_msg void OnGotoKey();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROOMEXITDETAILS_H__413CED75_7E78_11D2_A26F_0000B4595568__INCLUDED_)
