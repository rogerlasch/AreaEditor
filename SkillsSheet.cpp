/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// SkillsSheet.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "AreaEditor.h"
#include "SkillsSheet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkillsSheet

IMPLEMENT_DYNAMIC(CSkillsSheet, CPropertySheet)

CSkillsSheet::CSkillsSheet(CWnd* pWndParent, CSkill * skill)
	 : CPropertySheet("Edit skill/spell", pWndParent),
     m_skill (skill)
{

	AddPage(&m_Page1);
	AddPage(&m_Page2);
	AddPage(&m_Page3);
	AddPage(&m_Page4);

  m_Page1.m_skill = m_skill;
  m_Page2.m_skill = m_skill;
  m_Page3.m_skill = m_skill;
  m_Page4.m_skill = m_skill;
  
  m_bAdd = false;
  }

CSkillsSheet::~CSkillsSheet()
{
}


BEGIN_MESSAGE_MAP(CSkillsSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CSkillsSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
  ON_MESSAGE(WM_KICKIDLE, OnKickIdle)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSkillsSheet message handlers


LRESULT CSkillsSheet::OnKickIdle(WPARAM, LPARAM)
  {
  GetActivePage ()->SendMessage (WM_KICKIDLE, 0, 0);
  return 0;
  } // end of CPrefsPropertySheet::OnKickIdle
