#!/usr/bin/env pwsh
<#
 .SYNOPSIS
	Listing Font Properties; PowerShell script

 .DESCRIPTION
	Displays font metadata and other basic information on files in the given folder

 .PARAMETER

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
param()
<# To use write-verbose commandlet, run the script with -verbose parameter:
     <name>.ps1 -verbose
   (Note: CmdletBinding and param() are prerequiste)
   https://forums.powershell.org/t/listing-font-details/9230
#>

# To execute the script without agreeing with the execution policy
Set-ExecutionPolicy Bypass -Scope Process

#$folder = 'D:\temp\TTF\'
$folder = 'D:\temp\fonts_ps\ame\'
#$folder = 'C:\Windows\Fonts\'

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

#List all possible metadata for the files found in the folder
for ($attr = 0 ; $attr  -le 500; $attr++)
{
    $property = $objFolder.getDetailsOf($objFolder.items, $attr)
    if ( $property -and ( -not $attrList.Contains($property) ))
    {
        $attrList.add( $property, $attr )
        write-verbose "Property $($attr): $($property)"
    }
}

 #loop through all the fonts, and process
foreach($file in $objFolder.items())
{
    $fileList += $file
    write-verbose "`n$($fileList.Count). $($file.Name)"
    $name = $objFolder.getDetailsOf($file, $attrList["Name"])
    foreach( $item in $fontProperty)
    {
        $attrValue = $objFolder.getDetailsOf($file, $attrList[$item])
        write-verbose "Property $($item):id[$($attrList[$item])] = $($attrValue)"
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
$fileList | Select-Object $fontProperty |  out-gridview

