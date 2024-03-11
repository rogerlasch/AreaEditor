/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_MOBILERESISTANTPAGE_H__4B7C1BD7_EDF7_11D1_A20A_0000B4595568__INCLUDED_)
#define AFX_MOBILERESISTANTPAGE_H__4B7C1BD7_EDF7_11D1_A20A_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MobileResistantPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMobileResistantPage dialog

class CMobileResistantPage : public CDialog
{
// Construction
public:
	CMobileResistantPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMobileResistantPage)
	enum { IDD = IDD_MOBILE_RESISTANT };
	BOOL	m_res_acid;
	BOOL	m_res_blunt;
	BOOL	m_res_charm;
	BOOL	m_res_cold;
	BOOL	m_res_drain;
	BOOL	m_res_electricity;
	BOOL	m_res_energy;
	BOOL	m_res_fire;
	BOOL	m_res_hold;
	BOOL	m_res_magic;
	BOOL	m_res_nonmagic;
	BOOL	m_res_paralysis;
	BOOL	m_res_pierce;
	BOOL	m_res_plus1;
	BOOL	m_res_plus2;
	BOOL	m_res_plus3;
	BOOL	m_res_plus4;
	BOOL	m_res_plus5;
	BOOL	m_res_plus6;
	BOOL	m_res_poison;
	BOOL	m_res_slash;
	BOOL	m_res_sleep;
	BOOL	m_imm_acid;
	BOOL	m_imm_blunt;
	BOOL	m_imm_charm;
	BOOL	m_imm_cold;
	BOOL	m_imm_drain;
	BOOL	m_imm_electricity;
	BOOL	m_imm_energy;
	BOOL	m_imm_fire;
	BOOL	m_imm_hold;
	BOOL	m_imm_magic;
	BOOL	m_imm_nonmagic;
	BOOL	m_imm_paralysis;
	BOOL	m_imm_pierce;
	BOOL	m_imm_plus1;
	BOOL	m_imm_plus2;
	BOOL	m_imm_plus3;
	BOOL	m_imm_plus4;
	BOOL	m_imm_plus5;
	BOOL	m_imm_plus6;
	BOOL	m_imm_poison;
	BOOL	m_imm_slash;
	BOOL	m_imm_sleep;
	BOOL	m_sus_acid;
	BOOL	m_sus_blunt;
	BOOL	m_sus_charm;
	BOOL	m_sus_cold;
	BOOL	m_sus_drain;
	BOOL	m_sus_electricity;
	BOOL	m_sus_energy;
	BOOL	m_sus_fire;
	BOOL	m_sus_hold;
	BOOL	m_sus_magic;
	BOOL	m_sus_nonmagic;
	BOOL	m_sus_paralysis;
	BOOL	m_sus_pierce;
	BOOL	m_sus_plus1;
	BOOL	m_sus_plus2;
	BOOL	m_sus_plus3;
	BOOL	m_sus_plus4;
	BOOL	m_sus_plus5;
	BOOL	m_sus_plus6;
	BOOL	m_sus_poison;
	BOOL	m_sus_slash;
	BOOL	m_sus_sleep;
	//}}AFX_DATA

  CMobile * m_mob;    // which mobile we are displaying


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMobileResistantPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMobileResistantPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOBILERESISTANTPAGE_H__4B7C1BD7_EDF7_11D1_A20A_0000B4595568__INCLUDED_)
