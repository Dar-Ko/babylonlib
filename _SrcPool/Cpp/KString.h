/*$Workfile: KString.h$: header file
  $Revision: 13$ $Date: 2007-06-15 17:24:37$ 
  $Author: Darko Kolakovic$

  Interface for the CString class
  Copyright: CommonSoft Inc
 */
/* Group=Strings                                                             */

#ifndef _KSTRING_H_
    //$Workfile: KString.h$ sentry
  #define _KSTRING_H_

#ifdef  _MSC_VER    //Microsoft Visual C/C++
  #if _MSC_VER > 1000
    #pragma once
  #endif // _MSC_VER > 1000
#endif

#ifdef _STLP_STRING
  #if !definded _STLP_USE_NATIVE_STRING
    //included STLport std::string
    #define _STRING_ 14
  #endif
#endif
#ifdef __STRING__
  //included STL std::string
  #define _STRING_ 12
#endif

#ifdef __GNUG__ //GNU C++ compiler
  #ifdef __BASTRING__
    //included <std/bastring.h> with Free Software Foundation version of STL
    #define char_traits string_char_traits
  #endif //__BASTRING__
  #define _cdecl
#endif

#include "KTChar.h" //TCHAR
#include "KTrace.h" //ASSERT

#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
  #pragma message ("   #include " __FILE__ )
#endif

#ifdef __BORLANDC__
  #pragma option push -w-inl
//  #pragma warn -inl   // Turn off inline function warnings
#endif

/*
#define TCHAR char
#define _T(t)     t             //See also: _TEXT
  //TODO: exlude TCHAR( import KTChar.h)

typedef const TCHAR*    LPCTSTR;
typedef const wchar_t*  LPCWSTR;
typedef const char*     LPCSTR;
typedef unsigned int    UINT;
typedef TCHAR*          LPTSTR;
#define _tcsicmp    _stricmp    //Perform a lowercase comparison of strings.
#define _tcscoll    strcoll     //Compare strings using locale-specific information.
#define _tcsicoll   _stricoll   //Compare strings using locale-specific information.
#define _istspace   isspace     //Query if character is a white-space character (0x09 – 0x0D or 0x20).

*/
#ifdef _DEBUG
  //TODO: exlude ASSERT( import KTrace.h)
/*
  #ifndef ASSERT
    #include <assert.h>
    #define ASSERT assert
  #endif
  */
#endif


///////////////////////////////////////////////////////////////////////////////
// If the symbol _UNICODE is defined, CString uses type
// {html:<I><B>}wchar_t{html:</B></I>}, a 2-byte  character type; otherwise, 
// it uses {html:<I><B>}char{html:</B></I>}, the normal 1-byte character type.
//
// Note: uses Standard Template Library (STL).
class CString
{
#ifdef _STRING_ //STL <string> header included
  #ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
    #pragma message ("   #include <string>" )
  #endif
    //Uses STL string template as basic string handler
    //
    //Note:  <string> header have to be included before declaration of 
    //the CString class
  typedef std::basic_string<TCHAR, 
                            std::char_traits<TCHAR>
                            >   CStringHandler;
#endif

//Construction/destruction
public:
  CString();
  CString(const CString& strSource);
  CString(TCHAR   chSource, int iCount = 1);
  CString(LPCTSTR pchSource,int iLength);
  CString(const unsigned char* pszSource);
  CString(LPCWSTR szString);
  CString(LPCSTR  szString);
  virtual ~CString();

//Attributes
protected:
  CStringHandler* m_pData; //pointer to data holder

//Operations
public:
  //Indexed access

  int   GetLength() const;
  bool  IsEmpty() const;
  void  Empty();
  TCHAR GetAt(int iIndex) const;
  void  SetAt(int iIndex, TCHAR ch);
  TCHAR operator[](int iIndex) const;
  operator LPCTSTR() const;

  //Assignment

  const CString& operator=(const CString& stringSrc);
  const CString& operator=(TCHAR ch);
  #ifdef _UNICODE
    const CString& operator=(char ch);
  #endif
  const CString& operator=(LPCSTR lpsz);
  const CString& operator=(LPCWSTR lpsz);
  const CString& operator=(const unsigned char* psz);

  //Concatenation

  const CString& operator+=(const CString& string);
  const CString& operator+=(TCHAR ch);
  #ifdef _UNICODE
    const CString& operator+=(char ch);
  #endif
  const CString& operator+=(LPCTSTR lpsz);

  //Comparison

  int Compare      (LPCTSTR lpsz) const;
  int CompareNoCase(LPCTSTR lpsz) const;
  int Collate      (LPCTSTR lpsz) const;
  int CollateNoCase(LPCTSTR lpsz) const;

