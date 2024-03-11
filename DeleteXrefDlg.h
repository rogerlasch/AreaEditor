/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_DELETEXREFDLG_H__B300EC83_154E_11D2_A20B_0000B4595568__INCLUDED_)
#define AFX_DELETEXREFDLG_H__B300EC83_154E_11D2_A20B_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DeleteXrefDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDeleteXrefDlg dialog

class CDeleteXrefDlg : public CDialog
{
// Construction
public:
	CDeleteXrefDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDeleteXrefDlg)
	enum { IDD = IDD_DELETE_REFERENCES };
	CListBox	m_ctlXrefList;
	CString	m_strAboutToDelete;
	//}}AFX_DATA


  CMUDitemList * m_pxrefList,       // referencing item
               * m_pxrefOwnerList;  // owner of item (eg. room which owns exit)

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDeleteXrefDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDeleteXrefDlg)
	afx_msg void OnDeselectAll();
	afx_msg void OnSelectAll();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DELETEXREFDLG_H__B300EC83_154E_11D2_A20B_0000B4595568__INCLUDED_)
