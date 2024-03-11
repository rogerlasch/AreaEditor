/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_OBJECTNAMEPAGE_H__EBE07979_EF74_11D1_A20A_0000B4595568__INCLUDED_)
#define AFX_OBJECTNAMEPAGE_H__EBE07979_EF74_11D1_A20A_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ObjectNamePage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CObjectNamePage dialog

class CObjectNamePage : public CDialog
{
// Construction
public:
	CObjectNamePage(CWnd* pParent = NULL);   // standard constructor
  ~CObjectNamePage ();    // destructor

// Dialog Data
	//{{AFX_DATA(CObjectNamePage)
	enum { IDD = IDD_OBJECT_NAME };
	CEdit	m_ctlShortDescription;
	CEdit	m_ctlName;
	CEdit	m_ctlLongDescription;
	CComboBox	m_ctlType;
	CEdit	m_ctlActionDescription;
	int		m_vnum;
	CString	m_name;
	CString	m_short_descr;
	CString	m_description;
	CString	m_action_desc;
	//}}AFX_DATA

  CMUDObject * m_object;
  CFont * m_font;

  int m_OriginalVnum;   // original vnum before editing

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CObjectNamePage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

  void EditDescription (CEdit & ctlDescription, 
                        const bool bEndline = true,
                        const bool bSpellCheck = false);

	// Generated message map functions
	//{{AFX_MSG(CObjectNamePage)
	afx_msg void OnEditDescription();
	afx_msg void OnEditNames();
	afx_msg void OnEditShortDescription();
	afx_msg void OnEditLongDescription();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OBJECTNAMEPAGE_H__EBE07979_EF74_11D1_A20A_0000B4595568__INCLUDED_)
