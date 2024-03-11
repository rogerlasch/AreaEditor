/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_MOBILENAMEPAGE_H__ACFBE913_EB82_11D1_A20A_0000B4595568__INCLUDED_)
#define AFX_MOBILENAMEPAGE_H__ACFBE913_EB82_11D1_A20A_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MobileNamePage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMobileNamePage dialog

class CMobileNamePage : public CDialog
{
// Construction
public:
	CMobileNamePage(CWnd* pParent = NULL);   // standard constructor
  ~CMobileNamePage ();    // destructor

// Dialog Data
	//{{AFX_DATA(CMobileNamePage)
	enum { IDD = IDD_MOBILE_NAME };
	CEdit	m_ctlShortDescription;
	CEdit	m_ctlLongDescription;
	CEdit	m_ctlName;
	CComboBox	m_ctlSex;
	CComboBox	m_ctlSpecFun;
	CEdit	m_ctlDescription;
	CString	m_player_name;
	CString	m_short_descr;
	CString	m_long_descr;
	CString	m_description;
	int		m_level;
	int		m_vnum;
	//}}AFX_DATA

  CMobile * m_mob;    // which mobile we are displaying
  CFont * m_font;

  int m_OriginalVnum;   // original vnum before editing

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMobileNamePage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

  void EditDescription (CEdit & ctlDescription, 
                        const bool bEndline = true,
                        const bool bSpellCheck = false);

	// Generated message map functions
	//{{AFX_MSG(CMobileNamePage)
	afx_msg void OnEditDescription();
	afx_msg void OnEditNames();
	afx_msg void OnEditShortDescription();
	afx_msg void OnEditLongDescription();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOBILENAMEPAGE_H__ACFBE913_EB82_11D1_A20A_0000B4595568__INCLUDED_)
