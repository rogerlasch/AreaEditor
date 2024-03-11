/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// MobileBodyPartsPage.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "AreaEditorDoc.h"

#include "MobileBodyPartsPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMobileBodyPartsPage dialog


CMobileBodyPartsPage::CMobileBodyPartsPage(CWnd* pParent /*=NULL*/)
	: CDialog(CMobileBodyPartsPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMobileBodyPartsPage)
	m_arms = FALSE;
	m_beak = FALSE;
	m_brains = FALSE;
	m_claws = FALSE;
	m_ear = FALSE;
	m_eye = FALSE;
	m_eyestalks = FALSE;
	m_fangs = FALSE;
	m_feathers = FALSE;
	m_feet = FALSE;
	m_fins = FALSE;
	m_fingers = FALSE;
	m_forelegs = FALSE;
	m_guts = FALSE;
	m_hands = FALSE;
	m_haunch = FALSE;
	m_head = FALSE;
	m_heart = FALSE;
	m_horns = FALSE;
	m_legs = FALSE;
	m_paws = FALSE;
	m_scales = FALSE;
	m_sharpscales = FALSE;
	m_tail = FALSE;
	m_tailattack = FALSE;
	m_tentacles = FALSE;
	m_tusks = FALSE;
	m_wings = FALSE;
	m_hooves = FALSE;
	m_long_tongue = FALSE;
	//}}AFX_DATA_INIT

  m_mob = NULL;

}

#undef LOAD_FLAG
#define LOAD_FLAG(field, flag)  \
  field = IS_SET (m_mob->xflags, flag);

#undef UNLOAD_FLAG
#define UNLOAD_FLAG(field, flag)  \
  if (field != IS_SET (m_mob->xflags, flag)) bChanged = true; \
  if (field)                      \
    SET_BIT (m_mob->xflags, flag);\
  else                            \
    REMOVE_BIT (m_mob->xflags, flag)