  //Extraction

  CString Mid(int iFirst, int iCount) const;
  CString Mid(int iFirst) const;
  CString Left(int iCount) const;
  CString Right(int iCount) const;
  CString SpanIncluding(LPCTSTR lpszCharSet) const;
  CString SpanExcluding(LPCTSTR lpszCharSet) const;

  //Conversions

  void MakeUpper();
  void MakeLower();
  void MakeReverse();

  //Formatting

  void Format(LPCTSTR lpszFormat, ...);
  void Format(UINT nFormatID, ...);
  void FormatV(LPCTSTR lpszFormat, va_list argList);
  void FormatMessage(LPCTSTR lpszFormat, ...);
  void FormatMessage(UINT nFormatID, ...);

  int Replace(TCHAR chOld, TCHAR chNew);
  int Replace(LPCTSTR lpszOld, LPCTSTR lpszNew);
  int Remove(TCHAR chRemove);
  int Insert(int iIndex, TCHAR ch);
  int Insert(int iIndex, LPCTSTR pstr);
  int Delete(int iIndex, int iCount = 1);

  void TrimRight();
  void TrimRight(TCHAR chTarget);
  void TrimRight(LPCTSTR lpszTargets);
  void TrimLeft();
  void TrimLeft(TCHAR chTarget);
  void TrimLeft(LPCTSTR lpszTargets);

  //Searching

  int Find(TCHAR ch) const;
  int Find(TCHAR ch, int iStart) const;
  int Find(LPCTSTR lpszSub) const;
  int Find(LPCTSTR lpszSub, int iStart) const;
  int FindOneOf(LPCTSTR lpszCharSet) const;
  int ReverseFind(TCHAR ch) const;

  //Buffer Access

  LPTSTR GetBuffer(int iMinBufLength);
  void ReleaseBuffer(int iNewLength = -1);
  LPTSTR GetBufferSetLength(int iNewLength);
  void FreeExtra();
  LPTSTR LockBuffer();
  void UnlockBuffer();

  bool LoadString(UINT nID);
  #ifndef _UNICODE
  //ANSI and OEM conversion in place

    void AnsiToOem();
    void OemToAnsi();
  #endif

  //Operators

  friend CString operator+(const CString& string1,  const CString& string2);
  friend CString operator+(const CString& string, TCHAR ch);
  friend CString operator+(TCHAR ch, const CString& string); 
  #ifdef _UNICODE
    friend CString operator+(const CString& string, char ch);
    friend CString operator+(char ch, const CString& string);
  #endif
  friend CString operator+(const CString& string, LPCTSTR lpsz);
  friend CString operator+(LPCTSTR lpsz, const CString& string);

private:

  //I
  void Append(LPCTSTR string_p );
  void Append(TCHAR text_character, int number_of_times );
  void Append(const CString& source );
  void Copy(LPCSTR string_p, long number_of_characters = (-1), long beginning_at = 0 );
  void Copy(LPCWSTR string_p, long number_of_characters = (-1), long beginning_at = 0 );
  int  GetSize( void ) const;
  void SetLength( long new_length );

  //II
  //LPTSTR m_pchData;   // pointer to ref counted string data

