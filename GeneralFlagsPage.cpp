// GeneralFlagsPage.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "AreaEditorDoc.h"

#include "GeneralFlagsPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGeneralFlagsPage dialog


static int iCheckBoxes [32] =

  {
  IDC_FLAG1,
  IDC_FLAG2,
  IDC_FLAG3,
  IDC_FLAG4,
  IDC_FLAG5,
  IDC_FLAG6,
  IDC_FLAG7,
  IDC_FLAG8,
  IDC_FLAG9,
  IDC_FLAG10,
  IDC_FLAG11,
  IDC_FLAG12,
  IDC_FLAG13,
  IDC_FLAG14,
  IDC_FLAG15,
  IDC_FLAG16,
  IDC_FLAG17,
  IDC_FLAG18,
  IDC_FLAG19,
  IDC_FLAG20,
  IDC_FLAG21,
  IDC_FLAG22,
  IDC_FLAG23,
  IDC_FLAG24,
  IDC_FLAG25,
  IDC_FLAG26,
  IDC_FLAG27,
  IDC_FLAG28,
  IDC_FLAG29,
  IDC_FLAG30,
  IDC_FLAG31,
  IDC_FLAG32
  };

CGeneralFlagsPage::CGeneralFlagsPage(CWnd* pParent /*=NULL*/)
	: CDialog(CGeneralFlagsPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGeneralFlagsPage)
	//}}AFX_DATA_INIT

  m_pFlagsArray = NULL;
  m_pFlags = NULL;
  m_pDoc = NULL;

}


void CGeneralFlagsPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGeneralFlagsPage)
	//}}AFX_DATA_MAP

  if (pDX->m_bSaveAndValidate)
    {
  // unload the flag values
        
    if (!m_pFlagsArray || !m_pFlags || !m_pDoc)
      return;    // no array or flags - can't do much

    CButton * ctlChkBox;
    int i;
  
    // remember old flags value
    EXT_BV iOldValue = *m_pFlags;

    for (i = 0; i < MAX_BITS; i++)
      {
      ctlChkBox = (CButton *) GetDlgItem (iCheckBoxes [i]);
      if (ctlChkBox)
        if (!m_pFlagsArray->strName [i].IsEmpty ())
          {
          if (ctlChkBox->GetCheck ())
            SET_BIT (*m_pFlags, 1 << i);
          else
            REMOVE_BIT (*m_pFlags, 1 << i);
          }
      }   // end of checking the state of each check box

    // note if document has changed
    if (iOldValue != *m_pFlags)
      m_pDoc->SetModifiedFlag ();

    }   // end of saving and validating
}


BEGIN_MESSAGE_MAP(CGeneralFlagsPage, CDialog)
	//{{AFX_MSG_MAP(CGeneralFlagsPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGeneralFlagsPage message handlers


BOOL CGeneralFlagsPage::OnInitDialog() 
{
	CDialog::OnInitDialog();

  if (!m_pFlagsArray || !m_pFlags || !m_pDoc)
    return TRUE;    // no array or flags - can't do much

CButton * ctlChkBox;
int i;
BOOL bShowFlagNumbers = App.GetProfileInt  (sProfilePreferences, sProfileShowFlagNumbers, 0);

  for (i = 0; i < MAX_BITS; i++)
    {
    ctlChkBox = (CButton *) GetDlgItem (iCheckBoxes [i]);
    if (ctlChkBox)
      if (m_pFlagsArray->strName [i].IsEmpty ())
         ctlChkBox->ShowWindow(SW_HIDE);
      else
        {
        ctlChkBox->ShowWindow(SW_SHOW);
        if (bShowFlagNumbers)
          {
          // ROM flag is alpha, not a number
          if (m_pDoc->m_AreaType == eROM)
            {
            char c = 'A' + i;
            if (c > 'Z')
              c = 'a' + (i - 26);
            ctlChkBox->SetWindowText (CFormat ("%c. %s", c, (LPCTSTR) m_pFlagsArray->strName [i]));
            }
          else
            ctlChkBox->SetWindowText (CFormat ("%2i. %s", i + 1, (LPCTSTR) m_pFlagsArray->strName [i]));
          }
        else
          ctlChkBox->SetWindowText (m_pFlagsArray->strName [i]);
        ctlChkBox->SetCheck (IS_SET( *m_pFlags, 1 << i ));
        }
    }   // end of fixing up each check box

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
