@echo off
REM $RCSfile: KListAcl.bat,v $: batch command script
REM $Revision: 1.1 $ $Date: 2009/09/23 15:24:52 $
REM $Author: ddarko $
REM
REM Recursively displays access permissions (access control lists or ACL) of
REM directories
REM Requirements:
REM   Windows NT, 2000, XP, 2003;
REM   Windows Console Registry Tool REG.EXE
REM See also: ODBC data source administrator utility
REM
REM Note: Microsoft Windows (Win32) specific
REM Copyright: CommonSoft Inc
REM 2004-08-12 Darko Kolakovic

REM ----------------------------------------------------------------------------
:LBLSTART

REM Check Windows version: batch file not suited for DOS, Win9x.
IF NOT "%OS%"=="Windows_NT" GOTO LBLSYNTAX

TITLE List ACL
COLOR 06

if _%1_ == _-h_ goto LBLSYNTAX
if _%1_ == _-?_ goto LBLSYNTAX
if _%1_ == _/h_ goto LBLSYNTAX
if _%1_ == _/?_ goto LBLSYNTAX

REM Browse folder's ACL
:LBLPERMISSIONLIST
if _%1_ == __   set KACLTARGET=.
if not _%1_ == __   set KACLTARGET=%1

@ECHO.
cacls %KACLTARGET%
for /F "tokens=*" %%* in ('dir /b /ad "%KACLTARGET%"') do cacls "%KACLTARGET%\%%*"
GOTO LBLEND

REM Display the syntax of the command
:LBLSYNTAX
COLOR 02
@ECHO.
@ECHO $RCSfile: KListAcl.bat,v $ $Revision: 1.1 $
@ECHO Recursively displays directory access permissions (ACL)
@ECHO.Requires Windows 2000+, cacls.exe
@ECHO.
@ECHO Parameters:
@ECHO   Folder    8.3 directory name
@ECHO Example: KListAcl
@ECHO Example: KListAcl .\
@ECHO Example: KListAcl C:\Docume~1
@ECHO.

goto LBLEND2

:LBLEND
COLOR
:LBLEND2
TITLE Command Prompt
rem set KACLTARGET=
IF "%OS%"=="Windows_NT" ENDLOCAL
:LBLTHEEND

REM ----------------------------------------------------------------------------
REM $Log: KListAcl.bat,v $
REM Revision 1.1  2009/09/23 15:24:52  ddarko
REM Moved to repository
REM
REM

REM calc Displays or modifies access control lists (ACLs) of files
REM
REM CACLS filename [/T] [/E] [/C] [/G user:perm] [/R user [...]]
REM                [/P user:perm [...]] [/D user [...]]
REM    filename      Displays ACLs.
REM    /T            Changes ACLs of specified files in
REM                  the current directory and all subdirectories.
REM    /E            Edit ACL instead of replacing it.
REM    /C            Continue on access denied errors.
REM    /G user:perm  Grant specified user access rights.
REM                  Perm can be: R  Read
REM                               W  Write
REM                               C  Change (write)
REM                               F  Full control
REM    /R user       Revoke specified user's access rights (only valid with /E).
REM    /P user:perm  Replace specified user's access rights.
REM                  Perm can be: N  None
REM                               R  Read
REM                               W  Write
REM                               C  Change (write)
REM                               F  Full control
REM    /D user       Deny specified user access.
REM Wildcards can be used to specify more that one file in a command.
REM You can specify more than one user in a command.
REM
REM Abbreviations:
REM    CI - Container Inherit.
REM         The ACE will be inherited by directories.
REM    OI - Object Inherit.
REM         The ACE will be inherited by files.
REM    IO - Inherit Only.
REM         The ACE does not apply to the current file/directory.
