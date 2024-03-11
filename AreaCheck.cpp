/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#include "stdafx.h"
#include "AreaEditor.h"

#include "MainFrm.h"
#include "defaults.h"

#include "AreaEditorDoc.h"
#include "AreaLoadingProblems.h"
#include "AreaEditorView.h"
#include "ProgDlg.h"
       

CString strMessage;
int nErrors;
int iTotalPrograms;

void Comment (LPCTSTR lpszFormat, ...)
{

	ASSERT(AfxIsValidString(lpszFormat, FALSE));

	va_list argList;
	va_start(argList, lpszFormat);
	strMessage += CFormat (lpszFormat, argList);
  strMessage += ENDLINE;
	va_end(argList);

}

void Warning (CMUDitem * item, LPCTSTR lpszFormat, ...)
{

	ASSERT(AfxIsValidString(lpszFormat, FALSE));

	va_list argList;
	va_start(argList, lpszFormat);
  if (item)
    {

    CString strType = item->Type ();
    if (!strType.IsEmpty ())
	    strType.SetAt (0, UPPER(strType[0])); // capitalise first character

    strMessage += "** ";
    strMessage += strType;
    strMessage += ": ";
    strMessage += item->Summary ();
    if (strlen (lpszFormat) > 0)
      strMessage += ": ";
    }

  strMessage += CFormat (lpszFormat, argList);
  strMessage += ENDLINE;
	va_end(argList);

  nErrors++;

}

#ifdef SPELL_CHECKER

int SpellCheckBlock (CMUDitem * item, 
                     CString strText,
                     CStringList & strBadWordsList)
  {
SSCE_S16 sid;
SSCE_S16 blkId;
SSCE_S16 resultMask;
unsigned char * p;
SSCE_CHAR  errWord [SSCE_MAX_WORD_SZ];
SSCE_CHAR  replacement [SSCE_MAX_WORD_SZ];

CString strBadWords;
CString strError;
int iLength = strText.GetLength ();
int iCount = 0;
POSITION pos = strBadWordsList.GetTailPosition ();

  // get session ID
  sid = SSCE_GetSid ();

  if (sid < 0)
    return 0;   // cannot open spell checker

  p = (unsigned char * ) strText.GetBuffer (iLength + 2);

  blkId = SSCE_OpenBlock (sid, p, strText.GetLength (), iLength + 1, 0);

  if (blkId < 0)
    {
    strText.ReleaseBuffer ();
    return 0;   // cannot open block
    }


  do
    {
    // check the next word
    resultMask = SSCE_CheckBlock
      (sid, blkId, errWord, SSCE_MAX_WORD_SZ, replacement, SSCE_MAX_WORD_SZ);

    if (resultMask < 0)
      break;    // oops! bail out

    if (resultMask & SSCE_END_OF_BLOCK_RSLT)
      break;

    if (resultMask != 0)
      {
      if (resultMask & SSCE_DOUBLED_WORD_RSLT)
        {
        strError = errWord;
        strError += " ";
        strError += errWord;   // double it up so they know what we are about
        }
      else
        strError = errWord;

      if (strBadWordsList.Find (strError) == NULL)
        {
        strBadWordsList.AddTail (strError);
        iCount++;
        }   // end of word not in list
      // now get next word
      SSCE_NextBlockWord(sid, blkId);
      }   // end of misspelling

    } while ((resultMask & SSCE_END_OF_BLOCK_RSLT) == 0);

  SSCE_CloseBlock (sid, blkId);
  strText.ReleaseBuffer ();

  // don't report ones which were already in the list
  if (pos)
    strBadWordsList.GetNext (pos);
  else
    pos = strBadWordsList.GetHeadPosition ();

  if (pos)
    {
    while (pos)
      {
      CString strWord = strBadWordsList.GetNext (pos);
      if (strBadWords.IsEmpty ())
        strBadWords = CFormat ("%i spelling error%s: ", 
                                PLURAL (iCount));
      else
        strBadWords += ", ";
      strBadWords += strWord;
      }  // end of building up list

    if (item)
      ::Warning (item, strBadWords);
    }  // end of at least one error


  return iCount;
  }   // end of  SpellCheckBlock

#endif // SPELL_CHECKER


