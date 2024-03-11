/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_ROOMMAPVIEW_H__42F26DF6_F10D_11D1_A20A_0000B4595568__INCLUDED_)
#define AFX_ROOMMAPVIEW_H__42F26DF6_F10D_11D1_A20A_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RoomMapView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRoomMapView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CRoomMapView : public CFormView
{
protected:
	CRoomMapView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CRoomMapView)

// Form Data
public:
	//{{AFX_DATA(CRoomMapView)
	enum { IDD = IDD_OBJECT_ROOM_MAP };
	CString	m_entry;
	int		m_vnum;
	int		m_x;
	int		m_y;
	//}}AFX_DATA

// Attributes
public:

  CRoomMap * m_map;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRoomMapView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CRoomMapView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CRoomMapView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROOMMAPVIEW_H__42F26DF6_F10D_11D1_A20A_0000B4595568__INCLUDED_)
