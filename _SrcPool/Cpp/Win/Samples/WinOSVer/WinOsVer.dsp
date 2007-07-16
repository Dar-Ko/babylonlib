# Microsoft Developer Studio Project File - Name="WinOSVer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=WinOSVer - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "WinOsVer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "WinOsVer.mak" CFG="WinOSVer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WinOSVer - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\WinDbg\VC6.0"
# PROP Intermediate_Dir ".\ObjDbg\VC6.0"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\.." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /Yu"StdAfx.h" /FD /c
# SUBTRACT CPP /u
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /i ".\Res" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:".\WinDbg/VC6.0/WinOsVer6.exe"
# SUBTRACT LINK32 /verbose /nodefaultlib
# Begin Target

# Name "WinOSVer - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;for;f90"
# Begin Source File

SOURCE=..\..\KDbgOSVI.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\KGetPrSu.cpp
# End Source File
# Begin Source File

SOURCE=..\..\KGetPrTy.cpp
# End Source File
# Begin Source File

SOURCE=..\..\KIsProdS.cpp
# End Source File
# Begin Source File

SOURCE=..\..\KWinFWIs.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\KWinVerG.cpp
# ADD CPP /W4
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\KWinVers.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\StdAfx.cpp
# ADD CPP /Yc"StdAfx.h"
# End Source File
# Begin Source File

SOURCE=.\Src\TestAbout.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\TestApp.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\TestApp.rc
# ADD BASE RSC /l 0x409 /i "Src"
# SUBTRACT BASE RSC /i ".\Res"
# ADD RSC /l 0x409 /i "Src" /i ".\Src"
# SUBTRACT RSC /i ".\Res"
# End Source File
# Begin Source File

SOURCE=.\Src\TestDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\TestView.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\TsWinDetect.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=..\..\KFileHnd.inl
# End Source File
# Begin Source File

SOURCE=..\..\KWinVerG.inl
# End Source File
# Begin Source File

SOURCE=..\..\KWinVers.h
# End Source File
# Begin Source File

SOURCE=..\..\KWinVers.inl
# End Source File
# Begin Source File

SOURCE=.\Src\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Src\stdafx.h
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
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\TestApp.ico
# End Source File
# Begin Source File

SOURCE=.\res\TestAppDoc.ico
# End Source File
# End Group
# End Target
# End Project
