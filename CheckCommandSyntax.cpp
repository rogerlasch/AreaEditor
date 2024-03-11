/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#include "stdafx.h"
#include "AreaEditor.h"
#include "AreaEditorDoc.h"

static char * pWord,
            * pWordStart;
static long nLineNumber;
static int nGrownAmount;
static int iWordLength; // length of most recent word

// amount by which we can grow the command buffer (by changing vnums)

#define GROWSIZE 1000

// ----------------------------- stuff for if checks ----------------------------

CStringList lDirections;

typedef enum { 
       eCondNone = 0, // no special processing
       eCondObject,   // object name
       eCondRoom,     // room name
       eCondMobile,    // mob name
       eCondDirection   // eg. n, s, e, w etc.
      } t_condition_type;

typedef struct 
  {
  char * sFunctionName;
  t_condition_type Arg;  // condition argument is object/room/mobile, eg. mobinroom (1234)
  t_condition_type Value;   // condition compares to object/room/mobile, eg. inroom ($n) == 1234
  bool bBoolean;    // true for boolean checks, eg. isnpc ($n) 
  } t_specialconditions;

const t_specialconditions SpecialConditions [] =
  {

    // no vnums
    { "rand", eCondNone, eCondNone, true  },
    { "otypehere" },
    { "otyperoom" },
    { "otypecarry" },
    { "otypewear" },
    { "otypeinv" },
    { "number" },
    { "name" },
    

    // room argument, eg. mobinroom (10300) > 4
    { "economy", eCondRoom }, 
    { "mobinroom", eCondRoom }, 

    // mob argument
    { "timeskilled", eCondMobile }, 
    { "ismobinvis", eCondMobile, eCondNone, true },
    { "mobinvislevel", eCondMobile },
    { "ispc", eCondMobile, eCondNone, true },
    { "isnpc", eCondMobile, eCondNone, true },
    { "ispkill", eCondMobile, eCondNone, true },
    { "isdevoted", eCondMobile, eCondNone, true },
    { "canpkill", eCondMobile, eCondNone, true },
    { "ismounted", eCondMobile, eCondNone, true },
    { "isgood", eCondMobile, eCondNone, true },
    { "isneutral", eCondMobile, eCondNone, true },
    { "isevil", eCondMobile, eCondNone, true },
    { "isfight", eCondMobile, eCondNone, true },
    { "isimmort", eCondMobile, eCondNone, true },
    { "ischarmed", eCondMobile, eCondNone, true },
    { "isfollow", eCondMobile, eCondNone, true },
    { "isaffected", eCondMobile },

    { "hitprcnt", eCondMobile }, 
    { "inroom", eCondMobile, eCondRoom }, 
    { "wasinroom", eCondMobile, eCondRoom }, 
    { "norecall", eCondMobile }, 
    { "sex", eCondMobile }, 
    { "position", eCondMobile }, 
    { "doingquest", eCondMobile }, 
    { "ishelled", eCondMobile }, 
    { "level", eCondMobile }, 
    { "goldamt", eCondMobile }, 
    { "class", eCondMobile }, 
    { "race", eCondMobile }, 
    { "clan", eCondMobile }, 
    { "deity", eCondMobile }, 
    { "guild", eCondMobile }, 
    { "clantype", eCondMobile }, 
    { "favor", eCondMobile }, 
    { "str", eCondMobile }, 
    { "wis", eCondMobile }, 
    { "int", eCondMobile }, 
    { "dex", eCondMobile }, 
    { "con", eCondMobile }, 
    { "cha", eCondMobile }, 
    { "lck", eCondMobile }, 

    // extensions for Brian Carter
    { "iswearing", eCondMobile, eCondObject }, 
    { "iscarrying", eCondMobile, eCondObject }, 

    // object argument, eg. objtype (1234) == 1
    { "ovnumhere", eCondObject }, 
    { "ovnumroom",  eCondObject }, 
    { "ovnumwear", eCondObject }, 
    { "ovnumcarry", eCondObject }, 
    { "ovnuminv", eCondObject }, 
    { "objtype", eCondObject }, 
    { "objval0", eCondObject }, 
    { "objval1", eCondObject }, 
    { "objval2", eCondObject }, 
    { "objval3", eCondObject }, 
    { "objval4", eCondObject }, 
    { "objval5", eCondObject }, 

// direction tests for Brian Carter

    { "isclosed", eCondDirection, eCondNone, true },
    { "islocked", eCondDirection, eCondNone, true },
    { "isopen", eCondDirection, eCondNone, true },
    { "isunlocked", eCondDirection, eCondNone, true },

  };

