/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// AreaClimateView.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "AreaEditorDoc.h"
#include "defaults.h"

#include "AreaClimateView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAreaClimateView dialog


CAreaClimateView::CAreaClimateView(CWnd* pParent /*=NULL*/)
	: CDialog(CAreaClimateView::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAreaClimateView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

  m_area = NULL;

}

extern char *	temp_settings	[MAX_CLIMATE];
extern char *	precip_settings	[MAX_CLIMATE];
extern char * wind_settings [MAX_CLIMATE];

#undef LOAD_VALUE
#define LOAD_VALUE(field, value)  \
  field = m_area->value

#undef UNLOAD_VALUE
#define UNLOAD_VALUE(field, value)  \
  do {    \
    if (field != m_area->value) bChanged = true; \
    m_area->value = field;   \
    } while (false)

void CAreaClimateView::DoDataExchange(CDataExchange* pDX)
{

bool bChanged = false;

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAreaClimateView)
	DDX_Control(pDX, IDC_WIND, m_ctlWind);
	DDX_Control(pDX, IDC_TEMPERATURE, m_ctlTemperature);
	DDX_Control(pDX, IDC_PRECIPITATION, m_ctlPrecipitation);
	//}}AFX_DATA_MAP

  if (pDX->m_bSaveAndValidate)
    {

    int i;
    if (UnloadComboBox (m_ctlTemperature, i))
  	  UNLOAD_VALUE (i, climate_temp);
    if (UnloadComboBox (m_ctlPrecipitation, i))
  	  UNLOAD_VALUE (i, climate_precip);
    if (UnloadComboBox (m_ctlWind, i))
  	  UNLOAD_VALUE (i, climate_wind);
   
     if (bChanged)
       m_area->m_pDoc->SetModifiedFlag ();
    } // end of saving and validating
  else
    {
    LoadComboBox (m_ctlTemperature,     temp_settings,   MAX_CLIMATE, m_area->climate_temp);
    LoadComboBox (m_ctlPrecipitation,   precip_settings, MAX_CLIMATE, m_area->climate_precip);
    LoadComboBox (m_ctlWind,            wind_settings,   MAX_CLIMATE, m_area->climate_wind);
    }


}


BEGIN_MESSAGE_MAP(CAreaClimateView, CDialog)
	//{{AFX_MSG_MAP(CAreaClimateView)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAreaClimateView message handlers
