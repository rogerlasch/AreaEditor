/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#include "stdafx.h"
#include "AreaEditor.h"

#include "AreaEditorDoc.h"

#include "AreaEditorView.h"
#include "ResetView.h"
#include "defaults.h"

// constructor
CReset::CReset (CRuntimeClass* pViewClass, CAreaEditorDoc * pDoc) 
        : CMUDitem (pViewClass, pDoc) 
  {
  command = 'M';  // load mob
  extra = 0;
  arg1 = 0;
  arg2 = 1;
  arg3 = 0;
  arg4 = 1;   // ROM
  }  // end of constructor

void CReset::ChangeRHview (CAreaEditorView * pLHview, CView * pwhichView)
  {
  CResetView * pView = (CResetView *) pwhichView;

	ASSERT(pView->IsKindOf(RUNTIME_CLASS(CResetView)));

  pView->m_reset = this;

  }

CString CReset::Summary (void)
  {

CString str1,
        str2,
        str3;

CMobile * mob;
CMUDObject * object,
           * destobject;
CRoom * room;

  switch (command)
    {
    case 'M':
        if (mob = m_pDoc->get_mob_index( arg1))
          str1 = mob->Summary ();
        else
        if (mob = FindMob (arg1))
          str1 = FullMobName (mob);
        else
          str1 = CFormat ("#%i (not in area)", arg1);
      
        if (room = m_pDoc->get_room_index(arg3))
          str2 = room->Summary ();
        else
        if (room = FindRoom (arg3))
          str2 = (FullRoomName (room));
        else
          str2 = CFormat ("#%i (not in area)", arg3);

        return CFormat ("Mob: %s => %s", 
                (LPCTSTR) str1, (LPCTSTR) str2);

    case 'E':
    case 'G':
        if (object = m_pDoc->get_obj_index( arg1))
          str1 = object->Summary ();
        else
        if (object = FindObj (arg1))
          str1 = FullObjName (object);
        else
          str1 = CFormat ("#%i (not in area)", arg1);
      
        if (command == 'E')
          {
          return CFormat ("-- Equip: %s (%s)", 
                          (LPCTSTR) str1,
                          (LPCTSTR) ObjectWearList.ReturnName (arg3, false));
          }
        else
          return CFormat ("-- Give:  %s", (LPCTSTR) str1);


    case 'D':
      
        if (room = m_pDoc->get_room_index(arg1))
          str1 = room->Summary ();
        else
        if (room = FindRoom (arg1))
          str1 = (FullRoomName (room));
        else
          str1 = CFormat ("#%i (not in area)", arg1);
  
        str2 = RoomDirectionList.ReturnName (arg2, false);

        switch (arg3)
          {
          case 0: str3 = "open"; break;
          case 1: str3 = "closed"; break;
          case 2: str3 = "closed and locked"; break;
          default: str3 = "Bad lock"; break;
          }

        return CFormat ("Door: %s/%s => %s", 
                        (LPCTSTR) str1, (LPCTSTR) str2, (LPCTSTR) str3);

    case 'R':
      
        if (room = m_pDoc->get_room_index(arg1))
          str1 = room->Summary ();
        else
        if (room = FindRoom (arg1))
          str1 = (FullRoomName (room));
        else
          str1 = CFormat ("#%i (not in area)", arg1);
  
        return CFormat ("Rand: %s (%i exit%s)", 
                        (LPCTSTR) str1, PLURAL (arg2));

    case 'O':
        if (object = m_pDoc->get_obj_index( arg1))
          str1 = object->Summary ();
        else
        if (object = FindObj (arg1))
          str1 = FullObjName (object);
        else
          str1 = CFormat ("#%i (not in area)", arg1);
      
        if (room = m_pDoc->get_room_index(arg3))
          str2 = room->Summary ();
        else
        if (room = FindRoom (arg3))
          str2 = (FullRoomName (room));
        else
          str2 = CFormat ("#%i (not in area)", arg3);

        return CFormat ("Object: %s => %s", 
                (LPCTSTR) str1, (LPCTSTR) str2);

    case 'P':
        if (object = m_pDoc->get_obj_index( arg1))
          str1 = object->Summary ();
        else
        if (object = FindObj (arg1))
          str1 = FullObjName (object);
        else
          str1 = CFormat ("#%i (not in area)", arg1);
      
        if (destobject = m_pDoc->get_obj_index( arg3))
          str2 = destobject->Summary ();
        else
        if (destobject = FindObj (arg3))
          str2 = FullObjName (destobject);
        else
          str2 = CFormat ("#%i (not in area)", arg3);

        return CFormat ("Put: %s => %s", 
                (LPCTSTR) str1, (LPCTSTR) str2);

    default:
      return CFormat ("%c %i %i %i %i", 
                      command, 
                      extra,
                      arg1,
                      arg2,
                      arg3);

    } // end of switch

  } // end of CReset::Summary


