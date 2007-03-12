@echo off
REM $Workfile: KSetThis.bat$: batch command script
REM $Revision: 1$ $Date: 2006-11-01 11:21:13$
REM $Author: Darko Kolakovic$
REM
REM Map current directory to working directory S:\.
REM Note: Microsoft Windows specific (Win32)
REM Copyright: CommonSoft Inc
REM 2006-10-07 Darko Kolakovic

if "%1" == "/help" goto LBLHELP
if "%1" == "/h" goto LBLHELP
if "%1" == "/?" goto LBLHELP

REM ----------------------------------------------------------------------------
:LBLSTART
if not "Empty%2" == "Empty" goto LBLHAVEDIR
if "%OS%" == "Windows_NT" goto LBLWIN32
goto :LBLONEXIT

REM Get the current directory --------------------------------------------------
:LBLWIN32
setlocal

REM Note: To get the full list of the predefined environment variables, type
REM       SET /? or HELP SET
if "%OS%" == "Windows_NT" set KCURDIR=%CD%
goto LBLCHECKDRIVE

REM Set the path to be substituted ---------------------------------------------
:LBLHAVEDIR
set KCURDIR=%2

REM ------------------
:LBLCHECKDRIVE
REM If the drive letter is not given, S: is assumed
if "Empty%1" == "Empty" set KDRIVE=S:
if not "Empty%1" == "Empty" set KDRIVE=%1

@echo %KCURDIR% => %KDRIVE%\
if not exist %KDRIVE%\ goto LBLSUBST

:LBLSUBST
subst %KDRIVE% %KCURDIR%
goto LBLONEXIT

REM ----------------------------------------------------------------------------
:LBLHELP
@echo $Workfile: KSetThis.bat$ $Revision: 1$
@echo Associates a directory path with a drive letter.
@echo      KSetThis [drive1: [path]]
@echo If the path is not given, the current working path is assumed.
@echo If the drive letter is not given, S: is assumed.
@echo Example: KSetThis
@echo Example: KSetThis s:
@echo Example: KSetThis s: "C:\New Folder\"
goto END

REM ----------------------------------------------------------------------------
:LBLONEXIT
REM Clean up
if "%OS%" == "Windows_NT" endlocal
::set KCURDIR=

:END
REM ---------------------------------------------------------------------------
REM $Log: 
REM  1    Biblioteka1.0         2006-11-01 11:21:13  Darko Kolakovic 
REM $
