# Microsoft Developer Studio Project File - Name="_Doc" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=_Doc - Win32 Debug_SBCS
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "_Doc.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "_Doc.mak" CFG="_Doc - Win32 Debug_SBCS"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "_Doc - Win32 Debug_SBCS" (based on "Win32 (x86) Application")
!MESSAGE "_Doc - Win32 Debug_Unicode" (based on "Win32 (x86) Application")
!MESSAGE "_Doc - Win32 Release_SBCS" (based on "Win32 (x86) Application")
!MESSAGE "_Doc - Win32 Release_Unicode" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "_Doc - Win32 Debug_SBCS"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "_Doc___Win32_Debug_SBCS"
# PROP BASE Intermediate_Dir "_Doc___Win32_Debug_SBCS"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Library\HTMLHelp.tmp"
# PROP Intermediate_Dir ".\Library\HTMLHelp.tmp"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x1009 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /debug
# Begin Custom Build - Generating Documentation
InputPath=.\Library\HTMLHelp.tmp\_Doc.exe
SOURCE="$(InputPath)"

"Bogus.Target" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"S:\_SrcPool\Cpp\Documentation\MakeDoc.cmd"

# End Custom Build

!ELSEIF  "$(CFG)" == "_Doc - Win32 Debug_Unicode"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "_Doc___Win32_Debug_Unicode"
# PROP BASE Intermediate_Dir "_Doc___Win32_Debug_Unicode"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Library\HTMLHelp.tmp"
# PROP Intermediate_Dir ".\Library\HTMLHelp.tmp"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x1009 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /debug
# Begin Custom Build - Generating Documentation
InputPath=.\Library\HTMLHelp.tmp\_Doc.exe
SOURCE="$(InputPath)"

"Bogus.Target" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"S:\_SrcPool\Cpp\Documentation\MakeDoc.cmd"

# End Custom Build

!ELSEIF  "$(CFG)" == "_Doc - Win32 Release_SBCS"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "_Doc___Win32_Release_SBCS"
# PROP BASE Intermediate_Dir "_Doc___Win32_Release_SBCS"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Library\HTMLHelp.tmp"
# PROP Intermediate_Dir ".\Library\HTMLHelp.tmp"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x1009 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /incremental:yes /debug
# Begin Custom Build - Generating Documentation
InputPath=.\Library\HTMLHelp.tmp\_Doc.exe
SOURCE="$(InputPath)"

"Bogus.Target" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"S:\_SrcPool\Cpp\Documentation\MakeDoc.cmd"

# End Custom Build

!ELSEIF  "$(CFG)" == "_Doc - Win32 Release_Unicode"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "_Doc___Win32_Release_Unicode"
# PROP BASE Intermediate_Dir "_Doc___Win32_Release_Unicode"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Library\HTMLHelp.tmp"
# PROP Intermediate_Dir ".\Library\HTMLHelp.tmp"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x1009 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /incremental:yes /debug
# Begin Custom Build - Generating Documentation
InputPath=.\Library\HTMLHelp.tmp\_Doc.exe
SOURCE="$(InputPath)"

"Bogus.Target" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"S:\_SrcPool\Cpp\Documentation\MakeDoc.cmd"

# End Custom Build

!ENDIF 

# Begin Target

# Name "_Doc - Win32 Debug_SBCS"
# Name "_Doc - Win32 Debug_Unicode"
# Name "_Doc - Win32 Release_SBCS"
# Name "_Doc - Win32 Release_Unicode"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\_SrcPool.djt

!IF  "$(CFG)" == "_Doc - Win32 Debug_SBCS"

# PROP Ignore_Default_Tool 1
USERDEP___SRCP=".\MakeDoc.cmd"	
# Begin Custom Build - Making HTML documentation
IntDir=.\Library\HTMLHelp.tmp
ProjDir=.
InputPath=.\_SrcPool.djt
InputName=_SrcPool

"$(IntDir)\$(InputName).hhp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ProjDir)\MakeDoc.cmd

# End Custom Build

!ELSEIF  "$(CFG)" == "_Doc - Win32 Debug_Unicode"

# PROP Ignore_Default_Tool 1
USERDEP___SRCP=".\MakeDoc.cmd"	
# Begin Custom Build - Making HTML documentation
IntDir=.\Library\HTMLHelp.tmp
ProjDir=.
InputPath=.\_SrcPool.djt
InputName=_SrcPool

