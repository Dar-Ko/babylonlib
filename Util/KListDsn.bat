@echo off
REM $CVSfile: $: batch command script
REM $Revision: 1.1 $ $Date: 2008/05/28 19:54:52 $
REM $Author: ddarko $
REM
REM List System or User Data Source Names (DSN)
REM Requirements:
REM   Windows NT, 2000, XP, 2003;
REM   Windows Console Registry Tool REG.EXE
REM See also: ODBC data source administrator utility
REM
REM Note: Microsoft Windows (Win32) specific
REM Copyright: CommonSoft Inc
REM 2006-11-07 Darko Kolakovic

REM ----------------------------------------------------------------------------
:LBLSTART

REM Check Windows version: batch file not suited for DOS, Win9x.
IF NOT "%OS%"=="Windows_NT" GOTO LBLSYNTAX

TITLE List DNS
COLOR 06

if "%1" == "-h" goto LBLSYNTAX
if "%1" == "-?" goto LBLSYNTAX
if "%1" == "/h" goto LBLSYNTAX
if "%1" == "/?" goto LBLSYNTAX
if "%1" == ""   goto LBLSYNTAX

if /i %1==system goto LBLSYSTEMLIST
if /i %1==user   goto LBLUSERLIST

@ECHO Error: Invalid command line parameter.
goto LBLSYNTAX

REM Browse System DNS
:LBLSYSTEMLIST
@ECHO.
@ECHO %1 DNS %2 List
if "%3"=="" (
  REG query "hklm\software\odbc\odbc.ini\%~2"
)else (
  REG query "hklm\software\odbc\odbc.ini\%~2"|FIND /I "%~3"
)
GOTO LBLEND

REM Browse USer DNS
:LBLUSERLIST
@ECHO.
@ECHO %1 DNS %2 List
if %3.==. (
  reg query "hkcu\software\odbc\odbc.ini\%~2"
)else (
  reg query "hkcu\software\odbc\odbc.ini\%~2"|FIND /I "%~3"
)
goto LBLEND


REM Display the sintax of the command
:LBLSYNTAX
COLOR 02
@ECHO.
@ECHO $Workfile:$ $Revision: 1.1 $
@ECHO Browse Data Source Names (DSN) used for ODBC
@ECHO.Requires Windows 2000+, reg.exe
@ECHO.
@ECHO Parameters: System/User ["DSN Name" [token]]
@ECHO   System    list system DSNs
@ECHO   User      list user DSNs
@ECHO   DSN Name  list all keys for specified DSN. Use quotes If the DSN name
@ECHO             contains spaces.
@ECHO   token     list all keys for specified DSN with key names or values
@echo             matching given token.
@ECHO Example: KListDsn system
@ECHO Example: KListDsn USER "ODBC Data Sources"
@ECHO Example: KListDsn USER "ODBC Data Sources" I
@ECHO.

goto LBLEND2

:LBLEND
COLOR
:LBLEND2
TITLE Command Prompt
IF "%OS%"=="Windows_NT" ENDLOCAL
:LBLTHEEND

REM ----------------------------------------------------------------------------
REM $Log: KListDsn.bat,v $
REM Revision 1.1  2008/05/28 19:54:52  ddarko
REM Created
REM

REM reg Console Registry Tool for Windows - version 3.0
REM REG Operation [Parameter List]
REM   Operation  [QUERY | ADD | DELETE | COPY | SAVE | LOAD | UNLOAD | RESTORE |
REM               COMPARE | EXPORT | IMPORT ]
REM
REM Return Code: (Except of REG COMPARE)
REM   0 - Succussful
REM   1 - Failed
REM For help on a specific operation type:
REM   REG Operation /?
REM Examples:
REM   REG QUERY /?
REM   REG ADD /?
REM   REG DELETE /?
REM   REG COPY /?
REM   REG SAVE /?
REM   REG RESTORE /?
REM   REG LOAD /?
REM   REG UNLOAD /?
REM   REG COMPARE /?
REM   REG EXPORT /?
REM   REG IMPORT /?
