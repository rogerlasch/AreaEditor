/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#pragma once

#ifdef SETUP_DEFAULTS
  #define CONFIG(type, name, dflt) type name = dflt
  #define CONFIGNODEFAULT(type, name) type name
#else
  #define CONFIG(type, name, dflt) extern type name
  #define CONFIGNODEFAULT(type, name) extern type name
#endif

// general

CONFIG (int, iMaxLevel, 65);
CONFIG (int, iMaxVnum, 2147483647);
CONFIG (int, iMaxResetFreq, 60);
CONFIG (int, iMaxDescriptionLength, 79);

// mobiles

CONFIG (int, iMinAC, -300);
CONFIG (int, iMaxAC, +300);
CONFIG (int, iMaxdamnodice, 100);
CONFIG (int, iMaxdamplus, 1000);
CONFIG (int, iMaxdamroll, 65);
CONFIG (int, iMaxmananodice, 999);
CONFIG (int, iMaxmanaplus, 32767);
CONFIG (int, iMaxmanasizedice, 32767);
CONFIG (int, iMaxdamsizedice, 100);
CONFIG (int, iMaxhitnodice, 32767);
CONFIG (int, iMaxhitplus, 32767);
CONFIG (int, iMaxhitroll, 85);
CONFIG (int, iMaxhitsizedice, 32767);
CONFIG (int, iMinStats, 0);
CONFIG (int, iMaxStats, 25);
CONFIG (int, iMinAlignment, -1000);
CONFIG (int, iMaxAlignment, +1000);
CONFIG (int, iMaxNumattacks, 20);
CONFIG (int, iMinSavingthrow, -30);
CONFIG (int, iMaxSavingthrow, +30);
CONFIG (CString, strMobDefaultName, "new mob");
CONFIG (CString, strMobDefaultShortDescription, "A newly created mob");
CONFIG (CString, strMobDefaultLongDescription, "A newly created mob is standing here");
CONFIG (CString, strMobDefaultDescription, "Someone has abandoned a new mob here" ENDLINE);

// objects

CONFIG (CString, strObjectDefaultName, "Object name");
CONFIG (CString, strObjectDefaultShortDescription, "A newly created object");
CONFIG (CString, strObjectDefaultDescription, "A newly created object sits here." ENDLINE);
CONFIG (int, iMinCondition, 0);
CONFIG (int, iMaxCondition, 100);

// rooms

CONFIG (CString, strRoomDefaultName, "Room name");
CONFIG (CString, strRoomDefaultDescription, "You stumble into a newly created room." ENDLINE);

// exits

CONFIG (CString, strExitDefaultKeywords, "");
CONFIG (CString, strExitDefaultDescription, "Exit description");

// repairs

CONFIG (int, iMinprofitfix, 1);
CONFIG (int, iMaxprofitfix, 1000);


// shops

CONFIG (int, iMinprofitbuy, 1);
CONFIG (int, iMaxprofitbuy, 1000);
CONFIG (int, iMinprofitsell, 1);
CONFIG (int, iMaxprofitsell, 1000);


// mob flags

CONFIGNODEFAULT (tFlags, MobActFlags);
CONFIGNODEFAULT (tFlags, MobAffectFlags);
CONFIGNODEFAULT (tFlags, MobAttackFlags);
CONFIGNODEFAULT (tFlags, MobDefenseFlags);
CONFIGNODEFAULT (tFlags, MobPartsFlags);
CONFIGNODEFAULT (tFlags, MobResistFlags);
CONFIGNODEFAULT (tFlags, MobLanguageFlags);

// mob lists

CONFIGNODEFAULT (CConfigList, MobSexList);
CONFIGNODEFAULT (CConfigList, MobSizeList);
CONFIGNODEFAULT (CConfigList, MobRaceList);
CONFIGNODEFAULT (CConfigList, MobClassList);
CONFIGNODEFAULT (CConfigList, MobPositionList);
CONFIGNODEFAULT (CConfigList, MobSpecialList);

// object flags

CONFIGNODEFAULT (tFlags, ObjectFlags);
CONFIGNODEFAULT (tFlags, WearFlags);
CONFIGNODEFAULT (tFlags, ObjectFurnitureFlags);
CONFIGNODEFAULT (tFlags, ObjectContainerFlags);
CONFIGNODEFAULT (tFlags, ObjectWeaponFlags);
CONFIGNODEFAULT (tFlags, ObjectPortalFlags);


// object lists

CONFIGNODEFAULT (CConfigList, ObjectWeaponList);
CONFIGNODEFAULT (CConfigList, ObjectLiquidList);
CONFIGNODEFAULT (CConfigList, ObjectAttackList);
CONFIGNODEFAULT (CConfigList, ObjectItemList);
CONFIGNODEFAULT (CConfigList, ObjectWearList);
CONFIGNODEFAULT (CConfigList, ObjectAffectList);
CONFIGNODEFAULT (CConfigList, ObjectWeaponConditionList);
CONFIGNODEFAULT (CConfigList, ObjectArmourConditionList);
CONFIGNODEFAULT (CConfigList, ObjectFoodConditionList);
CONFIGNODEFAULT (CConfigList, ObjectAffectWhereList);

// room flags

CONFIGNODEFAULT (tFlags, RoomFlags);
CONFIGNODEFAULT (tFlags, ExitFlags);

// room lists

CONFIGNODEFAULT (CConfigList, RoomSectorList);
CONFIGNODEFAULT (CConfigList, RoomDirectionList);

// area flags

CONFIGNODEFAULT (tFlags, AreaFlags);


// ROM form flags

CONFIGNODEFAULT (tFlags, MobFormFlags);

// Constants

CONFIGNODEFAULT (CConfigList, Constants);


// skills and spells

CONFIGNODEFAULT (CConfigList, SkillTypeList);
CONFIGNODEFAULT (CConfigList, SpellNameList);
CONFIGNODEFAULT (CConfigList, SMAUGSkillNameList);
CONFIGNODEFAULT (CConfigList, ROMSkillNameList);

// programs

CONFIGNODEFAULT (CConfigList, ProgramNameList);
