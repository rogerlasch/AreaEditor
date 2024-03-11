/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// HelpView.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"

#include "AreaEditorDoc.h"

#include "HelpView.h"
#include "EditDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHelpView

IMPLEMENT_DYNCREATE(CHelpView, CFormView)

CHelpView::CHelpView()
	: CFormView(CHelpView::IDD)
{
	//{{AFX_DATA_INIT(CHelpView)
	m_level = 0;
	m_text = _T("");
	m_keyword = _T("");
	//}}AFX_DATA_INIT

  m_help = NULL;

}

CHelpView::~CHelpView()
{
}

#undef LOAD_VALUE
#define LOAD_VALUE(field, value)  \
  field = m_help->value

#undef UNLOAD_VALUE
#define UNLOAD_VALUE(field, value)  \
  if (field != m_help->value) bChanged = true; \
  m_help->value = field

void CHelpView::DoDataExchange(CDataExchange* pDX)
{
bool bChanged = false;

  if (!pDX->m_bSaveAndValidate && m_help)
    {
	  LOAD_VALUE (m_keyword      , keyword     );
	  LOAD_VALUE (m_level  , level );
	  LOAD_VALUE (m_text   , text);
    }
  else if (pDX->m_bSaveAndValidate && m_help)
    {
#ifdef SPELL_CHECKER

    // spell check the various edit controls
    if (App.m_bSpellCheckOK && 
        CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_CHECK_ON_VIEW))
      {
      if (CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_HELP_TEXT))
        App.SpellCheck (this, &m_ctlHelp);
      }
#endif // SPELL_CHECKER

    }

	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHelpView)
	DDX_Control(pDX, IDC_TEXT, m_ctlHelp);
	DDX_Text(pDX, IDC_LEVEL, m_level);
	DDX_Text(pDX, IDC_TEXT, m_text);
	DDX_Text(pDX, IDC_KEYWORDS, m_keyword);
	//}}AFX_DATA_MAP

  if (pDX->m_bSaveAndValidate && m_help)
    {

    CheckForTilde (pDX, IDC_KEYWORDS, m_keyword);
    CheckForTilde (pDX, IDC_TEXT, m_text);

	  UNLOAD_VALUE (m_keyword      , keyword     );
	  UNLOAD_VALUE (m_level  , level );
	  UNLOAD_VALUE (m_text   , text);
     if (bChanged)
       m_help->m_pDoc->SetModifiedFlag ();
    }

  if (m_help)
    m_help->m_pTreeCtrl->SetItemText (m_help->m_hdlTreeItem, m_help->Summary ());
}


BEGIN_MESSAGE_MAP(CHelpView, CFormView)
	//{{AFX_MSG_MAP(CHelpView)
	ON_BN_CLICKED(IDC_EDIT_HELP, OnEditHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHelpView diagnostics

#ifdef _DEBUG
void CHelpView::AssertValid() const
{
	CFormView::AssertValid();
}

void CHelpView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHelpView message handlers

void CHelpView::OnEditHelp() 
{
CEditDlg dlg;

	m_ctlHelp.GetWindowText (dlg.m_strEditText);

  dlg.m_bEndline = true;
  dlg.m_bSpellCheck = CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_HELP_TEXT);

  if (dlg.DoModal () != IDOK)
    return;
  
  m_ctlHelp.SetWindowText (dlg.m_strEditText);
	
}
