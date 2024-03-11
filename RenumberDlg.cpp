/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// RenumberDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "RenumberDlg.h"
#include "defaults.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRenumberDlg dialog


CRenumberDlg::CRenumberDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRenumberDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRenumberDlg)
	m_bMobCompact = FALSE;
	m_iMobCount = 0;
	m_iMobHighVnum = 0;
	m_iMobLowVnum = 0;
	m_iNewHighMobVnum = 0;
	m_iNewHighObjVnum = 0;
	m_iNewHighRoomVnum = 0;
	m_iNewLowMobVnum = 0;
	m_iNewLowObjVnum = 0;
	m_iNewLowRoomVnum = 0;
	m_bObjCompact = FALSE;
	m_iObjCount = 0;
	m_iObjHighVnum = 0;
	m_iObjLowVnum = 0;
	m_bRoomCompact = FALSE;
	m_iRoomCount = 0;
	m_iRoomHighVnum = 0;
	m_iRoomLowVnum = 0;
	//}}AFX_DATA_INIT
}


void CRenumberDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRenumberDlg)
	DDX_Control(pDX, IDC_NEW_HIGH_ROOM_VNUM, m_ctlNewHighRoomVnum);
	DDX_Control(pDX, IDC_NEW_HIGH_OBJECT_VNUM, m_ctlNewHighObjVnum);
	DDX_Control(pDX, IDC_NEW_HIGH_MOB_VNUM, m_ctlNewHighMobVnum);
	DDX_Control(pDX, IDC_NEW_LOW_MOB_VNUM, m_ctlNewLowMobVnum);
	DDX_Control(pDX, IDC_NEW_LOW_ROOM_VNUM, m_ctlNewLowRoomVnum);
	DDX_Control(pDX, IDC_NEW_LOW_OBJECT_VNUM, m_ctlNewLowObjVnum);
	DDX_Check(pDX, IDC_MOB_COMPACT, m_bMobCompact);
	DDX_Text(pDX, IDC_MOB_COUNT, m_iMobCount);
	DDX_Text(pDX, IDC_MOB_HIGH_VNUM, m_iMobHighVnum);
	DDX_Text(pDX, IDC_MOB_LOW_VNUM, m_iMobLowVnum);
	DDX_Text(pDX, IDC_NEW_HIGH_MOB_VNUM, m_iNewHighMobVnum);
	DDX_Text(pDX, IDC_NEW_HIGH_OBJECT_VNUM, m_iNewHighObjVnum);
	DDX_Text(pDX, IDC_NEW_HIGH_ROOM_VNUM, m_iNewHighRoomVnum);
	DDX_Check(pDX, IDC_OBJECT_COMPACT, m_bObjCompact);
	DDX_Text(pDX, IDC_OBJECT_COUNT, m_iObjCount);
	DDX_Text(pDX, IDC_OBJECT_HIGH_VNUM, m_iObjHighVnum);
	DDX_Text(pDX, IDC_OBJECT_LOW_VNUM, m_iObjLowVnum);
	DDX_Check(pDX, IDC_ROOM_COMPACT, m_bRoomCompact);
	DDX_Text(pDX, IDC_ROOM_COUNT, m_iRoomCount);
	DDX_Text(pDX, IDC_ROOM_HIGH_VNUM, m_iRoomHighVnum);
	DDX_Text(pDX, IDC_ROOM_LOW_VNUM, m_iRoomLowVnum);
	//}}AFX_DATA_MAP

	DDX_Text(pDX, IDC_NEW_LOW_MOB_VNUM, m_iNewLowMobVnum);
	DDV_MinMaxInt(pDX, m_iNewLowMobVnum, 1, iMaxVnum);
	DDX_Text(pDX, IDC_NEW_LOW_OBJECT_VNUM, m_iNewLowObjVnum);
	DDV_MinMaxInt(pDX, m_iNewLowObjVnum, 1, iMaxVnum);
	DDX_Text(pDX, IDC_NEW_LOW_ROOM_VNUM, m_iNewLowRoomVnum);
	DDV_MinMaxInt(pDX, m_iNewLowRoomVnum, 1, iMaxVnum);

  if (!pDX->m_bSaveAndValidate)
    {
    OnChangeNewLowMobVnum ();
    OnChangeNewLowObjectVnum ();
    OnChangeNewLowRoomVnum ();
    }
}


