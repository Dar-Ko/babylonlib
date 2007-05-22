# Microsoft Developer Studio Project File - Name="_LibraryTest" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=_LibraryTest - Win32 Debug_Unicode
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "_LibraryTest.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "_LibraryTest.mak" CFG="_LibraryTest - Win32 Debug_Unicode"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "_LibraryTest - Win32 Debug_SBCS" (based on "Win32 (x86) Console Application")
!MESSAGE "_LibraryTest - Win32 Debug_Unicode" (based on "Win32 (x86) Console Application")
!MESSAGE "_LibraryTest - Win32 Release_SBCS" (based on "Win32 (x86) Console Application")
!MESSAGE "_LibraryTest - Win32 Release_Unicode" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "_LibraryTest"
# PROP Scc_LocalPath "..\.."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "_LibraryTest - Win32 Debug_SBCS"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug_SBCS"
# PROP BASE Intermediate_Dir "Debug_SBCS"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\bin\Debug_SBCS\Win32"
# PROP Intermediate_Dir "..\Obj\Debug_SBCS\_LibraryTest\Win32"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\.." /I "..\Common\Src\Win" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_STL" /FR /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x1009 /d "_DEBUG"
# ADD RSC /l 0x1009 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "_LibraryTest - Win32 Debug_Unicode"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug_Unicode"
# PROP BASE Intermediate_Dir "Debug_Unicode"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\bin\Debug_Unicode\Win32"
# PROP Intermediate_Dir "..\Obj\Debug_Unicode\_LibraryTest\Win32"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\.." /I "..\Common\Src\Win" /D "_DEBUG" /D "_UNICODE" /D "WIN32" /D "_CONSOLE" /D "_STL" /FR /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x1009 /d "_DEBUG"
# ADD RSC /l 0x1009 /d "_DEBUG" /d "_UNICODE"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "_LibraryTest - Win32 Release_SBCS"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release_SBCS"
# PROP BASE Intermediate_Dir "Release_SBCS"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\bin\Release_SBCS\Win32"
# PROP Intermediate_Dir "..\Obj\Release_SBCS\_LibraryTest\Win32"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\.." /I "..\Common\Src\Win" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_STL" /FR /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x1009 /d "NDEBUG"
# ADD RSC /l 0x1009 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "_LibraryTest - Win32 Release_Unicode"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release_Unicode"
# PROP BASE Intermediate_Dir "Release_Unicode"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\bin\Release_Unicode\Win32"
# PROP Intermediate_Dir "..\Obj\Release_Unicode\_LibraryTest\Win32"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\.." /I "..\Common\Src\Win" /D "NDEBUG" /D "_UNICODE" /D "WIN32" /D "_CONSOLE" /D "_STL" /FR /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x1009 /d "NDEBUG"
# ADD RSC /l 0x1009 /d "NDEBUG" /d "_UNICODE"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ENDIF 

# Begin Target

# Name "_LibraryTest - Win32 Debug_SBCS"
# Name "_LibraryTest - Win32 Debug_Unicode"
# Name "_LibraryTest - Win32 Release_SBCS"
# Name "_LibraryTest - Win32 Release_Unicode"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\KDate.cpp
# End Source File
# Begin Source File

SOURCE=..\..\KDateConv.cpp
# End Source File
# Begin Source File

SOURCE=..\..\KDateCst.c
# End Source File
# Begin Source File

SOURCE=..\..\Win\32\KDateTime.cpp
# End Source File
# Begin Source File

SOURCE=..\..\KDateTm.c
# End Source File
# Begin Source File

SOURCE=..\..\KfNewtRp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\KfQuadEq.cpp
# End Source File
# Begin Source File

SOURCE=..\..\STL\KGetLines.cpp
# End Source File
# Begin Source File

SOURCE=..\..\KIsPrimeNo.cpp

!IF  "$(CFG)" == "_LibraryTest - Win32 Debug_SBCS"

# ADD CPP /D "_DEBUG_TEST"

!ELSEIF  "$(CFG)" == "_LibraryTest - Win32 Debug_Unicode"

# ADD CPP /D "_DEBUG_TEST"

!ELSEIF  "$(CFG)" == "_LibraryTest - Win32 Release_SBCS"

!ELSEIF  "$(CFG)" == "_LibraryTest - Win32 Release_Unicode"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\KRandomGauss.cpp
# End Source File
# Begin Source File

SOURCE=..\..\KRandomUniform.cpp
# End Source File
# Begin Source File

SOURCE=..\..\KStrAtoI.cpp
# End Source File
# Begin Source File

SOURCE=..\..\KStringHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\KStrPalindrome.cpp
# End Source File
# Begin Source File

SOURCE=..\..\STL\KStrWtoChar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\KTestLog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Win\32\KXmlProcessorSax.cpp
# ADD CPP /I "..\..\Win\WTL\include"
# End Source File
# Begin Source File

