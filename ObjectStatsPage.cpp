/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// ObjectStatsPage.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "AreaEditorDoc.h"

#include "defaults.h"

#include "ObjectView.h"
#include "ObjectStatsPage.h"
#include "ChooseSpellDlg.h"
#include "ChooseFromListDlg.h"
#include "ChooseFlagsDlg.h"
#include "ChooseObjectDlg.h"
#include "ChooseRoomDlg.h"

#pragma warning( disable : 4244)

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CObjectStatsPage dialog


CObjectStatsPage::CObjectStatsPage(CWnd* pParent /*=NULL*/)
	: CDialog(CObjectStatsPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CObjectStatsPage)
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
	m_type = _T("");
	m_iCondition = 0;
	m_iLevel = 0;
	m_strMaterial = _T("");
	m_strUnits = _T("");
	//}}AFX_DATA_INIT

  m_object = NULL;

}

#undef LOAD_VALUE
#define LOAD_VALUE(field, value)  \
  field = m_object->value

#undef UNLOAD_VALUE
#define UNLOAD_VALUE(field, value)  \
  if (field != m_object->value) bChanged = true; \
  m_object->value = field

void CObjectStatsPage::DoDataExchange(CDataExchange* pDX)
{
bool bChanged = false;

  if (!pDX->m_bSaveAndValidate && m_object)
    {
    m_type = ObjectItemList.ReturnName (m_object->item_type, true);
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
	  LOAD_VALUE (m_strMaterial, material);
	  LOAD_VALUE (m_iLevel, level);
	  LOAD_VALUE (m_iCondition, condition);

    if (m_object->m_pDoc->m_AreaType == eROM)
      m_strUnits = "1/10ths. pound";
    else
      m_strUnits = "pound(s)";

    }

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CObjectStatsPage)
	DDX_Control(pDX, IDC_MATERIAL_LABEL, m_ctlMaterialLabel);
	DDX_Control(pDX, IDC_MATERIAL, m_ctlMaterial);
	DDX_Control(pDX, IDC_LEVEL_LABEL, m_ctlLevelLabel);
	DDX_Control(pDX, IDC_LEVEL, m_ctlLevel);
	DDX_Control(pDX, IDC_CONDITION_LABEL, m_ctlConditionLabel);
	DDX_Control(pDX, IDC_CONDITION, m_ctlCondition);
	DDX_Control(pDX, IDC_CHOOSE6, m_ctlChoose6);
	DDX_Control(pDX, IDC_CHOOSE5, m_ctlChoose5);
	DDX_Control(pDX, IDC_CHOOSE4, m_ctlChoose4);
	DDX_Control(pDX, IDC_CHOOSE3, m_ctlChoose3);
	DDX_Control(pDX, IDC_CHOOSE2, m_ctlChoose2);
	DDX_Control(pDX, IDC_CHOOSE1, m_ctlChoose1);
	DDX_Control(pDX, IDC_VALUE6, m_ctlValue6);
	DDX_Control(pDX, IDC_VALUE5, m_ctlValue5);
	DDX_Control(pDX, IDC_VALUE4, m_ctlValue4);
	DDX_Control(pDX, IDC_VALUE3, m_ctlValue3);
	DDX_Control(pDX, IDC_VALUE2, m_ctlValue2);
	DDX_Control(pDX, IDC_VALUE1, m_ctlValue1);
	DDX_Control(pDX, IDC_LABEL_VALUE6, m_ctlLabelValue6);
	DDX_Control(pDX, IDC_LABEL_VALUE5, m_ctlLabelValue5);
	DDX_Control(pDX, IDC_LABEL_VALUE4, m_ctlLabelValue4);
	DDX_Control(pDX, IDC_LABEL_VALUE3, m_ctlLabelValue3);
	DDX_Control(pDX, IDC_LABEL_VALUE2, m_ctlLabelValue2);
	DDX_Control(pDX, IDC_DESC_VALUE6, m_ctlDescValue6);
	DDX_Control(pDX, IDC_DESC_VALUE5, m_ctlDescValue5);
	DDX_Control(pDX, IDC_DESC_VALUE3, m_ctlDescValue3);
	DDX_Control(pDX, IDC_DESC_VALUE4, m_ctlDescValue4);
	DDX_Control(pDX, IDC_DESC_VALUE2, m_ctlDescValue2);
	DDX_Control(pDX, IDC_DESC_VALUE1, m_ctlDescValue1);
	DDX_Control(pDX, IDC_LABEL_VALUE1, m_ctlLabelValue1);
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
	DDX_Text(pDX, IDC_TYPE, m_type);
	DDX_Text(pDX, IDC_CONDITION, m_iCondition);
	DDX_Text(pDX, IDC_MATERIAL, m_strMaterial);
	DDX_Text(pDX, IDC_WEIGHT_UNITS, m_strUnits);
	//}}AFX_DATA_MAP


  if (m_object->m_pDoc->m_AreaType == eROM)
    {
	  DDX_Text(pDX, IDC_LEVEL, m_iLevel);
	  DDV_MinMaxInt(pDX, m_iLevel, 0, iMaxLevel);
    DDX_Text(pDX, IDC_CONDITION, m_iCondition);
	  DDV_MinMaxInt(pDX, m_iCondition, iMinCondition, iMaxCondition);
    }

  if (!pDX->m_bSaveAndValidate)
    {
    if (m_object->m_pDoc->m_AreaType != eROM)
      {
      m_ctlMaterialLabel.ShowWindow (SW_HIDE);
      m_ctlMaterial.ShowWindow (SW_HIDE);
      m_ctlLevelLabel.ShowWindow (SW_HIDE);
      m_ctlLevel.ShowWindow (SW_HIDE);
      m_ctlConditionLabel.ShowWindow (SW_HIDE);
      m_ctlCondition.ShowWindow (SW_HIDE);
      }   // end of not ROM

    UpdateLabels ();
    }

  if (pDX->m_bSaveAndValidate)
    {
	  UNLOAD_VALUE (m_cost, cost);
	  UNLOAD_VALUE (m_layers, layers);
	  UNLOAD_VALUE (m_rent, rent);
	  UNLOAD_VALUE (m_value1, value [0]);
	  UNLOAD_VALUE (m_value2, value [1]);
	  UNLOAD_VALUE (m_value3, value [2]);
	  UNLOAD_VALUE (m_value4, value [3]);
	  UNLOAD_VALUE (m_value5, value [4]);
	  UNLOAD_VALUE (m_value6, value [5]);
	  UNLOAD_VALUE (m_weight, weight);
	  UNLOAD_VALUE (m_strMaterial, material);
	  UNLOAD_VALUE (m_iLevel, level);
	  UNLOAD_VALUE (m_iCondition, condition);
     if (bChanged)
       m_object->m_pDoc->SetModifiedFlag ();
    }

}


