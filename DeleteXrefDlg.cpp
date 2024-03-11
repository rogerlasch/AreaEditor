/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// DeleteXrefDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "AreaEditorDoc.h"
#include "DeleteXrefDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDeleteXrefDlg dialog


CDeleteXrefDlg::CDeleteXrefDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDeleteXrefDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDeleteXrefDlg)
	m_strAboutToDelete = _T("");
	//}}AFX_DATA_INIT

  m_pxrefList = NULL;
  m_pxrefOwnerList = NULL;

}


void CDeleteXrefDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDeleteXrefDlg)
	DDX_Control(pDX, IDC_XREF_LIST, m_ctlXrefList);
	DDX_Text(pDX, IDC_ABOUT_TO_DELETE, m_strAboutToDelete);
	//}}AFX_DATA_MAP

  if (!pDX->m_bSaveAndValidate)
    {

    CString strType,
            strMessage;

    // these 2 lists had better stay in sync!
    POSITION ownerpos = m_pxrefOwnerList->GetHeadPosition ();

    for (POSITION pos = m_pxrefList->GetHeadPosition (); pos; )
      {
      CMUDitem * owner = NULL;

      CMUDitem * item = m_pxrefList->GetNext (pos);
      
      if (ownerpos)
        owner = m_pxrefOwnerList->GetNext (ownerpos);

      strType = item->Type ();
      if (!strType.IsEmpty ())
	      strType.SetAt (0, UPPER(strType[0])); // capitalise first character

      strMessage = strType;
      strMessage += ": ";
      if (owner)
        {
        strMessage += owner->Summary ();
        strMessage += ": ";
        }

      strMessage += item->Summary ();

      item->AddToListBox (m_ctlXrefList, strMessage);
      }
    OnSelectAll ();
    }
}


BEGIN_MESSAGE_MAP(CDeleteXrefDlg, CDialog)
	//{{AFX_MSG_MAP(CDeleteXrefDlg)
	ON_BN_CLICKED(IDC_DESELECT_ALL, OnDeselectAll)
	ON_BN_CLICKED(IDC_SELECT_ALL, OnSelectAll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDeleteXrefDlg message handlers

void CDeleteXrefDlg::OnDeselectAll() 
{
 for (int i = 0; i < m_ctlXrefList.GetCount (); i++)
   m_ctlXrefList.SetSel(i, FALSE);	
}

void CDeleteXrefDlg::OnSelectAll() 
{
 for (int i = 0; i < m_ctlXrefList.GetCount (); i++)
   m_ctlXrefList.SetSel(i, TRUE);		
}
