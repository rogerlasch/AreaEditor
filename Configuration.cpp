/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#include "stdafx.h"
#include "AreaEditor.h"

#define SETUP_DEFAULTS
  #include "defaults.h"
#undef SETUP_DEFAULTS

#include "configuration.h"

#include "DefaultFlags.h"
#include "DefaultLists.h"

tConfiguration GeneralDirectives [] = 
  {
    { "maxlevel", cfgInteger, &iMaxLevel } ,
    { "maxvnum",  cfgInteger, &iMaxVnum },
    { "maxresetfreq", cfgInteger, &iMaxResetFreq },
    { "maxdescriptionlength", cfgInteger, &iMaxDescriptionLength },
    
  };    // end of configuration directives

tConfiguration MobDirectives [] = 
  {
    { "minac",          cfgInteger, &iMinAC } ,
    { "maxac",          cfgInteger, &iMaxAC },
    { "maxdamnodice",   cfgInteger, &iMaxdamnodice },
    { "maxdamplus",     cfgInteger, &iMaxdamplus},
    { "maxdamroll",     cfgInteger, &iMaxdamroll},
    { "maxmananodice",  cfgInteger, &iMaxmananodice },
    { "maxmanaplus",    cfgInteger, &iMaxmanaplus},
    { "maxmanasizedice",cfgInteger, &iMaxmanasizedice},
    { "maxdamsizedice", cfgInteger, &iMaxdamsizedice},
    { "maxhitnodice",   cfgInteger, &iMaxhitnodice },
    { "maxhitplus",     cfgInteger, &iMaxhitplus},
    { "maxhitroll",     cfgInteger, &iMaxhitroll},
    { "maxhitsizedice", cfgInteger, &iMaxhitsizedice},
    { "minstats",       cfgInteger, &iMinStats},
    { "maxstats",       cfgInteger, &iMaxStats},
    { "minalignment",   cfgInteger, &iMinAlignment},
    { "maxalignment",   cfgInteger, &iMaxAlignment},
    { "maxnumattacks",  cfgInteger, &iMaxNumattacks},
    { "minsavingthrow", cfgInteger, &iMinSavingthrow},
    { "maxsavingthrow", cfgInteger, &iMaxSavingthrow},
    { "defaultname",    cfgString,  &strMobDefaultName },
    { "defaultshortdescription",  cfgString,  &strMobDefaultShortDescription },
    { "defaultlongdescription",   cfgString,  &strMobDefaultLongDescription },
    { "defaultdescription",       cfgString,  &strMobDefaultDescription },

  };    // end of configuration directives

tConfiguration ObjectDirectives [] = 
  {
    { "defaultname",              cfgString,  &strObjectDefaultName },
    { "defaultshortdescription",  cfgString,  &strObjectDefaultShortDescription },
    { "defaultdescription",       cfgString,  &strObjectDefaultDescription },
    { "mincondition",             cfgInteger, &iMinCondition },
    { "maxcondition",             cfgInteger, &iMaxCondition },

  };    // end of configuration directives

tConfiguration RoomDirectives [] = 
  {
    { "defaultname",          cfgString,  &strRoomDefaultName },
    { "defaultdescription",   cfgString,  &strRoomDefaultDescription },

  };    // end of configuration directives

tConfiguration ExitDirectives [] = 
  {
    { "defaultkeywords",      cfgString,  &strExitDefaultKeywords },
    { "defaultdescription",   cfgString,  &strExitDefaultDescription },

  };    // end of configuration directives


tConfiguration RepairDirectives [] = 
  {
    { "minprofitfix",   cfgInteger, &iMinprofitfix } ,
    { "maxprofitfix",   cfgInteger, &iMaxprofitfix },
   
  };    // end of configuration directives

tConfiguration ShopDirectives [] = 
  {
    { "minprofitbuy",   cfgInteger, &iMinprofitbuy } ,
    { "maxprofitbuy",   cfgInteger, &iMaxprofitbuy },
    { "minprofitsell",  cfgInteger, &iMinprofitsell } ,
    { "maxprofitsell",  cfgInteger, &iMaxprofitsell },
   
  };    // end of configuration directives


// used for reading in flags in general

tFlags Flags;

