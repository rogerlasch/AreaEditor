/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// Format.cpp - format CStrings on-the-fly
//

#include "stdafx.h"
#include "format.h"


/////////////////////////////////////////////////////////////////////////////
// CFormat

CFormat::CFormat(LPCTSTR lpszFormat, ...)
{
	ASSERT(AfxIsValidString(lpszFormat, FALSE));

	va_list argList;
	va_start(argList, lpszFormat);
	FormatV(lpszFormat, argList);
	va_end(argList);
}

CFormat::CFormat(UINT nFormatID, ...)
{
	CString strFormat;
	VERIFY(strFormat.LoadString(nFormatID) != 0);

	va_list argList;
	va_start(argList, nFormatID);
	FormatV(strFormat, argList);
	va_end(argList);
}

CFormat::CFormat (LPCTSTR lpszFormat, va_list argList)
  {
	ASSERT(AfxIsValidString(lpszFormat, FALSE));
 
	FormatV(lpszFormat, argList);
  }

CFormat::CFormat (UINT nFormatID, va_list argList)
  {
	CString strFormat;
	VERIFY(strFormat.LoadString(nFormatID) != 0);

	FormatV(strFormat, argList);
  }

