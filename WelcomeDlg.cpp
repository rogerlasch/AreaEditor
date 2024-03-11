/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// WelcomeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "StatLink.h"
#include "AreaEditorDoc.h"
#include "WelcomeDlg.h"
#include "CreditsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWelcomeDlg dialog


CWelcomeDlg::CWelcomeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWelcomeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWelcomeDlg)
	m_strChangeHistoryAddress = _T("");
	m_strMessage = _T("");
	//}}AFX_DATA_INIT
}


void CWelcomeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWelcomeDlg)
	DDX_Text(pDX, IDC_CHANGES_ADDRESS, m_strChangeHistoryAddress);
	DDX_Text(pDX, IDC_MESSAGE, m_strMessage);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWelcomeDlg, CDialog)
	//{{AFX_MSG_MAP(CWelcomeDlg)
	ON_BN_CLICKED(IDC_LICENSE, OnLicense)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWelcomeDlg message handlers

BOOL CWelcomeDlg::OnInitDialog() 
{
	// subclass static controls.
	m_ChangesLink.SubclassDlgItem(IDC_CHANGES_ADDRESS,  this);
 
  m_strChangeHistoryAddress = CHANGES_WEB_PAGE;

	return CDialog::OnInitDialog();
}

void CWelcomeDlg::OnLicense() 
{
CCreditsDlg dlg;

  dlg.m_iResourceID = IDR_LICENSE;
  dlg.m_strTitle = "License";

  dlg.DoModal ();	
	
}
