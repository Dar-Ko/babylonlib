#!/usr/bin/env pwsh
<#
 .SYNOPSIS
    List Font Properties; PowerShell script

 .DESCRIPTION
    Displays font metadata and other basic information of font files.

 .PARAMETER FontFolder
    The path to the input folder, default is the system font folder

 .EXAMPLE
    chmod +x KFontProperties.ps1
    pwsh KFontProperties.ps1  ~\fonts

 .NOTES
    Help:
    PS> Get-Help ./KFontProperties.ps1

 .LINK
    Ref.: https://forums.powershell.org/t/listing-font-details/9230/2
 #>

[CmdletBinding()]
param(
    # The path to the input folder, default is the system font folder
    [Parameter(Mandatory=$false, Position=0, HelpMessage="The path to the font folder")]
    [string]$FontFolder
)

<# To use Write-Verbose commandlet, run the script with -verbose parameter:
     <name>.ps1 -verbose
   (Note: CmdletBinding and param() are prerequiste)
   https://forums.powershell.org/t/listing-font-details/9230
#>

###############################################################################
<#
.SYNOPSIS
    Returns the default system font directory based on the current operating system.
.DESCRIPTION
    On Windows, the function returns "C:\Windows\Fonts".
    On Linux returns "/usr/share/fonts" and on macOS returns "/System/Library/Fonts".
    If the OS cannot be determined, it writes an error and returns $null.
.EXAMPLE
    $fontDir = Get-DefaultFontDirectory
    Write-Host "Default font directory: $fontDir"
.OUTPUTS
    System.String
    Returns the path as a string, or $null if the OS is not supported.
#>
function Get-DefaultFontDirectory {
    # PowerShell Core (versions 6+) runs on Windows, Linux, and macOS.
    # It provides automatic boolean variables $IsWindows, $IsLinux, and $IsMacOS.
    # Windows PowerShell (versions 5.1 and earlier) runs only on Windows and
    # does not have those automatic variables and pwsh returns them as $null.

    # PowerShell Core uses $IsWindows, $IsLinux, $IsMacOS.
    # For Windows PowerShell, we use [Environment]::OSVersion.Platform.
    if ($IsWindows -or `
            ([Environment]::OSVersion.Platform -eq [System.PlatformID]::Win32NT)) {
        return "C:\Windows\Fonts"
    }
    elseif ($IsLinux -or [Environment]::OSVersion.Platform -eq [System.PlatformID]::Unix) {
        # On Linux, system fonts are in /usr/share/fonts. Additional directories like
        # /usr/local/share/fonts or user‑specific ~/.fonts also exist.
        # If checking specifically for Ubuntu is needed, verify the presence
        # of /etc/lsb-release or running lsb_release -d

        return "/usr/share/fonts"
    }
    elseif ($IsMacOS -or [Environment]::OSVersion.Platform -eq [System.PlatformID]::MacOSX) {
        # Common system font locations on macOS
        return "/System/Library/Fonts"
    }
    else {
        Write-Error "Unsupported operating system." -ForegroundColor Red
        return $null
    }
}

###############################################################################
<#
.SYNOPSIS
    Main function to list font properties

.DESCRIPTION
    Displays font metadata and other basic information of font files.
    The script uses the Shell.Application COM object to access file properties,
    which allows it to retrieve a wide range of metadata for font files in
    the specified folder.
    The properties are then displayed in an interactive grid view.

.PARAMETER folder
    A path to a folder containing font files

.EXAMPLE
    winMain -folder "C:\Windows\Fonts"
.NOTES
    The script is designed to work primarily on Windows, as it relies on the
    Shell.Application COM object, which is specific to Windows.
#>
function winMain {
    param(
        [string]$folder = (Get-DefaultFontDirectory)
    )

    if (-not $folder) {
        # Take the current working folder as a safe fallback
        $folder = "."
    }

    try {
        $objShell = New-Object -ComObject Shell.Application


        $fileList = @()
        $attrList = @{}
        $fontProperty = ("Filename",
        # Properties for Windows\Fonts system folder, CLSID={BD84B380-8CA2-1069-AB1D-08000948F534}
        # (other folders have different set of properties)
                    "Name",
                    "Title",
                    "Type",
                    #"Item type", the property already exist
                    "Font style",
                    "Show/hide",
                    "Designed for",
                    "Category",
                    "Designer/foundry" ,
                    "Font embeddability",
                    "Font type",
                    "Family",
                    #"Date created",
                    "Date modified",
                    "Collection",
                    "Font file names",
                    "Font version",
                    "File version",
                    "Copyright",
                    "Authors",
                    "License description"
                    )


        $objFolder = $objShell.namespace($folder)

        # List all possible metadata for the files found in the folder
        for ($attr = 0 ; $attr  -le 500; $attr++)
        {
            $property = $objFolder.getDetailsOf($objFolder.items, $attr)
            if ( $property -and ( -not $attrList.Contains($property) ))
            {
                $attrList.add( $property, $attr )
                Write-Verbose "Property $($attr): $($property)"
            }
        }

        # Loop through all the fonts, and process
        foreach($file in $objFolder.items())
        {
            $fileList += $file
            Write-Verbose "`n$($fileList.Count). $($file.Name)"
            $name = $objFolder.getDetailsOf($file, $attrList["Name"])
            foreach( $item in $fontProperty)
            {
                $attrValue = $objFolder.getDetailsOf($file, $attrList[$item])
                Write-Verbose "Property $($item):id[$($attrList[$item])] = $($attrValue)"
                if ( $attrValue -ne  $name )
                #if ($attrList -contains $item)
                {
                    Add-Member -InputObject $file -MemberType NoteProperty -Name $item -value $attrValue -Force
                }
                elseif ($item -eq "Filename") #attrList doesn't contain item
                {
                    #If a property is not in the attrList then getDetailsOf(file, nul) returns value of the property indexed with 0
                    if ($attrList["Font file names"])
                    {
                        #We are (probably) working with Windows\Fonts system folder, CLSID={BD84B380-8CA2-1069-AB1D-08000948F534}
                        $fontPath = $objFolder.getDetailsOf($file, $attrList["Font file names"])
                        if($fontPath)
                        {
                            $attrValue = Split-Path $fontPath -leaf
                        }
                        else
                        {
                            $attrValue = "-multiple files"
                        }

                    }
                    else #We are working with folder with no system font properties
                    {
                        $attrValue = $file.Name
                    }
                    Add-Member -InputObject $file -MemberType NoteProperty -Name $item -value $attrValue -Force
                }
                elseif ($item -eq "Font file names")
                {
                    $attrValue = $file.Path
                    Add-Member -InputObject $file -MemberType NoteProperty -Name $item -value $attrValue -Force
                }

            }
        }

        #Open a listbox and show the result
        $fileList | Select-Object $fontProperty | Out-GridView -Title "Font Properties in $folder"
    }
    catch {
        Write-Error "Exception: $_"
        exit 1
    }
}

