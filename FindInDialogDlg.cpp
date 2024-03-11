/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// FindInDialogDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "FindInDialogDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFindInDialogDlg dialog


CFindInDialogDlg::CFindInDialogDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFindInDialogDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFindInDialogDlg)
	//}}AFX_DATA_INIT
}


void CFindInDialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFindInDialogDlg)
	DDX_MinMaxString(pDX, IDC_FIND_WHAT, m_strFindWhat);
	DDV_MinMaxString(pDX, m_strFindWhat, 1, 500);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFindInDialogDlg, CDialog)
	//{{AFX_MSG_MAP(CFindInDialogDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFindInDialogDlg message handlers
