# Microsoft Developer Studio Project File - Name="VerInfoTest" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=VerInfoTest - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VerInfoTest.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VerInfoTest.mak" CFG="VerInfoTest - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VerInfoTest - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe
# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\WinDbg"
# PROP Intermediate_Dir ".\ObjDbg"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\.." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"StdAfx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /version:1.0 /subsystem:windows /debug /machine:I386 /pdbtype:sept
# Begin Target

# Name "VerInfoTest - Win32 Debug"
# Begin Group "Resources"

# PROP Default_Filter "*.ico;*.bmp;*.rc2;*.rc"
# Begin Source File

SOURCE=.\Res\TestApp.ico
# End Source File
# Begin Source File

SOURCE=.\Src\TestApp.rc
# End Source File
# Begin Source File

SOURCE=.\Res\TestApp.rc2
# End Source File
# Begin Source File

SOURCE=.\Res\TestAppDoc.ico
# End Source File
# End Group
# Begin Group "Headers"

# PROP Default_Filter "*.h;*.inl"
# Begin Source File

SOURCE=..\..\KVerInfo.h
# End Source File
# Begin Source File

SOURCE=.\Src\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Src\TestAbout.h
# End Source File
# Begin Source File

SOURCE=.\Src\TestApp.h
# End Source File
# Begin Source File

SOURCE=.\Src\TestDoc.h
# End Source File
# Begin Source File

SOURCE=.\Src\TestView.h
# End Source File
# End Group
# Begin Group "Source"

# PROP Default_Filter "*.cpp, *.c"
# Begin Source File

SOURCE=..\..\KSysErrM.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\KVerInDp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\KVerInfo.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Src\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\StdAfx.cpp
# ADD CPP /W4 /Yc"StdAfx.h"
# End Source File
# Begin Source File

SOURCE=.\Src\TestAbout.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\TestApp.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\TestDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\TestView.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\TsVerInfo.cpp
# End Source File
# End Group
# End Target
# End Project
