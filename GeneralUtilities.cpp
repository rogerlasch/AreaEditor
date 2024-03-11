/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/


#include "stdafx.h"

#include "AreaEditor.h"
#include "defaults.h"


#define SPACES " \t\r\n"

class CMUDitem;


inline string trim_right (const string & s, const string & t = SPACES)
  { 
  string d (s); 
  string::size_type i (d.find_last_not_of (t));
  if (i == string::npos)
    return "";
  else
   return d.erase (d.find_last_not_of (t) + 1) ; 
  }  // end of trim_right

inline string trim_left (const string & s, const string & t = SPACES) 
  { 
  string d (s); 
  return d.erase (0, s.find_first_not_of (t)) ; 
  }  // end of trim_left

inline string trim (const string & s, const string & t = SPACES)
  { 
  string d (s); 
  return trim_left (trim_right (d, t), t) ; 
  }  // end of trim

// string find-and-replace
inline string FindAndReplace
  (const string& source, const string target, const string replacement)
  {
  string str = source;
  string::size_type pos = 0,   // where we are now
                    found;     // where the found data is
  while ((found = str.find (target, pos)) != string::npos)
    {
    str.replace (found, target.size (), replacement);
    pos = found + replacement.size ();
    }
  return str;
  };   // end of FindAndReplace

string GetWord (string & s, 
                const string delim = " ",
                const bool trim_spaces = true);

void StringToVector (const string s, 
                     vector<string> & v,
                     const string delim = " ", 
                     const bool trim_spaces = true);

string VectorToString (const vector<string> & v, 
                       const string delim = " ");


bool FixWrap (CEdit & ctlEdit, const bool bEndline)
  {
  CString strOldText, strNewText;
  vector<string> v;
  string s;

  // don't start putting in trailing ENDLINEs if no text in the window to start with
  if (ctlEdit.GetWindowTextLength () == 0)
    return false;

  ctlEdit.GetWindowText (strOldText);

  StringToVector ((LPCTSTR) strOldText, v, ENDLINE);

  // we need to fix up the text with linefeeds at the end of each line

  for (int i = 0; i < ctlEdit.GetLineCount (); i++)
    {
    int iStart = ctlEdit.LineIndex (i),
        iEnd = ctlEdit.LineIndex (i + 1);
    
    if (iEnd == -1) // past end, take end of string
      iEnd = strOldText.GetLength ();

    CString strLine = strOldText.Mid (iStart, iEnd - iStart);
    strLine.Replace (ENDLINE, "");

    if (strLine.GetLength () > MAXDESCRIPTIONWIDTH)
      {
      ::AfxMessageBox (CFormat ("The contents of line %i exceeds the maximum permitted line width.\n"
                       "Please use the \"Edit\" button to edit the text.", i + 1),
                      MB_ICONEXCLAMATION);
      return true;
      }

    if (!strNewText.IsEmpty ())   // add a newline to all lines except the first
      strNewText += ENDLINE;

    strNewText += strLine;
    }

   if (bEndline)
     {
     // make sure it has a trailing ENDLINE
     if (strNewText.Right (strlen (ENDLINE)) != ENDLINE)
        strNewText += ENDLINE;
     }
   else
     {
     // make sure it has does NOT have a trailing ENDLINE
     if (strNewText.Right (strlen (ENDLINE)) == ENDLINE)
       strNewText = strNewText.Left (strNewText.GetLength () - 2);
     }

    // put new data back into control with endlines in place
    ctlEdit.SetWindowText (strNewText);
//    ::AfxMessageBox (strNewText);   //NJG
    return false;   // no errors

  }

// this is called to ensure we don't have tilde's in descriptions and names
void CheckForTilde (CDataExchange* pDX, int nIDC, CString& value)
  {
    if (value.Find ('~') != -1)
      {
      DDX_Text(pDX, nIDC, value);
      ::AfxMessageBox ("This field is not permitted to have a tilde (~) character in it", 
                       MB_ICONEXCLAMATION);
      pDX->Fail();
      }

  } // end of CheckForTilde


