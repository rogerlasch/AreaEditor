/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#include "stdafx.h"
#include "AreaEditor.h"
#include "MainFrm.h"

#include "SocialsListDlg.h"

void CAreaEditorApp::fread_social (CFileRead & FileRead)
  {
    CString buf;
    CString word;
    bool fMatch;
    CSocial * social;

    social = new CSocial;

    m_SocialList.AddTail (social);
    
    while (true)
    {
	    word   =  FileRead.fread_word ();
	    fMatch = FALSE;

	    switch ( UPPER(word[0]) )
	    {
	    case '*':
	        fMatch = TRUE;
	        FileRead.fread_to_eol ();
	        break;

	    case 'C':
	        KEY( "CharNoArg",	social->char_no_arg,	FileRead.fread_string () );
	        KEY( "CharFound",	social->char_found,	FileRead.fread_string () );
	        KEY( "CharAuto",	social->char_auto,	FileRead.fread_string () );
	        break;

	    case 'E':
	        if (word == "End" )
	        {
		      if ( !social->name )
		          ThrowErrorException( "Name not found");

          if ( !social->char_no_arg )
		          ThrowErrorException( "CharNoArg not found");
		      
          return;
	        }
	        break;

	    case 'N':
	        KEY( "Name",	social->name,		FileRead.fread_string () );
	        break;

	    case 'O':
	        KEY( "OthersNoArg",	social->others_no_arg,	FileRead.fread_string () );
	        KEY( "OthersFound",	social->others_found,	FileRead.fread_string () );
	        KEY( "OthersAuto",	social->others_auto,	FileRead.fread_string () );
	        break;

	    case 'V':
	        KEY( "VictFound",	social->vict_found,	FileRead.fread_string () );
	        break;
	    }
	    
	    if ( !fMatch )
          ThrowErrorException ("No match: %s", (LPCTSTR) word);
    }

  } // end of CAreaEditorApp::fread_social

void CAreaEditorApp::LoadSocials (const CString	strFileName) 
  {

  CWaitCursor	wait;

	try
	  {
    CFileRead FileRead;

    // Open socials file
		CFile	fSocials (strFileName, CFile::modeRead|CFile::shareDenyWrite);

    CArchive ar(&fSocials, CArchive::load);

    FileRead.Init ("Loading socials", &ar);

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
         if (word == "SOCIAL")
	        {
		      fread_social (FileRead);
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
      DeleteSocials ();    // error on load - don't keep half of them
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
                    CFormat ("Unable to open socials file: %s", 
                    (LPCTSTR) strFileName), 
                    MB_ICONEXCLAMATION);
		e->Delete();
    return;
	  }


  SortSocials ();
  }

void CAreaEditorApp::OnSocialsLoad() 
{
	CFileDialog	dlg(TRUE,						// TRUE for FileOpen
					"dat",						// default extension
					"socials.dat",						// initial file name
					OFN_HIDEREADONLY|OFN_FILEMUSTEXIST,
					"Socials files (*.dat)|*.dat||");
	dlg.m_ofn.lpstrTitle = "Select socials file";
	if (dlg.DoModal() != IDOK)
		return;

	LoadSocials (dlg.GetPathName());

}


void CAreaEditorApp::OnSocialsClose() 
{
  if (m_bSocialsDirty)
    {
    int iResponse = ::AfxMessageBox ("Socials file has changed. Save it?",
                                      MB_YESNOCANCEL | MB_ICONQUESTION);
    if (iResponse == IDCANCEL)
      return;

    if (iResponse == IDYES)
      OnSocialsSave ();

    }
  DeleteSocials ();
}

void CAreaEditorApp::OnUpdateSocialsClose(CCmdUI* pCmdUI) 
{
  pCmdUI->Enable (!m_SocialList.IsEmpty ());	
}

void CAreaEditorApp::OnUpdateSocialsLoad(CCmdUI* pCmdUI) 
{
  pCmdUI->Enable (m_SocialList.IsEmpty ());	
}

