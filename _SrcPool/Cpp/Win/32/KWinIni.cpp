/*$Workfile: KWinIni.cpp$: implementation file
  $Revision: 1.1 $ $Date: 2009/01/09 22:12:18 $
  $Author: ddarko $

  Configuration file handler (.INI format)
  Copyright: CommonSoft Inc.
  2003-12-29  Darko Kolakovic
 */

// Group=Windows

#include "stdafx.h" // MFC/ATL core and standard components
#include "KType32.h"
#include "KProgCst.h"

#ifdef _USE_ATL
  #pragma warning(disable: 4127) //warning C4127: conditional expression is constant
//  #include <atlfile.h> //CAtlFile class
  #pragma warning(default: 4127)
#endif

#ifdef _DEBUG
  #ifdef _USE_MFC
    #define new DEBUG_NEW
  #endif
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

#if defined _ATL_VER
  #ifndef TRACE
    #define TRACE ATLTRACE
  #endif
  #ifndef TRACE1
    #define TRACE1 ATLTRACE
  #endif
#endif

//-----------------------------------------------------------------------------
/*Retrieves all the keys and values for the specified section of an initialization
  file. The string is limited to the 256 characters.
  The function is not case-sensitive; the section name can be a combination
  of uppercase and lowercase letters.

  Initialization file have following format:
     [Section1]
     Key1=Value1
     Key2=Value2
     ...
     [Section2]
     Key3=Value3
     ...

  Returns section paragraph. The maximum section size is 32,767 characters.

  Note: uses Microsoft Foundation Library (MFC) or
        uses Microsoft Active Template Library (ATL);
        Microsoft Windows specific (Win32).
 */
CString GetIniSection(LPCTSTR szFilename, //[in] name of the initialization file.
                    //If this parameter does not contain a full path to the file,
                    //the system searches for the file in the Windows directory.
                      LPCTSTR szSection   //[in] null-terminated string that 
                    //specifies the name of the section containing the key name.
                      )
{
const int VAL_SIZE = 256;
CString strResult;
if((szFilename != NULL)        &&
   (szFilename[0] != _T('\0')) &&
   (szSection != NULL)         &&
   (szSection[0] != _T('\0'))   )
  {
  long lCount; //the number of characters copied to the buffer, not including 
               //the terminating null character. If the buffer is not large enough
               //to contain all the key name and value pairs associated with 
               //the named section, the return value is equal to size of the buffer
               //used minus two.
  lCount = GetPrivateProfileSection(szSection,
                                    strResult.GetBuffer(VAL_SIZE),
                                    VAL_SIZE,
                                    szFilename);

  strResult.ReleaseBuffer();  //Free extra space and set string length
  }
return strResult;
}

//-----------------------------------------------------------------------------
/*Retrieves a string from the specified section in an initialization file.
  The string is limited to the 256 characters.
  The function is not case-sensitive; the section name can be a combination
  of uppercase and lowercase letters.
  A section in the initialization file must have the following form: 

    [section]
    key=string

  An application can use this method to enumerate all of the sections and keys
  in a file if szSection and szKey are NULL. In that case, each string is
  followed by a null character and the final string is followed by a second
  null character. If the supplied destination buffer is too small to hold all
  the strings, the last string is truncated and followed by two null characters.

  Returns value of the specified initialization key.

  Note: uses Microsoft Foundation Library (MFC) or
        uses Microsoft Active Template Library (ATL);
        Microsoft Windows specific (Win32).
 */
