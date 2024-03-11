/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// CommandsListDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "CommandsListDlg.h"

#include "EditCommandDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCommandsListDlg dialog


CCommandsListDlg::CCommandsListDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCommandsListDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCommandsListDlg)
	m_strCommandCount = _T("");
	//}}AFX_DATA_INIT

  m_last_col = 0;
  m_reverse = FALSE;

}


void CCommandsListDlg::DoDataExchange(CDataExchange* pDX)
{
  if (!pDX->m_bSaveAndValidate)
    m_strCommandCount.Format ("%i commands", App.m_CommandList.GetCount ());

  CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCommandsListDlg)
	DDX_Control(pDX, IDC_COMMANDS_LIST, m_ctlCommandsList);
	DDX_Text(pDX, IDC_COMMAND_COUNT, m_strCommandCount);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCommandsListDlg, CDialog)
	//{{AFX_MSG_MAP(CCommandsListDlg)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_EDIT, OnEdit)
	ON_NOTIFY(NM_DBLCLK, IDC_COMMANDS_LIST, OnDblclkCommandsList)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_COMMANDS_LIST, OnColumnclickCommandsList)
	//}}AFX_MSG_MAP
  ON_MESSAGE(WM_KICKIDLE, OnKickIdle)
  ON_UPDATE_COMMAND_UI(IDC_EDIT, OnUpdateNeedSelection)
  ON_UPDATE_COMMAND_UI(IDC_DELETE, OnUpdateNeedSelection)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCommandsListDlg message handlers

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

CCommand * pCommand1 = (CCommand *) lParam1;
CCommand * pCommand2 = (CCommand *) lParam2;

 ASSERT (pCommand1 != NULL);
 ASSERT (pCommand2 != NULL);

int iResult = 0;

   switch (psort_param->sortkey)
     {
     case 2:
        if (pCommand1->level < pCommand2->level)
          {
          iResult = -1;
          break;
          }
        else
        if (pCommand1->level > pCommand2->level)
          {
          iResult = 1;
          break;
          }

// note - if level is same - fall through to code


     case 1:
        iResult = pCommand1->do_fun.CompareNoCase (pCommand2->do_fun);
        if (iResult != 0)
          break;

// note - if code is the same - fall through to name

     case 0:
        iResult = pCommand1->name.CompareNoCase (pCommand2->name);
        break;
     }  // end of switch

// if reverse sort wanted, reverse sense of result

  if (psort_param->reverse)
    iResult *= -1;

  return iResult;

  } // end of CompareFunc

#undef LOAD_VALUE
#define LOAD_VALUE(field, value)  \
  dlg.field = command->value

#undef UNLOAD_VALUE
#define UNLOAD_VALUE(field, value)  \
  do {    \
    if (dlg.field != command->value) bChanged = true; \
    command->value = dlg.field;   \
    } while (false)

#define LOAD_FLAG(field, flag)  \
  dlg.field = IS_SET (command->flags, flag);

#undef UNLOAD_FLAG
#define UNLOAD_FLAG(field, flag)  \
  if (dlg.field != IS_SET (command->flags, flag)) bChanged = true; \
  if (dlg.field)                      \
    SET_BIT (command->flags, flag);\
  else                            \
    REMOVE_BIT (command->flags, flag)


void CCommandsListDlg::OnAdd() 
{
  CEditCommandDlg dlg;
  bool bChanged = false;

  dlg.m_bAdd = true;

  if (dlg.DoModal() != IDOK)
    return;

  CCommand * command = new CCommand;

  App.m_CommandList.AddTail (command);

  UNLOAD_VALUE (m_level, level);
  UNLOAD_VALUE (m_log, log);
  UNLOAD_VALUE (m_name, name);
  UNLOAD_VALUE (m_position, position);
  UNLOAD_VALUE (m_do_fun, do_fun);
  UNLOAD_FLAG  (m_possessed, CMD_FLAG_POSSESS);
  UNLOAD_FLAG  (m_polymorphed, CMD_FLAG_POLYMORPHED);
  UNLOAD_FLAG  (m_watch, CMD_WATCH);

  App.SortCommands ();
  App.m_bCommandsDirty = true;
  RedrawList ();
	
}

