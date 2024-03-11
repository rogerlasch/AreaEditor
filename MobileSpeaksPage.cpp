/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// MobileSpeaksPage.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "AreaEditorDoc.h"

#include "MobileSpeaksPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMobileSpeaksPage dialog


CMobileSpeaksPage::CMobileSpeaksPage(CWnd* pParent /*=NULL*/)
	: CDialog(CMobileSpeaksPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMobileSpeaksPage)
	m_ancient = FALSE;
	m_clan = FALSE;
	m_common = FALSE;
	m_dragon = FALSE;
	m_dwarven = FALSE;
	m_elven = FALSE;
	m_gith = FALSE;
	m_goblin = FALSE;
	m_god = FALSE;
	m_halfling = FALSE;
	m_insectoid = FALSE;
	m_magical = FALSE;
	m_mammal = FALSE;
	m_ogre = FALSE;
	m_orcish = FALSE;
	m_pixie = FALSE;
	m_reptile = FALSE;
	m_rodent = FALSE;
	m_spiritual = FALSE;
	m_trollish = FALSE;
	m_spk_ancient = FALSE;
	m_spk_clan = FALSE;
	m_spk_common = FALSE;
	m_spk_dragon = FALSE;
	m_spk_dwarven = FALSE;
	m_spk_elven = FALSE;
	m_spk_gith = FALSE;
	m_spk_goblin = FALSE;
	m_spk_god = FALSE;
	m_spk_halfling = FALSE;
	m_spk_insectoid = FALSE;
	m_spk_magical = FALSE;
	m_spk_mammal = FALSE;
	m_spk_ogre = FALSE;
	m_spk_orcish = FALSE;
	m_spk_pixie = FALSE;
	m_spk_reptile = FALSE;
	m_spk_rodent = FALSE;
	m_spk_spiritual = FALSE;
	m_spk_trollish = FALSE;
	//}}AFX_DATA_INIT

  m_mob = NULL;

}

#undef LOAD_SPEAKS_FLAG
#define LOAD_SPEAKS_FLAG(field, flag)  \
  field = IS_SET (m_mob->speaks, flag);

#undef LOAD_SPEAKING_FLAG
#define LOAD_SPEAKING_FLAG(field, flag)  \
  field = IS_SET (m_mob->speaking, flag);

#undef UNLOAD_SPEAKS_FLAG
#define UNLOAD_SPEAKS_FLAG(field, flag)  \
  if (field != IS_SET (m_mob->speaks, flag)) bChanged = true; \
  if (field)                      \
    SET_BIT (m_mob->speaks, flag);\
  else                            \
    REMOVE_BIT (m_mob->speaks, flag)

#undef UNLOAD_SPEAKING_FLAG
#define UNLOAD_SPEAKING_FLAG(field, flag)  \
  if (field != IS_SET (m_mob->speaking, flag)) bChanged = true; \
  if (field)                      \
    SET_BIT (m_mob->speaking, flag);\
  else                            \
    REMOVE_BIT (m_mob->speaking, flag)

