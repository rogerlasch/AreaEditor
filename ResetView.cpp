/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// ResetView.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "AreaEditorDoc.h"

#include "ResetView.h"

#include "ChooseMobDlg.h"
#include "ChooseRoomDlg.h"
#include "ChooseObjectDlg.h"
#include "ChooseExitDlg.h"
#include "defaults.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResetView


IMPLEMENT_DYNCREATE(CResetView, CFormView)

CResetView::CResetView()
	: CFormView(CResetView::IDD)
{
	//{{AFX_DATA_INIT(CResetView)
	m_arg1 = 0;
	m_arg2 = 0;
	m_arg3 = 0;
	m_extra = 0;
	m_command = -1;
	m_arg4 = 0;
	//}}AFX_DATA_INIT

  m_reset = NULL;

}

CResetView::~CResetView()
{
}

#undef LOAD_VALUE
#define LOAD_VALUE(field, value)  \
  field = m_reset->value

#undef UNLOAD_VALUE
#define UNLOAD_VALUE(field, value)  \
  do {    \
    if (field != m_reset->value) bChanged = true; \
    m_reset->value = field;   \
    } while (false)

void CResetView::DoDataExchange(CDataExchange* pDX)
{
bool bChanged = false;

  if (!pDX->m_bSaveAndValidate && m_reset)
    {
	  LOAD_VALUE (m_arg1, arg1);
	  LOAD_VALUE (m_arg2, arg2);
	  LOAD_VALUE (m_arg3, arg3);
	  LOAD_VALUE (m_arg4, arg4);
	  LOAD_VALUE (m_extra, extra);

    switch (m_reset->command)
      {
      case 'M': m_command = 0; break;
      case 'O': m_command = 1; break;
      case 'G': m_command = 2; break;
      case 'E': m_command = 3; break;
      case 'P': m_command = 4; break;
      case 'D': m_command = 5; break;
      case 'R': m_command = 6; break;
      case 'T': m_command = 7; break;
      case 'H': m_command = 8; break;

      } // end of switch

    }   // end of not saving and validating

	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CResetView)
	DDX_Control(pDX, IDC_LABEL_ARG4, m_ctlLabelArg4);
	DDX_Control(pDX, IDC_DESC_ARG4, m_ctlDescArg4);
	DDX_Control(pDX, IDC_ARG4, m_ctlArg4);
	DDX_Control(pDX, IDC_WEAR_LOCATION_LABEL, m_ctlWearLocationLabel);
	DDX_Control(pDX, IDC_WEAR_LOCATION, m_ctlWearLocation);
	DDX_Control(pDX, IDC_MOBILE_BUTTON, m_ctlCommand);
	DDX_Control(pDX, IDC_EXTRA, m_ctlExtra);
	DDX_Control(pDX, IDC_ARG3, m_ctlArg3);
	DDX_Control(pDX, IDC_ARG2, m_ctlArg2);
	DDX_Control(pDX, IDC_ARG1, m_ctlArg1);
	DDX_Control(pDX, IDC_LABEL_EXTRA, m_ctlLabelExtra);
	DDX_Control(pDX, IDC_LABEL_ARG3, m_ctlLabelArg3);
	DDX_Control(pDX, IDC_LABEL_ARG2, m_ctlLabelArg2);
	DDX_Control(pDX, IDC_LABEL_ARG1, m_ctlLabelArg1);
	DDX_Control(pDX, IDC_DESC_EXTRA, m_ctlDescExtra);
	DDX_Control(pDX, IDC_DESC_ARG3, m_ctlDescArg3);
	DDX_Control(pDX, IDC_DESC_ARG2, m_ctlDescArg2);
	DDX_Control(pDX, IDC_DESC_ARG1, m_ctlDescArg1);
	DDX_Text(pDX, IDC_ARG1, m_arg1);
	DDX_Text(pDX, IDC_ARG2, m_arg2);
	DDX_Text(pDX, IDC_ARG3, m_arg3);
	DDX_Text(pDX, IDC_EXTRA, m_extra);
	DDX_Radio(pDX, IDC_MOBILE_BUTTON, m_command);
	DDX_Text(pDX, IDC_ARG4, m_arg4);
	//}}AFX_DATA_MAP

  if (!pDX->m_bSaveAndValidate && m_reset)
    {

    if (m_reset->m_pDoc->m_AreaType != eROM)
      {
      m_ctlArg4.ShowWindow (SW_HIDE);
      m_ctlDescArg4.ShowWindow (SW_HIDE);
      m_ctlArg4.ShowWindow (SW_HIDE);
      }   // end of not ROM

    LoadComboBoxList (m_ctlWearLocation, ObjectWearList, -1);
    OnUpdateArg1 ();
    OnUpdateArg2 ();
    OnUpdateArg3 ();
    OnUpdateArg4 ();
    OnUpdateExtra ();
    OnSelchangeWearLocation ();
    }

  if (pDX->m_bSaveAndValidate && m_reset)
    {
	  UNLOAD_VALUE (m_arg1, arg1);
	  UNLOAD_VALUE (m_arg2, arg2);
	  UNLOAD_VALUE (m_arg3, arg3);
	  UNLOAD_VALUE (m_arg4, arg4);
	  UNLOAD_VALUE (m_extra, extra);

    char c;

    switch (m_command)
      {
      case 0: c = 'M'; break;
      case 1: c = 'O'; break;
      case 2: c = 'G'; break;
      case 3: c = 'E'; break;
      case 4: c = 'P'; break;
      case 5: c = 'D'; break;
      case 6: c = 'R'; break;
      case 7: c = 'T'; break;
      case 8: c = 'H'; break;

      } // end of switch

	  UNLOAD_VALUE (c, command);

    m_reset->m_pTreeCtrl->SetItemText (m_reset->m_hdlTreeItem, m_reset->Summary ());

     if (bChanged)
       m_reset->m_pDoc->SetModifiedFlag ();
    }   // end of saving and validating

}


