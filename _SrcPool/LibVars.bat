@echo off
REM $Workfile: LibVars.bat$: batch command script
REM $Revision: 1$ $Date: 2004-10-07 21:31:33$
REM $Author: Darko$
REM
REM Mount default working drive
REM Note: Win32 specific
REM Copyright: CommonSoft Inc
REM 1999-06-07 Darko Kolakovic

REM Set default drive used by various tools and version control applications


if not exist S:\ subst S: F:\Biblioteka

REM ---------------------------------------------------------------------------
REM $Log: 
REM  1    Biblioteka1.0         2004-10-07 21:31:33  Darko           
REM $
