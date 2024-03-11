/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_NEIGHBOURNAMEDLG_H__68A3F684_4F56_11D2_AFA1_00A0247B3BFD__INCLUDED_)
#define AFX_NEIGHBOURNAMEDLG_H__68A3F684_4F56_11D2_AFA1_00A0247B3BFD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// NeighbourNameDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNeighbourNameDlg dialog

class CNeighbourNameDlg : public CDialog
{
// Construction
public:
	CNeighbourNameDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNeighbourNameDlg)
	enum { IDD = IDD_NEIGHBOUR_NAME };
	CString	m_strName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNeighbourNameDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNeighbourNameDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEIGHBOURNAMEDLG_H__68A3F684_4F56_11D2_AFA1_00A0247B3BFD__INCLUDED_)