CString GetIniValue(LPCTSTR szFilename, //[in] name of the initialization file.
                    //If this parameter does not contain a full path to the file,
                    //the system searches for the file in the Windows directory.
                    LPCTSTR szSection, //[in] null-terminated string that specifies
                    //the name of the section containing the key name.
                    //If this parameter is NULL, the function
                    //retrieves all section names in the file.
                    LPCTSTR szKey //[in] null-terminated string specifying the name
                    //of the key whose associated string is to be retrieved.
                    //If this parameter is NULL, all key names in the section specified
                    //by the szSection parameter are retrieved.
                   )
{
const int VAL_SIZE = 256;
CString strResult;
if((szFilename != NULL) &&
   (szFilename[0] != _T('\0')) )
  {
  long lCount; //the number of characters copied to the buffer, not including 
               //the terminating null character.
  /*Note: If neither section name nor key mame is NULL and the supplied 
    destination buffer is too small to hold the requested string, the string
    is truncated and followed by a null character, and the return value is equal 
    to of the buffer uused minus one.
    If either ection name or key name is NULL and the supplied destination buffer
    is too small to hold all the strings, the last string is truncated and 
    followed by two null characters. In this case, the return value is equal to
    buffer size minus two.
   */

  lCount = GetPrivateProfileString(szSection,
                                  szKey,
                                  _T(""),
                                  strResult.GetBuffer(VAL_SIZE),
                                  VAL_SIZE,
                                  szFilename);
  strResult.ReleaseBuffer();  //Free extra space and set string length
  }

return strResult;
}
#if 1
//-----------------------------------------------------------------------------
/*Retrieves a string value from the specified key in an initialization file.
  The search for the key is case insensitive.
  A section with keys must have the following form:
     [Section]
  A key in the initialization file must have the following form:
     Key=Value

  If the section is not specified, the function will search for the first occurrence
  of the key.

  Returns value of the specified initialization key or the empty string if the file
  or the key could not be found.

  Note: uses Microsoft Foundation Library (MFC) or
        uses Microsoft Active Template Library (ATL);
        Microsoft Windows specific (Win32).

  History: Ported from Bernie Madigan <bernie@ testrun.cjb.net> Visual Basic source.
 */
