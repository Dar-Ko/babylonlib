# Microsoft Developer Studio Project File - Name="Numeric" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=Numeric - Win32 Debug_SBCS
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Numeric.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Numeric.mak" CFG="Numeric - Win32 Debug_SBCS"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Numeric - Win32 Debug_SBCS" (based on "Win32 (x86) Console Application")
!MESSAGE "Numeric - Win32 Release_SBCS" (based on "Win32 (x86) Console Application")
!MESSAGE "Numeric - Win32 Debug_Unicode" (based on "Win32 (x86) Console Application")
!MESSAGE "Numeric - Win32 Release_Unicode" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 1
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Numeric - Win32 Debug_SBCS"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Numeric___Win32_Debug_SBCS"
# PROP BASE Intermediate_Dir "Numeric___Win32_Debug_SBCS"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\bin\Debug_SBCS\Win32"
# PROP Intermediate_Dir "..\Obj\Debug_SBCS\Numeric\Win32"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\.." /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /FD /GZ /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\.." /I "..\..\STL" /I "..\Common\Src\Win" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_STL" /FR /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x1009 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "Numeric - Win32 Release_SBCS"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Numeric___Win32_Release_SBCS"
# PROP BASE Intermediate_Dir "Numeric___Win32_Release_SBCS"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\bin\Release_SBCS\Win32"
# PROP Intermediate_Dir "..\Obj\Release_SBCS\Numeric\Win32"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /I "..\.." /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\.." /I "..\..\STL" /I "..\Common\Src\Win" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_STL" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x1009 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "Numeric - Win32 Debug_Unicode"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Numeric___Win32_Debug_Unicode"
# PROP BASE Intermediate_Dir "Numeric___Win32_Debug_Unicode"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\bin\Debug_Unicode\Win32"
# PROP Intermediate_Dir "..\Obj\Debug_Unicode\Numeric\Win32"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\.." /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /FD /GZ /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\.." /I "..\..\STL" /I "..\Common\Src\Win" /D "_DEBUG" /D "_UNICODE" /D "WIN32" /D "_CONSOLE" /D "_STL" /FR /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x1009 /d "_DEBUG" /d "_UNICODE"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "Numeric - Win32 Release_Unicode"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Numeric___Win32_Release_Unicode"
# PROP BASE Intermediate_Dir "Numeric___Win32_Release_Unicode"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\bin\Release_Unicode\Win32"
# PROP Intermediate_Dir "..\Obj\Release_Unicode\Numeric\Win32"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /I "..\.." /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\.." /I "..\..\STL" /I "..\Common\Src\Win" /D "NDEBUG" /D "_UNICODE" /D "WIN32" /D "_CONSOLE" /D "_STL" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x1009 /d "NDEBUG" /d "_UNICODE"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 /nologo /subsystem:console /machine:I386

!ENDIF 

# Begin Target

# Name "Numeric - Win32 Debug_SBCS"
# Name "Numeric - Win32 Release_SBCS"
# Name "Numeric - Win32 Debug_Unicode"
# Name "Numeric - Win32 Release_Unicode"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\KfFibonacci.cpp
# End Source File
# Begin Source File

SOURCE=..\..\KfNewtRp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\KfQuadEq.cpp
# End Source File
# Begin Source File

SOURCE=..\..\KIsPrimeNo.cpp

!IF  "$(CFG)" == "Numeric - Win32 Debug_SBCS"

# ADD BASE CPP /D "_DEBUG_TEST"
# ADD CPP /D "_DEBUG_TEST"

!ELSEIF  "$(CFG)" == "Numeric - Win32 Release_SBCS"

!ELSEIF  "$(CFG)" == "Numeric - Win32 Debug_Unicode"

# ADD BASE CPP /D "_DEBUG_TEST"
# ADD CPP /D "_DEBUG_TEST"

!ELSEIF  "$(CFG)" == "Numeric - Win32 Release_Unicode"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\KTestLog.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\main.cpp
# End Source File
# Begin Source File

SOURCE=S:\_SrcPool\Cpp\Samples\Common\Res\Win\32\Test.rc

!IF  "$(CFG)" == "Numeric - Win32 Debug_SBCS"

!ELSEIF  "$(CFG)" == "Numeric - Win32 Release_SBCS"

!ELSEIF  "$(CFG)" == "Numeric - Win32 Debug_Unicode"

!ELSEIF  "$(CFG)" == "Numeric - Win32 Release_Unicode"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Src\TestCommonNumeric.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\TestEndian.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\TestFibonnaci.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\TestNetByteOrder.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\TestNewtonRaphson.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\TestPrimes.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\TestRound.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\TestSwap.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\TestSwapRows.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\Src\TsWriteTxt.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\KMathCst.h
# End Source File
# Begin Source File

SOURCE=..\..\KMathCst.inl
# End Source File
# Begin Source File

SOURCE=..\..\KNetByte.h
# End Source File
# Begin Source File

SOURCE=..\..\KProgCst.h
# End Source File
# Begin Source File

SOURCE=..\..\KProgCst.inl
# End Source File
# Begin Source File

SOURCE=..\..\KSwpByte.h
# End Source File
# Begin Source File

SOURCE=..\..\KSwpByteOrder.h
# End Source File
# Begin Source File

SOURCE=..\..\KSwpElements.h
# End Source File
# Begin Source File

SOURCE=..\..\KSwpRows.h
# End Source File
# Begin Source File

SOURCE=..\..\KTrace.h
# End Source File
# Begin Source File

SOURCE=..\..\KTypedef.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "Logs"

# PROP Default_Filter "*.log"
# Begin Source File

SOURCE=S:\_SrcPool\Cpp\Samples\Numeric\LibraryTest.log
# End Source File
# Begin Source File

SOURCE=.\LibraryTestUni.log
# End Source File
# End Group
# End Target
# End Project
