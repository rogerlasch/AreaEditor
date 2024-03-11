/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#include "stdafx.h"
#include "AreaEditor.h"

#include "AreaEditorDoc.h"

#include "AreaView.h"

#include "defaults.h"

// constructor
CArea::CArea (CRuntimeClass* pViewClass, CAreaEditorDoc * pDoc) 
      : CMUDitem (pViewClass, pDoc) 
  
  {
	low_soft_range = 0;
	hi_soft_range = iMaxLevel;
	low_hard_range = 0;
	hi_hard_range = iMaxLevel;

  flags = 0;
  reset_frequency = 0;

  high_economy = 0;
  low_economy = 0;

  strAuthor = "unknown";

  // version 1.4 stuff

  // area version
  area_version = 0;
  
  // weather
  climate_temp = 2;
  climate_precip = 2;
  climate_wind = 2;


  // generated as we load the area
  obj_low_vnum = INT_MAX;
  obj_hi_vnum = 0;

  mob_low_vnum = INT_MAX;
  mob_hi_vnum = 0;

  room_low_vnum = INT_MAX;
  room_hi_vnum = 0;
  
  min_vnum = 0;   // ROM
  max_vnum = 0;   // ROM

  }   // end of constructor

void CArea::ChangeRHview (CAreaEditorView * pLHview, CView * pwhichView)
  {
  CAreaView * pView = (CAreaView *) pwhichView;

	ASSERT(pView->IsKindOf(RUNTIME_CLASS(CAreaView)));

  pView->m_area = this;

  pView->CreatePages ();   // add the tab control pages

  pView->ShowPages (m_pDoc);

  }

CString CArea::Summary (void)
  {
  return "Area";
  }


void CArea::Delete (void)
  {

  // deleting the area is too hard - don't do it

  } // end of CArea::Delete 
