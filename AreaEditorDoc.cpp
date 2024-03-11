/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// AreaEditorDoc.cpp : implementation of the CAreaEditorDoc class
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "MainFrm.h"

#include "AreaEditorDoc.h"
#include "AreaLoadingProblems.h"
#include "AreaEditorView.h"

#include "MobileView.h"
#include "MUDProgramView.h"
#include "ObjectView.h"
#include "ObjectAffectView.h"
#include "ObjectExtraDescriptionView.h"
#include "AreaView.h"
#include "RoomView.h"
#include "RoomExitView.h"
#include "RoomMapView.h"
#include "ResetView.h"
#include "ShopView.h"
#include "RepairView.h"
#include "HelpView.h"

#include "AreaSummary.h"
#include "WalkthroughDlg.h"
#include "defaults.h"
#include "AreaTypeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CMUDitem, CObject)

IMPLEMENT_DYNAMIC(CArea, CMUDitem)
IMPLEMENT_DYNAMIC(CMobile, CMUDitem)
IMPLEMENT_DYNAMIC(CMUDprogram, CMUDitem)
IMPLEMENT_DYNAMIC(CMUDObject, CMUDitem)
IMPLEMENT_DYNAMIC(CAffect, CMUDitem)
IMPLEMENT_DYNAMIC(CExtraDescription, CMUDitem)
IMPLEMENT_DYNAMIC(CExit, CMUDitem)
IMPLEMENT_DYNAMIC(CRoomMap, CMUDitem)
IMPLEMENT_DYNAMIC(CRoom, CMUDitem)
IMPLEMENT_DYNAMIC(CReset, CMUDitem)
IMPLEMENT_DYNAMIC(CShop, CMUDitem)
IMPLEMENT_DYNAMIC(CRepair, CMUDitem)
IMPLEMENT_DYNAMIC(CHelp, CMUDitem)

#define ROM (m_AreaType == eROM)
#define SMAUG (m_AreaType == eSMAUG)

/////////////////////////////////////////////////////////////////////////////
// CAreaEditorDoc

IMPLEMENT_DYNCREATE(CAreaEditorDoc, CDocument)

BEGIN_MESSAGE_MAP(CAreaEditorDoc, CDocument)
	//{{AFX_MSG_MAP(CAreaEditorDoc)
	ON_COMMAND(ID_FILE_AREA_SUMMARY, OnFileAreaSummary)
	ON_UPDATE_COMMAND_UI(ID_STATUS_MODIFIED, OnUpdateStatusModified)
	ON_COMMAND(ID_AREA_CHECK, OnAreaCheck)
	ON_COMMAND(ID_AREA_RENUMBER, OnAreaRenumber)
	ON_UPDATE_COMMAND_UI(ID_AREA_RENUMBER, OnUpdateAreaRenumber)
	ON_COMMAND(ID_AREA_WALKTHROUGH, OnAreaWalkthrough)
	ON_UPDATE_COMMAND_UI(ID_AREA_WALKTHROUGH, OnUpdateAreaWalkthrough)
	ON_COMMAND(ID_FILE_EXPORT_MUSH, OnFileExportMush)
	ON_UPDATE_COMMAND_UI(ID_FILE_EXPORT_MUSH, OnUpdateFileExportMush)
	ON_COMMAND(ID_VIEW_WARNINGS, OnViewWarnings)
	ON_UPDATE_COMMAND_UI(ID_VIEW_WARNINGS, OnUpdateViewWarnings)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CAreaEditorDoc construction/destruction

CAreaEditorDoc::CAreaEditorDoc()
{
  m_active_view = NULL;
  m_Area = NULL;
  m_leftview = NULL;
  m_iCurrentMobileTab = 0;
  m_iCurrentRoomTab = 0;
  m_iCurrentObjectTab = 0;
  m_iCurrentExitTab = 0;
  m_iCurrentAreaTab = 0;
  m_AreaType = (t_areatype) App.GetProfileInt (sProfilePreferences, sProfileDefaultAreaType, eSMAUG);
  m_Original_AreaType = m_AreaType;
  m_bDoingDelete = false;

}

CAreaEditorDoc::~CAreaEditorDoc()
{

// ========================================================================
// delete all mobs

  for (POSITION mobPos = m_MobList.GetHeadPosition (); mobPos; )
    delete m_MobList.GetNext (mobPos);

  m_MobList.RemoveAll ();   // pointers are deleted, remove list items


// ========================================================================
// delete all objects

  for (POSITION objPos = m_ObjectList.GetHeadPosition (); objPos; )
    delete m_ObjectList.GetNext (objPos);

  m_ObjectList.RemoveAll ();   // pointers are deleted, remove list items

// ========================================================================

// delete all rooms

  for (POSITION roomPos = m_RoomList.GetHeadPosition (); roomPos; )
    delete m_RoomList.GetNext (roomPos);

  m_RoomList.RemoveAll ();   // pointers are deleted, remove list items

// ========================================================================
// delete all resets


  for (POSITION resetPos = m_ResetList.GetHeadPosition (); resetPos; )
    delete m_ResetList.GetNext (resetPos);

  m_ResetList.RemoveAll ();   // pointers are deleted, remove list items

// ========================================================================
// delete all shops

  for (POSITION shopPos = m_ShopList.GetHeadPosition (); shopPos; )
    delete m_ShopList.GetNext (shopPos);

  m_ShopList.RemoveAll ();   // pointers are deleted, remove list items

// ========================================================================
// delete all repairs

  for (POSITION repairPos = m_RepairList.GetHeadPosition (); repairPos; )
    delete m_RepairList.GetNext (repairPos);

  m_RepairList.RemoveAll ();   // pointers are deleted, remove list items

// ========================================================================
// delete all helps

  for (POSITION helpPos = m_HelpList.GetHeadPosition (); helpPos; )
    delete m_HelpList.GetNext (helpPos);

  m_HelpList.RemoveAll ();   // pointers are deleted, remove list items

// ========================================================================
// delete the area object

  delete m_Area;

}   // end of CAreaEditorDoc::~CAreaEditorDoc  (destructor)


BOOL CAreaEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



char CAreaEditorDoc::fread_letter (void)
  {
  return m_FileRead.fread_letter ();
  }   // end of fread_letter

CString CAreaEditorDoc::fread_to_eol (void)
  {
  return m_FileRead.fread_to_eol ();
  }   // end of fread_to_eol

CString CAreaEditorDoc::fread_word (void)
  {
  return m_FileRead.fread_word ();
  } // end of fread_word

CString CAreaEditorDoc::fread_string (const bool bLeftJustify)
  {
  return m_FileRead.fread_string (bLeftJustify);
  } // end of fread_string

CString CAreaEditorDoc::fread_line (void)
  {
  return m_FileRead.fread_line ();
  } // end of fread_line

long CAreaEditorDoc::fread_number (const bool bFlag)
  {
  return m_FileRead.fread_number (bFlag);
  } // end of fread_number

EXT_BV CAreaEditorDoc::fread_bitvector (const bool bFlag)
  {
  return m_FileRead.fread_bitvector (bFlag);
  }

// ========================================================================

void CAreaEditorDoc::load_SMAUG_area (void)
  {

  m_Area->strAreaName = fread_string ();

  } // end of CAreaEditorDoc::load_SMAUG_area

// ========================================================================

void CAreaEditorDoc::load_ROM_area (void)
  {

  m_Area->strFileName	= fread_string ();
  m_Area->strAreaName		= fread_string ();
  m_Area->strAuthor	= fread_string ();
  m_Area->min_vnum	= fread_number ();
  m_Area->max_vnum	= fread_number ();

  } // end of CAreaEditorDoc::load_ROM_area

// ========================================================================

void CAreaEditorDoc::load_area (void)
  {

  if (m_Area)
    ThrowErrorException ("Already have a #AREA declared");

  m_Area = new CArea (RUNTIME_CLASS(CAreaView), this);

  if (SMAUG)
    load_SMAUG_area ();
  else if (ROM)
    load_ROM_area ();
  else
    ThrowErrorException ("Unknown area type: %i", m_AreaType);

  } // end of CAreaEditorDoc::load_area

// ========================================================================

void CAreaEditorDoc::load_author (void)
  {

  if (!m_Area)
    ThrowErrorException ("No #AREA declared");

  m_Area->strAuthor = fread_string ();
  } // end of CAreaEditorDoc::load_author

// ========================================================================

void CAreaEditorDoc::load_version(void)
{

  if (!m_Area)
    ThrowErrorException ("No #AREA declared");

  m_Area->area_version   = fread_number ();
} // end of CAreaEditorDoc::load_version

// ========================================================================

void CAreaEditorDoc::load_climate(void)
{

  if (!m_Area)
    ThrowErrorException ("No #AREA declared");
	
	m_Area->climate_temp    = fread_number ();
	m_Area->climate_precip  = fread_number ();
	m_Area->climate_wind    = fread_number ();
	
} // end of CAreaEditorDoc::load_climate


// ========================================================================

void CAreaEditorDoc::load_neighbour(void)
{

  if (!m_Area)
    ThrowErrorException ("No #AREA declared");
	
	m_Area->neighboursList.AddTail (fread_string ());
	
} // end of CAreaEditorDoc::load_neighbour

// ========================================================================

void CAreaEditorDoc::load_ranges (void)
  {

  if (!m_Area)
    ThrowErrorException ("No #AREA declared");

    int x1, x2, x3, x4;
    CString strLine;

    while (true)
    {
	  strLine = fread_line ();

	  if (strLine [0] == '$')
	    break;

	  x1=x2=x3=x4=0;
	  sscanf( strLine, "%i %i %i %i", &x1, &x2, &x3, &x4 );

	  m_Area->low_soft_range = x1;
	  m_Area->hi_soft_range = x2;
	  m_Area->low_hard_range = x3;
	  m_Area->hi_hard_range = x4;
    }
    return;

  } // end of CAreaEditorDoc::load_ranges

// ========================================================================

void CAreaEditorDoc::load_resetmsg (void)
  {
  if (!m_Area)
    ThrowErrorException ("No #AREA declared");

  m_Area->strResetMsg = fread_string ();
  } // end of CAreaEditorDoc::load_resetmsg

// ========================================================================

void CAreaEditorDoc::load_flags (void)
  {
  if (!m_Area)
    ThrowErrorException ("No #AREA declared");

    int x1, x2;
    CString strLine;
	  strLine = fread_line ();

    x1=x2=0;
    sscanf( strLine, "%i %i", &x1, &x2 );
    m_Area->flags = x1;
    m_Area->reset_frequency = x2;

  } // end of CAreaEditorDoc::load_flags

// ========================================================================

void CAreaEditorDoc::load_economy (void)
  {
  if (!m_Area)
    ThrowErrorException ("No #AREA declared");

  m_Area->high_economy = fread_number ();
  m_Area->low_economy = fread_number ();
  } // end of CAreaEditorDoc::load_economy

// ========================================================================

void CAreaEditorDoc::mprog_read_programs (CMUDitem * item, 
                                          CMUDprogramList & programlist)
  {
CMUDprogram * mprg;
  char        letter;
  bool        done = false;
CString strMessage;

  if (!m_Area)
    ThrowErrorException ("No #AREA declared");

// create first program item and add to mobile list

  mprg = new CMUDprogram (RUNTIME_CLASS(CMUDProgramView), this);
  programlist.AddTail (mprg);

    while ( !done )
  {

    CString strProgramType = fread_word();

    if (!ProgramNameList.FindValue (strProgramType, mprg->type, false))
        ThrowErrorException ("Unknown program type %s in MOB program",
                              (LPCTSTR) strProgramType);

    if (mprg->type == 0)    // IN_FILE_PROG
       ThrowErrorException("Have not implemented IN_FILE_PROG just now");

	  mprg->arglist        = fread_string();
	  fread_to_eol();
	  mprg->comlist        = fread_string(false);
	  fread_to_eol();

    if (CheckCommandSyntax (mprg->comlist, 
                            strMessage,
                            mprg->xref_rooms,
                            mprg->xref_objects,
                            mprg->xref_mobs))
       LoadWarning ("%s: %s",
                    (LPCTSTR) item->Summary (),
                    (LPCTSTR) strMessage);

	  switch ( letter = fread_letter() )
	  {
	    case '>':   // add new program to list
          mprg = new CMUDprogram (RUNTIME_CLASS(CMUDProgramView), this);
          programlist.AddTail (mprg);
	     break;
	    case '|':
	       fread_to_eol();
	       done = true;
	     break;
	    default:
        ThrowErrorException ("MOB program must be followed by \">\" or \"|\"");
	     break;
	  }
  }

  } // end of AreaEditorDoc::mprog_read_programs 

// ========================================================================

