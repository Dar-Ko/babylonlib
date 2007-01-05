@echo off
REM $Workfile: MakeHelp.cmd$: command line script
REM $Revision: 2$ $Date: 2004-10-07 12:40:56$
REM $Author: Darko$
REM
REM Generate Library Help documentation
REM Note: Win32 specific
REM Copyright: CommonSoft Inc
REM 2004-09-11 Darko Kolakovic

REM Set preconditions
rem Win3.1 help
rem set HELPPRJNAME=%1.hpj
rem set HELPTOOL="E:\Microsoft\Common\hcw.exe /C /E /M"

rem Win32 help
set HELPPRJNAME=%1.hhp
set HELPTOOL="E:\HTML Help Workshop\hhw.exe"
if not exist %HELPTOOL% goto :ERROR3

set HELPPRJSRCDIR="S:\_SrcPool\Cpp\Documentation\Library\HTMLHelp.tmp"

if not exist %HELPPRJSRCDIR% goto :ERROR1
if not exist %HELPPRJNAME% goto :ERROR2

REM Run the tool
%HELPTOOL% %HELPPRJNAME%
if errorlevel 1 goto :ERRORTOOL

REM Done
rem copy %HELPPRJSRCDIR%\*.hlp ..\..
copy %HELPPRJSRCDIR%\*.chm ..\..
rem del %HELPPRJSRCDIR%\*.*

goto :EXIT

:ERROR1
echo %HELPPRJSRCDIR% not exist.
goto :EXIT

:ERROR2
echo %HELPPRJNAME% not exist.
goto :EXIT

:ERROR3
echo %HELPTOOL% not exist or it is not in the path.
goto :EXIT

:ERRORTOOL
echo %HELPPRJNAME%(1) : error:
type %HELPPRJSRCDIR%\%1.log"
goto :EXIT

:EXIT
REM Clean up
set HELPPRJNAME=
set HELPTOOL=
set HELPPRJSRCDIR=

pause

REM ---------------------------------------------------------------------------
REM $Log: 
REM  2    Biblioteka1.1         2004-10-07 12:40:56  Darko           added chm help
REM  1    Biblioteka1.0         2004-10-07 12:12:47  Darko           
REM $
