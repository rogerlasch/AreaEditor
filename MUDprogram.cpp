/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#include "stdafx.h"
#include "AreaEditor.h"

#include "AreaEditorDoc.h"

#include "MUDprogramView.h"
#include "AreaEditorView.h"
#include "defaults.h"


// constructor
CMUDprogram::CMUDprogram (CRuntimeClass* pViewClass, CAreaEditorDoc * pDoc) 
    : CMUDitem (pViewClass, pDoc) 
  {
  type = RAND_PROG;
  arglist = "100";
  comlist = "say This is a new program";
  } // end of constructor

void CMUDprogram::ChangeRHview (CAreaEditorView * pLHview, CView * pwhichView)
  {
  CMUDProgramView * pView = (CMUDProgramView *) pwhichView;

	ASSERT(pView->IsKindOf(RUNTIME_CLASS(CMUDProgramView)));

  pView->m_program = this;

  }

CString CMUDprogram::Summary (void)
  {

  CString strName = ProgramNameList.ReturnName (type, false);
  if (strName.Right (5) == "_prog")
    strName = strName.Left (strName.GetLength () - 5);

  return CFormat ("%s %s", 
                  (LPCTSTR) strName, 
                  (LPCTSTR) arglist);
  }

// add for a program adds one after the current one
CMUDitem * CMUDprogram::Add (CAreaEditorView * pView, const bool bSelect)
  {
  HTREEITEM hdlItem = m_pTreeCtrl->GetParentItem (m_hdlTreeItem);

  if (!hdlItem)
    return NULL;

  // find associated MUD item, if any
  CMUDitem * pItem = (CMUDitem *) m_pTreeCtrl->GetItemData (hdlItem);
  
  if (!pItem)
    return NULL; 

  return pItem->AddProgram (pView, this, bSelect);

  } // end of CMUDprogram::Add 

CString CMUDprogram::AddDescription (void)  // description of what add does
  {
  return "program";
  }   // end of CMUDprogram::AddDescription


// do a search for this item
BOOL CMUDprogram::Search (const CString strWanted, 
                       const int iFindType,
                       const BOOL bMatchCase)
    {
    
    // we only care about programs here
    if (iFindType != eFindProgram)
      return CMUDitem::Search (strWanted, iFindType, bMatchCase);

    CString strFound = comlist;

    // if not case-sensitive, make upper case
    if (!bMatchCase)
      strFound.MakeUpper ();

    return strFound.Find (strWanted) != -1;

    } // end of CMUDprogram::Search

#define DUPLICATE(arg) arg = RHside->arg

// copy function for duplicating programs
void CMUDprogram::Copy (const CMUDprogram * const RHside)
  {
  DUPLICATE (type);
  DUPLICATE (arglist);
  DUPLICATE (comlist);
  }

// clone this program
void CMUDprogram::Duplicate (CAreaEditorView * pView)
  {

  HTREEITEM hdlItem = m_pTreeCtrl->GetParentItem (m_hdlTreeItem);

  if (!hdlItem)
    return;

  // find associated MUD item, if any
  CMUDitem * pItem = (CMUDitem *) m_pTreeCtrl->GetItemData (hdlItem);
  
  if (!pItem)
    return; 

  CMUDprogram * newprogram = pItem->AddProgram (pView, this, false);

  if (newprogram)
    {
    newprogram->Copy (this);    // copy existing program over
    newprogram->m_pTreeCtrl->SetItemText (newprogram->m_hdlTreeItem, 
                                          newprogram->Summary ());
    newprogram->GoTo ();
    }

  } // end of CMUDprogram::Duplicate 