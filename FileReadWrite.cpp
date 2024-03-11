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

// ========================================================================

void CFileRead::Init (const char * sMessage, 
                      CArchive * ar)
  {
  
  m_ar = ar;
  m_nLine = 0;
  m_strLastLineRead.Empty ();
  m_strPartialLine.Empty ();
  m_bProgressBar = false;

  if (strlen (sMessage) > 0)
    {
    Frame.CreateProgressBar (sMessage, ar->GetFile ()->GetLength ());
    m_bProgressBar = true;
    }

  } // end of CFileRead::Init 

void CFileRead::Wrapup (void)
  {
  if (m_bProgressBar)
    Frame.RemoveProgressBar ();
  m_ar = NULL;
  m_bProgressBar = false;
  } // end of CFileRead::Wrapup 

void CFileRead::fread_getnonblankline (const bool bLeftJustify)
  {

// read another line if necessary

  while (m_strPartialLine.IsEmpty ())
    {
    // find file position of this line
    if (!m_ar->ReadString (m_strPartialLine))
        ThrowErrorException ("Unexpected end of file");
    else
      {

      // removing leading spaces moves us further into the file
      if (bLeftJustify)
        m_strPartialLine.TrimLeft ();
      m_strPartialLine.TrimRight ();

      // save line details in case of exception
      m_strLastLineRead = m_strPartialLine;
      m_nLine++;

      if (m_bProgressBar)
        if (m_nLine % 32 == 0)
          Frame.UpdateProgressBar (m_ar->GetFile ()->GetPosition ());

      if (!bLeftJustify)
        break;    // keep blank lines for left-justification
      }
    } // end of read loop

  // removing leading spaces moves us further into the file
  if (bLeftJustify)
    m_strPartialLine.TrimLeft ();

  } // end of fread_getnonblankline

char CFileRead::fread_letter (void)
  {
  fread_getnonblankline ();

  char c = m_strPartialLine [0];

  m_strPartialLine = m_strPartialLine.Mid (1);
  return c;

  }   // end of fread_letter

CString CFileRead::fread_to_eol (void)
  {
  // we will return the rest of the line - it might be a comment
  CString strResult = m_strPartialLine;

  strResult.TrimRight ();

  m_strPartialLine.Empty ();
  return strResult;
  }   // end of fread_to_eol

CString CFileRead::fread_word (void)
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
  if (iEnd >= m_strPartialLine.GetLength ())
    m_strPartialLine.Empty ();
  else
    m_strPartialLine = m_strPartialLine.Mid (iEnd + 1);
  return strResult;

  } // end of fread_word

CString CFileRead::fread_string (const bool bLeftJustify)
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

    if (iEnd >= m_strPartialLine.GetLength ())
      m_strPartialLine.Empty ();
    else
      m_strPartialLine = m_strPartialLine.Mid (iEnd + 1);

    if (c == '~')
      break;

    strResult += ENDLINE;

    } // end of looping until we get a ~

  return strResult;

  } // end of fread_string

CString CFileRead::fread_line (void)
  {

  CString strResult;

  fread_getnonblankline ();

  strResult = m_strPartialLine;
  m_strPartialLine.Empty ();
    
  return strResult;

  } // end of fread_line

long CFileRead::fread_number (const bool bFlag)
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
    if (bFlag)
      {
      while (iPos < m_strPartialLine.GetLength () &&
            isalpha (c = m_strPartialLine[iPos]))
	      {
        number += flag_convert(c);
        iPos++;
  	    }
      }
    else
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

  } // end of fread_number


EXT_BV CFileRead::fread_bitvector (const bool bFlag)
  {

  EXT_BV ret = 0;
  char c;

  EXT_BV num = 0;
  
  for (int i = 0; i < 2; i++)
    {
  	num = (unsigned int) fread_number (bFlag);
    if (i == 1)
      num <<= 32; 
    ret |= num;
    // extended bitvectors should appear on a single line
    if (m_strPartialLine.IsEmpty ())
      break;
    c = m_strPartialLine [0];
	  if (c != '&')
	    break;
    m_strPartialLine = m_strPartialLine.Mid (1);
    }  // end of reading each number in the bitvector

  return ret;

  } // end of fread_bitvector