void CAreaEditorDoc::AreaCheck(int & iTotalRooms,
                               int & iTotalMobs,
                               int & iTotalObjects,
                               int & iTotalExits,
                               int & iTotalPrograms) 
{
POSITION mobPos;
POSITION RoomPos;
POSITION ObjectPos;
POSITION pos;


BOOL bWarnVnumsOutOfRange = App.GetProfileInt  (sProfilePreferences, sProfileWarnVnums, 1);

	CWaitCursor wait;

// this scans the area looking for problems

  // the date
  CString strTime;
  CTime theTime;
  theTime = CTime::GetCurrentTime();
  strTime = theTime.Format ("%A, %B %d, %Y, %#I:%M %p");

  ::Comment ("Checking area %s on %s", 
          m_Area ? (LPCTSTR) m_Area->strAreaName : "(untitled)",
          (LPCTSTR) strTime);

  // count all programs

  // count mob programs
  for (mobPos = m_MobList.GetHeadPosition (); mobPos; )
    iTotalPrograms += m_MobList.GetNext (mobPos)->programlist.GetCount ();

  // count object programs
  for (ObjectPos = m_ObjectList.GetHeadPosition (); ObjectPos; )
    iTotalPrograms += m_ObjectList.GetNext (ObjectPos)->programlist.GetCount ();

  // count room programs
  for (RoomPos = m_RoomList.GetHeadPosition (); RoomPos; )
    iTotalPrograms += m_RoomList.GetNext (RoomPos)->programlist.GetCount ();

  if (m_Area)
    {
    ::Comment ("Author: %s", (LPCTSTR) m_Area->strAuthor);
    ::Comment ("Reset message: %s", (LPCTSTR) m_Area->strResetMsg);
    ::Comment ("Levels: Soft: %i to %i, Hard: %i to %i", 
              m_Area->low_soft_range,
              m_Area->hi_soft_range,
              m_Area->low_hard_range,
              m_Area->low_hard_range);
    ::Comment ("Repop frequency: %s", m_Area->reset_frequency > 0 
              ? (LPCTSTR) CFormat ("%i", m_Area->reset_frequency) : "default");
    ::Comment ("Mobile vnums %i to %i", m_Area->mob_low_vnum, m_Area->mob_hi_vnum);
    ::Comment ("Object vnums %i to %i", m_Area->obj_low_vnum, m_Area->obj_hi_vnum);
    ::Comment ("Room vnums %i to %i", m_Area->room_low_vnum, m_Area->room_hi_vnum);
    }

  ::Comment ("");

  // who cares if we can't check programs if we don't have any?
  if (iTotalPrograms)
    {
    if (App.m_CommandList.IsEmpty ())
      ::Comment ("** WARNING - Commands file (commands.dat) not loaded.");
    
    if (App.m_SocialList.IsEmpty ())
      ::Comment ("** WARNING - Socials file (socials.dat) not loaded.");

    if (App.m_SkillList.IsEmpty ())
      ::Comment ("** WARNING - Skills file (skills.dat) not loaded.");

    if (App.m_CommandList.IsEmpty () 
     || App.m_SocialList.IsEmpty ()
     || App.m_SkillList.IsEmpty ())
      {
      ::Comment ("** Cannot check MUD program syntax.");
      ::Comment ("");
      }
    }

  // now look for program cross-references

  // process each mob

  CMobile * mob;
  CMUDObject * object;
  CRoom * room;
  CReset * reset;
  CExit * exit;
  CShop * shop;
  CRepair * repair;

  CMobile * refmob;
  CMUDObject * refobject;
  CRoom * refroom;

  CMUDprogram * program;
  CString strMessage;
  int vnum;
  int iExits;
  int OldnErrors = 0;
  int iPrograms;
  int iKeys = 0;
  int iHighLevel = 0;
  int iLowLevel = INT_MAX;
  int iSpellErrors = 0;


  int * pHPs = NULL;   // array of Hit points at a particular level
  int * pLowHPs = NULL;   // array of lowest Hit points at a particular level
  int * pHighHPs = NULL;   // array of highest Hit points at a particular level
  int * pCount = NULL; // array of counts of mob per level
  int * pAggressiveCount = NULL; // array of counts of mob per level

  long iMilestone = 0;

  long iItems =  m_MobList.GetCount ()
                   + m_ObjectList.GetCount ()
                   + m_RoomList.GetCount ()
                   + m_ResetList.GetCount ()
                   + m_ShopList.GetCount ()
                   + m_RepairList.GetCount ()
                   + m_HelpList.GetCount ();
  
  Frame.CreateProgressBar ("Checking area", iItems);

// check each mob's programs

  ::Comment ("Checking mobs");
  ::Comment ("");
  iPrograms = 0;
  OldnErrors = nErrors;

  
// find highest and lowest mob level

  for (mobPos = m_MobList.GetHeadPosition (); mobPos; )
    {
    mob = m_MobList.GetNext (mobPos);

    if (mob->level >= 0 && mob->level <= 1000)
      {
      if (mob->level > iHighLevel)
        iHighLevel = mob->level;

      if (mob->level < iLowLevel)
        iLowLevel = mob->level;
      }

    }   // end of checking each mob


  if (!m_MobList.IsEmpty ())
    {
    pHPs = new int [iHighLevel + 1];
    pLowHPs = new int [iHighLevel + 1];
    pHighHPs = new int [iHighLevel + 1];
    pCount = new int [iHighLevel + 1];
    pAggressiveCount = new int [iHighLevel + 1];

    for (int i = 0; i <= iHighLevel; i++)
      {
      pHPs [i] = 0;
      pLowHPs [i] = INT_MAX;
      pHighHPs [i] = 0;
      pCount [i] = 0;
      pAggressiveCount [i] = 0;
      }
    }

  iSpellErrors = 0;
  for (mobPos = m_MobList.GetHeadPosition (); mobPos; )
    {
    mob = m_MobList.GetNext (mobPos);

    if (iMilestone++ % 32 == 0)
      Frame.UpdateProgressBar (iMilestone);

    // ===================================================================
    // do various checks against config file

    // check vnum
    if (bWarnVnumsOutOfRange)
      if (mob->vnum < 1 || mob->vnum > iMaxVnum)
        ::Warning (mob, "Mob vnum of %i outside recommended range of 1 to %i",
                 mob->vnum, iMaxVnum);

    // check level
    if (mob->level < 1 || mob->level > iMaxLevel)
      ::Warning (mob, "Mob level of %i outside recommended range of 1 to %i",
               mob->level, iMaxLevel);

    // armour class
    if (mob->ac < iMinAC || mob->ac > iMaxAC)
      ::Warning (mob, "Mob armour class of %i outside recommended range of %i to %i",
               mob->ac, iMinAC, iMaxAC);

    // damnodice
    if (mob->damnodice < 0 || mob->damnodice > iMaxdamnodice)
      ::Warning (mob, "Mob damnodice of %i outside recommended range of 0 to %i",
               mob->damnodice, iMaxdamnodice);

    // damplus
    if (mob->damplus < 0 || mob->damplus > iMaxdamplus)
      ::Warning (mob, "Mob damplus of %i outside recommended range of 0 to %i",
               mob->damplus, iMaxdamplus);

    // damroll
    if (mob->damroll < 0 || mob->damroll > iMaxdamroll)
      ::Warning (mob, "Mob damroll of %i outside recommended range of 0 to %i",
               mob->damroll, iMaxdamroll);

    // damsizedice
    if (mob->damsizedice < 0 || mob->damsizedice > iMaxdamsizedice)
      ::Warning (mob, "Mob damsizedice of %i outside recommended range of 0 to %i",
               mob->damsizedice, iMaxdamsizedice);

    // hitnodice
    if (mob->hitnodice < 0 || mob->hitnodice > iMaxhitnodice)
      ::Warning (mob, "Mob hitnodice of %i outside recommended range of 0 to %i",
               mob->hitnodice, iMaxhitnodice);

    // hitplus
    if (mob->hitplus < 0 || mob->hitplus > iMaxhitplus)
      ::Warning (mob, "Mob hitplus of %i outside recommended range of 0 to %i",
               mob->hitplus, iMaxhitplus);

    // hitroll
    if (mob->hitroll < 0 || mob->hitroll > iMaxhitroll)
      ::Warning (mob, "Mob hitroll of %i outside recommended range of 0 to %i",
               mob->hitroll, iMaxhitroll);

    // hitsizedice
    if (mob->hitsizedice < 0 || mob->hitsizedice > iMaxhitsizedice)
      ::Warning (mob, "Mob hitsizedice of %i outside recommended range of 0 to %i",
               mob->hitsizedice, iMaxhitsizedice);

    // numattacks
    if (mob->numattacks < 0 || mob->numattacks > iMaxNumattacks)
      ::Warning (mob, "Mob numattacks of %i outside recommended range of 0 to %i",
               mob->numattacks, iMaxNumattacks);

    // saving_poison_death
    if (mob->saving_poison_death < iMinSavingthrow || mob->saving_poison_death > iMaxSavingthrow)
      ::Warning (mob, "Mob saving_poison_death of %i outside recommended range of %i to %i",
               mob->saving_poison_death, iMinSavingthrow, iMaxSavingthrow);

    // saving_wand
    if (mob->saving_wand < iMinSavingthrow || mob->saving_wand > iMaxSavingthrow)
      ::Warning (mob, "Mob saving_wand of %i outside recommended range of %i to %i",
               mob->saving_wand, iMinSavingthrow, iMaxSavingthrow);

    // saving_para_petri
    if (mob->saving_para_petri < iMinSavingthrow || mob->saving_para_petri > iMaxSavingthrow)
      ::Warning (mob, "Mob saving_para_petri of %i outside recommended range of %i to %i",
               mob->saving_para_petri, iMinSavingthrow, iMaxSavingthrow);

    // saving_breath
    if (mob->saving_breath < iMinSavingthrow || mob->saving_breath > iMaxSavingthrow)
      ::Warning (mob, "Mob saving_breath of %i outside recommended range of %i to %i",
               mob->saving_breath, iMinSavingthrow, iMaxSavingthrow);

    // saving_spell_staff
    if (mob->saving_spell_staff < iMinSavingthrow || mob->saving_spell_staff > iMaxSavingthrow)
      ::Warning (mob, "Mob saving_spell_staff of %i outside recommended range of %i to %i",
               mob->saving_spell_staff, iMinSavingthrow, iMaxSavingthrow);

    // alignment
    if (mob->alignment < iMinAlignment || mob->alignment > iMaxAlignment)
      ::Warning (mob, "Mob alignment of %i outside recommended range of %i to %i",
               mob->alignment, iMinAlignment, iMaxAlignment);

    // ===================================================================

    // check HPs, and lowest and highest
    if (mob->level >= 0 && mob->level <= 1000)
      {
      int HP = (mob->hitnodice * mob->hitsizedice) + mob->hitplus;
      pHPs [mob->level] += HP;
      pCount [mob->level] ++;
      if (IS_SET (mob->act, ACT_AGGRESSIVE))
        pAggressiveCount [mob->level] ++;
      if (HP > pHighHPs [mob->level])
        pHighHPs [mob->level] = HP;
      if (HP < pLowHPs [mob->level])
        pLowHPs [mob->level] = HP;
      }
    else
      ::Warning (mob, "Mobile has unexpected level of %i", mob->level);

    // ===================================================================

    // spell check

#ifdef SPELL_CHECKER

    if (App.m_bSpellCheckOK)    // provided loaded DLL and enabled it
      {
      CStringList strBadWordsList;

      // if the name of the item is an acceptable mis-spelling find it out now
      if (CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_ACCEPT_NAME))
         SpellCheckBlock (NULL, mob->player_name, strBadWordsList);

      if (CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_MOB_NAME))
        iSpellErrors += SpellCheckBlock (mob, mob->player_name, strBadWordsList);
      if (CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_MOB_SHORT))
        iSpellErrors += SpellCheckBlock (mob, mob->short_descr, strBadWordsList);
      if (CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_MOB_LONG))
        iSpellErrors += SpellCheckBlock (mob, mob->long_descr, strBadWordsList);
      if (CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_MOB_DESC))
        iSpellErrors += SpellCheckBlock (mob, mob->description, strBadWordsList);
      }

