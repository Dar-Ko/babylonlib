<#
 .SYNOPSIS
    Trial 5
    Displays font metadata and other basic information on files in the given
    folder
 .PARAMETER Directory
    The path to the folder with font files
 .PARAMETER Language
    Filter the FontFamilies collection by language. Default language is en-US".
    If the font has not the required language is not available, the first available
    will be presented. To disable filtering, set the value to "All".
 .EXAMPLE
    pwsh .\KFontList.ps1 -Directory "C:\Windows\Fonts\" -Verbose
    pwsh .\KFontList.ps1 -Directory "C:\Windows\Fonts\" -Locale "ja-jp"
    pwsh .\KFontList.ps1 -Directory "C:\Windows\Fonts\" -Locale "All"
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
    # The path to the input folder
    [Parameter(Mandatory=$true)]
    [string]$Directory,
    #Filter the FontFamilies collection by language.
    # Default is English (US). Set to "All" to skip filtering.
    [string]$Language = "en-US"
)


#[System.Windows.Media.GlyphTypeface]

# Set the preference to 'Continue' to display verbose messages
# If the user runs the script with -Verbose, this becomes 'Continue' automatically
# $VerbosePreference = "Continue"

Add-Type -AssemblyName PresentationCore

# Convert string to the required XmlLanguage type for dictionary lookups
$TargetLang = [System.Windows.Markup.XmlLanguage]::GetLanguage($Language)
Write-Verbose "Scan fonts in $Directory..."
Write-Verbose "TargetLang = $TargetLang"

# Define the file extensions to look for
$Extensions = "*.ttf", "*.otf", "*.woff", "*.woff2"
# Get all matching files
$Files = Get-ChildItem -Path $Directory -Include $Extensions -Recurse `
        -ErrorAction SilentlyContinue

<# Note: To stream data into Out-GridView from a loop, you must use
  the ForEach-Object cmdlet (the pipeline version) rather than
  the foreach ($item in $collection) statement
 #>
$Files | ForEach-Object {
    # Process each file
    $CurrentFile = $_
    # Check if it is a font file (PresentationCore can't read zip/7z/shx directly)
    try {
        # Directly load the font file as a GlyphTypeface for raw table access
        $GlyphType = New-Object System.Windows.Media.GlyphTypeface -ArgumentList $CurrentFile.FullName

        # Every font has at least one name record. We'll iterate through all available languages.

            $LangTag = $LangKey.IetfLanguageTag

            # Helper function to safely pull from dictionaries or fall back
            function Get-FontValue($Dict, $Key) {
                if ($null -eq $Dict) { return "N/A" }
                if ($Dict.ContainsKey($Key)) { return $Dict[$Key] }
                return ($Dict.Values | Select-Object -First 1)
            }

            # Extract fields directly from the GlyphTypeface object
            $FamilyName = Get-FontValue $GlyphType.FamilyNames $LangKey
            $FaceName   = Get-FontValue $GlyphType.FaceNames $LangKey
            $Copyright  = Get-FontValue $GlyphType.Copyrights $LangKey
            $VersionStr = Get-FontValue $GlyphType.VersionStrings $LangKey
            
            # Parse the Locale [en-US, Regular] from the version strings
            $Country = "N/A"; $ParsedStyle = "N/A"
            $AllVersions = ($GlyphType.VersionStrings.Values -join " ")
            if ($AllVersions -match '\[\w{2}-(?<Country>\w{2}),\s*(?<Style>[^\]]+)\]') {
                $Country = $Matches.Country
                $ParsedStyle = $Matches.Style
            }

            [PSCustomObject]@{
                FamilyName = $FamilyName
                FaceName   = $FaceName
                Language   = $LangTag
                Version    = $VersionStr
                Copyright  = $Copyright
                Country    = $Country
                Parsed     = $ParsedStyle
                FileName   = $CurrentFile.Name
                URI        = $CurrentFile.FullName
            }
        }
    } catch {
        Write-Verbose "Could not parse: $($CurrentFile.Name): $($_.Exception.Message)"
    }
} | Out-GridView -Title "$Directory (Filter: $Language)"