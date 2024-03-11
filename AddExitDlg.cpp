/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// AddExitDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "AreaEditorDoc.h"
#include "defaults.h"

#include "AddExitDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddExitDlg dialog


CAddExitDlg::CAddExitDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddExitDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddExitDlg)
	m_bMakeReverse = FALSE;
	//}}AFX_DATA_INIT

  m_iDirection = -1;

}


void CAddExitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddExitDlg)
	DDX_Control(pDX, IDOK, m_ctlOK);
	DDX_Control(pDX, IDC_DIRECTION, m_ctlDirection);
	DDX_Control(pDX, IDC_EXIT_LIST, m_ctlExitList);
	DDX_Check(pDX, IDC_MAKE_REVERSE, m_bMakeReverse);
	//}}AFX_DATA_MAP

  if (pDX->m_bSaveAndValidate)
    {
    int i;
    if (!UnloadComboBox (m_ctlDirection, i))
        {
        ::AfxMessageBox ("Please choose an exit direction before proceeding",
                          MB_ICONSTOP);
      	DDX_Control(pDX, IDC_DIRECTION, m_ctlDirection);
        pDX->Fail();
        }   // end of no direction chosen
    else
      m_iDirection = i;

    }
  else
    {
    LoadComboBoxList (m_ctlDirection, RoomDirectionList, m_iDirection);
    OnSelchangeDirection ();
    }
}


BEGIN_MESSAGE_MAP(CAddExitDlg, CDialog)
	//{{AFX_MSG_MAP(CAddExitDlg)
	ON_CBN_SELCHANGE(IDC_DIRECTION, OnSelchangeDirection)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddExitDlg message handlers

BOOL CAddExitDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
POSITION exitPos;
CExit * exit;

for (exitPos = m_room->exitlist.GetHeadPosition (); exitPos; )
  {
  exit = m_room->exitlist.GetNext (exitPos);
  exit->AddToListBox (m_ctlExitList, "", FALSE);
  }
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CAddExitDlg::OnSelchangeDirection() 
{
m_ctlOK.EnableWindow (m_ctlDirection.GetCurSel () != CB_ERR);

}
