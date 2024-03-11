// MobileActionsPage.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "AreaEditorDoc.h"
#include "MobileActionsPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMobileActionsPage dialog


CMobileActionsPage::CMobileActionsPage(CWnd* pParent /*=NULL*/)
	: CDialog(CMobileActionsPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMobileActionsPage)
	m_bAggressive = FALSE;
	m_bDeadly = FALSE;
	m_bGuardian = FALSE;
	m_bImmortal = FALSE;
	m_bIsNPC = FALSE;
	m_bMetaAggr = FALSE;
	m_bMobInvis = FALSE;
	m_bMountable = FALSE;
	m_bMounted = FALSE;
	m_bNoAssist = FALSE;
	m_bNoWander = FALSE;
	m_bPet = FALSE;
	m_bPolymorphed = FALSE;
	m_bPolySelf = FALSE;
	m_bPractice = FALSE;
	m_bPrototype = FALSE;
	m_bRunning = FALSE;
	m_bScavenger = FALSE;
	m_bScholar = FALSE;
	m_bSecretive = FALSE;
	m_bSentinel = FALSE;
	m_bStayArea = FALSE;
	m_bTrain = FALSE;
	m_bWimpy = FALSE;
	//}}AFX_DATA_INIT

  m_mob = NULL;

}

#define LOAD_FLAG(field, flag)  \
  field = IS_SET (m_mob->act, flag);

#undef UNLOAD_FLAG
#define UNLOAD_FLAG(field, flag)  \
  if (field != IS_SET (m_mob->act, flag)) bChanged = true; \
  if (field)                      \
    SET_BIT (m_mob->act, flag);\
  else                            \
    REMOVE_BIT (m_mob->act, flag)

