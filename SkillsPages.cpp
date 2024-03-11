/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// SkillsPages.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "AreaEditor.h"
#include "SkillsSheet.h"
#include "SkillsPages.h"
#include "defaults.h"
#include "EditAffectDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CSkillsPage1, CPropertyPage)
IMPLEMENT_DYNCREATE(CSkillsPage2, CPropertyPage)
IMPLEMENT_DYNCREATE(CSkillsPage3, CPropertyPage)
IMPLEMENT_DYNCREATE(CSkillsPage4, CPropertyPage)

#undef LOAD_VALUE
#define LOAD_VALUE(field, value)  \
  field = m_skill->value

#undef UNLOAD_VALUE
#define UNLOAD_VALUE(field, value)  \
  do {    \
    if (field != m_skill->value) bChanged = true; \
    m_skill->value = field;   \
    } while (false)


#undef LOAD_FLAG
#define LOAD_FLAG(field, flag)  \
  field = IS_SET (m_skill->flags, flag);

#undef UNLOAD_FLAG
#define UNLOAD_FLAG(field, flag)  \
  if (field != IS_SET (m_skill->flags, flag)) bChanged = true; \
  if (field)                      \
    SET_BIT (m_skill->flags, flag);\
  else                            \
    REMOVE_BIT (m_skill->flags, flag)

extern char * spell_damage[8];
extern char * spell_action[8];
extern char * spell_power[4];
extern char * spell_class[8];

/////////////////////////////////////////////////////////////////////////////
// CSkillsPage1 property page

CSkillsPage1::CSkillsPage1() : CPropertyPage(CSkillsPage1::IDD)
{
	//{{AFX_DATA_INIT(CSkillsPage1)
	m_name = _T("");
	m_slot = 0;
	m_guild = 0;
	m_min_level = 0;
	m_min_mana = 0;
	m_minimum_position = 0;
	m_target = 0;
	m_beats = 0;
	m_strFlags = _T("");
	m_spell_skill_fun = _T("");
	m_range = 0;
	m_info = 0;
	//}}AFX_DATA_INIT

  m_skill = NULL;

}

CSkillsPage1::~CSkillsPage1()
{
}

