/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// WearFlagsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "WearFlagsDlg.h"
#include "defaults.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWearFlagsDlg dialog


CWearFlagsDlg::CWearFlagsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWearFlagsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWearFlagsDlg)
	m_strWearLocations = _T("");
	m_strObject = _T("");
	//}}AFX_DATA_INIT
}


void CWearFlagsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWearFlagsDlg)
	DDX_Control(pDX, IDC_WEAR_LOCATION, m_ctlLocation);
	DDX_Text(pDX, IDC_WEAR_FLAGS, m_strWearLocations);
	DDX_Text(pDX, IDC_OBJECT, m_strObject);
	//}}AFX_DATA_MAP

  if (pDX->m_bSaveAndValidate)
    {
    int i;
    if (UnloadComboBox (m_ctlLocation, i))
      m_iWearLocation = i;
    }
  else
    LoadComboBoxList (m_ctlLocation, ObjectWearList, m_iWearLocation);

}


BEGIN_MESSAGE_MAP(CWearFlagsDlg, CDialog)
	//{{AFX_MSG_MAP(CWearFlagsDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWearFlagsDlg message handlers
