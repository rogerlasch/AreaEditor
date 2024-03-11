/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#include "stdafx.h"
#include "AreaEditor.h"

#include "AreaEditorDoc.h"

#include "MobileView.h"
#include "defaults.h"

#include "AreaEditorView.h"
#include "MUDProgramView.h"
#include "DeleteXrefDlg.h"

// constructor
CMobile::CMobile (CRuntimeClass* pViewClass, CAreaEditorDoc * pDoc) 
        : CMUDitem (pViewClass, pDoc) 
  {

  player_name = strMobDefaultName;
  short_descr = strMobDefaultShortDescription;
  long_descr = strMobDefaultLongDescription;
 	description = strMobDefaultDescription;

  vnum = 0;
  sex = 0;
  level = 1;
  act = ACT_IS_NPC;    
  affected_by = 0;
  alignment = 0;
  mobthac0 = 0;
  ac = 0;
  hitnodice = 8;
  hitsizedice = 1;
  hitplus = 0;
  damnodice = 0;
  damsizedice = 0;
  damplus = 0;
  numattacks = 0;
  gold = 0;
  exp = 0;
  xflags = 0;
  resistant = 0;
  immune = 0;
  susceptible = 0;
	attacks = 0;
	defenses = 0;
  speaks = 0;   // common
  speaking = 0;   // common
  position = POS_STANDING;
  defposition = POS_STANDING;
  height = 0;
  weight = 0;
  race = 0;   // probably RACE_HUMAN
  mobclass = 0;   // probably CLASS_MAGE
  hitroll = 0;
  damroll = 0;
  perm_str = 13;
  perm_int = 13;
  perm_wis = 13;
  perm_dex = 13;
  perm_con = 13;
  perm_cha = 13;
  perm_lck = 13;
  saving_poison_death = 0;
  saving_wand = 0;
  saving_para_petri = 0;
  saving_breath = 0;
  saving_spell_staff = 0;
  spec_fun = 0;

  // ROM stuff

  group = 0;
  ac_pierce = 0;   
  ac_bash = 0;     
  ac_slash = 0;    
  ac_exotic = 0;   
  dam_type = 0;    
  mananodice = 0;  
  manasizedice = 0;
  manaplus = 0; 
  size = 0;   // tiny
  form = 0;
  remove_act = 0; 
  remove_aff = 0; 
  remove_off = 0; 
  remove_imm = 0; 
  remove_res = 0; 
  remove_vul = 0; 
  remove_for = 0; 
  remove_par = 0; 

  }  // end of constructor

void CMobile::ChangeRHview (CAreaEditorView * pLHview, CView * pwhichView)
  {
  CMobileView * pView = (CMobileView *) pwhichView;

	ASSERT(pView->IsKindOf(RUNTIME_CLASS(CMobileView)));

  pView->m_mob = this;

  pView->CreatePages ();   // add the tab control pages

  pView->ShowPages (m_pDoc);

  }

CString CMobile::Summary (void)
  {

  return CFormat ("#%i %s", 
                  vnum, 
                  (LPCTSTR) short_descr);
  }


CMobile::~CMobile ()
  {

  // get rid of programs inside mobile

  for (POSITION progPos = programlist.GetHeadPosition (); progPos; )
    delete programlist.GetNext (progPos);

  programlist.RemoveAll ();  // pointers are deleted, remove list items

  } // end of destructor


void CMobile::Delete (void)
  {

  // look for things that refer to *this* mob and tell them about it

CDeleteXrefDlg dlg;

CMUDitemList xrefList;
CMUDitemList xrefOwnerList;
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

  // delete programs inside mobile

  for (POSITION progPos = programlist.GetHeadPosition (); progPos; )
    programlist.GetNext (progPos)->Delete ();

  programlist.RemoveAll ();  // pointers are deleted, remove list items

  // delete from list of mobs

  m_pDoc->m_MobList.RemoveAt (m_pDoc->m_MobList.Find (this, NULL));

  CMUDitem::Delete ();

  } // end of CMobile::Delete 


CMUDitem * CMobile::Add (CAreaEditorView * pView, const bool bSelect)
  {

  // add a program to a mobile
  return AddProgram (pView, NULL, bSelect);

  } // end of CMobile::Add 

CString CMobile::AddDescription (void)  // description of what add does
  {
  return "mob program";
  }   // end of CMobile::AddDescription

void CMobile::SubItemDeleted (CMUDitem * pItem)
  {
POSITION pos;

 // a program has been deleted?

  if (pos = programlist.Find (pItem, NULL))
    programlist.RemoveAt (pos);

  } // end of CMobile::SubItemDeleted 


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
CMUDprogram * CMobile::AddProgram (CAreaEditorView * pView, 
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
  } // end of CMobile::AddProgram 