void CCommandsListDlg::OnDelete() 
{
bool bChanged = false;

  for (int nIndex = -1;
      (nIndex = m_ctlCommandsList.GetNextItem(nIndex, LVNI_SELECTED)) != -1; )
   {
   CCommand * Command = (CCommand *) m_ctlCommandsList.GetItemData (nIndex);
  
// ask if they want to delete it

  if (::AfxMessageBox (CFormat ("OK to delete the command \"%s\"?", 
                    (LPCTSTR) Command->name), 
                    MB_ICONQUESTION | MB_YESNO) != IDYES)
                    continue;

   App.m_CommandList.RemoveAt (App.m_CommandList.Find (Command, NULL));
   bChanged = true;
   }

  if (bChanged)
    {
    App.m_bCommandsDirty = true;
    RedrawList ();
    }
	
}


void CCommandsListDlg::OnEdit() 
{
    for (int nIndex = -1;
      (nIndex = m_ctlCommandsList.GetNextItem(nIndex, LVNI_SELECTED)) != -1; )
   {
    CCommand * command = (CCommand *) m_ctlCommandsList.GetItemData (nIndex);

    CEditCommandDlg dlg;
    bool bChanged = false;

    LOAD_VALUE (m_level, level);
    LOAD_VALUE (m_log, log);
    LOAD_VALUE (m_name, name);
    LOAD_VALUE (m_position, position);
    LOAD_VALUE (m_do_fun, do_fun);
    LOAD_FLAG  (m_possessed, CMD_FLAG_POSSESS);
    LOAD_FLAG  (m_polymorphed, CMD_FLAG_POLYMORPHED);
    LOAD_FLAG  (m_watch, CMD_WATCH);


    if (dlg.DoModal() != IDOK)
      return;

    UNLOAD_VALUE (m_level, level);
    UNLOAD_VALUE (m_log, log);
    UNLOAD_VALUE (m_name, name);
    UNLOAD_VALUE (m_position, position);
    UNLOAD_VALUE (m_do_fun, do_fun);
    UNLOAD_FLAG  (m_possessed, CMD_FLAG_POSSESS);
    UNLOAD_FLAG  (m_polymorphed, CMD_FLAG_POLYMORPHED);
    UNLOAD_FLAG  (m_watch, CMD_WATCH);
	
    if (bChanged)
      {
      App.m_bCommandsDirty = true;
      RedrawList ();
      }

    }
	
}

void CCommandsListDlg::OnDblclkCommandsList(NMHDR* pNMHDR, LRESULT* pResult) 
{
  OnEdit ();
	
	*pResult = 0;
}

BOOL CCommandsListDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
// set list control to display whole row when selected

  m_ctlCommandsList.SendMessage (LVM_SETEXTENDEDLISTVIEWSTYLE, 0, 
                              m_ctlCommandsList.SendMessage (LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0) 
                              | LVS_EX_FULLROWSELECT);
  
  m_ctlCommandsList.InsertColumn(0, "Name", LVCFMT_LEFT, 80);
  m_ctlCommandsList.InsertColumn(1, "Code", LVCFMT_LEFT, 200);
  m_ctlCommandsList.InsertColumn(2, "Level", LVCFMT_RIGHT, 50);
	RedrawList ();
  
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CCommandsListDlg::RedrawList (void) 
  {
int nItem = 0;

POSITION commandPos;
CCommand * command;

  m_ctlCommandsList.DeleteAllItems ();


  for (commandPos = App.m_CommandList.GetHeadPosition (); commandPos; )
    {
    command = App.m_CommandList.GetNext (commandPos);


		m_ctlCommandsList.InsertItem (nItem, command->name);     
		m_ctlCommandsList.SetItemText(nItem, 1, command->do_fun);
		m_ctlCommandsList.SetItemText(nItem, 2, CFormat ("%i", command->level));
    m_ctlCommandsList.SetItemData (nItem, (DWORD) command);

    nItem++;

    }

  t_sort_param sort_param;

  sort_param.sortkey = m_last_col;
  sort_param.reverse = m_reverse;

  m_ctlCommandsList.SortItems (CompareFunc, (LPARAM) &sort_param); 

  } // end of CCommandsListDlg::RedrawList

void CCommandsListDlg::OnColumnclickCommandsList(NMHDR* pNMHDR, LRESULT* pResult) 
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

  m_ctlCommandsList.SortItems (CompareFunc, (LPARAM) &sort_param); 

	*pResult = 0;
}


LRESULT CCommandsListDlg::OnKickIdle(WPARAM, LPARAM)
  {
  UpdateDialogControls (AfxGetApp()->m_pMainWnd, false);
  return 0;
  } // end of CCommandsListDlg::OnKickIdle


void CCommandsListDlg::OnUpdateNeedSelection(CCmdUI* pCmdUI)
  {
  pCmdUI->Enable (m_ctlCommandsList.GetFirstSelectedItemPosition () != NULL);
  } // end of CCommandsListDlg::OnUpdateNeedSelection
