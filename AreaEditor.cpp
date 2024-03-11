/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// AreaEditor.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "AreaEditor.h"
#include <Delayimp.h>   // For error handling & advanced features

#include "MainFrm.h"
#include "ChildFrm.h"
#include "AreaEditorDoc.h"
#include "AreaEditorView.h"

#include "MobileView.h"
#include "ObjectView.h"
#include "RoomView.h"
#include "AreaView.h"

#include "StatLink.h"
#include "WelcomeDlg.h"
#include "Welcome1Dlg.h"
#include "CreditsDlg.h"

#include "winplace.h"
#include "StatLink.h"

#ifdef SPELL_CHECKER

// use the spell checker library     
#pragma comment( lib, "g:\\SentrySpellCheck\\SDK\\LIB\\SSCE5232.LIB" )

// Statically link __delayLoadHelper/__FUnloadDelayLoadedDLL
#pragma comment( lib, "Delayimp.lib")

// Tell the linker that the spell check DLL should be delay loaded
#pragma comment(linker, "/DelayLoad:SSCE5232.DLL")

#endif // SPELL_CHECKER

static TCHAR BASED_CODE szCtrlBars[] = _T("CtrlBars");

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAreaEditorApp

BEGIN_MESSAGE_MAP(CAreaEditorApp, CWinApp)
	//{{AFX_MSG_MAP(CAreaEditorApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_HELP_TIPOFTHEDAY, OnHelpTipoftheday)
	ON_COMMAND(ID_SKILLS_LOAD, OnSkillsLoad)
	ON_COMMAND(ID_SKILLS_EDIT, OnSkillsEdit)
	ON_UPDATE_COMMAND_UI(ID_SKILLS_EDIT, OnUpdateSkillsEdit)
	ON_COMMAND(ID_COMMANDS_LOAD, OnCommandsLoad)
	ON_COMMAND(ID_SOCIALS_LOAD, OnSocialsLoad)
	ON_UPDATE_COMMAND_UI(ID_SKILLS_LOAD, OnUpdateSkillsLoad)
	ON_COMMAND(ID_SKILLS_CLOSE, OnSkillsClose)
	ON_UPDATE_COMMAND_UI(ID_SKILLS_CLOSE, OnUpdateSkillsClose)
	ON_COMMAND(ID_SKILLS_SAVE, OnSkillsSave)
	ON_UPDATE_COMMAND_UI(ID_SKILLS_SAVE, OnUpdateSkillsSave)
	ON_COMMAND(ID_COMMANDS_SAVE, OnCommandsSave)
	ON_UPDATE_COMMAND_UI(ID_COMMANDS_SAVE, OnUpdateCommandsSave)
	ON_UPDATE_COMMAND_UI(ID_COMMANDS_LOAD, OnUpdateCommandsLoad)
	ON_COMMAND(ID_COMMANDS_CLOSE, OnCommandsClose)
	ON_UPDATE_COMMAND_UI(ID_COMMANDS_CLOSE, OnUpdateCommandsClose)
	ON_COMMAND(ID_SOCIALS_CLOSE, OnSocialsClose)
	ON_UPDATE_COMMAND_UI(ID_SOCIALS_CLOSE, OnUpdateSocialsClose)
	ON_UPDATE_COMMAND_UI(ID_SOCIALS_LOAD, OnUpdateSocialsLoad)
	ON_COMMAND(ID_SOCIALS_SAVE, OnSocialsSave)
	ON_UPDATE_COMMAND_UI(ID_SOCIALS_SAVE, OnUpdateSocialsSave)
	ON_COMMAND(ID_FILE_PREFERENCES, OnFilePreferences)
	ON_COMMAND(ID_EDIT_IGNORE_VALIDATION_ERRORS, OnEditIgnoreValidationErrors)
	ON_UPDATE_COMMAND_UI(ID_EDIT_IGNORE_VALIDATION_ERRORS, OnUpdateEditIgnoreValidationErrors)
	ON_COMMAND(ID_FILE_IMPORT_ROM, OnFileImportRom)
	ON_COMMAND(ID_FILE_IMPORT_SMAUG, OnFileImportSmaug)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAreaEditorApp construction

CAreaEditorApp::CAreaEditorApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CAreaEditorApp object

CAreaEditorApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CAreaEditorApp initialization