// do a search for this item
BOOL CMobile::Search (const CString strWanted, 
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
            if (strWanted [0] != 'M')
              return FALSE;   // they aren't looking for mobs
            return atoi (strWanted.Mid (1)) == vnum; 
            }

          return atoi (strWanted) == vnum; 

      case eFindDetail:
            
            SEARCH (player_name);
            SEARCH (short_descr);
            SEARCH (long_descr);
            SEARCH (description);
            SEARCH (MobSpecialList.ReturnName (spec_fun, false));
            SEARCH (convert_actflag (act));
            SEARCH (convert_partflag (xflags));
            SEARCH (convert_attackflag (attacks));
            SEARCH (convert_affectflag (affected_by));
            if (m_pDoc->m_AreaType == eROM)
              {
              SEARCH (convert_formflag (form));
              }
            else
              {
              SEARCH (convert_defenseflag (defenses));
              }
            SEARCH (convert_risflag (resistant));
            SEARCH (convert_risflag (immune));
            SEARCH (convert_risflag (susceptible));
            SEARCH (convert_languages (speaks));
            SEARCH (convert_languages (speaking));
            SEARCH (CFormat (
                    "Str: %i, Int: %i, Wis: %i, Dex: %i, Con: %i, Cha: %i, Lck: %i",
                    perm_str, perm_int, perm_wis, 
                    perm_dex, perm_con, perm_cha, perm_lck));
            SEARCH (MobSexList.ReturnName (sex, false));

            return FALSE;

      default:

          return CMUDitem::Search (strWanted, iFindType, bMatchCase);

      }   // end of switch

    } // end of CMobile::Search

void CMobile::Duplicate (CAreaEditorView * pView)
  {
CMobile * mob = m_pDoc->AddMobile (pView, false);

  if (!mob)
    return;   // could not create a new mob (no vnums available?)

  mob->Copy (this);

  mob->m_pTreeCtrl->SetItemText (mob->m_hdlTreeItem, mob->Summary ());

// now duplicate programs in the mob

CMUDprogram * oldProg,
            * newProg;
CString strMessage;  

  for (POSITION progPos = programlist.GetHeadPosition (); progPos; )
    {
    oldProg = programlist.GetNext (progPos);  // get a program
    newProg = new CMUDprogram (RUNTIME_CLASS(CMUDProgramView), m_pDoc);   // make a new one
    mob->programlist.AddTail (newProg);   // add to new mob
    pView->AddTreeItem (newProg, mob->m_hdlTreeItem); // add to mob's tree item
    newProg->Copy (oldProg);
    // check syntax so cross-referencing will be correct
    CheckCommandSyntax (newProg->comlist, 
                        strMessage,
                        newProg->xref_rooms,
                        newProg->xref_objects,
                        newProg->xref_mobs);
    newProg->m_pTreeCtrl->SetItemText (newProg->m_hdlTreeItem, newProg->Summary ());
    }   // end of processing each program

  mob->GoTo ();    // select it now it has been set up

  } // end of CMobile::Duplicate 

#define DUPLICATE(arg) arg = RHside->arg

// copy function for duplicating mobs
void CMobile::Copy (const CMobile * const RHside)
  {
   DUPLICATE (player_name);
   DUPLICATE (short_descr);
   DUPLICATE (long_descr);
   DUPLICATE (description);
// nb - do not duplicate vnum! - that must be unique
   DUPLICATE (sex);
   DUPLICATE (level);
   DUPLICATE (act);
   DUPLICATE (affected_by);
   DUPLICATE (alignment);
   DUPLICATE (mobthac0);	
   DUPLICATE (ac);
   DUPLICATE (hitnodice);
   DUPLICATE (hitsizedice);
   DUPLICATE (hitplus);
   DUPLICATE (damnodice);
   DUPLICATE (damsizedice);
   DUPLICATE (damplus);
   DUPLICATE (numattacks);
   DUPLICATE (gold);
   DUPLICATE (exp);
   DUPLICATE (xflags);
   DUPLICATE (resistant);
   DUPLICATE (immune);
   DUPLICATE (susceptible);
   DUPLICATE (attacks);
   DUPLICATE (defenses);
   DUPLICATE (speaks);
   DUPLICATE (speaking);
   DUPLICATE (position);
   DUPLICATE (defposition);
   DUPLICATE (height);
   DUPLICATE (weight);
   DUPLICATE (race);
   DUPLICATE (mobclass);
   DUPLICATE (hitroll);
   DUPLICATE (damroll);
   DUPLICATE (perm_str);
   DUPLICATE (perm_int);
   DUPLICATE (perm_wis);
   DUPLICATE (perm_dex);
   DUPLICATE (perm_con);
   DUPLICATE (perm_cha);
   DUPLICATE (perm_lck);
   DUPLICATE (saving_poison_death);
   DUPLICATE (saving_wand);
   DUPLICATE (saving_para_petri);
   DUPLICATE (saving_breath);
   DUPLICATE (saving_spell_staff);
  }   // end of CMobile::Copy

