/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// RoomFlagsPage.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "AreaEditorDoc.h"

#include "RoomFlagsPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRoomFlagsPage dialog


CRoomFlagsPage::CRoomFlagsPage(CWnd* pParent /*=NULL*/)
	: CDialog(CRoomFlagsPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRoomFlagsPage)
	m_chaotic = FALSE;
	m_clanstoreroom = FALSE;
	m_dark = FALSE;
	m_death = FALSE;
	m_donation = FALSE;
	m_indoors = FALSE;
	m_lawful = FALSE;
	m_logspeech = FALSE;
	m_neutral = FALSE;
	m_no_astral = FALSE;
	m_no_magic = FALSE;
	m_no_mob = FALSE;
	m_no_recall = FALSE;
	m_no_summon = FALSE;
	m_nodrop = FALSE;
	m_nodropall = FALSE;
	m_nofloor = FALSE;
	m_pet_shop = FALSE;
	m_private = FALSE;
	m_prototype = FALSE;
	m_safe = FALSE;
	m_silence = FALSE;
	m_solitary = FALSE;
	m_teleport = FALSE;
	m_teleshowdesc = FALSE;
	m_tunnel = FALSE;
	//}}AFX_DATA_INIT

  m_room = NULL;

}

#undef LOAD_FLAG
#define LOAD_FLAG(field, flag)  \
  field = IS_SET (m_room->room_flags, flag);

#undef UNLOAD_FLAG
#define UNLOAD_FLAG(field, flag)  \
  if (field != IS_SET (m_room->room_flags, flag)) bChanged = true; \
  if (field)                      \
    SET_BIT (m_room->room_flags, flag);\
  else                            \
    REMOVE_BIT (m_room->room_flags, flag)

