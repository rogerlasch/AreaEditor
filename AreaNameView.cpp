/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// AreaNameView.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "AreaEditorDoc.h"
#include "defaults.h"

#include "AreaNameView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAreaNameView dialog


CAreaNameView::CAreaNameView(CWnd* pParent /*=NULL*/)
	: CDialog(CAreaNameView::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAreaNameView)
	m_strAreaName = _T("");
	m_strAuthor = _T("");
	m_strFileName = _T("");
	m_strFlags = _T("");
	m_strRanges = _T("");
	m_reset_frequency = 0;
	m_reset_message = _T("");
	m_strVnums = _T("");
	m_area_version = 0;
	m_iAreaType = -1;
	//}}AFX_DATA_INIT

  m_area = NULL;
  m_pDoc = NULL;

}

#undef LOAD_VALUE
#define LOAD_VALUE(field, value)  \
  field = m_area->value

#undef UNLOAD_VALUE
#define UNLOAD_VALUE(field, value)  \
  if (field != m_area->value) bChanged = true; \
  m_area->value = field

void CAreaNameView::DoDataExchange(CDataExchange* pDX)
{

bool bChanged = false;

  if (!pDX->m_bSaveAndValidate && m_area)
    {
	  LOAD_VALUE (m_strAreaName      , strAreaName     );
	  LOAD_VALUE (m_strAuthor  , strAuthor );
	  LOAD_VALUE (m_reset_message  , strResetMsg );
	  LOAD_VALUE (m_reset_frequency  , reset_frequency );
	  LOAD_VALUE (m_area_version  , area_version );
	  m_iAreaType = m_pDoc->m_AreaType - 1;

    m_strFlags = convert_areaflag (m_area->flags);

    m_strRanges.Format ("Soft: %i to %i.  Hard: %i to %i",
                        m_area->low_soft_range,
                        m_area->hi_soft_range,
                        m_area->low_hard_range,
                        m_area->hi_hard_range);

    m_strVnums.Format ("Mobs: %i to %i" ENDLINE 
                       "Objects: %i to %i" ENDLINE
                       "Rooms: %i to %i",
	                      m_area->mob_low_vnum,
	                      m_area->mob_hi_vnum,
	                      m_area->obj_low_vnum,
	                      m_area->obj_hi_vnum,
	                      m_area->room_low_vnum,
	                      m_area->room_hi_vnum);

    // put file name into dialog for their information only
    m_strFileName = m_area->m_pDoc->GetPathName ();
    }


	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAreaNameView)
	DDX_Control(pDX, IDC_RESET_FREQUENCY, m_ctlResetFreq);
	DDX_Control(pDX, IDC_RESET_MESSAGE, m_ctlResetMessage);
	DDX_Control(pDX, IDC_VERSION_LIT, m_ctlVersionLit);
	DDX_Control(pDX, IDC_AREA_VERSION, m_ctlAreaVersion);
	DDX_Text(pDX, IDC_AREA_NAME, m_strAreaName);
	DDX_Text(pDX, IDC_AUTHOR, m_strAuthor);
	DDX_Text(pDX, IDC_FILENAME, m_strFileName);
	DDX_Text(pDX, IDC_FLAGS, m_strFlags);
	DDX_Text(pDX, IDC_RANGES, m_strRanges);
	DDX_Text(pDX, IDC_RESET_FREQUENCY, m_reset_frequency);
	DDX_Text(pDX, IDC_RESET_MESSAGE, m_reset_message);
	DDX_Text(pDX, IDC_VNUMS, m_strVnums);
	DDX_Text(pDX, IDC_AREA_VERSION, m_area_version);
	DDV_MinMaxInt(pDX, m_area_version, 0, 1);
	DDX_CBIndex(pDX, IDC_AREA_TYPE, m_iAreaType);
	//}}AFX_DATA_MAP


  // reset freq
	DDX_Text(pDX, IDC_RESET_FREQUENCY, m_reset_frequency);
	DDV_MinMaxInt(pDX, m_reset_frequency, 0, iMaxResetFreq);

  // put stuff back
  if (pDX->m_bSaveAndValidate && m_area)
    {

    CheckForTilde (pDX, IDC_AUTHOR, m_strAuthor);
    CheckForTilde (pDX, IDC_AREA_NAME, m_strAreaName);

	  UNLOAD_VALUE (m_strAreaName      , strAreaName     );
	  UNLOAD_VALUE (m_strAuthor  , strAuthor );
	  UNLOAD_VALUE (m_reset_message  , strResetMsg );
	  UNLOAD_VALUE (m_reset_frequency  , reset_frequency );
	  UNLOAD_VALUE (m_area_version  , area_version );
    if ((m_iAreaType + 1) != m_pDoc->m_AreaType) 
        bChanged = true;
    m_pDoc->m_AreaType = (t_areatype) (m_iAreaType + 1);
    if (bChanged)
       m_area->m_pDoc->SetModifiedFlag ();
    }   // end of saving and validating
  else
    {   // not saving -- hide/disable some windows if not SMAUG

    if (m_pDoc->m_AreaType != eSMAUG)
      {
      m_ctlResetFreq.EnableWindow (FALSE);
      m_ctlResetMessage.EnableWindow (FALSE);
      m_ctlAreaVersion.EnableWindow (FALSE);
      m_ctlVersionLit.ShowWindow (SW_HIDE);
      }

    }   // end of not saving

}


BEGIN_MESSAGE_MAP(CAreaNameView, CDialog)
	//{{AFX_MSG_MAP(CAreaNameView)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAreaNameView message handlers
