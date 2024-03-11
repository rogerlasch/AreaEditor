/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#include "stdafx.h"

#include "AreaEditor.h"
#include "MainFrm.h"

// ========================================================================

void CAreaRead::Init (CArchive * ar)
  {
  
  m_ar = ar;
  m_nLine = 0;
  m_strLastLineRead.Empty ();
  m_strPartialLine.Empty ();
  Frame.CreateProgressBar (ar->GetFile ()->GetLength ());

  } // end of CAreaRead::Init 

void CAreaRead::Wrapup (void)
  {
  Frame.RemoveProgressBar ();
  m_ar = NULL;
  } // end of CAreaRead::Wrapup 

void CAreaRead::fread_getnonblankline (bool bLeftJustify)
  {

// read another line if necessary

  while (m_strPartialLine.IsEmpty ())
    if (!m_ar->ReadString (m_strPartialLine))
      ThrowErrorException ("Unexpected end of file");
    else
      {
      if (bLeftJustify)
        m_strPartialLine.TrimLeft ();
      m_strPartialLine.TrimRight ();

      // save line details in case of exception
      m_strLastLineRead = m_strPartialLine;
      m_nLine++;

      if (m_nLine % 32 == 0)
        Frame.UpdateProgressBar (m_ar->GetFile ()->GetPosition ());

      if (!bLeftJustify)
        break;    // keep blank lines for left-justification
      }

  if (bLeftJustify)
    m_strPartialLine.TrimLeft ();

  } // end of fread_getnonblankline

char CAreaRead::fread_letter (void)
  {
  fread_getnonblankline ();

  char c = m_strPartialLine [0];

  m_strPartialLine = m_strPartialLine.Mid (1);
  return c;

  }   // end of fread_letter

void CAreaRead::fread_to_eol (void)
  {
  m_strPartialLine.Empty ();
  }   // end of fread_to_eol

CString CAreaRead::fread_word (void)
  {

  fread_getnonblankline ();

  int iStart,
      iEnd;
  char cEnd = m_strPartialLine [0];
  if (cEnd == '\'' || cEnd == '"')
    iStart = 1;
  else
    {
    cEnd = ' ';
    iStart = 0;
    }

  for (iEnd = iStart; iEnd < m_strPartialLine.GetLength (); iEnd++)
    if (cEnd == ' ' ? isspace(m_strPartialLine [iEnd]) : 
          m_strPartialLine [iEnd]== cEnd )
      break;

  CString strResult = m_strPartialLine.Mid (iStart, iEnd - iStart);
  m_strPartialLine = m_strPartialLine.Mid (iEnd + 1);
  return strResult;

  } // end of fread_word

CString CAreaRead::fread_string (bool bLeftJustify)
  {

  CString strResult;
  int iEnd;
  char c;

  while (true)
    {
    fread_getnonblankline (bLeftJustify);

    for (iEnd = 0; iEnd < m_strPartialLine.GetLength (); iEnd++)
      if ((c = m_strPartialLine [iEnd]) == '~')
        break;

    strResult += m_strPartialLine.Left (iEnd);

    m_strPartialLine = m_strPartialLine.Mid (iEnd + 1);

    if (c == '~')
      break;

    strResult += ENDLINE;

    } // end of looping until we get a ~

  return strResult;

  } // end of fread_string

CString CAreaRead::fread_line (void)
  {

  CString strResult;

  fread_getnonblankline ();
  strResult = m_strPartialLine;
  m_strPartialLine.Empty ();
    
  return strResult;

  } // end of fread_line

long CAreaRead::fread_number (void)
  {

  long number = 0;
  int iPos;
  bool negative = false;
  char c;

  fread_getnonblankline ();

  iPos = 0;

// find the leading sign, if any

  if (m_strPartialLine [0] == '+')
    iPos++;
  else
  if (m_strPartialLine [0] == '-')
    {
    iPos++;
    negative = true;
    }

// must start with a digit

  if (!isdigit (m_strPartialLine[iPos]))
      ThrowErrorException ("Expected a number");

  while (iPos < m_strPartialLine.GetLength () &&
        isdigit (c = m_strPartialLine[iPos]))
    {
  	number = number * 10 + c - '0';
    iPos++;
    }

  if (negative)
	  number = 0 - number;

  m_strPartialLine = m_strPartialLine.Mid (iPos);

  if (c == '|')
    {
    m_strPartialLine = m_strPartialLine.Mid (1);    // skip the "|" symbol
    number += fread_number ();
    }

  return number;

  } // end of fread_line


// ========================================================================

void CAreaWrite::Init (CArchive * ar, long iItems)
  {
  
  m_ar = ar;
  m_nLine = 0;
  m_iSaveMilestone = 0;

  Frame.CreateProgressBar (iItems);


  } // end of CAreaWrite::Init 

void CAreaWrite::Wrapup (void)
  {
  Frame.RemoveProgressBar ();
  m_ar = NULL;
  } // end of CAreaWrite::Wrapup 


void CAreaWrite::DoSaveMilestone (void)
  {

  if (m_iSaveMilestone++ % 32 == 0)
    Frame.UpdateProgressBar (m_iSaveMilestone);

  }


void CAreaWrite::fwrite_string (const char * s)
  {
  m_ar->WriteString (CFormat ("%s" ENDLINE, s));
  } // end of CAreaWrite::fwrite_string
