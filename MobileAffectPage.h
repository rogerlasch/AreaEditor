/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_MOBILEAFFECTPAGE_H__ACFBE916_EB82_11D1_A20A_0000B4595568__INCLUDED_)
#define AFX_MOBILEAFFECTPAGE_H__ACFBE916_EB82_11D1_A20A_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MobileAffectPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMobileAffectPage dialog

class CMobileAffectPage : public CDialog
{
// Construction
public:
	CMobileAffectPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMobileAffectPage)
	enum { IDD = IDD_MOBILE_AFFECT };
	BOOL	m_bBlind;
	BOOL	m_bInvisible;
	BOOL	m_bAquaBreath;
	BOOL	m_bBerserk;
	BOOL	m_bCharm;
	BOOL	m_bCurse;
	BOOL	m_bDetectEvil;
	BOOL	m_bDetectHidden;
	BOOL	m_bDetectInvis;
	BOOL	m_bDetectMagic;
	BOOL	m_bDetectTraps;
	BOOL	m_bFaeireFire;
	BOOL	m_bFireShield;
	BOOL	m_bFlaming;
	BOOL	m_bFloating;
	BOOL	m_bFlying;
	BOOL	m_bHaus1;
	BOOL	m_bHide;
	BOOL	m_bHold;
	BOOL	m_bIceShield;
	BOOL	m_bInfraRed;
	BOOL	m_bParalysis;
	BOOL	m_bPassDoor;
	BOOL	m_bPoison;
	BOOL	m_bPossess;
	BOOL	m_bProtect;
	BOOL	m_bSanctuary;
	BOOL	m_bScrying;
	BOOL	m_bShockShield;
	BOOL	m_bSleep;
	BOOL	m_bSneak;
	BOOL	m_bTrueSight;
	//}}AFX_DATA

  CMobile * m_mob;    // which mobile we are displaying

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMobileAffectPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMobileAffectPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOBILEAFFECTPAGE_H__ACFBE916_EB82_11D1_A20A_0000B4595568__INCLUDED_)