void CSkillsPage1::DoDataExchange(CDataExchange* pDX)
{
bool bChanged = false;

  if (!pDX->m_bSaveAndValidate && m_skill)
    {
    LOAD_VALUE (m_name, name);
    LOAD_VALUE (m_spell_skill_fun,  spell_skill_fun);
    LOAD_VALUE (m_slot,  slot);
    LOAD_VALUE (m_guild, guild);
    LOAD_VALUE (m_min_level,  min_level);
    LOAD_VALUE (m_min_mana,  min_mana);
    LOAD_VALUE (m_minimum_position, minimum_position);
    LOAD_VALUE (m_target,  target);
    LOAD_VALUE (m_beats,  beats);
    LOAD_VALUE (m_range,  range);
    LOAD_VALUE (m_info,  info);
    m_strFlags = convert_spell_flags (m_skill->flags >> 11);

    }

  CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSkillsPage1)
	DDX_Control(pDX, IDC_FUNCTION, m_ctlFunction);
	DDX_Control(pDX, IDC_POWER, m_ctlPower);
	DDX_Control(pDX, IDC_DAMAGE, m_ctlDamage);
	DDX_Control(pDX, IDC_CLASS, m_ctlClass);
	DDX_Control(pDX, IDC_ACTION, m_ctlAction);
	DDX_Control(pDX, IDC_TYPE, m_ctlType);
	DDX_Text(pDX, IDC_NAME, m_name);
	DDX_Text(pDX, IDC_SLOT, m_slot);
	DDX_Text(pDX, IDC_GUILD, m_guild);
	DDX_Text(pDX, IDC_MIN_MANA, m_min_mana);
	DDX_Text(pDX, IDC_MINIMUM_POSITION, m_minimum_position);
	DDX_Text(pDX, IDC_TARGET, m_target);
	DDX_Text(pDX, IDC_BEATS, m_beats);
	DDX_Text(pDX, IDC_FLAGS_SUMMARY, m_strFlags);
	DDX_CBString(pDX, IDC_FUNCTION, m_spell_skill_fun);
	DDX_Text(pDX, IDC_RANGE, m_range);
	DDX_Text(pDX, IDC_INFO, m_info);
	//}}AFX_DATA_MAP
  DDX_Text(pDX, IDC_MIN_LEVEL, m_min_level);
	DDV_MinMaxInt(pDX, m_min_level, 0, iMaxLevel);

  if (!pDX->m_bSaveAndValidate)
    {

    LoadComboBoxList (m_ctlType, SkillTypeList, m_skill->type);
    LoadComboBox (m_ctlAction, spell_action, NUMITEMS (spell_action), SPELL_ACTION (m_skill));
    LoadComboBox (m_ctlClass, spell_class, NUMITEMS (spell_class), SPELL_CLASS (m_skill));
    LoadComboBox (m_ctlDamage, spell_damage, NUMITEMS (spell_damage), SPELL_DAMAGE (m_skill));
    LoadComboBox (m_ctlPower, spell_power, NUMITEMS (spell_power), SPELL_POWER (m_skill));

    OnSelchangeType (); // load function (code) combo box
    }

  if (pDX->m_bSaveAndValidate && m_skill)
    {

    m_name.TrimLeft ();
    m_name.TrimRight ();

    if (m_name.IsEmpty ())
      {
      ::AfxMessageBox ("Skill/spell must have a name");
      DDX_Text(pDX, IDC_NAME, m_name);
      pDX->Fail();
      }

    // get type here so we know whether it needs a function
    int i;
    if (UnloadComboBox (m_ctlType, i))
    	  UNLOAD_VALUE (i, type);

    if (i == SKILL_SPELL || i == SKILL_SKILL)
      {

      m_spell_skill_fun.TrimLeft ();
      m_spell_skill_fun.TrimRight ();

      if (m_spell_skill_fun.IsEmpty ())
        {
        ::AfxMessageBox ("Please choose a function before proceeding",
                          MB_ICONSTOP);
        pDX->Fail();
        }   // end of no function chosen
      }    // end of spell or skill

    // look for duplicates

    if (((CSkillsSheet *) GetParent ())->m_bAdd)
      for (POSITION skillPos = App.m_SkillList.GetHeadPosition (); skillPos; )
        {
        CSkill * skill = App.m_SkillList.GetNext (skillPos);

        if (skill->name.CompareNoCase (m_name) == 0)
          {
          ::AfxMessageBox (CFormat ("There is already a skill called \"%s\"",
                          (LPCTSTR) m_name));
          DDX_Text(pDX, IDC_NAME, m_name);
          pDX->Fail();
          }
        }


    CheckForTilde (pDX, IDC_NAME, m_name);

    UNLOAD_VALUE (m_name, name);
    UNLOAD_VALUE (m_spell_skill_fun,  spell_skill_fun);
    UNLOAD_VALUE (m_slot,  slot);
    UNLOAD_VALUE (m_guild, guild);
    UNLOAD_VALUE (m_min_level,  min_level);
    UNLOAD_VALUE (m_min_mana,  min_mana);
    UNLOAD_VALUE (m_minimum_position, minimum_position);
    UNLOAD_VALUE (m_target,  target);
    UNLOAD_VALUE (m_beats,  beats);
    UNLOAD_VALUE (m_range,  range);
    UNLOAD_VALUE (m_info,  info);


    if (UnloadComboBox (m_ctlAction, i))
      {
      if (i != SPELL_ACTION (m_skill))
        bChanged = true;
      SET_SACT (m_skill, i);
      }
    if (UnloadComboBox (m_ctlClass, i))
      {
      if (i != SPELL_CLASS (m_skill))
        bChanged = true;
      SET_SCLA (m_skill, i);
      }
    if (UnloadComboBox (m_ctlDamage, i))
      {
      if (i != SPELL_DAMAGE (m_skill))
        bChanged = true;
      SET_SDAM (m_skill, i);
      }
    if (UnloadComboBox (m_ctlPower, i))
      {
      if (i != SPELL_POWER (m_skill))
        bChanged = true;
      SET_SPOW (m_skill, i);
      }

    if (bChanged)
      App.m_bSkillsDirty = true;

    }

}