// ------------------------------ end of if check stuff ----------------------------

static bool skip_spaces (void)
  {
  for ( ; *pWord && isspace (*pWord); pWord++)
    if (*pWord == '\n')
      return true;    // end of line reached

  return false;
  } // end of skip_spaces

static void fread_to_eol (void)
  {
  for ( ; *pWord && *pWord != '\n'; pWord++)
    ;

  if (*pWord == '\n')
    pWord++;    // skip end-of-line

  nLineNumber++;    // count lines too
  } // end of fread_to_eol

static CString fread_word (bool bQuoted = true)
  {
CString strResult;

  iWordLength = 0;

  if (skip_spaces ())
    return "";        // stop at end of line
  
  if (*pWord == 0)    // stop at end of file
    return "";

  char cEnd = ' ';

  if (bQuoted)
    {
    cEnd = *pWord;    // remember as trailing delimiter
	  if (cEnd == '\'' || cEnd == '"')
		  pWord++;
    else
      cEnd = ' ';
    }

  pWordStart = pWord;   // remember where word starts

  // a non-alpha start sounds like 'Hi there
  if (!bQuoted && !isalnum (*pWord))
    {
    pWord++;
    iWordLength++;
    strResult = CString (pWordStart, 1);
    }
  else
    {
    for (; *pWord; pWord++, iWordLength++)
      if (cEnd == ' ' ? isspace(*pWord) : *pWord == cEnd )
        break;
    strResult = CString (pWordStart, pWord - pWordStart);
    if (*pWord)
      pWord++;    // skip trailing delimiter
    }

  return strResult;

  } // end of fread_word

static CString fread_condition_word (void)
  {

  iWordLength = 0;

  if (skip_spaces ())
    return "";        // stop at end of line
  
  if (*pWord == 0)    // stop at end of file
    return "";

  pWordStart = pWord;   // remember where word starts

  char c;

  for ( ; c = *pWord; pWord++, iWordLength++)
    {
    if (c == '(' || 
        c == ')' || 
        isspace (c))
      break;
    }

  // if we stopped on 1st character, it must have been a bracket
  if (pWord == pWordStart)
    {
    pWord++;
    iWordLength++;
    }

  CString strResult = CString (pWordStart, pWord - pWordStart);

  return strResult;

  } // end of fread_condition_word

static CString fread_condition_operator (void)
  {

  iWordLength = 0;

  if (skip_spaces ())
    return "";        // stop at end of line
  
  if (*pWord == 0)    // stop at end of file
    return "";

  pWordStart = pWord;   // remember where word starts

  char c;

  for ( ; c = *pWord; pWord++, iWordLength++)
    {
    if (isalnum (c) || isspace (c))
      break;
    }

  CString strResult = CString (pWordStart, pWord - pWordStart);

  return strResult;

  } // end of fread_condition_operator

static void FixProgramVnum (const int vnum, 
                           const int * pOldVnums, 
                           const int * pNewVnums,
                           const int iVnumCount)
  {
  CString strNewVnum;

  int newvnum = vnum;

  // do the vnum lookup and see if we get a different one

  FixupVnum (newvnum, pOldVnums, pNewVnums, iVnumCount);

  // no change, don't do anything more
  if (newvnum == vnum)
    return;

  int iOldLength = iWordLength;  // how long the number *was*, excluding delimiter
  strNewVnum.Format ("%i", newvnum);        // new number
  int iNewLength = strNewVnum.GetLength (); // how long it is
  int iDifference = iNewLength - iOldLength;// length difference  

  // count amount we grow
  nGrownAmount += iDifference;

  if (nGrownAmount > GROWSIZE)
    ThrowErrorException ("Insufficient internal buffer space to renumber program vnums");

  // if necessary, shuffle rest of buffer along to allow for new vnum length
  if (iDifference && strlen (pWordStart + iOldLength))
    {
    memmove (pWordStart + iNewLength, 
             pWordStart + iOldLength, 
             strlen (pWordStart + iOldLength) + 1);  // add 1 to take null with us
    pWord += iDifference;    // adjust word pointer for *next* word we process
    }

  // move new vnum into position
  memcpy (pWordStart, (const char *) strNewVnum, strNewVnum.GetLength ());

  } // end of FixProgramVnum


