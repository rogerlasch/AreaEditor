/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#include "stdafx.h"
#include "AreaEditor.h"


// constructor

CSocial::CSocial ()
   {
   iReferenced = 0; 
   }    // end of constructor


void CSocial::AddToListBox (CListBox & ctlListBox, 
                             const char * strDescription,
                             const bool bSelectIt)
  {

int nItem;

  // no description supplied, take item summary
  if (strDescription [0] == 0)
    nItem = ctlListBox.AddString (name);
  else
    nItem = ctlListBox.AddString (strDescription);

  // now set item data to this item, if we added it OK
  if (nItem != LB_ERR && nItem != LB_ERRSPACE)
    {
    ctlListBox.SetItemData (nItem, (DWORD) this);

    if (bSelectIt)
      ctlListBox.SetCurSel (nItem);

    }   // end of successful add

  } // end of CSocial::AddItemToListBox