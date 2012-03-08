#-------------------------------------------------
#
#  $RCSfile: StreamIO.pro,v $: QtCreator project file
#  $Revision: 1.1 $ $Date: 2012/03/08 20:14:45 $
#  $Author: ddarko $
#
#-------------------------------------------------

QT       += core
QT       -= gui

TARGET = StdLib
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app
#Version number is in sync with KVersion.h
VERSION = 1.0.0_0

#Platform
unix {
PLATFORM = linux
DEFINES += LINUX
}

#Configuration
#Add qmake setting CONFIG+=[releaseBuild,debugBuild] in 'Build Steps'
CONFIG(releaseBuild) {
  message(Making release build.)
  CONFIG -= debug
  DEFINES += NDEBUG
  }

CONFIG(debugBuild){
  message(Making debug build.)
  CONFIG -= release
  DEFINES += _DEBUG
  }

BUILD = Debug_SBCS

#Intermediate directory
OutDirectory = ..
OBJECTS_DIR = "$$OutDirectory/Obj/$$BUILD/$$TARGET/$$PLATFORM"
RCC_DIR = "$$OBJECTS_DIR/RCCFiles"
UI_DIR = "$$OBJECTS_DIR/UICFiles"
MOC_DIR = "$$OBJECTS_DIR/MOCFiles"

#Output directory
DESTDIR = "$$OutDirectory/$$BUILD/$$PLATFORM"

#Preporcessor Definitions
CONFIG(console){
  DEFINES += _CONSOLE
  }
DEFINES += _SBCS

OTHER_FILES += \
    LibraryTestUni.log \
    LibraryTest.log

HEADERS += \
    ../../KDbgMacr.h \
    ../../KTestLog.h \
    ../../KTrace.h \
    ../../KTraceFx.h \
    KVersion.h

SOURCES += \
    ../../KTestLog.cpp \
    ../../KTestLog.cpp \
    ../Common/Src/TsWriteT.c \
    ../Common/Src/TsWriteTxt.cpp

unix{
  SOURCES += \
    ../../Linux/KVersion.c
  }
