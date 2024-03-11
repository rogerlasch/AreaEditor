# Microsoft Developer Studio Project File - Name="AreaEditor" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=AreaEditor - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "AreaEditor.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AreaEditor.mak" CFG="AreaEditor - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AreaEditor - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "AreaEditor - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "AreaEditor - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0xc09 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0xc09 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "AreaEditor - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0xc09 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0xc09 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "AreaEditor - Win32 Release"
# Name "AreaEditor - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Splitter Views"

# PROP Default_Filter ""
# Begin Group "Mobiles"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MobileNamePage.cpp
# End Source File
# Begin Source File

SOURCE=.\MobileResetsPage.cpp
# End Source File
# Begin Source File

SOURCE=.\MobileStatsPage.cpp
# End Source File
# Begin Source File

SOURCE=.\MobileSummaryPage.cpp
# End Source File
# Begin Source File

SOURCE=.\MobileView.cpp
# End Source File
# End Group
# Begin Group "Objects"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ObjectAffectView.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjectExtraDescriptionView.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjectNamePage.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjectResetsPage.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjectStatsPage.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjectSummaryPage.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjectView.cpp
# End Source File
# End Group
# Begin Group "Rooms"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\RoomExitDetails.cpp
# End Source File
# Begin Source File

SOURCE=.\RoomExitView.cpp
# End Source File
# Begin Source File

SOURCE=.\RoomMapView.cpp
# End Source File
# Begin Source File

SOURCE=.\RoomNamePage.cpp
# End Source File
# Begin Source File

SOURCE=.\RoomSummaryPage.cpp
# End Source File
# Begin Source File

SOURCE=.\RoomView.cpp
# End Source File
# End Group
# Begin Group "Area"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AreaClimateView.cpp
# End Source File
# Begin Source File

SOURCE=.\AreaNameView.cpp
# End Source File
# Begin Source File

SOURCE=.\AreaNeighbourView.cpp
# End Source File
# Begin Source File

SOURCE=.\AreaRangesView.cpp
# End Source File
# Begin Source File

SOURCE=.\AreaView.cpp
# End Source File
# Begin Source File

SOURCE=.\AreaVnumsView.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\BlankView.cpp
# End Source File
# Begin Source File

SOURCE=.\HelpView.cpp
# End Source File
# Begin Source File

SOURCE=.\MUDProgramView.cpp
# End Source File
# Begin Source File

SOURCE=.\RepairView.cpp
# End Source File
# Begin Source File

SOURCE=.\ResetView.cpp
# End Source File
# Begin Source File

SOURCE=.\ShopView.cpp
# End Source File
# End Group
# Begin Group "Utilities"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Clipboard.cpp
# End Source File
# Begin Source File

SOURCE=.\DDV_validation.cpp
# End Source File
# Begin Source File

SOURCE=.\exceptions.cpp
# End Source File
# Begin Source File

SOURCE=.\FileReadWrite.cpp
# End Source File
# Begin Source File

SOURCE=.\format.cpp
# End Source File
# Begin Source File

SOURCE=.\GeneralUtilities.cpp
# End Source File
# Begin Source File

SOURCE=.\genprint.cpp
# End Source File
# Begin Source File

SOURCE=.\HyprLink.cpp
# End Source File
# Begin Source File

SOURCE=.\NumberUtils.cpp
# End Source File
# Begin Source File

SOURCE=.\StatLink.cpp
# End Source File
# Begin Source File

SOURCE=.\winplace.cpp
# End Source File
# End Group
# Begin Group "Dialogs"

# PROP Default_Filter ""
# Begin Group "Choose"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ChooseExitDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ChooseFlagsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ChooseFromListDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ChooseMobDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ChooseObjectDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ChooseRoomDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ChooseSpellDlg.cpp
# End Source File
# End Group
# Begin Group "Prefs"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Preferences.cpp
# End Source File
# Begin Source File

SOURCE=.\PrefsP1.cpp
# End Source File
# Begin Source File

SOURCE=.\PrefsP2.cpp
# End Source File
# Begin Source File

SOURCE=.\PrefsP3.cpp
# End Source File
# Begin Source File

SOURCE=.\PrefsP4.cpp
# End Source File
# End Group
# Begin Group "Skills"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\EditAffectDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SkillsListDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SkillsPages.cpp
# End Source File
# Begin Source File

