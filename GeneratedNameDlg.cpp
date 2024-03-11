/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// GeneratedNameDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "GeneratedNameDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGeneratedNameDlg dialog


CGeneratedNameDlg::CGeneratedNameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGeneratedNameDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGeneratedNameDlg)
	m_strName = _T("");
	//}}AFX_DATA_INIT
}


void CGeneratedNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGeneratedNameDlg)
	DDX_Control(pDX, IDC_GENERATED_NAME, m_ctlName);
	DDX_Text(pDX, IDC_GENERATED_NAME, m_strName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGeneratedNameDlg, CDialog)
	//{{AFX_MSG_MAP(CGeneratedNameDlg)
	ON_BN_CLICKED(IDC_TRY_AGAIN, OnTryAgain)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGeneratedNameDlg message handlers

void CGeneratedNameDlg::OnTryAgain() 
{
CString strName = GenerateName ();

  	m_ctlName.SetWindowText (strName);
    m_ctlName.SetSel (0, -1);

}
