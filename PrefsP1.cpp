/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// PrefsP1.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "PrefsP1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrefsP1 property page

IMPLEMENT_DYNCREATE(CPrefsP1, CPropertyPage)

CPrefsP1::CPrefsP1() : CPropertyPage(CPrefsP1::IDD)
{
	//{{AFX_DATA_INIT(CPrefsP1)
	m_strCommandsFile = _T("");
	m_strConfigFile = _T("");
	m_strSkillsFile = _T("");
	m_strSocialsFile = _T("");
	//}}AFX_DATA_INIT
}

CPrefsP1::~CPrefsP1()
{
}

void CPrefsP1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrefsP1)
	DDX_Control(pDX, IDC_BROWSE_CONFIG, m_ctlBrowseConfig);
	DDX_Control(pDX, IDC_SOCIALS_FILE, m_ctlSocialsFile);
	DDX_Control(pDX, IDC_SKILLS_FILE, m_ctlSkillsFile);
	DDX_Control(pDX, IDC_CONFIG_FILE, m_ctlConfigFile);
	DDX_Control(pDX, IDC_COMMANDS_FILE, m_ctlCommandsFile);
	DDX_Text(pDX, IDC_COMMANDS_FILE, m_strCommandsFile);
	DDX_Text(pDX, IDC_CONFIG_FILE, m_strConfigFile);
	DDX_Text(pDX, IDC_SKILLS_FILE, m_strSkillsFile);
	DDX_Text(pDX, IDC_SOCIALS_FILE, m_strSocialsFile);
	//}}AFX_DATA_MAP

}


BEGIN_MESSAGE_MAP(CPrefsP1, CPropertyPage)
	//{{AFX_MSG_MAP(CPrefsP1)
	ON_BN_CLICKED(IDC_BROWSE_COMMANDS, OnBrowseCommands)
	ON_BN_CLICKED(IDC_BROWSE_SKILLS, OnBrowseSkills)
	ON_BN_CLICKED(IDC_BROWSE_SOCIALS, OnBrowseSocials)
	ON_BN_CLICKED(IDC_BROWSE_CONFIG, OnBrowseConfig)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrefsP1 message handlers

void CPrefsP1::OnBrowseCommands() 
{
	CFileDialog	dlg(TRUE,						// TRUE for FileOpen
					"dat",						// default extension
					"commands.dat",						// initial file name
					OFN_HIDEREADONLY|OFN_FILEMUSTEXIST,
					"Commands files (*.dat)|*.dat||");
	dlg.m_ofn.lpstrTitle = "Select commands file";
	if (dlg.DoModal() != IDOK)
		return;

	m_ctlCommandsFile.SetWindowText (dlg.GetPathName());
	
}

void CPrefsP1::OnBrowseSkills() 
{
	CFileDialog	dlg(TRUE,						// TRUE for FileOpen
					"dat",						// default extension
					"skills.dat",						// initial file name
					OFN_HIDEREADONLY|OFN_FILEMUSTEXIST,
					"Skills table files (*.dat)|*.dat||");
	dlg.m_ofn.lpstrTitle = "Select skills file";

	if (dlg.DoModal() != IDOK)
		return;

	m_ctlSkillsFile.SetWindowText (dlg.GetPathName());
	
}

void CPrefsP1::OnBrowseSocials() 
{
	CFileDialog	dlg(TRUE,						// TRUE for FileOpen
					"dat",						// default extension
					"socials.dat",						// initial file name
					OFN_HIDEREADONLY|OFN_FILEMUSTEXIST,
					"Socials files (*.dat)|*.dat||");
	dlg.m_ofn.lpstrTitle = "Select socials file";
	if (dlg.DoModal() != IDOK)
		return;

	m_ctlSocialsFile.SetWindowText (dlg.GetPathName());
	
	
}

void CPrefsP1::OnBrowseConfig() 
{
	CFileDialog	dlg(TRUE,						// TRUE for FileOpen
					"dat",						// default extension
					"config.dat",						// initial file name
					OFN_HIDEREADONLY|OFN_FILEMUSTEXIST,
					"config files (*.dat)|*.dat||");
	dlg.m_ofn.lpstrTitle = "Select config file";
	if (dlg.DoModal() != IDOK)
		return;

	m_ctlConfigFile.SetWindowText (dlg.GetPathName());
	
	
}
