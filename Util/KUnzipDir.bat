:: To actually include the path expansion character (tilde), I had to give valid numbers; see http://ss64.com/nt/rem.html for bug reference. Also, try call /? for more info.
@REM  batch script that will work for all zip files in the current folder (assuming 7zip is installed)
@REM The %~n0 extracts the name sans extension to use as output folder. 
@REM If you need full paths, use "%~dpn0". The -y forces overwriting by saying yes to everything. Or use -aoa to overwrite.
@REM Using `x` instead of `e` maintains dir structure (usually what we want)

@FOR /R %%a IN (*.zip) DO @(
    @if [%1] EQU [/y] (
        @7z x "%%a" -o"%%~dpna" -aoa
    ) else (
        @echo 7z x "%%a" -o"%%~dpna" -aoa
    )
)

@echo USAGE: Use /y to actually do the extraction