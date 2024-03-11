/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// GotoVnumDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "GotoVnumDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGotoVnumDlg dialog


CGotoVnumDlg::CGotoVnumDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGotoVnumDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGotoVnumDlg)
	m_iVnum = 0;
	m_iVnumType = -1;
	//}}AFX_DATA_INIT
}


void CGotoVnumDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGotoVnumDlg)
	DDX_Text(pDX, IDC_VNUM, m_iVnum);
	DDX_Radio(pDX, IDC_VNUM_TYPE, m_iVnumType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGotoVnumDlg, CDialog)
	//{{AFX_MSG_MAP(CGotoVnumDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGotoVnumDlg message handlers
