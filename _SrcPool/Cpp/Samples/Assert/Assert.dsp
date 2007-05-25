# Microsoft Developer Studio Project File - Name="Assert" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=Assert - Win32 Debug_Unicode_MFC
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Assert.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Assert.mak" CFG="Assert - Win32 Debug_Unicode_MFC"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Assert - Win32 Debug_SBCS" (based on "Win32 (x86) Console Application")
!MESSAGE "Assert - Win32 Release_SBCS" (based on "Win32 (x86) Console Application")
!MESSAGE "Assert - Win32 Debug_Unicode" (based on "Win32 (x86) Console Application")
!MESSAGE "Assert - Win32 Release_Unicode" (based on "Win32 (x86) Console Application")
!MESSAGE "Assert - Win32 Release_Unicode_MFC" (based on "Win32 (x86) Console Application")
!MESSAGE "Assert - Win32 Release_SBCS_MFC" (based on "Win32 (x86) Console Application")
!MESSAGE "Assert - Win32 Debug_SBCS_MFC" (based on "Win32 (x86) Console Application")
!MESSAGE "Assert - Win32 Debug_Unicode_MFC" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "Assert"
# PROP Scc_LocalPath "..\.."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Assert - Win32 Debug_SBCS"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Assert___Win32_Debug_SBCS"
# PROP BASE Intermediate_Dir "Assert___Win32_Debug_SBCS"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\bin\Debug_SBCS\Win32"
# PROP Intermediate_Dir "..\Obj\Debug_SBCS\Assert\Win32"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /Yu"StdAfx.h" /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\.." /I "..\Common\Src\Win" /I "..\Common\Src\Win\32" /I "..\Common\Res\Win" /I "..\Common\Res\Win\32" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_STL" /FR /FD /GZ /c
# SUBTRACT CPP /X /YX /Yc /Yu
# ADD BASE RSC /l 0x1009 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x1009 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "Assert - Win32 Release_SBCS"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Assert___Win32_Release_SBCS"
# PROP BASE Intermediate_Dir "Assert___Win32_Release_SBCS"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\bin\Release_SBCS\Win32"
# PROP Intermediate_Dir "..\Obj\Release_SBCS\Assert\Win32"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /Yu"StdAfx.h" /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\.." /I "..\Common\Src\Win" /I "..\Common\Src\Win\32" /I "..\Common\Res\Win" /I "..\Common\Res\Win\32" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_STL" /FR /FD /c
# SUBTRACT CPP /X /YX /Yc /Yu
# ADD BASE RSC /l 0x1009 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x1009 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "Assert - Win32 Debug_Unicode"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Assert___Win32_Debug_Unicode"
# PROP BASE Intermediate_Dir "Assert___Win32_Debug_Unicode"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\bin\Debug_Unicode\Win32"
# PROP Intermediate_Dir "..\Obj\Debug_Unicode\Assert\Win32"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /Yu"StdAfx.h" /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\.." /I "..\Common\Src\Win" /I "..\Common\Src\Win\32" /I "..\Common\Res\Win" /I "..\Common\Res\Win\32" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_UNICODE" /D "_STL" /FR /FD /GZ /c
# SUBTRACT CPP /X /YX /Yc /Yu
# ADD BASE RSC /l 0x1009 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x1009 /d "_DEBUG" /d "_UNICODE"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "Assert - Win32 Release_Unicode"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Assert___Win32_Release_Unicode"
# PROP BASE Intermediate_Dir "Assert___Win32_Release_Unicode"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\bin\Release_Unicode\Win32"
# PROP Intermediate_Dir "..\Obj\Release_Unicode\Assert\Win32"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /Yu"StdAfx.h" /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\.." /I "..\Common\Src\Win" /I "..\Common\Src\Win\32" /I "..\Common\Res\Win" /I "..\Common\Res\Win\32" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_UNICODE" /D "_STL" /FR /FD /c
# SUBTRACT CPP /X /YX /Yc /Yu
# ADD BASE RSC /l 0x1009 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x1009 /d "NDEBUG" /d "_UNICODE"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "Assert - Win32 Release_Unicode_MFC"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Assert___Win32_Release_Unicode_MFC"
# PROP BASE Intermediate_Dir "Assert___Win32_Release_Unicode_MFC"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\bin\Release_Unicode_MFC\Win32"
# PROP Intermediate_Dir "..\Obj\Debug_Unicode_MFC\Assert\Win32"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /Yu"StdAfx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\.." /I "..\Common\Src\Win" /I "..\Common\Src\Win\32" /I "..\Common\Res\Win" /I "..\Common\Res\Win\32" /D "NDEBUG" /D "_UNICODE" /D "_AFXDLL" /D "_STL" /D "WIN32" /D "_CONSOLE" /FR /FD /c
# SUBTRACT CPP /X /YX /Yc /Yu
# ADD BASE RSC /l 0x1009 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x1009 /d "NDEBUG" /d "_AFXDLL" /d "_UNICODE"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "Assert - Win32 Release_SBCS_MFC"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Assert___Win32_Release_SBCS_MFC"
# PROP BASE Intermediate_Dir "Assert___Win32_Release_SBCS_MFC"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\bin\Release_SBCS_MFC\Win32"
# PROP Intermediate_Dir "..\Obj\Release_SBCS_MFC\Assert\Win32"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /Yu"StdAfx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\.." /I "..\Common\Src\Win" /I "..\Common\Src\Win\32" /I "..\Common\Res\Win" /I "..\Common\Res\Win\32" /D "NDEBUG" /D "_AFXDLL" /D "_STL" /D "WIN32" /D "_CONSOLE" /FR /FD /c
# SUBTRACT CPP /X /YX /Yc /Yu
# ADD BASE RSC /l 0x1009 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x1009 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "Assert - Win32 Debug_SBCS_MFC"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Assert___Win32_Debug_SBCS_MFC"
# PROP BASE Intermediate_Dir "Assert___Win32_Debug_SBCS_MFC"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\bin\Debug_SBCS_MFC\Win32"
# PROP Intermediate_Dir "..\Obj\Debug_SBCS_MFC\Assert\Win32"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /Yu"StdAfx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\.." /I "..\Common\Src\Win" /I "..\Common\Src\Win\32" /I "..\Common\Res\Win" /I "..\Common\Res\Win\32" /D "_DEBUG" /D "_STL" /D "_AFXDLL" /D "WIN32" /D "_CONSOLE" /FR /FD /GZ /c
# SUBTRACT CPP /X /YX /Yc /Yu
# ADD BASE RSC /l 0x1009 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x1009 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "Assert - Win32 Debug_Unicode_MFC"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Assert___Win32_Debug_Unicode_MFC"
# PROP BASE Intermediate_Dir "Assert___Win32_Debug_Unicode_MFC"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\bin\Debug_Unicode_MFC\Win32"
# PROP Intermediate_Dir "..\Obj\Debug_Unicode_MFC\Assert\Win32"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /Yu"StdAfx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\.." /I "..\Common\Src\Win" /I "..\Common\Src\Win\32" /I "..\Common\Res\Win" /I "..\Common\Res\Win\32" /D "_DEBUG" /D "_UNICODE" /D "_AFXDLL" /D "_STL" /D "WIN32" /D "_CONSOLE" /FR /FD /GZ /c
# SUBTRACT CPP /X /YX /Yc /Yu
# ADD BASE RSC /l 0x1009 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x1009 /d "_DEBUG" /d "_AFXDLL" /d "_UNICODE"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Assert - Win32 Debug_SBCS"
# Name "Assert - Win32 Release_SBCS"
# Name "Assert - Win32 Debug_Unicode"
# Name "Assert - Win32 Release_Unicode"
# Name "Assert - Win32 Release_Unicode_MFC"
# Name "Assert - Win32 Release_SBCS_MFC"
# Name "Assert - Win32 Debug_SBCS_MFC"
# Name "Assert - Win32 Debug_Unicode_MFC"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\KTestLog.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\main.cpp

