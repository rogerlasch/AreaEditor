/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// MobileDefensesPage.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "AreaEditorDoc.h"

#include "MobileDefensesPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMobileDefensesPage dialog


CMobileDefensesPage::CMobileDefensesPage(CWnd* pParent /*=NULL*/)
	: CDialog(CMobileDefensesPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMobileDefensesPage)
	m_bless = FALSE;
	m_curecritical = FALSE;
	m_curelight = FALSE;
	m_cureserious = FALSE;
	m_disarm = FALSE;
	m_dispelevil = FALSE;
	m_dispelmagic = FALSE;
	m_dodge = FALSE;
	m_fireshield = FALSE;
	m_grip = FALSE;
	m_heal = FALSE;
	m_iceshield = FALSE;
	m_monsum1 = FALSE;
	m_monsum2 = FALSE;
	m_monsum4 = FALSE;
	m_monsum3 = FALSE;
	m_parry = FALSE;
	m_sanctuary = FALSE;
	m_shield = FALSE;
	m_shockshield = FALSE;
	m_stoneskin = FALSE;
	m_teleport = FALSE;
	//}}AFX_DATA_INIT

  m_mob = NULL;

}

#undef LOAD_FLAG
#define LOAD_FLAG(field, flag)  \
  field = IS_SET (m_mob->defenses, flag);

#undef UNLOAD_FLAG
#define UNLOAD_FLAG(field, flag)  \
  if (field != IS_SET (m_mob->defenses, flag)) bChanged = true; \
  if (field)                      \
    SET_BIT (m_mob->defenses, flag);\
  else                            \
    REMOVE_BIT (m_mob->defenses, flag)

void CMobileDefensesPage::DoDataExchange(CDataExchange* pDX)
{
bool bChanged = false;

  if (!pDX->m_bSaveAndValidate)
    {
	  LOAD_FLAG (m_bless, DFND_BLESS);
	  LOAD_FLAG (m_curecritical, DFND_CURECRITICAL);
	  LOAD_FLAG (m_curelight, DFND_CURELIGHT);
	  LOAD_FLAG (m_cureserious, DFND_CURESERIOUS);
	  LOAD_FLAG (m_disarm, DFND_DISARM);
	  LOAD_FLAG (m_dispelevil, DFND_DISPELEVIL);
	  LOAD_FLAG (m_dispelmagic, DFND_DISPELMAGIC);
	  LOAD_FLAG (m_dodge, DFND_DODGE);
	  LOAD_FLAG (m_fireshield, DFND_FIRESHIELD);
	  LOAD_FLAG (m_grip, DFND_GRIP);
	  LOAD_FLAG (m_heal, DFND_HEAL);
	  LOAD_FLAG (m_iceshield, DFND_ICESHIELD);
	  LOAD_FLAG (m_monsum1, DFND_MONSUM1);
	  LOAD_FLAG (m_monsum2, DFND_MONSUM2);
	  LOAD_FLAG (m_monsum4, DFND_MONSUM4);
	  LOAD_FLAG (m_monsum3, DFND_MONSUM3);
	  LOAD_FLAG (m_parry, DFND_PARRY);
	  LOAD_FLAG (m_sanctuary, DFND_SANCTUARY);
	  LOAD_FLAG (m_shield, DFND_SHIELD);
	  LOAD_FLAG (m_shockshield, DFND_SHOCKSHIELD);
	  LOAD_FLAG (m_stoneskin, DFND_STONESKIN);
	  LOAD_FLAG (m_teleport, DFND_TELEPORT);

    }


	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMobileDefensesPage)
	DDX_Check(pDX, IDC_BLESS, m_bless);
	DDX_Check(pDX, IDC_CURECRITICAL, m_curecritical);
	DDX_Check(pDX, IDC_CURELIGHT, m_curelight);
	DDX_Check(pDX, IDC_CURESERIOUS, m_cureserious);
	DDX_Check(pDX, IDC_DISARM, m_disarm);
	DDX_Check(pDX, IDC_DISPELEVIL, m_dispelevil);
	DDX_Check(pDX, IDC_DISPELMAGIC, m_dispelmagic);
	DDX_Check(pDX, IDC_DODGE, m_dodge);
	DDX_Check(pDX, IDC_FIRESHIELD, m_fireshield);
	DDX_Check(pDX, IDC_GRIP, m_grip);
	DDX_Check(pDX, IDC_HEAL, m_heal);
	DDX_Check(pDX, IDC_ICESHIELD, m_iceshield);
	DDX_Check(pDX, IDC_MONSUM1, m_monsum1);
	DDX_Check(pDX, IDC_MONSUM2, m_monsum2);
	DDX_Check(pDX, IDC_MONSUM4, m_monsum4);
	DDX_Check(pDX, IDC_MONSUM3, m_monsum3);
	DDX_Check(pDX, IDC_PARRY, m_parry);
	DDX_Check(pDX, IDC_SANCTUARY, m_sanctuary);
	DDX_Check(pDX, IDC_SHIELD, m_shield);
	DDX_Check(pDX, IDC_SHOCKSHIELD, m_shockshield);
	DDX_Check(pDX, IDC_STONESKIN, m_stoneskin);
	DDX_Check(pDX, IDC_TELEPORT, m_teleport);
	//}}AFX_DATA_MAP

  if (pDX->m_bSaveAndValidate)
    {
	  UNLOAD_FLAG (m_bless, DFND_BLESS);
	  UNLOAD_FLAG (m_curecritical, DFND_CURECRITICAL);
	  UNLOAD_FLAG (m_curelight, DFND_CURELIGHT);
	  UNLOAD_FLAG (m_cureserious, DFND_CURESERIOUS);
	  UNLOAD_FLAG (m_disarm, DFND_DISARM);
	  UNLOAD_FLAG (m_dispelevil, DFND_DISPELEVIL);
	  UNLOAD_FLAG (m_dispelmagic, DFND_DISPELMAGIC);
	  UNLOAD_FLAG (m_dodge, DFND_DODGE);
	  UNLOAD_FLAG (m_fireshield, DFND_FIRESHIELD);
	  UNLOAD_FLAG (m_grip, DFND_GRIP);
	  UNLOAD_FLAG (m_heal, DFND_HEAL);
	  UNLOAD_FLAG (m_iceshield, DFND_ICESHIELD);
	  UNLOAD_FLAG (m_monsum1, DFND_MONSUM1);
	  UNLOAD_FLAG (m_monsum2, DFND_MONSUM2);
	  UNLOAD_FLAG (m_monsum4, DFND_MONSUM4);
	  UNLOAD_FLAG (m_monsum3, DFND_MONSUM3);
	  UNLOAD_FLAG (m_parry, DFND_PARRY);
	  UNLOAD_FLAG (m_sanctuary, DFND_SANCTUARY);
	  UNLOAD_FLAG (m_shield, DFND_SHIELD);
	  UNLOAD_FLAG (m_shockshield, DFND_SHOCKSHIELD);
	  UNLOAD_FLAG (m_stoneskin, DFND_STONESKIN);
	  UNLOAD_FLAG (m_teleport, DFND_TELEPORT);

     if (bChanged)
       m_mob->m_pDoc->SetModifiedFlag ();
    }

}


BEGIN_MESSAGE_MAP(CMobileDefensesPage, CDialog)
	//{{AFX_MSG_MAP(CMobileDefensesPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMobileDefensesPage message handlers
