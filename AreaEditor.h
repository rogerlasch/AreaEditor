/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of this file
*/

// AreaEditor.h : main header file for the AREAEDITOR application
//

#if !defined(AFX_AREAEDITOR_H__30BE0357_E9F1_11D1_A20A_0000B4595568__INCLUDED_)
#define AFX_AREAEDITOR_H__30BE0357_E9F1_11D1_A20A_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

// area types
typedef enum
  {
  eAsk,     // ask which type to use
  eSMAUG,
  eROM,
  } t_areatype;

#define READY "For Help, press F1"
#define MAX_SPELL_ERRORS 10

// names used in the Registry to locate various preferences
#define sProfilePreferences "Global prefs" 

// files
#define sProfileCommandsFile "Commands file" 
#define sProfileSocialsFile "Socials file" 
#define sProfileSkillsFile "Skills file" 
#define sProfileConfigFile "Config file" 

// general
#define sProfileWarnVnums "Warn vnums out of range" 
#define sProfileShowWarnings "Show warnings" 
#define sProfileShowFlagNumbers "Show flag numbers" 

#define sProfileScreenFontName  "Screen font name"
#define sProfileScreenFontSize  "Screen font size"

#define sProfileSaveROMPrograms "Save ROM programs" 
#define sProfileDefaultAreaType "Default area type" 

// printing
#define sProfileFontName  "Font name"
#define sProfileFontSize  "Font size"
#define sProfileLeftMargin "Left margin"
#define sProfileTopMargin "Top margin"
#define sProfileLinesPerpage  "Lines per page"
#define sProfilePrintToFile "Print to file"
#define sProfileShowPrograms "Show programs"

// for loading commands, skills, socials

#define KEY( literal, field, value )					\
  		if (word == literal)	\
	  			{					\
			    field  = value;			\
			    fMatch = TRUE;			\
			    break;				\
		  		}

/*
 * A SMAUG spell
 */

class	CSkillAffect : public CObject
{

  public:

    CSkillAffect ();  // constructor

    CString		duration;
    int		    location;
    CString		modifier;
    int			  bitvector;
};

typedef CTypedPtrList <CPtrList, CSkillAffect*> CSkillAffectList;

/*
 * Skills include spells as a particular case.
 */
class CSkill : public CObject
{

  public:

  CSkill ();   // constructor
  ~CSkill ();  // destructor

    void AddToListBox (CListBox & ctlListBox, 
                       const char * strDescription = "",
                       const bool bSelectIt = false);

    CString	name;			/* Name of skill		*/
    int	skill_level[MAX_CLASS];	/* Level needed by class	*/
    int	skill_adept[MAX_CLASS];	/* Max attainable % in this skill */
    int	race_level[MAX_CLASS];	/* Racial abilities: level      */ 
    int	race_adept[MAX_CLASS];	/* Racial abilities: adept      */
    CString	spell_skill_fun;		/* Spell pointer (for spells)	*/
    int	target;			/* Legal targets		*/
    int	minimum_position;	/* Position for caster / user	*/
    int	slot;			/* Slot for #OBJECT loading	*/
    int	min_mana;		/* Minimum mana used		*/
    int	beats;			/* Rounds required to use skill	*/
    CString	noun_damage;		/* Damage message		*/
    CString	msg_off;		/* Wear off message		*/
    int	guild;			/* Which guild the skill belongs to */
    int	min_level;		/* Minimum level to be able to cast */
    int	type;			/* Spell/Skill/Weapon/Tongue	*/
    int		flags;			/* extra stuff			*/
    int  info;    /* Spell action/class/etc - new in 1.4 */
    int  range;   /* Range of spell (rooms) - new in 1.4 */
    CString	hit_char;		/* Success message to caster	*/
    CString hit_dest;   /* Success message to dest room	 - new in 1.4 */
    CString	hit_vict;		/* Success message to victim	*/
    CString	hit_room;		/* Success message to room	*/
    CString	miss_char;		/* Failure message to caster	*/
    CString	miss_vict;		/* Failure message to victim	*/
    CString	miss_room;		/* Failure message to room	*/
    CString	die_char;		/* Victim death msg to caster	*/
    CString	die_vict;		/* Victim death msg to victim	*/
    CString	die_room;		/* Victim death msg to room	*/
    CString	imm_char;		/* Victim immune msg to caster	*/
    CString	imm_vict;		/* Victim immune msg to victim	*/
    CString	imm_room;		/* Victim immune msg to room	*/
    CString	dice;			/* Dice roll			*/
    int		value;			/* Misc value			*/
    int	saves;			/* What saving spell applies	*/
    int	difficulty;		/* Difficulty of casting/learning */
    CSkillAffectList affects;		/* Spell affects, if any	*/
    CString	components;		/* Spell components, if any	*/
    CString	teachers;		/* Skill requires a special teacher */
    int	participants;		/* # of required participants	*/

// referenced count