BEGIN_MESSAGE_MAP(CObjectStatsPage, CDialog)
	//{{AFX_MSG_MAP(CObjectStatsPage)
	ON_EN_CHANGE(IDC_VALUE1, OnChangeValue)
	ON_BN_CLICKED(IDC_CHOOSE1, OnChoose1)
	ON_BN_CLICKED(IDC_CHOOSE2, OnChoose2)
	ON_BN_CLICKED(IDC_CHOOSE3, OnChoose3)
	ON_BN_CLICKED(IDC_CHOOSE4, OnChoose4)
	ON_BN_CLICKED(IDC_CHOOSE5, OnChoose5)
	ON_EN_CHANGE(IDC_VALUE2, OnChangeValue)
	ON_EN_CHANGE(IDC_VALUE3, OnChangeValue)
	ON_EN_CHANGE(IDC_VALUE4, OnChangeValue)
	ON_EN_CHANGE(IDC_VALUE5, OnChangeValue)
	ON_EN_CHANGE(IDC_VALUE6, OnChangeValue)
	ON_BN_CLICKED(IDC_CHOOSE6, OnChoose6)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CObjectStatsPage message handlers

typedef CString (* t_DisplayMeaning) (const __int64 iValue, 
                                      CAreaEditorDoc * const pDoc);
typedef __int64 (* t_ChooseMeaning) (const __int64 iValue, 
                                 CAreaEditorDoc * const pDoc);

CString DisplayLiquid (const __int64 iValue, 
                       CAreaEditorDoc * const pDoc)
  {
  return ObjectLiquidList.ReturnName (iValue, false);
  } // end of DisplayLiquid

CString DisplayWeaponType (const __int64 iValue, 
                           CAreaEditorDoc * const pDoc)
  {
  return ObjectAttackList.ReturnName (iValue, false);
  } // end of DisplayWeaponType

CString DisplayWeaponClass (const __int64 iValue, 
                            CAreaEditorDoc * const pDoc)
  {
  return ObjectWeaponList.ReturnName (iValue, false);
  } // end of DisplayWeaponClass

CString DisplayFurniture (const __int64 iValue, 
                          CAreaEditorDoc * const pDoc)
  {
  return FlagToString (iValue, ObjectFurnitureFlags);
  } // end of DisplayFurniture

CString DisplayContainer (const __int64 iValue, 
                          CAreaEditorDoc * const pDoc)
  {
  return FlagToString (iValue, ObjectContainerFlags);
  } // end of DisplayContainer

CString DisplayPortalFlags (const __int64 iValue, 
                            CAreaEditorDoc * const pDoc)
  {
  return FlagToString (iValue, ObjectPortalFlags);
  } // end of DisplayPortalFlags

CString DisplayWeaponFlags (const __int64 iValue, 
                            CAreaEditorDoc * const pDoc)
  {
  return FlagToString (iValue, ObjectWeaponFlags);
  } // end of DisplayWeaponFlags

