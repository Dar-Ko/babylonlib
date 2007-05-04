/*$Workfile: KIntStream.cpp$: implementation file
  $Revision: 9$ $Date: 2007-02-02 11:55:12$
  $Author: Darko Kolakovic$

  Write int64 to the stream
  Copyright: CommonSoft Inc.
  Feb 2002 Darko Kolakovic
*/

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

#ifdef _DEBUG
  #ifndef _STLP_DEBUG
    #define _STLP_DEBUG 1    //Debug STLPort library
  #endif
#else
  #ifdef _STLP_DEBUG
    #undef _STLP_DEBUG
  #endif
#endif

#if _MSC_VER 
  #if defined (_UNICODE)
    //Note: Some Microsoft headers file requires UNICODE macro in order
    //      to resolve character code mapping. Some headers are satisfied
    //      with _UNICODE, which is macro used by the library.
    #ifndef UNICODE
      #define UNICODE
    #endif
  #endif
#endif

#include <valarray> //valarray
#include <ios> //ios_base class
#include "KTchar.h"   //TCHAR typdef
#include "KOStream.h" //ostream template
#include "KTypedef.h"

#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;

  #if _MSC_VER < 1300 /*MS VC/C++ - Disable warning */
    //Fix for the warning(4786) cannot debug code with symbols longer
    //than 255 characters
  #pragma warning (disable: 4786)
  #endif
#endif

tostream& operator<<(tostream& outStream, const  int64 iValue);
tostream& operator<<(tostream& outStream, const uint64 nValue);
tostream& operator<<(tostream& outStream, const std::valarray<double>& vArray);

//-----------------------------------------------------------------------------
/*Writes the value to output stream.

  Note: uses Standard Template Library (STL).
 */
tostream& operator<<(tostream& outStream, //[out] output stream
                     const int64 iValue   //[in] value to write
                     )
{
const std::ios_base::fmtflags fmtFlags = outStream.flags();
//D.K. 20030923 replaced stream_type with ios_base (MSVC 7.1 STL)
int iRadix;
TCHAR szOut[70];
LPTSTR pHead = szOut;

if (fmtFlags & std::ios_base::oct)
  {
  szOut[0] = _T('0');
  iRadix = 8;
  pHead = &szOut[1];
  }
else if (fmtFlags & std::ios_base::hex)
  {
  szOut[0] = _T('0');
  szOut[0] = _T('x');
  iRadix = 16;
  pHead = &szOut[2];
  }
else
  {
  iRadix = 10;
  if (fmtFlags & std::ios_base::showpos)
    {
    szOut[0] = _T('+');
    pHead = &szOut[1];
    }
  }

_i64tot(iValue, pHead, iRadix);
return (outStream << szOut);
}

//-----------------------------------------------------------------------------
/*Writes the value to output stream.

  Note: uses Standard Template Library (STL).
 */
tostream& operator<<(tostream& outStream, //[out] output stream
                     const uint64 nValue  //[in] value to write
                     )
{
const std::ios_base::fmtflags fmtFlags = outStream.flags();
int iRadix;
TCHAR szOut[70];
LPTSTR pHead = szOut;

if (fmtFlags & std::ios_base::oct)
  {
  szOut[0] = _T('0');
  iRadix = 8;
  pHead = &szOut[1];
  }
else if (fmtFlags & std::ios_base::hex)
  {
  szOut[0] = _T('0');
  szOut[0] = _T('x');
  iRadix = 16;
  pHead = &szOut[2];
  }
else
  {
  iRadix = 10;
  if (fmtFlags & std::ios_base::showpos)
    {
    szOut[0] = _T('+');
    pHead = &szOut[1];
    }
  }

_ui64tot(nValue, pHead, iRadix);
return (outStream << szOut);
}

//-----------------------------------------------------------------------------
/*Writes the valarray<double> array elements to output stream. Elements are
  delimited with TAB '\t' character.
 */
tostream& operator<<(tostream& outStream, //[out] output stream
                     const std::valarray<double>& vArray //[in] array to write
                    )
{
for (unsigned iPos = 0; iPos < vArray.size() - 1; ++iPos)
  outStream << vArray[iPos] << _T('\t');
outStream << vArray[iPos]; //Output the last element
return outStream;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  3    Biblioteka1.2         2003-09-30 09:10:43  Darko           ostream <<
 *       tbool
 *  2    Biblioteka1.1         2003-09-22 22:26:18  Darko           formatting
 *  1    Biblioteka1.0         2003-09-22 21:25:17  Darko
 * $
 *****************************************************************************/