void CMobileSpeaksPage::DoDataExchange(CDataExchange* pDX)
{
bool bChanged = false;

  if (!pDX->m_bSaveAndValidate)
    {
	  LOAD_SPEAKS_FLAG (m_spk_ancient, LANG_ANCIENT);
	  LOAD_SPEAKS_FLAG (m_spk_clan, LANG_CLAN);
	  LOAD_SPEAKS_FLAG (m_spk_common, LANG_COMMON);
	  LOAD_SPEAKS_FLAG (m_spk_dragon, LANG_DRAGON);
	  LOAD_SPEAKS_FLAG (m_spk_dwarven, LANG_DWARVEN);
	  LOAD_SPEAKS_FLAG (m_spk_elven, LANG_ELVEN);
	  LOAD_SPEAKS_FLAG (m_spk_gith, LANG_GITH);
	  LOAD_SPEAKS_FLAG (m_spk_goblin, LANG_GOBLIN);
	  LOAD_SPEAKS_FLAG (m_spk_god, LANG_GOD);
	  LOAD_SPEAKS_FLAG (m_spk_halfling, LANG_HALFLING);
	  LOAD_SPEAKS_FLAG (m_spk_insectoid, LANG_INSECTOID);
	  LOAD_SPEAKS_FLAG (m_spk_magical, LANG_MAGICAL);
	  LOAD_SPEAKS_FLAG (m_spk_mammal, LANG_MAMMAL);
	  LOAD_SPEAKS_FLAG (m_spk_ogre, LANG_OGRE);
	  LOAD_SPEAKS_FLAG (m_spk_orcish, LANG_ORCISH);
	  LOAD_SPEAKS_FLAG (m_spk_pixie, LANG_PIXIE);
	  LOAD_SPEAKS_FLAG (m_spk_reptile, LANG_REPTILE);
	  LOAD_SPEAKS_FLAG (m_spk_rodent, LANG_RODENT);
	  LOAD_SPEAKS_FLAG (m_spk_spiritual, LANG_SPIRITUAL);
	  LOAD_SPEAKS_FLAG (m_spk_trollish, LANG_TROLLISH);

	  LOAD_SPEAKING_FLAG (m_ancient, LANG_ANCIENT);
	  LOAD_SPEAKING_FLAG (m_clan, LANG_CLAN);
	  LOAD_SPEAKING_FLAG (m_common, LANG_COMMON);
	  LOAD_SPEAKING_FLAG (m_dragon, LANG_DRAGON);
	  LOAD_SPEAKING_FLAG (m_dwarven, LANG_DWARVEN);
	  LOAD_SPEAKING_FLAG (m_elven, LANG_ELVEN);
	  LOAD_SPEAKING_FLAG (m_gith, LANG_GITH);
	  LOAD_SPEAKING_FLAG (m_goblin, LANG_GOBLIN);
	  LOAD_SPEAKING_FLAG (m_god, LANG_GOD);
	  LOAD_SPEAKING_FLAG (m_halfling, LANG_HALFLING);
	  LOAD_SPEAKING_FLAG (m_insectoid, LANG_INSECTOID);
	  LOAD_SPEAKING_FLAG (m_magical, LANG_MAGICAL);
	  LOAD_SPEAKING_FLAG (m_mammal, LANG_MAMMAL);
	  LOAD_SPEAKING_FLAG (m_ogre, LANG_OGRE);
	  LOAD_SPEAKING_FLAG (m_orcish, LANG_ORCISH);
	  LOAD_SPEAKING_FLAG (m_pixie, LANG_PIXIE);
	  LOAD_SPEAKING_FLAG (m_reptile, LANG_REPTILE);
	  LOAD_SPEAKING_FLAG (m_rodent, LANG_RODENT);
	  LOAD_SPEAKING_FLAG (m_spiritual, LANG_SPIRITUAL);
	  LOAD_SPEAKING_FLAG (m_trollish, LANG_TROLLISH);

    }

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMobileSpeaksPage)
	DDX_Check(pDX, IDC_ANCIENT, m_ancient);
	DDX_Check(pDX, IDC_CLAN, m_clan);
	DDX_Check(pDX, IDC_COMMON, m_common);
	DDX_Check(pDX, IDC_DRAGON, m_dragon);
	DDX_Check(pDX, IDC_DWARVEN, m_dwarven);
	DDX_Check(pDX, IDC_ELVEN, m_elven);
	DDX_Check(pDX, IDC_GITH, m_gith);
	DDX_Check(pDX, IDC_GOBLIN, m_goblin);
	DDX_Check(pDX, IDC_GOD, m_god);
	DDX_Check(pDX, IDC_HALFLING, m_halfling);
	DDX_Check(pDX, IDC_INSECTOID, m_insectoid);
	DDX_Check(pDX, IDC_MAGICAL, m_magical);
	DDX_Check(pDX, IDC_MAMMAL, m_mammal);
	DDX_Check(pDX, IDC_OGRE, m_ogre);
	DDX_Check(pDX, IDC_ORCISH, m_orcish);
	DDX_Check(pDX, IDC_PIXIE, m_pixie);
	DDX_Check(pDX, IDC_REPTILE, m_reptile);
	DDX_Check(pDX, IDC_RODENT, m_rodent);
	DDX_Check(pDX, IDC_SPIRITUAL, m_spiritual);
	DDX_Check(pDX, IDC_TROLLISH, m_trollish);
	DDX_Check(pDX, IDC_ANCIENT2, m_spk_ancient);
	DDX_Check(pDX, IDC_CLAN2, m_spk_clan);
	DDX_Check(pDX, IDC_COMMON2, m_spk_common);
	DDX_Check(pDX, IDC_DRAGON2, m_spk_dragon);
	DDX_Check(pDX, IDC_DWARVEN2, m_spk_dwarven);
	DDX_Check(pDX, IDC_ELVEN2, m_spk_elven);
	DDX_Check(pDX, IDC_GITH2, m_spk_gith);
	DDX_Check(pDX, IDC_GOBLIN2, m_spk_goblin);
	DDX_Check(pDX, IDC_GOD2, m_spk_god);
	DDX_Check(pDX, IDC_HALFLING2, m_spk_halfling);
	DDX_Check(pDX, IDC_INSECTOID2, m_spk_insectoid);
	DDX_Check(pDX, IDC_MAGICAL2, m_spk_magical);
	DDX_Check(pDX, IDC_MAMMAL2, m_spk_mammal);
	DDX_Check(pDX, IDC_OGRE2, m_spk_ogre);
	DDX_Check(pDX, IDC_ORCISH2, m_spk_orcish);
	DDX_Check(pDX, IDC_PIXIE2, m_spk_pixie);
	DDX_Check(pDX, IDC_REPTILE2, m_spk_reptile);
	DDX_Check(pDX, IDC_RODENT2, m_spk_rodent);
	DDX_Check(pDX, IDC_SPIRITUAL2, m_spk_spiritual);
	DDX_Check(pDX, IDC_TROLLISH2, m_spk_trollish);
	//}}AFX_DATA_MAP

  if (pDX->m_bSaveAndValidate)
    {
	  UNLOAD_SPEAKS_FLAG (m_spk_ancient, LANG_ANCIENT);
	  UNLOAD_SPEAKS_FLAG (m_spk_clan, LANG_CLAN);
	  UNLOAD_SPEAKS_FLAG (m_spk_common, LANG_COMMON);
	  UNLOAD_SPEAKS_FLAG (m_spk_dragon, LANG_DRAGON);
	  UNLOAD_SPEAKS_FLAG (m_spk_dwarven, LANG_DWARVEN);
	  UNLOAD_SPEAKS_FLAG (m_spk_elven, LANG_ELVEN);
	  UNLOAD_SPEAKS_FLAG (m_spk_gith, LANG_GITH);
	  UNLOAD_SPEAKS_FLAG (m_spk_goblin, LANG_GOBLIN);
	  UNLOAD_SPEAKS_FLAG (m_spk_god, LANG_GOD);
	  UNLOAD_SPEAKS_FLAG (m_spk_halfling, LANG_HALFLING);
	  UNLOAD_SPEAKS_FLAG (m_spk_insectoid, LANG_INSECTOID);
	  UNLOAD_SPEAKS_FLAG (m_spk_magical, LANG_MAGICAL);
	  UNLOAD_SPEAKS_FLAG (m_spk_mammal, LANG_MAMMAL);
	  UNLOAD_SPEAKS_FLAG (m_spk_ogre, LANG_OGRE);
	  UNLOAD_SPEAKS_FLAG (m_spk_orcish, LANG_ORCISH);
	  UNLOAD_SPEAKS_FLAG (m_spk_pixie, LANG_PIXIE);
	  UNLOAD_SPEAKS_FLAG (m_spk_reptile, LANG_REPTILE);
	  UNLOAD_SPEAKS_FLAG (m_spk_rodent, LANG_RODENT);
	  UNLOAD_SPEAKS_FLAG (m_spk_spiritual, LANG_SPIRITUAL);
	  UNLOAD_SPEAKS_FLAG (m_spk_trollish, LANG_TROLLISH);

	  UNLOAD_SPEAKING_FLAG (m_ancient, LANG_ANCIENT);
	  UNLOAD_SPEAKING_FLAG (m_clan, LANG_CLAN);
	  UNLOAD_SPEAKING_FLAG (m_common, LANG_COMMON);
	  UNLOAD_SPEAKING_FLAG (m_dragon, LANG_DRAGON);
	  UNLOAD_SPEAKING_FLAG (m_dwarven, LANG_DWARVEN);
	  UNLOAD_SPEAKING_FLAG (m_elven, LANG_ELVEN);
	  UNLOAD_SPEAKING_FLAG (m_gith, LANG_GITH);
	  UNLOAD_SPEAKING_FLAG (m_goblin, LANG_GOBLIN);
	  UNLOAD_SPEAKING_FLAG (m_god, LANG_GOD);
	  UNLOAD_SPEAKING_FLAG (m_halfling, LANG_HALFLING);
	  UNLOAD_SPEAKING_FLAG (m_insectoid, LANG_INSECTOID);
	  UNLOAD_SPEAKING_FLAG (m_magical, LANG_MAGICAL);
	  UNLOAD_SPEAKING_FLAG (m_mammal, LANG_MAMMAL);
	  UNLOAD_SPEAKING_FLAG (m_ogre, LANG_OGRE);
	  UNLOAD_SPEAKING_FLAG (m_orcish, LANG_ORCISH);
	  UNLOAD_SPEAKING_FLAG (m_pixie, LANG_PIXIE);
	  UNLOAD_SPEAKING_FLAG (m_reptile, LANG_REPTILE);
	  UNLOAD_SPEAKING_FLAG (m_rodent, LANG_RODENT);
	  UNLOAD_SPEAKING_FLAG (m_spiritual, LANG_SPIRITUAL);
	  UNLOAD_SPEAKING_FLAG (m_trollish, LANG_TROLLISH);

     if (bChanged)
       m_mob->m_pDoc->SetModifiedFlag ();
    }


}


BEGIN_MESSAGE_MAP(CMobileSpeaksPage, CDialog)
	//{{AFX_MSG_MAP(CMobileSpeaksPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMobileSpeaksPage message handlers
