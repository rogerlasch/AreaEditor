/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// EditAffectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "EditAffectDlg.h"
#include "defaults.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditAffectDlg dialog


CEditAffectDlg::CEditAffectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditAffectDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditAffectDlg)
	m_iFlags = 0;
	m_strDuration = _T("");
	m_strModifier = _T("");
	//}}AFX_DATA_INIT
}


void CEditAffectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditAffectDlg)
	DDX_Control(pDX, IDC_TYPE, m_ctlType);
	DDX_Control(pDX, IDC_FLAGS, m_ctlFlags);
	DDX_Control(pDX, IDC_FLAG_MEANINGS, m_ctlFlagMeanings);
	DDX_Text(pDX, IDC_FLAGS, m_iFlags);
	DDX_Text(pDX, IDC_DURATION, m_strDuration);
	DDX_Text(pDX, IDC_MODIFIER, m_strModifier);
	//}}AFX_DATA_MAP

  if (pDX->m_bSaveAndValidate)
    {
    int i;
    if (!UnloadComboBox (m_ctlType, i))
        {
        ::AfxMessageBox ("Please choose an affect type",
                          MB_ICONSTOP);
        pDX->Fail();
        }   // end of no type chosen
      else
  	    m_iLocation = i;


    if (m_strDuration.IsEmpty ())
      {
      ::AfxMessageBox ("Duration cannot be blank",
                        MB_ICONSTOP);
      pDX->Fail();
      }   // end of no duration chosen

    if (m_strModifier.IsEmpty ())
      {
      ::AfxMessageBox ("Modifier cannot be blank",
                        MB_ICONSTOP);
      pDX->Fail();
      }   // end of no modifier chosen


    }
  else
    LoadComboBoxList (m_ctlType, ObjectAffectList, m_iLocation);

}


BEGIN_MESSAGE_MAP(CEditAffectDlg, CDialog)
	//{{AFX_MSG_MAP(CEditAffectDlg)
	ON_EN_CHANGE(IDC_FLAGS, OnChangeFlags)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditAffectDlg message handlers

void CEditAffectDlg::OnChangeFlags() 
{
CString strFlags;

  m_ctlFlags.GetWindowText (strFlags);

int iFlag = atoi (strFlags);

  m_ctlFlagMeanings.SetWindowText (convert_affectflag (iFlag));
}

