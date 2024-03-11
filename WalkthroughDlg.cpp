/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

// WalkthroughDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AreaEditor.h"
#include "AreaEditorDoc.h"
#include "defaults.h"

#include "WalkthroughDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// save here so we return same settings next time

static BOOL bShowEquipment = FALSE;
static BOOL bShowVnums = FALSE;

/////////////////////////////////////////////////////////////////////////////
// CWalkthroughDlg dialog


CWalkthroughDlg::CWalkthroughDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWalkthroughDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWalkthroughDlg)
	m_bShowEquipment = FALSE;
	m_bShowVnums = FALSE;
	//}}AFX_DATA_INIT

  m_pDoc = NULL;
  m_room = NULL;
  m_font = NULL;

}

CWalkthroughDlg::~CWalkthroughDlg ()
  {
  delete m_font;
  }

void CWalkthroughDlg::DoDataExchange(CDataExchange* pDX)
{

  if (!pDX->m_bSaveAndValidate)
    {
    m_bShowEquipment = bShowEquipment;
    m_bShowVnums = bShowVnums;
    }

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWalkthroughDlg)
	DDX_Control(pDX, IDC_SHOW_EQUIPMENT, m_ctlShowEquipment);
	DDX_Control(pDX, IDC_SHOW_VNUMS, m_ctlShowVnums);
	DDX_Control(pDX, IDC_OUTPUT, m_ctlOutput);
	DDX_Control(pDX, IDC_COMMAND, m_ctlCommand);
	DDX_Check(pDX, IDC_SHOW_EQUIPMENT, m_bShowEquipment);
	DDX_Check(pDX, IDC_SHOW_VNUMS, m_bShowVnums);
	//}}AFX_DATA_MAP

  if (!pDX->m_bSaveAndValidate)
    {
    FixFont (m_font, m_ctlOutput);

    CDC dc;

    RECT rect;

    dc.CreateCompatibleDC (NULL);
    dc.SelectObject(m_font);
  
    TEXTMETRIC tm;
    dc.GetTextMetrics(&tm);

    int m_FontHeight = tm.tmHeight; 
    int m_FontWidth = tm.tmAveCharWidth; 

    int iDialogWidth = m_FontWidth * (MAXDESCRIPTIONWIDTH - 1) +
                      (GetSystemMetrics (SM_CXFRAME) * 2) +  // allow for border
                      GetSystemMetrics (SM_CXVSCROLL) +  // allow for vertical scroll bar
                      4;      // allow for Windows 95 frame

    // size output window to correct width
    m_ctlOutput.GetWindowRect (&rect);
    m_ctlOutput.SetWindowPos (NULL, 0, 0, iDialogWidth, rect.bottom - rect.top, 
                SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_NOACTIVATE);

    // make command window same width
//    m_ctlCommand.GetWindowRect (&rect);
//    m_ctlCommand.SetWindowPos (NULL, 0, 0, iDialogWidth, rect.bottom - rect.top, 
//                SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_NOACTIVATE);

    // now do the dialog itself

    // this calculation here is a complete wank - there is no reason for it to work
    iDialogWidth += GetSystemMetrics (SM_CXFRAME) + GetSystemMetrics (SM_CXVSCROLL);
    
    GetWindowRect (&rect);
    SetWindowPos (NULL, 0, 0, iDialogWidth, rect.bottom - rect.top, 
                  SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_NOACTIVATE);

    if (!m_room)
      m_room = m_pDoc->m_RoomList.GetHead ();
    RedrawRoom ();
    }

}


BEGIN_MESSAGE_MAP(CWalkthroughDlg, CDialog)
	//{{AFX_MSG_MAP(CWalkthroughDlg)
	ON_BN_CLICKED(IDC_SHOW_VNUMS, OnShowVnums)
	ON_BN_CLICKED(IDC_SHOW_EQUIPMENT, OnShowEquipment)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWalkthroughDlg message handlers

#define BUFFER_SIZE 50000

// ===============================================================================
static char * printline_buff = NULL;

static void WriteLine (CArchive & ar, 
                      int skip, 
                      const char * theline, ...)
  {
va_list arglist;

  if (!printline_buff)
    ThrowErrorException ("Not enough memory for printing buffer");

  // output the message as if it was a PRINTF type message
  va_start (arglist, theline);
  _vsnprintf (printline_buff, BUFFER_SIZE, theline, arglist);
  va_end (arglist);

  ar.WriteString (printline_buff);

  // now output the line feeds
  for (int i = 0; i < skip; i++)
    ar.WriteString (ENDLINE);

  } // end of WriteLine

