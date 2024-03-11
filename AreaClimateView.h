/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#if !defined(AFX_AREACLIMATEVIEW_H__68A3F685_4F56_11D2_AFA1_00A0247B3BFD__INCLUDED_)
#define AFX_AREACLIMATEVIEW_H__68A3F685_4F56_11D2_AFA1_00A0247B3BFD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AreaClimateView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAreaClimateView dialog

class CAreaClimateView : public CDialog
{
// Construction
public:
	CAreaClimateView(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAreaClimateView)
	enum { IDD = IDD_AREA_CLIMATE };
	CComboBox	m_ctlWind;
	CComboBox	m_ctlTemperature;
	CComboBox	m_ctlPrecipitation;
	//}}AFX_DATA

  CArea * m_area;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAreaClimateView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAreaClimateView)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AREACLIMATEVIEW_H__68A3F685_4F56_11D2_AFA1_00A0247B3BFD__INCLUDED_)
