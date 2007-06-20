# Microsoft Developer Studio Project File - Name="Strings" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

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
!MESSAGE "Strings - Win32 Release_MBCS" (based on "Win32 (x86) Console Application")
!MESSAGE "Strings - Win32 Debug_MBCS" (based on "Win32 (x86) Console Application")
!MESSAGE "Strings - Win32 Debug_Unicode" (based on "Win32 (x86) Console Application")
!MESSAGE "Strings - Win32 Debug_SBCS" (based on "Win32 (x86) Console Application")
!MESSAGE "Strings - Win32 Debug_SBCS_MFC" (based on "Win32 (x86) Console Application")
!MESSAGE "Strings - Win32 Debug_Unicode_MFC" (based on "Win32 (x86) Console Application")
!MESSAGE "Strings - Win32 Debug_MBCS_MFC" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "Strings"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Strings - Win32 Release_MBCS"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Strings___Win32_Release_MBCS"
# PROP BASE Intermediate_Dir "Strings___Win32_Release_MBCS"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\bin\Release_MBCS\Win32"
# PROP Intermediate_Dir "..\Obj\Release_MBCS\Strings\Win32"
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\.." /I "..\Common\Src\Win" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x1009 /d "NDEBUG"
# ADD RSC /l 0x1009 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_MBCS"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Strings___Win32_Debug_MBCS"
# PROP BASE Intermediate_Dir "Strings___Win32_Debug_MBCS"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\bin\Debug_MBCS\Win32"
# PROP Intermediate_Dir "..\Obj\Debug_MBCS\Strings\Win32"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\.." /I "..\Common\Src\Win" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x1009 /d "_DEBUG"
# ADD RSC /l 0x1009 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_Unicode"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Strings___Win32_Debug_Unicode"
# PROP BASE Intermediate_Dir "Strings___Win32_Debug_Unicode"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\bin\Debug_Unicode\Win32"
# PROP Intermediate_Dir "..\Obj\Debug_Unicode\Strings\Win32"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\.." /I "..\Common\Src\Win" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\.." /I "..\Common\Src\Win" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_UNICODE" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x1009 /d "_DEBUG"
# ADD RSC /l 0x1009 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_SBCS"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Strings___Win32_Debug_SBCS"
# PROP BASE Intermediate_Dir "Strings___Win32_Debug_SBCS"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\bin\Debug_SBCS\Win32"
# PROP Intermediate_Dir "..\Obj\Debug_SBCS\Strings\Win32"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\.." /I "..\Common\Src\Win" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\.." /I "..\Common\Src\Win" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_SBCS" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x1009 /d "_DEBUG"
# ADD RSC /l 0x1009 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /nodefaultlib

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_SBCS_MFC"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Strings___Win32_Debug_SBCS_MFC"
# PROP BASE Intermediate_Dir "Strings___Win32_Debug_SBCS_MFC"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\bin\Debug_SBCS_MFC\Win32"
# PROP Intermediate_Dir "..\Obj\Debug_SBCS_MFC\Strings\Win32"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\.." /I "..\Common\Src\Win" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_SBCS" /FR /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\.." /I "..\Common\Src\Win" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_SBCS" /D "_AFXDLL" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x1009 /d "_DEBUG"
# ADD RSC /l 0x1009 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# SUBTRACT BASE LINK32 /nodefaultlib
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_Unicode_MFC"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Strings___Win32_Debug_Unicode_MFC"
# PROP BASE Intermediate_Dir "Strings___Win32_Debug_Unicode_MFC"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\bin\Debug_Unicode_MFC\Win32"
# PROP Intermediate_Dir "..\Obj\Debug_Unicode_MFC\Strings\Win32"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\.." /I "..\Common\Src\Win" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_UNICODE" /FR /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\.." /I "..\Common\Src\Win" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_AFXDLL" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x1009 /d "_DEBUG"
# ADD RSC /l 0x1009 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_MBCS_MFC"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Strings___Win32_Debug_MBCS_MFC"
# PROP BASE Intermediate_Dir "Strings___Win32_Debug_MBCS_MFC"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\bin\Debug_MBCS_MFC\Win32"
# PROP Intermediate_Dir "..\Obj\Debug_MBCS_MFC\Strings\Win32"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\.." /I "..\Common\Src\Win" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\.." /I "..\Common\Src\Win" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x1009 /d "_DEBUG"
# ADD RSC /l 0x1009 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "Strings - Win32 Release_MBCS"
# Name "Strings - Win32 Debug_MBCS"
# Name "Strings - Win32 Debug_Unicode"
# Name "Strings - Win32 Debug_SBCS"
# Name "Strings - Win32 Debug_SBCS_MFC"
# Name "Strings - Win32 Debug_Unicode_MFC"
# Name "Strings - Win32 Debug_MBCS_MFC"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\KDtoA.c
# End Source File
# Begin Source File

