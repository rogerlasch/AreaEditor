/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// RoomExitDetails.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "AreaEditorDoc.h"
#include "defaults.h"

#include "RoomExitDetails.h"

#include "ChooseRoomDlg.h"
#include "ChooseObjectDlg.h"
#include "EditDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRoomExitDetails dialog


CRoomExitDetails::CRoomExitDetails(CWnd* pParent /*=NULL*/)
	: CDialog(CRoomExitDetails::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRoomExitDetails)
	m_description = _T("");
	m_keyword = _T("");
	m_vnum = 0;
	m_key = 0;
	m_distance = 0;
	m_strFlags = _T("");
	//}}AFX_DATA_INIT

  m_exit = NULL;
}

#undef LOAD_FLAG
#define LOAD_FLAG(field, flag)  \
  field = IS_SET (m_exit->exit_info, flag);

#undef UNLOAD_FLAG
#define UNLOAD_FLAG(field, flag)  \
  if (field != IS_SET (m_exit->exit_info, flag)) bChanged = true; \
  if (field)                      \
    SET_BIT (m_exit->exit_info, flag);\
  else                            \
    REMOVE_BIT (m_exit->exit_info, flag)

#undef LOAD_VALUE
#define LOAD_VALUE(field, value)  \
  field = m_exit->value

#undef UNLOAD_VALUE
#define UNLOAD_VALUE(field, value)  \
  if (field != m_exit->value) bChanged = true; \
  m_exit->value = field

void CRoomExitDetails::DoDataExchange(CDataExchange* pDX)
{

bool bChanged = false;

  if (!pDX->m_bSaveAndValidate && m_exit)
    {
	  LOAD_VALUE (m_description, description);
	  LOAD_VALUE (m_keyword, keyword);
	  LOAD_VALUE (m_vnum, vnum);
	  LOAD_VALUE (m_key, key);
	  LOAD_VALUE (m_distance, distance);

    m_strFlags = convert_exit_flags (m_exit->exit_info);

    }   // end of not saving and validating


	CDialog::DoDataExchange(pDX);

  if (pDX->m_bSaveAndValidate)
    if (FixWrap (m_ctlDescription))
      {
      DDX_Text(pDX, IDC_DESCRIPTION, m_description);
      pDX->Fail();
      }

	//{{AFX_DATA_MAP(CRoomExitDetails)
	DDX_Control(pDX, IDC_GOTO_KEY, m_ctlGoToKey);
	DDX_Control(pDX, IDC_KEY_DESCRIPTION, m_ctlKeyDescription);
	DDX_Control(pDX, IDC_GOTO, m_ctlGoTo);
	DDX_Control(pDX, IDC_DIRECTION, m_ctlDirection);
	DDX_Control(pDX, IDC_EXIT_TO, m_ctlExitTo);
	DDX_Control(pDX, IDC_EXIT_TO_DESCRIPTION, m_ctlExitDescription);
	DDX_Control(pDX, IDC_KEY, m_ctlKey);
	DDX_Control(pDX, IDC_DESCRIPTION, m_ctlDescription);
	DDX_Text(pDX, IDC_DESCRIPTION, m_description);
	DDX_Text(pDX, IDC_KEYWORD, m_keyword);
	DDX_Text(pDX, IDC_EXIT_TO, m_vnum);
	DDX_Text(pDX, IDC_KEY, m_key);
	DDX_Text(pDX, IDC_DISTANCE, m_distance);
	DDX_Text(pDX, IDC_FLAGS, m_strFlags);
	//}}AFX_DATA_MAP

  if (!pDX->m_bSaveAndValidate && m_exit)
    {
    LoadComboBoxList (m_ctlDirection, RoomDirectionList, m_exit->vdir);

    OnUpdateExitTo ();
    OnUpdateKey ();
    }

  if (pDX->m_bSaveAndValidate && m_exit)
    {
	  UNLOAD_VALUE (m_description, description);
	  UNLOAD_VALUE (m_keyword, keyword);
	  UNLOAD_VALUE (m_vnum, vnum);
	  UNLOAD_VALUE (m_key, key);
	  UNLOAD_VALUE (m_distance, distance);

    int i;
    if (UnloadComboBox (m_ctlDirection, i))
	    UNLOAD_VALUE (i, vdir);
    
    m_exit->m_pTreeCtrl->SetItemText (m_exit->m_hdlTreeItem, m_exit->Summary ());

    if (bChanged)
       m_exit->m_pDoc->SetModifiedFlag ();
    }   // end of saving and validating

}


BEGIN_MESSAGE_MAP(CRoomExitDetails, CDialog)
	//{{AFX_MSG_MAP(CRoomExitDetails)
	ON_EN_UPDATE(IDC_EXIT_TO, OnUpdateExitTo)
	ON_BN_CLICKED(IDC_CHOOSE, OnChoose)
	ON_BN_CLICKED(IDC_GOTO, OnGoto)
	ON_BN_CLICKED(IDC_EDIT, OnEdit)
	ON_BN_CLICKED(IDC_CHOOSE_KEY, OnChooseKey)
	ON_EN_UPDATE(IDC_KEY, OnUpdateKey)
	ON_BN_CLICKED(IDC_GOTO_KEY, OnGotoKey)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRoomExitDetails message handlers

