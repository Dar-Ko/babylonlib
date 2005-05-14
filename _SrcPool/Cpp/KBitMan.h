/*$Workfile: S:\_SrcPool\Cpp\KBitMan.h$: header file
  $Revision: 8$ $Date: 2005-05-12 17:34:53$
  $Author: Darko Kolakovic$

  Manipulation with bits.
  Jun 88 Darko Kolakovic
  Jan 98 inlines and cpp D.K.
 */

#ifndef _KBITMAN_H_
    /*$Workfile: S:\_SrcPool\Cpp\KBitMan.h$ sentry */
  #define _KBITMAN_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

/*///////////////////////////////////////////////////////////////////////////*/
/*Macros                                                                     */

/*RESET_NBITSL()-------------------------------------------------------------*/

/*Set n left of position p bits to zero.
 */
#define RESET_NBITSL( x, p, n)                                            \
     (                                                                    \
      x & ~((~0 << p) ^ ( ~0 << (p + n)) )                                \
     )

/*EXT_NBITSL()---------------------------------------------------------------*/

/*Extract n bits left of position p.
  ~(~0<<n) creates a mask with ones, and mask is moved left p times.

  Example: n=2, p=3, x=1001 1111 result: x=0001 1000
 */
#define EXT_NBITSL( x, p, n)                                              \
     (                                                                    \
      x & (~(~0 << n) << p)                               \
     )

/*CPY_NBITS()----------------------------------------------------------------*/
/*Copy n bits left from position xoff in x to y on position yoff.
 */
#define CPY_NBITS( y, yoff, x, xoff, n)                                      \
     (                                                                       \
      ((yoff-xoff) > 0) ?                                                    \
       RESET_NBITSL( y, yoff, n) | (ExtNbitsL ( x, xoff ,n) << (yoff-xoff)): \
       RESET_NBITSL( y, yoff, n) | (ExtNbitsL ( x, xoff ,n) >> (xoff-yoff))  \
     )



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
inline uint8_t& SetNbitsR(uint8_t& x,/*the field of bits to be set (result) */
                       uint8_t p, /*the start position of the area to set*/
                       uint8_t n  /*the number of bits to set            */
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
inline uint8_t& ResetNbitsL(uint8_t& x,/*the field of bits to be reset (result) */
                         uint8_t p, /*the start position of the area to reset*/
                         uint8_t n  /*the number of bits to reset             */
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
  This returns 6-th,5-th,4-th bit, right adjusted.

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
inline uint8_t GetNbitsR(uint8_t x, /*the source field of bits                   */
                      uint8_t p, /*the start position of the area to retrieve */
                      uint8_t n  /*the number of bits to retrieve             */
                      )
  {
  x = x >> (p + 1 - n) & ~(~0 << n);
  return x;
  }

//GetNBitsL()------------------------------------------------------------------
/*Get n bits left of position p. Desired bits are right adjusted.

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
inline uint8_t GetNBitsL(uint8_t x, /*the source field of bits                   */
                      uint8_t p, /*the start position of the area to retrieve */
                      uint8_t n  /*the number of bits to retrieve             */
                      )
  {
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
inline uint8_t ExtNbitsL(uint8_t x, /*the source field of bits                   */
                      uint8_t p, /*the start position of the area to retrieve */
                      uint8_t n  /*the number of bits to retrieve             */
                      )
  {
  x =  EXT_NBITSL( x, p, n);
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
inline uint8_t& CpyNbitsL(uint8_t& y,/*the result                                 */
                       uint8_t x, /*the source field of bits                   */
                       uint8_t p, /*the start position of the area to retrieve */
                       uint8_t n  /*the number of bits to retrieve             */
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
  Returns TRUE if a flag is set, otherwise FALSE
 */
template <class TYPE>
inline BOOL GetFlag(const TYPE& iStatus,const TYPE&  uFlag)
   {
   return ((iStatus & uFlag) == uFlag);
   };

//EnableFlag()-----------------------------------------------------------------
/*Returns status after a flags are set.
 */
template <class TYPE>
inline TYPE EnableFlag(TYPE& iStatus,const TYPE& uFlags)
   {
   return(iStatus = iStatus | uFlags);
   };

//DisableFlag()----------------------------------------------------------------
/*Returns status after a flags are cleared
 */
template <class TYPE>
inline TYPE DisableFlag(TYPE& iStatus, const TYPE& uFlags)
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
 */
template <class T> T SetNthBit (T& Status,const unsigned int& nPos)
  {
  return (Status | 1 << nPos);
  }

//ResetNthBit()----------------------------------------------------------------
/*Set bit on position nPos to 0
 */
template <class T> T ResetNthBit (T& Status,const unsigned int& nPos)
  {
  return (Status & ~(1 << nPos));
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
