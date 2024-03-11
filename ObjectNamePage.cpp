/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// ObjectNamePage.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "AreaEditorDoc.h"
#include "defaults.h"

#include "ObjectView.h"
#include "ObjectNamePage.h"
#include "EditDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CObjectNamePage dialog


CObjectNamePage::CObjectNamePage(CWnd* pParent /*=NULL*/)
	: CDialog(CObjectNamePage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CObjectNamePage)
	m_vnum = 0;
	m_name = _T("");
	m_short_descr = _T("");
	m_description = _T("");
	m_action_desc = _T("");
	//}}AFX_DATA_INIT

  m_object = NULL;
  m_font = NULL;
  m_OriginalVnum = 0;

}

CObjectNamePage::~CObjectNamePage ()
  {
  delete m_font;
  }

#undef LOAD_VALUE
#define LOAD_VALUE(field, value)  \
  field = m_object->value

#undef UNLOAD_VALUE
#define UNLOAD_VALUE(field, value)  \
  do {    \
    if (field != m_object->value) bChanged = true; \
    m_object->value = field;   \
    } while (false)

void CObjectNamePage::DoDataExchange(CDataExchange* pDX)
{
bool bChanged = false;

  if (!pDX->m_bSaveAndValidate)
    {
	  LOAD_VALUE (m_name, name);
	  LOAD_VALUE (m_short_descr, short_descr);
	  LOAD_VALUE (m_action_desc, action_desc);
	  LOAD_VALUE (m_description, description);
	  LOAD_VALUE (m_vnum, vnum);
    m_OriginalVnum = m_vnum;
    }

	CDialog::DoDataExchange(pDX);

  if (pDX->m_bSaveAndValidate)
    {
    if (FixWrap (m_ctlActionDescription))
      {
      DDX_Text(pDX, IDC_DESCRIPTION, m_action_desc);
      pDX->Fail();
      }
#ifdef SPELL_CHECKER

    // spell check the various edit controls
    if (App.m_bSpellCheckOK && 
        CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_CHECK_ON_VIEW))
      {
      if (CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_OBJECT_NAME))
        App.SpellCheck (this, &m_ctlName);
      if (CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_OBJECT_SHORT))
        App.SpellCheck (this, &m_ctlShortDescription);
      if (CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_OBJECT_LONG))
        App.SpellCheck (this, &m_ctlLongDescription);
      if (CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_OBJECT_ACTIONDESC))
        App.SpellCheck (this, &m_ctlActionDescription);
      }