CString DisplayYesOrNo (const __int64 iValue, 
                        CAreaEditorDoc * const pDoc)
  {
  return iValue ? "Yes" : "No";
  } // end of DisplayYesOrNo

CString DisplayWeaponCondition (const __int64 iValue, 
                                CAreaEditorDoc * const pDoc)
  {
  __int64 dam = ObjectWeaponConditionList.list.GetCount () - iValue;

  return ObjectWeaponConditionList.ReturnName (dam, false);
  } // end of DisplayWeaponCondition

CString DisplayKey (const __int64 iValue, 
                    CAreaEditorDoc * const pDoc)
  {
CMUDObject * object;

// key of 0 or -1 means "no key"

  if (iValue <= 0)
    return "(no key)";

  // find key object

  if (object = pDoc->get_obj_index (iValue))
    return object->short_descr;
  if (object = FindObj ( iValue ))
    return FullObjName (object);

  // not found - say so
  // (nb - this is not too bad, key may be in a different area)

  return CFormat ("Object #%i not in this area", iValue);

  } // end of DisplayKey

CString DisplayRoom (const __int64 iValue, 
                    CAreaEditorDoc * const pDoc)
  {
CRoom * room;

// key of 0 or -1 means "no room"

  if (iValue <= 0)
    return "(no room)";

  // find room

  if (room = pDoc->get_room_index (iValue))
    return room->name;

  // if room is in a different area, say so

  if (room = FindRoom (iValue))
    return FullRoomName (room);

  // not found - say so
  // (nb - this is not too bad, room may be in a different area)

  return CFormat ("Room #%i not in this area", iValue);

  } // end of DisplayRoom

CString DisplayArmourCondition (const __int64 iValue, 
                                CAreaEditorDoc * const pDoc)
  {
  __int64 dam = ObjectArmourConditionList.list.GetCount () - iValue;

  return ObjectArmourConditionList.ReturnName (dam, false);
  } // end of DisplayArmourCondition


CString DisplaySMAUGSpell (const __int64 iValue, 
                           CAreaEditorDoc * const pDoc)
  {
  CSkill * skill;

  if (iValue == -1)
    return "(none)";

  if (App.m_SkillList.IsEmpty ())
    return "(Skill list not loaded)";

  for (POSITION skillPos = App.m_SkillList.GetHeadPosition (); skillPos; )
    {
    skill =  App.m_SkillList.GetNext (skillPos);
    if (skill->slot == iValue)
      return skill->name;
    }

  return CFormat ("Unknown skill=%i", iValue);

  } // end of DisplaySMAUGSpell

CString DisplayROMSpell (const __int64 iValue, 
                         CAreaEditorDoc * const pDoc)
  {
  if (iValue == -1)
    return "(none)";

  return ROMSkillNameList.ReturnName (iValue, false);

  } // end of DisplayROMSpell

__int64 ChooseSMAUGSpell (const __int64 iValue, 
                      CAreaEditorDoc * const pDoc)
  {
CChooseSpellDlg dlg;

  if (App.m_SkillList.IsEmpty ())
    {
    ::AfxMessageBox ("Please load the skills table before choosing spells");
    return iValue;    // keep same value if no skills table
    }

  dlg.m_iSelectedSpell = iValue;

  if (dlg.DoModal () != IDOK)
    return iValue;    // keep same value if they cancel

  return dlg.m_iSelectedSpell;

  }   // end of ChooseSMAUGSpell

__int64 ChooseROMSpell (const __int64 iValue, 
                    CAreaEditorDoc * const pDoc)
  {
CChooseFromListDlg dlg;

  dlg.m_iSelectedItem = iValue;
  dlg.m_pList = &ROMSkillNameList;
  dlg.m_strTitle = "Choose spell";

  if (dlg.DoModal () != IDOK)
    return iValue;    // keep same value if they cancel

  return dlg.m_iSelectedItem;

  }   // end of ChooseROMSpell

__int64 ChooseFurniture (const __int64 iValue, 
                     CAreaEditorDoc * const pDoc)
  {
CChooseFlagsDlg dlg;

  dlg.m_pFlags = iValue;
  dlg.m_pFlagsArray = &ObjectFurnitureFlags;
  dlg.m_strTitle = "Choose furniture flags";
  dlg.m_AreaType = pDoc->m_AreaType;

  if (dlg.DoModal () != IDOK)
    return iValue;    // keep same value if they cancel

  return dlg.m_pFlags;

  }   // end of ChooseFurniture

__int64 ChooseContainer (const __int64 iValue, 
                     CAreaEditorDoc * const pDoc)
  {
CChooseFlagsDlg dlg;

  dlg.m_pFlags = iValue;
  dlg.m_pFlagsArray = &ObjectContainerFlags;
  dlg.m_strTitle = "Choose container flags";
  dlg.m_AreaType = pDoc->m_AreaType;

  if (dlg.DoModal () != IDOK)
    return iValue;    // keep same value if they cancel

  return dlg.m_pFlags;

  }   // end of ChooseContainer

