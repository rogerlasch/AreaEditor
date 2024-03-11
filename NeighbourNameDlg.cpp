/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// NeighbourNameDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "NeighbourNameDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNeighbourNameDlg dialog


CNeighbourNameDlg::CNeighbourNameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNeighbourNameDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNeighbourNameDlg)
	m_strName = _T("");
	//}}AFX_DATA_INIT
}


void CNeighbourNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNeighbourNameDlg)
	DDX_Text(pDX, IDC_NAME, m_strName);
	//}}AFX_DATA_MAP

  // check they didn't try to slip a tilde in
  if (pDX->m_bSaveAndValidate)
    {
    CheckForTilde (pDX, IDC_NAME, m_strName);
    }

}


BEGIN_MESSAGE_MAP(CNeighbourNameDlg, CDialog)
	//{{AFX_MSG_MAP(CNeighbourNameDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNeighbourNameDlg message handlers
