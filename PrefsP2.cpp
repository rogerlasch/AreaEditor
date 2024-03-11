/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// PrefsP2.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "PrefsP2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrefsP2 property page

IMPLEMENT_DYNCREATE(CPrefsP2, CPropertyPage)

CPrefsP2::CPrefsP2() : CPropertyPage(CPrefsP2::IDD)
{
	//{{AFX_DATA_INIT(CPrefsP2)
	m_bShowWarnings = FALSE;
	m_bWarnVnumsOutOfRange = FALSE;
	m_bShowFlagNumbers = FALSE;
	m_strFontName = _T("");
	m_bSaveROMPrograms = FALSE;
	m_iDefaultAreaType = -1;
	//}}AFX_DATA_INIT
}

CPrefsP2::~CPrefsP2()
{
}

void CPrefsP2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrefsP2)
	DDX_Control(pDX, IDC_FONT_NAME, m_ctlFontName);
	DDX_Check(pDX, IDC_SHOW_WARNINGS, m_bShowWarnings);
	DDX_Check(pDX, IDC_WARN_VNUMS_OUT_OF_RANGE, m_bWarnVnumsOutOfRange);
	DDX_Check(pDX, IDC_SHOW_FLAG_NUMBERS, m_bShowFlagNumbers);
	DDX_Text(pDX, IDC_FONT_NAME, m_strFontName);
	DDX_Check(pDX, IDC_SAVE_PROGRAMS, m_bSaveROMPrograms);
	DDX_CBIndex(pDX, IDC_AREA_TYPE, m_iDefaultAreaType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPrefsP2, CPropertyPage)
	//{{AFX_MSG_MAP(CPrefsP2)
	ON_BN_CLICKED(IDC_FONT, OnFont)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrefsP2 message handlers

void CPrefsP2::OnFont() 
{
CDC dc;

dc.CreateCompatibleDC (NULL);

LOGFONT lf;

ZeroMemory (&lf, sizeof lf);

CString strName;

  m_ctlFontName.GetWindowText (strName);

  lf.lfHeight = -MulDiv(m_iScreenFontSize, dc.GetDeviceCaps(LOGPIXELSY), 72);
  strncpy (lf.lfFaceName, strName, sizeof (lf.lfFaceName) - 1);
  lf.lfFaceName [sizeof (lf.lfFaceName) - 1] = 0;

  CFontDialog dlg (&lf,
                   CF_SCREENFONTS | CF_FIXEDPITCHONLY | CF_NOSTYLESEL,
                   NULL,
                   GetOwner ());       // owner view

  if (dlg.DoModal () != IDOK)
    return;

  m_iScreenFontSize = dlg.GetSize () / 10;

  m_ctlFontName.SetWindowText(dlg.GetFaceName ());
	
	
}
