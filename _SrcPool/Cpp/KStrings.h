/*$Workfile: KStrings.h$: implementation file
  $Revision: 18$ $Date: 9/10/02 6:55:24 PM$
  $Author: Darko Kolakovic$

  String manipulation
  Copyright: CommonSoft Inc
  May 97 Darko Kolakovic
 */
/* Group=Strings                                                             */

#ifndef __KSTRINGS_H__
    /*KStrings.h sentry                                                      */
  #define __KSTRINGS_H__


#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
  #pragma message ("   #include " __FILE__ )
#endif

#include "KTypedef.h"  //DWORD

/* ///////////////////////////////////////////////////////////////////////// */
/*Macros                                                                     */

/* ///////////////////////////////////////////////////////////////////////// */
/*Declarations                                                               */
#ifdef __cplusplus
#define _K_EXTRNDECL_ /*extern declaration                                   */
extern "C"
  {
#else
  #define _K_EXTRNDECL_ extern
#endif

  _K_EXTRNDECL_ TCHAR* StrToLower(TCHAR* szDestination,       TCHAR* szSource);
  _K_EXTRNDECL_ TCHAR* StrPCpy(   TCHAR* szDestination, const TCHAR* szSource);
  _K_EXTRNDECL_ TCHAR* StrCatV(   TCHAR* szDestination, const TCHAR* szSource, ...);
  _K_EXTRNDECL_ TCHAR* StrDup(LPCTSTR pszSource);
  _K_EXTRNDECL_ int    StrICmp(LPCTSTR szStr1,LPCTSTR szStr2);
  _K_EXTRNDECL_ LPTSTR StrTrim(LPTSTR szSource);
  _K_EXTRNDECL_ LPTSTR StrTrimSlash(LPTSTR szSource);
  _K_EXTRNDECL_ DWORD  BintoU(TCHAR* lpszValue);
  _K_EXTRNDECL_ TCHAR* BintoA(TCHAR* szResult,DWORD dwValue,int iMsBit,int iLsBit,
                              TCHAR iTrueChar,TCHAR iFalseChar);
  _K_EXTRNDECL_ TCHAR* ChtoAscii(int ch);
  _K_EXTRNDECL_ long   HextoL(LPCTSTR szSource);
  _K_EXTRNDECL_ long   OcttoL(LPCTSTR szSource);
  _K_EXTRNDECL_ TCHAR* UtoDec(unsigned long value, TCHAR* strResult);
  _K_EXTRNDECL_ TCHAR* UtoDecJust(unsigned long nValue, TCHAR* szDestination,
                                  int iSize, TCHAR cPad);

  _K_EXTRNDECL_ TCHAR* GetSubstring(TCHAR* szSource,TCHAR chDelimiter,int iSubstringIndex);
  _K_EXTRNDECL_ TCHAR* GetWord(TCHAR* lpszResult, TCHAR* lpszSource);
  _K_EXTRNDECL_ TCHAR* GetFirstSpace(TCHAR* lpszSource);
  _K_EXTRNDECL_ LPTSTR ReplaceEscapeSeq(LPTSTR szFormat);
  _K_EXTRNDECL_ LPTSTR ReplaceSpaces(LPTSTR szSource);
  _K_EXTRNDECL_ char*  ItoA(int iValue, char* szResult, int iRadix);
#ifdef __cplusplus
  }
#endif

/* ///////////////////////////////////////////////////////////////////////// */
/* C++ declarations                                                          */
#ifdef __cplusplus
/* ///////////////////////////////////////////////////////////////////////// */
/* Overloaded functions                                                      */
#include "KTChar.h"  //_T() macro
int EnumSubstring(const TCHAR* strSource,TCHAR chDelimiter = _T('\n'));
int EnumSubstring(const TCHAR* strSource,const TCHAR* Delimiters);
int GetLine(LPTSTR& szSource, LPTSTR& szLine);
/* ///////////////////////////////////////////////////////////////////////// */
/* STL functions                                                             */
  #ifdef _STRING_ //string standard header (STL)

    _K_EXTRNDECL_ std::string StrToUpper(const std::string& strSource);
    _K_EXTRNDECL_ std::string LocalDateToStr(char* szFormat = "%a %b %d %Y, %X %z");
  #endif //_STRING_

///////////////////////////////////////////////////////////////////////////////
// Inlines

//BoolToA()--------------------------------------------------------------------
/*Converts logical value of an expression to readable string.

  Returns "true' if bExpression is true, or "false" if bExpression is false.
 */
inline LPCTSTR BoolToA(bool bExpression //[in] Value of an expression
                       )
{
return (bExpression ? _T("true"): _T("false"));
}


#endif //__cplusplus

/* ///////////////////////////////////////////////////////////////////////// */
#endif  /*__KSTRINGS_H__                                                     */

/*****************************************************************************
 * $Log:
 *  5    Biblioteka1.4         18/07/2001 11:32:55 PMDarko           VSS tags
 *  4    Biblioteka1.3         11/07/2001 10:53:06 PMDarko
 *  3    Biblioteka1.2         08/06/2001 11:52:06 PMDarko           VSS
 *  2    Biblioteka1.1         21/09/2000 1:17:18 AMDarko           HextoL(),
 *       UtoDec()
 *  1    Biblioteka1.0         13/08/2000 4:00:40 PMDarko
 * $
 *   Jan 2k MSVC++ 6 revision D.K.
 *   Jan 2k STL functions
 *****************************************************************************/