#endif // SPELL_CHECKER

    // ===================================================================

    // check programs
    for (POSITION progPos = mob->programlist.GetHeadPosition (); progPos; )
      {
      POSITION pos;

      program = mob->programlist.GetNext (progPos);
      iPrograms++;

      // if syntax error, add to warning list
      if (CheckCommandSyntax (program->comlist, 
                              strMessage,
                              program->xref_rooms,
                              program->xref_objects,
                              program->xref_mobs))
         ::Warning (mob, strMessage);

      // see if all cross-refenced mobs exist
      for (pos = program->xref_mobs.GetHeadPosition (); pos; )
        {
        vnum = program->xref_mobs.GetNext (pos);
        if ((refmob = FindMob (vnum)) == NULL)
          ::Warning (mob, 
            CFormat ("<%s> mobile %i not in area", 
                     (LPCTSTR) program->Summary (), vnum));
        else
          refmob->m_bReferenced = true;

        } // end of checking each mob reference

      // see if all cross-refenced objects exist
      for (pos = program->xref_objects.GetHeadPosition (); pos; )
        {
        vnum = program->xref_objects.GetNext (pos);
        if ((refobject = FindObj (vnum)) == NULL)
          ::Warning (mob, 
            CFormat ("<%s> object %i not in area", 
                     (LPCTSTR) program->Summary (), vnum));
        else
          refobject->m_bReferenced = true;
        } // end of checking each object reference

      // see if all cross-refenced rooms exist
      for (pos = program->xref_rooms.GetHeadPosition (); pos; )
        {
        vnum = program->xref_rooms.GetNext (pos);
        if ((refroom = FindRoom (vnum)) == NULL)
          ::Warning (mob, 
            CFormat ("<%s> room %i not in area", 
                     (LPCTSTR) program->Summary (), vnum));
        else
          refroom->m_bReferenced = true;
        } // end of checking each room reference

      }   // end of each program
    
    } // end of each mob

  if (nErrors - OldnErrors)
    ::Comment ("");
  ::Comment ("%i mob%s", PLURAL (m_MobList.GetCount()));
  ::Comment ("%i mob program%s", PLURAL (iPrograms));
  ::Comment ("%i spelling error%s", PLURAL (iSpellErrors));

  iTotalMobs += m_MobList.GetCount();
  iTotalPrograms += iPrograms;

  ::Comment ("");
  if (m_MobList.GetCount())
    {
    ::Comment ("Lowest  level mob was level %i", iLowLevel);
    ::Comment ("Highest level mob was level %i", iHighLevel);

    ::Comment ("");

    for (int i = 0; i <= iHighLevel; i++)
      if (pCount [i])
        {
        CString strAggressive = "";
        CString strHP;

        // let's say (aggressive), (all aggressive), or (n aggressive) depending
        if (pAggressiveCount [i] && (pCount [i] == 1))    // the only one is aggressive
          strAggressive = " (aggressive)";
        else if (pAggressiveCount [i] && (pAggressiveCount [i] == pCount [i]))
          strAggressive = " (all aggressive)";    // they are ALL bloody aggressive
        else if (pAggressiveCount [i])  // there are aggressive ones, and it isn't the only one
          strAggressive.Format (" (%i aggressive)", pAggressiveCount [i]);

        // don't bother giving averages, minima and maxima if only one
        if (pCount [i] == 1)
          strHP.Format ("HP = %i", pHPs [i]);
        else
          strHP.Format ("lowest HP = %i, average HP = %i, highest HP = %i",
                  pLowHPs [i],
                  pHPs [i] / pCount [i],
                  pHighHPs [i]);

        ::Comment ("There %s %i level %i mob%s%s, %s",
                  pCount [i] == 1 ? "is" : "are",
                  pCount [i],
                  i,
                  pCount [i] == 1 ? "" : "s",
                  (LPCTSTR) strAggressive,
                  (LPCTSTR) strHP
                  );
        } // end of having a mob at this level

    }

  ::Comment ("");
  if (nErrors - OldnErrors)
    ::Comment ("** %i problem%s in mobs", PLURAL (nErrors - OldnErrors));
  else
    ::Comment ("No problems in mobs");

  // process each room

  ::Comment ("");
  ::Comment ("Checking rooms");
  ::Comment ("");
  iPrograms = 0;
  iExits = 0;
  OldnErrors = nErrors;

  iSpellErrors = 0;
  for (RoomPos = m_RoomList.GetHeadPosition (); RoomPos; )
    {
    room = m_RoomList.GetNext (RoomPos);

    if (iMilestone++ % 32 == 0)
      Frame.UpdateProgressBar (iMilestone);

    if (bWarnVnumsOutOfRange)
      if (room->vnum < 1 || room->vnum > iMaxVnum)
        ::Warning (room, "Room vnum of %i outside recommended range of 1 to %i",
                 room->vnum, iMaxVnum);

    for (POSITION progPos = room->programlist.GetHeadPosition (); progPos; )
      {
      POSITION pos;

      program = room->programlist.GetNext (progPos);
      iPrograms++;

      // if syntax error, add to warning list
      if (CheckCommandSyntax (program->comlist, 
                              strMessage,
                              program->xref_rooms,
                              program->xref_objects,
                              program->xref_mobs))
         ::Warning (room, strMessage);

      // see if all cross-refenced mobs exist
      for (pos = program->xref_mobs.GetHeadPosition (); pos; )
        {
        vnum = program->xref_mobs.GetNext (pos);
        if ((refmob = FindMob (vnum)) == NULL)
          ::Warning (room, 
            CFormat ("<%s> mobile %i not in area", 
                     (LPCTSTR) program->Summary (), vnum));
        else
          refmob->m_bReferenced = true;
        } // end of checking each mob reference

      // see if all cross-refenced objects exist
      for (pos = program->xref_objects.GetHeadPosition (); pos; )
        {
        vnum = program->xref_objects.GetNext (pos);
        if ((refobject = FindObj (vnum)) == NULL)
          ::Warning (room, 
            CFormat ("<%s> object %i not in area", 
                     (LPCTSTR) program->Summary (), vnum));
        else
          refobject->m_bReferenced = true;
        } // end of checking each object reference

      // see if all cross-refenced rooms exist
      for (pos = program->xref_rooms.GetHeadPosition (); pos; )
        {
        vnum = program->xref_rooms.GetNext (pos);
        if ((refroom = FindRoom (vnum)) == NULL)
          ::Warning (room, 
            CFormat ("<%s> room %i not in area", 
                     (LPCTSTR) program->Summary (), vnum));
        else
          refroom->m_bReferenced = true;
        } // end of checking each room reference

      }   // end of each program
    
    // check all exits

    for (pos = room->exitlist.GetHeadPosition (); pos; )
      {
      exit = room->exitlist.GetNext (pos);
      iExits++;

      if (exit->key > 0)    // NB - maybe should check for -1, but some seem to be zero
        {
        iKeys++;
        if ((refobject = FindObj (exit->key)) == NULL)
          ::Warning (exit, 
            CFormat ("Key (object %i) to exit not in area", 
                      exit->key));
        else
          refobject->m_bReferenced = true;
        }

      if (exit->vnum != -1)   // a vnum of -1 means an exit that doesn't lead anywhere
        if ((refroom = FindRoom (exit->vnum)) == 0)
          ::Warning (exit, CFormat ("from room #%i", room->vnum));   // exit message will say "not in area"
        else
          refroom->m_bReferenced = true;
      }   // end of processing each exit

    if (room->tele_vnum > 0)
      if ((refroom = FindRoom (room->tele_vnum)) == NULL)
        ::Warning (room, 
          CFormat ("Teleport room %i not in area", 
                    room->tele_vnum));
      else
        refroom->m_bReferenced = true;

    // ===================================================================

    // spell check

#ifdef SPELL_CHECKER

    if (App.m_bSpellCheckOK)    // provided loaded DLL and enabled it
      {
      CStringList strBadWordsList;

      if (CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_ROOM_NAME))
        iSpellErrors += SpellCheckBlock (room, room->name, strBadWordsList);
      if (CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_ROOM_DESC))
        iSpellErrors += SpellCheckBlock (room, room->description, strBadWordsList);

      // now do the extra descriptions
      for (POSITION extraPos = room->extralist.GetHeadPosition (); extraPos; )
        {
        CExtraDescription * extra = room->extralist.GetNext (extraPos);
        if (CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_EXTRA_DESC))
          iSpellErrors += SpellCheckBlock (room, extra->description, strBadWordsList);
        }

      }   // end of spell check OK

