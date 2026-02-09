#PowerShell script to save Windows 10 Spotlight screen images to a more accessible
#location.
#Windows Spotlight is a feature included by default in Windows 10 that downloads
#pictures and advertisements automatically from Bing and displays them when 
#the lock screen is being shown on a computer running Windows 10. 
#The majority of Windows' lock screen images and wallpapers come from Getty Images
# (http://www.gettyimages.com/).
#https://gist.github.com/ygra/eb379c339bae1914506f354ce5638f9e
#https://en.wikipedia.org/wiki/Windows_Spotlight
#https://support.microsoft.com/en-us/windows/wallpapers-5cfa0cc7-b75a-165a-467b-c95abaf5dc2a
#https://windows10spotlight.com/

$files = gci $Env:LocalAppData\Packages\Microsoft.Windows.ContentDeliveryManager_cw5n1h2txyewy\LocalState\Assets |
    where Length -gt 1kb
if ($files) {
    $shell = New-Object -ComObject Shell.Application
    #$folder = "$Env:USERPROFILE\Pictures\Spotlight"
    $Folder = [ System.Environment ]:: GetFolderPath('MyPictures') + '\Spotlight' ;
    if (!(Test-Path $folder)) { mkdir $folder }
    $files | % {
        $_ | Copy-Item -Destination $folder\$_.jpg
        Get-Item $folder\$_.jpg
    } | % {
        $namespace = $shell.namespace($folder)
        $item = $namespace.ParseName($_.Name)
        $size = $namespace.GetDetailsOf($item, 31)
        if ($size -match '(\d+) x (\d+)') {
            $width = [int]($Matches[1])
            $height = [int]($Matches[2])
        }
        if (!$size -or $width -lt 500 -or $height -lt 500) {
            Remove-Item $_
        }
    }
}
