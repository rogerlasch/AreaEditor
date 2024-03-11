/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_AREASUMMARY_H__3094D403_00E9_11D2_A20B_0000B4595568__INCLUDED_)
#define AFX_AREASUMMARY_H__3094D403_00E9_11D2_A20B_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AreaSummary.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAreaSummary dialog

class CAreaSummary : public CDialog
{
// Construction
public:
	CAreaSummary(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAreaSummary)
	enum { IDD = IDD_DOCUMENT_INFO };
	int		m_helps;
	int		m_mobiles;
	int		m_objects;
	int		m_repairs;
	int		m_resets;
	int		m_rooms;
	int		m_shops;
	int		m_mobile_programs;
	int		m_object_affects;
	int		m_object_programs;
	int		m_room_programs;
	int		m_room_exits;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAreaSummary)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAreaSummary)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AREASUMMARY_H__3094D403_00E9_11D2_A20B_0000B4595568__INCLUDED_)