#endif // SPELL_CHECKER

    } // end of each room

  if (nErrors - OldnErrors)
    ::Comment ("");

  ::Comment ("%i room%s", PLURAL (m_RoomList.GetCount()));
  ::Comment ("%i room program%s", PLURAL (iPrograms));
  ::Comment ("%i room exit%s", PLURAL (iExits));
  ::Comment ("%i spelling error%s", PLURAL (iSpellErrors));

  iTotalRooms += m_RoomList.GetCount();
  iTotalPrograms += iPrograms;
  iTotalExits += iExits;

  if (iKeys)
    ::Comment ("%i exit%s need%s a key", 
             PLURAL (iKeys),
             iKeys == 1 ? "s" : "");
  if (nErrors - OldnErrors)
    ::Comment ("** %i problem%s in rooms", PLURAL (nErrors - OldnErrors));
  else
    ::Comment ("No problems in rooms");

  // process each object

  ::Comment ("");
  ::Comment ("Checking objects");
  ::Comment ("");
  iPrograms = 0;
  OldnErrors = nErrors;
  iSpellErrors = 0;

  for (ObjectPos = m_ObjectList.GetHeadPosition (); ObjectPos; )
    {
    object = m_ObjectList.GetNext (ObjectPos);

    if (iMilestone++ % 32 == 0)
      Frame.UpdateProgressBar (iMilestone);

    if (bWarnVnumsOutOfRange)
      if (object->vnum < 1 || object->vnum > iMaxVnum)
        ::Warning (object, "Object vnum of %i outside recommended range of 1 to %i",
                 object->vnum, iMaxVnum);

    for (POSITION progPos = object->programlist.GetHeadPosition (); progPos; )
      {
      POSITION pos;

      program = object->programlist.GetNext (progPos);
      iPrograms++;

      // if syntax error, add to warning list
      if (CheckCommandSyntax (program->comlist, 
                              strMessage,
                              program->xref_rooms,
                              program->xref_objects,
                              program->xref_mobs))
         ::Warning (object, strMessage);

      // see if all cross-refenced mobs exist
      for (pos = program->xref_mobs.GetHeadPosition (); pos; )
        {
        vnum = program->xref_mobs.GetNext (pos);
        if ((refmob = FindMob (vnum)) == NULL)
          ::Warning (object, 
            CFormat ("<%s> mobile %i not in area", 
                     (LPCTSTR) program->Summary (), vnum));
        else
          refmob->m_bReferenced = true;
        } // end of checking each mob reference

      // see if all cross-refenced objects exist
      for (pos = program->xref_objects.GetHeadPosition (); pos; )
        {
        vnum = program->xref_objects.GetNext (pos);
        if ((refobject = FindObj (vnum)) == NULL)
          ::Warning (object, 
            CFormat ("<%s> object %i not in area", 
                     (LPCTSTR) program->Summary (), vnum));
        else
          refobject->m_bReferenced = true;
        } // end of checking each object reference

      // see if all cross-refenced rooms exist
      for (pos = program->xref_rooms.GetHeadPosition (); pos; )
        {
        vnum = program->xref_rooms.GetNext (pos);
        if ((refroom = FindRoom (vnum)) == NULL)
          ::Warning (object, 
            CFormat ("<%s> room %i not in area", 
                     (LPCTSTR) program->Summary (), vnum));
        else
          refroom->m_bReferenced = true;
        } // end of checking each room reference

      }   // end of each program

    // ===================================================================

    // spell check
#ifdef SPELL_CHECKER

    if (App.m_bSpellCheckOK)    // provided loaded DLL and enabled it
      {
      CStringList strBadWordsList;

      // if the name of the item is an acceptable mis-spelling find it out now
      if (CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_ACCEPT_NAME))
         SpellCheckBlock (NULL, object->name, strBadWordsList);

      if (CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_OBJECT_NAME))
        iSpellErrors += SpellCheckBlock (object, object->name, strBadWordsList);
      if (CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_OBJECT_SHORT))
        iSpellErrors += SpellCheckBlock (object, object->short_descr, strBadWordsList);
      if (CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_OBJECT_ACTIONDESC))
        iSpellErrors += SpellCheckBlock (object, object->action_desc, strBadWordsList);
      if (CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_OBJECT_LONG))
        iSpellErrors += SpellCheckBlock (object, object->description, strBadWordsList);

      // now do the extra descriptions
      for (POSITION extraPos = object->extralist.GetHeadPosition (); extraPos; )
        {
        CExtraDescription * extra = object->extralist.GetNext (extraPos);
        if (CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_EXTRA_DESC))
          iSpellErrors += SpellCheckBlock (object, extra->description, strBadWordsList);
        }

      }     // end of spellcheck wanted
    
