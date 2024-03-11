/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// FlagsListPage.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "AreaEditorDoc.h"

#include "FlagsListPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static BOOL bShowFlagNumbers;

/////////////////////////////////////////////////////////////////////////////
// CFlagsListPage dialog


CFlagsListPage::CFlagsListPage(CWnd* pParent /*=NULL*/)
	: CDialog(CFlagsListPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFlagsListPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

  m_pFlagsArray = NULL;
  m_pFlags = NULL;
  m_pDoc = NULL;

}


void CFlagsListPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFlagsListPage)
	DDX_Control(pDX, IDC_SELECTED_LIST, m_ctlSelectedList);
	DDX_Control(pDX, IDC_AVAILABLE_LIST, m_ctlAvailableList);
	//}}AFX_DATA_MAP

  if (pDX->m_bSaveAndValidate)
    {
  // unload the flag values
        
    if (!m_pFlagsArray || !m_pFlags || !m_pDoc)
      return;    // no array or flags - can't do much

    // note if document has changed
    if (m_NewFlags != *m_pFlags)
      m_pDoc->SetModifiedFlag ();

    *m_pFlags = m_NewFlags;
    }   // end of saving and validating
  else
    m_NewFlags = *m_pFlags;   // remember flags values

}


BEGIN_MESSAGE_MAP(CFlagsListPage, CDialog)
	//{{AFX_MSG_MAP(CFlagsListPage)
	ON_BN_CLICKED(IDC_INSERT, OnInsert)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_LBN_DBLCLK(IDC_AVAILABLE_LIST, OnDblclkAvailableList)
	ON_LBN_DBLCLK(IDC_SELECTED_LIST, OnDblclkSelectedList)
	ON_LBN_SELCHANGE(IDC_AVAILABLE_LIST, OnSelchangeAvailableList)
	ON_LBN_SELCHANGE(IDC_SELECTED_LIST, OnSelchangeSelectedList)
	ON_LBN_SELCANCEL(IDC_AVAILABLE_LIST, OnSelcancelAvailableList)
	ON_LBN_SELCANCEL(IDC_SELECTED_LIST, OnSelcancelSelectedList)
	//}}AFX_MSG_MAP
  ON_MESSAGE(WM_KICKIDLE, OnKickIdle)
  ON_UPDATE_COMMAND_UI(IDC_INSERT, OnUpdateInsert)
  ON_UPDATE_COMMAND_UI(IDC_DELETE, OnUpdateRemove)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFlagsListPage message handlers


void CFlagsListPage::LoadLists (void)
  {

  if (!m_pFlagsArray || !m_pFlags || !m_pDoc)
    return;    // no array or flags - can't do much

   m_ctlSelectedList.SetRedraw (FALSE);
   m_ctlAvailableList.SetRedraw (FALSE);
   m_ctlSelectedList.ResetContent ();
   m_ctlAvailableList.ResetContent ();

   CString strDescription;
   int nItem;

  for (__int64 i = 0; i < MAX_BITS; i++)
    {
    if (m_pFlagsArray->strName [i].IsEmpty ())
      strDescription = CFormat ("Flag %i", i);
    else
      {
      if (bShowFlagNumbers)
        {
        // ROM flag is alpha, not a number
        if (m_pDoc->m_AreaType == eROM)
          {
          char c = 'A' + (char) i;
          if (c > 'Z')
            c = 'a' + ((char) i - 26);
          strDescription = CFormat ("%c. %s", c, (LPCTSTR) m_pFlagsArray->strName [i]);
          }
        else
          strDescription = CFormat ("%02I64d. %s", i + 1, (LPCTSTR) m_pFlagsArray->strName [i]);
        }
      else
        strDescription = m_pFlagsArray->strName [i];
      }

    if (IS_SET (m_NewFlags, (unsigned __int64) 1 << i))
      {

      nItem = m_ctlSelectedList.AddString (strDescription);
      if (nItem != LB_ERR && nItem != LB_ERRSPACE)
        m_ctlSelectedList.SetItemData (nItem, (ULONG) i);


      }   // end of flag being set
     else
      if (!m_pFlagsArray->strName [i].IsEmpty ())
        {

        nItem = m_ctlAvailableList.AddString (strDescription);
        if (nItem != LB_ERR && nItem != LB_ERRSPACE)
          m_ctlAvailableList.SetItemData (nItem, (ULONG) i);
        }   // end of flag being set

    }    // end of processing all flags


  m_ctlSelectedList.SetRedraw (TRUE);
  m_ctlAvailableList.SetRedraw (TRUE);
  UpdateDialogControls (AfxGetApp()->m_pMainWnd, false);

  } // end of CFlagsListPage::LoadSelectedList 


