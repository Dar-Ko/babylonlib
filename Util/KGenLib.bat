@echo off
REM $Workfile: $: batch command script
REM $Revision: 1.2 $ $Date: 2007/07/27 19:49:44 $
REM $Author: dkolakovic $
REM
REM Creates 32-bit import libraries .LIB from .DLL built with a Microsoft compiler.
REM Note: Microsoft Windows (Win32) specific
REM Copyright: CommonSoft Inc
REM 2007-07-11 Darko Kolakovic

REM: MSDN article: See How To Create 32-bit Import Libraries Without .OBJs or Source, KB 131313

REM ----------------------------------------------------------------------------
:LBLSTART

SET KESC=$
REM Obtain the list of exported symbols for a .DLL
@echo Obtain the list of exported symbols
@echo ;%KESC%Workfile: %KESC%: module definition file> %1.def
@echo ;%KESC%Revision: %KESC% %KESC%Date: %KESC%>> %1.def
@echo ;%KESC%Author: %KESC%>> %1.def
@echo ;Declares the module parameters.>> %1.def
@echo DESCRIPTION "%1.dll Import Library">> %1.def
@echo EXPORTS>> %1.def
@echo ;--------------Cut here! ----------------  >> %1.def
@echo ;Delete all columns but "name" column from %1.def file. >> %1.def
@echo ;Move all C++ decorated names to %1.cpp file and specify __declspec(dllexport). >> %1.def
DUMPBIN /EXPORTS %1.dll >> %1.def

REM Modify the output list
@echo Delete all columns but "name" column from %1.def file.
@echo Move all C++ decorated names to %1.cpp file.
REM Exportded C functions or functions specified with the _cdecl attribute could
REM be used without any modifications
pause
:LBLLIB

REM Build dummy .OBJ with C++ exports and C functions declared for export in .def
REM Disable function inlining with /Ob0 to force generation of symbols for
REM the class member functions
if exist %1.cpp CL /c /Ob0 %1.cpp

REM Create the import library (.LIB) and exports file (.EXP)
@echo Generate the import library and exports file
if exist %1.obj goto LBLLNKOBJ


LIB /MACHINE:IX86 /DEF:%1.def
goto END

:LBLLNKOBJ
LIB /MACHINE:IX86 /DEF:%1.def %1.obj
goto END


:END
SET KESC=

REM ---------------------------------------------------------------------------
REM $Log: KGenLib.bat,v $
REM Revision 1.2  2007/07/27 19:49:44  dkolakovic
REM Creating Import Library fro a .DLL
REM

REM Microsoft Library Manager Version 6.00.8447
REM usage: LIB [options] [files]
REM options:
REM       /CONVERT
REM       /DEBUGTYPE:CV
REM       /DEF[:filename]
REM       /EXPORT:symbol
REM       /EXTRACT:membername
REM       /INCLUDE:symbol
REM       /LIBPATH:dir
REM       /LINK50COMPAT
REM       /LIST[:filename]
REM       /MACHINE:{ALPHA|ARM|IX86|MIPS|MIPS16|MIPSR41XX|PPC|SH3|SH4}
REM       /NAME:filename
REM       /NODEFAULTLIB[:library]
REM       /NOLOGO
REM       /OUT:filename
REM       /REMOVE:membername
REM       /SUBSYSTEM:{NATIVE|WINDOWS|CONSOLE|WINDOWSCE|POSIX}[,#[.##]]
REM       /VERBOSE
