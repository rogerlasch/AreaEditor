/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// AreaLoadingProblems.cpp : implementation file
//

// WARNING! WARNING!  This is designed to be used as a MODELESS dialog.
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "AreaLoadingProblems.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAreaLoadingProblems dialog


CAreaLoadingProblems::CAreaLoadingProblems(CWnd* pParent /*=NULL*/)
	: CDialog(CAreaLoadingProblems::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAreaLoadingProblems)
	m_strErrors = _T("");
	//}}AFX_DATA_INIT

  m_first_time = true;
  m_font = NULL;

}

CAreaLoadingProblems::~CAreaLoadingProblems ()   // destructor
  {
  delete m_font;
  }

void CAreaLoadingProblems::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAreaLoadingProblems)
	DDX_Control(pDX, IDC_ERROR_LIST, m_ctlErrorList);
	DDX_Text(pDX, IDC_ERROR_LIST, m_strErrors);
	//}}AFX_DATA_MAP

  if (!pDX->m_bSaveAndValidate)
    {
    FixFont (m_font, m_ctlErrorList);
    }


}


BEGIN_MESSAGE_MAP(CAreaLoadingProblems, CDialog)
	//{{AFX_MSG_MAP(CAreaLoadingProblems)
	ON_EN_SETFOCUS(IDC_ERROR_LIST, OnSetfocusErrorList)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAreaLoadingProblems message handlers

void CAreaLoadingProblems::OnSetfocusErrorList() 
{
  if (m_first_time)
    {
    m_ctlErrorList.SetSel (0, 0, FALSE);
    m_first_time = false;
    }
	
}

void CAreaLoadingProblems::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
  if (m_ctlErrorList.m_hWnd)
    {
	  m_ctlErrorList.MoveWindow(0, 0, cx, cy);
    }
	
}

BOOL CAreaLoadingProblems::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
RECT rect;

  GetClientRect (&rect);

  m_ctlErrorList.MoveWindow (&rect);
 
  if (!m_strTitle.IsEmpty ())
    SetWindowText (m_strTitle);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CAreaLoadingProblems::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDialog::PostNcDestroy();
  delete this;
}


void CAreaLoadingProblems::OnOK (void)
  {
  DestroyWindow ();
  }

void CAreaLoadingProblems::OnCancel (void)
  {
  DestroyWindow ();
  }