!IF  "$(CFG)" == "Assert - Win32 Debug_SBCS"

# ADD CPP /Yu"stdafx.h"

!ELSEIF  "$(CFG)" == "Assert - Win32 Release_SBCS"

# ADD CPP /Yu"stdafx.h"

!ELSEIF  "$(CFG)" == "Assert - Win32 Debug_Unicode"

# ADD CPP /Yu"stdafx.h"

!ELSEIF  "$(CFG)" == "Assert - Win32 Release_Unicode"

# ADD CPP /Yu"stdafx.h"

!ELSEIF  "$(CFG)" == "Assert - Win32 Release_Unicode_MFC"

# PROP Exclude_From_Build 1
# ADD CPP /Yu"stdafx.h"

!ELSEIF  "$(CFG)" == "Assert - Win32 Release_SBCS_MFC"

# PROP Exclude_From_Build 1
# ADD CPP /Yu"stdafx.h"

!ELSEIF  "$(CFG)" == "Assert - Win32 Debug_SBCS_MFC"

# PROP Exclude_From_Build 1
# ADD CPP /Yu"stdafx.h"

!ELSEIF  "$(CFG)" == "Assert - Win32 Debug_Unicode_MFC"

# PROP Exclude_From_Build 1
# ADD CPP /Yu"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Src\Win\32\main.cpp

