/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// ChooseFromListDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "ChooseFromListDlg.h"
#include "FindInDialogDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChooseFromListDlg dialog


CChooseFromListDlg::CChooseFromListDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChooseFromListDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChooseFromListDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

  m_iSelectedItem = -1;
  m_nFoundItem = -1;
  m_pList = NULL;

}


void CChooseFromListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChooseFromListDlg)
	DDX_Control(pDX, IDOK, m_ctlOK);
	DDX_Control(pDX, IDC_FIND_NEXT, m_ctlFindNext);
	DDX_Control(pDX, IDC_ITEM_LIST, m_ctlItemList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChooseFromListDlg, CDialog)
	//{{AFX_MSG_MAP(CChooseFromListDlg)
	ON_LBN_DBLCLK(IDC_ITEM_LIST, OnDblclkItemList)
	ON_BN_CLICKED(IDC_FIND, OnFind)
	ON_BN_CLICKED(IDC_FIND_NEXT, OnFindNext)
	ON_LBN_SELCHANGE(IDC_ITEM_LIST, OnSelchangeItemList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChooseFromListDlg message handlers

void CChooseFromListDlg::OnDblclkItemList() 
{
  OnOK ();	
}

void CChooseFromListDlg::OnFind() 
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

  m_ctlItemList.SetCurSel(-1);    // force search from start
  OnSelchangeItemList ();     // which means we can't do OK yet

  OnFindNext ();
	
}

void CChooseFromListDlg::OnFindNext() 
{
int nItem =  m_ctlItemList.GetCurSel( );

if (nItem == LB_ERR)
  nItem = -1;


CString strItem;
for (nItem++; nItem < m_ctlItemList.GetCount (); nItem++)

  {
  m_ctlItemList.GetText(nItem, strItem);
  strItem.MakeLower ();
  strItem.TrimLeft ();
  strItem.TrimRight ();

  if (strItem.Find (m_strFindString) != -1)
    {
    m_ctlItemList.SetCurSel(nItem);
    OnSelchangeItemList ();
    m_nFoundItem = nItem;
    return;
    } // end of found a match
  } // end of looking at each item

CString strAgain;

  if (m_ctlItemList.GetCurSel() == m_nFoundItem && 
      m_nFoundItem != -1)
      strAgain = " again";

  ::AfxMessageBox (CFormat ("Could not find \"%s\"%s", 
                   (LPCTSTR) m_strFindString,
                   (LPCTSTR) strAgain),
        MB_ICONINFORMATION);

  m_nFoundItem = -1;
	
}

void CChooseFromListDlg::OnOK() 
{
// find which item they selected, and return its value

int nItem =  m_ctlItemList.GetCurSel( );

  if (nItem != LB_ERR)
    m_iSelectedItem = m_ctlItemList.GetItemData (nItem);
	
	CDialog::OnOK();
}

BOOL CChooseFromListDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
POSITION pos;
CString strSelectedItem;

  if (m_pList)
    for (pos = m_pList->list.GetHeadPosition (); pos; )
      {
      tList ListItem = m_pList->list.GetNext (pos);

      int nItem =  m_ctlItemList.AddString (ListItem.strName);

      // now set item data to this item, if we added it OK
      if (nItem != LB_ERR && nItem != LB_ERRSPACE)
        m_ctlItemList.SetItemData (nItem, ListItem.iValue);

      if (m_iSelectedItem == ListItem.iValue)
        strSelectedItem = ListItem.strName;
      } // end of for loop

  // select the Item now (we can't do it earlier, as we sort the list)

  if (!strSelectedItem.IsEmpty ())
    m_ctlItemList.SelectString(-1, strSelectedItem);
	
  OnSelchangeItemList ();

  // fix up window title
  if (m_strTitle)
    SetWindowText (m_strTitle);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CChooseFromListDlg::OnSelchangeItemList() 
{
int nItem =  m_ctlItemList.GetCurSel( );

  m_ctlOK.EnableWindow (nItem != LB_ERR);
	
}
