/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// ShopView.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "AreaEditorDoc.h"
#include "defaults.h"

#include "ShopView.h"

#include "ChooseMobDlg.h"
#include "ChooseObjectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShopView

IMPLEMENT_DYNCREATE(CShopView, CFormView)

CShopView::CShopView()
	: CFormView(CShopView::IDD)
{
	//{{AFX_DATA_INIT(CShopView)
	m_keeper = 0;
	m_profit_buy = 0;
	m_profit_sell = 0;
	m_open_hour = 0;
	m_close_hour = 0;
	//}}AFX_DATA_INIT

  m_shop = NULL;
  m_KeeperMob = NULL;
  m_KeeperReset = NULL;
  m_pLHview = NULL;

}

CShopView::~CShopView()
{
}

#undef LOAD_VALUE
#define LOAD_VALUE(field, value)  \
  field = m_shop->value

#undef UNLOAD_VALUE
#define UNLOAD_VALUE(field, value)  \
  if (field != m_shop->value) bChanged = true; \
  m_shop->value = field

void CShopView::DoDataExchange(CDataExchange* pDX)
{
bool bChanged = false;

  if (!pDX->m_bSaveAndValidate && m_shop)
    {
	  LOAD_VALUE (m_keeper      , keeper     );
	  LOAD_VALUE (m_profit_buy  , profit_buy );
	  LOAD_VALUE (m_profit_sell , profit_sell);
	  LOAD_VALUE (m_open_hour   , open_hour  );
	  LOAD_VALUE (m_close_hour  , close_hour );
    }


	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShopView)
	DDX_Control(pDX, IDC_ADD_ITEM, m_ctlAddItem);
	DDX_Control(pDX, IDC_REMOVE_ITEM, m_ctlRemoveItem);
	DDX_Control(pDX, IDC_GOTO_OBJECT, m_ctlGoToItem);
	DDX_Control(pDX, IDC_SELLING, m_ctlSellingList);
	DDX_Control(pDX, IDC_BUY_TYPE5, m_ctlBuyType5);
	DDX_Control(pDX, IDC_BUY_TYPE4, m_ctlBuyType4);
	DDX_Control(pDX, IDC_BUY_TYPE3, m_ctlBuyType3);
	DDX_Control(pDX, IDC_BUY_TYPE2, m_ctlBuyType2);
	DDX_Control(pDX, IDC_BUY_TYPE1, m_ctlBuyType1);
	DDX_Control(pDX, IDC_GOTO, m_ctlGoTo);
	DDX_Control(pDX, IDC_KEEPER, m_ctlKeeper);
	DDX_Control(pDX, IDC_KEEPER_DESCRIPTION, m_ctlKeeperDescription);
	DDX_Text(pDX, IDC_KEEPER, m_keeper);
	DDX_Text(pDX, IDC_OPEN_HOUR, m_open_hour);
	DDV_MinMaxInt(pDX, m_open_hour, 0, 23);
	DDX_Text(pDX, IDC_CLOSE_HOUR, m_close_hour);
	DDV_MinMaxInt(pDX, m_close_hour, 0, 23);
	//}}AFX_DATA_MAP

	DDX_Text(pDX, IDC_PROFIT_BUY, m_profit_buy);
	DDV_MinMaxInt(pDX, m_profit_buy, iMinprofitbuy, iMaxprofitbuy);
	DDX_Text(pDX, IDC_PROFIT_SELL, m_profit_sell);
	DDV_MinMaxInt(pDX, m_profit_sell, iMinprofitsell, iMaxprofitsell);

  if (!pDX->m_bSaveAndValidate && m_shop)
    {
    LoadComboBoxList (m_ctlBuyType1, ObjectItemList, m_shop->buy_type [0]);
    LoadComboBoxList (m_ctlBuyType2, ObjectItemList, m_shop->buy_type [1]);
    LoadComboBoxList (m_ctlBuyType3, ObjectItemList, m_shop->buy_type [2]);
    LoadComboBoxList (m_ctlBuyType4, ObjectItemList, m_shop->buy_type [3]);
    LoadComboBoxList (m_ctlBuyType5, ObjectItemList, m_shop->buy_type [4]);
    OnChangeKeeper ();
    }

  if (pDX->m_bSaveAndValidate && m_shop)
    {
	  UNLOAD_VALUE (m_keeper      , keeper     );
	  UNLOAD_VALUE (m_profit_buy  , profit_buy );
	  UNLOAD_VALUE (m_profit_sell , profit_sell);
	  UNLOAD_VALUE (m_open_hour   , open_hour  );
	  UNLOAD_VALUE (m_close_hour  , close_hour );

    int i;
    if (UnloadComboBox (m_ctlBuyType1, i))
	    UNLOAD_VALUE (i, buy_type [0]);
    if (UnloadComboBox (m_ctlBuyType2, i))
	    UNLOAD_VALUE (i, buy_type [1]);
    if (UnloadComboBox (m_ctlBuyType3, i))
	    UNLOAD_VALUE (i, buy_type [2]);
    if (UnloadComboBox (m_ctlBuyType4, i))
	    UNLOAD_VALUE (i, buy_type [3]);
    if (UnloadComboBox (m_ctlBuyType5, i))
	    UNLOAD_VALUE (i, buy_type [4]);

    m_shop->m_pTreeCtrl->SetItemText (m_shop->m_hdlTreeItem, m_shop->Summary ());
     if (bChanged)
       m_shop->m_pDoc->SetModifiedFlag ();
    }

}


