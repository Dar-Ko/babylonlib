# Microsoft Developer Studio Project File - Name="SrcPool" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=SrcPool - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SrcPool.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SrcPool.mak" CFG="SrcPool - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SrcPool - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "SrcPool - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SrcPool - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Win32\Release"
# PROP Intermediate_Dir "Obj\Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "SrcPool - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "SrcPool___Win32_Debug"
# PROP BASE Intermediate_Dir "SrcPool___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Win32\Debug"
# PROP Intermediate_Dir "Obj\Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "SrcPool - Win32 Release"
# Name "SrcPool - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Cpp\KApnSyMn.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KClipCBm.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KClipCTx.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KDateCrl.cpp

!IF  "$(CFG)" == "SrcPool - Win32 Release"

!ELSEIF  "$(CFG)" == "SrcPool - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Cpp\KDateStr.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KDbgBtnS.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KDbgDCAt.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KDbgFILE.c
# End Source File
# Begin Source File

SOURCE=.\Cpp\KDbgFVSI.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KDbgGUID.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KDbgLDLL.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KDbgMapM.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KDbgOSVI.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KDbgPrpS.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KDbgRASS.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KDbgREFIID.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KDbgTLog.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KDbgVerI.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KDirName.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KDlgItem.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KDlgItLs.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KDlgRsiz.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KDlgTmIt.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KDlgTmpl.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KDockBar.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KFileExtR.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KFileFindOld.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KFileNam.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KFileNmB.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KFileNmF.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KFileRead.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KFileSetTime.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KFileShortcut.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KFileTmpName.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KFindEdt.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KfNewtRp.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KfQuadEq.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KGetLine.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KGetLines.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KGetLRC.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KGetPrSu.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KGetPrTy.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KGetShel.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KGif.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KGifImageData.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KGifImageDescriptor.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KGifLzw.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KGifViewer.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KHypLink.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KIsFileNameValid.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KIsLRC.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KIsPrimeNo.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KIsProdS.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KIsRASCo.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KIsSrvce.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KIsTerm.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KItoA.c
# End Source File
# Begin Source File

SOURCE=.\Cpp\KItoOct.c
# End Source File
# Begin Source File

SOURCE=.\Cpp\KLogoOut.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Cpp\KPropPgR.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KPropShR.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KRandomGauss.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KRandomUniform.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KRegExt.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KRegKey.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KSkipWSp.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KSpwnURL.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrBtoA.c
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrBtoH.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrBtoU.c
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrCatV.c
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrCtoA.c
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrDup.c
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrEnum.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrExC.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrFit.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrGetF.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrGetLine.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrGetS.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrGetW.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrGSu.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrHtoL.c
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrICmp.c
# End Source File
# Begin Source File

SOURCE=.\Cpp\KString.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrLowC.c
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrOtoL.c
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrPCpy.c
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrRpl.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrRplEOL.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrRplEscSeq.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrRplSpaces.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrRplT.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrStream.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrTrim.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrUppr.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrUtDJ.c
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrUtoD.c
# End Source File
# Begin Source File

SOURCE=.\Cpp\KSysErrM.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KTaskIco.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KTimer.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KTimerW.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KTipBox.cpp

!IF  "$(CFG)" == "SrcPool - Win32 Release"

!ELSEIF  "$(CFG)" == "SrcPool - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Cpp\KVerInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KWinFWIs.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KWinPlac.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KWinVerG.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KWinVers.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KZLineIn.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\SrcPool.rc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Cpp\KBitMan.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KBitmap.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KCharCst.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KChecksum.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KColorCt.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KComplex.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KComplxB.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KCrc32.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KDateCrl.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KDbgDump.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KDbgMacr.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KDlgItem.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KDlgItLs.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KDlgRsiz.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KDlgTmIt.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KDlgTmpl.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KFileExtR.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KFileHnd.inl
# End Source File
# Begin Source File

SOURCE=.\Cpp\KFileN32.inl
# End Source File
# Begin Source File

SOURCE=.\Cpp\KFileNam.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KFileNmB.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KFileShortcut.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KFileSys.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KFindRes.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KGif.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KGifImageData.h
# End Source File
# Begin Source File

SOURCE=.\CPP\KGifImageDescriptor.h
# End Source File
# Begin Source File

SOURCE=.\CPP\KGifLzw.h
# End Source File
# Begin Source File

SOURCE=.\CPP\KGifViewer.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KHypLink.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KIPAddress.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KMathCst.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KMathCst.inl
# End Source File
# Begin Source File

SOURCE=.\Cpp\KMatLog2.inl
# End Source File
# Begin Source File

SOURCE=.\Cpp\KNetByte.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KNLSCst.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KPair.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KPhysCst.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KPoint.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KProgCst.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KProgCst.inl
# End Source File
# Begin Source File

SOURCE=.\Cpp\KPropPgR.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KPropShR.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KRandom.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KRandomCongr.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KRandomGauss.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KRandomUniform.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KReal4Cv.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KReal4IE.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KReal8Cv.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KRegExt.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KRegKey.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KSound.inl
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrExt.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KString.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrings.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KSwpByte.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KSwpByteOrder.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KSwpElements.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KSwpRows.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KTaskIco.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KTChar.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KTimer.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KTimerW.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KTipBox.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KTrace.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KTypedef.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KVerInfo.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KWinPlac.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KWinVerG.inl
# End Source File
# Begin Source File

SOURCE=.\Cpp\KWinVers.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KWinVers.inl
# End Source File
# Begin Source File

SOURCE=.\Cpp\StdAfx.h
# End Source File
# End Group
# End Target
# End Project