void CWalkthroughDlg::RedrawRoom (void)
  {
  if (!m_room)
    return;

  // make title reflect which room we are in
  SetWindowText (m_room->Summary ());

POSITION pos;
POSITION resetPos;
CReset * reset;
CMobile * mob;
CMUDObject * object;

  bShowVnums = m_ctlShowVnums.GetCheck ();
  bShowEquipment = m_ctlShowEquipment.GetCheck ();

  CMemFile f;      // open memory file for writing
  CArchive ar (&f, CArchive::store);
  printline_buff = new char [BUFFER_SIZE];


  // display m_room
  if (bShowVnums)
    WriteLine (ar, 1, "%s", (LPCTSTR) m_room->Summary ());
  else
    WriteLine (ar, 1, "%s", (LPCTSTR) m_room->name);
  WriteLine (ar, 1, "%s", (LPCTSTR) m_room->description);

  // show all exits

  if (!m_room->exitlist.IsEmpty ())
    {
    WriteLine (ar, 1, "Exits: ");

    for (pos = m_room->exitlist.GetHeadPosition (); pos; )
      {
      CExit * exit = m_room->exitlist.GetNext (pos);

      if (bShowVnums)
        WriteLine (ar, 1, "%s %s", (LPCTSTR) exit->Summary (), 
                      (LPCTSTR) convert_exit_flags (exit->exit_info));
      else
        {
        CRoom * exitroom;
        CString strExitName;
        CString strExitDirection;

        strExitDirection = RoomDirectionList.ReturnName (exit->vdir, false);

        if (exitroom = FindRoom (exit->vnum))
          strExitName = exitroom->name;
        else
          strExitName = "not in area";

        WriteLine (ar, 1, "%-10s - %s",
                    (LPCTSTR) strExitDirection,
                    (LPCTSTR) strExitName);

        }
      }   // end of processing each exit

    WriteLine (ar, 1, "");    // wrap up line after exits
    } // end of having some exits

    // process each reset to show mobs and objects in the room

    bool bThisRoom = false;

    for (resetPos = m_pDoc->m_ResetList.GetHeadPosition (); resetPos; )
      {
      reset = m_pDoc->m_ResetList.GetNext (resetPos);

      switch (reset->command)
        {
        case 'M': // load mobile

          bThisRoom = reset->arg3 == m_room->vnum;

          if (!bThisRoom)
            break;    // wrong room - forget it

          if ((mob = FindMob ( reset->arg1)) == NULL)
            break;    // mob not found

          if (bShowVnums)
            WriteLine (ar, 1, "Mobile %s", (LPCTSTR) mob->Summary ());
          WriteLine (ar, 1, "%s", (LPCTSTR) mob->long_descr);
          
          break;

        case 'O': // load object
          if (reset->arg3 != m_room->vnum)
            break;    // wrong room - forget it

          if ((object = FindObj ( reset->arg1)) == NULL)
            break;    // object not found

          if (bShowVnums)
            WriteLine (ar, 1, "Object %s", (LPCTSTR) object->Summary ());
          WriteLine (ar, 1, "%s", (LPCTSTR) object->description);
          
          break;

          case 'G': // give object
          case 'E': // equip object
            if (!bThisRoom)   // not given to a mob in this room
              break;    // wrong room - forget it

            if ((object = FindObj ( reset->arg1)) == NULL)
              break;    // object not found

            if (bShowEquipment)
              if (bShowVnums)
                WriteLine (ar, 1, "%s", (LPCTSTR) reset->Summary ());
              else
                {
                CString str1;

                if (object = FindObj (reset->arg1))
                  str1 = object->short_descr;
                else
                  str1 = CFormat ("#%i (not in area)", reset->arg1);
      
                if (reset->command == 'E')
                  WriteLine (ar, 1, "-- Equip: %s", (LPCTSTR) str1);
                else
                  WriteLine (ar, 1, "-- Give:  %s", (LPCTSTR) str1);
                } // end of vnums not wanted

            break;


        } // end of switch

      }   // end of processing each reset

  WriteLine (ar, 1, "");


  // remove work buffer and close archive
  delete [] printline_buff;
  printline_buff = NULL;
  ar.Write ("", 1);   // write trailing null
  ar.Close ();

  // set window text to CFile contents
  int nLength = f.GetLength ();
  char * p = (char *) f.Detach ();
  CString strOutput (p, nLength);
  m_ctlOutput.SetWindowText (p);
  free (p);   // remove memory allocated in CMemFile

  m_ctlCommand.SetSel (0, -1);   // select all of command window
  
  }   // end of CWalkthroughDlg::RedrawRoom 

const char * pWord;
const char * pWordStart;
int iWordLength;

