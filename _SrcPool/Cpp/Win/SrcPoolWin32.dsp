# Microsoft Developer Studio Project File - Name="SrcPoolWin32" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=SrcPoolWin32 - Win32 Debug_Unicode
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SrcPoolWin32.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SrcPoolWin32.mak" CFG="SrcPoolWin32 - Win32 Debug_Unicode"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SrcPoolWin32 - Win32 Release_SBCS" (based on "Win32 (x86) Static Library")
!MESSAGE "SrcPoolWin32 - Win32 Debug_SBCS" (based on "Win32 (x86) Static Library")
!MESSAGE "SrcPoolWin32 - Win32 Debug_Unicode" (based on "Win32 (x86) Static Library")
!MESSAGE "SrcPoolWin32 - Win32 Release_Unicode" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SrcPoolWin32 - Win32 Release_SBCS"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Cpp\Samples\bin\Release_SBCS\Win32"
# PROP Intermediate_Dir ".\Cpp\SamplesObj\Release_SBCS\SrcPoolWin32\Win32"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "SrcPoolWin32 - Win32 Debug_SBCS"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "SrcPoolWin32___Win32_Debug"
# PROP BASE Intermediate_Dir "SrcPoolWin32___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Cpp\Samples\bin\Debug_SBCS\Win32"
# PROP Intermediate_Dir ".\Cpp\Samples\Obj\Debug_SBCS\SrcPoolWin32\Win32"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "SrcPoolWin32 - Win32 Debug_Unicode"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "SrcPoolWin32___Win32_Debug_Unicode"
# PROP BASE Intermediate_Dir "SrcPoolWin32___Win32_Debug_Unicode"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Cpp\Samples\bin\Debug_Unicode\Win32"
# PROP Intermediate_Dir ".\Cpp\Samples\Obj\Debug_Unicode\SrcPoolWin32\Win32"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /FR /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL" /d "_UNICODE"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "SrcPoolWin32 - Win32 Release_Unicode"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "SrcPoolWin32___Win32_Release_Unicode"
# PROP BASE Intermediate_Dir "SrcPoolWin32___Win32_Release_Unicode"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Cpp\Samples\bin\Release_Unicode\Win32"
# PROP Intermediate_Dir ".\Cpp\Samples\Obj\Release_Unicode\SrcPoolWin32\Win32"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL" /d "_UNICODE"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "SrcPoolWin32 - Win32 Release_SBCS"
# Name "SrcPoolWin32 - Win32 Debug_SBCS"
# Name "SrcPoolWin32 - Win32 Debug_Unicode"
# Name "SrcPoolWin32 - Win32 Release_Unicode"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\32\KAbout.cpp
# End Source File
# Begin Source File

SOURCE=.\Res\Win\32\KAbtRes.rc
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\32\KAdoConnection.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KAdoField.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KAdoRecordset.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KApnSyMn.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KBtnEx.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KCheckBox.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KClrShem.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KCoErrorShow.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KCoGetThreadModel.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KCoProviderErrors.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KDateTime.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KDbgAdoFieldType.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KDbgAdoPropertyAttributes.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KDbgAdoRecordsetSupport.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KDbgBtnS.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KDbgCoVariant.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KDbgDaoFieldType.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KDbgDaoQueryDefType.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KDbgDlgErrorCode.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KDbgFileExceptionError.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KDbgFVSI.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KDbgGUID.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KDbgLDLL.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KDbgMapM.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KDbgOSVI.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KDbgPrpS.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KDbgRASS.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KDbgREFIID.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KDbgTraceLog.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KDbgVerI.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KDbgWsaError.c
# End Source File
# Begin Source File

SOURCE=.\32\KDbgXmlWin.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KDirGetExe.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KDisplayComError.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KDlgItem.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KDlgItLs.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KDlgRsiz.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KDlgTmIt.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KDlgTmpl.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KDockBar.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KFileGetDirectory.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KFileTime.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KGetDomainName2k.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KGetPrSu.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KGetPrTy.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KGetShel.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KHypLink.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KIsProdS.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KIsRASCo.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KIsSrvce.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KIsTerm.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KListEx.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KRegCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KRegExt.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KRegKey.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KShellDocumentFile.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KSingleInstanceApp.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KSpwnURL.cpp
# End Source File
# Begin Source File

SOURCE=.\Res\Win\32\KSrcPool.rc
# End Source File
# Begin Source File

SOURCE=.\32\KStatusBarEx.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KStrAtoWChar.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KStrWtoChar.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KSysErrM.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KTaskIco.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KTimer.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KTimerW.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KTipBox.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KVerInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KWinFWIs.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KWinPlac.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KWinVerG.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KWinVers.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KXmlProcessorSax.cpp
# End Source File
# Begin Source File

