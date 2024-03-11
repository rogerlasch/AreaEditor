/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#pragma once


class CFileRead : CObject
  {
  protected:

    CString m_strPartialLine;   // partial line read
    void fread_getnonblankline (const bool bLeftJustify = true);

    CArchive * m_ar;    // current archive during load
    CString m_strLastLineRead;

    long m_nLine;       // what line we are on
    bool m_bProgressBar;

  public:

    CFileRead () { m_ar = NULL; 
                   m_bProgressBar = false; 
                  };   // constructor
    ~CFileRead () { Wrapup (); };   // destructor

    void Init (const char * sMessage, 
               CArchive * ar);    // called at start of reading a file
    void Wrapup (void);           // called at end

    char fread_letter (void);
    CString fread_word (void);
    CString fread_string (const bool bLeftJustify = true);
    CString fread_line (void);
    long fread_number (const bool bFlag = false);
    long flag_convert (const char letter);    // for converting ROM flags
    CString fread_to_eol (void);
    EXT_BV fread_bitvector (const bool bFlag = false);

    long GetLineNumber (void) const { return m_nLine; }
    CString GetLastLineRead (void) const { return m_strLastLineRead; }
    BOOL LineEmpty (void) const { return m_strPartialLine.IsEmpty (); }
  };

class CFileWrite : CObject
  {
  protected:

    CArchive * m_ar;    // current archive during save
    long m_nLine;
    long m_iSaveMilestone;
    bool m_bProgressBar;

  public:

    CFileWrite () { m_ar = NULL; m_bProgressBar = false; };   // constructor
    ~CFileWrite () { Wrapup (); };   // destructor

    void Init (const char * sMessage, CArchive * ar, long iItems);    // called at start of writing a file
    void Wrapup (void);           // called at end

    void fwrite_string (const char * s);
    void fwrite_bitvector (const EXT_BV & bits);
    void DoSaveMilestone (void);
    long GetLineNumber (void) const { return m_nLine; }
  };
