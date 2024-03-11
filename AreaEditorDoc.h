/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// AreaEditorDoc.h : interface of the CAreaEditorDoc class
//


/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_AREAEDITORDOC_H__30BE035F_E9F1_11D1_A20A_0000B4595568__INCLUDED_)
#define AFX_AREAEDITORDOC_H__30BE035F_E9F1_11D1_A20A_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


// ============================================================================

// New versions - things to change

#define THISVERSION 135                      // Step 1. - no leading zero or it's octal
const CString SMAUGEDITOR_VERSION = "1.35";    // Step 2.
// Step 3. Don't forget VERSION resource in Resources tab
// Step 4. Remember: README.TXT 

// ============================================================================

const CString MY_EMAIL_ADDRESS = "http://www.gammon.com.au/support/";
const CString MY_WEB_PAGE = "http://www.gammon.com.au";
const CString CHANGES_WEB_PAGE = "http://www.gammon.com.au/smaugeditor/buglist.htm";
const CString MUD_LIST = "http://www.gammon.com.au/links/muds.htm";

class CAreaEditorView;
class CShop;
class CRepair;
class CAreaEditorDoc;
class CMUDprogram;
class CExtraDescription;
class CExit;
class CRoomMap;
class CAffect;
class CRoom;
class CMobile;
class CMUDObject;

// find room in all open areas
CRoom * FindRoom (const int vnum);
CString FullRoomName (const CRoom * room);
// find mob in all open areas
CMobile * FindMob (const int vnum);
CString FullMobName (const CMobile * mob);
// find object in all open areas
CMUDObject * FindObj (const int vnum);
CString FullObjName (const CMUDObject * obj);

void CheckAreas (CAreaEditorDoc * pDoc);

enum { 
        eFindSummary,     // match on "summary" data only
        eFindDetail,      // match on as much detail as possible
        eFindProgram,     // match on program contents  
        eFindVnum,        // match on vnum
      };

// what sort of renumbering to do

typedef enum {
        eRenumberAll,
        eRenumberMob,
        eRenumberObj,
        eRenumberRoom,
  } t_renumbertype;


// ============================================================================

// CMUDitem is the basic item upon which mobs, rooms, objects and so on are built

class CMUDitem : public CObject
{

protected:
	DECLARE_DYNAMIC(CMUDitem)

    // constructor
  CMUDitem (CRuntimeClass* pViewClass, CAreaEditorDoc * pDoc);

  virtual void ChangeRHview (CAreaEditorView * pLHview, CView * pView) = 0;

  CRuntimeClass* m_pViewClass;    // for creating splitter window RH view

  HTREEITEM m_hdlTreeItem;        // which tree item displays it
  CTreeCtrl * m_pTreeCtrl;      // and the view which it belongs to

  CAreaEditorDoc * m_pDoc;          // which document owns it

  bool m_bReferenced;             // true if referenced by something else

  void GoTo (void);             // go to the tree item for this guy

  virtual CString Summary (void) = 0; // return summary of this item
  virtual const char * Type (void) = 0; // return item type (eg. mobile)
  virtual void Delete (void);       // delete item (and remove from tree ctrl)
  virtual CMUDitem * Add (CAreaEditorView * pView,
                          const bool bSelect = true) 
                        { return NULL; }; // add a sub-type (eg. a program to a mob)
  virtual BOOL CanAdd (void) { return FALSE; };  // can we add a subtype?
  virtual CString AddDescription (void) { return ""; };  // description of what add does
  virtual void Duplicate (CAreaEditorView * pView) {}; // duplicate this item
  virtual BOOL CanDuplicate (void) { return FALSE; };  // can we duplicate this item?
  virtual CMUDprogram * AddProgram (CAreaEditorView * pView, 
                                    CMUDitem * pItem,
                                    const bool bSelect = true) { return NULL; }; // add a program after the arg
  virtual CExtraDescription * AddDescription (CAreaEditorView * pView) { return NULL; }; // add a description
  virtual CExit * AddExit (CAreaEditorView * pView) { return NULL; }; // add an exit
  virtual CRoomMap * AddMap (CAreaEditorView * pView) { return NULL; }; // add a map
  virtual CAffect * AddAffect (CAreaEditorView * pView) { return NULL; }; // add an affect
  virtual void SubItemDeleted (CMUDitem * pItem) {}; // a sub-item has been deleted