BEGIN_MESSAGE_MAP(CSkillsPage1, CPropertyPage)
	//{{AFX_MSG_MAP(CSkillsPage1)
	ON_CBN_SELCHANGE(IDC_TYPE, OnSelchangeType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CSkillsPage1::OnSelchangeType() 
{
  int i;
  if (UnloadComboBox (m_ctlType, i))
    {
    if (i == SKILL_SPELL)
      {
      m_ctlFunction.EnableWindow (true);
      LoadComboBoxList (m_ctlFunction, SpellNameList, -1);
      m_ctlFunction.SelectString(-1, m_spell_skill_fun);
      }
    else
      if (i == SKILL_SKILL)
      {
      m_ctlFunction.EnableWindow (true);
      LoadComboBoxList (m_ctlFunction, SMAUGSkillNameList, -1);
      m_ctlFunction.SelectString(-1, m_spell_skill_fun);
      }
    else
      m_ctlFunction.EnableWindow (false);

    }
  else
    m_ctlFunction.EnableWindow (false);

}

/////////////////////////////////////////////////////////////////////////////
// CSkillsPage2 property page

CSkillsPage2::CSkillsPage2() : CPropertyPage(CSkillsPage2::IDD)
{
	//{{AFX_DATA_INIT(CSkillsPage2)
	m_noun_damage = _T("");
	m_hit_char = _T("");
	m_hit_room = _T("");
	m_hit_vict = _T("");
	m_msg_off = _T("");
	m_die_char = _T("");
	m_die_room = _T("");
	m_die_vict = _T("");
	m_imm_char = _T("");
	m_imm_room = _T("");
	m_imm_vict = _T("");
	m_miss_char = _T("");
	m_miss_room = _T("");
	m_miss_vict = _T("");
	m_hit_dest = _T("");
	//}}AFX_DATA_INIT

  m_skill = NULL;
}

CSkillsPage2::~CSkillsPage2()
{
}


void CSkillsPage2::DoDataExchange(CDataExchange* pDX)
{
bool bChanged = false;

  if (!pDX->m_bSaveAndValidate && m_skill)
    {
    LOAD_VALUE (m_noun_damage, noun_damage);
    LOAD_VALUE (m_hit_char,  hit_char);
    LOAD_VALUE (m_hit_room,  hit_room);
    LOAD_VALUE (m_hit_vict,  hit_vict);
    LOAD_VALUE (m_hit_dest,  hit_dest);
    LOAD_VALUE (m_msg_off,   msg_off);
    LOAD_VALUE (m_die_char,  die_char);
    LOAD_VALUE (m_die_room,  die_room);
    LOAD_VALUE (m_die_vict,  die_vict);
    LOAD_VALUE (m_imm_char,  imm_char);
    LOAD_VALUE (m_imm_room,  imm_room);
    LOAD_VALUE (m_imm_vict,  imm_vict);
    LOAD_VALUE (m_miss_char,  miss_char);
    LOAD_VALUE (m_miss_room,  miss_room);
    LOAD_VALUE (m_miss_vict,  miss_vict);
    }

	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSkillsPage2)
	DDX_Text(pDX, IDC_DAMAGE, m_noun_damage);
	DDX_Text(pDX, IDC_HIT_CHAR, m_hit_char);
	DDX_Text(pDX, IDC_HIT_ROOM, m_hit_room);
	DDX_Text(pDX, IDC_HIT_VICT, m_hit_vict);
	DDX_Text(pDX, IDC_WEAR_OFF, m_msg_off);
	DDX_Text(pDX, IDC_DIE_CHAR, m_die_char);
	DDX_Text(pDX, IDC_DIE_ROOM, m_die_room);
	DDX_Text(pDX, IDC_DIE_VICT, m_die_vict);
	DDX_Text(pDX, IDC_IMM_CHAR, m_imm_char);
	DDX_Text(pDX, IDC_IMM_ROOM, m_imm_room);
	DDX_Text(pDX, IDC_IMM_VICT, m_imm_vict);
	DDX_Text(pDX, IDC_MISS_CHAR, m_miss_char);
	DDX_Text(pDX, IDC_MISS_ROOM, m_miss_room);
	DDX_Text(pDX, IDC_MISS_VICT, m_miss_vict);
	DDX_Text(pDX, IDC_HIT_DEST, m_hit_dest);
	//}}AFX_DATA_MAP

  if (pDX->m_bSaveAndValidate && m_skill)
    {

	  CheckForTilde (pDX, IDC_DAMAGE, m_noun_damage);
	  CheckForTilde (pDX, IDC_HIT_CHAR, m_hit_char);
	  CheckForTilde (pDX, IDC_HIT_ROOM, m_hit_room);
	  CheckForTilde (pDX, IDC_HIT_VICT, m_hit_vict);
	  CheckForTilde (pDX, IDC_WEAR_OFF, m_msg_off);
	  CheckForTilde (pDX, IDC_DIE_CHAR, m_die_char);
	  CheckForTilde (pDX, IDC_DIE_ROOM, m_die_room);
	  CheckForTilde (pDX, IDC_DIE_VICT, m_die_vict);
	  CheckForTilde (pDX, IDC_IMM_CHAR, m_imm_char);
	  CheckForTilde (pDX, IDC_IMM_ROOM, m_imm_room);
	  CheckForTilde (pDX, IDC_IMM_VICT, m_imm_vict);
	  CheckForTilde (pDX, IDC_MISS_CHAR, m_miss_char);
	  CheckForTilde (pDX, IDC_MISS_ROOM, m_miss_room);
	  CheckForTilde (pDX, IDC_MISS_VICT, m_miss_vict);
	  CheckForTilde (pDX, IDC_HIT_DEST, m_hit_dest);

    UNLOAD_VALUE (m_noun_damage, noun_damage);
    UNLOAD_VALUE (m_hit_char,  hit_char);
    UNLOAD_VALUE (m_hit_room,  hit_room);
    UNLOAD_VALUE (m_hit_vict,  hit_vict);
    UNLOAD_VALUE (m_hit_dest,  hit_dest);
    UNLOAD_VALUE (m_msg_off,   msg_off);
    UNLOAD_VALUE (m_die_char,  die_char);
    UNLOAD_VALUE (m_die_room,  die_room);
    UNLOAD_VALUE (m_die_vict,  die_vict);
    UNLOAD_VALUE (m_imm_char,  imm_char);
    UNLOAD_VALUE (m_imm_room,  imm_room);
    UNLOAD_VALUE (m_imm_vict,  imm_vict);
    UNLOAD_VALUE (m_miss_char,  miss_char);
    UNLOAD_VALUE (m_miss_room,  miss_room);
    UNLOAD_VALUE (m_miss_vict,  miss_vict);
    if (bChanged)
      App.m_bSkillsDirty = true;
    }

}


