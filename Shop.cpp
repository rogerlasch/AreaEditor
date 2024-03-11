/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#include "stdafx.h"
#include "AreaEditor.h"

#include "AreaEditorDoc.h"

#include "ShopView.h"

// constructor

CShop::CShop (CRuntimeClass* pViewClass, CAreaEditorDoc * pDoc) 
      : CMUDitem (pViewClass, pDoc) 
  {

int i;

  keeper = 0;			/* Vnum of shop keeper mob	*/
  for (i = 0; i < MAX_TRADE; i++)
    buy_type [i] = 0;	/* Item types shop will buy	*/
  profit_buy = 120;		/* Cost multiplier for buying	*/
  profit_sell = 90;		/* Cost multiplier for selling	*/
  open_hour = 0;		/* First opening hour		*/
  close_hour = 23;		/* First closing hour		*/

  } // of constructor

void CShop::ChangeRHview (CAreaEditorView * pLHview, CView * pwhichView)
  {
  CShopView * pView = (CShopView *) pwhichView;

	ASSERT(pView->IsKindOf(RUNTIME_CLASS(CShopView)));

  pView->m_shop = this;
  pView->m_pLHview = pLHview;

  }

CString CShop::Summary (void)
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

void CShop::Delete (void)
  {

  // delete from list of Shops

  m_pDoc->m_ShopList.RemoveAt (m_pDoc->m_ShopList.Find (this, NULL));

  CMUDitem::Delete ();

  } // end of CShop::Delete 