BEGIN_MESSAGE_MAP(CResetView, CFormView)
	//{{AFX_MSG_MAP(CResetView)
	ON_EN_UPDATE(IDC_ARG1, OnUpdateArg1)
	ON_EN_UPDATE(IDC_ARG2, OnUpdateArg2)
	ON_EN_UPDATE(IDC_ARG3, OnUpdateArg3)
	ON_EN_UPDATE(IDC_EXTRA, OnUpdateExtra)
	ON_BN_CLICKED(IDC_MOBILE_BUTTON, OnCommand)
	ON_BN_CLICKED(IDC_ARG1_CHOOSE, OnArg1Choose)
	ON_BN_CLICKED(IDC_ARG1_GOTO, OnArg1Goto)
	ON_BN_CLICKED(IDC_ARG2_CHOOSE, OnArg2Choose)
	ON_BN_CLICKED(IDC_ARG2_GOTO, OnArg2Goto)
	ON_BN_CLICKED(IDC_ARG3_CHOOSE, OnArg3Choose)
	ON_BN_CLICKED(IDC_ARG3_GOTO, OnArg3Goto)
	ON_CBN_SELCHANGE(IDC_WEAR_LOCATION, OnSelchangeWearLocation)
	ON_BN_CLICKED(IDC_DOOR_BUTTON, OnCommand)
	ON_BN_CLICKED(IDC_EQUIP_BUTTON, OnCommand)
	ON_BN_CLICKED(IDC_GIVE_BUTTON, OnCommand)
	ON_BN_CLICKED(IDC_HIDE_BUTTON, OnCommand)
	ON_BN_CLICKED(IDC_OBJECT_BUTTON, OnCommand)
	ON_BN_CLICKED(IDC_PUT_BUTTON, OnCommand)
	ON_BN_CLICKED(IDC_RAND_BUTTON, OnCommand)
	ON_EN_UPDATE(IDC_ARG4, OnUpdateArg4)
	//}}AFX_MSG_MAP
  ON_MESSAGE(WM_KICKIDLE, OnKickIdle)
  ON_UPDATE_COMMAND_UI(IDC_ARG1_GOTO, OnUpdateGotoArg1)
  ON_UPDATE_COMMAND_UI(IDC_ARG2_GOTO, OnUpdateGotoArg2)
  ON_UPDATE_COMMAND_UI(IDC_ARG3_GOTO, OnUpdateGotoArg3)
  ON_UPDATE_COMMAND_UI(IDC_ARG1_CHOOSE, OnUpdateChooseArg1)
  ON_UPDATE_COMMAND_UI(IDC_ARG2_CHOOSE, OnUpdateChooseArg2)
  ON_UPDATE_COMMAND_UI(IDC_ARG3_CHOOSE, OnUpdateChooseArg3)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResetView diagnostics

