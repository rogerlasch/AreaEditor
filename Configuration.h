/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/


// configuration directive types
typedef enum
  {
  cfgString,    // string delimited by ~
  cfgWord,      // single word
  cfgInteger,   // number
  cfgBoolean,   // boolean

  } tConfigType;

// configuration directive entry
typedef struct
  {
  char * pName;   // configuration directive name
  tConfigType type; // what sort of directive it is
  void * pData;   // pointer to where to put the data
  bool bRequired; // is this directive mandatory?
  bool bFound;    // was it found?
  } tConfiguration;


// flags directive entry
typedef struct
  {
  char * pName; // name of flags section
  tFlags * pFlags;  // pointer to flags definitions
  char ** sDefaultFlags;    // default values
  int iMaxFlags;     // how many? (32 or 64)
  } tFlagsEntry;

// list directive entry
typedef struct
  {
  char * pName; // name of flags section
  CConfigList * pList;  // pointer to list definitions
  char ** sDefaultList;    // default values
  } tListEntry;

// other entry type
typedef struct
  {
  char * pName; // name of section
  tConfiguration * pSection;  // pointer to section definition
  int  nItems;  // number of items in section
  } tOtherEntry;