BOOL CFlagsListPage::OnInitDialog() 
{
	CDialog::OnInitDialog();

  // we only need to do this once, so do it now

  bShowFlagNumbers = App.GetProfileInt  
      (sProfilePreferences, sProfileShowFlagNumbers, 0);	
  
  LoadLists ();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFlagsListPage::OnInsert() 
{
int nCount;
CArray<int,int> aryListBoxSel;

  // Get the indexes of all the selected items.
  nCount = m_ctlAvailableList.GetSelCount();

  // give up if none
  if (nCount == LB_ERR || nCount < 1)
    return;

  // configure our array
  aryListBoxSel.SetSize(nCount);

  // get selected items
  m_ctlAvailableList.GetSelItems(nCount, aryListBoxSel.GetData()); 

  for (int i = 0; i < nCount; i++)
    {
    // find which item they want to insert
    int nItem = aryListBoxSel [i];
	
    // set the appropriate bit
    SET_BIT (m_NewFlags, (unsigned __int64) 1 << m_ctlAvailableList.GetItemData (nItem));

    }   // end of looping through each selected item


  LoadLists ();
	
}

void CFlagsListPage::OnDelete() 
{
int nCount;
CArray<int,int> aryListBoxSel;

  // Get the indexes of all the selected items.
  nCount = m_ctlSelectedList.GetSelCount();

  // give up if none
  if (nCount == LB_ERR || nCount < 1)
    return;

  // configure our array
  aryListBoxSel.SetSize(nCount);

  // get selected items
  m_ctlSelectedList.GetSelItems(nCount, aryListBoxSel.GetData()); 

  for (int i = 0; i < nCount; i++)
    {
    // find which item they want to insert
    int nItem = aryListBoxSel [i];
	
    // set the appropriate bit
    REMOVE_BIT (m_NewFlags, (unsigned __int64) 1 << m_ctlSelectedList.GetItemData (nItem));

    }   // end of looping through each selected item


  LoadLists ();
	
}


void CFlagsListPage::OnUpdateInsert(CCmdUI* pCmdUI)
  {
  pCmdUI->Enable (m_ctlAvailableList.GetSelCount() != LB_ERR &&
                  m_ctlAvailableList.GetSelCount() > 0);
  } // end of CFlagsListPage::OnUpdateInsert

void CFlagsListPage::OnUpdateRemove(CCmdUI* pCmdUI)
  {
  pCmdUI->Enable (m_ctlSelectedList.GetSelCount() != LB_ERR &&
                  m_ctlSelectedList.GetSelCount() > 0);
  } // end of CFlagsListPage::OnUpdateRemove

LRESULT CFlagsListPage::OnKickIdle(WPARAM, LPARAM)
  {
  UpdateDialogControls (AfxGetApp()->m_pMainWnd, false);
  return 0;
  } // end of CFlagsListPage::OnKickIdle

void CFlagsListPage::OnDblclkAvailableList() 
{
  OnInsert ();	
}

void CFlagsListPage::OnDblclkSelectedList() 
{
  OnDelete ();	
}

void CFlagsListPage::OnSelchangeAvailableList() 
{
  UpdateDialogControls (AfxGetApp()->m_pMainWnd, false);
	
}

void CFlagsListPage::OnSelchangeSelectedList() 
{
  UpdateDialogControls (AfxGetApp()->m_pMainWnd, false);
	
}

void CFlagsListPage::OnSelcancelAvailableList() 
{
  UpdateDialogControls (AfxGetApp()->m_pMainWnd, false);
	
}

void CFlagsListPage::OnSelcancelSelectedList() 
{
  UpdateDialogControls (AfxGetApp()->m_pMainWnd, false);
	
}
