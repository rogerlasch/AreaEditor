/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CFormat

struct CFormat : CString
  {
  CFormat (LPCTSTR lpszFormat, ...);
  CFormat (UINT nFormatID, ...);    
  CFormat (LPCTSTR lpszFormat, va_list argList);    
  CFormat (UINT nFormatID, va_list argList);    
  };