static bool skip_spaces (void)
  {
  for ( ; *pWord && isspace (*pWord); pWord++)
    if (*pWord == '\n')
      return true;    // end of line reached

  return false;
  } // end of skip_spaces

static void fread_to_eol (void)
  {
  for ( ; *pWord && *pWord != '\n'; pWord++)
    ;

  if (*pWord == '\n')
    pWord++;    // skip end-of-line
  } // end of fread_to_eol

static CString fread_word (bool bQuoted = true)
  {
CString strResult;

  iWordLength = 0;

  if (skip_spaces ())
    return "";        // stop at end of line
  
  if (*pWord == 0)    // stop at end of file
    return "";

  char cEnd = ' ';

  if (bQuoted)
    {
    cEnd = *pWord;    // remember as trailing delimiter
	  if (cEnd == '\'' || cEnd == '"')
		  pWord++;
    else
      cEnd = ' ';
    }

  pWordStart = pWord;   // remember where word starts

  // a non-alpha start sounds like 'Hi there
  if (!bQuoted && !isalnum (*pWord))
    {
    pWord++;
    iWordLength++;
    strResult = CString (pWordStart, 1);
    }
  else
    {
    for (; *pWord; pWord++, iWordLength++)
      if (cEnd == ' ' ? isspace(*pWord) : *pWord == cEnd )
        break;
    strResult = CString (pWordStart, pWord - pWordStart);
    if (*pWord)
      pWord++;    // skip trailing delimiter
    }

  return strResult;

  } // end of fread_word

