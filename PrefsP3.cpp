/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// PrefsP3.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "PrefsP3.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrefsP3 property page

IMPLEMENT_DYNCREATE(CPrefsP3, CPropertyPage)

CPrefsP3::CPrefsP3() : CPropertyPage(CPrefsP3::IDD)
{
	//{{AFX_DATA_INIT(CPrefsP3)
	m_strFontName = _T("");
	m_iLinesPerPage = 0;
	m_iTopMargin = 0;
	m_iLeftMargin = 0;
	m_bPrintToFile = FALSE;
	m_bShowPrograms = FALSE;
	//}}AFX_DATA_INIT
}

CPrefsP3::~CPrefsP3()
{
}

void CPrefsP3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrefsP3)
	DDX_Control(pDX, IDC_FONT_NAME, m_ctlFontName);
	DDX_Text(pDX, IDC_FONT_NAME, m_strFontName);
	DDX_Text(pDX, IDC_LINES_PER_PAGE, m_iLinesPerPage);
	DDX_Text(pDX, IDC_TOP_MARGIN, m_iTopMargin);
	DDX_Text(pDX, IDC_LEFT_MARGIN, m_iLeftMargin);
	DDX_Check(pDX, IDC_PRINT_TO_FILE, m_bPrintToFile);
	DDX_Check(pDX, IDC_SHOW_PROGRAMS, m_bShowPrograms);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPrefsP3, CPropertyPage)
	//{{AFX_MSG_MAP(CPrefsP3)
	ON_BN_CLICKED(IDC_FONT, OnFont)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrefsP3 message handlers

void CPrefsP3::OnFont() 
{
CDC dc;

dc.CreateCompatibleDC (NULL);

LOGFONT lf;

ZeroMemory (&lf, sizeof lf);

CString strName;

  m_ctlFontName.GetWindowText (strName);

  lf.lfHeight = -MulDiv(m_iPrinterFontSize, dc.GetDeviceCaps(LOGPIXELSY), 72);
  strncpy (lf.lfFaceName, strName, sizeof (lf.lfFaceName) - 1);
  lf.lfFaceName [sizeof (lf.lfFaceName) - 1] = 0;

  CFontDialog dlg (&lf,
                   CF_BOTH | CF_NOSTYLESEL,
                   NULL,
                   GetOwner ());       // owner view

  if (dlg.DoModal () != IDOK)
    return;

  m_iPrinterFontSize = dlg.GetSize () / 10;

  m_ctlFontName.SetWindowText(dlg.GetFaceName ());
	
}

BOOL CPrefsP3::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	((CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_TOP_MARGIN))->SetRange(0, 100);
	((CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_LEFT_MARGIN))->SetRange(0, 100);
	((CSpinButtonCtrl*) GetDlgItem(IDC_SPIN_LINES_PER_PAGE))->SetRange(10, 500);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
