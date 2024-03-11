/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// MobileSummaryPage.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "AreaEditorDoc.h"
#include "defaults.h"

#include "MobileSummaryPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMobileSummaryPage dialog


CMobileSummaryPage::CMobileSummaryPage(CWnd* pParent /*=NULL*/)
	: CDialog(CMobileSummaryPage::IDD /* , pParent */)
{
	//{{AFX_DATA_INIT(CMobileSummaryPage)
	m_player_name = _T("");
	m_short_descr = _T("");
	m_long_descr = _T("");
	m_strActions = _T("");
	m_vnum = 0;
	m_strAffectedBy = _T("");
	m_level = 0;
	m_strStats = _T("");
	m_strBodyParts = _T("");
	m_strAttacks = _T("");
	m_strDefenses = _T("");
	m_strResistant = _T("");
	m_strImmune = _T("");
	m_strSusceptible = _T("");
	m_strSpeaks = _T("");
	m_strSpeaking = _T("");
	m_strDefensesLabel = _T("");
	m_strSex = _T("");
	m_strAverage = _T("");
	//}}AFX_DATA_INIT

  m_mob = NULL;

}

#undef LOAD_VALUE
#define LOAD_VALUE(field, value)  \
  field = m_mob->value


void CMobileSummaryPage::DoDataExchange(CDataExchange* pDX)
{

  if (!pDX->m_bSaveAndValidate)
    {
  	LOAD_VALUE (m_vnum, vnum);
    LOAD_VALUE (m_level, level);
	  LOAD_VALUE (m_player_name, player_name);
	  LOAD_VALUE (m_short_descr, short_descr);
	  LOAD_VALUE (m_long_descr , long_descr);  

    m_strActions = convert_actflag (m_mob->act);
    m_strAffectedBy = convert_affectflag (m_mob->affected_by);
    m_strBodyParts = convert_partflag (m_mob->xflags);
    m_strAttacks = convert_attackflag (m_mob->attacks);

    int avgHit = (m_mob->hitnodice * m_mob->hitsizedice + m_mob->hitplus) / 2;
    int avgDam = (m_mob->damnodice * m_mob->damsizedice + m_mob->damplus) / 2;
    int avgMana = (m_mob->mananodice * m_mob->manasizedice + m_mob->manaplus) / 2;

    m_strAverage = CFormat ("Hit = %i, Damage = %i", avgHit, avgDam);

    if (m_mob->m_pDoc->m_AreaType == eROM)
      {
      m_strAverage += CFormat (", Mana = %i", avgMana);
      m_strDefensesLabel = "Form:";
      m_strDefenses = convert_formflag (m_mob->form);
      }
    else
      {
      m_strDefensesLabel = "Defenses:";
      m_strDefenses = convert_defenseflag (m_mob->defenses);
      }
    m_strResistant = convert_risflag (m_mob->resistant);
    m_strImmune = convert_risflag (m_mob->immune);
    m_strSusceptible = convert_risflag (m_mob->susceptible);
	  m_strSpeaks = convert_languages (m_mob->speaks);
	  m_strSpeaking = convert_languages (m_mob->speaking);
    m_strSex = MobSexList.ReturnName (m_mob->sex, false);

    m_strStats = CFormat (
      "Str: %i, Int: %i, Wis: %i, Dex: %i, Con: %i, Cha: %i, Lck: %i",
      m_mob->perm_str, m_mob->perm_int, m_mob->perm_wis, 
      m_mob->perm_dex, m_mob->perm_con, m_mob->perm_cha, m_mob->perm_lck);

    }

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMobileSummaryPage)
	DDX_Control(pDX, IDC_SPEAKING_LABEL, m_ctlSpeakingLabel);
	DDX_Control(pDX, IDC_SPEAKING, m_ctlSpeaking);
	DDX_Control(pDX, IDC_SPEAKS, m_ctlSpeaks);
	DDX_Control(pDX, IDC_SPEAKS_LABEL, m_ctlSpeaksLabel);
	DDX_Text(pDX, IDC_NAME, m_player_name);
	DDX_Text(pDX, IDC_SHORT_DESCRIPTION, m_short_descr);
	DDX_Text(pDX, IDC_LONG_DESCRIPTION, m_long_descr);
	DDX_Text(pDX, IDC_ACTIONS, m_strActions);
	DDX_Text(pDX, IDC_VNUM, m_vnum);
	DDX_Text(pDX, IDC_AFFECTEDBY, m_strAffectedBy);
	DDX_Text(pDX, IDC_LEVEL, m_level);
	DDX_Text(pDX, IDC_STATS, m_strStats);
	DDX_Text(pDX, IDC_BODYPARTS, m_strBodyParts);
	DDX_Text(pDX, IDC_ATTACKS, m_strAttacks);
	DDX_Text(pDX, IDC_DEFENSES, m_strDefenses);
	DDX_Text(pDX, IDC_RESISTANT, m_strResistant);
	DDX_Text(pDX, IDC_IMMUNE, m_strImmune);
	DDX_Text(pDX, IDC_SUSCEPTIBLE, m_strSusceptible);
	DDX_Text(pDX, IDC_SPEAKS, m_strSpeaks);
	DDX_Text(pDX, IDC_SPEAKING, m_strSpeaking);
	DDX_Text(pDX, IDC_DEFENSES_LABEL, m_strDefensesLabel);
	DDX_Text(pDX, IDC_SEX, m_strSex);
	DDX_Text(pDX, IDC_AVERAGE, m_strAverage);
	//}}AFX_DATA_MAP


  if (!pDX->m_bSaveAndValidate)
    {

    if (m_mob->m_pDoc->m_AreaType != eSMAUG)
      {
      m_ctlSpeakingLabel.ShowWindow (SW_HIDE);
      m_ctlSpeaking.ShowWindow (SW_HIDE);
      m_ctlSpeaks.ShowWindow (SW_HIDE);
      m_ctlSpeaksLabel.ShowWindow (SW_HIDE);
      }   // end of not SMAUG
    }   // end of not saving

}


BEGIN_MESSAGE_MAP(CMobileSummaryPage, CDialog)
	//{{AFX_MSG_MAP(CMobileSummaryPage)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMobileSummaryPage message handlers

void CMobileSummaryPage::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}
  