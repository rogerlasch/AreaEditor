/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_GENERALFLAGSPAGE_H__87A76363_4DFA_11D2_AFA0_00A0247B3BFD__INCLUDED_)
#define AFX_GENERALFLAGSPAGE_H__87A76363_4DFA_11D2_AFA0_00A0247B3BFD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// GeneralFlagsPage.h : header file
//

#include "defaults.h"

/////////////////////////////////////////////////////////////////////////////
// CGeneralFlagsPage dialog

class CGeneralFlagsPage : public CDialog
{
// Construction
public:
	CGeneralFlagsPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGeneralFlagsPage)
	enum { IDD = IDD_GENERAL_FLAGS };
	//}}AFX_DATA

  EXT_BV * m_pFlags;   // pointer to where the flags are
  tFlags * m_pFlagsArray;
  CAreaEditorDoc * m_pDoc;  // document - so we can set modified flag
  
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGeneralFlagsPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGeneralFlagsPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GENERALFLAGSPAGE_H__87A76363_4DFA_11D2_AFA0_00A0247B3BFD__INCLUDED_)