BEGIN_MESSAGE_MAP(CShopView, CFormView)
	//{{AFX_MSG_MAP(CShopView)
	ON_EN_CHANGE(IDC_KEEPER, OnChangeKeeper)
	ON_BN_CLICKED(IDC_CHOOSE, OnChoose)
	ON_BN_CLICKED(IDC_GOTO, OnGoto)
	ON_LBN_DBLCLK(IDC_SELLING, OnDblclkSelling)
	ON_LBN_SELCHANGE(IDC_SELLING, OnSelchangeSelling)
	ON_BN_CLICKED(IDC_GOTO_OBJECT, OnGotoObject)
	ON_BN_CLICKED(IDC_ADD_ITEM, OnAddItem)
	ON_BN_CLICKED(IDC_REMOVE_ITEM, OnRemoveItem)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShopView diagnostics

#ifdef _DEBUG
void CShopView::AssertValid() const
{
	CFormView::AssertValid();
}

void CShopView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CShopView message handlers

void CShopView::OnChangeKeeper() 
{
CAreaEditorDoc* pDoc = (CAreaEditorDoc* ) GetDocument();
ASSERT_VALID(pDoc);

CString strField;

// get amended text of window for ARG1

m_ctlKeeper.GetWindowText(strField);

// convert to number

int iField1 = atoi (strField);

CString strText;

	m_KeeperMob		= pDoc->get_mob_index(iField1);
  if (m_KeeperMob)
    {
	  strText = m_KeeperMob->short_descr;
    m_ctlGoTo.EnableWindow (true);
    }
  else
  if (m_KeeperMob = FindMob(iField1))
    {
	  strText = FullMobName (m_KeeperMob);
    m_ctlGoTo.EnableWindow (true);
    }
  else
    {
		strText = CFormat ("Mobile %i is not defined.", iField1);
    m_ctlGoTo.EnableWindow (false);
    }

  m_ctlKeeperDescription.SetWindowText (strText);
  AddItems ();

}

void CShopView::OnChoose() 
{
CAreaEditorDoc* pDoc = (CAreaEditorDoc* ) GetDocument();
ASSERT_VALID(pDoc);

CString strField;

// get amended text of window for ARG1

m_ctlKeeper.GetWindowText(strField);

// convert to number

int iField1 = atoi (strField);

CChooseMobDlg mob_dlg;

  mob_dlg.m_pDoc = pDoc;
  mob_dlg.m_iSelectedMob = iField1;
  if (mob_dlg.DoModal () == IDOK) 
    if (mob_dlg.m_iSelectedMob != -1)
      {
      m_ctlKeeper.SetWindowText(CFormat ("%i", mob_dlg.m_iSelectedMob));
      }
	
}

