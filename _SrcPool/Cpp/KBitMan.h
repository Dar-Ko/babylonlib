/*$Workfile: KBitMan.h$: header file
  $Revision: 8$ $Date: 2005-05-12 17:34:53$
  $Author: Darko Kolakovic$

  Manipulation with bits.
  Jun 88 Darko Kolakovic
  Jan 98 inlines and cpp D.K.
 */

#ifndef _KBITMAN_H_
    /*$Workfile: KBitMan.h$ sentry */
  #define _KBITMAN_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

/*///////////////////////////////////////////////////////////////////////////*/
/*Macros                                                                     */

/*RESET_NBITSL()-------------------------------------------------------------*/

/*Set n left of position p bits to zero.
 */
#define RESET_NBITSL( x, p, n)             \
     (                                     \
      x & ~((~0 << p) ^ ( ~0 << (p + n)) ) \
     )

/*EXT_NBITSL()---------------------------------------------------------------*/

/*Extract n bits left of position p.
  ~(~0<<n) creates a mask with ones, and mask is moved left p times.
  Note: sum of n and p must not exceed the number of bits in value x.

  Example: n=2, p=3, x=1001 1111 result: x=0001 1000
 */
#define EXT_NBITSL( x, p, n)       \
     (                             \
      x & (~(~0 << n) << p)        \
     )

/*CPY_NBITS()----------------------------------------------------------------*/
/*Copy n bits left from position xoff in x to y on position yoff.
 */
#define CPY_NBITS( y, yoff, x, xoff, n)                                      \
    (                                                                        \
     ((yoff-xoff) > 0) ?                                                     \
      RESET_NBITSL( y, yoff, n) | (EXT_NBITSL ( x, xoff ,n) << (yoff-xoff)): \
      RESET_NBITSL( y, yoff, n) | (EXT_NBITSL ( x, xoff ,n) >> (xoff-yoff))  \
    )


/*---------------------------------------------------------------------------*/
/*Gets a flag value from any continuous chunk of data x.
  Returns 1 if a flag is set, otherwise returns 0.

  Example:
        p % 8  <-        p & 7   counter [0, 7]
    8- (p % 8)  <=  7 - (p & 7)  counter [7, 0]

    GUID x = {0x04030201, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    //x = b0000 0100 0000 0011 0000 0010 0000 0001 0000 ...
    p = sizeof(x) * CHAR_BIT;
    while(--p >= 0)
      {
      nResult = GET_FLAG((GUID)nTestData, p);
      std::_tcout << nResult;
      if ((p % 4) == 0)
        std::_tcout << _T(" ");
      }
    std::_tcout << std::endl;

    Output:
      Little endian architecture
      0000 ... 0010 0000 1100 0000 0100 0000 1000 0000
 */
#define GET_FLAG(x, p)                                            \
    (                                                             \
       ( ((const int8_t*)&(x))[(p) >> 3] & 0x80 >> ((p) & 7) ) >> \
       (7 - ((p) & 7) )                                           \
    )

/*---------------------------------------------------------------------------*/
/*Calculate parity of all bits of value 1. Result is stord in the input
  value.
  Return 1 if the total number of bits of value 1 is odd or 0 if it is even.
 */
#define PARITY(x)                               \
    {                                           \
    uint32 nTmp = (uint32_t)x;                    \
    nTmp ^= nTmp >> 1;                          \
    nTmp ^= nTmp >> 2;                          \
    nTmp = (nTmp & 0x11111111U) * 0x11111111U;  \
    x = (nTmp >> (sizeof(nTmp) - 4)) & 1;       \
    }

/*Calculate parity of 64-bit long data. Result is stored in the input value.
  Return 1 if the total number of bits of value 1 is odd or 0 if it is even.
 */
#define PARITY64(x)                             \
    {                                           \
    uint64 nTmp = (uint64_t)x;                    \
    nTmp ^= nTmp >> 1;                          \
    nTmp ^= nTmp >> 2;                          \
    nTmp = (nTmp & 0x1111111111111111UL) * 0x1111111111111111UL;  \
    x = (nTmp >> (sizeof(nTmp) - 4)) & 1;       \
    }

