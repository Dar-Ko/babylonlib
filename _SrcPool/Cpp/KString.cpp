/*$Workfile: KString.cpp$: implementation file
  $Revision: 1.2 $ $Date: 2002/09/10 15:22:21 $
  $Author: ddarko $

  Implementation of the CString class. This is a STL port of MFC CString class
  Copyright: CommonSoft Inc.
 */
 
/* Group=Strings                                                             */

#include <string>     //std::string template
#include "KString.h"  //CString class

#ifdef _STRING_ //STL <string> header included
  #include <new>
  #include <locale>     //std::string template

///////////////////////////////////////////////////////////////////////////////
// Construction/Destruction

//::CString()------------------------------------------------------------------
/*Default constructor creates empty string.
 */
CString::CString()
{
m_pData = new(std::nothrow) CStringHandler;
}

/*Copy constructor.
 */
CString::CString(const CString& strSource //[in] a string to be copied into this
                                          //CString object.
                 )
{
m_pData = new(std::nothrow) CStringHandler;
if(m_pData != NULL)
  Copy(strSource);
}

/*Creates a string from a single character.
 */
CString::CString(TCHAR chSource, //[in] a single character to be copied iCount
                                 //times.
                 int iCount      //[in] = 1 number of times chSource will be copied
                 )
{
m_pData = new(std::nothrow) CStringHandler;
if(m_pData != NULL)
  Append(chSource,iCount);
}

/*Copies number of charactes from an array.
 */
CString::CString(LPCTSTR pchSource,//[in] an array of characters, not null-terminated.
                 int iLength       //[in] size of the array
                 )
{
m_pData = new(std::nothrow) CStringHandler;
if(m_pData != NULL)
  Copy(pchSource,iLength);
}

/*Converts BYTE array to CString.
 */
CString::CString(const unsigned char* pszSource //[in] null-terminated array of bytes
                )
{
m_pData = new(std::nothrow) CStringHandler;
if(m_pData != NULL)
  Copy((LPCSTR)pszSource);
}

/*Converts UNICODE string to CString.
 */
CString::CString(LPCWSTR szString //[in] null-terminated Unicode string
                 )
{
m_pData = new(std::nothrow) CStringHandler;
if(m_pData != NULL)
  Copy(szString);
}

/*Converts ANSI string to CString.
 */
CString::CString(LPCSTR szString //[in] null-terminated ANSI string
                 )
{
m_pData = new(std::nothrow) CStringHandler;
if(m_pData != NULL)
  Copy(szString);
}

//::~CString()-----------------------------------------------------------------
/*
 */
CString::~CString()
{
if(m_pData != NULL)
  {
  delete m_pData;
  m_pData = NULL;
  }
}

///////////////////////////////////////////////////////////////////////////////
// Indexed access

//::GetLength()----------------------------------------------------------------
/*Obtains number of letters in a string
  Returns: the number of characters in a CString object, not including
           a null terminator.

  Example:
      CString strTemp(_T("abcdef"));
      ASSERT(strTemp.GetLength() == 6);
 */
int CString::GetLength() const
{
return (m_pData != NULL) ? m_pData->length() : 0;
}

//::IsEmpty()------------------------------------------------------------------
/*Validates a string.
  Returns: TRUE if string have no characters, otherwise returns FALSE;

  Example:
      CString strTemp(_T("abcdef"));
      ASSERT(!strTemp.IsEmpty());

 */
bool CString::IsEmpty() const
{
if (m_pData == NULL)
  return true;
return m_pData->empty() ? true : false;
}

//::Empty()--------------------------------------------------------------------
/*Makes this CString object an empty string and frees memory as appropriate.

  Example:

    CString strTemp("abc");
    strTemp.Empty();
    ASSERT(strTemp.GetLength() == 0);

 */
void CString::Empty()
{
m_pData->erase();
}

//----------------------------------------------------------------------------
/*Obtains specified element of the character array.
  Returns: the character at a given position or '\0' if position is out of range.
  Example:
    CString strTemp(_T("abcdef"));
    ASSERT(strTemp.GetAt(2) == _T('c'));

 */
TCHAR CString::GetAt(int iIndex //[in] zero-based index of the character in
                     //the string object. The parameter must be greater than
                     //or equal to 0 and less than the value returned by GetLength.
                     ) const
{
try
  {
  return m_pData->at(iIndex);
  }
catch(std::out_of_range e)
  {
  return _T('\0');
  }
}

//::SetAt()--------------------------------------------------------------------
/*Sets a character at a given position.
 */
