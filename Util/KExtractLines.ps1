<#
 .SYNOPSIS
    Extract lines from a source file containing a specific keyword and saves 
    them to a target file
 .PARAMETER SourceFile
    The path to the input file
 .PARAMETER Keyword
    The keyword to search for
 .PARAMETER TargetFile
    The path to the output file
 .EXAMPLE
    pwsh .\KExtractLines.ps1 -SourceFile "input.txt" -Keyword "error" -TargetFile "output.txt"
 .NOTES
    The script will overwrite existing target files.
    Handles files up to 1GB in size (PowerShell's default limit).
    The match operator uses regex - escape special characters (e.g., . becomes \.)
    for literal matching
 .OUTPUTS
    0: No error - The operation completed successfully.
    1: Fatal error - The operation failed due to a fatal error and did not complete.
#>

param(
    # The path to the input file
    [Parameter(Mandatory=$true)]
    [string]$SourceFile,
    
    # The keyword to search for
    [Parameter(Mandatory=$true)]
    [string]$Keyword,
    
    # The path to the output file
    [Parameter(Mandatory=$true)]
    [string]$TargetFile
)

try {
    # Read source file and filter lines containing the keyword (case-insensitive)
    $matchingLines = Get-Content $SourceFile | Where-Object { $_ -match $Keyword }
    # Case-sensitive search
    # $matchingLines = Get-Content $SourceFile | Where-Object { $_ -cmatch $Keyword }

    # Save results to target file
    $matchingLines | Out-File $TargetFile
    
    Write-Host "Success! Found $($matchingLines.Count) matching lines saved to $TargetFile"
}
catch {
    Write-Host "Error: $_" -ForegroundColor Red
    exit 1
}