#ifdef _DEBUG
void CResetView::AssertValid() const
{
	CFormView::AssertValid();
}

void CResetView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CResetView message handlers

void CResetView::OnUpdateArg1() 
{
CAreaEditorDoc* pDoc = (CAreaEditorDoc* ) GetDocument();
ASSERT_VALID(pDoc);

CString strField;

// get amended text of window

m_ctlArg1.GetWindowText(strField);

// convert to number

int iField = atoi (strField);

CString strText;
CString strLabel;

CMobile * mob;
CMUDObject * object;
CRoom * room;

  switch (m_reset->command)
    {
    case 'M': // load mobile
        if (mob = pDoc->get_mob_index( iField))
          strText = mob->Summary ();
        else
        if (mob = FindMob (iField))
          strText = FullMobName (mob);
        else
          strText = CFormat ("Mobile #%i is not in this area", iField);
        strLabel = "Mobile";
        break;

    case 'O': // load object
    case 'P': // put object into object
    case 'G': // give object to mob
    case 'E': // equip last mob
    case 'H': // hide last object
      if (object = pDoc->get_obj_index( iField))
          strText = object->Summary ();
        else
        if (object = FindObj (iField))
          strText = FullObjName (object);
        else
          strText = CFormat ("Object #%i is not in this area", iField);
        strLabel = "Object";
        break;

    case 'D':   // door
    case 'R':   // randomise exits
        if (room = pDoc->get_room_index(iField))
          strText = room->Summary ();
        else
  // if room is in a different area, say so
        if (room = FindRoom (iField))
          strText = FullRoomName (room);
        else
          strText = CFormat ("Room #%i is not in any open area", iField);
        strLabel = "Room";
        break;

    } // end of switch

  m_ctlDescArg1.SetWindowText (strText);
  m_ctlLabelArg1.SetWindowText (strLabel);

  UpdateDialogControls (AfxGetApp()->m_pMainWnd, false);

}

void CResetView::OnUpdateArg2() 
{
CAreaEditorDoc* pDoc = (CAreaEditorDoc* ) GetDocument();
ASSERT_VALID(pDoc);

CString strField;

// get amended text of window for ARG1

m_ctlArg1.GetWindowText(strField);

// convert to number

int iField1 = atoi (strField);

// get amended text of window for ARG2

m_ctlArg2.GetWindowText(strField);

// convert to number

int iField = atoi (strField);


CString strText;
CString strLabel;
CString strExitDirection;
CRoom * exitroom;
CString strExitName;

CRoom * room;
CExit * exit;
CAreaEditorDoc * area;

  switch (m_reset->command)
    {
    case 'M':
    case 'O':
    case 'P':
    case 'G':
    case 'E':

        strText = CFormat ("limit = %i", iField);
        strLabel = "Limit";
        break;

    case 'D':
      strLabel = "Door";
      if ((room = pDoc->get_room_index(iField1)) == NULL)
        {
        if ((room = FindRoom (iField1)) == NULL)
          {
          strText = CFormat ("Room #%i is not in any open area", iField1);
          break;
          }
        }
      area = room->m_pDoc;
      if (iField < 0
	      ||   iField > MAX_DIR+1)
        {
        strText = CFormat ("Exit #%i is not a valid direction", iField);
        break;
        }
      if ((exit = area->get_exit(room, iField)) == NULL)
        {
        strText = CFormat ("Door #%i is not in room #%i", iField, iField1);
        break;
        }
      if (!IS_SET( exit->exit_info, EX_ISDOOR ) )
        {
        strText = CFormat ("Exit #%i in room #%i is not a door", iField, iField1);
        break;
        }
      strExitDirection = RoomDirectionList.ReturnName (exit->vdir, false);
      if (exitroom = pDoc->get_room_index (exit->vnum))
        strExitName = exitroom->name;
      else
      if (exitroom = FindRoom (exit->vnum))
        strExitName = FullRoomName (exitroom);
      else
        strExitName = "not in any open area";

      strText = exit->Summary ();

      break;    // end of 'D'

    case 'R':
        strText = CFormat ("max exits = %i", iField);
        strLabel = "Max exits";
        break;

    } // end of switch

  m_ctlDescArg2.SetWindowText (strText);
  m_ctlLabelArg2.SetWindowText (strLabel);

  UpdateDialogControls (AfxGetApp()->m_pMainWnd, false);
	
}