BOOL CAreaEditorApp::InitInstance()
{

  m_bShowInitialDelay = true;
  m_bMatchCase = false;   // default case insensitive
  m_bAllAreas = false;   // default search one area
  m_iFindType = eFindSummary; // default summary find
  m_bIgnoreValidationErrors = false;
#ifdef SPELL_CHECKER
  m_bSpellCheckOK = false;
  m_SpellCheckOptions = 0;  // spell check options
  m_iSpellErrorCount = 0;
#endif  // SPELL_CHECKER
  m_bSkillsDirty = false;
  m_bCommandsDirty = false;
  m_bSocialsDirty = false;

	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

//  AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
//	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// You should modify this string to be something appropriate
	// such as the name of your company or organization.
  SetRegistryKey (_T("Gammon Software Solutions"));
	
	LoadStdProfileSettings(9);  // Load standard INI file options (including MRU)

  srand ((unsigned) time(NULL));                // Initialise random number generator

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	m_pDocTemplate = new CMultiDocTemplate(
		IDR_AREAEDTYPE,
		RUNTIME_CLASS(CAreaEditorDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CAreaEditorView));
	AddDocTemplate(m_pDocTemplate);

  // read global prefs from the Registry

  m_nPrinterFontSize                = GetProfileInt     (sProfilePreferences, "PrinterFontSize",        10);
  m_nPrinterLeftMargin              = GetProfileInt     (sProfilePreferences, "PrinterLeftMargin",      15);
  m_nPrinterTopMargin               = GetProfileInt     (sProfilePreferences, "PrinterTopMargin",       15);
  m_nPrinterLinesPerPage            = GetProfileInt     (sProfilePreferences, "PrinterLinesPerPage",    60);
  m_strPrinterFont                  = GetProfileString  (sProfilePreferences, "PrinterFont",         "Courier");
  m_SpellCheckOptions               = GetProfileInt     (sProfilePreferences, "SpellCheckOptions",      0);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	pMainFrame->ShowWindow(m_nCmdShow);

// get main window position from last time

  CWindowPlacement wp;
  wp.Restore ("Main window", pMainFrame, true);

  pMainFrame->LoadBarState(szCtrlBars);

	// The main window has been initialized, so show and update it.
	pMainFrame->UpdateWindow();

  // Don't display a new MDI child window during startup
  if (cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew)
    cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;

// Show first welcome

  BOOL firsttime = GetProfileInt ("Miscellaneous", "First time", 1);	
  UINT version = 0;

  if (firsttime)
    {
    CWelcomeDlg dlg;

    dlg.m_strMessage.Format ("I notice that this is the first time you have used "
                         "Area Editor Version %s on this PC.", SMAUGEDITOR_VERSION);

    dlg.DoModal ();

    WriteProfileInt ("Miscellaneous", "First time", 0);	

    }   // end of first time

  else   // not the first time they have used this program
    
    {

    version = GetProfileInt ("Miscellaneous", "Version", 0);	

    if (version < THISVERSION)  // THISVERSION is defined at start of this module
      {

      CWelcome1Dlg dlg;         // Welcome to this version dialog

      dlg.m_strMessage1.Format ("Welcome to Area Editor, version %s", SMAUGEDITOR_VERSION);
      dlg.m_strMessage2.Format ("Thank you for upgrading Area Editor to version %s",
                                SMAUGEDITOR_VERSION);
  
      dlg.DoModal ();

      // set default area type to "ask" because earlier version will be wrong
      if (version <= 104)
        App.WriteProfileInt     (sProfilePreferences, sProfileDefaultAreaType, eAsk);

      } // end of having lower version than THISVERSION
    
    } // end of not first time


// Write out the new version number if necessary

  if (version != THISVERSION)
    WriteProfileInt ("Miscellaneous", "Version", THISVERSION);	

// Find which version of Windows we are using.

OSVERSIONINFO VersionInformation;

  VersionInformation.dwOSVersionInfoSize = sizeof (VersionInformation);

  GetVersionEx(&VersionInformation);

  platform = VersionInformation.dwPlatformId;

  // in case I make a mistake in the default flags or lists
  try
	{
    // set up default flag names
    SetUpDefaultFlags ();

    // set up default lists
    SetUpDefaultLists ();

	  }   // end of try block
	catch(CException* e)
  	{
    e->ReportError ();
		e->Delete();
	  }

  // auto load config, skills, commands and socials if wanted

  CString strFileName;

  // config
  strFileName   = GetProfileString  (sProfilePreferences, sProfileConfigFile, "");
  if (!strFileName.IsEmpty ())
    LoadConfig (strFileName);

  // commands
  strFileName = GetProfileString  (sProfilePreferences, sProfileCommandsFile, "");
  if (!strFileName.IsEmpty ())
    LoadCommands (strFileName);

  // socials
  strFileName  = GetProfileString  (sProfilePreferences, sProfileSocialsFile, "");
  if (!strFileName.IsEmpty ())
    LoadSocials (strFileName);

  // skills
  strFileName   = GetProfileString  (sProfilePreferences, sProfileSkillsFile, "");
  if (!strFileName.IsEmpty ())
    LoadSkills (strFileName);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

  init_mm ();   // initialise random number generator

  // enable spell checker, if wanted in prefs
  if (CHECK_BIT_NUMBER (m_SpellCheckOptions, SK_ENABLE))
    InitSpellCheck ();

  SpellPaths ();    // set up path name to dictionary etc.

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
  protected:

 	// static controls with hyperlinks
	CStaticLink	m_EmailLink;
	CStaticLink	m_WebLink;
	CStaticLink	m_ChangesLink;

public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CString	m_strVersion;
	CString	m_strEmail;
	CString	m_strWebAddress;
	CString	m_strChangeHistoryAddress;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnCredits();
	afx_msg void OnLicense();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	m_strVersion = _T("");
	m_strEmail = _T("");
	m_strWebAddress = _T("");
	m_strChangeHistoryAddress = _T("");
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Text(pDX, IDC_VERSION_LABEL, m_strVersion);
	DDX_Text(pDX, IDC_EMAIL_ADDRESS, m_strEmail);
	DDX_Text(pDX, IDC_WEB_ADDRESS, m_strWebAddress);
	DDX_Text(pDX, IDC_CHANGES_ADDRESS, m_strChangeHistoryAddress);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_BN_CLICKED(IDC_CREDITS, OnCredits)
	ON_BN_CLICKED(IDC_LICENSE, OnLicense)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CAreaEditorApp::OnAppAbout()
{
	static CAboutDlg aboutDlg;
  
  aboutDlg.m_strVersion = "Version ";
  aboutDlg.m_strVersion += SMAUGEDITOR_VERSION;
  aboutDlg.m_strEmail = MY_EMAIL_ADDRESS;
  aboutDlg.m_strWebAddress = MY_WEB_PAGE;
  aboutDlg.m_strChangeHistoryAddress = CHANGES_WEB_PAGE;

  aboutDlg.DoModal();
}

BOOL CAboutDlg::OnInitDialog() 
{
	// subclass static controls.
	m_EmailLink.SubclassDlgItem(IDC_EMAIL_ADDRESS,  this);
	m_WebLink.SubclassDlgItem(IDC_WEB_ADDRESS, this);
	m_ChangesLink.SubclassDlgItem(IDC_CHANGES_ADDRESS,  this);
	
  m_EmailLink.m_link = MY_EMAIL_ADDRESS;

	return CDialog::OnInitDialog();
}

/////////////////////////////////////////////////////////////////////////////
// CAreaEditorApp commands

// --------------------------------------------------------------------------
// CAreaEditorApp::PreTranslateMessage
//	
// This function intercepts all WM_KEYDOWN messages for the current 
// active view window of the frame window.  If messages are not handled by 
// the view, it will be routed to the MFC message routing routines.
//
// Refer to HandleKeyDownMsg() for more information.
// --------------------------------------------------------------------------
BOOL CAreaEditorApp::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN)
	  {

    // Get the frame window
    CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;

    // Get the active MDI child window.
    if (pFrame)
      {
      CMDIChildWnd *pChild = (CMDIChildWnd *) pFrame->GetActiveFrame();

      if (pChild)
        {
        // Get the active view attached to the active MDI child window.
          CView *pView = pChild->GetActiveView();

        // only do this if it is the tab view that has the focus

          if (pView)
            {
            if (pView->IsKindOf(RUNTIME_CLASS(CMobileView)))
		          if (((CMobileView *) pView)->HandleKeyDownMsg(pMsg))
			          return TRUE;			              
            if (pView->IsKindOf(RUNTIME_CLASS(CObjectView)))
		          if (((CObjectView *) pView)->HandleKeyDownMsg(pMsg))
			          return TRUE;			              
            if (pView->IsKindOf(RUNTIME_CLASS(CRoomView)))
		          if (((CRoomView *) pView)->HandleKeyDownMsg(pMsg))
			          return TRUE;			              
            if (pView->IsKindOf(RUNTIME_CLASS(CAreaView)))
		          if (((CAreaView *) pView)->HandleKeyDownMsg(pMsg))
			          return TRUE;			              
            }
        } // end of having an MDI child view

      } // end of having a frame window

	  } // end of being a WM_KEYDOWN message

	return CWinApp::PreTranslateMessage(pMsg);
}