__int64 ChoosePortalFlags (const __int64 iValue, 
                       CAreaEditorDoc * const pDoc)
  {
CChooseFlagsDlg dlg;

  dlg.m_pFlags = iValue;
  dlg.m_pFlagsArray = &ObjectPortalFlags;
  dlg.m_strTitle = "Choose portal flags";
  dlg.m_AreaType = pDoc->m_AreaType;

  if (dlg.DoModal () != IDOK)
    return iValue;    // keep same value if they cancel

  return dlg.m_pFlags;

  }   // end of ChoosePortalFlags

__int64 ChooseWeaponFlags(const __int64 iValue, 
                      CAreaEditorDoc * const pDoc)
  {
CChooseFlagsDlg dlg;

  dlg.m_pFlags = iValue;
  dlg.m_pFlagsArray = &ObjectWeaponFlags;
  dlg.m_strTitle = "Choose weapon flags";
  dlg.m_AreaType = pDoc->m_AreaType;

  if (dlg.DoModal () != IDOK)
    return iValue;    // keep same value if they cancel

  return dlg.m_pFlags;

  }   // end of ChooseWeaponFlags

__int64 ChooseKey (const __int64 iValue, 
               CAreaEditorDoc * const pDoc)
  {
CChooseObjectDlg dlg;

  dlg.m_pDoc = pDoc;
  dlg.m_iSelectedObject = iValue;
  dlg.m_iItemType = eTakeItem;    // only choose take-type items
  if (dlg.DoModal () == IDOK) 
    if (dlg.m_iSelectedObject != -1)
      return dlg.m_iSelectedObject;
  
  return iValue;    // default to what they originally had

  }   // end of ChooseKey

__int64 ChooseRoom (const __int64 iValue, 
               CAreaEditorDoc * const pDoc)
  {
CChooseRoomDlg dlg;

  dlg.m_pDoc = pDoc;
  dlg.m_iSelectedRoom = iValue;
  if (dlg.DoModal () == IDOK) 
    if (dlg.m_iSelectedRoom != -1)
      return dlg.m_iSelectedRoom;
  
  return iValue;    // default to what they originally had

  }   // end of ChooseRoom

__int64 ChooseLiquid (const __int64 iValue, 
                  CAreaEditorDoc * const pDoc)
  {
CChooseFromListDlg dlg;

  dlg.m_iSelectedItem = iValue;
  dlg.m_pList = &ObjectLiquidList;
  dlg.m_strTitle = "Choose liquid type";

  if (dlg.DoModal () != IDOK)
    return iValue;    // keep same value if they cancel

  return dlg.m_iSelectedItem;

  }   // end of ChooseLiquid

__int64 ChooseWeaponClass (const __int64 iValue, 
                       CAreaEditorDoc * const pDoc)
  {
CChooseFromListDlg dlg;

  dlg.m_iSelectedItem = iValue;
  dlg.m_pList = &ObjectWeaponList;
  dlg.m_strTitle = "Choose weapon class";

  if (dlg.DoModal () != IDOK)
    return iValue;    // keep same value if they cancel

  return dlg.m_iSelectedItem;

  }   // end of ChooseWeaponClass

__int64 ChooseWeaponType (const __int64 iValue, 
                      CAreaEditorDoc * const pDoc)
  {
CChooseFromListDlg dlg;

  dlg.m_iSelectedItem = iValue;
  dlg.m_pList = &ObjectAttackList;
  dlg.m_strTitle = "Choose weapon type";

  if (dlg.DoModal () != IDOK)
    return iValue;    // keep same value if they cancel

  return dlg.m_iSelectedItem;

  }   // end of ChooseWeaponType

__int64 ChooseWeaponCondition (const __int64 iValue, 
                      CAreaEditorDoc * const pDoc)
  {
CChooseFromListDlg dlg;

  dlg.m_iSelectedItem = ObjectWeaponConditionList.list.GetCount () - iValue;
  dlg.m_pList = &ObjectWeaponConditionList;
  dlg.m_strTitle = "Choose weapon condition";

  if (dlg.DoModal () != IDOK)
    return iValue;    // keep same value if they cancel

  return ObjectWeaponConditionList.list.GetCount () - dlg.m_iSelectedItem;

  }   // end of ChooseWeaponCondition

__int64 ChoosePoisoned (const __int64 iValue, 
                    CAreaEditorDoc * const pDoc)
  {
int iResult = ::AfxMessageBox ("Poisoned?", MB_YESNOCANCEL | MB_ICONQUESTION | 
    (iValue ? MB_DEFBUTTON1 : MB_DEFBUTTON2));

  if (iResult == IDCANCEL)
    return iValue;
  else if (iResult == IDYES)
    return 1;
  else
    return 0;
  } // end of ChoosePoisoned