void CWalkthroughDlg::OnOK() 
  {
CString strCommands;

  m_ctlCommand.GetWindowText (strCommands);

  pWord = strCommands;

CString strCommand = fread_word (false);

  // no command, ignore it
  if (strCommand.IsEmpty ())
    return;

  strCommand.MakeLower ();

int i;
POSITION pos;
POSITION resetPos;
CReset * reset;
CMobile * mob;
CMUDObject * object;

  // translate common direction abbreviations

  if (strCommand == "ne")
    strCommand = "northeast";
  else if (strCommand == "nw")
    strCommand = "northwest";
  else if (strCommand == "se")
    strCommand = "southeast";
  else if (strCommand == "sw")
    strCommand = "southwest";
  else if (strCommand == "enter")   // enter and leave go to "somewhere"
    strCommand = "somewhere";
  else if (strCommand == "leave")
    strCommand = "somewhere";

  // ==================== DIRECTION ==============================
  // first, see if the command is a direction (north, south etc.)

  if (RoomDirectionList.FindValue (strCommand, i, true))  // found it!
    {

    // look for that exit
    for (pos = m_room->exitlist.GetHeadPosition (); pos; )
      {
      CExit * exit = m_room->exitlist.GetNext (pos);
      if (exit->vdir == i)
        {
        CRoom * new_room = FindRoom (exit->vnum);
        if (new_room)
          {
          m_room = new_room;
          RedrawRoom ();
          }   // end of leading to a valid room
        else
          AppendToOutput (exit->Summary ());   // not a valid room

        return;
        } // end of exit found in room

      }   // end of processing each exit

    AppendToOutput (CFormat ("No exit to %s", (LPCTSTR) RoomDirectionList.ReturnName (i, false)));
    return;
    }   // end of processing each possible direction (and finding a match)


  // ==================== EXIT keywords ==============================
  // check all exits
  for (pos = m_room->exitlist.GetHeadPosition (); pos; )
    {
    CExit * exit = m_room->exitlist.GetNext (pos);
    if (!str_prefix (strCommand, exit->keyword))  // found it!
      {
      CRoom * new_room = FindRoom (exit->vnum);
      if (new_room)
        {
        m_room = new_room;
        RedrawRoom ();
        }   // end of leading to a valid room
      else
        AppendToOutput (exit->Summary ());   // not a valid room

      return;
      } // end of exit found with keyword matching entered word (eg. opening)
    }   // end of processing each exit


  // ==================== GOTO ==============================
  // look for "goto" command
  if (!str_prefix (strCommand, "goto"))  // found it!
    {
    CString strDest = fread_word (false);

    if (strDest.IsEmpty ())
      {
      AppendToOutput ("GOTO must be followed by room vnum, eg. GOTO 1234");
      return;
      }

    int iDest = atoi (strDest);

    if (iDest)
      {
      CRoom * new_room = FindRoom (iDest);
      if (new_room)
        {
        m_room = new_room;
        RedrawRoom ();
        return;
        }   // end of leading to a valid room
      }
    else
      {
      AppendToOutput ("GOTO vnum must be a number, eg. GOTO 1234");
      return;
      }

    AppendToOutput (CFormat ("Room %s not in this area", strDest));
    return;
    }

  // ==================== LOOK ==============================
  // look for "look" command
  if (!str_prefix (strCommand, "look"))  // found it!
    {
    CString strTarget = fread_word (false);
    if (strTarget.IsEmpty ())   // 'Look' on its own redraws current room
      {
      RedrawRoom ();
      return;
      }

    if (strTarget == "self")
      {
      AppendToOutput ("You see a slightly bemused builder standing here.  :)");
      return;
      }

    strTarget += ' ';   // trailing space, so we match on whole words

    // look for word in extra descriptions
    for (POSITION extraPos = m_room->extralist.GetHeadPosition (); extraPos; )
      {
      CExtraDescription * extra = m_room->extralist.GetNext (extraPos);
      CString strKeyword = extra->keyword;

      strKeyword.MakeLower ();
      strKeyword += ' ';

      // see if our word matches a description keyword
      if (strKeyword.Find (strTarget) != -1)
        {
        AppendToOutput (extra->description);
        return;
        } // end of match on keyword
      } // end of checking each extra description

    strTarget.TrimRight ();   // get rid of trailing space

    if (RoomDirectionList.FindValue (strTarget, i, true))  // found it!
      {
      // look for that exit
      for (pos = m_room->exitlist.GetHeadPosition (); pos; )
        {
        CExit * exit = m_room->exitlist.GetNext (pos);
        if (exit->vdir == i)
          {
          AppendToOutput (exit->description);

          CRoom * new_room = FindRoom (exit->vnum);
          if (new_room)
            {
            AppendToOutput (new_room->name);
            AppendToOutput (new_room->description);
            }   // end of leading to a valid room

          return;
          } // end of exit found in room

        }   // end of processing each exit

      }   // end of exit name found

    // OK, look for mobs and objects

    bool bThisRoom = false;
    CString strKeyword;

    strTarget += ' ';   // trailing space, so we match on whole words

    for (resetPos = m_pDoc->m_ResetList.GetHeadPosition (); resetPos; )
      {
      reset = m_pDoc->m_ResetList.GetNext (resetPos);

      switch (reset->command)
        {
        case 'M': // load mobile

          bThisRoom = reset->arg3 == m_room->vnum;

          if (!bThisRoom)
            break;    // wrong room - forget it

          if ((mob = FindMob ( reset->arg1)) == NULL)
            break;    // mob not found

          strKeyword = mob->player_name;
          strKeyword.MakeLower ();
          strKeyword += ' ';

          // see if our word matches a description keyword
          if (strKeyword.Find (strTarget) != -1)
            {
            AppendToOutput (mob->description);
            return;
            } // end of match on keyword
          
          break;

        case 'O': // load object
          if (reset->arg3 != m_room->vnum)
            break;    // wrong room - forget it

          if ((object = FindObj ( reset->arg1)) == NULL)
            break;    // object not found

          // look for word in extra descriptions
          for (POSITION extraPos = object->extralist.GetHeadPosition (); extraPos; )
            {
            CExtraDescription * extra = object->extralist.GetNext (extraPos);
            CString strKeyword = extra->keyword;

            strKeyword.MakeLower ();
            strKeyword += ' ';

            // see if our word matches a description keyword
            if (strKeyword.Find (strTarget) != -1)
              {
              AppendToOutput (extra->description);
              return;
              } // end of match on keyword
            } // end of checking each extra description

          strKeyword = object->name;
          strKeyword.MakeLower ();
          strKeyword += ' ';

          // see if our word matches a description keyword
          if (strKeyword.Find (strTarget) != -1)
            {
            AppendToOutput (object->description);
            return;
            } // end of match on keyword
          
          break;

        } // end of switch

      }   // end of processing each reset

    AppendToOutput ("You do not see that here");
    return;
    }   // end of doing a LOOK

  AppendToOutput ("Huh?");

  } // end of CWalkthroughDlg::OnOK


void CWalkthroughDlg::AppendToOutput (const char * sText)
  {
CString strOutput;

  m_ctlOutput.GetWindowText (strOutput);

  strOutput += ENDLINE;
  strOutput += sText;

  m_ctlOutput.SetWindowText (strOutput);
  m_ctlOutput.SetSel (SHRT_MAX, SHRT_MAX);   // select end of window

  m_ctlCommand.SetSel (0, -1);   // select command window

  } // end of CWalkthroughDlg::AppendToOutput

void CWalkthroughDlg::OnShowVnums() 
{
  RedrawRoom ();
}

void CWalkthroughDlg::OnShowEquipment() 
{
  RedrawRoom ();
}


