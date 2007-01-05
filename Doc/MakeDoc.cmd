rem @echo off
REM $Workfile: MakeDoc.cmd$: command line script
REM $Revision: 7$ $Date: 2005-06-21 15:49:51$
REM $Author: Darko Kolakovic$
REM
REM Generate Library documentation
REM Note: Win32 specific
REM Copyright: CommonSoft Inc
REM 2004-06-10 Darko Kolakovic

REM Set preconditions
REM set DOCTOOLPATH=E:\doxygen\DocJet
set DOCTOOLPATH=C:\Program Files\Development\doxygen\DocJet
set DOCTOOL=%DOCTOOLPATH%\Program\Generator.exe
set DOCTOOLWRKDIR=S:\_SrcPool\Cpp\Documentation
set DOCTOOLSCRIPT=S:\_SrcPool\Cpp\Documentation\_SrcPool.djt

md "Library"
md "Library\HTMLHelp.tmp"
md "Library\HTMLHelp.tmp\Resources"
md "Library\HTMLHelp.tmp\Images"
md "Library\HTMLHelp.tmp\Documentation"

copy Resources\*.* "Library\HTMLHelp.tmp\Resources"
copy Images\*.* "Library\HTMLHelp.tmp\Images"
copy "%DOCTOOLPATH%\Gifs\*.*" "Library\HTMLHelp.tmp\Resources"
copy ".\*.htm" "Library\HTMLHelp.tmp\Documentation"

md "Library\Samples"
md "Library\Samples\HTMLHelp.tmp"
md "Library\Samples\HTMLHelp.tmp\Resources"
copy Resources\*.* "Library\Samples\HTMLHelp.tmp\Resources"

REM Change the working directory
S:
cd "%DOCTOOLWRKDIR%"

REM Run the tool
"%DOCTOOL%" "%DOCTOOLSCRIPT%"

set DOCTOOLSCRIPT=S:\_SrcPool\Cpp\Documentation\_Samples.djt
"%DOCTOOL%" "%DOCTOOLSCRIPT%"

REM Clean up
set DOCTOOL=
set DOCTOOLWRKDIR=
set DOCTOOLSCRIPT=
set DOCTOOLPATH=

pause

REM ---------------------------------------------------------------------------
REM $Log:
REM  3    Biblioteka1.2         2004-10-07 12:12:24  Darko           Added
REM       environment variables
REM  2    Biblioteka1.1         2004-07-01 11:28:59  Darko           Long file names
REM  1    Biblioteka1.0         2004-06-10 13:24:53  Darko
REM $
