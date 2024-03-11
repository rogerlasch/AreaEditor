/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// FindDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "FindDlg.h"
#include "AreaEditorDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFindDlg dialog


CFindDlg::CFindDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFindDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFindDlg)
	m_bMatchCase = FALSE;
	m_iFindType = -1;
	m_bAllAreas = FALSE;
	//}}AFX_DATA_INIT
}


void CFindDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFindDlg)
	DDX_Control(pDX, IDC_FIND_TEXT, m_ctlFindText);
	DDX_Check(pDX, IDC_MATCH_CASE, m_bMatchCase);
	DDX_Radio(pDX, IDC_FIND_TYPE, m_iFindType);
	DDX_MinMaxCBString(pDX, IDC_FIND_TEXT, m_strFindText);
	DDV_MinMaxCBString(pDX, m_strFindText, 1, 1000);
	DDX_Check(pDX, IDC_ALL_AREAS, m_bAllAreas);
	//}}AFX_DATA_MAP

  if (pDX->m_bSaveAndValidate)
    {
    
    if (m_iFindType == eFindVnum)
      {
      CString strValidate = m_strFindText;
      strValidate.TrimLeft ();
      strValidate.TrimRight ();
      strValidate.MakeUpper ();

      if (strValidate [0] == 'M' 
        || strValidate [0] == 'O' 
        || strValidate [0] == 'R')
        {
        strValidate = strValidate.Mid (1);
        strValidate.TrimLeft ();
        }

      int vnum = atoi (strValidate);

      for (int i = 0; i < strValidate.GetLength (); i++)
        if (!isdigit (strValidate [i]))
          {
          ::AfxMessageBox ("VNUM must be numeric (optionally starting with M, O, or R)",
                            MB_ICONSTOP);
          DDX_Text(pDX, IDC_FIND_TEXT, m_strFindText);
          pDX->Fail();

          }   // end of bad vnum
      
      }   // end of finding a vnum


    } // end of saving and validating
  else
    {

    // fill the list box in reverse order with the previous things they found
    for (POSITION pos = App.m_strFindText.GetTailPosition (); pos; )
      m_ctlFindText.AddString (App.m_strFindText.GetPrev (pos));
    } // end of not saving


}


BEGIN_MESSAGE_MAP(CFindDlg, CDialog)
	//{{AFX_MSG_MAP(CFindDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFindDlg message handlers

