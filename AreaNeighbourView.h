/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_AREANEIGHBOURVIEW_H__68A3F683_4F56_11D2_AFA1_00A0247B3BFD__INCLUDED_)
#define AFX_AREANEIGHBOURVIEW_H__68A3F683_4F56_11D2_AFA1_00A0247B3BFD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AreaNeighbourView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAreaNeighbourView dialog

class CAreaNeighbourView : public CDialog
{
// Construction
public:
	CAreaNeighbourView(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAreaNeighbourView)
	enum { IDD = IDD_AREA_NEIGHBOUR };
	CListCtrl	m_ctlNeighboursList;
	//}}AFX_DATA

  CArea * m_area;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAreaNeighbourView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

  void RedrawList (void);

	// Generated message map functions
	//{{AFX_MSG(CAreaNeighbourView)
	afx_msg void OnAdd();
	afx_msg void OnDelete();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AREANEIGHBOURVIEW_H__68A3F683_4F56_11D2_AFA1_00A0247B3BFD__INCLUDED_)