void CString::SetAt(int iIndex, //[in] zero-based index of the character in the
                    //tring object. The parameter must be greater than or equal
                    //to 0 and less than the value returned by GetLength.
                    TCHAR ch    //[in] character to set.

                    )
{
try
  {
  m_pData->at(iIndex) = ch;
  }
catch(std::out_of_range e)
  {
  ASSERT(false);
  }
}

//::LPCTSTR()------------------------------------------------------------------
/*Obtains characters array stored in a string object as a C-style
  null-terminated string.

  Returns: a character pointer to the string’s data.

  Note: Calling any non-const member function for this object after you have
        obtained the character pointer can invalidate the returned pointer.
 */
CString::operator LPCTSTR() const
{
return m_pData->c_str();
}

//::operator[]-----------------------------------------------------------------
/*Obtains specified element of the character array.

  Returns: the character at a given position or '\0' if position is out of range.

  Note: You can use the subscript ([]) operator to get the value of a character
        in a CString, but you cannot use it to change the value of a character
        in a CString.

  Example:
    CString strTemp(_T("abcdef"));
    ASSERT(strTemp[2] == _T('c'));
 */
TCHAR CString::operator[](int iIndex //[in] zero-based index of the character in
                     //the string object. The parameter must be greater than
                     //or equal to 0 and less than the value returned by GetLength.
                         ) const
{
try
  {
  return m_pData->at(iIndex);
  }
catch(std::out_of_range e)
  {
  return _T('\0');
  }
}

///////////////////////////////////////////////////////////////////////////////
// Assignment

//::operator=()----------------------------------------------------------------
/*Assigns a new value to a CString object.

  Note: memory exceptions may occur whenever you use the assignment operator
  because new storage is often allocated to hold the resulting CString object.
 */
const CString& CString::operator=(const CString& stringSrc)
{
Copy(stringSrc);
return *this;
}

const CString& CString::operator=(TCHAR ch)
{
m_pData->erase();
m_pData->append(1,ch);
return *this;
}

#ifdef _UNICODE
  const CString& CString::operator=(char ch)
    {
    *this = (TCHAR)ch;
    return *this;
    }
#endif

const CString& CString::operator=(LPCSTR lpsz)
{
Copy(lpsz);
return *this;
}

const CString& CString::operator=(LPCWSTR lpsz)
{
Copy(lpsz);
return *this;
}

const CString& CString::operator=(const unsigned char* psz)
{
Copy(reinterpret_cast<LPCSTR>(psz));
return *this;
}

//::LoadString()---------------------------------------------------------------
/*Loads an existing CString object from a resource.
  Returns: true if resource load was successful; otherwise returns false.
 */
bool CString::LoadString(UINT nID //string resource ID
                        )
{

//TOdo
return false;
/*
	static int __stdcall _LoadString(UINT nID, LPTSTR lpszBuf, UINT nMaxBuf)
	{
#ifdef _DEBUG
		// LoadString without annoying warning from the Debug kernel if the
		//  segment containing the string is not present
		if (::FindResource(_Module.GetResourceInstance(), MAKEINTRESOURCE((nID>>4)+1), RT_STRING) == NULL)
		{
			lpszBuf[0] = '\0';
			return 0; // not found
		}
#endif //_DEBUG
		int nLen = ::LoadString(_Module.GetResourceInstance(), nID, lpszBuf, nMaxBuf);
		if (nLen == 0)
			lpszBuf[0] = '\0';
		return nLen;
	}

	// try fixed buffer first (to avoid wasting space in the heap)
	TCHAR szTemp[256];
	int nCount =  sizeof(szTemp) / sizeof(szTemp[0]);
	int nLen = _LoadString(nID, szTemp, nCount);
	if (nCount - nLen > CHAR_FUDGE)
	{
		*this = szTemp;
		return nLen > 0;
	}

	// try buffer size of 512, then larger size until entire string is retrieved
	int nSize = 256;
	do
	{
		nSize += 256;
		nLen = _LoadString(nID, GetBuffer(nSize-1), nSize);
	} while (nSize - nLen <= CHAR_FUDGE);
	ReleaseBuffer();

	return nLen > 0;
/////////////v2
bool CStdStr<CT>::Load(UINT nId)
{
	bool bLoaded		= false;	// set to true of we succeed.

#ifdef _MFC_VER		// When in Rome...

	CString strRes;
	bLoaded				= FALSE != strRes.LoadString(nId);
	if ( bLoaded )
		*this			= strRes;

#else
	
	// Get the resource name and module handle

	PCTSTR szName		= MAKEINTRESOURCE((nId>>4)+1); // lifted from CString
	HMODULE hModule		= GetResourceHandle();
	DWORD dwSize		= 0;

	// No sense continuing if we can't find the resource

	HRSRC hrsrc			= ::FindResource(hModule, szName, RT_STRING);

	if ( NULL == hrsrc )
		TRACE(_T("Cannot find resource %d: 0x%X"), nId, ::GetLastError());
	else if ( 0 == (dwSize = ::SizeofResource(hModule, hrsrc) / sizeof(CT)) )
		TRACE(_T("Cannot get size of resource %d: 0x%X\n"), nId, GetLastError());
	else
	{
		bLoaded			= ( 0 != ssload(hModule, nId, Buffer(dwSize), dwSize) );
		ReleaseBuffer();
	}

#endif

	if ( !bLoaded )
		TRACE(_T("String not loaded 0x%X\n"), ::GetLastError());

	return bLoaded;
}

#ifdef SS_ANSI
#else
	inline int ssload(HMODULE hInst, UINT uId, PSTR pBuf, int nMax)
	{
		return ::LoadStringA(hInst, uId, pBuf, nMax);
	}
	inline int ssload(HMODULE hInst, UINT uId, PWSTR pBuf, int nMax)
	{
		return ::LoadStringW(hInst, uId, pBuf, nMax);
	}
#endif

///////
*/
}