  // Search does the appropriate type of search and returns true if found
  virtual BOOL Search (const CString strWanted, 
                       const int iFindType,
                       const BOOL bMatchCase);

  // helper utility for adding a reference to this item to a listbox
  void AddToListBox (CListBox & ctlListBox, 
                     const char * strDescription = "",
                     const bool bSelectIt = false);

};


typedef CTypedPtrList <CPtrList, CMUDitem*> CMUDitemList;

// This is for cross references in programs
typedef CList<int, int> CIntList;

typedef struct
  {
  int * pOldMobVnum;    // old mob vnums
  int * pNewMobVnum;    // new mob vnums
  int * pOldObjVnum;    // old object vnums
  int * pNewObjVnum;    // new object vnums
  int * pOldRoomVnum;   // old room vnums 
  int * pNewRoomVnum;   // new room vnums
  int iMobCount;        // how many mobs
  int iObjCount;        // how many objects
  int iRoomCount;       // how many rooms
  } t_renumber, * t_prenumber;

// scans a MUD program looking for errors (returns true if error found)
// strMessage: error reason
// also returns list of cross-referenced rooms, objects and mobs
bool CheckCommandSyntax (CString & strCommands, 
                         CString & strMessage,            // error message on error
                         CIntList & xref_rooms,
                         CIntList & xref_objects,
                         CIntList & xref_mobs,
                         t_prenumber pRenumberStuff = NULL);

class CMUDprogram : public CMUDitem
{
  DECLARE_DYNAMIC(CMUDprogram)

  int		 type;
  CString	 arglist;
  CString	 comlist;

  CIntList xref_rooms;      // which rooms this program refers to
  CIntList xref_objects;    // which objects this program refers to
  CIntList xref_mobs;       // which mobs this program refers to

  int     iSortSeq;   // for sorting after an add

  virtual void ChangeRHview (CAreaEditorView * pLHview, CView * pView);
  CMUDprogram (CRuntimeClass* pViewClass, CAreaEditorDoc * pDoc);
  virtual CString Summary (void);
  virtual const char * Type (void) { return "program"; };
  virtual CMUDitem * Add (CAreaEditorView * pView,
                          const bool bSelect);  // add a sub-type (eg. a program to a mob)
  virtual CString AddDescription (void);  // description of what add does
  virtual BOOL CanAdd (void) { return TRUE; }; // can we add a subtype?
  virtual void Duplicate (CAreaEditorView * pView); // duplicate this item
  virtual BOOL CanDuplicate (void) { return TRUE; };  // can we duplicate this item?
  // Search does the appropriate type of search and returns true if found
  virtual BOOL Search (const CString strWanted, 
                       const int iFindType,
                       const BOOL bMatchCase);
  void Copy (const CMUDprogram * const RHside);
  };

typedef CTypedPtrList <CPtrList, CMUDprogram*> CMUDprogramList;

class CAffect : public CMUDitem
{
  DECLARE_DYNAMIC(CAffect)

    int		location;
    EXT_BV		modifier;
    int   where;    // ROM
    EXT_BV   bitvector;    // ROM

  virtual void ChangeRHview (CAreaEditorView * pLHview, CView * pView);
  CAffect (CRuntimeClass* pViewClass, CAreaEditorDoc * pDoc);
  virtual CString Summary (void);
  virtual const char * Type (void) { return "affect"; };
  // Search does the appropriate type of search and returns true if found
  virtual BOOL Search (const CString strWanted, 
                       const int iFindType,
                       const BOOL bMatchCase);
  void Copy (const CAffect * const RHside);
  virtual void Duplicate (CAreaEditorView * pView); // duplicate this item
  virtual BOOL CanDuplicate (void) { return TRUE; };  // can we duplicate this item?

  };