// Helper routine for setting the font in certain description windows to a
// fixed-pitch courier, to make editing easier.

void FixFont (ptrCFont & pFont, CEdit & editctrl)
  {

   delete pFont;         // get rid of old font

   pFont = new CFont;    // create new font

   if (pFont)
    {

    int iSize = App.GetProfileInt (sProfilePreferences, sProfileScreenFontSize, 9);
    CString strName = App.GetProfileString (sProfilePreferences, sProfileScreenFontName, "FixedSys");
    
    CDC dc;

    dc.CreateCompatibleDC (NULL);

     int lfHeight = -MulDiv(iSize, 
                    dc.GetDeviceCaps(LOGPIXELSY), 72);

     pFont->CreateFont(lfHeight, // int nHeight, 
				    0, // int nWidth, 
				    0, // int nEscapement, 
				    0, // int nOrientation, 
				    FW_NORMAL, // int nWeight, 
				    0, // BYTE bItalic, 
				    0, // BYTE bUnderline, 
            0, // BYTE cStrikeOut, 
            0, // BYTE nCharSet, 
            0, // BYTE nOutPrecision, 
            0, // BYTE nClipPrecision, 
            0, // BYTE nQuality, 
            FIXED_PITCH, // BYTE nPitchAndFamily,  
            strName);// LPCTSTR lpszFacename );

      // Get the metrics of the font.

      dc.SelectObject(pFont);

      if (pFont)
        editctrl.SendMessage (WM_SETFONT,
                                   (WPARAM) pFont->m_hObject,
                                   MAKELPARAM (TRUE, 0));
     }  // end of having a font to select


  }   // end of FixFont


// we load up quite a few combo boxes from pointer arrays
// centralise it all here

void LoadComboBox (CComboBox & ctlComboBox, 
                   const tpNames pNames, 
                   const int iMaxItems,
                   const int iSelected)
  {
  int i,
      sel;

  // empty combo box

  ctlComboBox.ResetContent ();

  // load combo box from pointer array

  for (i = 0; i < iMaxItems; i++)
    {
    int nItem = ctlComboBox.AddString (pNames [i]);
    if (nItem != CB_ERR && nItem != CB_ERRSPACE)
      ctlComboBox.SetItemData (nItem, i); // for recalling later
    }

  // if selected (ie. current) item is in range, select it

  if (iSelected >= 0 && iSelected < iMaxItems)
    {
    sel = ctlComboBox.FindStringExact(-1, pNames [iSelected]);
    if (sel != CB_ERR)
      ctlComboBox.SetCurSel(sel);
    }
  else
    ctlComboBox.SetCurSel(-1);


  }   // end of LoadComboBox

// and here if the source is a list

void LoadComboBoxList (CComboBox & ctlComboBox, 
                       const CConfigList & WhichList, 
                       const int iSelected)
  {

  tList selectedItem;
  bool  bFoundIt = false;

  // empty combo box

  ctlComboBox.ResetContent ();

    // load combo box from list

  for (POSITION pos = WhichList.list.GetHeadPosition (); pos; )
    {
    tList listItem = WhichList.list.GetNext (pos);

    int nItem = ctlComboBox.AddString (listItem.strName);
    if (nItem != CB_ERR && nItem != CB_ERRSPACE)
      {
      ctlComboBox.SetItemData (nItem, listItem.iValue); // for recalling later
      if (listItem.iValue == iSelected)
        {
        bFoundIt = true;
        selectedItem = listItem;
        }
      }
    } // end of loop

  // if selected (ie. current) item is in range, select it
  // we do it here in case the list is sorted

  if (bFoundIt)
    {
    int sel = ctlComboBox.FindStringExact(-1, selectedItem.strName);
    if (sel != CB_ERR)
      ctlComboBox.SetCurSel(sel);
    }
  else
    ctlComboBox.SetCurSel(-1);

  }   // end of LoadComboBoxList

// find which item in combo box, if any, was selected (returns true if found)

bool UnloadComboBox (CComboBox & ctlComboBox, 
                     int & iSelected)
  {
  int sel = ctlComboBox.GetCurSel ();
  if (sel == CB_ERR)
    return false;   // nothing selected

  iSelected = ctlComboBox.GetItemData (sel);
  return true;

  }   // end of LoadComboBox

