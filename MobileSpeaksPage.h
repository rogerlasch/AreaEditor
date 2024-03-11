/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_MOBILESPEAKSPAGE_H__4B7C1BD8_EDF7_11D1_A20A_0000B4595568__INCLUDED_)
#define AFX_MOBILESPEAKSPAGE_H__4B7C1BD8_EDF7_11D1_A20A_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MobileSpeaksPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMobileSpeaksPage dialog

class CMobileSpeaksPage : public CDialog
{
// Construction
public:
	CMobileSpeaksPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMobileSpeaksPage)
	enum { IDD = IDD_MOBILE_SPEAKS };
	BOOL	m_ancient;
	BOOL	m_clan;
	BOOL	m_common;
	BOOL	m_dragon;
	BOOL	m_dwarven;
	BOOL	m_elven;
	BOOL	m_gith;
	BOOL	m_goblin;
	BOOL	m_god;
	BOOL	m_halfling;
	BOOL	m_insectoid;
	BOOL	m_magical;
	BOOL	m_mammal;
	BOOL	m_ogre;
	BOOL	m_orcish;
	BOOL	m_pixie;
	BOOL	m_reptile;
	BOOL	m_rodent;
	BOOL	m_spiritual;
	BOOL	m_trollish;
	BOOL	m_spk_ancient;
	BOOL	m_spk_clan;
	BOOL	m_spk_common;
	BOOL	m_spk_dragon;
	BOOL	m_spk_dwarven;
	BOOL	m_spk_elven;
	BOOL	m_spk_gith;
	BOOL	m_spk_goblin;
	BOOL	m_spk_god;
	BOOL	m_spk_halfling;
	BOOL	m_spk_insectoid;
	BOOL	m_spk_magical;
	BOOL	m_spk_mammal;
	BOOL	m_spk_ogre;
	BOOL	m_spk_orcish;
	BOOL	m_spk_pixie;
	BOOL	m_spk_reptile;
	BOOL	m_spk_rodent;
	BOOL	m_spk_spiritual;
	BOOL	m_spk_trollish;
	//}}AFX_DATA

  CMobile * m_mob;    // which mobile we are displaying

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMobileSpeaksPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMobileSpeaksPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOBILESPEAKSPAGE_H__4B7C1BD8_EDF7_11D1_A20A_0000B4595568__INCLUDED_)