void CAreaEditorDoc::load_SMAUG_mobiles (void)
  {
  long vnum;
  CMobile * pMobIndex;
  char letter;
  CString ln;
  int x1, x2, x3, x4, x5, x6, x7;

  if (!m_Area)
    ThrowErrorException ("No #AREA declared");

  letter = fread_letter (); // priming read - end of loop reads another one

  while (true)
    {
    // mob must start with #<mob number>

    if (letter != '#')
        ThrowErrorException ("MOB details must start with a \"#\"");

    vnum = fread_number ();
	  if (vnum == 0)
	      break;    // end of mobiles list

    pMobIndex = new CMobile (RUNTIME_CLASS(CMobileView), this);    // allocate a new mob class thingummy
    m_MobList.AddTail (pMobIndex);    // and add it to our list

  	pMobIndex->vnum			= vnum;

    // update vnum ranges
    if (vnum > m_Area->mob_hi_vnum)
      m_Area->mob_hi_vnum = vnum;
    if (vnum < m_Area->mob_low_vnum)
      m_Area->mob_low_vnum = vnum;

	  pMobIndex->player_name		= fread_string();
	  pMobIndex->short_descr		= fread_string();
	  pMobIndex->long_descr		= fread_string();

    // remove trailing ENDLINE from long description
    if (pMobIndex->long_descr.Right (strlen (ENDLINE)) == ENDLINE)
      pMobIndex->long_descr = pMobIndex->long_descr.Left 
          (pMobIndex->long_descr.GetLength () - 2);

    // long description shouldn't exceed iMaxDescriptionLength characters
    if (pMobIndex->long_descr.GetLength () > iMaxDescriptionLength)
      LoadWarning ("Mob %i description \"%s\" more than %i characters",
                  vnum, 
                  (LPCTSTR) pMobIndex->long_descr,
                  iMaxDescriptionLength);

	  pMobIndex->description		= fread_string(false);

    if (!pMobIndex->long_descr.IsEmpty ())
	    pMobIndex->long_descr.SetAt (0, UPPER(pMobIndex->long_descr[0]));
    if (!pMobIndex->description.IsEmpty ())
  	  pMobIndex->description.SetAt (0, UPPER(pMobIndex->description[0]));

	  pMobIndex->act			= fread_bitvector();  
	  pMobIndex->affected_by		= fread_bitvector();  
	  pMobIndex->alignment		= fread_number();

	  letter				= fread_letter();

	  pMobIndex->level		= fread_number();

	  pMobIndex->mobthac0		= fread_number();
	  pMobIndex->ac			= fread_number();
	  pMobIndex->hitnodice		= fread_number();
	  /* 'd'		*/		  fread_letter();
	  pMobIndex->hitsizedice		= fread_number();
	  /* '+'		*/		  fread_letter();
	  pMobIndex->hitplus		= fread_number();
	  pMobIndex->damnodice		= fread_number();
	  /* 'd'		*/		  fread_letter();
	  pMobIndex->damsizedice		= fread_number();
	  /* '+'		*/		  fread_letter();
	  pMobIndex->damplus		= fread_number();
	  pMobIndex->gold			= fread_number();
	  pMobIndex->exp			= fread_number();
	  pMobIndex->position		= fread_number();
	  pMobIndex->defposition		= fread_number();

	  /*
	   * Back to meaningful values.
	   */
	  pMobIndex->sex			= fread_number();

	  if ( letter != 'S' && letter != 'C' )
      ThrowErrorException ("MOB type must be \"S\" or \"C\"");


	  if ( letter == 'C' ) /* Realms complex mob 	-Thoric */
	    {
	      pMobIndex->perm_str			= fread_number();
	      pMobIndex->perm_int			= fread_number();
	      pMobIndex->perm_wis			= fread_number();
	      pMobIndex->perm_dex			= fread_number();
	      pMobIndex->perm_con			= fread_number();
	      pMobIndex->perm_cha			= fread_number();
	      pMobIndex->perm_lck			= fread_number();
 	      pMobIndex->saving_poison_death	= fread_number();
	      pMobIndex->saving_wand		= fread_number();
	      pMobIndex->saving_para_petri	= fread_number();
	      pMobIndex->saving_breath		= fread_number();
	      pMobIndex->saving_spell_staff	= fread_number();
	      ln = fread_line();
	      x1=x2=x3=x4=x5=x6=x7=0;
	      sscanf( ln, "%i %i %i %i %i %i %i", &x1, &x2, &x3, &x4, &x5, &x6, &x7 );
	      pMobIndex->race		= x1;
	      pMobIndex->mobclass		= x2;
	      pMobIndex->height		= x3;
	      pMobIndex->weight		= x4;
	      pMobIndex->speaks		= x5;
	      pMobIndex->speaking		= x6;
	      pMobIndex->numattacks	= x7;
	      pMobIndex->hitroll		= fread_number();
	      pMobIndex->damroll		= fread_number();
	      pMobIndex->xflags		= fread_number();
	      pMobIndex->resistant	= fread_number();
	      pMobIndex->immune		= fread_number();
	      pMobIndex->susceptible	= fread_number();
	      pMobIndex->attacks		= fread_bitvector();
	      pMobIndex->defenses		= fread_bitvector();
	    }   // end of Realms complex mob
	  else
	    {   // not a Realms complex mob
	      pMobIndex->perm_str		= 13;
	      pMobIndex->perm_dex		= 13;
	      pMobIndex->perm_int		= 13;
	      pMobIndex->perm_wis		= 13;
	      pMobIndex->perm_cha		= 13;
	      pMobIndex->perm_con		= 13;
	      pMobIndex->perm_lck		= 13;
	      pMobIndex->race		= 0;
	      pMobIndex->mobclass		= 3;
	      pMobIndex->xflags		= 0;
	      pMobIndex->resistant	= 0;
	      pMobIndex->immune		= 0;
	      pMobIndex->susceptible	= 0;
	      pMobIndex->numattacks	= 0;
	      pMobIndex->attacks = 0;
	      pMobIndex->defenses = 0;
	      pMobIndex->hitroll		= 0;
	      pMobIndex->damroll		= 0;
        pMobIndex->saving_poison_death = 0;
        pMobIndex->saving_wand		= 0;
        pMobIndex->saving_para_petri= 0;
        pMobIndex->saving_breath		= 0;
        pMobIndex->saving_spell_staff	= 0;
	      pMobIndex->height		= 0;
	      pMobIndex->weight		= 0;
	      pMobIndex->speaks		= 0;
	      pMobIndex->speaking		= 0;

	    }   // end of not a Realms complex mob

    letter = fread_letter();
	  if ( letter == '>' )    // mob program?
      {
	     mprog_read_programs(pMobIndex, pMobIndex->programlist);
  	   letter = fread_letter(); // re-prime read for next time around loop
      }   // end of having a mob program
    
    } // end of processing each mob
  
  } // end of CAreaEditorDoc::load_SMAUG_mobiles

  // ========================================================================

  /*
  OK guys, ROM is so different from SMAUG I thought it would be less
  confusing to do its own section.
  */

void CAreaEditorDoc::load_ROM_mobiles (void)
  {
  long vnum;
  CMobile * pMobIndex;
  char letter;
  CString word;

  if (!m_Area)
    ThrowErrorException ("No #AREA declared");

  letter = fread_letter (); // priming read - end of loop reads another one

  while (true)
    {
    // mob must start with #<mob number>

    if (letter != '#')
        ThrowErrorException ("MOB details must start with a \"#\"");

    vnum = fread_number ();
	  if (vnum == 0)
	      break;    // end of mobiles list

    pMobIndex = new CMobile (RUNTIME_CLASS(CMobileView), this);    // allocate a new mob class thingummy
    m_MobList.AddTail (pMobIndex);    // and add it to our list

  	pMobIndex->vnum			= vnum;

    // update vnum ranges
    if (vnum > m_Area->mob_hi_vnum)
      m_Area->mob_hi_vnum = vnum;
    if (vnum < m_Area->mob_low_vnum)
      m_Area->mob_low_vnum = vnum;

	  pMobIndex->player_name		= fread_string();
	  pMobIndex->short_descr		= fread_string();
	  pMobIndex->long_descr		= fread_string();

    // remove trailing ENDLINE from long description
    if (pMobIndex->long_descr.Right (strlen (ENDLINE)) == ENDLINE)
      pMobIndex->long_descr = pMobIndex->long_descr.Left 
          (pMobIndex->long_descr.GetLength () - 2);

    // long description shouldn't exceed iMaxDescriptionLength characters
    if (pMobIndex->long_descr.GetLength () > iMaxDescriptionLength)
      LoadWarning ("Mob %i description \"%s\" more than %i characters",
                  vnum, 
                  (LPCTSTR) pMobIndex->long_descr,
                  iMaxDescriptionLength);

	  pMobIndex->description		= fread_string(false);

    if (!pMobIndex->long_descr.IsEmpty ())
	    pMobIndex->long_descr.SetAt (0, UPPER(pMobIndex->long_descr[0]));
    if (!pMobIndex->description.IsEmpty ())
  	  pMobIndex->description.SetAt (0, UPPER(pMobIndex->description[0]));

    // ROM race is alpha - lookup race table to convert it

    /* sex */
    word = fread_string();
    if (!MobRaceList.FindValue (word, pMobIndex->race, true))
      LoadWarning ("Mob %i race \"%s\" not in race table",
                  vnum, (LPCTSTR) word);

	  pMobIndex->act			= fread_bitvector(true);   // ROM flag
	  pMobIndex->affected_by		= fread_bitvector(true);   // ROM flag
	  pMobIndex->alignment		= fread_number();
    pMobIndex->group		= fread_number();
	  pMobIndex->level		= fread_number();

    pMobIndex->hitroll  = fread_number ();  

	  /* read hit dice */
    pMobIndex->hitnodice = fread_number();  
    /* 'd'          */                fread_letter(); 
    pMobIndex->hitsizedice 	= fread_number();
    /* '+'          */                fread_letter();   
    pMobIndex->hitplus  = fread_number(); 

 	  /* read mana dice */
	  pMobIndex->mananodice	= fread_number();
					    fread_letter();
	  pMobIndex->manasizedice	= fread_number();
					    fread_letter();
	  pMobIndex->manaplus= fread_number();

	  /* read damage dice */
	  pMobIndex->damnodice	= fread_number();
					    fread_letter();
	  pMobIndex->damsizedice	= fread_number();
					    fread_letter();
	  pMobIndex->damplus	= fread_number();


    /* damage type */
    word = fread_word();
    if (!ObjectAttackList.FindValue (word, pMobIndex->dam_type, true))
      LoadWarning ("Mob %i damage type \"%s\" not in attack table",
                  vnum, (LPCTSTR) word);

	  /* read armor class */
	  pMobIndex->ac_pierce	= fread_number() * 10;
	  pMobIndex->ac_bash		= fread_number() * 10;
	  pMobIndex->ac_slash		= fread_number() * 10;
	  pMobIndex->ac_exotic	= fread_number() * 10;

	  /* read flags and add in data from the race table */
	  pMobIndex->attacks		  = fread_bitvector(true);
	  pMobIndex->immune		    = fread_number(true);
	  pMobIndex->resistant		= fread_number(true);
	  pMobIndex->susceptible	= fread_number(true);

	  /* vital statistics */


    /* position */
    word = fread_word();
    if (!MobPositionList.FindValue (word, pMobIndex->position, true))
      LoadWarning ("Mob %i position \"%s\" not in position table",
                  vnum, (LPCTSTR) word);


    /* position */
    word = fread_word();
    if (!MobPositionList.FindValue (word, pMobIndex->defposition, true))
      LoadWarning ("Mob %i default position \"%s\" not in position table",
                  vnum, (LPCTSTR) word);

    /* sex */
    word = fread_word();
    if (!MobSexList.FindValue (word, pMobIndex->sex, true))
      LoadWarning ("Mob %i sex type \"%s\" not in sex table",
                  vnum, (LPCTSTR) word);

	  pMobIndex->gold		= fread_number();

	  pMobIndex->form			= fread_number(true);  
	  pMobIndex->xflags		= fread_number(true);

    /* size */
    word = fread_word();
    if (!MobSizeList.FindValue (word, pMobIndex->size, true))
      LoadWarning ("Mob %i size type \"%s\" not in size table",
                  vnum, (LPCTSTR) word);

	  pMobIndex->material		= fread_word();

    while (true)
      {
  	  letter = fread_letter();
	
      if ( letter == '>' )    // mob program?
	       mprog_read_programs(pMobIndex, pMobIndex->programlist);
      else
        if (letter == 'F')
          {
          CString strFlagName = fread_word ();
          long vector = fread_number (true);  // get flag

		      if (!str_prefix(strFlagName,"act"))
		          pMobIndex->remove_act |= vector;
          else if (!str_prefix(strFlagName,"aff"))
		          pMobIndex->remove_aff |= vector;
		      else if (!str_prefix(strFlagName,"off"))
		          pMobIndex->remove_off |= vector;
		      else if (!str_prefix(strFlagName,"imm"))
		          pMobIndex->remove_imm |= vector;
		      else if (!str_prefix(strFlagName,"res"))
		          pMobIndex->remove_res |= vector;
		      else if (!str_prefix(strFlagName,"vul"))
		          pMobIndex->remove_vul |= vector;
		      else if (!str_prefix(strFlagName,"for"))
		          pMobIndex->remove_for |= vector;
		      else if (!str_prefix(strFlagName,"par"))
		          pMobIndex->remove_par |= vector;
		      else
            ThrowErrorException ("Flag \"%s\" not found.", 
                (LPCTSTR) strFlagName);
         }
        else
          break;    // not a flag
    
      } // end of looking for flags and things

    } // end of processing each mob
  
  } // end of CAreaEditorDoc::load_ROM_mobiles

// ========================================================================

void CAreaEditorDoc::load_mobiles (void)
  {
  if (ROM)
    load_ROM_mobiles ();
  else if (SMAUG)
    load_SMAUG_mobiles ();
  else
    ThrowErrorException ("Unknown area type: %i", m_AreaType);

  } // end of CAreaEditorDoc::load_mobiles

// ========================================================================

int CAreaEditorDoc::SMAUG_skill_lookup (const char *name)
    {

    if (App.m_SkillList.IsEmpty ())
      ThrowErrorException ("Skills table not loaded - cannot look up skill name");

    for (POSITION skillPos = App.m_SkillList.GetHeadPosition (); skillPos; )
      {
      CSkill * skill = App.m_SkillList.GetNext (skillPos);
			if ( LOWER(name[0]) == LOWER(skill->name[0])
			    &&  !str_prefix( name, skill->name ) )
          return skill->slot;
      }

    return -1;

    }   // end of CAreaEditorDoc::SMAUG_skill_lookup

// ========================================================================

CString CAreaEditorDoc::SMAUG_skill_name (const int iValue,
                                          const bool bNone)
  {
  CSkill * skill;

  if (iValue == -1)
    return bNone ? "NONE" : "";

  for (POSITION skillPos = App.m_SkillList.GetHeadPosition (); skillPos; )
    {
    skill =  App.m_SkillList.GetNext (skillPos);
    if (skill->slot == iValue)
      return skill->name;
    }

  return bNone ? "NONE" : "";

  } // end of SMAUG_skill_name

// ========================================================================

int CAreaEditorDoc::ROM_skill_lookup (const char *name)
    {
int iValue;

    if (ROMSkillNameList.FindValue (name, iValue, true))
      return iValue;

    return -1;

    }   // end of CAreaEditorDoc::ROM_skill_lookup

// ========================================================================

CString CAreaEditorDoc::ROM_skill_name (const int iValue,
                                        const bool bNone)
  {
  CString strName;

  if (iValue == -1)
    return bNone ? "NONE" : "";

  if (ROMSkillNameList.FindName (iValue, strName))
    return strName;

  return bNone ? "NONE" : "";

  } // end of ROM_skill_name

// ========================================================================

CString CAreaEditorDoc::skill_name (const int iValue,
                                    const bool bNone)
  {

  if (ROM)
    return ROM_skill_name (iValue, bNone);
  else if (SMAUG)
    return SMAUG_skill_name (iValue, bNone);
  else
    return bNone ? "NONE" : "";

  } // end of skill_name

