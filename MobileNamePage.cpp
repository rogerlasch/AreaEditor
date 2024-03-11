/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// MobileNamePage.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "AreaEditorDoc.h"
#include "defaults.h"

#include "MobileView.h"
#include "MobileNamePage.h"
#include "EditDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMobileNamePage dialog


CMobileNamePage::CMobileNamePage(CWnd* pParent /*=NULL*/)
	: CDialog(CMobileNamePage::IDD, pParent)
{

	//{{AFX_DATA_INIT(CMobileNamePage)
	m_player_name = _T("");
	m_short_descr = _T("");
	m_long_descr = _T("");
	m_description = _T("");
	m_level = 0;
	m_vnum = 0;
	//}}AFX_DATA_INIT

  m_mob = NULL;
  m_font = NULL;
  m_OriginalVnum = 0;

}

CMobileNamePage::~CMobileNamePage ()
  {
  delete m_font;
  }

#undef LOAD_VALUE
#define LOAD_VALUE(field, value)  \
  field = m_mob->value

#undef UNLOAD_VALUE
#define UNLOAD_VALUE(field, value)  \
  do {    \
    if (field != m_mob->value) bChanged = true; \
    m_mob->value = field;   \
    } while (false)

void CMobileNamePage::DoDataExchange(CDataExchange* pDX)
{
bool bChanged = false;

  if (!pDX->m_bSaveAndValidate)
    {
	  LOAD_VALUE (m_player_name, player_name);
	  LOAD_VALUE (m_short_descr, short_descr);
	  LOAD_VALUE (m_long_descr , long_descr);  
	  LOAD_VALUE (m_description, description);
    LOAD_VALUE (m_level, level);
  	LOAD_VALUE (m_vnum, vnum);
    m_OriginalVnum = m_vnum;
    }

	CDialog::DoDataExchange(pDX);

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
      if (CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_MOB_NAME))
        App.SpellCheck (this, &m_ctlName);
      if (CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_MOB_SHORT))
        App.SpellCheck (this, &m_ctlShortDescription);
      if (CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_MOB_LONG))
        App.SpellCheck (this, &m_ctlLongDescription);
      if (CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_MOB_DESC))
        App.SpellCheck (this, &m_ctlDescription);
      }