typedef CTypedPtrList <CPtrList, CAffect*> CAffectList;

class CExtraDescription : public CMUDitem
{
  DECLARE_DYNAMIC(CExtraDescription)

  CString keyword;              /* Keyword in look/examine          */
  CString description;          /* What to see                      */

  int     iSortSeq;   // for sorting after an add

  virtual void ChangeRHview (CAreaEditorView * pLHview, CView * pView);
  CExtraDescription (CRuntimeClass* pViewClass, CAreaEditorDoc * pDoc)
        : CMUDitem (pViewClass, pDoc) {};
  virtual CString Summary (void);
  virtual const char * Type (void) { return "description"; };
  // Search does the appropriate type of search and returns true if found
  virtual BOOL Search (const CString strWanted, 
                       const int iFindType,
                       const BOOL bMatchCase);
  
  void Copy (const CExtraDescription * const RHside);
  virtual void Duplicate (CAreaEditorView * pView); // duplicate this item
  virtual BOOL CanDuplicate (void) { return TRUE; };  // can we duplicate this item?
  };

typedef CTypedPtrList <CPtrList, CExtraDescription*> CExtraDescriptionList;


class CExit : public CMUDitem
{
  DECLARE_DYNAMIC(CExit)

  CString		keyword;	/* Keywords for exit or door	*/
  CString		description;	/* Description of exit		*/
  int		vnum;		/* Vnum of room exit leads to	*/
  EXT_BV		exit_info;	/* door states & other flags	*/
  int		key;		/* Key vnum			*/
  int		vdir;		/* Physical "direction"		*/
  int		distance;	/* how far to the next room	*/

  virtual void ChangeRHview (CAreaEditorView * pLHview, CView * pView);
  CExit (CRuntimeClass* pViewClass, CAreaEditorDoc * pDoc);
  virtual CString Summary (void);
  virtual const char * Type (void) { return "exit"; };
  // Search does the appropriate type of search and returns true if found
  virtual BOOL Search (const CString strWanted, 
                       const int iFindType,
                       const BOOL bMatchCase);
  void Copy (const CExit * const RHside);
  virtual void Duplicate (CAreaEditorView * pView); // duplicate this item
  virtual BOOL CanDuplicate (void) { return TRUE; };  // can we duplicate this item?

  };

typedef CTypedPtrList <CPtrList, CExit*> CExitList;

class CRoomMap : public CMUDitem
{
  DECLARE_DYNAMIC(CRoomMap)

  int vnum;		/* which map this room belongs to */
  int x;		/* horizontal coordinate */
  int y;		/* vertical coordinate */
  char entry;		/* code that shows up on map */ 

  virtual void ChangeRHview (CAreaEditorView * pLHview, CView * pView);
  CRoomMap (CRuntimeClass* pViewClass, CAreaEditorDoc * pDoc);
  virtual CString Summary (void);
  virtual const char * Type (void) { return "room map"; };
  void Copy (const CRoomMap * const RHside);
  virtual void Duplicate (CAreaEditorView * pView); // duplicate this item
  virtual BOOL CanDuplicate (void) { return TRUE; };  // can we duplicate this item?
  
  };

typedef CTypedPtrList <CPtrList, CRoomMap*> CRoomMapList;

class CRoom : public CMUDitem
{
  DECLARE_DYNAMIC(CRoom)

    CString		name;
    CString		description;
    int		vnum;
    EXT_BV		room_flags;
    int		sector_type;
    int		tele_vnum;
    int		tele_delay;
    int		tunnel;		     /* max people that will fit */

