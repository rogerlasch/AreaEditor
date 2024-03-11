/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_WALKTHROUGHDLG_H__71C2E743_51EE_11D2_AFA2_00A0247B3BFD__INCLUDED_)
#define AFX_WALKTHROUGHDLG_H__71C2E743_51EE_11D2_AFA2_00A0247B3BFD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// WalkthroughDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWalkthroughDlg dialog

class CWalkthroughDlg : public CDialog
{
// Construction
public:
	CWalkthroughDlg(CWnd* pParent = NULL);   // standard constructor
	~CWalkthroughDlg();   // destructor
  
// Dialog Data
	//{{AFX_DATA(CWalkthroughDlg)
	enum { IDD = IDD_WALKTHROUGH };
	CButton	m_ctlShowEquipment;
	CButton	m_ctlShowVnums;
	CEdit	m_ctlOutput;
	CEdit	m_ctlCommand;
	BOOL	m_bShowEquipment;
	BOOL	m_bShowVnums;
	//}}AFX_DATA


  CAreaEditorDoc * m_pDoc;
  CRoom * m_room;
  CFont * m_font;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWalkthroughDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

  void RedrawRoom (void);
  void AppendToOutput (const char * sText);

  void OnOK();

	// Generated message map functions
	//{{AFX_MSG(CWalkthroughDlg)
	afx_msg void OnShowVnums();
	afx_msg void OnShowEquipment();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WALKTHROUGHDLG_H__71C2E743_51EE_11D2_AFA2_00A0247B3BFD__INCLUDED_)