__int64 ChooseKeep (const __int64 iValue, 
                CAreaEditorDoc * const pDoc)
  {

int iResult = ::AfxMessageBox ("Keep?", MB_YESNOCANCEL | MB_ICONQUESTION | 
    (iValue ? MB_DEFBUTTON1 : MB_DEFBUTTON2));

  if (iResult == IDCANCEL)
    return iValue;
  else if (iResult == IDYES)
    return 1;
  else
    return 0;
  } // end of ChooseKeep

// this food stuff seems a bit dodgy - I think I'll leave the condition out of it
CString DisplayFoodCondition (const __int64 iValue, 
                             CAreaEditorDoc * const pDoc)
  {
  int dam = ObjectFoodConditionList.list.GetCount () - iValue;

  return ObjectFoodConditionList.ReturnName (dam, false);
  } // end of DisplayFoodCondition

#define MAXVALUES 6

typedef struct 
  {
    char * sLabel;
    bool bEnabled;
    t_DisplayMeaning DisplayMeaning;
    t_ChooseMeaning ChooseMeaning;
  } t_itemvalue;

typedef struct 
  {
  int iItemType;
  t_itemvalue ValueDetails [MAXVALUES];  // meaning of all 6 values
  } t_itemvalues;


const t_itemvalues SMAUGItemValues [] =
    {       
      { ITEM_ARMOR,
        {
        { "Current AC:", true },   // 1
        { "Original AC:", true },  // 2
        } // end of 6 values
      },   // end of item
      { ITEM_CONTAINER,
        {
        { "Capacity:", true },   // 1
        { "Flags:", true },  // 2
        { "Key vnum:", true, DisplayKey, ChooseKey },  // 3
        { "Condition:", true },  // 4
        } // end of 6 values
      },   // end of item
      { ITEM_DRINK_CON,
        {
        { "Capacity:", true },   // 1
        { "Quantity:", true },  // 2
        { "Liquid #:", true },  // 3
        { "Poison?:", true, DisplayYesOrNo, ChoosePoisoned },  // 4
        } // end of 6 values
      },   // end of item
      { ITEM_FOOD,
        {
        { "Food value:", true },   // 1
        { "Condition:", true },  // 2
        { "?:", true },  // 3
        { "Poison?:", true, DisplayYesOrNo, ChoosePoisoned },  // 4
        } // end of 6 values
      },   // end of item
      { ITEM_HERB,
        {
        { "?:", true },   // 1
        { "Charges:", true },  // 2
        { "Herb #:", true },  // 3
        } // end of 6 values
      },   // end of item
      { ITEM_KEY,
        {
        { "Lock #:", true },   // 1
        } // end of 6 values
      },   // end of item
      { ITEM_LEVER,
        {
        { "Lever flags:", true },   // 1
        { "Vnum/sn:", true },  // 2
        { "Vnum:", true },  // 3
        { "Vnum/value:", true },  // 4
        } // end of 6 values
      },   // end of item
      { ITEM_LIGHT,
        {
        { "" },   // 1
        { "" },  // 2
        { "Hours left:", true },  // 3
        } // end of 6 values
      },   // end of item
      { ITEM_MONEY,
        {
        { "# coins:", true },   // 1
        { "Coin type:", true },  // 2
        } // end of 6 values
      },   // end of item
      { ITEM_PILL,
        {
        { "Spell level:", true },   // 1
        { "Spell 1:", true, DisplaySMAUGSpell, ChooseSMAUGSpell },  // 2
        { "Spell 2:", true, DisplaySMAUGSpell, ChooseSMAUGSpell },  // 3
        { "Spell 3:", true, DisplaySMAUGSpell, ChooseSMAUGSpell },  // 4
        { "Food value:", true },  // 5
        } // end of 6 values
      },   // end of item
      { ITEM_POTION,
        {
        { "Spell level:", true },   // 1
        { "Spell 1:", true, DisplaySMAUGSpell, ChooseSMAUGSpell },  // 2
        { "Spell 2:", true, DisplaySMAUGSpell, ChooseSMAUGSpell },  // 3
        { "Spell 3:", true, DisplaySMAUGSpell, ChooseSMAUGSpell },  // 4
        } // end of 6 values
      },   // end of item
      { ITEM_SALVE,
        {
        { "Spell level:", true },   // 1
        { "Max charge:", true },  // 2
        { "Charges:", true },  // 3
        { "Delay:", true },  // 4
        { "Spell:", true, DisplaySMAUGSpell, ChooseSMAUGSpell },  // 5
        { "Spell:", true, DisplaySMAUGSpell, ChooseSMAUGSpell },  // 6
        } // end of 6 values
      },   // end of item
      { ITEM_SCROLL,
        {
        { "Spell level:", true },   // 1
        { "Spell 1:", true, DisplaySMAUGSpell, ChooseSMAUGSpell },  // 2
        { "Spell 2:", true, DisplaySMAUGSpell, ChooseSMAUGSpell },  // 3
        { "Spell 3:", true, DisplaySMAUGSpell, ChooseSMAUGSpell },  // 4
        } // end of 6 values
      },   // end of item
      { ITEM_STAFF,
        {
        { "Spell level:", true },   // 1
        { "Max charges:", true },  // 2
        { "Charges:", true },  // 3
        { "Spell:", true, DisplaySMAUGSpell, ChooseSMAUGSpell },  // 4
        } // end of 6 values
      },   // end of item
      { ITEM_SWITCH,
        {
        { "Lever flags:", true },   // 1
        { "Vnum/sn:", true },  // 2
        { "Vnum:", true },  // 3
        { "Vnum/value:", true },  // 4
        } // end of 6 values
      },   // end of item
      { ITEM_TRAP,
        {
        { "Charges:", true },   // 1
        { "Type:", true },  // 2
        { "Level:", true },  // 3
        { "Flags:", true },  // 4
        } // end of 6 values
      },   // end of item
      { ITEM_TREASURE,
        {
        { "Type:", true },   // 1
        { "Condition:", true },  // 2
        } // end of 6 values
      },   // end of item
      { ITEM_WAND,
        {
        { "Level:", true },   // 1
        { "Max charges:", true },  // 2
        { "Charges:", true },  // 3
        { "Spell:", true, DisplaySMAUGSpell, ChooseSMAUGSpell },  // 4
        } // end of 6 values
      },   // end of item
      { ITEM_WEAPON,
        {
        { "Condition:", true, DisplayWeaponCondition, ChooseWeaponCondition },   // 1
        { "Num dice:", true },  // 2
        { "Size dice:", true },  // 3
        { "Weapon type:", true, DisplayWeaponType, ChooseWeaponType },  // 4
        } // end of 6 values
      },   // end of item

        {
        -1
        } // end of item list
  };    // end of SMAUGItemValues

