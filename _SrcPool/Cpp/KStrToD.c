/*$Workfile: KStrToD.c$: implementation file
  $Revision: 5$ $Date: 2005-06-21 10:11:59$
  $Author: Darko Kolakovic$

  Converts a string to the real number
  Copyright: CommonSoft Inc.
  Mar 1989 Darko Kolakovic
*/

/* Group=Strings                                                             */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#include <math.h> /*pow() */
#ifndef bool
  #include "KTypedef.h"
#endif
#include "KTChar.h"  /*TCHAR*/
//#include "KProgCst.h" /*NaN_NUMBER*/
#include "KProgCst.inl" /*NaN_NUMBER*/
#ifdef _DEBUG
  static char THIS_FILE[] = __FILE__;
#endif

#ifdef _M_IX86    /*Intel x86 CPU */
  #ifndef CST_dNaN
      /*double quiet NaN (not a number) -1.#IND according to IEC 559         */
    static const NaN_NUMBER CST_dNaN  = {0x0,NaN_DQUIET};
  #endif
#else /*~Intel x86 CPU */
  #error 'TODO: not tested with other CPU D.K.'
#endif

#ifdef _WIN32
  #ifdef _UNICODE
    #define _CH2INT_ wint_t
  #else
    #define _CH2INT_ int
  #endif
#else
  #define _CH2INT_ int
#endif

/*StrToD()-------------------------------------------------------------------*/
/*The function converts given string to floating-point.
  String has to be in following format:

      SD.ESDD
      where    S is optional sign + or -
               D    digits [0,9]
               .    optional decimal point
               E    optional exponential tag e or E

  Example:
      //Valid formats
      LPCTSR szRealNumber1 = _T("   11");
      LPCTSR szRealNumber2 = _T("  +11.");
      LPCTSR szRealNumber3 = _T("  -11.2");
      LPCTSR szRealNumber4 = _T("     .2");
      LPCTSR szRealNumber5 = _T("   11e3");
      LPCTSR szRealNumber6 = _T("  +11.E+3");
      LPCTSR szRealNumber7 = _T("  -11.2E-3");
      LPCTSR szRealNumber8 = _T("     .2e3");

  This function ignores leading white space characters and does not validate
  overflow or underflow cases.

  Returns: real number or quiet NaN (not a number) in case of error. If ppTail
  is not NULL, the pointer to the first character after parsed number is also
  returnded.

  See also: {html:<a href="http://stevehollasch.com/cgindex/coding/ieeefloat.html">
  IEEE Standard 754 </a>}
 */
double StrToD(LPCTSTR pSource,     /*[in] pointer to string representing real
                                          number*/
              const TCHAR** ppTail /*[out] pointer to the first character after
                                           parsed number*/
              )
{
double dResult = NaN_DVALUE(CST_dNaN); /*default result*/
bool bNegative = false;                /*sign flag*/
unsigned long lInteger = 0;            /*integer part*/
unsigned long lFraction = 0;           /*fractional part*/
LPTSTR pHead = (LPTSTR)pSource;

  /*Trim leading white space */
while (_istspace(*pHead))
  {
  pHead++;
  }

  /*Get optional sign*/
if (*pHead == _T('+'))
  pHead++;
if (*pHead == _T('-'))
  {
  bNegative = true;
  pHead++;
  }

if ((*pHead == _T('.')) || (_istdigit ((_CH2INT_)(*pHead))) ) /*Validate format*/
  {
    /*Parse integer part*/
  while (_istdigit((_CH2INT_)*pHead))
    {
    lInteger *= 10;
    lInteger += (long)(*pHead - _T('0'));
    pHead++;
    }
  dResult = (double)lInteger;

    /*Parse fractional part*/
  if (*pHead == _T('.'))
    {
    unsigned long lDivisor  = 1;
    pHead++;
    while (isdigit((_CH2INT_)*pHead))
      {
      lFraction *= 10;
      lFraction += (*pHead - _T('0'));
      lDivisor *= 10;
      pHead++;
      }
    if (lFraction > 0)
      {
      dResult += (double)lFraction / (double)lDivisor;
      }
    else
      if (lInteger == 0)
        {
          /*Both integer and fraction are zero*/
        if (ppTail != NULL)
          *ppTail = pHead; /*Return pointer to the first character
                            after parsed number*/
        return dResult; /*Return 0.0*/
        }
    }

  if (bNegative)
    dResult = -dResult;

    /*Parse exponential part*/
  if ((*pHead == _T('e')) || (*pHead == _T('E')))
    {
    pHead++;
      /*Get optional sign of the exponent*/
    bNegative = false;
    if (*pHead == _T('+'))
      pHead++;
    if (*pHead == _T('-'))
      {
      bNegative = true;
      pHead++;
      }

    lInteger = 0;
    while (_istdigit((_CH2INT_)*pHead))
      {
      lInteger *= 10;
      lInteger += (*pHead - _T('0'));
      pHead++;
      }

    if (lInteger > 0)
      {
      if (bNegative)
        dResult /= pow((double)10, (double)lInteger);
      else
        dResult *= pow((double)10, (double)lInteger);
      }
    }
  }

if (ppTail != NULL)
  *ppTail = pHead;/*Return pointer to the first character after parsed number*/

return dResult;
}
/* ///////////////////////////////////////////////////////////////////////// */
/*****************************************************************************
 * $Log:
 *  3    Biblioteka1.2         2004-06-01 17:53:39  Darko           time sync
 *  2    Biblioteka1.1         2003-09-22 22:26:53  Darko           formatting
 *  1    Biblioteka1.0         2003-09-22 22:22:23  Darko
 * $
 *  0 1989-03   Darko Kolakovic
 *****************************************************************************/
