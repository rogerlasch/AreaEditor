/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// ObjectAffectView.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "AreaEditorDoc.h"
#include "defaults.h"

#include "ObjectAffectView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static int iCheckBoxes [32] =

  {
  IDC_FLAG1,
  IDC_FLAG2,
  IDC_FLAG3,
  IDC_FLAG4,
  IDC_FLAG5,
  IDC_FLAG6,
  IDC_FLAG7,
  IDC_FLAG8,
  IDC_FLAG9,
  IDC_FLAG10,
  IDC_FLAG11,
  IDC_FLAG12,
  IDC_FLAG13,
  IDC_FLAG14,
  IDC_FLAG15,
  IDC_FLAG16,
  IDC_FLAG17,
  IDC_FLAG18,
  IDC_FLAG19,
  IDC_FLAG20,
  IDC_FLAG21,
  IDC_FLAG22,
  IDC_FLAG23,
  IDC_FLAG24,
  IDC_FLAG25,
  IDC_FLAG26,
  IDC_FLAG27,
  IDC_FLAG28,
  IDC_FLAG29,
  IDC_FLAG30,
  IDC_FLAG31,
  IDC_FLAG32
  };

/////////////////////////////////////////////////////////////////////////////
// CObjectAffectView

IMPLEMENT_DYNCREATE(CObjectAffectView, CFormView)

CObjectAffectView::CObjectAffectView()
	: CFormView(CObjectAffectView::IDD)
{
	//{{AFX_DATA_INIT(CObjectAffectView)
	m_modifier = 0;
	//}}AFX_DATA_INIT

  m_affect = NULL;

}

CObjectAffectView::~CObjectAffectView()
{
}

#undef LOAD_VALUE
#define LOAD_VALUE(field, value)  \
  field = (int) m_affect->value

#undef UNLOAD_VALUE
#define UNLOAD_VALUE(field, value)  \
  do {    \
    if (field != m_affect->value) bChanged = true; \
    m_affect->value = field;   \
    } while (false)

void CObjectAffectView::DoDataExchange(CDataExchange* pDX)
{
bool bChanged = false;

  if (!pDX->m_bSaveAndValidate && m_affect)
    {
    CButton * ctlChkBox;
    int i;

    // set the bits in the check boxes according to the bit vector
    for (i = 0; i < MAX_BITS; i++)
      {
      ctlChkBox = (CButton *) GetDlgItem (iCheckBoxes [i]);
      if (ctlChkBox)
        ctlChkBox->SetCheck (IS_SET(m_affect->bitvector, 1 << i ));
      }   // end of fixing up each check box

    LOAD_VALUE (m_modifier, modifier);
    }

	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CObjectAffectView)
	DDX_Control(pDX, IDC_WHAT_LABEL, m_ctlWhatLabel);
	DDX_Control(pDX, IDC_WHERE_LABEL, m_ctlWhereLabel);
	DDX_Control(pDX, IDC_AFFECT_TYPE, m_ctlAffectWhere);
	DDX_Control(pDX, IDC_LOCATION, m_ctlLocation);
	DDX_Text(pDX, IDC_MODIFIER, m_modifier);
	//}}AFX_DATA_MAP

  if (!pDX->m_bSaveAndValidate && m_affect)
    {
    LoadComboBoxList (m_ctlLocation, ObjectAffectList, m_affect->location);
    LoadComboBoxList (m_ctlAffectWhere, ObjectAffectWhereList, m_affect->where);

    // bitvectors only apply to ROM
    if (m_affect->m_pDoc->m_AreaType != eROM)
      {
      m_ctlWhatLabel.ShowWindow (SW_HIDE);
      m_ctlWhereLabel.ShowWindow (SW_HIDE);
      m_ctlAffectWhere.ShowWindow (SW_HIDE);
      }

    // show bitvector labels
    OnSelchangeAffectType ();
    }   // end of not saving and validating

  if (pDX->m_bSaveAndValidate && m_affect)
    {

    if (m_affect->m_pDoc->m_AreaType == eROM && m_pFlagsArray)
      {
      // unload the flag values
        
        CButton * ctlChkBox;
        int i;
  
        // remember old flags value
        EXT_BV iOldValue = m_affect->bitvector;

        for (i = 0; i < MAX_BITS; i++)
          {
          ctlChkBox = (CButton *) GetDlgItem (iCheckBoxes [i]);
          if (ctlChkBox)
            if (!m_pFlagsArray->strName [i].IsEmpty ())
              {
              if (ctlChkBox->GetCheck ())
                SET_BIT (m_affect->bitvector, 1 << i);
              else
                REMOVE_BIT (m_affect->bitvector, 1 << i);
              }
          }   // end of checking the state of each check box

        // note if document has changed
        if (iOldValue != m_affect->bitvector)
          m_affect->m_pDoc->SetModifiedFlag ();

      }   // end of ROM

	  UNLOAD_VALUE (m_modifier, modifier);

    int i;
    if (UnloadComboBox (m_ctlLocation, i))
  	  UNLOAD_VALUE (i, location);

    if (UnloadComboBox (m_ctlAffectWhere, i))
  	  UNLOAD_VALUE (i, where);

    m_affect->m_pTreeCtrl->SetItemText (m_affect->m_hdlTreeItem, m_affect->Summary ());

     if (bChanged)
       m_affect->m_pDoc->SetModifiedFlag ();
    
    }

}