void CResetView::OnUpdateArg3() 
{
CAreaEditorDoc* pDoc = (CAreaEditorDoc* ) GetDocument();
ASSERT_VALID(pDoc);

CString strField;

// get amended text of window

m_ctlArg3.GetWindowText(strField);

// convert to number

int iField = atoi (strField);

CString strText;
CString strLabel;

CRoom * room;
CMUDObject * object;
int sel;

  switch (m_reset->command)
    {
    case 'M':
    case 'O':
        if (room = pDoc->get_room_index(iField))
          strText = room->Summary ();
        else
        if (room = FindRoom (iField))
          strText = FullRoomName (room);
        else
          strText = CFormat ("Room #%i is not in this area", iField);
        strLabel = "Room";
        break;

    case 'P':
        if (object = pDoc->get_obj_index( iField))
          strText = object->Summary ();
        else
        if (object = FindObj (iField))
          strText = FullObjName (object);
        else
          strText = CFormat ("Object #%i is not in this area", iField);
        strLabel = "Dest. object";
        break;

    case 'D':
          strLabel = "Lock";

          switch (iField)
            {
            case 0: strText = "open"; break;
            case 1: strText = "closed"; break;
            case 2: strText = "closed and locked"; break;
            default: strText = "Bad lock"; break;
            }
          break;

    case 'E':

      strText = ObjectWearList.ReturnName (iField, false);

      // they have changed the wear location - update the combo box
      sel = m_ctlWearLocation.FindStringExact(-1, strText);
      m_ctlWearLocation.SetCurSel(sel);   // CB_ERR will deselect the entry

      break;

    } // end of switch

  m_ctlDescArg3.SetWindowText (strText);
  m_ctlLabelArg3.SetWindowText (strLabel);

  UpdateDialogControls (AfxGetApp()->m_pMainWnd, false);

  }

void CResetView::OnCommand() 
{

// find which button they checked - this seems a bit longwinded,
// but is the way MFC does it.

  HWND hWndCtrl = m_ctlCommand;
  int value = -1;

	// walk all children in group
	int iButton = 0;
	do
	{
		if (::SendMessage(hWndCtrl, WM_GETDLGCODE, 0, 0L) & DLGC_RADIOBUTTON)
		  {
			// control in group is a radio button
		if (::SendMessage(hWndCtrl, BM_GETCHECK, 0, 0L) != 0)
				value = iButton;
			iButton++;
		  }
		else
		  {
			TRACE0("Warning: skipping non-radio button in group.\n");
		  }
		hWndCtrl = ::GetWindow(hWndCtrl, GW_HWNDNEXT);

	} while (hWndCtrl != NULL &&
		!(GetWindowLong(hWndCtrl, GWL_STYLE) & WS_GROUP));

  switch (value)
    {
    case 0: m_reset->command = 'M'; break;
    case 1: m_reset->command = 'O'; break;
    case 2: m_reset->command = 'G'; break;
    case 3: m_reset->command = 'E'; break;
    case 4: m_reset->command = 'P'; break;
    case 5: m_reset->command = 'D'; break;
    case 6: m_reset->command = 'R'; break;
    case 7: m_reset->command = 'T'; break;
    case 8: m_reset->command = 'H'; break;
    }

// update meanings of each field

  OnUpdateArg1 ();
  OnUpdateArg2 ();
  OnUpdateArg3 ();
  OnUpdateArg4 ();
  OnUpdateExtra ();
  OnSelchangeWearLocation ();

}

void CResetView::OnUpdateExtra() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	
}


