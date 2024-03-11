/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#include "stdafx.h"
#include "AreaEditor.h"

#include "AreaEditorDoc.h"

#include "RepairView.h"

// constructor

CRepair::CRepair (CRuntimeClass* pViewClass, CAreaEditorDoc * pDoc) 
        : CMUDitem (pViewClass, pDoc) 
  {
int i;

  keeper = 0;		/* Vnum of shop keeper mob	*/
  for (i = 0; i < MAX_FIX; i++)
    fix_type [i] = 0;	/* Item types shop will fix	*/
  profit_fix = 100;		/* Cost multiplier for fixing	*/
  shop_type = SHOP_FIX;		/* Repair shop type		*/
  open_hour = 0;		/* First opening hour		*/
  close_hour = 23;		/* First closing hour		*/

  } // of constructor

void CRepair::ChangeRHview (CAreaEditorView * pLHview, CView * pwhichView)
  {
  CRepairView * pView = (CRepairView *) pwhichView;

	ASSERT(pView->IsKindOf(RUNTIME_CLASS(CRepairView)));

  pView->m_repair = this;

  }

CString CRepair::Summary (void)
  {
CMobile * mob;
CString strKeeper;

  if (mob = FindMob ( keeper))
    strKeeper = CFormat ("#%i %s", 
                    mob->vnum, 
                    (LPCTSTR) mob->short_descr);
  else
    strKeeper = CFormat ("#%i (not in area)", keeper);

  return CFormat ("%s", (LPCTSTR) strKeeper);
  }


void CRepair::Delete (void)
  {

  // delete from list of Repairs

  m_pDoc->m_RepairList.RemoveAt (m_pDoc->m_RepairList.Find (this, NULL));

  CMUDitem::Delete ();

  } // end of CRepair::Delete 
