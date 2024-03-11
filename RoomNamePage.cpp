/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// RoomNamePage.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "AreaEditorDoc.h"
#include "defaults.h"

#include "RoomNamePage.h"
#include "EditDlg.h"
#include "RoomView.h"

#include "ChooseRoomDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRoomNamePage dialog


CRoomNamePage::CRoomNamePage(CWnd* pParent /*=NULL*/)
	: CDialog(CRoomNamePage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRoomNamePage)
	m_description = _T("");
	m_name = _T("");
	m_vnum = 0;
	m_tele_vnum = 0;
	m_tunnel = 0;
	m_tele_delay = 0;
	m_clan = _T("");
	m_heal_rate = 0;
	m_mana_rate = 0;
	//}}AFX_DATA_INIT

  m_room = NULL;
  m_font = NULL;
  m_OriginalVnum = 0;
}

CRoomNamePage::~CRoomNamePage ()
  {
  delete m_font;
  }

#undef LOAD_VALUE
#define LOAD_VALUE(field, value)  \
  field = m_room->value

#undef UNLOAD_VALUE
#define UNLOAD_VALUE(field, value)  \
  do {    \
    if (field != m_room->value) bChanged = true; \
    m_room->value = field;   \
    } while (false)

void CRoomNamePage::DoDataExchange(CDataExchange* pDX)
{
bool bChanged = false;

  if (!pDX->m_bSaveAndValidate)
    {
	  LOAD_VALUE (m_vnum, vnum);
	  LOAD_VALUE (m_name, name);
	  LOAD_VALUE (m_description, description);
	  LOAD_VALUE (m_tele_vnum, tele_vnum);
	  LOAD_VALUE (m_tele_delay, tele_delay);
	  LOAD_VALUE (m_tunnel, tunnel);
	  LOAD_VALUE (m_clan, clan);
	  LOAD_VALUE (m_mana_rate, mana_rate);
	  LOAD_VALUE (m_heal_rate, heal_rate);
    m_OriginalVnum = m_vnum;
    }   // end of not saving and validating

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
      if (CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_ROOM_NAME))
        App.SpellCheck (this, &m_ctlName);
      if (CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_ROOM_DESC))
        App.SpellCheck (this, &m_ctlDescription);
      }
