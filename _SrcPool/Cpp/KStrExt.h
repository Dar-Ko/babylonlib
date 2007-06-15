/*$Workfile: KStrExt.h$: header file
  $Revision: 11$ $Date: 2007-06-15 17:24:25$
  $Author: Darko Kolakovic$

  CString Extensions declarations
  CommonSoft Inc.
  Feb 96 Darko Kolakovic
  May 97
 */
/* Group=Strings                                                             */

#ifndef _KSTRINGEXT_H_
    //$Workfile: KStrExt.h$ sentry
  #define _KSTRINGEXT_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

//#ifdef WIN32
//  #ifdef __AFXWIN_H__
//    #include <afxwin.h>
//  #endif
//#endif

  #ifdef _DOCBROwSER //Dummy elif
  #else
//TODO: Replace MFC with STL D.K.
#include <string.h> //TCHAR macro

///////////////////////////////////////////////////////////////////////////////
// Helper class RESOURCESTRINGID
/*String resource ID type
  Used to distinguish UINT from resource UINT for overloaded operators

  Note: Microsoft Windows specific (Win).

  Example:
    CString strTitle;
    strTitle << RESOURCESTRINGID(IDS_PAN_FILENAME) << (TCHAR)'\t'
             << _T("File Name") << '\n' << _T('\n');
 */
class RESOURCESTRINGID
{
public:
  RESOURCESTRINGID(const unsigned int nID) : m_IDStr(nID)
    {};
protected:
  const unsigned int m_IDStr; //String resource ID
public:
  operator int()
    {return m_IDStr;}
  operator unsigned int()
    {return m_IDStr;}
};

/*Synonym for Empty CString function for overloaded operators

  Example:
    CString strTitle;
    EmptyString Erase = 0;
    strTitle << Erase << _T("Number ") << 12 << '\n';
 */
typedef void (*EmptyString)();

///////////////////////////////////////////////////////////////////////////////
//Functions using MFC
//  TODO: replace MFC D.K.

#ifdef _USE_MFC
  CString  GetSubstring(CString& strSource,LPCSTR Delimiters,int iSubstringIndex);
  CString  FitString(CDC* pDC,CString strText, int iWidth,LPCTSTR szSuffix);
  CString  Extract(CString& strSrc, const int iStart, const int iEnd );
  CString& ReplaceChar(CString& strSource, TCHAR chOld, TCHAR chNew);
  CString& ReplaceTabs(CString& strSource, const int iTabPos);
  int      FindNoCase(const CString& strSource, LPCTSTR szToken, const unsigned nStart = 0);

  ///////////////////////////////////////////////////////////////////////////////
  //Functions using STL and MFC
  #if defined(_STL) || defined (_USE_STL) //Use Standard Template Library (STL)
    //Note: include <strstrea.h> or <iostream.h> or <iostream>
    istream& operator>>(istream& cInput,CString& strTarget);
    ostream& operator<<(ostream& cOutput,const CString& strSource);
  #endif //_STL || _USE_STL
///////////////////////////////////////////////////////////////////////////////
//inline functions

//operator!()------------------------------------------------------------------
/*The logical-negation (logical-NOT) operator produces the value true (nonzero)
  if CString object is empty and the value 0 if CString contains any text.
 */
inline int operator!(CString& strSrc)
{
return strSrc.IsEmpty();
}

//operator--()-----------------------------------------------------------------
/*CString prefix decrement operator
 */
inline CString& operator--(CString& strSrc)
{
strSrc = strSrc.Left(strSrc.GetLength() - 1);
return strSrc;
}

//operator--()-----------------------------------------------------------------
/*CString postfix decrement operator.
  Example:
    CString strText;
    strText--;
    operator--(strText, 4);

 */
inline CString& operator --(CString& strSrc, int n)
{
if (strSrc.GetLength() <= n)
  strSrc.Empty();
else
  {
  if (n = 0)
    --strSrc;
  else
    strSrc = strSrc.Left(strSrc.GetLength() - n);
  }
return strSrc;
}

