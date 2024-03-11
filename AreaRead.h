/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#pragma once


class CAreaRead : CObject
  {
  protected:

    CString m_strPartialLine;   // partial line read

    void fread_getnonblankline (bool bLeftJustify = true);
    CArchive * m_ar;    // current archive during load
    // for showing error messages, record line number and last line read

    CString m_strLastLineRead;
    long m_nLine;

  public:

    CAreaRead () { m_ar = NULL;};   // constructor

    void Init (CArchive * ar);    // called at start of reading a file
    void Wrapup (void);           // called at end

    char fread_letter (void);
    CString fread_word (void);
    CString fread_string (bool bLeftJustify = true);
    CString fread_line (void);
    long fread_number (void);
    void fread_to_eol (void);

    long GetLineNumber (void) const { return m_nLine; }
    CString GetLastLineRead (void) const { return m_strLastLineRead; }
  };

class CAreaWrite : CObject
  {
  protected:

    CArchive * m_ar;    // current archive during save
    long m_nLine;
    long m_iSaveMilestone;

  public:

    CAreaWrite () { m_ar = NULL;};   // constructor

    void Init (CArchive * ar, long iItems);    // called at start of writing a file
    void Wrapup (void);           // called at end

    void fwrite_string (const char * s);
    void DoSaveMilestone (void);
    long GetLineNumber (void) const { return m_nLine; }
  };
