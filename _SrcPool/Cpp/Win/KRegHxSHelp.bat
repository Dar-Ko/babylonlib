REM // $Workfile: KRegHxSHelp.bat$: batch command file
REM // $Revision: 2$ $Date: 2003-08-13 09:48:53$
REM // $Author: Darko$
REM //
REM // Register a help file to the help collection
REM // requires Microsoft Help 2.0 SDK
REM // %1 - fully qualified file name of compiled help file:  "X:\...\...\FileName.HxS"
REM // %2 - Description of the file in quotes: "My Book Example"
REM // %3 - Alias of the file: MYBOOK
REM // %4 - Name of the new or existing collection where %3 will be included: MyCollection
REM // Example: 
REM // KRegHxSHelp.bat "C:\bin\release\PDLTT.HxS" "PD Long Term Trending" PDLTT PDLTT
REM // Copyright: CommonSoft Inc
REM // 2003-08 Darko Kolakovic
REM ///////////////////////////////////////////////////////////////////////////
@ECHO OFF
REM Directory with Microsoft Help 2.0 (Hx...) tools
SET HXTOOLSPATH=C:\Program Files\Microsoft Help 2.0 SDK

REM Register the description for the namespace
"%HXTOOLSPATH%\HxReg.exe" -n %3 -c "%1"-d %2

REM Register the namespace 
"%HXTOOLSPATH%\HxReg.exe" -n %3 -i %4 -s "%1"

REM Test registration with DExplore viewer 
"C:\Program Files\Common Files\Microsoft Shared\Help\DExplore.exe" /helpcol ms-help://%4

SET HXTOOLSPATH=
REM ///////////////////////////////////////////////////////////////////////////
REM /*************************************************************************
REM  * $Log: 
REM  *  2    Biblioteka1.1         2003-08-13 09:48:53  Darko           comment
REM  *  1    Biblioteka1.0         2003-08-12 12:56:11  Darko           
REM  * $
REM  *************************************************************************/

 