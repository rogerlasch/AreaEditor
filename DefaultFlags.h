/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// MOB act flags

static char *	act_flags [MAX_BITS] =
{
"Npc", 
"Sentinel", 
"Scavenger", 
"", 
"", 
"Aggressive", 
"Stayarea",
"Wimpy", 
"Pet", 
"Train", 
"Practice", 
"Immortal", 
"Deadly", 
"Polyself",
"Meta_aggr", 
"Guardian", 
"Running", 
"Nowander", 
"Mountable", 
"Mounted", 
"Scholar",
"Secretive", 
"Polymorphed", 
"Mobinvis", 
"Noassist", 
"", 
"", 
"", 
"",
"", 
"Prototype", 
  };

static char *	a_flags [MAX_BITS] =
{
"Blind",                // 1
"Invisible", 
"Detect_evil", 
"Detect_invis", 
"Detect_magic",
"Detect_hidden", 
"Hold", 
"Sanctuary", 
"Faerie_fire", 
"Infrared",     // 10
"Curse",
"Flaming", 
"Poison", 
"Protect", 
"Paralysis", 
"Sneak", 
"Hide", 
"Sleep",
"Charm", 
"Flying",       // 20
"Pass_door", 
"Floating", 
"Truesight", 
"Detect_traps",
"Scrying", 
"Fireshield", 
"Shockshield", 
"", 
"Iceshield", 
"Possess",    // 30
"Berserk", 
"Aqua_breath",  // 32
"Recurringspell",    // 33
"Contagious",         // 34
"Acidmist",           // 35
"Venomshield"         // 36
 };

static char *	attack_flags [MAX_BITS] =
{
"Bite", 
"Claws", 
"Tail", 
"Sting", 
"Punch", 
"Kick", 
"Trip", 
"Bash", 
"Stun",
"Gouge", 
"Backstab", 
"Feed", 
"Drain", 
"Firebreath", 
"Frostbreath",
"Acidbreath", 
"Lightnbreath", 
"Gasbreath", 
"Poison", 
"Nastypoison", 
"Gaze",
"Blindness", 
"Causeserious", 
"Earthquake", 
"Causecritical", 
"Curse",
"Flamestrike", 
"Harm", 
"Fireball", 
"Colorspray", 
"Weaken", 
};

static char *	defense_flags [MAX_BITS] =
{
"Parry", 
"Dodge", 
"Heal", 
"Curelight", 
"Cureserious", 
"Curecritical",
"Dispelmagic", 
"Dispelevil", 
"Sanctuary", 
"Fireshield", 
"Shockshield",
"Shield", 
"Bless", 
"Stoneskin", 
"Teleport", 
"Monsum1", 
"Monsum2", 
"Monsum3",
"Monsum4", 
"Disarm", 
"Iceshield", 
"Grip", 
};

static char *	part_flags [MAX_BITS] =
{
"Head", 
"Arms", 
"Legs", 
"Heart", 
"Brains", 
"Guts", 
"Hands", 
"Feet", 
"Fingers",
"Ear", 
"Eye", 
"Long_tongue", 
"Eyestalks", 
"Tentacles", 
"Fins", 
"Wings",
"Tail", 
"Scales", 
"Claws", 
"Fangs", 
"Horns", 
"Tusks", 
"Tailattack",
"Sharpscales", 
"Beak", 
"Haunches", 
"Hooves", 
"Paws", 
"Forelegs", 
"Feathers",
};

static char *	ris_flags [MAX_BITS] =
{
"Fire", 
"Cold", 
"Electricity", 
"Energy", 
"Blunt", 
"Pierce", 
"Slash", 
"Acid",
"Poison", 
"Drain", 
"Sleep", 
"Charm", 
"Hold", 
"Nonmagic", 
"Plus1", 
"Plus2",
"Plus3", 
"Plus4", 
"Plus5", 
"Plus6", 
"Magic", 
"Paralysis", 
};

