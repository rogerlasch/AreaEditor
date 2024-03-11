/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// MobileResistantPage.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "AreaEditorDoc.h"

#include "MobileResistantPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMobileResistantPage dialog


CMobileResistantPage::CMobileResistantPage(CWnd* pParent /*=NULL*/)
	: CDialog(CMobileResistantPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMobileResistantPage)
	m_res_acid = FALSE;
	m_res_blunt = FALSE;
	m_res_charm = FALSE;
	m_res_cold = FALSE;
	m_res_drain = FALSE;
	m_res_electricity = FALSE;
	m_res_energy = FALSE;
	m_res_fire = FALSE;
	m_res_hold = FALSE;
	m_res_magic = FALSE;
	m_res_nonmagic = FALSE;
	m_res_paralysis = FALSE;
	m_res_pierce = FALSE;
	m_res_plus1 = FALSE;
	m_res_plus2 = FALSE;
	m_res_plus3 = FALSE;
	m_res_plus4 = FALSE;
	m_res_plus5 = FALSE;
	m_res_plus6 = FALSE;
	m_res_poison = FALSE;
	m_res_slash = FALSE;
	m_res_sleep = FALSE;
	m_imm_acid = FALSE;
	m_imm_blunt = FALSE;
	m_imm_charm = FALSE;
	m_imm_cold = FALSE;
	m_imm_drain = FALSE;
	m_imm_electricity = FALSE;
	m_imm_energy = FALSE;
	m_imm_fire = FALSE;
	m_imm_hold = FALSE;
	m_imm_magic = FALSE;
	m_imm_nonmagic = FALSE;
	m_imm_paralysis = FALSE;
	m_imm_pierce = FALSE;
	m_imm_plus1 = FALSE;
	m_imm_plus2 = FALSE;
	m_imm_plus3 = FALSE;
	m_imm_plus4 = FALSE;
	m_imm_plus5 = FALSE;
	m_imm_plus6 = FALSE;
	m_imm_poison = FALSE;
	m_imm_slash = FALSE;
	m_imm_sleep = FALSE;
	m_sus_acid = FALSE;
	m_sus_blunt = FALSE;
	m_sus_charm = FALSE;
	m_sus_cold = FALSE;
	m_sus_drain = FALSE;
	m_sus_electricity = FALSE;
	m_sus_energy = FALSE;
	m_sus_fire = FALSE;
	m_sus_hold = FALSE;
	m_sus_magic = FALSE;
	m_sus_nonmagic = FALSE;
	m_sus_paralysis = FALSE;
	m_sus_pierce = FALSE;
	m_sus_plus1 = FALSE;
	m_sus_plus2 = FALSE;
	m_sus_plus3 = FALSE;
	m_sus_plus4 = FALSE;
	m_sus_plus5 = FALSE;
	m_sus_plus6 = FALSE;
	m_sus_poison = FALSE;
	m_sus_slash = FALSE;
	m_sus_sleep = FALSE;
	//}}AFX_DATA_INIT

  m_mob = NULL;

}

#undef LOAD_RESISTANT_FLAG
#define LOAD_RESISTANT_FLAG(field, flag)  \
  field = IS_SET (m_mob->resistant, flag);

#undef LOAD_IMMUNE_FLAG
#define LOAD_IMMUNE_FLAG(field, flag)  \
  field = IS_SET (m_mob->immune, flag);

#undef LOAD_SUSCEPTIBLE_FLAG
#define LOAD_SUSCEPTIBLE_FLAG(field, flag)  \
  field = IS_SET (m_mob->susceptible, flag);

#undef UNLOAD_RESISTANT_FLAG
#define UNLOAD_RESISTANT_FLAG(field, flag)  \
  if (field != IS_SET (m_mob->resistant, flag)) bChanged = true; \
  if (field)                      \
    SET_BIT (m_mob->resistant, flag);\
  else                            \
    REMOVE_BIT (m_mob->resistant, flag)

#undef UNLOAD_IMMUNE_FLAG
#define UNLOAD_IMMUNE_FLAG(field, flag)  \
  if (field != IS_SET (m_mob->immune, flag)) bChanged = true; \
  if (field)                      \
    SET_BIT (m_mob->immune, flag);\
  else                            \
    REMOVE_BIT (m_mob->immune, flag)

