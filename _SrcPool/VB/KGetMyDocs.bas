Attribute VB_Name = "KGetMyDocs"
'$Workfile: KGetMyDocs.bas$: implementation file
'$Revision: 2$ $Date: 2007-05-10 16:59:09$
'$Author: Darko Kolakovic$
'
'Obtain a Windows folder
'Copyright:   CommonSoft Inc
 
'Group=Windows
Option Explicit

'-------------------------------------------------------------------------------
'Returns 'My Documents' system folder
Public Function GetMyDocumentsFolder() As String
  Dim strRet As String * 255
  Dim hKey As Long
  Dim iAccess As Long
     
  On Error GoTo ON_ERROR
  iAccess = KEY_ALL_ACCESS
  Call RegOpenKeyEx(HKEY_CURRENT_USER, "Software", 0, iAccess, hKey)
  Call RegOpenKeyEx(hKey, "Microsoft", 0, iAccess, hKey)
  Call RegOpenKeyEx(hKey, "Windows", 0, iAccess, hKey)
  Call RegOpenKeyEx(hKey, "CurrentVersion", 0, iAccess, hKey)
  Call RegOpenKeyEx(hKey, "Explorer", 0, iAccess, hKey)
  Call RegOpenKeyEx(hKey, "Shell Folders", 0, iAccess, hKey)
  
  Call RegQueryValueEx(hKey, "Personal", 0, REG_SZ, strRet, Len(strRet))
  If InStr(1, strRet, Chr(0)) <> 0 Then
    GetMyDocumentsFolder = Mid(strRet, 1, InStr(1, strRet, Chr(0)) - 1)
  End If
  Exit Function
     
ON_ERROR:
  Call MsgBox(Err.Description, vbCritical)
     
End Function
'///////////////////////////////////////////////////////////////////////////////
'*******************************************************************************
'$Log:
' 1    Biblioteka1.0         2007-05-10 11:11:36  Darko Kolakovic
'$
'*******************************************************************************


