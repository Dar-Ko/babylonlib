# Microsoft Developer Studio Project File - Name="StringsConsole" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=StringsConsole - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "StringsConsole.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "StringsConsole.mak" CFG="StringsConsole - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "StringsConsole - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "StringsConsole - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "StringsConsole - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\WinRel\Console"
# PROP Intermediate_Dir ".\ObjRel\Console"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "../.." /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 /out:".\WinRel\Console/Strings.exe"

!ELSEIF  "$(CFG)" == "StringsConsole - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\WinDbg\Console"
# PROP Intermediate_Dir ".\ObjDbg\Console"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "../.." /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /out:".\WinDbg\Console/Strings.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "StringsConsole - Win32 Release"
# Name "StringsConsole - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\KFileRead.cpp
# End Source File
# Begin Source File

SOURCE=..\..\KItoA.c

!IF  "$(CFG)" == "StringsConsole - Win32 Release"

!ELSEIF  "$(CFG)" == "StringsConsole - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\KItoOct.c
# End Source File
# Begin Source File

SOURCE=..\..\KStrBtoA.c
# End Source File
# Begin Source File

SOURCE=..\..\KStrBtoH.cpp
# End Source File
# Begin Source File

SOURCE=..\..\KStrCtoA.c
# End Source File
# Begin Source File

SOURCE=..\..\KStrDup.c
# End Source File
# Begin Source File

SOURCE=..\..\KStrGetLine.cpp
# End Source File
# Begin Source File

SOURCE=..\..\KStrHtoL.c
# End Source File
# Begin Source File

SOURCE=..\..\KStrICmp.c
# End Source File
# Begin Source File

SOURCE=..\..\KStrOtoL.c
# End Source File
# Begin Source File

SOURCE=..\..\KStrRplSpaces.cpp
# End Source File
# Begin Source File

SOURCE=..\..\KStrTrim.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\main.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\StdAfx.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\TsCharConversion.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\TsConversionToStr.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\TsCString.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\TsGetLine.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\TsReplaceSpace.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\KCharCst.h
# End Source File
# Begin Source File

SOURCE=..\..\KString.h
# End Source File
# Begin Source File

SOURCE=..\..\KStrings.h
# End Source File
# Begin Source File

SOURCE=..\..\KTChar.h
# End Source File
# Begin Source File

SOURCE=..\..\KTrace.h
# End Source File
# Begin Source File

SOURCE=..\..\KTypedef.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe;*.txt"
# Begin Source File

SOURCE=.\Res\TomSawyer.txt
# End Source File
# End Group
# End Target
# End Project