// ========================================================================

  void CAreaEditorDoc::load_SMAUG_objects (void)
  {
  long vnum;
  CMUDObject * pObjIndex;
  char letter;
  CString ln;
  int x1, x2, x3, x4, x5, x6;

  if (!m_Area)
    ThrowErrorException ("No #AREA declared");

  letter = fread_letter (); // priming read - end of loop reads another one

  while (true)
    {
    // object must start with #<object number>

    if (letter != '#')
        ThrowErrorException ("Object details must start with a \"#\"");

    vnum = fread_number ();
	  if (vnum == 0)
	      break;    // end of objects list

    pObjIndex = new CMUDObject (RUNTIME_CLASS(CObjectView), this);    // allocate a new mob class thingummy
    m_ObjectList.AddTail (pObjIndex);    // and add it to our list

  	pObjIndex->vnum			= vnum;

    // update vnum ranges
    if (vnum > m_Area->obj_hi_vnum)
      m_Area->obj_hi_vnum = vnum;
    if (vnum < m_Area->obj_low_vnum)
      m_Area->obj_low_vnum = vnum;

	  pObjIndex->name		= fread_string();
	  pObjIndex->short_descr		= fread_string();
	  pObjIndex->description		= fread_string();
	  pObjIndex->action_desc		= fread_string(false);

    if (!pObjIndex->description.IsEmpty ())
  	  pObjIndex->description.SetAt (0, UPPER(pObjIndex->description[0]));


	  pObjIndex->item_type		= fread_number ();
	  pObjIndex->extra_flags		= fread_bitvector();
	  pObjIndex->wear_flags		= fread_bitvector();

    if (!m_FileRead.LineEmpty ())
       pObjIndex->layers = fread_number ();
    else
       pObjIndex->layers = 0;

#if 0
	  ln = fread_line ();
	  x1=0;
	  sscanf( ln, "%i", &x1 );
	  pObjIndex->layers		= x1;
#endif

	  ln = fread_line ();
	  x1=x2=x3=x4=x5=x6=0;
	  sscanf( ln, "%i %i %i %i %i %i",
		  &x1, &x2, &x3, &x4, &x5, &x6 );
	  pObjIndex->value[0]		= x1;
	  pObjIndex->value[1]		= x2;
	  pObjIndex->value[2]		= x3;
	  pObjIndex->value[3]		= x4;
	  pObjIndex->value[4]		= x5;
	  pObjIndex->value[5]		= x6;
	  pObjIndex->weight		= fread_number ();
	  pObjIndex->weight = UMAX( 1, pObjIndex->weight );
	  pObjIndex->cost			= fread_number ();
	  pObjIndex->rent		  	= fread_number (); /* unused */

    if (m_Area->area_version == 1 )
      {
	    switch ( pObjIndex->item_type )
	    {
	    case ITEM_PILL:
	    case ITEM_POTION:
	    case ITEM_SCROLL:
	        pObjIndex->value[1] = SMAUG_skill_lookup ( fread_word ()) ;
	        pObjIndex->value[2] = SMAUG_skill_lookup ( fread_word ()) ;
	        pObjIndex->value[3] = SMAUG_skill_lookup ( fread_word ()) ;
	      break;
	    case ITEM_STAFF:
	    case ITEM_WAND:
	        pObjIndex->value[3] = SMAUG_skill_lookup ( fread_word ()) ;
	      break;
	    case ITEM_SALVE:
	        pObjIndex->value[4] = SMAUG_skill_lookup ( fread_word ()) ;
	        pObjIndex->value[5] = SMAUG_skill_lookup ( fread_word ()) ;
	      break;
	    }   // end of switch on object type
    }   // end of area version not being zero
  
    // look for programs, extras, affects

	  while (true)
	    {
	    letter = fread_letter();

	    if ( letter == 'A' )    // affects
	      {
		    CAffect *paf = new CAffect (RUNTIME_CLASS(CObjectAffectView), this);
        pObjIndex->affectlist.AddTail (paf);
		    paf->location		= fread_number ();
        /*
		    if ( paf->location == APPLY_WEAPONSPELL
		    ||   paf->location == APPLY_WEARSPELL
		    ||   paf->location == APPLY_REMOVESPELL
		    ||   paf->location == APPLY_STRIPSN )
          {
          CSkill * skill = NULL;
          int i = 0;
          int slot =  fread_number ();
          for (skillPos = App.m_SkillList.GetHeadPosition (); skillPos; i++)
            {
            CSkill * skill = App.m_SkillList.GetNext (skillPos);
            if (skill->slot == slot)
              break;
            }
          if (skill)
		        paf->modifier		= i;
          else
            ThrowErrorException ("skill not in skill table");
          }
		    else
        */
		      paf->modifier		= fread_number ();
	      }

      else if ( letter == 'E' )   // extra description
	      {
		    CExtraDescription *ed = new CExtraDescription (RUNTIME_CLASS(CObjectExtraDescriptionView), this);
        pObjIndex->extralist.AddTail (ed);

		    ed->keyword		= fread_string ();
		    ed->description		= fread_string (false);
	      }

      else if ( letter == '>' )   // programs
	      {
	       mprog_read_programs(pObjIndex, pObjIndex->programlist);
	      }   // end of reading programs

      else
  		  break;
	  }   // end of loooking for programs, extras, affects
    
    } // end of processing each object
  
  } // end of CAreaEditorDoc::load_SMAUG_objects

  // ========================================================================

  void CAreaEditorDoc::load_ROM_objects (void)
  {
  long vnum;
  CMUDObject * pObjIndex;
  char letter;
  CString word;

  if (!m_Area)
    ThrowErrorException ("No #AREA declared");

  letter = fread_letter (); // priming read - end of loop reads another one

  while (true)
    {
    // object must start with #<object number>

    if (letter != '#')
        ThrowErrorException ("Object details must start with a \"#\"");

    vnum = fread_number ();
	  if (vnum == 0)
	      break;    // end of objects list

    pObjIndex = new CMUDObject (RUNTIME_CLASS(CObjectView), this);    // allocate a new mob class thingummy
    m_ObjectList.AddTail (pObjIndex);    // and add it to our list

  	pObjIndex->vnum			= vnum;

    // update vnum ranges
    if (vnum > m_Area->obj_hi_vnum)
      m_Area->obj_hi_vnum = vnum;
    if (vnum < m_Area->obj_low_vnum)
      m_Area->obj_low_vnum = vnum;

	  pObjIndex->name		= fread_string();
	  pObjIndex->short_descr		= fread_string();
	  pObjIndex->description		= fread_string();

    if (!pObjIndex->description.IsEmpty ())
  	  pObjIndex->description.SetAt (0, UPPER(pObjIndex->description[0]));

    pObjIndex->material		= fread_string();

    // item type
    word = fread_word();
    if (!ObjectItemList.FindValue (word, pObjIndex->item_type, true))
      LoadWarning ("Object %i item type \"%s\" not in item table",
                  vnum, (LPCTSTR) word);

    pObjIndex->extra_flags          = fread_bitvector (true);
    pObjIndex->wear_flags           = fread_number (true);

  CString word;
  CString strAttackType;

	switch(pObjIndex->item_type)
	{
	case ITEM_WEAPON:

      // weapon lookup
      word = fread_word();
      if (!ObjectWeaponList.FindValue (word, pObjIndex->value[0], true))
        LoadWarning ("Object %i weapon type \"%s\" not in weapon table",
                    vnum, (LPCTSTR) word);

	    pObjIndex->value[1]		= fread_number();
	    pObjIndex->value[2]		= fread_number();

      /* attack lookup */
      word = fread_word();
      if (!ObjectAttackList.FindValue (word, pObjIndex->value[3], true))
        LoadWarning ("Object %i attack type \"%s\" not in attack table",
                    vnum, (LPCTSTR) word);

	    pObjIndex->value[4]		= fread_number (true);
	    break;
	case ITEM_CONTAINER:
	    pObjIndex->value[0]		= fread_number();
	    pObjIndex->value[1]		= fread_number (true);
	    pObjIndex->value[2]		= fread_number();
	    pObjIndex->value[3]		= fread_number();
	    pObjIndex->value[4]		= fread_number();
	    break;
  case ITEM_DRINK_CON:
	case ITEM_FOUNTAIN:
            pObjIndex->value[0]         = fread_number();
            pObjIndex->value[1]         = fread_number();

            // liquid lookup
            word = fread_word();
            if (!ObjectLiquidList.FindValue (word, pObjIndex->value[2], true))
              LoadWarning ("Object %i liquid type \"%s\" not in liquid type table",
                          vnum, (LPCTSTR) word);

            pObjIndex->value[3]         = fread_number();
            pObjIndex->value[4]         = fread_number();
            break;
	case ITEM_WAND:
	case ITEM_STAFF:
	    pObjIndex->value[0]		= fread_number();
	    pObjIndex->value[1]		= fread_number();
	    pObjIndex->value[2]		= fread_number();
	    pObjIndex->value[3]		= ROM_skill_lookup(fread_word());
	    pObjIndex->value[4]		= fread_number();
	    break;
	case ITEM_POTION:
	case ITEM_PILL:
	case ITEM_SCROLL:
 	    pObjIndex->value[0]		= fread_number();
	    pObjIndex->value[1]		= ROM_skill_lookup(fread_word());
	    pObjIndex->value[2]		= ROM_skill_lookup(fread_word());
	    pObjIndex->value[3]		= ROM_skill_lookup(fread_word());
	    pObjIndex->value[4]		= ROM_skill_lookup(fread_word());
	    break;
	default:
      pObjIndex->value[0]    = fread_number (true);
      pObjIndex->value[1]    = fread_number (true);
      pObjIndex->value[2]    = fread_number (true);
      pObjIndex->value[3]    = fread_number (true);
	    pObjIndex->value[4]		 = fread_number (true);
	    break;
	}
	
  pObjIndex->level		= fread_number();
  pObjIndex->weight     = fread_number();
  pObjIndex->cost       = fread_number(); 

  /* condition */
  letter 				= fread_letter();
	switch (letter)
 	{
	    case ('P') :		pObjIndex->condition = 100; break;
	    case ('G') :		pObjIndex->condition =  90; break;
	    case ('A') :		pObjIndex->condition =  75; break;
	    case ('W') :		pObjIndex->condition =  50; break;
	    case ('D') :		pObjIndex->condition =  25; break;
	    case ('B') :		pObjIndex->condition =  10; break;
	    case ('R') :		pObjIndex->condition =   0; break;
	    default:			pObjIndex->condition = 100; break;
	}
 
    // look for programs, extras, affects

	  while (true)
	    {
	    letter = fread_letter();

	    if ( letter == 'A' )    // affects
	      {
		    CAffect *paf = new CAffect (RUNTIME_CLASS(CObjectAffectView), this);
        pObjIndex->affectlist.AddTail (paf);
		    paf->location		= fread_number ();
	      paf->modifier		= fread_number ();
	      } // end of flag A

      else if ( letter == 'F' )   // other sort of affect
        {
		    CAffect *paf = new CAffect (RUNTIME_CLASS(CObjectAffectView), this);
        pObjIndex->affectlist.AddTail (paf);

        letter 			= fread_letter();
        switch (letter)
          {
          case 'A':
            paf->where     = TO_AFFECTS;
            break;
          case 'I':
            paf->where		= TO_IMMUNE;
            break;
          case 'R':
            paf->where		= TO_RESIST;
            break;
          case 'V':
            paf->where		= TO_VULN;
            break;
          default:
            ThrowErrorException( "Load_objects: Bad where '%c' on flag set.", letter );
          }
		    paf->location		= fread_number ();
	      paf->modifier		= fread_bitvector ();
	      paf->bitvector	= fread_bitvector (true);

        } // end of flag F
      else if ( letter == 'E' )   // extra description
	      {
		    CExtraDescription *ed = new CExtraDescription (RUNTIME_CLASS(CObjectExtraDescriptionView), this);
        pObjIndex->extralist.AddTail (ed);

		    ed->keyword		= fread_string ();
		    ed->description		= fread_string (false);
	      }

      else if ( letter == '>' )   // programs
	      {
	       mprog_read_programs(pObjIndex, pObjIndex->programlist);
	      }   // end of reading programs

      else
  		  break;
	  }   // end of loooking for programs, extras, affects
    
    } // end of processing each object
  
  } // end of CAreaEditorDoc::load_ROM_objects

// ========================================================================

void CAreaEditorDoc::load_objects (void)
  {
  if (ROM)
    load_ROM_objects ();
  else if (SMAUG)
    load_SMAUG_objects ();
  else
    ThrowErrorException ("Unknown area type: %i", m_AreaType);

  } // end of CAreaEditorDoc::load_objects


// ========================================================================

  void CAreaEditorDoc::load_SMAUG_rooms (void)
  {
  long vnum;
  CRoom * pRoomIndex;
  char letter;
  CString ln;
  int x1, x2, x3, x4, x5, x6;

  letter = fread_letter (); // priming read - end of loop reads another one

  while (true)
    {
    // room must start with #<object number>

    if (letter != '#')
        ThrowErrorException ("Room details must start with a \"#\"");

    vnum = fread_number ();
	  if (vnum == 0)
	      break;    // end of rooms list

    pRoomIndex = new CRoom (RUNTIME_CLASS(CRoomView), this);    // allocate a new mob class thingummy
    m_RoomList.AddTail (pRoomIndex);    // and add it to our list

  	pRoomIndex->vnum			= vnum;

    // update vnum ranges
    if (vnum > m_Area->room_hi_vnum)
      m_Area->room_hi_vnum = vnum;
    if (vnum < m_Area->room_low_vnum)
      m_Area->room_low_vnum = vnum;

    pRoomIndex->name		= fread_string ();
	  pRoomIndex->description		= fread_string (false);

 
	  ln = fread_line ();
	  x1=x2=x3=x4=x5=x6=0;
	  sscanf( ln, "%i %i %i %i %i %i",
	        &x1, &x2, &x3, &x4, &x5, &x6 );

	  pRoomIndex->room_flags		= x2;
	  pRoomIndex->sector_type		= x3;
	  pRoomIndex->tele_delay		= x4;
	  pRoomIndex->tele_vnum		= x5;
	  pRoomIndex->tunnel		= x6;

    if (!RoomSectorList.FindName (pRoomIndex->sector_type, ln)) 
	    ThrowErrorException( "Fread_rooms: vnum %d has bad sector_type %d.", 
                          vnum ,
	                        pRoomIndex->sector_type);

    // look for programs, extras, doors, maps

	  while (true)
	    {
	    letter = fread_letter();

      if ( letter == 'S' )    // pretty pathetic little flag :)
        {
  	    letter = fread_letter();    // prime for next room
        break;
        }
      else if ( letter == 'D' ) // door (exit)
	      {
		    int door;

		    door = fread_number ();
        CString strName;

		    if (!RoomDirectionList.FindName (door, strName))
		        ThrowErrorException ("Fread_rooms: vnum %d has bad door number %d.", 
                vnum,
		            door );

        CExit *pexit = new CExit (RUNTIME_CLASS(CRoomExitView), this);
        pRoomIndex->exitlist.AddTail (pexit);

		    pexit->description	= fread_string ();
		    pexit->keyword	= fread_string ();
		    pexit->exit_info	= 0;
		    ln = fread_line ();
		    x1=x2=x3=x4=0;
		    sscanf( ln, "%i %i %i %i",
		        &x1, &x2, &x3, &x4 );

		    pexit->exit_info = x1;
		    pexit->key		= x2;
		    pexit->vnum		= x3;
		    pexit->vdir		= door;
		    pexit->distance	= x4;

        // amend exit info slightly
		    switch ( pexit->exit_info )
		    {
		      case 1:  pexit->exit_info = EX_ISDOOR;                break;
		      case 2:  pexit->exit_info = EX_ISDOOR | EX_PICKPROOF; break;
		    }

	      }   // end of type D - door (exit)

      else if ( letter == 'E' ) // extra description
	      {
		    CExtraDescription *ed = new CExtraDescription (RUNTIME_CLASS(CObjectExtraDescriptionView), this);
        pRoomIndex->extralist.AddTail (ed);

		    ed->keyword		= fread_string ();
		    ed->description		= fread_string (false);
	      }   // end of type E - extra description

      else if ( letter == 'M' ) // map
	      {
		    CRoomMap *map = new CRoomMap (RUNTIME_CLASS(CRoomMapView), this);
        pRoomIndex->maplist.AddTail (map);

        map->vnum                     = fread_number ();
        map->x                        = fread_number (); 
        map->y                        = fread_number ();
        map->entry		      = fread_letter (); 

	      }   // end of type M - map

      else if ( letter == '>' )   // programs
	      {
	       mprog_read_programs(pRoomIndex, pRoomIndex->programlist);
	      } // end of reading programs

      else
  		  break;
	  }   // end of loooking for programs, extras, doors, maps
    
    } // end of processing each room
  
  } // end of CAreaEditorDoc::load_SMAUG_rooms

  // ========================================================================

  void CAreaEditorDoc::load_ROM_rooms (void)
  {
  long vnum;
  CRoom * pRoomIndex;
  char letter;
  CString ln;

  letter = fread_letter (); // priming read - end of loop reads another one

  while (true)
    {
    // room must start with #<object number>

    if (letter != '#')
        ThrowErrorException ("Room details must start with a \"#\"");

    vnum = fread_number ();
	  if (vnum == 0)
	      break;    // end of rooms list

    pRoomIndex = new CRoom (RUNTIME_CLASS(CRoomView), this);    // allocate a new mob class thingummy
    m_RoomList.AddTail (pRoomIndex);    // and add it to our list

  	pRoomIndex->vnum			= vnum;

    // update vnum ranges
    if (vnum > m_Area->room_hi_vnum)
      m_Area->room_hi_vnum = vnum;
    if (vnum < m_Area->room_low_vnum)
      m_Area->room_low_vnum = vnum;

    pRoomIndex->name		= fread_string ();
	  pRoomIndex->description		= fread_string (false);

 
	  /* Area number */		  fread_number();
	  pRoomIndex->room_flags		= fread_number(true);
	  pRoomIndex->sector_type		= fread_number();

    // look for programs, extras, doors, maps

	  while (true)
	    {
	    letter = fread_letter();

      if ( letter == 'S' )    // pretty pathetic little flag :)
        {
  	    letter = fread_letter();    // prime for next room
        break;
        }
      else  if ( letter == 'H') /* healing room */
        pRoomIndex->heal_rate = fread_number();
      
      else if ( letter == 'M') /* mana room */
        pRoomIndex->mana_rate = fread_number();
      
      else if ( letter == 'C') /* clan */
        {
        if (!pRoomIndex->clan.IsEmpty ())
          ThrowErrorException ("Load_rooms: duplicate clan fields.");
        pRoomIndex->clan = fread_string();
        }

      else if ( letter == 'D' ) // door (exit)
	      {
		    int door;

		    door = fread_number ();
        CString strName;

		    if (!RoomDirectionList.FindName (door, strName))
		        ThrowErrorException ("Fread_rooms: vnum %d has bad door number %d.", 
                vnum,
		            door );

        CExit *pexit = new CExit (RUNTIME_CLASS(CRoomExitView), this);
        pRoomIndex->exitlist.AddTail (pexit);

		    pexit->description	= fread_string();
		    pexit->keyword		= fread_string();
		    pexit->exit_info = fread_bitvector();
		    pexit->key		= fread_number();
		    pexit->vnum		= fread_number();
		    pexit->vdir		= door;

		    switch ( pexit->exit_info )
		      {
		    case 1: pexit->exit_info = ROM_EX_ISDOOR;                break;
		    case 2: pexit->exit_info = ROM_EX_ISDOOR | ROM_EX_PICKPROOF; break;
		    case 3: pexit->exit_info = ROM_EX_ISDOOR | ROM_EX_NOPASS;    break;
		    case 4: pexit->exit_info = ROM_EX_ISDOOR|ROM_EX_NOPASS|ROM_EX_PICKPROOF;
			    break;
		      }

	      }   // end of type D - door (exit)

      else if ( letter == 'E' ) // extra description
	      {
		    CExtraDescription *ed = new CExtraDescription (RUNTIME_CLASS(CObjectExtraDescriptionView), this);
        pRoomIndex->extralist.AddTail (ed);

		    ed->keyword		= fread_string ();
		    ed->description		= fread_string (false);
	      }   // end of type E - extra description

      else if (letter == 'O')
        {
        if (!pRoomIndex->owner.IsEmpty ())
		        ThrowErrorException ("Load_rooms: duplicate owner.");
        
        pRoomIndex->owner = fread_string();
        }

      else if ( letter == '>' )   // programs
	      {
	       mprog_read_programs(pRoomIndex, pRoomIndex->programlist);
	      } // end of reading programs

      else
  		  break;
	  }   // end of loooking for programs, extras, doors, maps
    
    } // end of processing each room
  
  } // end of CAreaEditorDoc::load_ROM_rooms

  // ========================================================================

  void CAreaEditorDoc::load_rooms (void)
  {

  if (!m_Area)
    ThrowErrorException ("No #AREA declared");

  if (SMAUG)
    load_SMAUG_rooms ();
  else if (ROM)
    load_ROM_rooms ();
  else
    ThrowErrorException ("Unknown area type: %i", m_AreaType);

  } // end of CAreaEditorDoc::load_rooms

