/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// MobileAttacksPage.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "AreaEditorDoc.h"

#include "MobileAttacksPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMobileAttacksPage dialog


CMobileAttacksPage::CMobileAttacksPage(CWnd* pParent /*=NULL*/)
	: CDialog(CMobileAttacksPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMobileAttacksPage)
	m_acidbreath = FALSE;
	m_backstab = FALSE;
	m_bash = FALSE;
	m_bite = FALSE;
	m_blindness = FALSE;
	m_causecritical = FALSE;
	m_causeserious = FALSE;
	m_claws = FALSE;
	m_colorspray = FALSE;
	m_curse = FALSE;
	m_drain = FALSE;
	m_earthquake = FALSE;
	m_feed = FALSE;
	m_fireball = FALSE;
	m_firebreath = FALSE;
	m_flamestrike = FALSE;
	m_frostbreath = FALSE;
	m_gasbreath = FALSE;
	m_gaze = FALSE;
	m_gouge = FALSE;
	m_harm = FALSE;
	m_kick = FALSE;
	m_lightnbreath = FALSE;
	m_nastypoison = FALSE;
	m_poison = FALSE;
	m_punch = FALSE;
	m_spiralblast = FALSE;
	m_sting = FALSE;
	m_stun = FALSE;
	m_tail = FALSE;
	m_trip = FALSE;
	m_weaken = FALSE;
	//}}AFX_DATA_INIT

  m_mob = NULL;

}

#undef LOAD_FLAG
#define LOAD_FLAG(field, flag)  \
  field = IS_SET (m_mob->attacks, flag);

#undef UNLOAD_FLAG
#define UNLOAD_FLAG(field, flag)  \
  if (field != IS_SET (m_mob->attacks, flag)) bChanged = true; \
  if (field)                      \
    SET_BIT (m_mob->attacks, flag);\
  else                            \
    REMOVE_BIT (m_mob->attacks, flag)

