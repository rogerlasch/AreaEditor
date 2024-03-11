/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// EditCommandDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "EditCommandDlg.h"
#include "defaults.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditCommandDlg dialog


CEditCommandDlg::CEditCommandDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditCommandDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditCommandDlg)
	m_level = 0;
	m_log = 0;
	m_name = _T("");
	m_position = 0;
	m_do_fun = _T("");
	m_possessed = FALSE;
	m_polymorphed = FALSE;
	m_watch = FALSE;
	//}}AFX_DATA_INIT

  m_bAdd = false;

}


void CEditCommandDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditCommandDlg)
	DDX_Control(pDX, IDC_FUNCTION, m_ctlFunction);
	DDX_Text(pDX, IDC_LOG, m_log);
	DDX_Text(pDX, IDC_NAME, m_name);
	DDX_Text(pDX, IDC_POSITION, m_position);
	DDX_CBString(pDX, IDC_FUNCTION, m_do_fun);
	DDX_Check(pDX, IDC_POSSESSED, m_possessed);
	DDX_Check(pDX, IDC_POLYMORPHED, m_polymorphed);
	DDX_Check(pDX, IDC_WATCH, m_watch);
	//}}AFX_DATA_MAP
  DDX_Text(pDX, IDC_LEVEL, m_level);
	DDV_MinMaxInt(pDX, m_level, 0, iMaxLevel);


  if (pDX->m_bSaveAndValidate)
    {
    m_name.TrimLeft ();
    m_name.TrimRight ();

    if (m_name.IsEmpty ())
      {
      ::AfxMessageBox ("Command must have a name");
      DDX_Text(pDX, IDC_NAME, m_name);
      pDX->Fail();
      }
            
    m_name.MakeLower ();    // I think this is wise

    m_do_fun.TrimLeft ();
    m_do_fun.TrimRight ();

    if (m_do_fun.IsEmpty ())
      {
      ::AfxMessageBox ("Please choose a function before proceeding",
                        MB_ICONSTOP);
      pDX->Fail();
      }   // end of no function chosen

    // look for duplicates

    if (m_bAdd)
      for (POSITION commandPos = App.m_CommandList.GetHeadPosition (); commandPos; )
        {
        CCommand * command = App.m_CommandList.GetNext (commandPos);

        if (command->name.CompareNoCase (m_name) == 0)
          {
          ::AfxMessageBox (CFormat ("There is already a command called \"%s\"",
                          (LPCTSTR) m_name));
          DDX_Text(pDX, IDC_NAME, m_name);
          pDX->Fail();
          }
        }

    CheckForTilde (pDX, IDC_NAME, m_name);

    }
  else
    {
    LoadComboBoxList (m_ctlFunction, SMAUGSkillNameList, -1);
    m_ctlFunction.SelectString(-1, m_do_fun);
    }

}


BEGIN_MESSAGE_MAP(CEditCommandDlg, CDialog)
	//{{AFX_MSG_MAP(CEditCommandDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditCommandDlg message handlers