BEGIN_MESSAGE_MAP(CRenumberDlg, CDialog)
	//{{AFX_MSG_MAP(CRenumberDlg)
	ON_EN_CHANGE(IDC_NEW_LOW_MOB_VNUM, OnChangeNewLowMobVnum)
	ON_EN_CHANGE(IDC_NEW_LOW_OBJECT_VNUM, OnChangeNewLowObjectVnum)
	ON_EN_CHANGE(IDC_NEW_LOW_ROOM_VNUM, OnChangeNewLowRoomVnum)
	ON_BN_CLICKED(IDC_MOB_COMPACT, OnMobCompact)
	ON_BN_CLICKED(IDC_OBJECT_COMPACT, OnObjectCompact)
	ON_BN_CLICKED(IDC_ROOM_COMPACT, OnRoomCompact)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRenumberDlg message handlers

void CRenumberDlg::OnChangeNewLowMobVnum() 
{

CString strVnum;
BOOL bCompact = IsDlgButtonChecked (IDC_MOB_COMPACT);

int iNewLowVnum;
int iDifference;
int iNewHighVnum;

// get amended text of window

  m_ctlNewLowMobVnum.GetWindowText(strVnum);
  iNewLowVnum = atoi (strVnum);

  iDifference = iNewLowVnum - m_iMobLowVnum;

  if (bCompact)
    iNewHighVnum = iNewLowVnum + m_iMobCount - 1;
  else
    iNewHighVnum = m_iMobHighVnum + iDifference;

  m_ctlNewHighMobVnum.SetWindowText (CFormat ("%i", iNewHighVnum));
    
}

void CRenumberDlg::OnChangeNewLowObjectVnum() 
{
CString strVnum;
BOOL bCompact = IsDlgButtonChecked (IDC_OBJECT_COMPACT);

int iNewLowVnum;
int iDifference;
int iNewHighVnum;

// get amended text of window

  m_ctlNewLowObjVnum.GetWindowText(strVnum);
  iNewLowVnum = atoi (strVnum);

  iDifference = iNewLowVnum - m_iObjLowVnum;

  if (bCompact)
    iNewHighVnum = iNewLowVnum + m_iObjCount - 1;
  else
    iNewHighVnum = m_iObjHighVnum + iDifference;

  m_ctlNewHighObjVnum.SetWindowText (CFormat ("%i", iNewHighVnum));
	
}

void CRenumberDlg::OnChangeNewLowRoomVnum() 
{
CString strVnum;
BOOL bCompact = IsDlgButtonChecked (IDC_ROOM_COMPACT);

int iNewLowVnum;
int iDifference;
int iNewHighVnum;

// get amended text of window

  m_ctlNewLowRoomVnum.GetWindowText(strVnum);
  iNewLowVnum = atoi (strVnum);

  iDifference = iNewLowVnum - m_iRoomLowVnum;

  if (bCompact)
    iNewHighVnum = iNewLowVnum + m_iRoomCount - 1;
  else
    iNewHighVnum = m_iRoomHighVnum + iDifference;

  m_ctlNewHighRoomVnum.SetWindowText (CFormat ("%i", iNewHighVnum));
	
}

void CRenumberDlg::OnMobCompact() 
{
  OnChangeNewLowMobVnum ();	
}

void CRenumberDlg::OnObjectCompact() 
{
  OnChangeNewLowObjectVnum ();	
}

void CRenumberDlg::OnRoomCompact() 
{
  OnChangeNewLowRoomVnum ();	
}
