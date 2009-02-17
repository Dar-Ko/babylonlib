/*$Workfile: KWinIni.cpp$: implementation file
  $Revision: 1.7 $ $Date: 2009/02/17 21:08:06 $
  $Author: ddarko $

  Configuration file handler (.INI format)
  Copyright: CommonSoft Inc.
  2003-12-29  Darko Kolakovic
 */

// Group=Windows

#include "stdafx.h" // MFC/ATL core and standard components
#include "KType32.h"
#include "KProgCst.h"
#include "KWinStrArray.h" //CStringArray class

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
  #ifndef ASSERT
    #define ASSERT ATLASSERT
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
TRACE(_T("GetIniSection()\n"));

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
/*Retrieves all section names of an initialization file.

  Initialization file have following format:
     [Section1]
     Key1=Value1
     Key2=Value2
     ...
     [Section2]
     Key3=Value3
     ...
  Section names does not include enclosing brackets. Heading and trailing white space
  is truncated. As a consequence of former, section names that contains only white 
  space or empty strings will stop section enumeration.
  Section name include filter szFilter is case sensitive.

  Returns the number of filtered section names and the list of section paragraphs.

  Note: uses Microsoft Foundation Library (MFC) or
        uses Microsoft Active Template Library (ATL);
        Microsoft Windows specific (Win32).
 */
int GetIniSectionList(CStringArray& strResult, //[out] list of sections
                     //found in the initialization file
                      LPCTSTR szFilename, //[in] name of the initialization file.
                    //If this parameter does not contain a full path to the file,
                    //the system searches for the file in the Windows directory.
                      LPCTSTR szFilter   //[in] null-terminated string that
                    //specifies name token included in a section name. If it is NULL or
                    //an empty string, all section names that are found will be returned.
                      )
{
TRACE(_T("GetIniSectionList()\n"));

const int VAL_SIZE = 512; //text buffer granule
int iSectionCount = 0;

if((szFilename != NULL) && (szFilename[0] != _T('\0')) )
  {
  bool bReadSuccessfully = false; //true if  all section names are processsed
  int nStep = 1;      //buffer granule increment
  long lBuffSize = 0; //text buffer size;
  LPTSTR listSection = NULL;  //buffer that receives the section names associated
                              //with the named file. The buffer is filled with one
                              //or more null-terminated strings; the last string is
                              //followed by a second null character.

  do
    {
    lBuffSize = nStep * VAL_SIZE;
    if ((lBuffSize == INT_MAX) || (lBuffSize <= 0)) //Sanity and integer overflow check
      {
      ASSERT(false); //File is ridiculously big
      break;
      }

    listSection = new TCHAR[lBuffSize];
    long lCount; //the number of characters copied to the buffer, not including
                 //the terminating null character. If the buffer is not large enough
                 //to contain all the key name and value pairs associated with
                 //the named section, the return value is equal to size of the buffer
                 //used minus two.
    if (listSection != NULL)
      {
      lCount = GetPrivateProfileSectionNames(listSection,
                                             lBuffSize,
                                             szFilename);
      if (lCount <= 2)
        break; //File contains no section names
      bReadSuccessfully = (lCount < (lBuffSize - 2));
      if(!bReadSuccessfully)
        {
        //The buffer was too small
        delete []listSection;
        listSection = NULL;
        nStep++;
        }
      }
  } while(!bReadSuccessfully);

  if (bReadSuccessfully)
    {
    //Parse and filter found section names
    strResult.RemoveAll();
    nStep = 0; //character index in text buffer
    const TCHAR ENDOFLIST = _T('\0');
    while(listSection[nStep] != ENDOFLIST)
      {
      CString strSectionName = &listSection[nStep];
      if (!strSectionName.IsEmpty())
        {
        if((szFilter != NULL) && (szFilter[0] != _T('\0')))
          {
          //Find sections containing include filter in their names
          if(strSectionName.Find(szFilter) > -1)
            strResult.Add(strSectionName);
          }
        else
          strResult.Add(strSectionName);
        }
      //Find next zero-delimited string
      while(listSection[nStep] != _T('\0'))
        nStep++;
      nStep++; //Index of first character in the string
      }

    #ifdef _USE_ATLSIMPLEARRAY
      iSectionCount = strResult.GetSize();
    #else
      iSectionCount = strResult.GetCount();
    #endif
    }

  if (listSection != NULL)
    delete []listSection;
  }

return iSectionCount; //Return number of sections
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

  See also: GetPrivateProfileString()
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
TRACE(_T("GetIniValue()\n"));

const int VAL_SIZE = 256;
CString strResult;
if((szFilename != NULL) &&
   (szFilename[0] != _T('\0')) )
  {
  long lCount; //the number of characters copied to the buffer, not including 
               //the terminating null character.
  /*Note: If neither section name nor key name is NULL and the supplied
    destination buffer is too small to hold the requested string, the string
    is truncated and followed by a null character, and the return value is equal
    to of the buffer used minus one.
    If either section name or key name is NULL and the supplied destination buffer
    is too small to hold all the strings, the last string is truncated and
    followed by two null characters. In this case, the return value is equal to
    buffer size minus two.
   */

  lCount = GetPrivateProfileString(szSection,
                                  szKey,
                                  _T(""), //default string, if the key
                                          //cannot be found 
                                  strResult.GetBuffer(VAL_SIZE),
                                  VAL_SIZE,
                                  szFilename);
  strResult.ReleaseBuffer();  //Free extra space and set string length
  }

return strResult;
}