SOURCE=..\..\STL\KFileRead.cpp
# End Source File
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

SOURCE=..\..\KItoA.c
# End Source File
# Begin Source File

SOURCE=..\..\KItoOct.c
# End Source File
# Begin Source File

SOURCE=..\..\KStrAtoI.cpp
# End Source File
# Begin Source File

SOURCE=..\..\KStrAtoU.c
# End Source File
# Begin Source File

SOURCE=..\..\KStrBtoA.c
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\KStrBtoH.cpp
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

SOURCE=..\..\KStrDup.c
# End Source File
# Begin Source File

SOURCE=..\..\KStrEnum.cpp
# End Source File
# Begin Source File

SOURCE=..\..\KStrEscC.c
# End Source File
# Begin Source File

SOURCE=..\..\KStrExC.cpp
# End Source File
# Begin Source File

SOURCE=..\..\KStrFindNoCase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\KStrGetF.cpp
# End Source File
# Begin Source File

SOURCE=..\..\KStrGetLine.cpp
# End Source File
# Begin Source File

SOURCE=..\..\KStrGetS.cpp
# End Source File
# Begin Source File

SOURCE=..\..\KStrGetW.cpp
# End Source File
# Begin Source File

SOURCE=..\..\KStrGSu.cpp
# End Source File
# Begin Source File

SOURCE=..\..\KStrGuid.cpp
# End Source File
# Begin Source File

SOURCE=..\..\KStrHtoL.c
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\KStrICmp.c
# End Source File
# Begin Source File

SOURCE=..\..\KStringHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\KStrIStr.c
# End Source File
# Begin Source File

SOURCE=..\..\KStrLowC.c
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\KStrNDup.c
# End Source File
# Begin Source File

SOURCE=..\..\KStrOtoL.c
# End Source File
# Begin Source File

SOURCE=..\..\KStrPalindrome.cpp
# End Source File
# Begin Source File

SOURCE=..\..\KStrPCpy.c
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\KStrPrefix.cpp
# End Source File
# Begin Source File

SOURCE=..\..\KStrRpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\KStrRplEscSeq.cpp
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\KStrRplSpaces.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\KStrRplT.cpp
# End Source File
# Begin Source File

SOURCE=..\..\KStrRTab.c
# End Source File
# Begin Source File

SOURCE=..\..\KStrToD.c
# End Source File
# Begin Source File

SOURCE=..\..\KStrTrim.cpp
# End Source File
# Begin Source File

SOURCE=..\..\KStrTrSl.c
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

SOURCE=..\..\KStrVowel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\KTestLog.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\KZtoA.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Src\main.cpp

!IF  "$(CFG)" == "Strings - Win32 Release_MBCS"

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_MBCS"

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_Unicode"

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_SBCS"

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_SBCS_MFC"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_Unicode_MFC"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_MBCS_MFC"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Common\Src\Win\stdafx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Src\TestCharConversion.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Src\TestCommonStrings.cpp
# End Source File
# Begin Source File

SOURCE=..\Complex\Src\TestComplexToA.cpp
# ADD CPP /D "NUSE_TESTCCOMPLEX"
# End Source File
# Begin Source File

SOURCE=.\Src\TestConversionToStr.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Src\TestGetLine.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\StringDyn\Src\TestIsPalindrome.cpp
# ADD CPP /YX"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\StringDyn\Src\TestIsVowel.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\TestReplaceSpace.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Src\TestStrDup.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Src\TestStrings.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\Src\Win\32\TsMfcAbout.cpp

!IF  "$(CFG)" == "Strings - Win32 Release_MBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_MBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_Unicode"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_SBCS"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_SBCS_MFC"

# PROP BASE Exclude_From_Build 1
# ADD CPP /I "..\Common\Res\Win"

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_Unicode_MFC"

# PROP BASE Exclude_From_Build 1
# ADD CPP /I "..\Common\Res\Win"

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_MBCS_MFC"

# PROP BASE Exclude_From_Build 1
# ADD CPP /I "..\Common\Res\Win"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Common\Src\Win\32\TsMfcApp.cpp

!IF  "$(CFG)" == "Strings - Win32 Release_MBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_MBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_Unicode"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_SBCS"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_SBCS_MFC"

# PROP BASE Exclude_From_Build 1
# ADD CPP /I "..\Common\Res\Win"

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_Unicode_MFC"

# PROP BASE Exclude_From_Build 1
# ADD CPP /I "..\Common\Res\Win"

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_MBCS_MFC"

# PROP BASE Exclude_From_Build 1
# ADD CPP /I "..\Common\Res\Win"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Common\Src\Win\32\TsMfcDoc.cpp

