@echo off
REM $Workfile: KUnPack.bat$: Batch command script file
REM $Revision: 1$ $Date: 2007-07-10 15:44:34$
REM $Author: Darko Kolakovic$
REM
REM Unpack compressed files in every subdirectory.
REM Requirements:
REM Windows NT, 2000, XP, 2003; UnRar.exe (part of WinRar application)

CLS
REM Check Windows version: batch file not suited for DOS, Win9x.
IF NOT "%OS%"=="Windows_NT" GOTO LBLSYNTAX

TITLE Unpack archives
COLOR 09

if "%1" == "-h" goto LBLSYNTAX
if "%1" == "-?" goto LBLSYNTAX
if "%1" == "/h" goto LBLSYNTAX
if "%1" == "/?" goto LBLSYNTAX

::Localize variables
SETLOCAL

:: .RAR files
::SET PATH="C:\Program Files\WinRAR\";%PATH%
::SET TmpArchCmd=UnRar.exe e
:: .ZIP; .JAR files (xf - extract,  tf - browse)
SET TmpArchCmd=jar xf


REM Check command line arguments
IF "[%1]"=="[]" (SET TmpArchFileFiilter=*.zip;*.jar) ELSE (SET TmpArchFileFiilter=%1)

:: Unpack each archive in the directory tree
FOR /F %%k IN ('dir /s /b %TmpArchFileFiilter%') DO CALL :LBLEXECUTE "%%k"
GOTO LBLEXECUTEEND

:LBLEXECUTE
@ECHO %~p1%TmpArchFileFiilter%
DIR %~p1%TmpArchFileFiilter% /b

CHOICE /T:y,3 Unpack?
:: if choice is No, skip execution
IF ERRORLEVEL 2 GOTO LBLTHEEND
::% ~dpI expands %I to a drive and path; see FOR help
::Bug Note: percent~dpI in the comment line causes error 'substitution is invalid: % ~dpI'
CD "%~dp1"
%TmpArchCmd% %~nx1
DEL %~nx1
CD ..

GOTO LBLTHEEND

:LBLEXECUTEEND
@ECHO _Fine_
GOTO LBLEND

REM Display the syntax of the command
:LBLSYNTAX
COLOR 02
@ECHO.
@ECHO $Workfile: KUnPack.bat$ $Revision: 1$
@ECHO Unpack archives in current directory and all subdirectories.
@ECHO.Requires Windows 2000+, UnRar.exe or JRE
@ECHO.
@ECHO Parameters: [FileExtensionsList]
@ECHO Example: KUnpack *.zip;*.rar
@ECHO.
goto LBLEND2

:LBLEND
COLOR
:LBLEND2
TITLE Command Prompt
IF "%OS%"=="Windows_NT" ENDLOCAL
:LBLTHEEND
REM ============================================================================
REM $Log: 
REM  1    Biblioteka1.0         2007-07-10 15:44:34  Darko Kolakovic 
REM $

REM Archiver for .rar files
REM UNRAR 3.42 freeware
REM Usage:     unrar <command> -<switch 1> -<switch N> <archive> <files...>
REM                <@listfiles...> <path_to_extract\>
REM
REM <Commands>
REM   e             Extract files to current directory
REM   l[t,b]        List archive [technical, bare]
REM   p             Print file to stdout
REM   t             Test archive files
REM   v[t,b]        Verbosely list archive [technical,bare]
REM   x             Extract files with full path
REM
REM <Switches>
REM   -             Stop switches scanning
REM   ac            Clear Archive attribute after compression or extraction
REM   ad            Append archive name to destination path
REM   ap<path>      Set path inside archive
REM   av-           Disable authenticity verification check
REM   c-            Disable comments show
REM   cfg-          Disable read configuration
REM   cl            Convert names to lower case
REM   cu            Convert names to upper case
REM   dh            Open shared files
REM   ep            Exclude paths from names
REM   ep3           Expand paths to full including the drive letter
REM   f             Freshen files
REM   idp           Disable percentage display
REM   ierr          Send all messages to stderr
REM   inul          Disable all messages
REM   ioff          Turn PC off after completing an operation
REM   kb            Keep broken extracted files
REM   o+            Overwrite existing files
REM   o-            Do not overwrite existing files
REM   oc            Set NTFS Compressed attribute
REM   ow            Save or restore file owner and group
REM   p[password]   Set password
REM   p-            Do not query password
REM   r             Recurse subdirectories
REM   ta<date>      Process files modified after <date> in YYYYMMDDHHMMSS format
REM   tb<date>      Process files modified before <date> in YYYYMMDDHHMMSS format
REM   tn<time>      Process files newer than <time>
REM   to<time>      Process files older than <time>
REM   ts<m,c,a>[N]  Save or restore file time (modification, creation, access)
REM   u             Update files
REM   v             List all volumes
REM   ver[n]        File version control
REM   vp            Pause before each volume
REM   x<file>       Exclude specified file
REM   x@            Read file names to exclude from stdin
REM   x@<list>      Exclude files in specified list file
REM   y             Assume Yes on all queries

REM Archiver for .jar; .zip files (part of Java Run-time Environment JRE)
REM Usage: jar {ctxu}[vfm0Mi] [jar-file] [manifest-file] [-C dir] files ...
REM Options:
REM     -c  create new archive
REM     -t  list table of contents for archive
REM     -x  extract named (or all) files from archive
REM     -u  update existing archive
REM     -v  generate verbose output on standard output
REM     -f  specify archive file name
REM     -m  include manifest information from specified manifest file
REM     -0  store only; use no ZIP compression
REM     -M  do not create a manifest file for the entries
REM     -i  generate index information for the specified jar files
REM     -C  change to the specified directory and include the following file
REM If any file is a directory then it is processed recursively.
REM The manifest file name and the archive file name needs to be specified
REM in the same order the 'm' and 'f' flags are specified.
REM
REM Example 1: to archive two class files into an archive called classes.jar:
REM        jar cvf classes.jar Foo.class Bar.class
REM Example 2: use an existing manifest file 'mymanifest' and archive all the
REM            files in the foo/ directory into 'classes.jar':
REM        jar cvfm classes.jar mymanifest -C foo/ .
REM Example 3: unpack archive
REM        jar xvf MyArchive.zip
