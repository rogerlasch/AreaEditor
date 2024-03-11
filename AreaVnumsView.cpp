/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// AreaVnumsView.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "AreaEditorDoc.h"
#include "defaults.h"

#include "AreaVnumsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAreaVnumsView dialog


CAreaVnumsView::CAreaVnumsView(CWnd* pParent /*=NULL*/)
	: CDialog(CAreaVnumsView::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAreaVnumsView)
	m_mob_hi_vnum = 0;
	m_mob_low_vnum = 0;
	m_obj_hi_vnum = 0;
	m_obj_low_vnum = 0;
	m_room_hi_vnum = 0;
	m_room_low_vnum = 0;
	//}}AFX_DATA_INIT

  m_area = NULL;

}

#undef LOAD_VALUE
#define LOAD_VALUE(field, value)  \
  field = m_area->value

#undef UNLOAD_VALUE
#define UNLOAD_VALUE(field, value)  \
  if (field != m_area->value) bChanged = true; \
  m_area->value = field

void CAreaVnumsView::DoDataExchange(CDataExchange* pDX)
{

bool bChanged = false;

  if (!pDX->m_bSaveAndValidate && m_area)
    {
	  LOAD_VALUE (m_mob_hi_vnum,  mob_hi_vnum);
	  LOAD_VALUE (m_mob_low_vnum, mob_low_vnum);
	  LOAD_VALUE (m_obj_hi_vnum,  obj_hi_vnum);
	  LOAD_VALUE (m_obj_low_vnum, obj_low_vnum);
	  LOAD_VALUE (m_room_hi_vnum, room_hi_vnum);
	  LOAD_VALUE (m_room_low_vnum,room_low_vnum);
    }

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAreaVnumsView)
	//}}AFX_DATA_MAP

  //vnums
	DDX_Text(pDX, IDC_MOB_HIGH_VNUM, m_mob_hi_vnum);
	DDV_MinMaxInt(pDX, m_mob_hi_vnum, 1, iMaxVnum);
	DDX_Text(pDX, IDC_MOB_LOW_VNUM, m_mob_low_vnum);
	DDV_MinMaxInt(pDX, m_mob_low_vnum, 1, iMaxVnum);
	DDX_Text(pDX, IDC_OBJ_HIGH_VNUM, m_obj_hi_vnum);
	DDV_MinMaxInt(pDX, m_obj_hi_vnum, 1, iMaxVnum);
	DDX_Text(pDX, IDC_OBJ_LOW_VNUM, m_obj_low_vnum);
	DDV_MinMaxInt(pDX, m_obj_low_vnum, 1, iMaxVnum);
	DDX_Text(pDX, IDC_ROOM_HIGH_VNUM, m_room_hi_vnum);
	DDV_MinMaxInt(pDX, m_room_hi_vnum, 1, iMaxVnum);
	DDX_Text(pDX, IDC_ROOM_LOW_VNUM, m_room_low_vnum);
	DDV_MinMaxInt(pDX, m_room_low_vnum, 1, iMaxVnum);

  // put stuff back
  if (pDX->m_bSaveAndValidate && m_area)
    {
	  UNLOAD_VALUE (m_mob_hi_vnum,  mob_hi_vnum);
	  UNLOAD_VALUE (m_mob_low_vnum, mob_low_vnum);
	  UNLOAD_VALUE (m_obj_hi_vnum,  obj_hi_vnum);
	  UNLOAD_VALUE (m_obj_low_vnum, obj_low_vnum);
	  UNLOAD_VALUE (m_room_hi_vnum, room_hi_vnum);
	  UNLOAD_VALUE (m_room_low_vnum,room_low_vnum);
     if (bChanged)
       m_area->m_pDoc->SetModifiedFlag ();
    }

}


BEGIN_MESSAGE_MAP(CAreaVnumsView, CDialog)
	//{{AFX_MSG_MAP(CAreaVnumsView)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAreaVnumsView message handlers
