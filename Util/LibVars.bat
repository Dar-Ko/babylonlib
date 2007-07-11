@echo off
REM $Workfile: LibVars.bat$: batch command script
REM $Revision: 2$ $Date: 2005-05-11 22:08:27$
REM $Author: Darko$
REM
REM Mount default working drive
REM Note: Win32 specific
REM Copyright: CommonSoft Inc
REM 1999-06-07 Darko Kolakovic

REM Set default drive used by various tools and version control applications

set SRCPOOLROOT=\\Mayordomo\Babylon

if not exist %SRCPOOLROOT% goto ERROR1

if not exist S:\ net use S: \\Mayordomo\Babylon

goto END

:ERROR1
echo LibVars.bat(13) : error : %SRCPOOLROOT% folder not exist!
pause

:END

REM ---------------------------------------------------------------------------
REM $Log:
REM  1    Biblioteka1.0         2004-10-07 22:31:33  Darko
REM $
