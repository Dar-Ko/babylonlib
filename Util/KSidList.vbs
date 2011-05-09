'Author			: Ramesh Srinivasan, Microsoft MVP [Windows Shell/User]
'Description	: Lists all the user accounts, their SIDs and Profile paths.
'Copyright		: Copyright © 2005-2006, Ramesh Srinivasan
'Created on		: Aug 10, 2005
'Revised on		: Sep 16, 2006
'Prerequisite	: For Windows® XP
'Homepage		: http://windowsxp.mvps.org & http://www.winhelponline.com

Set WshShell = CreateObject("Wscript.Shell")
Set fso = Wscript.CreateObject("Scripting.FilesystemObject")
fName = WshShell.SpecialFolders("Desktop") & "\SIDlist.txt"
Set b = fso.CreateTextFile(fName, true)
b.writeblanklines 1
b.writeline string(61,"*")
b.writeline "Lists all the user accounts, their SIDs and Profile paths."
b.WriteLine "SIDList.vbs - Copyright © 2005-2006, Ramesh Srinivasan"
b.WriteLine "WWW: http://windowsxp.mvps.org & http://www.winhelponline.com"
b.writeline string(61,"*")
b.writeblanklines 1

strProfileBranch = "HKLM\SOFTWARE\Microsoft\Windows NT\CurrentVersion\ProfileList\"
strComputer = "."
Set objWMIService = GetObject("winmgmts:\\" & strComputer & "\root\cimv2")
Set colAccounts = objWMIService.ExecQuery _
    ("Select * From Win32_UserAccount")

For Each objAccount in colAccounts
	If objAccount.Name = "HelpAssistant" or objAccount.Name = "SUPPORT_388945a0" then
	else
		b.writeline "Username  	 : " & objAccount.Name
		b.writeline "SID      	 : " & objAccount.SID
		b.writeline "Profile dir 	 : " & GetHomePath(objAccount.SID)
		b.writeblanklines 1
	end if
Next

Function GetHomePath(strSID)
	On Error Resume Next
		GetHomePath = WshShell.ExpandEnvironmentStrings(Trim(WshShell.RegRead (strProfileBranch & strSID & "\ProfileImagePath")))
	On Error Goto 0
End Function

b.writeline string(61,"*")
b.close
WshShell.Run "notepad.exe " & fName

Set fso = Nothing
set Wshshell = Nothing