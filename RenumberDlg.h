/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_RENUMBERDLG_H__9D44F003_16B6_11D2_A20B_0000B4595568__INCLUDED_)
#define AFX_RENUMBERDLG_H__9D44F003_16B6_11D2_A20B_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RenumberDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRenumberDlg dialog

class CRenumberDlg : public CDialog
{
// Construction
public:
	CRenumberDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRenumberDlg)
	enum { IDD = IDD_RENUMBER };
	CEdit	m_ctlNewHighRoomVnum;
	CEdit	m_ctlNewHighObjVnum;
	CEdit	m_ctlNewHighMobVnum;
	CEdit	m_ctlNewLowMobVnum;
	CEdit	m_ctlNewLowRoomVnum;
	CEdit	m_ctlNewLowObjVnum;
	BOOL	m_bMobCompact;
	int		m_iMobCount;
	int		m_iMobHighVnum;
	int		m_iMobLowVnum;
	int		m_iNewHighMobVnum;
	int		m_iNewHighObjVnum;
	int		m_iNewHighRoomVnum;
	int		m_iNewLowMobVnum;
	int		m_iNewLowObjVnum;
	int		m_iNewLowRoomVnum;
	BOOL	m_bObjCompact;
	int		m_iObjCount;
	int		m_iObjHighVnum;
	int		m_iObjLowVnum;
	BOOL	m_bRoomCompact;
	int		m_iRoomCount;
	int		m_iRoomHighVnum;
	int		m_iRoomLowVnum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRenumberDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRenumberDlg)
	afx_msg void OnChangeNewLowMobVnum();
	afx_msg void OnChangeNewLowObjectVnum();
	afx_msg void OnChangeNewLowRoomVnum();
	afx_msg void OnMobCompact();
	afx_msg void OnObjectCompact();
	afx_msg void OnRoomCompact();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RENUMBERDLG_H__9D44F003_16B6_11D2_A20B_0000B4595568__INCLUDED_)
