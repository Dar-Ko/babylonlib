# Microsoft Developer Studio Project File - Name="TestStatic" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=TestStatic - Win32 Debug_SBCS_MFC
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TestStatic.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TestStatic.mak" CFG="TestStatic - Win32 Debug_SBCS_MFC"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TestStatic - Win32 Debug_Unicode_MFC" (based on "Win32 (x86) Application")
!MESSAGE "TestStatic - Win32 Debug_SBCS_MFC" (based on "Win32 (x86) Application")
!MESSAGE "TestStatic - Win32 Release_Unicode_MFC" (based on "Win32 (x86) Application")
!MESSAGE "TestStatic - Win32 Release_SBCS_MFC" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TestStatic - Win32 Debug_Unicode_MFC"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug_Unicode_MFC"
# PROP BASE Intermediate_Dir "Debug_Unicode_MFC"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\bin\Debug_Unicode_MFC\Win32"
# PROP Intermediate_Dir "..\Obj\Debug_Unicode_MFC\TestStatic\Win32"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "../Res" /I "../../../Win/32./Src" /I "./Res" /I "../../.." /I "../../Win/32" /I "../../../Win/32" /I "./Src" /I "../Generic/Src" /I "../Generic" /D "_DEBUG" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "_USE_MFC" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x1009 /d "_DEBUG"
# ADD RSC /l 0x1009 /i "../Generic/Res" /i "Res" /i ".." /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "TestStatic - Win32 Debug_SBCS_MFC"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug_SBCS_MFC"
# PROP BASE Intermediate_Dir "Debug_SBCS_MFC"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\bin\Debug_SBCS_MFC\Win32"
# PROP Intermediate_Dir "..\Obj\Debug_SBCS_MFC\TestStatic\Win32"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "../Res" /I "../../../Win/32./Src" /I "./Res" /I "../../.." /I "../../Win/32" /I "../../../Win/32" /I "./Src" /I "../Generic/Src" /I "../Generic" /D "_DEBUG" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "_USE_MFC" /FR /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x1009 /d "_DEBUG"
# ADD RSC /l 0x1009 /i "../Generic/Res" /i "Res" /i ".." /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "TestStatic - Win32 Release_Unicode_MFC"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release_Unicode_MFC"
# PROP BASE Intermediate_Dir "Release_Unicode_MFC"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\bin\Release_Unicode_MFC\Win32"
# PROP Intermediate_Dir "..\Obj\Release_Unicode_MFC\TestStatic\Win32"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "../Res" /I "../Generic" /I "../../../Win/32./Src" /I "./Res" /I "../../.." /I "../../Win/32" /I "../../../Win/32" /I "./Src" /I "../Generic/Src" /D "NDEBUG" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "_USE_MFC" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x1009 /d "NDEBUG"
# ADD RSC /l 0x1009 /i "../Generic/Res" /i "Res" /i ".." /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "TestStatic - Win32 Release_SBCS_MFC"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release_SBCS_MFC"
# PROP BASE Intermediate_Dir "Release_SBCS_MFC"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\bin\Release_SBCS_MFC\Win32"
# PROP Intermediate_Dir "..\Obj\Release_SBCS_MFC\TestStatic\Win32"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "../Res" /I "../../../Win/32./Src" /I "./Res" /I "../../.." /I "../../Win/32" /I "../../../Win/32" /I "./Src" /I "../Generic/Src" /I "../Generic" /D "NDEBUG" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "_USE_MFC" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x1009 /d "NDEBUG"
# ADD RSC /l 0x1009 /i "../Generic/Res" /i "Res" /i ".." /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ENDIF 

# Begin Target

# Name "TestStatic - Win32 Debug_Unicode_MFC"
# Name "TestStatic - Win32 Debug_SBCS_MFC"
# Name "TestStatic - Win32 Release_Unicode_MFC"
# Name "TestStatic - Win32 Release_SBCS_MFC"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\32\KHypLink.cpp
# End Source File
# Begin Source File

SOURCE=..\..\32\KIsRASCo.cpp

!IF  "$(CFG)" == "TestStatic - Win32 Debug_Unicode_MFC"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "TestStatic - Win32 Debug_SBCS_MFC"

!ELSEIF  "$(CFG)" == "TestStatic - Win32 Release_Unicode_MFC"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "TestStatic - Win32 Release_SBCS_MFC"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\32\KRegExt.cpp
# End Source File
# Begin Source File

SOURCE=..\..\32\KRegKey.cpp

!IF  "$(CFG)" == "TestStatic - Win32 Debug_Unicode_MFC"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "TestStatic - Win32 Debug_SBCS_MFC"

