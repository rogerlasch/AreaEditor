/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// AreaNeighbourView.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "AreaEditorDoc.h"
#include "defaults.h"

#include "AreaNeighbourView.h"
#include "NeighbourNameDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAreaNeighbourView dialog


CAreaNeighbourView::CAreaNeighbourView(CWnd* pParent /*=NULL*/)
	: CDialog(CAreaNeighbourView::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAreaNeighbourView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

  m_area = NULL;

}


void CAreaNeighbourView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAreaNeighbourView)
	DDX_Control(pDX, IDC_NEIGHBOURS_LIST, m_ctlNeighboursList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAreaNeighbourView, CDialog)
	//{{AFX_MSG_MAP(CAreaNeighbourView)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAreaNeighbourView message handlers

void CAreaNeighbourView::OnAdd() 
{
CNeighbourNameDlg dlg;

  if (dlg.DoModal () != IDOK)
    return;

  m_area->neighboursList.AddTail (dlg.m_strName);   // add to neighbours list
  m_area->m_pDoc->SetModifiedFlag ();

  // redraw the list
  RedrawList ();

}

void CAreaNeighbourView::OnDelete() 
{
  for (int nIndex = -1;
    (nIndex = m_ctlNeighboursList.GetNextItem(nIndex, LVNI_SELECTED)) != -1; )
   {

   CString strItem = m_ctlNeighboursList.GetItemText (nIndex, 0);

    POSITION pos = (POSITION) m_area->neighboursList.Find (strItem);

    if (pos)
      {
	    m_area->neighboursList.RemoveAt (pos);    // remove from string list
      m_area->m_pDoc->SetModifiedFlag ();
      m_ctlNeighboursList.DeleteItem (nIndex);  // and delete from control
      }
    }
	


}

BOOL CAreaNeighbourView::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
// set list control to display whole row when selected

  m_ctlNeighboursList.SendMessage (LVM_SETEXTENDEDLISTVIEWSTYLE, 0, 
                              m_ctlNeighboursList.SendMessage (LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0) 
                              | LVS_EX_FULLROWSELECT);
  
  m_ctlNeighboursList.InsertColumn(0, "Name", LVCFMT_LEFT, 80);
	RedrawList ();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CAreaNeighbourView::RedrawList (void) 
  {
int nItem = 0;

POSITION neighbourPos;

  m_ctlNeighboursList.DeleteAllItems ();


  for (neighbourPos = m_area->neighboursList.GetHeadPosition (); neighbourPos; )
    {
    CString strNeighbour = m_area->neighboursList.GetNext (neighbourPos);


		m_ctlNeighboursList.InsertItem (nItem, strNeighbour);     
    m_ctlNeighboursList.SetItemData (nItem, (DWORD) neighbourPos);

    nItem++;

    }

  } // end of CAreaNeighbourView::RedrawList