///////////////////////////////////////////////////////////////////////////////
// Concatenation

//::operator+=()---------------------------------------------------------------
/*Concatenates a new string to the end of an existing string.
  Returns: reference to this string.

  Note: memory exceptions may occur because new storage may be allocated for 
        characters added to this CString object.

  Example:

    CString strTemp("abc");
    strTemp += "def";
    ASSERT(strTemp == "abcdef");

 */
const CString& CString::operator+=(const CString& string //[in] a CString to 
                                   //concatenate to this string.
                                  )
{
m_pData->append(*string.m_pData);
return *this;
}

const CString& CString::operator+=(TCHAR ch //[in] a character to concatenate
                                            //to this string.
                                  )
{
m_pData->append(1,ch);
return *this;
}

#ifdef _UNICODE
  /*Concatenate a single-byte character after converting it to TCHAR
   */
  const CString& CString::operator+=(char ch //[in] a character to concatenate
                                             //to this string.
                                    )
    {
    m_pData->append(1,(TCHAR)ch);
    return *this;
    }
#endif

const CString& CString::operator+=(LPCTSTR lpsz //[in] a pointer to 
                      //a zero-terminated string to concatenate to this string.
                                  )
{
ASSERT(lpsz != NULL);
m_pData->append(lpsz);
return *this;
}

///////////////////////////////////////////////////////////////////////////////
// Comparison

//::Compare()------------------------------------------------------------------
/*Performs a case-sensitive comparison of the strings, and is not affected by 
  locale. 
  Returns:
    - A negative value if the first differing element in the controlled sequence
    compares less than the corresponding element in the operand sequence, 
    or if the two have a common prefix but the operand sequence is longer. 
    - Zero if the two compare equal element by element and are the same length. 
    - A positive value otherwise. 

 */
int CString::Compare(LPCTSTR lpsz //[in] a zero-terminated string used for 
                                  //comparison
                     ) const
{
return m_pData->compare(lpsz);
}

//::CompareNoCase()------------------------------------------------------------
/*Performs a case-insensitive comparison of the strings, and is not affected 
  by locale. 
  Returns:
    - A negative value if the first differing element in the controlled sequence
    compares less than the corresponding element in the operand sequence, 
    or if the two have a common prefix but the operand sequence is longer. 
    - Zero if the two compare equal element by element and are the same length. 
    - A positive value otherwise. 
 */
int CString::CompareNoCase(LPCTSTR lpsz //[in] a zero-terminated string used for 
                                        //comparison
                          ) const
{
ASSERT(lpsz != NULL);
return _tcsicmp(m_pData->c_str(), lpsz);
}

//::Collate()------------------------------------------------------------------
/*Performs a case-sensitive comparison of the strings according to the code 
  page currently in use.
  Returns:
    - A negative value if the first differing element in the controlled sequence
    compares less than the corresponding element in the operand sequence, 
    or if the two have a common prefix but the operand sequence is longer. 
    - Zero if the two compare equal element by element and are the same length. 
    - A positive value otherwise.

  Example:

    CString str1 = _T("co-op");
    CString str2 = _T("coop");
    //Collation uses language rules, such as ignoring dashes
    int iRes = str1.Collate(str2);
    ASSERT(iRes == 0);
 */