void CShopView::OnGoto() 
{
CAreaEditorDoc* pDoc = (CAreaEditorDoc* ) GetDocument();
ASSERT_VALID(pDoc);

CString strField;

// get amended text of window for ARG1

m_ctlKeeper.GetWindowText(strField);

// convert to number

int iField1 = atoi (strField);
	
  pDoc->goto_mob (iField1);

}


void CShopView::AddItems(void)
  {


  m_ctlSellingList.ResetContent ();

  POSITION resetPos;
  CReset * reset;

  bool bKeeper = false;
  CMUDObject * object;

  m_KeeperReset = NULL;

    // process each reset

  for (resetPos = m_shop->m_pDoc->m_ResetList.GetHeadPosition (); resetPos; )
    {
    reset = m_shop->m_pDoc->m_ResetList.GetNext (resetPos);

    switch (reset->command)
      {
      case 'M': // load mobile

        if (m_KeeperMob)
          {
          bKeeper = reset->arg1 == m_KeeperMob->vnum;
          if (bKeeper)
            m_KeeperReset = reset;
          }

        break;

      case 'G': // give object
        if (!bKeeper)   // not given to the keeper
          break;    // not for this keeper - forget it

        if ((object = FindObj ( reset->arg1)) == NULL)
          break;    // object not found

        // aha! - add to list of objects, if non-zero cost

        if (object->cost)
          reset->AddToListBox (m_ctlSellingList, object->Summary ());

        break;

      } // end of switch

    }   // end of processing each reset

  OnSelchangeSelling ();

  }

void CShopView::OnDblclkSelling() 
{
  OnGotoObject ();	
}

void CShopView::OnSelchangeSelling() 
{
// find which item they selected

int nItem =  m_ctlSellingList.GetCurSel( );
	
m_ctlGoToItem.EnableWindow (nItem != LB_ERR);
m_ctlRemoveItem.EnableWindow (nItem != LB_ERR && m_KeeperReset != NULL);
m_ctlAddItem.EnableWindow (m_KeeperReset != NULL);
	
}

void CShopView::OnGotoObject() 
{
// find which item they selected, and go to it

int nItem =  m_ctlSellingList.GetCurSel( );

if (nItem != LB_ERR)
  ((CMUDitem *) m_ctlSellingList.GetItemData (nItem))->GoTo ();
	
}


void CShopView::OnAddItem() 
{
CChooseObjectDlg object_dlg;

  object_dlg.m_pDoc = m_shop->m_pDoc;
  object_dlg.m_iItemType = eShopItem;
  if (object_dlg.DoModal () == IDOK) 
    if (object_dlg.m_iSelectedObject != -1 && m_KeeperReset != NULL)
      {
      CReset * reset = (CReset *) m_KeeperReset->Add (m_pLHview, false);
      reset->command = 'G';
      reset->arg1 = object_dlg.m_iSelectedObject;   // what object
      reset->arg2 = 1;    // limit
      reset->extra = 1;   // not sure what this does ...
      reset->m_pTreeCtrl->SetItemText (reset->m_hdlTreeItem, reset->Summary ());
      AddItems ();
      }
	
}

void CShopView::OnRemoveItem() 
{

// find which item they selected, and remove to it

int nItem =  m_ctlSellingList.GetCurSel( );

if (nItem == LB_ERR)
  return;

 CMUDitem * pItem =  (CMUDitem *) m_ctlSellingList.GetItemData (nItem);

// ask if they want to delete it

  if (::AfxMessageBox (CFormat ("OK to delete %s %s?", 
                    pItem->Type (),
                    (LPCTSTR) pItem->Summary ()), 
                    MB_ICONQUESTION | MB_YESNO) != IDYES)
                    return;

  pItem->Delete ();
  AddItems ();    // redraw list
	
}
