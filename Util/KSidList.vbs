'$RCSfile: KSidList.vbs,v $: script file
'$Revision: 1.2 $ $Date: 2011/05/09 13:40:18 $
'$Author: ddarko $
'
'Lists all the user accounts, their SIDs and Profile paths.
'Requires Windows® XP or higher.
'Copyright: Copyright © 2005-2006, Ramesh Srinivasan
'Ramesh Srinivasan, Microsoft MVP [Windows Shell/User], Aug 10, 2005
'Revised on: Sep 16, 2006
'http://windowsxp.mvps.org & http://www.winhelponline.com


'Group=Utility

'------------------------------------------------------------------------------
'Returns user's home directory, if any, from the SID record.
Function GetHomePath(strSID)
  On Error Resume Next
    GetHomePath = WshShell.ExpandEnvironmentStrings(Trim(WshShell.RegRead _ 
          (strProfileBranch & strSID & "\ProfileImagePath")))
  On Error Goto 0
End Function

'------------------------------------------------------------------------------
'Lists all the user accounts, their SIDs and Profile paths.
'Creates file SIDlist.txt on the user's desktop.
Set WshShell = CreateObject("Wscript.Shell")
Set fso = Wscript.CreateObject("Scripting.FilesystemObject")
fName = WshShell.SpecialFolders("Desktop") & "\SIDlist.txt"
Set b = fso.CreateTextFile(fName, true)
b.writeline "List of the user accounts, their SIDs and Profile paths."
b.writeline string(61,"_")
b.writeblanklines 1

strProfileBranch = "HKLM\SOFTWARE\Microsoft\Windows NT\CurrentVersion\ProfileList\"
strComputer = "."
Set objWMIService = GetObject("winmgmts:\\" & strComputer & "\root\cimv2")
Set colAccounts = objWMIService.ExecQuery _
    ("Select * From Win32_UserAccount")

For Each objAccount in colAccounts
  If objAccount.Name = "HelpAssistant" or objAccount.Name = "SUPPORT_388945a0" then
  else
    b.writeline "Username   : " & objAccount.Name
    b.writeline "SID        : " & objAccount.SID
    b.writeline "Profile dir: " & GetHomePath(objAccount.SID)
    b.writeblanklines 1
  end if
Next

'Append ending line
b.writeline string(61,"=")
b.close
'Open and present the list
WshShell.Run "notepad.exe " & fName

Set fso = Nothing
set Wshshell = Nothing