void CResetView::OnArg1Choose() 
{
CAreaEditorDoc* pDoc = (CAreaEditorDoc* ) GetDocument();
ASSERT_VALID(pDoc);

CString strField;

// get text of window

m_ctlArg1.GetWindowText(strField);

// convert to number

int iField = atoi (strField);

CChooseMobDlg  mob_dlg;
CChooseRoomDlg room_dlg;
CChooseObjectDlg object_dlg;

  switch (m_reset->command)
    {
    case 'M': // mobile

            mob_dlg.m_pDoc = pDoc;
            mob_dlg.m_iSelectedMob = iField;
            if (mob_dlg.DoModal () == IDOK) 
              if (mob_dlg.m_iSelectedMob != -1)
                m_ctlArg1.SetWindowText(CFormat ("%i", mob_dlg.m_iSelectedMob));
            break;

    case 'D':   // door
    case 'R':   // randomise exits
            room_dlg.m_pDoc = pDoc;
            room_dlg.m_iSelectedRoom = iField;
            if (room_dlg.DoModal () == IDOK) 
              if (room_dlg.m_iSelectedRoom != -1)
                m_ctlArg1.SetWindowText(CFormat ("%i", room_dlg.m_iSelectedRoom));
            break;

    case 'O': // load object
    case 'P': // put object into room
    case 'G': // give object to mob
    case 'E': // equip last mob
    case 'H': // hide last object
            object_dlg.m_pDoc = pDoc;
            object_dlg.m_iSelectedObject = iField;
            if (object_dlg.DoModal () == IDOK) 
              if (object_dlg.m_iSelectedObject != -1)
                m_ctlArg1.SetWindowText(CFormat ("%i", object_dlg.m_iSelectedObject));
            break;

    default:
      ::AfxMessageBox ("Choosing for this reset type not implemented yet, sorry");
      break;
    } // end of switch


  }   // end of CResetView::OnArg1Choose() 

void CResetView::OnArg1Goto() 
{
CAreaEditorDoc* pDoc = (CAreaEditorDoc* ) GetDocument();
ASSERT_VALID(pDoc);

CString strField;

// get text of window

m_ctlArg1.GetWindowText(strField);

// convert to number

int iField = atoi (strField);


  switch (m_reset->command)
    {
    case 'M':   // mobile
            pDoc->goto_mob (iField);
            break;

    case 'D':   // door
    case 'R':   // randomise exits
            pDoc->goto_room (iField);
            break;

    case 'O': // load object
    case 'P': // put object into room
    case 'G': // give object to mob
    case 'E': // equip last mob
    case 'H': // hide last object
            pDoc->goto_object (iField);
            break;

    default:
      ::AfxMessageBox ("Go to for this reset type not implemented yet, sorry");
      break;
    } // end of switch
	
}

LRESULT CResetView::OnKickIdle(WPARAM, LPARAM)
  {
  UpdateDialogControls (AfxGetApp()->m_pMainWnd, false);
  return 0;
  } // end of CResetView::OnKickIdle

void CResetView::OnUpdateChooseArg1(CCmdUI* pCmdUI)
  {
    switch (m_reset->command)
    {
    case 'M': // load mobile
    case 'D':   // door
    case 'R':   // randomise exits
    case 'O': // load object
    case 'P': // put object into room
    case 'G': // give object to mob
    case 'E': // equip last mob
    case 'H': // hide last object
        pCmdUI->Enable (true);
        break;

    default:
        pCmdUI->Enable (false);
        break;

      } // end of switch

  } // end of CResetView::OnUpdateChooseArg1

void CResetView::OnUpdateGotoArg1(CCmdUI* pCmdUI)
  {
CAreaEditorDoc* pDoc = (CAreaEditorDoc* ) GetDocument();
ASSERT_VALID(pDoc);

CString strField;

// get amended text of window

m_ctlArg1.GetWindowText(strField);

// convert to number

int iField = atoi (strField);

    switch (m_reset->command)
    {
    case 'M': // load mobile
        pCmdUI->Enable (FindMob (iField) != NULL);
        break;

    case 'D':   // door
    case 'R':   // randomise exits
        pCmdUI->Enable (FindRoom (iField) != NULL);
        break;

    case 'O': // load object
    case 'P': // put object into room
    case 'G': // give object to mob
    case 'E': // equip last mob
    case 'H': // hide last object
        pCmdUI->Enable (FindObj (iField) != NULL);
        break;

    default:
        pCmdUI->Enable (false);
        break;

      } // end of switch


  }   // end of CResetView::OnUpdateGotoArg1

