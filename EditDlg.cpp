/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// EditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"

#include "AreaEditorDoc.h"

#include "EditDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditDlg dialog


CEditDlg::CEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditDlg)
	m_strEditText = _T("");
	//}}AFX_DATA_INIT

  m_font = NULL;
  m_bFirstTime = true;
  m_bProgram = false;
  m_bEndline = true;
  m_bSpellCheck = false;

}

// destructor
CEditDlg::~CEditDlg ()
  {
  delete m_font;
  }

void CEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditDlg)
	DDX_Control(pDX, IDC_SPELL_CHECK, m_ctlSpellCheck);
	DDX_Control(pDX, IDC_COLUMN_COUNT, m_ctlColumnCount);
	DDX_Control(pDX, IDC_WRAP, m_ctlWrap);
	DDX_Control(pDX, IDC_EDIT_TEXT, m_ctlEditText);
	DDX_Text(pDX, IDC_EDIT_TEXT, m_strEditText);
	//}}AFX_DATA_MAP

  if (!pDX->m_bSaveAndValidate)
    {
    FixFont (m_font, m_ctlEditText);

    if (m_font)
      m_ctlColumnCount.SendMessage (WM_SETFONT,
                                   (WPARAM) m_font->m_hObject,
                                    MAKELPARAM (TRUE, 0));

    CDC dc;

    RECT rect;

    dc.CreateCompatibleDC (NULL);
    dc.SelectObject(m_font);
  
    TEXTMETRIC tm;
    dc.GetTextMetrics(&tm);

    int m_FontHeight = tm.tmHeight; 
    int m_FontWidth = tm.tmAveCharWidth; 

    int iDialogWidth = m_FontWidth * (MAXDESCRIPTIONWIDTH - 1) +
                      (GetSystemMetrics (SM_CXFRAME) * 2) +  // allow for border
                      GetSystemMetrics (SM_CXVSCROLL) +  // allow for vertical scroll bar
                      4;      // allow for Windows 95 frame

    m_ctlEditText.GetWindowRect (&rect);

    m_ctlEditText.SetWindowPos (NULL, 0, 0, iDialogWidth, rect.bottom - rect.top, 
                SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_NOACTIVATE);

    // size the column counter
    m_ctlColumnCount.GetWindowRect (&rect);

    m_ctlColumnCount.SetWindowPos (NULL, 0, 0, iDialogWidth, rect.bottom - rect.top, 
                SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_NOACTIVATE);

    // now do the dialog itself

    // this calculation here is a complete wank - there is no reason for it to work
    iDialogWidth += GetSystemMetrics (SM_CXFRAME) + GetSystemMetrics (SM_CXVSCROLL);
    
    GetWindowRect (&rect);
    SetWindowPos (NULL, 0, 0, iDialogWidth, rect.bottom - rect.top, 
                  SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_NOACTIVATE);

    m_ctlEditText.SetSel (0, 0, FALSE);

    if (m_bProgram)
      {
      m_ctlWrap.ShowWindow (SW_HIDE);
      m_ctlSpellCheck.ShowWindow (SW_HIDE);   // spell checking programs is a bit problematic
      }
    else
      m_ctlColumnCount.SetWindowText ("         1         2         3         4         5         6         7"
                                      ENDLINE
                                      "1234567890123456789012345678901234567890123456789012345678901234567890123456789");

    }

}


BEGIN_MESSAGE_MAP(CEditDlg, CDialog)
	//{{AFX_MSG_MAP(CEditDlg)
	ON_EN_SETFOCUS(IDC_EDIT_TEXT, OnSetfocusEditText)
	ON_BN_CLICKED(IDC_WRAP, OnWrap)
	ON_BN_CLICKED(IDC_SPELL_CHECK, OnSpellCheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditDlg message handlers

void CEditDlg::OnSetfocusEditText() 
{
  if (m_bFirstTime)
    {
    m_ctlEditText.SetSel (0, 0, FALSE);
    m_bFirstTime = false;
    }
	
}


void CEditDlg::OnOK() 
{

CIntList xref_rooms,
         xref_objects,
         xref_mobs;

// if a description (ie, not a program) make sure lines aren't too long

if (m_bProgram)
  {
  CString strCommand,
          strMessage;
  m_ctlEditText.GetWindowText (strCommand);


  strCommand.TrimRight ();

  if (!strCommand.IsEmpty ())
    {

   // make sure it has a trailing ENDLINE
  if (strCommand.Right (strlen (ENDLINE)) != ENDLINE)
    strCommand += ENDLINE;

  // no commmands or socials loaded - cannot validate
  if (App.m_CommandList.IsEmpty () || App.m_SocialList.IsEmpty ())
       ::AfxMessageBox ("You must load COMMANDS.DAT and SOCIALS.DAT in order to validate programs",
              MB_ICONINFORMATION);
  else 
    if (CheckCommandSyntax (strCommand, strMessage,
                                xref_rooms,
                                xref_objects,
                                xref_mobs))
      {
      ::AfxMessageBox (strMessage, MB_ICONEXCLAMATION);
      return;
      }
    }   // end of non-empty program

  }   // end of having a program
else
  {
  if (m_bSpellCheck)
	  if (CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_CHECK_EDIT_WINDOW))
      App.SpellCheck (this, &m_ctlEditText);
  FixWrap (m_ctlEditText, m_bEndline);
  }

	CDialog::OnOK();
}

void CEditDlg::OnWrap() 
{

int nStartChar,
    nEndChar;
CString strText,
        strNewText;
//int iPos;

  m_ctlEditText.GetSel(nStartChar, nEndChar);
  m_ctlEditText.GetWindowText (strText);

  // get partial text if necessary
  if (nEndChar > nStartChar &&
                  nStartChar != -1 &&
                  nEndChar != -1)
    strText = strText.Mid (nStartChar, nEndChar - nStartChar);

  /*
  while ((iPos = strText.Find (ENDLINE)) != -1)
    {
    strNewText = strText.Left (iPos);
    strNewText += ' ';
    strNewText += strText.Mid (iPos + strlen (ENDLINE));
    strText = strNewText;
    }

  */
  strText.Replace (ENDLINE, " ");


  // do partial or full replacement
  if (nEndChar > nStartChar &&
                  nStartChar != -1 &&
                  nEndChar != -1)
    {
    m_ctlEditText.ReplaceSel(strText, TRUE);
    m_ctlEditText.SetSel(nStartChar, nStartChar + strText.GetLength ());
    }
  else
    m_ctlEditText.SetWindowText (strText);

  
}

void CEditDlg::OnSpellCheck() 
{
#ifdef SPELL_CHECKER

  if (App.m_bSpellCheckOK)
    App.SpellCheck (this, &m_ctlEditText);
#endif // SPELL_CHECKER
}

BOOL CEditDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
#ifdef SPELL_CHECKER
	
  // but *can* they spell check?
  m_ctlSpellCheck.EnableWindow (App.m_bSpellCheckOK);	

#endif // SPELL_CHECKER

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
