/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// sex table

static char *  sex_table [] =
{
"none"	,
"male"	,
"female",
"either",
NULL
};

/* mob sizes - ROM only uses this I think */
static char * size_table [] =
{ 
"tiny"	,
"small" ,
"medium",
"large"	,
"huge",
"giant",
NULL
};


/* weapon type list */
static char *  weapon_table []	=
  {
"exotic",
"sword",
"mace",	
"dagger",
"axe",	
"staff",	
"flail",	
"whip",	
"polearm",
NULL
  };


/* liquid type list */
static char *  liquid_table []	=
  {
"water",			
"beer",			
"red wine",	
"ale",		
"dark ale",	
"whisky",		
"lemonade",	
"firebreather",	
"local specialty",	
"slime mold juice",	
"milk",		
"tea",			
"coffee",	
"blood",		
"salt water",	
"coke",			
"root beer",	
"elvish wine",	
"white wine",	
"champagne",		
"mead",			
"rose wine",	
"benedictine wine",	
"vodka",		
"cranberry juice",	
"orange juice",
"absinthe",		
"brandy",			
"aquavit",	
"schnapps",		
"icewine",	
"amontillado",		
"sherry",			
"framboise",	
"rum",			
"cordial",
NULL
  };

/*  ROM race table 
static char *	race_table []		=
{
"unique", "human", "elf", "dwarf", "giant", "bat", "bear", "cat", "centipede", "dog", 
"doll", "dragon", "fido", "fox", "goblin", "hobgoblin", "kobold", "lizard", "modron", 
"orc", "pig", "rabbit", "school monster", "snake", "song bird", "troll", "water fowl", 
"wolf", "wyvern", "unique",
NULL
};    // end of race_table

*/


//  SMAUG race table

static char *	race_table	[] =
{
"human", "elf", "dwarf", "halfling", "pixie", "vampire", "half-ogre",
"half-orc", "half-troll", "half-elf", "gith", "r1", "r2", "r3", "r4", "r5",
"r6", "r7", "r8", "r9", "ant", "ape", "baboon", "bat", "bear", "bee",
"beetle", "boar", "bugbear", "cat", "dog", "dragon", "ferret", "fly",
"gargoyle", "gelatin", "ghoul", "gnoll", "gnome", "goblin", "golem",
"gorgon", "harpy", "hobgoblin", "kobold", "lizardman", "locust",
"lycanthrope", "minotaur", "mold", "mule", "neanderthal", "ooze", "orc",
"rat", "rustmonster", "shadow", "shapeshifter", "shrew", "shrieker",
"skeleton", "slime", "snake", "spider", "stirge", "thoul", "troglodyte",
"undead", "wight", "wolf", "worm", "zombie", "bovine", "canine", "feline",
"porcine", "mammal", "rodent", "avis", "reptile", "amphibian", "fish",
"crustacean", "insect", "spirit", "magical", "horse", "animal", "humanoid",
"monster", "god",
NULL
};



/* attack table  -- not very organized :( */
static char * 	attack_table	[]	=
{
"none", "slice", "stab", "slash", "whip", "claw", "blast", "pound", "crush", "grep", 
"bite", "pierce", "suction", "beating", "digestion", "charge", "slap", "punch", 
"wrath", "magic", "divine", "cleave", "scratch", "peck", "peckb", "chop", "sting", 
"smash", "shbite", "flbite", "frbite", "acbite", "chomp", "drain", "thrust", 
"slime", "shock", "thwack", "flame", "chill",
NULL
};


static char *  position_table  [] =
{
"dead",			
"mortally wounded",	
"incapacitated",
"stunned",	
"sleeping",	
"resting",	
"sitting",
"fighting",	
"standing",
"mounted", 
"being shoved", 
"being dragged",
NULL
};


// SMAUG items

static char * item_table	[] =
{
"(none)", "light", "scroll", "wand", "staff", "weapon", "_fireweapon", "_missile",
"treasure", "armor", "potion", "_worn", "furniture", "trash", "_oldtrap",
"container", "_note", "drinkcon", "key", "food", "money", "pen", "boat",
"corpse", "corpse_pc", "fountain", "pill", "blood", "bloodstain",
"scraps", "pipe", "herbcon", "herb", "incense", "fire", "book", "switch",
"lever", "pullchain", "button", "dial", "rune", "runepouch", "match", "trap",
"map", "portal", "paper", "tinder", "lockpick", "spike", "disease", "oil",
"fuel", "shortbow", "longbow", "crossbow", "projectile", "quiver", "shovel",
"salve",
NULL
};


