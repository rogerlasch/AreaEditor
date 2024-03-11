// ObjectExtraFlagsPage.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "AreaEditorDoc.h"

#include "ObjectExtraFlagsPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CObjectExtraFlagsPage dialog


CObjectExtraFlagsPage::CObjectExtraFlagsPage(CWnd* pParent /*=NULL*/)
	: CDialog(CObjectExtraFlagsPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CObjectExtraFlagsPage)
	m_anti_cleric = FALSE;
	m_anti_druid = FALSE;
	m_anti_evil = FALSE;
	m_anti_good = FALSE;
	m_anti_mage = FALSE;
	m_anti_neutral = FALSE;
	m_anti_thief = FALSE;
	m_anti_vampire = FALSE;
	m_anti_warrior = FALSE;
	m_bless = FALSE;
	m_buried = FALSE;
	m_clancorpse = FALSE;
	m_clanobject = FALSE;
	m_covering = FALSE;
	m_dark = FALSE;
	m_deathrot = FALSE;
	m_donation = FALSE;
	m_evil = FALSE;
	m_glow = FALSE;
	m_hidden = FALSE;
	m_hum = FALSE;
	m_inventory = FALSE;
	m_invis = FALSE;
	m_loyal = FALSE;
	m_magic = FALSE;
	m_metal = FALSE;
	m_nodrop = FALSE;
	m_noremove = FALSE;
	m_organic = FALSE;
	m_poisoned = FALSE;
	m_prototype = FALSE;
	m_dual_wield = FALSE;
	m_hold = FALSE;
	m_missile_wield = FALSE;
	m_take = FALSE;
	m_wear_about = FALSE;
	m_wear_arms = FALSE;
	m_wear_body = FALSE;
	m_wear_ears = FALSE;
	m_wear_eyes = FALSE;
	m_wear_feet = FALSE;
	m_wear_finger = FALSE;
	m_wear_hands = FALSE;
	m_wear_head = FALSE;
	m_wear_legs = FALSE;
	m_wear_neck = FALSE;
	m_wear_shield = FALSE;
	m_wear_waist = FALSE;
	m_wear_wrist = FALSE;
	m_wield = FALSE;
	//}}AFX_DATA_INIT

  m_object = NULL;

}

#undef LOAD_EXTRA_FLAG
#define LOAD_EXTRA_FLAG(field, flag)  \
  field = IS_SET (m_object->extra_flags, flag);

#undef UNLOAD_EXTRA_FLAG
#define UNLOAD_EXTRA_FLAG(field, flag)  \
  if (field != IS_SET (m_object->extra_flags, flag)) bChanged = true; \
  if (field)                      \
    SET_BIT (m_object->extra_flags, flag);\
  else                            \
    REMOVE_BIT (m_object->extra_flags, flag)

#undef LOAD_WEAR_FLAG
#define LOAD_WEAR_FLAG(field, flag)  \
  field = IS_SET (m_object->wear_flags, flag);

#undef UNLOAD_WEAR_FLAG
#define UNLOAD_WEAR_FLAG(field, flag)  \
  if (field != IS_SET (m_object->wear_flags, flag)) bChanged = true; \
  if (field)                      \
    SET_BIT (m_object->wear_flags, flag);\
  else                            \
    REMOVE_BIT (m_object->wear_flags, flag)