// ========================================================================

  void CAreaEditorDoc::load_resets (void)
  {
  CRoom * pRoomIndex;
  CExit *pexit;
  CReset *reset;
  char letter;
	int extra, arg1, arg2, arg3, arg4;
  bool not01 = FALSE;
  CString strComment;

  if (!m_Area)
    ThrowErrorException ("No #AREA declared");

  while (true)
    {

	  if ( ( letter = fread_letter() ) == 'S' )
	      break;

	  if ( letter == '*' )
	  {
	      fread_to_eol();
	      continue;
	  }

	  extra	= fread_number();
	  arg1	= fread_number();
	  arg2	= fread_number();
	  arg3	= (letter == 'G' || letter == 'R')
		    ? 0 : fread_number();

    // ROM sometimes reads a 4th argument
    if (ROM)
	    arg4	= (letter == 'P' || letter == 'M')
			        ? fread_number() : 0;
    else
      arg4 = 0;

		strComment = fread_to_eol();

    strComment.TrimLeft ();
    strComment.TrimRight ();

    letter = toupper (letter);

	  /*
	   * Validate parameters.
	   * We're calling the index functions for the side effect.
	   */
	  switch ( letter )
	  {
	  default:
        ThrowErrorException( "Load_resets: bad command '%c'.",  letter );
	      return;

	  case 'M':
	      if ( FindMob ( arg1 ) == NULL)
		      LoadWarning( "Load_resets: 'M': mobile %d not in area.",
		       arg1 );
	      if ( FindRoom ( arg3 ) == NULL)
		      LoadWarning( "Load_resets: 'M': room %d not in area.",
		       arg3 );
	      break;

	  case 'O':
	      if ( FindObj(arg1) == NULL)
		      LoadWarning( "Load_resets: '%c': object %d not in area.",
		       letter, arg1 );
	      if ( FindRoom (arg3) == NULL)
		      LoadWarning( "Load_resets: '%c': room %d not in area.",
		       letter, arg3 );
	      break;

	  case 'P':
	      if ( FindObj(arg1) == NULL)
		      LoadWarning( "Load_resets: '%c': object %d not in area.",
		       letter, arg1 );
	      if ( arg3 > 0 )
		  if ( FindObj(arg3) == NULL)
		      LoadWarning( "Load_resets: 'P': destination object %d not in area.",
			   arg3 );
	      else if ( extra > 1 )
	        not01 = TRUE;
	      break;

	  case 'G':
	  case 'E':
	      if ( FindObj(arg1) == NULL)
		      LoadWarning( "Load_resets: '%c': object %d not in area.",
		       letter, arg1 );
	      break;

	  case 'T':
	      break;

	  case 'H':
	      if ( arg1 > 0 )
		      if ( FindObj(arg1) == NULL)
		          LoadWarning( "Load_resets: 'H': object %d not in area.",
			   arg1 );
	      break;

	  case 'D':
	      pRoomIndex = FindRoom ( arg1 );
	      if ( !pRoomIndex )
	      {
		     LoadWarning( "Load_resets: 'D': room %d not in area.",
			     arg1 );
		    break;
	      }

        if (!RoomDirectionList.IsValueInList (arg2))
          {
   
		       LoadWarning( "Load_resets: 'D': exit %d direction is not valid.",
			                   arg2 );
           break;

          }

	      if ((pexit = get_exit(pRoomIndex, arg2)) == NULL)
	      {
		     LoadWarning( "Load_resets: 'D': exit %d does not exist.",
			                 arg2 );
         break;
	      }

	      if (!IS_SET( pexit->exit_info, EX_ISDOOR ) )
	      {
		     LoadWarning( "Load_resets: 'D': exit %d not door.",
			                 arg2 );
         break;
	      }

	      if ( arg3 < 0 || arg3 > 2 )
	      {
		    LoadWarning( "Load_resets: 'D': bad 'locks': %d.",
			   arg3 );
	      }
	      break;

	  case 'R':
	      pRoomIndex = FindRoom ( arg1 );
	      if ( !pRoomIndex)
		  LoadWarning( "Load_resets: 'R': room %d not in area.",
		       arg1 );

	      if ( arg2 < 0 || arg2 > 6 )
	      {
		    LoadWarning( "Load_resets: 'R': bad exit %d.",
			   arg2 );
		  break;
	      }

	      break;
	  }

    reset = new CReset (RUNTIME_CLASS(CResetView), this);
    m_ResetList.AddTail (reset);

    reset->command = letter;
    reset->extra = extra;
    reset->arg1 = arg1;
    reset->arg2 = arg2;
    reset->arg3 = arg3;
    reset->arg4 = arg4;
    reset->strComment = strComment;
    
    } // end of processing each reset
  
  } // end of CAreaEditorDoc::load_resets

  // ========================================================================

  void CAreaEditorDoc::load_shops (void)
  {
  long vnum;

  CShop *pShop;

  CMobile *pMobIndex;
	int iTrade;

  if (!m_Area)
    ThrowErrorException ("No #AREA declared");

  while (true)
    {

    vnum = fread_number ();
	  if (vnum == 0)
	      break;    // end of shops list

    pShop = new CShop (RUNTIME_CLASS(CShopView), this);    // allocate a new mob class thingummy
    m_ShopList.AddTail (pShop);    // and add it to our list

  	pShop->keeper			= vnum;


	  for ( iTrade = 0; iTrade < MAX_TRADE; iTrade++ )
	      pShop->buy_type[iTrade]	= fread_number ();
	  pShop->profit_buy	= fread_number ();
	  pShop->profit_sell	= fread_number ();
	  pShop->open_hour	= fread_number ();
	  pShop->close_hour	= fread_number ();
				    fread_to_eol ();
	  pMobIndex		= FindMob ( pShop->keeper );
    if (!pMobIndex)
		  LoadWarning( "Load_shops: Mobile %i is not defined.", pShop->keeper );

    }   // end of processing each shop

  } // end of CAreaEditorDoc::load_shops

  // ========================================================================

  void CAreaEditorDoc::load_repairs (void)
  {
  long vnum;

  CRepair *rShop;

  CMobile *pMobIndex;
	int iFix;

  if (!m_Area)
    ThrowErrorException ("No #AREA declared");

  while (true)
    {

    vnum = fread_number ();
	  if (vnum == 0)
	      break;    // end of repairs list

    rShop = new CRepair (RUNTIME_CLASS(CRepairView), this);    // allocate a new mob class thingummy
    m_RepairList.AddTail (rShop);    // and add it to our list

  	rShop->keeper			= vnum;


	for ( iFix = 0; iFix < MAX_FIX; iFix++ )
	  rShop->fix_type[iFix] = fread_number ();
	rShop->profit_fix	= fread_number ();
	rShop->shop_type	= fread_number ();
	rShop->open_hour	= fread_number ();
	rShop->close_hour	= fread_number ();
				  fread_to_eol ();
	pMobIndex		= FindMob ( rShop->keeper );
	
  if (!pMobIndex)
		LoadWarning( "Load_repairs: Mobile %i is not defined.", rShop->keeper );

    }   // end of processing each repair

  } // end of CAreaEditorDoc::load_repairs

 // ========================================================================

  void CAreaEditorDoc::load_specials (void)
  {

  int vnum;
  CMobile *pMobIndex;

  if (!m_Area)
    ThrowErrorException ("No #AREA declared");

  while (true)
    {

	  char letter;

	  switch ( letter = fread_letter () )
	  {
	  default:
	      ThrowErrorException( "Load_specials: letter '%c' not *, M, or S.", letter );

	  case 'S':
	      return;

	  case '*':
	      break;

	  case 'M':

        vnum = fread_number  ();
	      pMobIndex		= FindMob	(vnum );

        if (!pMobIndex)
		        ThrowErrorException ("Load_specials: mob %i is not in area.", 
                vnum);
        
        CString strFunction;

        strFunction = fread_word    ();
		    if (!MobSpecialList.FindValue (strFunction, pMobIndex->spec_fun, false))
		        ThrowErrorException ("Load_specials: mob %i special function %s does not exist.", 
                                vnum,
		                            (LPCTSTR) strFunction );

	      break;
	  }

	  fread_to_eol ();
    }   // end of processing each special

  } // end of CAreaEditorDoc::load_specials

  // ========================================================================

  void CAreaEditorDoc::load_helps (void)
  {

  CHelp *pHelp;

  int iLevel;
  CString strKeyword;
  CString strText;

  while (true)
    {

	  iLevel	= fread_number ();
	  strKeyword	= fread_string ();
	  if (strKeyword.Left (1) == "$" )
	      break;

	  strText	= fread_string (false);

    if (strKeyword.IsEmpty ())
      continue;

    pHelp = new CHelp (RUNTIME_CLASS(CHelpView), this);    // allocate a new help item
    m_HelpList.AddTail (pHelp);    // and add it to our list

	  pHelp->level	= iLevel;
	  pHelp->keyword	= strKeyword;
	  pHelp->text	= strText;

    }   // end of processing each help

  } // end of CAreaEditorDoc::load_helps

// ========================================================================

void CAreaEditorDoc::fwrite_string (const char * s)
  {
  m_FileWrite.fwrite_string (s);
  } // end of CAreaEditorDoc::fwrite_string

// ========================================================================

void CAreaEditorDoc::save_SMAUG_area (void)
  {
  fwrite_string (CFormat ("#AREA %s~", (LPCTSTR) m_Area->strAreaName));
  fwrite_string (""); // blank line

  // version number and climate only apply to version 1 onwards
  if (m_Area->area_version)
    {
    // version number
    fwrite_string (CFormat ("#VERSION %i", m_Area->area_version));
    fwrite_string (""); // blank line

    // climate details
    fwrite_string (CFormat ("#CLIMATE %i %i %i", 
                  m_Area->climate_temp,  
                  m_Area->climate_precip,
                  m_Area->climate_wind   
                  ));
    fwrite_string (""); // blank line

    // neighbours
    for (POSITION pos = m_Area->neighboursList.GetHeadPosition (); pos; )
      {
      CString strNeighbour = m_Area->neighboursList.GetNext (pos);
      fwrite_string (CFormat ("#NEIGHBOR %s~", (LPCTSTR) strNeighbour));
      } // end of writing out neighhours
    if (!m_Area->neighboursList.IsEmpty ())
      fwrite_string (""); // blank line

    }   // end of not version zero
  
  // author
  fwrite_string (CFormat ("#AUTHOR %s~", (LPCTSTR) m_Area->strAuthor));
  fwrite_string (""); // blank line

  // ranges
  fwrite_string ("#RANGES");
  fwrite_string (CFormat ("%i %i %i %i", 	  
                          m_Area->low_soft_range,
	                        m_Area->hi_soft_range,
	                        m_Area->low_hard_range, 
	                        m_Area->hi_hard_range));
  fwrite_string ("$"); // end of ranges
  fwrite_string (""); // blank line

  // reset msg
  fwrite_string (CFormat ("#RESETMSG %s~", (LPCTSTR) m_Area->strResetMsg));
  fwrite_string (""); // blank line

  // flags
  fwrite_string ("#FLAGS");
  fwrite_string (CFormat ("%s %i", 	  
                          (LPCTSTR) print_bitvector (m_Area->flags),
	                        m_Area->reset_frequency));
  fwrite_string (""); // blank line

  // economy
  fwrite_string (CFormat ("#ECONOMY %i %i", 	  
                          m_Area->high_economy,
	                        m_Area->low_economy));

  } // end of CAreaEditorDoc::save_SMAUG_area

// ========================================================================

void CAreaEditorDoc::save_ROM_area (void)
  {
  fwrite_string ("#AREA");

  // for SMAUG to ROM conversion ...
  // if filename is empty - use document title which should be file name anyway
  if (m_Area->strFileName.IsEmpty ())
    m_Area->strFileName = GetTitle ();

  m_Area->max_vnum = 0;
  m_Area->min_vnum = INT_MAX;

  // update vnum ranges
  if (m_Area->max_vnum < m_Area->mob_hi_vnum)
    m_Area->max_vnum = m_Area->mob_hi_vnum;
  if (m_Area->min_vnum > m_Area->mob_low_vnum)
    m_Area->min_vnum = m_Area->mob_low_vnum;

  if (m_Area->max_vnum < m_Area->obj_hi_vnum)
    m_Area->max_vnum = m_Area->obj_hi_vnum;
  if (m_Area->min_vnum > m_Area->obj_low_vnum)
    m_Area->min_vnum = m_Area->obj_low_vnum;

  if (m_Area->max_vnum < m_Area->room_hi_vnum)
    m_Area->max_vnum = m_Area->room_hi_vnum;
  if (m_Area->min_vnum > m_Area->room_low_vnum)
    m_Area->min_vnum = m_Area->room_low_vnum;

  fwrite_string (CFormat ("%s~", (LPCTSTR) m_Area->strFileName));
  fwrite_string (CFormat ("%s~", (LPCTSTR) m_Area->strAreaName));
  fwrite_string (CFormat ("%s~", (LPCTSTR) m_Area->strAuthor));
  fwrite_string (CFormat ("%i %i", m_Area->min_vnum, m_Area->max_vnum));
  } // end of CAreaEditorDoc::save_ROM_area


// ========================================================================

void CAreaEditorDoc::save_area (void)
  {

  if (SMAUG)
    save_SMAUG_area ();
  else if (ROM)
    save_ROM_area ();
  else
    ThrowErrorException ("Unknown area type: %i", m_AreaType);
  
  fwrite_string (""); // blank line

  } // end of CAreaEditorDoc::save_area


