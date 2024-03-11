/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// SkillsPages.h : header file
//

#ifndef __SKILLSPAGES_H__
#define __SKILLSPAGES_H__

/////////////////////////////////////////////////////////////////////////////
// CSkillsPage1 dialog

class CSkillsPage1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CSkillsPage1)

// Construction
public:
	CSkillsPage1();
	~CSkillsPage1();

// Dialog Data
	//{{AFX_DATA(CSkillsPage1)
	enum { IDD = IDD_SKILLSPAGE1 };
	CComboBox	m_ctlFunction;
	CComboBox	m_ctlPower;
	CComboBox	m_ctlDamage;
	CComboBox	m_ctlClass;
	CComboBox	m_ctlAction;
	CComboBox	m_ctlType;
	CString	m_name;
	int		m_slot;
	int		m_guild;
	int		m_min_level;
	int		m_min_mana;
	int		m_minimum_position;
	int		m_target;
	int		m_beats;
	CString	m_strFlags;
	CString	m_spell_skill_fun;
	int		m_range;
	int		m_info;
	//}}AFX_DATA

  CSkill * m_skill;


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSkillsPage1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSkillsPage1)
	afx_msg void OnSelchangeType();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


/////////////////////////////////////////////////////////////////////////////
// CSkillsPage2 dialog

class CSkillsPage2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CSkillsPage2)

// Construction
public:
	CSkillsPage2();
	~CSkillsPage2();

// Dialog Data
	//{{AFX_DATA(CSkillsPage2)
	enum { IDD = IDD_SKILLSPAGE2 };
	CString	m_noun_damage;
	CString	m_hit_char;
	CString	m_hit_room;
	CString	m_hit_vict;
	CString	m_msg_off;
	CString	m_die_char;
	CString	m_die_room;
	CString	m_die_vict;
	CString	m_imm_char;
	CString	m_imm_room;
	CString	m_imm_vict;
	CString	m_miss_char;
	CString	m_miss_room;
	CString	m_miss_vict;
	CString	m_hit_dest;
	//}}AFX_DATA

  CSkill * m_skill;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSkillsPage2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSkillsPage2)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


/////////////////////////////////////////////////////////////////////////////
// CSkillsPage3 dialog

class CSkillsPage3 : public CPropertyPage
{
	DECLARE_DYNCREATE(CSkillsPage3)

// Construction
public:
	CSkillsPage3();
	~CSkillsPage3();

// Dialog Data
	//{{AFX_DATA(CSkillsPage3)
	enum { IDD = IDD_SKILLSPAGE3 };
	CListCtrl	m_ctlAffectsList;
	int		m_difficulty;
	int		m_participants;
	int		m_saves;
	int		m_value;
	CString	m_dice;
	//}}AFX_DATA

  CSkill * m_skill;
  int m_last_col;
  BOOL m_reverse;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSkillsPage3)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
  
  void RedrawList (void);

	// Generated message map functions
	//{{AFX_MSG(CSkillsPage3)
	afx_msg void OnDblclkAffectsList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnclickAffectsList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnAdd();
	afx_msg void OnEdit();
	afx_msg void OnDelete();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
  afx_msg LRESULT OnKickIdle(WPARAM, LPARAM);
  afx_msg void OnUpdateNeedSelection(CCmdUI* pCmdUI);
  DECLARE_MESSAGE_MAP()

};


/////////////////////////////////////////////////////////////////////////////
// CSkillsPage4 dialog

class CSkillsPage4 : public CPropertyPage
{
	DECLARE_DYNCREATE(CSkillsPage4)

// Construction
public:
	CSkillsPage4();
	~CSkillsPage4();

// Dialog Data
	//{{AFX_DATA(CSkillsPage4)
	enum { IDD = IDD_SKILLSPAGE4 };
	BOOL	m_accumulative;
	BOOL	m_air;
	BOOL	m_area;
	BOOL	m_astral;
	BOOL	m_character;
	BOOL	m_distant;
	BOOL	m_earth;
	BOOL	m_groupspell;
	BOOL	m_nobrew;
	BOOL	m_noscribe;
	BOOL	m_object;
	BOOL	m_pksensitive;
	BOOL	m_recastable;
	BOOL	m_reverse;
	BOOL	m_save_half_damage;
	BOOL	m_save_negates;
	BOOL	m_secretskill;
	BOOL	m_stoponfail;
	BOOL	m_water;
	//}}AFX_DATA

  CSkill * m_skill;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSkillsPage4)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSkillsPage4)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};



#endif // __SKILLSPAGES_H__
