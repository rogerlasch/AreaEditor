/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#include "stdafx.h"
#include "AreaEditor.h"

#include "PrefsP1.h"
#include "PrefsP2.h"
#include "PrefsP3.h"
#include "PrefsP4.h"

void CAreaEditorApp::OnFilePreferences() 
{

CPropertySheet sheet ("Preferences");

CPrefsP1 page1;
CPrefsP2 page2;
CPrefsP3 page3;
#ifdef SPELL_CHECKER
CPrefsP4 page4;
#endif  // SPELL_CHECKER

sheet.AddPage (&page1);
sheet.AddPage (&page2);
sheet.AddPage (&page3);
#ifdef SPELL_CHECKER
  sheet.AddPage (&page4);
#endif  // SPELL_CHECKER
  // page 1
  page1.m_strCommandsFile = App.GetProfileString  (sProfilePreferences, sProfileCommandsFile, "");
  page1.m_strSocialsFile  = App.GetProfileString  (sProfilePreferences, sProfileSocialsFile, "");
  page1.m_strSkillsFile   = App.GetProfileString  (sProfilePreferences, sProfileSkillsFile, "");
  page1.m_strConfigFile   = App.GetProfileString  (sProfilePreferences, sProfileConfigFile, "");

  // page 2
	page2.m_bWarnVnumsOutOfRange = App.GetProfileInt  (sProfilePreferences, sProfileWarnVnums, 1);
	page2.m_bShowWarnings = App.GetProfileInt         (sProfilePreferences, sProfileShowWarnings, 1);
	page2.m_bShowFlagNumbers = App.GetProfileInt      (sProfilePreferences, sProfileShowFlagNumbers, 0);
  page2.m_strFontName = App.GetProfileString        (sProfilePreferences, sProfileScreenFontName, "FixedSys");
	page2.m_iScreenFontSize = App.GetProfileInt       (sProfilePreferences, sProfileScreenFontSize, 9);
  page2.m_bSaveROMPrograms = App.GetProfileInt      (sProfilePreferences, sProfileSaveROMPrograms, 0);
	page2.m_iDefaultAreaType = App.GetProfileInt      (sProfilePreferences, sProfileDefaultAreaType, eSMAUG);

  // page 3
  page3.m_strFontName = App.GetProfileString  (sProfilePreferences, sProfileFontName, "Courier");
	page3.m_iPrinterFontSize = App.GetProfileInt  (sProfilePreferences, sProfileFontSize, 9);
	page3.m_iLeftMargin = App.GetProfileInt  (sProfilePreferences, sProfileLeftMargin, 15);
	page3.m_iTopMargin = App.GetProfileInt  (sProfilePreferences, sProfileTopMargin, 15);
	page3.m_iLinesPerPage = App.GetProfileInt  (sProfilePreferences, sProfileLinesPerpage, 60);
	page3.m_bPrintToFile = App.GetProfileInt  (sProfilePreferences, sProfilePrintToFile, 0);
	page3.m_bShowPrograms = App.GetProfileInt  (sProfilePreferences, sProfileShowPrograms, 0);

#ifdef SPELL_CHECKER

  // page 4

	page4.m_bAreaCheck = CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_AREA_CHECK);
	page4.m_bEditWindow = CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_CHECK_EDIT_WINDOW);
	page4.m_bHelp = CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_HELP_TEXT);
	page4.m_bEnable = CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_ENABLE);
	page4.m_bMobDesc = CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_MOB_DESC);
	page4.m_bMobLong = CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_MOB_LONG); 
	page4.m_bMobName = CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_MOB_NAME);
	page4.m_bMobShort = CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_MOB_SHORT);
	page4.m_bObjActionDesc = CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_OBJECT_ACTIONDESC);
	page4.m_bExtraDesc = CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_EXTRA_DESC);
	page4.m_bObjLong = CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_OBJECT_LONG);
	page4.m_bObjName = CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_OBJECT_NAME);
	page4.m_bObjShort = CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_OBJECT_SHORT);
	page4.m_bRoomDesc = CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_ROOM_DESC);
	page4.m_bRoomName = CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_ROOM_NAME);
	page4.m_bCheckView = CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_CHECK_ON_VIEW);
	page4.m_bAcceptName = CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_ACCEPT_NAME);
	page4.m_bExitDesc = CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_EXIT_DESC);

