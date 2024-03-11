/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_MOBILEACTIONSPAGE_H__ACFBE914_EB82_11D1_A20A_0000B4595568__INCLUDED_)
#define AFX_MOBILEACTIONSPAGE_H__ACFBE914_EB82_11D1_A20A_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MobileActionsPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMobileActionsPage dialog

class CMobileActionsPage : public CDialog
{
// Construction
public:
	CMobileActionsPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMobileActionsPage)
	enum { IDD = IDD_MOBILE_ACTIONS };
	BOOL	m_bAggressive;
	BOOL	m_bDeadly;
	BOOL	m_bGuardian;
	BOOL	m_bImmortal;
	BOOL	m_bIsNPC;
	BOOL	m_bMetaAggr;
	BOOL	m_bMobInvis;
	BOOL	m_bMountable;
	BOOL	m_bMounted;
	BOOL	m_bNoAssist;
	BOOL	m_bNoWander;
	BOOL	m_bPet;
	BOOL	m_bPolymorphed;
	BOOL	m_bPolySelf;
	BOOL	m_bPractice;
	BOOL	m_bPrototype;
	BOOL	m_bRunning;
	BOOL	m_bScavenger;
	BOOL	m_bScholar;
	BOOL	m_bSecretive;
	BOOL	m_bSentinel;
	BOOL	m_bStayArea;
	BOOL	m_bTrain;
	BOOL	m_bWimpy;
	//}}AFX_DATA

  CMobile * m_mob;    // which mobile we are displaying


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMobileActionsPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMobileActionsPage)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOBILEACTIONSPAGE_H__ACFBE914_EB82_11D1_A20A_0000B4595568__INCLUDED_)