SOURCE=.\32\KXmlSaxErrorHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\32\stdafx.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\32\ATL30Conv.inl
# End Source File
# Begin Source File

SOURCE=.\32\KAbout.h
# End Source File
# Begin Source File

SOURCE=.\32\KAbtRes.h
# End Source File
# Begin Source File

SOURCE=.\32\KAdoConnection.h
# End Source File
# Begin Source File

SOURCE=.\32\KAdoField.h
# End Source File
# Begin Source File

SOURCE=.\32\KAdoRecordset.h
# End Source File
# Begin Source File

SOURCE=.\32\KAtlExt.h
# End Source File
# Begin Source File

SOURCE=.\32\KBtnEx.h
# End Source File
# Begin Source File

SOURCE=.\32\KCheckBox.h
# End Source File
# Begin Source File

SOURCE=.\32\KClrShem.h
# End Source File
# Begin Source File

SOURCE=.\32\KDateTime.h
# End Source File
# Begin Source File

SOURCE=.\32\KDbgDump.h
# End Source File
# Begin Source File

SOURCE=.\32\KDbgXmlWin.h
# End Source File
# Begin Source File

SOURCE=.\32\KDlgItem.h
# End Source File
# Begin Source File

SOURCE=.\32\KDlgItLs.h
# End Source File
# Begin Source File

SOURCE=.\32\KDlgRsiz.h
# End Source File
# Begin Source File

SOURCE=.\32\KDlgTmIt.h
# End Source File
# Begin Source File

SOURCE=.\32\KDlgTmpl.h
# End Source File
# Begin Source File

SOURCE=.\32\KFileTime.h
# End Source File
# Begin Source File

SOURCE=.\32\KFileTimeCm.h
# End Source File
# Begin Source File

SOURCE=.\32\KHypLink.h
# End Source File
# Begin Source File

SOURCE=.\32\KListEx.h
# End Source File
# Begin Source File

SOURCE=.\32\KRegCtrl.h
# End Source File
# Begin Source File

SOURCE=.\32\KRegExt.h
# End Source File
# Begin Source File

SOURCE=.\32\KRegKey.h
# End Source File
# Begin Source File

SOURCE=.\32\KSingleInstanceApp.h
# End Source File
# Begin Source File

SOURCE=.\32\KSound.inl
# End Source File
# Begin Source File

SOURCE=.\32\KStatusBarEx.h
# End Source File
# Begin Source File

SOURCE=.\Res\Win\KStdRes.h
# End Source File
# Begin Source File

SOURCE=.\32\KTaskIco.h
# End Source File
# Begin Source File

SOURCE=.\32\KTimer.h
# End Source File
# Begin Source File

SOURCE=.\32\KTimerW.h
# End Source File
# Begin Source File

SOURCE=.\32\KTipBox.h
# End Source File
# Begin Source File

SOURCE=.\32\KVerInfo.h
# End Source File
# Begin Source File

SOURCE=.\32\KWinPlac.h
# End Source File
# Begin Source File

SOURCE=.\32\KWinVerG.inl
# End Source File
# Begin Source File

SOURCE=.\32\KWinVers.h
# End Source File
# Begin Source File

SOURCE=.\32\KWinVers.inl
# End Source File
# Begin Source File

SOURCE=.\32\KXmlProcessorSax.h
# End Source File
# Begin Source File

SOURCE=.\32\KXmlSaxErrorHandler.h
# End Source File
# Begin Source File

SOURCE=.\32\KXmlSaxHandler.h
# End Source File
# Begin Source File

SOURCE=.\32\KXmlTypeWin.h
# End Source File
# Begin Source File

SOURCE=.\32\MFC40Hlp.inl
# End Source File
# Begin Source File

SOURCE=.\Res\Win\Resource.h
# End Source File
# Begin Source File

SOURCE=.\32\SrcPoolR.h
# End Source File
# Begin Source File

SOURCE=.\32\stdafx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe;png;xml;htm"
# Begin Source File

SOURCE=.\Res\Win\SrcPool.ico
# End Source File
# End Group
# Begin Group "ToDo Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Cpp\Win\32\KClrShem.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\Win\32\KClrShem.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KCmdLineParser.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KCmdLineParser.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KIpAddress.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\Win\32\KListEx.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\Win\32\KListEx.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KMatGcd.c
# End Source File
# Begin Source File

SOURCE=.\Cpp\KNetByte.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStringStd.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStringStd.h
# End Source File
# End Group
# End Target
# End Project