void CMobileBodyPartsPage::DoDataExchange(CDataExchange* pDX)
{
bool bChanged = false;

  if (!pDX->m_bSaveAndValidate)
    {
	  LOAD_FLAG (m_arms, PART_ARMS);
	  LOAD_FLAG (m_beak, PART_BEAK);
	  LOAD_FLAG (m_brains, PART_BRAINS);
	  LOAD_FLAG (m_claws, PART_CLAWS);
	  LOAD_FLAG (m_ear, PART_EAR);
	  LOAD_FLAG (m_eye, PART_EYE);
	  LOAD_FLAG (m_eyestalks, PART_EYESTALKS);
	  LOAD_FLAG (m_fangs, PART_FANGS);
	  LOAD_FLAG (m_feathers, PART_FEATHERS);
	  LOAD_FLAG (m_feet, PART_FEET);
	  LOAD_FLAG (m_fins, PART_FINS);
	  LOAD_FLAG (m_fingers, PART_FINGERS);
	  LOAD_FLAG (m_forelegs, PART_FORELEGS);
	  LOAD_FLAG (m_guts, PART_GUTS);
	  LOAD_FLAG (m_hands, PART_HANDS);
	  LOAD_FLAG (m_haunch, PART_HAUNCH);
	  LOAD_FLAG (m_head, PART_HEAD);
	  LOAD_FLAG (m_hooves, PART_HOOVES);
	  LOAD_FLAG (m_heart, PART_HEART);
	  LOAD_FLAG (m_horns, PART_HORNS);
	  LOAD_FLAG (m_legs, PART_LEGS);
	  LOAD_FLAG (m_long_tongue, PART_LONG_TONGUE);
	  LOAD_FLAG (m_paws, PART_PAWS);
	  LOAD_FLAG (m_scales, PART_SCALES);
	  LOAD_FLAG (m_sharpscales, PART_SHARPSCALES);
	  LOAD_FLAG (m_tail, PART_TAIL);
	  LOAD_FLAG (m_tailattack, PART_TAILATTACK);
	  LOAD_FLAG (m_tentacles, PART_TENTACLES);
	  LOAD_FLAG (m_tusks, PART_TUSKS);
	  LOAD_FLAG (m_wings, PART_WINGS);

    }

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMobileBodyPartsPage)
	DDX_Check(pDX, IDC_ARMS, m_arms);
	DDX_Check(pDX, IDC_BEAK, m_beak);
	DDX_Check(pDX, IDC_BRAINS, m_brains);
	DDX_Check(pDX, IDC_CLAWS, m_claws);
	DDX_Check(pDX, IDC_EAR, m_ear);
	DDX_Check(pDX, IDC_EYE, m_eye);
	DDX_Check(pDX, IDC_EYESTALKS, m_eyestalks);
	DDX_Check(pDX, IDC_FANGS, m_fangs);
	DDX_Check(pDX, IDC_FEATHERS, m_feathers);
	DDX_Check(pDX, IDC_FEET, m_feet);
	DDX_Check(pDX, IDC_FINS, m_fins);
	DDX_Check(pDX, IDC_FINGERS, m_fingers);
	DDX_Check(pDX, IDC_FORELEGS, m_forelegs);
	DDX_Check(pDX, IDC_GUTS, m_guts);
	DDX_Check(pDX, IDC_HANDS, m_hands);
	DDX_Check(pDX, IDC_HAUNCH, m_haunch);
	DDX_Check(pDX, IDC_HEAD, m_head);
	DDX_Check(pDX, IDC_HEART, m_heart);
	DDX_Check(pDX, IDC_HORNS, m_horns);
	DDX_Check(pDX, IDC_LEGS, m_legs);
	DDX_Check(pDX, IDC_PAWS, m_paws);
	DDX_Check(pDX, IDC_SCALES, m_scales);
	DDX_Check(pDX, IDC_SHARPSCALES, m_sharpscales);
	DDX_Check(pDX, IDC_TAIL, m_tail);
	DDX_Check(pDX, IDC_TAILATTACK, m_tailattack);
	DDX_Check(pDX, IDC_TENTACLES, m_tentacles);
	DDX_Check(pDX, IDC_TUSKS, m_tusks);
	DDX_Check(pDX, IDC_WINGS, m_wings);
	DDX_Check(pDX, IDC_HOOVES, m_hooves);
	DDX_Check(pDX, IDC_LONG_TONGUE, m_long_tongue);
	//}}AFX_DATA_MAP

  if (pDX->m_bSaveAndValidate)
    {
	  UNLOAD_FLAG (m_arms, PART_ARMS);
	  UNLOAD_FLAG (m_beak, PART_BEAK);
	  UNLOAD_FLAG (m_brains, PART_BRAINS);
	  UNLOAD_FLAG (m_claws, PART_CLAWS);
	  UNLOAD_FLAG (m_ear, PART_EAR);
	  UNLOAD_FLAG (m_eye, PART_EYE);
	  UNLOAD_FLAG (m_eyestalks, PART_EYESTALKS);
	  UNLOAD_FLAG (m_fangs, PART_FANGS);
	  UNLOAD_FLAG (m_feathers, PART_FEATHERS);
	  UNLOAD_FLAG (m_feet, PART_FEET);
	  UNLOAD_FLAG (m_fins, PART_FINS);
	  UNLOAD_FLAG (m_fingers, PART_FINGERS);
	  UNLOAD_FLAG (m_forelegs, PART_FORELEGS);
	  UNLOAD_FLAG (m_guts, PART_GUTS);
	  UNLOAD_FLAG (m_hands, PART_HANDS);
	  UNLOAD_FLAG (m_haunch, PART_HAUNCH);
	  UNLOAD_FLAG (m_head, PART_HEAD);
	  UNLOAD_FLAG (m_hooves, PART_HOOVES);
	  UNLOAD_FLAG (m_heart, PART_HEART);
	  UNLOAD_FLAG (m_horns, PART_HORNS);
	  UNLOAD_FLAG (m_legs, PART_LEGS);
	  UNLOAD_FLAG (m_long_tongue, PART_LONG_TONGUE);
	  UNLOAD_FLAG (m_paws, PART_PAWS);
	  UNLOAD_FLAG (m_scales, PART_SCALES);
	  UNLOAD_FLAG (m_sharpscales, PART_SHARPSCALES);
	  UNLOAD_FLAG (m_tail, PART_TAIL);
	  UNLOAD_FLAG (m_tailattack, PART_TAILATTACK);
	  UNLOAD_FLAG (m_tentacles, PART_TENTACLES);
	  UNLOAD_FLAG (m_tusks, PART_TUSKS);
	  UNLOAD_FLAG (m_wings, PART_WINGS);

     if (bChanged)
       m_mob->m_pDoc->SetModifiedFlag ();
    }

}


BEGIN_MESSAGE_MAP(CMobileBodyPartsPage, CDialog)
	//{{AFX_MSG_MAP(CMobileBodyPartsPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMobileBodyPartsPage message handlers
