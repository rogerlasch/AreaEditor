/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#include "stdafx.h"
#include "AreaEditor.h"

#include "MainFrm.h"

#include "AreaEditorDoc.h"
#include "AreaEditorView.h"
#include "defaults.h"

#include "genprint.h"

static int iPages = 0;
static int iLine = 0;
static BOOL bShowPrograms;

#define BUFFER_SIZE 50000

// ===============================================================================
static char * printline_buff = NULL;

static void WriteLine (CArchive & ar, 
                      int skip, 
                      const char * theline, ...)
  {
va_list arglist;

  if (!printline_buff)
    ThrowErrorException ("Not enough memory for printing buffer");

  // output the message as if it was a PRINTF type message
  va_start (arglist, theline);
  _vsnprintf (printline_buff, BUFFER_SIZE, theline, arglist);
  va_end (arglist);

  ar.WriteString (printline_buff);

  // now output the line feeds
  for (int i = 0; i < skip; i++)
    ar.WriteString (ENDLINE);

  } // end of WriteLine

// ===============================================================================
static void ShowPrograms (CArchive & ar, const CMUDprogramList & programlist)
  {
CMUDprogram * program;
int i = 1;

  if (programlist.IsEmpty ())
    return;

  // blank line before programs list
  WriteLine (ar, 1, "");

  // show programs
  i = 1;
  for (POSITION progPos = programlist.GetHeadPosition (); 
       progPos; 
       i++)
    {
    program = programlist.GetNext (progPos);
    if (bShowPrograms && i > 1)
      WriteLine (ar, 1, "");    // blank line before each program
    WriteLine (ar, 1, "Program %i: %s", i, (LPCTSTR) program->Summary ());
    if (bShowPrograms)
      {
      WriteLine (ar, 2, "-----------(begin program %i)--------------------", i);
      WriteLine (ar, 1, "%s", (LPCTSTR) program->comlist);
      WriteLine (ar, 1, "------------(end program %i)---------------------", i);
      }
    }   // end of each program

  }