//-----------------------------------------------------------------------------
/*Retrieves the value of an integer from an entry within a specified section of
  the initialization (INI) file. The function is not case-sensitive.
  This function supports hexadecimal notation for the value in the .INI file.
  A section in the initialization file must have the following form:

    [section]
    key=value

  Returns the integer value of the string that follows the specified entry if 
  the function is successful. When you retrieve a signed integer, you should
  cast the value into an int.
  The return value is the value of the nDefault parameter if the function does
  not find the entry. The return value is 0 if the value that corresponds to
  the specified entry is not an integer.

  Note: Microsoft Windows specific (Win32).

  See also: GetPrivateProfileInt()
 */
unsigned int GetIniValue(LPCTSTR szFilename, //[in] name of the initialization file.
                    //If this parameter does not contain a full path to the file,
                    //the system searches for the file in the Windows directory.
                    LPCTSTR szSection, //[in] null-terminated string that specifies
                    //the name of the section containing the key name.
                    //If this parameter is NULL, the function
                    LPCTSTR szKey, //[in] null-terminated string specifying the name
                    //of the key whose associated string is to be retrieved.
                    //If this parameter is NULL, all key names in the section specified
                    //by the szSection parameter are retrieved.
                    int nDefault
                    )
{
TRACE(_T("GetIniValue(int)\n"));

ASSERT(szFilename != NULL);
return ::GetPrivateProfileInt(szSection, 
                              szKey, 
                              nDefault,
                              szFilename);
}

#if 0
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

//-----------------------------------------------------------------------------
/*Replaces the keys and values for the specified section in an initialization
  file.

  If file name parameter does not contain a full path for the file, the function
  searches the Windows directory for the file. If the file does not exist and
  szFileName does not contain a full path, the function creates the file in the
  Windows directory. If the file exists and was created using Unicode characters,
  the function writes Unicode characters to the file. Otherwise, the function
  creates a file using ANSI characters.

  The data in the list of new key names consists of one or more null-terminated
  strings, followed by a final null character:

      key1=string1\0key2=string2\0 ... keyN=stringN\0\0

  Maximum length is limited to 65,535 bytes.

  Returns true if successful; otherwise false. To get extended error information,
  call GetLastError().

  Note: Microsoft Windows specific (Win32).
 */
bool SetIniSection(LPCTSTR szFilename, //[in] name of the initialization file.
                   LPCTSTR szSection,  //[in] name of the section in which data
                                       //is written.
                   LPCTSTR szList //[in] list of new key names and associated values that
                   //are to be written to the named section.
                  )
{
TRACE(_T("SetIniSection()\n"));
ASSERT((szList != NULL) && (szList[0] != _T('\0')));
ASSERT((szSection != NULL) && (szSection[0] != _T('\0')));

if ( ((szList != NULL) && (szList[0] != _T('\0'))) ||
     ((szSection != NULL) && (szSection[0] != _T('\0'))) )
  {
  if (WritePrivateProfileSection(szSection, szList, szFilename) == TRUE)
    return true;
  TRACE1(_T("  Failed to write section: error 0x%08X!\n"), GetLastError());
  }
else
  SetLastError(ERROR_INVALID_PARAMETER);
return false;
}

