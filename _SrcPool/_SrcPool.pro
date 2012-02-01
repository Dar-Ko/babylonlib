#-------------------------------------------------
#
# Project created by QtCreator 2012-01-31T17:32:37
#
#-------------------------------------------------

QT       -= core gui

TARGET = _SrcPool
TEMPLATE = lib
CONFIG += staticlib

CONFIG(debug, debug|release)
  {
  RCC_DIR = "$$ParentDirectory/src/Obj/Debug/RCCFiles"
  UI_DIR = "$$ParentDirectory/src/Obj/Debug/UICFiles"
  MOC_DIR = "$$ParentDirectory/src/Obj/Debug/MOCFiles"
  OBJECTS_DIR = "$$ParentDirectory/src/Obj/Debug"
  DESTDIR = "$$ParentDirectory/debug/linux"
  DEFINES += _DEBUG
  }

CONFIG(release, debug|release)
  {
  RCC_DIR = "$$ParentDirectory/src/Obj/Release/RCCFiles"
  UI_DIR = "$$ParentDirectory/src/Obj/Release/UICFiles"
  MOC_DIR = "$$ParentDirectory/src/Obj/Release/MOCFiles"
  OBJECTS_DIR = "$$ParentDirectory/src/Obj/Release"
  DESTDIR = "$$ParentDirectory/bin/release/linux"
  DEFINES += NDEBUG
  }

SOURCES += \
    Cpp/KZLineIn.cpp \
    Cpp/KXmlWriter.cpp \
    Cpp/KXmlStringData.cpp \
    Cpp/KXmlNode.cpp \
    Cpp/KXmlEscape.cpp \
    Cpp/KXmlDocument.cpp \
    Cpp/KXmlDataType.cpp \
    Cpp/KXmlAttribute.cpp \
    Cpp/KVariantToStr.cpp \
    Cpp/KVarBstrFromStr.cpp \
    Cpp/KTestLog.cpp \
    Cpp/KStrVowel.cpp \
    Cpp/KStrTrim.cpp \
    Cpp/KStrToInt.cpp \
    Cpp/KStrRplT.cpp \
    Cpp/KStrRplSpaces.cpp \
    Cpp/KStrRplEscSeq.cpp \
    Cpp/KStrRpl.cpp \
    Cpp/KStrPrefix.cpp \
    Cpp/KStrPalindrome.cpp \
    Cpp/KStringStd.cpp \
    Cpp/KStringHandler.cpp \
    Cpp/KStrGuidToA.cpp \
    Cpp/KStrGuid.cpp \
    Cpp/KStrGSu.cpp \
    Cpp/KStrGetW.cpp \
    Cpp/KStrGetS.cpp \
    Cpp/KStrGetLine.cpp \
    Cpp/KStrGetF.cpp \
    Cpp/KStrFindNoCase.cpp \
    Cpp/KStrExC.cpp \
    Cpp/KStrEnum.cpp \
    Cpp/KStrBtoH.cpp \
    Cpp/KStrBool.cpp \
    Cpp/KStrAtoI.cpp \
    Cpp/KSerialIo.cpp \
    Cpp/KRandomUniform.cpp \
    Cpp/KRandomGauss.cpp \
    Cpp/KOctave.cpp \
    Cpp/KMod10.cpp \
    Cpp/KMatPerc.cpp \
    Cpp/KMatFact.cpp \
    Cpp/KMatAcosC.cpp \
    Cpp/KIsPrimeNo.cpp \
    Cpp/KIsLRC.cpp \
    Cpp/KHtmlAttrList.cpp \
    Cpp/KGifImageDescriptor.cpp \
    Cpp/KGifImageData.cpp \
    Cpp/KGif.cpp \
    Cpp/KGetLRC.cpp \
    Cpp/KGetLine.cpp \
    Cpp/KGetFileExtension.cpp \
    Cpp/KGetFileExt.cpp \
    Cpp/KfQuadEq.cpp \
    Cpp/KfNewtRp.cpp \
    Cpp/KfKepler.cpp \
    Cpp/KfFibonacci.cpp \
    Cpp/KDbgVariantType.cpp \
    Cpp/KDbgCimType.cpp \
    Cpp/KDateConv.cpp \
    Cpp/KDate.cpp \
    Cpp/KColorShade.cpp \
    Cpp/KCmdLineParser.cpp \
    Cpp/KProgCst.inl \
    Cpp/KMatLog2.inl \
    Cpp/KMathCst.inl \
    Cpp/KTmCmp.c \
    Cpp/KStrUtoD.c \
    Cpp/KStrUtDJ.c \
    Cpp/KStrTrSl.c \
    Cpp/KStrToD.c \
    Cpp/KStrRTab.c \
    Cpp/KStrPCpy.c \
    Cpp/KStrOtoL.c \
    Cpp/KStrNDup.c \
    Cpp/KStrLowC.c \
    Cpp/KStrIStr.c \
    Cpp/KStrICmp.c \
    Cpp/KStrHtoL.c \
    Cpp/KStrEscC.c \
    Cpp/KStrDup.c \
    Cpp/KStrCtoA.c \
    Cpp/KStrCatV.c \
    Cpp/KStrBtoU.c \
    Cpp/KStrBtoA.c \
    Cpp/KStrAtoU.c \
    Cpp/KStColor.c \
    Cpp/KMatGcd.c \
    Cpp/KLinkedListS.c \
    Cpp/KItoOct.c \
    Cpp/KItoA.c \
    Cpp/KDtoA.c \
    Cpp/KDbgFILE.c \
    Cpp/KDateTm.c \
    Cpp/KDateCst.c \
    Cpp/KColorSt.c \
    Cpp/KZtoA.cpp \
    Cpp/STL/KUcsToHex.cpp \
    Cpp/STL/KStrWtoChar.cpp \
    Cpp/STL/KStrUppr.cpp \
    Cpp/STL/KStrStream.cpp \
    Cpp/STL/KStrRplEOL.cpp \
    Cpp/STL/KStringStl.cpp \
    Cpp/STL/KStrAtoWChar.cpp \
    Cpp/STL/KSkipWSp.cpp \
    Cpp/STL/KLogMsg.cpp \
    Cpp/STL/KIntStream.cpp \
    Cpp/STL/KGetLines.cpp \
    Cpp/STL/KGetFileName.cpp \
    Cpp/STL/KGetFileExtn.cpp \
    Cpp/STL/KFileRead.cpp \
    Cpp/STL/KFileExistStl.cpp \
    Cpp/STL/KDbgLimits.cpp \
    Cpp/STL/KDateStr.cpp

