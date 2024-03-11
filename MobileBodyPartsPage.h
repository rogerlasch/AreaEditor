/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_MOBILEBODYPARTSPAGE_H__4B7C1BD6_EDF7_11D1_A20A_0000B4595568__INCLUDED_)
#define AFX_MOBILEBODYPARTSPAGE_H__4B7C1BD6_EDF7_11D1_A20A_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MobileBodyPartsPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMobileBodyPartsPage dialog

class CMobileBodyPartsPage : public CDialog
{
// Construction
public:
	CMobileBodyPartsPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMobileBodyPartsPage)
	enum { IDD = IDD_MOBILE_BODY_PARTS };
	BOOL	m_arms;
	BOOL	m_beak;
	BOOL	m_brains;
	BOOL	m_claws;
	BOOL	m_ear;
	BOOL	m_eye;
	BOOL	m_eyestalks;
	BOOL	m_fangs;
	BOOL	m_feathers;
	BOOL	m_feet;
	BOOL	m_fins;
	BOOL	m_fingers;
	BOOL	m_forelegs;
	BOOL	m_guts;
	BOOL	m_hands;
	BOOL	m_haunch;
	BOOL	m_head;
	BOOL	m_heart;
	BOOL	m_horns;
	BOOL	m_legs;
	BOOL	m_paws;
	BOOL	m_scales;
	BOOL	m_sharpscales;
	BOOL	m_tail;
	BOOL	m_tailattack;
	BOOL	m_tentacles;
	BOOL	m_tusks;
	BOOL	m_wings;
	BOOL	m_hooves;
	BOOL	m_long_tongue;
	//}}AFX_DATA

  CMobile * m_mob;    // which mobile we are displaying


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMobileBodyPartsPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMobileBodyPartsPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOBILEBODYPARTSPAGE_H__4B7C1BD6_EDF7_11D1_A20A_0000B4595568__INCLUDED_)