#ifdef __cplusplus
///////////////////////////////////////////////////////////////////////////////
//Inlines

#ifdef _MSC_VER
  #pragma warning( disable : 4244 )//Warning :conversion from 'int' to 'uint8_t'
#endif

//SetNbitsR()-----------------------------------------------------------------
/*Set n right bits of position p to TRUE (one); n must be smaller than p + 1.

  Example:
    x = 0;
    p = 6;
    n = 3;
     7 6 5 4   3 2 1 0   <-bits
     1 1 1 1   1 1 1 1   <- ~0

     1 1 1 1   0 0 0 0   <- (~0 << (p + 1 - n))
     1 0 0 0   0 0 0 0   <- (~0 << (p + 1))
     0 1 1 1   0 0 0 0   <- ()^() :Mask
     x x x x   x x x x   <- x
     x 1 1 1   x x x x   <- x | Mask
    n bits right of p are set to one
*/
inline unsigned int& SetNbitsR(unsigned int& x,//[in, out] the field of bits to be set
                      uint8_t p, //[in] the start position of the area to set
                      uint8_t n  //[in] the number of bits to set
                     )
  {
  x = x | (( ~0 << (p + 1) ) ^ ( ~0 << (p + 1 - n)));
  return x;
  }

//ResetNbitsL()----------------------------------------------------------------
/*Set n left bits to zero from position p;

  Example:
    x = 255;
    p = 4;
    n = 3;

     7 6 5 4   3 2 1 0   <-bits
     1 1 1 1   1 1 1 1   <- ~0

     1 0 0 0   0 0 0 0   <- (~0 << (p + n))
     1 1 1 1   0 0 0 0   <- (~0 << p)
     1 0 0 0   1 1 1 1   <- ~(()^()) :Mask
     x x x x   x x x x   <- x
     x 0 0 0   x x x x   <- x & Mask
    n bits left from p are set to zero
*/
inline unsigned int& ResetNbitsL(unsigned int& x,//[in, out] the field of bits
                                                 //to be reset
                         uint8_t p, //[in] the start position of the area to reset
                         uint8_t n  //[in] the number of bits to reset
                         )
  {
  x = RESET_NBITSL( x, p, n);
  return x;
  }

//GetNbitsR()------------------------------------------------------------------
/*Get n bits right of position p.

  Example:
  x>>(p+1-n) moves the desired field of three bits to the right end of the
  word. Unsigned arguments ensures that when it is rightshifted, vacated bits
  will be filled with zeroes, regardless of the machine. ~(~0<<n) creates a
  mask with ones in the rightmost three (n=3) bits. n must be smaller or
  equal to p + 1.

  Following example returns 6-th,5-th,4-th bit, right adjusted:

    x = 156;
    p = 6;
    n = 3;
      7 6 5 4   3 2 1 0   <-bits
      1 1 1 1   1 1 1 1   <- ~0
     #
      1 1 1 1   1 0 0 0   <- (~0 << n)
      0 0 0 0   0 1 1 1   <- ~(~0 << n) :Mask
      h g f e   d c b a   <- x
      0 0 0 0    h g f e   <- x >> (p + 1 - n)
      0 0 0 0    0 g f e   <- x & Mask
    result is n bits right from p
*/
inline unsigned int GetNbitsR(unsigned int x, //[in] the source field of bits
                      uint8_t p, //[in] the start position of the area to retrieve
                      uint8_t n  //[in] the number of bits to retrieve
                      )
  {
  x = x >> (p + 1 - n) & ~(~0 << n);
  return x;
  }

