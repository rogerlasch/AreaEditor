/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// MobileAffectPage.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "AreaEditorDoc.h"
#include "MobileAffectPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMobileAffectPage dialog


CMobileAffectPage::CMobileAffectPage(CWnd* pParent /*=NULL*/)
	: CDialog(CMobileAffectPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMobileAffectPage)
	m_bBlind = FALSE;
	m_bInvisible = FALSE;
	m_bAquaBreath = FALSE;
	m_bBerserk = FALSE;
	m_bCharm = FALSE;
	m_bCurse = FALSE;
	m_bDetectEvil = FALSE;
	m_bDetectHidden = FALSE;
	m_bDetectInvis = FALSE;
	m_bDetectMagic = FALSE;
	m_bDetectTraps = FALSE;
	m_bFaeireFire = FALSE;
	m_bFireShield = FALSE;
	m_bFlaming = FALSE;
	m_bFloating = FALSE;
	m_bFlying = FALSE;
	m_bHaus1 = FALSE;
	m_bHide = FALSE;
	m_bHold = FALSE;
	m_bIceShield = FALSE;
	m_bInfraRed = FALSE;
	m_bParalysis = FALSE;
	m_bPassDoor = FALSE;
	m_bPoison = FALSE;
	m_bPossess = FALSE;
	m_bProtect = FALSE;
	m_bSanctuary = FALSE;
	m_bScrying = FALSE;
	m_bShockShield = FALSE;
	m_bSleep = FALSE;
	m_bSneak = FALSE;
	m_bTrueSight = FALSE;
	//}}AFX_DATA_INIT

  m_mob = NULL;

}

#undef LOAD_FLAG
#define LOAD_FLAG(field, flag)  \
  field = IS_SET (m_mob->affected_by, flag);

#undef UNLOAD_FLAG
#define UNLOAD_FLAG(field, flag)  \
  if (field != IS_SET (m_mob->affected_by, flag)) bChanged = true; \
  if (field)                      \
    SET_BIT (m_mob->affected_by, flag);\
  else                            \
    REMOVE_BIT (m_mob->affected_by, flag)