/* ROM item table 
static char * item_table	[]	=
{
"(none)",
"light",
"scroll",
"wand",
"staff",
"weapon",
"treasure=8",
"armor",
"potion",
"clothing",
"furniture",
"trash",
"container=15",
"drink=17",
"key",
"food",
"money",
"boat=22",
"npc_corpse",
"pc_corpse",
"fountain",
"pill",
"protect",
"map",
"portal",
"warp_stone",
"room_key",
"gem",
"jewelry",
"jukebox",
NULL
};

*/


static char * sector_table [] =
{
"In a room"	,	
"In a city"	,
"In a field"	,	
"In a forest"	,
"Hills"	,	    
"On a mountain"	,
"In the water"	,	
"In rough water"	,
"Underwater" ,	
"In the air"	,
"In a desert",	
"Somewhere",
"Ocean floor" ,	
"Underground"	,
NULL
};


static char * wear_table [] =
{
"(none)=-1", "Light", "Finger-L", "Finger-R", "Neck-1", "Neck-2", "Body", "Head", "Legs",
"Feet", "Hands", "Arms", "Shield", "About", "Waist", "Wrist-L", "Wrist-R",
"Wield", "Hold", "Dual Wield", "Ears", "Eyes", "Missile Wield",
"Back", "Face",  "Ankle-L", "Ankle-R",
NULL
};


static char *	class_table	[] =
{
"mage", "cleric", "thief", "warrior", "vampire", "druid", "ranger",
"augurer", "pc8", "pc9", "pc10", "pc11", "pc12", "pc13", "pc14", "pc15",
"pc16", "pc17", "pc18", "pc19",
"baker", "butcher", "blacksmith", "mayor", "king", "queen",
NULL
};


static char *	direction_table	[] =
{
"North", "East", "South", "West", "Up", "Down",
"Northeast", "Northwest", "Southeast", "Southwest", "Somewhere",
NULL
};


static char * affect_table	[] =
{
"(none)", "strength", "dexterity", "intelligence", "wisdom", "constitution",
"sex", "class", "level", "age", "height", "weight", "mana", "hit", "move",
"gold", "experience", "armor", "hitroll", "damroll", "save_poison", "save_rod",
"save_para", "save_breath", "save_spell", "charisma", "affected", "resistant",
"immune", "susceptible", "weaponspell", "luck", "backstab", "pick", "track",
"steal", "sneak", "hide", "palm", "detrap", "dodge", "peek", "scan", "gouge",
"search", "mount", "disarm", "kick", "parry", "bash", "stun", "punch", "climb",
"grip", "scribe", "brew", "wearspell", "removespell", "mentalstate", "emotion",
"stripsn", "remove", "dig", "full", "thirst", "drunk", "blood",
NULL
};

static char * weapon_condition_table [] =
  {
	 "in superb condition",
   "in excellent condition",
   "in very good condition",
   "in good shape",
   "showing a bit of wear",
   "a little run down",
   "in need of repair",
   "in great need of repair",
   "in dire need of repair",
   "very badly worn",
   "practically worthless",
   "almost broken",
   "broken",
   NULL
  };

static char * armour_condition_table [] =
  {
	"in superb condition",
  "in very good condition",
  "in good shape",
  "showing a bit of wear",
  "a little run down",
  "in need of repair",
  "in great need of repair",
  "in dire need of repair",
  "very badly worn",
  "practically worthless",
  "broken",
  NULL
  };


static char * food_condition_table [] =
  {
  "is fresh",
  "is nearly fresh",
  "is perfectly fine",
  "looks good",
  "looks ok",
  "is a little stale",
  "is a bit stale",
  "smells slightly off",
  "smells quite rank",
  "smells revolting",
  "is crawling with maggots",
  NULL
  };

static char * special_functions_table [] =
  {
  "(none)",   // used to indicate no special function
  "spec_breath_any",	  
  "spec_breath_acid",
  "spec_breath_fire",	
  "spec_breath_frost",	
  "spec_breath_gas",
  "spec_breath_lightning",
  "spec_cast_adept",	  
  "spec_cast_cleric",	
  "spec_cast_mage",	  
  "spec_cast_undead",	
  "spec_executioner",	
  "spec_fido",		 
  "spec_guard",	
  "spec_janitor",
  "spec_mayor",	
  "spec_poison",	
  "spec_thief"	,
  "spec_questmaster",     // for ROM only
  NULL
  };

static char * skill_types_table [] = 
  { 
  "unknown", "Spell", "Skill", "Weapon", "Tongue", "Herb", 
  "Racial", "Disease",
  NULL
  };