//GetNBitsL()------------------------------------------------------------------
/*Get n bits left of position p. Desired bits are right adjusted.
  Note: sum of n and p must not exceed the number of bits in value x.

  Example:
     x>>p moves the desired field of bits to the right.
     ~(~0<<n) creates a mask with ones.
     If p + n is greater than 8, result will be padded
     with zeroes.
     x = 156;
     p = 4;
     n = 3;
        7 6 5 4   3 2 1 0   <-bits
        1 1 1 1   1 1 1 1   <- ~0

     1 1 1 1   1 0 0 0   <- (~0 << n)
     0 0 0 0   0 1 1 1   <- ~(~0 << n) :Mask
     h g f e   d c b a   <- x
     0 0 0 0   h g f e   <- x >> p
     0 0 0 0   0 g f e   <- x & Mask
     result is n bits right from p
*/
inline unsigned int GetNBitsL(unsigned int x, //[in] the source field of bits
                      unsigned int p, //[in] the start position of the area to retrieve
                      unsigned int n  //[in] the number of bits to retrieve
                      )
  {
  #ifdef _DEBUG
    #ifndef CHAR_BIT
      const T CHAR_BIT = 8; //Number of bits in a byte
    #endif
    ASSERT((p+n) <= (CHAR_BIT * sizeof(x)));
  #endif

  x = x >> p & ~(~0 << n);
  return x;
  }

//ExtNbitsL()------------------------------------------------------------------
/*Extract n bits left of position p.

  Example:
    x = 156;
    p = 4;
    n = 3;
    ~(~0<<n) creates a mask with ones, and mask is moved left p times.

     7 6 5 4   3 2 1 0   <-bits
     1 1 1 1   1 1 1 1   <- ~0
    #
     1 1 1 1   1 0 0 0   <- (~0 << n)
     0 0 0 0   0 1 1 1   <- ~(~0 << n)
     0 1 1 1   0 0 0 0   <- ~(~0 << n) << p
     h g f e   d c b a   <- x
     0 g f e   0 0 0 0   <- x & Mask
    result is n bits right from p
*/
inline unsigned int ExtNbitsL(unsigned int x, //[in] the source field of bits
                      uint8_t p, //[in] the start position of the area to retrieve
                      uint8_t n  //[in] the number of bits to retrieve
                      )
  {
  x = EXT_NBITSL( x, p, n);
  return x;
  }

//CpyNbitsL()------------------------------------------------------------------
/*Copy n bits from source x left of position p to target y.

  Example:
    ~(~0<<n) creates a mask with ones, and mask is moved left p times.
    x = 156;
    y = 45;
    p = 4;
    n = 3;
     7 6 5 4   3 2 1 0   <-bits
     1 1 1 1   1 1 1 1   <- ~0
     Extract n bits
     1 1 1 1   1 0 0 0   <- (~0 << n)
     0 0 0 0   0 1 1 1   <- ~(~0 << n)
     0 1 1 1   0 0 0 0   <- ~(~0 << n) << p
     x x x x   x x x x   <- x
     0 x x x   0 0 0 0   <- x & Mask
     Reset n bits
     1 0 0 0   0 0 0 0   <- (~0 << (p + n))
     1 1 1 1   0 0 0 0   <- (~0 << p)
     1 0 0 0   1 1 1 1   <- ~(()^()) :Mask
     y y y y   y y y y   <- y
     y 0 0 0   y y y y   <- y & Mask

     y x x x   y y y y   <- y | x
    result is n bits right from p
*/
inline unsigned int& CpyNbitsL(unsigned int& y,//[out] the result
                               uint8_t x, //[in] the source field of bits
                               uint8_t p, //[in] the start position of the area
                                          //to retrieve
                               uint8_t n  //[in] the number of bits to retrieve
                       )
  {
  x =  ExtNbitsL(x,p,n);
  ResetNbitsL(y,p,n);
  y = y | x;
  return y;
  }
#pragma warning( default : 4244 )//Warning :conversion from 'int' to 'uint8_t'