#endif  // SPELL_CHECKER


  if (sheet.DoModal () != IDOK)
    return;

  // page 1
  App.WriteProfileString  (sProfilePreferences, sProfileCommandsFile, page1.m_strCommandsFile);
  App.WriteProfileString  (sProfilePreferences, sProfileSocialsFile,  page1.m_strSocialsFile);
  App.WriteProfileString  (sProfilePreferences, sProfileSkillsFile,  page1.m_strSkillsFile);
  App.WriteProfileString  (sProfilePreferences, sProfileConfigFile,  page1.m_strConfigFile);

  // page 2
  App.WriteProfileInt     (sProfilePreferences, sProfileWarnVnums,      page2.m_bWarnVnumsOutOfRange);
  App.WriteProfileInt     (sProfilePreferences, sProfileShowWarnings,   page2.m_bShowWarnings);
  App.WriteProfileInt     (sProfilePreferences, sProfileShowFlagNumbers, page2.m_bShowFlagNumbers);

  App.WriteProfileString  (sProfilePreferences, sProfileScreenFontName, page2.m_strFontName);
	App.WriteProfileInt     (sProfilePreferences, sProfileScreenFontSize, page2.m_iScreenFontSize);

  App.WriteProfileInt     (sProfilePreferences, sProfileSaveROMPrograms, page2.m_bSaveROMPrograms);
  App.WriteProfileInt     (sProfilePreferences, sProfileDefaultAreaType, page2.m_iDefaultAreaType);

  // page 3
  App.WriteProfileString  (sProfilePreferences, sProfileFontName, page3.m_strFontName);
	App.WriteProfileInt  (sProfilePreferences,    sProfileFontSize, page3.m_iPrinterFontSize);
	App.WriteProfileInt  (sProfilePreferences,    sProfileLeftMargin, page3.m_iLeftMargin);
	App.WriteProfileInt  (sProfilePreferences,    sProfileTopMargin, page3.m_iTopMargin);
	App.WriteProfileInt  (sProfilePreferences,    sProfileLinesPerpage, page3.m_iLinesPerPage);
	App.WriteProfileInt  (sProfilePreferences,    sProfilePrintToFile, page3.m_bPrintToFile);
	App.WriteProfileInt  (sProfilePreferences,    sProfileShowPrograms, page3.m_bShowPrograms);

  // page 4

#ifdef SPELL_CHECKER

  // no options set yet
  App.m_SpellCheckOptions = 0;

  if (page4.m_bAreaCheck) 
    SET_BIT_NUMBER (App.m_SpellCheckOptions, SK_AREA_CHECK);
  if (page4.m_bEditWindow) 
    SET_BIT_NUMBER (App.m_SpellCheckOptions, SK_CHECK_EDIT_WINDOW);
  if (page4.m_bHelp) 
    SET_BIT_NUMBER (App.m_SpellCheckOptions, SK_HELP_TEXT);
  if (page4.m_bEnable) 
    SET_BIT_NUMBER (App.m_SpellCheckOptions, SK_ENABLE);
  if (page4.m_bMobDesc) 
    SET_BIT_NUMBER (App.m_SpellCheckOptions, SK_MOB_DESC);
  if (page4.m_bMobLong) 
    SET_BIT_NUMBER (App.m_SpellCheckOptions, SK_MOB_LONG); 
  if (page4.m_bMobName) 
    SET_BIT_NUMBER (App.m_SpellCheckOptions, SK_MOB_NAME);
  if (page4.m_bMobShort) 
    SET_BIT_NUMBER (App.m_SpellCheckOptions, SK_MOB_SHORT);
  if (page4.m_bObjActionDesc) 
    SET_BIT_NUMBER (App.m_SpellCheckOptions, SK_OBJECT_ACTIONDESC);
  if (page4.m_bExtraDesc) 
    SET_BIT_NUMBER (App.m_SpellCheckOptions, SK_EXTRA_DESC);
  if (page4.m_bObjLong) 
    SET_BIT_NUMBER (App.m_SpellCheckOptions, SK_OBJECT_LONG);
  if (page4.m_bObjName) 
    SET_BIT_NUMBER (App.m_SpellCheckOptions, SK_OBJECT_NAME);
  if (page4.m_bObjShort) 
    SET_BIT_NUMBER (App.m_SpellCheckOptions, SK_OBJECT_SHORT);
  if (page4.m_bRoomDesc) 
    SET_BIT_NUMBER (App.m_SpellCheckOptions, SK_ROOM_DESC);
  if (page4.m_bRoomName) 
    SET_BIT_NUMBER (App.m_SpellCheckOptions, SK_ROOM_NAME);
	if (page4.m_bCheckView)
    SET_BIT_NUMBER (App.m_SpellCheckOptions, SK_CHECK_ON_VIEW);
	if (page4.m_bAcceptName)
    SET_BIT_NUMBER (App.m_SpellCheckOptions, SK_ACCEPT_NAME);
	if (page4.m_bExitDesc)
    SET_BIT_NUMBER (App.m_SpellCheckOptions, SK_EXIT_DESC);

  // save as a single integer
  App.WriteProfileInt     (sProfilePreferences, "SpellCheckOptions",  
                            App.m_SpellCheckOptions);

#endif  // SPELL_CHECKER

// if config file is specified load it.

  if (!page1.m_strConfigFile.IsEmpty ())
    LoadConfig (page1.m_strConfigFile);

#ifdef SPELL_CHECKER

  // enable spell checker, if wanted in prefs
  if (CHECK_BIT_NUMBER (App.m_SpellCheckOptions, SK_ENABLE))
    App.InitSpellCheck ();      // re-init, in case it was off before
  else
    App.m_bSpellCheckOK = false;    // the user doesn't want the spell checker

  App.SpellPaths ();    // set up path name to dictionary etc.

#endif // SPELL_CHECKER

}