    int iReferenced;

};

typedef CTypedPtrList <CPtrList, CSkill*> CSkillList;


const int eCmdNone = 0;       // no special processing
const int eCmdObject = 0x1;   // command followed by object name
const int eCmdRoom = 0x2;     // command followed by room name
const int eCmdMobile = 0x4;   // command followed by mob name
const int eCmdName = 0x8;     // command followed by player name
const int eCmdRepeat = 0x10;  // command followed another command
const int eCmdSpell = 0x20;   // command followed by a spell

class CCommand : public CObject
{

  public:

  CCommand ();   // constructor

    void AddToListBox (CListBox & ctlListBox, 
                       const char * strDescription = "",
                       const bool bSelectIt = false);

    CString		name;
    CString		do_fun;
    int		position;
    int		level;
    int		log;
    int   flags;    // new in 1.4

// Nick's parsing flags

    int   FollowedBy;  // is command followed by something, eg. MPMLOAD 1234

// referenced count

    int iReferenced;
};

typedef CTypedPtrList <CPtrList, CCommand*> CCommandList;

class CSocial : public CObject
{
  public:

    CSocial ();  // constructor

    void AddToListBox (CListBox & ctlListBox, 
                       const char * strDescription = "",
                       const bool bSelectIt = false);

    CString		name;
    CString		char_no_arg;
    CString		others_no_arg;
    CString		char_found;
    CString		others_found;
    CString		vict_found;
    CString		char_auto;
    CString		others_auto;

// referenced count

    int iReferenced;

};

typedef CTypedPtrList <CPtrList, CSocial*> CSocialList;


//================================================================================
// This is for our tabs in our form view property pages

class CTabPage : public CObject
{
  public:

    CTabPage () { m_pDlg = NULL; 
                  m_bCreated = false; 
                  m_DlgID = -1; }    // constructor

    ~CTabPage () { delete m_pDlg; } // destructor

    CString		m_name;
    CDialog*  m_pDlg;
    bool      m_bCreated;
    int       m_DlgID;


};

typedef CTypedPtrArray<CObArray, CTabPage*> CTabPageArray;

/////////////////////////////////////////////////////////////////////////////
// CAreaEditorApp:
// See AreaEditor.cpp for the implementation of this class
//

class CAreaEditorApp : public CWinApp
{
public:
	CAreaEditorApp();
	~CAreaEditorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAreaEditorApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnIdle(LONG lCount);
	virtual BOOL SaveAllModified();
	//}}AFX_VIRTUAL

  DWORD platform;
  bool m_bShowInitialDelay;

  CSkillList m_SkillList;   // list of loaded skills
  bool m_bSkillsDirty;
  CCommandList m_CommandList; // list of loaded commands
  bool m_bCommandsDirty;
  CSocialList m_SocialList; // list of loaded socials
  bool m_bSocialsDirty;

  bool m_bIgnoreValidationErrors;   // if true, give option to proceed after field validation failure

// global preferences

  unsigned int m_nPrinterFontSize;
  unsigned int m_nPrinterLeftMargin;
  unsigned int m_nPrinterTopMargin;
  unsigned int m_nPrinterLinesPerPage;
  CString      m_strPrinterFont;

#ifdef SPELL_CHECKER

