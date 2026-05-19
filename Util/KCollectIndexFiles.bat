@echo off
REM Add all Index files recursively to the specified archive file.
REM Requires 7-Zip command line application.
REM Used 7-Zip commands:
REM a : Add files to archive
REM -mx[N] : set compression level: -mx1 (fastest) ... -mx9 (ultra)
REM -spf : use fully qualified file paths
REM -r[-|0] : Recourse subdirectories

setlocal
set "CIF_ARCHIVE=\\PA3HO\cabe3\CaBe3\Catalogus\_0Index.7z"
set "CIF_SOURCEFILTER=\\PA3HO\cabe3\CaBe3\_*Index.tsv"

REM Check if source file exists
if exist "%CIF_ARCHIVE%" (
    echo Creating backup of "%CIF_ARCHIVE%"...
    copy %CIF_ARCHIVE% %CIF_ARCHIVE%.bak
)

REM Gather and archive all index files 
7z a -mx9 -spf2 -r %CIF_ARCHIVE%  %CIF_SOURCEFILTER%

REM Make 2nd set of index files
set "CIF_ARCHIVE=\\PA3HO\cabe3\CaBe3\Catalogus\_01Index.7z"
set "CIF_SOURCEFILTER=\\PE3EPBOAP\TPE3OP\CaBe3\_*Index.tsv"

REM Check if source file exists
if exist "%CIF_ARCHIVE%" (
    echo Creating backup of "%CIF_ARCHIVE%"...
    copy %CIF_ARCHIVE% %CIF_ARCHIVE%.bak
)

REM Gather and archive all index files 
7z a -mx9 -spf2 -r %CIF_ARCHIVE%  %CIF_SOURCEFILTER%

endlocal