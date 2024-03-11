/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// MobileResetsPage.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "AreaEditorDoc.h"
#include "MobileResetsPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMobileResetsPage dialog


CMobileResetsPage::CMobileResetsPage(CWnd* pParent /*=NULL*/)
	: CDialog(CMobileResetsPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMobileResetsPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

  m_mob = NULL;

}


void CMobileResetsPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMobileResetsPage)
	DDX_Control(pDX, IDC_GOTO_RESET, m_ctlGoToReset);
	DDX_Control(pDX, IDC_LOADED, m_ctlLoadedList);
	//}}AFX_DATA_MAP

  if (!pDX->m_bSaveAndValidate)
    AddResets ();

}


BEGIN_MESSAGE_MAP(CMobileResetsPage, CDialog)
	//{{AFX_MSG_MAP(CMobileResetsPage)
	ON_BN_CLICKED(IDC_GOTO_RESET, OnGotoReset)
	ON_LBN_SELCHANGE(IDC_LOADED, OnSelchangeLoaded)
	ON_LBN_DBLCLK(IDC_LOADED, OnDblclkLoaded)
	ON_LBN_SELCANCEL(IDC_LOADED, OnSelcancelLoaded)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMobileResetsPage message handlers


void CMobileResetsPage::AddResets (void)
  {

  POSITION resetPos;
  CReset * reset;
  CMUDObject * object;
  bool bThisMob = false;
  CRoom * room;

  m_ctlLoadedList.ResetContent ();

  // scan all open areas for resets

  for (POSITION docPos = App.m_pDocTemplate->GetFirstDocPosition();
      docPos != NULL; )
    {

    CAreaEditorDoc * pDoc = (CAreaEditorDoc *) App.m_pDocTemplate->GetNextDoc(docPos);

      // process each reset

    for (resetPos = pDoc->m_ResetList.GetHeadPosition (); resetPos; )
      {
      reset = pDoc->m_ResetList.GetNext (resetPos);

      switch (reset->command)
        {
        case 'M': // load mobile
          bThisMob = reset->arg1 == m_mob->vnum;

          if (!bThisMob)
            break;    // wrong mob - forget it

          if ((room = FindRoom ( reset->arg3)) == NULL)
            break;    // room not found

          reset->AddToListBox (m_ctlLoadedList, room->Summary ());

          break;

        case 'G': // give object
        case 'E': // equip object
          if (!bThisMob)   // not given to our mob
            break;    // wrong room - forget it

          if ((object = FindObj ( reset->arg1)) == NULL)
            break;    // object not found

          // aha! - add to list of objects
          reset->AddToListBox (m_ctlLoadedList, reset->Summary ());

          break;


        } // end of switch

      }   // end of processing each reset

    // now look for program cross-references

    // process each mob

    CMobile * mob;
    CMUDprogram * program;
    CString strErrorMessage;

    for (POSITION mobPos = pDoc->m_MobList.GetHeadPosition (); mobPos; )
      {
      mob = pDoc->m_MobList.GetNext (mobPos);
      for (POSITION progPos = mob->programlist.GetHeadPosition (); progPos; )
        {
        POSITION pos;

        program = mob->programlist.GetNext (progPos);

        for (pos = program->xref_mobs.GetHeadPosition (); pos; )
          if (program->xref_mobs.GetNext (pos) == m_mob->vnum)
            program->AddToListBox (m_ctlLoadedList,
                                  CFormat ("Program: %s <%s>", 
                                            (LPCTSTR) mob->Summary (),
                                            (LPCTSTR) program->Summary ()));


        }   // end of each program
    
      } // end of each mob

    // process each room

    for (POSITION RoomPos = pDoc->m_RoomList.GetHeadPosition (); RoomPos; )
      {
      room = pDoc->m_RoomList.GetNext (RoomPos);
      for (POSITION progPos = room->programlist.GetHeadPosition (); progPos; )
        {
        POSITION pos;

        program = room->programlist.GetNext (progPos);

        for (pos = program->xref_mobs.GetHeadPosition (); pos; )
          if (program->xref_mobs.GetNext (pos) == m_mob->vnum)
            program->AddToListBox (m_ctlLoadedList,
                                  CFormat ("Room prog: %s <%s>", 
                                            (LPCTSTR) room->Summary (),
                                            (LPCTSTR) program->Summary ()));
        }   // end of each program
    
      } // end of each room

    // process each object

    for (POSITION ObjectPos = pDoc->m_ObjectList.GetHeadPosition (); ObjectPos; )
      {
      object = pDoc->m_ObjectList.GetNext (ObjectPos);
      for (POSITION progPos = object->programlist.GetHeadPosition (); progPos; )
        {
        POSITION pos;

        program = object->programlist.GetNext (progPos);

        for (pos = program->xref_mobs.GetHeadPosition (); pos; )
          if (program->xref_mobs.GetNext (pos) == m_mob->vnum)
            program->AddToListBox (m_ctlLoadedList,
                                  CFormat ("Object prog: %s <%s>", 
                                            (LPCTSTR) object->Summary (),
                                            (LPCTSTR) program->Summary ()));

        }   // end of each program
    
      } // end of each object

    } // end of doing each document

  OnSelchangeLoaded ();

  }   // end of CMobileResetsPage::AddEntrances 

void CMobileResetsPage::OnGotoReset() 
{
// find which item they selected, and go to it

int nItem =  m_ctlLoadedList.GetCurSel( );

if (nItem != LB_ERR)
  ((CMUDitem *) m_ctlLoadedList.GetItemData (nItem))->GoTo ();
	
}

void CMobileResetsPage::OnSelchangeLoaded() 
{
  // find which item they selected

int nItem =  m_ctlLoadedList.GetCurSel( );
	
m_ctlGoToReset.EnableWindow (nItem != LB_ERR);

}

void CMobileResetsPage::OnDblclkLoaded() 
{
  OnGotoReset ();	
}

void CMobileResetsPage::OnSelcancelLoaded() 
{
  OnSelchangeLoaded ();
}