// ========================================================================

void CAreaEditorDoc::save_programs (CMUDprogramList & programlist)
    {

  if (programlist.IsEmpty ())
    return;   // no programs, just exit

POSITION progPos;
CMUDprogram * prog;

  // save all programs

  for (progPos = programlist.GetHeadPosition (); progPos; )
    {
    prog = programlist.GetNext (progPos);

    fwrite_string (CFormat ("> %s %s~",
                            (LPCTSTR) ProgramNameList.ReturnName (prog->type, false),
                            (LPCTSTR) prog->arglist));

   fwrite_string (CFormat ("%s~", (LPCTSTR) prog->comlist));

    }   // end of each program

  fwrite_string ("|");    // program terminator

  }   // end of CAreaEditorDoc::save_programs

// ========================================================================

void CAreaEditorDoc::save_SMAUG_mobiles (void)
  {

POSITION mobPos;
CMobile * mob;

// cycle through all mobiles

for (mobPos = m_MobList.GetHeadPosition (); mobPos; )
  {
  mob = m_MobList.GetNext (mobPos);

  DoSaveMilestone ();

  fwrite_string (CFormat ("#%i", mob->vnum));
  fwrite_string (CFormat ("%s~", (LPCTSTR) mob->player_name));
  fwrite_string (CFormat ("%s~", (LPCTSTR) mob->short_descr));
  fwrite_string (CFormat ("%s" ENDLINE "~", (LPCTSTR) mob->long_descr));
  fwrite_string (CFormat ("%s~", (LPCTSTR) mob->description));
  fwrite_string (CFormat ("%s %s %i C", (LPCTSTR) print_bitvector (mob->act),
                                        (LPCTSTR) print_bitvector (mob->affected_by),
                                        mob->alignment));

  fwrite_string (CFormat ("%i %i %i %id%i+%i %id%i+%i", 
                mob->level,
                mob->mobthac0,
                mob->ac,
                mob->hitnodice,
                mob->hitsizedice,
                mob->hitplus,
                mob->damnodice,
                mob->damsizedice,
                mob->damplus));

  fwrite_string (CFormat ("%i %i", mob->gold,
                                   mob->exp));

  fwrite_string (CFormat ("%i %i %i", mob->position,
                                      mob->defposition,
                                      mob->sex));


  fwrite_string (CFormat ("%i %i %i %i %i %i %i", 
                mob->perm_str,
                mob->perm_int,
                mob->perm_wis,
                mob->perm_dex,
                mob->perm_con,
                mob->perm_cha,
                mob->perm_lck));

  fwrite_string (CFormat ("%i %i %i %i %i", 
                mob->saving_poison_death,
                mob->saving_wand,
                mob->saving_para_petri,
                mob->saving_breath,
                mob->saving_spell_staff));

  fwrite_string (CFormat ("%i %i %i %i %s %s %i", 
                mob->race,
                mob->mobclass,
                mob->height,
                mob->weight,
                (LPCTSTR) print_bitvector (mob->speaks),
                (LPCTSTR) print_bitvector (mob->speaking),
                mob->numattacks));

  fwrite_string (CFormat ("%i %i %s %s %s %s %s %s", 
                mob->hitroll,
                mob->damroll,
                (LPCTSTR) print_bitvector (mob->xflags),
                (LPCTSTR) print_bitvector (mob->resistant),
                (LPCTSTR) print_bitvector (mob->immune),
                (LPCTSTR) print_bitvector (mob->susceptible),
                (LPCTSTR) print_bitvector (mob->attacks),
                (LPCTSTR) print_bitvector (mob->defenses)));

  // now do all programs inside mobile

  save_programs (mob->programlist);

  } // end of each mobile


  } // end of CAreaEditorDoc::save_SMAUG_mobiles

// ========================================================================

void CAreaEditorDoc::save_ROM_mobiles (void)
  {

POSITION mobPos;
CMobile * mob;

// cycle through all mobiles

for (mobPos = m_MobList.GetHeadPosition (); mobPos; )
  {
  mob = m_MobList.GetNext (mobPos);

  DoSaveMilestone ();

  fwrite_string (CFormat ("#%i", mob->vnum));
  fwrite_string (CFormat ("%s~", (LPCTSTR) mob->player_name));
  fwrite_string (CFormat ("%s~", (LPCTSTR) mob->short_descr));
  fwrite_string (CFormat ("%s" ENDLINE "~", (LPCTSTR) mob->long_descr));
  fwrite_string (CFormat ("%s~", (LPCTSTR) mob->description));

  if (!MobRaceList.IsValueInList (mob->race))
    Warning (mob, 
            "Race %i not in race list, defaulting to first one",
            mob->race);

  fwrite_string (CFormat ("%s~", (LPCTSTR) MobRaceList.ReturnName (mob->race)));

  fwrite_string (CFormat ("%s %s %i %i", (LPCTSTR) ConvertROMFlag (mob->act),
                                         (LPCTSTR) ConvertROMFlag (mob->affected_by),
                                         mob->alignment,
                                         mob->group));

  if (!ObjectAttackList.IsValueInList (mob->dam_type))
    Warning (mob, 
            "Attack type %i not in attack list, defaulting to first one",
            mob->dam_type);

  fwrite_string (CFormat ("%i %i %id%i+%i %id%i+%i %id%i+%i %s", 
                mob->level,
                mob->hitroll,
                mob->hitnodice,
                mob->hitsizedice,
                mob->hitplus,
                mob->mananodice,
                mob->manasizedice,
                mob->manaplus,
                mob->damnodice,
                mob->damsizedice,
                mob->damplus,
                (LPCTSTR) ObjectAttackList.ReturnName (mob->dam_type)));

  fwrite_string (CFormat ("%i %i %i %i", mob->ac_pierce / 10,
                                         mob->ac_bash / 10,
                                         mob->ac_slash / 10,
                                         mob->ac_exotic / 10));


  fwrite_string (CFormat ("%s %s %s %s", (LPCTSTR) ConvertROMFlag (mob->attacks),
                                         (LPCTSTR) ConvertROMFlag (mob->immune),
                                         (LPCTSTR) ConvertROMFlag (mob->resistant),
                                         (LPCTSTR) ConvertROMFlag (mob->susceptible)));

  if (!MobPositionList.IsValueInList (mob->position))
    Warning (mob, 
            "Position %i not in position list, defaulting to first one",
            mob->position);

  if (!MobPositionList.IsValueInList (mob->defposition))
    Warning (mob, 
            "Default position %i not in position list, defaulting to first one",
            mob->defposition);

  if (!MobSexList.IsValueInList (mob->sex))
    Warning (mob, 
            "Sex %i not in sex list, defaulting to first one",
            mob->sex);

  fwrite_string (CFormat ("%s %s %s %i", 
                          (LPCTSTR) MobPositionList.ReturnName (mob->position),
                          (LPCTSTR) MobPositionList.ReturnName (mob->defposition),
                          (LPCTSTR) MobSexList.ReturnName (mob->sex),
                          mob->gold));

  // for SMAUG to ROM conversion - material cannot be empty
  if (mob->material.IsEmpty ())
    mob->material = "0";

  if (!MobSizeList.IsValueInList (mob->size))
    Warning (mob, 
            "Size %i not in size list, defaulting to first one",
            mob->size);

  fwrite_string (CFormat ("%s %s %s %s", (LPCTSTR) ConvertROMFlag (mob->form),
                                         (LPCTSTR) ConvertROMFlag (mob->xflags),
                                         (LPCTSTR) MobSizeList.ReturnName (mob->size),
                                         (LPCTSTR) mob->material));

  // save "remove" flags

  if (mob->remove_act)
    fwrite_string (CFormat ("F act %s", 
                   (LPCTSTR) ConvertROMFlag (mob->remove_act)));
  if (mob->remove_aff)
    fwrite_string (CFormat ("F aff %s", 
                   (LPCTSTR) ConvertROMFlag (mob->remove_aff)));
  if (mob->remove_off)
    fwrite_string (CFormat ("F off %s", 
                   (LPCTSTR) ConvertROMFlag (mob->remove_off)));
  if (mob->remove_imm)
    fwrite_string (CFormat ("F imm %s", 
                   (LPCTSTR) ConvertROMFlag (mob->remove_imm)));
  if (mob->remove_res)
    fwrite_string (CFormat ("F res %s", 
                   (LPCTSTR) ConvertROMFlag (mob->remove_res)));
  if (mob->remove_vul)
    fwrite_string (CFormat ("F vul %s", 
                   (LPCTSTR) ConvertROMFlag (mob->remove_vul)));
  if (mob->remove_for)
    fwrite_string (CFormat ("F for %s", 
                   (LPCTSTR) ConvertROMFlag (mob->remove_for)));
  if (mob->remove_par)
    fwrite_string (CFormat ("F par %s", 
                   (LPCTSTR) ConvertROMFlag (mob->remove_par)));

  // now do all programs inside mobile if wanted

  if (App.GetProfileInt (sProfilePreferences, sProfileSaveROMPrograms, 0))
    save_programs (mob->programlist);

  } // end of each mobile


  } // end of CAreaEditorDoc::save_ROM_mobiles

// ========================================================================

void CAreaEditorDoc::save_mobiles (void)
  {
  if (m_MobList.IsEmpty ())
    return;

  fwrite_string ("#MOBILES");

  if (SMAUG)
    save_SMAUG_mobiles ();
  else if (ROM)
    save_ROM_mobiles ();
  else
    ThrowErrorException ("Unknown area type: %i", m_AreaType);

  fwrite_string ("#0");    // mobiles terminator
  fwrite_string (""); // blank line

  } // end of CAreaEditorDoc::save_mobiles

// ========================================================================

void CAreaEditorDoc::save_SMAUG_objects (void)
  {

POSITION objPos;
CMUDObject * obj;

POSITION affectPos;
CAffect * affect;

POSITION extraPos;
CExtraDescription * extra;

// cycle through all objects

for (objPos = m_ObjectList.GetHeadPosition (); objPos; )
  {
  obj = m_ObjectList.GetNext (objPos);

  DoSaveMilestone ();

  fwrite_string (CFormat ("#%i", obj->vnum));
  fwrite_string (CFormat ("%s~", (LPCTSTR) obj->name));
  fwrite_string (CFormat ("%s~", (LPCTSTR) obj->short_descr));
  fwrite_string (CFormat ("%s~", (LPCTSTR) obj->description));
  fwrite_string (CFormat ("%s~", (LPCTSTR) obj->action_desc));

  fwrite_string (CFormat ("%i %s %s %i", 
                obj->item_type,
                (LPCTSTR) print_bitvector (obj->extra_flags),
                (LPCTSTR) print_bitvector (obj->wear_flags),
                obj->layers));


	int val0 = obj->value[0];
	int val1 = obj->value[1];
	int val2 = obj->value[2];
	int val3 = obj->value[3];
	int val4 = obj->value[4];
	int val5 = obj->value[5];

  if (m_Area->area_version)
	  switch ( obj->item_type )
	  {
	  case ITEM_PILL:
	  case ITEM_POTION:
	  case ITEM_SCROLL:
      val1 = HAS_SPELL_INDEX;
      val2 = HAS_SPELL_INDEX;
      val3 = HAS_SPELL_INDEX;
	    break;
	  case ITEM_STAFF:
	  case ITEM_WAND:
      val3 = HAS_SPELL_INDEX;
	    break;
	  case ITEM_SALVE:
      val4 = HAS_SPELL_INDEX;
      val5 = HAS_SPELL_INDEX;
      break;
	  }

	if ( val4 || val5 )
    fwrite_string (CFormat ("%i %i %i %i %i %i", 
                  val0,
                  val1,
                  val2,
                  val3,
                  val4,
                  val5));
  else
    fwrite_string (CFormat ("%i %i %i %i", 
                  val0,
                  val1,
                  val2,
                  val3));

  fwrite_string (CFormat ("%i %i %i", obj->weight,
                                      obj->cost,
                                      obj->rent));


  // we write out spell names in version 1 upwards
  if (m_Area->area_version)
    {
	    switch ( obj->item_type )
	    {
	    case ITEM_PILL:
	    case ITEM_POTION:
	    case ITEM_SCROLL:
          fwrite_string (CFormat ("'%s' '%s' '%s'", 
                          (LPCTSTR) skill_name (obj->value[1], true),
                          (LPCTSTR) skill_name (obj->value[2], true),
                          (LPCTSTR) skill_name (obj->value[3], true)));

	      break;
	    case ITEM_STAFF:
	    case ITEM_WAND:
          fwrite_string (CFormat ("'%s'", 
                          (LPCTSTR) skill_name (obj->value[3], true)));
	      break;
	    case ITEM_SALVE:
          fwrite_string (CFormat ("'%s' '%s'", 
                          (LPCTSTR) skill_name (obj->value[4], true),
                          (LPCTSTR) skill_name (obj->value[5], true)));
	      break;
	    }   // end of switch on object type


    }   // end of version not being zero

    // now do all programs, extras, affects inside the object

  // Extra descriptions first ...

  for (extraPos = obj->extralist.GetHeadPosition (); extraPos; )
    {
    extra = obj->extralist.GetNext (extraPos);

    fwrite_string ("E");    // Extra description flag
    fwrite_string (CFormat ("%s~", (LPCTSTR) extra->keyword));
    fwrite_string (CFormat ("%s~", (LPCTSTR) extra->description));
    }
  
  // Affects next ...

  for (affectPos = obj->affectlist.GetHeadPosition (); affectPos; )
    {
    affect = obj->affectlist.GetNext (affectPos);

    fwrite_string ("A");    // Affects flag
    fwrite_string (CFormat ("%i %i", affect->location,
                                        affect->modifier));
    }

  // Programs last ...

  // now do all programs inside object

  save_programs (obj->programlist);

  } // end of each object


  } // end of CAreaEditorDoc::save_SMAUG_objects

// ========================================================================

