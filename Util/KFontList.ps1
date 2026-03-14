<#
 .SYNOPSIS
	Displays font metadata and other basic information on files in the given
	folder
 .PARAMETER Directory
    The path to the folder with font files
 .EXAMPLE
    pwsh .\KFontList.ps1 -Directory "C:\Windows\Fonts\" -Verbose
 .NOTES
    The script will overwrite existing target files.
    Handles files up to 1GB in size (PowerShell's default limit).
    The match operator uses regex - escape special characters (e.g., . becomes \.)
    for literal matching
 .OUTPUTS
    0: No error - The operation completed successfully.
    1: Fatal error - The operation failed due to a fatal error and did not complete.
#>

param (
    [Parameter(Mandatory=$true)]
    [string]$Directory
)

# Load the required .NET library for Font handling
Add-Type -AssemblyName PresentationCore

# Define the file extensions to look for
$Extensions = "*.ttf", "*.otf", "*.woff", "*.woff2", "*.shx", "*.zip", "*.7z"

# Get all matching files
$Files = Get-ChildItem -Path $Directory -Include $Extensions -Recurse -ErrorAction SilentlyContinue

$Files | ForEach-Object {
    $CurrentFile = $_
    
    # Check if it is a font file (PresentationCore can't read zip/7z/shx directly)
    if ($CurrentFile.Extension -match '\.(ttf|otf|woff2?)') {
        try {
            $Uri = New-Object System.Uri($CurrentFile.FullName)
            $FontFamilies = [System.Windows.Media.Fonts]::GetFontFamilies($Uri)

            foreach ($Family in $FontFamilies) {
                foreach ($Typeface in $Family.GetTypefaces()) {
                    
                    # Get the raw version/locale string (usually the first one)
                    $RawString = @($Typeface.VersionStrings.Values)[0]
                    
                    # Parse the string: [en-US, Regular] -> US and Regular
                    $Country = "N/A"
                    $Style = "N/A"
                    if ($RawString -match '\[\w{2}-(?<Country>\w{2}),\s*(?<Style>[^\]]+)\]') {
                        $Country = $Matches.Country
                        $Style = $Matches.Style
                    }

                    # Output the object (Becomes a row in GridView)
                    [PSCustomObject]@{
                        FileName = $CurrentFile.Name
                        Family   = $Family.Source
                        Country  = $Country
                        Style    = $Style
                        Path     = $CurrentFile.FullName
                    }
                }
            }
        } catch {
            # If the font file is corrupt or unreadable
            [PSCustomObject]@{ FileName = $CurrentFile.Name; Family = "Error Reading Font"; Country = "N/A"; Style = "N/A"; Path = $CurrentFile.FullName }
        }
    } else {
        # For non-font files (zip, 7z, shx), just list them
        [PSCustomObject]@{
            FileName = $CurrentFile.Name
            Family   = "Archive/Non-Font"
            Country  = "N/A"
            Style    = "N/A"
            Path     = $CurrentFile.FullName
        }
    }
} | Out-GridView -Title "Font and Archive Inventory: $Directory"