"$(IntDir)\$(InputName).hhp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ProjDir)\MakeDoc.cmd

# End Custom Build

!ELSEIF  "$(CFG)" == "_Doc - Win32 Release_SBCS"

# PROP Ignore_Default_Tool 1
USERDEP___SRCP=".\MakeDoc.cmd"	
# Begin Custom Build - Making HTML documentation
IntDir=.\Library\HTMLHelp.tmp
ProjDir=.
InputPath=.\_SrcPool.djt
InputName=_SrcPool

"$(IntDir)\$(InputName).hhp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ProjDir)\MakeDoc.cmd

# End Custom Build

!ELSEIF  "$(CFG)" == "_Doc - Win32 Release_Unicode"

# PROP Ignore_Default_Tool 1
USERDEP___SRCP=".\MakeDoc.cmd"	
# Begin Custom Build - Making HTML documentation
IntDir=.\Library\HTMLHelp.tmp
ProjDir=.
InputPath=.\_SrcPool.djt
InputName=_SrcPool

"$(IntDir)\$(InputName).hhp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ProjDir)\MakeDoc.cmd

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Library\HTMLHelp.tmp\_SrcPool.hhp

!IF  "$(CFG)" == "_Doc - Win32 Debug_SBCS"

# PROP Ignore_Default_Tool 1
USERDEP___SRCPO=".\MakeHelp.cmd"	".\Library\HTMLHelp.tmp\_SrcPool.hhc"	".\Library\HTMLHelp.tmp\_SrcPool.hhk"	
# Begin Custom Build - Making HTML help file...
IntDir=.\Library\HTMLHelp.tmp
OutDir=.\Library\HTMLHelp.tmp
ProjDir=.
InputPath=.\Library\HTMLHelp.tmp\_SrcPool.hhp
InputName=_SrcPool

"$(OutDir)\$(InputName).chm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ProjDir)\MakeHelp.cmd S:\_SrcPool\Cpp\Documentation\$(IntDir)\$(InputName)

# End Custom Build

!ELSEIF  "$(CFG)" == "_Doc - Win32 Debug_Unicode"

# PROP Ignore_Default_Tool 1
USERDEP___SRCPO=".\MakeHelp.cmd"	".\Library\HTMLHelp.tmp\_SrcPool.hhc"	".\Library\HTMLHelp.tmp\_SrcPool.hhk"	
# Begin Custom Build - Making HTML help file...
IntDir=.\Library\HTMLHelp.tmp
OutDir=.\Library\HTMLHelp.tmp
ProjDir=.
InputPath=.\Library\HTMLHelp.tmp\_SrcPool.hhp
InputName=_SrcPool

"$(OutDir)\$(InputName).chm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ProjDir)\MakeHelp.cmd S:\_SrcPool\Cpp\Documentation\$(IntDir)\$(InputName)

# End Custom Build

!ELSEIF  "$(CFG)" == "_Doc - Win32 Release_SBCS"

# PROP Ignore_Default_Tool 1
USERDEP___SRCPO=".\MakeHelp.cmd"	".\Library\HTMLHelp.tmp\_SrcPool.hhc"	".\Library\HTMLHelp.tmp\_SrcPool.hhk"	
# Begin Custom Build - Making HTML help file...
IntDir=.\Library\HTMLHelp.tmp
OutDir=.\Library\HTMLHelp.tmp
ProjDir=.
InputPath=.\Library\HTMLHelp.tmp\_SrcPool.hhp
InputName=_SrcPool

"$(OutDir)\$(InputName).chm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ProjDir)\MakeHelp.cmd S:\_SrcPool\Cpp\Documentation\$(IntDir)\$(InputName)

# End Custom Build

!ELSEIF  "$(CFG)" == "_Doc - Win32 Release_Unicode"

# PROP Ignore_Default_Tool 1
USERDEP___SRCPO=".\MakeHelp.cmd"	".\Library\HTMLHelp.tmp\_SrcPool.hhc"	".\Library\HTMLHelp.tmp\_SrcPool.hhk"	
# Begin Custom Build - Making HTML help file...
IntDir=.\Library\HTMLHelp.tmp
OutDir=.\Library\HTMLHelp.tmp
ProjDir=.
InputPath=.\Library\HTMLHelp.tmp\_SrcPool.hhp
InputName=_SrcPool