SOURCE=..\..\Win\32\KXmlSaxErrorHandler.cpp
# ADD CPP /I "..\..\Win\WTL\include"
# End Source File
# Begin Source File

SOURCE=.\Src\main.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\Src\Win\stdafx.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\Res\Win\32\Test.rc
# End Source File
# Begin Source File

SOURCE=..\Assert\Src\TestAssert.cpp
# End Source File
# Begin Source File

SOURCE=..\Assert\Src\TestAssertC.c
# End Source File
# Begin Source File

SOURCE=..\DateTime\Src\TestAtoI.cpp
# End Source File
# Begin Source File

SOURCE=..\Assert\Src\TestCommonAssert.cpp
# End Source File
# Begin Source File

SOURCE=..\Console\Src\TestCommonConsole.cpp
# End Source File
# Begin Source File

SOURCE=..\DateTime\Src\TestCommonDateTime.cpp
# End Source File
# Begin Source File

SOURCE=..\HtmlIO\Src\TestCommonHtmlIO.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\TestCommonLibrary.cpp
# End Source File
# Begin Source File

SOURCE=..\Numeric\Src\TestCommonNumeric.cpp
# End Source File
# Begin Source File

SOURCE=..\Random\Src\TestCommonRandom.cpp
# End Source File
# Begin Source File

SOURCE=..\StdLib\Src\TestCommonStdLib.c
# End Source File
# Begin Source File

SOURCE=..\StreamIO\Src\TestCommonStreamIO.cpp
# End Source File
# Begin Source File

SOURCE=..\StringDyn\Src\TestCommonStringDyn.cpp
# End Source File
# Begin Source File

SOURCE=..\Utilities\Src\TestCommonUtilities.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=..\DateTime\Src\TestDate.cpp
# End Source File
# Begin Source File

SOURCE=..\DateTime\Src\TestDateConversion.cpp
# End Source File
# Begin Source File

SOURCE=..\Numeric\Src\TestEndian.cpp
# End Source File
# Begin Source File

SOURCE=..\StreamIO\Src\TestGetLines.cpp
# End Source File
# Begin Source File

SOURCE=..\StringDyn\Src\TestIsPalindrome.cpp
# End Source File
# Begin Source File

SOURCE=..\DateTime\Src\TestLeapYear.cpp
# End Source File
# Begin Source File

SOURCE=..\HtmlIO\Src\Win\32\TestMsSaxParser.cpp
# ADD CPP /I "..\..\Win\32" /I "..\..\Win\WTL\include"
# End Source File
# Begin Source File

SOURCE=..\Numeric\Src\TestNetByteOrder.cpp
# End Source File
# Begin Source File

SOURCE=..\Numeric\Src\TestNewtonRaphson.cpp
# End Source File
# Begin Source File

SOURCE=..\Assert\Src\TestPredefinedMacros.cpp
# End Source File
# Begin Source File

SOURCE=..\Assert\Src\TestPredefinedMacrosC.c
# End Source File
# Begin Source File

SOURCE=..\Numeric\Src\TestPrimes.cpp
# End Source File
# Begin Source File

SOURCE=..\Random\Src\TestRandomCongr.cpp
# End Source File
# Begin Source File

SOURCE=..\Random\Src\TestRandomGauss.cpp
# End Source File
# Begin Source File

SOURCE=..\Random\Src\TestRandomNo.cpp
# End Source File
# Begin Source File

SOURCE=..\Random\Src\TestRandomUniform.cpp
# End Source File
# Begin Source File

SOURCE=..\Numeric\Src\TestRound.cpp
# End Source File
# Begin Source File

SOURCE=..\StringDyn\Src\TestStringHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\Numeric\Src\TestSwap.cpp
# End Source File
# Begin Source File

SOURCE=..\Numeric\Src\TestSwapRows.cpp
# End Source File
# Begin Source File

SOURCE=..\Assert\Src\TestTrace.cpp
# End Source File
# Begin Source File

SOURCE=..\Assert\Src\TestTraceC.c
# End Source File
# Begin Source File

SOURCE=..\HtmlIO\Src\TestXmlParser.cpp
# End Source File
# Begin Source File

SOURCE=..\HtmlIO\Src\TestXmlString.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\Src\TsWriteTxt.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\Common\Src\Win\stdafx.h
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
# End Group
# Begin Source File

SOURCE=.\_LibraryTest.txt
# End Source File
# Begin Source File

SOURCE=..\..\Documentation\KCopyright.htm
# End Source File
# Begin Source File

SOURCE=..\..\Documentation\KDirTree.htm
# End Source File
# Begin Source File

SOURCE=..\Common\Src\Win\32\ReadMe.txt
# End Source File
# End Target
# End Project
