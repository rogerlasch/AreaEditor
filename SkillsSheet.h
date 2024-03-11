/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// SkillsSheet.h : header file
//
// This class defines custom modal property sheet 
// CSkillsSheet.
 
#ifndef __SKILLSSHEET_H__
#define __SKILLSSHEET_H__

#include "SkillsPages.h"

/////////////////////////////////////////////////////////////////////////////
// CSkillsSheet

class CSkillsSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CSkillsSheet)

// Construction
public:
	CSkillsSheet(CWnd* pWndParent = NULL, CSkill * skill = NULL);

// Attributes
public:
	CSkillsPage1 m_Page1;
	CSkillsPage2 m_Page2;
	CSkillsPage3 m_Page3;
	CSkillsPage4 m_Page4;

  CSkill * m_skill;
  bool m_bAdd;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkillsSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSkillsSheet();

// Generated message map functions
protected:
	//{{AFX_MSG(CSkillsSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
  afx_msg LRESULT OnKickIdle(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif	// __SKILLSSHEET_H__
