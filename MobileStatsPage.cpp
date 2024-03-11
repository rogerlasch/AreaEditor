/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// MobileStatsPage.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "AreaEditorDoc.h"
#include "defaults.h"

#include "MobileStatsPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMobileStatsPage dialog


CMobileStatsPage::CMobileStatsPage(CWnd* pParent /*=NULL*/)
	: CDialog(CMobileStatsPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMobileStatsPage)
	m_ac = 0;
	m_alignment = 0;
	m_cha = 0;
	m_con = 0;
	m_damnodice = 0;
	m_damplus = 0;
	m_damroll = 0;
	m_damsizedice = 0;
	m_dex = 0;
	m_exp = 0;
	m_gold = 0;
	m_height = 0;
	m_hitnodice = 0;
	m_hitplus = 0;
	m_hitroll = 0;
	m_hitsizedice = 0;
	m_int = 0;
	m_lck = 0;
	m_mobthac0 = 0;
	m_numattacks = 0;
	m_saving_breath = 0;
	m_saving_poison_death = 0;
	m_saving_wand = 0;
	m_str = 0;
	m_weight = 0;
	m_wis = 0;
	m_saving_spell_staff = 0;
	m_saving_para_petri = 0;
	m_mananodice = 0;
	m_manasizedice = 0;
	m_manaplusdice = 0;
	m_ac_label = _T("");
	m_exp_label = _T("");
	m_height_label = _T("");
	m_weight_label = _T("");
	//}}AFX_DATA_INIT

  m_mob = NULL;

}

#undef LOAD_VALUE
#define LOAD_VALUE(field, value)  \
  field = m_mob->value

#undef UNLOAD_VALUE
#define UNLOAD_VALUE(field, value)  \
  do {    \
    if (field != m_mob->value) bChanged = true; \
    m_mob->value = field;   \
    } while (false)

