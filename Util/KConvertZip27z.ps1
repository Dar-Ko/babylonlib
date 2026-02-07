<#
 .SYNOPSIS
	Convert all .zip archives to .7z
 .PARAMETER directoryToScan
	Folder to browse or file for archives
 .EXAMPLE
	chmod +x KConvertZip27z.ps1
	pwsh KConvertZip27z.ps1  ~\Documents
 .NOTES
	Help:
	PS> Get-Help ./KConvertZip27z.ps1 -full
 .NOTES
	Add the directory with 7z binaries to the PATH environment variable.
	Help:
	PS> Get-Help ./KConvertZip27z.ps1 -full
 .OUTPUTS
	0: No error - The operation completed successfully.
	2: Fatal error - The operation failed due to a fatal error and did not complete.
#>

##requires -PSEdition Core
# Folder to browse or file for archives
param ([Parameter(Mandatory)]$directoryToScan)

<##############################################################################
.SYNOPSIS
	Prompts the user for an action after error
.OUTPUTS
	- true : proceed with the execution
	- false : break the execution
#>
function OnErrorPrompt()
	{
	# Wait for user input
	Write-Host  "Proceed with the conversion? [y/n] " -ForegroundColor Yellow -NoNewline
	$userInput = Read-Host
	switch($userInput)
		{
		{$_ -in '1','y','yes','T','true'}
			{
			return $true
			}
		default
			{
			return $false
			}
		}
	}

###############################################################################
### PowerShell script

# Generate an unique folder name where archives will be unpacked
$tmpDir = ("{0:X}" -f [DateTime]::Now.Ticks) + ".TMP"
# The format of the archive and archive file extension
New-Variable -Name extSource -Value "zip" -Option Constant

try
	{
	# Prerequisite:
	# Check if the 7-Zip executable is installed and available in the system path
	$sevenZipCommand = "7z"

	# Try to get the version of 7-Zip
	$version = & $sevenZipCommand | Select-String "7-Zip"
	if ($version) 
		{
		Write-Host $version
		}
	else
		{
		throw "7-Zip is not installed."
		}
	
	# Check if the path exists
	if (-not (Test-Path -Path $directoryToScan))
		{
		throw "ERROR: '$directoryToScan' does not exist."
		}
	# Check if the directoryToScan is a directory
	if (Test-Path -Path $directoryToScan -PathType Container)
		{
			Write-Host "Convert archives from" $directoryToScan

			# Create a temporary subfolder where archives will be unpacked. Absolute path is required.
			# Out-Null equivalent to '>/dev/null' (Linux) or '>null' (Windows)
			$tmpDir = Join-Path -Path (Resolve-Path -Path $directoryToScan) -ChildPath $tmpDir
			New-Item -Path $tmpDir -ItemType Directory | Out-Null

			# Get all .zip files in the specified folder. Note that the filter is case-insensitive by default.
			$archiveFiles = Get-ChildItem -Path $directoryToScan -Filter *.$extSource -Recurse -ErrorAction SilentlyContinue -Force

			# Loop through every archive
			foreach ($file in $archiveFiles) 
				{
				$archiveName = [System.IO.Path]::GetFileNameWithoutExtension($file.Name)

				Write-Host "Extract: $file"
				$unpackedFilesDir = $(Join-Path -Path $tmpDir -ChildPath $archiveName)
				# 7z outputs some errors to stderr and some to stdout. Redirection of stderr is desirable ( 2>&1 in example )
				# Example: 7z x -bso1 -bsp0  -o/home/user/Temp ~/Temp/file.zip 2>&1 | grep "ERROR:"
				# Note: the output directory specified with -o have to be absolute path.
				& $sevenZipCommand x -bso0 -bsp0 "-o$unpackedFilesDir" $file 2>&1 | Select-String "ERROR:"
				if ($LASTEXITCODE -ne 0)
					{
					# 7z returns with an error
					if(-not (OnErrorPrompt))
						{
						throw "ERROR: 7z exit code $LASTEXITCODE"
						}
					#Pause
					}
				else
					{
					#Dbg: Write-Host "=> $(Join-Path -Path $([System.IO.Path]::GetDirectoryName($file)) -ChildPath "$archiveName.7z") $unpackedFilesDir/*"
					# Add the files to 7z archive
					& $sevenZipCommand a -bso0 -bsp0 `
						$(Join-Path -Path $([System.IO.Path]::GetDirectoryName($file)) -ChildPath "$archiveName.7z") `
						$($unpackedFilesDir + [IO.Path]::DirectorySeparatorChar + "*") 2>&1 | Select-String "ERROR:"
					if ($LASTEXITCODE -ne 0)
						{
						# 7z returns with an error
						if((OnErrorPrompt) -eq $false)
							{
							throw "ERROR: 7z exit code $LASTEXITCODE"
							}
						# Delete temporrary subfolder to save storage space for the next iteration
						Remove-Item -Path $unpackedFilesDir -Recurse -Force
						}
					}
				}
		

		}
	else
		{
		# The directoryToScan parameter is a file name
		if([System.IO.Path]::GetExtension($directoryToScan) -eq $extSource)
			{
			$filePath = [System.IO.Path]::GetDirectoryName($directoryToScan)

			# Create a temporary folder where archives will be unpacked
			$tmpDir = Join-Path -Path $filePath -ChildPath $tmpDir
			New-Item -Path $tmpDir -ItemType Directory | Out-Null
			}
		else
			{
			# Verify the file consistency
			}
		}

	}