void CResetView::OnUpdateChooseArg2(CCmdUI* pCmdUI)
  {

    switch (m_reset->command)
    {

    case 'D':
        pCmdUI->Enable (true);
        break;
    
    default:
        pCmdUI->Enable (false);
        break;

      } // end of switch

  } // end of CResetView::OnUpdateChooseArg2

void CResetView::OnUpdateGotoArg2(CCmdUI* pCmdUI)
  {
CAreaEditorDoc* pDoc = (CAreaEditorDoc* ) GetDocument();
ASSERT_VALID(pDoc);

CString strField;

// get amended text of window for ARG1

m_ctlArg1.GetWindowText(strField);

// convert to number

int iField1 = atoi (strField);

// get amended text of window

m_ctlArg2.GetWindowText(strField);

// convert to number

int iField = atoi (strField);

CRoom * room;

    switch (m_reset->command)
    {

    case 'D':
        if ((room = FindRoom (iField1)) == NULL)
          {
          pCmdUI->Enable (false);
          break;   // room not in area, can't go to it
          }

        pCmdUI->Enable (pDoc->get_exit (room, iField) != NULL);
        break;

    default:
        pCmdUI->Enable (false);
        break;

      } // end of switch


  }   // end of CResetView::OnUpdateGotoArg2

void CResetView::OnUpdateChooseArg3(CCmdUI* pCmdUI)
  {
    switch (m_reset->command)
    {
    case 'M': // load mobile
    case 'O': // load object
    case 'P': // put object
        pCmdUI->Enable (true);
        break;

    default:
        pCmdUI->Enable (false);
        break;

      } // end of switch

  } // end of CResetView::OnUpdateChooseArg3

void CResetView::OnUpdateGotoArg3(CCmdUI* pCmdUI)
  {
CAreaEditorDoc* pDoc = (CAreaEditorDoc* ) GetDocument();
ASSERT_VALID(pDoc);

CString strField;

// get amended text of window

m_ctlArg3.GetWindowText(strField);

// convert to number

int iField = atoi (strField);

    switch (m_reset->command)
    {

    case 'M':   // load mobile
    case 'O':   // load object
        pCmdUI->Enable (FindRoom (iField) != NULL);
        break;

    case 'P':   // put object
        pCmdUI->Enable (FindObj (iField) != NULL);
        break;

    default:
        pCmdUI->Enable (false);
        break;

      } // end of switch


  }   // end of CResetView::OnUpdateGotoArg3

void CResetView::OnArg2Choose() 
{
CAreaEditorDoc* pDoc = (CAreaEditorDoc* ) GetDocument();
ASSERT_VALID(pDoc);

CRoom * room;

CString strField;

// get amended text of window for ARG1

m_ctlArg1.GetWindowText(strField);

// convert to number

int iField1 = atoi (strField);

// get text of window

m_ctlArg2.GetWindowText(strField);

// convert to number

int iField = atoi (strField);

CChooseExitDlg  exit_dlg;

  switch (m_reset->command)
    {

    case 'D':   // door
            if ((room = FindRoom (iField1)) == NULL)
              return;   // room not in area, can't choose door for it

            exit_dlg.m_ExitList = &room->exitlist;
            exit_dlg.m_iSelectedExit = iField;
            exit_dlg.m_pDoc = pDoc;
            if (exit_dlg.DoModal () == IDOK) 
              if (exit_dlg.m_iSelectedExit != -1)
                m_ctlArg2.SetWindowText(CFormat ("%i", exit_dlg.m_iSelectedExit));
            break;


    default:
      ::AfxMessageBox ("Choosing for this reset type not implemented yet, sorry");
      break;
    } // end of switch

	
}

