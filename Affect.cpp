/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#include "stdafx.h"
#include "AreaEditor.h"

#include "AreaEditorDoc.h"
#include "defaults.h"

#include "ObjectAffectView.h"

// constructor
CAffect::CAffect (CRuntimeClass* pViewClass, CAreaEditorDoc * pDoc) 
      : CMUDitem (pViewClass, pDoc) 
    {

    location = APPLY_NONE;
    modifier = 1;
    where = TO_OBJECT;  // ROM
    bitvector = 0;  // ROM

    }   // end of constructor

void CAffect::ChangeRHview (CAreaEditorView * pLHview, CView * pwhichView)
  {
  CObjectAffectView * pView = (CObjectAffectView *) pwhichView;

	ASSERT(pView->IsKindOf(RUNTIME_CLASS(CObjectAffectView)));

  pView->m_affect = this;

  }

CString CAffect::Summary (void)
  {

  CString strLocation = ObjectAffectList.ReturnName (location % REVERSE_APPLY, false);
	if ( location >= REVERSE_APPLY )
		strLocation += " (caster)";

  CString strModifier;

  // if the affect is to change resistant/immune/susceptible
  // then the modifier is in fact a bitmap (in a string)

  switch (location % REVERSE_APPLY)
    {
    case APPLY_RESISTANT:
    case APPLY_IMMUNE:
    case APPLY_SUSCEPTIBLE:
      strModifier = "to \"" + convert_risflag (modifier) + "\'";
      break;

    case APPLY_AFFECT:
      strModifier = "\'" + convert_affectflag (modifier) + "\'";
      break;

    default: 
      strModifier = CFormat ("by %i", modifier);
      break;

    } // end of switch

  CString strWhere;

  if (m_pDoc->m_AreaType == eROM)
    {
    strWhere = " [";
    strWhere += ObjectAffectWhereList.ReturnName (where);
    strWhere += "] ";
    }

  return CFormat ("Affects: %s %s%s", 
                  (LPCTSTR) strLocation,
                  (LPCTSTR) strWhere,
                  (LPCTSTR) strModifier);
  }



// do a search for this item
BOOL CAffect::Search (const CString strWanted, 
                       const int iFindType,
                       const BOOL bMatchCase)
    {
CString strFound;
    
    // we only care about detailed searches here
    if (iFindType != eFindDetail)
      return CMUDitem::Search (strWanted, iFindType, bMatchCase);

    SEARCH (Summary ());

    return FALSE;

    } // end of CAffect::Search

#define DUPLICATE(arg) arg = RHside->arg

// copy function for duplicating affects
void CAffect::Copy (const CAffect * const RHside)
  {
  DUPLICATE (location);
  DUPLICATE (modifier);
  }

// clone this affect
void CAffect::Duplicate (CAreaEditorView * pView)
  {

  HTREEITEM hdlItem = m_pTreeCtrl->GetParentItem (m_hdlTreeItem);

  if (!hdlItem)
    return;

  // find associated MUD item, if any
  CMUDitem * pItem = (CMUDitem *) m_pTreeCtrl->GetItemData (hdlItem);
  
  if (!pItem)
    return; 

  CAffect * newaffect = pItem->AddAffect (pView);

  if (newaffect)
    {
    newaffect->Copy (this);    // copy existing affect over
    newaffect->m_pTreeCtrl->SetItemText (newaffect->m_hdlTreeItem, 
                                              newaffect->Summary ());
    newaffect->GoTo ();
    }

  } // end of CAffect::Duplicate 