void CRoomFlagsPage::DoDataExchange(CDataExchange* pDX)
{
bool bChanged = false;

  if (!pDX->m_bSaveAndValidate)
    {
	  LOAD_FLAG (m_chaotic, ROOM_CHAOTIC);
	  LOAD_FLAG (m_clanstoreroom, ROOM_CLANSTOREROOM);
	  LOAD_FLAG (m_dark, ROOM_DARK);
	  LOAD_FLAG (m_death, ROOM_DEATH);
	  LOAD_FLAG (m_donation, ROOM_DONATION);
	  LOAD_FLAG (m_indoors, ROOM_INDOORS);
	  LOAD_FLAG (m_lawful, ROOM_LAWFUL);
	  LOAD_FLAG (m_logspeech, ROOM_LOGSPEECH);
	  LOAD_FLAG (m_neutral, ROOM_NEUTRAL);
	  LOAD_FLAG (m_no_astral, ROOM_NO_ASTRAL);
	  LOAD_FLAG (m_no_magic, ROOM_NO_MAGIC);
	  LOAD_FLAG (m_no_mob, ROOM_NO_MOB);
	  LOAD_FLAG (m_no_recall, ROOM_NO_RECALL);
	  LOAD_FLAG (m_no_summon, ROOM_NO_SUMMON);
	  LOAD_FLAG (m_nodrop, ROOM_NODROP);
	  LOAD_FLAG (m_nodropall, ROOM_NODROPALL);
	  LOAD_FLAG (m_nofloor, ROOM_NOFLOOR);
	  LOAD_FLAG (m_pet_shop, ROOM_PET_SHOP);
	  LOAD_FLAG (m_private, ROOM_PRIVATE);
	  LOAD_FLAG (m_prototype, ROOM_PROTOTYPE);
	  LOAD_FLAG (m_safe, ROOM_SAFE);
	  LOAD_FLAG (m_silence, ROOM_SILENCE);
	  LOAD_FLAG (m_solitary, ROOM_SOLITARY);
	  LOAD_FLAG (m_teleport, ROOM_TELEPORT);
	  LOAD_FLAG (m_teleshowdesc, ROOM_TELESHOWDESC);
	  LOAD_FLAG (m_tunnel, ROOM_TUNNEL);
    }

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRoomFlagsPage)
	DDX_Check(pDX, IDC_CHAOTIC, m_chaotic);
	DDX_Check(pDX, IDC_CLANSTOREROOM, m_clanstoreroom);
	DDX_Check(pDX, IDC_DARK, m_dark);
	DDX_Check(pDX, IDC_DEATH, m_death);
	DDX_Check(pDX, IDC_DONATION, m_donation);
	DDX_Check(pDX, IDC_INDOORS, m_indoors);
	DDX_Check(pDX, IDC_LAWFUL, m_lawful);
	DDX_Check(pDX, IDC_LOGSPEECH, m_logspeech);
	DDX_Check(pDX, IDC_NEUTRAL, m_neutral);
	DDX_Check(pDX, IDC_NO_ASTRAL, m_no_astral);
	DDX_Check(pDX, IDC_NO_MAGIC, m_no_magic);
	DDX_Check(pDX, IDC_NO_MOB, m_no_mob);
	DDX_Check(pDX, IDC_NO_RECALL, m_no_recall);
	DDX_Check(pDX, IDC_NO_SUMMON, m_no_summon);
	DDX_Check(pDX, IDC_NODROP, m_nodrop);
	DDX_Check(pDX, IDC_NODROPALL, m_nodropall);
	DDX_Check(pDX, IDC_NOFLOOR, m_nofloor);
	DDX_Check(pDX, IDC_PET_SHOP, m_pet_shop);
	DDX_Check(pDX, IDC_PRIVATE, m_private);
	DDX_Check(pDX, IDC_PROTOTYPE, m_prototype);
	DDX_Check(pDX, IDC_SAFE, m_safe);
	DDX_Check(pDX, IDC_SILENCE, m_silence);
	DDX_Check(pDX, IDC_SOLITARY, m_solitary);
	DDX_Check(pDX, IDC_TELEPORT, m_teleport);
	DDX_Check(pDX, IDC_TELESHOWDESC, m_teleshowdesc);
	DDX_Check(pDX, IDC_TUNNEL, m_tunnel);
	//}}AFX_DATA_MAP

  if (pDX->m_bSaveAndValidate)
    {
	  UNLOAD_FLAG (m_chaotic, ROOM_CHAOTIC);
	  UNLOAD_FLAG (m_clanstoreroom, ROOM_CLANSTOREROOM);
	  UNLOAD_FLAG (m_dark, ROOM_DARK);
	  UNLOAD_FLAG (m_death, ROOM_DEATH);
	  UNLOAD_FLAG (m_donation, ROOM_DONATION);
	  UNLOAD_FLAG (m_indoors, ROOM_INDOORS);
	  UNLOAD_FLAG (m_lawful, ROOM_LAWFUL);
	  UNLOAD_FLAG (m_logspeech, ROOM_LOGSPEECH);
	  UNLOAD_FLAG (m_neutral, ROOM_NEUTRAL);
	  UNLOAD_FLAG (m_no_astral, ROOM_NO_ASTRAL);
	  UNLOAD_FLAG (m_no_magic, ROOM_NO_MAGIC);
	  UNLOAD_FLAG (m_no_mob, ROOM_NO_MOB);
	  UNLOAD_FLAG (m_no_recall, ROOM_NO_RECALL);
	  UNLOAD_FLAG (m_no_summon, ROOM_NO_SUMMON);
	  UNLOAD_FLAG (m_nodrop, ROOM_NODROP);
	  UNLOAD_FLAG (m_nodropall, ROOM_NODROPALL);
	  UNLOAD_FLAG (m_nofloor, ROOM_NOFLOOR);
	  UNLOAD_FLAG (m_pet_shop, ROOM_PET_SHOP);
	  UNLOAD_FLAG (m_private, ROOM_PRIVATE);
	  UNLOAD_FLAG (m_prototype, ROOM_PROTOTYPE);
	  UNLOAD_FLAG (m_safe, ROOM_SAFE);
	  UNLOAD_FLAG (m_silence, ROOM_SILENCE);
	  UNLOAD_FLAG (m_solitary, ROOM_SOLITARY);
	  UNLOAD_FLAG (m_teleport, ROOM_TELEPORT);
	  UNLOAD_FLAG (m_teleshowdesc, ROOM_TELESHOWDESC);
	  UNLOAD_FLAG (m_tunnel, ROOM_TUNNEL);
     if (bChanged)
       m_room->m_pDoc->SetModifiedFlag ();
    }

}


BEGIN_MESSAGE_MAP(CRoomFlagsPage, CDialog)
	//{{AFX_MSG_MAP(CRoomFlagsPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRoomFlagsPage message handlers
