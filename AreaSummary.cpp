/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// AreaSummary.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "AreaSummary.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAreaSummary dialog


CAreaSummary::CAreaSummary(CWnd* pParent /*=NULL*/)
	: CDialog(CAreaSummary::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAreaSummary)
	m_helps = 0;
	m_mobiles = 0;
	m_objects = 0;
	m_repairs = 0;
	m_resets = 0;
	m_rooms = 0;
	m_shops = 0;
	m_mobile_programs = 0;
	m_object_affects = 0;
	m_object_programs = 0;
	m_room_programs = 0;
	m_room_exits = 0;
	//}}AFX_DATA_INIT
}


void CAreaSummary::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAreaSummary)
	DDX_Text(pDX, IDC_HELPS, m_helps);
	DDX_Text(pDX, IDC_MOBILES, m_mobiles);
	DDX_Text(pDX, IDC_OBJECTS, m_objects);
	DDX_Text(pDX, IDC_REPAIRS, m_repairs);
	DDX_Text(pDX, IDC_RESETS, m_resets);
	DDX_Text(pDX, IDC_ROOMS, m_rooms);
	DDX_Text(pDX, IDC_SHOPS, m_shops);
	DDX_Text(pDX, IDC_MOBILE_PROGRAMS, m_mobile_programs);
	DDX_Text(pDX, IDC_OBJECT_AFFECTS, m_object_affects);
	DDX_Text(pDX, IDC_OBJECT_PROGRAMS, m_object_programs);
	DDX_Text(pDX, IDC_ROOM_PROGRAMS, m_room_programs);
	DDX_Text(pDX, IDC_ROOM_EXITS, m_room_exits);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAreaSummary, CDialog)
	//{{AFX_MSG_MAP(CAreaSummary)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAreaSummary message handlers