    int   heal_rate;     // ROM;
    int   mana_rate;     // ROM
    CString clan;        // ROM
    CString owner;       // ROM

  CRoomMapList maplist;
  CExitList exitlist;
  CExtraDescriptionList extralist;
  CMUDprogramList programlist;


  virtual void ChangeRHview (CAreaEditorView * pLHview, CView * pView);
  CRoom (CRuntimeClass* pViewClass, CAreaEditorDoc * pDoc);
  virtual CString Summary (void);
  virtual const char * Type (void) { return "room"; };
  
  ~CRoom ();
  virtual void Delete (void);       // delete item (and remove from tree ctrl)
  virtual void SubItemDeleted (CMUDitem * pItem); // a sub-item has been deleted
  virtual CMUDitem * Add (CAreaEditorView * pView,
                          const bool bSelect);  // add a sub-type (eg. a program to a mob)
  virtual CString AddDescription (void);  // description of what add does
  virtual BOOL CanAdd (void) { return TRUE; }; // can we add a subtype?
  virtual void Duplicate (CAreaEditorView * pView); // duplicate this item
  virtual BOOL CanDuplicate (void) { return TRUE; }; // can we duplicate it?
  virtual CMUDprogram * AddProgram (CAreaEditorView * pView, 
                                    CMUDitem * pItem,
                                    const bool bSelect = true); // add a program after the arg
  virtual CExtraDescription * AddDescription (CAreaEditorView * pView) ; // add a description
  virtual CExit * AddExit (CAreaEditorView * pView); // add an exit
  virtual CRoomMap * AddMap (CAreaEditorView * pView); // add a map
  // Search does the appropriate type of search and returns true if found
  virtual BOOL Search (const CString strWanted, 
                       const int iFindType,
                       const BOOL bMatchCase);
  void Copy (const CRoom * const RHside);
  };

typedef CTypedPtrList <CPtrList, CRoom*> CRoomList;

class CMobile : public CMUDitem
  {
  protected:
  DECLARE_DYNAMIC(CMobile)
  public:

    CString	player_name;
    CString	short_descr;
    CString	long_descr;
    CString	description;
    int   spec_fun;
    int		vnum;
    int		sex;
    int		level;
    EXT_BV		act;
    EXT_BV		affected_by;
    int		alignment;
    int		mobthac0;		/* Unused */
    int		ac;
    int		hitnodice;
    int		hitsizedice;
    int		hitplus;
    int		damnodice;
    int		damsizedice;
    int		damplus;
    int		numattacks;
    int		gold;
    int		exp;
    EXT_BV		xflags;
    EXT_BV		resistant;
    EXT_BV		immune;
    EXT_BV		susceptible;
    EXT_BV		attacks;
    EXT_BV		defenses;
    EXT_BV		speaks;
    EXT_BV 	speaking;
    int		position;
    int		defposition;
    int		height;
    int		weight;
    int		race;
    int		mobclass;
    int		hitroll;
    int		damroll;
    int		perm_str;
    int		perm_int;
    int		perm_wis;
    int		perm_dex;
    int		perm_con;
    int		perm_cha;
    int		perm_lck;
    int		saving_poison_death;
    int		saving_wand;
    int		saving_para_petri;
    int		saving_breath;
    int		saving_spell_staff;


    CString material;   // ROM
    int   group;        // ROM
    int   ac_pierce;    // ROM
    int   ac_bash;      // ROM
    int   ac_slash;     // ROM
    int   ac_exotic;    // ROM
    int   dam_type;     // ROM
    int		mananodice;   // ROM
    int		manasizedice; // ROM
    int		manaplus;     // ROM
    int   size;         // ROM
    EXT_BV   form;         // ROM
    int   remove_act;   // ROM
    int   remove_aff;   // ROM
    int   remove_off;   // ROM
    int   remove_imm;   // ROM
    int   remove_res;   // ROM
    int   remove_vul;   // ROM
    int   remove_for;   // ROM
    int   remove_par;   // ROM

  CMUDprogramList programlist;

  virtual void ChangeRHview (CAreaEditorView * pLHview, CView * pView);
  CMobile (CRuntimeClass* pViewClass, CAreaEditorDoc * pDoc);
  virtual CString Summary (void);
  virtual const char * Type (void) { return "mobile"; };

  ~CMobile(); // destructor
  virtual void Delete (void);       // delete item (and remove from tree ctrl)
  virtual CMUDitem * Add (CAreaEditorView * pView,
                          const bool bSelect);  // add a sub-type (eg. a program to a mob)
  virtual CString AddDescription (void);  // description of what add does
  virtual BOOL CanAdd (void) { return TRUE; }; // can we add a subtype?
  virtual void Duplicate (CAreaEditorView * pView); // duplicate this item
  virtual BOOL CanDuplicate (void) { return TRUE; }; // can we duplicate it?
  virtual CMUDprogram * AddProgram (CAreaEditorView * pView, 
                                    CMUDitem * pItem,
                                    const bool bSelect = true); // add a program after the arg
  virtual void SubItemDeleted (CMUDitem * pItem); // a sub-item has been deleted
  // Search does the appropriate type of search and returns true if found
  virtual BOOL Search (const CString strWanted, 
                       const int iFindType,
                       const BOOL bMatchCase);
  void Copy (const CMobile * const RHside);

  };