void CAreaEditorDoc::save_ROM_objects (void)
  {

POSITION objPos;
CMUDObject * obj;

POSITION affectPos;
CAffect * affect;

POSITION extraPos;
CExtraDescription * extra;

int i;

// cycle through all objects

for (objPos = m_ObjectList.GetHeadPosition (); objPos; )
  {
  obj = m_ObjectList.GetNext (objPos);

  DoSaveMilestone ();

  fwrite_string (CFormat ("#%i", obj->vnum));
  fwrite_string (CFormat ("%s~", (LPCTSTR) obj->name));
  fwrite_string (CFormat ("%s~", (LPCTSTR) obj->short_descr));
  fwrite_string (CFormat ("%s~", (LPCTSTR) obj->description));
  fwrite_string (CFormat ("%s~", (LPCTSTR) obj->material));

  if (!ObjectItemList.IsValueInList (obj->item_type))
    Warning (obj, 
            "Item type %i not in item type list, defaulting to first one",
            obj->item_type);

  fwrite_string (CFormat ("%s %s %s", 
                (LPCTSTR) Quote (ObjectItemList.ReturnName (obj->item_type)),
                (LPCTSTR) ConvertROMFlag (obj->extra_flags),
                (LPCTSTR) ConvertROMFlag (obj->wear_flags)));

	switch(obj->item_type)
	{
	case ITEM_WEAPON:

      if (!ObjectWeaponList.IsValueInList (obj->value[0]))
        Warning (obj, 
                "Weapon type %i not in weapon type list, defaulting to first one",
                obj->value[0]);

      if (!ObjectAttackList.IsValueInList (obj->value[3]))
        Warning (obj, 
                "Attack type %i not in attack type list, defaulting to first one",
                obj->value[3]);

      fwrite_string (CFormat ("%s %i %i %s %s", 
                    (LPCTSTR) Quote (ObjectWeaponList.ReturnName (obj->value[0])),
                    obj->value[1],
                    obj->value[2],
                    (LPCTSTR) Quote (ObjectAttackList.ReturnName (obj->value[3])),
                    (LPCTSTR) ConvertROMFlag (obj->value[4])));

	    break;

	case ITEM_CONTAINER:

      fwrite_string (CFormat ("%i %s %i %i %i", 
                    obj->value[0],
                    (LPCTSTR) ConvertROMFlag (obj->value[1]),
                    obj->value[2],
                    obj->value[3],
                    obj->value[4]));
	    break;

  case ITEM_DRINK_CON:
	case ITEM_FOUNTAIN:

      if (!ObjectLiquidList.IsValueInList (obj->value[2]))
        Warning (obj, 
                "Liquid type %i not in liquid type list, defaulting to first one",
                obj->value[2]);

      fwrite_string (CFormat ("%i %i %s %i %i", 
                    obj->value[0],
                    obj->value[1],
                    (LPCTSTR) Quote (ObjectLiquidList.ReturnName (obj->value[2])),
                    obj->value[3],
                    obj->value[4]));

            break;

	case ITEM_WAND:
	case ITEM_STAFF:

      if (obj->value[3] != -1)
        if (!ROMSkillNameList.IsValueInList (obj->value[3]))
          Warning (obj, 
                  "Skill type %i not in skill type list, defaulting to first one",
                  obj->value[3]);
     

      fwrite_string (CFormat ("%i %i %i '%s' %i", 
                    obj->value[0],
                    obj->value[1],
                    obj->value[2],
                    (LPCTSTR) skill_name (obj->value[3]),
                    obj->value[4]));

	    break;
	case ITEM_POTION:
	case ITEM_PILL:
	case ITEM_SCROLL:

      for (i = 1; i <= 4; i++)
        if (obj->value[i] != -1)
          if (!ROMSkillNameList.IsValueInList (obj->value[i]))
            Warning (obj, 
                    "Skill type %i not in skill type list, defaulting to first one",
                    obj->value[i]);

      fwrite_string (CFormat ("%i '%s' '%s' '%s' '%s'", 
                    obj->value[0],
                    (LPCTSTR) skill_name (obj->value[1]),
                    (LPCTSTR) skill_name (obj->value[2]),
                    (LPCTSTR) skill_name (obj->value[3]),
                    (LPCTSTR) skill_name (obj->value[4])));
	    break;

	default:
    fwrite_string (CFormat ("%i %i %i %i %i", 
                  obj->value[0],
                  obj->value[1],
                  obj->value[2],
                  obj->value[3],
                  obj->value[4]));
	    break;
	}

          /* set up condition */
  char cCondition;
  if (obj->condition < 10)
    cCondition = 'R';   // rats?
  else if (obj->condition < 25)
    cCondition = 'B';   // broken?
  else if (obj->condition < 50)
    cCondition = 'D';   // damaged?
  else if (obj->condition < 75)
    cCondition = 'W';   // wobbly??
  else if (obj->condition < 90)
    cCondition = 'A';   // average?
  else if (obj->condition < 100)
    cCondition = 'G';   // good?
  else 
    cCondition = 'P'; // perfect?
 
  fwrite_string (CFormat ("%i %i %i %c", 
                obj->level,
                obj->weight,
                obj->cost,
                cCondition));

  // now do all programs, extras, affects inside the object
  
  // Affects first ...

  for (affectPos = obj->affectlist.GetHeadPosition (); affectPos; )
    {
    affect = obj->affectlist.GetNext (affectPos);

    if (affect->where == TO_OBJECT)
      {
      fwrite_string ("A");    // Affects flag
      fwrite_string (CFormat ("%i %i", affect->location,
                                       affect->modifier));
      }   // end of affect on object (TO_OBJECT)
    else
      {
      char cAffectType;
      switch (affect->where)
        {
        case TO_AFFECTS:  cAffectType = 'A'; break;
        case TO_IMMUNE:   cAffectType = 'I'; break;
        case TO_RESIST:   cAffectType = 'R'; break;
        case TO_VULN:     cAffectType = 'V'; break;
        default:          cAffectType = 'X'; break;
        } // end of switch

      fwrite_string ("F");    // Affects flag
      fwrite_string (CFormat ("%c %i %s %s",
                               cAffectType,
                               affect->location,
                               (LPCTSTR) print_bitvector (affect->modifier),
                               (LPCTSTR) ConvertROMFlag (affect->bitvector)));

      }   // end of flag affect
    }     // end of affects list

  // Extra descriptions next ...

  for (extraPos = obj->extralist.GetHeadPosition (); extraPos; )
    {
    extra = obj->extralist.GetNext (extraPos);

    fwrite_string ("E");    // Extra description flag
    fwrite_string (CFormat ("%s~", (LPCTSTR) extra->keyword));
    fwrite_string (CFormat ("%s~", (LPCTSTR) extra->description));
    }

  // Programs last ...

  // now do all programs inside object

  if (App.GetProfileInt (sProfilePreferences, sProfileSaveROMPrograms, 0))
    save_programs (obj->programlist);

  } // end of each object


  } // end of CAreaEditorDoc::save_ROM_objects

// ========================================================================

void CAreaEditorDoc::save_objects (void)
  {
  if (m_ObjectList.IsEmpty ())
    return;

  fwrite_string ("#OBJECTS");

  if (SMAUG)
    save_SMAUG_objects ();
  else if (ROM)
    save_ROM_objects ();
  else
    ThrowErrorException ("Unknown area type: %i", m_AreaType);

  fwrite_string ("#0");    // objects terminator
  fwrite_string (""); // blank line

  } // end of CAreaEditorDoc::save_objects

// ========================================================================

void CAreaEditorDoc::save_SMAUG_rooms (void)
  {

POSITION roomPos;
CRoom * room;

POSITION exitPos;
CExit * exit;

POSITION mapPos;
CRoomMap * map;

POSITION extraPos;
CExtraDescription * extra;

// cycle through all rooms

for (roomPos = m_RoomList.GetHeadPosition (); roomPos; )
  {
  room = m_RoomList.GetNext (roomPos);

  DoSaveMilestone ();

  fwrite_string (CFormat ("#%i", room->vnum));
  fwrite_string (CFormat ("%s~", (LPCTSTR) room->name));
  fwrite_string (CFormat ("%s~", (LPCTSTR) room->description));

  fwrite_string (CFormat ("0 %s %i %i %i %i", 
                (LPCTSTR) print_bitvector (room->room_flags),
                room->sector_type,
                room->tele_delay,
                room->tele_vnum,
                room->tunnel));

  // now do all programs, extras, doors, maps inside the room

  // Doors first

  for (exitPos = room->exitlist.GetHeadPosition (); exitPos; )
    {
    exit = room->exitlist.GetNext (exitPos);

    int vdir = exit->vdir;

    if (!RoomDirectionList.IsValueInList (vdir))
      {
      Warning (exit, 
              "Exit direction %i not in direction list, defaulting to first one",
              vdir);
      vdir = 0;
      };

    fwrite_string (CFormat ("D%i", vdir));    // door flag and number
    fwrite_string (CFormat ("%s~", (LPCTSTR) exit->description));
    fwrite_string (CFormat ("%s~", (LPCTSTR) exit->keyword));

    fwrite_string (CFormat ("%s %i %i %i", 
                  (LPCTSTR) print_bitvector (exit->exit_info),
                  exit->key,
                  exit->vnum,
                  exit->distance));
    }   // end of each exit


  // Extra descriptions next ...

  for (extraPos = room->extralist.GetHeadPosition (); extraPos; )
    {
    extra = room->extralist.GetNext (extraPos);

    fwrite_string ("E");    // Extra description flag
    fwrite_string (CFormat ("%s~", (LPCTSTR) extra->keyword));
    fwrite_string (CFormat ("%s~", (LPCTSTR) extra->description));
    }   // end of each description
    
  // Maps next ...

  for (mapPos = room->maplist.GetHeadPosition (); mapPos; )
    {
    map = room->maplist.GetNext (mapPos);

    fwrite_string ("M");    // maps flag
    fwrite_string (CFormat ("%i %i %i %c", 
                              map->vnum,
                              map->x,
                              map->y,
                              map->entry));
    }

  // Programs last ...

  // now do all programs inside room

  save_programs (room->programlist);

  fwrite_string ("S");    // end of extra stuff terminator

  } // end of each room

  } // end of CAreaEditorDoc::save_SMAUG_rooms

// ========================================================================

void CAreaEditorDoc::save_ROM_rooms (void)
  {

POSITION roomPos;
CRoom * room;

POSITION exitPos;
CExit * exit;

POSITION extraPos;
CExtraDescription * extra;

// cycle through all rooms

for (roomPos = m_RoomList.GetHeadPosition (); roomPos; )
  {
  room = m_RoomList.GetNext (roomPos);

  DoSaveMilestone ();

  fwrite_string (CFormat ("#%i", room->vnum));
  fwrite_string (CFormat ("%s~", (LPCTSTR) room->name));
  fwrite_string (CFormat ("%s~", (LPCTSTR) room->description));

  fwrite_string (CFormat ("0 %s %i", 
                (LPCTSTR) ConvertROMFlag (room->room_flags),
                room->sector_type));

  // now do all programs, extras, doors, maps inside the room

  // Doors first

  EXT_BV exit_info;

  for (exitPos = room->exitlist.GetHeadPosition (); exitPos; )
    {
    exit = room->exitlist.GetNext (exitPos);

    int vdir = exit->vdir;

    if (!RoomDirectionList.IsValueInList (vdir))
      {
      Warning (exit, 
              "Exit direction %i not in direction list, defaulting to first one",
              vdir);
      vdir = 0;
      };

    exit_info = exit->exit_info;

    // go back to old style for compatibility

    if (exit_info == ROM_EX_ISDOOR)
      exit_info = 1;
    else if (exit_info == (ROM_EX_ISDOOR | ROM_EX_PICKPROOF))
      exit_info = 2;
    else if (exit_info == (ROM_EX_ISDOOR | ROM_EX_NOPASS))
      exit_info = 3;
    else if (exit_info == (ROM_EX_ISDOOR|ROM_EX_NOPASS|ROM_EX_PICKPROOF))
      exit_info = 4;

    fwrite_string (CFormat ("D%i", vdir));    // door flag and number
    fwrite_string (CFormat ("%s~", (LPCTSTR) exit->description));
    fwrite_string (CFormat ("%s~", (LPCTSTR) exit->keyword));
    fwrite_string (CFormat ("%s %i %i", 
                  (LPCTSTR) print_bitvector (exit_info),
                  exit->key,
                  exit->vnum));
    }   // end of each exit


  // now do various flags

  if (room->heal_rate)
    fwrite_string (CFormat ("H %i", room->heal_rate));    // healing room

  if (room->mana_rate)
    fwrite_string (CFormat ("M %i", room->mana_rate));    // mana room

  if (!room->clan.IsEmpty ())
    fwrite_string (CFormat ("C %s~", (LPCTSTR) room->clan));    // clan room

  if (!room->owner.IsEmpty ())
    fwrite_string (CFormat ("O %s", (LPCTSTR) room->owner));    // owner

  // Extra descriptions next ...

  for (extraPos = room->extralist.GetHeadPosition (); extraPos; )
    {
    extra = room->extralist.GetNext (extraPos);

    fwrite_string ("E");    // Extra description flag
    fwrite_string (CFormat ("%s~", (LPCTSTR) extra->keyword));
    fwrite_string (CFormat ("%s~", (LPCTSTR) extra->description));
    }   // end of each description
    
  // Programs last ...

  // now do all programs inside room

  if (App.GetProfileInt (sProfilePreferences, sProfileSaveROMPrograms, 0))
    save_programs (room->programlist);

  fwrite_string ("S");    // end of extra stuff terminator

  } // end of each room

  } // end of CAreaEditorDoc::save_ROM_rooms

// ========================================================================

void CAreaEditorDoc::save_rooms (void)
  {
  if (m_RoomList.IsEmpty ())
    return;

  fwrite_string ("#ROOMS");

  if (SMAUG)
    save_SMAUG_rooms ();
  else if (ROM) 
    save_ROM_rooms ();
  else
    ThrowErrorException ("Unknown area type: %i", m_AreaType);

  fwrite_string ("#0");    // rooms terminator
  fwrite_string (""); // blank line

  } // end of CAreaEditorDoc::save_rooms


// ========================================================================

void CAreaEditorDoc::save_resets (void)
  {
  if (m_ResetList.IsEmpty ())
    return;

  fwrite_string ("#RESETS");

POSITION resetPos;
CReset * reset;


// cycle through all resets

for (resetPos = m_ResetList.GetHeadPosition (); resetPos; )
  {
  reset = m_ResetList.GetNext (resetPos);

  DoSaveMilestone ();

  CString strComment = reset->strComment;
  if (strComment.IsEmpty ())
    {
    strComment = "; ";
    strComment += reset->Summary ();
    }

  // ROM sometimes writes out 4 args
  if (ROM && (reset->command == 'P' || reset->command == 'M'))
    fwrite_string (CFormat ("%c %i %i %i %i %i %s", 
                    reset->command,
                    reset->extra,
                    reset->arg1,
                    reset->arg2,
                    reset->arg3,
                    reset->arg4,
                    (LPCTSTR) strComment));
  // for G and R resets there are only 2 arguments
  else if (reset->command == 'G' || reset->command == 'R')
    fwrite_string (CFormat ("%c %i %i %i %s", 
                    reset->command,
                    reset->extra,
                    reset->arg1,
                    reset->arg2,
                    (LPCTSTR) strComment));
  // otherwise, 3 arguments
  else
    fwrite_string (CFormat ("%c %i %i %i %i  %s", 
                    reset->command,
                    reset->extra,
                    reset->arg1,
                    reset->arg2,
                    reset->arg3,
                    (LPCTSTR) strComment));


  } // end of each reset


  fwrite_string ("S");    // resets terminator
  fwrite_string (""); // blank line

  } // end of CAreaEditorDoc::save_resets

// ========================================================================

void CAreaEditorDoc::save_shops (void)
  {
  if (m_ShopList.IsEmpty ())
    return;

  fwrite_string ("#SHOPS");

POSITION shopPos;
CShop * shop;

CMobile * mob;

CString strMob;

  // cycle through all shops

  for (shopPos = m_ShopList.GetHeadPosition (); shopPos; )
    {
    shop = m_ShopList.GetNext (shopPos);

    DoSaveMilestone ();

    // make a comment giving the keeper's name
    if (mob	= FindMob (shop->keeper))
	    strMob = CFormat (" ; %s", (LPCTSTR) mob->short_descr);

    fwrite_string (CFormat ("%i %i %i %i %i %i %i %i %i %i%s", 
                  shop->keeper,
                  shop->buy_type [0],
                  shop->buy_type [1],
                  shop->buy_type [2],
                  shop->buy_type [3],
                  shop->buy_type [4],
                  shop->profit_buy,
                  shop->profit_sell,
                  shop->open_hour,
                  shop->close_hour,
                  (LPCTSTR) strMob));

    } // end of each shop


  fwrite_string ("0");    // shops terminator
  fwrite_string (""); // blank line

  } // end of CAreaEditorDoc::save_shops

// ========================================================================

void CAreaEditorDoc::save_repairs (void)
  {
  if (m_RepairList.IsEmpty ())
    return;

  fwrite_string ("#REPAIRS");

POSITION repairPos;
CRepair * repair;

CMobile * mob;

CString strMob;

  // cycle through all repairs

  for (repairPos = m_RepairList.GetHeadPosition (); repairPos; )
    {
    repair = m_RepairList.GetNext (repairPos);

    DoSaveMilestone ();

    // make a comment giving the keeper's name
    if (mob	= FindMob (repair->keeper))
	    strMob = CFormat (" ; %s", (LPCTSTR) mob->short_descr);

    fwrite_string (CFormat ("%i %i %i %i %i %i %i %i%s", 
                  repair->keeper,
                  repair->fix_type [0],
                  repair->fix_type [1],
                  repair->fix_type [2],
                  repair->profit_fix,
                  repair->shop_type,
                  repair->open_hour,
                  repair->close_hour,
                  (LPCTSTR) strMob));

    } // end of each repair


  fwrite_string ("0");    // repairs terminator
  fwrite_string (""); // blank line

  } // end of CAreaEditorDoc::save_repairs

