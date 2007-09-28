/*$Workfile: KDtoA.c$: implementation file
  $Revision: 4$ $Date: 2007-06-27 16:45:50$
  $Author: Darko Kolakovic$

  Converts a real number to the string.
  Copyright: CommonSoft Inc.
  Mar 1989 Darko Kolakovic
*/

/* Group=Strings                                                             */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

/*Replaces library header file names with the compiler's aliases*/
#ifdef _USE_STD_HEADERS
  #ifdef _WIN32
    #ifdef _MSC_VER //Micorsoft C++ compiler
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

#ifdef _MSC_VER
  /*Microsoft C Compiler*/
  #include <stdlib.h> /*_gcvt()*/
  #include <float.h>  /*DBL_DIG*/

  #if _MSC_VER < 1300
    /*Microsoft compilers before Visual C++ .Net 2002, 32-bit, version 7.0
      expect the users to have set up their own storage
     */

    #define _CVTBUFSIZE (309+40) /* Number of digits in maximum double precision
                                    value + slop
                                  */
  #endif
#endif

/*DtoA()---------------------------------------------------------------------*/

/*Converts the given floating-point value to a zero-terminated string.
  The supplied buffer should be large enough to accommodate the converted value.
  The value includes a decimal point and possible sign and exponent information,
  plus a terminating null character, which is appended automatically.

  Returns: a pointer to zero-terminated string. There is no error return.
 */
LPTSTR DtoA(double dValue,   /*[in] real number to be converted               */
            LPTSTR szResult, /*[out] pointer to string buffer                 */
            unsigned int iSize /*[in] size of the resulting buffer in
                                 characters
                                */
           )
{
#ifdef _MSC_VER
  /*Microsoft C Compiler*/
  char szTemp[_CVTBUFSIZE];

  #if !defined _MBCS && !defined _UNICODE
    #if _MSC_VER < 1400 /*Before Visual C/C++ 2005, version 8.0*/

    /*Singlebyte-character (SBCS or ASCII) text mapping*/
    if (szResult != NULL)
      {
      unsigned int i = 0;
      _gcvt(dValue,   /*value to be converted              */
            DBL_DIG,  /*number of significant digits stored*/
            szTemp    /*storage location for result        */
            );
      while ((szTemp[i] != '\0') && (i < iSize))
        {
        szResult[i] = szTemp[i];
        i++;
        }
      szResult[i] = '\0';
      }
    #else /*Visual C/C++ 2005, version 8.0*/
    /*Note: If a failure occurs due to an invalid parameter, the invalid
      parameter handler is invoked as described in Parameter Validation and
      function returns EINVAL.
     */
    _gcvt_s(szResult, /*Buffer to store the result of the conversion.*/
            iSize,    /*Size of the buffer.                          */
            dValue,   /*Value to be converted.                       */
            DBL_DIG   /*Number of significant digits stored.         */
            );
    #endif
  #else
    /*Multibyte-character or Unicode (wide-character) text mapping*/

    if (szResult != NULL)
      {
      #if _MSC_VER < 1400 /*Before Visual C/C++ 2005, version 8.0*/
      _gcvt(dValue, /*value to be converted              */
            DBL_DIG,/*number of significant digits stored*/
            szTemp  /*storage location for result        */
            );
      #else /*Visual C/C++ 2005, version 8.0*/
      /*Note: If a failure occurs due to an invalid parameter, the invalid
        parameter handler is invoked as described in Parameter Validation and
        function returns EINVAL
       */
      if (_gcvt_s(szResult, /*Buffer to store the result of the conversion.*/
                  iSize,    /*Size of the buffer.                          */
                  dValue,   /*Value to be converted.                       */
                  DBL_DIG   /*Number of significant digits stored.         */
                  ) != 0)
        return szResult;
      #endif

      /*Convert ANSI string to Unicode*/
    MultiByteToWideChar(CP_ACP,           /*code page is ANSI*/
                        0,                /*character-type options*/
                        szTemp,           /*string to map*/
                        (int)strlen(szTemp)+1, /*number of bytes in string*/
                        (LPWSTR)szResult,         /*wide-character buffer*/
                        iSize             /*size of buffer*/
                        );
    /*Note: If the MultiByteToWideChar() fails, the return value is zero.
      To get extended error information, call GetLastError. GetLastError
      may return one of the following error codes:

            ERROR_INSUFFICIENT_BUFFER
            ERROR_INVALID_FLAGS
            ERROR_INVALID_PARAMETER
            ERROR_NO_UNICODE_TRANSLATION
     */

    }
  #endif

#endif /* _MSC_VER */

return szResult;
}

/* ///////////////////////////////////////////////////////////////////////// */
/******************************************************************************
 *$Log:
 * 3    Biblioteka1.2         8/14/2003 5:00:54 AM Darko           Unicode
 * 2    Biblioteka1.1         7/16/2002 1:41:15 AM Darko           Fixed VSS Log
 *      tag
 * 1    Biblioteka1.0         3/7/2002 5:03:38 PM  Darko
 *$
 *****************************************************************************/