void CAreaEditorApp::ShowTipAtStartup(void)
{
	// CG: This function added by 'Tip of the Day' component.

	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	CTipDlg dlg;
	if (dlg.m_bStartup)
		dlg.DoModal();

}


void CAreaEditorApp::OnHelpTipoftheday() 
{
	CTipDlg dlg;
	dlg.DoModal();
}

void CAboutDlg::OnCredits() 
{
CCreditsDlg dlg;

  dlg.m_iResourceID = IDR_CREDITS;
  dlg.m_strTitle = "Credits";

  dlg.DoModal ();	
}


// CAreaEditorApp destructor
CAreaEditorApp::~CAreaEditorApp()
  {
  DeleteSkills ();
  DeleteCommands ();
  DeleteSocials ();
  } // end of CAreaEditorApp::~CAreaEditorApp


void CAreaEditorApp::OnEditIgnoreValidationErrors() 
  {
  m_bIgnoreValidationErrors = !m_bIgnoreValidationErrors;
  }


void CAreaEditorApp::OnUpdateEditIgnoreValidationErrors(CCmdUI* pCmdUI) 
{
  pCmdUI->SetCheck (m_bIgnoreValidationErrors);	
}

void CAreaEditorApp::Import (t_areatype AreaType, CString newName)
  {

	// prompt the user (with all document templates)
  if (newName.IsEmpty ())
    {
	  if (!DoPromptFileName(newName, AFX_IDS_OPENFILE,
	    OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, TRUE, NULL))
		  return; // open cancelled
    }

	CAreaEditorDoc* pDocument = (CAreaEditorDoc*) m_pDocTemplate->CreateNewDocument();
	if (pDocument == NULL)
	{
		TRACE0("CDocTemplate::CreateNewDocument returned NULL.\n");
		AfxMessageBox(AFX_IDP_FAILED_TO_CREATE_DOC);
		return;
	}
	ASSERT_VALID(pDocument);

  // this is the important line - set the area type ---------------------
  pDocument->m_AreaType = AreaType;

	BOOL bAutoDelete = pDocument->m_bAutoDelete;
	pDocument->m_bAutoDelete = FALSE;   // don't destroy if something goes wrong
	CFrameWnd* pFrame = m_pDocTemplate->CreateNewFrame(pDocument, NULL);
	pDocument->m_bAutoDelete = bAutoDelete;
	if (pFrame == NULL)
	{
		AfxMessageBox(AFX_IDP_FAILED_TO_CREATE_DOC);
		delete pDocument;       // explicit delete on error
		return;
	}
	ASSERT_VALID(pFrame);

  // open an existing document
	CWaitCursor wait;
	if (!pDocument->OnOpenDocument(newName))
	{
		// user has be alerted to what failed in OnOpenDocument
		TRACE0("CDocument::OnOpenDocument returned FALSE.\n");
		pFrame->DestroyWindow();
		return;
	}
	pDocument->SetPathName(newName);


	m_pDocTemplate->InitialUpdateFrame(pFrame, pDocument, TRUE);
	return;

  } // end of CAreaEditorApp::Import 


