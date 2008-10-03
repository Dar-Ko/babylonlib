# Microsoft Developer Studio Project File - Name="Usb" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=Usb - Win32 Debug_SBCS
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Usb.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Usb.mak" CFG="Usb - Win32 Debug_SBCS"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Usb - Win32 Debug_Unicode" (based on "Win32 (x86) Console Application")
!MESSAGE "Usb - Win32 Debug_SBCS" (based on "Win32 (x86) Console Application")
!MESSAGE "Usb - Win32 Release_Unicode" (based on "Win32 (x86) Console Application")
!MESSAGE "Usb - Win32 Release_SBCS" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Usb - Win32 Debug_Unicode"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Usb___Win32_Debug_Unicode"
# PROP BASE Intermediate_Dir "Usb___Win32_Debug_Unicode"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\bin\Debug_Unicode\Win32"
# PROP Intermediate_Dir "..\Obj\Debug_Unicode\Usb\Win32"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W4 /Gm /GX /ZI /Od /I "..\Common\Src\Win\32" /I "..\Common\Src\Win" /I "..\.." /I "..\..\STL" /I "..\..\Win\32" /I "..\..\Platform" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_UNICODE" /D "UNICODE" /D "_USE_STL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x1009 /d "_DEBUG"
# ADD RSC /l 0x1009 /d "_DEBUG" /d "_UNICODE"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /version:1.1 /subsystem:console /debug /machine:I386 /pdbtype:sept /VERBOSE:LIB
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Usb - Win32 Debug_SBCS"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Usb___Win32_Debug_SBCS"
# PROP BASE Intermediate_Dir "Usb___Win32_Debug_SBCS"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\bin\Debug_SBCS\Win32"
# PROP Intermediate_Dir "..\Obj\Debug_SBCS\Usb\Win32"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W4 /Gm /GX /ZI /Od /I "..\Common\Src\Win" /I "..\.." /I "..\..\STL" /I "..\..\Win\32" /I "..\..\Platform" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_USE_STL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x1009 /d "_DEBUG"
# ADD RSC /l 0x1009 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /version:1.1 /subsystem:console /debug /machine:I386 /pdbtype:sept /VERBOSE:LIB
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Usb - Win32 Release_Unicode"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Usb___Win32_Release_Unicode"
# PROP BASE Intermediate_Dir "Usb___Win32_Release_Unicode"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\bin\Release_Unicode\Win32"
# PROP Intermediate_Dir "..\Obj\Release_Unicode\Usb\Win32"
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W4 /GX /O2 /I "..\Common\Src\Win\32" /I "..\Common\Src\Win" /I "..\.." /I "..\..\STL" /I "..\..\Win\32" /I "..\..\Platform" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_UNICODE" /D "UNICODE" /D "_USE_STL" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x1009 /d "NDEBUG"
# ADD RSC /l 0x1009 /d "NDEBUG" /d "_UNICODE"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /version:1.1 /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "Usb - Win32 Release_SBCS"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Usb___Win32_Release_SBCS"
# PROP BASE Intermediate_Dir "Usb___Win32_Release_SBCS"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\bin\Release_SBCS\Win32"
# PROP Intermediate_Dir "..\Obj\Release_SBCS\Usb\Win32"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
MTL=midl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W4 /GX /O2 /I "..\Common\Src\Win\32" /I "..\Common\Src\Win" /I "..\.." /I "..\..\STL" /I "..\..\Win\32" /I "..\..\Platform" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_USE_STL" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x1009 /d "NDEBUG"
# ADD RSC /l 0x1009 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /version:1.1 /subsystem:console /machine:I386 /nodefaultlib:"LIBC.LIB"

!ENDIF 

# Begin Target

# Name "Usb - Win32 Debug_Unicode"
# Name "Usb - Win32 Debug_SBCS"
# Name "Usb - Win32 Release_Unicode"
# Name "Usb - Win32 Release_SBCS"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\Win\32\KDbgRpt.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\KStrHtoL.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\KStrToInt.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\KTestLog.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\Win\32\KUsbHub.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\Win\32\KWinUsbHid.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Src\main.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\Src\Win\stdafx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\Common\Res\Win\32\Test.rc
# End Source File
# Begin Source File

SOURCE=.\Src\TestCommonUsb.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\TestFindUsbHid.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\Src\TsWriteTxt.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\KTestLog.h
# End Source File
# Begin Source File

SOURCE=..\..\KUsb.h
# End Source File
# Begin Source File

SOURCE=..\..\Win\32\KUsbHid.h
# End Source File
# Begin Source File

SOURCE=..\..\Win\32\KUsbHub.h
# End Source File
# Begin Source File

SOURCE=..\..\Win\32\KWinUsb.h
# End Source File
# Begin Source File

SOURCE=..\Common\Src\Win\stdafx.h
# End Source File
# Begin Source File

SOURCE=..\..\Platform\UsbVid.h
# End Source File
# Begin Source File

SOURCE=..\..\Platform\UsbVid0000.h
# End Source File
# Begin Source File

SOURCE=..\..\Platform\UsbVid046D.h
# End Source File
# Begin Source File

SOURCE=..\..\Platform\UsbVid04B4.h
# End Source File
# Begin Source File

SOURCE=..\..\Platform\UsbVid04CF.h
# End Source File
# Begin Source File

SOURCE=..\..\Platform\UsbVid05E0.h
# End Source File
# Begin Source File

SOURCE=..\..\Platform\UsbVid078B.h
# End Source File
# Begin Source File

SOURCE=..\..\Platform\UsbVid0801.h
# End Source File
# Begin Source File

SOURCE=..\..\Platform\UsbVid0839.h
# End Source File
# Begin Source File

SOURCE=..\..\Platform\UsbVid0AA7.h
# End Source File
# Begin Source File

SOURCE=..\..\Platform\UsbVid0ACD.h
# End Source File
# Begin Source File

SOURCE=..\..\Platform\UsbVid0D85.h
# End Source File
# Begin Source File

SOURCE=..\..\Platform\UsbVid0DD4.h
# End Source File
# Begin Source File

SOURCE=..\..\Platform\UsbVid152D.h
# End Source File
# Begin Source File

SOURCE=..\..\Platform\UsbVid413C.h
# End Source File
# Begin Source File

SOURCE=..\..\Platform\UsbVid8086.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\..\..\..\Doc\Res\icoUsb.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\Usb.txt
# End Source File
# End Target
# End Project