tConfiguration FlagDirectives [64] = 
  {
    { "flag01",   cfgWord, &Flags.strName [0] } ,
    { "flag02",   cfgWord, &Flags.strName [1] } ,
    { "flag03",   cfgWord, &Flags.strName [2] } ,
    { "flag04",   cfgWord, &Flags.strName [3] } ,
    { "flag05",   cfgWord, &Flags.strName [4] } ,
    { "flag06",   cfgWord, &Flags.strName [5] } ,
    { "flag07",   cfgWord, &Flags.strName [6] } ,
    { "flag08",   cfgWord, &Flags.strName [7] } ,
    { "flag09",   cfgWord, &Flags.strName [8] } ,
    { "flag10",   cfgWord, &Flags.strName [9] } ,
    { "flag11",   cfgWord, &Flags.strName [10] } ,
    { "flag12",   cfgWord, &Flags.strName [11] } ,
    { "flag13",   cfgWord, &Flags.strName [12] } ,
    { "flag14",   cfgWord, &Flags.strName [13] } ,
    { "flag15",   cfgWord, &Flags.strName [14] } ,
    { "flag16",   cfgWord, &Flags.strName [15] } ,
    { "flag17",   cfgWord, &Flags.strName [16] } ,
    { "flag18",   cfgWord, &Flags.strName [17] } ,
    { "flag19",   cfgWord, &Flags.strName [18] } ,
    { "flag20",   cfgWord, &Flags.strName [19] } ,
    { "flag21",   cfgWord, &Flags.strName [20] } ,
    { "flag22",   cfgWord, &Flags.strName [21] } ,
    { "flag23",   cfgWord, &Flags.strName [22] } ,
    { "flag24",   cfgWord, &Flags.strName [23] } ,
    { "flag25",   cfgWord, &Flags.strName [24] } ,
    { "flag26",   cfgWord, &Flags.strName [25] } ,
    { "flag27",   cfgWord, &Flags.strName [26] } ,
    { "flag28",   cfgWord, &Flags.strName [27] } ,
    { "flag29",   cfgWord, &Flags.strName [28] } ,
    { "flag30",   cfgWord, &Flags.strName [29] } ,
    { "flag31",   cfgWord, &Flags.strName [30] } ,
    { "flag32",   cfgWord, &Flags.strName [31] } ,
    { "flag33",   cfgWord, &Flags.strName [32] } ,
    { "flag34",   cfgWord, &Flags.strName [33] } ,
    { "flag35",   cfgWord, &Flags.strName [34] } ,
    { "flag36",   cfgWord, &Flags.strName [35] } ,
    { "flag37",   cfgWord, &Flags.strName [36] } ,
    { "flag38",   cfgWord, &Flags.strName [37] } ,
    { "flag39",   cfgWord, &Flags.strName [38] } ,
    { "flag40",   cfgWord, &Flags.strName [39] } ,
    { "flag41",   cfgWord, &Flags.strName [40] } ,
    { "flag42",   cfgWord, &Flags.strName [41] } ,
    { "flag43",   cfgWord, &Flags.strName [42] } ,
    { "flag44",   cfgWord, &Flags.strName [43] } ,
    { "flag45",   cfgWord, &Flags.strName [44] } ,
    { "flag46",   cfgWord, &Flags.strName [45] } ,
    { "flag47",   cfgWord, &Flags.strName [46] } ,
    { "flag48",   cfgWord, &Flags.strName [47] } ,
    { "flag49",   cfgWord, &Flags.strName [48] } ,
    { "flag50",   cfgWord, &Flags.strName [49] } ,
    { "flag51",   cfgWord, &Flags.strName [50] } ,
    { "flag52",   cfgWord, &Flags.strName [51] } ,
    { "flag53",   cfgWord, &Flags.strName [52] } ,
    { "flag54",   cfgWord, &Flags.strName [53] } ,
    { "flag55",   cfgWord, &Flags.strName [54] } ,
    { "flag56",   cfgWord, &Flags.strName [55] } ,
    { "flag57",   cfgWord, &Flags.strName [56] } ,
    { "flag58",   cfgWord, &Flags.strName [57] } ,
    { "flag59",   cfgWord, &Flags.strName [58] } ,
    { "flag60",   cfgWord, &Flags.strName [59] } ,
    { "flag61",   cfgWord, &Flags.strName [60] } ,
    { "flag62",   cfgWord, &Flags.strName [61] } ,
    { "flag63",   cfgWord, &Flags.strName [62] } ,
    { "flag64",   cfgWord, &Flags.strName [63] } ,
   
  };    // end of configuration directives