int CString::Collate(LPCTSTR lpsz //[in] a zero-terminated string used for 
                                  //comparison
                          ) const
{
ASSERT(lpsz != NULL);
return _tcscoll(m_pData->c_str(), lpsz);
}

//::CollateNoCase()------------------------------------------------------------
/*Performs a case-insensitive comparison of the strings, according to the code 
  page currently in use.

  Returns:
    - A negative value if the first differing element in the controlled sequence
    compares less than the corresponding element in the operand sequence, 
    or if the two have a common prefix but the operand sequence is longer. 
    - Zero if the two compare equal element by element and are the same length. 
    - A positive value otherwise.

  Example:

    CString str1 = _T("co-op");
    CString str2 = _T("Coop");
    //Collation uses language rules, such as ignoring dashes
    int iRes = str1.CollateNoCase(str2);
    ASSERT(iRes == 0);
 */
int CString::CollateNoCase(LPCTSTR lpsz //[in] a zero-terminated string used for 
                                        //comparison
                          ) const
{
ASSERT(lpsz != NULL);
return _tcsicoll(m_pData->c_str(), lpsz);
}


///////////////////////////////////////////////////////////////////////////////
// Extraction

//::Mid()----------------------------------------------------------------------
/*Extracts a substring of length iCount characters from this CString object, 
  starting at position iFirst.
  Returns: a copy of the specified range of characters or an empty string.

  Example:

    CString strTemp(_T("abcdef"));
    CString strToken = strTemp.Mid(2, 3);
    ASSERT(strToken == _T("cde"));

 */
CString CString::Mid(int iFirst, //[in]zero-based index of the first character
                     //that is to be included in the extracted substring.
                     int iCount  //[in] number of characters to extract.
                    ) const
{
CString strResult;
    //Validate parameters
if (iFirst < 0)
  iFirst = 0;
if (iCount < 0)
  iCount = 0;
if (iFirst + iCount > static_cast<int>(m_pData->length()))
	iCount = static_cast<int>(m_pData->length()) - iFirst;
if (iFirst > static_cast<int>(m_pData->length()))
	iCount = 0;

ASSERT(iFirst >= 0);
ASSERT(iFirst + iCount <= static_cast<int>(m_pData->length()));

	//Optimize case of returning entire string
if (iFirst == 0 && iFirst + iCount == static_cast<int>(m_pData->length()))
  return *this;

strResult.m_pData = m_pData->substr(iFirst, iCount);
return strResult;
}

/*Returns: a copy of the rightmost characters from the postion given by iFirst
  or an empty string.
 */
CString CString::Mid(int iFirst //[in]zero-based index of the first character
                     //that is to be included in the extracted substring.
                     ) const
{
return Mid(iFirst, m_pData->length() - iFirst);
}

//::Left()---------------------------------------------------------------------
/*Extracts the first iCount characters. 
  Returns: returns a copy of the extracted substring or an empty string.

  Example:
    CString strTemp(_T("abcdef"));
    CString strToken = strTemp.Right(2)
    ASSERT(strToken == _T("ab"));
 */
CString CString::Left(int iCount //[in] number of characters to extract
                     ) const
{
if (iCount < 0)
	iCount = 0;
if (iCount >= static_cast<int>(m_pData->length()))
	return *this;

CString strResult;
strResult.m_pData = m_pData->substr(0, iCount);
return strResult;
}

//::Right()--------------------------------------------------------------------
/*Extracts the rightmost iCount characters. If iCount exceeds the string 
  length, then the entire string is extracted.
  Returns: returns a copy of the extracted substring or an empty string.

  Example:
    CString strTemp(_T("abcdef"));
    CString strToken = strTemp.Right(2)
    ASSERT(strToken == _T("ef"));
 */
CString CString::Right(int iCount //[in] number of characters to extract
                      ) const
{
if (iCount < 0)
	iCount = 0;
if (iCount >= static_cast<int>(m_pData->length()))
	return *this;

CString strResult;
strResult.m_pData = m_pData->substr(static_cast<int>(m_pData->length()) - 
                                    iCount);
return strResult;
}

//::SpanIncluding()------------------------------------------------------------
/*Extracts a substring that contains only the characters in a set, beginning 
  with the first character in the string and ending when a character is found
  in the string that is not in lpszCharSet. 
  Returns: a substring that contains characters found in both: this string and 
  in the lpszCharSet. If the first character in the string is not in 
  the specified set, an empty strin is returned.


  Example:

      CString strTemp(_T("babylon"));
      CString strRes = strTemp.SpanIncluding(_T("abon"));
      ASSERT( strRes == _T("bab") );
      strRes = strTemp.SpanIncluding(_T("ylon"));
      ASSERT( strRes.IsEmpty() );

 */
