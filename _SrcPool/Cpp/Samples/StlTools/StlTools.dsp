# Microsoft Developer Studio Project File - Name="StlTools" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=StlTools - Win32 Debug_Unicode
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "StlTools.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "StlTools.mak" CFG="StlTools - Win32 Debug_Unicode"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "StlTools - Win32 Debug_SBCS" (based on "Win32 (x86) Console Application")
!MESSAGE "StlTools - Win32 Debug_Unicode" (based on "Win32 (x86) Console Application")
!MESSAGE "StlTools - Win32 Release_SBCS" (based on "Win32 (x86) Console Application")
!MESSAGE "StlTools - Win32 Release_Unicode" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "StlTools"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "StlTools - Win32 Debug_SBCS"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug_SBCS"
# PROP BASE Intermediate_Dir "Debug_SBCS"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\bin\Debug_SBCS\Win32"
# PROP Intermediate_Dir "..\Obj\Debug_SBCS\StlTools\Win32"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\.." /I "..\..\STL" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_STL" /FR /YX"stdstl.h" /FD /GZ /c
# ADD BASE RSC /l 0x1009 /d "_DEBUG"
# ADD RSC /l 0x1009 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib advapi32.lib shell32.lib uuid.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "StlTools - Win32 Debug_Unicode"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug_Unicode"
# PROP BASE Intermediate_Dir "Debug_Unicode"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\bin\Debug_Unicode\Win32"
# PROP Intermediate_Dir "..\Obj\Debug_Unicode\StlTools\Win32"
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\.." /I "..\..\STL" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_UNICODE" /D "_STL" /FR /YX"stdstl.h" /FD /GZ /c
# ADD BASE RSC /l 0x1009 /d "_DEBUG"
# ADD RSC /l 0x1009 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib advapi32.lib shell32.lib uuid.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "StlTools - Win32 Release_SBCS"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release_SBCS"
# PROP BASE Intermediate_Dir "Release_SBCS"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\bin\Release_SBCS\Win32"
# PROP Intermediate_Dir "..\Obj\Release_SBCS\StlTools\Win32"
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\.." /I "..\..\STL" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_STL" /FR /YX"stdstl.h" /FD /c
# ADD BASE RSC /l 0x1009 /d "NDEBUG"
# ADD RSC /l 0x1009 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib advapi32.lib shell32.lib uuid.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "StlTools - Win32 Release_Unicode"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release_Unicode"
# PROP BASE Intermediate_Dir "Release_Unicode"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\bin\Release_Unicode\Win32"
# PROP Intermediate_Dir "..\Obj\Release_Unicode\StlTools\Win32"
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\.." /I "..\..\STL" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_UNICODE" /D "_STL" /FR /YX"stdstl.h" /FD /c
# ADD BASE RSC /l 0x1009 /d "NDEBUG"
# ADD RSC /l 0x1009 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib advapi32.lib shell32.lib uuid.lib /nologo /subsystem:console /machine:I386

!ENDIF 

# Begin Target

# Name "StlTools - Win32 Debug_SBCS"
# Name "StlTools - Win32 Debug_Unicode"
# Name "StlTools - Win32 Release_SBCS"
# Name "StlTools - Win32 Release_Unicode"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\STL\KDateStr.cpp

!IF  "$(CFG)" == "StlTools - Win32 Debug_SBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "StlTools - Win32 Debug_Unicode"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "StlTools - Win32 Release_SBCS"

!ELSEIF  "$(CFG)" == "StlTools - Win32 Release_Unicode"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\STL\KDbgLimits.cpp

!IF  "$(CFG)" == "StlTools - Win32 Debug_SBCS"

# PROP Exclude_From_Build 1
# SUBTRACT CPP /YX

!ELSEIF  "$(CFG)" == "StlTools - Win32 Debug_Unicode"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "StlTools - Win32 Release_SBCS"

!ELSEIF  "$(CFG)" == "StlTools - Win32 Release_Unicode"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\STL\KFileRead.cpp

!IF  "$(CFG)" == "StlTools - Win32 Debug_SBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "StlTools - Win32 Debug_Unicode"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "StlTools - Win32 Release_SBCS"

!ELSEIF  "$(CFG)" == "StlTools - Win32 Release_Unicode"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\STL\KGetFileExtn.cpp

!IF  "$(CFG)" == "StlTools - Win32 Debug_SBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "StlTools - Win32 Debug_Unicode"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "StlTools - Win32 Release_SBCS"