typedef CTypedPtrList <CPtrList, CMobile*> CMobileList;

class CMUDObject : public CMUDitem
  {
  protected:
  DECLARE_DYNAMIC(CMUDObject)
  public:

    CString	name;
    CString	short_descr;
    CString	description;
    CString	action_desc;
    int		vnum;
    int		item_type;
    EXT_BV		extra_flags;
    int		magic_flags; 
    EXT_BV		wear_flags;
    int		weight;
    int		cost;
    int		value	[6];
    int		layers;
    int		rent;			/* Unused */

  CString material;   // ROM
  int     level;      // ROM
  int     condition;  // ROM

  CMUDprogramList programlist;
  CAffectList affectlist;
  CExtraDescriptionList extralist;

  virtual void ChangeRHview (CAreaEditorView * pLHview, CView * pView);
  CMUDObject (CRuntimeClass* pViewClass, CAreaEditorDoc * pDoc);
  virtual CString Summary (void);
  virtual const char * Type (void) { return "object"; };

  ~CMUDObject ();
  virtual void Delete (void);       // delete item (and remove from tree ctrl)
  virtual CMUDitem * Add (CAreaEditorView * pView,
                          const bool bSelect);  // add a sub-type (eg. a program to a mob)
  virtual CString AddDescription (void);  // description of what add does
  virtual BOOL CanAdd (void) { return TRUE; }; // can we add a subtype?
  virtual void Duplicate (CAreaEditorView * pView); // duplicate this item
  virtual BOOL CanDuplicate (void) { return TRUE; }; // can we duplicate it?
  virtual CMUDprogram * AddProgram (CAreaEditorView * pView, 
                                    CMUDitem * pItem,
                                    const bool bSelect = true); // add a program after the arg
  virtual CExtraDescription * AddDescription (CAreaEditorView * pView); // add a description
  virtual CAffect * AddAffect (CAreaEditorView * pView); // add an affect
  virtual void SubItemDeleted (CMUDitem * pItem); // a sub-item has been deleted
  // Search does the appropriate type of search and returns true if found
  virtual BOOL Search (const CString strWanted, 
                       const int iFindType,
                       const BOOL bMatchCase);
  void Copy (const CMUDObject * const RHside);
  CString ValueSummary (void) const;  // summarises what the values mean
  };

typedef CTypedPtrList <CPtrList, CMUDObject*> CMUDObjectList;


