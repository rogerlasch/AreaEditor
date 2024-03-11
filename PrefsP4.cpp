/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// PrefsP4.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "PrefsP4.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrefsP4 property page

IMPLEMENT_DYNCREATE(CPrefsP4, CPropertyPage)

CPrefsP4::CPrefsP4() : CPropertyPage(CPrefsP4::IDD)
{
	//{{AFX_DATA_INIT(CPrefsP4)
	m_bAreaCheck = FALSE;
	m_bEditWindow = FALSE;
	m_bHelp = FALSE;
	m_bEnable = FALSE;
	m_bMobDesc = FALSE;
	m_bMobLong = FALSE;
	m_bMobName = FALSE;
	m_bMobShort = FALSE;
	m_bObjActionDesc = FALSE;
	m_bObjLong = FALSE;
	m_bObjName = FALSE;
	m_bObjShort = FALSE;
	m_bRoomDesc = FALSE;
	m_bRoomName = FALSE;
	m_bAcceptName = FALSE;
	m_bCheckView = FALSE;
	m_bExitDesc = FALSE;
	m_bExtraDesc = FALSE;
	//}}AFX_DATA_INIT
}

CPrefsP4::~CPrefsP4()
{
}

void CPrefsP4::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrefsP4)
	DDX_Control(pDX, IDC_ENABLE, m_ctlEnable);
	DDX_Check(pDX, IDC_CK_AREA_CHECK, m_bAreaCheck);
	DDX_Check(pDX, IDC_CK_EDIT_WINDOW, m_bEditWindow);
	DDX_Check(pDX, IDC_CK_HELP, m_bHelp);
	DDX_Check(pDX, IDC_ENABLE, m_bEnable);
	DDX_Check(pDX, IDC_MOB_DESC, m_bMobDesc);
	DDX_Check(pDX, IDC_MOB_LONG, m_bMobLong);
	DDX_Check(pDX, IDC_MOB_NAME, m_bMobName);
	DDX_Check(pDX, IDC_MOB_SHORT, m_bMobShort);
	DDX_Check(pDX, IDC_OBJ_ACTION_DESC, m_bObjActionDesc);
	DDX_Check(pDX, IDC_OBJ_LONG, m_bObjLong);
	DDX_Check(pDX, IDC_OBJ_NAME, m_bObjName);
	DDX_Check(pDX, IDC_OBJ_SHORT, m_bObjShort);
	DDX_Check(pDX, IDC_ROOM_DESC, m_bRoomDesc);
	DDX_Check(pDX, IDC_ROOM_NAME, m_bRoomName);
	DDX_Check(pDX, IDC_ACCEPT_NAME, m_bAcceptName);
	DDX_Check(pDX, IDC_CK_VIEW, m_bCheckView);
	DDX_Check(pDX, IDC_CK_EXIT_DESC, m_bExitDesc);
	DDX_Check(pDX, IDC_EXTRA_DESC, m_bExtraDesc);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPrefsP4, CPropertyPage)
	//{{AFX_MSG_MAP(CPrefsP4)
	ON_BN_CLICKED(IDC_ENGINE_PREFS, OnEnginePrefs)
	ON_BN_CLICKED(IDC_ENABLE, OnEnable)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrefsP4 message handlers

void CPrefsP4::OnEnginePrefs() 
{
#ifdef SPELL_CHECKER

  // re-initialise in case they found the DLL
  App.InitSpellCheck (); 

  if (!App.m_bSpellCheckOK)
    {
    ::AfxMessageBox ("The spell check DLL was not found at program startup.\n\n"
                     "Please place it in your search path and restart Area Editor",
                     MB_ICONSTOP);
    return;
    }

  // show the options dialog  (with our custom dialog box)
  SSCE_OptionsDlgTmplt(m_hWnd, AfxGetResourceHandle (), "OPTIONSDLG");

#endif // SPELL_CHECKER

}

int iControls [] = 
  {
  IDC_CK_AREA_CHECK,
  IDC_CK_EDIT_WINDOW,
  IDC_CK_HELP, 
  IDC_MOB_DESC, 
  IDC_MOB_LONG, 
  IDC_MOB_NAME, 
  IDC_MOB_SHORT, 
  IDC_OBJ_ACTION_DESC,
  IDC_EXTRA_DESC, 
  IDC_OBJ_LONG, 
  IDC_OBJ_NAME, 
  IDC_OBJ_SHORT, 
  IDC_ROOM_DESC, 
  IDC_ROOM_NAME, 
  IDC_ACCEPT_NAME, 
  IDC_CK_VIEW, 
  IDC_ENGINE_PREFS,
  IDC_CK_EXIT_DESC
  };  // list of controls

void CPrefsP4::OnEnable() 
{
BOOL bEnabled = m_ctlEnable.GetCheck ();
CWnd * pWnd;
	
  for (int i = 0; i < NUMITEMS (iControls); i++)
    {
    pWnd = GetDlgItem  (iControls [i]);
    if (pWnd)
      pWnd->EnableWindow (bEnabled);
    }

}

BOOL CPrefsP4::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
  OnEnable ();	    // grey out controls appropriately

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