const t_itemvalues ROMItemValues [] =
    {       
      { ITEM_ARMOR,
        {
        { "AC pierce:", true },   // 1
        { "AC bash:", true },  // 2
        { "AC slash:", true },   // 3
        { "AC magic:", true },  // 4
        } // end of 6 values
      },   // end of item
      { ITEM_CONTAINER,
        {
        { "Max. total wt:", true },   // 1
        { "Flags:", true, DisplayContainer, ChooseContainer },  // 2
        { "Key vnum:", true, DisplayKey, ChooseKey },  // 3
        { "Max single weight:", true },  // 4
        { "Weight multiplier %:", true },  // 5
        } // end of 6 values
      },   // end of item
      { ITEM_DRINK_CON,
        {
        { "Capacity:", true },   // 1
        { "Quantity:", true },  // 2
        { "Liquid type:", true, DisplayLiquid, ChooseLiquid },  // 3
        { "Poison?:", true, DisplayYesOrNo, ChoosePoisoned },  // 4
        } // end of 6 values
      },   // end of item
      { ITEM_FOUNTAIN,
        {
        { "" },   // 1
        { "" },  // 2
        { "Liquid type:", true, DisplayLiquid, ChooseLiquid },  // 3
        { "Poison?:", true, DisplayYesOrNo, ChoosePoisoned },  // 4
        } // end of 6 values
      },   // end of item
      { ITEM_FURNITURE,
       {
        { "Max. people:", true },   // 1
        { "" },  // 2
        { "Flags:", true, DisplayFurniture, ChooseFurniture },  // 3
        { "Mana regen.:", true },  // 4
        { "HP regen.:", true },  // 5
        } // end of 6 values
      },   // end of item
      { ITEM_FOOD,
        {
        { "Fill value:", true },   // 1
        { "Sate value:", true },  // 2
        { "" },  // 3
        { "Poison?:", true, DisplayYesOrNo, ChoosePoisoned },  // 4
        } // end of 6 values
      },   // end of item
      { ITEM_KEY,
        {
        { "Keep?:", true, DisplayYesOrNo, ChooseKeep },   // 1
        } // end of 6 values
      },   // end of item
      { ITEM_LIGHT,
        {
        { "" },   // 1
        { "" },  // 2
        { "Hours left:", true },  // 3
        } // end of 6 values
      },   // end of item

      { ITEM_MONEY,
        {
        { "Silver value:", true },   // 1
        { "Gold value:", true },  // 2
        } // end of 6 values
      },   // end of item
      { ITEM_PILL,
        {
        { "Spell level:", true },   // 1
        { "Spell 1:", true, DisplayROMSpell, ChooseROMSpell },  // 2
        { "Spell 2:", true, DisplayROMSpell, ChooseROMSpell },  // 3
        { "Spell 3:", true, DisplayROMSpell, ChooseROMSpell },  // 4
        { "Spell 4:", true, DisplayROMSpell, ChooseROMSpell },  // 5
        } // end of 6 values
      },   // end of item
      { ITEM_POTION,
        {
        { "Spell level:", true },   // 1
        { "Spell 1:", true, DisplayROMSpell, ChooseROMSpell },  // 2
        { "Spell 2:", true, DisplayROMSpell, ChooseROMSpell },  // 3
        { "Spell 3:", true, DisplayROMSpell, ChooseROMSpell },  // 4
        { "Spell 4:", true, DisplayROMSpell, ChooseROMSpell },  // 5
        } // end of 6 values
      },   // end of item
      { ITEM_SCROLL,
        {
        { "Spell level:", true },   // 1
        { "Spell 1:", true, DisplayROMSpell, ChooseROMSpell },  // 2
        { "Spell 2:", true, DisplayROMSpell, ChooseROMSpell },  // 3
        { "Spell 3:", true, DisplayROMSpell, ChooseROMSpell },  // 4
        { "Spell 4:", true, DisplayROMSpell, ChooseROMSpell },  // 5
        } // end of 6 values
      },   // end of item
      { ITEM_STAFF,
        {
        { "Spell level:", true },   // 1
        { "Max charges:", true },  // 2
        { "Charges:", true },  // 3
        { "Sn:", true, DisplayROMSpell, ChooseROMSpell },  // 4
        } // end of 6 values
      },   // end of item
      { ITEM_PORTAL,
        {
        { "Num. charges:", true },   // 1
        { "" },  // 2
        { "Gate flag:", true, DisplayPortalFlags, ChoosePortalFlags },  // 3
        { "Room vnum:", true, DisplayRoom, ChooseRoom },  // 4
        } // end of 6 values
      },   // end of item

      { ITEM_WAND,
        {
        { "Level:", true },   // 1
        { "Max charges:", true },  // 2
        { "Current charges:", true },  // 3
        { "Spell:", true, DisplayROMSpell, ChooseROMSpell },  // 4
        } // end of 6 values
      },   // end of item
      { ITEM_WEAPON,
        {
        { "Weapon class:", true, DisplayWeaponClass, ChooseWeaponClass },   // 1
        { "Num dice:", true },  // 2
        { "Size dice:", true },  // 3
        { "Weapon type:", true, DisplayWeaponType, ChooseWeaponType },  // 4
        { "Flags:", true, DisplayWeaponFlags, ChooseWeaponFlags } // 5
        } // end of 6 values
      },   // end of item

        {
        -1
        } // end of item list
  };  // end of ROMItemValues


  // arrays of item value lists (0 = SMAUG, 1 = ROM)