static char * lang_names [MAX_BITS] = 
  { 
"Common",   
"Elvish", 
"Dwarven", 
"Pixie", 
"Ogre",
"Orcish", 
"Trollese", 
"Rodent", 
"Insectoid",
"Mammal", 
"Reptile", 
"Dragon", 
"Spiritual",
"Magical", 
"Goblin", 
"God", 
"Ancient",
"Halfling", 
"Clan", 
"Gith"
 
  };

static char *	o_flags	[MAX_BITS] =
{
"Glow", 
"Hum", 
"Dark", 
"Loyal", 
"Evil", 
"Invis", 
"Magic", 
"Nodrop", 
"Bless",
"Antigood", 
"Antievil", 
"Antineutral", 
"Noremove", 
"Inventory",
"Antimage", 
"Antithief", 
"Antiwarrior", 
"Anticleric", 
"Organic", 
"Metal",
"Donation", 
"Clanobject", 
"Clancorpse", 
"Antivampire", 
"Antidruid", 
"Hidden", 
"Poisoned", 
"Covering", 
"Deathrot", 
"Burried", 
"Prototype",
};

static char *	w_flags	[MAX_BITS] =
{
"Take", 
"Finger", 
"Neck", 
"Body", 
"Head", 
"Legs", 
"Feet", 
"Hands", 
"Arms",
"Shield", 
"About", 
"Waist", 
"Wrist", 
"Wield", 
"Hold", 
"Dual", 
"Ears", 
"Eyes",
"Missile", 
};

static char *	r_flags	[MAX_BITS] =
{
"Dark", 
"Death", 
"Nomob", 
"Indoors", 
"Lawful", 
"Neutral", 
"Chaotic",
"Nomagic", 
"Tunnel", 
"Private", 
"Safe", 
"Solitary", 
"Petshop", 
"Norecall",
"Donation", 
"Nodropall", 
"Silence", 
"Logspeech", 
"Nodrop", 
"Clanstoreroom",
"Nosummon", 
"Noastral", 
"Teleport", 
"Teleshowdesc", 
"Nofloor", 
"", 
"",
"", 
"", 
"", 
"Prototype", 
};


static char *	area_flags	[MAX_BITS] =
{
"Nopkill", 
};


// ROM form flags

static char * form_flags [MAX_BITS] =
  {
"Edible",           
"Poison",
"Magical",            
"Instant_decay",      
"Other",
"",              
"Animal",             
"Sentient",           
"Undead",             
"Construct",          
"Mist",               
"Intangible",        
"Biped",              
"Centaur",            
"Insect",             
"Spider",             
"Crustacean",         
"Worm",               
"Blob",
"",              
"",              
"Mammal",             
"Bird",               
"Reptile",            
"Snake",              
"Dragon",             
"Amphibian",          
"Fish",               
"Cold_blood",
  };

static char *  exit_flags [MAX_BITS] = 
{ 
"isdoor", 
"", 
"", 
"", 
"", 
"pickproof", 
"", 
"",
"", 
"", 
"nopass" };

static char * furniture_flags [MAX_BITS] =
  {
"Stand_at",
"Stand_on",
"Stand_in",
"Sit_at",
"Sit_on",
"Sit_in",
"Rest_at",
"Rest_on",
"Rest_in",
"Sleep_at",
"Sleep_on",
"Sleep_in",
"Put_at",
"Put_on",
"Put_in",
"Put_inside",
  };


static char * container_flags [MAX_BITS] =
  {
"Closeable",
"Pickproof",
"Closed",	 
"Locked",	 
"Put_on",	 
  };


static char * portal_flags [MAX_BITS] =
  {
"Normal_exit",
"Nocurse",		
"Gowith",
"Buggy",	
"Random",
};


static char * weapon_flags [MAX_BITS] =
  {
"Flaming",	
"Frost",		
"Vampiric",	
"Sharp",		
"Vorpal",		
"Two_hands",
"Shocking",	
"Poison",		
  };
