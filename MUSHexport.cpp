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


// helper routine for turning descriptions into one long sequence

static CString FixUpDescription (const CString strOldText)
  {
CString strText = strOldText;
CString strNewText;
int iPos;

  while ((iPos = strText.Find (ENDLINE)) != -1)
    {
    strNewText = strText.Left (iPos);
    strNewText += ' ';
    strNewText += strText.Mid (iPos + strlen (ENDLINE));
    strText = strNewText;
    }   // end of finding an ENDLINE sequence

  // get rid of opening braces
  while ((iPos = strText.Find ('{')) != -1)
    strText.SetAt (iPos, '(');

  // get rid of closing braces
  while ((iPos = strText.Find ('}')) != -1)
    strText.SetAt (iPos, ')');

  strNewText = strText;

  // surround text in braces - this will "escape out" characters like a comma
  strText = '{';
  strText += strNewText;
  strText += '}';

  return strText;

  } // end of FixUpDescription


static char *	dir_mushname	[11]		=
{
    "North;n", "East;e", "South;s", "West;w", "Up;u", "Down;d",
    "Northeast;ne", "Northwest;nw", "Southeast;se", "Southwest;sw", ""
};

void CAreaEditorDoc::OnFileExportMush() 
{
	CFileDialog	dlg(FALSE,						// FALSE for FileSave
					"txt",						// default extension
					"mushcode.txt",
					OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_PATHMUSTEXIST,
					"Text files (*.txt)|*.txt||",
					NULL);
	dlg.m_ofn.lpstrTitle = "MUSHcode file";

	if (dlg.DoModal() != IDOK)
		return;

  POSITION RoomPos;
  POSITION ExitPos;
  int i;

  int iRoomCount = 0,
      iExitCount = 0,
      iMobCount = 0,
      iObjectCount = 0;


	try
	  {
		CFile	f (dlg.GetPathName(), CFile::modeCreate|CFile::modeWrite|CFile::shareExclusive);

    CArchive ar (&f, CArchive::store);

    // create a placeholder for vnum # to db # translations
    ar.WriteString ("think --------" ENDLINE);
    ar.WriteString ("think Creating vnum# to db# placeholder ..." ENDLINE);
    ar.WriteString ("think --------" ENDLINE);
    ar.WriteString ("@destroy DBHOLDER" ENDLINE); // delete old one
    ar.WriteString ("@destroy DBHOLDER" ENDLINE); // make it really go
    ar.WriteString ("@create DBHOLDER" ENDLINE);  // create new one

    CRoom * room;

/* **************************************************************************
   Create rooms
   ************************************************************************** */

    ar.WriteString ("think --------" ENDLINE);
    ar.WriteString (CFormat ("think Generating %i rooms and room descriptions ..." ENDLINE,
                    m_RoomList.GetCount ()));
    ar.WriteString ("think --------" ENDLINE);

    for (RoomPos = m_RoomList.GetHeadPosition (); RoomPos; )
      {
      room = m_RoomList.GetNext (RoomPos);

      // create the room (dig it)
      ar.WriteString (CFormat ("@set DBHOLDER=room%i:[dig(%s)]" ENDLINE,
                      room->vnum,
                      (LPCTSTR) FixUpDescription (room->name)
                      ));

      iRoomCount++;

      // if it has a description, set it
      if (!room->description.IsEmpty ())
        ar.WriteString (CFormat ("@describe xget(DBHOLDER, room%i)=%s" ENDLINE,
                        room->vnum,
                        (LPCTSTR) FixUpDescription (room->description)
                        ));

      } // end of each room

/* **************************************************************************
   Create exits to link the rooms
   ************************************************************************** */

    ar.WriteString ("think --------" ENDLINE);
    ar.WriteString ("think Creating exits and linking them to rooms ..." ENDLINE);
    ar.WriteString ("think --------" ENDLINE);

    for (RoomPos = m_RoomList.GetHeadPosition (); RoomPos; )
      {
      room = m_RoomList.GetNext (RoomPos);
      i = 1;
      for (ExitPos = room->exitlist.GetHeadPosition (); ExitPos; i++)
        {
        CExit * exit = room->exitlist.GetNext (ExitPos);

          CRoom * exitroom;
          CString strExitName;
          CString strExitDirection;
          CString strThisName;

          strExitDirection = dir_mushname [exit->vdir];
          if (strExitDirection.IsEmpty ())
              strExitDirection = exit->keyword;   // for "somewhere" exits

          if (exitroom = get_room_index (exit->vnum))
            {
            strExitName = exitroom->name;
            strThisName = room->name;

            // create the exit (open it)
            ar.WriteString (CFormat ("@set DBHOLDER=room%iexit%i:[open(%s, xget(DBHOLDER, room%i))]" 
                            ENDLINE,
                            room->vnum,
                            i,
                            (LPCTSTR) strExitDirection,
                            exit->vnum
                            ));

            iExitCount++;
            // the exit's description will be the name of the room it leads to
            ar.WriteString (CFormat ("@describe xget(DBHOLDER, room%iexit%i)=%s" ENDLINE,
                            room->vnum,
                            i,
                            (LPCTSTR) FixUpDescription (strExitName)
                            ));

            // teleport the exit to its appropriate room
            ar.WriteString (CFormat ("@teleport xget(DBHOLDER, room%iexit%i)=xget(DBHOLDER, room%i)" ENDLINE,
                            room->vnum,
                            i,
                            room->vnum
                            ));

        /* **************************************************************************
           Do @succ, @osucc, and @odrop messages
           ************************************************************************** */

            // make first char of direction lower case
            if (!strExitDirection.IsEmpty ())
              {
      	      strExitDirection.SetAt (0, LOWER(strExitDirection[0]));

              // truncate direction to remove anything after the semicolon
              int iSemicolon;
              if ((iSemicolon = strExitDirection.Find (';')) != -1)
                strExitDirection = strExitDirection.Left (iSemicolon);
              }


            // ditto for destination room
            if (!strExitName.IsEmpty ())
      	      strExitName.SetAt (0, LOWER(strExitName[0]));

            // and this room
            if (!strThisName.IsEmpty ())
      	      strThisName.SetAt (0, LOWER(strThisName[0]));

            // do the @succ message
            ar.WriteString (CFormat ("@succ xget(DBHOLDER, room%iexit%i)=%s" ENDLINE,
                            room->vnum,
                            i,
                            (LPCTSTR) FixUpDescription
                                      (CFormat ("You go %s to %s.",
                                               (LPCTSTR) strExitDirection,
                                               (LPCTSTR) strExitName))
                            ));

            // do the @osucc message
            ar.WriteString (CFormat ("@osucc xget(DBHOLDER, room%iexit%i)=%s" ENDLINE,
                            room->vnum,
                            i,
                            (LPCTSTR) FixUpDescription
                                      (CFormat ("goes %s to %s.",
                                               (LPCTSTR) strExitDirection,
                                               (LPCTSTR) strExitName))
                            ));

            // do the @odrop message
            ar.WriteString (CFormat ("@odrop xget(DBHOLDER, room%iexit%i)=%s" ENDLINE,
                            room->vnum,
                            i,
                            (LPCTSTR) FixUpDescription
                                      (CFormat ("enters from %s.",
                                               (LPCTSTR) strThisName))
                            ));


            } // end of exited-to room being in this area
        }   // end of processing each exit
      } // end of each room


/* **************************************************************************
   Add mobs and objects to rooms
   ************************************************************************** */

    ar.WriteString ("think --------" ENDLINE);
    ar.WriteString ("think Loading mobs and objects ..." ENDLINE);
    ar.WriteString ("think --------" ENDLINE);

    CMobile * mob;
    CMUDObject * object;

    i = 1;

    for (POSITION resetPos = m_ResetList.GetHeadPosition (); resetPos; i++)
      {
      CReset * reset = m_ResetList.GetNext (resetPos);

      switch (reset->command)
        {
        case 'M': // load mobile

          if ((room = get_room_index (reset->arg3)) == NULL)
            break;    // room not found

          if ((mob = get_mob_index( reset->arg1)) == NULL)
            break;    // mob not found

          ar.WriteString (CFormat ("@set DBHOLDER=reset%i:[create(%s, 10)]" ENDLINE,
                          i,
                          (LPCTSTR) FixUpDescription (mob->long_descr)
                          ));

          iMobCount++;

          // if it has a description, set it
          if (!mob->description.IsEmpty ())
            ar.WriteString (CFormat ("@describe xget(DBHOLDER, reset%i)=%s" ENDLINE,
                            i,
                            (LPCTSTR) FixUpDescription (mob->description)
                            ));

          // lock it to itself
          ar.WriteString (CFormat ("@lock xget(DBHOLDER, reset%i)=xget(DBHOLDER, reset%i)" ENDLINE,
                          i,
                          i
                          ));
          
          // teleport the mob to its appropriate room
          ar.WriteString (CFormat ("@teleport xget(DBHOLDER, reset%i)=xget(DBHOLDER, room%i)" ENDLINE,
                          i,
                          room->vnum
                          ));

          break;

        case 'O': // load object
          if ((room = get_room_index (reset->arg3)) == NULL)
            break;    // room not found

          if ((object = get_obj_index( reset->arg1)) == NULL)
            break;    // object not found

          ar.WriteString (CFormat ("@set DBHOLDER=reset%i:[create(%s, 10)]" ENDLINE,
                          i,
                          (LPCTSTR) FixUpDescription (object->description)
                          ));

          iObjectCount++;

          // if no extra description, just make the description the description
          if (object->extralist.IsEmpty ())
            ar.WriteString (CFormat ("@describe xget(DBHOLDER, reset%i)=%s" ENDLINE,
                            i,
                            (LPCTSTR) FixUpDescription (object->description)
                            ));
          else
          // we will assume that the first extra description is the object's description
            ar.WriteString (CFormat ("@describe xget(DBHOLDER, reset%i)=%s" ENDLINE,
                            i,
                            (LPCTSTR) FixUpDescription (object->extralist.GetHead ()->description)
                            ));

          // lock it to itself
          ar.WriteString (CFormat ("@lock xget(DBHOLDER, reset%i)=xget(DBHOLDER, reset%i)" ENDLINE,
                          i,
                          i
                          ));
          
          // teleport the object to its appropriate room
          ar.WriteString (CFormat ("@teleport xget(DBHOLDER, reset%i)=xget(DBHOLDER, room%i)" ENDLINE,
                          i,
                          room->vnum
                          ));
          break;


        } // end of switch

      }   // end of processing each reset

/* **************************************************************************
   All done
   ************************************************************************** */

    ar.WriteString ("think --------" ENDLINE);
    ar.WriteString ("think Done." ENDLINE);
    ar.WriteString ("think --------" ENDLINE);

    ar.Close ();

    }
	catch (CException* e)
	{
		e->ReportError();
		e->Delete();
    return;
	}
	
  ::AfxMessageBox (CFormat ("Exported %i room%s, %i exit%s, %i mobile%s, %i object%s." 
                            ENDLINE 
                            ENDLINE
                            "Please read file MUSHEXPORT.TXT before attempting to use this file.",
                            PLURAL (iRoomCount),
                            PLURAL (iExitCount),
                            PLURAL (iMobCount),
                            PLURAL (iObjectCount)),
                    MB_ICONINFORMATION);

}

void CAreaEditorDoc::OnUpdateFileExportMush(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (!m_RoomList.IsEmpty ());
	
}