class CReset : public CMUDitem
  {
  protected:
  DECLARE_DYNAMIC(CReset)
  public:

/*
 * Reset commands:
 *   '*': comment
 *   'M': read a mobile
 *   'O': read an object
 *   'P': put object in object
 *   'G': give object to mobile
 *   'E': equip object to mobile
 *   'H': hide an object
 *   'B': set a bitvector
 *   'T': trap an object
 *   'D': set state of door
 *   'R': randomize room exits
 *   'S': stop (end of list)
 */

  char		command;
  int			extra;
  int			arg1;
  int			arg2;
  int			arg3;
  int     arg4; // ROM

  CString strComment;   // comment from loaded file

  int     iSortSeq;   // for sorting after an add

  virtual void ChangeRHview (CAreaEditorView * pLHview, CView * pView);
  CReset (CRuntimeClass* pViewClass, CAreaEditorDoc * pDoc);
  virtual CString Summary (void);
  virtual const char * Type (void) { return "reset"; };
  virtual void Delete (void);       // delete item (and remove from tree ctrl)
  virtual CMUDitem * Add (CAreaEditorView * pView,
                          const bool bSelect);  // add a sub-type (eg. a program to a mob)
  virtual CString AddDescription (void);  // description of what add does
  virtual BOOL CanAdd (void) { return TRUE; }; // can we add a subtype?
  virtual void Duplicate (CAreaEditorView * pView); // duplicate this item
  virtual BOOL CanDuplicate (void) { return TRUE; }; // can we duplicate it?
  void Copy (const CReset * const RHside);
  };

typedef CTypedPtrList <CPtrList, CReset*> CResetList;

#define MAX_TRADE	 5

class CShop : public CMUDitem
  {
  protected:
  DECLARE_DYNAMIC(CShop)
  public:

    int	keeper;			/* Vnum of shop keeper mob	*/
    int	buy_type [MAX_TRADE];	/* Item types shop will buy	*/
    int	profit_buy;		/* Cost multiplier for buying	*/
    int	profit_sell;		/* Cost multiplier for selling	*/
    int	open_hour;		/* First opening hour		*/
    int	close_hour;		/* First closing hour		*/

  virtual void ChangeRHview (CAreaEditorView * pLHview, CView * pView);
  CShop (CRuntimeClass* pViewClass, CAreaEditorDoc * pDoc);
  virtual CString Summary (void);
  virtual const char * Type (void) { return "shop"; };
  virtual void Delete (void);       // delete item (and remove from tree ctrl)
  };

typedef CTypedPtrList <CPtrList, CShop*> CShopList;

#define MAX_FIX		3
#define SHOP_FIX	1
#define SHOP_RECHARGE	2

class CRepair : public CMUDitem
  {
  protected:
  DECLARE_DYNAMIC(CRepair)
  public:

    int		keeper;		/* Vnum of shop keeper mob	*/
    int	  fix_type [MAX_FIX];	/* Item types shop will fix	*/
    int	  profit_fix;		/* Cost multiplier for fixing	*/
    int	  shop_type;		/* Repair shop type		*/
    int	  open_hour;		/* First opening hour		*/
    int	  close_hour;		/* First closing hour		*/

  virtual void ChangeRHview (CAreaEditorView * pLHview, CView * pView);
  CRepair (CRuntimeClass* pViewClass, CAreaEditorDoc * pDoc);
  virtual CString Summary (void);
  virtual const char * Type (void) { return "repair"; };
  virtual void Delete (void);       // delete item (and remove from tree ctrl)
  };

typedef CTypedPtrList <CPtrList, CRepair*> CRepairList;

class CHelp : public CMUDitem
  {
  protected:
  DECLARE_DYNAMIC(CHelp)
  public:

    int	level;
    CString	keyword;
    CString	text;

  virtual void ChangeRHview (CAreaEditorView * pLHview, CView * pView);
  CHelp (CRuntimeClass* pViewClass, CAreaEditorDoc * pDoc);
  virtual CString Summary (void);
  virtual const char * Type (void) { return "help"; };
  virtual void Delete (void);       // delete item (and remove from tree ctrl)
  // Search does the appropriate type of search and returns true if found
  virtual BOOL Search (const CString strWanted, 
                       const int iFindType,
                       const BOOL bMatchCase);
  };

