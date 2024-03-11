/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_OBJECTEXTRAFLAGSPAGE_H__FF493039_F036_11D1_A20A_0000B4595568__INCLUDED_)
#define AFX_OBJECTEXTRAFLAGSPAGE_H__FF493039_F036_11D1_A20A_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ObjectExtraFlagsPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CObjectExtraFlagsPage dialog

class CObjectExtraFlagsPage : public CDialog
{
// Construction
public:
	CObjectExtraFlagsPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CObjectExtraFlagsPage)
	enum { IDD = IDD_OBJECT_EXTRA_FLAGS };
	BOOL	m_anti_cleric;
	BOOL	m_anti_druid;
	BOOL	m_anti_evil;
	BOOL	m_anti_good;
	BOOL	m_anti_mage;
	BOOL	m_anti_neutral;
	BOOL	m_anti_thief;
	BOOL	m_anti_vampire;
	BOOL	m_anti_warrior;
	BOOL	m_bless;
	BOOL	m_buried;
	BOOL	m_clancorpse;
	BOOL	m_clanobject;
	BOOL	m_covering;
	BOOL	m_dark;
	BOOL	m_deathrot;
	BOOL	m_donation;
	BOOL	m_evil;
	BOOL	m_glow;
	BOOL	m_hidden;
	BOOL	m_hum;
	BOOL	m_inventory;
	BOOL	m_invis;
	BOOL	m_loyal;
	BOOL	m_magic;
	BOOL	m_metal;
	BOOL	m_nodrop;
	BOOL	m_noremove;
	BOOL	m_organic;
	BOOL	m_poisoned;
	BOOL	m_prototype;
	BOOL	m_dual_wield;
	BOOL	m_hold;
	BOOL	m_missile_wield;
	BOOL	m_take;
	BOOL	m_wear_about;
	BOOL	m_wear_arms;
	BOOL	m_wear_body;
	BOOL	m_wear_ears;
	BOOL	m_wear_eyes;
	BOOL	m_wear_feet;
	BOOL	m_wear_finger;
	BOOL	m_wear_hands;
	BOOL	m_wear_head;
	BOOL	m_wear_legs;
	BOOL	m_wear_neck;
	BOOL	m_wear_shield;
	BOOL	m_wear_waist;
	BOOL	m_wear_wrist;
	BOOL	m_wield;
	//}}AFX_DATA

  CMUDObject * m_object;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CObjectExtraFlagsPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CObjectExtraFlagsPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OBJECTEXTRAFLAGSPAGE_H__FF493039_F036_11D1_A20A_0000B4595568__INCLUDED_)