static char * spell_names_table [] =
  {
"spell_smaug" , "spell_acid_blast" , "spell_animate_dead" , "spell_astral_walk" , 
"spell_blindness" , "spell_burning_hands" , "spell_call_lightning" , "spell_cause_critical" ,
"spell_cause_light" , "spell_cause_serious" , "spell_change_sex" , "spell_charm_person" ,
"spell_chill_touch" , "spell_colour_spray" , "spell_control_weather" , "spell_create_food" ,
"spell_create_water" , "spell_cure_blindness" , "spell_cure_poison" , "spell_curse" ,
"spell_detect_poison" , "spell_dispel_evil" , "spell_dispel_magic" , "spell_dream" ,
"spell_earthquake" , "spell_enchant_weapon" , "spell_energy_drain" , "spell_faerie_fire" ,
"spell_faerie_fog" , "spell_farsight" , "spell_fireball" , "spell_flamestrike" ,
"spell_gate" , "spell_knock" , "spell_harm" , "spell_identify" , "spell_invis" ,
"spell_know_alignment" , "spell_lightning_bolt" , "spell_locate_object" , "spell_magic_missile" ,
"spell_mist_walk" , "spell_pass_door" , "spell_plant_pass" , "spell_poison" ,
"spell_polymorph" , "spell_possess" , "spell_recharge" , "spell_remove_curse" ,
"spell_remove_invis" , "spell_remove_trap" , "spell_shocking_grasp" , "spell_sleep" ,
"spell_solar_flight" , "spell_summon" , "spell_teleport" , "spell_ventriloquate" ,
"spell_weaken" , "spell_word_of_recall" , "spell_acid_breath" , "spell_fire_breath" ,
"spell_frost_breath" , "spell_gas_breath" , "spell_lightning_breath" , "spell_spiral_blast" ,
"spell_scorching_surge" , "spell_helical_flow" , "spell_transport" , "spell_portal" ,
"spell_ethereal_fist" , "spell_spectral_furor" , "spell_hand_of_chaos" , "spell_disruption" ,
"spell_sonic_resonance" , "spell_mind_wrack" , "spell_mind_wrench" , "spell_revive" ,
"spell_sulfurous_spray" , "spell_caustic_fount" , "spell_acetum_primus" , "spell_galvanic_whip" ,
"spell_magnetic_thrust" , "spell_quantum_spike" , "spell_black_hand" , "spell_black_fist" ,
"spell_black_lightning" , "spell_midas_touch" , "reserved" , "spell_null" , 
NULL
  };