"$(OutDir)\$(InputName).chm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ProjDir)\MakeHelp.cmd S:\_SrcPool\Cpp\Documentation\$(IntDir)\$(InputName)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Library\_SrcPool.hpj
# PROP Exclude_From_Build 1
# PROP Ignore_Default_Tool 1
# End Source File
# Begin Source File

SOURCE=.\Doc\main.cpp

!IF  "$(CFG)" == "_Doc - Win32 Debug_SBCS"

# PROP BASE Intermediate_Dir "_Doc"
# PROP BASE Exclude_From_Build 1
# PROP Intermediate_Dir "_Doc"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "_Doc - Win32 Debug_Unicode"

# PROP BASE Intermediate_Dir "_Doc"
# PROP BASE Exclude_From_Build 1
# PROP Intermediate_Dir "_Doc"
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "_Doc - Win32 Release_SBCS"

!ELSEIF  "$(CFG)" == "_Doc - Win32 Release_Unicode"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe;png;htm;gif"
# Begin Source File

SOURCE=.\Res\arrowDBlue.gif
# End Source File
# Begin Source File

SOURCE=.\Res\arrowLBlue.gif
# End Source File
# Begin Source File

SOURCE=.\Res\arrowRBlue.gif
# End Source File
# Begin Source File

SOURCE=.\Res\arrowTBlue.gif
# End Source File
# Begin Source File

SOURCE=.\Res\arrowUBlue.gif
# End Source File
# Begin Source File

SOURCE=.\Res\BcgkChessBlue.gif
# End Source File
# Begin Source File

SOURCE=.\Res\BcgkCpp.gif
# End Source File
# Begin Source File

SOURCE=.\Res\BckgBookOfHoursIllumination_BuildingOfTheTowerOfBabel.jpg
# End Source File
# Begin Source File

SOURCE=.\Res\BckgBruegelPieter_LittleTowerofBabel.jpg
# End Source File
# Begin Source File

SOURCE=.\Res\BckgBruegelPieter_TowerofBabel.jpg
# End Source File
# Begin Source File

SOURCE=.\Res\BckgUml.jpg
# End Source File
# Begin Source File

SOURCE=.\Res\btnGoto.gif
# End Source File
# Begin Source File

SOURCE=.\Res\btnHelp.gif
# End Source File
# Begin Source File

SOURCE=.\Res\btnPrinter.gif
# End Source File
# Begin Source File

SOURCE=.\Res\btnResize.gif
# End Source File
# Begin Source File

SOURCE=.\Res\Desktop.ico
# End Source File
# Begin Source File

SOURCE=.\Images\eqFibonacci.gif
# End Source File
# Begin Source File

SOURCE=.\Images\eqFibonacciLim.gif
# End Source File
# Begin Source File

SOURCE=.\Images\eqGoldenMean.gif
# End Source File
# Begin Source File

SOURCE=.\Images\eqGoldenRatio.gif
# End Source File
# Begin Source File

SOURCE=.\Images\eqGoldenRect.gif
# End Source File
# Begin Source File

SOURCE=.\Images\eqSectioAurea.gif
# End Source File
# Begin Source File

SOURCE=.\Images\graphGoldenRect.gif
# End Source File
# Begin Source File

SOURCE=.\Res\icoAnsi.ico
# End Source File
# Begin Source File

SOURCE=.\Res\icoBas.ico
# End Source File
# Begin Source File

SOURCE=.\Res\icoBoost.ico
# End Source File
# Begin Source File

SOURCE=.\Res\icoClass.ico
# End Source File
# Begin Source File

SOURCE=.\Res\icoConfig.ico
# End Source File
# Begin Source File

SOURCE=.\Res\icoCpp.ico
# End Source File
# Begin Source File

SOURCE=.\Res\icoCss.ico
# End Source File
# Begin Source File

SOURCE=.\Res\icoCvs.ico
# End Source File
# Begin Source File

SOURCE=.\Res\icoDocumentation.ico
# End Source File
# Begin Source File

SOURCE=.\Res\icoFlag.ico
# End Source File
# Begin Source File

SOURCE=.\Res\icoISoc.ico
# End Source File
# Begin Source File

SOURCE=.\Res\icoJava.ico
# End Source File
# Begin Source File

SOURCE=.\Res\icoJavaScript.ico
# End Source File
# Begin Source File

SOURCE=.\Res\icoLinux.ico
# End Source File
# Begin Source File