void CReset::Delete (void)
  {
POSITION pos = m_pDoc->m_ResetList.Find (this, NULL);

CReset * reset;

  if (!pos)
    {
    ::AfxMessageBox (CFormat ("Could not find reset \"%s\" in list of resets",
                      (LPCTSTR) Summary ()),
                      MB_ICONSTOP);
    return;   // Doh! could not find in reset list
    }

  if (command == 'M')
    {
  // if a mob reset, delete all EQUIP and GIVE resets until another mob

    for (POSITION nextpos = pos; nextpos; )
      {
      reset = m_pDoc->m_ResetList.GetNext (nextpos);
      if (reset == this)
        continue;   // ignore ourselves
      if (reset->command == 'M')
        break;    // stop when we get another mob reset
      if (reset->command == 'E' || reset->command == 'G')
        reset->Delete ();   // delete the Equip or Give reset
      }
    } // end of a mob

  // delete from list of resets

  m_pDoc->m_ResetList.RemoveAt (pos);

  CMUDitem::Delete ();

  } // end of CReset::Delete 

static int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM 
                lParamSort)
  {
CReset * reset1 = (CReset *) lParam1;
CReset * reset2 = (CReset *) lParam2;

  if (reset1->iSortSeq < reset2->iSortSeq)
    return -1;
  else if (reset1->iSortSeq > reset2->iSortSeq)
    return 1;
  else
    return 0;

  } // end of CompareFunc


// add for a reset adds one after the current one
CMUDitem * CReset::Add (CAreaEditorView * pView, const bool bSelect)
  {

TV_SORTCB sortCB;
int iSeq = 0;
   
    CReset * reset = new CReset (RUNTIME_CLASS(CResetView), m_pDoc);
    POSITION pos = m_pDoc->m_ResetList.Find (this, NULL);
    m_pDoc->m_ResetList.InsertAfter (pos, reset);    // and add it to our list
    HTREEITEM hdlResetItem = pView->AddTreeItem (reset, pView->m_hdlTreeResets);

    sortCB.hParent = pView->m_hdlTreeResets;
    sortCB.lpfnCompare = CompareFunc;
    sortCB.lParam = 0;

    // give each reset a sequence so we can sort them into list order
    for (POSITION resetPos = m_pDoc->m_ResetList.GetHeadPosition (); resetPos; )
      m_pDoc->m_ResetList.GetNext (resetPos)->iSortSeq = iSeq++;

    m_pTreeCtrl->SortChildrenCB (&sortCB);    // sort into proper order
    if (bSelect)
      m_pTreeCtrl->Select (hdlResetItem, TVGN_CARET);   // select it

    m_pDoc->SetModifiedFlag ();

    return reset;

  } // end of CReset::Add 

CString CReset::AddDescription (void)  // description of what add does
  {
  return "reset";
  }   // end of CReset::AddDescription


void CReset::Duplicate (CAreaEditorView * pView)
  {
TV_SORTCB sortCB;
int iSeq = 0;
   
  CReset * reset = new CReset (RUNTIME_CLASS(CResetView), m_pDoc);
  POSITION pos = m_pDoc->m_ResetList.Find (this, NULL);
  m_pDoc->m_ResetList.InsertAfter (pos, reset);    // and add it to our list
  HTREEITEM hdlResetItem = pView->AddTreeItem (reset, pView->m_hdlTreeResets);

  sortCB.hParent = pView->m_hdlTreeResets;
  sortCB.lpfnCompare = CompareFunc;
  sortCB.lParam = 0;

  // give each reset a sequence so we can sort them into list order
  for (POSITION resetPos = m_pDoc->m_ResetList.GetHeadPosition (); resetPos; )
    m_pDoc->m_ResetList.GetNext (resetPos)->iSortSeq = iSeq++;

  m_pTreeCtrl->SortChildrenCB (&sortCB);    // sort into proper order

  m_pDoc->SetModifiedFlag ();
  reset->Copy (this);
  reset->m_pTreeCtrl->SetItemText (reset->m_hdlTreeItem, reset->Summary ());
  reset->GoTo ();    // select it now it has been set up

  } // end of CReset::Duplicate 

#define DUPLICATE(arg) arg = RHside->arg

// copy function for duplicating mobs
void CReset::Copy (const CReset * const RHside)
  {
  DUPLICATE (command);
  DUPLICATE (extra);
  DUPLICATE (arg1);
  DUPLICATE (arg2);
  DUPLICATE (arg3);
  DUPLICATE (arg4); 
  }   // end of CReset::Copy

