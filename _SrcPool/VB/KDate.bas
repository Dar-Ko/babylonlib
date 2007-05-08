Attribute VB_Name = "KDate"
'$Workfile: KDate.bas$: implementation file
'$Revision: 2$ $Date: 2007-05-08 10:13:12$
'$Author: Darko Kolakovic$
'
'Date and time manipulators
'2004-08-19
Option Explicit
'-------------------------------------------------------------------------------
' Returns current Universal Coordinated Time (UTC) in the ISO 8601 date format:
'   Basic format      YYYYMMDDThhmmss,fff
'   Extended format   YYYY-MM-DDThh:mm:ss,fff
'   where:
'    *  hh  is the number of complete hours that have passed since midnight;
'           represented by two digits in the range [00, 24].
'           The Hour 00 is the beginning of any given day and the Hour 24 is the
'           end of the day. Midnight will normally be represented as 0000 or 2400.
'           Hour 24  have the minute and second values zero 24:00:00.
'    * mm   is the number of complete minutes that have passed since the start
'           of the hour; represented by two digits in the range [00, 59].
'    * ss   is the number of complete seconds since the start of the minute;
'           represented by two digits in the range [00, 60].
'           Value 60 allows to add a leap second to
'           the Coordinated Universal Time (UTC).
'    * ffff is the decimal fraction of the preceding time unit (hour, minute or
'           second); it is represented by any previously agreed number of digits
'           bigger or equal to one. Decimal sign is comma (,)  or dot (.),
'           but comma is preferred.
'    * Inserting time designator T is preferred way to store date and time
'      in a single field.
Public Function GetUtcTime(Optional ByVal bBasicFormat As Boolean) As String
  Dim uSystTime As SYSTEMTIME
  On Error Resume Next

  Call GetSystemTime(uSystTime)
  If bBasicFormat Then
    GetUtcTime = Right(uSystTime.wYear, 4) & _
                  Format(uSystTime.wMonth, "0#") & _
                  Format(uSystTime.wDay, "0#") & "T" & _
                  Format(uSystTime.wHour, "0#") & _
                  Format(uSystTime.wMinute, "0#") & _
                  Format(uSystTime.wSecond, "0#") & "," & _
                  Format(uSystTime.wMilliseconds, "00#")
  Else 'Extended format
    GetUtcTime = Right(uSystTime.wYear, 4) & "-" & _
                  Format(uSystTime.wMonth, "0#") & "-" & _
                  Format(uSystTime.wDay, "0#") & "T" & _
                  Format(uSystTime.wHour, "0#") & ":" & _
                  Format(uSystTime.wMinute, "0#") & ":" & _
                  Format(uSystTime.wSecond, "0#") & "," & _
                  Format(uSystTime.wMilliseconds, "00#")
  End If
End Function
'-------------------------------------------------------------------------------
'Parses time in the format:
'   hh:mm:ss
Public Sub Str2Time(ByRef lHour As Long, _
                    ByRef lMinute As Long, _
                    ByRef lSecond As Long, _
                    ByRef strTime As String, _
                    Optional ByRef strDelimiter As String)
  If strTime = "" Then
    Exit Sub 'Nothing to do
  End If
  
  If strDelimiter = "" Then
    strDelimiter = ":"
  End If
  lHour = Val(Left(strTime, InStr(1, strTime, strDelimiter) - 1))
  lMinute = Val(Mid(strTime, InStr(1, strTime, strDelimiter) + 1, _
                    InStrRev(strTime, strDelimiter) - _
                    InStr(1, strTime, strDelimiter) - 1))
  lSecond = Val(Mid(strTime, InStrRev(strTime, strDelimiter) + 1))
End Sub

'///////////////////////////////////////////////////////////////////////////////
'*******************************************************************************
'$Log:
' 1    Biblioteka1.0         2007-04-30 16:51:34  Darko Kolakovic
'$
'*******************************************************************************

