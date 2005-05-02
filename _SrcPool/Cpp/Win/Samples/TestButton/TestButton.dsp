# Microsoft Developer Studio Project File - Name="TestButton" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=TestButton - Win32 Debug_SBCS_MFC
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TestButton.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TestButton.mak" CFG="TestButton - Win32 Debug_SBCS_MFC"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TestButton - Win32 Debug_Unicode_MFC" (based on "Win32 (x86) Application")
!MESSAGE "TestButton - Win32 Debug_SBCS_MFC" (based on "Win32 (x86) Application")
!MESSAGE "TestButton - Win32 Release_Unicode_MFC" (based on "Win32 (x86) Application")
!MESSAGE "TestButton - Win32 Release_SBCS_MFC" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TestButton - Win32 Debug_Unicode_MFC"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug_Unicode_MFC"
# PROP BASE Intermediate_Dir "Debug_Unicode_MFC"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\bin\Debug_Unicode_MFC\Win32"
# PROP Intermediate_Dir "..\Obj\Debug_Unicode_MFC\TestButton\Win32"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "../../../Win/32./Src" /I "./Res" /I "../../.." /I "../../Win/32" /I "../../../Win/32" /I "./Src" /I "../Generic/Src" /D "_DEBUG" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "_USE_MFC" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x1009 /d "_DEBUG"
# ADD RSC /l 0x1009 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "TestButton - Win32 Debug_SBCS_MFC"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug_SBCS_MFC"
# PROP BASE Intermediate_Dir "Debug_SBCS_MFC"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\bin\Debug_SBCS_MFC\Win32"
# PROP Intermediate_Dir "..\Obj\Debug_SBCS_MFC\TestButton\Win32"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "../../../Win/32./Src" /I "./Res" /I "../../.." /I "../../Win/32" /I "../../../Win/32" /I "./Src" /I "../Generic/Src" /D "_DEBUG" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "_USE_MFC" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x1009 /d "_DEBUG"
# ADD RSC /l 0x1009 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "TestButton - Win32 Release_Unicode_MFC"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release_Unicode_MFC"
# PROP BASE Intermediate_Dir "Release_Unicode_MFC"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\bin\Release_Unicode_MFC\Win32"
# PROP Intermediate_Dir "..\Obj\Release_Unicode_MFC\TestButton\Win32"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "../../../Win/32./Src" /I "./Res" /I "../../.." /I "../../Win/32" /I "../../../Win/32" /I "./Src" /I "../Generic/Src" /D "NDEBUG" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "_USE_MFC" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x1009 /d "NDEBUG"
# ADD RSC /l 0x1009 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "TestButton - Win32 Release_SBCS_MFC"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release_SBCS_MFC"
# PROP BASE Intermediate_Dir "Release_SBCS_MFC"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\bin\Release_SBCS_MFC\Win32"
# PROP Intermediate_Dir "..\Obj\Release_SBCS_MFC\TestButton\Win32"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "../../../Win/32./Src" /I "./Res" /I "../../.." /I "../../Win/32" /I "../../../Win/32" /I "./Src" /I "../Generic/Src" /D "NDEBUG" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "_USE_MFC" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x1009 /d "NDEBUG"
# ADD RSC /l 0x1009 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ENDIF 

# Begin Target

# Name "TestButton - Win32 Debug_Unicode_MFC"
# Name "TestButton - Win32 Debug_SBCS_MFC"
# Name "TestButton - Win32 Release_Unicode_MFC"
# Name "TestButton - Win32 Release_SBCS_MFC"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\32\KBtnEx.cpp
# End Source File
# Begin Source File

SOURCE=..\..\32\KCheckBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\32\KDbgBtnS.cpp
# End Source File
# Begin Source File

SOURCE=..\..\32\stdafx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\Generic\Src\TestAboutDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Res\TestButton.rc
# End Source File
# Begin Source File

SOURCE=.\Src\TestButtonApp.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\TestButtonDlg.cpp

!IF  "$(CFG)" == "TestButton - Win32 Debug_Unicode_MFC"

!ELSEIF  "$(CFG)" == "TestButton - Win32 Debug_SBCS_MFC"

!ELSEIF  "$(CFG)" == "TestButton - Win32 Release_Unicode_MFC"

!ELSEIF  "$(CFG)" == "TestButton - Win32 Release_SBCS_MFC"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Generic\Src\TestDialogApp.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\TestDumpButtonStyle.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\32\KBtnEx.h
# End Source File
# Begin Source File

SOURCE=..\..\32\KCheckBox.h
# End Source File
# Begin Source File

SOURCE=..\..\..\KColorCt.h
# End Source File
# Begin Source File

SOURCE=.\Res\Resource.h
# End Source File
# Begin Source File

SOURCE=..\..\32\stdafx.h
# End Source File
# Begin Source File

SOURCE=..\Generic\Src\TestAboutDlg.h
# End Source File
# Begin Source File

SOURCE=.\Src\TestButtonDlg.h
# End Source File
# Begin Source File

SOURCE=..\Generic\Src\TestDialogApp.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\..\Res\Win\SrcPool.ico
# End Source File
# Begin Source File

SOURCE=.\res\TestButton.ico
# End Source File
# Begin Source File

SOURCE=.\res\TestButton.rc2
# End Source File
# End Group
# Begin Group "Help Files"

# PROP Default_Filter "cnt;rtf"
# Begin Source File

SOURCE=.\hlp\AfxDlg.rtf
# End Source File
# Begin Source File

SOURCE=.\hlp\TestButton.cnt

!IF  "$(CFG)" == "TestButton - Win32 Debug_Unicode_MFC"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Copying contents file...
OutDir=.\..\bin\Debug_Unicode_MFC\Win32
InputPath=.\hlp\TestButton.cnt
InputName=TestButton

"$(OutDir)\$(InputName).cnt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "hlp\$(InputName).cnt" $(OutDir)

# End Custom Build

!ELSEIF  "$(CFG)" == "TestButton - Win32 Debug_SBCS_MFC"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Copying contents file...
OutDir=.\..\bin\Debug_SBCS_MFC\Win32
InputPath=.\hlp\TestButton.cnt
InputName=TestButton

"$(OutDir)\$(InputName).cnt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "hlp\$(InputName).cnt" $(OutDir)

# End Custom Build

!ELSEIF  "$(CFG)" == "TestButton - Win32 Release_Unicode_MFC"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Copying contents file...
OutDir=.\..\bin\Release_Unicode_MFC\Win32
InputPath=.\hlp\TestButton.cnt
InputName=TestButton

"$(OutDir)\$(InputName).cnt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "hlp\$(InputName).cnt" $(OutDir)

# End Custom Build

!ELSEIF  "$(CFG)" == "TestButton - Win32 Release_SBCS_MFC"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Copying contents file...
OutDir=.\..\bin\Release_SBCS_MFC\Win32
InputPath=.\hlp\TestButton.cnt
InputName=TestButton

"$(OutDir)\$(InputName).cnt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "hlp\$(InputName).cnt" $(OutDir)

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Log Files"

# PROP Default_Filter "*.log"
# End Group
# End Target
# End Project
