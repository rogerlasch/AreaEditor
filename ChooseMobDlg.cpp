/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// ChooseMobDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "AreaEditorDoc.h"
#include "defaults.h"

#include "ChooseMobDlg.h"
#include "FindInDialogDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChooseMobDlg dialog


CChooseMobDlg::CChooseMobDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChooseMobDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChooseMobDlg)
	//}}AFX_DATA_INIT

  m_pDoc = NULL;
  m_iSelectedMob = -1;
  m_nFoundItem = -1;

}


void CChooseMobDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChooseMobDlg)
	DDX_Control(pDX, IDC_AREA, m_ctlArea);
	DDX_Control(pDX, IDC_FIND_NEXT, m_ctlFindNext);
	DDX_Control(pDX, IDOK, m_ctlOK);
	DDX_Control(pDX, IDC_STATS, m_ctlStats);
	DDX_Control(pDX, IDC_SUMMARY, m_ctlSummary);
	DDX_Control(pDX, IDC_DESCRIPTION, m_ctlDescription);
	DDX_Control(pDX, IDC_MOB_LIST, m_ctlMobList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChooseMobDlg, CDialog)
	//{{AFX_MSG_MAP(CChooseMobDlg)
	ON_LBN_DBLCLK(IDC_MOB_LIST, OnDblclkMobList)
	ON_LBN_SELCHANGE(IDC_MOB_LIST, OnSelchangeMobList)
	ON_BN_CLICKED(IDC_FIND, OnFind)
	ON_BN_CLICKED(IDC_FIND_NEXT, OnFindNext)
	ON_CBN_SELCHANGE(IDC_AREA, OnSelchangeArea)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChooseMobDlg message handlers

BOOL CChooseMobDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
  
  for (POSITION docPos = App.m_pDocTemplate->GetFirstDocPosition();
      docPos != NULL; )
    {

    CAreaEditorDoc * pDoc =  (CAreaEditorDoc *) App.m_pDocTemplate->GetNextDoc(docPos);

    if (pDoc->m_Area)
      {
      int nItem = m_ctlArea.AddString (pDoc->m_Area->strAreaName);
      if (nItem != CB_ERR && nItem != CB_ERRSPACE)
        m_ctlArea.SetItemData (nItem, (DWORD) pDoc);    // remember which document
      }

    } // end of doing each document


  // find which area the *selected* Mobile is in
  CMobile * mob = FindMob (m_iSelectedMob);
  if (mob)
    m_pDoc = mob->m_pDoc;

  // now select the correct area

  for (int i = 0; i <  m_ctlArea.GetCount (); i++)
    if (m_ctlArea.GetItemData (i) == (DWORD) m_pDoc)
      {
      m_ctlArea.SetCurSel (i);
      break;
      }

  ReloadList ();

  m_ctlFindNext.EnableWindow (FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CChooseMobDlg::OnDblclkMobList() 
{
  OnOK ();
}

void CChooseMobDlg::OnOK() 
{
// find which item they selected, and return its value

int nItem =  m_ctlMobList.GetCurSel( );

if (nItem != LB_ERR)
  m_iSelectedMob = ((CMobile *) m_ctlMobList.GetItemData (nItem))->vnum;
	
	CDialog::OnOK();
}

void CChooseMobDlg::OnSelchangeMobList() 
{
int nItem =  m_ctlMobList.GetCurSel( );
CMobile * mob;

  m_ctlOK.EnableWindow (nItem != LB_ERR);

  if (nItem == LB_ERR)
    return;

  mob = (CMobile *) m_ctlMobList.GetItemData (nItem);
	
  m_ctlDescription.SetWindowText (mob->long_descr);

  m_ctlSummary.SetWindowText (CFormat ("\'%s\' is a level %i %s %s %s",
                 (LPCTSTR) mob->player_name,
                 mob->level,
                 (LPCTSTR) MobSexList.ReturnName (mob->sex, false), 
                 (LPCTSTR) MobRaceList.ReturnName (mob->race, false),
                 (LPCTSTR) MobClassList.ReturnName (mob->mobclass, false)
                 ));

  m_ctlStats.SetWindowText (CFormat (
              "Str: %i, Int: %i, Wis: %i, Dex: %i, Con: %i, Cha: %i, Lck: %i",
              mob->perm_str, mob->perm_int, mob->perm_wis, 
              mob->perm_dex, mob->perm_con, mob->perm_cha, mob->perm_lck));

}

void CChooseMobDlg::OnFind() 
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

  m_ctlMobList.SetCurSel(-1);    // force search from start
  OnSelchangeMobList ();     // which means we can't do OK yet

  OnFindNext ();
	
}

void CChooseMobDlg::OnFindNext() 
{
int nItem =  m_ctlMobList.GetCurSel( );

if (nItem == LB_ERR)
  nItem = -1;


CString strItem;
for (nItem++; nItem < m_ctlMobList.GetCount (); nItem++)

  {
  m_ctlMobList.GetText(nItem, strItem);
  strItem.MakeLower ();
  strItem.TrimLeft ();
  strItem.TrimRight ();

  if (strItem.Find (m_strFindString) != -1)
    {
    m_ctlMobList.SetCurSel(nItem);
    OnSelchangeMobList ();
    m_nFoundItem = nItem;
    return;
    } // end of found a match
  } // end of looking at each item

CString strAgain;

  if (m_ctlMobList.GetCurSel() == m_nFoundItem && 
      m_nFoundItem != -1)
      strAgain = " again";

  ::AfxMessageBox (CFormat ("Could not find \"%s\"%s", 
                   (LPCTSTR) m_strFindString,
                   (LPCTSTR) strAgain),
        MB_ICONINFORMATION);

  m_nFoundItem = -1;
	
}


void CChooseMobDlg::ReloadList (void) 
  {

POSITION mobPos;
CMobile * mob;

  m_ctlMobList.ResetContent ();

  for (mobPos = m_pDoc->m_MobList.GetHeadPosition (); mobPos; )
    {
    mob = m_pDoc->m_MobList.GetNext (mobPos);
    mob->AddToListBox (m_ctlMobList, "", mob->vnum == m_iSelectedMob);
    }
	
  OnSelchangeMobList ();
  }

void CChooseMobDlg::OnSelchangeArea() 
{
int nItem = m_ctlArea.GetCurSel ();

  if (nItem != CB_ERR)
    {
    m_pDoc =  (CAreaEditorDoc *) m_ctlArea.GetItemData (nItem);
    m_ctlDescription.SetWindowText ("");
    m_ctlSummary.SetWindowText ("");
    m_ctlStats.SetWindowText ("");
    ReloadList ();
    }
	
}
