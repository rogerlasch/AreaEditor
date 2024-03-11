/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#include "stdafx.h"
#include "AreaEditor.h"

#include "MainFrm.h"

#include "AreaEditorDoc.h"
#include "AreaEditorView.h"

#include "RenumberDlg.h"
#include "AreaLoadingProblems.h"

#define FixupMobVnum(arg) FixupVnum (arg, pOldMobVnum, pNewMobVnum, iMobCount)
#define FixupObjVnum(arg) FixupVnum (arg, pOldObjVnum, pNewObjVnum, iObjCount)
#define FixupRoomVnum(arg) FixupVnum (arg, pOldRoomVnum, pNewRoomVnum, iRoomCount)

bool CAreaEditorDoc::AreaRenumber (const t_renumbertype iRenumberType,
                                   const int iOldVnum,
                                   const int iNewVnum)
{

// vnums - low and high
int   obj_low_vnum = INT_MAX;
int   obj_hi_vnum = 0;
int   mob_low_vnum = INT_MAX;
int   mob_hi_vnum = 0;
int   room_low_vnum = INT_MAX;
int   room_hi_vnum = 0;

// item counts
int iMobCount = m_MobList.GetCount ();
int iObjCount = m_ObjectList.GetCount ();
int iRoomCount = m_RoomList.GetCount ();
int iPrograms = 0;
long iMilestone = 0;

POSITION pos;
POSITION mobPos;
POSITION objPos;
POSITION roomPos;

CMobile * mob;
CRoom * room;
CMUDObject * obj;

CMUDprogram * program;
CString strMessage;

  CRenumberDlg dlg;

	dlg.m_iMobCount = iMobCount;
	dlg.m_iObjCount = iObjCount;
	dlg.m_iRoomCount = iRoomCount;
	
  // update mob vnum ranges
  for (mobPos = m_MobList.GetHeadPosition (); mobPos; )
    {
    mob = m_MobList.GetNext (mobPos);
    if (mob->vnum > mob_hi_vnum)
      mob_hi_vnum = mob->vnum;
    if (mob->vnum < mob_low_vnum)
      mob_low_vnum = mob->vnum;
    iPrograms += mob->programlist.GetCount ();  // count programs
    } // end of each mob

  if (mob_low_vnum == INT_MAX)
    mob_low_vnum = 0;

  // update obj vnum ranges
  for (objPos = m_ObjectList.GetHeadPosition (); objPos; )
    {
    obj = m_ObjectList.GetNext (objPos);
    if (obj->vnum > obj_hi_vnum)
      obj_hi_vnum = obj->vnum;
    if (obj->vnum < obj_low_vnum)
      obj_low_vnum = obj->vnum;
    iPrograms += obj->programlist.GetCount ();  // count programs
    } // end of each object

  if (obj_low_vnum == INT_MAX)
    obj_low_vnum = 0;

  // update room vnum ranges
  for (roomPos = m_RoomList.GetHeadPosition (); roomPos; )
    {
    room = m_RoomList.GetNext (roomPos);
    if (room->vnum > room_hi_vnum)
      room_hi_vnum = room->vnum;
    if (room->vnum < room_low_vnum)
      room_low_vnum = room->vnum;
    iPrograms += room->programlist.GetCount ();  // count programs
    } // end of each room

  if (room_low_vnum == INT_MAX)
    room_low_vnum = 0;

  dlg.m_iMobLowVnum = mob_low_vnum;
  dlg.m_iMobHighVnum = mob_hi_vnum;
  dlg.m_iObjLowVnum = obj_low_vnum;
  dlg.m_iObjHighVnum = obj_hi_vnum;
  dlg.m_iRoomLowVnum = room_low_vnum;
  dlg.m_iRoomHighVnum = room_hi_vnum;

  dlg.m_iNewLowMobVnum = mob_low_vnum;
  dlg.m_iNewLowObjVnum = obj_low_vnum;
  dlg.m_iNewLowRoomVnum = room_low_vnum;

  if (iRenumberType == eRenumberAll)
    {
    if (dlg.DoModal () != IDOK)
      return false;

    // check they actually want to renumber something
    if (dlg.m_iNewLowMobVnum == mob_low_vnum &&
        dlg.m_iNewLowObjVnum == obj_low_vnum &&
        dlg.m_iNewLowRoomVnum == room_low_vnum &&
        !dlg.m_bMobCompact &&
        !dlg.m_bObjCompact &&
        !dlg.m_bRoomCompact)
      {
       ::AfxMessageBox ("No renumbering requested - all vnums the same", 
                        MB_ICONINFORMATION);
       return false;
      } // end of no renumber wanted
    } // end of renumber all

   // don't do it if we have not commands, socials or skills
  if (iPrograms)
    {

    if (App.m_CommandList.IsEmpty () 
      || App.m_SocialList.IsEmpty ()
      || App.m_SkillList.IsEmpty ())
      {
      ::AfxMessageBox ("Your area has MUD programs, but you have not loaded all of the"
                       " following files:"
                       "\ncommands.dat, socials.dat and skills.dat."
                       "\n\nRenumbering cannot proceed as MUD programs cannot be analysed", 
                       MB_ICONSTOP);
      return false;
      }

  // Just to be safe, check syntax in all programs, and only go ahead if no errors

    m_strErrorMessage.Empty ();
    m_nErrors = 0;

    Frame.CreateProgressBar ("Checking programs", iPrograms);

    // check mobs

    for (mobPos = m_MobList.GetHeadPosition (); mobPos; )
      {
      mob = m_MobList.GetNext (mobPos);

      for (POSITION progPos = mob->programlist.GetHeadPosition (); progPos; )
        {
        program = mob->programlist.GetNext (progPos);

        if (iMilestone++ % 10 == 0)
          Frame.UpdateProgressBar (iMilestone);

        // check program
        if (CheckCommandSyntax (program->comlist, 
                            strMessage,
                            program->xref_rooms,
                            program->xref_objects,
                            program->xref_mobs))
             Warning (mob, strMessage);

        } // end of each program
    
      } // end of each mob

    // check rooms

    for (roomPos = m_RoomList.GetHeadPosition (); roomPos; )
      {
      room = m_RoomList.GetNext (roomPos);

      for (POSITION progPos = room->programlist.GetHeadPosition (); progPos; )
        {
        program = room->programlist.GetNext (progPos);

        if (iMilestone++ % 10 == 0)
          Frame.UpdateProgressBar (iMilestone);

        // check program
        if (CheckCommandSyntax (program->comlist, 
                            strMessage,
                            program->xref_rooms,
                            program->xref_objects,
                            program->xref_mobs))
             Warning (room, strMessage);

        } // end of each program

      }   // end of each room

    // check objects

    for (objPos = m_ObjectList.GetHeadPosition (); objPos; )
      {
      obj = m_ObjectList.GetNext (objPos);

      for (POSITION progPos = obj->programlist.GetHeadPosition (); progPos; )
        {
        program = obj->programlist.GetNext (progPos);

        if (iMilestone++ % 10 == 0)
          Frame.UpdateProgressBar (iMilestone);

        // check program
        if (CheckCommandSyntax (program->comlist, 
                            strMessage,
                            program->xref_rooms,
                            program->xref_objects,
                            program->xref_mobs))
             Warning (obj, strMessage);

        } // end of each program
    
      } // end of each obj

    Frame.RemoveProgressBar ();

    if (m_nErrors)
      {

      // MODELESS dialog here

      CAreaLoadingProblems * dlg = new CAreaLoadingProblems;
      dlg->m_strTitle = "Error(s) in programs - cannot renumber";  // set up dialog title
      dlg->m_strErrors = m_strErrorMessage;            // what it says
      dlg->Create (ID_PROBLEMS_LOADING_AREA, NULL);  // create it
      dlg->ShowWindow(SW_SHOW);  // and, finally, show it - dialog will delete itself

      return false;
    } // end of errors in programs

  } // end of having at least one program somewhere


int * pOldMobVnum = NULL; 
int * pNewMobVnum = NULL;
int * pOldObjVnum = NULL; 
int * pNewObjVnum = NULL; 
int * pOldRoomVnum = NULL;
int * pNewRoomVnum = NULL;
int i;
int iDifference;

switch (iRenumberType)
  {
  case eRenumberAll: 
        // deselect "area" view so that vnums get updated correctly
        if (m_leftview)
          m_leftview->GetTreeCtrl().Select (m_leftview->m_hdlTreeHelps, TVGN_CARET);
        // set up for new vnum ranges
        m_Area->obj_low_vnum = INT_MAX;
        m_Area->obj_hi_vnum = 0;
        m_Area->mob_low_vnum = INT_MAX;
        m_Area->mob_hi_vnum = 0;
        m_Area->room_low_vnum = INT_MAX;
        m_Area->room_hi_vnum = 0;
        // create arrays to hold the "from" and "to" vnums
        pOldMobVnum = new int [iMobCount];
        pNewMobVnum = new int [iMobCount];
        pOldObjVnum = new int [iObjCount];
        pNewObjVnum = new int [iObjCount];
        pOldRoomVnum = new int [iRoomCount];
        pNewRoomVnum = new int [iRoomCount];
        break;

  case eRenumberMob:
        iMobCount = 1;
        iObjCount = 0;
        iRoomCount = 0;
        pOldMobVnum = new int [1];
        pNewMobVnum = new int [1];
        pOldMobVnum [0] = iOldVnum;
        pNewMobVnum [0] = iNewVnum;
        break;

  case eRenumberObj:
        iMobCount = 0;
        iObjCount = 1;
        iRoomCount = 0;
        pOldObjVnum = new int [1];
        pNewObjVnum = new int [1];
        pOldObjVnum [0] = iOldVnum;
        pNewObjVnum [0] = iNewVnum;
        break;

  case eRenumberRoom:
        iMobCount = 0;
        iObjCount = 0;
        iRoomCount = 1;
        pOldRoomVnum = new int [1];
        pNewRoomVnum = new int [1];
        pOldRoomVnum [0] = iOldVnum;
        pNewRoomVnum [0] = iNewVnum;
        break;

  } // end of switch

  iMilestone = 0;

  long iItems =  m_MobList.GetCount ()
                   + m_ObjectList.GetCount ()
                   + m_RoomList.GetCount ()
                   + m_ResetList.GetCount ()
                   + m_ShopList.GetCount ()
                   + m_RepairList.GetCount ()
                   + m_HelpList.GetCount ();
  
  Frame.CreateProgressBar ("Renumbering area", iItems);

  // on a renumber all, go through each one and assign its new number

  if (iRenumberType == eRenumberAll)
    {
    // renumber mobs

    iDifference = dlg.m_iNewLowMobVnum - mob_low_vnum;

    for (i = 0, mobPos = m_MobList.GetHeadPosition (); mobPos; i++)
      {
      mob = m_MobList.GetNext (mobPos);
      pOldMobVnum [i] = mob->vnum;    // remember old vnum
      if (dlg.m_bMobCompact)          
        mob->vnum = dlg.m_iNewLowMobVnum + i;   // compact, just add 1
      else
        mob->vnum = mob->vnum + iDifference;     // otherwise take difference
      pNewMobVnum [i] = mob->vnum;                  // remember new vnum
      mob->m_pTreeCtrl->SetItemText (mob->m_hdlTreeItem, mob->Summary ());  // alter summary
      // update vnum ranges
      if (mob->vnum > m_Area->mob_hi_vnum)
        m_Area->mob_hi_vnum = mob->vnum;
      if (mob->vnum < m_Area->mob_low_vnum)
        m_Area->mob_low_vnum = mob->vnum;
      } // end of each mob

    // renumber objects

    iDifference = dlg.m_iNewLowObjVnum - obj_low_vnum;

    for (i = 0, objPos = m_ObjectList.GetHeadPosition (); objPos; i++)
      {
      obj = m_ObjectList.GetNext (objPos);
      pOldObjVnum [i] = obj->vnum;    // remember old vnum
      if (dlg.m_bObjCompact)          
        obj->vnum = dlg.m_iNewLowObjVnum + i;   // compact, just add 1
      else
        obj->vnum = obj->vnum + iDifference;     // otherwise take difference
      pNewObjVnum [i] = obj->vnum;                  // remember new vnum
      obj->m_pTreeCtrl->SetItemText (obj->m_hdlTreeItem, obj->Summary ());  // alter summary
      // update vnum ranges
      if (obj->vnum > m_Area->obj_hi_vnum)
        m_Area->obj_hi_vnum = obj->vnum;
      if (obj->vnum < m_Area->obj_low_vnum)
        m_Area->obj_low_vnum = obj->vnum;
      } // end of each obj

    // renumber rooms

    iDifference = dlg.m_iNewLowRoomVnum - room_low_vnum;

    for (i = 0, roomPos = m_RoomList.GetHeadPosition (); roomPos; i++)
      {
      room = m_RoomList.GetNext (roomPos);
      pOldRoomVnum [i] = room->vnum;    // remember old vnum
      if (dlg.m_bRoomCompact)          
        room->vnum = dlg.m_iNewLowRoomVnum + i;   // compact, just add 1
      else
        room->vnum = room->vnum + iDifference;     // otherwise take difference
      pNewRoomVnum [i] = room->vnum;                  // remember new vnum
      room->m_pTreeCtrl->SetItemText (room->m_hdlTreeItem, room->Summary ());  // alter summary
      // update vnum ranges
      if (room->vnum > m_Area->room_hi_vnum)
        m_Area->room_hi_vnum = room->vnum;
      if (room->vnum < m_Area->room_low_vnum)
        m_Area->room_low_vnum = room->vnum;
      } // end of each room
    } // end of renumber all

  // fix up cross-references - cannot do above, as we may have an exit
  // to a room that is not renumbered yet!!

t_renumber ProgramRenumberStuff;

  ProgramRenumberStuff.pOldMobVnum    = pOldMobVnum ;
  ProgramRenumberStuff.pNewMobVnum    = pNewMobVnum ;
  ProgramRenumberStuff.pOldObjVnum    = pOldObjVnum ;
  ProgramRenumberStuff.pNewObjVnum    = pNewObjVnum ;
  ProgramRenumberStuff.pOldRoomVnum   = pOldRoomVnum;
  ProgramRenumberStuff.pNewRoomVnum   = pNewRoomVnum;
  ProgramRenumberStuff.iMobCount      = iMobCount; 
  ProgramRenumberStuff.iObjCount      = iObjCount ;
  ProgramRenumberStuff.iRoomCount     = iRoomCount;

  // fix up mobs

  for (mobPos = m_MobList.GetHeadPosition (); mobPos; )
    {
    mob = m_MobList.GetNext (mobPos);

    if (iMilestone++ % 32 == 0)
      Frame.UpdateProgressBar (iMilestone);

    for (POSITION progPos = mob->programlist.GetHeadPosition (); progPos; )
      {
      program = mob->programlist.GetNext (progPos);

      // renumber program
      CheckCommandSyntax (program->comlist, 
                          strMessage,
                          program->xref_rooms,
                          program->xref_objects,
                          program->xref_mobs,
                          &ProgramRenumberStuff);
      } // end of each program
    
    } // end of each mob


  // fix up rooms

  for (roomPos = m_RoomList.GetHeadPosition (); roomPos; )
    {
    room = m_RoomList.GetNext (roomPos);

    if (iMilestone++ % 32 == 0)
      Frame.UpdateProgressBar (iMilestone);

    // fix up the tele_vnum

    FixupRoomVnum (room->tele_vnum);

    // fix up all exits

    for (pos = room->exitlist.GetHeadPosition (); pos; )
      {
      CExit * exit = room->exitlist.GetNext (pos);
      FixupObjVnum (exit->key);
      FixupRoomVnum (exit->vnum);
      exit->m_pTreeCtrl->SetItemText (exit->m_hdlTreeItem, exit->Summary ());  // alter summary
      }   // end of processing each exit


    for (POSITION progPos = room->programlist.GetHeadPosition (); progPos; )
      {
      program = room->programlist.GetNext (progPos);

      // renumber program
      CheckCommandSyntax (program->comlist, 
                          strMessage,
                          program->xref_rooms,
                          program->xref_objects,
                          program->xref_mobs,
                          &ProgramRenumberStuff);
      } // end of each program

    }   // end of each room

  // fix up objects

  for (objPos = m_ObjectList.GetHeadPosition (); objPos; )
    {
    obj = m_ObjectList.GetNext (objPos);

    if (iMilestone++ % 32 == 0)
      Frame.UpdateProgressBar (iMilestone);

    for (POSITION progPos = obj->programlist.GetHeadPosition (); progPos; )
      {
      program = obj->programlist.GetNext (progPos);

      // renumber program
      CheckCommandSyntax (program->comlist, 
                          strMessage,
                          program->xref_rooms,
                          program->xref_objects,
                          program->xref_mobs,
                          &ProgramRenumberStuff);
      } // end of each program
    
    } // end of each obj


  // fix up the resets

  for (pos = m_ResetList.GetHeadPosition (); pos; )
    {
    CReset * reset = m_ResetList.GetNext (pos);

    if (iMilestone++ % 32 == 0)
      Frame.UpdateProgressBar (iMilestone);

    switch (reset->command)
	    {
	    case 'M':
          FixupMobVnum (reset->arg1);
          FixupRoomVnum (reset->arg3);
	        break;

	    case 'O':
          FixupObjVnum (reset->arg1);
          FixupRoomVnum (reset->arg3);
	        break;

	    case 'P':
          FixupObjVnum (reset->arg1);
          FixupObjVnum (reset->arg3);
	        break;

	    case 'G':
	    case 'E':
          FixupObjVnum (reset->arg1);
	        break;

	    case 'H':
          FixupObjVnum (reset->arg1);
	        break;

	    case 'D':
          FixupRoomVnum (reset->arg1);
	        break;

	    case 'R':
          FixupRoomVnum (reset->arg1);
	        break;
	    }   // end of switch
    reset->m_pTreeCtrl->SetItemText (reset->m_hdlTreeItem, reset->Summary ());  // alter summary
  }   // end of processing each reset


  // fix up the shops

  for (pos = m_ShopList.GetHeadPosition (); pos; )
    {
    CShop * shop = m_ShopList.GetNext (pos);

    if (iMilestone++ % 32 == 0)
      Frame.UpdateProgressBar (iMilestone);

    FixupMobVnum (shop->keeper);
    shop->m_pTreeCtrl->SetItemText (shop->m_hdlTreeItem, shop->Summary ());  // alter summary
    }   // end of processing each shop

  // fix up the repairs

  for (pos = m_RepairList.GetHeadPosition (); pos; )
    {
    CRepair * repair = m_RepairList.GetNext (pos);

    if (iMilestone++ % 32 == 0)
      Frame.UpdateProgressBar (iMilestone);

    FixupMobVnum (repair->keeper);
    repair->m_pTreeCtrl->SetItemText (repair->m_hdlTreeItem, repair->Summary ());  // alter summary
    }   // end of processing each repair

  // get rid of "from" and "to" arrays

  delete [] pOldMobVnum;
  delete [] pNewMobVnum;
  delete [] pOldObjVnum;
  delete [] pNewObjVnum;
  delete [] pOldRoomVnum;
  delete [] pNewRoomVnum;

  // don't show ridiculous numbers if no items in a category
  if (m_Area->mob_low_vnum == INT_MAX)
    m_Area->mob_low_vnum = 0;
  if (m_Area->obj_low_vnum == INT_MAX)
    m_Area->obj_low_vnum = 0;
  if (m_Area->room_low_vnum == INT_MAX)
    m_Area->room_low_vnum = 0;

  Frame.RemoveProgressBar ();

  SetModifiedFlag ();

  // tell them, if we renumber all
  if (iRenumberType == eRenumberAll)
    {
    // reselect "area" view so that vnums get updated correctly

    if (m_leftview)
      m_leftview->GetTreeCtrl().Select (m_leftview->m_hdlTreeArea, TVGN_CARET);

    ::AfxMessageBox ("Area renumbered", MB_ICONINFORMATION);
    }

  return true;  // OK return

} // end of CAreaEditorDoc::AreaRenumber

void CAreaEditorDoc::OnUpdateAreaRenumber(CCmdUI* pCmdUI) 
{
  pCmdUI->Enable (m_Area != NULL);
}


void CAreaEditorDoc::OnAreaRenumber() 
  {
  AreaRenumber ();    // renumber all
  } // end of CAreaEditorDoc::OnAreaRenumber