@echo off
REM $Workfile: KCvsizer.bat$: batch command script file
REM $Revision: 2$ $Date: 2007-07-10 15:39:30$
REM $Author: Darko Kolakovic$
REM
REM Inserts a header paragraph with CVS keywords and footer text

CLS

TITLE Add CVS Header
COLOR 09

REM Set default values
set TmpListCCode=*.h;*.hpp;*.inl;*.c;*.cpp;*.cxx;*.idl;*.java;*.js;
set TmpAppendix=copyright.txt
REM File type description
set TmpHeaderFilteType1=declaration header file
set TmpHeaderFileType=implementation file

if "%1" == "-h" goto LBLSYNTAX
if "%1" == "-?" goto LBLSYNTAX
if "%1" == "/h" goto LBLSYNTAX
if "%1" == "/?" goto LBLSYNTAX

REM Validate appendix
if not "[%2]" == "[]" (set TmpAppendix=%2)
if not exist %TmpAppendix% @echo File %TmpAppendix% is missing.

REM List specified files and execute command on each
if not "[%1]" == "[]" (set TmpListCCode=%1)
@echo Add header to all %TmpListCCode% files.

REM File description in the header
if not "[%3]" == "[]" (set TmpHeaderFileType=%3)
if "[%3]" == "[2]" (set TmpHeaderFileType=%TmpHeaderFilteType1%)

REM Hack to avoid CVS keyword expansion if this file is under version control
set TmpCvsEscapeChar=$
pause


for /F "tokens=*" %%A in ('dir %TmpListCCode% /b') do for %%? in (%%A) do call :LBLEXECUTE %%?
goto LBLEXECUTEEND

:LBLEXECUTE
REM Insert the header
@echo %* file
@echo /*%TmpCvsEscapeChar%Workfile: $: %TmpHeaderFileType%> _tmpFile
@echo   %TmpCvsEscapeChar%Revision: $ %TmpCvsEscapeChar%Date: $>> _tmpFile
@echo   %TmpCvsEscapeChar%Author: $>> _tmpFile
@echo  */>> _tmpFile
type %* >> _tmpFile

REM Append the footer
REM Start the paragraph in the new line
@echo. >> _tmpFile
@echo /*------------------------------------------------------------------------------>> _tmpFile
@echo  *%TmpCvsEscapeChar%Log: $>> _tmpFile
@echo  */>> _tmpFile
if exist %TmpAppendix% type %TmpAppendix% >> _tmpFile

REM Create backup copy of the file in the question and replace the the original
if exist ~%* (del ~%*)
ren %* ~%*
ren _tmpFile %*

goto LBLTHEEND

:LBLEXECUTEEND
@echo _Fine_
goto LBLEND

REM Display the sintax of the command
:LBLSYNTAX
COLOR 02
@ECHO.
@ECHO $Workfile: KCvsizer.bat$ $Revision: 2$
@ECHO Add CVS header to source code files
@ECHO.
@ECHO Parameters: [FileExtensionsList] [AppendixFileName] [FileDescription]
@ECHO Default FileExtensionsList is: %TmpListCCode%
@ECHO Default AppendixFileName is: %TmpAppendix%
@ECHO Default FileDescription is: "%TmpHeaderFileType%"
@ECHO Note: parameters could not contain Space characters.
@ECHO.
@ECHO Example: Cvsizer *.h;*.cpp; gpl.txt declaration
@ECHO.
goto LBLEND2

:LBLEND
COLOR
:LBLEND2
TITLE Command Prompt
set TmpListCCode=
set TmpAppendix=
set TmpCvsEscapeChar=
set TmpHeaderFilteType1=
set TmpHeaderFileType=
:LBLTHEEND
REM ============================================================================
REM $Log: $
REM  1    Biblioteka1.0         2007-07-10 13:46:30  Darko Kolakovic


