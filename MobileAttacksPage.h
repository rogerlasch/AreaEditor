/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_MOBILEATTACKSPAGE_H__4B7C1BD4_EDF7_11D1_A20A_0000B4595568__INCLUDED_)
#define AFX_MOBILEATTACKSPAGE_H__4B7C1BD4_EDF7_11D1_A20A_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MobileAttacksPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMobileAttacksPage dialog

class CMobileAttacksPage : public CDialog
{
// Construction
public:
	CMobileAttacksPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMobileAttacksPage)
	enum { IDD = IDD_MOBILE_ATTACKS };
	BOOL	m_acidbreath;
	BOOL	m_backstab;
	BOOL	m_bash;
	BOOL	m_bite;
	BOOL	m_blindness;
	BOOL	m_causecritical;
	BOOL	m_causeserious;
	BOOL	m_claws;
	BOOL	m_colorspray;
	BOOL	m_curse;
	BOOL	m_drain;
	BOOL	m_earthquake;
	BOOL	m_feed;
	BOOL	m_fireball;
	BOOL	m_firebreath;
	BOOL	m_flamestrike;
	BOOL	m_frostbreath;
	BOOL	m_gasbreath;
	BOOL	m_gaze;
	BOOL	m_gouge;
	BOOL	m_harm;
	BOOL	m_kick;
	BOOL	m_lightnbreath;
	BOOL	m_nastypoison;
	BOOL	m_poison;
	BOOL	m_punch;
	BOOL	m_spiralblast;
	BOOL	m_sting;
	BOOL	m_stun;
	BOOL	m_tail;
	BOOL	m_trip;
	BOOL	m_weaken;
	//}}AFX_DATA

  CMobile * m_mob;    // which mobile we are displaying

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMobileAttacksPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMobileAttacksPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOBILEATTACKSPAGE_H__4B7C1BD4_EDF7_11D1_A20A_0000B4595568__INCLUDED_)
