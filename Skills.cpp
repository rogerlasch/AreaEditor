/*
** AreaEditor - a program for editing SMAUG and ROM area files.
** Author: Nick Gammon
** http://www.gammon.com.au/
** See Copyright Notice at the end of AreaEditor.h
*/

#include "stdafx.h"
#include "AreaEditor.h"
#include "MainFrm.h"
#include "defaults.h"

#include "SkillsListDlg.h"

int get_skill (const CString & skilltype)
  {
  if ( skilltype ==  "Race" )
    return SKILL_RACIAL;
  if ( skilltype ==  "Spell" )
    return SKILL_SPELL;
  if ( skilltype ==  "Skill" )
    return SKILL_SKILL;
  if ( skilltype ==  "Weapon" )
    return SKILL_WEAPON;
  if ( skilltype ==  "Tongue" )
    return SKILL_TONGUE;
  if ( skilltype ==  "Herb" )
    return SKILL_HERB;
  return SKILL_UNKNOWN;
  }

void CAreaEditorApp::fread_skill (CFileRead & FileRead)
  {
    CString buf;
    CString word;
    bool fMatch;
    bool got_info;
    CSkill  *skill;

    skill = new CSkill;

    m_SkillList.AddTail (skill);

    while (true)
    {
	  word   = FileRead.fread_word ();
	  fMatch = FALSE;

	  switch ( UPPER(word[0]) )
	  {
	  case '*':
	      fMatch = TRUE;
	      FileRead.fread_to_eol ();
	      break;

	  case 'A':
	      if (word == "Affect")
	        {
		      CSkillAffect *aff;

		      aff = new CSkillAffect;

		      aff->duration = FileRead.fread_word ();
		      aff->location = FileRead.fread_number ();
		      aff->modifier = FileRead.fread_word ();
		      aff->bitvector = FileRead.fread_number ();
		      skill->affects.AddTail (aff);
		      fMatch = TRUE;
		      break;
	        }
	      break;

	  case 'C':

	      if ( word == "Class" )
	      {
		      int theclass = FileRead.fread_number ();
          int level = FileRead.fread_number ();
          int adept = FileRead.fread_number ();
          if (theclass >= 0 && theclass < MAX_CLASS)
            {
		        skill->skill_level[theclass] = level;
		        skill->skill_adept[theclass] = adept;
            }
		      fMatch = TRUE;
		      break;
	        }
/*
huh?
	      if ( word == "Code" )
	        {
		      skill->spell_skill_fun = FileRead.fread_word ();
  		    fMatch = TRUE;
		      break;  
	        }

  */
	      KEY( "Code",	skill->spell_skill_fun, FileRead.fread_word () );
	      KEY( "Components",	skill->components,	FileRead.fread_string () );
	      break;
 
	  case 'D':
        KEY( "Dammsg",	    skill->noun_damage,	FileRead.fread_string () );
	      KEY( "Dice",	      skill->dice,		FileRead.fread_string () );
	      KEY( "Diechar",	    skill->die_char,	FileRead.fread_string () );
	      KEY( "Dieroom",	    skill->die_room,	FileRead.fread_string () );
	      KEY( "Dievict",	    skill->die_vict,	FileRead.fread_string () );
	      KEY( "Difficulty",	skill->difficulty,	FileRead.fread_number () );
	      break;

	  case 'E':
	      if ( word == "End" )
		    return;
	      break;
	      
	  case 'F':
	      KEY( "Flags",	skill->flags,		FileRead.fread_number () );
	      break;

	  case 'G':
	      KEY( "Guild",	skill->guild,		FileRead.fread_number () );
	      break;

	  case 'H':
	      KEY( "Hitchar",	skill->hit_char,	FileRead.fread_string () );
  	    KEY( "Hitdest",	skill->hit_dest,	FileRead.fread_string () );
	      KEY( "Hitroom",	skill->hit_room,	FileRead.fread_string () );
	      KEY( "Hitvict",	skill->hit_vict,	FileRead.fread_string () );
	      break;

	  case 'I':
	      KEY( "Immchar",	skill->imm_char,	FileRead.fread_string () );
	      KEY( "Immroom",	skill->imm_room,	FileRead.fread_string () );
	      KEY( "Immvict",	skill->imm_vict,	FileRead.fread_string () );
	      if ( !strcmp( word, "Info" ) )
	        {
		      skill->info = FileRead.fread_number ();
		      got_info = TRUE;
		      fMatch = TRUE;
		      break;
	        }

	      break;

	  case 'M':
	      KEY( "Mana",	skill->min_mana,	FileRead.fread_number () );
	      KEY( "Minlevel",	skill->min_level,	FileRead.fread_number () );
	      KEY( "Minpos",	skill->minimum_position, FileRead.fread_number () );
	      KEY( "Misschar",	skill->miss_char,	FileRead.fread_string () );
	      KEY( "Missroom",	skill->miss_room,	FileRead.fread_string () );
	      KEY( "Missvict",	skill->miss_vict,	FileRead.fread_string () );
	      break;
	  
	  case 'N':
        KEY( "Name",	skill->name,		FileRead.fread_string () );
	      break;

	  case 'P':
	      KEY( "Participants",skill->participants,	FileRead.fread_number () );
	      break;

	  case 'R':
  	    KEY( "Range",	skill->range,		FileRead.fread_number () );
	      KEY( "Rounds",	skill->beats,		FileRead.fread_number () );

	      if ( !strcmp( word, "Race" ) )
	        {
		      int race = FileRead.fread_number ();
          int level = FileRead.fread_number ();
          int adept = FileRead.fread_number ();

          if (race >= 0 && race < MAX_CLASS)
            {
		        skill->race_level[race] = level;
		        skill->race_adept[race] = adept;
            }
		      fMatch = TRUE;
		      break;
          }
	      break;

	      break;

	  case 'S':
	      KEY( "Slot",	skill->slot,		FileRead.fread_number () );
	      KEY( "Saves",	skill->saves,		FileRead.fread_number () );
	      break;

	  case 'T':
	      KEY( "Target",	skill->target,		FileRead.fread_number () );
	      KEY( "Teachers",	skill->teachers,	FileRead.fread_string () );
	      KEY( "Type",	skill->type,  get_skill(FileRead.fread_word ())  );
	      break;

	  case 'V':
	      KEY( "Value",	skill->value,		FileRead.fread_number () );
	      break;

	  case 'W':
	      KEY( "Wearoff",	skill->msg_off,		FileRead.fread_string () );
	      break;
	  }
	  
	  if ( !fMatch )
       ThrowErrorException ("No match: %s", (LPCTSTR) word );
    }   // end of processing each word

  } // end of CAreaEditorApp::fread_skill 