###############################################################################
<#
.SYNOPSIS
    Main function to list font properties

.DESCRIPTION
    Displays font metadata and other basic information of font files.
    The script uses the exiftool to access file properties,
    which allows it to retrieve a wide range of metadata for font files in
    the specified folder.

.PARAMETER folder
    A path to a folder containing font files

.EXAMPLE
    linMain -folder "/usr/share/fonts"
.NOTES
    The script relies on the exiftool command-line utility to retrieve
    detailed metadata for font files on Linux.
#>
function linMain {
    param(
        [string]$folder = (Get-DefaultFontDirectory)
    )

    if (-not $folder) {
        # Take the current working folder as a safe fallback
        $folder = "."
    }

    try {
        # Get a list font files
        $fontFiles = Get-ChildItem -Path $folder -Include "*.ttf", "*.ttc", "*.otf", "*.woff", "*.woff2" `
                     -Recurse -ErrorAction SilentlyContinue

        if ($fontFiles.Count -eq 0) {
            Write-Warning "No font files found in $folder"
            return 2
        }

        # Check if ExifTool is available
        $exifToolAvailable = $null -ne (Get-Command "exiftool" -ErrorAction SilentlyContinue)

        if ($exifToolAvailable) {
            # If ExifTool is available, we can retrieve more detailed metadata for each font file
            $results =foreach ($font in $fontFiles) {

                $fields = @(
                "-FontName", "-FullName", "-FontType", "-FontSubfamily",
                "-Designer", "-Manufacturer", "-FSType", "-FontFamily",
                "-Version", "-Copyright", "-License", "-NumFonts"
                )

                $metadata = & exiftool -j $fields `
                             $font.FullName 2>$null | ConvertFrom-Json

                [PSCustomObject]@{
                    FileName = $font.Name
                    FontName = $metadata.FontName
                    #FullName = $metadata.FullName
                    PostScriptName = if ($metadata.PostScriptFontName) {
                                            $metadata.PostScriptFontName } else { "N/A" }
                    Family = $metadata.FontFamily
                    Style = $metadata.FontSubfamily
                    Designer = $metadata.Designer
                    Manufacturer = $metadata.Manufacturer
                    Version = $metadata.Version
                    Copyright = $metadata.Copyright
                    License = $metadata.License
                    FontType = $metadata.FontType
                    Embeddability = $metadata.FSType
                    Collection = if ($metadata.NumFonts -gt 1) { "Yes ($($metadata.NumFonts) fonts)" } else { "No" }
                    DateModified = $font.LastWriteTime
                    FileSizeMB = [math]::Round($font.Length/1MB, 2)
               }

            }
        }
        else {
            Write-Warning "ExifTool is not available.`nInstall ExifTool to retrieve detailed font metadata."

        }
    # Display results;
    # on Linux/macOS, always use console table
    $results | Format-Table -AutoSize
    }
    catch {
        Write-Error "Exception: $_"
        exit 3
    }
}
###############################################################################

if (-not $FontFolder) {
    # Take the system font folder
    $FontFolder = (Get-DefaultFontDirectory)
}

# Execute the script without agreeing with the execution policy
if ($IsWindows -or [Environment]::OSVersion.Platform -eq [System.PlatformID]::Win32NT) {
    try {
        # Execute the script without agreeing with the execution policy
        Set-ExecutionPolicy Bypass -Scope Process -Force
        Write-Verbose "Execution policy set to Bypass for current Windows session"
    }
    catch {
        Write-Warning "Could not set execution policy: $_"
    }
    # Call the main function
    winMain $FontFolder
}
else {
    # On Linux/macOS, execution policy is not applicable
    # The script will run based on file permissions instead
    Write-Verbose "Non-Windows OS detected, skipping execution policy configuration"

    # Call the main function
    linMain $FontFolder

}