void CMobileAffectPage::DoDataExchange(CDataExchange* pDX)
{
bool bChanged = false;

  if (!pDX->m_bSaveAndValidate)
    {
	  LOAD_FLAG (m_bBlind, AFF_BLIND);
	  LOAD_FLAG (m_bInvisible, AFF_INVISIBLE);
	  LOAD_FLAG (m_bAquaBreath, AFF_AQUA_BREATH);
	  LOAD_FLAG (m_bBerserk, AFF_BERSERK);
	  LOAD_FLAG (m_bCharm, AFF_CHARM);
	  LOAD_FLAG (m_bCurse, AFF_CURSE);
	  LOAD_FLAG (m_bDetectEvil, AFF_DETECT_EVIL);
	  LOAD_FLAG (m_bDetectHidden, AFF_DETECT_HIDDEN);
	  LOAD_FLAG (m_bDetectInvis, AFF_DETECT_INVIS);
	  LOAD_FLAG (m_bDetectMagic, AFF_DETECT_MAGIC);
	  LOAD_FLAG (m_bDetectTraps, AFF_DETECTTRAPS);
	  LOAD_FLAG (m_bFaeireFire, AFF_FAERIE_FIRE);
	  LOAD_FLAG (m_bFireShield, AFF_FIRESHIELD);
	  LOAD_FLAG (m_bFlaming, AFF_FLAMING);
	  LOAD_FLAG (m_bFloating, AFF_FLOATING);
	  LOAD_FLAG (m_bFlying, AFF_FLYING);
	  LOAD_FLAG (m_bHaus1, AFF_HAUS1);
	  LOAD_FLAG (m_bHide, AFF_HIDE);
	  LOAD_FLAG (m_bHold, AFF_HOLD);
	  LOAD_FLAG (m_bIceShield, AFF_ICESHIELD);
	  LOAD_FLAG (m_bInfraRed, AFF_INFRARED);
	  LOAD_FLAG (m_bParalysis, AFF_PARALYSIS);
	  LOAD_FLAG (m_bPassDoor, AFF_PASS_DOOR);
	  LOAD_FLAG (m_bPoison, AFF_POISON);
	  LOAD_FLAG (m_bPossess, AFF_POSSESS);
	  LOAD_FLAG (m_bProtect, AFF_PROTECT);
	  LOAD_FLAG (m_bSanctuary, AFF_SANCTUARY);
	  LOAD_FLAG (m_bScrying, AFF_SCRYING);
	  LOAD_FLAG (m_bShockShield, AFF_SHOCKSHIELD);
	  LOAD_FLAG (m_bSleep, AFF_SLEEP);
	  LOAD_FLAG (m_bSneak, AFF_SNEAK);
	  LOAD_FLAG (m_bTrueSight, AFF_TRUESIGHT);

    }

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMobileAffectPage)
	DDX_Check(pDX, IDC_AFF_BLIND, m_bBlind);
	DDX_Check(pDX, IDC_AFF_INVISIBLE, m_bInvisible);
	DDX_Check(pDX, IDC_AFF_AQUA_BREATH, m_bAquaBreath);
	DDX_Check(pDX, IDC_AFF_BERSERK, m_bBerserk);
	DDX_Check(pDX, IDC_AFF_CHARM, m_bCharm);
	DDX_Check(pDX, IDC_AFF_CURSE, m_bCurse);
	DDX_Check(pDX, IDC_AFF_DETECT_EVIL, m_bDetectEvil);
	DDX_Check(pDX, IDC_AFF_DETECT_HIDDEN, m_bDetectHidden);
	DDX_Check(pDX, IDC_AFF_DETECT_INVIS, m_bDetectInvis);
	DDX_Check(pDX, IDC_AFF_DETECT_MAGIC, m_bDetectMagic);
	DDX_Check(pDX, IDC_AFF_DETECTTRAPS, m_bDetectTraps);
	DDX_Check(pDX, IDC_AFF_FAERIE_FIRE, m_bFaeireFire);
	DDX_Check(pDX, IDC_AFF_FIRESHIELD, m_bFireShield);
	DDX_Check(pDX, IDC_AFF_FLAMING, m_bFlaming);
	DDX_Check(pDX, IDC_AFF_FLOATING, m_bFloating);
	DDX_Check(pDX, IDC_AFF_FLYING, m_bFlying);
	DDX_Check(pDX, IDC_AFF_HAUS1, m_bHaus1);
	DDX_Check(pDX, IDC_AFF_HIDE, m_bHide);
	DDX_Check(pDX, IDC_AFF_HOLD, m_bHold);
	DDX_Check(pDX, IDC_AFF_ICESHIELD, m_bIceShield);
	DDX_Check(pDX, IDC_AFF_INFRARED, m_bInfraRed);
	DDX_Check(pDX, IDC_AFF_PARALYSIS, m_bParalysis);
	DDX_Check(pDX, IDC_AFF_PASS_DOOR, m_bPassDoor);
	DDX_Check(pDX, IDC_AFF_POISON, m_bPoison);
	DDX_Check(pDX, IDC_AFF_POSSESS, m_bPossess);
	DDX_Check(pDX, IDC_AFF_PROTECT, m_bProtect);
	DDX_Check(pDX, IDC_AFF_SANCTUARY, m_bSanctuary);
	DDX_Check(pDX, IDC_AFF_SCRYING, m_bScrying);
	DDX_Check(pDX, IDC_AFF_SHOCKSHIELD, m_bShockShield);
	DDX_Check(pDX, IDC_AFF_SLEEP, m_bSleep);
	DDX_Check(pDX, IDC_AFF_SNEAK, m_bSneak);
	DDX_Check(pDX, IDC_AFF_TRUESIGHT, m_bTrueSight);
	//}}AFX_DATA_MAP

  if (pDX->m_bSaveAndValidate)
    {
	  UNLOAD_FLAG (m_bBlind, AFF_BLIND);
	  UNLOAD_FLAG (m_bInvisible, AFF_INVISIBLE);
	  UNLOAD_FLAG (m_bAquaBreath, AFF_AQUA_BREATH);
	  UNLOAD_FLAG (m_bBerserk, AFF_BERSERK);
	  UNLOAD_FLAG (m_bCharm, AFF_CHARM);
	  UNLOAD_FLAG (m_bCurse, AFF_CURSE);
	  UNLOAD_FLAG (m_bDetectEvil, AFF_DETECT_EVIL);
	  UNLOAD_FLAG (m_bDetectHidden, AFF_DETECT_HIDDEN);
	  UNLOAD_FLAG (m_bDetectInvis, AFF_DETECT_INVIS);
	  UNLOAD_FLAG (m_bDetectMagic, AFF_DETECT_MAGIC);
	  UNLOAD_FLAG (m_bDetectTraps, AFF_DETECTTRAPS);
	  UNLOAD_FLAG (m_bFaeireFire, AFF_FAERIE_FIRE);
	  UNLOAD_FLAG (m_bFireShield, AFF_FIRESHIELD);
	  UNLOAD_FLAG (m_bFlaming, AFF_FLAMING);
	  UNLOAD_FLAG (m_bFloating, AFF_FLOATING);
	  UNLOAD_FLAG (m_bFlying, AFF_FLYING);
	  UNLOAD_FLAG (m_bHaus1, AFF_HAUS1);
	  UNLOAD_FLAG (m_bHide, AFF_HIDE);
	  UNLOAD_FLAG (m_bHold, AFF_HOLD);
	  UNLOAD_FLAG (m_bIceShield, AFF_ICESHIELD);
	  UNLOAD_FLAG (m_bInfraRed, AFF_INFRARED);
	  UNLOAD_FLAG (m_bParalysis, AFF_PARALYSIS);
	  UNLOAD_FLAG (m_bPassDoor, AFF_PASS_DOOR);
	  UNLOAD_FLAG (m_bPoison, AFF_POISON);
	  UNLOAD_FLAG (m_bPossess, AFF_POSSESS);
	  UNLOAD_FLAG (m_bProtect, AFF_PROTECT);
	  UNLOAD_FLAG (m_bSanctuary, AFF_SANCTUARY);
	  UNLOAD_FLAG (m_bScrying, AFF_SCRYING);
	  UNLOAD_FLAG (m_bShockShield, AFF_SHOCKSHIELD);
	  UNLOAD_FLAG (m_bSleep, AFF_SLEEP);
	  UNLOAD_FLAG (m_bSneak, AFF_SNEAK);
	  UNLOAD_FLAG (m_bTrueSight, AFF_TRUESIGHT);

     if (bChanged)
       m_mob->m_pDoc->SetModifiedFlag ();

    }

}


BEGIN_MESSAGE_MAP(CMobileAffectPage, CDialog)
	//{{AFX_MSG_MAP(CMobileAffectPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMobileAffectPage message handlers
