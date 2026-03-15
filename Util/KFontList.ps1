<#
 .SYNOPSIS
	Trial 3
	Displays font metadata and other basic information on files in the given
	folder
 .PARAMETER Directory
    The path to the folder with font files
 .EXAMPLE
    pwsh .\KListFonts.ps1 -Directory "C:\Windows\Fonts\" -Verbose
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
    [string]$Language = "jp-JP"
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
        $Uri = [System.Uri]$CurrentFile.FullName
        $FontFamilies = [System.Windows.Media.Fonts]::GetFontFamilies($Uri)

        foreach ($Family in $FontFamilies) {
            # SAFETY CHECK: Ensure FamilyNames is not null
            if ($null -eq $Family.FamilyNames) { continue }

            foreach ($LangKey in $Family.FamilyNames.Keys) {
                $LangTag = $LangKey.IetfLanguageTag
                $FamilyName = $Family.FamilyNames[$LangKey]

                foreach ($Typeface in $Family.GetTypefaces()) {
                    
                    # 1. Safe FaceName Retrieval
                    $FaceName = "N/A"
                    if ($null -ne $Typeface.FaceNames) {
                        $FaceName = if ($Typeface.FaceNames.ContainsKey($LangKey)) { $Typeface.FaceNames[$LangKey] } else { @($Typeface.FaceNames.Values)[0] }
                    }

                    # 2. Safe Copyright Retrieval
                    $Copyright = "N/A"
                    if ($null -ne $Family.Copyrights) {
                        $Copyright = if ($Family.Copyrights.ContainsKey($LangKey)) { $Family.Copyrights[$LangKey] } else { @($Family.Copyrights.Values)[0] }
                    }

                    # 3. Safe Version Retrieval
                    $Version = "N/A"
                    if ($null -ne $Typeface.VersionStrings) {
                        $Version = if ($Typeface.VersionStrings.ContainsKey($LangKey)) { $Typeface.VersionStrings[$LangKey] } else { @($Typeface.VersionStrings.Values)[0] }
                    }

                    # 4. Parse Locale [en-US, Regular]
                    $Country = "N/A"; $ParsedStyle = "N/A"
                    if ($null -ne $Typeface.VersionStrings) {
                        $RawLocale = @($Typeface.VersionStrings.Values) -join " "
                        if ($RawLocale -match '\[\w{2}-(?<Country>\w{2}),\s*(?<Style>[^\]]+)\]') {
                            $Country = $Matches.Country; $ParsedStyle = $Matches.Style
                        }
                    }

                    [PSCustomObject]@{
                        FileName   = $CurrentFile.Name
                        FamilyName = $FamilyName
                        FaceName   = $FaceName
                        Language   = $LangTag
                        Version    = $Version
                        Copyright  = $Copyright
                        Country    = $Country
                        Parsed     = $ParsedStyle
                        URI        = $Uri.AbsoluteUri
                    }
                }
            }
        }
    } catch {
        Write-Verbose "Could not parse: $($CurrentFile.Name): $($_.Exception.Message)"
    }
} | Out-GridView -Title "Fonts in $Directory (Filter: $Language)"