// this lists all flag sections
tFlagsEntry AllFlags [] =
  {
    {"act",     &MobActFlags,     act_flags, 64 },
    {"affect",  &MobAffectFlags,  a_flags, 64 },
    {"attack",  &MobAttackFlags,  attack_flags, 64 },
    {"defense", &MobDefenseFlags, defense_flags, 64 },
    {"parts",   &MobPartsFlags,   part_flags, 32 },
    {"resist",  &MobResistFlags,  ris_flags, 32 },
    {"language",&MobLanguageFlags,lang_names, 32 },
    {"object",  &ObjectFlags,     o_flags, 64 },
    {"wear",    &WearFlags,       w_flags, 32 },
    {"room",    &RoomFlags,       r_flags, 32 },
    {"exit",    &ExitFlags,       exit_flags, 32 },
    {"area",    &AreaFlags,       area_flags, 32 },

    // for ROM
    {"form",    &MobFormFlags,    form_flags, 32 },
    {"furniture",    &ObjectFurnitureFlags,   furniture_flags, 32 },
    {"container",    &ObjectContainerFlags,   container_flags, 32 },
    {"weaponflags",    &ObjectWeaponFlags,   weapon_flags, 32 },
    {"portal",    &ObjectPortalFlags,   portal_flags, 32 },

    
  };  // end of list of flags

tListEntry AllLists [] =
  {

    {"constants",  &Constants,     NULL },

    // mobs
    {"sex",        &MobSexList,    sex_table },
    {"size",       &MobSizeList,   size_table },
    {"race",       &MobRaceList,   race_table },
    {"class",      &MobClassList,  class_table },
    {"position",   &MobPositionList,   position_table },
    {"special",    &MobSpecialList,   special_functions_table },

    
    // objects
    {"weapon",     &ObjectWeaponList, weapon_table },
    {"liquid",     &ObjectLiquidList, liquid_table },
    {"attacklist",    &ObjectAttackList, attack_table },
    {"item"  ,     &ObjectItemList,   item_table },
    {"wearlist"  ,     &ObjectWearList,   wear_table },
    {"affects",    &ObjectAffectList, affect_table },
    {"weaponcondition",  &ObjectWeaponConditionList, weapon_condition_table },
    {"armourcondition",  &ObjectArmourConditionList, armour_condition_table },
    {"foodcondition",    &ObjectFoodConditionList,   food_condition_table },
    {"affectwhere",  &ObjectAffectWhereList, affect_where_table },

    // rooms

    {"sector",     &RoomSectorList,     sector_table },
    {"direction",  &RoomDirectionList,  direction_table },

    // general

    {"skilltype",   &SkillTypeList,     skill_types_table },
    {"spell",       &SpellNameList,     spell_names_table },
    {"smaugskill",  &SMAUGSkillNameList,SMAUG_skill_names_table },
    {"romskill",    &ROMSkillNameList,  ROM_skill_names_table },
    {"program",     &ProgramNameList,   program_table },

    
    
  };  // end of list of lists

// this lists all non-flag sections
tOtherEntry AllSections [] =
  {
    { "general",  GeneralDirectives,  NUMITEMS (GeneralDirectives) },
    { "mobiles",  MobDirectives,      NUMITEMS (MobDirectives) },
    { "objects",  ObjectDirectives,   NUMITEMS (ObjectDirectives) },
    { "rooms",    RoomDirectives,     NUMITEMS (RoomDirectives) },
    { "exits",    ExitDirectives,     NUMITEMS (ExitDirectives) },
    { "repairs",  RepairDirectives,   NUMITEMS (RepairDirectives) },
    { "shops",    ShopDirectives,     NUMITEMS (ShopDirectives) },
  };  // end of list of other things