#endif // SPELL_CHECKER

    } // end of each object

  if (nErrors - OldnErrors)
    ::Comment ("");

  ::Comment ("%i object%s", PLURAL (m_ObjectList.GetCount()));
  ::Comment ("%i object program%s", PLURAL (iPrograms));
  ::Comment ("%i spelling error%s", PLURAL (iSpellErrors));

  iTotalObjects += m_ObjectList.GetCount();
  iTotalPrograms += iPrograms;

  if (nErrors - OldnErrors)
    ::Comment ("** %i problem%s in objects", PLURAL (nErrors - OldnErrors));
  else
    ::Comment ("No problems in objects");

    // process each reset

  ::Comment ("");
  ::Comment ("Checking resets");
  ::Comment ("");
  OldnErrors = nErrors;

  for (pos = m_ResetList.GetHeadPosition (); pos; )
    {
    reset = m_ResetList.GetNext (pos);

    if (iMilestone++ % 32 == 0)
      Frame.UpdateProgressBar (iMilestone);

    switch (reset->command)
	    {
	    default:
          ::Warning (reset, "Bad command '%c'.",  reset->command);
	        return;

	    case 'M':
	        if ((refmob = FindMob ( reset->arg1 )) == NULL)
		        ::Warning (reset, "");
          else
            refmob->m_bReferenced = true;
	        if ((refroom = FindRoom ( reset->arg3 )) == NULL)
		        ::Warning (reset, "");
          else
            refroom->m_bReferenced = true;
	        break;

	    case 'O':
	        if ((refobject = FindObj(reset->arg1)) == NULL)
		        ::Warning (reset, "");
          else
            refobject->m_bReferenced = true;
	        if ((refroom = FindRoom (reset->arg3)) == NULL)
		        ::Warning (reset, "");
          else
            refroom->m_bReferenced = true;

	        break;

	    case 'P':
	        if ((refobject = FindObj(reset->arg1)) == NULL)
		        ::Warning (reset, "");
          else
            refobject->m_bReferenced = true;
	        if (reset->arg3 > 0 )
		        if ((refobject = FindObj(reset->arg3)) == NULL)
		            ::Warning (reset, "");
          else
            refobject->m_bReferenced = true;
	        break;

	    case 'G':
	    case 'E':
	        if ((refobject =  FindObj(reset->arg1)) == NULL)
		        ::Warning (reset, "");
          else
            refobject->m_bReferenced = true;
	        break;

	    case 'T':
	        break;

	    case 'H':
	        if ( reset->arg1 > 0 )
		        if ((refobject =  FindObj(reset->arg1)) == NULL)
		            ::Warning (reset, "");
          else
            refobject->m_bReferenced = true;
	        break;

	    case 'D':
	        room = FindRoom ( reset->arg1 );
	        if ( !room )
	        {
		       ::Warning (reset, "");
		      break;
	        }
          else
            room->m_bReferenced = true;

	        if ( reset->arg2 < 0
	        ||   reset->arg2 > MAX_DIR+1
	        || ( exit = get_exit(room, reset->arg2)) == NULL
	        || !IS_SET( exit->exit_info, EX_ISDOOR ) )
	        {
		       ::Warning (reset,  "Exit %i not door.",
			                   reset->arg2 );
	        }

	        if ( reset->arg3 < 0 || reset->arg3 > 2 )
	        {
		      ::Warning (reset,  "Bad 'locks': %i.",
			     reset->arg3 );
	        }
	        break;

	    case 'R':
	        room = FindRoom ( reset->arg1 );
	        if ( !room)
            ::Warning (reset, "");
          else
            room->m_bReferenced = true;

	        if ( reset->arg2 < 0 || reset->arg2 > 6 )
	        {
		      ::Warning (reset,  "Bad exit %i.",
			     reset->arg2 );
		      break;
	        }

	        break;
	    }   // end of switch
  }   // end of processing each reset

  if (nErrors - OldnErrors)
    ::Comment ("");

  ::Comment ("%i reset%s", PLURAL (m_ResetList.GetCount()));

  if (nErrors - OldnErrors)
    ::Comment ("** %i problem%s in resets", PLURAL (nErrors - OldnErrors));
  else
    ::Comment ("No problems in resets");

