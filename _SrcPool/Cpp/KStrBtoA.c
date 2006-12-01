/*$Workfile: KStrBtoA.c$: implementation file
  $Revision: 8$ $Date: 2005-06-21 11:11:38$
  $Author: Darko Kolakovic$

  Converts a range of bits to a binary string
  Apr. 95 Darko Kolakovic
*/

/* Group=Strings                                                             */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#include "KTChar.h"  /*_tcschr()*/

#ifdef _DEBUG
  static char THIS_FILE[] = __FILE__;
#endif

#ifndef DWORD
  #include "KTypedef.h"
#endif

/*BintoA()---------------------------------------------------------------------*/
/*Convert a range of bits to a binary string. Presentation of the binary values is
  specified with parameters iTrueChar and iFalseChar. Range limit is 32 bits
  (size of double word).
  Returns resulting string as a pointer to  to a caller-supplied
  buffer. Function does not test buffer overflow.

  Example:
      #include <StdIO.h>
      #include "KStrings.h"
      #define STRING_SIZE 16
      void main ()
        {
        char buffer[STRING_SIZE + 1];
        WORD wTest = 0x0A0A;
        printf ( "Convert a word 0x0A0A into binary string: %s\n",
                  BintoA(buffer, (DWORD)wTest, STRING_SIZE, 0, 'H', 'L' ));
        }

  See also: KStrings.h
*/
TCHAR* BintoA(TCHAR* szResult,/*string result         */
             DWORD dwValue,   /*number to be converted*/
             int   iMsBit,    /*most significant bit + 1 to be converted [1,32]*/
             int   iLsBit,    /*less significant bit to be converted [0,31]*/
             TCHAR iTrueChar, /*symbol for TRUE value */
             TCHAR iFalseChar /*symbol for FALSE value*/
             )
{
TCHAR* lpszRes = szResult;  /*Start position */
DWORD  dwBitMask;      /*Selection mask */
DWORD  dwFirstBit;     /*Start position */
DWORD  dwLastBit;     /*End position   */

*szResult = _T('\0');                        /*Erase string      */
dwFirstBit = (DWORD) 0x01 << (iMsBit - 1);   /*Set start position*/
dwLastBit  = (DWORD) 0x01 << iLsBit;         /*Set end position  */
dwBitMask = dwFirstBit;
while(dwBitMask >= dwLastBit)
  {
  *szResult++ = (TCHAR)((dwValue & dwBitMask) ? iTrueChar : iFalseChar);
  dwBitMask >>= 1;
  }

*szResult = _T('\0');    /*Terminate string*/
return lpszRes;          /*Result          */
}

/* ///////////////////////////////////////////////////////////////////////// */
/*****************************************************************************
 * $Log:
 *  7    Biblioteka1.6         14/08/2003 5:01:38 AMDarko           KTypedef.h
 *  6    Biblioteka1.5         19/08/2002 10:42:05 AMDarko Kolakovic
 *  5    Biblioteka1.4         12/02/2002 5:39:03 PMDarko           Replaced
 *       tchar.h with KTChar.h
 *  4    Biblioteka1.3         19/08/2001 11:55:00 PMDarko           Butyfier
 *  3    Biblioteka1.2         11/07/2001 10:52:36 PMDarko
 *  2    Biblioteka1.1         08/06/2001 11:51:45 PMDarko           VSS
 *  1    Biblioteka1.0         13/08/2000 3:59:17 PMDarko
 * $
 *****************************************************************************/
