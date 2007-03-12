@echo off
REM $Workfile: KErrLvl.bat$: batch command script
REM $Revision: 1$ $Date: 2006-11-01 11:21:11$
REM $Author: Darko Kolakovic$
REM
REM Obtain the exit codes (ERRORLEVEL) returned by commands.
REM Note: DOS, Microsoft Windows (Win32) specific
REM Copyright: CommonSoft Inc
REM 2006-10-07 Darko Kolakovic

REM Not every command or console application return the exit code, but if does,
REM the most used convention is that 0 means successful command execution and
REM any positive number is error code of a failure.
REM Note: Some applications return a negative number as error code, specially in
REM WinNT, Win2k environment.

REM Note: 'IF ERRORLEVEL' statement returns TRUE if the return code was
REM equal to or higher than the specified ERRORLEVEL

REM WinNT specific: The value of the exit code of the last command returned one
REM is stored in the environment variable %ERRORLEVEL%.

REM WinNT, Win2k, WinXP specific: the SET command itself returns 0, if successful

if "%1" == "" goto LBLHELP
if "%1" == "/help" goto LBLHELP
if "%1" == "/h" goto LBLHELP
if "%1" == "/?" goto LBLHELP

REM Set the command line with up to 9 arguments.
REM Check first none or only one argument, as most probable case
if "%2" == "" goto LBLARG0
if "%3" == "" goto LBLARG1
if "%4" == "" goto LBLARG2
if "%5" == "" goto LBLARG3
if "%6" == "" goto LBLARG4
if "%7" == "" goto LBLARG5
if "%8" == "" goto LBLARG6
if "%9" == "" goto LBLARG7
if not "%9" == "" set KCMDLINE=%1 %2 %3 %4 %5 %6 %7 %8 %9
goto LBLSTART

REM Store the command and command arguments
:LBLARG0
set KCMDLINE=%1
goto LBLSTART
:LBLARG1
set KCMDLINE=%1 %2
goto LBLSTART
:LBLARG2
set KCMDLINE=%1 %2 %3
goto LBLSTART
:LBLARG3
set KCMDLINE=%1 %2 %3 %4
goto LBLSTART
:LBLARG4
set KCMDLINE=%1 %2 %3 %4 %5
goto LBLSTART
:LBLARG5
set KCMDLINE=%1 %2 %3 %4 %5 %6
goto LBLSTART
:LBLARG6
set KCMDLINE=%1 %2 %3 %4 %5 %6 %7
goto LBLSTART
:LBLARG7
set KCMDLINE=%1 %2 %3 %4 %5 %6 %7 %8
goto LBLSTART
:LBLARG8
set KCMDLINE=%1 %2 %3 %4 %5 %6 %7 %8 %9

REM ----------------------------------------------------------------------------
:LBLSTART
@echo The command:
@echo "%KCMDLINE%"

REM Execute the command
%KCMDLINE% > NUL

REM Check returned code
if ERRORLEVEL == 255 goto LBL255
if ERRORLEVEL == 128 goto LBL128
if ERRORLEVEL ==  64 goto LBL064
if ERRORLEVEL ==  32 goto LBL032
if ERRORLEVEL ==  16 goto LBL016
if ERRORLEVEL ==  15 goto LBL015
if ERRORLEVEL ==  14 goto LBL014
if ERRORLEVEL ==  13 goto LBL013
if ERRORLEVEL ==  12 goto LBL012
if ERRORLEVEL ==  11 goto LBL011
if ERRORLEVEL ==  10 goto LBL010
if ERRORLEVEL ==   9 goto LBL009
if ERRORLEVEL ==   8 goto LBL008
if ERRORLEVEL ==   7 goto LBL007
if ERRORLEVEL ==   6 goto LBL006
if ERRORLEVEL ==   5 goto LBL005
if ERRORLEVEL ==   4 goto LBL004
if ERRORLEVEL ==   3 goto LBL003
if ERRORLEVEL ==   2 goto LBL002
if ERRORLEVEL ==   1 goto LBL001
if ERRORLEVEL ==   0 goto LBL000
set KCMDEXIT=nothing
goto LBLONEXIT

:LBL255
set KCMDEXIT=255 or greater
goto LBLONEXIT
:LBL128
set KCMDEXIT=128 or greater
goto LBLONEXIT
:LBL064
set KCMDEXIT=64 or greater
goto LBLONEXIT
:LBL032
set KCMDEXIT=32 or greater
goto LBLONEXIT
:LBL016
set KCMDEXIT=16
goto LBLONEXIT
:LBL015
set KCMDEXIT=15
goto LBLONEXIT
:LBL014
set KCMDEXIT=14
goto LBLONEXIT
:LBL013
set KCMDEXIT=13
goto LBLONEXIT
:LBL012
set KCMDEXIT=12
goto LBLONEXIT
:LBL011
set KCMDEXIT=11
goto LBLONEXIT
:LBL010
set KCMDEXIT=10
goto LBLONEXIT
:LBL009
set KCMDEXIT=9
goto LBLONEXIT
:LBL008
set KCMDEXIT=8
goto LBLONEXIT
:LBL007
set KCMDEXIT=7
goto LBLONEXIT
:LBL006
set KCMDEXIT=6
goto LBLONEXIT
:LBL005
set KCMDEXIT=5
goto LBLONEXIT
:LBL004
set KCMDEXIT=4
goto LBLONEXIT
:LBL003
set KCMDEXIT=3
goto LBLONEXIT
:LBL002
set KCMDEXIT=2
goto LBLONEXIT
:LBL001
set KCMDEXIT=1
goto LBLONEXIT
:LBL000
set KCMDEXIT=0

goto LBLONEXIT

REM ----------------------------------------------------------------------------
:LBLHELP
@echo $Workfile: KErrLvl.bat$ $Revision: 1$
@echo Returns the exit code of an executed command.
@echo Example: KErrLvl dir . /qwerty
@echo Example: KErrLvl dir c:\

goto END

REM ----------------------------------------------------------------------------
:LBLONEXIT
@echo returned %KCMDEXIT%.

REM Clean up
set KCMDLINE=
set KCMDEXIT=

:END
REM ---------------------------------------------------------------------------
REM $Log: 
REM  1    Biblioteka1.0         2006-11-01 11:21:11  Darko Kolakovic 
REM $