SOURCE=.\SkillsSheet.cpp
# End Source File
# End Group
# Begin Group "Socials"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\EditSocialDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SocialsListDlg.cpp
# End Source File
# End Group
# Begin Group "Welcome, splash, tips"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TipDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Welcome1Dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\WelcomeDlg.cpp
# End Source File
# End Group
# Begin Group "Adding"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AddExitDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AddToObjectDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AddToRoomDlg.cpp
# End Source File
# End Group
# Begin Group "Commands"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CommandsListDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\EditCommandDlg.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\AreaLoadingProblems.cpp
# End Source File
# Begin Source File

SOURCE=.\AreaSummary.cpp
# End Source File
# Begin Source File

SOURCE=.\AreaTypeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CreditsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DeleteXrefDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\EditDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\FindDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\FindInDialogDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\FlagsListPage.cpp
# End Source File
# Begin Source File

SOURCE=.\GotoVnumDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\NeighbourNameDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ProgDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RenumberDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\WalkthroughDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\WearFlagsDlg.cpp
# End Source File
# End Group
# Begin Group "Subtypes"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Affect.cpp
# End Source File
# Begin Source File

SOURCE=.\Area.cpp
# End Source File
# Begin Source File

SOURCE=.\Command.cpp
# End Source File
# Begin Source File

SOURCE=.\Exit.cpp
# End Source File
# Begin Source File

SOURCE=.\ExtraDescription.cpp
# End Source File
# Begin Source File

SOURCE=.\Help.cpp
# End Source File
# Begin Source File

SOURCE=.\Mobile.cpp
# End Source File
# Begin Source File

SOURCE=.\MUDitem.cpp
# End Source File
# Begin Source File

SOURCE=.\MUDObject.cpp
# End Source File
# Begin Source File

SOURCE=.\MUDprogram.cpp
# End Source File
# Begin Source File

SOURCE=.\Repair.cpp
# End Source File
# Begin Source File

SOURCE=.\Reset.cpp
# End Source File
# Begin Source File

SOURCE=.\Room.cpp
# End Source File
# Begin Source File

SOURCE=.\RoomMap.cpp
# End Source File
# Begin Source File

SOURCE=.\Shop.cpp
# End Source File
# Begin Source File

SOURCE=.\Skill.cpp
# End Source File
# Begin Source File

SOURCE=.\SkillAffect.cpp
# End Source File
# Begin Source File

SOURCE=.\Social.cpp
# End Source File
# End Group
# Begin Group "Commands_Skills_Socials"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CheckCommandSyntax.cpp
# End Source File
# Begin Source File

SOURCE=.\Commands.cpp
# End Source File
# Begin Source File

SOURCE=.\Skills.cpp
# End Source File
# Begin Source File

SOURCE=.\Socials.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\AreaCheck.cpp
# End Source File
# Begin Source File

SOURCE=.\AreaEditor.cpp
# End Source File
# Begin Source File

SOURCE=.\AreaEditor.rc
# End Source File
# Begin Source File

SOURCE=.\AreaEditorDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\AreaEditorView.cpp
# End Source File
# Begin Source File

SOURCE=.\AreaRenumber.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Configuration.cpp
# End Source File
# Begin Source File

SOURCE=.\const.cpp
# End Source File
# Begin Source File

SOURCE=.\GeneratedNameDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MUSHexport.cpp
# End Source File
# Begin Source File

SOURCE=.\NameGeneration.cpp
# End Source File
# Begin Source File

SOURCE=.\Printing.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AddToObjectDlg.h
# End Source File
# Begin Source File

SOURCE=.\AddToRoomDlg.h
# End Source File
# Begin Source File

SOURCE=.\AreaClimateView.h
# End Source File
# Begin Source File

SOURCE=.\AreaEditor.h
# End Source File
# Begin Source File

SOURCE=.\AreaEditorDoc.h
# End Source File
# Begin Source File

SOURCE=.\AreaEditorView.h
# End Source File
# Begin Source File

SOURCE=.\AreaFlagsView.h
# End Source File
# Begin Source File

SOURCE=.\AreaLoadingProblems.h
# End Source File
# Begin Source File

SOURCE=.\AreaNameView.h
# End Source File
# Begin Source File

SOURCE=.\AreaNeighbourView.h
# End Source File
# Begin Source File

SOURCE=.\AreaRangesView.h
# End Source File
# Begin Source File

SOURCE=.\AreaRead.h
# End Source File
# Begin Source File

SOURCE=.\AreaSummary.h
# End Source File
# Begin Source File

SOURCE=.\AreaTypeDlg.h
# End Source File
# Begin Source File

SOURCE=.\AreaView.h
# End Source File
# Begin Source File

SOURCE=.\AreaVnumsView.h
# End Source File
# Begin Source File

SOURCE=.\AuthorNameView.h
# End Source File
# Begin Source File

