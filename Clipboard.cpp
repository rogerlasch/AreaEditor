/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/


#include "stdafx.h"

/* +++++++++++++++++++++++++++++++++++++++++++++++++++ */
/*                                                     */
/*       putontoclipboard                              */
/*                                                     */
/* +++++++++++++++++++++++++++++++++++++++++++++++++++ */


// puts "data" onto the clipboard

BOOL putontoclipboard (const CString & data)
  {

// Open clipboard

  if (!::OpenClipboard(NULL) )
       {
       ::AfxMessageBox( "Cannot open the Clipboard" );
       return TRUE;
       }

// Empty the clipboard, which also gives ownership to us

    ::EmptyClipboard ();

// Allocate memory for the clipboard


   HGLOBAL hData = GlobalAlloc (GMEM_MOVEABLE | GMEM_DDESHARE, strlen (data) + 1);

   if (!hData)
      {
      ::AfxMessageBox( "Unable to allocate memory for Clipboard data" );
      ::CloseClipboard();
      return TRUE;
      }

// Lock the handle in order to get a pointer to real memory

   char * p = (char *) GlobalLock (hData);

   if (!p)
      {
      ::AfxMessageBox( "Unable to lock memory for Clipboard data" );
      ::CloseClipboard();
      return TRUE;
      }

// Copy the field into the allocated memory

   strncpy (p, data, strlen (data) + 1);

   GlobalUnlock (hData);

// Set the clipboard data

   if ( ::SetClipboardData( CF_TEXT, hData ) == NULL )
   {
      ::AfxMessageBox( "Unable to set Clipboard data" );
      ::CloseClipboard();
      return TRUE;
   }

// Close the clipboard

  ::CloseClipboard();

  return FALSE;

  } // end of putontoclipboard 
