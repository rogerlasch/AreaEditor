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

#include "ObjectView.h"
#include "AddToObjectDlg.h"
#include "defaults.h"

#include "MUDProgramView.h"
#include "ObjectAffectView.h"
#include "ObjectExtraDescriptionView.h"
#include "DeleteXrefDlg.h"

// constructor
CMUDObject::CMUDObject (CRuntimeClass* pViewClass, CAreaEditorDoc * pDoc)
        : CMUDitem (pViewClass, pDoc) 
    {
    name = strObjectDefaultName;
    short_descr = strObjectDefaultShortDescription;
    description = strObjectDefaultDescription;
    vnum = 0;
    item_type = ITEM_TRASH;
    extra_flags = 0;
    magic_flags = 0; 
    wear_flags = 0;
    weight = 1;
    cost = 0;
    value	[0] = 0;
    value	[1] = 0;
    value	[2] = 0;
    value	[3] = 0;
    value	[4] = 0;
    value	[5] = 0;
    layers = 0;
    rent = 0;	

    // ROM values
    level = 0;    
    condition = 100;

    }   // end of constructor

void CMUDObject::ChangeRHview (CAreaEditorView * pLHview, CView * pwhichView)
  {
  CObjectView * pView = (CObjectView *) pwhichView;

	ASSERT(pView->IsKindOf(RUNTIME_CLASS(CObjectView)));

  pView->m_object = this;

  pView->CreatePages ();   // add the tab control pages

  pView->ShowPages (m_pDoc);

  }

CString CMUDObject::Summary (void)
  {

  return CFormat ("#%i %s", 
                  vnum, 
                  (LPCTSTR) short_descr);
  }


CMUDObject::~CMUDObject ()
  {

  // get rid of programs inside object

  for (POSITION progPos = programlist.GetHeadPosition (); progPos; )
    delete programlist.GetNext (progPos);

  programlist.RemoveAll ();  // pointers are deleted, remove list items

  // get rid of affects inside object

  for (POSITION affectPos = affectlist.GetHeadPosition (); affectPos; )
    delete affectlist.GetNext (affectPos);

  affectlist.RemoveAll ();  // pointers are deleted, remove list items

  // get rid of extra descriptions inside object

  for (POSITION extraPos = extralist.GetHeadPosition (); extraPos; )
    delete extralist.GetNext (extraPos);

  extralist.RemoveAll ();  // pointers are deleted, remove list items

  } // end of destructor


void CMUDObject::Delete (void)
  {

  // look for things that refer to *this* object and tell them about it

CDeleteXrefDlg dlg;

CMUDitemList xrefList;
CMUDitemList xrefOwnerList;
CMobile * refmob = NULL;
CMUDitem * noitem = NULL;
 
  dlg.m_pxrefList = &xrefList;
  dlg.m_pxrefOwnerList = &xrefOwnerList;
  dlg.m_strAboutToDelete = Summary ();

  for (POSITION ResetPos = m_pDoc->m_ResetList.GetHeadPosition (); ResetPos; )
    {
    CReset * reset = m_pDoc->m_ResetList.GetNext (ResetPos);

    switch (reset->command)
	    {

      case 'M':
          refmob = m_pDoc->get_mob_index  (reset->arg1);    // remember for owner later
          break;

	    case 'O':
          if (reset->arg1 == vnum)
            {
            xrefOwnerList.AddTail (noitem);   // no owner of reset
            xrefList.AddTail (reset);       // which reset
            }
	        break;

	    case 'P':
          if (reset->arg1 == vnum || reset->arg3 == vnum)
            {
            xrefOwnerList.AddTail (noitem);   // no owner of reset
            xrefList.AddTail (reset);       // which reset
            }
	        break;

	    case 'G':
	    case 'E':
          if (reset->arg1 == vnum)
            {
            xrefOwnerList.AddTail (refmob);   // which mob owns the item
            xrefList.AddTail (reset);       // which reset
            }
	        break;

	    case 'H':
          if (reset->arg1 == vnum)
            {
            xrefOwnerList.AddTail (noitem);   // no owner of reset
            xrefList.AddTail (reset);       // which reset
            }
	        break;

	    }   // end of switch

  }   // end of processing each reset
  
  if (!xrefList.IsEmpty ())   // don't bother if no references
    if (dlg.DoModal () != IDOK)
      return;   // they changed their mind (hope it works better!)

  // delete referencing items

  for (POSITION refPos = xrefList.GetHeadPosition (); refPos; )
    xrefList.GetNext (refPos)->Delete ();

  // delete programs inside object

  for (POSITION progPos = programlist.GetHeadPosition (); progPos; )
    programlist.GetNext (progPos)->Delete ();

  programlist.RemoveAll ();  // pointers are deleted, remove list items

  // delete affects inside object

  for (POSITION affectPos = affectlist.GetHeadPosition (); affectPos; )
    affectlist.GetNext (affectPos)->Delete ();

  affectlist.RemoveAll ();  // pointers are deleted, remove list items

  // delete extra descriptions inside object

  for (POSITION extraPos = extralist.GetHeadPosition (); extraPos; )
    extralist.GetNext (extraPos)->Delete ();

  extralist.RemoveAll ();  // pointers are deleted, remove list items

  // delete from list of objects

  m_pDoc->m_ObjectList.RemoveAt (m_pDoc->m_ObjectList.Find (this, NULL));

  CMUDitem::Delete ();

  } // end of CMUDObject::Delete 

