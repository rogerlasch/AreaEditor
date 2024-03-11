/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

//{{AFX_INCLUDES()
//}}AFX_INCLUDES
#if !defined(AFX_EDITDLG_H__B62F65B4_0703_11D2_A20B_0000B4595568__INCLUDED_)
#define AFX_EDITDLG_H__B62F65B4_0703_11D2_A20B_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// EditDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditDlg dialog

class CEditDlg : public CDialog
{
// Construction
public:
	CEditDlg(CWnd* pParent = NULL);   // standard constructor
  ~CEditDlg ();

// Dialog Data
	//{{AFX_DATA(CEditDlg)
	enum { IDD = IDD_EDIT };
	CButton	m_ctlSpellCheck;
	CEdit	m_ctlColumnCount;
	CButton	m_ctlWrap;
	CEdit	m_ctlEditText;
	CString	m_strEditText;
	//}}AFX_DATA

  CFont * m_font;
  bool m_bFirstTime;
  bool m_bProgram;
  bool m_bEndline;        // want an ENDLINE at the end of the text?
  bool m_bSpellCheck;     // want to spell check it?

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEditDlg)
	afx_msg void OnSetfocusEditText();
	virtual void OnOK();
	afx_msg void OnWrap();
	afx_msg void OnSpellCheck();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITDLG_H__B62F65B4_0703_11D2_A20B_0000B4595568__INCLUDED_)
