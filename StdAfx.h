/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__30BE0359_E9F1_11D1_A20A_0000B4595568__INCLUDED_)
#define AFX_STDAFX_H__30BE0359_E9F1_11D1_A20A_0000B4595568__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxcview.h>
//#include <afxdisp.h>        // MFC OLE automation classes
#include <afxpriv.h>
#include <afxtempl.h>     // for templates

#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#ifdef SPELL_CHECKER
#include "sscemfc.hpp"  // spell check stuff
#endif // SPELL_CHECKER
             
#ifdef WIN32
// disable warnings about long STL-generated names
  #pragma warning( disable : 4786 4800)
#endif

#include <string>
#include <vector>
#include <deque>      
#include <algorithm>  
#include <functional>
#include <iostream>
#include <iterator>
#include <sstream>

using namespace std ;

#include "format.h"
#include "exceptions.h"
#include "constants.h"

// ============================================================================

#if 0

#ifndef INTBITS
  #define INTBITS	32
#endif
#define XBM		31	/* extended bitmask   ( INTBITS - 1 )	*/
#define RSV		5	/* right-shift value  ( sqrt(XBM+1) )	*/
#define XBI		4	/* integers in an extended bitvector	*/
#define MAX_BITS	XBI * INTBITS
/*
 * Structure for extended bitvectors 
 */
struct extended_bitvector
  {
  long		bits[XBI];
  };

typedef struct	extended_bitvector	EXT_BV;

#endif

// My temporary form of extended bitvector - NJG

typedef	__int64	EXT_BV;
#define MAX_BITS	64

#include "FileReadWrite.h"

extern "C"
  {
#include "TipDlg.h"
  }

// function prototypes for minimum string validation in dialog boxes

void AFXAPI DDV_MinMaxString(CDataExchange* pDX, CString& value, int nMinChars, int nMaxChars);
void AFXAPI DDX_MinMaxString(CDataExchange* pDX, int nIDC, CString& value);
void AFXAPI DDV_MinMaxCBString(CDataExchange* pDX, CString& value, int nMinChars, int nMaxChars);
void AFXAPI DDX_MinMaxCBString(CDataExchange* pDX, int nIDC, CString& value);

// clipboard helper function

BOOL putontoclipboard (const CString & data);
BOOL GetClipboardContents (CString & strClipboard);

// The define below gets the current app and casts it to the correct type

#define App (*((CAreaEditorApp*)AfxGetApp()))

// The define below gets the current frame and casts it to the correct type

#define Frame (*((CMainFrame*)App.m_pMainWnd))

// The define below is for easily outputting status message to the status line

#define SetStatusMsg(arg) Frame.SetStatusMessage (arg)


typedef CFont * ptrCFont;     // for changing fonts in edit windows
typedef char * tpNames [];    // for arrays of pointers

// configuration flags structure
typedef struct
  {
  CString strName [MAX_BITS];   // flag name
  CString strDescription [MAX_BITS];  // description of flag
  } tFlags;

// configuration list structure
class tList
  {
  public:
  tList () { iValue = 0; };   // default constructor
  tList (const char * sName, const int iNewValue)
    { strName = sName; iValue = iNewValue; };   // end of constructor
  CString strName;   // flag name
  int     iValue;  // corresponding value
  };

class CConfigList
  {
  public:
  CList <tList, tList&> list;
  bool FindName (const int iValue, 
                 CString & strName,
                 const bool bDefaultToFirst = true) const;     // true if found
  bool IsValueInList (const int iValue) const;     // true if found

  bool FindValue (const CString strName, 
                  int & iValue,
                  const bool bPartialMatch = false) const;  // true if found
  bool IsNameInList (const CString strName,
                     const bool bPartialMatch = false) const;

  CString ReturnName (const EXT_BV iValue,
                      const bool bDefaultToFirst = true) const;    // returns name
  int ReturnValue (const CString strName,
                   const bool bPartialMatch = false) const;  // returns value or 0 if not found
  };

