/*$Workfile: KString.h$: header file
  $Revision: 7$ $Date: 1/29/02 11:22:18 PM$ 
  $Author: Darko$

  Interface for the CString class
  Copyright: CommonSoft Inc
 */
/* Group=Strings                                                             */

#ifndef _KSTRING_H__
    //$Workfile: KString.h$ sentry
  #define _KSTRING_H__

#ifdef  _MSC_VER    //Microsoft Visual C/C++
  #if _MSC_VER > 1000
    #pragma once
  #endif // _MSC_VER > 1000

  //#include <tchar.h> //Unicode mapping
#else
  //#include "KTChar.h" //Unicode mapping
#endif

#ifdef __STRING__
  #define _STRING_
#endif

#ifdef __GNUG__ //GNU C++ compiler
  #ifdef __BASTRING__
    //included <std/bastring.h> with Free Software Foundation version of STL
    #define char_traits string_char_traits
  #endif //__BASTRING__
  #define _cdecl
#endif

#define TCHAR char
#define _T(t)     t             //See also: _TEXT

typedef const TCHAR*    LPCTSTR;
typedef const wchar_t*  LPCWSTR;
typedef const char*     LPCSTR;
typedef unsigned int    UINT;
typedef TCHAR*          LPTSTR;

#include <assert.h>
#define ASSERT assert

#define _tcsicmp    _stricmp    //Perform a lowercase comparison of strings.
#define _tcscoll    strcoll     //Compare strings using locale-specific information.
#define _tcsicoll   _stricoll   //Compare strings using locale-specific information.
#define _istspace   isspace     //Query if character is a white-space character (0x09 – 0x0D or 0x20).

///////////////////////////////////////////////////////////////////////////////
// If the symbol _UNICODE is defined, CString uses type
// {html:<I><B>}wchar_t{html:</B></I>}, a 2-byte  character type; otherwise, 
// it uses {html:<I><B>}char{html:</B></I>}, the normal 1-byte character type.
//
// Note: uses Standard Template Library (STL).
class CString
{
#ifdef _STRING_ //STL <string> header included
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

  friend CString operator+(const CString& string1,	const CString& string2);
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
#endif // _KSTRING_H__
/******************************************************************************
 * $Log: 
 *  7    Biblioteka1.6         1/29/02 11:22:18 PM  Darko           Used lbraries
 *       notes 
 *  6    Biblioteka1.5         1/24/02 7:19:32 PM   Darko           Updated
 *       comments
 *  5    Biblioteka1.4         1/23/02 7:23:25 PM   Darko           
 *  4    Biblioteka1.3         1/6/02 1:47:37 AM    Darko           
 *  3    Biblioteka1.2         12/30/01 8:20:25 PM  Darko           
 *  2    Biblioteka1.1         11/6/01 3:52:08 PM   Darko           pointer to data
 *       holder
 *  1    Biblioteka1.0         11/5/01 3:13:04 PM   Darko           
 * $
 *****************************************************************************/