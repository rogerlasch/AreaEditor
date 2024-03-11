/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_AREAVNUMSVIEW_H__670FCF56_4EA7_11D2_AFA0_00A0247B3BFD__INCLUDED_)
#define AFX_AREAVNUMSVIEW_H__670FCF56_4EA7_11D2_AFA0_00A0247B3BFD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AreaVnumsView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAreaVnumsView dialog

class CAreaVnumsView : public CDialog
{
// Construction
public:
	CAreaVnumsView(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAreaVnumsView)
	enum { IDD = IDD_AREA_VNUMS };
	int		m_mob_hi_vnum;
	int		m_mob_low_vnum;
	int		m_obj_hi_vnum;
	int		m_obj_low_vnum;
	int		m_room_hi_vnum;
	int		m_room_low_vnum;
	//}}AFX_DATA

  CArea * m_area;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAreaVnumsView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAreaVnumsView)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AREAVNUMSVIEW_H__670FCF56_4EA7_11D2_AFA0_00A0247B3BFD__INCLUDED_)
