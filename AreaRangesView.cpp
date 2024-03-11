/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// AreaRangesView.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "AreaEditorDoc.h"
#include "defaults.h"

#include "AreaRangesView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAreaRangesView dialog


CAreaRangesView::CAreaRangesView(CWnd* pParent /*=NULL*/)
	: CDialog(CAreaRangesView::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAreaRangesView)
	m_high_economy = 0;
	m_low_economy = 0;
	m_high_hard_range = 0;
	m_high_soft_range = 0;
	m_low_hard_range = 0;
	m_low_soft_range = 0;
	//}}AFX_DATA_INIT

    m_area = NULL;

}

#undef LOAD_VALUE
#define LOAD_VALUE(field, value)  \
  field = m_area->value

#undef UNLOAD_VALUE
#define UNLOAD_VALUE(field, value)  \
  if (field != m_area->value) bChanged = true; \
  m_area->value = field


void CAreaRangesView::DoDataExchange(CDataExchange* pDX)
{

bool bChanged = false;

  if (!pDX->m_bSaveAndValidate && m_area)
    {
	  LOAD_VALUE (m_low_soft_range   , low_soft_range);
	  LOAD_VALUE (m_high_soft_range   , hi_soft_range  );
	  LOAD_VALUE (m_low_hard_range  , low_hard_range );
	  LOAD_VALUE (m_high_hard_range  , hi_hard_range );
	  LOAD_VALUE (m_high_economy  , high_economy );
	  LOAD_VALUE (m_low_economy  , low_economy );
    }

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAreaRangesView)
	DDX_Control(pDX, IDC_TOTAL_ECONOMY, m_ctlTotalEconomy);
	DDX_Control(pDX, IDC_HIGH_ECONOMY, m_ctlHighEconomy);
	DDX_Control(pDX, IDC_LOW_ECONOMY, m_ctlLowEconomy);
	DDX_Text(pDX, IDC_HIGH_ECONOMY, m_high_economy);
	DDV_MinMaxInt(pDX, m_high_economy, 0, 999999999);
	DDX_Text(pDX, IDC_LOW_ECONOMY, m_low_economy);
	DDV_MinMaxInt(pDX, m_low_economy, 0, 999999999);
	//}}AFX_DATA_MAP

  // calculate total economy
  if (!pDX->m_bSaveAndValidate)
    OnChangeEconomy ();

  // ranges
  DDX_Text(pDX, IDC_LOW_SOFT_RANGE, m_low_soft_range);
	DDV_MinMaxInt(pDX, m_low_soft_range, 0, iMaxLevel);
	DDX_Text(pDX, IDC_LOW_HARD_RANGE, m_low_hard_range);
	DDV_MinMaxInt(pDX, m_low_hard_range, 0, iMaxLevel);
	DDX_Text(pDX, IDC_HIGH_HARD_RANGE, m_high_hard_range);
	DDV_MinMaxInt(pDX, m_high_hard_range, 0, iMaxLevel);
	DDX_Text(pDX, IDC_HIGH_SOFT_RANGE, m_high_soft_range);
	DDV_MinMaxInt(pDX, m_high_soft_range, 0, iMaxLevel);


  // put stuff back
  if (pDX->m_bSaveAndValidate && m_area)
    {
	  UNLOAD_VALUE (m_low_soft_range   , low_soft_range);
	  UNLOAD_VALUE (m_high_soft_range   , hi_soft_range  );
	  UNLOAD_VALUE (m_low_hard_range  , low_hard_range );
	  UNLOAD_VALUE (m_high_hard_range  , hi_hard_range );
	  UNLOAD_VALUE (m_high_economy  , high_economy );
    
    if (bChanged)
       m_area->m_pDoc->SetModifiedFlag ();
    }

}


BEGIN_MESSAGE_MAP(CAreaRangesView, CDialog)
	//{{AFX_MSG_MAP(CAreaRangesView)
	ON_EN_CHANGE(IDC_LOW_ECONOMY, OnChangeEconomy)
	ON_EN_CHANGE(IDC_HIGH_ECONOMY, OnChangeEconomy)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAreaRangesView message handlers

void CAreaRangesView::OnChangeEconomy() 
{

CString strField;

// get text of window

m_ctlLowEconomy.GetWindowText(strField);

// convert to number

int iLowEconomy = atoi (strField);

// get text of window

m_ctlHighEconomy.GetWindowText(strField);

// convert to number

int iHighEconomy = atoi (strField);

__int64 economy = (__int64) iHighEconomy * 1000000000 + 
                  (__int64) iLowEconomy;


char sTotalEconomy [30];

sprintf (sTotalEconomy, "%I64d", economy);

m_ctlTotalEconomy.SetWindowText (sTotalEconomy);
	
}