// ========================================================================

void CAreaEditorDoc::save_specials (void)
  {
  if (m_MobList.IsEmpty ())
    return;

  fwrite_string ("#SPECIALS");

POSITION mobPos;
CMobile * mob;


// cycle through all specials

for (mobPos = m_MobList.GetHeadPosition (); mobPos; )
  {
  mob = m_MobList.GetNext (mobPos);

  // zero means no special function
  if (mob->spec_fun) 
    fwrite_string (CFormat ("M %i %s   ; %s", 
                            mob->vnum,
                            (LPCTSTR) MobSpecialList.ReturnName (mob->spec_fun, true),
                            (LPCTSTR) mob->short_descr));

  } // end of each special


  fwrite_string ("S");    // specials terminator
  fwrite_string (""); // blank line

  } // end of CAreaEditorDoc::save_specials


// ========================================================================

void CAreaEditorDoc::save_helps (void)
  {
  if (m_HelpList.IsEmpty ())
    return;

  fwrite_string ("#HELPS");

POSITION helpPos;
CHelp * help;

  // cycle through all helps

  for (helpPos = m_HelpList.GetHeadPosition (); helpPos; )
    {
    help = m_HelpList.GetNext (helpPos);

    DoSaveMilestone ();

    fwrite_string (CFormat ("%i %s~", 
                  help->level,
                  (LPCTSTR) help->keyword));

    fwrite_string (CFormat ("%s~", 
                  (LPCTSTR) help->text));

    } // end of each help


  fwrite_string ("0 $~");    // helps terminator
  fwrite_string (""); // blank line

  } // end of CAreaEditorDoc::save_helps

// ========================================================================

void CAreaEditorDoc::DoSaveMilestone (void)
  {
  m_FileWrite.DoSaveMilestone ();
  }

/////////////////////////////////////////////////////////////////////////////
// CAreaEditorDoc serialization

void CAreaEditorDoc::Serialize(CArchive& ar)
{
CString strSection;

  m_strErrorMessage.Empty ();
  m_nErrors = 0;

	if (ar.IsStoring())
	  {
    try 
      {

      m_strWarningType = "saving";

      if (m_Area && m_Area->area_version)
        if (App.m_SkillList.IsEmpty ())
          ThrowErrorException ("Skill list not loaded - cannot save area");

      long iItems =  m_MobList.GetCount ()
                       + m_ObjectList.GetCount ()
                       + m_RoomList.GetCount ()
                       + m_ResetList.GetCount ()
                       + m_ShopList.GetCount ()
                       + m_RepairList.GetCount ()
                       + m_HelpList.GetCount ();

      m_FileWrite.Init ("Saving area", &ar, iItems);

    // #AREA
    // #AUTHOR
    // #RANGES
    // #RESETMSG
    // #FLAGS
    // #ECONOMY

      if (m_Area)
        save_area ();

    // #MOBILES

      save_mobiles ();

    // #OBJECTS

      save_objects ();

    // #ROOMS

      save_rooms ();

      // #RESETS

      save_resets ();

    // #SHOPS

      save_shops ();

    // #REPAIRS

      save_repairs ();

    // #SPECIALS

      save_specials ();

    // #HELPS

      save_helps ();

      fwrite_string ("#$");    // area file terminator

      m_FileWrite.Wrapup ();

      }   // end of try block

    catch (CException * e)
      {
      m_FileWrite.Wrapup ();
      e->ReportError ();
      throw e;

      } // end of catch handler

    }
	else
	{

  m_Original_AreaType = m_AreaType; // so we know if they changed types

  try
    {

    m_strWarningType = "loading";

    m_FileRead.Init ("Loading area", &ar);

    while (true)
      {
      if (fread_letter () != '#')
        ThrowErrorException ("Area section must start with a \"#\"");
    
      strSection = fread_word ();
      strSection.MakeUpper ();

      if (strSection == "AREA")
        load_area ();
      else if (strSection == "AUTHOR")
        load_author ();
      else if (strSection == "VERSION")
        load_version ();
      else if (strSection == "NEIGHBOR")
        load_neighbour ();
      else if (strSection == "CLIMATE")
        load_climate ();
      else if (strSection == "RANGES")
        load_ranges ();
      else if (strSection == "RESETMSG")
        load_resetmsg ();
      else if (strSection == "FLAGS")
        load_flags ();
      else if (strSection == "ECONOMY")
        load_economy ();
      else if (strSection == "MOBILES")
        load_mobiles ();
      else if (strSection == "OBJECTS")
        load_objects ();
      else if (strSection == "ROOMS")
        load_rooms ();
      else if (strSection == "RESETS")
        load_resets ();
      else if (strSection == "SHOPS")
        load_shops ();
      else if (strSection == "REPAIRS")
        load_repairs ();
      else if (strSection == "SPECIALS")
        load_specials ();
      else if (strSection == "HELPS")
        load_helps ();
      else if (strSection == "$")    // end of file
        break;
      else
        ThrowErrorException ("Unrecognised area section header: %s",
                            (LPCTSTR) strSection);


      } // end of read loop

    // in case some turkey keys things in the wrong order with a text editor, sort them
    SortMobiles ();
    SortObjects ();
    SortRooms ();

    } // end of try block

// on an exception, show the error, then the line details, then throw
// an archive exception to tell the document we couldn't load it

  catch (CException * e)
    {
    m_FileRead.Wrapup ();
    e->ReportError ();
    e->Delete ();

    ::AfxMessageBox (CFormat ("Error occurred at (line %ld) \"%s\"",
                      m_FileRead.GetLineNumber (), 
                      (LPCTSTR) m_FileRead.GetLastLineRead ()),
                      MB_ICONINFORMATION);
    AfxThrowArchiveException (CArchiveException::badSchema);

    } // end of catch handler

  m_FileRead.Wrapup ();

  if (m_Area)
    {
    // don't show ridiculous numbers if no items in a category
    if (m_Area->mob_low_vnum == INT_MAX)
      {
      m_Area->mob_low_vnum = 9900;
      m_Area->mob_hi_vnum = 9950;
      }
    if (m_Area->obj_low_vnum == INT_MAX)
      {
      m_Area->obj_low_vnum = 9900;
      m_Area->obj_hi_vnum = 9950;
      }
    if (m_Area->room_low_vnum == INT_MAX)
      {
      m_Area->room_low_vnum = 9900;
      m_Area->room_hi_vnum = 9950;
      }
    }

  }   // end of loading

  // show any non-fatal errors, if wanted

  if (!m_strErrorMessage.IsEmpty ())
    if (App.GetProfileInt  (sProfilePreferences, sProfileShowWarnings, 1))
      {
      // show the errors

      // MODELESS dialog here

      CAreaLoadingProblems * dlg = new CAreaLoadingProblems;
      dlg->m_strErrors = CFormat ("Problems %s area: ", (LPCTSTR) m_strWarningType);
      dlg->m_strErrors += ar.GetFile ()->GetFileName () + ENDLINE + ENDLINE;
      dlg->m_strErrors += m_strErrorMessage + ENDLINE;
      dlg->m_strErrors += "Press <Esc> to dismiss this window";
      dlg->Create (ID_PROBLEMS_LOADING_AREA, NULL);  // create it
      dlg->ShowWindow(SW_SHOW);  // and, finally, show it - dialog will delete itself

      }

} // end of CAreaEditorDoc::Serialize

/////////////////////////////////////////////////////////////////////////////
// CAreaEditorDoc diagnostics

#ifdef _DEBUG
void CAreaEditorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAreaEditorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAreaEditorDoc commands

// overall find room - scan all open documents for the room
CRoom * FindRoom (const int vnum)
  {
CRoom * room;

  for (POSITION docPos = App.m_pDocTemplate->GetFirstDocPosition();
      docPos != NULL; )
    {

    CAreaEditorDoc * pDoc = (CAreaEditorDoc *) App.m_pDocTemplate->GetNextDoc(docPos);

    // look in this document for the room
    room = pDoc->get_room_index (vnum);

    // if found - don't bother looking up any more
    if (room)
      return room;

    } // end of doing each document

  return NULL;
  }
             
CString FullRoomName (const CRoom * room)
  {

  if (room == NULL)
    return "(NULL ROOM)";

CString strName = room->name;

  if (room->m_pDoc->m_Area && !room->m_pDoc->m_Area->strAreaName.IsEmpty ())
    {
    strName += " [";
    strName += room->m_pDoc->m_Area->strAreaName;
    strName += "]";
    }
  else
    strName += " [untitled area]";

  return strName;

  }

CRoom * CAreaEditorDoc::get_room_index (const int vnum) const
  {
POSITION roomPos;
CRoom * room;

for (roomPos = m_RoomList.GetHeadPosition (); roomPos; )
  {
  room = m_RoomList.GetNext (roomPos);

  if (room->vnum == vnum)
    return room;

  }   // end of scanning all rooms

// not found, return NULL

  return NULL;

  } // end of CAreaEditorDoc::get_room_index 

void CAreaEditorDoc::goto_room (const int vnum)
  {
CRoom * room = FindRoom (vnum);

  // can't find - obviously can't go to it

  if (room == NULL)
    return;

  room->GoTo ();

  } // end of CAreaEditorDoc::goto_room 

// overall find mob - scan all open documents for the mob
CMobile * FindMob (const int vnum)
  {
CMobile * mob;

  for (POSITION docPos = App.m_pDocTemplate->GetFirstDocPosition();
      docPos != NULL; )
    {

    CAreaEditorDoc * pDoc = (CAreaEditorDoc *) App.m_pDocTemplate->GetNextDoc(docPos);

    // look in this document for the mob
    mob = pDoc->get_mob_index (vnum);

    // if found - don't bother looking up any more
    if (mob)
      return mob;

    } // end of doing each document

  return NULL;
  }
             
CString FullMobName (const CMobile * mob)
  {

  if (mob == NULL)
    return "(NULL MOB)";

CString strName = mob->short_descr;

  if (mob->m_pDoc->m_Area && !mob->m_pDoc->m_Area->strAreaName.IsEmpty ())
    {
    strName += " [";
    strName += mob->m_pDoc->m_Area->strAreaName;
    strName += "]";
    }
  else
    strName += " [untitled area]";

  return strName;

  }

CMobile * CAreaEditorDoc::get_mob_index (const int vnum)
  {
POSITION mobPos;
CMobile * mob;

for (mobPos = m_MobList.GetHeadPosition (); mobPos; )
  {
  mob = m_MobList.GetNext (mobPos);

  if (mob->vnum == vnum)
    return mob;

  }   // end of scanning all mobs

// not found, return NULL

  return NULL;

  } // end of CAreaEditorDoc::get_mob_index 

void CAreaEditorDoc::goto_mob (const int vnum)
  {
CMobile * mob = FindMob (vnum);

  // can't find - obviously can't go to it

  if (mob == NULL)
    return;

  mob->GoTo ();

  } // end of CAreaEditorDoc::goto_mob 

void CAreaEditorDoc::goto_object (const int vnum) 
  {
CMUDObject * object = FindObj (vnum);

  // can't find - obviously can't go to it

  if (object == NULL)
    return;

  object->GoTo ();

  } // end of CAreaEditorDoc::goto_object 

// overall find obj - scan all open documents for the object
CMUDObject * FindObj (const int vnum)
  {
CMUDObject * obj;

  for (POSITION docPos = App.m_pDocTemplate->GetFirstDocPosition();
      docPos != NULL; )
    {

    CAreaEditorDoc * pDoc = (CAreaEditorDoc *) App.m_pDocTemplate->GetNextDoc(docPos);

    // look in this document for the object
    obj = pDoc->get_obj_index (vnum);

    // if found - don't bother looking up any more
    if (obj)
      return obj;

    } // end of doing each document

  return NULL;
  }
             
CString FullObjName (const CMUDObject * obj)
  {

  if (obj == NULL)
    return "(NULL OBJECT)";

CString strName = obj->name;

  if (obj->m_pDoc->m_Area && !obj->m_pDoc->m_Area->strAreaName.IsEmpty ())
    {
    strName += " [";
    strName += obj->m_pDoc->m_Area->strAreaName;
    strName += "]";
    }
  else
    strName += " [untitled area]";

  return strName;

  }

CMUDObject * CAreaEditorDoc::get_obj_index (const int vnum) const
  {
POSITION objPos;
CMUDObject * obj;

for (objPos = m_ObjectList.GetHeadPosition (); objPos; )
  {
  obj = m_ObjectList.GetNext (objPos);

  if (obj->vnum == vnum)
    return obj;

  }   // end of scanning all objects

// not found, return NULL

  return NULL;

  } // end of CAreaEditorDoc::get_obj_index 


void CAreaEditorDoc::goto_exit (const CRoom * pRoomIndex, const int vdir)
  {
CExit * exit = get_exit (pRoomIndex, vdir);

  // can't find - obviously can't go to it

  if (exit == NULL)
    return;

  exit->GoTo ();

  } // end of CAreaEditorDoc::goto_exit 


CExit * CAreaEditorDoc::get_exit (const CRoom * pRoomIndex, const int vdir) const
  {
POSITION exitPos;
CExit * exit;

if (pRoomIndex == NULL)
  return NULL;

for (exitPos = pRoomIndex->exitlist.GetHeadPosition (); exitPos; )
  {
  exit = pRoomIndex->exitlist.GetNext (exitPos);

  if (exit->vdir == vdir)
    return exit;

  }   // end of scanning all exits

// not found, return NULL

  return NULL;

  } // end of CAreaEditorDoc::get_exit 

// This is to record non-fatal warnings when loading the area

void CAreaEditorDoc::LoadWarning (LPCTSTR lpszFormat, ...)
{

	ASSERT(AfxIsValidString(lpszFormat, FALSE));

	va_list argList;
	va_start(argList, lpszFormat);
  m_strErrorMessage += CFormat ("[line %i] \"%s\" - ", 
                       m_FileRead.GetLineNumber (), 
                      (LPCTSTR) m_FileRead.GetLastLineRead ());
	m_strErrorMessage += CFormat (lpszFormat, argList);
  m_strErrorMessage += ENDLINE;
	va_end(argList);
  m_nErrors++;

  }

// This is to record non-fatal warnings when loading the area

void CAreaEditorDoc::Warning (CMUDitem * item, LPCTSTR lpszFormat, ...)
{

	ASSERT(AfxIsValidString(lpszFormat, FALSE));

	va_list argList;
	va_start(argList, lpszFormat);
  if (item)
    {

    CString strType = item->Type ();
    if (!strType.IsEmpty ())
	    strType.SetAt (0, UPPER(strType[0])); // capitalise first character

    m_strErrorMessage += "** ";
    m_strErrorMessage += strType;
    m_strErrorMessage += ": ";
    m_strErrorMessage += item->Summary ();
    if (strlen (lpszFormat) > 0)
      m_strErrorMessage += ": ";
    }

  m_strErrorMessage += CFormat (lpszFormat, argList);
  m_strErrorMessage += ENDLINE;
	va_end(argList);

  m_nErrors++;

}

