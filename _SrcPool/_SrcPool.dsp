# Microsoft Developer Studio Project File - Name="_SrcPool" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=_SrcPool - Win32 Debug_Unicode
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "_SrcPool.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "_SrcPool.mak" CFG="_SrcPool - Win32 Debug_Unicode"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "_SrcPool - Win32 Release_SBCS" (based on "Win32 (x86) Static Library")
!MESSAGE "_SrcPool - Win32 Debug_SBCS" (based on "Win32 (x86) Static Library")
!MESSAGE "_SrcPool - Win32 Debug_Unicode" (based on "Win32 (x86) Static Library")
!MESSAGE "_SrcPool - Win32 Release_Unicode" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "_SrcPool"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "_SrcPool - Win32 Release_SBCS"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Cpp\Samples\bin\Release_SBCS\Win32"
# PROP Intermediate_Dir ".\Cpp\SamplesObj\Release_SBCS\_SrcPool\Win32"
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

!ELSEIF  "$(CFG)" == "_SrcPool - Win32 Debug_SBCS"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "_SrcPool___Win32_Debug"
# PROP BASE Intermediate_Dir "_SrcPool___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Cpp\Samples\bin\Debug_SBCS\Win32"
# PROP Intermediate_Dir ".\Cpp\Samples\Obj\Debug_SBCS\_SrcPool\Win32"
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

!ELSEIF  "$(CFG)" == "_SrcPool - Win32 Debug_Unicode"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "_SrcPool___Win32_Debug_Unicode"
# PROP BASE Intermediate_Dir "_SrcPool___Win32_Debug_Unicode"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Cpp\Samples\bin\Debug_Unicode\Win32"
# PROP Intermediate_Dir ".\Cpp\Samples\Obj\Debug_Unicode\_SrcPool\Win32"
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

!ELSEIF  "$(CFG)" == "_SrcPool - Win32 Release_Unicode"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "_SrcPool___Win32_Release_Unicode"
# PROP BASE Intermediate_Dir "_SrcPool___Win32_Release_Unicode"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Cpp\Samples\bin\Release_Unicode\Win32"
# PROP Intermediate_Dir ".\Cpp\Samples\Obj\Release_Unicode\_SrcPool\Win32"
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

# Name "_SrcPool - Win32 Release_SBCS"
# Name "_SrcPool - Win32 Debug_SBCS"
# Name "_SrcPool - Win32 Debug_Unicode"
# Name "_SrcPool - Win32 Release_Unicode"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "STL"

# PROP Default_Filter "cpp;"
# Begin Source File

SOURCE=.\Cpp\STL\KDateStr.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\STL\KDbgLimits.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\STL\KGetFileExtn.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\STL\KGetFileName.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\STL\KGetLines.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\STL\KIntStream.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KMatAcosh.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KSerialIo.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\STL\KSkipWSp.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\STL\KStrAtoWChar.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\STL\KStringStl.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrPrefix.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\STL\KStrRplEOL.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\STL\KStrStream.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\STL\KStrUppr.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrVowel.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\STL\KStrWtoChar.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KXmlDataType.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\Cpp\KColorShade.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KColorSt.c
# End Source File
# Begin Source File

SOURCE=.\Cpp\KDate.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KDateConv.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KDateCst.c
# End Source File
# Begin Source File

SOURCE=.\Cpp\KDateTm.c
# End Source File
# Begin Source File

SOURCE=.\Cpp\KDbgFILE.c
# End Source File
# Begin Source File

SOURCE=.\Cpp\KDtoA.c
# End Source File
# Begin Source File

SOURCE=.\Cpp\KfFibonacci.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KFileNam.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KfKepler.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KfNewtRp.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KfQuadEq.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KGetFileExt.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KGetFileExtension.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KGetLine.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KGetLRC.cpp
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

SOURCE=.\Cpp\KGuid.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KIsLRC.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KIsPrimeNo.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KItoA.c
# End Source File
# Begin Source File

SOURCE=.\Cpp\KItoOct.c
# End Source File
# Begin Source File

SOURCE=.\Cpp\KLinkedListS.c
# End Source File
# Begin Source File

SOURCE=.\Cpp\KMatFact.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KMatPerc.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KOctave.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KRandomGauss.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KRandomUniform.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStColor.c
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrAtoI.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrAtoU.c
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

SOURCE=.\Cpp\KStrEscC.c
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrExC.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrFindNoCase.cpp
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

SOURCE=.\Cpp\KStrGuid.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrHtoL.c
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrICmp.c
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStringHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrIStr.c
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrLowC.c
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrNDup.c
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrOtoL.c
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrPalindrome.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrPCpy.c
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrRpl.cpp
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

SOURCE=.\Cpp\KStrRTab.c
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrToD.c
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrTrim.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrTrSl.c
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrUtDJ.c
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrUtoD.c
# End Source File
# Begin Source File

SOURCE=.\Cpp\KTestLog.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KTmCmp.c
# End Source File
# Begin Source File

SOURCE=.\Cpp\KXmlAttribute.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KXmlNode.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KXmlParserI.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KXmlStringData.cpp
# End Source File
# Begin Source File

SOURCE=.\Cpp\KZLineIn.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "STL Header Files"

# PROP Default_Filter "h;hpp"
# Begin Source File

SOURCE=.\Cpp\STL\KBoolStream.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\STL\KDbgStlA.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\STL\KHexStream.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\STL\KOStream.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\STL\KTString.h
# End Source File
# End Group
# Begin Group "Platform Header Files"

# PROP Default_Filter "*.h;*.inl"
# Begin Source File

SOURCE=.\Cpp\Platform\KioPIT.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\Platform\KioPPI.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Cpp\KBeep.h
# End Source File
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

SOURCE=.\Cpp\KConvCst.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KCrc32.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KDate.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KDateConv.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KDbgMacr.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KFileNam.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KFileSys.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KGaussianInt.h
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

SOURCE=.\Cpp\KGuid.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KLinkedListS.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KMatGcd.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KMathCst.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KMathCst.inl
# End Source File
# Begin Source File

SOURCE=.\Cpp\KMatLcm.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KMatLog2.inl
# End Source File
# Begin Source File

SOURCE=.\Cpp\KNLSCst.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KOctave.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KOsService.h
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

SOURCE=.\Cpp\KRefCounter.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KRound.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KRvrElements.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KRvrRows.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KSerialIo.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStdLib.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrConvert.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStrExt.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KString.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KStringHandler.h
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

SOURCE=.\Cpp\KTChar.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KTestLog.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KTime.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KTmConv.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KTrace.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KTraceFx.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KType32.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KTypedef.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KXmlAttribute.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\STL\KXmlAttributeVector.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KXmlBinding.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\STL\KXmlElementVector.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KXmlNode.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KXmlParserI.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\KXmlStringData.h
# End Source File
# Begin Source File

SOURCE=.\Cpp\STL\KXmlTypeStl.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe;png;xml;htm"
# Begin Source File

SOURCE=.\Cpp\Win\Res\Win\SrcPool.ico
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