BEGIN_MESSAGE_MAP(CSkillsPage2, CPropertyPage)
	//{{AFX_MSG_MAP(CSkillsPage2)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSkillsPage3 property page


typedef struct 
  {  
  int        sortkey;             // which key to use
  int        reverse;             // reverse sort or not
  } t_sort_param;

static int CALLBACK CompareFunc ( LPARAM lParam1, 
                           LPARAM lParam2,
                           LPARAM lParamSort)
  { 

 ASSERT (lParamSort != NULL);

t_sort_param * psort_param = (t_sort_param *) lParamSort;

CSkillAffect * pAffect1 = (CSkillAffect *) lParam1;
CSkillAffect * pAffect2 = (CSkillAffect *) lParam2;

 ASSERT (pAffect1 != NULL);
 ASSERT (pAffect2 != NULL);

int iResult = 0;

CString strLocation1 = ObjectAffectList.ReturnName (pAffect1->location % REVERSE_APPLY, false);
if ( pAffect1->location >= REVERSE_APPLY )
	strLocation1 += " (caster)";
CString strLocation2 = ObjectAffectList.ReturnName (pAffect2->location % REVERSE_APPLY, false);
if ( pAffect2->location >= REVERSE_APPLY )
	strLocation2 += " (caster)";

   switch (psort_param->sortkey)
     {
     case 0:
        iResult = strLocation1.CompareNoCase (strLocation2);
        break;

     case 1:
        iResult = pAffect1->modifier.CompareNoCase (pAffect2->modifier);
        break;

     case 2:
        iResult = pAffect1->duration.CompareNoCase (pAffect2->duration);
        break;

     case 3:
        iResult = stricmp (convert_affectflag (pAffect1->bitvector),
                          convert_affectflag (pAffect2->bitvector));
        break;

     }  // end of switch

// if reverse sort wanted, reverse sense of result

  if (psort_param->reverse)
    iResult *= -1;

  return iResult;

  } // end of CompareFunc