// check each shop

  if (!m_ShopList.IsEmpty ())
    {
    ::Comment ("");
    ::Comment ("Checking shops");
    ::Comment ("");
    OldnErrors = nErrors;

    for (pos = m_ShopList.GetHeadPosition (); pos; )
      {
      shop = m_ShopList.GetNext (pos);
      if (iMilestone++ % 32 == 0)
        Frame.UpdateProgressBar (iMilestone);

      // check keeper in area
 	    mob		= FindMob ( shop->keeper );
      if (!mob)
		    ::Warning(shop, "Mobile %i is not in area.", shop->keeper );

      }   // end of processing each shop


    if (nErrors - OldnErrors)
      ::Comment ("");
    
    ::Comment ("%i shop%s", PLURAL (m_ShopList.GetCount()));
  
    if (nErrors - OldnErrors)
      ::Comment ("** %i problem%s in shops", PLURAL (nErrors - OldnErrors));
    else
      ::Comment ("No problems in shops");
    }

// check all repairs

  if (!m_RepairList.IsEmpty ())
    {
    ::Comment ("");
    ::Comment ("Checking repairs");
    ::Comment ("");
    OldnErrors = nErrors;

    // cycle through all repairs

    for (pos = m_RepairList.GetHeadPosition (); pos; )
      {
      repair = m_RepairList.GetNext (pos);
      if (iMilestone++ % 32 == 0)
        Frame.UpdateProgressBar (iMilestone);

      // check keeper in area
	    mob		= FindMob ( repair->keeper );
      if (!mob)
		    ::Warning(repair, "Mobile %i is not in area.", repair->keeper );

      }   // end of processing each repair

      if (nErrors - OldnErrors)
        ::Comment ("");

      ::Comment ("%i repair%s", PLURAL (m_RepairList.GetCount()));

      if (nErrors - OldnErrors)
        ::Comment ("** %i problem%s in repairs", PLURAL (nErrors - OldnErrors));
      else
        ::Comment ("No problems in repairs");
      }


// check each help

#ifdef SPELL_CHECKER

  if (App.m_bSpellCheckOK && 
      CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_HELP_TEXT))
    {
    iSpellErrors = 0;
    CStringList strBadWordsList;

    if (!m_HelpList.IsEmpty ())
      {
      ::Comment ("");
      ::Comment ("Checking helps");
      ::Comment ("");
      OldnErrors = nErrors;

      for (pos = m_HelpList.GetHeadPosition (); pos; )
        {
        CHelp * help = m_HelpList.GetNext (pos);
        if (iMilestone++ % 32 == 0)
          Frame.UpdateProgressBar (iMilestone);


        iSpellErrors += SpellCheckBlock (help, help->text, strBadWordsList);

        }   // end of processing each help


      if (nErrors - OldnErrors)
        ::Comment ("");
    
      ::Comment ("%i help%s", PLURAL (m_HelpList.GetCount()));
      ::Comment ("%i spelling error%s", PLURAL (iSpellErrors));
      
      if (nErrors - OldnErrors)
        ::Comment ("** %i problem%s in helps", PLURAL (nErrors - OldnErrors));
      else
        ::Comment ("No problems in helps");
      }   // end of having helps
    } // end of spell check on help wanted