void ProcessSection (CFileRead & FileRead, 
                     tConfiguration * ConfigurationDirectives,
                     const int iNumber)
  {
    CString word;
    CString buf;
    bool bMatch;

    for (int i = 0; i < iNumber; i++)
      ConfigurationDirectives [i].bFound = false;
    
    while (true)
    {
	    word   =  FileRead.fread_word ();
      word.MakeLower ();
	    bMatch = false;

      if (word == "*")
        {
	      FileRead.fread_to_eol ();
        bMatch = true;
        }
      else if (word == "end")
        {
        // check all required directives found
        for (int i = 0; i < iNumber; i++)
          if (ConfigurationDirectives [i].bRequired &&
             !ConfigurationDirectives [i].bFound)
             ThrowErrorException ("Required entry \"%s\" not found.",
                ConfigurationDirectives [i].pName);
        
        return;

        }
      else
        for (int i = 0; i < iNumber; i++)
          {

          if (word == ConfigurationDirectives [i].pName)
            {
            switch (ConfigurationDirectives [i].type)
              {
              case cfgString:    // string delimited by ~
                *((CString *)  ConfigurationDirectives [i].pData) = 
                             FileRead.fread_string ();
                break;
              case cfgWord:      // single word
                *((CString *) ConfigurationDirectives [i].pData) = 
                              FileRead.fread_word ();
                break;
              case cfgInteger:   // number
                *((int *) ConfigurationDirectives [i].pData) = 
                              FileRead.fread_number ();
                break;
              case cfgBoolean:   // boolean
                buf = FileRead.fread_word ();
                buf.MakeLower ();
                if (buf == "yes" || buf == "y" || buf == "true")
                  *((bool *) ConfigurationDirectives [i].pData) = true;
                else if (buf == "no" || buf == "n" || buf == "false")
                  *((bool *) ConfigurationDirectives [i].pData) = false;
                else
                  ThrowErrorException ("Directive \"%s\" value \"%s\" should be YES or NO",
                                        ConfigurationDirectives [i].pName,
                                        (LPCTSTR) buf);
                break;

              default: ThrowErrorException 
                         ("Unknown configuration type for directive \"%s\"",
                          ConfigurationDirectives [i].pName);

              } // end of switch on type

            ConfigurationDirectives [i].bFound = true;  // note we found this one
            bMatch = true;
    	      FileRead.fread_to_eol ();   // skip rest of line so it can be a comment
            break;
            }   // end of a match


        } // end of looping through all directives

	    if ( !bMatch )
          ThrowErrorException ("Configuration directive \"%s\" unknown.", (LPCTSTR) word);

   
    }   // end of looping until End found

  } // end of ProcessSection


static void GetFlags (CFileRead & FileRead, tFlags & DestinationFlags, const int iMaxFlags)
  {

  // process the flags section into our general-purpose array
  ProcessSection (FileRead, FlagDirectives, NUMITEMS (FlagDirectives));

  // copy from general-purpose array to specific flags
  for (int i = 0; i < MAX_BITS; i++)
    if (FlagDirectives [i].bFound)
      {
      if (i > iMaxFlags)
        ThrowErrorException ("Too many flags for this section");
      DestinationFlags.strName [i] = *((CString *) FlagDirectives [i].pData);
      }
    else
      DestinationFlags.strName [i].Empty ();

  } // end of GetFlags


static void AddListItem (const CString & sWord, 
                         CConfigList & DestinationList,
                         int & iLastValue)
  {
CString strName;
CString strValue;
int iValue;
int iEquals;

  iEquals = sWord.Find ('=');
  if (iEquals == -1)
    { // take next value
    iLastValue++;
    DestinationList.list.AddTail (tList (sWord, iLastValue));
    } // end of no value specified
  else
    {

    // list items can be:  fred=22
    // isolate name and value
    strName = sWord.Left (iEquals);
    strValue = sWord.Mid (iEquals + 1);
    strName.TrimLeft ();
    strName.TrimRight ();
    strValue.TrimLeft ();
    strValue.TrimRight ();

    // name cannot be empty
    if (strName.IsEmpty ())
      ThrowErrorException ("Invalid list item format \"%s\" - null name",
                            (LPCTSTR) sWord);

    // check for duplicates
    int iExistingValue;
    if (DestinationList.FindValue (strName, iExistingValue))
      ThrowErrorException ("List item \"%s\" is already in this list with value %i",
                            (LPCTSTR) strName,
                            iExistingValue);

    // value cannot be empty
    if (strValue.IsEmpty ())
      ThrowErrorException ("Invalid list item format \"%s\" - null value",
                            (LPCTSTR) sWord);

    // if value is numeric, use it
    if (isdigit (strValue [0]) ||
        strValue [0] == '+' ||
        strValue [0] == '-')
      iValue = atoi (strValue);
    else
      {
      // lookup constants list, so you can cross-reference to a list of constants
      if (!Constants.FindValue (strValue, iValue))
      // lookup an earlier entry in this list, so you can equate values
        if (!DestinationList.FindValue (strValue, iValue))
      // not a number, or existing list item - must be an error
         ThrowErrorException ("Invalid list item format \"%s\" - bad value",
                              (LPCTSTR) sWord);
      }
    
    iLastValue = iValue;

    DestinationList.list.AddTail (tList (strName, iValue));

    } // end of value specified

  } // end of AddListItem