#endif // SPELL_CHECKER

    }

	//{{AFX_DATA_MAP(CObjectNamePage)
	DDX_Control(pDX, IDC_SHORT_DESCRIPTION, m_ctlShortDescription);
	DDX_Control(pDX, IDC_NAME, m_ctlName);
	DDX_Control(pDX, IDC_LONG_DESCRIPTION, m_ctlLongDescription);
	DDX_Control(pDX, IDC_LOCATION, m_ctlType);
	DDX_Control(pDX, IDC_DESCRIPTION, m_ctlActionDescription);
	DDX_Text(pDX, IDC_NAME, m_name);
	DDX_Text(pDX, IDC_SHORT_DESCRIPTION, m_short_descr);
	DDX_Text(pDX, IDC_LONG_DESCRIPTION, m_description);
	DDX_Text(pDX, IDC_DESCRIPTION, m_action_desc);
	//}}AFX_DATA_MAP

	DDX_Text(pDX, IDC_VNUM, m_vnum);
	DDV_MinMaxInt(pDX, m_vnum, 1, iMaxVnum);

  if (!pDX->m_bSaveAndValidate && m_object)
    {

    LoadComboBoxList (m_ctlType, ObjectItemList, m_object->item_type);

    }   // end of not saving and validating

  if (pDX->m_bSaveAndValidate)
    {

    // tilde is a FATAL error - do not allow them to ignore it
    CheckForTilde (pDX, IDC_NAME, m_name);
    CheckForTilde (pDX, IDC_SHORT_DESCRIPTION, m_short_descr);
    CheckForTilde (pDX, IDC_LONG_DESCRIPTION, m_description);
    CheckForTilde (pDX, IDC_DESCRIPTION, m_action_desc);

    // put it in a try block, they can ignore these errors
    try
      {
      if (m_vnum < m_object->m_pDoc->m_Area->obj_low_vnum ||
          m_vnum > m_object->m_pDoc->m_Area->obj_hi_vnum )
        {
        if (::AfxMessageBox(
                          CFormat ("The vnum must be in the range %i to %i.\n\n"
                                   "Adjust permitted range to include this in it?",
          m_object->m_pDoc->m_Area->obj_low_vnum, m_object->m_pDoc->m_Area->obj_hi_vnum),
          MB_ICONQUESTION | MB_YESNO) == IDNO)
          {
          DDX_Text(pDX, IDC_VNUM, m_vnum);
          pDX->Fail();       
          return;
          }

        if (m_vnum < m_object->m_pDoc->m_Area->obj_low_vnum)
          m_object->m_pDoc->m_Area->obj_low_vnum = m_vnum;
        if (m_vnum > m_object->m_pDoc->m_Area->obj_hi_vnum)
          m_object->m_pDoc->m_Area->obj_hi_vnum = m_vnum;
         m_object->m_pDoc->SetModifiedFlag ();
        } // end of vnum out of range
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

    CMUDObject * obj;

    if ((obj = FindObj (m_vnum)) && (obj != m_object))
      {
      ::AfxMessageBox(CFormat ("This vnum is already used by object: %s.",
        (LPCTSTR) obj->Summary ()),
        MB_ICONEXCLAMATION);
      DDX_Text(pDX, IDC_VNUM, m_vnum);
      pDX->Fail();
      return;
      }     // end of vnum in use

	  UNLOAD_VALUE (m_name, name);
	  UNLOAD_VALUE (m_short_descr, short_descr);
	  UNLOAD_VALUE (m_action_desc, action_desc);
	  UNLOAD_VALUE (m_description, description);
	  UNLOAD_VALUE (m_vnum, vnum);

    int i;
    if (UnloadComboBox (m_ctlType, i))
	    UNLOAD_VALUE (i, item_type);

// ** DO THIS LAST! ** - if vnum changes, reorganise position in list and tree ctrl
    if (m_OriginalVnum != m_vnum)
      {
      CAreaEditorDoc* pDoc = m_object->m_pDoc;
      ASSERT_VALID(pDoc);

      if (!pDoc->AreaRenumber (eRenumberObj, m_OriginalVnum, m_vnum))
        {   // renumber of area failed
        m_vnum = m_OriginalVnum;        // cancel change
      	UNLOAD_VALUE (m_vnum, vnum);    // put object vnum back
        }
      else
        {

        CMUDObject * obj,
                   * prevObj = NULL;

        // find the highest object with a vnum lower than this one
        for (POSITION objPos = pDoc->m_ObjectList.GetHeadPosition (); objPos; )
          {
          obj = pDoc->m_ObjectList.GetNext (objPos);
          if (obj->vnum < m_vnum)
            prevObj = obj;
          }

        // delete from list of objects

        pDoc->m_ObjectList.RemoveAt (pDoc->m_ObjectList.Find (m_object, NULL));

        // re-add in new position
        if (prevObj)
          pDoc->m_ObjectList.InsertAfter (pDoc->m_ObjectList.Find (prevObj, NULL), m_object);    // and add it to our list
        else
          pDoc->m_ObjectList.AddHead (m_object);    // nothing before? Add to start of list

        // resort objiles tree so that it appears in the correct place

        m_object->m_pTreeCtrl->SetItemText (m_object->m_hdlTreeItem, m_object->Summary ());
        m_object->m_pTreeCtrl->SortChildren (m_object->m_pTreeCtrl->GetParentItem(m_object->m_hdlTreeItem));

        // remember new vnum in case they change it again
        m_OriginalVnum = m_vnum;
        } // end of renumbered OK
      }   // end of vnum changing

     if (bChanged)
       m_object->m_pDoc->SetModifiedFlag ();
    }

 }


BEGIN_MESSAGE_MAP(CObjectNamePage, CDialog)
	//{{AFX_MSG_MAP(CObjectNamePage)
	ON_BN_CLICKED(IDC_EDIT_DESCRIPTION, OnEditDescription)
	ON_BN_CLICKED(IDC_EDIT_NAMES, OnEditNames)
	ON_BN_CLICKED(IDC_EDIT_SHORT_DESCRIPTION, OnEditShortDescription)
	ON_BN_CLICKED(IDC_EDIT_LONG_DESCRIPTION, OnEditLongDescription)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CObjectNamePage message handlers


void CObjectNamePage::EditDescription (CEdit & ctlDescription, 
                                       const bool bEndline,
                                       const bool bSpellCheck)
  {
CEditDlg dlg;

CObjectView * wndParent = (CObjectView *) GetParent ();

	ctlDescription.GetWindowText (dlg.m_strEditText);

  wndParent->m_bEditingText = true;
  dlg.m_bEndline = bEndline;
  dlg.m_bSpellCheck = bSpellCheck;

  if (dlg.DoModal () != IDOK)
    {
    wndParent->m_bEditingText = false;
    return;
    }
  
  wndParent->m_bEditingText = false;

  ctlDescription.SetWindowText (dlg.m_strEditText);


  } // end of EditDescription


void CObjectNamePage::OnEditDescription() 
{
EditDescription (m_ctlActionDescription, true,
                 CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_OBJECT_ACTIONDESC));
}


void CObjectNamePage::OnEditNames() 
{
EditDescription (m_ctlName, false, 
                 CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_OBJECT_NAME));
}

void CObjectNamePage::OnEditShortDescription() 
{
EditDescription (m_ctlShortDescription, false,
                 CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_OBJECT_SHORT));
}

void CObjectNamePage::OnEditLongDescription() 
{
EditDescription (m_ctlLongDescription, true,
                 CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_OBJECT_LONG));
}