catch
	{
	Write-Error $_
	Write-Error $_.ScriptStackTrace

	# Clean the leftovers
	if (Test-Path -Path $tmpDir)
		{
		Remove-Item -Path $tmpDir -Recurse -Force
		}

	exit 2; # The operation failed due to a fatal error and did not complete.
	}

# Delete the temporary folder
if (Test-Path -Path $tmpDir)
	{
	Remove-Item -Path $tmpDir -Recurse -Force
	}

<##############################################################################
  Note: 7z usage
	7z <command> [<switches>...] <archive_name> [<file_names>...] [<@listfiles...>]
	where:
	<command>
	  a : Add files to archive
	  b : Benchmark
	  d : Delete files from archive
	  e : Extract files from archive (without using directory names)
	  h : Calculate hash values for files
	  i : Show information about supported formats
	  l : List contents of archive
	  rn : Rename files in archive
	  t : Test integrity of archive
	  u : Update files to archive
	  x : eXtract files with full paths

	<switches>
	  -- : Stop switches parsing
	  -ai[r[-|0]]{@listfile|!wildcard} : Include archives
	  -ax[r[-|0]]{@listfile|!wildcard} : eXclude archives
	  -ao{a|s|t|u} : set Overwrite mode
	  -an : disable archive_name field
	  -ba : ouput short validations only
	  -bb[0-3] : set output log level
	  -bd : disable progress indicator
	  -bs{o|e|p}{0|1|2} : set output stream for output/error/progress line
	  -bso0 -bsp0 : output nothing, but errors 
	  -bt : show execution time statistics
	  -i[r[-|0]]{@listfile|!wildcard} : Include filenames
	  -m{Parameters} : set compression Method
	  -o{Directory} : set Output directory
	  -p{Password} : set Password
	  -r[-|0] : Recurse subdirectories
	  -sa{a|e|s} : set Archive nam
	  -scc{UTF-8|WIN|DOS} : set charset for for console input/output
	  -scs{UTF-8|UTF-16LE|UTF-16BE|WIN|DOS|{id}} : set charset for list files
	  -scrc[CRC32|CRC64|SHA1|SHA256|*] : set hash function for x, e, h commands
	  -sdel : delete files after compression
	  -seml[.] : send archive by email
	  -sfx[{name}] : Create SFX archive
	  -si[{name}] : read data from stdin
	  -slp : set Large Pages mode
	  -slt : show technical information for l (List) command
	  -snh : store hard links as links
	  -snl : store symbolic links as links
	  -sni : store NT security information
	  -sns[-] : store NTFS alternate streams
	  -so : write data to stdout
	  -spd : disable wildcard matching for file names
	  -spe : eliminate duplication of root folder for extract command
	  -spf : use fully qualified file paths
	  -ssc[-] : set sensitive case mode
	  -ssw : compress shared files
	  -stl : set archive timestamp from the most recently modified file
	  -stm{HexMask} : set CPU thread affinity mask (hexadecimal number)
	  -stx{Type} : exclude archive type
	  -t{Type} : Set type of archive
	  -u[-][p#][q#][r#][x#][y#][z#][!newArchiveName] : Update options
	    -u- : not to update the archive
		-u* : updates all files, regardless of whether they have changed
		-u@ : specify a list of files to be updated from a file
		-up1: update files if their size or last modification date is different from that in the archive
		-up2: update files only if their date is newer than the one in the archive, regardless of size.
		-up3: update files only if their size is different from the one in the archive, regardless of the date.
		-uq : update mode with File Size and Date
		-uz : update mode with Date Only
	  -v{Size}[b|k|m|g] : Create volumes
	  -w[{path}] : assign Work directory. Empty path means a temporary directory
	  -x[r[-|0]]{@listfile|!wildcard} : eXclude filenames
	  -y : assume Yes on all queries

	Common 7z Exit Codes:
		0: No error - The operation completed successfully.
		1: Warning - One or more warnings were encountered, but the operation completed.
		2: Fatal error - The operation failed due to a fatal error and did not complete.
		7: Command line error - There was an issue with the command line parameters.
		8: Not enough memory - The operation could not be completed due to insufficient memory.
		255: User stopped the process - The operation was terminated by the user.
#>