void CResetView::OnArg2Goto() 
{
CAreaEditorDoc* pDoc = (CAreaEditorDoc* ) GetDocument();
ASSERT_VALID(pDoc);

CString strField;

// get amended text of window for ARG1

m_ctlArg1.GetWindowText(strField);

// convert to number

int iField1 = atoi (strField);


// get text of window

m_ctlArg2.GetWindowText(strField);

// convert to number

int iField = atoi (strField);

CRoom * room;

  switch (m_reset->command)
    {

    case 'D':   // door
            if ((room = FindRoom (iField1)) == NULL)
              return;   // room not in area, can't choose door for it

            pDoc->goto_exit (room, iField);
            break;

    default:
      ::AfxMessageBox ("Go to for this reset type not implemented yet, sorry");
      break;
    } // end of switch
	
}

void CResetView::OnArg3Choose() 
{
CAreaEditorDoc* pDoc = (CAreaEditorDoc* ) GetDocument();
ASSERT_VALID(pDoc);

CString strField;

// get text of window

m_ctlArg3.GetWindowText(strField);

// convert to number

int iField = atoi (strField);

CChooseMobDlg  mob_dlg;
CChooseRoomDlg room_dlg;
CChooseObjectDlg object_dlg;

  switch (m_reset->command)
    {
    case 'M': // mobile
    case 'O':
            room_dlg.m_pDoc = pDoc;
            room_dlg.m_iSelectedRoom = iField;
            if (room_dlg.DoModal () == IDOK) 
              if (room_dlg.m_iSelectedRoom != -1)
                m_ctlArg3.SetWindowText(CFormat ("%i", room_dlg.m_iSelectedRoom));
            break;

    case 'P':

            object_dlg.m_pDoc = pDoc;
            object_dlg.m_iSelectedObject = iField;
            object_dlg.m_iItemType = eContainerItem;
            object_dlg.m_iWantedType = ITEM_CONTAINER;
            if (object_dlg.DoModal () == IDOK) 
              if (object_dlg.m_iSelectedObject != -1)
                m_ctlArg3.SetWindowText(CFormat ("%i", object_dlg.m_iSelectedObject));
            break;

    default:
      ::AfxMessageBox ("Choosing for this reset type not implemented yet, sorry");
      break;
    } // end of switch


}

void CResetView::OnArg3Goto() 
{
CAreaEditorDoc* pDoc = (CAreaEditorDoc* ) GetDocument();
ASSERT_VALID(pDoc);

CString strField;

// get text of window

m_ctlArg3.GetWindowText(strField);

// convert to number

int iField = atoi (strField);


  switch (m_reset->command)
    {
    case 'M':   // mobile
    case 'O':
            pDoc->goto_room (iField);
            break;

    case 'P':   // put object
            pDoc->goto_object (iField);
            break;

    default:
      ::AfxMessageBox ("Go to for this reset type not implemented yet, sorry");
      break;
    } // end of switch
}


void CResetView::OnSelchangeWearLocation() 
{
  int i;

  if (m_reset->command == 'E')
    {
    if (UnloadComboBox (m_ctlWearLocation, i))
      m_ctlArg3.SetWindowText(CFormat ("%i", i));
    m_ctlWearLocation.ShowWindow(SW_SHOW);
    m_ctlWearLocationLabel.ShowWindow(SW_SHOW);
    }
  else
    {
    m_ctlWearLocation.ShowWindow(SW_HIDE);
    m_ctlWearLocationLabel.ShowWindow(SW_HIDE);
    }

	
}

void CResetView::OnUpdateArg4() 
{
CAreaEditorDoc* pDoc = (CAreaEditorDoc* ) GetDocument();
ASSERT_VALID(pDoc);

CString strField;

// get amended text of window

m_ctlArg4.GetWindowText(strField);

// convert to number

int iField = atoi (strField);

CString strText;
CString strLabel;

  if (m_reset->m_pDoc->m_AreaType == eROM)
    switch (m_reset->command)
      {
      case 'M':
          strText = CFormat ("limit = %i", iField);
          strLabel = "Limit";
          break;

      case 'P':
          strText = CFormat ("limit = %i", iField);
          strLabel = "Limit";
          break;
      } // end of switch

  m_ctlDescArg4.SetWindowText (strText);
  m_ctlLabelArg4.SetWindowText (strLabel);

  UpdateDialogControls (AfxGetApp()->m_pMainWnd, false);
	
}