void CMobileActionsPage::DoDataExchange(CDataExchange* pDX)
{
bool bChanged = false;

  if (!pDX->m_bSaveAndValidate)
    {
	   LOAD_FLAG (m_bAggressive, ACT_AGGRESSIVE);
	   LOAD_FLAG (m_bDeadly, ACT_DEADLY);
	   LOAD_FLAG (m_bGuardian, ACT_GUARDIAN);
	   LOAD_FLAG (m_bImmortal, ACT_IMMORTAL);
	   LOAD_FLAG (m_bIsNPC, ACT_IS_NPC);
	   LOAD_FLAG (m_bMetaAggr, ACT_META_AGGR);
	   LOAD_FLAG (m_bMobInvis, ACT_MOBINVIS);
	   LOAD_FLAG (m_bMountable, ACT_MOUNTABLE);
	   LOAD_FLAG (m_bMounted, ACT_MOUNTED);
	   LOAD_FLAG (m_bNoAssist, ACT_NOASSIST);
	   LOAD_FLAG (m_bNoWander, ACT_NOWANDER);
	   LOAD_FLAG (m_bPet, ACT_PET);
	   LOAD_FLAG (m_bPolymorphed, ACT_POLYMORPHED);
	   LOAD_FLAG (m_bPolySelf, ACT_POLYSELF);
	   LOAD_FLAG (m_bPractice, ACT_PRACTICE);
	   LOAD_FLAG (m_bPrototype, ACT_PROTOTYPE);
	   LOAD_FLAG (m_bRunning, ACT_RUNNING);
	   LOAD_FLAG (m_bScavenger, ACT_SCAVENGER);
	   LOAD_FLAG (m_bScholar, ACT_SCHOLAR);
	   LOAD_FLAG (m_bSecretive, ACT_SECRETIVE);
	   LOAD_FLAG (m_bSentinel, ACT_SENTINEL);
	   LOAD_FLAG (m_bStayArea, ACT_STAY_AREA);
	   LOAD_FLAG (m_bTrain, ACT_TRAIN);
	   LOAD_FLAG (m_bWimpy, ACT_WIMPY);
    }

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMobileActionsPage)
	DDX_Check(pDX, IDC_ACT_AGGRESSIVE, m_bAggressive);
	DDX_Check(pDX, IDC_ACT_DEADLY, m_bDeadly);
	DDX_Check(pDX, IDC_ACT_GUARDIAN, m_bGuardian);
	DDX_Check(pDX, IDC_ACT_IMMORTAL, m_bImmortal);
	DDX_Check(pDX, IDC_ACT_IS_NPC, m_bIsNPC);
	DDX_Check(pDX, IDC_ACT_META_AGGR, m_bMetaAggr);
	DDX_Check(pDX, IDC_ACT_MOBINVIS, m_bMobInvis);
	DDX_Check(pDX, IDC_ACT_MOUNTABLE, m_bMountable);
	DDX_Check(pDX, IDC_ACT_MOUNTED, m_bMounted);
	DDX_Check(pDX, IDC_ACT_NOASSIST, m_bNoAssist);
	DDX_Check(pDX, IDC_ACT_NOWANDER, m_bNoWander);
	DDX_Check(pDX, IDC_ACT_PET, m_bPet);
	DDX_Check(pDX, IDC_ACT_POLYMORPHED, m_bPolymorphed);
	DDX_Check(pDX, IDC_ACT_POLYSELF, m_bPolySelf);
	DDX_Check(pDX, IDC_ACT_PRACTICE, m_bPractice);
	DDX_Check(pDX, IDC_ACT_PROTOTYPE, m_bPrototype);
	DDX_Check(pDX, IDC_ACT_RUNNING, m_bRunning);
	DDX_Check(pDX, IDC_ACT_SCAVENGER, m_bScavenger);
	DDX_Check(pDX, IDC_ACT_SCHOLAR, m_bScholar);
	DDX_Check(pDX, IDC_ACT_SECRETIVE, m_bSecretive);
	DDX_Check(pDX, IDC_ACT_SENTINEL, m_bSentinel);
	DDX_Check(pDX, IDC_ACT_STAY_AREA, m_bStayArea);
	DDX_Check(pDX, IDC_ACT_TRAIN, m_bTrain);
	DDX_Check(pDX, IDC_ACT_WIMPY, m_bWimpy);
	//}}AFX_DATA_MAP

  if (pDX->m_bSaveAndValidate)
    {
	   UNLOAD_FLAG (m_bAggressive, ACT_AGGRESSIVE);
	   UNLOAD_FLAG (m_bDeadly, ACT_DEADLY);
	   UNLOAD_FLAG (m_bGuardian, ACT_GUARDIAN);
	   UNLOAD_FLAG (m_bImmortal, ACT_IMMORTAL);
	   UNLOAD_FLAG (m_bIsNPC, ACT_IS_NPC);
	   UNLOAD_FLAG (m_bMetaAggr, ACT_META_AGGR);
	   UNLOAD_FLAG (m_bMobInvis, ACT_MOBINVIS);
	   UNLOAD_FLAG (m_bMountable, ACT_MOUNTABLE);
	   UNLOAD_FLAG (m_bMounted, ACT_MOUNTED);
	   UNLOAD_FLAG (m_bNoAssist, ACT_NOASSIST);
	   UNLOAD_FLAG (m_bNoWander, ACT_NOWANDER);
	   UNLOAD_FLAG (m_bPet, ACT_PET);
	   UNLOAD_FLAG (m_bPolymorphed, ACT_POLYMORPHED);
	   UNLOAD_FLAG (m_bPolySelf, ACT_POLYSELF);
	   UNLOAD_FLAG (m_bPractice, ACT_PRACTICE);
	   UNLOAD_FLAG (m_bPrototype, ACT_PROTOTYPE);
	   UNLOAD_FLAG (m_bRunning, ACT_RUNNING);
	   UNLOAD_FLAG (m_bScavenger, ACT_SCAVENGER);
	   UNLOAD_FLAG (m_bScholar, ACT_SCHOLAR);
	   UNLOAD_FLAG (m_bSecretive, ACT_SECRETIVE);
	   UNLOAD_FLAG (m_bSentinel, ACT_SENTINEL);
	   UNLOAD_FLAG (m_bStayArea, ACT_STAY_AREA);
	   UNLOAD_FLAG (m_bTrain, ACT_TRAIN);
	   UNLOAD_FLAG (m_bWimpy, ACT_WIMPY);

     if (bChanged)
       m_mob->m_pDoc->SetModifiedFlag ();

    }

}


BEGIN_MESSAGE_MAP(CMobileActionsPage, CDialog)
	//{{AFX_MSG_MAP(CMobileActionsPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMobileActionsPage message handlers