static void HandleCondition (t_prenumber pRenumberStuff)
  {

int vnum = 0;
int i;
const t_specialconditions * pCondition = NULL;

char * pWordOrig = pWord;   // save word pointer

  // get the condition name
CString strCondition = fread_condition_word ();

  strCondition.TrimLeft ();
  strCondition.TrimRight ();
  strCondition.MakeLower ();

  // search table for if checks that match this one
  for (i = 0; i < NUMITEMS (SpecialConditions); i++)
    if (strCondition == SpecialConditions [i].sFunctionName)
      pCondition = &SpecialConditions [i];

  if (!pCondition)
    ThrowErrorException ("Unknown IF test \"%s\"",
                         (LPCTSTR) strCondition);

  if (fread_condition_word () != '(')
    ThrowErrorException ("No \"(\" symbol");
  
CString strArg = fread_condition_word ();

  if (strArg.IsEmpty ())
    ThrowErrorException ("No argument supplied in brackets");

  strArg.MakeLower ();

  if (strArg [0] == '$')
    {
    if (strArg.GetLength () < 2)
      ThrowErrorException ("$ must be followed by a letter");

    if (strchr ("introp", strArg [1]) == NULL)
      ThrowErrorException ("Bad argument character \"%s\"",
                            (LPCTSTR) strArg);

    } // end of $n argument
  else if (pCondition->Arg == eCondDirection)
    {
    if (!lDirections.Find (strArg))
      ThrowErrorException ("Bad direction \"%s\"",
                            (LPCTSTR) strArg);
    }
  else
    { // must be a vnum?
    vnum = atoi (strArg);
  
    if (vnum && pRenumberStuff)
      {
      switch (pCondition->Arg)
        {
        case eCondMobile:
            FixProgramVnum (vnum, 
                            pRenumberStuff->pOldMobVnum, 
                            pRenumberStuff->pNewMobVnum, 
                            pRenumberStuff->iMobCount);
            break;
        case eCondRoom:
            FixProgramVnum (vnum, 
                            pRenumberStuff->pOldRoomVnum, 
                            pRenumberStuff->pNewRoomVnum, 
                            pRenumberStuff->iRoomCount);
            break;
        case eCondObject:
            FixProgramVnum (vnum, 
                            pRenumberStuff->pOldObjVnum, 
                            pRenumberStuff->pNewObjVnum, 
                            pRenumberStuff->iObjCount);
            break;
        } // end of switch
      } // end of having a vnum and wanting to renumber
    } // end of vnum

  if (fread_condition_word () != ')')
    ThrowErrorException ("no \")\" symbol");

  if (pCondition->bBoolean)
    {
    pWord = pWordOrig;    // put word pointer back
    return;   // boolean condition - no arguments
    }

  CString strOperator = fread_condition_operator ();

  if (strOperator == "")
    ThrowErrorException ("expected operator (eg. ==)");

  if (strOperator != "==" &&
      strOperator != "!=" &&
      strOperator != "/" &&
      strOperator != "!/" &&
      strOperator != "<" &&
      strOperator != ">" &&
      strOperator != "<=" &&
      strOperator != ">=" &&
      strOperator != "&" &&
      strOperator != "|")
    ThrowErrorException ("improper operator \"%s\"",
                          (LPCTSTR) strOperator);

      
      
  // get what we are comparing it to

CString strValue = fread_condition_word ();

  vnum = atoi (strValue);

  if (vnum && pRenumberStuff)
    {
    switch (pCondition->Value)
      {
      case eCondMobile:
          FixProgramVnum (vnum, 
                          pRenumberStuff->pOldMobVnum, 
                          pRenumberStuff->pNewMobVnum, 
                          pRenumberStuff->iMobCount);
          break;
      case eCondRoom:
          FixProgramVnum (vnum, 
                          pRenumberStuff->pOldRoomVnum, 
                          pRenumberStuff->pNewRoomVnum, 
                          pRenumberStuff->iRoomCount);
          break;
      case eCondObject:
          FixProgramVnum (vnum, 
                          pRenumberStuff->pOldObjVnum, 
                          pRenumberStuff->pNewObjVnum, 
                          pRenumberStuff->iObjCount);
          break;
      } // end of switch
    } // end of having a vnum and wanting to renumber

  pWord = pWordOrig;    // put word pointer back

  }   // end of HandleCondition

