/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// ChooseExitDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "AreaEditorDoc.h"

#include "ChooseExitDlg.h"
#include "FindInDialogDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CChooseExitDlg dialog


CChooseExitDlg::CChooseExitDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChooseExitDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChooseExitDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

  m_ExitList = NULL;
  m_pDoc = NULL;

  m_iSelectedExit = -1;
  m_nFoundItem = -1;

}


void CChooseExitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChooseExitDlg)
	DDX_Control(pDX, IDOK, m_ctlOK);
	DDX_Control(pDX, IDC_FIND_NEXT, m_ctlFindNext);
	DDX_Control(pDX, IDC_EXIT_LIST, m_ctlExitList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChooseExitDlg, CDialog)
	//{{AFX_MSG_MAP(CChooseExitDlg)
	ON_LBN_DBLCLK(IDC_EXIT_LIST, OnDblclkExitList)
	ON_BN_CLICKED(IDC_FIND, OnFind)
	ON_BN_CLICKED(IDC_FIND_NEXT, OnFindNext)
	ON_LBN_SELCHANGE(IDC_EXIT_LIST, OnSelchangeExitList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChooseExitDlg message handlers

void CChooseExitDlg::OnDblclkExitList() 
{
  OnOK ();
}

void CChooseExitDlg::OnOK() 
{
// find which item they selected, and return its value

int nItem =  m_ctlExitList.GetCurSel( );
CString strSelectedOption;

if (nItem != LB_ERR)
  m_iSelectedExit = ((CExit *) m_ctlExitList.GetItemData (nItem))->vdir;
	
	CDialog::OnOK();
}

BOOL CChooseExitDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
POSITION exitPos;
CExit * exit;

for (exitPos = m_ExitList->GetHeadPosition (); exitPos; )
  {
  exit = m_ExitList->GetNext (exitPos);

  // only allow doors to be chosen

  if (!IS_SET( exit->exit_info, EX_ISDOOR ) )
    continue;

  exit->AddToListBox (m_ctlExitList, "", exit->vdir == m_iSelectedExit);

  }

  OnSelchangeExitList ();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CChooseExitDlg::OnFind() 
{
CFindInDialogDlg dlg;

  dlg.m_strFindWhat = m_strFindString;
  if (dlg.DoModal () != IDOK)
    return;

  m_strFindString = dlg.m_strFindWhat;

  m_strFindString.MakeLower ();
  m_strFindString.TrimLeft ();
  m_strFindString.TrimRight ();

  m_ctlFindNext.EnableWindow (TRUE);

  m_ctlExitList.SetCurSel(-1);    // force search from start
  OnSelchangeExitList ();     // which means we can't do OK yet

  OnFindNext ();
	
}

void CChooseExitDlg::OnFindNext() 
{
int nItem =  m_ctlExitList.GetCurSel( );

if (nItem == LB_ERR)
  nItem = -1;


CString strItem;
for (nItem++; nItem < m_ctlExitList.GetCount (); nItem++)

  {
  m_ctlExitList.GetText(nItem, strItem);
  strItem.MakeLower ();
  strItem.TrimLeft ();
  strItem.TrimRight ();

  if (strItem.Find (m_strFindString) != -1)
    {
    m_ctlExitList.SetCurSel(nItem);
    OnSelchangeExitList ();
    m_nFoundItem = nItem;
    return;
    } // end of found a match
  } // end of looking at each item

CString strAgain;

  if (m_ctlExitList.GetCurSel() == m_nFoundItem && 
      m_nFoundItem != -1)
      strAgain = " again";

  ::AfxMessageBox (CFormat ("Could not find \"%s\"%s", 
                   (LPCTSTR) m_strFindString,
                   (LPCTSTR) strAgain),
        MB_ICONINFORMATION);

  m_nFoundItem = -1;
	
}

void CChooseExitDlg::OnSelchangeExitList() 
{
int nItem =  m_ctlExitList.GetCurSel( );

  m_ctlOK.EnableWindow (nItem != LB_ERR);
	
}
