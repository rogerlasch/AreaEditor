/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// RoomMapView.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "AreaEditorDoc.h"

#include "RoomMapView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRoomMapView

IMPLEMENT_DYNCREATE(CRoomMapView, CFormView)

CRoomMapView::CRoomMapView()
	: CFormView(CRoomMapView::IDD)
{
	//{{AFX_DATA_INIT(CRoomMapView)
	m_vnum = 0;
	m_x = 0;
	m_y = 0;
	//}}AFX_DATA_INIT

  m_map = NULL;

}

CRoomMapView::~CRoomMapView()
{
}

#undef LOAD_VALUE
#define LOAD_VALUE(field, value)  \
  field = m_map->value

#undef UNLOAD_VALUE
#define UNLOAD_VALUE(field, value)  \
  if (field != m_map->value) bChanged = true; \
  m_map->value = field


void CRoomMapView::DoDataExchange(CDataExchange* pDX)
{
bool bChanged = false;

  if (!pDX->m_bSaveAndValidate && m_map)
    {
	  LOAD_VALUE (m_vnum, vnum);
	  LOAD_VALUE (m_entry, entry);
	  LOAD_VALUE (m_x, x);
	  LOAD_VALUE (m_y, y);
    }   // end of not saving and validating

	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRoomMapView)
	DDX_MinMaxString(pDX, IDC_ENTRY, m_entry);
	DDV_MinMaxString(pDX, m_entry, 1, 1);
	DDX_Text(pDX, IDC_VNUM, m_vnum);
	DDX_Text(pDX, IDC_X, m_x);
	DDX_Text(pDX, IDC_Y, m_y);
	//}}AFX_DATA_MAP

  if (pDX->m_bSaveAndValidate && m_map)
    {
	  UNLOAD_VALUE (m_vnum, vnum);
	  UNLOAD_VALUE (m_entry [0], entry);
	  UNLOAD_VALUE (m_x, x);
	  UNLOAD_VALUE (m_y, y);
     if (bChanged)
       m_map->m_pDoc->SetModifiedFlag ();
    }   // end of not saving and validating

}


BEGIN_MESSAGE_MAP(CRoomMapView, CFormView)
	//{{AFX_MSG_MAP(CRoomMapView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRoomMapView diagnostics

#ifdef _DEBUG
void CRoomMapView::AssertValid() const
{
	CFormView::AssertValid();
}

void CRoomMapView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRoomMapView message handlers