const t_itemvalues * ItemValues [] =
  { 
  SMAUGItemValues,
  ROMItemValues,
  };


void CObjectStatsPage::UpdateLabels (void)
  {
int i,
    value;

CWnd * ctlLabel [MAXVALUES] = 
  {
  &m_ctlLabelValue1,
  &m_ctlLabelValue2,
  &m_ctlLabelValue3,
  &m_ctlLabelValue4,
  &m_ctlLabelValue5,
  &m_ctlLabelValue6
  };  // end of label controls

CWnd * ctlButton [MAXVALUES] = 
  {
  &m_ctlChoose1,
  &m_ctlChoose2,
  &m_ctlChoose3,
  &m_ctlChoose4,
  &m_ctlChoose5,
  &m_ctlChoose6
  };  // end of button controls

// 0 = eAsk, 1=SMAUG, 2=ROM etc.
int AreaIndex = m_object->m_pDoc->m_AreaType - 1;
  
  // scan table provided area type is allowed for here
  if (AreaIndex < NUMITEMS (ItemValues)) 
    {
    const t_itemvalues * ItemList = ItemValues [AreaIndex];

    for (i = 0; ItemList [i].iItemType != -1; i++)
      {

      if (ItemList [i].iItemType == m_object->item_type)
        {
        for (value = 0; value < MAXVALUES; value++)
          {
          if (ItemList [i].ValueDetails [value].sLabel)
            ctlLabel [value]->SetWindowText (ItemList [i].ValueDetails [value].sLabel);
          else
            ctlLabel [value]->SetWindowText ("");
          ctlButton [value]->ShowWindow 
              (ItemList [i].ValueDetails [value].ChooseMeaning != NULL ?
                SW_SHOW : SW_HIDE);
        
          }
        UpdateDescriptions ();
        return;
        } // end of type found

      }   // end of searching for item type

    } // end of area type allowed for

  // not found - use defaults -- which at present will be nothing :)

  for (value = 0; value < MAXVALUES; value++)
    {
//    ctlLabel [value]->SetWindowText (CFormat ("Value%i:", value + 1));
    ctlLabel [value]->SetWindowText ("");
    ctlButton [value]->ShowWindow (SW_HIDE);
    }   // end of setting labels and buttons to defaults    

  UpdateDescriptions ();

  }   // end of CObjectStatsPage::UpdateLabels


