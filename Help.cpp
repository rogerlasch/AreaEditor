/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#include "stdafx.h"
#include "AreaEditor.h"

#include "AreaEditorDoc.h"

#include "HelpView.h"

// constructor
CHelp::CHelp (CRuntimeClass* pViewClass, CAreaEditorDoc * pDoc)
        : CMUDitem (pViewClass, pDoc) 
  {
  level = 1;
  keyword = "new help topic";
  } // of constructor

void CHelp::ChangeRHview (CAreaEditorView * pLHview, CView * pwhichView)
  {
  CHelpView * pView = (CHelpView *) pwhichView;

	ASSERT(pView->IsKindOf(RUNTIME_CLASS(CHelpView)));

  pView->m_help = this;

  }

CString CHelp::Summary (void)
  {
  return CFormat ("%s", 
                  (LPCTSTR) keyword);
  }

void CHelp::Delete (void)
  {

  // delete from list of Helps

  m_pDoc->m_HelpList.RemoveAt (m_pDoc->m_HelpList.Find (this, NULL));

  CMUDitem::Delete ();

  } // end of CHelp::Delete 

// do a search for this item
BOOL CHelp::Search (const CString strWanted, 
                       const int iFindType,
                       const BOOL bMatchCase)
    {
CString strFound;
    
    // we only care about detailed searches here
    if (iFindType != eFindDetail)
      return CMUDitem::Search (strWanted, iFindType, bMatchCase);
  
    SEARCH (keyword);
    SEARCH (text);

    return FALSE;

    } // end of CHelp::Search