void CAreaEditorApp::OnFileImportRom() 
{
	Import (eROM);
}

void CAreaEditorApp::OnFileImportSmaug() 
{
	Import (eSMAUG);
}

BOOL CAreaEditorApp::OnIdle(LONG lCount) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	if (CWinApp::OnIdle(lCount))
    return 1;

//      	App.ShowTipAtStartup();

  return 0;   // no more idle processing
  
  }


LONG WINAPI DelayLoadDllExceptionFilter(PEXCEPTION_POINTERS pep) {
   // Assume we recognize this exception
   LONG lDisposition = EXCEPTION_EXECUTE_HANDLER;  
   // If this is a Delay-load problem, ExceptionInformation[0] points 
   // to a DelayLoadInfo structure that has detailed error info
   PDelayLoadInfo pdli = PDelayLoadInfo(pep->ExceptionRecord
      ->ExceptionInformation[0]);
   // Create a buffer where we construct error messages
   char sz[500] = { 0 };
   switch (pep->ExceptionRecord->ExceptionCode) {
   case VcppException(ERROR_SEVERITY_ERROR, ERROR_MOD_NOT_FOUND):
      // The DLL module was not found at runtime
      wsprintf(sz, "Spell Checker DLL \"%s\" not found\n\n"
                   "Please ensure it is in your path.", pdli->szDll); 
      break;
   case VcppException(ERROR_SEVERITY_ERROR, ERROR_PROC_NOT_FOUND):
      // The DLL module was found but it doesn’t contain the function
      if (pdli->dlp.fImportByName) {
         wsprintf(sz, "Function %s was not found in %s",
            pdli->dlp.szProcName, pdli->szDll);
      } else {
         wsprintf(sz, "Function ordinal %d was not found in %s",
            pdli->dlp.dwOrdinal, pdli->szDll);
      }
      break; 
   default:
      lDisposition = EXCEPTION_CONTINUE_SEARCH;  // We don’t recognize this                                                     // exception
      break;
   }
   if (lDisposition == EXCEPTION_EXECUTE_HANDLER) {
      // We recognized this error and constructed a message, show it
      MessageBox(NULL, sz, NULL, MB_OK);
   }
   return(lDisposition);
}


