/*$Workfile: KStrBtoH.cpp$: implementation file
  $Revision: 1$ $Date: 8/13/02 6:53:10 PM$
  $Author: Darko Kolakovic$

  Converts a character to descriptive string
  Jun 1990 Darko Kolakovic
*/

/* Group=Strings                                                             */

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#include "KTypedef.h"
#include "KTChar.h"

#ifdef _DEBUG
  static char THIS_FILE[] = __FILE__;
  #include "KTrace.h"
#endif


//ByteToHex()------------------------------------------------------------------
/*Converts a byte to a hexadecimal string. 
 
  Note:  Required size of the buffer is 3 characters or more.

  Returns: szResult containing hexadecimal representation of a byte value.
 */
TCHAR* ByteToHex(BYTE cValue, //[in] value of a byte to convert [0, 255]
                 TCHAR* szResult //[out] zero-terminated string
                             //containing hexadecimal representation of 
                             //a byte value.
                             )
{
ASSERT(szResult != NULL);

int iHiNibble = cValue >> 4;
int iLoNibble  = cValue & 0x0F;

szResult[0] = (iHiNibble > 9) ? 
                  (_T('A') + iHiNibble - 10) : (_T('0') + iHiNibble);
szResult[1] = (iLoNibble > 9) ? 
                  (_T('A') + iLoNibble - 10) : (_T('0') + iLoNibble);
szResult[2] = '\0';

return szResult;
}

///////////////////////////////////////////////////////////////////////////////