static char * SMAUG_skill_names_table [] = 
  {
"do_aassign" , "do_advance" , "do_affected" , "do_afk" , "do_aid" , "do_allow" , 
"do_ansi" , "do_answer" , "do_apply" , "do_appraise" , "do_areas" , "do_aset" ,
"do_ask" , "do_astat" , "do_at" , "do_auction" , "do_authorize" , "do_avtalk" ,
"do_backstab" , "do_balzhur" , "do_bamfin" , "do_bamfout" , "do_ban" , "do_bash" ,
"do_bashdoor" , "do_berserk" , "do_bestow" , "do_bestowarea" , "do_bio" , "do_boards" ,
"do_bodybag" , "do_brandish" , "do_brew" , "do_bset" , "do_bstat" , "do_bug" ,
"do_bury" , "do_buy" , "do_cast" , "do_cedit" , "do_channels" , "do_chat" , 
"do_check_vnums" , "do_circle" , "do_clans" , "do_clantalk" , "do_clear" , "do_climb" ,
"do_close" , "do_cmdtable" , "do_cmenu" , "do_commands" , "do_comment" , "do_compare" ,
"do_config" , "do_consider" , "do_council_induct" , "do_council_outcast" , 
"do_councils" , "do_counciltalk" , "do_credits" , "do_cset" , "do_deities" , 
"do_deny" , "do_description" , "do_destro" , "do_destroy" , "do_detrap" , "do_devote" ,
"do_dig" , "do_disarm" , "do_disconnect" , "do_dismount" , "do_dmesg" , "do_down" ,
"do_drag" , "do_drink" , "do_drop" , "do_diagnose" , "do_east" , "do_eat" , 
"do_echo" , "do_emote" , "do_empty" , "do_enter" , "do_equipment" , "do_examine" ,
"do_exits" , "do_feed" , "do_fill" , "do_fixchar" , "do_flee" , "do_foldarea" ,
"do_follow" , "do_for" , "do_force" , "do_forceclose" , "do_form_password" ,
"do_fquit" , "do_freeze" , "do_get" , "do_give" , "do_glance" , "do_gold" , 
"do_goto" , "do_gouge" , "do_group" , "do_grub" , "do_gtell" , "do_guilds" , 
"do_guildtalk" , "do_hedit" , "do_hell" , "do_help" , "do_hide" , "do_hitall" ,
"do_hlist" , "do_holylight" , "do_homepage" , "do_hset" , "do_ide" , "do_idea" ,
"do_immortalize" , "do_immtalk" , "do_induct" , "do_installarea" , "do_instaroom" ,
"do_instazone" , "do_inventory" , "do_invis" , "do_kick" , "do_kill" , "do_languages" ,
"do_last" , "do_leave" , "do_level" , "do_light" , "do_list" , "do_litterbug" ,
"do_loadarea" , "do_loadup" , "do_lock" , "do_log" , "do_look" , "do_lookmap" ,
"do_low_purge" , "do_mailroom" , "do_make" , "do_makeboard" , "do_makeclan" ,
"do_makecouncil" , "do_makedeity" , "do_makerepair" , "do_makeshop" , "do_makewizlist" ,
"do_mapout" , "do_massign" , "do_mcreate" , "do_mdelete" , "do_memory" , "do_mfind" ,
"do_minvoke" , "do_mlist" , "do_mmenu" , "do_mount" , "do_mp_close_passage" ,
"do_mp_damage" , "do_mp_deposit" , "do_mp_open_passage" , "do_mp_practice" ,
"do_mp_restore" , "do_mp_slay" , "do_mp_withdraw" , "do_mpadvance" , "do_mpapply" ,
"do_mpapplyb" , "do_mpasound" , "do_mpat" , "do_mpdream" , "do_mpecho" , "do_mpechoaround" ,
"do_mpechoat" , "do_mpedit" , "do_mpfavor" , "do_mpforce" , "do_mpgoto" , "do_mpinvis" ,
"do_mpjunk" , "do_mpkill" , "do_mpmload" , "do_mpmset" , "do_mpnothing" , "do_mpoload" ,
"do_mposet" , "do_mppkset" , "do_mppurge" , "do_mpstat" , "do_mptransfer" , 
"do_mrange" , "do_mset" , "do_mstat" , "do_murde" , "do_murder" , "do_muse" , 
"do_music" , "do_mwhere" , "do_name" , "do_newbiechat" , "do_newbieset" , "do_newzones" ,
"do_noemote" , "do_noresolve" , "do_north" , "do_northeast" , "do_northwest" ,
"do_notell" , "do_notitle" , "do_noteroom" , "do_oassign" , "do_ocreate" , 
"do_odelete" , "do_ofind" , "do_ogrub" , "do_oinvoke" , "do_oldscore" , "do_olist" ,
"do_omenu" , "do_opedit" , "do_open" , "do_opstat" , "do_orange" , "do_order" ,
"do_orders" , "do_ordertalk" , "do_oset" , "do_ostat" , "do_outcast" , "do_owhere" ,
"do_pagelen" , "do_pager" , "do_pardon" , "do_password" , "do_peace" , "do_pick" ,
"do_poison_weapon" , "do_practice" , "do_prompt" , "do_pull" , "do_punch" , 
"do_purge" , "do_push" , "do_put" , "do_qpset" , "do_quaff" , "do_quest" , "do_qui" ,
"do_quit" , "do_rank" , "do_rassign" , "do_rat" , "do_rdelete" , "do_reboo" ,
"do_reboot" , "do_recho" , "do_recite" , "do_redit" , "do_redraw_page" , "do_refresh_page" ,
"do_regoto" , "do_remove" , "do_rent" , "do_repair" , "do_repairset" , "do_repairshops" ,
"do_repairstat" , "do_reply" , "do_report" , "do_rescue" , "do_reset" , "do_rest" ,
"do_restore" , "do_restoretime" , "do_restrict" , "do_retire" , "do_retran" ,
"do_return" , "do_revert" , "do_rip" , "do_rlist" , "do_rmenu" , "do_rpedit" ,
"do_rpstat" , "do_rreset" , "do_rset" , "do_rstat" , "do_sacrifice" , "do_save" ,
"do_savearea" , "do_say" , "do_scan" , "do_score" , "do_scribe" , "do_search" ,
"do_sedit" , "do_sell" , "do_set_boot_time" , "do_setclan" , "do_setclass" ,
"do_setcouncil" , "do_setdeity" , "do_shops" , "do_shopset" , "do_shopstat" ,
"do_shout" , "do_shove" , "do_showclan" , "do_showclass" , "do_showcouncil" ,
"do_showdeity" , "do_shutdow" , "do_shutdown" , "do_silence" , "do_sit" , "do_sla" ,
"do_slay" , "do_sleep" , "do_slice" , "do_slist" , "do_slookup" , "do_smoke" ,
"do_snoop" , "do_sober" , "do_socials" , "do_south" , "do_southeast" , "do_southwest" ,
"do_speak" , "do_split" , "do_sset" , "do_stand" , "do_steal" , "do_stun" , 
"do_supplicate" , "do_switch" , "do_tamp" , "do_tell" , "do_think" , "do_time" ,
"do_timecmd" , "do_title" , "do_track" , "do_transfer" , "do_trust" , "do_typo" ,
"do_unfoldarea" , "do_unhell" , "do_unlock" , "do_unsilence" , "do_up" , "do_users" ,
"do_value" , "do_visible" , "do_vnums" , "do_vsearch" , "do_wake" , "do_wartalk" ,
"do_wear" , "do_weather" , "do_west" , "do_where" , "do_who" , "do_whois" , 
"do_wimpy" , "do_wizhelp" , "do_wizlist" , "do_wizlock" , "do_yell" , "do_zap", 
"do_zones" ,  
 NULL
};


