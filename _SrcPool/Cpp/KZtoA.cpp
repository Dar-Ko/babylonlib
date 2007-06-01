/*$Workfile: S:\_SrcPool\Cpp\KZtoA.cpp$: implementation file
  $Revision: 1$ $Date: 2007-06-01 17:34:07$
  $Author: Darko Kolakovic$

  Converts a complex number to the string.
  Copyright: CommonSoft Inc.
  2007-06-01 Darko Kolakovic
*/

/* Group=Strings                                                             */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

/*Replaces library header file names with the compiler's aliases*/
#ifdef _USE_STD_HEADERS
  #ifdef _WIN32
    #ifdef _MSC_VER //Microsoft C++ compiler
      #ifdef _UNICODE
        #ifndef UNICODE
          //To enable Unicode for some Microsoft Visual C/C++ header files,
          //the UNICODE definition is required
          #define UNICODE
        #endif
      #endif
      #pragma include_alias("KTChar.h", "wtypes.h")
      #if _MSC_VER < 1300
        #pragma include_alias("KTrace.h", "trace.h")
      #endif
    #endif  //_MSC_VER
  #endif  //_WIN32

#endif  //_USE_STD_HEADERS

#include "KTrace.h" /*ASSERT macro */
#include "KTChar.h" /*LPCTSTR typedef*/
extern "C" LPTSTR DtoA(double dValue, LPTSTR szResult, unsigned int iSize);

const int ZBUFFSIZEMIN = 6; /*Minimal number of characters for the
                formatted complex number includes terminating zero: '1 + j\0'*/

/*---------------------------------------------------------------------------*/

/*Converts a complex number values to a zero-terminated string.
  The output have following format:
      (-)x +/- iy

  The supplied buffer should be large enough to accommodate the converted value,
  including decimal points,sign and exponent information and a terminating null
  character, which is appended automatically.

  Returns: a pointer to zero-terminated string. There is no error return.

  See also: ostream::operator<<(std::ostream<E, T>& os,const std::complex<U>& x)
 */
LPTSTR ZtoA(double dReal,  //[in] real part of a complex number
            double dImag,  //[in] imaginary part of a complex number
            LPTSTR szResult,  //[in] pointer to string buffer
            unsigned int iSize //[in] size of the resulting buffer in characters
           )
{
if ((szResult != NULL) && (iSize > ZBUFFSIZEMIN))
  {
  if ((dReal == 0.0) && (dImag == 0.0))
    {
    szResult[0] = _T('0');
    szResult[1] = _T('\0');
    }
  else
    {  
    int iBuffSize = (iSize - ZBUFFSIZEMIN)/2;
    DtoA(dReal, szResult, iBuffSize); //Format real part
    //Find the end of the string
    int i = 0;
    while (szResult[i] != _T('\0'))
      {
      i++;
      }
    ASSERT(iSize > (unsigned int)i);
    //Append space and i
    szResult[i++] = _T(' ');
    if (dImag < 0.0)
      {
      dImag = - dImag; //Get absolute value
      szResult[i++] = _T('-'); //Append the sign
      }
    else
      szResult[i++] = _T('+');

    szResult[i++] = _T(' ');
    szResult[i++] = _T('i');
    if (dReal == dImag)
      {
      //Copy already formatted value
      iBuffSize = (szResult[iBuffSize] == _T('-')) ? 1 : 0;
      while (szResult[iBuffSize] != _T(' '))
        {
        szResult[i++] = szResult[iBuffSize++];
        }
      szResult[i] = _T('\0');
      }
    else  //Format imaginary value (sign is not considered)
      DtoA(dImag, &szResult[i], iSize - i);
    }
  }
return szResult;
}

/* ///////////////////////////////////////////////////////////////////////// */
/******************************************************************************
 *$Log: 
 * 1    Biblioteka1.0         2007-06-01 17:34:07  Darko Kolakovic 
 *$
 *****************************************************************************/
