/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#include "stdafx.h"
#include "AreaEditor.h"
#include "MainFrm.h"

#include "CommandsListDlg.h"


typedef struct 
  {
  char * sFunctionName;
  int FollowedBy;  // is command followed by something, eg. MPMLOAD 1234
  } t_specialcommands;


const t_specialcommands SpecialCommands [] =
  {
    { "do_mpmload", eCmdMobile },   // load a mob
    { "do_mpoload", eCmdObject },   // load an object
    { "do_mpforce", eCmdName | eCmdRepeat },  // force a named something to do something
    { "do_mpat",    eCmdRoom | eCmdRepeat}, // do a command at another location
    { "do_mptransfer",    eCmdName | eCmdRoom }, // transfer <name> to <room>
    { "do_mpgoto",    eCmdRoom },     // go to another room
    { "do_mpechoaround",    eCmdName },     // echo around that person
    { "do_cast",    eCmdSpell },     // cast a spell
  // This is for Brian Carter
    { "do_mpoput", eCmdObject },   // put an object into a container
  };


void CAreaEditorApp::fread_command (CFileRead & FileRead)
  {
    CString buf;
    CString word;
    bool fMatch;
    CCommand * command;

    command = new CCommand;

    m_CommandList.AddTail (command);

    while (true)
    {
	    word   = FileRead.fread_word ();
	    fMatch = FALSE;

	    switch ( UPPER(word[0]) )
	    {
	    case '*':
	        fMatch = TRUE;
	        FileRead.fread_to_eol ();
	        break;

	    case 'C':
	        KEY( "Code",	command->do_fun,	FileRead.fread_word () );
	        break;

	    case 'E':
	        if (word == "End" )
	          {
		        if (command->name.IsEmpty () )
		            ThrowErrorException ( "Name not found");

            if (command->do_fun.IsEmpty () )
		            ThrowErrorException( "Function not found");

            // look for commands with special flags
            for (int i = 0; i < NUMITEMS (SpecialCommands); i++)
              if (command->do_fun == SpecialCommands [i].sFunctionName)
                { // found a match - copy across flags
                command->FollowedBy = SpecialCommands [i].FollowedBy;
                break;
                }

		        return;
	          }
	        break;

        case 'F':
            KEY ("Flags", command->flags, FileRead.fread_number ());
            break;

	    case 'L':
	        KEY( "Level",	command->level,		FileRead.fread_number () );
	        KEY( "Log",		command->log,		FileRead.fread_number () );
	        break;

	    case 'N':
	        KEY( "Name",	command->name,		FileRead.fread_string () );
	        break;

	    case 'P':
	        KEY( "Position",	command->position,	FileRead.fread_number () );
	        break;
	    }
	    
	    if ( !fMatch )
          ThrowErrorException ("No match: %s", (LPCTSTR) word );
    } // end of read loop

  } // end of CAreaEditorApp::fread_command

void CAreaEditorApp::LoadCommands (const CString strFileName) 
  {
	CWaitCursor	wait;

	try
	  {
    CFileRead FileRead;

    // Open commands file
		CFile	fCommands (strFileName, CFile::modeRead|CFile::shareDenyWrite);

    CArchive ar(&fCommands, CArchive::load);

    FileRead.Init ("Loading commands", &ar);

	  try
	    {
	    while (true)
	     {
	     char letter;
	     CString word;

	     letter = FileRead.fread_letter();
	     if ( letter == '*' )
	       {
	      FileRead.fread_to_eol ();
	      continue;
	      }

	      if ( letter != '#' )
          ThrowErrorException ( "# not found.");

	      word = FileRead.fread_word ();
         if (word == "COMMAND")
	        {
		      fread_command (FileRead);
		      continue;
	        }
	      else
	        if (word == "END")
	          break;
	      else
          ThrowErrorException ( "Bad section.");
	     } // end of read loop
	    }   // end of try block
	  catch(CException* e)
  	  {
      FileRead.Wrapup ();
      DeleteCommands ();    // error on load - don't keep half of them
      e->ReportError ();
      ::AfxMessageBox (CFormat ("Error occurred in file %s at (line %ld) \"%s\"",
                    (LPCTSTR) strFileName,
                    FileRead.GetLineNumber (), 
                    (LPCTSTR) FileRead.GetLastLineRead ()),
                    MB_ICONINFORMATION);
		  e->Delete();
      ar.Close();
      return;
	    }

    ar.Close();

    FileRead.Wrapup ();

	  }
	catch(CException* e)
  	{
    ::AfxMessageBox (
                    CFormat ("Unable to open commands file: %s", 
                    (LPCTSTR) strFileName), 
                    MB_ICONEXCLAMATION);
		e->Delete();
    return;
	  }

  SortCommands ();

  } // end of CAreaEditorApp::LoadCommands 

void CAreaEditorApp::OnCommandsLoad() 
{
	CFileDialog	dlg(TRUE,						// TRUE for FileOpen
					"dat",						// default extension
					"commands.dat",						// initial file name
					OFN_HIDEREADONLY|OFN_FILEMUSTEXIST,
					"Commands files (*.dat)|*.dat||");
	dlg.m_ofn.lpstrTitle = "Select commands file";
	if (dlg.DoModal() != IDOK)
		return;

	LoadCommands (dlg.GetPathName());

}