//------------------------------------------------------------------------------
/*Copies a string into the specified section of an initialization file.
  If the file exists and was created using Unicode characters, the function
  writes Unicode characters to the file. Otherwise, the function writes ANSI
  characters.
  If the key does not exist in the specified section, it is created. If key
  parameter is NULL, the entire section, including all entries within the section,
  is deleted.
  If the function fails, or if it flushes the cached version of the most recently
  accessed initialization file, the return value is zero. To get extended error
  information, call GetLastError().

  A section in the initialization file have the following form:
      [section]
      key=string
      ...

  Returns true if successful; otherwise false.

  Note: Microsoft Windows specific (Win32).

  See also: WritePrivateProfileString()
 */
bool SetIniValue(LPCTSTR szFilename, //[in] name of the initialization file.
                 LPCTSTR szSection, //[in] case-insensitive name of the section
                 //to which the string will be copied. If the section does not exist,
                 //it is created.
                 LPCTSTR szKey, //[in] name of the key to be associated with a value.
                 //If it is NULL, the section is deleted.
                 LPCTSTR szValue //[in] null-terminated string to be written to the
                                 //file. If it is NULL, the associated key is deleted.
                 )
{
TRACE(_T("SetIniValue()\n"));
ASSERT((szFilename != NULL) && (szFilename[0] != _T('\0')));

if ((szFilename != NULL) && (szFilename[0] != _T('\0')))
  {
  if (WritePrivateProfileString(szSection, szKey, szValue, szFilename) == TRUE)
    return true;
  TRACE1(_T("  Failed to write section: error 0x%08X!\n"), GetLastError());
  }
else
  SetLastError(ERROR_INVALID_PARAMETER);
return false;
}

//------------------------------------------------------------------------------
/*write the specified value into the specified section of the initialization
  (INI) file.
  If the key does not exist in the specified section, it is created. If key
  parameter is NULL, the entire section, including all entries within the section,
  is deleted.
  A comment at the end of key-value line will not be preserved after saving a new
  value.
  If the function fails, or if it flushes the cached version of the most recently
  accessed initialization file, the return value is zero. To get extended error
  information, call GetLastError().

  A section in the initialization file have the following form:
      [section]
      key=value
      ...

  Returns true if successful; otherwise false.

  Esample:

       SetIniValue(_T("file.ini"), _T("My Section"), _T("My Int Item"), 1234);
       int nValue = GetIniValue(strSection, strIntItem, 0);
       ASSERT(nValue == 1234);

  Note: Microsoft Windows specific (Win32).

  See also: WritePrivateProfileString()
 */
bool SetIniValue(LPCTSTR szFilename,//[in] name of the initialization file.
                 LPCTSTR szSection, //[in] case-insensitive name of the section
//to which the string will be copied. If the section does not exist, it is created.
                 LPCTSTR szKey, //[in] name of the key to be associated with a value.
                 int nValue          //[in] value to be written
               )
{
TRACE(_T("SetIniValue(int)\n"));
ASSERT((szFilename != NULL) && (szFilename[0] != _T('\0')));
if ((szFilename != NULL) && (szFilename[0] != _T('\0')))
  {
  TCHAR szT[16];
  _stprintf_s(szT, _countof(szT), _T("%d"), nValue);
  return (::WritePrivateProfileString(szSection,
                                     szKey,
                                     szT,
                                     szFilename) == TRUE) ? true : false;
  }
SetLastError(ERROR_INVALID_PARAMETER);
return false;
}

////////////////////////////////////////////////////////////////////////////////
/*******************************************************************************
 $Log: KWinIni.cpp,v $
 Revision 1.7  2009/02/17 21:08:06  ddarko
 Fixed typos

 Revision 1.6  2009/02/07 22:29:16  ddarko
 SetIniValue(int)

 Revision 1.5  2009/02/04 23:06:19  ddarko
 Enumerate sections

 Revision 1.4  2009/02/03 23:05:31  ddarko
 GetIniSectionList()

 Revision 1.3  2009/01/13 22:25:40  ddarko
 Trace

 Revision 1.2  2009/01/12 23:01:10  dkolakovic
 SetIniSection()

 Revision 1.1  2009/01/09 22:05:01  dkolakovic
 babylonlib.sourceforge.net

 ******************************************************************************/
