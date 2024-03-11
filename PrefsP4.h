/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_PREFSP4_H__7BD1AC4A_23A8_11D4_BB0D_0080AD7972EF__INCLUDED_)
#define AFX_PREFSP4_H__7BD1AC4A_23A8_11D4_BB0D_0080AD7972EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PrefsP4.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPrefsP4 dialog

class CPrefsP4 : public CPropertyPage
{
	DECLARE_DYNCREATE(CPrefsP4)

// Construction
public:
	CPrefsP4();
	~CPrefsP4();

// Dialog Data
	//{{AFX_DATA(CPrefsP4)
	enum { IDD = IDD_PREFSP4 };
	CButton	m_ctlEnable;
	BOOL	m_bAreaCheck;
	BOOL	m_bEditWindow;
	BOOL	m_bHelp;
	BOOL	m_bEnable;
	BOOL	m_bMobDesc;
	BOOL	m_bMobLong;
	BOOL	m_bMobName;
	BOOL	m_bMobShort;
	BOOL	m_bObjActionDesc;
	BOOL	m_bObjLong;
	BOOL	m_bObjName;
	BOOL	m_bObjShort;
	BOOL	m_bRoomDesc;
	BOOL	m_bRoomName;
	BOOL	m_bAcceptName;
	BOOL	m_bCheckView;
	BOOL	m_bExitDesc;
	BOOL	m_bExtraDesc;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPrefsP4)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPrefsP4)
	afx_msg void OnEnginePrefs();
	afx_msg void OnEnable();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PREFSP4_H__7BD1AC4A_23A8_11D4_BB0D_0080AD7972EF__INCLUDED_)