#endif // SPELL_CHECKER

    }

	//{{AFX_DATA_MAP(CRoomNamePage)
	DDX_Control(pDX, IDC_NAME, m_ctlName);
	DDX_Control(pDX, IDC_TUNNEL, m_ctlTunnel);
	DDX_Control(pDX, IDC_TUNNEL_LABEL, m_ctlTunnelLabel);
	DDX_Control(pDX, IDC_MANA_RATE_LABEL, m_ctlManaRateLabel);
	DDX_Control(pDX, IDC_MANA_RATE, m_ctlManaRate);
	DDX_Control(pDX, IDC_HEAL_RATE_LABEL, m_ctlHealRateLabel);
	DDX_Control(pDX, IDC_HEAL_RATE, m_ctlHealRate);
	DDX_Control(pDX, IDC_CLAN_NAME_LABEL, m_ctlClanLabel);
	DDX_Control(pDX, IDC_CLAN_NAME, m_ctlClan);
	DDX_Control(pDX, IDC_TELE_DELAY, m_ctlTeleportDelay);
	DDX_Control(pDX, IDC_TELEPORT_CHOOSE, m_ctlTeleportChoose);
	DDX_Control(pDX, IDC_TELEPORT_GOTO, m_ctlTeleportGoto);
	DDX_Control(pDX, IDC_DESC_TELEPORT, m_ctlDescTeleport);
	DDX_Control(pDX, IDC_TELE_VNUM, m_ctlTeleportVnum);
	DDX_Control(pDX, IDC_SECTOR_TYPE, m_ctlSectorType);
	DDX_Control(pDX, IDC_DESCRIPTION, m_ctlDescription);
	DDX_Text(pDX, IDC_DESCRIPTION, m_description);
	DDX_Text(pDX, IDC_NAME, m_name);
	DDX_Text(pDX, IDC_TUNNEL, m_tunnel);
	DDX_Text(pDX, IDC_TELE_DELAY, m_tele_delay);
	DDX_Text(pDX, IDC_CLAN_NAME, m_clan);
	DDX_Text(pDX, IDC_HEAL_RATE, m_heal_rate);
	DDX_Text(pDX, IDC_MANA_RATE, m_mana_rate);
	//}}AFX_DATA_MAP

	DDX_Text(pDX, IDC_VNUM, m_vnum);
	DDV_MinMaxInt(pDX, m_vnum, 1, iMaxVnum);
	DDX_Text(pDX, IDC_TELE_VNUM, m_tele_vnum);
	DDV_MinMaxInt(pDX, m_vnum, 0, iMaxVnum);

  if (!pDX->m_bSaveAndValidate && m_room)
    {

    LoadComboBoxList (m_ctlSectorType, RoomSectorList, m_room->sector_type);

    OnChangeTeleVnum ();

    // mana rate, healing rate and clan only apply to ROM
    if (m_room->m_pDoc->m_AreaType != eROM)
      {
		  m_ctlManaRateLabel.ShowWindow (SW_HIDE);
		  m_ctlManaRate.ShowWindow (SW_HIDE);
		  m_ctlHealRateLabel.ShowWindow (SW_HIDE);
		  m_ctlHealRate.ShowWindow (SW_HIDE);
		  m_ctlClanLabel.ShowWindow (SW_HIDE);
		  m_ctlClan.ShowWindow (SW_HIDE);
      }

    // tunnel only applies to SMAUG
    if (m_room->m_pDoc->m_AreaType != eSMAUG)
      {
		  m_ctlTunnelLabel.ShowWindow (SW_HIDE);
		  m_ctlTunnel.ShowWindow (SW_HIDE);
      }

    }   // end of not saving and validating

  if (m_room)
    UpdateTeleport ();

  if (pDX->m_bSaveAndValidate)
    {

    // tilde is a FATAL error - do not allow them to ignore it
    CheckForTilde (pDX, IDC_NAME, m_name);
    CheckForTilde (pDX, IDC_DESCRIPTION, m_description);
    CheckForTilde (pDX, IDC_CLAN_NAME, m_clan);

    // put it in a try block, they can ignore these errors
    try
      {
      if (m_vnum < m_room->m_pDoc->m_Area->room_low_vnum ||
          m_vnum > m_room->m_pDoc->m_Area->room_hi_vnum )
        {
        if (::AfxMessageBox(
                          CFormat ("The vnum must be in the range %i to %i.\n\n"
                                   "Adjust permitted range to include this in it?",
          m_room->m_pDoc->m_Area->room_low_vnum, m_room->m_pDoc->m_Area->room_hi_vnum),
          MB_ICONQUESTION | MB_YESNO) == IDNO)
          {
          DDX_Text(pDX, IDC_VNUM, m_vnum);
          pDX->Fail();       
          return;
          }

        if (m_vnum < m_room->m_pDoc->m_Area->room_low_vnum)
          m_room->m_pDoc->m_Area->room_low_vnum = m_vnum;
        if (m_vnum > m_room->m_pDoc->m_Area->room_hi_vnum)
          m_room->m_pDoc->m_Area->room_hi_vnum = m_vnum;
         m_room->m_pDoc->SetModifiedFlag ();
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

    CRoom * room;

    if ((room = FindRoom (m_vnum)) && (room != m_room))
      {
      ::AfxMessageBox(CFormat ("This vnum is already used by room: %s.",
        (LPCTSTR) room->Summary ()),
        MB_ICONEXCLAMATION);
      DDX_Text(pDX, IDC_VNUM, m_vnum);
      pDX->Fail();
      return;
      }     // end of vnum in use

	  UNLOAD_VALUE (m_vnum, vnum);
	  UNLOAD_VALUE (m_name, name);
	  UNLOAD_VALUE (m_description, description);
	  UNLOAD_VALUE (m_tele_vnum, tele_vnum);
	  UNLOAD_VALUE (m_tele_delay, tele_delay);
	  UNLOAD_VALUE (m_tunnel, tunnel);
	  UNLOAD_VALUE (m_clan, clan);
	  UNLOAD_VALUE (m_mana_rate, mana_rate);
	  UNLOAD_VALUE (m_heal_rate, heal_rate);

    int i;
    if (UnloadComboBox (m_ctlSectorType, i))
	    UNLOAD_VALUE (i, sector_type);


// ** DO THIS LAST! ** - if vnum changes, reorganise position in list and tree ctrl
    if (m_OriginalVnum != m_vnum)
      {
      CAreaEditorDoc* pDoc = m_room->m_pDoc;
      ASSERT_VALID(pDoc);

      if (!pDoc->AreaRenumber (eRenumberRoom, m_OriginalVnum, m_vnum))
        {   // renumber of area failed
        m_vnum = m_OriginalVnum;        // cancel change
      	UNLOAD_VALUE (m_vnum, vnum);    // put room vnum back
        }
      else
        {

        CRoom * room,
              * prevRoom = NULL;

        // find the highest room with a vnum lower than this one
        for (POSITION roomPos = pDoc->m_RoomList.GetHeadPosition (); roomPos; )
          {
          room = pDoc->m_RoomList.GetNext (roomPos);
          if (room->vnum < m_vnum)
            prevRoom = room;
          }

        // delete from list of rooms

        pDoc->m_RoomList.RemoveAt (pDoc->m_RoomList.Find (m_room, NULL));

        // re-add in new position
        if (prevRoom)
          pDoc->m_RoomList.InsertAfter (pDoc->m_RoomList.Find (prevRoom, NULL), m_room);    // and add it to our list
        else
          pDoc->m_RoomList.AddHead (m_room);    // nothing before? Add to start of list

        // resort rooms tree so that it appears in the correct place

        m_room->m_pTreeCtrl->SetItemText (m_room->m_hdlTreeItem, m_room->Summary ());
        m_room->m_pTreeCtrl->SortChildren (m_room->m_pTreeCtrl->GetParentItem(m_room->m_hdlTreeItem));

        // remember new vnum in case they change it again
        m_OriginalVnum = m_vnum;
        } // end of renumbered OK
      }   // end of vnum changing

     if (bChanged)
       m_room->m_pDoc->SetModifiedFlag ();
    }   // end of saving and validating

}


BEGIN_MESSAGE_MAP(CRoomNamePage, CDialog)
	//{{AFX_MSG_MAP(CRoomNamePage)
	ON_BN_CLICKED(IDC_EDIT_DESCRIPTION, OnEditDescription)
	ON_BN_CLICKED(IDC_TELEPORT_CHOOSE, OnTeleportChoose)
	ON_BN_CLICKED(IDC_TELEPORT_GOTO, OnTeleportGoto)
	ON_EN_CHANGE(IDC_TELE_VNUM, OnChangeTeleVnum)
	ON_BN_CLICKED(IDC_EDIT_NAMES, OnEditNames)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRoomNamePage message handlers

void CRoomNamePage::EditDescription (CEdit & ctlDescription, 
                                       const bool bEndline,
                                       const bool bSpellCheck)
  {
CEditDlg dlg;

CRoomView * wndParent = (CRoomView *) GetParent ();

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

void CRoomNamePage::OnEditDescription() 
{
EditDescription (m_ctlDescription, true,
                 CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_ROOM_DESC));
}

void CRoomNamePage::OnEditNames() 
{
EditDescription (m_ctlName, false,
                 CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_ROOM_NAME));
}