CString CString::SpanIncluding(LPCTSTR lpszCharSet //[in] a set of characters
                               //to be excluded
                              ) const
{
return( Left( _tcsspn(m_pData->c_str(), lpszCharSet)) );
}

//::SpanExcluding()------------------------------------------------------------
/*Extracts all characters found before any of given delimiter characters,
  beginning with the first character in the string and ending with the 
  first character found in the string that is also in lpszCharSet.
  Returns: a substring with part of this string that is left from first
  delimiter found or the entire string if no character in lpszCharSet is found.

  Example:

      CString strTemp(_T("babylon vejo"));
      CString strRes = strTemp.SpanExcluding(_T(".; :-"));
      ASSERT( strRes == _T("babylon") );

 */
CString CString::SpanExcluding(LPCTSTR lpszCharSet //[in] a set of delimiting
                                                   //characters
                               ) const
{
return( Left(_tcscspn(m_pData->c_str(), lpszCharSet)) );
}

///////////////////////////////////////////////////////////////////////////////
// Conversions

//::MakeUpper()----------------------------------------------------------------
/*Converts all the characters in this string to uppercase characters.
 */
void CString::MakeUpper()
{
std::ctype<TCHAR>().toupper(m_pData->begin(), m_pData->end() );
}

//::MakeLower()----------------------------------------------------------------
/*Converts all the characters in this string to lowercase characters.
 */
void CString::MakeLower()
{
std::ctype<TCHAR>().tolower(m_pData->begin(), m_pData->end() );
}

//::MakeReverse()--------------------------------------------------------------
/*Reverses the order of the characters in this string.
 */
void CString::MakeReverse()
{
long lLeftIndex  = 0;
long lRightIndex = m_pData->length() - 1;
while( lLeftIndex++ < lRightIndex-- )
  {
  TCHAR chSwap = m_pData->at(lLeftIndex);
  m_pData->at(lLeftIndex ) = m_pData->at(lRightIndex);
  m_pData->at(lRightIndex) = chSwap;
  }
}

///////////////////////////////////////////////////////////////////////////////
// Formatting

//::Format()-------------------------------------------------------------------
/*This function creates a string according to the given format and stores it 
  in this object.
 */
void _cdecl CString::Format(LPCTSTR lpszFormat, //[in] format-control string;
                           //it has the same form and function as the format
                           //argument for the printf function.
                            ...)
{
va_list argList;
va_start(argList, lpszFormat);
FormatV(lpszFormat, argList);
va_end(argList);
}

/*Reads the format string from a string resource.
 */
void _cdecl CString::Format(UINT nFormatID, //[in] string resource identifier 
                            //that contains the format-control string;
                            //it has the same form and function as the format
                            //argument for the printf function.
                            ...)
{
}

//::FormatV()------------------------------------------------------------------
/*This method formats and stores a series of characters and values in the
  string object. The string and arguments are converted and output according
  to the corresponding format specification in lpszFormat.

  Note: If this string object itself is offered as a parameter to this->FormatV, 
       the call fails.
 */
void CString::FormatV(LPCTSTR lpszFormat, //[in] format-control string
                      va_list argList     //[in] list of arguments that are passed
                      )
{
try
  {
  long buffer_size = _tcslen( lpszFormat ) * 2;
  CString format_object( lpszFormat );

  int string_index = 0;
  while((string_index = format_object.Find( _T( '%' ), string_index ) ) != (-1) )
   {
     string_index++;
     // Add 128 bytes for every % in the string
     buffer_size += 128;
   }
  TCHAR * buffer_to_write_to = NULL;

  try
    {
    buffer_to_write_to = (TCHAR *) malloc( ( buffer_size + 1 ) * sizeof( TCHAR ) );

    va_list argListNew;
    if ( buffer_to_write_to == NULL )
      {
        va_end( argListNew );
        return;
      }

     bool exit_loop = false;

     while( exit_loop != true )
     {
        argListNew = argList;

        if ( _vsntprintf( buffer_to_write_to, buffer_size, lpszFormat, argListNew ) == (-1) )
        {
           buffer_size *= 2;

           free( buffer_to_write_to );
           buffer_to_write_to = NULL;

           buffer_to_write_to = (TCHAR *) malloc( ( buffer_size + 1 ) * sizeof( TCHAR ) );

           if ( buffer_to_write_to == NULL )
           {
              va_end( argListNew );
              return;
           }
        }
        else
        {
           exit_loop = true;
        }
     }

     va_end( argListNew );

     // Now copy the string into our buffer

     m_pData->assign( buffer_to_write_to );
     free( buffer_to_write_to );
     buffer_to_write_to = NULL;
  }
  catch( ... )
  {
     try
     {
        if ( buffer_to_write_to != NULL )
        {
           free( buffer_to_write_to );
           buffer_to_write_to = NULL;
        }
     }
     catch( ... )
     {
     }
  }
}
catch( ... )
  {
  }

}

