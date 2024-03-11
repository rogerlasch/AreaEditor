/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// ObjectSummaryPage.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "AreaEditorDoc.h"
#include "defaults.h"

#include "ObjectSummaryPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CObjectSummaryPage dialog


CObjectSummaryPage::CObjectSummaryPage(CWnd* pParent /*=NULL*/)
	: CDialog(CObjectSummaryPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CObjectSummaryPage)
	m_vnum = 0;
	m_type = _T("");
	m_name = _T("");
	m_short_descr = _T("");
	m_description = _T("");
	m_strExtraFlags = _T("");
	m_strWearFlags = _T("");
	m_cost = 0;
	m_layers = 0;
	m_rent = 0;
	m_value1 = 0;
	m_value2 = 0;
	m_value3 = 0;
	m_value4 = 0;
	m_value5 = 0;
	m_value6 = 0;
	m_weight = 0;
	m_strAffects = _T("");
	m_strValueMeanings = _T("");
	m_iLevel = 0;
	m_iCondition = 0;
	//}}AFX_DATA_INIT

  m_object = NULL;

}

#undef LOAD_VALUE
#define LOAD_VALUE(field, value)  \
  field = m_object->value

void CObjectSummaryPage::DoDataExchange(CDataExchange* pDX)
{

  if (!pDX->m_bSaveAndValidate)
    {
    m_type = ObjectItemList.ReturnName (m_object->item_type, false);
    m_strExtraFlags = convert_object_flags (m_object->extra_flags);
    m_strWearFlags = convert_wear_flags (m_object->wear_flags);
    m_strValueMeanings = m_object->ValueSummary ();

	  LOAD_VALUE (m_vnum, vnum);
	  LOAD_VALUE (m_name, name);
	  LOAD_VALUE (m_short_descr, short_descr);
	  LOAD_VALUE (m_description, description);
    LOAD_VALUE (m_cost, cost);
	  LOAD_VALUE (m_layers, layers);
	  LOAD_VALUE (m_rent, rent);
	  LOAD_VALUE (m_value1, value [0]);
	  LOAD_VALUE (m_value2, value [1]);
	  LOAD_VALUE (m_value3, value [2]);
	  LOAD_VALUE (m_value4, value [3]);
	  LOAD_VALUE (m_value5, value [4]);
	  LOAD_VALUE (m_value6, value [5]);
	  LOAD_VALUE (m_weight, weight);
	  LOAD_VALUE (m_iLevel, level);
	  LOAD_VALUE (m_iCondition, condition);


// list the affects caused by this object

    POSITION affectPos;
    CAffect * affect;

    m_strAffects.Empty ();

    for (affectPos = m_object->affectlist.GetHeadPosition (); affectPos; )
      {
      affect = m_object->affectlist.GetNext (affectPos);

      if (!m_strAffects.IsEmpty ())
        m_strAffects += ", ";
       m_strAffects += affect->Summary ();

      }   // end of adding each affect item

    }   // end of not saving and validating

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CObjectSummaryPage)
	DDX_Control(pDX, IDC_CONDITION, m_ctlCondition);
	DDX_Control(pDX, IDC_LEVEL, m_ctlLevel);
	DDX_Control(pDX, IDC_CONDITION_LABEL, m_ctlConditionLabel);
	DDX_Control(pDX, IDC_LEVEL_LABEL, m_ctlLevelLabel);
	DDX_Text(pDX, IDC_VNUM, m_vnum);
	DDX_Text(pDX, IDC_TYPE, m_type);
	DDX_Text(pDX, IDC_NAME, m_name);
	DDX_Text(pDX, IDC_SHORT_DESCRIPTION, m_short_descr);
	DDX_Text(pDX, IDC_LONG_DESCRIPTION, m_description);
	DDX_Text(pDX, IDC_EXTRA_FLAGS, m_strExtraFlags);
	DDX_Text(pDX, IDC_WEAR_FLAGS, m_strWearFlags);
	DDX_Text(pDX, IDC_COST, m_cost);
	DDX_Text(pDX, IDC_LAYERS, m_layers);
	DDX_Text(pDX, IDC_RENT, m_rent);
	DDX_Text(pDX, IDC_VALUE1, m_value1);
	DDX_Text(pDX, IDC_VALUE2, m_value2);
	DDX_Text(pDX, IDC_VALUE3, m_value3);
	DDX_Text(pDX, IDC_VALUE4, m_value4);
	DDX_Text(pDX, IDC_VALUE5, m_value5);
	DDX_Text(pDX, IDC_VALUE6, m_value6);
	DDX_Text(pDX, IDC_WEIGHT, m_weight);
	DDX_Text(pDX, IDC_AFFECTS, m_strAffects);
	DDX_Text(pDX, IDC_VALUE_MEANINGS, m_strValueMeanings);
	DDX_Text(pDX, IDC_LEVEL, m_iLevel);
	DDX_Text(pDX, IDC_CONDITION, m_iCondition);
	//}}AFX_DATA_MAP

  if (!pDX->m_bSaveAndValidate)
    {
    if (m_object->m_pDoc->m_AreaType != eROM)
      {
      m_ctlLevelLabel.ShowWindow (SW_HIDE);
      m_ctlLevel.ShowWindow (SW_HIDE);
      m_ctlConditionLabel.ShowWindow (SW_HIDE);
      m_ctlCondition.ShowWindow (SW_HIDE);
      }   // end of not ROM

    }

}


BEGIN_MESSAGE_MAP(CObjectSummaryPage, CDialog)
	//{{AFX_MSG_MAP(CObjectSummaryPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CObjectSummaryPage message handlers
