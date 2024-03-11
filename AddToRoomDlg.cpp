/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// AddToRoomDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "AddToRoomDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddToRoomDlg dialog


CAddToRoomDlg::CAddToRoomDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddToRoomDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddToRoomDlg)
	m_iAddType = -1;
	//}}AFX_DATA_INIT
}


void CAddToRoomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddToRoomDlg)
	DDX_Radio(pDX, IDC_ADD_BUTTONS, m_iAddType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddToRoomDlg, CDialog)
	//{{AFX_MSG_MAP(CAddToRoomDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddToRoomDlg message handlers