//----------------------------------------------------------------------------
/* throws memory exception
#ifdef _WIN32
  #include <Windows.h> //FormatMessage()
#endif
/*
 */
void _cdecl CString::FormatMessage(LPCTSTR lpszFormat, ...)
{
va_list argList;
va_start(argList, szFormat);
LPTSTR szTemp;
if ((::FormatMessage(FORMAT_MESSAGE_FROM_STRING|
                     FORMAT_MESSAGE_ALLOCATE_BUFFER,
                     lpszFormat,
                     0,
                     0,
                     &szTemp,
                     0,
                     &argList) == 0) || 
    (szTemp == NULL) )
  {
  throw std::runtime_error(_T("out of memory"));
  }

m_pData = szTemp;
::LocalFree(szTemp);
va_end(argList);
}

//----------------------------------------------------------------------------
/*
 */
void _cdecl CString::FormatMessage(UINT nFormatID, ...)
{
CString lpszFormat;
lpszFormat.LoadString(nFormatId);
va_list argList;
va_start(argList, szFormat);
LPTSTR szTemp;
if ((::FormatMessage(FORMAT_MESSAGE_FROM_STRING|
                     FORMAT_MESSAGE_ALLOCATE_BUFFER,
                     lpszFormat,
                     0,
                     0,
                     &szTemp,
                     0,
                     &argList) == 0) || 
    (szTemp == NULL) )
  {
  throw std::runtime_error(_T("out of memory"));
  }

m_pData = szTemp;
::LocalFree(szTemp);
va_end(argList);
}

//::Replace()------------------------------------------------------------------
/*
 */
int CString::Replace(TCHAR chOld, //[in] character to be replaced 
                     TCHAR chNew  //[in] character replacing chOld
                    )
{
}

/*
 */
int CString::Replace(LPCTSTR lpszOld, //[in] token string to be replaced
                     LPCTSTR lpszNew  //[in] token string replacing lpszOld 
                                      //or NULL
                    )
{
}

//::Remove()-------------------------------------------------------------------
/*
 */
int CString::Remove(TCHAR chRemove)
{
}

//::Insert()-------------------------------------------------------------------
/*
 */
int CString::Insert(int iIndex, TCHAR ch)
{
}

/*
 */
int CString::Insert(int iIndex, LPCTSTR pstr)
{
}

//::Delete()-------------------------------------------------------------------
/*
 */
int CString::Delete(int iIndex, //[in]
                    int iCount  //[in] = 1
                    )
{

}

//::TrimRight()----------------------------------------------------------------
/*
 */
void CString::TrimRight()
{
  //Find index of first non-white character
long lIndex = m_pData->length() - 1;
if ( _istspace( m_pData->at(lIndex)))
  {
  while(_istspace( m_pData->at(--lIndex)) )
    {
    if (lIndex == 0 )
      break;
    }
  m_pData->resize(lIndex);
  }
}

/*
 */
void CString::TrimRight(TCHAR chTarget)
{
while( chTarget == m_pData->at( m_pData->length() - 1 ) )
  {
  m_pData->erase( m_pData->length() - 1, 1 );
  }
}

/*
 */
void CString::TrimRight(LPCTSTR lpszTargets)
{
}

//::TrimLeft()-----------------------------------------------------------------
/*
 */
void CString::TrimLeft()
{
long lLen = m_pData->length();

if( lLen > 0 )
  {
  long lIndex = 0;
  while( _istspace(m_pData->at(lIndex++)) )
    {
    //If exception out_of_range is not handled, exit the loop
    if (lIndex >= lLen)
      break;
    }

  m_pData->erase( 0, lIndex );
  }

}

/*
 */
void CString::TrimLeft(TCHAR chTarget)
{
long lLen = m_pData->length();

if ( lLen > 0 )
  {
  long lIndex = 0;
  while( chTarget == m_pData->at(lIndex) )
    {
    lIndex++;
    //If exception out_of_range is not handled, exit the loop
    if (lIndex >= lLen)
      break;
    }
  m_pData->erase( 0, lIndex );
  }

}

/*
 */
void CString::TrimLeft(LPCTSTR lpszTargets)
{
}

