Attribute VB_Name = "KDbgPrint"
'$Workfile: KDbgPrint.bas$: implementation file
'$Revision: 1.2 $ $Date: 2008/05/16 18:46:28 $
'$Author: ddarko $
'
'File I/O/ handling helpers
'2008-01-29
Option Explicit

'------------------------------------------------------------------------------
'Outputs diagnostic message to a debugging viewer
Public Sub DebugPrint(ByVal strMsg As String)
  Dim strText As String

  strText = App.EXEName & ": " & strMsg & vbCrLf & String(2, vbNullChar)
  Call OutputDebugString(strText)
End Sub
'///////////////////////////////////////////////////////////////////////////////
'*******************************************************************************
'$Log: KDbgPrint.bas,v $
'Revision 1.2  2008/05/16 18:46:28  ddarko
'Comment
'
'Revision 1.1  2008/05/16 18:44:33  ddarko
'Created
'
'*******************************************************************************