static void GetList(CFileRead & FileRead, CConfigList & DestinationList)
  {
  CString word;
  int iLastValue = -1;

  // clear old contents of list
  DestinationList.list.RemoveAll ();

  while (true)
  {
	  word   =  FileRead.fread_line ();
    word.MakeLower ();

    if (word [0] == '*')
      continue;   // ignore line starting with * (comment)
    else if (word == "end")
      return;     // the word "end" ends the list
    else
      AddListItem (word, DestinationList, iLastValue); 

  }   // end of looping until End found

  } // end of GetFlags

void CAreaEditorApp::LoadConfig (const CString	strFileName) 
  {

  int i;
  CWaitCursor	wait;

	try
	  {

    // they are (re)processing the config file - (re)setup all default flags
    SetUpDefaultFlags ();
    SetUpDefaultLists (); // and lists

    CFileRead FileRead;

    // Open Config file
		CFile	fConfig (strFileName, CFile::modeRead|CFile::shareDenyWrite);

    CArchive ar(&fConfig, CArchive::load);

    FileRead.Init ("Loading Config", &ar);

	  try
	    {
	    while (true)
	     {
	     char letter;
	     CString word;

	     letter = FileRead.fread_letter();
	     if ( letter == '*' )
	       {
	      FileRead.fread_to_eol ();
	      continue;
	      }

	      if ( letter != '#' )
          ThrowErrorException ( "# not found.");

	      word = FileRead.fread_word ();
        word.MakeLower ();

        // look for configuration sections like "general", "mobiles"
        for (i = 0; i < NUMITEMS (AllSections); i++)
          {
          if (word == AllSections [i].pName)
            {
            ProcessSection (FileRead, 
                            AllSections [i].pSection, 
                            AllSections [i].nItems);
            break;
            }
          }

        if (i < NUMITEMS (AllSections))
          continue;   // found section, don't need to look at others

        // look for "flag" sections (eg. "act", "room")
        for (i = 0; i < NUMITEMS (AllFlags); i++)
          {
          if (word == AllFlags [i].pName)
            {
            GetFlags (FileRead, *(AllFlags [i].pFlags), AllFlags [i].iMaxFlags);
            break;
            }
          }

        if (i < NUMITEMS (AllFlags))
          continue;   // found flag, don't need to look at others

        // look for "list" sections (eg. "sex", "race")
        for (i = 0; i < NUMITEMS (AllLists); i++)
          {
          if (word == AllLists [i].pName)
            {
            GetList (FileRead, *(AllLists [i].pList));
            break;
            }
          }

        if (i < NUMITEMS (AllLists))
          continue;   // found list, don't need to look at others

        if (word == "end")
	          break;
	      else
          ThrowErrorException ( "Bad section: %s.", (LPCTSTR) word);
	     } // end of read loop
	    }   // end of try block
	  catch(CException* e)
  	  {
      FileRead.Wrapup ();
      e->ReportError ();
      ::AfxMessageBox (CFormat ("Error occurred in file %s at (line %ld) \"%s\"",
                    (LPCTSTR) strFileName,
                    FileRead.GetLineNumber (), 
                    (LPCTSTR) FileRead.GetLastLineRead ()),
                    MB_ICONINFORMATION);
		  e->Delete();
      ar.Close();
      return;
	    }

    ar.Close();

    FileRead.Wrapup ();

	  }
	catch(CException* e)
  	{
    ::AfxMessageBox (
                    CFormat ("Unable to open Config file: %s", 
                    (LPCTSTR) strFileName), 
                    MB_ICONEXCLAMATION);
		e->Delete();
    return;
	  }

  }


void CAreaEditorApp::SetUpDefaultFlags (void) 
  {
int i,
    j;

  // initialise all default flag names
  for (j = 0; j < NUMITEMS (AllFlags); j++)
    for (i = 0; i < MAX_BITS; i++)
      AllFlags [j].pFlags->strName [i] = AllFlags [j].sDefaultFlags [i];

  }