// ===============================================================================
// returns true on error in producing report
bool CAreaEditorDoc::ProduceReport (CFile & fOutput)
  {
POSITION pos;
POSITION resetPos;
CReset * reset;
CMobile * mob;
CMUDObject * object;

  // find if they want program contents listed
  bShowPrograms = App.GetProfileInt  (sProfilePreferences, sProfileShowPrograms, 0);;

  CArchive ar (&fOutput, CArchive::store);

  printline_buff = new char [BUFFER_SIZE];

  try
    {

    // area header
    if (m_Area)
      {
      __int64 economy = (__int64) m_Area->high_economy * 1000000000 + // 1 billion
                        (__int64) m_Area->low_economy;

      WriteLine (ar, 1, "Author: %s", (LPCTSTR) m_Area->strAuthor);
      WriteLine (ar, 1, "Reset message: %s", (LPCTSTR) m_Area->strResetMsg);
      WriteLine (ar, 1, "Levels: Soft: %i to %i, Hard: %i to %i", 
                m_Area->low_soft_range,
                m_Area->hi_soft_range,
                m_Area->low_hard_range,
                m_Area->low_hard_range);
      WriteLine (ar, 1, "Repop frequency: %s", m_Area->reset_frequency > 0 
                ? (LPCTSTR) CFormat ("%i", m_Area->reset_frequency) : "default");
      WriteLine (ar, 1, "Mobile vnums %i to %i", m_Area->mob_low_vnum, m_Area->mob_hi_vnum);
      WriteLine (ar, 1, "Object vnums %i to %i", m_Area->obj_low_vnum, m_Area->obj_hi_vnum);
      WriteLine (ar, 1, "Room   vnums %i to %i", m_Area->room_low_vnum, m_Area->room_hi_vnum);
      WriteLine (ar, 1, "Economy: %I64d gold coins", economy);
      if (m_Area->flags)
        WriteLine (ar, 1, "Flags: %s", (LPCTSTR) convert_areaflag (m_Area->flags));
      }

    WriteLine (ar, 2, "");
    WriteLine (ar, 2, "***** %i room%s *****", PLURAL (m_RoomList.GetCount ()));

    // rooms ****************************************************************
    for (POSITION RoomPos = m_RoomList.GetHeadPosition (); RoomPos; )
      {
      CRoom * room = m_RoomList.GetNext (RoomPos);
    
      WriteLine (ar, 1, "%s", (LPCTSTR) room->Summary ());
      WriteLine (ar, 1, "%s", (LPCTSTR) room->description);

      if (room->room_flags)
        WriteLine (ar, 1, "Flags: %s", (LPCTSTR) convert_room_flags (room->room_flags));
      WriteLine (ar, 2, "Sector type: %s", 
                RoomSectorList.ReturnName (room->sector_type, false));

      // show all exits

      if (!room->exitlist.IsEmpty ())
        {
        WriteLine (ar, 1, "Exits: ");

        for (pos = room->exitlist.GetHeadPosition (); pos; )
          {
          CExit * exit = room->exitlist.GetNext (pos);
          WriteLine (ar, 1, "%s %s", (LPCTSTR) exit->Summary (), 
                      (LPCTSTR) convert_exit_flags (exit->exit_info));
          if (IS_SET (exit->exit_info, EX_LOCKED))
            {
            object = FindObj (exit->key);
            if (object)
              WriteLine (ar, 1, "... key: %s", (LPCTSTR) object->Summary ());
            }   // end of exit being locked

          }   // end of processing each exit

        WriteLine (ar, 1, "");    // wrap up line after exits
        } // end of having some exits

        // process each reset to show mobs and objects in the room

        bool bThisRoom = false;

        for (resetPos = m_ResetList.GetHeadPosition (); resetPos; )
          {
          reset = m_ResetList.GetNext (resetPos);

          switch (reset->command)
            {
            case 'M': // load mobile

              bThisRoom = reset->arg3 == room->vnum;

              if (!bThisRoom)
                break;    // wrong room - forget it

              if ((mob = FindMob( reset->arg1)) == NULL)
                  break;    // mob not found

              WriteLine (ar, 1, "Mobile %s", (LPCTSTR) mob->Summary ());
              WriteLine (ar, 1, "%s", (LPCTSTR) mob->long_descr);
              
              break;

            case 'O': // load object
              if (reset->arg3 != room->vnum)
                break;    // wrong room - forget it

              if ((object = FindObj ( reset->arg1)) == NULL)
                break;    // object not found

              WriteLine (ar, 1, "Object %s", (LPCTSTR) object->Summary ());
              WriteLine (ar, 1, "%s", (LPCTSTR) object->description);
              
              break;

              case 'G': // give object
              case 'E': // equip object
                if (!bThisRoom)   // not given to a mob in this room
                  break;    // wrong room - forget it

                if ((object = FindObj ( reset->arg1)) == NULL)
                  break;    // object not found

                WriteLine (ar, 1, "%s", (LPCTSTR) reset->Summary ());
                break;


            } // end of switch

          }   // end of processing each reset

      WriteLine (ar, 1, "");

      // now add extra descriptions

      for (POSITION extraPos = room->extralist.GetHeadPosition (); extraPos; )
        {
        CExtraDescription * extra = room->extralist.GetNext (extraPos);

        WriteLine (ar, 1, "%s", (LPCTSTR) extra->Summary ());
        WriteLine (ar, 2, "%s", (LPCTSTR) extra->description);

        }

      // now print all programs
      ShowPrograms (ar, room->programlist);

      WriteLine (ar, 2, "----------------------------------------------------------------------");
      // line of 70 hyphens, then blank line after room

      } // end of each room


    WriteLine (ar, 2, "");
    WriteLine (ar, 2, "***** %i mobile%s *****", PLURAL (m_MobList.GetCount ()));

      // mobiles ****************************************************************
    for (POSITION mobPos = m_MobList.GetHeadPosition (); mobPos; )
      {
      mob = m_MobList.GetNext (mobPos);

      WriteLine (ar, 1, "%s", (LPCTSTR) mob->Summary ());
      WriteLine (ar, 2, "%s", (LPCTSTR) mob->long_descr);
    
      WriteLine (ar, 2, "Mobile #%i \'%s\' is a level %i %s %s %s",
                 mob->vnum,
                 (LPCTSTR) mob->player_name,
                 mob->level,
                 (LPCTSTR) MobSexList.ReturnName (mob->sex, false), 
                 (LPCTSTR) MobRaceList.ReturnName (mob->race, false),
                 (LPCTSTR) MobRaceList.ReturnName (mob->mobclass, false)
                 );
      
      if (!mob->description.IsEmpty ())
        WriteLine (ar, 1, "%s", (LPCTSTR) mob->description);
 
      WriteLine (ar, 1,
              "Str: %i, Int: %i, Wis: %i, Dex: %i, Con: %i, Cha: %i, Lck: %i",
              mob->perm_str, mob->perm_int, mob->perm_wis, 
              mob->perm_dex, mob->perm_con, mob->perm_cha, mob->perm_lck);

      if (mob->act)
        WriteLine (ar, 1, "Actions: %s", (LPCTSTR) convert_actflag (mob->act));
      if (mob->affected_by)
        WriteLine (ar, 1, "Affected by: %s", (LPCTSTR) convert_affectflag (mob->affected_by));
      if (mob->xflags)
        WriteLine (ar, 1, "Body parts: %s", (LPCTSTR) convert_partflag (mob->xflags));
      if (mob->attacks)
        WriteLine (ar, 1, "Attacks: %s",  (LPCTSTR) convert_attackflag (mob->attacks));
      if (mob->defenses)
        WriteLine (ar, 1, "Defenses: %s", (LPCTSTR) convert_defenseflag (mob->defenses));
      if (mob->form)
        WriteLine (ar, 1, "Form: %s", (LPCTSTR) convert_formflag (mob->form));
      if (mob->resistant)
        WriteLine (ar, 1, "Resistant: %s",  (LPCTSTR) convert_risflag (mob->resistant));
      if (mob->immune)
        WriteLine (ar, 1, "Immune: %s",  (LPCTSTR) convert_risflag (mob->immune));
      if (mob->susceptible)
        WriteLine (ar, 1, "Susceptible: %s",  (LPCTSTR) convert_risflag (mob->susceptible));
      if (mob->speaks)
	      WriteLine (ar, 1, "Speaks: %s",  (LPCTSTR) convert_languages (mob->speaks));
      if (mob->speaking)
	      WriteLine (ar, 1, "Speaking: %s", (LPCTSTR) convert_languages (mob->speaking));

      // now print all programs
      ShowPrograms (ar, mob->programlist);

      WriteLine (ar, 2, "----------------------------------------------------------------------");
      // line of 70 hyphens, then blank line after mob

      }   // end of each mob

    WriteLine (ar, 2, "");
    WriteLine (ar, 2, "***** %i object%s *****", PLURAL (m_ObjectList.GetCount ()));

      // objects ****************************************************************
    for (POSITION ObjectPos = m_ObjectList.GetHeadPosition (); ObjectPos; )
      {
      object = m_ObjectList.GetNext (ObjectPos);

      WriteLine (ar, 1, "%s", (LPCTSTR) object->Summary ());
//      WriteLine (ar, 2, "%s", (LPCTSTR) object->short_descr); // short descr is in summary I think
      if (!object->description.IsEmpty ())
        WriteLine (ar, 2, "%s", (LPCTSTR) object->description);
    
      WriteLine (ar, 1, "Type: %s", 
                (LPCTSTR) ObjectItemList.ReturnName (object->item_type, false));
      WriteLine (ar, 1, "Weight: %i, Cost: %i",
                object->weight, object->cost);
      if (object->extra_flags)
        WriteLine (ar, 1, "Flags: %s",  (LPCTSTR) convert_object_flags (object->extra_flags));
      if (object->wear_flags)
        WriteLine (ar, 1, "Wear: %s", (LPCTSTR) convert_wear_flags (object->wear_flags));

    // list the affects caused by this object

      POSITION affectPos;
      CAffect * affect;
      CString strAffects;

      strAffects.Empty ();

      for (affectPos = object->affectlist.GetHeadPosition (); affectPos; )
        {
        affect = object->affectlist.GetNext (affectPos);

        if (!strAffects.IsEmpty ())
          strAffects += ", ";
         strAffects += affect->Summary ();

        }   // end of adding each affect item
      if (!strAffects.IsEmpty ())
        WriteLine (ar, 1, "Affects: %s",  (LPCTSTR) strAffects);

      // summarise spell type, armour class etc.
      CString strSummary = object->ValueSummary ();
      if (!strSummary.IsEmpty ())
        WriteLine (ar, 1, "%s",  (LPCTSTR) strSummary);

      WriteLine (ar, 1, "");

      // now add extra descriptions

      for (POSITION extraPos = object->extralist.GetHeadPosition (); extraPos; )
        {
        CExtraDescription * extra = object->extralist.GetNext (extraPos);

        WriteLine (ar, 1, "%s", (LPCTSTR) extra->Summary ());
        WriteLine (ar, 1, "%s", (LPCTSTR) extra->description);

        }

      // now print all programs
      ShowPrograms (ar, object->programlist);

      WriteLine (ar, 2, "----------------------------------------------------------------------");
      // line of 70 hyphens, then blank line after object
      } // end of each object
    

    }   // end of try
  catch (CException * e)
    {
    e->ReportError ();
    ar.Close ();
    e->Delete ();
    Frame.SetStatusMessage (READY);
    delete [] printline_buff;
    printline_buff = NULL;
    return true;
    }

  // good exit
  ar.Write ("", 1);   // write trailing null
  ar.Close ();
  delete [] printline_buff;
  printline_buff = NULL;
  return false;

}   // end of CAreaEditorDoc::ProduceReport