void CAreaEditorDoc::OnFileAreaSummary() 
{
CAreaSummary dlg;

	dlg.m_helps = m_HelpList.GetCount ();
	dlg.m_mobiles = m_MobList.GetCount ();
	dlg.m_objects = m_ObjectList.GetCount ();
	dlg.m_repairs = m_RepairList.GetCount ();
	dlg.m_resets = m_ResetList.GetCount ();
	dlg.m_rooms = m_RoomList.GetCount ();
	dlg.m_shops = m_ShopList.GetCount ();

  for (POSITION mobPos = m_MobList.GetHeadPosition (); mobPos; )
    dlg.m_mobile_programs += m_MobList.GetNext (mobPos)->programlist.GetCount ();

  for (POSITION objPos = m_ObjectList.GetHeadPosition (); objPos; )
    {
    CMUDObject * object = m_ObjectList.GetNext (objPos);
    dlg.m_object_affects += object->affectlist.GetCount ();
    dlg.m_object_programs += object->programlist.GetCount ();
    }

  for (POSITION roomPos = m_RoomList.GetHeadPosition (); roomPos; )
    {
    CRoom * room = m_RoomList.GetNext (roomPos);
    dlg.m_room_programs += room->programlist.GetCount ();
    dlg.m_room_exits += room->exitlist.GetCount ();
    }

  dlg.DoModal ();

}

// we need to force an update on the current pane before closing the document

BOOL CAreaEditorDoc::SaveModified() 
{
 
  // find our splitter view

   for (POSITION pos = GetFirstViewPosition(); pos;)
   {
      CView* pView = GetNextView(pos);

      // if the splitter view, update current pane
      if (pView->IsKindOf(RUNTIME_CLASS(CAreaEditorView)))
        {
        pView = (CView *) ((CAreaEditorView *)pView)->m_pSplitterWindow->GetPane(0,1);
        if (!pView->UpdateData (TRUE))
          return 0;
        }
   }   
   
	return CDocument::SaveModified();
}

// we need to force an update on the current pane before saving the document

BOOL CAreaEditorDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
  // find our splitter view

   for (POSITION pos = GetFirstViewPosition(); pos;)
   {
      CView* pView = GetNextView(pos);

      // if the splitter view, update current pane
      if (pView->IsKindOf(RUNTIME_CLASS(CAreaEditorView)))
        {
        pView = (CView *) ((CAreaEditorView *)pView)->m_pSplitterWindow->GetPane(0,1);
        if (!pView->UpdateData (TRUE))
          {
          ::AfxMessageBox ("Document not saved.", MB_ICONEXCLAMATION);
          return 0;
          }
        }
   }   
	
  if (m_Original_AreaType != m_AreaType &&
      GetPathName () == lpszPathName)
    {
    CString strOriginalType = "SMAUG";
    CString strNewType = "SMAUG";

    if (m_Original_AreaType == eROM)
      strOriginalType = "ROM";

    if (m_AreaType == eROM)
      strNewType = "ROM";

    if (::AfxMessageBox (CFormat
      ("You have changed the type of this area from %s to %s.\n\n"
       "You are advised to do a \"Save As\" and save under a different name "
       "as some features of areas are not common to both area types.\n\n"
       "Do you wish to continue with the save?",
        (LPCTSTR) strOriginalType,
        (LPCTSTR) strNewType),
      MB_ICONQUESTION | MB_YESNO | MB_DEFBUTTON2) != IDYES)
      return 0;

    }

	return CDocument::OnSaveDocument(lpszPathName);
}

void CAreaEditorDoc::OnUpdateStatusModified(CCmdUI* pCmdUI) 
{

  if (IsModified ())
    pCmdUI->SetText ("Modified");
  else
    pCmdUI->SetText ("");
	  
  pCmdUI->Enable (true);

}



void CAreaEditorDoc::OnCloseDocument() 
{
  Frame.FixUpTitleBar ();	

	CDocument::OnCloseDocument();
}

BOOL CAreaEditorDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{

  if (m_AreaType == eAsk)
    {
    CAreaTypeDlg dlg;

    if (dlg.DoModal () != IDOK)
      return FALSE;   // cancelled so can't open document

    // add 1, as 0 is "ask", 1 = SMAUG (response zero) and so on
    m_AreaType = (t_areatype) (dlg.m_iAreaType + 1);

    }

	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
  Frame.FixUpTitleBar (this);	
	
	return TRUE;
}


CMobile * CAreaEditorDoc::AddMobile (CAreaEditorView * pView,
                                    const bool bSelect)
  {
  int vnum = -1,
      prevVnum = INT_MAX;

  CMobile * mob,
          * prevMob = NULL;

  // look for a gap in the mob vnums, so we can allocate it to this mob
  for (POSITION mobPos = m_MobList.GetHeadPosition (); 
        mobPos && (vnum == -1); )
    {
    mob = m_MobList.GetNext (mobPos);
    if ((prevVnum != INT_MAX) && (mob->vnum > (prevVnum + 1)))
      vnum = prevVnum + 1;
    prevVnum = mob->vnum;
    prevMob = mob;    // remember previous mob
    }

  // no gap found
  if (vnum == -1)
    if (prevVnum == INT_MAX)    // no mobs - take lowest available vnum
      vnum = m_Area->mob_low_vnum;
    else
      {
      vnum = prevVnum + 1;      // take highest, plus 1
      prevMob = NULL;          // force an "addtail"
      }

  if (vnum < m_Area->mob_low_vnum || vnum > m_Area->mob_hi_vnum)
    {
    ::AfxMessageBox (CFormat ("No free mob vnums in the range %i to %i",
          m_Area->mob_low_vnum, m_Area->mob_hi_vnum),
        MB_ICONEXCLAMATION);
    return NULL;
    }

  mob = new CMobile (RUNTIME_CLASS(CMobileView), this);
  mob->vnum = vnum;   // use our new vnum

  // insert in numeric order (insert before because prevMob is *higher*)
  if (prevMob)
    m_MobList.InsertBefore (m_MobList.Find (prevMob, NULL), mob);    // and add it to our list
  else
    m_MobList.AddTail (mob);    // and add it to our list
  HTREEITEM hdlMobItem = pView->AddTreeItem (mob, pView->m_hdlTreeMobiles);
  pView->GetTreeCtrl().SortChildren (pView->m_hdlTreeMobiles);    // put in right part of tree ctrl
  if (bSelect)
    pView->GetTreeCtrl().Select (hdlMobItem, TVGN_CARET);   // select it
  SetModifiedFlag ();

  return mob;

  } // end of CAreaEditorDoc::AddMobile


CMUDObject * CAreaEditorDoc::AddObject (CAreaEditorView * pView,
                                 const bool bSelect)
  {
  int vnum = -1,
      prevVnum = INT_MAX;

  CMUDObject * obj,
             * prevObj = NULL;

  // look for a gap in the obj vnums, so we can allocate it to this obj
  for (POSITION ObjPos = m_ObjectList.GetHeadPosition (); 
        ObjPos && (vnum == -1); )
    {
    obj = m_ObjectList.GetNext (ObjPos);
    if ((prevVnum != INT_MAX) && (obj->vnum > (prevVnum + 1)))
      vnum = prevVnum + 1;
    prevVnum = obj->vnum;
    prevObj = obj;    // remember previous obj
    }

  // no gap found
  if (vnum == -1)
    if (prevVnum == INT_MAX)    // no objects - take lowest available vnum
      vnum = m_Area->obj_low_vnum;
    else
      {
      vnum = prevVnum + 1;      // take highest, plus 1
      prevObj = NULL;          // force an "addtail"
      }

  if (vnum < m_Area->obj_low_vnum || vnum > m_Area->obj_hi_vnum)
    {
    ::AfxMessageBox (CFormat ("No free object vnums in the range %i to %i",
          m_Area->obj_low_vnum, m_Area->obj_hi_vnum),
        MB_ICONEXCLAMATION);
    return NULL;
    }

  obj = new CMUDObject (RUNTIME_CLASS(CObjectView), this);
  obj->vnum = vnum;   // use our new vnum

  // insert in numeric order (insert before because prevObj is *higher*)
  if (prevObj)
    m_ObjectList.InsertBefore (m_ObjectList.Find (prevObj, NULL), obj);    // and add it to our list
  else
    m_ObjectList.AddTail (obj);    // and add it to our list
  HTREEITEM hdlMobItem = pView->AddTreeItem (obj, pView->m_hdlTreeObjects);
  pView->GetTreeCtrl().SortChildren (pView->m_hdlTreeObjects);    // put in right part of tree ctrl
  if (bSelect)
    pView->GetTreeCtrl().Select (hdlMobItem, TVGN_CARET);   // select it
  SetModifiedFlag ();

  return obj;

  } // end of CAreaEditorDoc::AddObject

CRoom * CAreaEditorDoc::AddRoom (CAreaEditorView * pView,
                                 const bool bSelect)
  {
    int vnum = -1,
      prevVnum = INT_MAX;

  CRoom * room,
        * prevRoom = NULL;

  // look for a gap in the room vnums, so we can allocate it to this room
  for (POSITION roomPos = m_RoomList.GetHeadPosition (); 
        roomPos && (vnum == -1); )
    {
    room = m_RoomList.GetNext (roomPos);
    if ((prevVnum != INT_MAX) && (room->vnum > (prevVnum + 1)))
      vnum = prevVnum + 1;
    prevVnum = room->vnum;
    prevRoom = room;    // remember previous room
    }

  // no gap found
  if (vnum == -1)
    if (prevVnum == INT_MAX)    // no rooms - take lowest available vnum
      vnum = m_Area->room_low_vnum;
    else
      {
      vnum = prevVnum + 1;      // take highest, plus 1
      prevRoom = NULL;          // force an "addtail"
      }

  if (vnum < m_Area->room_low_vnum || vnum > m_Area->room_hi_vnum)
    {
    ::AfxMessageBox (CFormat ("No free room vnums in the range %i to %i",
          m_Area->room_low_vnum, m_Area->room_hi_vnum),
        MB_ICONEXCLAMATION);
    return NULL;
    }

  room = new CRoom (RUNTIME_CLASS(CRoomView), this);
  room->vnum = vnum;   // use our new vnum

  // insert in numeric order (insert before because prevRoom is *higher*)
  if (prevRoom)
    m_RoomList.InsertBefore (m_RoomList.Find (prevRoom, NULL), room);    // and add it to our list
  else
    m_RoomList.AddTail (room);    // and add it to our list
  HTREEITEM hdlRoomItem = pView->AddTreeItem (room, pView->m_hdlTreeRooms);
  pView->GetTreeCtrl().SortChildren (pView->m_hdlTreeRooms);    // put in right part of tree ctrl
  if (bSelect)
    pView->GetTreeCtrl().Select (hdlRoomItem, TVGN_CARET);   // select it
  SetModifiedFlag ();

  return room;
  } // end of CAreaEditorDoc::AddRoom


void CAreaEditorDoc::OnAreaWalkthrough() 
{
CWalkthroughDlg dlg;

  dlg.m_pDoc = this;

HTREEITEM hdlItem = m_leftview->GetItem ();

  if (hdlItem)
    {
    CMUDitem * pItem = (CMUDitem *) m_leftview->GetTreeCtrl().GetItemData (hdlItem);

    // if a room item, start with that one
    if (pItem && strcmp (pItem->Type (), "room") == 0)
      dlg.m_room = (CRoom *) pItem;
    } // end of having a selected tree view item


  dlg.DoModal ();	

  // select the room we have travelled to - they probably want to amend it a bit

  if (dlg.m_room)
    dlg.m_room->GoTo ();
}

void CAreaEditorDoc::OnUpdateAreaWalkthrough(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (!m_RoomList.IsEmpty ());
}


void CAreaEditorDoc::OnViewWarnings() 
{
  if (!m_strErrorMessage.IsEmpty ())
    {
    // show the errors

    // MODELESS dialog here

    CAreaLoadingProblems * dlg = new CAreaLoadingProblems;
    dlg->m_strErrors = CFormat ("Problems %s area: ", (LPCTSTR) m_strWarningType);
    dlg->m_strErrors += GetTitle () + ENDLINE + ENDLINE;
    dlg->m_strErrors += m_strErrorMessage + ENDLINE;
    dlg->m_strErrors += "Press <Esc> to dismiss this window";
    dlg->Create (ID_PROBLEMS_LOADING_AREA, NULL);  // create it
    dlg->ShowWindow(SW_SHOW);  // and, finally, show it - dialog will delete itself

    }
	
}

void CAreaEditorDoc::OnUpdateViewWarnings(CCmdUI* pCmdUI) 
{
	
	pCmdUI->Enable (!m_strErrorMessage.IsEmpty ());

}

void CAreaEditorDoc::OnUpdateFileSave(CCmdUI* pCmdUI) 
{
  pCmdUI->Enable (IsModified ());	
}



int CompareMobile (const void * elem1, const void * elem2)
  {
  CMobile * mob1 = (*((CMobile **) elem1));
  CMobile * mob2 = (*((CMobile **) elem2));

  if (mob1->vnum < mob2->vnum)
    return -1;
  else if (mob1->vnum > mob2->vnum)
    return 1;
  else return 0;

  }   // end of CompareMobile

void CAreaEditorDoc::SortMobiles (void)
  {
POSITION MobilePos;
CTypedPtrArray <CPtrArray, CMobile*> CMobilesArray;
int iCount = m_MobList.GetCount ();
int i;

  CMobilesArray.SetSize (iCount);

  // extract pointers into a simple array
  for (i = 0, MobilePos = m_MobList.GetHeadPosition (); MobilePos; i++)
    CMobilesArray.SetAt (i, m_MobList.GetNext (MobilePos)); 

  // sort the array
  qsort (CMobilesArray.GetData (), 
         iCount,
         sizeof (CMobile *),
         CompareMobile);

  // get rid of old list
  m_MobList.RemoveAll ();

  // re-add in sorted order
  for (i = 0; i < iCount; i++)
    m_MobList.AddTail (CMobilesArray [i]);

  }  // end of CAreaEditorDoc::SortMobiles 

int CompareRoom (const void * elem1, const void * elem2)
  {
  CRoom * room1 = (*((CRoom **) elem1));
  CRoom * room2 = (*((CRoom **) elem2));

  if (room1->vnum < room2->vnum)
    return -1;
  else if (room1->vnum > room2->vnum)
    return 1;
  else return 0;

  }   // end of CompareRoom

void CAreaEditorDoc::SortRooms (void)
  {
POSITION RoomPos;
CTypedPtrArray <CPtrArray, CRoom*> CRoomsArray;
int iCount = m_RoomList.GetCount ();
int i;

  CRoomsArray.SetSize (iCount);

  // extract pointers into a simple array
  for (i = 0, RoomPos = m_RoomList.GetHeadPosition (); RoomPos; i++)
    CRoomsArray.SetAt (i, m_RoomList.GetNext (RoomPos)); 

  // sort the array
  qsort (CRoomsArray.GetData (), 
         iCount,
         sizeof (CRoom *),
         CompareRoom);

  // get rid of old list
  m_RoomList.RemoveAll ();

  // re-add in sorted order
  for (i = 0; i < iCount; i++)
    m_RoomList.AddTail (CRoomsArray [i]);

  }  // end of CAreaEditorDoc::SortRooms 

int CompareObject (const void * elem1, const void * elem2)
  {
  CMUDObject * obj1 = (*((CMUDObject **) elem1));
  CMUDObject * obj2 = (*((CMUDObject **) elem2));

  if (obj1->vnum < obj2->vnum)
    return -1;
  else if (obj1->vnum > obj2->vnum)
    return 1;
  else return 0;

  }   // end of CompareObject

void CAreaEditorDoc::SortObjects (void)
  {
POSITION ObjectPos;
CTypedPtrArray <CPtrArray, CMUDObject*> CObjectsArray;
int iCount = m_ObjectList.GetCount ();
int i;

  CObjectsArray.SetSize (iCount);

  // extract pointers into a simple array
  for (i = 0, ObjectPos = m_ObjectList.GetHeadPosition (); ObjectPos; i++)
    CObjectsArray.SetAt (i, m_ObjectList.GetNext (ObjectPos)); 

  // sort the array
  qsort (CObjectsArray.GetData (), 
         iCount,
         sizeof (CObject *),
         CompareObject);

  // get rid of old list
  m_ObjectList.RemoveAll ();

  // re-add in sorted order
  for (i = 0; i < iCount; i++)
    m_ObjectList.AddTail (CObjectsArray [i]);

  }  // end of CAreaEditorDoc::SortObjects 