void CRoomExitDetails::OnUpdateExitTo() 
{
	CAreaEditorDoc* pDoc = m_exit->m_pDoc;
	ASSERT_VALID(pDoc);

CRoom * room;
CString strExit;

// get amended text of window

m_ctlExitTo.GetWindowText(strExit);

// convert to number

int iExit = atoi (strExit);

// exit of -1 means "no room"

if (iExit == -1)
  {
    m_ctlExitDescription.SetWindowText ("(no exit)");
    m_ctlGoTo.EnableWindow (false);
  }
else

  // scan existing rooms to see if exit points to it

  if (room = pDoc->get_room_index (iExit))
    {
    m_ctlExitDescription.SetWindowText (room->name);
    m_ctlGoTo.EnableWindow (true);
    }
  else 

  // not found - say so
  // (nb - this is not too bad, room may link to a different area)

    {
    if (room = FindRoom (iExit))
      {
      m_ctlExitDescription.SetWindowText (FullRoomName (room));
      m_ctlGoTo.EnableWindow (true);
      }
    else
      {
      m_ctlExitDescription.SetWindowText 
            (CFormat ("Room #%i not in this area", iExit));
      m_ctlGoTo.EnableWindow (false);
      }
    }
}



void CRoomExitDetails::OnChoose() 
{
CAreaEditorDoc* pDoc = m_exit->m_pDoc;
ASSERT_VALID(pDoc);

CString strExit;

// get amended text of window

m_ctlExitTo.GetWindowText(strExit);

// convert to number

int iExit = atoi (strExit);

CChooseRoomDlg room_dlg;

  room_dlg.m_pDoc = pDoc;
  room_dlg.m_iSelectedRoom = iExit;
  if (room_dlg.DoModal () == IDOK) 
    if (room_dlg.m_iSelectedRoom != -1)
      m_ctlExitTo.SetWindowText(CFormat ("%i", room_dlg.m_iSelectedRoom));
	
}

void CRoomExitDetails::OnGoto() 
{
CAreaEditorDoc* pDoc = m_exit->m_pDoc;
ASSERT_VALID(pDoc);

CString strExit;

// get amended text of window

  m_ctlExitTo.GetWindowText(strExit);

// go to it

  pDoc->goto_room (atoi (strExit));
	
}

void CRoomExitDetails::OnEdit() 
{
CEditDlg dlg;

	m_ctlDescription.GetWindowText (dlg.m_strEditText);

  dlg.m_bEndline = true;
  dlg.m_bSpellCheck = CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_EXIT_DESC);

  if (dlg.DoModal () != IDOK)
    return;

  m_ctlDescription.SetWindowText (dlg.m_strEditText);
	
	
}

void CRoomExitDetails::OnChooseKey() 
{
CAreaEditorDoc* pDoc = m_exit->m_pDoc;
ASSERT_VALID(pDoc);

CString strKey;

// get amended text of window

m_ctlKey.GetWindowText(strKey);

// convert to number

int iKey = atoi (strKey);

CChooseObjectDlg object_dlg;

  object_dlg.m_pDoc = pDoc;
  object_dlg.m_iSelectedObject = iKey;
  object_dlg.m_iItemType = eTakeItem;    // only choose take-type items
  if (object_dlg.DoModal () == IDOK) 
    if (object_dlg.m_iSelectedObject != -1)
      m_ctlKey.SetWindowText(CFormat ("%i", object_dlg.m_iSelectedObject));
	
}

void CRoomExitDetails::OnUpdateKey() 
{
	CAreaEditorDoc* pDoc = m_exit->m_pDoc;
	ASSERT_VALID(pDoc);

CMUDObject * object;
CString strKey;

// get amended text of window

m_ctlKey.GetWindowText(strKey);

// convert to number

int iKey = atoi (strKey);

// key of -1 means "no key"

if (iKey == -1)
  {
    m_ctlKeyDescription.SetWindowText ("(no key)");
    m_ctlGoToKey.EnableWindow (false);
  }
else

  // find key object

  if (object = pDoc->get_obj_index (iKey))
    {
    m_ctlKeyDescription.SetWindowText (object->short_descr);
    m_ctlGoToKey.EnableWindow (true);
    }
  else 
  if (object = FindObj (iKey))
    {
    m_ctlKeyDescription.SetWindowText (FullObjName (object));
    m_ctlGoToKey.EnableWindow (true);
    }
  else 

  // not found - say so
  // (nb - this is not too bad, key may be in a different area)

    {
    m_ctlKeyDescription.SetWindowText 
            (CFormat ("Object #%i not in this area", iKey));
    m_ctlGoToKey.EnableWindow (false);
    }
}

void CRoomExitDetails::OnGotoKey() 
{
CAreaEditorDoc* pDoc = m_exit->m_pDoc;
ASSERT_VALID(pDoc);

CString strKey;

// get amended text of window

  m_ctlExitTo.GetWindowText(strKey);

// go to it

  pDoc->goto_object (atoi (strKey));
	
}