long CFileRead::flag_convert (const char letter)
  {
  long bitsum = 0;
  char i;

  if ('A' <= letter && letter <= 'Z') 
    {
    bitsum = 1;
    for (i = letter; i > 'A'; i--)
	    bitsum *= 2;
    }
  else if ('a' <= letter && letter <= 'z')
    {
    bitsum = 67108864; /* 2^26 */
    for (i = letter; i > 'a'; i --)
	    bitsum *= 2;
    }

  return bitsum;

  }

// ========================================================================

void CFileWrite::Init (const char * sMessage, CArchive * ar, long iItems)
  {
  
  m_ar = ar;
  m_nLine = 0;
  m_iSaveMilestone = 0;
  m_bProgressBar = false;

  if (strlen (sMessage) > 0)
    {
    Frame.CreateProgressBar (sMessage, iItems);
    m_bProgressBar = true;
    }

  } // end of CFileWrite::Init 

void CFileWrite::Wrapup (void)
  {
  if (m_bProgressBar)
    Frame.RemoveProgressBar ();
  m_ar = NULL;
  m_bProgressBar = false;
  } // end of CFileWrite::Wrapup 


void CFileWrite::DoSaveMilestone (void)
  {

  if (m_bProgressBar)
    if (m_iSaveMilestone++ % 32 == 0)
      Frame.UpdateProgressBar (m_iSaveMilestone);

  }


void CFileWrite::fwrite_string (const char * s)
  {
  m_ar->WriteString (CFormat ("%s" ENDLINE, s));
  } // end of CFileWrite::fwrite_string


#if 0

/*
 * Extended Bitvector Routines					-Thoric
 */

/* check to see if the extended bitvector is completely empty */
bool ext_is_empty( EXT_BV *bits )
{
  int x;

  for ( x = 0; x < XBI; x++ )
	  if ( bits->bits[x] != 0 )
	    return FALSE;

  return TRUE;
}

void ext_clear_bits( EXT_BV *bits )
{
  int x;

  for ( x = 0; x < XBI; x++ )
  	bits->bits[x] = 0;
}

/* for use by xHAS_BITS() -- works like IS_SET() */
int ext_has_bits( EXT_BV *var, EXT_BV *bits )
{
  int x, bit;

  for ( x = 0; x < XBI; x++ )
  	if ( (bit=(var->bits[x] & bits->bits[x])) != 0 )
	    return bit;

  return 0;
}

/* for use by xSAME_BITS() -- works like == */
bool ext_same_bits( EXT_BV *var, EXT_BV *bits )
{
  int x;

  for ( x = 0; x < XBI; x++ )
  	if ( var->bits[x] != bits->bits[x] )
	    return FALSE;

  return TRUE;
}

/* for use by xSET_BITS() -- works like SET_BIT() */
void ext_set_bits( EXT_BV *var, EXT_BV *bits )
{
  int x;

  for ( x = 0; x < XBI; x++ )
	  var->bits[x] |= bits->bits[x];
}

/* for use by xREMOVE_BITS() -- works like REMOVE_BIT() */
void ext_remove_bits( EXT_BV *var, EXT_BV *bits )
{
  int x;

  for ( x = 0; x < XBI; x++ )
	  var->bits[x] &= ~(bits->bits[x]);
}

/* for use by xTOGGLE_BITS() -- works like TOGGLE_BIT() */
void ext_toggle_bits( EXT_BV *var, EXT_BV *bits )
{
  int x;

  for ( x = 0; x < XBI; x++ )
  	var->bits[x] ^= bits->bits[x];
}


#endif

/* return a string for writing a bitvector to a file */
CString print_bitvector (const EXT_BV & bits)
{

CString strResult;

LARGE_INTEGER number;

  number.QuadPart = bits;

  if (number.HighPart == 0)
    strResult = CFormat ("%d", number.LowPart);
  else
    strResult = CFormat ("%d&%d", number.LowPart, number.HighPart);

  return strResult;
}

/*
 * Write an extended bitvector to a file			-Thoric
 */

void CFileWrite::fwrite_bitvector (const EXT_BV & bits)
  {
  m_ar->WriteString (CFormat ("%s" ENDLINE, (LPCTSTR) print_bitvector (bits)));
  } // end of CFileWrite::fwrite_bitvector
