/*$Workfile: KStrBtoH.cpp$: implementation file
  $Revision: 4$ $Date: 2004-06-01 16:52:59$
  $Author: Darko$

  Converts a character to descriptive string
  Jun 1990 Darko Kolakovic
*/

/* Group=Strings                                                             */

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

#include "KTypedef.h"
#include "KTChar.h"


#ifdef _DEBUG
  static char THIS_FILE[] = __FILE__;
  #include "KTrace.h"
#endif

#ifdef _MSC_VER //Microsoft C/C++ compiler
  #pragma warning( push, 3 )
    //warning C4127: conditional expression is constant
  #pragma warning(disable: 4217)

  #ifndef _DEBUG
    #ifndef ASSERT
      #if _MSC_VER > 1200
        #define ASSERT __noop
      #else
        #define ASSERT (void(0))
      #endif
    #endif
  #endif
#endif

//ByteToHex()------------------------------------------------------------------
/*Converts a byte to a hexadecimal string. 
 
  Note:  Required size of the buffer is 3 characters or more.

  Returns: szResult containing hexadecimal representation of a byte value.

  TODO: test Unicode D.K.
 */
TCHAR* ByteToHex(BYTE cValue, //[in] value of a byte to convert [0, 255]
                 TCHAR* szResult //[out] zero-terminated string
                             //containing hexadecimal representation of 
                             //a byte value.
                             )
{
ASSERT(szResult != NULL);

int iHiNibble = cValue >> 4;
int iLoNibble = cValue & 0x0F;

szResult[0] = (iHiNibble > 9) ? 
                  (_T('A') + iHiNibble - 10) : (_T('0') + iHiNibble);
szResult[1] = (iLoNibble > 9) ? 
                  (_T('A') + iLoNibble - 10) : (_T('0') + iLoNibble);
szResult[2] = '\0';

return szResult;
}

///////////////////////////////////////////////////////////////////////////////
#ifdef _MSC_VER //Microsoft C/C++ compiler
    //warning C4127: conditional expression is constant
  #pragma warning(default: 4217)
  #pragma warning( pop )
#endif

/*****************************************************************************
 * $Log: 
 *  4    Biblioteka1.3         2004-06-01 16:52:59  Darko           time sync
 *  3    Biblioteka1.2         2003-09-02 00:04:13  Darko           fixed release
 *       version
 *  2    Biblioteka1.1         2003-08-25 01:53:30  Darko           VSS tags
 *  1    Biblioteka1.0         2002-08-13 17:53:10  Darko Kolakovic 
 * $
 *  0    Biblioteka0           Darko Kolakovic  May '97
 *****************************************************************************/

