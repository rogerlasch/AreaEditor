/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// ChooseRoomDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "AreaEditorDoc.h"

#include "ChooseRoomDlg.h"
#include "FindInDialogDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChooseRoomDlg dialog


CChooseRoomDlg::CChooseRoomDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChooseRoomDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChooseRoomDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

//  m_RoomList = NULL;

  m_pDoc = NULL;
  m_iSelectedRoom = -1;
  m_nFoundItem = -1;

}


void CChooseRoomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChooseRoomDlg)
	DDX_Control(pDX, IDC_AREA, m_ctlArea);
	DDX_Control(pDX, IDC_FIND_NEXT, m_ctlFindNext);
	DDX_Control(pDX, IDOK, m_ctlOK);
	DDX_Control(pDX, IDC_FLAGS, m_ctlFlags);
	DDX_Control(pDX, IDC_ROOM_LIST, m_ctlRoomList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChooseRoomDlg, CDialog)
	//{{AFX_MSG_MAP(CChooseRoomDlg)
	ON_LBN_DBLCLK(IDC_ROOM_LIST, OnDblclkRoomList)
	ON_LBN_SELCHANGE(IDC_ROOM_LIST, OnSelchangeRoomList)
	ON_BN_CLICKED(IDC_FIND, OnFind)
	ON_BN_CLICKED(IDC_FIND_NEXT, OnFindNext)
	ON_CBN_SELCHANGE(IDC_AREA, OnSelchangeArea)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChooseRoomDlg message handlers

void CChooseRoomDlg::OnDblclkRoomList() 
{
  OnOK ();
}

void CChooseRoomDlg::OnOK() 
{
// find which item they selected, and return its value

int nItem =  m_ctlRoomList.GetCurSel( );

if (nItem != LB_ERR)
  m_iSelectedRoom = ((CRoom *) m_ctlRoomList.GetItemData (nItem))->vnum;
	
	CDialog::OnOK();
}

BOOL CChooseRoomDlg::OnInitDialog() 
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


  // find which area the *selected* room is in
  CRoom * room = FindRoom (m_iSelectedRoom);
  if (room)
    m_pDoc = room->m_pDoc;

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

void CChooseRoomDlg::ReloadList (void)
  {

POSITION roomPos;
CRoom * room;

  m_ctlRoomList.ResetContent ();
  for (roomPos = m_pDoc->m_RoomList.GetHeadPosition (); roomPos; )
    {
    room = m_pDoc->m_RoomList.GetNext (roomPos);
    room->AddToListBox (m_ctlRoomList, "", room->vnum == m_iSelectedRoom);
    }
	  
  OnSelchangeRoomList ();

  }

void CChooseRoomDlg::OnSelchangeRoomList() 
{
int nItem =  m_ctlRoomList.GetCurSel( );

  m_ctlOK.EnableWindow (nItem != LB_ERR);

  if (nItem == LB_ERR)
    return;

  CRoom * room = (CRoom *) m_ctlRoomList.GetItemData (nItem);

  m_ctlFlags.SetWindowText (convert_room_flags (room->room_flags));
	
}

void CChooseRoomDlg::OnFind() 
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

  m_ctlRoomList.SetCurSel(-1);    // force search from start
  OnSelchangeRoomList ();

  OnFindNext ();
	
}

void CChooseRoomDlg::OnFindNext() 
{
int nItem =  m_ctlRoomList.GetCurSel( );

if (nItem == LB_ERR)
  nItem = -1;


CString strItem;
for (nItem++; nItem < m_ctlRoomList.GetCount (); nItem++)

  {
  m_ctlRoomList.GetText(nItem, strItem);
  strItem.MakeLower ();
  strItem.TrimLeft ();
  strItem.TrimRight ();

  if (strItem.Find (m_strFindString) != -1)
    {
    m_ctlRoomList.SetCurSel(nItem);
    OnSelchangeRoomList ();
    m_nFoundItem = nItem;
    return;
    } // end of found a match
  } // end of looking at each item

CString strAgain;

  if (m_ctlRoomList.GetCurSel() == m_nFoundItem && 
      m_nFoundItem != -1)
      strAgain = " again";

  ::AfxMessageBox (CFormat ("Could not find \"%s\"%s", 
                   (LPCTSTR) m_strFindString,
                   (LPCTSTR) strAgain),
        MB_ICONINFORMATION);

  m_nFoundItem = -1;
	
}

void CChooseRoomDlg::OnSelchangeArea() 
{

int nItem = m_ctlArea.GetCurSel ();

  if (nItem != CB_ERR)
    {
    m_pDoc =  (CAreaEditorDoc *) m_ctlArea.GetItemData (nItem);
    ReloadList ();
    }

}
