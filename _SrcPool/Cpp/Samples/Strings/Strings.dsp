# Microsoft Developer Studio Project File - Name="Strings" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Strings - Win32 Debug_MBCS_MFC
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Strings.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Strings.mak" CFG="Strings - Win32 Debug_MBCS_MFC"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Strings - Win32 Debug_Unicode_MFC" (based on "Win32 (x86) Application")
!MESSAGE "Strings - Win32 Release_Unicode_MFC" (based on "Win32 (x86) Application")
!MESSAGE "Strings - Win32 Debug_Unicode" (based on "Win32 (x86) Application")
!MESSAGE "Strings - Win32 Release_Unicode" (based on "Win32 (x86) Application")
!MESSAGE "Strings - Win32 Debug_SBCS" (based on "Win32 (x86) Application")
!MESSAGE "Strings - Win32 Debug_MBCS" (based on "Win32 (x86) Application")
!MESSAGE "Strings - Win32 Debug_MBCS_MFC" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Strings - Win32 Debug_Unicode_MFC"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Strings___Win32_Debug_Unicode_MFC"
# PROP BASE Intermediate_Dir "Strings___Win32_Debug_Unicode_MFC"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\bin\Debug_Unicode_MFC\Win32"
# PROP Intermediate_Dir "..\Obj\Debug_Unicode_MFC\Strings\Win32"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\.." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"StdAfx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\.." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x1009 /d "_DEBUG" /d "_AFXDLL" /d "_UNICODE"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /version:1.0 /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /version:1.0 /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "Strings - Win32 Release_Unicode_MFC"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Strings___Win32_Release_Unicode_MFC"
# PROP BASE Intermediate_Dir "Strings___Win32_Release_Unicode_MFC"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\bin\Release_Unicode_MFC\Win32"
# PROP Intermediate_Dir "..\Obj\Release_Unicode_MFC\Strings\Win32"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\.." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"StdAfx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /I "..\.." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /FR /Yu"stdafx.h" /FD /GZ /c
# SUBTRACT CPP /O<none>
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x1009 /d "_DEBUG" /d "_AFXDLL" /d "_UNICODE"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /version:1.0 /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /version:1.0 /subsystem:windows /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /debug

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_Unicode"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Strings___Win32_Debug_Unicode"
# PROP BASE Intermediate_Dir "Strings___Win32_Debug_Unicode"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\bin\Debug_Unicode\Win32"
# PROP Intermediate_Dir "..\Obj\Debug_Unicode\Strings\Win32"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\.." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"StdAfx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\.." /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_UNICODE" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x1009 /d "_DEBUG" /d "_UNICODE"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /version:1.0 /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /version:1.0 /subsystem:console /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Strings - Win32 Release_Unicode"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Strings___Win32_Release_Unicode"
# PROP BASE Intermediate_Dir "Strings___Win32_Release_Unicode"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\bin\Release_Unicode\Win32"
# PROP Intermediate_Dir "..\Obj\Release_Unicode\Strings\Win32"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\.." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"StdAfx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /I "..\.." /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_UNICODE" /FR /Yu"stdafx.h" /FD /GZ /c
# SUBTRACT CPP /O<none>
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x1009 /d "NDEBUG" /d "_UNICODE"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /version:1.0 /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /version:1.0 /subsystem:console /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_SBCS"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Strings___Win32_Debug_SBCS"
# PROP BASE Intermediate_Dir "Strings___Win32_Debug_SBCS"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\bin\Debug_SBCS\Win32"
# PROP Intermediate_Dir "..\Obj\Debug_SBCS\Strings\Win32"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\.." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"StdAfx.h" /FD /GZ /c
# ADD CPP /nologo /W4 /Gm /GX /ZI /Od /I "..\.." /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_SBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x1009 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /version:1.0 /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /version:1.0 /subsystem:console /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_MBCS"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Strings___Win32_Debug_MBCS"
# PROP BASE Intermediate_Dir "Strings___Win32_Debug_MBCS"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\bin\Debug_MBCS\Win32"
# PROP Intermediate_Dir "..\Obj\Debug_MBCS\Strings\Win32"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\.." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"StdAfx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\.." /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x1009 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /version:1.0 /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /version:1.0 /subsystem:console /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_MBCS_MFC"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Strings___Win32_Debug_MBCS_MFC"
# PROP BASE Intermediate_Dir "Strings___Win32_Debug_MBCS_MFC"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\bin\Debug_MBCS_MFC\Win32"
# PROP Intermediate_Dir "..\Obj\Debug_MBCS_MFC\Strings\Win32"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\.." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"StdAfx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "..\.." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x1009 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /version:1.0 /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /version:1.0 /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Strings - Win32 Debug_Unicode_MFC"
# Name "Strings - Win32 Release_Unicode_MFC"
# Name "Strings - Win32 Debug_Unicode"
# Name "Strings - Win32 Release_Unicode"
# Name "Strings - Win32 Debug_SBCS"
# Name "Strings - Win32 Debug_MBCS"
# Name "Strings - Win32 Debug_MBCS_MFC"
# Begin Group "Resources"

# PROP Default_Filter "*.ico;*.bmp;*.rc2;*.rc"
# Begin Source File

SOURCE=..\Common\Res\Win\SrcPool.ico
# End Source File
# Begin Source File

SOURCE=..\Common\Res\Win\32\TestMfcApp.rc

!IF  "$(CFG)" == "Strings - Win32 Debug_Unicode_MFC"

!ELSEIF  "$(CFG)" == "Strings - Win32 Release_Unicode_MFC"

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_Unicode"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Release_Unicode"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_SBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_MBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_MBCS_MFC"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Common\Res\Win\32\TestMfcApp.rc2
# End Source File
# End Group
# Begin Group "Headers"

# PROP Default_Filter "*.h;*.inl"
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

SOURCE=.\Src\MainFrm.h
# End Source File
# Begin Source File

SOURCE=..\Common\Src\Win\stdafx.h
# End Source File
# Begin Source File

SOURCE=.\Src\StdAfx.h
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

# PROP Default_Filter "cpp,c"
# Begin Source File

SOURCE=..\..\KGetLRC.cpp
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\KIsLRC.cpp
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\KStrBtoA.c
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\KStrBtoU.c
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\KStrCatV.c
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\KStrCtoA.c
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\KStrHtoL.c
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\KString.cpp
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\KStrLowC.c
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\KStrPCpy.c
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\KStrRplEscSeq.cpp
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\KStrRplSpaces.cpp
# End Source File
# Begin Source File

SOURCE=..\..\KStrUtDJ.c
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\KStrUtoD.c
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\Common\Src\Win\stdafx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Src\TestView.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\TsCString.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\TsStrings.cpp
# End Source File
# End Group
# Begin Group "Logs"

# PROP Default_Filter "*.log"
# Begin Source File

SOURCE=.\Strings.log
# End Source File
# End Group
# Begin Source File

SOURCE=.\Strings.txt
# End Source File
# End Target
# End Project
