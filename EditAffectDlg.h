/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_EDITAFFECTDLG_H__3414F598_2628_11D4_BB0D_0080AD7972EF__INCLUDED_)
#define AFX_EDITAFFECTDLG_H__3414F598_2628_11D4_BB0D_0080AD7972EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditAffectDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditAffectDlg dialog

class CEditAffectDlg : public CDialog
{
// Construction
public:
	CEditAffectDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEditAffectDlg)
	enum { IDD = IDD_AFFECT_EDIT };
	CComboBox	m_ctlType;
	CEdit	m_ctlFlags;
	CEdit	m_ctlFlagMeanings;
	int		m_iFlags;
	CString	m_strDuration;
	CString	m_strModifier;
	//}}AFX_DATA


  int m_iLocation;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditAffectDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEditAffectDlg)
	afx_msg void OnChangeFlags();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITAFFECTDLG_H__3414F598_2628_11D4_BB0D_0080AD7972EF__INCLUDED_)