void CAreaEditorApp::SetUpDefaultLists (void) 
  {
int i,
    j;
int iLastValue;

  // initialise all default list entries
  for (j = 0; j < NUMITEMS (AllLists); j++)
    {
    iLastValue = -1;    // new list - starts at zero
    AllLists [j].pList->list.RemoveAll ();
    if (AllLists [j].sDefaultList)    // null list means no defaults
      for (i = 0; AllLists [j].sDefaultList [i]; i++) 
        AddListItem (AllLists [j].sDefaultList [i], 
                     *(AllLists [j].pList),
                     iLastValue);
    }   // end of doing each list

  }   // end of CAreaEditorApp::SetUpDefaultLists 



// finds a corresponding name for a given value

bool CConfigList::FindName (const int iValue, 
                            CString & strName, 
                            const bool bDefaultToFirst) const
  {
  
  if (list.IsEmpty () && bDefaultToFirst)
    {
    strName = "0";  // cannot show first item, show zero
    return false;
    }

  for (POSITION pos = list.GetHeadPosition (); pos; )
    {
    tList listItem = list.GetNext (pos);

    if (listItem.iValue == iValue)
      {
      strName = listItem.strName;
      return true;
      }
    } // end of loop

  // if not found, default to first item in list

  if (bDefaultToFirst)
    strName = list.GetHead ().strName;
  else
    strName = CFormat ("Unknown=%i", iValue);
  return false;   // not found

  }   // end of CConfigList::FindName

// returns a corresponding name for a given value

CString CConfigList::ReturnName (const EXT_BV iValue, 
                                 const bool bDefaultToFirst) const
  {

  if (list.IsEmpty () && bDefaultToFirst)
    return "0";
  
  for (POSITION pos = list.GetHeadPosition (); pos; )
    {
    tList listItem = list.GetNext (pos);
    if (listItem.iValue == iValue)
      return listItem.strName;
    } // end of loop

  // if not found, default to first item in list or show offending item
  if (bDefaultToFirst)
    return list.GetHead ().strName;   // not found
  else
    return CFormat ("Unknown=%i", iValue);

  }   // end of CConfigList::ReturnName

bool CConfigList::IsValueInList (const int iValue) const     // true if found
  {
  for (POSITION pos = list.GetHeadPosition (); pos; )
    if (list.GetNext (pos).iValue == iValue)
      return true;
  return false;   // not found
  }

// finds a corresponding value for a given name

bool CConfigList::FindValue (const CString strName, 
                             int & iValue,
                             const bool bPartialMatch) const
  {
  
  for (POSITION pos = list.GetHeadPosition (); pos; )
    {
    tList listItem = list.GetNext (pos);

    if (bPartialMatch)
      {
      if (str_prefix (strName, listItem.strName) == 0)
        {
        iValue = listItem.iValue;
        return true;
        } // end of partial match
      } // end of partial match OK
    else
      if (listItem.strName.CompareNoCase (strName) == 0)
        {
        iValue = listItem.iValue;
        return true;
          }
    } // end of loop

  iValue = 0;
  return false;   // not found

  }   // end of CConfigList::FindValue 


// returns a corresponding value for a given name

int CConfigList::ReturnValue (const CString strName,
                              const bool bPartialMatch) const
  {
  
  for (POSITION pos = list.GetHeadPosition (); pos; )
    {
    tList listItem = list.GetNext (pos);

    if (bPartialMatch)
      {
      if (str_prefix (strName, listItem.strName) == 0)
        return listItem.iValue;
      } // end of partial match OK
    else
      if (listItem.strName.CompareNoCase (strName) == 0)
        return listItem.iValue;
    } // end of loop

  return 0;   // not found

  }   // end of CConfigList::ReturnValue 

bool CConfigList::IsNameInList (const CString strName,
                                const bool bPartialMatch) const
  {
  for (POSITION pos = list.GetHeadPosition (); pos; )
    {
    tList listItem = list.GetNext (pos);

    if (bPartialMatch)
      {
      if (str_prefix (strName, listItem.strName) == 0)
        return true;
      } // end of partial match OK
    else
      if (listItem.strName.CompareNoCase (strName) == 0)
        return true;
    } // end of loop

  return false;   // not found
  }
