/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_MOBILESTATSPAGE_H__4B7C1BD3_EDF7_11D1_A20A_0000B4595568__INCLUDED_)
#define AFX_MOBILESTATSPAGE_H__4B7C1BD3_EDF7_11D1_A20A_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MobileStatsPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMobileStatsPage dialog

class CMobileStatsPage : public CDialog
{
// Construction
public:
	CMobileStatsPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMobileStatsPage)
	enum { IDD = IDD_MOBILE_STATS };
	CEdit	m_ctlNumAttacks;
	CStatic	m_ctlDamageTypeLabel;
	CComboBox	m_ctlDamageType;
	CEdit	m_ctlSavingSpell;
	CEdit	m_ctlSavingBreath;
	CEdit	m_ctlSavingPara;
	CEdit	m_ctlSavingWand;
	CEdit	m_ctlSavingPoison;
	CEdit	m_ctlMobthac0;
	CEdit	m_ctlLck;
	CEdit	m_ctlCha;
	CEdit	m_ctlCon;
	CEdit	m_ctlDex;
	CEdit	m_ctlWis;
	CEdit	m_ctlInt;
	CEdit	m_ctlStr;
	CComboBox	m_ctlSize;
	CEdit	m_ctlManaSizeDice;
	CEdit	m_ctlManaPlusDice;
	CEdit	m_ctlManaNoDice;
	CEdit	m_ctlArmourClass;
	CEdit	m_ctlHitPlus;
	CEdit	m_ctlHitSizeDice;
	CEdit	m_ctlHitNoDice;
	CComboBox	m_ctlDefposition;
	CComboBox	m_ctlPosition;
	CComboBox	m_ctlClass;
	CComboBox	m_ctlRace;
	int		m_ac;
	int		m_alignment;
	int		m_cha;
	int		m_con;
	int		m_damnodice;
	int		m_damplus;
	int		m_damroll;
	int		m_damsizedice;
	int		m_dex;
	int		m_exp;
	int		m_gold;
	int		m_height;
	int		m_hitnodice;
	int		m_hitplus;
	int		m_hitroll;
	int		m_hitsizedice;
	int		m_int;
	int		m_lck;
	int		m_mobthac0;
	int		m_numattacks;
	int		m_saving_breath;
	int		m_saving_poison_death;
	int		m_saving_wand;
	int		m_str;
	int		m_weight;
	int		m_wis;
	int		m_saving_spell_staff;
	int		m_saving_para_petri;
	int		m_mananodice;
	int		m_manasizedice;
	int		m_manaplusdice;
	CString	m_ac_label;
	CString	m_exp_label;
	CString	m_height_label;
	CString	m_weight_label;
	//}}AFX_DATA

  CMobile * m_mob;    // which mobile we are displaying

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMobileStatsPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMobileStatsPage)
	afx_msg void OnSuggestHit();
	afx_msg void OnSuggestAc();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOBILESTATSPAGE_H__4B7C1BD3_EDF7_11D1_A20A_0000B4595568__INCLUDED_)
