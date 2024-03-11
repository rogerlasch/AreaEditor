/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// AuthorNameView.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "AuthorNameView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAuthorNameView

IMPLEMENT_DYNCREATE(CAuthorNameView, CFormView)

CAuthorNameView::CAuthorNameView()
	: CFormView(CAuthorNameView::IDD)
{
	//{{AFX_DATA_INIT(CAuthorNameView)
	m_strAuthorName = _T("");
	//}}AFX_DATA_INIT
}

CAuthorNameView::~CAuthorNameView()
{
}

void CAuthorNameView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAuthorNameView)
	DDX_Text(pDX, IDC_AUTHOR_NAME, m_strAuthorName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAuthorNameView, CFormView)
	//{{AFX_MSG_MAP(CAuthorNameView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAuthorNameView diagnostics

#ifdef _DEBUG
void CAuthorNameView::AssertValid() const
{
	CFormView::AssertValid();
}

void CAuthorNameView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAuthorNameView message handlers
