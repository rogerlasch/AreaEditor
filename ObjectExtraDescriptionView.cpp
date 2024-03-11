/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// ObjectExtraDescriptionView.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "AreaEditorDoc.h"

#include "ObjectExtraDescriptionView.h"
#include "EditDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CObjectExtraDescriptionView

IMPLEMENT_DYNCREATE(CObjectExtraDescriptionView, CFormView)

CObjectExtraDescriptionView::CObjectExtraDescriptionView()
	: CFormView(CObjectExtraDescriptionView::IDD)
{
	//{{AFX_DATA_INIT(CObjectExtraDescriptionView)
	m_keyword = _T("");
	m_description = _T("");
	//}}AFX_DATA_INIT

  m_extradescription = NULL;
  m_font = NULL;

}

CObjectExtraDescriptionView::~CObjectExtraDescriptionView()
{
  delete m_font;
}

#undef LOAD_VALUE
#define LOAD_VALUE(field, value)  \
  field = m_extradescription->value

#undef UNLOAD_VALUE
#define UNLOAD_VALUE(field, value)  \
  if (field != m_extradescription->value) bChanged = true; \
  m_extradescription->value = field

void CObjectExtraDescriptionView::DoDataExchange(CDataExchange* pDX)
{
bool bChanged = false;

  if (!pDX->m_bSaveAndValidate && m_extradescription)
    {
	  LOAD_VALUE (m_keyword, keyword);
	  LOAD_VALUE (m_description, description);
    }

	CFormView::DoDataExchange(pDX);

  if (pDX->m_bSaveAndValidate)
    {
    if (FixWrap (m_ctlDescription))
      {
      DDX_Text(pDX, IDC_DESCRIPTION, m_description);
      pDX->Fail();
      }
#ifdef SPELL_CHECKER

    // spell check the various edit controls
    if (App.m_bSpellCheckOK && 
        CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_CHECK_ON_VIEW))
      {
      if (CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_EXTRA_DESC))
        App.SpellCheck (this, &m_ctlDescription);
      }
#endif // SPELL_CHECKER

    }   // end of m_bSaveAndValidate

	//{{AFX_DATA_MAP(CObjectExtraDescriptionView)
	DDX_Control(pDX, IDC_DESCRIPTION, m_ctlDescription);
	DDX_Text(pDX, IDC_NAME, m_keyword);
	DDX_Text(pDX, IDC_DESCRIPTION, m_description);
	//}}AFX_DATA_MAP


  if (pDX->m_bSaveAndValidate && m_extradescription)
    {

    // tilde is a FATAL error - do not allow them to ignore it
    CheckForTilde (pDX, IDC_NAME, m_keyword);
    CheckForTilde (pDX, IDC_DESCRIPTION, m_description);

	  UNLOAD_VALUE (m_keyword, keyword);
	  UNLOAD_VALUE (m_description, description);
    m_extradescription->m_pTreeCtrl->SetItemText (m_extradescription->m_hdlTreeItem, m_extradescription->Summary ());

     if (bChanged)
       m_extradescription->m_pDoc->SetModifiedFlag ();
    }

}


BEGIN_MESSAGE_MAP(CObjectExtraDescriptionView, CFormView)
	//{{AFX_MSG_MAP(CObjectExtraDescriptionView)
	ON_BN_CLICKED(IDC_EDIT_DESCRIPTION, OnEditDescription)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CObjectExtraDescriptionView diagnostics

#ifdef _DEBUG
void CObjectExtraDescriptionView::AssertValid() const
{
	CFormView::AssertValid();
}

void CObjectExtraDescriptionView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CObjectExtraDescriptionView message handlers

void CObjectExtraDescriptionView::OnEditDescription() 
{
CEditDlg dlg;

	m_ctlDescription.GetWindowText (dlg.m_strEditText);

  dlg.m_bEndline = true;
  dlg.m_bSpellCheck = CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_EXTRA_DESC);

  if (dlg.DoModal () != IDOK)
    return;
  
  m_ctlDescription.SetWindowText (dlg.m_strEditText);
	
}