void CMobileAttacksPage::DoDataExchange(CDataExchange* pDX)
{
bool bChanged = false;

  if (!pDX->m_bSaveAndValidate)
    {
	  LOAD_FLAG (m_acidbreath, ATCK_ACIDBREATH);
	  LOAD_FLAG (m_backstab, ATCK_BACKSTAB);
	  LOAD_FLAG (m_bash, ATCK_BASH);
	  LOAD_FLAG (m_bite, ATCK_BITE);
	  LOAD_FLAG (m_blindness, ATCK_BLINDNESS);
	  LOAD_FLAG (m_causecritical, ATCK_CAUSECRITICAL);
	  LOAD_FLAG (m_causeserious, ATCK_CAUSESERIOUS);
	  LOAD_FLAG (m_claws, ATCK_CLAWS);
	  LOAD_FLAG (m_colorspray, ATCK_COLORSPRAY);
	  LOAD_FLAG (m_curse, ATCK_CURSE);
	  LOAD_FLAG (m_drain, ATCK_DRAIN);
	  LOAD_FLAG (m_earthquake, ATCK_EARTHQUAKE);
	  LOAD_FLAG (m_feed, ATCK_FEED);
	  LOAD_FLAG (m_fireball, ATCK_FIREBALL);
	  LOAD_FLAG (m_firebreath, ATCK_FIREBREATH);
	  LOAD_FLAG (m_flamestrike, ATCK_FLAMESTRIKE);
	  LOAD_FLAG (m_frostbreath, ATCK_FROSTBREATH);
	  LOAD_FLAG (m_gasbreath, ATCK_GASBREATH);
	  LOAD_FLAG (m_gaze, ATCK_GAZE);
	  LOAD_FLAG (m_gouge, ATCK_GOUGE);
	  LOAD_FLAG (m_harm, ATCK_HARM);
	  LOAD_FLAG (m_kick, ATCK_KICK);
	  LOAD_FLAG (m_lightnbreath, ATCK_LIGHTNBREATH);
	  LOAD_FLAG (m_nastypoison, ATCK_NASTYPOISON);
	  LOAD_FLAG (m_poison, ATCK_POISON);
	  LOAD_FLAG (m_punch, ATCK_PUNCH);
	  LOAD_FLAG (m_spiralblast, ATCK_SPIRALBLAST);
	  LOAD_FLAG (m_sting, ATCK_STING);
	  LOAD_FLAG (m_stun, ATCK_STUN);
	  LOAD_FLAG (m_tail, ATCK_TAIL);
	  LOAD_FLAG (m_trip, ATCK_TRIP);
	  LOAD_FLAG (m_weaken, ATCK_WEAKEN);

    }

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMobileAttacksPage)
	DDX_Check(pDX, IDC_ACIDBREATH, m_acidbreath);
	DDX_Check(pDX, IDC_BACKSTAB, m_backstab);
	DDX_Check(pDX, IDC_BASH, m_bash);
	DDX_Check(pDX, IDC_BITE, m_bite);
	DDX_Check(pDX, IDC_BLINDNESS, m_blindness);
	DDX_Check(pDX, IDC_CAUSECRITICAL, m_causecritical);
	DDX_Check(pDX, IDC_CAUSESERIOUS, m_causeserious);
	DDX_Check(pDX, IDC_CLAWS, m_claws);
	DDX_Check(pDX, IDC_COLORSPRAY, m_colorspray);
	DDX_Check(pDX, IDC_CURSE, m_curse);
	DDX_Check(pDX, IDC_DRAIN, m_drain);
	DDX_Check(pDX, IDC_EARTHQUAKE, m_earthquake);
	DDX_Check(pDX, IDC_FEED, m_feed);
	DDX_Check(pDX, IDC_FIREBALL, m_fireball);
	DDX_Check(pDX, IDC_FIREBREATH, m_firebreath);
	DDX_Check(pDX, IDC_FLAMESTRIKE, m_flamestrike);
	DDX_Check(pDX, IDC_FROSTBREATH, m_frostbreath);
	DDX_Check(pDX, IDC_GASBREATH, m_gasbreath);
	DDX_Check(pDX, IDC_GAZE, m_gaze);
	DDX_Check(pDX, IDC_GOUGE, m_gouge);
	DDX_Check(pDX, IDC_HARM, m_harm);
	DDX_Check(pDX, IDC_KICK, m_kick);
	DDX_Check(pDX, IDC_LIGHTNBREATH, m_lightnbreath);
	DDX_Check(pDX, IDC_NASTYPOISON, m_nastypoison);
	DDX_Check(pDX, IDC_POISON, m_poison);
	DDX_Check(pDX, IDC_PUNCH, m_punch);
	DDX_Check(pDX, IDC_SPIRALBLAST, m_spiralblast);
	DDX_Check(pDX, IDC_STING, m_sting);
	DDX_Check(pDX, IDC_STUN, m_stun);
	DDX_Check(pDX, IDC_TAIL, m_tail);
	DDX_Check(pDX, IDC_TRIP, m_trip);
	DDX_Check(pDX, IDC_WEAKEN, m_weaken);
	//}}AFX_DATA_MAP

  if (pDX->m_bSaveAndValidate)
    {
	  UNLOAD_FLAG (m_acidbreath, ATCK_ACIDBREATH);
	  UNLOAD_FLAG (m_backstab, ATCK_BACKSTAB);
	  UNLOAD_FLAG (m_bash, ATCK_BASH);
	  UNLOAD_FLAG (m_bite, ATCK_BITE);
	  UNLOAD_FLAG (m_blindness, ATCK_BLINDNESS);
	  UNLOAD_FLAG (m_causecritical, ATCK_CAUSECRITICAL);
	  UNLOAD_FLAG (m_causeserious, ATCK_CAUSESERIOUS);
	  UNLOAD_FLAG (m_claws, ATCK_CLAWS);
	  UNLOAD_FLAG (m_colorspray, ATCK_COLORSPRAY);
	  UNLOAD_FLAG (m_curse, ATCK_CURSE);
	  UNLOAD_FLAG (m_drain, ATCK_DRAIN);
	  UNLOAD_FLAG (m_earthquake, ATCK_EARTHQUAKE);
	  UNLOAD_FLAG (m_feed, ATCK_FEED);
	  UNLOAD_FLAG (m_fireball, ATCK_FIREBALL);
	  UNLOAD_FLAG (m_firebreath, ATCK_FIREBREATH);
	  UNLOAD_FLAG (m_flamestrike, ATCK_FLAMESTRIKE);
	  UNLOAD_FLAG (m_frostbreath, ATCK_FROSTBREATH);
	  UNLOAD_FLAG (m_gasbreath, ATCK_GASBREATH);
	  UNLOAD_FLAG (m_gaze, ATCK_GAZE);
	  UNLOAD_FLAG (m_gouge, ATCK_GOUGE);
	  UNLOAD_FLAG (m_harm, ATCK_HARM);
	  UNLOAD_FLAG (m_kick, ATCK_KICK);
	  UNLOAD_FLAG (m_lightnbreath, ATCK_LIGHTNBREATH);
	  UNLOAD_FLAG (m_nastypoison, ATCK_NASTYPOISON);
	  UNLOAD_FLAG (m_poison, ATCK_POISON);
	  UNLOAD_FLAG (m_punch, ATCK_PUNCH);
	  UNLOAD_FLAG (m_spiralblast, ATCK_SPIRALBLAST);
	  UNLOAD_FLAG (m_sting, ATCK_STING);
	  UNLOAD_FLAG (m_stun, ATCK_STUN);
	  UNLOAD_FLAG (m_tail, ATCK_TAIL);
	  UNLOAD_FLAG (m_trip, ATCK_TRIP);
	  UNLOAD_FLAG (m_weaken, ATCK_WEAKEN);

     if (bChanged)
       m_mob->m_pDoc->SetModifiedFlag ();
    }

}


BEGIN_MESSAGE_MAP(CMobileAttacksPage, CDialog)
	//{{AFX_MSG_MAP(CMobileAttacksPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMobileAttacksPage message handlers