//GetFlag()--------------------------------------------------------------------
/*Gets a flag value.
  Returns true if a flag is set, otherwise false

  Parameter:
    - TYPE the basic type of the value to be examined.

  Example:
    #include "KBitMan.h"
    ...
  uint32 nValue     = 0x1111000;
  uint32 nMaskTrue  = 0x0011000;
  uint32 nMaskFalse = 0x0001100;

  bool bRes = GetFlag(nValue, nMaskTrue);  //check if flags are up
  bRes = !GetFlag(nValue, nMaskFalse);      //check if one flag is down
 */
template <class TYPE>
inline bool GetFlag(const TYPE& iStatus, //[in] bit array to be examined
                    const TYPE&  uFlag   //[in] bit mask
                    )
   {
   return ((iStatus & uFlag) == uFlag);
   };

//EnableFlag()-----------------------------------------------------------------
/*Returns status after a flags are set.

  Parameter:
    - TYPE the basic type of the value to be manipulated.
 */
template <class TYPE>
inline TYPE EnableFlag(TYPE& iStatus,     //[in] bit array
                       const TYPE& uFlags //[in] bit mask
                       )
   {
   return(iStatus = iStatus | uFlags);
   };

//DisableFlag()----------------------------------------------------------------
/*Returns status after a flags are cleared

  Parameter:
    - TYPE the basic type of the value to be manipulated.
 */
template <class TYPE>
inline TYPE DisableFlag(TYPE& iStatus,     //[in] bit array
                        const TYPE& uFlags //[in] bit mask
                        )
  {
  #ifdef _DEBUG
    //Note: This allows to set breakpoint on the intermediate result. D.K.
    TYPE i = iStatus & ~uFlags;
    iStatus = i;
    return iStatus;
  #else
    return(iStatus = iStatus & ~uFlags);
  #endif
  };

//SetNthBit()------------------------------------------------------------------
/*Set bit on position nPos to 1

  Parameter:
    - T the basic type of the value to be manipulated.
 */
template <class T> T SetNthBit (T& Status,               //[in] bit array
                                const unsigned int& nPos //[in]
                                )
  {
  return (Status | 1 << nPos);
  }

//ResetNthBit()----------------------------------------------------------------
/*Set bit on position nPos to 0

  Parameter:
    - T the basic type of the value to be manipulated.
 */
template <class T> T ResetNthBit (T& Status,               //[in] bit array
                                  const unsigned int& nPos //[in]
                                  )
  {
  return (Status & ~(1 << nPos));
  }

//-----------------------------------------------------------------------------
/*Reverse order of bits in the given value.

  Returns the value with the individual bits ordered in oposite way.

  Parameter:
    - T the basic type of the value to be reversed.

  Example:
    #include "KBitMan.h"
    ...
    uint32 nResult = ReverseBits<uint32>(0xD2E30021);
 */
template <typename T> T ReverseBits (T value //[in] bits to be reversed
                                     )
  {
  #ifndef CHAR_BIT
    const T CHAR_BIT = 8; //Number of bits in a byte
  #endif

  T result = 0;
  int iCount = CHAR_BIT * sizeof(value);
  while(value > 0) //Reverse bits until only 0 are left
    {
    result = (result << 1) | (value & 1);
    value >>= 1;
    --iCount;
    }
  result <<= iCount; //Shift remaining bits
  return result;
  }

///////////////////////////////////////////////////////////////////////////////
#endif /*__cplusplus                                                         */

/*///////////////////////////////////////////////////////////////////////////*/
#endif /*_KBITMAN_H_                                                         */
/*****************************************************************************
 * $Log:
 *  6    Biblioteka1.5         2003-09-30 10:15:56  Darko           formatting
 *  5    Biblioteka1.4         2002-01-25 16:56:07  Darko           Updated
 *       comments
 *  4    Biblioteka1.3         2001-08-19 23:51:30  Darko           Butyfier
 *  3    Biblioteka1.2         2001-07-11 22:50:12  Darko
 *  2    Biblioteka1.1         2001-06-08 23:49:08  Darko           VSS
 *  1    Biblioteka1.0         2000-08-13 15:55:31  Darko
 * $
 *****************************************************************************/