#endif // SPELL_CHECKER

  // delete HP and count arrays

  delete [] pHPs;
  delete [] pLowHPs;
  delete [] pHighHPs;
  delete [] pCount;
  delete [] pAggressiveCount;

  Frame.RemoveProgressBar ();

	
}

void CAreaEditorDoc::CrossReferenceCheck() 
  {
POSITION mobPos;
POSITION RoomPos;
POSITION ObjectPos;

  CMobile * mob;
  CMUDObject * object;
  CRoom * room;

  for (mobPos = m_MobList.GetHeadPosition (); mobPos; )
    if (!(mob = m_MobList.GetNext (mobPos))->m_bReferenced)
      ::Warning (mob, "Not used.");

  for (RoomPos = m_RoomList.GetHeadPosition (); RoomPos; )
    if (!(room = m_RoomList.GetNext (RoomPos))->m_bReferenced)
      ::Warning (room, "Not used.");

  for (ObjectPos = m_ObjectList.GetHeadPosition (); ObjectPos; )
    if (!(object = m_ObjectList.GetNext (ObjectPos))->m_bReferenced)
      ::Warning (object, "Not used.");
  }



void CheckAreas (CAreaEditorDoc * pDoc)
  {
POSITION mobPos;
POSITION RoomPos;
POSITION ObjectPos;
POSITION commandPos;
POSITION socialPos;
POSITION skillPos;

CCommand * command;
CSocial * social;
CSkill * skill;
CProgressDlg * pProgressDlg = NULL;
int iCount = 0,
    iTotal = 0;

int OldnErrors = 0;

int iTotalRooms = 0;
int iTotalMobs = 0;
int iTotalObjects = 0;
int iTotalExits = 0;
int iTotalPrograms = 0;

  strMessage.Empty ();
  nErrors = 0;
  iTotalPrograms = 0;

  // clear all "referenced" flags

  for (POSITION docPos = App.m_pDocTemplate->GetFirstDocPosition();
      docPos != NULL; )
    {

    CAreaEditorDoc * pDoc = (CAreaEditorDoc *) App.m_pDocTemplate->GetNextDoc(docPos);

    for (mobPos = pDoc->m_MobList.GetHeadPosition (); mobPos; )
      pDoc->m_MobList.GetNext (mobPos)->m_bReferenced = false;

    for (RoomPos = pDoc->m_RoomList.GetHeadPosition (); RoomPos; )
      pDoc->m_RoomList.GetNext (RoomPos)->m_bReferenced = false;

    for (ObjectPos = pDoc->m_ObjectList.GetHeadPosition (); ObjectPos; )
      pDoc->m_ObjectList.GetNext (ObjectPos)->m_bReferenced = false;

    } // end of doing each document


  // clear all program reference counts

  for (commandPos = App.m_CommandList.GetHeadPosition (); commandPos; )
    App.m_CommandList.GetNext (commandPos)->iReferenced = 0;

  for (socialPos = App.m_SocialList.GetHeadPosition (); socialPos; )
    App.m_SocialList.GetNext (socialPos)->iReferenced = 0;

  for (skillPos = App.m_SkillList.GetHeadPosition (); skillPos; )
    App.m_SkillList.GetNext (skillPos)->iReferenced = 0;


  if (pDoc)
    pDoc->AreaCheck (iTotalRooms,
                     iTotalMobs,
                     iTotalObjects,
                     iTotalExits,
                     iTotalPrograms);   // check this area
  else
    {
    POSITION docPos;

    // count number of documents
    for (docPos = App.m_pDocTemplate->GetFirstDocPosition();
        docPos != NULL; iTotal++)
      App.m_pDocTemplate->GetNextDoc(docPos);

    pProgressDlg = new CProgressDlg;
    pProgressDlg->Create ();
    pProgressDlg->SetRange (0, iTotal);     
    pProgressDlg->SetWindowText ("Checking areas ...");                              

    for (docPos = App.m_pDocTemplate->GetFirstDocPosition();
        docPos != NULL; )
      {

      CAreaEditorDoc * pDoc = (CAreaEditorDoc *) App.m_pDocTemplate->GetNextDoc(docPos);

      CString strName = pDoc->GetTitle ();

      if (pDoc->m_Area && !pDoc->m_Area->strAreaName.IsEmpty ())
        strName = pDoc->m_Area->strAreaName;

      ::Comment ("");
      ::Comment ("--------------- Area: %s ---------------", strName);
      ::Comment ("");

      pProgressDlg->SetStatus (CFormat ("Checking %s ...", (LPCTSTR) strName));    // area name
      pProgressDlg->SetPos (iCount++);   // which one

      pDoc->AreaCheck (iTotalRooms,
                       iTotalMobs,
                       iTotalObjects,
                       iTotalExits,
                       iTotalPrograms);   // check this area

      // if they cancel, exit read loop
      if (pProgressDlg->CheckCancelButton())
        {
        Comment (" (cancelled by user)");
        break;
        }

      }   // end of doing each document

    ::Comment ("");
    ::Comment ("------------- (end of areas) -------------");
    ::Comment ("");

    }   // end of wanting all areas

  ::Comment ("");
  ::Comment ("-------- Checking everything is used ---------");
  ::Comment ("");
  OldnErrors = nErrors;

// check that each room/mob/object is cross-referenced somewhere

  if (pProgressDlg)
    pProgressDlg->SetStatus ("Checking all cross-references"); // warn them of delay

  if (pDoc)
    pDoc->CrossReferenceCheck ();   // check this area
  else
    {
    Frame.CreateProgressBar ("Cross-referencing", iTotal);
    iCount = 0;

    for (POSITION docPos = App.m_pDocTemplate->GetFirstDocPosition();
        docPos != NULL; )
      {

      CAreaEditorDoc * pDoc = (CAreaEditorDoc *) App.m_pDocTemplate->GetNextDoc(docPos);

      CString strName = pDoc->GetTitle ();

      if (pDoc->m_Area && !pDoc->m_Area->strAreaName.IsEmpty ())
        strName = pDoc->m_Area->strAreaName;

      ::Comment ("");
      ::Comment ("--------------- Area: %s ---------------", strName);
      ::Comment ("");

      Frame.UpdateProgressBar (iCount++);

      pDoc->CrossReferenceCheck ();   // check this area

      }   // end of doing each document

    ::Comment ("");
    ::Comment ("------------- (end of areas) -------------");
    ::Comment ("");

    Frame.RemoveProgressBar ();

    }   // end of wanting all areas

  if (nErrors - OldnErrors)
    {
    ::Comment ("");
    ::Comment ("** %i item%s not used", PLURAL (nErrors - OldnErrors));
    if (iTotalPrograms)
      if (App.m_CommandList.IsEmpty () 
       || App.m_SocialList.IsEmpty ()
       || App.m_SkillList.IsEmpty ())
        ::Comment ("** Cross-referencing of items is likely to be inaccurate "
                 "because commands/socials/skills file(s) not loaded.");
    }
  else
    ::Comment ("No unused items found.");

  if (iTotalPrograms &&
      !App.m_CommandList.IsEmpty () &&
      !App.m_SocialList.IsEmpty () &&
      !App.m_SkillList.IsEmpty ())
    {
    ::Comment ("");
    ::Comment ("Commands used");
    ::Comment ("");
    iCount = 0;

    for (commandPos = App.m_CommandList.GetHeadPosition (); commandPos; )
      {
      command = App.m_CommandList.GetNext (commandPos);
      if (command->iReferenced)
        {
        ::Comment ("%s - %i time%s", 
                 (LPCTSTR) command->name,
                 PLURAL (command->iReferenced));
        iCount++;
        }
      }

    if (iCount)
      {
      ::Comment ("");
      ::Comment ("%i (different) MUD program command%s used", PLURAL (iCount));
      }
    else
      ::Comment ("No MUD program commands used.");

    ::Comment ("");
    ::Comment ("Socials used");
    ::Comment ("");
    iCount = 0;

    for (socialPos = App.m_SocialList.GetHeadPosition (); socialPos; )
      {
      social = App.m_SocialList.GetNext (socialPos);
      if (social->iReferenced)
        {
        ::Comment ("%s - %i time%s", 
                 (LPCTSTR) social->name,
                 PLURAL (social->iReferenced));
        iCount++;
        }
      }

    if (iCount)
      {
      ::Comment ("");
      ::Comment ("%i (different) social%s used", PLURAL (iCount));
      }
    else
      ::Comment ("No socials used in programs.");

    ::Comment ("");
    ::Comment ("Spells used in programs");
    ::Comment ("");
    iCount = 0;

    for (skillPos = App.m_SkillList.GetHeadPosition (); skillPos; )
      {
      skill = App.m_SkillList.GetNext (skillPos);
      if (skill->type == SKILL_SPELL && skill->iReferenced)
        {
        ::Comment ("%s - %i time%s", 
                 (LPCTSTR) skill->name,
                 PLURAL (skill->iReferenced));
        iCount++;
        }
      }

    if (iCount)
      {
      ::Comment ("");
      ::Comment ("%i (different) spell%s used", PLURAL (iCount));
      }
    else
      ::Comment ("No spells used in programs.");

    ::Comment ("");
    ::Comment ("Skills used in programs");
    ::Comment ("");
    iCount = 0;

    for (skillPos = App.m_SkillList.GetHeadPosition (); skillPos; )
      {
      skill = App.m_SkillList.GetNext (skillPos);
      if (skill->type == SKILL_SKILL && skill->iReferenced)
        {
        ::Comment ("%s - %i time%s", 
                 (LPCTSTR) skill->name,
                 PLURAL (skill->iReferenced));
        iCount++;
        }
      }

    if (iCount)
      {
      ::Comment ("");
      ::Comment ("%i (different) skill%s used", PLURAL (iCount));
      }
    else
      ::Comment ("No skills used in programs.");

    }   // end of commands/socials/skills loaded

  ::Comment ("");
  ::Comment ("%i total warning%s.", PLURAL (nErrors));

  ::Comment ("");
  ::Comment ("-- Totals --");
  ::Comment ("");

  ::Comment ("%i room%s", PLURAL (iTotalRooms));
  ::Comment ("%i mobile%s", PLURAL (iTotalMobs));
  ::Comment ("%i object%s", PLURAL (iTotalObjects));
  ::Comment ("%i exit%s", PLURAL (iTotalExits));
  ::Comment ("%i program%s", PLURAL (iTotalPrograms));

  ::Comment ("");
  ::Comment ("End of area check.");

  ::Comment ("");
  ::Comment ("Press <Esc> to close this window.");

  delete pProgressDlg;

  /*

  // MODAL way of doing it

  CAreaLoadingProblems dlg;

  dlg.m_strTitle = "Area check results";

  dlg.m_strErrors = strMessage;

  dlg.DoModal ();

  */

  // MODELESS dialog here

  CAreaLoadingProblems * dlg = new CAreaLoadingProblems;
  dlg->m_strTitle = "Area check results";   // set up dialog title
  dlg->m_strErrors = strMessage;            // what it says
  dlg->Create (ID_PROBLEMS_LOADING_AREA, NULL);  // create it
  dlg->ShowWindow(SW_SHOW);  // and, finally, show it - dialog will delete itself

  }



void CAreaEditorDoc::OnAreaCheck() 
  {
// first - update the current item

// find our splitter view

 for (POSITION pos = GetFirstViewPosition(); pos;)
   {
    CView* pView = GetNextView(pos);

    // if the splitter view, update current pane
    if (pView->IsKindOf(RUNTIME_CLASS(CAreaEditorView)))
      {
      pView = (CView *) ((CAreaEditorView *)pView)->m_pSplitterWindow->GetPane(0,1);
      if (!pView->UpdateData (TRUE))
        return;
      }
   }   


  CheckAreas (this);

  }
