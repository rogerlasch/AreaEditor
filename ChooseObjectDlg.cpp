/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// ChooseObjectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "AreaEditorDoc.h"
#include "defaults.h"

#include "ChooseObjectDlg.h"
#include "FindInDialogDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChooseObjectDlg dialog

CChooseObjectDlg::CChooseObjectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChooseObjectDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChooseObjectDlg)
	m_strConditions = _T("");
	//}}AFX_DATA_INIT

  m_pDoc = NULL;
  m_iSelectedObject = -1;
  m_iItemType = eAny;
  m_iWantedType = 0;
  m_nFoundItem = -1;
}


void CChooseObjectDlg::DoDataExchange(CDataExchange* pDX)
{

  if (!pDX->m_bSaveAndValidate)
    {
    switch (m_iItemType)
      {
      case eAny: m_strConditions = ""; break;
      case eShopItem: m_strConditions = "Cost must be non-zero"; break;
      case eWearItem: m_strConditions = "Must have a \"wear\" flag set"; break;
      case eTakeItem: m_strConditions = "Must have a \"take\" flag set"; break;
      case eContainerItem: m_strConditions = "Must be a container"; break;
      }   // end of switch

    }   // end of not saving

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChooseObjectDlg)
	DDX_Control(pDX, IDC_AREA, m_ctlArea);
	DDX_Control(pDX, IDC_FIND_NEXT, m_ctlFindNext);
	DDX_Control(pDX, IDC_OBJECT_TYPE, m_ctlType);
	DDX_Control(pDX, IDOK, m_ctlOK);
	DDX_Control(pDX, IDC_VALUES, m_ctlValues);
	DDX_Control(pDX, IDC_STATS, m_ctlStats);
	DDX_Control(pDX, IDC_DESCRIPTION, m_ctlDescription);
	DDX_Control(pDX, IDC_OBJECT_LIST, m_ctlObjectList);
	DDX_Text(pDX, IDC_CONDITIONS, m_strConditions);
	//}}AFX_DATA_MAP

  if (!pDX->m_bSaveAndValidate)
    LoadComboBoxList (m_ctlType, ObjectItemList, m_iWantedType ? m_iWantedType : -1);
}


BEGIN_MESSAGE_MAP(CChooseObjectDlg, CDialog)
	//{{AFX_MSG_MAP(CChooseObjectDlg)
	ON_LBN_DBLCLK(IDC_OBJECT_LIST, OnDblclkObjectList)
	ON_LBN_SELCHANGE(IDC_OBJECT_LIST, OnSelchangeObjectList)
	ON_CBN_SELCHANGE(IDC_OBJECT_TYPE, OnSelchangeObjectType)
	ON_BN_CLICKED(IDC_FIND, OnFind)
	ON_BN_CLICKED(IDC_FIND_NEXT, OnFindNext)
	ON_CBN_SELCHANGE(IDC_AREA, OnSelchangeArea)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChooseObjectDlg message handlers

void CChooseObjectDlg::OnDblclkObjectList() 
{
  OnOK ();
}

void CChooseObjectDlg::OnOK() 
{
// find which item they selected, and return its value

int nItem =  m_ctlObjectList.GetCurSel( );

if (nItem != LB_ERR)
  m_iSelectedObject = ((CMUDObject *) m_ctlObjectList.GetItemData (nItem))->vnum;
	
	CDialog::OnOK();
}

BOOL CChooseObjectDlg::OnInitDialog() 
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
  CMUDObject * obj = FindObj (m_iSelectedObject);
  if (obj)
    m_pDoc = obj->m_pDoc;

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