#endif // SPELL_CHECKER

    }

	//{{AFX_DATA_MAP(CMobileNamePage)
	DDX_Control(pDX, IDC_SHORT_DESCRIPTION, m_ctlShortDescription);
	DDX_Control(pDX, IDC_LONG_DESCRIPTION, m_ctlLongDescription);
	DDX_Control(pDX, IDC_NAME, m_ctlName);
	DDX_Control(pDX, IDC_SEX, m_ctlSex);
	DDX_Control(pDX, IDC_SPEC_FUN, m_ctlSpecFun);
	DDX_Control(pDX, IDC_DESCRIPTION, m_ctlDescription);
	DDX_Text(pDX, IDC_NAME, m_player_name);
	DDX_Text(pDX, IDC_SHORT_DESCRIPTION, m_short_descr);
	DDX_Text(pDX, IDC_DESCRIPTION, m_description);
	//}}AFX_DATA_MAP

	DDX_Text(pDX, IDC_LONG_DESCRIPTION, m_long_descr);
	DDV_MaxChars(pDX, m_long_descr, iMaxDescriptionLength);
	DDX_Text(pDX, IDC_LEVEL, m_level);
	DDV_MinMaxInt(pDX, m_level, 0, iMaxLevel);
	DDX_Text(pDX, IDC_VNUM, m_vnum);
	DDV_MinMaxInt(pDX, m_vnum, 1, iMaxVnum);

  if (!pDX->m_bSaveAndValidate)
    {
    LoadComboBoxList (m_ctlSpecFun, MobSpecialList, m_mob->spec_fun);
    LoadComboBoxList (m_ctlSex, MobSexList, m_mob->sex);
    }

  if (pDX->m_bSaveAndValidate)
    {

    // tilde is a FATAL error - do not allow them to ignore it
    CheckForTilde (pDX, IDC_NAME, m_player_name);
    CheckForTilde (pDX, IDC_SHORT_DESCRIPTION, m_short_descr);
    CheckForTilde (pDX, IDC_LONG_DESCRIPTION, m_long_descr);
    CheckForTilde (pDX, IDC_DESCRIPTION, m_description);

    // put it in a try block, they can ignore these errors
    try
      {
    
      if (m_vnum < m_mob->m_pDoc->m_Area->mob_low_vnum ||
          m_vnum > m_mob->m_pDoc->m_Area->mob_hi_vnum )
        {
        if (::AfxMessageBox(
                          CFormat ("The vnum must be in the range %i to %i.\n\n"
                                   "Adjust permitted range to include this in it?",
          m_mob->m_pDoc->m_Area->mob_low_vnum, m_mob->m_pDoc->m_Area->mob_hi_vnum),
          MB_ICONQUESTION | MB_YESNO) == IDNO)
          {
          DDX_Text(pDX, IDC_VNUM, m_vnum);
          pDX->Fail();       
          return;
          }

        if (m_vnum < m_mob->m_pDoc->m_Area->mob_low_vnum)
          m_mob->m_pDoc->m_Area->mob_low_vnum = m_vnum;
        if (m_vnum > m_mob->m_pDoc->m_Area->mob_hi_vnum)
          m_mob->m_pDoc->m_Area->mob_hi_vnum = m_vnum;
         m_mob->m_pDoc->SetModifiedFlag ();
        }     // end of vnum being out of range

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

    CMobile * mob;

    if ((mob = FindMob (m_vnum)) && (mob != m_mob))
      {
      ::AfxMessageBox(CFormat ("This vnum is already used by mobile: %s.",
        (LPCTSTR) mob->Summary ()),
        MB_ICONEXCLAMATION);
      DDX_Text(pDX, IDC_VNUM, m_vnum);
      pDX->Fail();
      return;
      }     // end of vnum in use

	  UNLOAD_VALUE (m_player_name, player_name);
	  UNLOAD_VALUE (m_short_descr, short_descr);
	  UNLOAD_VALUE (m_long_descr , long_descr);  
	  UNLOAD_VALUE (m_description, description);
    UNLOAD_VALUE (m_level, level);
  	UNLOAD_VALUE (m_vnum, vnum);

    int i;
    if (UnloadComboBox (m_ctlSex, i))
	    UNLOAD_VALUE (i, sex);

    if (UnloadComboBox (m_ctlSpecFun, i))
	    UNLOAD_VALUE (i, spec_fun);

// ** DO THIS LAST! ** - if vnum changes, reorganise position in list and tree ctrl
    if (m_OriginalVnum != m_vnum)
      {
      CAreaEditorDoc* pDoc = m_mob->m_pDoc;
      ASSERT_VALID(pDoc);

      if (!pDoc->AreaRenumber (eRenumberMob, m_OriginalVnum, m_vnum))
        {   // renumber of area failed
        m_vnum = m_OriginalVnum;        // cancel change
      	UNLOAD_VALUE (m_vnum, vnum);    // put mob vnum back
        }
      else
        {

        CMobile * mob,
                * prevMob = NULL;

        // find the highest mob with a vnum lower than this one
        for (POSITION mobPos = pDoc->m_MobList.GetHeadPosition (); mobPos; )
          {
          mob = pDoc->m_MobList.GetNext (mobPos);
          if (mob->vnum < m_vnum)
            prevMob = mob;
          }

        // delete from list of mobs

        pDoc->m_MobList.RemoveAt (pDoc->m_MobList.Find (m_mob, NULL));

        // re-add in new position
        if (prevMob)
          pDoc->m_MobList.InsertAfter (pDoc->m_MobList.Find (prevMob, NULL), m_mob);    // and add it to our list
        else
          pDoc->m_MobList.AddHead (m_mob);    // nothing before? Add to start of list

        // resort mobiles tree so that it appears in the correct place

        m_mob->m_pTreeCtrl->SetItemText (m_mob->m_hdlTreeItem, m_mob->Summary ());
        m_mob->m_pTreeCtrl->SortChildren (m_mob->m_pTreeCtrl->GetParentItem(m_mob->m_hdlTreeItem));

        // remember new vnum in case they change it again
        m_OriginalVnum = m_vnum;
        } // end of renumbered mob OK
      }   // end of vnum changing

     if (bChanged)
       m_mob->m_pDoc->SetModifiedFlag ();

    }   // end of saving and validating

}


BEGIN_MESSAGE_MAP(CMobileNamePage, CDialog)
	//{{AFX_MSG_MAP(CMobileNamePage)
	ON_BN_CLICKED(IDC_EDIT_DESCRIPTION, OnEditDescription)
	ON_BN_CLICKED(IDC_EDIT_NAMES, OnEditNames)
	ON_BN_CLICKED(IDC_EDIT_SHORT_DESCRIPTION, OnEditShortDescription)
	ON_BN_CLICKED(IDC_EDIT_LONG_DESCRIPTION, OnEditLongDescription)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMobileNamePage message handlers


void CMobileNamePage::EditDescription (CEdit & ctlDescription, 
                                       const bool bEndline,
                                       const bool bSpellCheck)
  {
CEditDlg dlg;

CMobileView * wndParent = (CMobileView *) GetParent ();

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

void CMobileNamePage::OnEditDescription() 
{
  EditDescription (m_ctlDescription, true,
      CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_MOB_DESC));
}

void CMobileNamePage::OnEditNames() 
{
  EditDescription (m_ctlName, false, 
      CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_MOB_NAME));
}

void CMobileNamePage::OnEditShortDescription() 
{
  EditDescription (m_ctlShortDescription, false,
      CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_MOB_SHORT));
}

void CMobileNamePage::OnEditLongDescription() 
{
  EditDescription (m_ctlLongDescription, true,
      CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_MOB_LONG));
}