void CAreaEditorApp::LoadSkills (const CString strFileName) 
  {

	CWaitCursor	wait;

	try
	  {
    CFileRead FileRead;

    // Open skills file
		CFile	fSkills (strFileName, CFile::modeRead|CFile::shareDenyWrite);

    CArchive ar(&fSkills, CArchive::load);

    FileRead.Init ("Loading skills", &ar);

	  try
	    {
	    while (true)
	     {
	     char letter;
	     CString word;

	     letter = FileRead.fread_letter();
	     if ( letter == '*' )
	       {
	      FileRead.fread_to_eol ();
	      continue;
	      }

	      if ( letter != '#' )
          ThrowErrorException ( "# not found.");

	      word = FileRead.fread_word ();
         if (word == "SKILL")
	        {
		      fread_skill (FileRead);
		      continue;
	        }
	      else
	        if (word == "END")
	          break;
	      else
          ThrowErrorException ( "Bad section.");
	     } // end of read loop

      m_bSkillsDirty = false;
	    }   // end of try block
	  catch(CException* e)
  	  {
      FileRead.Wrapup ();
      DeleteSkills ();    // error on load - don't keep half of them
      e->ReportError ();
      ::AfxMessageBox (CFormat ("Error occurred in file %s at (line %ld) \"%s\"",
                    (LPCTSTR) strFileName,
                    FileRead.GetLineNumber (), 
                    (LPCTSTR) FileRead.GetLastLineRead ()),
                    MB_ICONINFORMATION);
		  e->Delete();
      ar.Close();
      return;
	    }

    ar.Close();

    FileRead.Wrapup ();

	  }
	catch(CException* e)
  	{
    ::AfxMessageBox (
                    CFormat ("Unable to open skills file: %s", 
                    (LPCTSTR) strFileName), 
                    MB_ICONEXCLAMATION);
		e->Delete();
    return;
	  }

  SortSkills ();

  }   // end of CAreaEditorApp::LoadSkills 

