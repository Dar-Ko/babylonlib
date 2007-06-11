# Microsoft Developer Studio Project File - Name="Complex" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=Complex - Win32 Debug_Unicode_MFC
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Complex.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Complex.mak" CFG="Complex - Win32 Debug_Unicode_MFC"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Complex - Win32 Release_SBCS" (based on "Win32 (x86) Console Application")
!MESSAGE "Complex - Win32 Debug_SBCS" (based on "Win32 (x86) Console Application")
!MESSAGE "Complex - Win32 Debug_Unicode" (based on "Win32 (x86) Console Application")
!MESSAGE "Complex - Win32 Release_Unicode" (based on "Win32 (x86) Console Application")
!MESSAGE "Complex - Win32 Debug_SBCS_MFC" (based on "Win32 (x86) Console Application")
!MESSAGE "Complex - Win32 Release_SBCS_MFC" (based on "Win32 (x86) Console Application")
!MESSAGE "Complex - Win32 Debug_Unicode_MFC" (based on "Win32 (x86) Console Application")
!MESSAGE "Complex - Win32 Release_Unicode_MFC" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "Complex"
# PROP Scc_LocalPath "..\.."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Complex - Win32 Release_SBCS"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\bin\Release_SBCS\Win32"
# PROP Intermediate_Dir "..\Obj\Release_SBCS\Complex\Win32"
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\.." /I "..\..\STL" /I "..\Common\Src\Win" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_STL" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x1009 /d "NDEBUG"
# ADD RSC /l 0x1009 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_SBCS"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\bin\Debug_SBCS\Win32"
# PROP Intermediate_Dir "..\Obj\Debug_SBCS\Complex\Win32"
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\.." /I "..\..\STL" /I "..\Common\Src\Win" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_STL" /FR /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x1009 /d "_DEBUG"
# ADD RSC /l 0x1009 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_Unicode"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Complex___Win32_Debug_Unicode"
# PROP BASE Intermediate_Dir "Complex___Win32_Debug_Unicode"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\bin\Debug_Unicode\Win32"
# PROP Intermediate_Dir "..\Obj\Debug_Unicode\Complex\Win32"
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /I "../.." /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\.." /I "..\..\STL" /I "..\Common\Src\Win" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_UNICODE" /D "_STL" /FR /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x1009 /d "_DEBUG"
# ADD RSC /l 0x1009 /d "_DEBUG" /d "_UNICODE"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "Complex - Win32 Release_Unicode"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Complex___Win32_Release_Unicode"
# PROP BASE Intermediate_Dir "Complex___Win32_Release_Unicode"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\bin\Release_Unicode\Win32"
# PROP Intermediate_Dir "..\Obj\Release_Unicode\Complex\Win32"
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\.." /I "..\..\STL" /I "..\Common\Src\Win" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_UNICODE" /D "_STL" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x1009 /d "NDEBUG"
# ADD RSC /l 0x1009 /d "NDEBUG" /d "_UNICODE"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_SBCS_MFC"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Complex___Win32_Debug_SBCS_MFC"
# PROP BASE Intermediate_Dir "Complex___Win32_Debug_SBCS_MFC"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\bin\Debug_SBCS_MFC\Win32"
# PROP Intermediate_Dir "..\Obj\Debug_SBCS_MFC\Complex\Win32"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\.." /I "..\..\STL" /I "..\Common\Src\Win" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_STL" /FR /FD /GZ /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\.." /I "..\..\STL" /I "..\Common\Src\Win" /I "..\Common\Src\Win\32" /I "..\Common\Res\Win" /D "WIN32" /D "_DEBUG" /D "NCONSOLE" /D "_STL" /D "_AFXDLL" /FR /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x1009 /d "_DEBUG"
# ADD RSC /l 0x1009 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "Complex - Win32 Release_SBCS_MFC"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Complex___Win32_Release_SBCS_MFC"
# PROP BASE Intermediate_Dir "Complex___Win32_Release_SBCS_MFC"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\bin\Release_SBCS_MFC\Win32"
# PROP Intermediate_Dir "..\Obj\Release_SBCS_MFC\Complex\Win32"
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /I "..\.." /I "..\..\STL" /I "..\Common\Src\Win" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_STL" /FD /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\.." /I "..\..\STL" /I "..\Common\Src\Win" /I "..\Common\Src\Win\32" /I "..\Common\Res\Win" /D "WIN32" /D "NDEBUG" /D "NCONSOLE" /D "_STL" /D "_AFXDLL" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x1009 /d "NDEBUG"
# ADD RSC /l 0x1009 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_Unicode_MFC"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Complex___Win32_Debug_Unicode_MFC"
# PROP BASE Intermediate_Dir "Complex___Win32_Debug_Unicode_MFC"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\bin\Debug_Unicode_MFC\Win32"
# PROP Intermediate_Dir "..\Obj\Debug_Unicode_MFC\Complex\Win32"
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\.." /I "..\..\STL" /I "..\Common\Src\Win" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_UNICODE" /D "_STL" /FR /FD /GZ /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\.." /I "..\..\STL" /I "..\Common\Src\Win" /I "..\Common\Src\Win\32" /I "..\Common\Res\Win" /D "WIN32" /D "_DEBUG" /D "NCONSOLE" /D "_UNICODE" /D "_STL" /D "_AFXDLL" /FR /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x1009 /d "_DEBUG" /d "_UNICODE"
# ADD RSC /l 0x1009 /d "_DEBUG" /d "_UNICODE" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "Complex - Win32 Release_Unicode_MFC"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Complex___Win32_Release_Unicode_MFC"
# PROP BASE Intermediate_Dir "Complex___Win32_Release_Unicode_MFC"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\bin\Release_Unicode_MFC\Win32"
# PROP Intermediate_Dir "..\Obj\Debug_Unicode_MFC\Complex\Win32"
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /I "..\.." /I "..\..\STL" /I "..\Common\Src\Win" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_UNICODE" /D "_STL" /FD /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\.." /I "..\..\STL" /I "..\Common\Src\Win" /I "..\Common\Src\Win\32" /I "..\Common\Res\Win" /D "WIN32" /D "NDEBUG" /D "NCONSOLE" /D "_UNICODE" /D "_STL" /D "_AFXDLL" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x1009 /d "NDEBUG" /d "_UNICODE"
# ADD RSC /l 0x1009 /d "NDEBUG" /d "_UNICODE" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 /nologo /subsystem:console /machine:I386