SOURCE=.\BlankView.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\ChooseExitDlg.h
# End Source File
# Begin Source File

SOURCE=.\ChooseFlagsDlg.h
# End Source File
# Begin Source File

SOURCE=.\ChooseFromListDlg.h
# End Source File
# Begin Source File

SOURCE=.\ChooseMobDlg.h
# End Source File
# Begin Source File

SOURCE=.\ChooseObjectDlg.h
# End Source File
# Begin Source File

SOURCE=.\ChooseRoomDlg.h
# End Source File
# Begin Source File

SOURCE=.\ChooseSpellDlg.h
# End Source File
# Begin Source File

SOURCE=.\CommandsListDlg.h
# End Source File
# Begin Source File

SOURCE=.\Configuration.h
# End Source File
# Begin Source File

SOURCE=.\constants.h
# End Source File
# Begin Source File

SOURCE=.\CreditsDlg.h
# End Source File
# Begin Source File

SOURCE=.\DefaultFlags.h
# End Source File
# Begin Source File

SOURCE=.\DefaultLists.h
# End Source File
# Begin Source File

SOURCE=.\defaults.h
# End Source File
# Begin Source File

SOURCE=.\DeleteXrefDlg.h
# End Source File
# Begin Source File

SOURCE=.\EditAffectDlg.h
# End Source File
# Begin Source File

SOURCE=.\EditCommandDlg.h
# End Source File
# Begin Source File

SOURCE=.\EditDlg.h
# End Source File
# Begin Source File

SOURCE=.\EditSocialDlg.h
# End Source File
# Begin Source File

SOURCE=.\FindDlg.h
# End Source File
# Begin Source File

SOURCE=.\FindInDialogDlg.h
# End Source File
# Begin Source File

SOURCE=.\FlagsListPage.h
# End Source File
# Begin Source File

SOURCE=.\GeneralFlagsPage.h
# End Source File
# Begin Source File

SOURCE=.\GeneratedNameDlg.h
# End Source File
# Begin Source File

SOURCE=.\GotoVnumDlg.h
# End Source File
# Begin Source File

SOURCE=.\HelpView.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MobileActionsPage.h
# End Source File
# Begin Source File

SOURCE=.\MobileAffectPage.h
# End Source File
# Begin Source File

SOURCE=.\MobileAttacksPage.h
# End Source File
# Begin Source File

SOURCE=.\MobileBodyPartsPage.h
# End Source File
# Begin Source File

SOURCE=.\MobileDefensesPage.h
# End Source File
# Begin Source File

SOURCE=.\MobileNamePage.h
# End Source File
# Begin Source File

SOURCE=.\MobileResetsPage.h
# End Source File
# Begin Source File

SOURCE=.\MobileResistantPage.h
# End Source File
# Begin Source File

SOURCE=.\MobileSpeaksPage.h
# End Source File
# Begin Source File

SOURCE=.\MobileStatsPage.h
# End Source File
# Begin Source File

SOURCE=.\MobileSummaryPage.h
# End Source File
# Begin Source File

SOURCE=.\MobileView.h
# End Source File
# Begin Source File

SOURCE=.\MUDProgramView.h
# End Source File
# Begin Source File

SOURCE=.\NeighbourNameDlg.h
# End Source File
# Begin Source File

SOURCE=.\ObjectAffectView.h
# End Source File
# Begin Source File

SOURCE=.\ObjectExtraDescriptionView.h
# End Source File
# Begin Source File

SOURCE=.\ObjectExtraFlagsPage.h
# End Source File
# Begin Source File

SOURCE=.\ObjectNamePage.h
# End Source File
# Begin Source File

SOURCE=.\ObjectResetsPage.h
# End Source File
# Begin Source File

SOURCE=.\ObjectStatsPage.h
# End Source File
# Begin Source File

SOURCE=.\ObjectSummaryPage.h
# End Source File
# Begin Source File

SOURCE=.\ObjectView.h
# End Source File
# Begin Source File

SOURCE=.\PrefsDlg.h
# End Source File
# Begin Source File

SOURCE=.\PrefsP1.h
# End Source File
# Begin Source File

SOURCE=.\PrefsP2.h
# End Source File
# Begin Source File

SOURCE=.\PrefsP3.h
# End Source File
# Begin Source File

SOURCE=.\PrefsP4.h
# End Source File
# Begin Source File

SOURCE=.\ProgDlg.h
# End Source File
# Begin Source File

SOURCE=.\RenumberDlg.h
# End Source File
# Begin Source File

SOURCE=.\RepairView.h
# End Source File
# Begin Source File

SOURCE=.\ResetView.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\RoomExitDetails.h
# End Source File
# Begin Source File

