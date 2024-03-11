/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_MOBILEDEFENSESPAGE_H__4B7C1BD5_EDF7_11D1_A20A_0000B4595568__INCLUDED_)
#define AFX_MOBILEDEFENSESPAGE_H__4B7C1BD5_EDF7_11D1_A20A_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MobileDefensesPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMobileDefensesPage dialog

class CMobileDefensesPage : public CDialog
{
// Construction
public:
	CMobileDefensesPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMobileDefensesPage)
	enum { IDD = IDD_MOBILE_DEFENSES };
	BOOL	m_bless;
	BOOL	m_curecritical;
	BOOL	m_curelight;
	BOOL	m_cureserious;
	BOOL	m_disarm;
	BOOL	m_dispelevil;
	BOOL	m_dispelmagic;
	BOOL	m_dodge;
	BOOL	m_fireshield;
	BOOL	m_grip;
	BOOL	m_heal;
	BOOL	m_iceshield;
	BOOL	m_monsum1;
	BOOL	m_monsum2;
	BOOL	m_monsum4;
	BOOL	m_monsum3;
	BOOL	m_parry;
	BOOL	m_sanctuary;
	BOOL	m_shield;
	BOOL	m_shockshield;
	BOOL	m_stoneskin;
	BOOL	m_teleport;
	//}}AFX_DATA

  CMobile * m_mob;    // which mobile we are displaying

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMobileDefensesPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMobileDefensesPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOBILEDEFENSESPAGE_H__4B7C1BD5_EDF7_11D1_A20A_0000B4595568__INCLUDED_)
