/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// AddToObjectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "AddToObjectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddToObjectDlg dialog


CAddToObjectDlg::CAddToObjectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddToObjectDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddToObjectDlg)
	m_iAddType = -1;
	//}}AFX_DATA_INIT
}


void CAddToObjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddToObjectDlg)
	DDX_Radio(pDX, IDC_ADD_BUTTONS, m_iAddType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddToObjectDlg, CDialog)
	//{{AFX_MSG_MAP(CAddToObjectDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddToObjectDlg message handlers