void CObjectExtraFlagsPage::DoDataExchange(CDataExchange* pDX)
{
bool bChanged = false;

  if (!pDX->m_bSaveAndValidate)
    {
	   LOAD_EXTRA_FLAG (m_anti_cleric, ITEM_ANTI_CLERIC);
	   LOAD_EXTRA_FLAG (m_anti_druid, ITEM_ANTI_DRUID);
	   LOAD_EXTRA_FLAG (m_anti_evil, ITEM_ANTI_EVIL);
	   LOAD_EXTRA_FLAG (m_anti_good, ITEM_ANTI_GOOD);
	   LOAD_EXTRA_FLAG (m_anti_mage, ITEM_ANTI_MAGE);
	   LOAD_EXTRA_FLAG (m_anti_neutral, ITEM_ANTI_NEUTRAL);
	   LOAD_EXTRA_FLAG (m_anti_thief, ITEM_ANTI_THIEF);
	   LOAD_EXTRA_FLAG (m_anti_vampire, ITEM_ANTI_VAMPIRE);
	   LOAD_EXTRA_FLAG (m_anti_warrior, ITEM_ANTI_WARRIOR);
	   LOAD_EXTRA_FLAG (m_bless, ITEM_BLESS);
	   LOAD_EXTRA_FLAG (m_buried, ITEM_BURRIED);
	   LOAD_EXTRA_FLAG (m_clancorpse, ITEM_CLANCORPSE);
	   LOAD_EXTRA_FLAG (m_clanobject, ITEM_CLANOBJECT);
	   LOAD_EXTRA_FLAG (m_covering, ITEM_COVERING);
	   LOAD_EXTRA_FLAG (m_dark, ITEM_DARK);
	   LOAD_EXTRA_FLAG (m_deathrot, ITEM_DEATHROT);
	   LOAD_EXTRA_FLAG (m_donation, ITEM_DONATION);
	   LOAD_EXTRA_FLAG (m_evil, ITEM_EVIL);
	   LOAD_EXTRA_FLAG (m_glow, ITEM_GLOW);
	   LOAD_EXTRA_FLAG (m_hidden, ITEM_HIDDEN);
	   LOAD_EXTRA_FLAG (m_hum, ITEM_HUM);
	   LOAD_EXTRA_FLAG (m_inventory, ITEM_INVENTORY);
	   LOAD_EXTRA_FLAG (m_invis, ITEM_INVIS);
	   LOAD_EXTRA_FLAG (m_loyal, ITEM_LOYAL);
     LOAD_EXTRA_FLAG (m_magic, ITEM_MAGIC);
     LOAD_EXTRA_FLAG (m_metal, ITEM_METAL);
     LOAD_EXTRA_FLAG (m_nodrop, ITEM_NODROP);
     LOAD_EXTRA_FLAG (m_noremove, ITEM_NOREMOVE);
     LOAD_EXTRA_FLAG (m_organic, ITEM_ORGANIC);
     LOAD_EXTRA_FLAG (m_poisoned, ITEM_POISONED);
     LOAD_EXTRA_FLAG (m_prototype, ITEM_PROTOTYPE);


	   LOAD_WEAR_FLAG (m_dual_wield, ITEM_DUAL_WIELD);
	   LOAD_WEAR_FLAG (m_hold, ITEM_HOLD);
	   LOAD_WEAR_FLAG (m_missile_wield, ITEM_MISSILE_WIELD);
	   LOAD_WEAR_FLAG (m_take, ITEM_TAKE);
	   LOAD_WEAR_FLAG (m_wear_about, ITEM_WEAR_ABOUT);
	   LOAD_WEAR_FLAG (m_wear_arms, ITEM_WEAR_ARMS);
	   LOAD_WEAR_FLAG (m_wear_body, ITEM_WEAR_BODY);
	   LOAD_WEAR_FLAG (m_wear_ears, ITEM_WEAR_EARS);
	   LOAD_WEAR_FLAG (m_wear_eyes, ITEM_WEAR_EYES);
	   LOAD_WEAR_FLAG (m_wear_feet, ITEM_WEAR_FEET);
	   LOAD_WEAR_FLAG (m_wear_finger, ITEM_WEAR_FINGER);
	   LOAD_WEAR_FLAG (m_wear_hands, ITEM_WEAR_HANDS);
	   LOAD_WEAR_FLAG (m_wear_head, ITEM_WEAR_HEAD);
	   LOAD_WEAR_FLAG (m_wear_legs, ITEM_WEAR_LEGS);
	   LOAD_WEAR_FLAG (m_wear_neck, ITEM_WEAR_NECK);
	   LOAD_WEAR_FLAG (m_wear_shield, ITEM_WEAR_SHIELD);
	   LOAD_WEAR_FLAG (m_wear_waist, ITEM_WEAR_WAIST);
	   LOAD_WEAR_FLAG (m_wear_wrist, ITEM_WEAR_WRIST);
	   LOAD_WEAR_FLAG (m_wield, ITEM_WIELD);

    }

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CObjectExtraFlagsPage)
	DDX_Check(pDX, IDC_ANTI_CLERIC, m_anti_cleric);
	DDX_Check(pDX, IDC_ANTI_DRUID, m_anti_druid);
	DDX_Check(pDX, IDC_ANTI_EVIL, m_anti_evil);
	DDX_Check(pDX, IDC_ANTI_GOOD, m_anti_good);
	DDX_Check(pDX, IDC_ANTI_MAGE, m_anti_mage);
	DDX_Check(pDX, IDC_ANTI_NEUTRAL, m_anti_neutral);
	DDX_Check(pDX, IDC_ANTI_THIEF, m_anti_thief);
	DDX_Check(pDX, IDC_ANTI_VAMPIRE, m_anti_vampire);
	DDX_Check(pDX, IDC_ANTI_WARRIOR, m_anti_warrior);
	DDX_Check(pDX, IDC_BLESS, m_bless);
	DDX_Check(pDX, IDC_BURIED, m_buried);
	DDX_Check(pDX, IDC_CLANCORPSE, m_clancorpse);
	DDX_Check(pDX, IDC_CLANOBJECT, m_clanobject);
	DDX_Check(pDX, IDC_COVERING, m_covering);
	DDX_Check(pDX, IDC_DARK, m_dark);
	DDX_Check(pDX, IDC_DEATHROT, m_deathrot);
	DDX_Check(pDX, IDC_DONATION, m_donation);
	DDX_Check(pDX, IDC_EVIL, m_evil);
	DDX_Check(pDX, IDC_GLOW, m_glow);
	DDX_Check(pDX, IDC_HIDDEN, m_hidden);
	DDX_Check(pDX, IDC_HUM, m_hum);
	DDX_Check(pDX, IDC_INVENTORY, m_inventory);
	DDX_Check(pDX, IDC_INVIS, m_invis);
	DDX_Check(pDX, IDC_LOYAL, m_loyal);
	DDX_Check(pDX, IDC_MAGIC, m_magic);
	DDX_Check(pDX, IDC_METAL, m_metal);
	DDX_Check(pDX, IDC_NODROP, m_nodrop);
	DDX_Check(pDX, IDC_NOREMOVE, m_noremove);
	DDX_Check(pDX, IDC_ORGANIC, m_organic);
	DDX_Check(pDX, IDC_POISONED, m_poisoned);
	DDX_Check(pDX, IDC_PROTOTYPE, m_prototype);
	DDX_Check(pDX, IDC_DUAL_WIELD, m_dual_wield);
	DDX_Check(pDX, IDC_HOLD, m_hold);
	DDX_Check(pDX, IDC_MISSILE_WIELD, m_missile_wield);
	DDX_Check(pDX, IDC_TAKE, m_take);
	DDX_Check(pDX, IDC_WEAR_ABOUT, m_wear_about);
	DDX_Check(pDX, IDC_WEAR_ARMS, m_wear_arms);
	DDX_Check(pDX, IDC_WEAR_BODY, m_wear_body);
	DDX_Check(pDX, IDC_WEAR_EARS, m_wear_ears);
	DDX_Check(pDX, IDC_WEAR_EYES, m_wear_eyes);
	DDX_Check(pDX, IDC_WEAR_FEET, m_wear_feet);
	DDX_Check(pDX, IDC_WEAR_FINGER, m_wear_finger);
	DDX_Check(pDX, IDC_WEAR_HANDS, m_wear_hands);
	DDX_Check(pDX, IDC_WEAR_HEAD, m_wear_head);
	DDX_Check(pDX, IDC_WEAR_LEGS, m_wear_legs);
	DDX_Check(pDX, IDC_WEAR_NECK, m_wear_neck);
	DDX_Check(pDX, IDC_WEAR_SHIELD, m_wear_shield);
	DDX_Check(pDX, IDC_WEAR_WAIST, m_wear_waist);
	DDX_Check(pDX, IDC_WEAR_WRIST, m_wear_wrist);
	DDX_Check(pDX, IDC_WIELD, m_wield);
	//}}AFX_DATA_MAP

  if (pDX->m_bSaveAndValidate)
    {
	   UNLOAD_EXTRA_FLAG (m_anti_cleric, ITEM_ANTI_CLERIC);
	   UNLOAD_EXTRA_FLAG (m_anti_druid, ITEM_ANTI_DRUID);
	   UNLOAD_EXTRA_FLAG (m_anti_evil, ITEM_ANTI_EVIL);
	   UNLOAD_EXTRA_FLAG (m_anti_good, ITEM_ANTI_GOOD);
	   UNLOAD_EXTRA_FLAG (m_anti_mage, ITEM_ANTI_MAGE);
	   UNLOAD_EXTRA_FLAG (m_anti_neutral, ITEM_ANTI_NEUTRAL);
	   UNLOAD_EXTRA_FLAG (m_anti_thief, ITEM_ANTI_THIEF);
	   UNLOAD_EXTRA_FLAG (m_anti_vampire, ITEM_ANTI_VAMPIRE);
	   UNLOAD_EXTRA_FLAG (m_anti_warrior, ITEM_ANTI_WARRIOR);
	   UNLOAD_EXTRA_FLAG (m_bless, ITEM_BLESS);
	   UNLOAD_EXTRA_FLAG (m_buried, ITEM_BURRIED);
	   UNLOAD_EXTRA_FLAG (m_clancorpse, ITEM_CLANCORPSE);
	   UNLOAD_EXTRA_FLAG (m_clanobject, ITEM_CLANOBJECT);
	   UNLOAD_EXTRA_FLAG (m_covering, ITEM_COVERING);
	   UNLOAD_EXTRA_FLAG (m_dark, ITEM_DARK);
	   UNLOAD_EXTRA_FLAG (m_deathrot, ITEM_DEATHROT);
	   UNLOAD_EXTRA_FLAG (m_donation, ITEM_DONATION);
	   UNLOAD_EXTRA_FLAG (m_evil, ITEM_EVIL);
	   UNLOAD_EXTRA_FLAG (m_glow, ITEM_GLOW);
	   UNLOAD_EXTRA_FLAG (m_hidden, ITEM_HIDDEN);
	   UNLOAD_EXTRA_FLAG (m_hum, ITEM_HUM);
	   UNLOAD_EXTRA_FLAG (m_inventory, ITEM_INVENTORY);
	   UNLOAD_EXTRA_FLAG (m_invis, ITEM_INVIS);
	   UNLOAD_EXTRA_FLAG (m_loyal, ITEM_LOYAL);
     UNLOAD_EXTRA_FLAG (m_magic, ITEM_MAGIC);
     UNLOAD_EXTRA_FLAG (m_metal, ITEM_METAL);
     UNLOAD_EXTRA_FLAG (m_nodrop, ITEM_NODROP);
     UNLOAD_EXTRA_FLAG (m_noremove, ITEM_NOREMOVE);
     UNLOAD_EXTRA_FLAG (m_organic, ITEM_ORGANIC);
     UNLOAD_EXTRA_FLAG (m_poisoned, ITEM_POISONED);
     UNLOAD_EXTRA_FLAG (m_prototype, ITEM_PROTOTYPE);

	   UNLOAD_WEAR_FLAG (m_dual_wield, ITEM_DUAL_WIELD);
	   UNLOAD_WEAR_FLAG (m_hold, ITEM_HOLD);
	   UNLOAD_WEAR_FLAG (m_missile_wield, ITEM_MISSILE_WIELD);
	   UNLOAD_WEAR_FLAG (m_take, ITEM_TAKE);
	   UNLOAD_WEAR_FLAG (m_wear_about, ITEM_WEAR_ABOUT);
	   UNLOAD_WEAR_FLAG (m_wear_arms, ITEM_WEAR_ARMS);
	   UNLOAD_WEAR_FLAG (m_wear_body, ITEM_WEAR_BODY);
	   UNLOAD_WEAR_FLAG (m_wear_ears, ITEM_WEAR_EARS);
	   UNLOAD_WEAR_FLAG (m_wear_eyes, ITEM_WEAR_EYES);
	   UNLOAD_WEAR_FLAG (m_wear_feet, ITEM_WEAR_FEET);
	   UNLOAD_WEAR_FLAG (m_wear_finger, ITEM_WEAR_FINGER);
	   UNLOAD_WEAR_FLAG (m_wear_hands, ITEM_WEAR_HANDS);
	   UNLOAD_WEAR_FLAG (m_wear_head, ITEM_WEAR_HEAD);
	   UNLOAD_WEAR_FLAG (m_wear_legs, ITEM_WEAR_LEGS);
	   UNLOAD_WEAR_FLAG (m_wear_neck, ITEM_WEAR_NECK);
	   UNLOAD_WEAR_FLAG (m_wear_shield, ITEM_WEAR_SHIELD);
	   UNLOAD_WEAR_FLAG (m_wear_waist, ITEM_WEAR_WAIST);
	   UNLOAD_WEAR_FLAG (m_wear_wrist, ITEM_WEAR_WRIST);
	   UNLOAD_WEAR_FLAG (m_wield, ITEM_WIELD);

     if (bChanged)
       m_object->m_pDoc->SetModifiedFlag ();
    }

}


BEGIN_MESSAGE_MAP(CObjectExtraFlagsPage, CDialog)
	//{{AFX_MSG_MAP(CObjectExtraFlagsPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CObjectExtraFlagsPage message handlers
