/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// AreaFlagsView.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "AreaFlagsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAreaFlagsView

IMPLEMENT_DYNCREATE(CAreaFlagsView, CFormView)

CAreaFlagsView::CAreaFlagsView()
	: CFormView(CAreaFlagsView::IDD)
{
	//{{AFX_DATA_INIT(CAreaFlagsView)
	m_bPkill = FALSE;
	m_nResetFrequency = 0;
	//}}AFX_DATA_INIT
}

CAreaFlagsView::~CAreaFlagsView()
{
}

void CAreaFlagsView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAreaFlagsView)
	DDX_Check(pDX, IDC_PLAYER_KILL_ALLOWED, m_bPkill);
	DDX_Text(pDX, IDC_RESET_FREQUENCY, m_nResetFrequency);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAreaFlagsView, CFormView)
	//{{AFX_MSG_MAP(CAreaFlagsView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAreaFlagsView diagnostics

#ifdef _DEBUG
void CAreaFlagsView::AssertValid() const
{
	CFormView::AssertValid();
}

void CAreaFlagsView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAreaFlagsView message handlers