!IF  "$(CFG)" == "Strings - Win32 Release_MBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_MBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_Unicode"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_SBCS"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_SBCS_MFC"

# PROP BASE Exclude_From_Build 1
# ADD CPP /I "..\Common\Res\Win"

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_Unicode_MFC"

# PROP BASE Exclude_From_Build 1
# ADD CPP /I "..\Common\Res\Win"

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_MBCS_MFC"

# PROP BASE Exclude_From_Build 1
# ADD CPP /I "..\Common\Res\Win"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Common\Src\Win\32\TsMfcFrame.cpp

!IF  "$(CFG)" == "Strings - Win32 Release_MBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_MBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_Unicode"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_SBCS"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_SBCS_MFC"

# PROP BASE Exclude_From_Build 1
# ADD CPP /I "..\Common\Res\Win"

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_Unicode_MFC"

# PROP BASE Exclude_From_Build 1
# ADD CPP /I "..\Common\Res\Win"

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_MBCS_MFC"

# PROP BASE Exclude_From_Build 1
# ADD CPP /I "..\Common\Res\Win"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Common\Src\Win\32\TsMfcView.cpp

!IF  "$(CFG)" == "Strings - Win32 Release_MBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_MBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_Unicode"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_SBCS"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_SBCS_MFC"

# PROP BASE Exclude_From_Build 1
# ADD CPP /I "..\Common\Res\Win"

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_Unicode_MFC"

# PROP BASE Exclude_From_Build 1
# ADD CPP /I "..\Common\Res\Win"

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_MBCS_MFC"

# PROP BASE Exclude_From_Build 1
# ADD CPP /I "..\Common\Res\Win"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Common\Src\Win\32\TsMfcWriteTxt.cpp

!IF  "$(CFG)" == "Strings - Win32 Release_MBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_MBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_Unicode"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_SBCS"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_SBCS_MFC"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_Unicode_MFC"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_MBCS_MFC"

# PROP BASE Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Common\Src\TsWriteTxt.cpp

!IF  "$(CFG)" == "Strings - Win32 Release_MBCS"

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_MBCS"

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_Unicode"

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_SBCS"

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_SBCS_MFC"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_Unicode_MFC"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_MBCS_MFC"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\KCharCst.h
# End Source File
# Begin Source File

SOURCE=..\..\KStrConvert.h
# End Source File
# Begin Source File

SOURCE=..\..\KStrExt.h
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

SOURCE=..\Common\Src\Win\stdafx.h
# End Source File
# Begin Source File

SOURCE=..\Common\Src\Win\32\TsMfcAbout.h
# End Source File
# Begin Source File

SOURCE=..\Common\Src\Win\32\TsMfcApp.h
# End Source File
# Begin Source File

SOURCE=..\Common\Src\Win\32\TsMfcDoc.h
# End Source File
# Begin Source File

SOURCE=..\Common\Src\Win\32\TsMfcFrame.h
# End Source File
# Begin Source File

SOURCE=..\Common\Src\Win\32\TsMfcView.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\Common\Res\Win\SrcPool.ico
# End Source File
# Begin Source File

SOURCE=..\Common\Res\Win\32\Test.rc

!IF  "$(CFG)" == "Strings - Win32 Release_MBCS"

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_MBCS"

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_Unicode"

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_SBCS"

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_SBCS_MFC"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_Unicode_MFC"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_MBCS_MFC"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Common\Res\Win\32\Test.rc2

!IF  "$(CFG)" == "Strings - Win32 Release_MBCS"

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_MBCS"

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_Unicode"

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_SBCS"

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_SBCS_MFC"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_Unicode_MFC"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_MBCS_MFC"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Common\Res\Win\32\TestMfcApp.rc

!IF  "$(CFG)" == "Strings - Win32 Release_MBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_MBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_Unicode"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_SBCS"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_SBCS_MFC"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_Unicode_MFC"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_MBCS_MFC"

# PROP BASE Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Common\Res\Win\32\TestMfcApp.rc2

!IF  "$(CFG)" == "Strings - Win32 Release_MBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_MBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_Unicode"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_SBCS"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_SBCS_MFC"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_Unicode_MFC"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_MBCS_MFC"

# PROP BASE Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Res\TomSawyer.txt
# End Source File
# Begin Source File

SOURCE=..\Common\Res\Win\TsMfcRes.h

!IF  "$(CFG)" == "Strings - Win32 Release_MBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_MBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_Unicode"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_SBCS"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_SBCS_MFC"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_Unicode_MFC"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Strings - Win32 Debug_MBCS_MFC"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "Logs"

# PROP Default_Filter "*.log"
# Begin Source File

SOURCE=.\LibraryTest.log
# End Source File
# End Group
# Begin Source File

SOURCE=.\Strings.txt
# End Source File
# End Target
# End Project
