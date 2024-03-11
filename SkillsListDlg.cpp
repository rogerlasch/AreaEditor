/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// SkillsListDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "SkillsListDlg.h"
#include "defaults.h"

#include "SkillsSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkillsListDlg dialog


CSkillsListDlg::CSkillsListDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSkillsListDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSkillsListDlg)
	m_strSkillsCount = _T("");
	//}}AFX_DATA_INIT

  m_last_col = 0;
  m_reverse = FALSE;

}


void CSkillsListDlg::DoDataExchange(CDataExchange* pDX)
{
  if (!pDX->m_bSaveAndValidate)
    m_strSkillsCount.Format ("%i skills/spells/tongues/weapons", 
                             App.m_SkillList.GetCount ());

  CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSkillsListDlg)
	DDX_Control(pDX, IDC_SKILLS_LIST, m_ctlSkillsList);
	DDX_Text(pDX, IDC_SKILL_COUNT, m_strSkillsCount);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSkillsListDlg, CDialog)
	//{{AFX_MSG_MAP(CSkillsListDlg)
	ON_NOTIFY(NM_DBLCLK, IDC_SKILLS_LIST, OnDblclkSkillsList)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_EDIT, OnEdit)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_SKILLS_LIST, OnColumnclickSkillsList)
	//}}AFX_MSG_MAP
  ON_MESSAGE(WM_KICKIDLE, OnKickIdle)
  ON_UPDATE_COMMAND_UI(IDC_EDIT, OnUpdateNeedSelection)
  ON_UPDATE_COMMAND_UI(IDC_DELETE, OnUpdateNeedSelection)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkillsListDlg message handlers

typedef struct 
  {  
  int        sortkey;             // which key to use
  int        reverse;             // reverse sort or not
  } t_sort_param;


static int CALLBACK CompareFunc ( LPARAM lParam1, 
                           LPARAM lParam2,
                           LPARAM lParamSort)
  { 

 ASSERT (lParamSort != NULL);

t_sort_param * psort_param = (t_sort_param *) lParamSort;

CSkill * pSkill1 = (CSkill *) lParam1;
CSkill * pSkill2 = (CSkill *) lParam2;

 ASSERT (pSkill1 != NULL);
 ASSERT (pSkill2 != NULL);

int iResult = 0;

   switch (psort_param->sortkey)
     {

     case 3:
        if (pSkill1->affects.GetCount () < pSkill2->affects.GetCount ())
          {
          iResult = -1;
          break;
          }
        else
        if (pSkill1->affects.GetCount () > pSkill2->affects.GetCount ())
          {
          iResult = 1;
          break;
          }

// if affects count is the same, fall through to slot

     case 2:
        if (pSkill1->slot < pSkill2->slot)
          {
          iResult = -1;
          break;
          }
        else
        if (pSkill1->slot > pSkill2->slot)
          {
          iResult = 1;
          break;
          }

// note - if slot is same - fall through to type

     case 0:
        iResult = stricmp (SkillTypeList.ReturnName (pSkill1->type, false), 
                           SkillTypeList.ReturnName (pSkill2->type, false));
        if (iResult != 0)
          break;

// note - if type is the same - fall through to name

     case 1:
        iResult = pSkill1->name.CompareNoCase (pSkill2->name);
        break;


     }  // end of switch

// if reverse sort wanted, reverse sense of result

  if (psort_param->reverse)
    iResult *= -1;

  return iResult;

  } // end of CompareFunc

void CSkillsListDlg::OnDblclkSkillsList(NMHDR* pNMHDR, LRESULT* pResult) 
{
  OnEdit ();
	
	*pResult = 0;
}


BOOL CSkillsListDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
// set list control to display whole row when selected

  m_ctlSkillsList.SendMessage (LVM_SETEXTENDEDLISTVIEWSTYLE, 0, 
                              m_ctlSkillsList.SendMessage (LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0) 
                              | LVS_EX_FULLROWSELECT);
  
  m_ctlSkillsList.InsertColumn(0, "Type", LVCFMT_LEFT, 80);
  m_ctlSkillsList.InsertColumn(1, "Name", LVCFMT_LEFT, 150);
  m_ctlSkillsList.InsertColumn(2, "Slot", LVCFMT_RIGHT, 50);
  m_ctlSkillsList.InsertColumn(3, "Affects", LVCFMT_RIGHT, 50);
	RedrawList ();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSkillsListDlg::OnAdd() 
{
  CSkill * skill = new CSkill;

  CSkillsSheet propSheet (NULL, skill);

  propSheet.m_skill = skill;
  propSheet.m_bAdd = true;
  
  if (propSheet.DoModal() != IDOK)
    {
    delete skill;   // don't need it now
    return;
    }

  App.SortSkills ();
  App.m_SkillList.AddTail (skill);
  
  RedrawList ();    // in case they renamed it
	
}