//operator<<()-----------------------------------------------------------------
/*Inserts a string to a CString object. Throws the memory exceptions in case
  of insufficient memory space.

  Example:
    CString strTitle;
    strTitle << RESOURCESTRINGID(IDS_PAN_FILENAME) << (TCHAR)'\t'
             << _T("File Name") << '\n' << _T('\n');
      //Clear buffer and insert new values
    EmptyString Erase = 0;
    strTitle << Erase << _T("Number ") << 12 << '\n';
 */
inline
CString& operator<<(CString& strDestination, LPCTSTR szSource)
{
strDestination += szSource;
return strDestination;
}

inline
CString& operator<<(CString& strDestination, LPTSTR szSource)
{
strDestination += szSource;
return strDestination;
}

//operator<<()-----------------------------------------------------------------
/*Inserts a Windows string resource to a CString object.
 */
inline
CString& AFXAPI operator<<(CString& strDestination, RESOURCESTRINGID& rcstrSource)
{
ASSERT ((int)rcstrSource != 0);
CString strTemp;
VERIFY (strTemp.LoadString((UINT)rcstrSource));
strDestination += strTemp;
return strDestination;
}

//operator>>()-----------------------------------------------------------------
/*Inserts a string to a CString object.
 */
inline
CString& AFXAPI operator>>(CString& strSource, CString& strDestination)
{
strDestination += strSource;
return strDestination;
}

//operator<<()-----------------------------------------------------------------
/*Inserts an integer to a CString object.
 */
inline
CString& AFXAPI operator<<(CString& strDestination, int iSource)
{
const NOOFDIGITS = 17;
TCHAR szTemp[NOOFDIGITS];
return strDestination << _itot(iSource,szTemp,10);
}

//operator<<()-----------------------------------------------------------------
#if !defined _MBCS && !defined _UNICODE
  /*Inserts a floating-point number to a CString object.

    Note: MSDN KB119504: Result Differs Between 16-bit and 32-bit _gcvt()
    (rounding differs).

  TODO: Test Unicode D.K.
  TODO: replace MFC D.K.
  */
  inline
  CString& AFXAPI operator<<(CString& strDestination, double dSource)
  {
  const NOOFDIGITS = 25;
  TCHAR szTemp[NOOFDIGITS];
  #if defined _MSC_VER || defined __OS400_TGTVRM__
    //Microsoft C/C++ C Run-Time (CRT),
    //IBM ILE C++ for AS/400
    //supports char *_gcvt(double value, int digits,char *buffer);
    #if !defined _MBCS && !defined _UNICODE
      return strDestination << _gcvt(dSource,NOOFDIGITS-1,szTemp);
    #endif
  #endif
  }

  inline
  CString& AFXAPI operator<<(CString& strDestination, float fSource)
  {
  return strDestination << (double)fSource;
  }
#else
  #ifdef _DEBUG
    #include "KDbgMacr.h" //Dump compiler's environment
  #endif
#endif

//operator<<()-----------------------------------------------------------------
/*Inserts a character to a CString object. Throws the memory exceptions in case
  of insufficient memory space.

  TODO: replace MFC D.K.
 */
inline
CString& operator<<(CString& strDestination, TCHAR chSource)
{
strDestination += chSource;
return strDestination;
}

//operator<<()-----------------------------------------------------------------
/*Makes this CString object an empty string and frees memory as appropriate.

  Example:
    CString strBuffer("abcd");
      //Clear buffer and insert new values
    EmptyString Erase;
    strBuffer << Erase << _T("new value") << '\n';

      TODO: replace MFC D.K.
 */
inline
CString& operator<<(CString& strDestination, EmptyString )
{
strDestination.Empty();
return strDestination;
}
  #endif

///////////////////////////////////////////////////////////////////////////////
#endif //_USE_MFC

//////////////////////////////////////////////////////////////////////////////
#endif  //_KSTRINGEXT_H_
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         18/08/2001 2:47:04 PMDarko
 * $
 *****************************************************************************/