///////////////////////////////////////////////////////////////////////////////
// Searching

//::Find()---------------------------------------------------------------------
/*Searches this string for the first match of a character.
  Returns: zero-based index of the first character in this string that matches 
  the given character or -1 if string does not contain that character.
 */
int CString::Find(TCHAR ch //[in] a character to search for
                 ) const
{
return static_cast<int>(m_pData->find_first_of(ch));
}

/*Note: The character at iStart is excluded from the search if iStart is not
        equal to 0.
 */
int CString::Find(TCHAR ch,  //[in] a character to search for
                  int iStart //[in] index of the character in the string to 
                             //begin the search with.
                 ) const
{
return static_cast<int>(m_pData->find_first_of(ch, iStart+1));
}

/*Searches this string for the first match of a substring. 
  Returns: zero-based index of the first character in this string that matches 
  the given substring or -1 if string does not contain that substring.
 */
int CString::Find(LPCTSTR lpszSub //[in] a substring to search for.
                 ) const
{
return static_cast<int>(m_pData->find(lpszSub));
}

/*
 */
int CString::Find(LPCTSTR lpszSub, //[in] a substring to search for.
                  int iStart //[in] index of the character in the string to 
                             //begin the search with.
                 ) const
{
return static_cast<int>(m_pData->find(lpszSub, iStart+1));
}

//::FindOneOf()----------------------------------------------------------------
/*Searches this string for the first character that matches any character 
  contained in a set of characters.
  Returns: zero-based index of the first character in this string that is also
  element of given set or -1 if string does not contain characters from the set.
 */
int CString::FindOneOf(LPCTSTR lpszCharSet //[in] string containing characters
                                           //to find
                      ) const
{
return static_cast<int>(m_pData->find_first_of(lpszCharSet));
}

//::ReverseFind()--------------------------------------------------------------
/*Searches this CString object for the last match of the given character.
  Returns: index of the last character in this string equal to the requested 
  character or –1 if the character is not found.
 */
int CString::ReverseFind(TCHAR ch //[in] character to search 
                        ) const
{
return m_pData->rfind(ch);
}

///////////////////////////////////////////////////////////////////////////////
// Buffer Access

//::GetBuffer()----------------------------------------------------------------
/*Obtains a pointer to the internal character buffer for this object.
  Returns: pointer to the object’s zero-terminated character buffer.
 */
LPTSTR CString::GetBuffer(int iMinBufLength //[in] minimum size of the character
                       //buffer in characters. This value does not include space
                       //for a null terminator.
                         )
{
ASSERT(iMinBufLength >= 0);

m_pData->resize(iMinBufLength + 1);
m_pData->at(iMinBufLength) = _T('\0'); //Set the null-terminator
return m_pData->empty() ? const_cast<LPTSTR>(m_pData->data()) : &(m_pData->at(0));
}

//::ReleaseBuffer()------------------------------------------------------------
/*Releases a buffer allocated by GetBuffer. If the string in the buffer is 
  zero-terminated, you length argument can be omited. The address returned by 
  GetBuffer is invalid after the call to ReleaseBuffer or any other CString 
  operation.

  Example:

    CString strTemp(_T("Marocco"));
    LPTSTR szTemp = strTemp.GetBuffer(32);
    _tcscpy(szTemp, _T("abc"));
    szTemp.ReleaseBuffer();  //Free memory
    ASSERT(szTemps.GetLength() == 3);

 */
void CString::ReleaseBuffer(int iNewLength //[in] = -1 new length of the string
                            //in characters, not counting a null terminator. 
                            //If the string is null-terminated, the -1 default
                            //value sets the CString size to the current length
                            //of the string.
                            )
{
m_pData->resize( (iNewLength > -1 ? 
                      iNewLength : 
                      std::char_traits<TCHAR>::length(m_pData->c_str()) ) );
}

//::GetBufferSetLength()-------------------------------------------------------
/*Resizes the internal data storage for this string object.
  Returns: pointer to the zero-terminated character buffer.
 */
LPTSTR CString::GetBufferSetLength(int iNewLength //[in] new size of 
                                   //the character buffer in characters
                                   )
{
iNewLength = (iNewLength > 0) ? iNewLength : 0;

m_pData->resize(iNewLength+1);
m_pData->at(iNewLength) = _T('\0'); //Set the null-terminator

return const_cast<LPTSTR>(m_pData->data());
}

//::FreeExtra()----------------------------------------------------------------
/*Call this member function to free any extra memory previously allocated by 
  the string but no longer needed.
 */