CString ReadIniValue(LPCTSTR szFilename, //[in] name of the initialization file.
                     CString strSection, //[in] the name of the section containing 
                     //the key name or an empty string.
                     CString strKey      //[in] the name of the key whose associated 
                     //string is to be retrieved.
                    )
{
TRACE1(_T("ReadIniValue(%s)\n"),szFilename);

CString strResult;
//Nothing to do if parameters are empty
if((szFilename != NULL)          &&
   (szFilename[0] != _T('\0'))    &&
   (strKey.GetLength() != 0))
  {
  //File name nad key are specified
  bool bBrowseSections;

  //Normalize search strings to lower case
  strKey = strKey.MakeLower();

  if (strSection.GetLength() != 0)
    {
    //Find the section
    CString strSectionFrmt(_T("["));
    strSectionFrmt += strSection.MakeLower();
    strSectionFrmt += _T("]");
    strSection = strSectionFrmt;
    bBrowseSections = true;
    }
  else //Find the fist occurrence of the key
    bBrowseSections = false;

  CString strLine;             //line of text
  CString strNormalizedLine;   //line of text in lower case
  bool bFoundSection = false;  //line contains a section name

  HANDLE hFile = CreateFile(szFilename,
                           GENERIC_READ,
                           FILE_SHARE_READ,
                           NULL,//if lpSecurityAttributes is NULL,
                            //the handle cannot be inherited.
                           OPEN_EXISTING,
                           0,
                           NULL);
  if (hFile != INVALID_HANDLE_VALUE)
    {
    /*Assupmtion is that configuration files are smaller than 0xffffffff bytes.
      If expected file size is larger than INVALID_FILE_SIZE = 0xffffffff bytes,
      GetFileSizeEx() have to be used or 
      GetFileSize(HANDLE hFile, LPDWORD lpFileSizeHigh).
     */
    DWORD dwFileSize = ::GetFileSize(hFile, NULL);
    if (dwFileSize == INVALID_FILE_SIZE)
      {
      //Failed to obtain file size because file is larger than 0xffffffff bytes
      //or because of some other I/O error.
      TRACE1(_T("  GetFileSize failed with error %0.8X!\n"), 
              HRESULT_FROM_WIN32(::GetLastError()));
      }
    else
      {
      const int MAX_SIZE = 64*1024;
      const int MIN_SIZE = 2; //smallest file possible is encoded as single-byte
                              //text containing only a key with no value 'k='.
      if (dwFileSize > MAX_SIZE)
        {
      //TODO: create file memory map! D.K.
        TRACE1(_T("  TODO: Files large than 64kB requires memory mapped file! (size is %d bytes).\n"), 
              dwFileSize);
      //TODO: error message
        strResult = _T("<configuration file is too big>");
        CloseHandle(hFile);
        return strResult;
        }
      if (dwFileSize <= MIN_SIZE)
        {
        TRACE1(_T("  File with %d bytes doesn't contain key values!\n"), 
               dwFileSize);
        strResult = _T(""); //Return no value
        CloseHandle(hFile);
        return strResult;
        }
      //Get file encoding
      byte cBom[sizeof(uint32_t)];
      DWORD nBytesRead = 0;
      if (::ReadFile(hFile, 
                     cBom, 
                     sizeof(wchar_t), 
                     &nBytesRead, 
                     NULL
                     ) == FALSE)
          {
          TRACE1(_T("  ReadFile failed with error %0.8X!\n"), 
                  HRESULT_FROM_WIN32(::GetLastError()));
          //TODO: error message
          strResult = _T(""); //Return no value
          CloseHandle(hFile);
          return strResult;
          }

      if (ISUCBOMBE(cBom)) //File has Big Endian Unicode encoding
        {
        //TOOD: conversion from  Big Endian
        TRACE(_T("  Big Endian Unicode encoding is not supported!\n"));
        //TODO: error message
        strResult = _T("<encoding is not supported>"); 
        CloseHandle(hFile);
        return strResult;
        }

      if (ISUCBOM(*(wchar_t*)cBom)) //File has native Unicode encoding
        {

        }

       //if 
      nBytesRead = MAX_SIZE;
      //end-of-file is reached when the number of bytes read is less than asked
      while(nBytesRead == (MAX_SIZE * sizeof(TCHAR))) 
        {
        if (::ReadFile(hFile, 
                       strResult.GetBuffer(MAX_SIZE), 
                       MAX_SIZE * sizeof(TCHAR), 
                       &nBytesRead, 
                       NULL
                       ) == FALSE)
          {
          TRACE1(_T("  ReadFile failed with error %0.8X!\n"), 
                  HRESULT_FROM_WIN32(::GetLastError()));
          break;
          }

        }
        
      }
    //TODO
/*
    //Read the file lines until the end of file
    While Not EOF(hFile)
      {
    Line Input #hFile, strLine
    strNormalizedLine = LCase$(strLine)
      Find the section name

    if bBrowseSections Then   Find the section
      if Not bFoundSection And (InStr(strNormalizedLine, strSection) <> 0)
        {
        bFoundSection = True   Found a section
        GoTo GET_NEXT   Break and read next line
      }
      if bFoundSection
        {
        if InStr(strNormalizedLine, "[") <> 0
          {
            Found next section
          Close hFile
          Exit Function   Stop searching
        else
          if InStr(strNormalizedLine, strKey) <> 0
            {
              Found the key
            if InStr(strNormalizedLine, strKey & "=") = 1
              {
                Get the key value
              ReadIniValue = Mid$(strLine, 1 + Len(strKey & "="))
              Close hFile
              Exit Function
            }
          }
        }
      }
    else   Find first occurrence of the key, regardless of section
      if InStr(strNormalizedLine, strKey) <> 0
        {
          Found the key
        if InStr(strNormalizedLine, strKey & "=") = 1
          {
            Get the key value
          ReadIniValue = Mid$(strLine, 1 + Len(strKey & "="))
          Close hFile
          Exit Function
        }
      }
    }
*/
    CloseHandle(hFile);
    }


  }

return strResult;
}
#endif
#if 0
//-----------------------------------------------------------------------------
/*Replaces the keys and values for the specified section in an initialization
  file.

  Note: uses Microsoft Foundation Library (MFC) or
        uses Microsoft Active Template Library (ATL);
        Microsoft Windows specific (Win32).

 */
void SetIniSection(LPCTSTR szFilename, //[in]
                   LPCTSTR szSection As String, //[in]
                   LPCTSTR szList //[in]
                  )
{
  Call WritePrivateProfileSection(szSection, szList, szFilename)
}
#endif
#if 0
//------------------------------------------------------------------------------
/*Copies a string into the specified section of an initialization file.

  Note: uses Microsoft Foundation Library (MFC) or
        uses Microsoft Active Template Library (ATL);
        Microsoft Windows specific (Win32).

 */
void SetIniValue(LPCTSTR szFilename, //[in]
                 LPCTSTR szSection, //[in]
                 LPCTSTR szKey, //[in]
                 LPCTSTR szValue //[in]
                 )
{
  Call WritePrivateProfileString(szSection, szKey, szValue, szFilename)
}
#endif
#if 0
//------------------------------------------------------------------------------
/*Copies a string into the specified section of an initialization file.
  Requires 2 times file size of free memory. if file does not exist, creates
  new one.

  Note: uses Microsoft Foundation Library (MFC) or
        uses Microsoft Active Template Library (ATL);
        Microsoft Windows specific (Win32).

  Ported from Bernie Madigan <bernie@ testrun.cjb.net> Visual Basic source.
 */