SOURCE=.\RoomExitView.h
# End Source File
# Begin Source File

SOURCE=.\RoomFlagsPage.h
# End Source File
# Begin Source File

SOURCE=.\RoomMapView.h
# End Source File
# Begin Source File

SOURCE=.\RoomNamePage.h
# End Source File
# Begin Source File

SOURCE=.\RoomSummaryPage.h
# End Source File
# Begin Source File

SOURCE=.\RoomView.h
# End Source File
# Begin Source File

SOURCE=.\ShopView.h
# End Source File
# Begin Source File

SOURCE=.\SkillsListDlg.h
# End Source File
# Begin Source File

SOURCE=.\SkillsPages.h
# End Source File
# Begin Source File

SOURCE=.\SkillsSheet.h
# End Source File
# Begin Source File

SOURCE=.\SocialsListDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TipDlg.h
# End Source File
# Begin Source File

SOURCE=.\WalkthroughDlg.h
# End Source File
# Begin Source File

SOURCE=.\WearFlagsDlg.h
# End Source File
# Begin Source File

SOURCE=.\Welcome1Dlg.h
# End Source File
# Begin Source File

SOURCE=.\WelcomeDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\AreaEditor.ico
# End Source File
# Begin Source File

SOURCE=.\res\AreaEditor.rc2
# End Source File
# Begin Source File

SOURCE=.\res\AreaEditorDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\litebulb.bmp
# End Source File
# Begin Source File

SOURCE=.\logo.bmp
# End Source File
# Begin Source File

SOURCE=.\Splsh16.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\AreaEditor.reg
# End Source File
# Begin Source File

SOURCE=.\config.dat
# End Source File
# Begin Source File

SOURCE=.\configuration.txt
# End Source File
# Begin Source File

SOURCE=.\res\credits.txt
# End Source File
# Begin Source File

SOURCE=.\res\license.txt
# End Source File
# Begin Source File

SOURCE=.\mushexport.txt
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\tips.txt
# End Source File
# End Target
# End Project
# Section AreaEditor : {ACEFFC24-4628-11D1-B14A-105C01C13001}
# 	2:5:Class:CWSpell
# 	2:10:HeaderFile:wspell.h
# 	2:8:ImplFile:wspell.cpp
# End Section
# Section AreaEditor : {000095BD-0010-0A00-2600-260010000500}
# 	1:17:CG_IDS_DIDYOUKNOW:107
# 	1:22:CG_IDS_TIPOFTHEDAYMENU:106
# 	1:18:CG_IDS_TIPOFTHEDAY:105
# 	1:22:CG_IDS_TIPOFTHEDAYHELP:110
# 	1:19:CG_IDP_FILE_CORRUPT:109
# 	1:7:IDD_TIP:104
# 	1:13:IDB_LIGHTBULB:103
# 	1:18:CG_IDS_FILE_ABSENT:108
# 	2:17:CG_IDS_DIDYOUKNOW:CG_IDS_DIDYOUKNOW
# 	2:7:CTipDlg:CTipDlg
# 	2:22:CG_IDS_TIPOFTHEDAYMENU:CG_IDS_TIPOFTHEDAYMENU
# 	2:18:CG_IDS_TIPOFTHEDAY:CG_IDS_TIPOFTHEDAY
# 	2:12:CTIP_Written:OK
# 	2:22:CG_IDS_TIPOFTHEDAYHELP:CG_IDS_TIPOFTHEDAYHELP
# 	2:2:BH:
# 	2:19:CG_IDP_FILE_CORRUPT:CG_IDP_FILE_CORRUPT
# 	2:7:IDD_TIP:IDD_TIP
# 	2:8:TipDlg.h:TipDlg.h
# 	2:13:IDB_LIGHTBULB:IDB_LIGHTBULB
# 	2:18:CG_IDS_FILE_ABSENT:CG_IDS_FILE_ABSENT
# 	2:10:TipDlg.cpp:TipDlg.cpp
# End Section
# Section AreaEditor : {001C6502-6102-001D-0263-1E0002651F00}
# 	1:29:CG_IDR_POPUP_AREA_EDITOR_VIEW:117
# End Section
# Section AreaEditor : {ACEFFC26-4628-11D1-B14A-105C01C13001}
# 	2:21:DefaultSinkHeaderFile:wspell.h
# 	2:16:DefaultSinkClass:CWSpell
# End Section
# Section AreaEditor : {000009E5-09E5-0000-E509-0000E5090000}
# 	1:10:IDB_SPLASH:102
# 	2:21:SplashScreenInsertKey:4.0
# End Section
