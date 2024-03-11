/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// MUDProgramView.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "AreaEditorDoc.h"

#include "ObjectView.h"
#include "MUDProgramView.h"
#include "EditDlg.h"
#include "defaults.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMUDProgramView

IMPLEMENT_DYNCREATE(CMUDProgramView, CFormView)

CMUDProgramView::CMUDProgramView()
	: CFormView(CMUDProgramView::IDD)
{
	//{{AFX_DATA_INIT(CMUDProgramView)
	m_comlist = _T("");
	//}}AFX_DATA_INIT

  m_program = NULL;
  m_font = NULL;

}

CMUDProgramView::~CMUDProgramView()
{
  delete m_font;
}

#undef LOAD_VALUE
#define LOAD_VALUE(field, value)  \
  field = m_program->value

#undef UNLOAD_VALUE
#define UNLOAD_VALUE(field, value)  \
  do {    \
    if (field != m_program->value) bChanged = true; \
    m_program->value = field;   \
    }  while (false)

void CMUDProgramView::DoDataExchange(CDataExchange* pDX)
{
 bool bChanged = false;

 if (!pDX->m_bSaveAndValidate && m_program)
    {
    LOAD_VALUE (m_arglist, arglist);
    LOAD_VALUE (m_comlist, comlist);
    }

  CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMUDProgramView)
	DDX_Control(pDX, IDC_PROGRAM_TYPE, m_ctlProgramType);
	DDX_Control(pDX, IDC_COMLIST, m_ctlcomlist);
	DDX_Text(pDX, IDC_COMLIST, m_comlist);
	DDX_MinMaxString(pDX, IDC_ARGLIST, m_arglist);
	DDV_MinMaxString(pDX, m_arglist, 1, 1000);
	//}}AFX_DATA_MAP

  if (!pDX->m_bSaveAndValidate)
    {

    if (m_program)
      LoadComboBoxList (m_ctlProgramType, ProgramNameList, m_program->type);

    }   // end of not saving and validating

  if (pDX->m_bSaveAndValidate && m_program)
    {

    // tilde is a FATAL error - do not allow them to ignore it
    CheckForTilde (pDX, IDC_COMLIST, m_comlist);
    CheckForTilde (pDX, IDC_ARGLIST, m_arglist);
  
    // put it in a try block, they can ignore syntax check errors
    try
      {

      CString strMessage;

      if (CheckCommandSyntax (m_comlist, 
                              strMessage, 
                              m_program->xref_rooms,
                              m_program->xref_objects,
                              m_program->xref_mobs))
        {
        ::AfxMessageBox (strMessage, MB_ICONEXCLAMATION);
        DDX_Text(pDX, IDC_COMLIST, m_comlist);
        pDX->Fail();
        return;
        }

      } // end of try block

    catch (CUserException * e)
      {

      if (App.m_bIgnoreValidationErrors && 
          ::AfxMessageBox ("Ignore this error?", 
          MB_YESNO | MB_DEFBUTTON2 | MB_ICONQUESTION)
          == IDYES)
        e->Delete ();
      else
        throw;
      } // end of catch

    UNLOAD_VALUE (m_arglist, arglist);
    UNLOAD_VALUE (m_comlist, comlist);

    int i;
    if (UnloadComboBox (m_ctlProgramType, i))
	    UNLOAD_VALUE (i, type);

    m_program->m_pTreeCtrl->SetItemText (m_program->m_hdlTreeItem, m_program->Summary ());
     if (bChanged)
       m_program->m_pDoc->SetModifiedFlag ();
    } // end of validating



}


BEGIN_MESSAGE_MAP(CMUDProgramView, CFormView)
	//{{AFX_MSG_MAP(CMUDProgramView)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_EDIT_PROGRAM, OnEditProgram)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMUDProgramView diagnostics

#ifdef _DEBUG
void CMUDProgramView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMUDProgramView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMUDProgramView message handlers

void CMUDProgramView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
// resize commands so they fit in new window size
  
  if (m_ctlcomlist.m_hWnd)
    {
    WINDOWPLACEMENT wp;

    m_ctlcomlist.GetWindowPlacement (&wp);
    wp.rcNormalPosition.right = cx - 10 - wp.rcNormalPosition.left;
    wp.rcNormalPosition.bottom = cy - 10 - wp.rcNormalPosition.top;

	  m_ctlcomlist.SetWindowPos(NULL, 
                            0,
                            0,
                            wp.rcNormalPosition.right,
                            wp.rcNormalPosition.bottom,
                            SWP_NOACTIVATE | 
                            SWP_NOMOVE | 
                            SWP_NOOWNERZORDER | 
                            SWP_NOZORDER 
      );
    }
	
}

void CMUDProgramView::OnEditProgram() 
{
CEditDlg dlg;

	m_ctlcomlist.GetWindowText (dlg.m_strEditText);

  dlg.m_bProgram = true;    // tell it we are editing a program

  if (dlg.DoModal () != IDOK)
    return;

  m_ctlcomlist.SetWindowText (dlg.m_strEditText);
	
}