  bool m_bSpellCheckOK;
  SSCE_S16 m_SpellCheckSid;   // session ID for spell checker
  int m_iSpellErrorCount;     // maximum of MAX_SPELL_ERRORS if not registered

#endif // SPELL_CHECKER

  unsigned int m_SpellCheckOptions;  // bit mask, see stdafx.h

// finding stuff

  CStringList m_strFindText;
  BOOL m_bMatchCase;
  BOOL m_bAllAreas;
  int  m_iFindType;             // what sort of find we did last

	void ShowTipAtStartup(void);

  CMultiDocTemplate * m_pDocTemplate;

  void fread_skill (CFileRead & FileRead);
  void fread_command (CFileRead & FileRead);
  void fread_social (CFileRead & FileRead);

  void LoadSkills (const CString strFileName);
  void LoadCommands (const CString strFileName);
  void LoadSocials (const CString strFileName);
  void SortSocials (void);
  void SortCommands (void);
  void SortSkills (void);
  void LoadConfig (const CString strFileName);
  void SetUpDefaultFlags (void);
  void SetUpDefaultLists(void);  

  void DeleteSkills (void);
  void DeleteCommands (void);
  void DeleteSocials (void);

  void Import (t_areatype AreaType, CString newName = "");

  // spell check stuff
  void InitSpellCheck (void);
  void SpellCheck (CWnd * pWnd, CEdit * pEdit);
  void SpellPaths (void);

// Implementation

	//{{AFX_MSG(CAreaEditorApp)
	afx_msg void OnAppAbout();
	afx_msg void OnHelpTipoftheday();
	afx_msg void OnSkillsLoad();
	afx_msg void OnSkillsEdit();
	afx_msg void OnUpdateSkillsEdit(CCmdUI* pCmdUI);
	afx_msg void OnCommandsLoad();
	afx_msg void OnSocialsLoad();
	afx_msg void OnUpdateSkillsLoad(CCmdUI* pCmdUI);
	afx_msg void OnSkillsClose();
	afx_msg void OnUpdateSkillsClose(CCmdUI* pCmdUI);
	afx_msg void OnSkillsSave();
	afx_msg void OnUpdateSkillsSave(CCmdUI* pCmdUI);
	afx_msg void OnCommandsSave();
	afx_msg void OnUpdateCommandsSave(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCommandsLoad(CCmdUI* pCmdUI);
	afx_msg void OnCommandsClose();
	afx_msg void OnUpdateCommandsClose(CCmdUI* pCmdUI);
	afx_msg void OnSocialsClose();
	afx_msg void OnUpdateSocialsClose(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSocialsLoad(CCmdUI* pCmdUI);
	afx_msg void OnSocialsSave();
	afx_msg void OnUpdateSocialsSave(CCmdUI* pCmdUI);
	afx_msg void OnFilePreferences();
	afx_msg void OnEditIgnoreValidationErrors();
	afx_msg void OnUpdateEditIgnoreValidationErrors(CCmdUI* pCmdUI);
	afx_msg void OnFileImportRom();
	afx_msg void OnFileImportSmaug();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AREAEDITOR_H__30BE0357_E9F1_11D1_A20A_0000B4595568__INCLUDED_)


/******************************************************************************
* Copyright (C) 2006 Nick Gammon.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining
* a copy of this software and associated documentation files (the
* "Software"), to deal in the Software without restriction, including
* without limitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to
* permit persons to whom the Software is furnished to do so, subject to
* the following conditions:
*
* The above copyright notice and this permission notice shall be
* included in all copies or substantial portions of the Software.
*
* The software is provided "as is", without warranty of any kind,
* express or implied, including but not limited to the warranties of
* merchantability, fitness for a particular purpose and noninfringement.
* In no event shall the authors or copyright holders be liable for any
* claim, damages or other liability, whether in an action of contract,
* tort or otherwise, arising from, out of or in connection with the
* software or the use or other dealings in the software.
******************************************************************************/