void CAreaEditorApp::OnSocialsSave() 
{
	CFileDialog	dlg(FALSE,						// FALSE for FileSave
					"dat",						// default extension
					"socials.dat",
					OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_PATHMUSTEXIST,
					"Data files (*.dat)|*.dat||",
					&Frame);
	dlg.m_ofn.lpstrTitle = "Socials file";

	if (dlg.DoModal() != IDOK)
		return;

	try
	  {
    POSITION socialPos;
    CSocial * social;

		CFile	f (dlg.GetPathName(), CFile::modeCreate|CFile::modeWrite|CFile::shareExclusive);

    CArchive ar(&f, CArchive::store);

    for (socialPos = App.m_SocialList.GetHeadPosition (); socialPos; )
      {
      social = App.m_SocialList.GetNext (socialPos);

      ar.WriteString ("#SOCIAL" ENDLINE);

      // these two lines are required
      ar.WriteString (CFormat ("Name        %s~" ENDLINE, (LPCTSTR) social->name));
      ar.WriteString (CFormat ("CharNoArg   %s~" ENDLINE, (LPCTSTR) social->char_no_arg));

      // these are optional
      if (!social->others_no_arg.IsEmpty ())
        ar.WriteString (CFormat ("OthersNoArg %s~" ENDLINE, (LPCTSTR) social->others_no_arg));
      if (!social->char_found.IsEmpty ())
        ar.WriteString (CFormat ("CharFound   %s~" ENDLINE, (LPCTSTR) social->char_found));
      if (!social->others_found.IsEmpty ())
        ar.WriteString (CFormat ("OthersFound %s~" ENDLINE, (LPCTSTR) social->others_found));
      if (!social->vict_found.IsEmpty ())
        ar.WriteString (CFormat ("VictFound   %s~" ENDLINE, (LPCTSTR) social->vict_found));
      if (!social->char_auto.IsEmpty ())
        ar.WriteString (CFormat ("CharAuto    %s~" ENDLINE, (LPCTSTR) social->char_auto));
      if (!social->others_auto.IsEmpty ())
        ar.WriteString (CFormat ("OthersAuto  %s~" ENDLINE, (LPCTSTR) social->others_auto));

      ar.WriteString ("End" ENDLINE);    // end of this social
      ar.WriteString (ENDLINE);    // blank line
         
      }   // end of each social


    ar.WriteString ("#END" ENDLINE);    // socials file terminator

    ar.Close ();
    
    }
	catch (CException* e)
	{
		e->ReportError();
		e->Delete();
	}

  m_bSocialsDirty = false;
}

void CAreaEditorApp::OnUpdateSocialsSave(CCmdUI* pCmdUI) 
{
  pCmdUI->Enable (!m_SocialList.IsEmpty () && m_bSocialsDirty);	
  
}

void CAreaEditorApp::DeleteSocials (void)
  {
// ========================================================================
// delete all socials

  for (POSITION socialPos = m_SocialList.GetHeadPosition (); socialPos; )
    delete m_SocialList.GetNext (socialPos);

  m_SocialList.RemoveAll ();   // pointers are deleted, remove list items

  m_bSocialsDirty = false;

  }



void CMainFrame::OnSocialsEdit() 
{
CSocialsListDlg dlg;

  dlg.DoModal ();
	
}

void CMainFrame::OnUpdateSocialsEdit(CCmdUI* pCmdUI) 
{
  pCmdUI->Enable (!App.m_SocialList.IsEmpty ());	
	
}

int CompareSocial (const void * elem1, const void * elem2)
  {
  // ah yes, *this* line was fun to get working :)
  return (*((CSocial **) elem1))->name.CompareNoCase ((*((CSocial **) elem2))->name);
  }

void CAreaEditorApp::SortSocials (void)
  {
POSITION socialPos;
CTypedPtrArray <CPtrArray, CSocial*> CSocialsArray;
int iCount = App.m_SocialList.GetCount ();
int i;

	try
	  {

    CSocialsArray.SetSize (iCount);

    // extract pointers into a simple array
    for (i = 0, socialPos = m_SocialList.GetHeadPosition (); socialPos; i++)
      CSocialsArray.SetAt (i, m_SocialList.GetNext (socialPos)); 


    // sort the array
    qsort (CSocialsArray.GetData (), 
           iCount,
           sizeof (CSocial *),
           CompareSocial);

    // get rid of old list
    m_SocialList.RemoveAll ();

    // re-add in sorted order
    for (i = 0; i < iCount; i++)
      m_SocialList.AddTail (CSocialsArray [i]);

    }   // end of try block
	catch(CException* e)
  	{
    e->ReportError ();
		e->Delete();
	  }


  }