CSkillsPage3::CSkillsPage3() : CPropertyPage(CSkillsPage3::IDD)
{
	//{{AFX_DATA_INIT(CSkillsPage3)
	m_difficulty = 0;
	m_participants = 0;
	m_saves = 0;
	m_value = 0;
	m_dice = _T("");
	//}}AFX_DATA_INIT

  m_last_col = 0;
  m_reverse = FALSE;

}

CSkillsPage3::~CSkillsPage3()
{
}

void CSkillsPage3::DoDataExchange(CDataExchange* pDX)
{
bool bChanged = false;

  if (!pDX->m_bSaveAndValidate && m_skill)
    {
	  LOAD_VALUE (m_dice,            dice); 
	  LOAD_VALUE (m_difficulty, difficulty); 
	  LOAD_VALUE (m_participants, participants);
	  LOAD_VALUE (m_saves, saves);
	  LOAD_VALUE (m_value, value);
    }

	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSkillsPage3)
	DDX_Control(pDX, IDC_AFFECTS_LIST, m_ctlAffectsList);
	DDX_Text(pDX, IDC_DIFFICULTY, m_difficulty);
	DDX_Text(pDX, IDC_PARTICIPANTS, m_participants);
	DDX_Text(pDX, IDC_SAVES, m_saves);
	DDX_Text(pDX, IDC_VALUE, m_value);
	DDX_Text(pDX, IDC_DICE, m_dice);
	//}}AFX_DATA_MAP

  if (pDX->m_bSaveAndValidate && m_skill)
    {
	  CheckForTilde (pDX, IDC_DICE, m_dice);

    UNLOAD_VALUE (m_dice,            dice); 
	  UNLOAD_VALUE (m_difficulty, difficulty); 
	  UNLOAD_VALUE (m_participants, participants);
	  UNLOAD_VALUE (m_saves, saves);
	  UNLOAD_VALUE (m_value, value);
    if (bChanged)
      App.m_bSkillsDirty = true;
    }

}


BEGIN_MESSAGE_MAP(CSkillsPage3, CPropertyPage)
	//{{AFX_MSG_MAP(CSkillsPage3)
	ON_NOTIFY(NM_DBLCLK, IDC_AFFECTS_LIST, OnDblclkAffectsList)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_AFFECTS_LIST, OnColumnclickAffectsList)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_EDIT, OnEdit)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	//}}AFX_MSG_MAP
  ON_MESSAGE(WM_KICKIDLE, OnKickIdle)
  ON_UPDATE_COMMAND_UI(IDC_EDIT, OnUpdateNeedSelection)
  ON_UPDATE_COMMAND_UI(IDC_DELETE, OnUpdateNeedSelection)
END_MESSAGE_MAP()

void CSkillsPage3::OnDblclkAffectsList(NMHDR* pNMHDR, LRESULT* pResult) 
{
  OnEdit ();
	
	*pResult = 0;
}

void CSkillsPage3::OnColumnclickAffectsList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

  int col = pNMListView->iSubItem;

  t_sort_param sort_param;

  if (col == m_last_col)
    m_reverse = !m_reverse;
  else
    m_reverse = FALSE;

  m_last_col = col;

  sort_param.sortkey = m_last_col;
  sort_param.reverse = m_reverse;

  m_ctlAffectsList.SortItems (CompareFunc, (LPARAM) &sort_param); 

	*pResult = 0;
}