HEADERS += \
    Cpp/KXmlWriter.h \
    Cpp/KXmlStringData.h \
    Cpp/KXmlParserI.h \
    Cpp/KXmlNode.h \
    Cpp/KXmlDocument.h \
    Cpp/KXmlBinding.h \
    Cpp/KXmlAttribute.h \
    Cpp/KVersion.h \
    Cpp/KTypedef.h \
    Cpp/KType32.h \
    Cpp/KTraceFx.h \
    Cpp/KTrace.h \
    Cpp/KTmConv.h \
    Cpp/KTimeCst.h \
    Cpp/KTime.h \
    Cpp/KTestLog.h \
    Cpp/KTChar.h \
    Cpp/KSwpByteOrder.h \
    Cpp/KSwpByte.h \
    Cpp/KStrLimits.h \
    Cpp/KStringStd.h \
    Cpp/KStrings.h \
    Cpp/KStringHandler.h \
    Cpp/KString.h \
    Cpp/KStrExt.h \
    Cpp/KStrConvert.h \
    Cpp/KStrArray.h \
    Cpp/KStdLib.h \
    Cpp/KSet.h \
    Cpp/KSerialIo.h \
    Cpp/KSafeArray.h \
    Cpp/KRvrRows.h \
    Cpp/KRvrElements.h \
    Cpp/KRound.h \
    Cpp/KRefCounter.h \
    Cpp/KReal8Cv.h \
    Cpp/KReal4IE.h \
    Cpp/KReal4Cv.h \
    Cpp/KRandomUniform.h \
    Cpp/KRandomGauss.h \
    Cpp/KRandomCongr.h \
    Cpp/KRandom.h \
    Cpp/KProgCst.h \
    Cpp/KProgCase.h \
    Cpp/KPoint.h \
    Cpp/KPhysCst.h \
    Cpp/KPair.h \
    Cpp/KPackPsh.h \
    Cpp/KPackPop.h \
    Cpp/KOsService.h \
    Cpp/KOctave.h \
    Cpp/KNLSCst.h \
    Cpp/KNetByte.h \
    Cpp/KMatrix.h \
    Cpp/KMatLcm.h \
    Cpp/KMathCst.h \
    Cpp/KMatGcd.h \
    Cpp/KLinkedListS.h \
    Cpp/KIpAddress.h \
    Cpp/KGuid.h \
    Cpp/KGifImageDescriptor.h \
    Cpp/KGifImageData.h \
    Cpp/KGif.h \
    Cpp/KGaussianInt.h \
    Cpp/KFileSys.h \
    Cpp/KFileSimple.h \
    Cpp/KFileNam.h \
    Cpp/KFileIni.h \
    Cpp/KDll.h \
    Cpp/KDbgMAns.h \
    Cpp/KDbgMacr.h \
    Cpp/KDateConv.h \
    Cpp/KDate.h \
    Cpp/KConvCst.h \
    Cpp/KComplxB.h \
    Cpp/KComplex.h \
    Cpp/KColorCt.h \
    Cpp/KCmdLineParser.h \
    Cpp/KCharCst.h \
    Cpp/KCExcept.h \
    Cpp/KBitmap.h \
    Cpp/KBitMan.h \
    Cpp/KBeep.h \
    Cpp/KArrayPtr.h \
    Cpp/KArray.h \
    Cpp/STL/KXmlTypeStl.h \
    Cpp/STL/KXmlElementVector.h \
    Cpp/STL/KXmlAttributeVector.h \
    Cpp/STL/KTString.h \
    Cpp/STL/KOStream.h \
    Cpp/STL/KHexStream.h \
    Cpp/STL/KDbgStlA.h \
    Cpp/STL/KBoolStream.h \
    Cpp/STL/KBinStream.h \
    Cpp/STL/KArrayStl.h


OTHER_FILES += \
    _SrcPool.txt \
    Cpp/STL/Desktop.ini