#undef UNLOAD_SUSCEPTIBLE_FLAG
#define UNLOAD_SUSCEPTIBLE_FLAG(field, flag)  \
  if (field != IS_SET (m_mob->susceptible, flag)) bChanged = true; \
  if (field)                      \
    SET_BIT (m_mob->susceptible, flag);\
  else                            \
    REMOVE_BIT (m_mob->susceptible, flag)

void CMobileResistantPage::DoDataExchange(CDataExchange* pDX)
{
bool bChanged = false;

  if (!pDX->m_bSaveAndValidate)
    {
	  LOAD_RESISTANT_FLAG (m_res_acid, RIS_ACID);
	  LOAD_RESISTANT_FLAG (m_res_blunt, RIS_BLUNT);
	  LOAD_RESISTANT_FLAG (m_res_charm, RIS_CHARM);
	  LOAD_RESISTANT_FLAG (m_res_cold, RIS_COLD);
	  LOAD_RESISTANT_FLAG (m_res_drain, RIS_DRAIN);
	  LOAD_RESISTANT_FLAG (m_res_electricity, RIS_ELECTRICITY);
	  LOAD_RESISTANT_FLAG (m_res_energy, RIS_ENERGY);
	  LOAD_RESISTANT_FLAG (m_res_fire, RIS_FIRE);
	  LOAD_RESISTANT_FLAG (m_res_hold, RIS_HOLD);
	  LOAD_RESISTANT_FLAG (m_res_magic, RIS_MAGIC);
	  LOAD_RESISTANT_FLAG (m_res_nonmagic, RIS_NONMAGIC);
	  LOAD_RESISTANT_FLAG (m_res_paralysis, RIS_PARALYSIS);
	  LOAD_RESISTANT_FLAG (m_res_pierce, RIS_PIERCE);
	  LOAD_RESISTANT_FLAG (m_res_plus1, RIS_PLUS1);
	  LOAD_RESISTANT_FLAG (m_res_plus2, RIS_PLUS2);
	  LOAD_RESISTANT_FLAG (m_res_plus3, RIS_PLUS3);
	  LOAD_RESISTANT_FLAG (m_res_plus4, RIS_PLUS4);
	  LOAD_RESISTANT_FLAG (m_res_plus5, RIS_PLUS5);
	  LOAD_RESISTANT_FLAG (m_res_plus6, RIS_PLUS6);
	  LOAD_RESISTANT_FLAG (m_res_poison, RIS_POISON);
	  LOAD_RESISTANT_FLAG (m_res_slash, RIS_SLASH);
	  LOAD_RESISTANT_FLAG (m_res_sleep, RIS_SLEEP);

	  LOAD_IMMUNE_FLAG (m_imm_acid, RIS_ACID);
	  LOAD_IMMUNE_FLAG (m_imm_blunt, RIS_BLUNT);
	  LOAD_IMMUNE_FLAG (m_imm_charm, RIS_CHARM);
	  LOAD_IMMUNE_FLAG (m_imm_cold, RIS_COLD);
	  LOAD_IMMUNE_FLAG (m_imm_drain, RIS_DRAIN);
	  LOAD_IMMUNE_FLAG (m_imm_electricity, RIS_ELECTRICITY);
	  LOAD_IMMUNE_FLAG (m_imm_energy, RIS_ENERGY);
	  LOAD_IMMUNE_FLAG (m_imm_fire, RIS_FIRE);
	  LOAD_IMMUNE_FLAG (m_imm_hold, RIS_HOLD);
	  LOAD_IMMUNE_FLAG (m_imm_magic, RIS_MAGIC);
	  LOAD_IMMUNE_FLAG (m_imm_nonmagic, RIS_NONMAGIC);
	  LOAD_IMMUNE_FLAG (m_imm_paralysis, RIS_PARALYSIS);
	  LOAD_IMMUNE_FLAG (m_imm_pierce, RIS_PIERCE);
	  LOAD_IMMUNE_FLAG (m_imm_plus1, RIS_PLUS1);
	  LOAD_IMMUNE_FLAG (m_imm_plus2, RIS_PLUS2);
	  LOAD_IMMUNE_FLAG (m_imm_plus3, RIS_PLUS3);
	  LOAD_IMMUNE_FLAG (m_imm_plus4, RIS_PLUS4);
	  LOAD_IMMUNE_FLAG (m_imm_plus5, RIS_PLUS5);
	  LOAD_IMMUNE_FLAG (m_imm_plus6, RIS_PLUS6);
	  LOAD_IMMUNE_FLAG (m_imm_poison, RIS_POISON);
	  LOAD_IMMUNE_FLAG (m_imm_slash, RIS_SLASH);
	  LOAD_IMMUNE_FLAG (m_imm_sleep, RIS_SLEEP);

	  LOAD_SUSCEPTIBLE_FLAG (m_sus_acid, RIS_ACID);
	  LOAD_SUSCEPTIBLE_FLAG (m_sus_blunt, RIS_BLUNT);
	  LOAD_SUSCEPTIBLE_FLAG (m_sus_charm, RIS_CHARM);
	  LOAD_SUSCEPTIBLE_FLAG (m_sus_cold, RIS_COLD);
	  LOAD_SUSCEPTIBLE_FLAG (m_sus_drain, RIS_DRAIN);
	  LOAD_SUSCEPTIBLE_FLAG (m_sus_electricity, RIS_ELECTRICITY);
	  LOAD_SUSCEPTIBLE_FLAG (m_sus_energy, RIS_ENERGY);
	  LOAD_SUSCEPTIBLE_FLAG (m_sus_fire, RIS_FIRE);
	  LOAD_SUSCEPTIBLE_FLAG (m_sus_hold, RIS_HOLD);
	  LOAD_SUSCEPTIBLE_FLAG (m_sus_magic, RIS_MAGIC);
	  LOAD_SUSCEPTIBLE_FLAG (m_sus_nonmagic, RIS_NONMAGIC);
	  LOAD_SUSCEPTIBLE_FLAG (m_sus_paralysis, RIS_PARALYSIS);
	  LOAD_SUSCEPTIBLE_FLAG (m_sus_pierce, RIS_PIERCE);
	  LOAD_SUSCEPTIBLE_FLAG (m_sus_plus1, RIS_PLUS1);
	  LOAD_SUSCEPTIBLE_FLAG (m_sus_plus2, RIS_PLUS2);
	  LOAD_SUSCEPTIBLE_FLAG (m_sus_plus3, RIS_PLUS3);
	  LOAD_SUSCEPTIBLE_FLAG (m_sus_plus4, RIS_PLUS4);
	  LOAD_SUSCEPTIBLE_FLAG (m_sus_plus5, RIS_PLUS5);
	  LOAD_SUSCEPTIBLE_FLAG (m_sus_plus6, RIS_PLUS6);
	  LOAD_SUSCEPTIBLE_FLAG (m_sus_poison, RIS_POISON);
	  LOAD_SUSCEPTIBLE_FLAG (m_sus_slash, RIS_SLASH);
	  LOAD_SUSCEPTIBLE_FLAG (m_sus_sleep, RIS_SLEEP);

   }

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMobileResistantPage)
	DDX_Check(pDX, IDC_ACID, m_res_acid);
	DDX_Check(pDX, IDC_BLUNT, m_res_blunt);
	DDX_Check(pDX, IDC_CHARM, m_res_charm);
	DDX_Check(pDX, IDC_COLD, m_res_cold);
	DDX_Check(pDX, IDC_DRAIN, m_res_drain);
	DDX_Check(pDX, IDC_ELECTRICITY, m_res_electricity);
	DDX_Check(pDX, IDC_ENERGY, m_res_energy);
	DDX_Check(pDX, IDC_FIRE, m_res_fire);
	DDX_Check(pDX, IDC_HOLD, m_res_hold);
	DDX_Check(pDX, IDC_MAGIC, m_res_magic);
	DDX_Check(pDX, IDC_NONMAGIC, m_res_nonmagic);
	DDX_Check(pDX, IDC_PARALYSIS, m_res_paralysis);
	DDX_Check(pDX, IDC_PIERCE, m_res_pierce);
	DDX_Check(pDX, IDC_PLUS1, m_res_plus1);
	DDX_Check(pDX, IDC_PLUS2, m_res_plus2);
	DDX_Check(pDX, IDC_PLUS3, m_res_plus3);
	DDX_Check(pDX, IDC_PLUS4, m_res_plus4);
	DDX_Check(pDX, IDC_PLUS5, m_res_plus5);
	DDX_Check(pDX, IDC_PLUS6, m_res_plus6);
	DDX_Check(pDX, IDC_POISON, m_res_poison);
	DDX_Check(pDX, IDC_SLASH, m_res_slash);
	DDX_Check(pDX, IDC_SLEEP, m_res_sleep);
	DDX_Check(pDX, IDC_ACID2, m_imm_acid);
	DDX_Check(pDX, IDC_BLUNT2, m_imm_blunt);
	DDX_Check(pDX, IDC_CHARM2, m_imm_charm);
	DDX_Check(pDX, IDC_COLD2, m_imm_cold);
	DDX_Check(pDX, IDC_DRAIN2, m_imm_drain);
	DDX_Check(pDX, IDC_ELECTRICITY2, m_imm_electricity);
	DDX_Check(pDX, IDC_ENERGY2, m_imm_energy);
	DDX_Check(pDX, IDC_FIRE2, m_imm_fire);
	DDX_Check(pDX, IDC_HOLD2, m_imm_hold);
	DDX_Check(pDX, IDC_MAGIC2, m_imm_magic);
	DDX_Check(pDX, IDC_NONMAGIC2, m_imm_nonmagic);
	DDX_Check(pDX, IDC_PARALYSIS2, m_imm_paralysis);
	DDX_Check(pDX, IDC_PIERCE2, m_imm_pierce);
	DDX_Check(pDX, IDC_PLUS7, m_imm_plus1);
	DDX_Check(pDX, IDC_PLUS8, m_imm_plus2);
	DDX_Check(pDX, IDC_PLUS9, m_imm_plus3);
	DDX_Check(pDX, IDC_PLUS10, m_imm_plus4);
	DDX_Check(pDX, IDC_PLUS11, m_imm_plus5);
	DDX_Check(pDX, IDC_PLUS12, m_imm_plus6);
	DDX_Check(pDX, IDC_POISON2, m_imm_poison);
	DDX_Check(pDX, IDC_SLASH2, m_imm_slash);
	DDX_Check(pDX, IDC_SLEEP2, m_imm_sleep);
	DDX_Check(pDX, IDC_ACID3, m_sus_acid);
	DDX_Check(pDX, IDC_BLUNT3, m_sus_blunt);
	DDX_Check(pDX, IDC_CHARM3, m_sus_charm);
	DDX_Check(pDX, IDC_COLD3, m_sus_cold);
	DDX_Check(pDX, IDC_DRAIN3, m_sus_drain);
	DDX_Check(pDX, IDC_ELECTRICITY3, m_sus_electricity);
	DDX_Check(pDX, IDC_ENERGY3, m_sus_energy);
	DDX_Check(pDX, IDC_FIRE3, m_sus_fire);
	DDX_Check(pDX, IDC_HOLD3, m_sus_hold);
	DDX_Check(pDX, IDC_MAGIC3, m_sus_magic);
	DDX_Check(pDX, IDC_NONMAGIC3, m_sus_nonmagic);
	DDX_Check(pDX, IDC_PARALYSIS3, m_sus_paralysis);
	DDX_Check(pDX, IDC_PIERCE3, m_sus_pierce);
	DDX_Check(pDX, IDC_PLUS13, m_sus_plus1);
	DDX_Check(pDX, IDC_PLUS14, m_sus_plus2);
	DDX_Check(pDX, IDC_PLUS15, m_sus_plus3);
	DDX_Check(pDX, IDC_PLUS16, m_sus_plus4);
	DDX_Check(pDX, IDC_PLUS17, m_sus_plus5);
	DDX_Check(pDX, IDC_PLUS18, m_sus_plus6);
	DDX_Check(pDX, IDC_POISON3, m_sus_poison);
	DDX_Check(pDX, IDC_SLASH3, m_sus_slash);
	DDX_Check(pDX, IDC_SLEEP3, m_sus_sleep);
	//}}AFX_DATA_MAP

  if (pDX->m_bSaveAndValidate)
    {
	  UNLOAD_RESISTANT_FLAG (m_res_acid, RIS_ACID);
	  UNLOAD_RESISTANT_FLAG (m_res_blunt, RIS_BLUNT);
	  UNLOAD_RESISTANT_FLAG (m_res_charm, RIS_CHARM);
	  UNLOAD_RESISTANT_FLAG (m_res_cold, RIS_COLD);
	  UNLOAD_RESISTANT_FLAG (m_res_drain, RIS_DRAIN);
	  UNLOAD_RESISTANT_FLAG (m_res_electricity, RIS_ELECTRICITY);
	  UNLOAD_RESISTANT_FLAG (m_res_energy, RIS_ENERGY);
	  UNLOAD_RESISTANT_FLAG (m_res_fire, RIS_FIRE);
	  UNLOAD_RESISTANT_FLAG (m_res_hold, RIS_HOLD);
	  UNLOAD_RESISTANT_FLAG (m_res_magic, RIS_MAGIC);
	  UNLOAD_RESISTANT_FLAG (m_res_nonmagic, RIS_NONMAGIC);
	  UNLOAD_RESISTANT_FLAG (m_res_paralysis, RIS_PARALYSIS);
	  UNLOAD_RESISTANT_FLAG (m_res_pierce, RIS_PIERCE);
	  UNLOAD_RESISTANT_FLAG (m_res_plus1, RIS_PLUS1);
	  UNLOAD_RESISTANT_FLAG (m_res_plus2, RIS_PLUS2);
	  UNLOAD_RESISTANT_FLAG (m_res_plus3, RIS_PLUS3);
	  UNLOAD_RESISTANT_FLAG (m_res_plus4, RIS_PLUS4);
	  UNLOAD_RESISTANT_FLAG (m_res_plus5, RIS_PLUS5);
	  UNLOAD_RESISTANT_FLAG (m_res_plus6, RIS_PLUS6);
	  UNLOAD_RESISTANT_FLAG (m_res_poison, RIS_POISON);
	  UNLOAD_RESISTANT_FLAG (m_res_slash, RIS_SLASH);
	  UNLOAD_RESISTANT_FLAG (m_res_sleep, RIS_SLEEP);

	  UNLOAD_IMMUNE_FLAG (m_imm_acid, RIS_ACID);
	  UNLOAD_IMMUNE_FLAG (m_imm_blunt, RIS_BLUNT);
	  UNLOAD_IMMUNE_FLAG (m_imm_charm, RIS_CHARM);
	  UNLOAD_IMMUNE_FLAG (m_imm_cold, RIS_COLD);
	  UNLOAD_IMMUNE_FLAG (m_imm_drain, RIS_DRAIN);
	  UNLOAD_IMMUNE_FLAG (m_imm_electricity, RIS_ELECTRICITY);
	  UNLOAD_IMMUNE_FLAG (m_imm_energy, RIS_ENERGY);
	  UNLOAD_IMMUNE_FLAG (m_imm_fire, RIS_FIRE);
	  UNLOAD_IMMUNE_FLAG (m_imm_hold, RIS_HOLD);
	  UNLOAD_IMMUNE_FLAG (m_imm_magic, RIS_MAGIC);
	  UNLOAD_IMMUNE_FLAG (m_imm_nonmagic, RIS_NONMAGIC);
	  UNLOAD_IMMUNE_FLAG (m_imm_paralysis, RIS_PARALYSIS);
	  UNLOAD_IMMUNE_FLAG (m_imm_pierce, RIS_PIERCE);
	  UNLOAD_IMMUNE_FLAG (m_imm_plus1, RIS_PLUS1);
	  UNLOAD_IMMUNE_FLAG (m_imm_plus2, RIS_PLUS2);
	  UNLOAD_IMMUNE_FLAG (m_imm_plus3, RIS_PLUS3);
	  UNLOAD_IMMUNE_FLAG (m_imm_plus4, RIS_PLUS4);
	  UNLOAD_IMMUNE_FLAG (m_imm_plus5, RIS_PLUS5);
	  UNLOAD_IMMUNE_FLAG (m_imm_plus6, RIS_PLUS6);
	  UNLOAD_IMMUNE_FLAG (m_imm_poison, RIS_POISON);
	  UNLOAD_IMMUNE_FLAG (m_imm_slash, RIS_SLASH);
	  UNLOAD_IMMUNE_FLAG (m_imm_sleep, RIS_SLEEP);

	  UNLOAD_SUSCEPTIBLE_FLAG (m_sus_acid, RIS_ACID);
	  UNLOAD_SUSCEPTIBLE_FLAG (m_sus_blunt, RIS_BLUNT);
	  UNLOAD_SUSCEPTIBLE_FLAG (m_sus_charm, RIS_CHARM);
	  UNLOAD_SUSCEPTIBLE_FLAG (m_sus_cold, RIS_COLD);
	  UNLOAD_SUSCEPTIBLE_FLAG (m_sus_drain, RIS_DRAIN);
	  UNLOAD_SUSCEPTIBLE_FLAG (m_sus_electricity, RIS_ELECTRICITY);
	  UNLOAD_SUSCEPTIBLE_FLAG (m_sus_energy, RIS_ENERGY);
	  UNLOAD_SUSCEPTIBLE_FLAG (m_sus_fire, RIS_FIRE);
	  UNLOAD_SUSCEPTIBLE_FLAG (m_sus_hold, RIS_HOLD);
	  UNLOAD_SUSCEPTIBLE_FLAG (m_sus_magic, RIS_MAGIC);
	  UNLOAD_SUSCEPTIBLE_FLAG (m_sus_nonmagic, RIS_NONMAGIC);
	  UNLOAD_SUSCEPTIBLE_FLAG (m_sus_paralysis, RIS_PARALYSIS);
	  UNLOAD_SUSCEPTIBLE_FLAG (m_sus_pierce, RIS_PIERCE);
	  UNLOAD_SUSCEPTIBLE_FLAG (m_sus_plus1, RIS_PLUS1);
	  UNLOAD_SUSCEPTIBLE_FLAG (m_sus_plus2, RIS_PLUS2);
	  UNLOAD_SUSCEPTIBLE_FLAG (m_sus_plus3, RIS_PLUS3);
	  UNLOAD_SUSCEPTIBLE_FLAG (m_sus_plus4, RIS_PLUS4);
	  UNLOAD_SUSCEPTIBLE_FLAG (m_sus_plus5, RIS_PLUS5);
	  UNLOAD_SUSCEPTIBLE_FLAG (m_sus_plus6, RIS_PLUS6);
	  UNLOAD_SUSCEPTIBLE_FLAG (m_sus_poison, RIS_POISON);
	  UNLOAD_SUSCEPTIBLE_FLAG (m_sus_slash, RIS_SLASH);
	  UNLOAD_SUSCEPTIBLE_FLAG (m_sus_sleep, RIS_SLEEP);

   // put it in a try block, they can ignore these errors
    try
      {

      if (m_mob->resistant & m_mob->immune)
        {
        ::AfxMessageBox ("You cannot be resistant and immune to the same thing.",
                          MB_ICONSTOP);
        pDX->Fail();
        return;
        }

      if (m_mob->susceptible & m_mob->immune)
        {
        ::AfxMessageBox ("You cannot be susceptible and immune to the same thing.",
                          MB_ICONSTOP);
        pDX->Fail();
        return;
        }

      } // end of try block

     catch (CUserException * e)
      {

      if (App.m_bIgnoreValidationErrors && 
          ::AfxMessageBox ("Ignore this error?", 
          MB_YESNO | MB_DEFBUTTON2 | MB_ICONQUESTION)
          == IDYES)
        e->Delete ();
      else
        throw;
      } // end of catch

     if (bChanged)
       m_mob->m_pDoc->SetModifiedFlag ();
   }

}


BEGIN_MESSAGE_MAP(CMobileResistantPage, CDialog)
	//{{AFX_MSG_MAP(CMobileResistantPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMobileResistantPage message handlers