CMUDitem * CMUDObject::Add (CAreaEditorView * pView, const bool bSelect)
  {
// add program, affect or extra to this object
CAddToObjectDlg dlg;

  dlg.m_iAddType = 0;

  if (dlg.DoModal () != IDOK)
    return NULL;   // they cancelled, the bastards!

CMUDprogram * prog;
HTREEITEM hdlItem;
CMUDitem * pItem = NULL;

  switch (dlg.m_iAddType)
    {
    case 0:   // Affect

            pItem = AddAffect (pView);
            break;

    case 1:   // Extra description

            pItem = AddDescription (pView);
            break;


    case 2:   // Program
            
            prog = new CMUDprogram (RUNTIME_CLASS(CMUDProgramView), 
                                m_pDoc);
            programlist.AddHead (prog);    // and add it to our list
            hdlItem = pView->AddTreeItem (prog, m_hdlTreeItem);
            if (bSelect)
              m_pTreeCtrl->Select (hdlItem, TVGN_CARET);   // select it
            m_pDoc->SetModifiedFlag ();
            pItem = prog;
            break;


    }

  if (bSelect)
    pItem->GoTo ();
  return pItem;
  } // end of CMUDObject::Add 

CString CMUDObject::AddDescription (void)  // description of what add does
  {
  return "affect/description/program";
  }   // end of CMUDObject::AddDescription

void CMUDObject::SubItemDeleted (CMUDitem * pItem)
  {
POSITION pos;

 // a program has been deleted?

  if (pos = programlist.Find (pItem, NULL))
    programlist.RemoveAt (pos);

 // an affect been deleted?

  if (pos = affectlist.Find (pItem, NULL))
    affectlist.RemoveAt (pos);

 // an extra description has been deleted?

  if (pos = extralist.Find (pItem, NULL))
    extralist.RemoveAt (pos);

  } // end of CMUDObject::SubItemDeleted 

static int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM 
                lParamSort)
  {
CMUDprogram * prog1 = (CMUDprogram *) lParam1;
CMUDprogram * prog2 = (CMUDprogram *) lParam2;

  if (prog1->iSortSeq < prog2->iSortSeq)
    return -1;
  else if (prog1->iSortSeq > prog2->iSortSeq)
    return 1;
  else
    return 0;

  } // end of CompareFunc

// add for a program adds one after the current one
CMUDprogram * CMUDObject::AddProgram (CAreaEditorView * pView, 
                                     CMUDitem * pItem,
                                     const bool bSelect)
  {
TV_SORTCB sortCB;
int iSeq = 0;
   
    CMUDprogram * prog = new CMUDprogram (RUNTIME_CLASS(CMUDProgramView), m_pDoc);
    if (pItem)
      {
      POSITION pos = programlist.Find (pItem, NULL);
      programlist.InsertAfter (pos, prog);    // and add it to our list
      }
    else
      programlist.AddHead (prog);    // add at head

    HTREEITEM hdlprogItem = pView->AddTreeItem (prog, m_hdlTreeItem);

    sortCB.hParent = m_hdlTreeItem;
    sortCB.lpfnCompare = CompareFunc;
    sortCB.lParam = 0;

    // give each prog a sequence so we can sort them into list order
    for (POSITION progPos = programlist.GetHeadPosition (); progPos; )
      programlist.GetNext (progPos)->iSortSeq = iSeq++;

    m_pTreeCtrl->SortChildrenCB (&sortCB);    // sort into proper order
    if (bSelect)
      m_pTreeCtrl->Select (hdlprogItem, TVGN_CARET);   // select it

    m_pDoc->SetModifiedFlag ();

    return prog;

  } // end of CMUDObject::AddProgram 