void CChooseObjectDlg::ReloadList (void)
  {

m_ctlObjectList. ResetContent ();

POSITION objectPos;
CMUDObject * object;

for (objectPos = m_pDoc->m_ObjectList.GetHeadPosition (); objectPos; )
  {

  bool bUseThis = false;

  object = m_pDoc->m_ObjectList.GetNext (objectPos);

  switch (m_iItemType)
    {
    case eAny: bUseThis = true; break;
    case eShopItem: bUseThis = object->cost > 0; break;
    case eWearItem: bUseThis = (object->wear_flags &
                                (
                                ITEM_WEAR_FINGER	  |
                                ITEM_WEAR_NECK		  |
                                ITEM_WEAR_BODY		  |
                                ITEM_WEAR_HEAD		  |
                                ITEM_WEAR_LEGS		  |
                                ITEM_WEAR_FEET		  |
                                ITEM_WEAR_HANDS		  |
                                ITEM_WEAR_ARMS		  |
                                ITEM_WEAR_SHIELD	  |
                                ITEM_WEAR_ABOUT		  |
                                ITEM_WEAR_WAIST		  |
                                ITEM_WEAR_WRIST		  |
                                ITEM_WIELD		      |
                                ITEM_HOLD		        |
                                ITEM_DUAL_WIELD		  |
                                ITEM_WEAR_EARS		  |
                                ITEM_WEAR_EYES		  |
                                ITEM_MISSILE_WIELD  
                                )) != 0; break;
    case eTakeItem: bUseThis = (object->wear_flags & ITEM_TAKE) != 0; break;
    case eContainerItem: bUseThis = object->item_type == ITEM_CONTAINER; break;
    }   // end of switch
    
  if (m_iWantedType && object->item_type != m_iWantedType)
    bUseThis = false;

  if (bUseThis)
    object->AddToListBox (m_ctlObjectList, "", object->vnum == m_iSelectedObject);
  }
	
  OnSelchangeObjectList ();

  } // end of CChooseObjectDlg::ReloadList

void CChooseObjectDlg::OnSelchangeObjectList() 
{
// find which item they selected, and return its value

int nItem =  m_ctlObjectList.GetCurSel( );

  m_ctlOK.EnableWindow (nItem != LB_ERR);

  if (nItem == LB_ERR)
    {
    m_ctlDescription.SetWindowText ("");
    m_ctlStats.SetWindowText ("");
    m_ctlValues.SetWindowText ("");
    return;
    }

  CMUDObject * object = (CMUDObject *) m_ctlObjectList.GetItemData (nItem);

  m_ctlDescription.SetWindowText (object->description);

  m_ctlStats.SetWindowText (CFormat ("Type: %s, weight: %i, Cost: %i",
                            (LPCTSTR) ObjectItemList.ReturnName (object->item_type, false),
                            object->weight, 
                            object->cost
    ));

  m_ctlValues.SetWindowText (object->ValueSummary ());
	
}

void CChooseObjectDlg::OnSelchangeObjectType() 
{
int nItem =  m_ctlType.GetCurSel( );

  if (nItem == LB_ERR)
    return;
	
  m_iWantedType = m_ctlType.GetItemData (nItem);
  
  ReloadList ();

}

void CChooseObjectDlg::OnFind() 
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

  m_ctlObjectList.SetCurSel(-1);    // force search from start
  OnSelchangeObjectList ();     // which means we can't do OK yet

  OnFindNext ();

}

void CChooseObjectDlg::OnFindNext() 
{
int nItem =  m_ctlObjectList.GetCurSel( );

if (nItem == LB_ERR)
  nItem = -1;


CString strItem;
for (nItem++; nItem < m_ctlObjectList.GetCount (); nItem++)

  {
  m_ctlObjectList.GetText(nItem, strItem);
  strItem.MakeLower ();
  strItem.TrimLeft ();
  strItem.TrimRight ();

  if (strItem.Find (m_strFindString) != -1)
    {
    m_ctlObjectList.SetCurSel(nItem);
    OnSelchangeObjectList ();
    m_nFoundItem = nItem;
    return;
    } // end of found a match
  } // end of looking at each item

CString strAgain;

  if (m_ctlObjectList.GetCurSel() == m_nFoundItem && 
      m_nFoundItem != -1)
      strAgain = " again";

  ::AfxMessageBox (CFormat ("Could not find \"%s\"%s", 
                   (LPCTSTR) m_strFindString,
                   (LPCTSTR) strAgain),
        MB_ICONINFORMATION);

  m_nFoundItem = -1;
}

void CChooseObjectDlg::OnSelchangeArea() 
{
int nItem = m_ctlArea.GetCurSel ();

  if (nItem != CB_ERR)
    {
    m_pDoc =  (CAreaEditorDoc *) m_ctlArea.GetItemData (nItem);
    ReloadList ();
    }
	
}