!ELSEIF  "$(CFG)" == "StlTools - Win32 Release_Unicode"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\STL\KGetFileName.cpp

!IF  "$(CFG)" == "StlTools - Win32 Debug_SBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "StlTools - Win32 Debug_Unicode"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "StlTools - Win32 Release_SBCS"

!ELSEIF  "$(CFG)" == "StlTools - Win32 Release_Unicode"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\STL\KGetLines.cpp

!IF  "$(CFG)" == "StlTools - Win32 Debug_SBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "StlTools - Win32 Debug_Unicode"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "StlTools - Win32 Release_SBCS"

!ELSEIF  "$(CFG)" == "StlTools - Win32 Release_Unicode"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\STL\KIntStream.cpp

!IF  "$(CFG)" == "StlTools - Win32 Debug_SBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "StlTools - Win32 Debug_Unicode"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "StlTools - Win32 Release_SBCS"

!ELSEIF  "$(CFG)" == "StlTools - Win32 Release_Unicode"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\STL\KSkipWSp.cpp

!IF  "$(CFG)" == "StlTools - Win32 Debug_SBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "StlTools - Win32 Debug_Unicode"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "StlTools - Win32 Release_SBCS"

!ELSEIF  "$(CFG)" == "StlTools - Win32 Release_Unicode"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\STL\KStrAtoWChar.cpp

!IF  "$(CFG)" == "StlTools - Win32 Debug_SBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "StlTools - Win32 Debug_Unicode"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "StlTools - Win32 Release_SBCS"

!ELSEIF  "$(CFG)" == "StlTools - Win32 Release_Unicode"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\STL\KStringStl.cpp

!IF  "$(CFG)" == "StlTools - Win32 Debug_SBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "StlTools - Win32 Debug_Unicode"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "StlTools - Win32 Release_SBCS"

!ELSEIF  "$(CFG)" == "StlTools - Win32 Release_Unicode"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\STL\KStrRplEOL.cpp
# End Source File
# Begin Source File

SOURCE=..\..\STL\KStrStream.cpp

!IF  "$(CFG)" == "StlTools - Win32 Debug_SBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "StlTools - Win32 Debug_Unicode"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "StlTools - Win32 Release_SBCS"

!ELSEIF  "$(CFG)" == "StlTools - Win32 Release_Unicode"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\STL\KStrUppr.cpp

!IF  "$(CFG)" == "StlTools - Win32 Debug_SBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "StlTools - Win32 Debug_Unicode"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "StlTools - Win32 Release_SBCS"

!ELSEIF  "$(CFG)" == "StlTools - Win32 Release_Unicode"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\STL\KStrWtoChar.cpp

!IF  "$(CFG)" == "StlTools - Win32 Debug_SBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "StlTools - Win32 Debug_Unicode"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "StlTools - Win32 Release_SBCS"

!ELSEIF  "$(CFG)" == "StlTools - Win32 Release_Unicode"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\KTestLog.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\main.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\stdstl.cpp
# ADD CPP /Yc"stdstl.h"
# End Source File
# Begin Source File

SOURCE=.\Src\TestCommonStlTools.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\TestStlStrings.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\Src\TsText.c
# End Source File
# Begin Source File

SOURCE=..\Common\Src\TsWriteTxt.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\STL\KBoolStream.h
# End Source File
# Begin Source File

SOURCE=..\..\STL\KDbgStlA.h
# End Source File
# Begin Source File

SOURCE=..\..\STL\KHexStream.h
# End Source File
# Begin Source File

SOURCE=..\..\STL\KOStream.h
# End Source File
# Begin Source File

SOURCE=..\..\KTestLog.h
# End Source File
# Begin Source File

SOURCE=..\..\STL\KTString.h
# End Source File
# Begin Source File

SOURCE=..\..\STL\KXmlAttributeVector.h
# End Source File
# Begin Source File

SOURCE=..\..\STL\KXmlElementVector.h
# End Source File
# Begin Source File

SOURCE=..\..\STL\KXmlTypeStl.h
# End Source File
# Begin Source File

SOURCE=.\Src\stdstl.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "Logs"

# PROP Default_Filter "*.log"
# Begin Source File

SOURCE=.\LibraryTest.log
# End Source File
# Begin Source File

SOURCE=.\LibraryTestUni.log
# End Source File
# End Group
# Begin Source File

SOURCE=.\StlTools.txt
# End Source File
# End Target
# End Project