typedef CTypedPtrList <CPtrList, CHelp*> CHelpList;

class CArea : public CMUDitem
  {
  protected:
  DECLARE_DYNAMIC(CArea)
  public:

// #AREA

  CString strAreaName;

  // ------------ for ROM -------------------
  CString strFileName;  
  int min_vnum;
  int max_vnum;

// #AUTHOR

  CString strAuthor;

// #RANGES

  int low_soft_range;
  int hi_soft_range; 
  int low_hard_range;
  int hi_hard_range; 

// #RESETMSG

  CString strResetMsg;

// #FLAGS

  EXT_BV flags;
  int reset_frequency;

// #ECONOMY

  long high_economy;
  long low_economy;

// #VERSION

  int area_version;

// #WEATHER

  int	climate_temp;	/* climate of the area */
  int	climate_precip;
  int	climate_wind;

// #NEIGHBOR

  CStringList neighboursList;

// for internal use

  int obj_low_vnum;
  int obj_hi_vnum;

  int mob_low_vnum;
  int mob_hi_vnum;

  int room_low_vnum;
  int room_hi_vnum;

  virtual void ChangeRHview (CAreaEditorView * pLHview, CView * pView);
  CArea (CRuntimeClass* pViewClass, CAreaEditorDoc * pDoc);
  virtual CString Summary (void);
  virtual const char * Type (void) { return "area"; };
  virtual void Delete (void);       // delete item (and remove from tree ctrl)
  };

class CAreaEditorDoc : public CDocument
{
protected: // create from serialization only
	CAreaEditorDoc();
	DECLARE_DYNCREATE(CAreaEditorDoc)

// Attributes
public:

  CAreaEditorView * m_active_view;

  CAreaEditorView * m_leftview;   // LH pane view

  int m_iCurrentMobileTab;
  int m_iCurrentRoomTab;
  int m_iCurrentObjectTab;
  int m_iCurrentExitTab;
  int m_iCurrentAreaTab;

  CString m_strErrorMessage;    // for showing at end of area load
  CString m_strWarningType;     // load or save
  int m_nErrors;

  bool m_bDoingDelete;        // true if in middle of deleting an item

  t_areatype m_AreaType,             // eSMAUG or eROM
             m_Original_AreaType;    // what it was loaded as

  CFileRead m_FileRead;
  CFileWrite m_FileWrite;

// #AREA
// #AUTHOR
// #RANGES
// #RESETMSG
// #FLAGS
// #ECONOMY
// #VERSION
// #CLIMATE
// #NEIGHBOR

  CArea * m_Area;

// #MOBILES

  CMobileList m_MobList;

// #OBJECTS

  CMUDObjectList m_ObjectList;

// #ROOMS

  CRoomList m_RoomList;

// #RESETS

  CResetList m_ResetList;

// #SHOPS

  CShopList m_ShopList;

// #REPAIRS

  CRepairList m_RepairList;

// #HELPS

  CHelpList m_HelpList;

// Operations
public:

  char fread_letter (void);
  CString fread_word (void);
  CString fread_string (const bool bLeftJustify = true);
  CString fread_line (void);
  long fread_number (const bool bFlag = false);
  EXT_BV fread_bitvector (const bool bFlag = false);
  CString fread_to_eol (void);

