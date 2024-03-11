/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#include "stdafx.h"
#include "AreaEditor.h"


CSkill::CSkill ()
  {
  for (int x = 0; x < MAX_CLASS; x++ )
    {
    skill_level[x] = 0;
	  skill_adept[x] = 0;
    race_level[x] = 0;
    race_adept[x] = 0;
    }
  guild = -1;

  target = 0;			/* Legal targets		*/
  minimum_position = 0;	/* Position for caster / user	*/
  slot = 0;			/* Slot for #OBJECT loading	*/
  min_mana = 0;		/* Minimum mana used		*/
  beats = 0;			/* Rounds required to use skill	*/
  guild = 0;			/* Which guild the skill belongs to */
  min_level = 0;		/* Minimum level to be able to cast */
  type = 0;			/* Spell/Skill/Weapon/Tongue	*/
  flags = 0;			/* extra stuff			*/
  value = 0;			/* Misc value			*/
  saves = 0;			/* What saving spell applies	*/
  info = 0;     /* Spell action/class/etc - new in 1.4 */
  range = 0;    /* Range of spell (rooms) - new in 1.4 */
  difficulty = 0;		/* Difficulty of casting/learning */
  participants = 0;		/* # of required participants	*/
  iReferenced = 0;  // referenced count
  }   // end of constructor


CSkill::~CSkill ()
  {

  // get rid of affects inside skill

  for (POSITION affectPos = affects.GetHeadPosition (); affectPos; )
    delete affects.GetNext (affectPos);

  affects.RemoveAll ();  // pointers are deleted, remove list items

  } // end of destructor


void CSkill::AddToListBox (CListBox & ctlListBox, 
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

  } // end of CMUDitem::AddItemToListBox