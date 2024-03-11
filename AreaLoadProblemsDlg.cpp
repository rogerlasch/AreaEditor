/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// AreaLoadProblemsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "AreaLoadProblemsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAreaLoadProblemsDlg dialog


CAreaLoadProblemsDlg::CAreaLoadProblemsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAreaLoadProblemsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAreaLoadProblemsDlg)
	m_strErrorList = _T("");
	//}}AFX_DATA_INIT

  m_font = NULL;
}


void CAreaLoadProblemsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAreaLoadProblemsDlg)
	DDX_Control(pDX, IDC_ERROR_LIST, m_ctlErrorList);
	DDX_Text(pDX, IDC_ERROR_LIST, m_strErrorList);
	//}}AFX_DATA_MAP

  if (!pDX->m_bSaveAndValidate)
    {
    FixFont (m_font, m_ctlErrorList);
    }

}


BEGIN_MESSAGE_MAP(CAreaLoadProblemsDlg, CDialog)
	//{{AFX_MSG_MAP(CAreaLoadProblemsDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAreaLoadProblemsDlg message handlers
