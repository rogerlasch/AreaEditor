/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#include "stdafx.h"
#include "defaults.h"

/*
 * ------------------------------------------------------------------------ *
 *			     Mud constants module			    *
 ****************************************************************************/

#include "AreaEditor.h"

#include "AreaEditorDoc.h"

char *  spell_flag[18] =
{ "water", "earth", "air", "astral", "area", "distant", "reverse",
"save_half_dam", "save_negates", "accumulative", "recastable", "noscribe",
"nobrew", "group", "object", "character", "secretskill", "pksensitive" };

char * spell_saves[8] =
{ "none", "poison_death", "wands", "para_petri", "breath", "spell_staff", 
  "unknown", "unknown"  };

char * spell_damage[8] =
{ "none", "fire", "cold", "electricity", "energy", "acid", "poison", "drain" };

char * spell_action[8] =
{ "none", "create", "destroy", "resist", "suscept", "divinate", "obscure",
"change" };

char * spell_power[4] =
{ "none", "minor", "greater", "major" };

char * spell_class[8] =
{ "none", "lunar", "solar", "travel", "summon", "life", "death", "illusion" };

char * target_type[5] =
{ "ignore", "offensive", "defensive", "self", "objinv" };

CString flag_string( EXT_BV bitvector, char * const flagarray[] )
{
    CString buf;
    int x;

    buf.Empty ();
    for ( x = 0; x < MAX_BITS ; x++ )
      if ( IS_SET( bitvector,  (unsigned __int64) 1 << x ) )
      {
      if (!buf.IsEmpty ())
        buf += " ";
      buf += flagarray[x];
      }
    
    return buf;
}

CString FlagToString (const EXT_BV bitvector, const tFlags & flagarray )
{
    CString buf;
    int x;

    buf.Empty ();
    for ( x = 0; x < MAX_BITS ; x++ )
      if ( IS_SET( bitvector, (unsigned __int64) 1 << x ) )
      {
      if (!buf.IsEmpty ())
        buf += " ";
      buf += flagarray.strName[x];
      }
    
    return buf;
}


CString convert_areaflag (const EXT_BV flag)
  {
  return FlagToString (flag, AreaFlags);
  }

CString convert_actflag (const EXT_BV flag)
  {
  return FlagToString (flag, MobActFlags);
  }

CString convert_affectflag (const EXT_BV flag)
  {
  return FlagToString (flag, MobAffectFlags);
  }


CString convert_object_flags (const EXT_BV flag)
  {
  return FlagToString (flag, ObjectFlags);
  }

CString convert_room_flags (const EXT_BV flag)
  {
  return FlagToString (flag, RoomFlags);
  }

CString convert_wear_flags (const EXT_BV flag)
  {
  return FlagToString (flag, WearFlags);
  }

CString convert_partflag (const EXT_BV flag)
  {
  return FlagToString (flag, MobPartsFlags);
  }

CString convert_attackflag (const EXT_BV flag)
  {
  return FlagToString (flag, MobAttackFlags);
  }

CString convert_defenseflag (const EXT_BV flag)
  {
  return FlagToString (flag, MobDefenseFlags);
  }

CString convert_formflag (const EXT_BV flag)
  {
  return FlagToString (flag, MobFormFlags);
  }

CString convert_risflag (const EXT_BV flag)
  {
  return FlagToString (flag, MobResistFlags);
  }

CString convert_languages (const EXT_BV flag)
  {
  return FlagToString (flag, MobLanguageFlags);
  }

CString convert_spell_flags (const EXT_BV flag)
  {
  return flag_string (flag, spell_flag);
  }

CString convert_exit_flags (const EXT_BV flag)
  {
  return FlagToString (flag, ExitFlags);
  }

/* Weather constants - FB */
char * temp_settings[MAX_CLIMATE] =
{
	"cold",
	"cool",
	"normal",
	"warm",
	"hot",
};

char * precip_settings[MAX_CLIMATE] =
{
	"arid",
	"dry",
	"normal",
	"damp",
	"wet",
};

char * wind_settings[MAX_CLIMATE] =
{
	"still",
	"calm",
	"normal",
	"breezy",
	"windy",
};

