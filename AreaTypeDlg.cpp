/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// AreaTypeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "AreaTypeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAreaTypeDlg dialog


CAreaTypeDlg::CAreaTypeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAreaTypeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAreaTypeDlg)
	m_iAreaType = -1;
	//}}AFX_DATA_INIT
}


void CAreaTypeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAreaTypeDlg)
	DDX_Radio(pDX, IDC_AREA_TYPE, m_iAreaType);
	//}}AFX_DATA_MAP

  if (pDX->m_bSaveAndValidate)
    {

    if (m_iAreaType == -1)
        {
        ::AfxMessageBox ("Please choose an area type before proceeding",
                          MB_ICONSTOP);
	      DDX_Radio(pDX, IDC_AREA_TYPE, m_iAreaType);
        pDX->Fail();
        }   // end of no area type chosen
    }

}


BEGIN_MESSAGE_MAP(CAreaTypeDlg, CDialog)
	//{{AFX_MSG_MAP(CAreaTypeDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAreaTypeDlg message handlers