void CRoomNamePage::OnTeleportChoose() 
{

CString strField;

// get text of window

m_ctlTeleportVnum.GetWindowText(strField);

// convert to number

int iField = atoi (strField);

CChooseRoomDlg room_dlg;
CRoomView * wndParent = (CRoomView *) GetParent ();
	
  room_dlg.m_pDoc = m_room->m_pDoc;
  room_dlg.m_iSelectedRoom = iField;
  wndParent->m_bEditingText = true;
  if (room_dlg.DoModal () == IDOK) 
    if (room_dlg.m_iSelectedRoom != -1)
      m_ctlTeleportVnum.SetWindowText(CFormat ("%i", room_dlg.m_iSelectedRoom));
  wndParent->m_bEditingText = false;

}

void CRoomNamePage::OnTeleportGoto() 
{
CString strField;

// get text of window

m_ctlTeleportVnum.GetWindowText(strField);

// convert to number

int iField = atoi (strField);

  m_room->m_pDoc->goto_room (iField);
	
}

void CRoomNamePage::OnChangeTeleVnum() 
{
CString strField;

// get text of window

m_ctlTeleportVnum.GetWindowText(strField);

// convert to number

int iField = atoi (strField);

CRoom * room;
CString strText;

  if (iField == 0)
    strText = "(none)";
  else
    if (room = m_room->m_pDoc->get_room_index(iField))
      strText = room->Summary ();
    else
    if (room = FindRoom (iField))
      strText = FullRoomName (room);
    else
      strText = CFormat ("Room #%i is not in this area", iField);

  m_ctlDescTeleport.SetWindowText (strText);
}


void CRoomNamePage::UpdateTeleport (void)
  {
bool bEnable = (m_room->room_flags & ROOM_TELEPORT) != 0;

  m_ctlTeleportVnum.EnableWindow (bEnable);
  m_ctlTeleportDelay.EnableWindow (bEnable);
  m_ctlTeleportChoose.EnableWindow (bEnable);
  m_ctlTeleportGoto.EnableWindow (bEnable);

  }