!ENDIF 

# Begin Target

# Name "Complex - Win32 Release_SBCS"
# Name "Complex - Win32 Debug_SBCS"
# Name "Complex - Win32 Debug_Unicode"
# Name "Complex - Win32 Release_Unicode"
# Name "Complex - Win32 Debug_SBCS_MFC"
# Name "Complex - Win32 Release_SBCS_MFC"
# Name "Complex - Win32 Debug_Unicode_MFC"
# Name "Complex - Win32 Release_Unicode_MFC"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;for;f90"
# Begin Source File

SOURCE=..\..\KDtoA.c

!IF  "$(CFG)" == "Complex - Win32 Release_SBCS"

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_SBCS"

# ADD CPP /D "NUSE_STD_HEADERS"

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_Unicode"

!ELSEIF  "$(CFG)" == "Complex - Win32 Release_Unicode"

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_SBCS_MFC"

# ADD BASE CPP /D "NUSE_STD_HEADERS"
# ADD CPP /D "NUSE_STD_HEADERS"

!ELSEIF  "$(CFG)" == "Complex - Win32 Release_SBCS_MFC"

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_Unicode_MFC"

!ELSEIF  "$(CFG)" == "Complex - Win32 Release_Unicode_MFC"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\KMatAcosC.cpp
# End Source File
# Begin Source File

SOURCE=..\..\KTestLog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\KZLineIn.cpp
# End Source File
# Begin Source File

SOURCE=..\..\KZtoA.cpp

!IF  "$(CFG)" == "Complex - Win32 Release_SBCS"

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_SBCS"

# ADD CPP /D "NUSE_STD_HEADERS"

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_Unicode"

!ELSEIF  "$(CFG)" == "Complex - Win32 Release_Unicode"

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_SBCS_MFC"

# ADD BASE CPP /D "NUSE_STD_HEADERS"
# ADD CPP /D "NUSE_STD_HEADERS"

!ELSEIF  "$(CFG)" == "Complex - Win32 Release_SBCS_MFC"

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_Unicode_MFC"

!ELSEIF  "$(CFG)" == "Complex - Win32 Release_Unicode_MFC"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Src\main.cpp

!IF  "$(CFG)" == "Complex - Win32 Release_SBCS"

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_SBCS"

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_Unicode"

!ELSEIF  "$(CFG)" == "Complex - Win32 Release_Unicode"

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_SBCS_MFC"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Complex - Win32 Release_SBCS_MFC"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_Unicode_MFC"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Complex - Win32 Release_Unicode_MFC"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Src\TestCommonComplex.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\TestComplex.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\TestComplexBase.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\TestComplexToA.cpp
# End Source File
# Begin Source File

SOURCE=..\Numeric\Src\TestNaN.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\Src\Win\32\TsMfcAbout.cpp

!IF  "$(CFG)" == "Complex - Win32 Release_SBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_SBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_Unicode"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Complex - Win32 Release_Unicode"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_SBCS_MFC"

!ELSEIF  "$(CFG)" == "Complex - Win32 Release_SBCS_MFC"

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_Unicode_MFC"

!ELSEIF  "$(CFG)" == "Complex - Win32 Release_Unicode_MFC"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Common\Src\Win\32\TsMfcApp.cpp

!IF  "$(CFG)" == "Complex - Win32 Release_SBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_SBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_Unicode"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Complex - Win32 Release_Unicode"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_SBCS_MFC"

!ELSEIF  "$(CFG)" == "Complex - Win32 Release_SBCS_MFC"

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_Unicode_MFC"

