/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_ROOMFLAGSPAGE_H__811BAEE5_F371_11D1_A20B_0000B4595568__INCLUDED_)
#define AFX_ROOMFLAGSPAGE_H__811BAEE5_F371_11D1_A20B_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RoomFlagsPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRoomFlagsPage dialog

class CRoomFlagsPage : public CDialog
{
// Construction
public:
	CRoomFlagsPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRoomFlagsPage)
	enum { IDD = IDD_ROOM_FLAGS };
	BOOL	m_chaotic;
	BOOL	m_clanstoreroom;
	BOOL	m_dark;
	BOOL	m_death;
	BOOL	m_donation;
	BOOL	m_indoors;
	BOOL	m_lawful;
	BOOL	m_logspeech;
	BOOL	m_neutral;
	BOOL	m_no_astral;
	BOOL	m_no_magic;
	BOOL	m_no_mob;
	BOOL	m_no_recall;
	BOOL	m_no_summon;
	BOOL	m_nodrop;
	BOOL	m_nodropall;
	BOOL	m_nofloor;
	BOOL	m_pet_shop;
	BOOL	m_private;
	BOOL	m_prototype;
	BOOL	m_safe;
	BOOL	m_silence;
	BOOL	m_solitary;
	BOOL	m_teleport;
	BOOL	m_teleshowdesc;
	BOOL	m_tunnel;
	//}}AFX_DATA

  CRoom * m_room;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRoomFlagsPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRoomFlagsPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROOMFLAGSPAGE_H__811BAEE5_F371_11D1_A20B_0000B4595568__INCLUDED_)