void CAreaEditorApp::InitSpellCheck (void)
  {
#ifdef SPELL_CHECKER

   // Wrap all calls to delay-load DLL functions inside SEH
   __try 
     {

     SSCE_SetRegTreeName ("Software\\Gammon Software Solutions\\AreaEditor\\SSCE");
     m_bSpellCheckOK = true;

     }
   __except (DelayLoadDllExceptionFilter(GetExceptionInformation())) 
     {
      // Nothing to do in here, thread continues to run normally
     m_bSpellCheckOK = false;
     }
#endif // SPELL_CHECKER


  }

void CAreaEditorApp::SpellCheck (CWnd * pWnd, CEdit * pEdit)
  {
#ifdef SPELL_CHECKER

  if (!m_bSpellCheckOK)
    return;

 CSentrySpellDlg spellDlg(pWnd);
 spellDlg.Check(pEdit,    // which control
                FALSE,    // don't do selection only
                AfxGetResourceHandle (),  // where our resources are
                "CHECKSPELLINGDLG",       // custom dialog box
                "EDITLEXDLG",             // ditto
                "OPTIONSDLG",             // ditto
                "NEWLEXDLG");             // ditto
#endif // SPELL_CHECKER
     
  }



void CAreaEditorApp::SpellPaths (void)
  {
#ifdef SPELL_CHECKER

  if (m_bSpellCheckOK)
    {
    char fullfilename [MAX_PATH];
    CString spellpath;
    CString helpfilename;
    CString userlexfilename;
    char * p;

    // look for spellcheck dictionaries in the subdirectory "spell" from the executable
    if (GetModuleFileName (NULL, fullfilename, sizeof (fullfilename)))
      {
      // remove last part of file name to get working directory
      p = strrchr (fullfilename, '\\');
      if (p)
        *p = 0;
      }
    else
      strcpy (fullfilename, ".");

     // spell checker folder pathname
     spellpath =  fullfilename;
     spellpath += "\\spell";
     // help file is in that folder
     helpfilename = spellpath;
     helpfilename += "\\ssce.hlp";
     // user dictionary is also in that folder
     userlexfilename = spellpath;
     userlexfilename += "\\userdic.tlx";

     // set path to dictionaries
     if (GetProfileString ("SSCE", "MainLexPath", "").IsEmpty ())   // don't override their change
       SSCE_SetMainLexPath (spellpath);   // spell dicts are in spell subdirectory
     // set path to help file
     if (GetProfileString ("SSCE", "HelpFile", "").IsEmpty ())   // don't override their change
       SSCE_SetHelpFile (helpfilename);   // help file is in spell subdirectory
     // set main lexicons up
     if (GetProfileString ("SSCE", "MainLexFiles", "").IsEmpty ())   // don't override their change
       SSCE_SetMainLexFiles ("ssceam.tlx,ssceam2.clx,userdic.tlx"); // default to American dictionaries
     // set path to user dictionary
     if (GetProfileString ("SSCE", "UserLexFiles", "").IsEmpty ())   // don't override their change
       SSCE_SetUserLexFiles (userlexfilename); // take our user dictionary
    }
#endif // SPELL_CHECKER
  }

BOOL CAreaEditorApp::SaveAllModified() 
{
  
  // close all socials
	
  OnSocialsClose ();

  // still have them? must have cancelled

  if (m_bSocialsDirty)
    return FALSE;

  // close all Commands
	
  OnCommandsClose ();

  // still have them? must have cancelled

  if (m_bCommandsDirty)
    return FALSE;

  // close all Skills
	
  OnSkillsClose ();

  // still have them? must have cancelled

  if (m_bSkillsDirty)
    return FALSE;

	return CWinApp::SaveAllModified();
}

void CAboutDlg::OnLicense() 
{
CCreditsDlg dlg;

  dlg.m_iResourceID = IDR_LICENSE;
  dlg.m_strTitle = "License";

  dlg.DoModal ();	
	
}