void CAreaEditorApp::OnSkillsLoad() 
{

	CFileDialog	dlg(TRUE,						// TRUE for FileOpen
					"dat",						// default extension
					"skills.dat",						// initial file name
					OFN_HIDEREADONLY|OFN_FILEMUSTEXIST,
					"Skills table files (*.dat)|*.dat||");
	dlg.m_ofn.lpstrTitle = "Select skills file";
	
  if (dlg.DoModal() != IDOK)
		return;

	LoadSkills (dlg.GetPathName());
}

void CAreaEditorApp::OnSkillsEdit() 
{
CSkillsListDlg dlg;

  dlg.DoModal ();
  
}

void CAreaEditorApp::OnUpdateSkillsEdit(CCmdUI* pCmdUI) 
{
  pCmdUI->Enable (!m_SkillList.IsEmpty ());	
}

void CAreaEditorApp::OnUpdateSkillsLoad(CCmdUI* pCmdUI) 
{
  pCmdUI->Enable (m_SkillList.IsEmpty ());	
}

void CAreaEditorApp::OnSkillsClose() 
{
  if (m_bSkillsDirty)
    {
    int iResponse = ::AfxMessageBox ("Skills file has changed. Save it?",
                                      MB_YESNOCANCEL | MB_ICONQUESTION);
    if (iResponse == IDCANCEL)
      return;

    if (iResponse == IDYES)
      OnSkillsSave ();

    }
  DeleteSkills ();
}

void CAreaEditorApp::OnUpdateSkillsClose(CCmdUI* pCmdUI) 
{
  pCmdUI->Enable (!m_SkillList.IsEmpty ());	
}

void CAreaEditorApp::OnSkillsSave() 
{
	CFileDialog	dlg(FALSE,						// FALSE for FileSave
					"dat",						// default extension
					"skills.dat",
					OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_PATHMUSTEXIST,
					"Data files (*.dat)|*.dat||",
					&Frame);
	dlg.m_ofn.lpstrTitle = "Skills file";

	if (dlg.DoModal() != IDOK)
		return;

	try
	  {
    POSITION skillPos;
    CSkill * skill;

		CFile	f (dlg.GetPathName(), CFile::modeCreate|CFile::modeWrite|CFile::shareExclusive);

    CArchive ar(&f, CArchive::store);

    for (skillPos = App.m_SkillList.GetHeadPosition (); skillPos; )
      {
      skill = App.m_SkillList.GetNext (skillPos);

      ar.WriteString ("#SKILL" ENDLINE);

      CString strType = SkillTypeList.ReturnName (skill->type, false);
      if (!strType.IsEmpty ())
        strType.SetAt (0, toupper (strType [0]));   // capitalise type


#define CONDSTRING(name, field)  \
      do  {  \
       if (!skill->field.IsEmpty ())  \
          ar.WriteString (CFormat (name "%s~" ENDLINE, (LPCTSTR) skill->field));  \
          } while (false)

#define CONDWORD(name, field)  \
      do  {  \
       if (!skill->field.IsEmpty ())  \
          ar.WriteString (CFormat (name "%s" ENDLINE, (LPCTSTR) skill->field));  \
          } while (false)

#define CONDNUMBER(name, field)  \
      do  {  \
       if (skill->field)  \
          ar.WriteString (CFormat (name "%i" ENDLINE, skill->field));  \
          } while (false)

      // these two lines are required
      ar.WriteString (CFormat ("Name         %s~" ENDLINE, (LPCTSTR) skill->name));
      ar.WriteString (CFormat ("Type         %s"  ENDLINE, (LPCTSTR) strType));
      ar.WriteString (CFormat ("Flags        %i"  ENDLINE,  skill->flags));
//      CONDNUMBER ("Flags        ", flags);
      CONDNUMBER ("Guild        ", guild);
      CONDNUMBER ("Target       ", target);
      CONDNUMBER ("Minpos       ", minimum_position);
      CONDNUMBER ("Slot         ", slot);
      CONDNUMBER ("Mana         ", min_mana);
      CONDNUMBER ("Rounds       ", beats);
      CONDWORD   ("Code         ", spell_skill_fun);
      ar.WriteString (CFormat ("Dammsg       %s~" ENDLINE, (LPCTSTR) skill->noun_damage));
      CONDSTRING ("Wearoff      ", msg_off);
      CONDSTRING ("Teachers     ", teachers);
      CONDSTRING ("Hitchar      ", hit_char);
      CONDSTRING ("Hitvict      ", hit_vict);
      CONDSTRING ("Hitroom      ", hit_room);
      CONDSTRING ("Hitdest      ", hit_dest);
      CONDSTRING ("Misschar     ", miss_char);
      CONDSTRING ("Missvict     ", miss_vict);
      CONDSTRING ("Missroom     ", miss_room);
      CONDSTRING ("Dice         ", dice);
      CONDNUMBER ("Participants ", participants);
      CONDSTRING ("Components   ", components);
      CONDSTRING ("Immchar      ", imm_char);
      CONDSTRING ("Immroom      ", imm_room);
      CONDSTRING ("Immvict      ", imm_vict);
      CONDSTRING ("Diechar      ", die_char);
      CONDSTRING ("Dieroom      ", die_room);
      CONDSTRING ("Dievict      ", die_vict);

      // affects

      for (POSITION affectPos = skill->affects.GetHeadPosition (); affectPos; )
        {
        CSkillAffect *affect = skill->affects.GetNext (affectPos);
          ar.WriteString (CFormat ("Affect      \'%s\' %i \'%s\' %i" ENDLINE, 
                          (LPCTSTR) affect->duration,
                          affect->location,
                          (LPCTSTR) affect->modifier,
                          affect->bitvector));
        }   // end of affects list

      CONDNUMBER ("Value        ", value);
      ar.WriteString (CFormat ("Minlevel     %i"  ENDLINE,  skill->min_level));
      CONDNUMBER ("Difficulty   ", difficulty);
      CONDNUMBER ("Info         ", info);
      CONDNUMBER ("Range        ", range);
      CONDNUMBER ("Saves        ", saves);

      // Races

      int x;

      // I don't have an example of race, but will assume we do it if nonzero
      for (x = 0; x < MAX_CLASS; x++ )
        {
        if (skill->race_level[x] || skill->race_adept[x])
          ar.WriteString (CFormat ("Race        %i %i %i" ENDLINE, 
                          x, 
                          skill->race_level[x] ,
                          skill->race_adept[x]));
        }

      // Classs

      // I don't have an example of class, but will assume we do it if nonzero
      for (x = 0; x < MAX_CLASS; x++ )
        {
        if (skill->skill_level[x] || skill->skill_adept[x])
          ar.WriteString (CFormat ("Class        %i %i %i" ENDLINE, 
                          x, 
                          skill->skill_level[x] ,
                          skill->skill_adept[x]));
        }

      ar.WriteString ("End" ENDLINE);    // end of this skill
      ar.WriteString (ENDLINE);    // blank line
         
      }   // end of each skill


    ar.WriteString ("#END" ENDLINE);    // skills file terminator

    ar.Close ();
    
    }
	catch (CException* e)
	{
		e->ReportError();
		e->Delete();
	}

  m_bSkillsDirty = false;
}