  void fwrite_string (const char * s);
  void load_area (void);
    void load_SMAUG_area (void);
    void load_ROM_area (void);
  void load_author (void);
  void load_version (void);
  void load_climate (void);
  void load_neighbour (void);
  void load_ranges (void);
  void load_resetmsg (void);
  void load_flags (void);
  void load_economy (void);
  void load_mobiles (void);
    void load_SMAUG_mobiles (void);
    void load_ROM_mobiles (void);
  void load_objects (void);
    void load_SMAUG_objects (void);
    void load_ROM_objects (void);
  void load_rooms (void);
    void load_SMAUG_rooms (void);
    void load_ROM_rooms (void);
  void load_resets (void);
  void load_shops (void);
  void load_repairs (void);
  void load_specials (void);
  void load_helps (void);

  void SortMobiles (void);
  void SortObjects (void);
  void SortRooms (void);

  CString skill_name (const int iValue, const bool bNone = false);

    int SMAUG_skill_lookup (const char *name);
    CString SMAUG_skill_name (const int iValue, const bool bNone = false);

    int ROM_skill_lookup (const char *name);
    CString ROM_skill_name (const int iValue, const bool bNone = false);

  void save_area (void);
    void save_SMAUG_area (void);
    void save_ROM_area (void);
  void save_mobiles (void);
    void save_SMAUG_mobiles (void);
    void save_ROM_mobiles (void);
  void save_objects (void);
    void save_SMAUG_objects (void);
    void save_ROM_objects (void);
  void save_rooms (void);
    void save_SMAUG_rooms (void);
    void save_ROM_rooms (void);
  void save_resets (void);
  void save_shops (void);
  void save_repairs (void);
  void save_specials (void);
  void save_helps (void);
  void DoSaveMilestone (void);


  void mprog_read_programs (CMUDitem * item, 
                            CMUDprogramList & programlist);
  void save_programs (CMUDprogramList & programlist);


  CRoom * get_room_index (const int vnum) const;
  void goto_room (const int vnum);
  
  CMobile * get_mob_index (const int vnum);
  void goto_mob (const int vnum);

  CMUDObject * get_obj_index (const int vnum) const;
  void goto_object (const int vnum);

  CExit * get_exit (const CRoom * pRoomIndex, const int vdir) const;
  void goto_exit (const CRoom * pRoomIndex, const int vdir);

  void LoadWarning (LPCTSTR lpszFormat, ...);
  void Warning (CMUDitem * item, LPCTSTR lpszFormat, ...);

  bool AreaRenumber (const t_renumbertype iRenumberType = eRenumberAll,
                     const int iOldVnum = 0,
                     const int iNewVnum = 0);

  void AreaCheck ( int & iTotalRooms,
                   int & iTotalMobs,
                   int & iTotalObjects,
                   int & iTotalExits,
                   int & iTotalPrograms);
  void CrossReferenceCheck (void);

// Adding things

  CMobile * AddMobile (CAreaEditorView * pView, const bool bSelect = false);
  CMUDObject * AddObject (CAreaEditorView * pView, const bool bSelect = false);
  CRoom * AddRoom (CAreaEditorView * pView, const bool bSelect = false);

// printing

  bool ProduceReport (CFile & fOutput);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAreaEditorDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	protected:
	virtual BOOL SaveModified();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAreaEditorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
  BOOL MySaveModified() { return SaveModified (); };

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAreaEditorDoc)
	afx_msg void OnFileAreaSummary();
	afx_msg void OnUpdateStatusModified(CCmdUI* pCmdUI);
	afx_msg void OnAreaCheck();
	afx_msg void OnAreaRenumber();
	afx_msg void OnUpdateAreaRenumber(CCmdUI* pCmdUI);
	afx_msg void OnAreaWalkthrough();
	afx_msg void OnUpdateAreaWalkthrough(CCmdUI* pCmdUI);
	afx_msg void OnFileExportMush();
	afx_msg void OnUpdateFileExportMush(CCmdUI* pCmdUI);
	afx_msg void OnViewWarnings();
	afx_msg void OnUpdateViewWarnings(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AREAEDITORDOC_H__30BE035F_E9F1_11D1_A20A_0000B4595568__INCLUDED_)