void CObjectStatsPage::UpdateDescriptions (void)
  {
int i,
    value;

CString strField;
CString strOldDescription,
        strNewDescription;

int iField;

CWnd * ctlDescription [MAXVALUES] = 
  {
  &m_ctlDescValue1,
  &m_ctlDescValue2,
  &m_ctlDescValue3,
  &m_ctlDescValue4,
  &m_ctlDescValue5,
  &m_ctlDescValue6
  };  // end of description controls

CWnd * ctlValue [MAXVALUES] = 
  {
  &m_ctlValue1,
  &m_ctlValue2,
  &m_ctlValue3,
  &m_ctlValue4,
  &m_ctlValue5,
  &m_ctlValue6
  };  // end of value controls

// 0 = eAsk, 1=SMAUG, 2=ROM etc.
int AreaIndex = m_object->m_pDoc->m_AreaType - 1;
  
  // scan table provided area type is allowed for here
  if (AreaIndex < NUMITEMS (ItemValues)) 
    {
    const t_itemvalues * ItemList = ItemValues [AreaIndex];

    for (i = 0; ItemList [i].iItemType != -1; i++)
    {

    if (ItemList [i].iItemType == m_object->item_type)
      {
      for (value = 0; value < MAXVALUES; value++)
        {

        // get amended text of window

        ctlValue [value]->GetWindowText(strField);

        // convert to number

        // if empty, assume zero
        if (strField.IsEmpty ())
          iField = 0;
        else
          iField = atoi (strField);

        if (ItemList [i].ValueDetails [value].DisplayMeaning)
          {
          strNewDescription = ((*(ItemList [i].ValueDetails [value].DisplayMeaning)) 
                              (iField, m_object->m_pDoc));
          ctlDescription [value]->GetWindowText (strOldDescription);
          if (strOldDescription != strNewDescription)   // avoid flicker
            ctlDescription [value]->SetWindowText (strNewDescription);
          }
        else
          // no description routine given - blank out any existing description
          {
          ctlDescription [value]->GetWindowText (strOldDescription);
          if (!strOldDescription.IsEmpty ())
            ctlDescription [value]->SetWindowText ("");
          }
        
        } // end of all 6 values

      return;
      } // end of type found

    }   // end of searching for item type

    } // end of area type allowed for

  for (value = 0; value < MAXVALUES; value++)
    {
    ctlDescription [value]->GetWindowText (strOldDescription);
    if (!strOldDescription.IsEmpty ())
      ctlDescription [value]->SetWindowText ("");
    }

  }  // end of CObjectStatsPage::UpdateDescriptions

// if any of the 6 values change, update all descriptions (ie. value explanations)
void CObjectStatsPage::OnChangeValue() 
{
  UpdateDescriptions ();
}


void CObjectStatsPage::ChooseItem (const int iItem)
  {

CWnd * ctlValue [MAXVALUES] = 
  {
  &m_ctlValue1,
  &m_ctlValue2,
  &m_ctlValue3,
  &m_ctlValue4,
  &m_ctlValue5,
  &m_ctlValue6
  };  // end of value controls

int iValue;
CString strField;
int iField;
int i;

CObjectView * wndParent = (CObjectView *) GetParent ();

// 0 = eAsk, 1=SMAUG, 2=ROM etc.
int AreaIndex = m_object->m_pDoc->m_AreaType - 1;
  
  // scan table provided area type is allowed for here
  if (AreaIndex < NUMITEMS (ItemValues)) 
    {
    const t_itemvalues * ItemList = ItemValues [AreaIndex];

  for (i = 0; ItemList [i].iItemType != -1; i++)
    {

    if (ItemList [i].iItemType == m_object->item_type)
      {

      if (ItemList [i].ValueDetails [iItem].ChooseMeaning)
        {
        // get amended text of window

        ctlValue [iItem]->GetWindowText(strField);

        // convert to number

        iField = atoi (strField);
        wndParent->m_bEditingText = true;
        iValue = ((*(ItemList [i].ValueDetails [iItem].ChooseMeaning))
                (iField, m_object->m_pDoc));
        wndParent->m_bEditingText = false;
        ctlValue [iItem]->SetWindowText(CFormat ("%i", iValue));

        }

      return;
      } // end of type found

    }   // end of searching for item type

    } // end of area type allowed for

  } // end of CObjectStatsPage::ChooseItem

void CObjectStatsPage::OnChoose1() 
{
  ChooseItem (0);	
}

void CObjectStatsPage::OnChoose2() 
{
  ChooseItem (1);	
}

void CObjectStatsPage::OnChoose3() 
{
  ChooseItem (2);	
}

void CObjectStatsPage::OnChoose4() 
{
  ChooseItem (3);	
}

void CObjectStatsPage::OnChoose5() 
{
  ChooseItem (4);	
}

void CObjectStatsPage::OnChoose6() 
{
  ChooseItem (5);	
}
