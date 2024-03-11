/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_AREANAMEVIEW_H__670FCF54_4EA7_11D2_AFA0_00A0247B3BFD__INCLUDED_)
#define AFX_AREANAMEVIEW_H__670FCF54_4EA7_11D2_AFA0_00A0247B3BFD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AreaNameView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAreaNameView dialog

class CAreaNameView : public CDialog
{
// Construction
public:
	CAreaNameView(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAreaNameView)
	enum { IDD = IDD_AREA_NAME };
	CEdit	m_ctlResetFreq;
	CEdit	m_ctlResetMessage;
	CStatic	m_ctlVersionLit;
	CEdit	m_ctlAreaVersion;
	CString	m_strAreaName;
	CString	m_strAuthor;
	CString	m_strFileName;
	CString	m_strFlags;
	CString	m_strRanges;
	int		m_reset_frequency;
	CString	m_reset_message;
	CString	m_strVnums;
	int		m_area_version;
	int		m_iAreaType;
	//}}AFX_DATA

  CArea * m_area;
  CAreaEditorDoc * m_pDoc;
  CAreaEditorView * m_pLHview;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAreaNameView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAreaNameView)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AREANAMEVIEW_H__670FCF54_4EA7_11D2_AFA0_00A0247B3BFD__INCLUDED_)