void CString::FreeExtra()
{
if (m_pData->capacity() > m_pData->length())
  {
  m_pData->resize( std::char_traits<TCHAR>::length(m_pData->c_str()) );
  }
}

//::LockBuffer()---------------------------------------------------------------
/*Ensures that the string’s exclusive hold on the internal data storage will
  remain intact. Call UnlockBuffer to allow refernce counting.
 */
LPTSTR CString::LockBuffer()
{
//TODO:
	LPTSTR lpsz = GetBuffer(0);
//	GetData()->nRefs = -1;
	return lpsz;

}

//::UnlockBuffer()-------------------------------------------------------------
/*Enables reference counting and releases the string in the internal data 
  storage.
 */
void CString::UnlockBuffer()
{
//TODO:
//	ASSERT(GetData()->nRefs == -1);
//	if (GetData() != _afxDataNil)
//		GetData()->nRefs = 1;

}

//::AnsiToOem()----------------------------------------------------------------
#ifndef _UNICODE
  #ifdef _WIN32
    #include <Windows.h> //CharToOem()
  #endif
/*Converts all the characters in this string from the American National 
  Standards Institute (ANSI) character set to the original equipment 
  manufacturer (OEM) character set.

  Note: The function is not available if _UNICODE is defined.

  Note: Microsoft Windows specific (Win). 
 */
void CString::AnsiToOem()
{
#ifdef _WIN32
  if (!IsEmpty())
    {
    ::CharToOem(reinterpret_cast<const char*>(m_pData->c_str()),//string to translate
		  				  reinterpret_cast<char*>(&(m_pData->at(0))));//translated string

    /*Note: If the CharToOem function is being used as an ANSI function, 
      the string can be translated in place by setting the lpszDst parameter to
      the same address as the lpszSrc parameter. This cannot be done if 
      CharToOem is being used as a wide-character function.
      CharToOem function is implemented as Unicode and ANSI versions only on 
      Windows NT/2000.
    */
  }
#else
  ASSERT(false);
#endif
}
#endif

//::OemToAnsi()----------------------------------------------------------------
#ifndef _UNICODE
  #ifdef _WIN32
    #include <Windows.h> //OemToChar()
  #endif
/*Converts all the characters in this string from the original equipment 
  manufacturer (OEM) character set to the American National Standards Institute
  (ANSI) character set.

  Note: The function is not available if _UNICODE is defined.

  Note: Microsoft Windows specific (Win). 
 */
void CString::OemToAnsi()
{
#ifdef _WIN32
  if (!IsEmpty())
    {
    ::OemToChar(reinterpret_cast<const char*>(c_str()), //string to translate
		  				  reinterpret_cast<char*>(&(m_pData->at(0))));//translated string

    /*Note: If the OemToChar function is being used as an ANSI function, 
      the string can be translated in place by setting the lpszDst parameter to
      the same address as the lpszSrc parameter. This cannot be done if 
      OemToChar is being used as a wide-character function.
      OemToChar function is implemented as Unicode and ANSI versions only on 
      Windows NT/2000.
    */
  }
#else
  ASSERT(false);
#endif

}
#endif


///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: 
 *  9    Biblioteka1.8         5/6/02 4:09:19 PM    Darko           TrimLeft() If
 *       exception out_of_range is not handled, lenght exits the loop
 *  8    Biblioteka1.7         1/29/02 11:22:14 PM  Darko           Used lbraries
 *       notes 
 *  7    Biblioteka1.6         1/25/02 4:58:54 PM   Darko           Updated
 *       comments
 *  6    Biblioteka1.5         1/6/02 1:47:33 AM    Darko           
 *  5    Biblioteka1.4         1/3/02 1:58:57 AM    Darko           TrimLeft();
 *       TrimRight()
 *  4    Biblioteka1.3         12/30/01 8:20:21 PM  Darko           
 *  3    Biblioteka1.2         12/24/01 12:37:36 AM Darko           operators [],
 *       LPCTSR
 *  2    Biblioteka1.1         11/6/01 3:52:36 PM   Darko           constructors
 *  1    Biblioteka1.0         11/5/01 3:12:59 PM   Darko           
 * $
 *****************************************************************************/

//////////////////////////////////////////////////////////////////////////////
// Diagnostic support
/*
#ifdef _DEBUG
//Note: uses Microsoft Fundation Library (MFC).
CDumpContext& AFXAPI operator<<(CDumpContext& dc, const CString& string)
{
	dc << string.m_pchData;
	return dc;
}
#endif //_DEBUG

	// input and output
#ifdef _DEBUG
	friend CDumpContext& AFXAPI operator<<(CDumpContext& dc,
				const CString& string);
#endif
*/