#undef LOAD_AFFECT_VALUE
#define LOAD_AFFECT_VALUE(field, value)  \
  field = affect->value

#undef UNLOAD_AFFECT_VALUE
#define UNLOAD_AFFECT_VALUE(field, value)  \
  do {    \
    if (field != affect->value) bChanged = true; \
    affect->value = field;   \
    } while (false)

void CSkillsPage3::OnAdd() 
{

  CEditAffectDlg dlg;
  bool bChanged = false;

  dlg.m_strDuration = "0";
  dlg.m_strModifier = "0";

  if (dlg.DoModal() != IDOK)
    return;

  CSkillAffect * affect = new CSkillAffect;

  UNLOAD_AFFECT_VALUE (dlg.m_strDuration, duration);
  UNLOAD_AFFECT_VALUE (dlg.m_iFlags, bitvector);
  UNLOAD_AFFECT_VALUE (dlg.m_strModifier, modifier);
  UNLOAD_AFFECT_VALUE (dlg.m_iLocation, location);

  m_skill->affects.AddTail (affect);

  App.m_bSkillsDirty = true;

  RedrawList ();   
	
}

void CSkillsPage3::OnEdit() 
{

  for (int nIndex = -1;
      (nIndex = m_ctlAffectsList.GetNextItem(nIndex, LVNI_SELECTED)) != -1; )
   {
    bool bChanged = false;

    CSkillAffect * affect = (CSkillAffect *) m_ctlAffectsList.GetItemData (nIndex);

    CEditAffectDlg dlg;

    LOAD_AFFECT_VALUE (dlg.m_strDuration, duration);
    LOAD_AFFECT_VALUE (dlg.m_iFlags, bitvector);
    LOAD_AFFECT_VALUE (dlg.m_strModifier, modifier);
    LOAD_AFFECT_VALUE (dlg.m_iLocation, location);
    
    if (dlg.DoModal() != IDOK)
      continue;

    UNLOAD_AFFECT_VALUE (dlg.m_strDuration, duration);
    UNLOAD_AFFECT_VALUE (dlg.m_iFlags, bitvector);
    UNLOAD_AFFECT_VALUE (dlg.m_strModifier, modifier);
    UNLOAD_AFFECT_VALUE (dlg.m_iLocation, location);
	
    if (bChanged)
      App.m_bSkillsDirty = true;

    }

  RedrawList ();    // in case they renamed it

}

void CSkillsPage3::OnDelete() 
{
  for (int nIndex = -1;
      (nIndex = m_ctlAffectsList.GetNextItem(nIndex, LVNI_SELECTED)) != -1; )
   {

    CSkillAffect * affect = (CSkillAffect *) m_ctlAffectsList.GetItemData (nIndex);

// ask if they want to delete it

    if (::AfxMessageBox ("OK to delete the select affect?", 
                      MB_ICONQUESTION | MB_YESNO) != IDYES)
                      continue;

     m_skill->affects.RemoveAt (m_skill->affects.Find (affect, NULL));
     App.m_bSkillsDirty = true;

    }

  RedrawList ();    // in case they deleted it
	
}

