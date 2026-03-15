<#
 .SYNOPSIS
	Trial 4
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
    [string]$Directory,

    # Default is English (US). Set to "All" to skip filtering.
    [string]$Language = "en-US"
)

Add-Type -AssemblyName PresentationCore

$Extensions = "*.ttf", "*.otf", "*.woff", "*.woff2"
$Files = Get-ChildItem -Path $Directory -Include $Extensions -Recurse -ErrorAction SilentlyContinue

# Convert string to the required XmlLanguage type for dictionary lookups
$TargetLang = [System.Windows.Markup.XmlLanguage]::GetLanguage($Language)
Write-Verbose "Scan fonts in $Directory..."
Write-Verbose "TargetLang = $TargetLang"

$Extensions = "*.ttf", "*.otf", "*.woff", "*.woff2"
$Files = Get-ChildItem -Path $Directory -Include $Extensions -Recurse -ErrorAction SilentlyContinue

$Files | ForEach-Object {
    $CurrentFile = $_
    try {
        # Directly load the font file as a GlyphTypeface for raw table access
        $GlyphType = New-Object System.Windows.Media.GlyphTypeface -ArgumentList $CurrentFile.FullName
        
        # Every font has at least one name record. We'll iterate through all available languages.
        foreach ($LangKey in $GlyphType.FamilyNames.Keys) {
            
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
} | Out-GridView -Title "Fonts in $Directory (Filter: $Language)"