void CAreaEditorApp::OnUpdateSkillsSave(CCmdUI* pCmdUI) 
{
  pCmdUI->Enable (!m_SkillList.IsEmpty () && m_bSkillsDirty);	
}

void CAreaEditorApp::DeleteSkills (void)
  {
// ========================================================================
// delete all skills

  for (POSITION skillPos = m_SkillList.GetHeadPosition (); skillPos; )
    delete m_SkillList.GetNext (skillPos);

  m_SkillList.RemoveAll ();   // pointers are deleted, remove list items

  m_bSkillsDirty = false;

  }


int CompareSkill (const void * elem1, const void * elem2)
  {
  // ah yes, *this* line was fun to get working :)
  return (*((CSkill **) elem1))->name.CompareNoCase ((*((CSkill **) elem2))->name);
  }


void CAreaEditorApp::SortSkills (void)
  {
POSITION SkillPos;
CTypedPtrArray <CPtrArray, CSkill*> CSkillsArray;
int iCount = App.m_SkillList.GetCount ();
int i;

	try
	  {

    CSkillsArray.SetSize (iCount);

    // extract pointers into a simple array
    for (i = 0, SkillPos = m_SkillList.GetHeadPosition (); SkillPos; i++)
      CSkillsArray.SetAt (i, m_SkillList.GetNext (SkillPos)); 


    // sort the array
    qsort (CSkillsArray.GetData (), 
           iCount,
           sizeof (CSkill *),
           CompareSkill);

    // get rid of old list
    m_SkillList.RemoveAll ();

    // re-add in sorted order
    for (i = 0; i < iCount; i++)
      m_SkillList.AddTail (CSkillsArray [i]);

    }   // end of try block
	catch(CException* e)
  	{
    e->ReportError ();
		e->Delete();
	  }


  }