/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#include "stdafx.h"
#include "AreaEditor.h"

static CStringArray FirstNames;
static CStringArray MiddleNames;
static CStringArray LastNames;

bool bNamesRead = false;

void ReadNames (void)
  {

  bNamesRead = false;

	try
	  {

    CString sBuf;
    BOOL bOK;

    FirstNames.RemoveAll ();
    MiddleNames.RemoveAll ();
    LastNames.RemoveAll ();

	  CFileDialog	dlg(TRUE,						// TRUE for FileOpen
					  "txt",						// default extension
					  "names.txt",						// initial file name
					  OFN_HIDEREADONLY|OFN_FILEMUSTEXIST,
					  "Text files (*.txt)|*.txt|All files (*.*)|*.*||");
	  dlg.m_ofn.lpstrTitle = "Select names file";
	  if (dlg.DoModal() != IDOK)
		  return;

    CStdioFile f (dlg.GetPathName(), CFile::modeRead|CFile::shareDenyNone|CFile::typeText);
  
    // look for [start]
    while (bOK = f.ReadString (sBuf))
      {
      sBuf.TrimRight ();
      sBuf.TrimLeft ();
      if (sBuf.CompareNoCase ("[start]") == 0)
        break;
      }
    if (!bOK)
      ThrowErrorException ("No [start] in names file");

    // look for [middle]
    while (bOK = f.ReadString (sBuf))
      {
      sBuf.TrimRight ();
      sBuf.TrimLeft ();
      if (sBuf.CompareNoCase ("[middle]") == 0)
        break;
      else
        FirstNames.Add (sBuf);
      }
    if (!bOK)
      ThrowErrorException ("No [middle] in names file");

    // look for [end]
    while (bOK = f.ReadString (sBuf))
      {
      sBuf.TrimRight ();
      sBuf.TrimLeft ();
      if (sBuf.CompareNoCase ("[end]") == 0)
        break;
      else
        MiddleNames.Add (sBuf);
      }
    if (!bOK)
      ThrowErrorException ("No [end] in names file");

    // look for [stop]
    while (bOK = f.ReadString (sBuf))
      {
      sBuf.TrimRight ();
      sBuf.TrimLeft ();
      if (sBuf.CompareNoCase ("[stop]") == 0)
        break;
      else
        LastNames.Add (sBuf);
      }
    if (!bOK)
      ThrowErrorException ("No [stop] in names file");
    bNamesRead = true;

    }
	catch (CException* e)
	  {
		e->ReportError();
		e->Delete();
	  }

  } // end of ReadNames

CString GenerateName (void)
  {
CString strName;

  if (!bNamesRead)
     ReadNames ();

  if (bNamesRead)
    {
    strName = FirstNames [rand () % FirstNames.GetSize ()];
    strName += MiddleNames [rand () % MiddleNames.GetSize ()];
    strName += LastNames [rand () % LastNames.GetSize ()];
    }

  return strName;

  } // end of GenerateName