// add for a new description
CExtraDescription * CMUDObject::AddDescription (CAreaEditorView * pView)
  {

    CExtraDescription * extra = new CExtraDescription 
                      (RUNTIME_CLASS(CObjectExtraDescriptionView), m_pDoc);
    extralist.AddHead (extra);    // and add it to our list
    pView->AddTreeItem (extra, m_hdlTreeItem);
    m_pDoc->SetModifiedFlag ();

    return extra;
  } // end of CMUDObject::AddDescription 

// add for a new affect
CAffect * CMUDObject::AddAffect (CAreaEditorView * pView)
  {

    CAffect * affect = new CAffect (RUNTIME_CLASS(CObjectAffectView), m_pDoc);
    affectlist.AddHead (affect);    // and add it to our list
    pView->AddTreeItem (affect, m_hdlTreeItem);
    m_pDoc->SetModifiedFlag ();

    return affect;
  } // end of CMUDObject::CAffect 

// do a search for this item
BOOL CMUDObject::Search (const CString strWanted, 
                       const int iFindType,
                       const BOOL bMatchCase)
    {
CString strFound;
 
    // switch on find type
    switch (iFindType)
      {
      case eFindVnum:
      
          if (isalpha (strWanted [0]))
            {
            if (strWanted [0] != 'O')
              return FALSE;   // they aren't looking for objects
            return atoi (strWanted.Mid (1)) == vnum; 
            }

          return atoi (strWanted) == vnum; 

      case eFindDetail:
            
            SEARCH (name);
            SEARCH (short_descr);
            SEARCH (description);
            SEARCH (action_desc);
            SEARCH (ObjectItemList.ReturnName (item_type, false));
            SEARCH (convert_object_flags (extra_flags));
            SEARCH (convert_wear_flags (wear_flags));
            SEARCH (ValueSummary ());

            return FALSE;

      default:

          return CMUDitem::Search (strWanted, iFindType, bMatchCase);

      }   // end of switch

    } // end of CMUDObject::Search


void CMUDObject::Duplicate (CAreaEditorView * pView)
  {
CMUDObject * object = m_pDoc->AddObject (pView, false);

  if (!object)
    return;   // could not create a new object (no vnums available?)

  object->Copy (this);
  object->m_pTreeCtrl->SetItemText (object->m_hdlTreeItem, object->Summary ());

// now duplicate programs in the object

CMUDprogram * oldProg,
            * newProg;
CString strMessage;  

  for (POSITION progPos = programlist.GetHeadPosition (); progPos; )
    {
    oldProg = programlist.GetNext (progPos);  // get a program
    newProg = new CMUDprogram (RUNTIME_CLASS(CMUDProgramView), m_pDoc);   // make a new one
    object->programlist.AddTail (newProg);   // add to new object
    pView->AddTreeItem (newProg, object->m_hdlTreeItem); // add to object's tree item
    newProg->Copy (oldProg);
    // check syntax so cross-referencing will be correct
    CheckCommandSyntax (newProg->comlist, 
                        strMessage,
                        newProg->xref_objects,
                        newProg->xref_objects,
                        newProg->xref_objects);
    newProg->m_pTreeCtrl->SetItemText (newProg->m_hdlTreeItem, newProg->Summary ());
    }   // end of processing each program

// now duplicate extra descriptions for the object

CExtraDescription * oldDesc,
                  * newDesc;

  for (POSITION DescPos = extralist.GetHeadPosition (); DescPos; )
    {
    oldDesc = extralist.GetNext (DescPos);  // get a description
    newDesc = new CExtraDescription (RUNTIME_CLASS(CObjectExtraDescriptionView), m_pDoc);   // make a new one
    object->extralist.AddTail (newDesc);   // add to new object
    pView->AddTreeItem (newDesc, object->m_hdlTreeItem); // add to object's tree item
    newDesc->Copy (oldDesc);
    newDesc->m_pTreeCtrl->SetItemText (newDesc->m_hdlTreeItem, newDesc->Summary ());
    }   // end of processing each description

// now duplicate Affects for the object

CAffect * oldAffect,
        * newAffect;

  for (POSITION AffectPos = affectlist.GetHeadPosition (); AffectPos; )
    {
    oldAffect = affectlist.GetNext (AffectPos);  // get an Affect
    newAffect = new CAffect (RUNTIME_CLASS(CObjectAffectView), m_pDoc);   // make a new one
    object->affectlist.AddTail (newAffect);   // add to new object
    pView->AddTreeItem (newAffect, object->m_hdlTreeItem); // add to object's tree item
    newAffect->Copy (oldAffect);
    newAffect->m_pTreeCtrl->SetItemText (newAffect->m_hdlTreeItem, newAffect->Summary ());
    }   // end of processing each Affect

  object->GoTo ();    // select it now it has been set up

  } // end of CMUDObject::Duplicate 

