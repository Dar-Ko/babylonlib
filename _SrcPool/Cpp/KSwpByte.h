/*$Workfile: KSwpByte.h$: header file
  $Revision: 9$ $Date: 8/3/02 7:27:15 PM$
  $Author: Darko$

  Flip bytes of built-in types
  Copyright: CommonSoft Inc
  D. Kolakovic   May 2k1
 */

#ifndef __KSWPBYTE_H__
    //KSwpByte.h sentry
  #define __KSWPBYTE_H__

#if _MSC_VER > 1000 /*Microsoft Visual Studio C/C++ compiler                 */
  #pragma once
#endif // _MSC_VER > 1000


///////////////////////////////////////////////////////////////////////////////
// Inlines

//SwapByteOrder()--------------------------------------------------------------
/*The class swaps tailing bytes with bytes from the beginning of the 32-bit value.
  Usefull for conversion between little endian and big endian integers.
  Returns a DWORD with swapped bytes.
 */
inline DWORD SwapByteOrder(DWORD dwValue)
{
ASSERT(sizeof(DWORD) == 4);
return  ((dwValue >> 24) & 0X000000FF) |
        ((dwValue >> 8)  & 0X0000FF00) |
        ((dwValue << 8)  & 0X00FF0000) |
        ((dwValue << 24) & 0XFF000000) ;
}

/*The class swaps tailing bytes with bytes from the beginning of the 16-bit value.
  Usefull for conversion between little endian and big endian short integers.
  Returns a WORD with swapped bytes.
 */
inline WORD SwapByteOrder(WORD wValue)
{
ASSERT(sizeof(WORD) == 2);
return  ((wValue >> 8)  & 0x00FF) |
        ((wValue << 8)  & 0xFF00) ;
}

/*The class swaps tailing bytes with bytes from the beginning of the 64-bit value.
  Usefull for conversion between little endian and big endian integers.
  Returns a uint64 with swapped bytes.
 */
inline UINT64 SwapByteOrder(UINT64 uValue)
{
#ifdef _MSC_VER /*Microsoft Visual C/C++ compiler */
  return  (  (uValue << 56)                         |
            ((uValue << 40) & 0x00FF000000000000i64) |
            ((uValue << 24) & 0x0000FF0000000000i64) |
            ((uValue <<  8) & 0x000000FF00000000i64) |
            ((uValue >>  8) & 0x00000000FF000000i64) |
            ((uValue >> 24) & 0x0000000000FF0000i64) |
            ((uValue >> 40) & 0x000000000000FF00i64) |
             (uValue >> 56) );
#endif

#ifdef _GNUG_ /*GNU C++ compiler */
  return  (  (uValue << 56)                         |
            ((uValue << 40) & 0x00FF000000000000LL) |
            ((uValue << 24) & 0x0000FF0000000000LL) |
            ((uValue <<  8) & 0x000000FF00000000LL) |
            ((uValue >>  8) & 0x00000000FF000000LL) |
            ((uValue >> 24) & 0x0000000000FF0000LL) |
            ((uValue >> 40) & 0x000000000000FF00LL) |
             (uValue >> 56) );
#endif
}

inline int64 SwapByteOrder(int64 iValue)
{
return (int64)SwapByteOrder((UINT64)iValue);
}

///////////////////////////////////////////////////////////////////////////////
#endif // __KSWPBYTE_H__
/******************************************************************************
 * $Log:
 *  1    Biblioteka1.0         26/07/2001 9:31:33 PMDarko
 * $
 *****************************************************************************/
