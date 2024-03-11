/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_AREATYPEDLG_H__8FC61445_76DD_11D2_AFAB_00A0247B3BFD__INCLUDED_)
#define AFX_AREATYPEDLG_H__8FC61445_76DD_11D2_AFAB_00A0247B3BFD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AreaTypeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAreaTypeDlg dialog

class CAreaTypeDlg : public CDialog
{
// Construction
public:
	CAreaTypeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAreaTypeDlg)
	enum { IDD = IDD_AREA_TYPE };
	int		m_iAreaType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAreaTypeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAreaTypeDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AREATYPEDLG_H__8FC61445_76DD_11D2_AFAB_00A0247B3BFD__INCLUDED_)