static char * program_table [] =
  {
"in_file_prog" , "act_prog" , "speech_prog" , "rand_prog" , "fight_prog" , "hitprcnt_prog" ,
"death_prog" , "entry_prog" , "greet_prog" , "all_greet_prog", "give_prog" ,
"bribe_prog" , "time_prog" , "hour_prog" , "wear_prog" , "remove_prog" , "sac_prog" ,
"look_prog" , "exa_prog" , "zap_prog" , "get_prog" , "drop_prog" , "damage_prog" ,
"repair_prog" , "greet_prog" , "randiw_prog" , "speechiw_prog" , "pull_prog",
"push_prog"	 , "sleep_prog" , "rest_prog"	 , "rfight_prog" , "enter_prog" ,
"leave_prog" , "rdeath_prog"	 , "script_prog"	 , "use_prog"	 ,
NULL
  };


static char * ROM_skill_names_table [] =
  {
"(none)=-1",
"reserved",
"acid blast",
"armor",
"bless",
"blindness",
"burning hands",
"call lightning",
"calm",
"cancellation",
"cause critical",
"cause light",
"cause serious",
"chain lightning",
"change sex",
"charm person",
"chill touch",
"colour spray",
"continual light",
"control weather",
"create food",
"create rose",
"create spring",
"create water",
"cure blindness",
"cure critical",
"cure disease",
"cure light",
"cure poison",
"cure serious",
"curse",
"demonfire",
"detect evil",
"detect good",
"detect hidden",
"detect invis",
"detect magic",
"detect poison",
"dispel evil",
"dispel good",
"dispel magic",
"earthquake",
"enchant armor",
"enchant weapon",
"energy drain",
"faerie fire",
"faerie fog",
"farsight",
"fireball",
"fireproof",
"flamestrike",
"fly",
"floating disc",
"frenzy",
"gate",
"giant strength",
"harm",
"haste",
"heal",
"heat metal",
"holy word",
"identify",
"infravision",
"invisibility",
"know alignment",
"lightning bolt",
"locate object",
"magic missile",
"mass healing",
"mass invis",
"nexus",
"pass door",
"plague",
"poison",
"portal",
"protection evil",
"protection good",
"ray of truth",
"recharge",
"refresh",
"remove curse",
"sanctuary",
"shield",
"shocking grasp",
"sleep",
"slow",
"stone skin",
"summon",
"teleport",
"ventriloquate",
"weaken",
"word of recall",
"acid breath",
"fire breath",
"frost breath",
"gas breath",
"lightning breath",
"general purpose",
"high explosive",
"axe",
"dagger",
"flail",
"mace",
"polearm",
"shield block",
"spear",
"sword",
"whip",
"backstab",
"bash",
"berserk",
"dirt kicking",
"disarm",
"dodge",
"enhanced damage",
"envenom",
"hand to hand",
"kick",
"parry",
"rescue",
"trip",
"second attack",
"third attack",
"fast healing",
"haggle",
"hide",
"lore",
"meditation",
"peek",
"pick lock",
"sneak",
"steal",
"scrolls",
"staves",
"wands",
"recall",
NULL

  };

static char * affect_where_table [] =
  {
"affects",
"object",	
"immune",	
"resist",	
"vuln",		
"weapon",	
NULL
  };