/*
 * Utility macros.
 */
#define UMIN(a, b)		((a) < (b) ? (a) : (b))
#define UMAX(a, b)		((a) > (b) ? (a) : (b))
#define URANGE(a, b, c)		((b) < (a) ? (a) : ((b) > (c) ? (c) : (b)))
#define LOWER(c)		((c) >= 'A' && (c) <= 'Z' ? (c)+'a'-'A' : (c))
#define UPPER(c)		((c) >= 'a' && (c) <= 'z' ? (c)+'A'-'a' : (c))
#define NUMITEMS(arg) (sizeof (arg) / sizeof (arg [0]))
// helper define for appending an "s" to plural amounts
#define PLURAL(arg) (arg), (arg) == 1 ? "" : "s"

#define ENDLINE "\r\n"

#define MAXDESCRIPTIONWIDTH 79

/*
 * Old-style Bit manipulation macros
 *
 * The bit passed is the actual value of the bit (Use the BV## defines)
 */ 

#define IS_SET(flag, bit)	(((flag) & (bit)) != 0)
#define SET_BIT(var, bit)	((var) |= (bit))
#define REMOVE_BIT(var, bit)	((var) &= ~(bit))
#define TOGGLE_BIT(var, bit)	((var) ^= (bit))

// Nick's bit manipulations routines, that require bit numbers, not masks
#define CHECK_BIT_NUMBER(flag, bit) (((flag) & (1 << bit)) != 0)
#define SET_BIT_NUMBER(flag, bit) ((flag) |= (1 << bit))
#define CLEAR_BIT_NUMBER(flag, bit) ((flag) &= ~(1 << bit))
#define TOGGLE_BIT_NUMBER(flag, bit) ((flag) ^= (1 << bit))

#if 0
/*
 * Macros for accessing virtually unlimited bitvectors.		-Thoric
 *
 * Note that these macros use the bit number rather than the bit value
 * itself -- which means that you can only access _one_ bit at a time
 *
 * This code uses an array of integers
 */

/*
 * The functions for these prototypes can be found in misc.c
 * They are up here because they are used by the macros below
 */
bool	ext_is_empty		( EXT_BV *bits );
void	ext_clear_bits	( EXT_BV *bits );
int	ext_has_bits		  ( EXT_BV *var, EXT_BV *bits);
bool	ext_same_bits		( EXT_BV *var, EXT_BV *bits);
void	ext_set_bits		( EXT_BV *var, EXT_BV *bits);
void	ext_remove_bits	( EXT_BV *var, EXT_BV *bits);
void	ext_toggle_bits ( EXT_BV *var, EXT_BV *bits);

/*
 * Here are the extended bitvector macros:
 */
#define xIS_SET(var, bit)	    ((var).bits[(bit) >> RSV] & 1 << ((bit) & XBM))
#define xSET_BIT(var, bit)	  ((var).bits[(bit) >> RSV] |= 1 << ((bit) & XBM))
#define xSET_BITS(var, bit)	  (ext_set_bits(&(var), &(bit)))
#define xREMOVE_BIT(var, bit)	((var).bits[(bit) >> RSV] &= ~(1 << ((bit) & XBM)))
#define xREMOVE_BITS(var, bit)(ext_remove_bits(&(var), &(bit)))
#define xTOGGLE_BIT(var, bit)	((var).bits[(bit) >> RSV] ^= 1 << ((bit) & XBM))
#define xTOGGLE_BITS(var, bit)(ext_toggle_bits(&(var), &(bit)))
#define xCLEAR_BITS(var)	    (ext_clear_bits(&(var)))
#define xIS_EMPTY(var)		    (ext_is_empty(&(var)))
#define xHAS_BITS(var, bit)	  (ext_has_bits(&(var), &(bit)))
#define xSAME_BITS(var, bit)	(ext_same_bits(&(var), &(bit)))

#endif

// macro to help with searches