!ELSEIF  "$(CFG)" == "Complex - Win32 Release_Unicode_MFC"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Common\Src\Win\32\TsMfcDoc.cpp

!IF  "$(CFG)" == "Complex - Win32 Release_SBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_SBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_Unicode"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Complex - Win32 Release_Unicode"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_SBCS_MFC"

!ELSEIF  "$(CFG)" == "Complex - Win32 Release_SBCS_MFC"

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_Unicode_MFC"

!ELSEIF  "$(CFG)" == "Complex - Win32 Release_Unicode_MFC"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Common\Src\Win\32\TsMfcFrame.cpp

!IF  "$(CFG)" == "Complex - Win32 Release_SBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_SBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_Unicode"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Complex - Win32 Release_Unicode"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_SBCS_MFC"

!ELSEIF  "$(CFG)" == "Complex - Win32 Release_SBCS_MFC"

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_Unicode_MFC"

!ELSEIF  "$(CFG)" == "Complex - Win32 Release_Unicode_MFC"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Common\Src\Win\32\TsMfcView.cpp

!IF  "$(CFG)" == "Complex - Win32 Release_SBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_SBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_Unicode"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Complex - Win32 Release_Unicode"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_SBCS_MFC"

!ELSEIF  "$(CFG)" == "Complex - Win32 Release_SBCS_MFC"

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_Unicode_MFC"

!ELSEIF  "$(CFG)" == "Complex - Win32 Release_Unicode_MFC"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=..\..\KComplex.h
# End Source File
# Begin Source File

SOURCE=..\..\KComplxB.h
# End Source File
# Begin Source File

SOURCE=..\..\KGaussianInt.h
# End Source File
# Begin Source File

SOURCE=..\..\KMathCst.h
# End Source File
# Begin Source File

SOURCE=..\..\KMathCst.inl
# End Source File
# Begin Source File

SOURCE=..\..\KProgCst.inl
# End Source File
# Begin Source File

SOURCE=..\Common\Src\Win\stdafx.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\Res\Win\32\Test.rc
# End Source File
# Begin Source File

SOURCE=.\Src\TestComplex.h
# End Source File
# Begin Source File

SOURCE=.\Src\TestZAssert.h
# End Source File
# Begin Source File

SOURCE=..\Common\Src\Win\32\TsMfcAbout.h

!IF  "$(CFG)" == "Complex - Win32 Release_SBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_SBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_Unicode"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Complex - Win32 Release_Unicode"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_SBCS_MFC"

!ELSEIF  "$(CFG)" == "Complex - Win32 Release_SBCS_MFC"

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_Unicode_MFC"

!ELSEIF  "$(CFG)" == "Complex - Win32 Release_Unicode_MFC"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Common\Src\Win\32\TsMfcApp.h

!IF  "$(CFG)" == "Complex - Win32 Release_SBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_SBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_Unicode"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Complex - Win32 Release_Unicode"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_SBCS_MFC"

!ELSEIF  "$(CFG)" == "Complex - Win32 Release_SBCS_MFC"

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_Unicode_MFC"

!ELSEIF  "$(CFG)" == "Complex - Win32 Release_Unicode_MFC"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Common\Src\Win\32\TsMfcDoc.h

!IF  "$(CFG)" == "Complex - Win32 Release_SBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_SBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_Unicode"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Complex - Win32 Release_Unicode"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_SBCS_MFC"

!ELSEIF  "$(CFG)" == "Complex - Win32 Release_SBCS_MFC"

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_Unicode_MFC"

!ELSEIF  "$(CFG)" == "Complex - Win32 Release_Unicode_MFC"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Common\Src\Win\32\TsMfcFrame.h

!IF  "$(CFG)" == "Complex - Win32 Release_SBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_SBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_Unicode"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Complex - Win32 Release_Unicode"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_SBCS_MFC"

!ELSEIF  "$(CFG)" == "Complex - Win32 Release_SBCS_MFC"

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_Unicode_MFC"

!ELSEIF  "$(CFG)" == "Complex - Win32 Release_Unicode_MFC"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Common\Res\Win\TsMfcRes.h

!IF  "$(CFG)" == "Complex - Win32 Release_SBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_SBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_Unicode"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Complex - Win32 Release_Unicode"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_SBCS_MFC"

!ELSEIF  "$(CFG)" == "Complex - Win32 Release_SBCS_MFC"

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_Unicode_MFC"

!ELSEIF  "$(CFG)" == "Complex - Win32 Release_Unicode_MFC"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Common\Src\Win\32\TsMfcView.h

!IF  "$(CFG)" == "Complex - Win32 Release_SBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_SBCS"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_Unicode"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Complex - Win32 Release_Unicode"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_SBCS_MFC"

!ELSEIF  "$(CFG)" == "Complex - Win32 Release_SBCS_MFC"

!ELSEIF  "$(CFG)" == "Complex - Win32 Debug_Unicode_MFC"

!ELSEIF  "$(CFG)" == "Complex - Win32 Release_Unicode_MFC"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Common\Src\TsWriteTxt.cpp
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
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
# End Target
# End Project
