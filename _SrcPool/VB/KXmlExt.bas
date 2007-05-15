Attribute VB_Name = "KXmlExt"
'$Workfile: S:\_SrcPool\VB\KXmlExt.bas$: implementation file
'$Revision: 1$ $Date: 2007-05-15 15:45:44$
'$Author: Darko Kolakovic$
'
'XML manipulation helpers
'2005-08-03

Option Explicit
'------------------------------------------------------------------------------
'Escapes special XML characters in the given text with predefined entities:
'     Character          XML entity
'     ampersand    &        &amp;
'     less than    <        &lt;
'     greater than >        &gt;
'     quote        "        &quot;
'     apostrophe   '        &apos;
'
'Note: slash (\) and space ( ) characters does not require escaping.
'
'Returns String value containing escaped characters
Public Function XmlEscape(ByRef strData As String) As String
    
  XmlEscape = strData 'Copy source string
  
  If InStrB(1, XmlEscape, "&") Then XmlEscape = Replace(XmlEscape, "&", "&amp;")
  If InStrB(1, XmlEscape, "<") Then XmlEscape = Replace(XmlEscape, "<", "&lt;")
  If InStrB(1, XmlEscape, ">") Then XmlEscape = Replace(XmlEscape, ">", "&gt;")
  If InStrB(1, XmlEscape, """") Then XmlEscape = Replace(XmlEscape, """", "&quot;")
  If InStrB(1, XmlEscape, "'") Then XmlEscape = Replace(XmlEscape, "'", "&apos;")
End Function
'------------------------------------------------------------------------------
'Replaces XML entities used for to escape special XML characters with the
'corresponding values. Replaced entities are:
'     XML entity      Character
'       &amp;       ampersand    &
'       &lt;        less than    <
'       &gt;        greater than >
'      &quot;       quote        "
'      &apos;       apostrophe   '
'
'Returns: XML sentence as plain text
Public Function XmlUnescape(ByRef strData As String) As String
  XmlUnescape = strData 'Copy source string
  
  If LenB(XmlUnescape) Then
    Dim lPos As Long
    lPos = InStrB(1, XmlUnescape, "&") 'Find start of any XML entity
    If lPos <> 0 Then
      If InStrB(lPos, XmlUnescape, ";") Then 'Find the end of the entity
        'Replace special entities with characters
        If InStrB(lPos, XmlUnescape, "&lt;") Then XmlUnescape = Replace(XmlUnescape, "&lt;", "<")
        If InStrB(lPos, XmlUnescape, "&gt;") Then XmlUnescape = Replace(XmlUnescape, "&gt;", ">")
        If InStrB(lPos, XmlUnescape, "&quot;") Then XmlUnescape = Replace(XmlUnescape, "&quot;", """")
        If InStrB(lPos, XmlUnescape, "&apos;") Then XmlUnescape = Replace(XmlUnescape, "&apos;", "'")
        If InStrB(lPos, XmlUnescape, "&amp;") Then XmlUnescape = Replace(XmlUnescape, "&amp;", "&")
      End If
    End If
  End If
End Function
'//////////////////////////////////////////////////////////////////////////////
'******************************************************************************
'$Log: 
' 1    Biblioteka1.0         2007-05-15 15:45:44  Darko Kolakovic 
'$
'******************************************************************************


