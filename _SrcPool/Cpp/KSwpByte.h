/*$Workfile: KSwpByte.h$: header file
  $Revision: 11$ $Date: 2004-07-07 16:49:26$
  $Author: Darko$

  Flip bytes of built-in types
  Copyright: CommonSoft Inc
  D. Kolakovic   May 2k1
*/

#ifndef _KSWPBYTE_H_
  //$Workfile: KSwpByte.h$ sentry
  #define _KSWPBYTE_H_

#if _MSC_VER > 1000 /*Microsoft Visual Studio C/C++ compiler                 */
  #pragma once
#endif // _MSC_VER > 1000


///////////////////////////////////////////////////////////////////////////////
// Inlines

//SwapByteOrder()--------------------------------------------------------------
/*The class swaps tailing bytes with bytes from the beginning of the 32-bit value.
  Usefull for conversion between little endian and big endian integers.

  Returns: 32-bit integer with swapped bytes.
 */
inline uint32 SwapByteOrder(uint32 dwValue //[in] 32-bit value to convert
                           )
{
return  ((dwValue >> 24) & 0X000000FF) |
  ((dwValue >> 8)  & 0X0000FF00) |
  ((dwValue << 8)  & 0X00FF0000) |
  ((dwValue << 24) & 0XFF000000) ;
}

/*The class swaps tailing bytes with bytes from the beginning of the 16-bit value.
  Usefull for conversion between little endian and big endian short integers.

  Returns: 16-bit integer with swapped bytes.
 */
inline uint16 SwapByteOrder(uint16 wValue //[in] 16-bit value to convert
                            )
{
return  ((wValue >> 8)  & 0x00FF) |
  ((wValue << 8)  & 0xFF00) ;
}

/*The class swaps tailing bytes with bytes from the beginning of the 64-bit value.
  Usefull for conversion between little endian and big endian integers.
  Returns a uint64 with swapped bytes.
 */
inline uint64 SwapByteOrder(uint64 uValue //[in] 64-bit value to convert
                            )
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

inline int64 SwapByteOrder(int64 iValue //[in] 64-bit value to convert
                           )
{
return (int64)SwapByteOrder((UINT64)iValue);
}

///////////////////////////////////////////////////////////////////////////////
#endif // _KSWPBYTE_H_
/******************************************************************************
* $Log:
*  1    Biblioteka1.0         26/07/2001 9:31:33 PMDarko
* $
*****************************************************************************/