void CSkillsListDlg::OnEdit() 
{

    for (int nIndex = -1;
      (nIndex = m_ctlSkillsList.GetNextItem(nIndex, LVNI_SELECTED)) != -1; )
   {
    CSkill * skill = (CSkill *) m_ctlSkillsList.GetItemData (nIndex);

    CSkillsSheet propSheet (NULL, skill);

    propSheet.m_skill = skill;
    propSheet.m_bAdd = false;
    if (propSheet.DoModal() != IDOK)
      return;

    RedrawList ();    // in case they renamed it
	
    }

}

void CSkillsListDlg::OnDelete() 
{
bool bChanged = false;

  for (int nIndex = -1;
      (nIndex = m_ctlSkillsList.GetNextItem(nIndex, LVNI_SELECTED)) != -1; )
   {
   CSkill * skill = (CSkill *) m_ctlSkillsList.GetItemData (nIndex);
  
// ask if they want to delete it

  if (::AfxMessageBox (CFormat ("OK to delete the %s \"%s\"?", 
                    (LPCTSTR) SkillTypeList.ReturnName (skill->type, false),
                    (LPCTSTR) skill->name), 
                    MB_ICONQUESTION | MB_YESNO) != IDYES)
                    continue;

   App.m_SkillList.RemoveAt (App.m_SkillList.Find (skill, NULL));
   bChanged = true;
   }

  if (bChanged)
    {
    App.m_bSkillsDirty = true;
    RedrawList ();
    }
	

}


void CSkillsListDlg::RedrawList (void) 
  {
int nItem = 0;

POSITION skillPos;
CSkill * skill;

  m_ctlSkillsList.DeleteAllItems ();


  for (skillPos = App.m_SkillList.GetHeadPosition (); skillPos; )
    {
    skill = App.m_SkillList.GetNext (skillPos);


		m_ctlSkillsList.InsertItem (nItem, SkillTypeList.ReturnName (skill->type, false));     
		m_ctlSkillsList.SetItemText(nItem, 1, skill->name);
		m_ctlSkillsList.SetItemText(nItem, 2, CFormat ("%i", skill->slot));
		m_ctlSkillsList.SetItemText(nItem, 3, CFormat ("%i", skill->affects.GetCount ()));
    m_ctlSkillsList.SetItemData (nItem, (DWORD) skill);

    nItem++;

    }

  t_sort_param sort_param;

  sort_param.sortkey = m_last_col;
  sort_param.reverse = m_reverse;

  m_ctlSkillsList.SortItems (CompareFunc, (LPARAM) &sort_param); 

  } // end of CSkillsListDlg::RedrawList

void CSkillsListDlg::OnColumnclickSkillsList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
int col = pNMListView->iSubItem;

  t_sort_param sort_param;

  if (col == m_last_col)
    m_reverse = !m_reverse;
  else
    m_reverse = FALSE;

  m_last_col = col;

  sort_param.sortkey = m_last_col;
  sort_param.reverse = m_reverse;

  m_ctlSkillsList.SortItems (CompareFunc, (LPARAM) &sort_param); 

	*pResult = 0;
}


LRESULT CSkillsListDlg::OnKickIdle(WPARAM, LPARAM)
  {
  UpdateDialogControls (AfxGetApp()->m_pMainWnd, false);
  return 0;
  } // end of CSkillsListDlg::OnKickIdle


void CSkillsListDlg::OnUpdateNeedSelection(CCmdUI* pCmdUI)
  {
  pCmdUI->Enable (m_ctlSkillsList.GetFirstSelectedItemPosition () != NULL);
  } // end of CSkillsListDlg::OnUpdateNeedSelection