bool CheckCommandSyntax (CString & strCommands, 
                         CString & strMessage,            // error message on error
                         CIntList & xref_rooms,
                         CIntList & xref_objects,
                         CIntList & xref_mobs,
                         t_prenumber pRenumberStuff)
  {
CString str;    // this is for each line of the commands
CString strCommand;
CString strArgument;
CCommand * command;
CSocial * social;
CSkill * skill;
CIntList iflist;

bool bError = false;
POSITION pos;

   strMessage.Empty ();
   xref_rooms.RemoveAll ();
   xref_objects.RemoveAll ();
   xref_mobs.RemoveAll ();

   // don't do it if we have not commands, socials or skills
   if (App.m_CommandList.IsEmpty () 
    || App.m_SocialList.IsEmpty ()
    || App.m_SkillList.IsEmpty ())
     return false;

CStringList lControlFlow;

   lControlFlow.AddTail ("if");
   lControlFlow.AddTail ("or");
   lControlFlow.AddTail ("and");
   lControlFlow.AddTail ("endif");
   lControlFlow.AddTail ("break");
   lControlFlow.AddTail ("else");

   lDirections.RemoveAll ();
   lDirections.AddTail ("n");
   lDirections.AddTail ("s");
   lDirections.AddTail ("e");
   lDirections.AddTail ("w");
   lDirections.AddTail ("ne");
   lDirections.AddTail ("nw");
   lDirections.AddTail ("se");
   lDirections.AddTail ("sw");
   lDirections.AddTail ("u");
   lDirections.AddTail ("d");
   lDirections.AddTail ("somewhere");

   pWord = strCommands.GetBuffer (strCommands.GetLength () + GROWSIZE);
   nLineNumber = 1;     // start at line 1
   nGrownAmount = 0;    // amount we have grown the buffer so far

   try
     {

     while (!bError && *pWord)
       {

       // get next word
       
       strCommand = fread_word (false); // commands are not quoted, but might be a quote

       if (strCommand.IsEmpty ())
         {
         fread_to_eol ();
         continue;   // ignore blank commands
         }

       strCommand.MakeLower ();

       // if found in "control flow" list, keep going (eg. if, else)

       if (lControlFlow.Find (strCommand))
         {
          if (strCommand == "if")
            {
            iflist.AddTail (0);   // add if to list, no elses yet
            HandleCondition (pRenumberStuff);   // look for vnums in conditions
            }
          else if (strCommand == "endif")
            {
            if (iflist.IsEmpty ())
              ThrowErrorException ("ENDIF without corresponding IF");
            iflist.RemoveTail ();   // one less else now
            } // end of endif
          else if (strCommand == "or")
            {
            if (iflist.IsEmpty ())
              ThrowErrorException ("OR without corresponding IF");
            HandleCondition (pRenumberStuff);   // look for vnums in conditions
            } // end of OR
          else if (strCommand == "and")
            {
            if (iflist.IsEmpty ())
              ThrowErrorException ("AND without corresponding IF");
            HandleCondition (pRenumberStuff);   // look for vnums in conditions
            } // end of AND
          else if (strCommand == "else")
            {
            if (iflist.IsEmpty ())
              ThrowErrorException ("ELSE without corresponding IF");

            int iHaveElse = 1;
            POSITION matchpos = NULL;
            // Scan backwards to find last if without an else, and associate
            // the else with it. This is so we can have lots of ifs and elses
            // and know which else belongs to which if
            for (pos = iflist.GetTailPosition (); pos; )
              {
              matchpos = pos;
              if ((iHaveElse = iflist.GetPrev (pos)) == 0)
                break;
              }

            if (iHaveElse)
              ThrowErrorException ("Too many ELSES");

            iflist.SetAt (matchpos, 1); // note else here
            } // end of else

         fread_to_eol ();
         continue;
         }  // end of flow control command (if, endif etc.)

       // look up command in table

      for (pos = App.m_CommandList.GetHeadPosition (); pos; )
        {
        command =  App.m_CommandList.GetNext (pos);

        if (!str_prefix (strCommand, command->name))
          { // command found!
          int vnum;

          command->iReferenced++;   // note used count

          // read vnum or argument if necessary

          if (command->FollowedBy & eCmdName)
            {
            fread_word ();
            }   // end of having an name after it

          if (command->FollowedBy & eCmdSpell)
            {
            CString strSpell = fread_word ();
            POSITION skillpos = 0;
            for (skillpos = App.m_SkillList.GetHeadPosition (); skillpos; )
              {
              skill =  App.m_SkillList.GetNext (skillpos);

              if (skill->type == SKILL_SPELL && !str_prefix (strSpell, skill->name))
                {
                skill->iReferenced++;   // note used count
                break;
                }   // end of match on spell
              }   // end of checking each skill
             
             if (!skillpos)
               ThrowErrorException ("Unknown spell \"%s\"", (LPCTSTR) strSpell);

            }   // end of having an spell after it

          if (command->FollowedBy & eCmdObject)
            {
            vnum = atoi (fread_word ());   // may not be a number, eg $n!
            if (vnum)
              {
              if (xref_objects.Find (vnum) == NULL)
                xref_objects.AddTail (vnum);      // another object cross reference
              if (pRenumberStuff)
                FixProgramVnum (vnum, 
                                pRenumberStuff->pOldObjVnum, 
                                pRenumberStuff->pNewObjVnum, 
                                pRenumberStuff->iObjCount);
              }
            }   // end of having an object after it


          if (command->FollowedBy & eCmdRoom)
            {
            vnum = atoi (fread_word ());   // may not be a number, eg $n!
            if (vnum)
              if (xref_rooms.Find (vnum) == NULL)
                xref_rooms.AddTail (vnum);      // another room cross reference
              if (pRenumberStuff)
                FixProgramVnum (vnum, 
                                pRenumberStuff->pOldRoomVnum, 
                                pRenumberStuff->pNewRoomVnum, 
                                pRenumberStuff->iRoomCount);
            }   // end of having a room after it

          if (command->FollowedBy & eCmdMobile)
            {
            vnum = atoi (fread_word ());   // may not be a number, eg $n!
            if (vnum)
              if (xref_mobs.Find (vnum) == NULL)
                xref_mobs.AddTail (vnum);      // another mob cross reference
              if (pRenumberStuff)
                FixProgramVnum (vnum, 
                                pRenumberStuff->pOldMobVnum, 
                                pRenumberStuff->pNewMobVnum, 
                                pRenumberStuff->iMobCount);
            }   // end of having a mob after it


          if (!(command->FollowedBy & eCmdRepeat))
            fread_to_eol ();

          break;    // out of command-lookup loop
          }   // end of command found

        }   // command-lookup loop

       // if pos is zero, we didn't find the command

       // so, look up social in table

      if (!pos)
        for (pos = App.m_SocialList.GetHeadPosition (); pos; )
          {
          social =  App.m_SocialList.GetNext (pos);

          if (!str_prefix (strCommand, social->name))
            {
            social->iReferenced++;   // note used count
            fread_to_eol ();   // socials are not followed by commands
            break;
            }

          }

       // if pos is zero, we didn't find the command or social

       // so, look up skill in table

      if (!pos)
        for (pos = App.m_SkillList.GetHeadPosition (); pos; )
          {
          skill =  App.m_SkillList.GetNext (pos);

          if (skill->type == SKILL_SKILL && !str_prefix (strCommand, skill->name))
            {
            skill->iReferenced++;   // note used count
            fread_to_eol ();   // skills are not followed by commands
            break;
            }

          }

       // if pos is zero, we didn't find the command, social or skill

       if (!pos)
         ThrowErrorException ("Unknown MUD program command \"%s\"", (LPCTSTR) strCommand);

       }    // end of reading each line

// if we don't have an error yet, report unmatched if/endif

    if (!bError)
      if (!iflist.IsEmpty ())
        {
        int i = iflist.GetCount ();
         strMessage.Format ("There %s %i IF%s without %scorresponding ENDIF%s",
                            i == 1 ? "is" : "are",
                            PLURAL (i),
                            i == 1 ? "a " : " ",
                            i == 1 ? "" : "s");
         bError = true;
        }

    }   // end of try block
  catch (CException * e)
    {

    TCHAR    szCause[255];

    e->GetErrorMessage(szCause, 255);
    strMessage.Format ("%s at line %i of program",
                       (LPCTSTR) szCause, nLineNumber);
    bError = true;
    e->Delete ();
    }

  strCommands.ReleaseBuffer ();  

  return bError;    // return true on syntax error
  } // end of CheckCommandSyntax