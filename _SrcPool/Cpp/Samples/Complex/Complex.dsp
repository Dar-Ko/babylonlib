# Microsoft Developer Studio Project File - Name="Complex" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Complex - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Complex.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Complex.mak" CFG="Complex - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Complex - Win32 Debug" (based on "Win32 (x86) Application")
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
# ADD CPP /nologo /MDd /w /W0 /Gm /GX /ZI /Od /I "..\.." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /Yu"StdAfx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /i ".\Res" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:".\WinDbg/VC6.0/Complex6.exe"
# SUBTRACT LINK32 /verbose /nodefaultlib
# Begin Target

# Name "Complex - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;for;f90"
# Begin Source File

SOURCE=..\..\KZLineIn.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\StdAfx.cpp
# ADD CPP /W3 /Yc"StdAfx.h"
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

SOURCE=.\Src\TsComplex.cpp
# ADD CPP /W4
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=..\..\KComplex.h
# End Source File
# Begin Source File

SOURCE=..\..\KMathCst.h
# End Source File
# Begin Source File

SOURCE=..\..\KMathCst.inl
# End Source File
# Begin Source File

SOURCE=..\..\KPhysCst.h
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