void FixupVnum (int& iVnum,
                const int * const pOldVnum, 
                const int * const pNewVnum, 
                const int iMax)
 {

  // search array for match, if found return corresponding new vnum
  for (int i = 0; i < iMax; i++)
    if (iVnum == pOldVnum [i])
      {
      iVnum = pNewVnum [i];
      return;
      }

  // no match, vnum stays the same
  return;
  }   // end of FixupVnum

// for lookup up a char * table to find a match on a given name

int TableLookup (const char * pWhichName,
                 const tpNames pNames, 
                 const int iMaxItems)
  {
int i;

  for (i = 0; i < iMaxItems; i++)
    if (!str_prefix (pWhichName, pNames [i]))
      return i;

  return -1;
  } // end of TableLookup

// for converting a ROM flag into an string (eg. ACGT)

CString ConvertROMFlag (const EXT_BV iFlag)
  {
long iBit = 1;
char c = 'A';
int i;
CString strResult;

  if (iFlag == 0)
    return "0";

  // do upper-case letters
  for (i = 0; i < 26; i++)
    {
    if (iBit & iFlag)
      strResult += c;
    c++;
    iBit <<= 1;
    }

  c = 'a';

    // do lower-case letters
  for (i = 0; i < 6; i++)
    {
    if (iBit & iFlag)
      strResult += c;
    c++;
    iBit <<= 1;
    }

  return strResult;

  } // end of ConvertFlag


// quotes a string for writing to the database, if necessary

CString Quote (const CString & strName)
  {
  // if it isn't empty and doesn't contains spaces, it is OK as is
  if (strName.Find (' ') == -1 && !strName.IsEmpty ())
    return strName;

  CString strNew = '\'';
  strNew += strName;
  strNew += '\'';

  return strNew;

  }; // end of Quote


// split a line into the first word, and rest-of-the-line
string GetWord (string & s, 
                const string delim,
                const bool trim_spaces)
  {
    
  // find delimiter  
  string::size_type i (s.find (delim));

  // split into before and after delimiter
  string w (s.substr (0, i));

  // if no delimiter, remainder is empty
  if (i == string::npos)
    s.erase ();
  else
    // erase up to the delimiter
    s.erase (0, i + delim.size ());

  // trim spaces if required
  if (trim_spaces)
    {
    w = trim (w);
    s = trim (s);
    }

  // return first word in line
  return w;
  
  } // end of GetWord	

// To be symmetric, we assume an empty string (after trimming spaces)
// will give an empty vector.
// However, a non-empty string (with no delimiter) will give one item
// After that, you get an item per delimiter, plus 1.
// eg.  ""      => empty
//      "a"     => 1 item
//      "a,b"   => 2 items
//      "a,b,"  => 3 items (last one empty)

void StringToVector (const string s, 
                     vector<string> & v,
                     const string delim, 
                     const bool trim_spaces)
  {

  // start with initial string, trimmed of leading/trailing spaces if required
  string s1 (trim_spaces ? trim (s) : s);

  v.clear (); // ensure vector empty

  // no string? no elements
  if (s1.empty ())
    return;

  // add to vector while we have a delimiter
  while (!s1.empty () && s1.find (delim) != string::npos)
    v.push_back (GetWord (s1, delim, trim_spaces));

  // add final element
  v.push_back (s1);
  } // end of StringToVector 

// Takes a vector of strings and converts it to a string 
// like "apples,peaches,pears" 
// Should be symmetric with StringToVector (excepting any spaces that might have
//  been trimmed).

string VectorToString (const vector<string> & v, 
                       const string delim)
  {
  // vector empty gives empty string
  if (v.empty ())
    return "";

  // for copying results into
  ostringstream os;

  // copy all but last one, with delimiter after each one
  copy (v.begin (), v.end () - 1, 
        ostream_iterator<string> (os, delim.c_str ()));

  // return string with final element appended
  return os.str () + *(v.end () - 1);

  } // end of VectorToString
