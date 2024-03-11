/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// ChooseSpellDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "ChooseSpellDlg.h"
#include "FindInDialogDlg.h"
#include "defaults.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChooseSpellDlg dialog


CChooseSpellDlg::CChooseSpellDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChooseSpellDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChooseSpellDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

  m_iSelectedSpell = -1;
  m_nFoundItem = -1;

}


void CChooseSpellDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChooseSpellDlg)
	DDX_Control(pDX, IDOK, m_ctlOK);
	DDX_Control(pDX, IDC_FIND_NEXT, m_ctlFindNext);
	DDX_Control(pDX, IDC_SPELL_LIST, m_ctlSpellList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChooseSpellDlg, CDialog)
	//{{AFX_MSG_MAP(CChooseSpellDlg)
	ON_LBN_DBLCLK(IDC_SPELL_LIST, OnDblclkSpellList)
	ON_BN_CLICKED(IDOK, OnOk)
	ON_BN_CLICKED(IDC_FIND, OnFind)
	ON_BN_CLICKED(IDC_FIND_NEXT, OnFindNext)
	ON_LBN_SELCHANGE(IDC_SPELL_LIST, OnSelchangeSpellList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChooseSpellDlg message handlers

void CChooseSpellDlg::OnDblclkSpellList() 
{
  OnOk ();
}

void CChooseSpellDlg::OnOk() 
{
// find which item they selected, and return its value

int nItem =  m_ctlSpellList.GetCurSel( );

  if (nItem != LB_ERR)
    m_iSelectedSpell = ((CSkill *) m_ctlSpellList.GetItemData (nItem))->slot;
	
	CDialog::OnOK();
	
}

BOOL CChooseSpellDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
POSITION pos;
CSkill * skill;
CString strSelectedItem;


  for (pos = App.m_SkillList.GetHeadPosition (); pos; )
    {
    skill = App.m_SkillList.GetNext (pos);

    // don't add spells without slots

    if (skill->slot == 0)
      continue;

    if (skill->type != SKILL_SPELL)
      continue;

    skill->AddToListBox (m_ctlSpellList);

    if (m_iSelectedSpell == skill->slot)
      strSelectedItem = skill->name;
    } // end of for loop


  // select the spell now (we can't do it earlier, as we sort the list)

  if (!strSelectedItem.IsEmpty ())
    m_ctlSpellList.SelectString(-1, strSelectedItem);
	

  OnSelchangeSpellList ();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CChooseSpellDlg::OnFind() 
{
CFindInDialogDlg dlg;

  dlg.m_strFindWhat = m_strFindString;
  if (dlg.DoModal () != IDOK)
    return;

  m_strFindString = dlg.m_strFindWhat;

  m_strFindString.MakeLower ();
  m_strFindString.TrimLeft ();
  m_strFindString.TrimRight ();

  m_ctlFindNext.EnableWindow (TRUE);

  m_ctlSpellList.SetCurSel(-1);    // force search from start
  OnSelchangeSpellList ();     // which means we can't do OK yet

  OnFindNext ();
	
}

void CChooseSpellDlg::OnFindNext() 
{
int nItem =  m_ctlSpellList.GetCurSel( );

if (nItem == LB_ERR)
  nItem = -1;


CString strItem;
for (nItem++; nItem < m_ctlSpellList.GetCount (); nItem++)

  {
  m_ctlSpellList.GetText(nItem, strItem);
  strItem.MakeLower ();
  strItem.TrimLeft ();
  strItem.TrimRight ();

  if (strItem.Find (m_strFindString) != -1)
    {
    m_ctlSpellList.SetCurSel(nItem);
    OnSelchangeSpellList ();
    m_nFoundItem = nItem;
    return;
    } // end of found a match
  } // end of looking at each item

CString strAgain;

  if (m_ctlSpellList.GetCurSel() == m_nFoundItem && 
      m_nFoundItem != -1)
      strAgain = " again";

  ::AfxMessageBox (CFormat ("Could not find \"%s\"%s", 
                   (LPCTSTR) m_strFindString,
                   (LPCTSTR) strAgain),
        MB_ICONINFORMATION);

  m_nFoundItem = -1;
	
}

void CChooseSpellDlg::OnSelchangeSpellList() 
{
int nItem =  m_ctlSpellList.GetCurSel( );

  m_ctlOK.EnableWindow (nItem != LB_ERR);
	
}
