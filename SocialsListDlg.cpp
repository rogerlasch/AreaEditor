/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// SocialsListDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "SocialsListDlg.h"

#include "EditSocialDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSocialsListDlg dialog


CSocialsListDlg::CSocialsListDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSocialsListDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSocialsListDlg)
	m_strSocialsCount = _T("");
	//}}AFX_DATA_INIT
}


void CSocialsListDlg::DoDataExchange(CDataExchange* pDX)
{
  if (!pDX->m_bSaveAndValidate)
    m_strSocialsCount.Format ("%i socials", App.m_SocialList.GetCount ());

  CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSocialsListDlg)
	DDX_Control(pDX, IDC_SOCIALS_LIST, m_ctlSocialsList);
	DDX_Text(pDX, IDC_SOCIALS_COUNT, m_strSocialsCount);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSocialsListDlg, CDialog)
	//{{AFX_MSG_MAP(CSocialsListDlg)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_EDIT, OnEdit)
	ON_NOTIFY(NM_DBLCLK, IDC_SOCIALS_LIST, OnDblclkSocialsList)
	//}}AFX_MSG_MAP
  ON_MESSAGE(WM_KICKIDLE, OnKickIdle)
  ON_UPDATE_COMMAND_UI(IDC_EDIT, OnUpdateNeedSelection)
  ON_UPDATE_COMMAND_UI(IDC_DELETE, OnUpdateNeedSelection)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSocialsListDlg message handlers

#undef LOAD_VALUE
#define LOAD_VALUE(field, value)  \
  dlg.field = social->value

#undef UNLOAD_VALUE
#define UNLOAD_VALUE(field, value)  \
  do {    \
    if (dlg.field != social->value) bChanged = true; \
    social->value = dlg.field;   \
    } while (false)


void CSocialsListDlg::OnAdd() 
{
  CEditSocialDlg dlg;
  bool bChanged = false;
                      
  dlg.m_bAdd = true;

  if (dlg.DoModal() != IDOK)
    return;

  CSocial * social = new CSocial;

  App.m_SocialList.AddTail (social);

	UNLOAD_VALUE (m_char_auto,     char_auto); 
	UNLOAD_VALUE (m_char_found, char_found);
	UNLOAD_VALUE (m_char_no_arg, char_no_arg); 
	UNLOAD_VALUE (m_name, name);
	UNLOAD_VALUE (m_others_auto, others_auto);
	UNLOAD_VALUE (m_others_found, others_found);
	UNLOAD_VALUE (m_others_no_arg, others_no_arg);
	UNLOAD_VALUE (m_vict_found, vict_found);

  App.SortSocials ();
  App.m_bSocialsDirty = true;
  RedrawList ();
	
}

void CSocialsListDlg::OnDelete() 
{

bool bChanged = false;

  for (int nIndex = -1;
      (nIndex = m_ctlSocialsList.GetNextItem(nIndex, LVNI_SELECTED)) != -1; )
   {
   CSocial * social = (CSocial *) m_ctlSocialsList.GetItemData (nIndex);
  
// ask if they want to delete it

  if (::AfxMessageBox (CFormat ("OK to delete the social \"%s\"?", 
                    (LPCTSTR) social->name), 
                    MB_ICONQUESTION | MB_YESNO) != IDYES)
                    continue;

   App.m_SocialList.RemoveAt (App.m_SocialList.Find (social, NULL));
   bChanged = true;
   }

  if (bChanged)
    {
    App.m_bSocialsDirty = true;
    RedrawList ();
    }
	
}

void CSocialsListDlg::OnEdit() 
{
    for (int nIndex = -1;
      (nIndex = m_ctlSocialsList.GetNextItem(nIndex, LVNI_SELECTED)) != -1; )
   {
    CSocial * social = (CSocial *) m_ctlSocialsList.GetItemData (nIndex);

    CEditSocialDlg dlg;
    bool bChanged = false;

	  LOAD_VALUE (m_char_auto,     char_auto); 
	  LOAD_VALUE (m_char_found, char_found);
	  LOAD_VALUE (m_char_no_arg, char_no_arg); 
	  LOAD_VALUE (m_name, name);
	  LOAD_VALUE (m_others_auto, others_auto);
	  LOAD_VALUE (m_others_found, others_found);
	  LOAD_VALUE (m_others_no_arg, others_no_arg);
	  LOAD_VALUE (m_vict_found, vict_found);

    if (dlg.DoModal() != IDOK)
      return;

	  UNLOAD_VALUE (m_char_auto,     char_auto); 
	  UNLOAD_VALUE (m_char_found, char_found);
	  UNLOAD_VALUE (m_char_no_arg, char_no_arg); 
	  UNLOAD_VALUE (m_name, name);
	  UNLOAD_VALUE (m_others_auto, others_auto);
	  UNLOAD_VALUE (m_others_found, others_found);
	  UNLOAD_VALUE (m_others_no_arg, others_no_arg);
	  UNLOAD_VALUE (m_vict_found, vict_found);
	
    if (bChanged)
      {
      App.m_bSocialsDirty = true;
      RedrawList ();
      }
    }
	
}

void CSocialsListDlg::OnDblclkSocialsList(NMHDR* pNMHDR, LRESULT* pResult) 
{
  OnEdit ();
	
	*pResult = 0;
}

BOOL CSocialsListDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
// set list control to display whole row when selected

  m_ctlSocialsList.SendMessage (LVM_SETEXTENDEDLISTVIEWSTYLE, 0, 
                              m_ctlSocialsList.SendMessage (LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0) 
                              | LVS_EX_FULLROWSELECT);
  
  m_ctlSocialsList.InsertColumn(0, "Name", LVCFMT_LEFT, 80);
	RedrawList ();
  
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CSocialsListDlg::RedrawList (void) 
  {
int nItem = 0;

POSITION socialPos;
CSocial * social;

  m_ctlSocialsList.DeleteAllItems ();


  for (socialPos = App.m_SocialList.GetHeadPosition (); socialPos; )
    {
    social = App.m_SocialList.GetNext (socialPos);


		m_ctlSocialsList.InsertItem (nItem, social->name);     
    m_ctlSocialsList.SetItemData (nItem, (DWORD) social);

    nItem++;

    }

  } // end of CSocialsListDlg::RedrawList


LRESULT CSocialsListDlg::OnKickIdle(WPARAM, LPARAM)
  {
  UpdateDialogControls (AfxGetApp()->m_pMainWnd, false);
  return 0;
  } // end of CSocialsListDlg::OnKickIdle


void CSocialsListDlg::OnUpdateNeedSelection(CCmdUI* pCmdUI)
  {
  pCmdUI->Enable (m_ctlSocialsList.GetFirstSelectedItemPosition () != NULL);
  } // end of CSocialsListDlg::OnUpdateNeedSelection