void CMainFrame::OnCommandsEdit() 
{
CCommandsListDlg dlg;

  dlg.DoModal ();
}

void CMainFrame::OnUpdateCommandsEdit(CCmdUI* pCmdUI) 
{
  pCmdUI->Enable (!App.m_CommandList.IsEmpty ());	
}


void CAreaEditorApp::OnCommandsSave() 
{
	CFileDialog	dlg(FALSE,						// FALSE for FileSave
					"dat",						// default extension
					"commands.dat",
					OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_PATHMUSTEXIST,
					"Data files (*.dat)|*.dat||",
					&Frame);
	dlg.m_ofn.lpstrTitle = "Commands file";

	if (dlg.DoModal() != IDOK)
		return;

	try
	  {
    POSITION commandPos;
    CCommand * command;

		CFile	f (dlg.GetPathName(), CFile::modeCreate|CFile::modeWrite|CFile::shareExclusive);

    CArchive ar(&f, CArchive::store);

    for (commandPos = App.m_CommandList.GetHeadPosition (); commandPos; )
      {
      command = App.m_CommandList.GetNext (commandPos);

      ar.WriteString ("#COMMAND" ENDLINE);

      // these two lines are required
      ar.WriteString (CFormat ("Name        %s~" ENDLINE, (LPCTSTR) command->name));
      ar.WriteString (CFormat ("Code        %s"  ENDLINE, (LPCTSTR) command->do_fun));
      ar.WriteString (CFormat ("Position    %i" ENDLINE, command->position));
      ar.WriteString (CFormat ("Level       %i" ENDLINE, command->level));
      ar.WriteString (CFormat ("Log         %i" ENDLINE, command->log));
      if (command->flags)
        ar.WriteString (CFormat ("Flags       %i" ENDLINE, command->flags));

      ar.WriteString ("End" ENDLINE);    // end of this command
      ar.WriteString (ENDLINE);    // blank line
         
      }   // end of each command


    ar.WriteString ("#END" ENDLINE);    // commands file terminator

    ar.Close ();
    
    }
	catch (CException* e)
	{
		e->ReportError();
		e->Delete();
	}

  m_bCommandsDirty = false;
}

void CAreaEditorApp::OnUpdateCommandsSave(CCmdUI* pCmdUI) 
{
  pCmdUI->Enable (!m_CommandList.IsEmpty () && m_bCommandsDirty);	
	
}

void CAreaEditorApp::OnUpdateCommandsLoad(CCmdUI* pCmdUI) 
{
  pCmdUI->Enable (m_CommandList.IsEmpty ());	
}

void CAreaEditorApp::OnCommandsClose() 
{
  if (m_bCommandsDirty)
    {
    int iResponse = ::AfxMessageBox ("Commands file has changed. Save it?",
                                      MB_YESNOCANCEL | MB_ICONQUESTION);
    if (iResponse == IDCANCEL)
      return;

    if (iResponse == IDYES)
      OnCommandsSave ();

    }
  DeleteCommands ();
	
}

void CAreaEditorApp::OnUpdateCommandsClose(CCmdUI* pCmdUI) 
{
  pCmdUI->Enable (!m_CommandList.IsEmpty ());		
}

void CAreaEditorApp::DeleteCommands (void)
  {
// ========================================================================
// delete all commands

  for (POSITION commandPos = m_CommandList.GetHeadPosition (); commandPos; )
    delete m_CommandList.GetNext (commandPos);

  m_CommandList.RemoveAll ();   // pointers are deleted, remove list items

  m_bCommandsDirty = false;
  }


/*
 * Compare strings, case insensitive, for prefix matching.
 * Return TRUE if astr not a prefix of bstr
 */
bool str_prefix (const char *astr, const char *bstr)
{
    if ( !astr )
	    return TRUE;

    if ( !bstr )
	    return TRUE;

    if (*astr == 0)
      return TRUE;

    for ( ; *astr; astr++, bstr++ )
    {
	  if ( LOWER(*astr) != LOWER(*bstr) )
	      return TRUE;
    }

    return FALSE;
}



int CompareCommand (const void * elem1, const void * elem2)
  {
  // ah yes, *this* line was fun to get working :)
  return (*((CCommand **) elem1))->name.CompareNoCase ((*((CCommand **) elem2))->name);
  }

void CAreaEditorApp::SortCommands (void)
  {
POSITION CommandPos;
CTypedPtrArray <CPtrArray, CCommand*> CCommandsArray;
int iCount = App.m_CommandList.GetCount ();
int i;

	try
	  {

    CCommandsArray.SetSize (iCount);

    // extract pointers into a simple array
    for (i = 0, CommandPos = m_CommandList.GetHeadPosition (); CommandPos; i++)
      CCommandsArray.SetAt (i, m_CommandList.GetNext (CommandPos)); 


    // sort the array
    qsort (CCommandsArray.GetData (), 
           iCount,
           sizeof (CCommand *),
           CompareCommand);

    // get rid of old list
    m_CommandList.RemoveAll ();

    // re-add in sorted order
    for (i = 0; i < iCount; i++)
      m_CommandList.AddTail (CCommandsArray [i]);

    }   // end of try block
	catch(CException* e)
  	{
    e->ReportError ();
		e->Delete();
	  }


  }