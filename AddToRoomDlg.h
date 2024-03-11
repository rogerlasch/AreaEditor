/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_ADDTOROOMDLG_H__F848CAF4_0572_11D2_A20B_0000B4595568__INCLUDED_)
#define AFX_ADDTOROOMDLG_H__F848CAF4_0572_11D2_A20B_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AddToRoomDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddToRoomDlg dialog

class CAddToRoomDlg : public CDialog
{
// Construction
public:
	CAddToRoomDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddToRoomDlg)
	enum { IDD = IDD_ADD_TO_ROOM };
	int		m_iAddType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddToRoomDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddToRoomDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDTOROOMDLG_H__F848CAF4_0572_11D2_A20B_0000B4595568__INCLUDED_)