BOOL CSkillsPage3::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	
// set list control to display whole row when selected

  m_ctlAffectsList.SendMessage (LVM_SETEXTENDEDLISTVIEWSTYLE, 0, 
                              m_ctlAffectsList.SendMessage (LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0) 
                              | LVS_EX_FULLROWSELECT);
  
  m_ctlAffectsList.InsertColumn(0, "Affects", LVCFMT_LEFT, 90);
  m_ctlAffectsList.InsertColumn(1, "Modifier", LVCFMT_LEFT, 60);
  m_ctlAffectsList.InsertColumn(2, "Duration", LVCFMT_LEFT, 70);
  m_ctlAffectsList.InsertColumn(3, "Flags", LVCFMT_LEFT, 100);
	RedrawList ();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSkillsPage3::RedrawList (void) 
  {
int nItem = 0;

POSITION affectPos;
CSkillAffect * affect;

  m_ctlAffectsList.DeleteAllItems ();

  for (affectPos = m_skill->affects.GetHeadPosition (); affectPos; )
    {
    affect = m_skill->affects.GetNext (affectPos);

    CString strLocation = ObjectAffectList.ReturnName (affect->location % REVERSE_APPLY, false);

	  if ( affect->location >= REVERSE_APPLY )
		  strLocation += " (caster)";

    CString strModifier;

    // if the affect is to change resistant/immune/susceptible
    // then the modifier is in fact a bitmap (in a string)

    switch (affect->location % REVERSE_APPLY)
      {
      case APPLY_RESISTANT:
      case APPLY_IMMUNE:
      case APPLY_SUSCEPTIBLE:
        strModifier = convert_risflag (atoi (affect->modifier));
        break;

      default: 
        strModifier = affect->modifier;
        break;

      } // end of switch

		m_ctlAffectsList.InsertItem (nItem, strLocation);     
		m_ctlAffectsList.SetItemText(nItem, 1, strModifier);
		m_ctlAffectsList.SetItemText(nItem, 2, affect->duration);
		m_ctlAffectsList.SetItemText(nItem, 3, convert_affectflag (affect->bitvector));
    m_ctlAffectsList.SetItemData (nItem, (DWORD) affect);

    nItem++;

    }

  t_sort_param sort_param;

  sort_param.sortkey = m_last_col;
  sort_param.reverse = m_reverse;

  m_ctlAffectsList.SortItems (CompareFunc, (LPARAM) &sort_param); 

  } // end of CSkillsPage3::RedrawList


LRESULT CSkillsPage3::OnKickIdle(WPARAM, LPARAM)
  {
  UpdateDialogControls (AfxGetApp()->m_pMainWnd, false);
  return 0;
  } // end of CSkillsPage3::OnKickIdle


void CSkillsPage3::OnUpdateNeedSelection(CCmdUI* pCmdUI)
  {
  pCmdUI->Enable (m_ctlAffectsList.GetFirstSelectedItemPosition () != NULL);
  } // end of CSkillsPage3::OnUpdateNeedSelection

/////////////////////////////////////////////////////////////////////////////
// CSkillsPage4 property page

CSkillsPage4::CSkillsPage4() : CPropertyPage(CSkillsPage4::IDD)
{
	//{{AFX_DATA_INIT(CSkillsPage4)
	m_accumulative = FALSE;
	m_air = FALSE;
	m_area = FALSE;
	m_astral = FALSE;
	m_character = FALSE;
	m_distant = FALSE;
	m_earth = FALSE;
	m_groupspell = FALSE;
	m_nobrew = FALSE;
	m_noscribe = FALSE;
	m_object = FALSE;
	m_pksensitive = FALSE;
	m_recastable = FALSE;
	m_reverse = FALSE;
	m_save_half_damage = FALSE;
	m_save_negates = FALSE;
	m_secretskill = FALSE;
	m_stoponfail = FALSE;
	m_water = FALSE;
	//}}AFX_DATA_INIT
}

CSkillsPage4::~CSkillsPage4()
{
}

