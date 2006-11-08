# Microsoft Developer Studio Project File - Name="Utilities" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=Utilities - Win32 Debug_Unicode
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Utilities.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Utilities.mak" CFG="Utilities - Win32 Debug_Unicode"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Utilities - Win32 Debug_SBCS" (based on "Win32 (x86) Console Application")
!MESSAGE "Utilities - Win32 Debug_Unicode" (based on "Win32 (x86) Console Application")
!MESSAGE "Utilities - Win32 Release_SBCS" (based on "Win32 (x86) Console Application")
!MESSAGE "Utilities - Win32 Release_Unicode" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Utilities - Win32 Debug_SBCS"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Utilities___Win32_Debug_SBCS"
# PROP BASE Intermediate_Dir "Utilities___Win32_Debug_SBCS"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\bin\Debug_SBCS\Win32"
# PROP Intermediate_Dir "..\Obj\Debug_SBCS\Utilities\Win32"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /I "../.." /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FD /GZ /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "../.." /I "./Src" /I ".." /I "..\.." /I "..\Common\Src\Win" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "_USE_STL" /FR /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x1009 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /profile /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /profile /debug /machine:I386

!ELSEIF  "$(CFG)" == "Utilities - Win32 Debug_Unicode"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Utilities___Win32_Debug_Unicode"
# PROP BASE Intermediate_Dir "Utilities___Win32_Debug_Unicode"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\bin\Debug_Unicode\Win32"
# PROP Intermediate_Dir "..\Obj\Debug_Unicode\Utilities\Win32"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /I "../.." /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FD /GZ /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "../.." /I "./Src" /I ".." /I "..\.." /I "..\Common\Src\Win" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_UNICODE" /FR /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x1009 /d "_DEBUG" /d "_UNICODE"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /profile /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /profile /debug /machine:I386

!ELSEIF  "$(CFG)" == "Utilities - Win32 Release_SBCS"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Utilities___Win32_Release_SBCS"
# PROP BASE Intermediate_Dir "Utilities___Win32_Release_SBCS"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\bin\Release_SBCS\Win32"
# PROP Intermediate_Dir "..\Obj\Release_SBCS\Utilities\Win32"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /FD /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /W3 /GX /O2 /I "./Src" /I ".." /I "..\.." /I "..\Common\Src\Win" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x1009 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /profile /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /profile /machine:I386

!ELSEIF  "$(CFG)" == "Utilities - Win32 Release_Unicode"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Utilities___Win32_Release_Unicode"
# PROP BASE Intermediate_Dir "Utilities___Win32_Release_Unicode"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\bin\Release_Unicode\Win32"
# PROP Intermediate_Dir "..\Obj\Release_Unicode\Utilities\Win32"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /I ".." /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /FD /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /W3 /GX /O2 /I "./Src" /I ".." /I "..\.." /I "..\Common\Src\Win" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_UNICODE" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x1009 /d "NDEBUG" /d "_UNICODE"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /profile /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /profile /machine:I386

!ENDIF 

# Begin Target

# Name "Utilities - Win32 Debug_SBCS"
# Name "Utilities - Win32 Debug_Unicode"
# Name "Utilities - Win32 Release_SBCS"
# Name "Utilities - Win32 Release_Unicode"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\Win\32\KBeepWin.cpp
# End Source File
# Begin Source File

SOURCE=..\..\KGuid.cpp

!IF  "$(CFG)" == "Utilities - Win32 Debug_SBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Utilities - Win32 Debug_Unicode"

!ELSEIF  "$(CFG)" == "Utilities - Win32 Release_SBCS"

!ELSEIF  "$(CFG)" == "Utilities - Win32 Release_Unicode"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\KOctave.cpp
# End Source File
# Begin Source File

SOURCE=..\..\KStrGuid.cpp

!IF  "$(CFG)" == "Utilities - Win32 Debug_SBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Utilities - Win32 Debug_Unicode"

# PROP Exclude_From_Build 1
# ADD CPP /D "_USE_STL"

!ELSEIF  "$(CFG)" == "Utilities - Win32 Release_SBCS"

!ELSEIF  "$(CFG)" == "Utilities - Win32 Release_Unicode"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\Win\32\KStrGuidWin.cpp

!IF  "$(CFG)" == "Utilities - Win32 Debug_SBCS"

# ADD CPP /D "_DEBUG_INCL_PREPROCESS"

!ELSEIF  "$(CFG)" == "Utilities - Win32 Debug_Unicode"

# ADD CPP /D "_USE_STL"

!ELSEIF  "$(CFG)" == "Utilities - Win32 Release_SBCS"

!ELSEIF  "$(CFG)" == "Utilities - Win32 Release_Unicode"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\Win\32\KSysErrM.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\main.cpp

!IF  "$(CFG)" == "Utilities - Win32 Debug_SBCS"

# ADD CPP /D "_DEBUG_INCL_PREPROCESS"

!ELSEIF  "$(CFG)" == "Utilities - Win32 Debug_Unicode"

!ELSEIF  "$(CFG)" == "Utilities - Win32 Release_SBCS"

!ELSEIF  "$(CFG)" == "Utilities - Win32 Release_Unicode"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Src\TestBeep.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\TestCommonUtilities.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\TestGuid.cpp

!IF  "$(CFG)" == "Utilities - Win32 Debug_SBCS"

!ELSEIF  "$(CFG)" == "Utilities - Win32 Debug_Unicode"

# ADD CPP /D "_USE_STL"

!ELSEIF  "$(CFG)" == "Utilities - Win32 Release_SBCS"

!ELSEIF  "$(CFG)" == "Utilities - Win32 Release_Unicode"

# ADD CPP /D "UNICODE"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Common\Src\TsWriteTxt.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\KBeep.h
# End Source File
# Begin Source File

SOURCE=..\..\KBitMan.h
# End Source File
# Begin Source File

SOURCE=..\..\KGuid.h
# End Source File
# Begin Source File

SOURCE=..\..\KOctave.h
# End Source File
# Begin Source File

SOURCE=..\..\KPoint.h
# End Source File
# Begin Source File

SOURCE=..\..\KTypedef.h
# End Source File
# Begin Source File

SOURCE=..\Common\Src\Win\stdafx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "Logs"

# PROP Default_Filter "*.log"
# End Group
# Begin Source File

SOURCE=.\Utilities.txt
# End Source File
# End Target
# End Project
