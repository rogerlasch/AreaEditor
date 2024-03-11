/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// RepairView.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "AreaEditorDoc.h"
#include "defaults.h"

#include "RepairView.h"

#include "ChooseMobDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRepairView

IMPLEMENT_DYNCREATE(CRepairView, CFormView)

CRepairView::CRepairView()
        : CFormView(CRepairView::IDD)
{
        //{{AFX_DATA_INIT(CRepairView)
        m_close_hour = 0;
        m_keeper = 0;
        m_open_hour = 0;
        m_profit_fix = 0;
        //}}AFX_DATA_INIT

  m_repair = NULL;

}

CRepairView::~CRepairView()
{
}

char * fix_types [2] =
  { "standard", "recharge" };

#undef LOAD_VALUE
#define LOAD_VALUE(field, value)  \
  field = m_repair->value

#undef UNLOAD_VALUE
#define UNLOAD_VALUE(field, value)  \
  if (field != m_repair->value) bChanged = true; \
  m_repair->value = field

void CRepairView::DoDataExchange(CDataExchange* pDX)
{
bool bChanged = false;

  if (!pDX->m_bSaveAndValidate && m_repair)
    {
          LOAD_VALUE (m_keeper      , keeper     );
          LOAD_VALUE (m_profit_fix  , profit_fix );
          LOAD_VALUE (m_open_hour   , open_hour  );
          LOAD_VALUE (m_close_hour  , close_hour );
    }

        CFormView::DoDataExchange(pDX);
        //{{AFX_DATA_MAP(CRepairView)
        DDX_Control(pDX, IDC_REPAIR_TYPE, m_ctlRepairType);
        DDX_Control(pDX, IDC_FIX_TYPE1, m_ctlFixType1);
        DDX_Control(pDX, IDC_FIX_TYPE3, m_ctlFixType3);
        DDX_Control(pDX, IDC_FIX_TYPE2, m_ctlFixType2);
        DDX_Control(pDX, IDC_GOTO, m_ctlGoTo);
        DDX_Control(pDX, IDC_KEEPER_DESCRIPTION, m_ctlKeeperDescription);
        DDX_Control(pDX, IDC_KEEPER, m_ctlKeeper);
        DDX_Text(pDX, IDC_CLOSE_HOUR, m_close_hour);
        DDV_MinMaxInt(pDX, m_close_hour, 0, 23);
        DDX_Text(pDX, IDC_KEEPER, m_keeper);
        DDX_Text(pDX, IDC_OPEN_HOUR, m_open_hour);
        DDV_MinMaxInt(pDX, m_open_hour, 0, 23);
        //}}AFX_DATA_MAP

        DDX_Text(pDX, IDC_PROFIT_FIX, m_profit_fix);
        DDV_MinMaxInt(pDX, m_profit_fix, iMinprofitfix, iMaxprofitfix);

  if (!pDX->m_bSaveAndValidate && m_repair)
    {
    LoadComboBoxList (m_ctlFixType1, ObjectItemList, m_repair->fix_type [0]);
    LoadComboBoxList (m_ctlFixType2, ObjectItemList, m_repair->fix_type [1]);
    LoadComboBoxList (m_ctlFixType3, ObjectItemList, m_repair->fix_type [2]);
    LoadComboBox (m_ctlRepairType, fix_types, 2, m_repair->shop_type);
    OnChangeKeeper ();
    }

  if (pDX->m_bSaveAndValidate && m_repair)
    {
          UNLOAD_VALUE (m_keeper      , keeper     );
          UNLOAD_VALUE (m_profit_fix  , profit_fix );
          UNLOAD_VALUE (m_open_hour   , open_hour  );
          UNLOAD_VALUE (m_close_hour  , close_hour );

    int i;
    if (UnloadComboBox (m_ctlFixType1, i))
            UNLOAD_VALUE (i, fix_type [0]);
    if (UnloadComboBox (m_ctlFixType2, i))
            UNLOAD_VALUE (i, fix_type [1]);
    if (UnloadComboBox (m_ctlFixType3, i))
            UNLOAD_VALUE (i, fix_type [2]);
    if (UnloadComboBox (m_ctlRepairType, i))
            UNLOAD_VALUE (i, shop_type);

    m_repair->m_pTreeCtrl->SetItemText (m_repair->m_hdlTreeItem, m_repair->Summary ());
     if (bChanged)
       m_repair->m_pDoc->SetModifiedFlag ();
    }

}


BEGIN_MESSAGE_MAP(CRepairView, CFormView)
        //{{AFX_MSG_MAP(CRepairView)
        ON_EN_CHANGE(IDC_KEEPER, OnChangeKeeper)
        ON_BN_CLICKED(IDC_CHOOSE, OnChoose)
        ON_BN_CLICKED(IDC_GOTO, OnGoto)
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRepairView diagnostics

#ifdef _DEBUG
void CRepairView::AssertValid() const
{
        CFormView::AssertValid();
}

void CRepairView::Dump(CDumpContext& dc) const
{
        CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRepairView message handlers

void CRepairView::OnChangeKeeper() 
{
CAreaEditorDoc* pDoc = (CAreaEditorDoc* ) GetDocument();
ASSERT_VALID(pDoc);

CString strField;

// get amended text of window for ARG1

m_ctlKeeper.GetWindowText(strField);

// convert to number

int iField1 = atoi (strField);

CMobile * pMobIndex;

CString strText;

        pMobIndex                = pDoc->get_mob_index(iField1);
  if (pMobIndex)
    {
          strText = pMobIndex->short_descr;
    m_ctlGoTo.EnableWindow (true);
    }
  else
  if (pMobIndex = FindMob(iField1))
    {
          strText = FullMobName (pMobIndex);
    m_ctlGoTo.EnableWindow (true);
    }
  else
    {
                strText = CFormat ("Mobile %i is not defined.", iField1);
    m_ctlGoTo.EnableWindow (false);
    }

  m_ctlKeeperDescription.SetWindowText (strText);

}

void CRepairView::OnChoose() 
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
      m_ctlKeeper.SetWindowText(CFormat ("%i", mob_dlg.m_iSelectedMob));
        
}

void CRepairView::OnGoto() 
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