void WriteIniValue(LPCTSTR szFilename, //[in]
                   LPCTSTR strSection, //[in]
                   LPCTSTR strKey, //[in]
                   LPCTSTR strValue //[in]
                  )
{
  Dim hFile As Integer   file handle
  Dim strSectionName As String   normalized section name
  Dim iSectionNameLen As Integer
  Dim strKeyName As String   normalized key name

  if (szFilename = "")
  {
    Err.Raise ERROR_INVALID_DATA, App.Title, "Invalid filename"
    Exit Function   Nothing to do
  }

  hFile = FreeFile
  strSectionName = vbCrLf & "[" & LCase$(strSection) & "]" & Chr$(13)
  iSectionNameLen = Len(strSectionName)
  strKeyName = Chr$(10) & LCase$(strKey) & "="

    Create file if not exist
  Open szFilename For Binary As hFile
  Close hFile
  SetAttr szFilename, vbArchive

    Read the file
  Dim strFileContent As String
  Dim strNormalizedContent As String
  Open szFilename For Input As hFile
  strFileContent = Input$(LOF(hFile), hFile)
  strFileContent = vbCrLf & strFileContent & "[]"
  Close hFile
  strNormalizedContent = LCase$(strFileContent)

    Get position of the elements
  Dim iSectionStart As Integer   section start position
  iSectionStart = InStr(strNormalizedContent, strSectionName)
  if iSectionStart = 0 Then GoTo INSERT_KEY:

  Dim iSectionEnd As Integer   section end position
  iSectionEnd = InStr(iSectionStart + iSectionNameLen, strNormalizedContent, "[")

  Dim iKeyEnd As Integer   key name end position
  iKeyEnd = InStr(iSectionStart, strNormalizedContent, strKeyName)
  if iKeyEnd > iSectionEnd Or iKeyEnd < iSectionStart Then GoTo INSERT_VALUE:

  GoTo CHANGE_VALUE:

INSERT_KEY:
  strFileContent = Left$(strFileContent, Len(strFileContent) - 2)
  strFileContent = strFileContent & vbCrLf & vbCrLf & _
                   "[" & strSection & "]" & vbCrLf & _
                   strKey & "=" & strValue
  GoTo FORMAT_OUTPUT:

INSERT_VALUE:
  strFileContent = Left$(strFileContent, Len(strFileContent) - 2)
  strFileContent = Left$(strFileContent, iSectionStart + iSectionNameLen) & _
                   strKey & "=" & strValue & vbCrLf & _
                   Mid$(strFileContent, iSectionStart + iSectionNameLen + 1)
  GoTo FORMAT_OUTPUT:

CHANGE_VALUE:
  Dim iValueEnd As Integer   text value end position
  strFileContent = Left$(strFileContent, Len(strFileContent) - 2)
  iValueEnd = InStr(iKeyEnd, strFileContent, Chr$(13))
  strFileContent = Left$(strFileContent, iKeyEnd) & _
                   strKey & "=" & strValue & _
                   Mid$(strFileContent, iValueEnd)
  GoTo FORMAT_OUTPUT:

FORMAT_OUTPUT:
  strFileContent = Mid$(strFileContent, 2)
  Do Until InStr(strFileContent, vbCrLf & vbCrLf & vbCrLf) = 0
    strFileContent = Replace(strFileContent, vbCrLf & vbCrLf & vbCrLf, vbCrLf & vbCrLf)
  Loop

  Do Until Right$(strFileContent, 1) > Chr$(13)
    strFileContent = Left$(strFileContent, Len(strFileContent) - 1)
  Loop

  Do Until Left$(strFileContent, 1) > Chr$(13)
    strFileContent = Mid$(strFileContent, 2)
  Loop

    Save the result
  Open szFilename For Output As hFile
  Print #hFile, strFileContent
  Close hFile

}
#endif

////////////////////////////////////////////////////////////////////////////////
/*******************************************************************************
 $Log: KWinIni.cpp,v $
 Revision 1.1  2009/01/09 22:12:18  ddarko
 Added VB port

 Revision 1.1  2009/01/09 22:05:01  dkolakovic
 babylonlib.sourceforge.net

 ******************************************************************************/
