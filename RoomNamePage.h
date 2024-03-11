/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_ROOMNAMEPAGE_H__811BAEE4_F371_11D1_A20B_0000B4595568__INCLUDED_)
#define AFX_ROOMNAMEPAGE_H__811BAEE4_F371_11D1_A20B_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RoomNamePage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRoomNamePage dialog

class CRoomNamePage : public CDialog
{
// Construction
public:
	CRoomNamePage(CWnd* pParent = NULL);   // standard constructor
  ~CRoomNamePage ();    // destructor

// Dialog Data
	//{{AFX_DATA(CRoomNamePage)
	enum { IDD = IDD_ROOM_NAME };
	CEdit	m_ctlName;
	CEdit	m_ctlTunnel;
	CStatic	m_ctlTunnelLabel;
	CStatic	m_ctlManaRateLabel;
	CEdit	m_ctlManaRate;
	CStatic	m_ctlHealRateLabel;
	CEdit	m_ctlHealRate;
	CStatic	m_ctlClanLabel;
	CEdit	m_ctlClan;
	CEdit	m_ctlTeleportDelay;
	CButton	m_ctlTeleportChoose;
	CButton	m_ctlTeleportGoto;
	CEdit	m_ctlDescTeleport;
	CEdit	m_ctlTeleportVnum;
	CComboBox	m_ctlSectorType;
	CEdit	m_ctlDescription;
	CString	m_description;
	CString	m_name;
	int		m_vnum;
	int		m_tele_vnum;
	int		m_tunnel;
	int		m_tele_delay;
	CString	m_clan;
	int		m_heal_rate;
	int		m_mana_rate;
	//}}AFX_DATA


  CRoom * m_room;
  CFont * m_font;

  int m_OriginalVnum;   // original vnum before editing

  void UpdateTeleport (void);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRoomNamePage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

  void EditDescription (CEdit & ctlDescription, 
                        const bool bEndline = true,
                        const bool bSpellCheck = false);

	// Generated message map functions
	//{{AFX_MSG(CRoomNamePage)
	afx_msg void OnEditDescription();
	afx_msg void OnTeleportChoose();
	afx_msg void OnTeleportGoto();
	afx_msg void OnChangeTeleVnum();
	afx_msg void OnEditNames();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROOMNAMEPAGE_H__811BAEE4_F371_11D1_A20B_0000B4595568__INCLUDED_)