  // implementation helpers
  /*
  int GetAllocLength() const;
  CStringData* GetData() const;
  void Init();
  void AllocCopy(CString& dest, int nCopyLen, int nCopyIndex, int nExtraLen) const;
  void AllocBuffer(int nLen);
  void AssignCopy(int nSrcLen, LPCTSTR lpszSrcData);
  void ConcatCopy(int nSrc1Len, LPCTSTR lpszSrc1Data, int nSrc2Len, LPCTSTR lpszSrc2Data);
  void ConcatInPlace(int nSrcLen, LPCTSTR lpszSrcData);
  void CopyBeforeWrite();
  void AllocBeforeWrite(int nLen);
  void Release();
  static void PASCAL Release(CStringData* pData);
  static int PASCAL SafeStrlen(LPCTSTR lpsz);
  static void FASTCALL FreeData(CStringData* pData);
*/
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*Destructor
 */
inline CString::~CString()
  {
  //TODO: replace with CStringHandler base class
  if (m_pData != NULL)
    delete m_pData;
  }

  
//::operator<()----------------------------------------------------------------
/*Operator performs case-sensitive comparison of two strings.
  Returns true if the strings meet the comparison condition; 
  otherwise returns false.
 */
inline bool operator< (const CString& s1, const CString& s2)
{
return s1.Compare(s2) < 0;
}

inline bool operator< (const CString& s1, LPCTSTR s2)
{
return s1.Compare(s2) < 0;
}

inline bool operator< (LPCTSTR s1, const CString& s2)
{
return s2.Compare(s1) > 0;
}

//::operator<=()---------------------------------------------------------------
/*Operator performs case-sensitive comparison of two strings.
  Returns true if the strings meet the comparison condition; 
  otherwise returns false.
 */
inline bool operator<=(const CString& s1, const CString& s2)
{
return s1.Compare(s2) <= 0;
}

inline bool operator<=(const CString& s1, LPCTSTR s2)
{
return s1.Compare(s2) <= 0;
}

inline bool operator<=(LPCTSTR  s1, const CString& s2)
{
return s2.Compare(s1) >= 0;
}

//::operator==()---------------------------------------------------------------
/*Operator performs case-sensitive comparison of two strings.
  Returns true if the strings meet the comparison condition; 
  otherwise returns false.
 */
inline bool operator==(const CString& s1, const CString& s2)
{
return s1.Compare(s2) == 0;
}

inline bool operator==(const CString& s1, LPCTSTR s2)
{
return s1.Compare(s2) == 0;
}

inline bool operator==(LPCTSTR s1, const CString& s2)
{
return s2.Compare(s1) == 0;
}

//::operator>=()---------------------------------------------------------------
/*Operator performs case-sensitive comparison of two strings.
  Returns true if the strings meet the comparison condition; 
  otherwise returns false.
 */
inline bool operator>=(const CString& s1, const CString& s2)
{
return s1.Compare(s2) >= 0;
}

inline bool operator>=(const CString& s1, LPCTSTR s2)
{
return s1.Compare(s2) >= 0;
}

inline bool operator>=(LPCTSTR s1, const CString& s2)
{
return s2.Compare(s1) <= 0;
}

//::operator>()----------------------------------------------------------------
/*Operator performs case-sensitive comparison of two strings.
  Returns true if the strings meet the comparison condition; 
  otherwise returns false.
 */
inline bool operator>(const CString& s1, const CString& s2)
{
return s1.Compare(s2) > 0;
}

inline bool operator>(const CString& s1, LPCTSTR s2)
{
return s1.Compare(s2) > 0;
}

inline bool operator>(LPCTSTR s1, const CString& s2)
{
return s2.Compare(s1) < 0;
}

//::operator!=()---------------------------------------------------------------
/*Operator performs case-sensitive comparison of two strings.
  Returns true if the strings meet the comparison condition; 
  otherwise returns false.
 */
inline bool operator!=(const CString& s1, const CString& s2)
{
return s1.Compare(s2) != 0;
}

inline bool operator!=(const CString& s1, LPCTSTR s2)
{
return s1.Compare(s2) != 0;
}

inline bool operator!=(LPCTSTR s1, const CString& s2)
{
return s2.Compare(s1) != 0;
}

///////////////////////////////////////////////////////////////////////////////
#ifdef __BORLANDC__
  #pragma option pop  // Turn back on inline function warnings
  //#pragma warn +inl   // Turn back on inline function warnings
#endif

#endif // _KSTRING_H_
/******************************************************************************
 * $Log: 
 *  13   Biblioteka1.12        2007-06-15 17:24:37  Darko Kolakovic _USE_MFC for
 *       CString
 *  12   Biblioteka1.11        2007-05-03 15:54:14  Darko Kolakovic ASSERT
 *  11   Biblioteka1.10        2004-06-01 16:52:17  Darko           STLport
 *       included
 *  10   Biblioteka1.9         2003-11-03 13:13:22  Darko           Borland pragmas
 *  9    Biblioteka1.8         2003-09-05 12:54:11  Darko           formatting
 *  8    Biblioteka1.7         2003-01-20 04:10:14  Darko           Added ASSERT
 *       and TCHAR header files
 *  7    Biblioteka1.6         2002-01-29 23:22:18  Darko           Used lbraries
 *       notes 
 *  6    Biblioteka1.5         2002-01-24 19:19:32  Darko           Updated
 *       comments
 *  5    Biblioteka1.4         2002-01-23 19:23:25  Darko           
 *  4    Biblioteka1.3         2002-01-06 01:47:37  Darko           
 *  3    Biblioteka1.2         2001-12-30 20:20:25  Darko           
 *  2    Biblioteka1.1         2001-11-06 15:52:08  Darko           pointer to data
 *       holder
 *  1    Biblioteka1.0         2001-11-05 15:13:04  Darko           
 * $
 *****************************************************************************/