!ELSEIF  "$(CFG)" == "TestStatic - Win32 Release_Unicode_MFC"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "TestStatic - Win32 Release_SBCS_MFC"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\32\KSpwnURL.cpp

!IF  "$(CFG)" == "TestStatic - Win32 Debug_Unicode_MFC"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "TestStatic - Win32 Debug_SBCS_MFC"

!ELSEIF  "$(CFG)" == "TestStatic - Win32 Release_Unicode_MFC"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "TestStatic - Win32 Release_SBCS_MFC"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\32\KStaticEx.cpp
# End Source File
# Begin Source File

SOURCE=..\..\32\stdafx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\Generic\Src\TestAboutDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\Generic\Src\TestDialogApp.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\TestStaticApp.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\TestStaticDlg.cpp

!IF  "$(CFG)" == "TestStatic - Win32 Debug_Unicode_MFC"

!ELSEIF  "$(CFG)" == "TestStatic - Win32 Debug_SBCS_MFC"

# ADD CPP /I "S:\_SrcPool\Cpp\Win\32" /YX"stdafx.h"
# SUBTRACT CPP /I "../../Win/32"

!ELSEIF  "$(CFG)" == "TestStatic - Win32 Release_Unicode_MFC"

!ELSEIF  "$(CFG)" == "TestStatic - Win32 Release_SBCS_MFC"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Src\TestUrlDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\32\KHypLink.h
# End Source File
# Begin Source File

SOURCE=..\..\32\KRegExt.h
# End Source File
# Begin Source File

SOURCE=..\..\32\KRegKey.h
# End Source File
# Begin Source File

SOURCE=..\..\32\KStaticEx.h
# End Source File
# Begin Source File

SOURCE=.\Res\Resource.h
# End Source File
# Begin Source File

SOURCE=..\..\32\stdafx.h
# End Source File
# Begin Source File

SOURCE=..\Generic\Src\TestDialogApp.h
# End Source File
# Begin Source File

SOURCE=..\Generic\Res\TestResource.h
# End Source File
# Begin Source File

SOURCE=.\Src\TestStaticDlg.h
# End Source File
# Begin Source File

SOURCE=.\Src\TestUrlDlg.h
# End Source File
# Begin Source File

SOURCE=..\Generic\Res\TestWinRes.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "rc;xml;ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\..\Res\Win\SrcPool.ico
# End Source File
# Begin Source File

SOURCE=.\Res\TestStatic.rc

!IF  "$(CFG)" == "TestStatic - Win32 Debug_Unicode_MFC"

# ADD BASE RSC /l 0x1009 /i "Res"
# SUBTRACT BASE RSC /i ".." /i "Res"
# ADD RSC /l 0x1009 /i "../.." /i "Res"
# SUBTRACT RSC /i ".."

!ELSEIF  "$(CFG)" == "TestStatic - Win32 Debug_SBCS_MFC"

# ADD BASE RSC /l 0x1009 /i "Res"
# SUBTRACT BASE RSC /i "Res" /i ".."
# ADD RSC /l 0x1009 /i "../.." /i "Res"

!ELSEIF  "$(CFG)" == "TestStatic - Win32 Release_Unicode_MFC"

# ADD BASE RSC /l 0x1009 /i "Res"
# SUBTRACT BASE RSC /i "../Generic/Res" /i "Res" /i ".."
# ADD RSC /l 0x1009 /i "../.." /i "Res"
# SUBTRACT RSC /i "../Generic/Res"

!ELSEIF  "$(CFG)" == "TestStatic - Win32 Release_SBCS_MFC"

# ADD BASE RSC /l 0x1009 /i "Res"
# SUBTRACT BASE RSC /i "../Generic/Res" /i "Res" /i ".."
# ADD RSC /l 0x1009 /i "../.." /i "Res"
# SUBTRACT RSC /i "../Generic/Res"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\TestStatic.rc2
# End Source File
# Begin Source File

SOURCE=..\Generic\Res\TestWin.rc
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "Help Files"

# PROP Default_Filter "cnt;rtf"
# Begin Source File

SOURCE=.\hlp\AfxDlg.rtf
# End Source File
# Begin Source File

SOURCE=.\hlp\TestStatic.cnt
# PROP BASE Ignore_Default_Tool 1
# PROP Exclude_From_Build 1
# PROP Ignore_Default_Tool 1
# End Source File
# End Group
# Begin Group "Log Files"

# PROP Default_Filter "*.log"
# End Group
# Begin Source File

SOURCE=.\TestStatic.txt
# End Source File
# End Target
# End Project