SOURCE=.\Res\icoMfc.ico
# End Source File
# Begin Source File

SOURCE=.\Res\icoMsDev.ico
# End Source File
# Begin Source File

SOURCE=.\Res\icoMsdn.ico
# End Source File
# Begin Source File

SOURCE=.\Res\icoMsVb6.ico
# End Source File
# Begin Source File

SOURCE=.\Res\icoPalm.ico
# End Source File
# Begin Source File

SOURCE=.\Res\icoPcb.ico
# End Source File
# Begin Source File

SOURCE=.\Res\icoSample.ico
# End Source File
# Begin Source File

SOURCE=.\Res\icoStatic.ico
# End Source File
# Begin Source File

SOURCE=.\Res\icoStl.ico
# End Source File
# Begin Source File

SOURCE=.\Res\icoStlPort.ico
# End Source File
# Begin Source File

SOURCE=.\Res\icoSubversion.ico
# End Source File
# Begin Source File

SOURCE=.\Res\icoUnicode.ico
# End Source File
# Begin Source File

SOURCE=.\Res\icoVbScript.ico
# End Source File
# Begin Source File

SOURCE=.\Res\icoWin16.ico
# End Source File
# Begin Source File

SOURCE=.\Res\icoWin32.ico
# End Source File
# Begin Source File

SOURCE=.\Res\icoWinCE.ico
# End Source File
# Begin Source File

SOURCE=.\Res\icoWinXP.ico
# End Source File
# Begin Source File

SOURCE=.\Res\imgPetraTreasury.jpg
# End Source File
# Begin Source File

SOURCE=.\Res\imgTheStaircase.jpg
# End Source File
# Begin Source File

SOURCE=.\Res\imgUgaritTable.jpg
# End Source File
# Begin Source File

SOURCE=.\Html\KAbstract.htm
# End Source File
# Begin Source File

SOURCE=.\Html\KArticles.htm
# End Source File
# Begin Source File

SOURCE=.\Html\KASCIICharTable.htm
# End Source File
# Begin Source File

SOURCE=.\Html\KASCIIOem.htm
# End Source File
# Begin Source File

SOURCE=.\Res\KBckgGray.jpg
# End Source File
# Begin Source File

SOURCE=.\Res\KBook.ico
# End Source File
# Begin Source File

SOURCE=.\Html\KCodingLF.htm
# End Source File
# Begin Source File

SOURCE=.\Html\KColorCt.htm
# End Source File
# Begin Source File

SOURCE=.\Html\KColorCt256.htm
# End Source File
# Begin Source File

SOURCE=.\Html\KComputerLaws.htm
# End Source File
# Begin Source File

SOURCE=.\Html\KContentA.htm
# End Source File
# Begin Source File

SOURCE=.\Html\KContentB.htm
# End Source File
# Begin Source File

SOURCE=.\Html\KContentC.htm
# End Source File
# Begin Source File

SOURCE=.\Html\KCopyright.htm
# End Source File
# Begin Source File

SOURCE=.\Html\KDirTree.htm
# End Source File
# Begin Source File

SOURCE=.\Res\KFootnote.cur
# End Source File
# Begin Source File

SOURCE=.\Html\KGifFormat.htm
# End Source File
# Begin Source File

SOURCE=.\Res\KHelp.cur
# End Source File
# Begin Source File

SOURCE=.\Html\KHtmlCharEntity.htm
# End Source File
# Begin Source File

SOURCE=.\Html\KMusicScale.htm
# End Source File
# Begin Source File

SOURCE=.\Res\KReference.cur
# End Source File
# Begin Source File

SOURCE=.\Html\KReferences.htm
# End Source File
# Begin Source File

SOURCE=.\Html\KRefFrame.htm
# End Source File
# Begin Source File

SOURCE=.\Html\KRefOnline.htm
# End Source File
# Begin Source File

SOURCE=.\Html\KRepository.htm
# End Source File
# Begin Source File

SOURCE=.\Html\KStandards.htm
# End Source File
# Begin Source File

SOURCE=.\Html\kVsCreatedFiles.htm
# End Source File
# Begin Source File

SOURCE=.\Html\KXModemProtocol.htm
# End Source File
# Begin Source File

SOURCE=.\Html\KYModemProtocol.htm
# End Source File
# Begin Source File

SOURCE=.\Res\SrcPool.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\_Doc.txt
# End Source File
# End Target
# End Project