void CAreaEditorView::OnFilePrint() 
{
CAreaEditorDoc* pDoc = GetDocument();
ASSERT_VALID(pDoc);

int iLinesPerPage = App.GetProfileInt  (sProfilePreferences, sProfileLinesPerpage, 60);
CString strName = "Untitled world";

if (pDoc->m_Area && !pDoc->m_Area->strAreaName.IsEmpty ())
  strName = pDoc->m_Area->strAreaName;

if (App.GetProfileInt  (sProfilePreferences, sProfilePrintToFile, 0))
  {
	  CFileDialog	dlg(FALSE,						// FALSE for FileSave
					  "txt",						// default extension
					  "arealisting.txt",
					  OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_PATHMUSTEXIST,
					  "Text files (*.txt)|*.txt||",
					  this);
	  dlg.m_ofn.lpstrTitle = "Area listing";

	  if (dlg.DoModal() != IDOK)
		  return;

	  try
	    {
		  CFile	f (dlg.GetPathName(), CFile::modeCreate|CFile::modeWrite|CFile::shareExclusive);

      if (pDoc->ProduceReport (f))
        return;     // error in producing form
    
      }
	  catch (CException* e)
	  {
		  e->ReportError();
		  e->Delete();
	  }

  return;
  }   // end of printing to a file


CMemFile f;      // open memory file for writing

Frame.SetStatusMessage ("Generating print file...");

if (pDoc->ProduceReport (f))
  return;     // error in producing form

iPages = 0;
iLine = 0;

// printer control block for printing

t_print_control_block pcb;

// count pages in print file - allow 4 lines for header and footer

  Frame.SetStatusMessage ("Counting pages...");
  
  try
    {

    CString str;

    f.SeekToBegin ();   // back to start of file, we now read it back in
    CArchive ar (&f, CArchive::load);     // we can read an archive as lines
    while (ar.ReadString (str))
      iLine++;

    } // end of try

  catch (...)
    {
    ::AfxMessageBox ("An error occurred whilst printing area", 
                      MB_ICONEXCLAMATION);
    Frame.SetStatusMessage (READY);
    return;
    } // end of catching an exception

  Frame.SetStatusMessage (READY);

  // now work out how many pages that would have taken
  iPages = (iLine + (iLinesPerPage - 4) - 1) / (iLinesPerPage - 4);

// attempt to open the printer

  if (print_start_document (pcb, 
                            strName, 
                            1, 
                            iPages,
                            App.GetProfileInt  (sProfilePreferences, sProfileLeftMargin, 15),
                            App.GetProfileInt  (sProfilePreferences, sProfileTopMargin, 15),
                            iLinesPerPage,
                            App.GetProfileInt  (sProfilePreferences, sProfileFontSize, 9),
                            App.GetProfileInt  (sProfilePreferences, sProfileFontSize, 9),   // Line spacing
                            App.GetProfileString  (sProfilePreferences, sProfileFontName, "Courier"),
                            false))
    return;

  Frame.SetStatusMessage ("Printing area...");

  int current_line = iLinesPerPage;   // force new page immediately

  try
    {

    CString str;

    f.SeekToBegin ();   // back to start of file, we now read it back in
    CArchive ar (&f, CArchive::load);     // we can read an archive as lines
    while (ar.ReadString (str))
      {

// do footer and header if required

    if (current_line > (iLinesPerPage - 2))
      {

// do footer if not first page

      if (pcb.current_page > 0)
        {
        if (print_printline (pcb, 1, ""))     // first do a blank Line
          break;

        print_font (pcb, FONT_BOLD);

        if (print_printline (pcb, 1, "Page %i of %i", 
                              pcb.current_page, iPages))     // then print the page number
          break;

        print_font (pcb, FONT_NORMAL);

        print_end_page (pcb);

        }   // end of not first page

// now do page header

      print_start_page (pcb);

      print_font (pcb, FONT_BOLD | FONT_UNDERLINE);

      CString strTime;
      strTime = CTime::GetCurrentTime().Format ("%A, %B %d, %Y, %#I:%M %p");

      if (print_printline (pcb, 2, "%s - %s", 
                            (LPCTSTR) strName,
                            (LPCTSTR) strTime)) 
        break;

      print_font (pcb, FONT_NORMAL);

      current_line = 2;     // back to top of page
        
      }  // end of past end of page
      
 // finished header and footer, print the current Line

      print_font (pcb, FONT_NORMAL);

      if (print_printline (pcb, 1, str))   // print each line
        break;

      current_line++;

      }   // end of processing each line

    ar.Close ();      // finished with archive
    }
  catch (...)
    {
    ::AfxMessageBox ("An error occurred whilst printing area", 
                      MB_ICONEXCLAMATION);
    Frame.SetStatusMessage (READY);
    return;
    } // end of catching an exception

// do final page footer

  if (!pcb.cancelled)
    {
    while (current_line <= (iLinesPerPage - 2))
      {
      if (print_printline (pcb, 1, ""))     // first do a blank iLine
        break;
      current_line++;
      }
      
    if (!pcb.cancelled)
      {
      print_font (pcb, FONT_BOLD);

      print_printline (pcb, 1, "Page %ld", pcb.current_page); 

      print_font (pcb, FONT_NORMAL);
      } 

    }   // end of doing page footer

// terminate the report by sending out the last page

  print_end_page (pcb);
  
  print_end_document (pcb);

  if (pcb.cancelled)
    ::AfxMessageBox ("Printing cancelled");
                                             
  Frame.SetStatusMessage (READY);
	
}
