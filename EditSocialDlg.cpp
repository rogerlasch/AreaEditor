/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// EditSocialDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "EditSocialDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditSocialDlg dialog


CEditSocialDlg::CEditSocialDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditSocialDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditSocialDlg)
	m_char_auto = _T("");
	m_char_found = _T("");
	m_char_no_arg = _T("");
	m_name = _T("");
	m_others_auto = _T("");
	m_others_found = _T("");
	m_others_no_arg = _T("");
	m_vict_found = _T("");
	//}}AFX_DATA_INIT

  m_bAdd = false;

}


void CEditSocialDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditSocialDlg)
	DDX_Text(pDX, IDC_CHAR_AUTO, m_char_auto);
	DDX_Text(pDX, IDC_CHAR_FOUND, m_char_found);
	DDX_Text(pDX, IDC_CHAR_NO_ARG, m_char_no_arg);
	DDX_Text(pDX, IDC_NAME, m_name);
	DDX_Text(pDX, IDC_OTHERS_AUTO, m_others_auto);
	DDX_Text(pDX, IDC_OTHERS_FOUND, m_others_found);
	DDX_Text(pDX, IDC_OTHERS_NO_ARG, m_others_no_arg);
	DDX_Text(pDX, IDC_VICT_FOUND, m_vict_found);
	//}}AFX_DATA_MAP

  if (pDX->m_bSaveAndValidate)
    {
  
    m_name.TrimLeft ();
    m_name.TrimRight ();

    if (m_name.IsEmpty ())
      {
      ::AfxMessageBox ("Social must have a name");
      DDX_Text(pDX, IDC_NAME, m_name);
      pDX->Fail();
      }
            
    m_name.MakeLower ();    // I think this is wise

    m_char_no_arg.TrimLeft ();
    m_char_no_arg.TrimRight ();

    if (m_char_no_arg.IsEmpty ())
      {
      ::AfxMessageBox ("Social must have a \"Char no-arg\" entry.");
      DDX_Text(pDX, IDC_CHAR_NO_ARG, m_char_no_arg);
      pDX->Fail();
      }

    // look for duplicates

    if (m_bAdd)
      for (POSITION socialPos = App.m_SocialList.GetHeadPosition (); socialPos; )
        {
        CSocial * social = App.m_SocialList.GetNext (socialPos);

        if (social->name.CompareNoCase (m_name) == 0)
          {
          ::AfxMessageBox (CFormat ("There is already a social called \"%s\"",
                          (LPCTSTR) m_name));
          DDX_Text(pDX, IDC_NAME, m_name);
          pDX->Fail();
          }
        }

    CheckForTilde (pDX, IDC_CHAR_AUTO, m_char_auto);
    CheckForTilde (pDX, IDC_CHAR_FOUND, m_char_found);
    CheckForTilde (pDX, IDC_CHAR_NO_ARG, m_char_no_arg);
    CheckForTilde (pDX, IDC_NAME, m_name);
    CheckForTilde (pDX, IDC_OTHERS_AUTO, m_others_auto);
    CheckForTilde (pDX, IDC_OTHERS_FOUND, m_others_found);
    CheckForTilde (pDX, IDC_OTHERS_NO_ARG, m_others_no_arg);
    CheckForTilde (pDX, IDC_VICT_FOUND, m_vict_found);

    }   // end of save and validate

}


BEGIN_MESSAGE_MAP(CEditSocialDlg, CDialog)
	//{{AFX_MSG_MAP(CEditSocialDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditSocialDlg message handlers