void CSkillsPage4::DoDataExchange(CDataExchange* pDX)
{
bool bChanged = false;

  if (!pDX->m_bSaveAndValidate && m_skill)
    {
	  LOAD_FLAG (m_accumulative , SF_ACCUMULATIVE);
	  LOAD_FLAG (m_air , SF_AIR);
	  LOAD_FLAG (m_area , SF_AREA);
	  LOAD_FLAG (m_astral , SF_ASTRAL);
	  LOAD_FLAG (m_character , SF_CHARACTER);
	  LOAD_FLAG (m_distant , SF_DISTANT);
	  LOAD_FLAG (m_earth , SF_EARTH);
	  LOAD_FLAG (m_groupspell , SF_GROUPSPELL);
	  LOAD_FLAG (m_nobrew , SF_NOBREW);
	  LOAD_FLAG (m_noscribe , SF_NOSCRIBE);
	  LOAD_FLAG (m_object , SF_OBJECT);
	  LOAD_FLAG (m_pksensitive , SF_PKSENSITIVE);
	  LOAD_FLAG (m_recastable , SF_RECASTABLE);
	  LOAD_FLAG (m_reverse , SF_REVERSE);
	  LOAD_FLAG (m_save_half_damage, SF_SAVE_HALF_DAMAGE);
	  LOAD_FLAG (m_save_negates , SF_SAVE_NEGATES);
	  LOAD_FLAG (m_secretskill , SF_SECRETSKILL);
	  LOAD_FLAG (m_stoponfail , SF_STOPONFAIL);
	  LOAD_FLAG (m_water , SF_WATER);
    }

	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSkillsPage4)
	DDX_Check(pDX, IDC_ACCUMULATIVE, m_accumulative);
	DDX_Check(pDX, IDC_AIR, m_air);
	DDX_Check(pDX, IDC_AREA, m_area);
	DDX_Check(pDX, IDC_ASTRAL, m_astral);
	DDX_Check(pDX, IDC_CHARACTER, m_character);
	DDX_Check(pDX, IDC_DISTANT, m_distant);
	DDX_Check(pDX, IDC_EARTH, m_earth);
	DDX_Check(pDX, IDC_GROUPSPELL, m_groupspell);
	DDX_Check(pDX, IDC_NOBREW, m_nobrew);
	DDX_Check(pDX, IDC_NOSCRIBE, m_noscribe);
	DDX_Check(pDX, IDC_OBJECT, m_object);
	DDX_Check(pDX, IDC_PKSENSITIVE, m_pksensitive);
	DDX_Check(pDX, IDC_RECASTABLE, m_recastable);
	DDX_Check(pDX, IDC_REVERSE, m_reverse);
	DDX_Check(pDX, IDC_SAVE_HALF_DAMAGE, m_save_half_damage);
	DDX_Check(pDX, IDC_SAVE_NEGATES, m_save_negates);
	DDX_Check(pDX, IDC_SECRETSKILL, m_secretskill);
	DDX_Check(pDX, IDC_STOPONFAIL, m_stoponfail);
	DDX_Check(pDX, IDC_WATER, m_water);
	//}}AFX_DATA_MAP

  if (pDX->m_bSaveAndValidate && m_skill)
    {
	  UNLOAD_FLAG (m_accumulative , SF_ACCUMULATIVE);
	  UNLOAD_FLAG (m_air , SF_AIR);
	  UNLOAD_FLAG (m_area , SF_AREA);
	  UNLOAD_FLAG (m_astral , SF_ASTRAL);
	  UNLOAD_FLAG (m_character , SF_CHARACTER);
	  UNLOAD_FLAG (m_distant , SF_DISTANT);
	  UNLOAD_FLAG (m_earth , SF_EARTH);
	  UNLOAD_FLAG (m_groupspell , SF_GROUPSPELL);
	  UNLOAD_FLAG (m_nobrew , SF_NOBREW);
	  UNLOAD_FLAG (m_noscribe , SF_NOSCRIBE);
	  UNLOAD_FLAG (m_object , SF_OBJECT);
	  UNLOAD_FLAG (m_pksensitive , SF_PKSENSITIVE);
	  UNLOAD_FLAG (m_recastable , SF_RECASTABLE);
	  UNLOAD_FLAG (m_reverse , SF_REVERSE);
	  UNLOAD_FLAG (m_save_half_damage, SF_SAVE_HALF_DAMAGE);
	  UNLOAD_FLAG (m_save_negates , SF_SAVE_NEGATES);
	  UNLOAD_FLAG (m_secretskill , SF_SECRETSKILL);
	  UNLOAD_FLAG (m_stoponfail , SF_STOPONFAIL);
	  UNLOAD_FLAG (m_water , SF_WATER);
    if (bChanged)
      App.m_bSkillsDirty = true;
    }

}


BEGIN_MESSAGE_MAP(CSkillsPage4, CPropertyPage)
	//{{AFX_MSG_MAP(CSkillsPage4)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