#define DUPLICATE(arg) arg = RHside->arg

// copy function for duplicating objects
void CMUDObject::Copy (const CMUDObject * const RHside)
  {
   DUPLICATE (name);
   DUPLICATE (short_descr);
   DUPLICATE (description);
   DUPLICATE (action_desc);
// nb - do not duplicate vnum! - that must be unique
   DUPLICATE (item_type);
   DUPLICATE (extra_flags);
   DUPLICATE (magic_flags);
   DUPLICATE (wear_flags);
   DUPLICATE (weight);
   DUPLICATE (cost);
   DUPLICATE (layers);
   DUPLICATE (rent);
   for (int i = 0; i < 6; i++)
     DUPLICATE (value [i]);
  } // end of CMUDObject::Copy 

CString CMUDObject::ValueSummary (void) const  // summarises what the values mean
  {

  switch (item_type)
    {
    case ITEM_ARMOR:      return CFormat ("AC: %i, current AC: %i",
                                      - value [0], - value [1]);

    case ITEM_CONTAINER:  return CFormat ("Capacity: %i", value [0]);

    case ITEM_DRINK_CON:  return CFormat ("Capacity: %i, quantity %i", 
                                      value [0], value [1]);

    case ITEM_FOOD:       return CFormat ("Food value: %i", value [0]);

	  case ITEM_PILL:
	  case ITEM_POTION:
	  case ITEM_SCROLL:

          {
          CString strResult;

          if (m_pDoc->skill_name (value[1], true) != "NONE")
            strResult += "'" + m_pDoc->skill_name (value[1]) + "' ";
          if (m_pDoc->skill_name (value[2], true) != "NONE")
            strResult += "'" + m_pDoc->skill_name (value[2]) + "' ";
          if (m_pDoc->skill_name (value[3], true) != "NONE")
            strResult += "'" + m_pDoc->skill_name (value[3]) + "' ";

          if (strResult.IsEmpty ())
            strResult = "'NONE'";

          return CFormat ("Level %i, spell(s): %s", 
                          value[0],
                          (LPCTSTR) strResult);
          }

	    case ITEM_STAFF:
	    case ITEM_WAND:


          return CFormat ("Level: %i, charges: %i, max charges: %i, spell: '%s'", 
                          value[0],
                          value[1],
                          value[2],
                          (LPCTSTR) m_pDoc->skill_name (value[3], true));

	    case ITEM_SALVE:

          {
          CString strResult;

          if (m_pDoc->skill_name (value[4], true) != "NONE")
            strResult += "'" + m_pDoc->skill_name (value[4]) + "' ";
          if (m_pDoc->skill_name (value[5], true) != "NONE")
            strResult += "'" + m_pDoc->skill_name (value[5]) + "' ";

          if (strResult.IsEmpty ())
            strResult = "'NONE'";

          return CFormat ("Level %i, max charge: %i, charges: %i, delay: %i, spell(s): %s", 
                          value[0],
                          value[1],
                          value[2],
                          value[3],
                          (LPCTSTR) strResult);
          }

      case ITEM_WEAPON:

        {
          CString strResult;

          strResult =  CFormat ("Attack: %id%i, weapon type: %s", 
                            value[1],
                            value[2],
                            (LPCTSTR) ObjectAttackList.ReturnName (value[3], false));


          if (m_pDoc->m_AreaType == eROM && value [4])
            {
            strResult += ", flags: ";
            strResult += FlagToString (value[4], ObjectWeaponFlags);
            } // end of a ROM object with weapon flags

          return strResult;

        }

      case ITEM_LIGHT:

        if (value[2] == -1)
          return "Hours left: infinite";

        return CFormat ("Hours left: %i", value [2]);

    } // end of switch

  return "";

  } // end of  CMUDObject::ValueSummary