void CMobileStatsPage::DoDataExchange(CDataExchange* pDX)
{
bool bChanged = false;

  if (!pDX->m_bSaveAndValidate)
    {
	  LOAD_VALUE (m_alignment, alignment);
	  LOAD_VALUE (m_cha, perm_cha);
	  LOAD_VALUE (m_con, perm_con);
	  LOAD_VALUE (m_damnodice, damnodice);
	  LOAD_VALUE (m_damplus, damplus);
	  LOAD_VALUE (m_damroll, damroll);
	  LOAD_VALUE (m_damsizedice, damsizedice);
	  LOAD_VALUE (m_mananodice, mananodice);
	  LOAD_VALUE (m_manaplusdice, manaplus);
	  LOAD_VALUE (m_manasizedice, manasizedice);
	  LOAD_VALUE (m_dex, perm_dex);
	  LOAD_VALUE (m_gold, gold);
	  LOAD_VALUE (m_hitnodice, hitnodice);
	  LOAD_VALUE (m_hitplus, hitplus);
	  LOAD_VALUE (m_hitroll, hitroll);
	  LOAD_VALUE (m_hitsizedice, hitsizedice);
	  LOAD_VALUE (m_int, perm_int);
	  LOAD_VALUE (m_lck, perm_lck);
	  LOAD_VALUE (m_mobthac0, mobthac0);
	  LOAD_VALUE (m_numattacks, numattacks);
	  LOAD_VALUE (m_saving_breath, saving_breath);
	  LOAD_VALUE (m_saving_para_petri, saving_para_petri);
	  LOAD_VALUE (m_saving_poison_death, saving_poison_death);
	  LOAD_VALUE (m_saving_spell_staff, saving_spell_staff);
	  LOAD_VALUE (m_saving_wand, saving_wand);
	  LOAD_VALUE (m_str, perm_str);
	  LOAD_VALUE (m_wis, perm_wis);

    if (m_mob && m_mob->m_pDoc->m_AreaType == eSMAUG)
      {
      m_ac_label = "AC:";
      m_exp_label = "Exp:";
      m_height_label = "Height:";
      m_weight_label = "Weight:";
  	  LOAD_VALUE (m_ac, ac);
  	  LOAD_VALUE (m_exp, exp);
  	  LOAD_VALUE (m_height, height);
  	  LOAD_VALUE (m_weight, weight);
      } // end of SMAUG mob
    else if (m_mob && m_mob->m_pDoc->m_AreaType == eROM)
      {
      m_ac_label = "AC pierce:";
      m_exp_label = "AC bash:";
      m_height_label = "AC slash:";
      m_weight_label = "AC exotic:";
  	  LOAD_VALUE (m_ac, ac_pierce);
  	  LOAD_VALUE (m_exp, ac_bash);
  	  LOAD_VALUE (m_height, ac_slash);
  	  LOAD_VALUE (m_weight, ac_exotic);
      } // end of ROM mob

    }


	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMobileStatsPage)
	DDX_Control(pDX, IDC_NUMATTACKS, m_ctlNumAttacks);
	DDX_Control(pDX, IDC_DAMAGE_TYPE_LABEL, m_ctlDamageTypeLabel);
	DDX_Control(pDX, IDC_DAMAGE_TYPE, m_ctlDamageType);
	DDX_Control(pDX, IDC_SAVING_SPELL_STAFF, m_ctlSavingSpell);
	DDX_Control(pDX, IDC_SAVING_BREATH, m_ctlSavingBreath);
	DDX_Control(pDX, IDC_SAVING_PARA_PETRI, m_ctlSavingPara);
	DDX_Control(pDX, IDC_SAVING_WAND, m_ctlSavingWand);
	DDX_Control(pDX, IDC_SAVING_POISON_DEATH, m_ctlSavingPoison);
	DDX_Control(pDX, IDC_MOBTHAC0, m_ctlMobthac0);
	DDX_Control(pDX, IDC_LCK, m_ctlLck);
	DDX_Control(pDX, IDC_CHA, m_ctlCha);
	DDX_Control(pDX, IDC_CON, m_ctlCon);
	DDX_Control(pDX, IDC_DEX, m_ctlDex);
	DDX_Control(pDX, IDC_WIS, m_ctlWis);
	DDX_Control(pDX, IDC_INT, m_ctlInt);
	DDX_Control(pDX, IDC_STR, m_ctlStr);
	DDX_Control(pDX, IDC_MOBSIZE, m_ctlSize);
	DDX_Control(pDX, IDC_MANASIZEDICE, m_ctlManaSizeDice);
	DDX_Control(pDX, IDC_MANAPLUS, m_ctlManaPlusDice);
	DDX_Control(pDX, IDC_MANANODICE, m_ctlManaNoDice);
	DDX_Control(pDX, IDC_AC, m_ctlArmourClass);
	DDX_Control(pDX, IDC_HITPLUS, m_ctlHitPlus);
	DDX_Control(pDX, IDC_HITSIZEDICE, m_ctlHitSizeDice);
	DDX_Control(pDX, IDC_HITNODICE, m_ctlHitNoDice);
	DDX_Control(pDX, IDC_DEFPOSITION, m_ctlDefposition);
	DDX_Control(pDX, IDC_POSITION, m_ctlPosition);
	DDX_Control(pDX, IDC_CLASS, m_ctlClass);
	DDX_Control(pDX, IDC_RACE, m_ctlRace);
	DDX_Text(pDX, IDC_GOLD, m_gold);
	DDX_Text(pDX, IDC_AC_LABEL, m_ac_label);
	DDX_Text(pDX, IDC_EXP_LABEL, m_exp_label);
	DDX_Text(pDX, IDC_HEIGHT_LABEL, m_height_label);
	DDX_Text(pDX, IDC_WEIGHT_LABEL, m_weight_label);
	//}}AFX_DATA_MAP

  // basic stats    - SMAUG
  if (m_mob->m_pDoc->m_AreaType == eSMAUG)
    {
	  DDX_Text(pDX, IDC_CHA, m_cha);
	  DDV_MinMaxInt(pDX, m_cha, iMinStats, iMaxStats);
	  DDX_Text(pDX, IDC_CON, m_con);
	  DDV_MinMaxInt(pDX, m_con, iMinStats, iMaxStats);
	  DDX_Text(pDX, IDC_DEX, m_dex);
	  DDV_MinMaxInt(pDX, m_dex, iMinStats, iMaxStats);
	  DDX_Text(pDX, IDC_INT, m_int);
	  DDV_MinMaxInt(pDX, m_int, iMinStats, iMaxStats);
	  DDX_Text(pDX, IDC_LCK, m_lck);
	  DDV_MinMaxInt(pDX, m_lck, iMinStats, iMaxStats);
	  DDX_Text(pDX, IDC_STR, m_str);
	  DDV_MinMaxInt(pDX, m_str, iMinStats, iMaxStats);
	  DDX_Text(pDX, IDC_WIS, m_wis);
	  DDV_MinMaxInt(pDX, m_wis, iMinStats, iMaxStats);

    // this is SMAUG only too
  	DDX_Text(pDX, IDC_MOBTHAC0, m_mobthac0);
    }

  // alignment
	DDX_Text(pDX, IDC_ALIGNMENT, m_alignment);
	DDV_MinMaxInt(pDX, m_alignment, iMinAlignment, iMaxAlignment);

  // SMAUG: ac, exp, height, weight
  if (m_mob->m_pDoc->m_AreaType == eSMAUG)
    {
	  DDX_Text(pDX, IDC_AC, m_ac);
    DDV_MinMaxInt(pDX, m_ac, iMinAC, iMaxAC);
	  DDX_Text(pDX, IDC_EXP, m_exp);
	  DDX_Text(pDX, IDC_HEIGHT, m_height);
	  DDX_Text(pDX, IDC_WEIGHT, m_weight);
    }
  else if (m_mob->m_pDoc->m_AreaType == eROM)
    {
	  DDX_Text(pDX, IDC_AC, m_ac);
    DDV_MinMaxInt(pDX, m_ac, iMinAC, iMaxAC);
	  DDX_Text(pDX, IDC_EXP, m_exp);
    DDV_MinMaxInt(pDX, m_exp, iMinAC, iMaxAC);
	  DDX_Text(pDX, IDC_HEIGHT, m_height);
    DDV_MinMaxInt(pDX, m_height, iMinAC, iMaxAC);
	  DDX_Text(pDX, IDC_WEIGHT, m_weight);
    DDV_MinMaxInt(pDX, m_weight, iMinAC, iMaxAC);
    }

  // damage
	DDX_Text(pDX, IDC_DAMNODICE, m_damnodice);
	DDV_MinMaxInt(pDX, m_damnodice, 0, iMaxdamnodice);
	DDX_Text(pDX, IDC_DAMPLUS, m_damplus);
	DDV_MinMaxInt(pDX, m_damplus, 0, iMaxdamplus);
	DDX_Text(pDX, IDC_DAMROLL, m_damroll);
	DDV_MinMaxInt(pDX, m_damroll, 0, iMaxdamroll);
	DDX_Text(pDX, IDC_DAMSIZEDICE, m_damsizedice);
	DDV_MinMaxInt(pDX, m_damsizedice, 0, iMaxdamsizedice);

  // hits
	DDX_Text(pDX, IDC_HITNODICE, m_hitnodice);
	DDV_MinMaxInt(pDX, m_hitnodice, 0, iMaxhitnodice);
	DDX_Text(pDX, IDC_HITPLUS, m_hitplus);
	DDV_MinMaxInt(pDX, m_hitplus, 0, iMaxhitplus);
	DDX_Text(pDX, IDC_HITROLL, m_hitroll);
	DDV_MinMaxInt(pDX, m_hitroll, 0, iMaxhitroll);
	DDX_Text(pDX, IDC_HITSIZEDICE, m_hitsizedice);
	DDV_MinMaxInt(pDX, m_hitsizedice, 0, iMaxhitsizedice);
	DDX_Text(pDX, IDC_NUMATTACKS, m_numattacks);
	DDV_MinMaxInt(pDX, m_numattacks, 0, iMaxNumattacks);

  // mana  - for ROM
  if (m_mob->m_pDoc->m_AreaType == eROM)
    {
	  DDX_Text(pDX, IDC_MANANODICE, m_mananodice);
	  DDV_MinMaxInt(pDX, m_mananodice, 0, iMaxmananodice);
	  DDX_Text(pDX, IDC_MANASIZEDICE, m_manasizedice);
	  DDV_MinMaxInt(pDX, m_manasizedice, 0, iMaxmanasizedice);
	  DDX_Text(pDX, IDC_MANAPLUS, m_manaplusdice);
	  DDV_MinMaxInt(pDX, m_manaplusdice, 0, iMaxmanaplus);
    }

  // saving throws   - SMAUG
  if (m_mob->m_pDoc->m_AreaType == eSMAUG)
    {
	  DDX_Text(pDX, IDC_SAVING_BREATH, m_saving_breath);
	  DDV_MinMaxInt(pDX, m_saving_breath, iMinSavingthrow, iMaxSavingthrow);
	  DDX_Text(pDX, IDC_SAVING_POISON_DEATH, m_saving_poison_death);
	  DDV_MinMaxInt(pDX, m_saving_poison_death, iMinSavingthrow, iMaxSavingthrow);
	  DDX_Text(pDX, IDC_SAVING_WAND, m_saving_wand);
	  DDV_MinMaxInt(pDX, m_saving_wand, iMinSavingthrow, iMaxSavingthrow);
	  DDX_Text(pDX, IDC_SAVING_SPELL_STAFF, m_saving_spell_staff);
	  DDV_MinMaxInt(pDX, m_saving_spell_staff, iMinSavingthrow, iMaxSavingthrow);
	  DDX_Text(pDX, IDC_SAVING_PARA_PETRI, m_saving_para_petri);
	  DDV_MinMaxInt(pDX, m_saving_para_petri, iMinSavingthrow, iMaxSavingthrow);
    }

  if (!pDX->m_bSaveAndValidate)
    {
    LoadComboBoxList (m_ctlRace,        MobRaceList,     m_mob->race);
    LoadComboBoxList (m_ctlClass,       MobClassList,    m_mob->mobclass);
    LoadComboBoxList (m_ctlPosition,    MobPositionList, m_mob->position);
    LoadComboBoxList (m_ctlDefposition, MobPositionList, m_mob->defposition);
    LoadComboBoxList (m_ctlSize, MobSizeList, m_mob->size);
    LoadComboBoxList (m_ctlDamageType, ObjectAttackList, m_mob->dam_type);

    if (m_mob->m_pDoc->m_AreaType != eROM)
      {
      m_ctlManaSizeDice.EnableWindow (FALSE);
      m_ctlManaPlusDice.EnableWindow (FALSE);
      m_ctlManaNoDice.EnableWindow (FALSE);
      m_ctlSize.EnableWindow (FALSE);
      m_ctlDamageTypeLabel.ShowWindow (SW_HIDE);
      m_ctlDamageType.ShowWindow (SW_HIDE);
      }   // end of not ROM

    if (m_mob->m_pDoc->m_AreaType != eSMAUG)
      {
      m_ctlMobthac0.EnableWindow (FALSE);
      m_ctlLck.EnableWindow (FALSE);
      m_ctlCha.EnableWindow (FALSE);
      m_ctlCon.EnableWindow (FALSE);
      m_ctlDex.EnableWindow (FALSE);
      m_ctlWis.EnableWindow (FALSE);
      m_ctlInt.EnableWindow (FALSE);
      m_ctlStr.EnableWindow (FALSE);
      m_ctlNumAttacks.EnableWindow (FALSE);
      m_ctlSavingPoison.EnableWindow (FALSE);
      m_ctlSavingWand.EnableWindow (FALSE);
      m_ctlSavingPara.EnableWindow (FALSE);
      m_ctlSavingBreath.EnableWindow (FALSE);
      m_ctlSavingSpell.EnableWindow (FALSE);
      }   // end of not SMAUG

    }

  if (pDX->m_bSaveAndValidate)
    {
	  UNLOAD_VALUE (m_alignment, alignment);
	  UNLOAD_VALUE (m_cha, perm_cha);
	  UNLOAD_VALUE (m_con, perm_con);
	  UNLOAD_VALUE (m_damnodice, damnodice);
	  UNLOAD_VALUE (m_damplus, damplus);
	  UNLOAD_VALUE (m_damroll, damroll);
	  UNLOAD_VALUE (m_damsizedice, damsizedice);
	  UNLOAD_VALUE (m_dex, perm_dex);
	  UNLOAD_VALUE (m_gold, gold);
	  UNLOAD_VALUE (m_hitnodice, hitnodice);
	  UNLOAD_VALUE (m_hitplus, hitplus);
	  UNLOAD_VALUE (m_hitroll, hitroll);
	  UNLOAD_VALUE (m_hitsizedice, hitsizedice);
	  UNLOAD_VALUE (m_int, perm_int);
	  UNLOAD_VALUE (m_lck, perm_lck);
	  UNLOAD_VALUE (m_mobthac0, mobthac0);
	  UNLOAD_VALUE (m_numattacks, numattacks);
	  UNLOAD_VALUE (m_saving_breath, saving_breath);
	  UNLOAD_VALUE (m_saving_para_petri, saving_para_petri);
	  UNLOAD_VALUE (m_saving_poison_death, saving_poison_death);
	  UNLOAD_VALUE (m_saving_spell_staff, saving_spell_staff);
	  UNLOAD_VALUE (m_saving_wand, saving_wand);
	  UNLOAD_VALUE (m_str, perm_str);
	  UNLOAD_VALUE (m_wis, perm_wis);

    if (m_mob->m_pDoc->m_AreaType == eSMAUG)
      {
  	  UNLOAD_VALUE (m_ac, ac);
  	  UNLOAD_VALUE (m_exp, exp);
  	  UNLOAD_VALUE (m_height, height);
  	  UNLOAD_VALUE (m_weight, weight);
      } // end of SMAUG mob
    else if (m_mob->m_pDoc->m_AreaType == eROM)
      {
  	  UNLOAD_VALUE (m_ac, ac_pierce);
  	  UNLOAD_VALUE (m_exp, ac_bash);
  	  UNLOAD_VALUE (m_height, ac_slash);
  	  UNLOAD_VALUE (m_weight, ac_exotic);
      } // end of ROM mob

    int i;
    if (UnloadComboBox (m_ctlClass, i))
  	  UNLOAD_VALUE (i, mobclass);
    if (UnloadComboBox (m_ctlRace, i))
  	  UNLOAD_VALUE (i, race);
    if (UnloadComboBox (m_ctlPosition, i))
  	  UNLOAD_VALUE (i, position);
    if (UnloadComboBox (m_ctlDefposition, i))
  	  UNLOAD_VALUE (i, defposition);
    if (UnloadComboBox (m_ctlSize, i))
	    UNLOAD_VALUE (i, size);
    if (UnloadComboBox (m_ctlDamageType, i))
	    UNLOAD_VALUE (i, dam_type);

     if (bChanged)
       m_mob->m_pDoc->SetModifiedFlag ();
    } // of saving


}


BEGIN_MESSAGE_MAP(CMobileStatsPage, CDialog)
	//{{AFX_MSG_MAP(CMobileStatsPage)
	ON_BN_CLICKED(IDC_SUGGEST_HIT, OnSuggestHit)
	ON_BN_CLICKED(IDC_SUGGEST_AC, OnSuggestAc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMobileStatsPage message handlers

void CMobileStatsPage::OnSuggestHit() 
{
 int hit		= m_mob->level * 8 + number_range(
					        m_mob->level * m_mob->level / 4,
					        m_mob->level * m_mob->level );
	

  m_ctlHitNoDice.SetWindowText (CFormat ("%i", hit));
  m_ctlHitSizeDice.SetWindowText ("1");
  m_ctlHitPlus.SetWindowText ("0");

}


void CMobileStatsPage::OnSuggestAc() 
{
int AC = interpolate( m_mob->level, 100, -100 );

  m_ctlArmourClass.SetWindowText (CFormat ("%i", AC));
}
