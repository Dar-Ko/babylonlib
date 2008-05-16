Attribute VB_Name = "KWinComDlg32"
'$Workfile: S:\_SrcPool\VB\KWinGdi32.bas$: implementation file
'$Revision: 1.1 $ $Date: 2008/05/16 18:31:33 $
'$Author: ddarko $
'
'MS Windows comdlg32 DLL
'2007-05-14
Option Explicit

'------------------------------------------------------------------------------
'Commdlg.h

'The OPENFILENAME structure contains information that the GetOpenFileName and
'GetSaveFileName functions use to initialize an Open or Save As dialog box.
'After the user closes the dialog box, the system returns information about
'the user's selection in this structure.
Public Type OPENFILENAME
  lStructSize       As Long 'specifies the length, in bytes, of the structure.
  hwndOwner         As Long 'handle to the window that owns the dialog box or NULL if the dialog box has no owner.
  hInstance         As Long 'handle to a memory object or a module that contains a dialog box template
  lpstrFilter       As String 'buffer containing pairs of null-terminated filter strings. The last string in the buffer must be terminated by two NULL characters.
  lpstrCustomFilter As String 'static buffer that contains a pair of null-terminated filter strings for preserving the filter pattern chosen by the user
  nMaxCustFilter    As Long 'size, in TCHARs, of the buffer identified by lpstrCustomFilter
  nFilterIndex      As Long 'index of the currently selected filter in the File Types control.
  lpstrFile         As String 'file name used to initialize the File Name edit control
  nMaxFile          As Long 'size, in TCHARs, of the buffer pointed to by lpstrFile
  lpstrFileTitle    As String 'buffer that receives the file name and extension  or NULL
  nMaxFileTitle     As Long 'size, in TCHARs, of the buffer pointed to by lpstrFileTitle
  lpstrInitialDir   As String 'the initial directory
  lpstrTitle        As String 'title to be placed in the title bar of the dialog box
  flags             As Long 'set of bit flags you can use to initialize the dialog box
  nFileOffset       As Integer 'zero-based offset, in TCHARs, from the beginning of the path to the file name in the string pointed to by lpstrFile
  nFileExtension    As Integer 'zero-based offset, in TCHARs, from the beginning of the path to the file name extension in the string pointed to by lpstrFile
  lpstrDefExt       As String 'default extension. GetOpenFileName and GetSaveFileName append this extension to the file name if the user fails to type an extension
  lCustData         As Long 'application-defined data that the system passes to the hook procedure identified by the lpfnHook member
  lpfnHook          As Long 'hook procedure
  lpTemplateName    As String 'dialog template resource in the module identified by the hInstance member
End Type

Public Declare Function GetOpenFileName Lib "comdlg32.dll" Alias "GetOpenFileNameA" (pOpenfilename As OPENFILENAME) As Long

'///////////////////////////////////////////////////////////////////////////////
'*******************************************************************************
'$Log: KWinComDlg32.bas,v $
'Revision 1.1  2008/05/16 18:31:33  ddarko
'Created
'
'*******************************************************************************