#define SEARCH(arg)   \
    strFound = arg;  \
    if (!bMatchCase)  \
      strFound.MakeUpper ();  \
    if (strFound.Find (strWanted) != -1)  \
      return TRUE;

void FixFont (ptrCFont & pFont, CEdit & editctrl);

void LoadComboBox (CComboBox & ctlComboBox, 
                   const tpNames pNames, 
                   const int iMaxItems,
                   const int iSelected);

void LoadComboBoxList (CComboBox & ctlComboBox, 
                       const CConfigList & WhichList, 
                       const int iSelected);

bool UnloadComboBox (CComboBox & ctlComboBox, 
                    int & iSelected);

CString flag_string( int bitvector, char * const flagarray[] );

CString convert_actflag (const EXT_BV flag);
CString convert_areaflag (const EXT_BV flag);
CString convert_affectflag (const EXT_BV flag);
CString convert_partflag (const EXT_BV flag);
CString convert_attackflag (const EXT_BV flag);
CString convert_defenseflag (const EXT_BV flag);
CString convert_formflag (const EXT_BV flag);
CString convert_risflag (const EXT_BV flag);
CString convert_languages (const EXT_BV flag);
CString convert_object_flags (const EXT_BV flag);
CString convert_wear_flags (const EXT_BV flag);
CString convert_room_flags (const EXT_BV flag);
CString convert_spell_flags (const EXT_BV flag);
CString convert_exit_flags (const EXT_BV flag);
CString FlagToString (const EXT_BV bitvector, const tFlags & flagarray );

int slot_lookup( int slot );
bool str_prefix (const char *astr, const char *bstr);

int number_fuzzy (int number);
int number_bits (int width);
int number_range (int from, int to);
int number_percent (void);
int number_door (void);
void init_mm (void);
int number_mm (void);
int dice (int number, int size);
int interpolate (int level, int value_00, int value_32);
CString print_bitvector (const EXT_BV & bits);

bool FixWrap (CEdit & ctlEdit, const bool bEndline = true);
void CheckForTilde (CDataExchange* pDX, int nIDC, CString& value);
void FixupVnum (int& iVnum,
                const int * const pOldVnum, 
                const int * const pNewVnum, 
                const int iMax);

int TableLookup (const char * pWhichName,
                 const tpNames pNames, 
                 const int iMaxItems);

CString ConvertROMFlag (const EXT_BV iFlag);
CString Quote (const CString & strName);

void ReadNames (void);
CString GenerateName (void);

// Spell check bits (use with CHECK_BIT_NUMBER macro)
// (stored in App.m_SpellCheckOptions)

enum {
  SK_ENABLE,      // enable spell check
  SK_CHECK_EDIT_WINDOW,   // check when they close edit window
  SK_AREA_CHECK,   // check when they do an area check
  SK_CHECK_ON_VIEW,   // check when they view an item (eg. go from one mob to next)
  SK_ACCEPT_NAME,  // the "name" is considered valid spelling (eg. naga)
  SK_HELP_TEXT,   // check help section text
  SK_MOB_NAME,    // check mob name
  SK_MOB_SHORT,   // check mob short description
  SK_MOB_LONG,    // check mob long description
  SK_MOB_DESC,    // check mob description
  SK_OBJECT_NAME,    // check object name
  SK_OBJECT_SHORT,   // check object short description
  SK_OBJECT_LONG,    // check object long description
  SK_EXTRA_DESC,    // check object and room extra description
  SK_OBJECT_ACTIONDESC,    // check object action description
  SK_ROOM_NAME,    // check room name
  SK_ROOM_DESC,    // check room description
  SK_EXIT_DESC,    // check exit description

  };


// Forward function prototype for delay loading exception filter
LONG WINAPI DelayLoadDllExceptionFilter(PEXCEPTION_POINTERS pep);

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__30BE0359_E9F1_11D1_A20A_0000B4595568__INCLUDED_)
