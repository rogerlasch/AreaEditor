/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// Welcome1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "StatLink.h"
#include "AreaEditorDoc.h"
#include "Welcome1Dlg.h"
#include "CreditsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWelcome1Dlg dialog


CWelcome1Dlg::CWelcome1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWelcome1Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWelcome1Dlg)
	m_strChangeHistoryAddress = _T("");
	m_strMessage1 = _T("");
	m_strMessage2 = _T("");
	//}}AFX_DATA_INIT
}


void CWelcome1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWelcome1Dlg)
	DDX_Text(pDX, IDC_CHANGES_ADDRESS, m_strChangeHistoryAddress);
	DDX_Text(pDX, IDC_MESSAGE1, m_strMessage1);
	DDX_Text(pDX, IDC_MESSAGE2, m_strMessage2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWelcome1Dlg, CDialog)
	//{{AFX_MSG_MAP(CWelcome1Dlg)
	ON_BN_CLICKED(IDC_LICENSE, OnLicense)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWelcome1Dlg message handlers

BOOL CWelcome1Dlg::OnInitDialog() 
{
	// subclass static controls.
	m_ChangesLink.SubclassDlgItem(IDC_CHANGES_ADDRESS,  this);
  m_strChangeHistoryAddress = CHANGES_WEB_PAGE;
	
	return CDialog::OnInitDialog();
}

void CWelcome1Dlg::OnLicense() 
{
CCreditsDlg dlg;

  dlg.m_iResourceID = IDR_LICENSE;
  dlg.m_strTitle = "License";

  dlg.DoModal ();	
	
}
