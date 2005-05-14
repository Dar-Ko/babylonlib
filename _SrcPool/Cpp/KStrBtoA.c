/*$Workfile: KStrBtoA.c$: implementation file
  $Revision: 7$ $Date: 8/14/2003 5:01:38 AM$
  $Author: Darko$

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
 *  7    Biblioteka1.6         8/14/2003 5:01:38 AM Darko           KTypedef.h
 *  6    Biblioteka1.5         8/19/2002 10:42:05 AMDarko Kolakovic 
 *  5    Biblioteka1.4         2/12/2002 5:39:03 PM Darko           Replaced
 *       tchar.h with KTChar.h
 *  4    Biblioteka1.3         8/19/2001 11:55:00 PMDarko           Butyfier
 *  3    Biblioteka1.2         7/11/2001 10:52:36 PMDarko           
 *  2    Biblioteka1.1         6/8/2001 11:51:45 PM Darko           VSS
 *  1    Biblioteka1.0         8/13/2000 3:59:17 PM Darko           
 * $
 *****************************************************************************/