!IF  "$(CFG)" == "Assert - Win32 Debug_SBCS"

# PROP Exclude_From_Build 1
# ADD CPP /Yu"stdafx.h"

!ELSEIF  "$(CFG)" == "Assert - Win32 Release_SBCS"

# PROP Exclude_From_Build 1
# ADD CPP /Yu"stdafx.h"

!ELSEIF  "$(CFG)" == "Assert - Win32 Debug_Unicode"

# PROP Exclude_From_Build 1
# ADD CPP /Yu"stdafx.h"

!ELSEIF  "$(CFG)" == "Assert - Win32 Release_Unicode"

# PROP Exclude_From_Build 1
# ADD CPP /Yu"stdafx.h"

!ELSEIF  "$(CFG)" == "Assert - Win32 Release_Unicode_MFC"

# ADD CPP /Yu"stdafx.h"

!ELSEIF  "$(CFG)" == "Assert - Win32 Release_SBCS_MFC"

# ADD CPP /Yu"stdafx.h"

!ELSEIF  "$(CFG)" == "Assert - Win32 Debug_SBCS_MFC"

# ADD CPP /Yu"stdafx.h"

!ELSEIF  "$(CFG)" == "Assert - Win32 Debug_Unicode_MFC"

# ADD CPP /Yu"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Common\Src\Win\stdafx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\Common\Res\Win\32\Test.rc
# End Source File
# Begin Source File

SOURCE=.\Src\TestAssert.cpp
# ADD CPP /Yu"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Src\TestAssertC.c
# End Source File
# Begin Source File

SOURCE=.\Src\TestCastConst.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\TestCastDynamic.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\TestCastOverload.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\TestCastReinterpret.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\TestCastStatic.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\TestCommonAssert.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\TestConformance.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\TestEndian.c
# End Source File
# Begin Source File

SOURCE=.\Src\TestKeywordExplicit.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\TestKeywordMutable.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\TestKeywordNamespace.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\TestKeywordTypename.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\TestPredefinedMacros.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\TestPredefinedMacrosC.c
# End Source File
# Begin Source File

SOURCE=.\Src\TestTrace.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\TestTraceC.c
# End Source File
# Begin Source File

SOURCE=..\Common\Src\TsWriteT.c
# End Source File
# Begin Source File

SOURCE=..\Common\Src\TsWriteTxt.cpp
# ADD CPP /Yu"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\KDbgMacr.h
# End Source File
# Begin Source File

SOURCE=..\..\KTestLog.h
# End Source File
# Begin Source File

SOURCE=..\..\KTrace.h
# End Source File
# Begin Source File

SOURCE=..\Common\Res\Win32\Resource.h
# End Source File
# Begin Source File

SOURCE=..\Common\Src\Win\stdafx.h
# End Source File
# Begin Source File

SOURCE=.\Src\TestConformance.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\Common\Res\SrcPool.ico
# End Source File
# Begin Source File

SOURCE=..\Common\Res\Win\SrcPool.ico
# End Source File
# End Group
# Begin Group "Logs"

# PROP Default_Filter "*.log"
# End Group
# Begin Source File

SOURCE=.\Assert.txt
# End Source File
# Begin Source File

SOURCE=..\Common\Src\Win\32\ReadMe.txt
# End Source File
# End Target
# End Project