BEGIN_MESSAGE_MAP(CObjectAffectView, CFormView)
	//{{AFX_MSG_MAP(CObjectAffectView)
	ON_CBN_SELCHANGE(IDC_AFFECT_TYPE, OnSelchangeAffectType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CObjectAffectView diagnostics

#ifdef _DEBUG
void CObjectAffectView::AssertValid() const
{
	CFormView::AssertValid();
}

void CObjectAffectView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CObjectAffectView message handlers


void CObjectAffectView::OnSelchangeAffectType() 
{

  if (!m_affect)
    return;
  
  CButton * ctlChkBox;
  int i;

  // not ROM - hide 32 flags check boxes
  if (m_affect->m_pDoc->m_AreaType != eROM)
    {
    for (i = 0; i < 32; i++)
      {
      ctlChkBox = (CButton *) GetDlgItem (iCheckBoxes [i]);
      if (ctlChkBox)
        ctlChkBox->ShowWindow(SW_HIDE);
      }
    return;
    }

  // get new value of combo box
  int iWhere;
  if (!UnloadComboBox (m_ctlAffectWhere, iWhere))
  	iWhere = -1;   // nothing selected

  // work out what sort of affect we have
  switch(iWhere)   
    {
		  case TO_AFFECTS:
          m_pFlagsArray = &MobAffectFlags;
          break;
      case TO_WEAPON:
          m_pFlagsArray = &ObjectWeaponFlags;
		      break;
      case TO_OBJECT:
//          m_pFlagsArray = &ObjectFlags;
          m_pFlagsArray = NULL;
          break;
      case TO_IMMUNE:
          m_pFlagsArray = &MobResistFlags;
          break;
      case TO_RESIST:
          m_pFlagsArray = &MobResistFlags;
          break;
      case TO_VULN:
          m_pFlagsArray = &MobResistFlags;
          break;
      default:
          m_pFlagsArray = NULL;
          break;
    }   // end of switch

  // adjust labels accordingly

  BOOL bShowFlagNumbers = App.GetProfileInt  (sProfilePreferences, sProfileShowFlagNumbers, 0);

  for (i = 0; i < 32; i++)
    {
    ctlChkBox = (CButton *) GetDlgItem (iCheckBoxes [i]);
    if (ctlChkBox)
      if (m_pFlagsArray == NULL || 
          m_pFlagsArray->strName [i].IsEmpty ())
         ctlChkBox->ShowWindow(SW_HIDE);
      else
        {
        ctlChkBox->ShowWindow(SW_SHOW);
        CString strOldTitle;
        CString strNewTitle;

        ctlChkBox->GetWindowText (strOldTitle);

        if (bShowFlagNumbers)
          {
          char c = 'A' + i;
          if (c > 'Z')
            c = 'a' + (i - 26);
          strNewTitle = CFormat ("%c. %s", c, (LPCTSTR) m_pFlagsArray->strName [i]);
          }
        else
          strNewTitle = m_pFlagsArray->strName [i];

        // avoid flicker
        if (strNewTitle != strOldTitle)
          ctlChkBox->SetWindowText (strNewTitle);
        }
    }   // end of fixing up each check box


    m_ctlWhatLabel.ShowWindow (m_pFlagsArray == NULL ? SW_HIDE : SW_SHOW);
  
}
