/*$Workfile: KProgCst.h$: header file
  $Revision: 13$ $Date: 7/12/02 6:19:05 PM$
  $Author: Darko Kolakovic$

  Constants
  Copyright: CommonSoft Inc.
  Nov. 93 D. Kolakovic
  Jan. 96 IS_EQUAL D.K.
  Dec. 99 NaN constants D.K.
 */

#ifndef __KPROGCST_H__
    /*KProgCst.h sentry                                                      */
  #define __KPROGCST_H__

#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
  #pragma message ("   #include " __FILE__ )
#endif

    /*"Little Endian" flag signals that the little end, or lower end, is
      stored first in the memory (low byte at low address, high byte at high
      address). This means a Hex word like 0x0102 is stored in memory as
      (0x02 0x01). This architecture is used with Z80, VAX, Intel 80X86, ARM
      DEC Alpha, MIPS, etc. The RISC-based MIPS computers and the DEC Alpha
      computers are configurable for Big Endian or Little Endian.

           Table 1.1 Byte Ordering of Different Computer Architectures
           Architecture  16 Bit   32 Bit   Floating Point
             MC68000      21       4321       87654321
           IBM 360/370    21       4321       87654321
             Intel        12       1234       12345678
            PDP-11        12       3412       78563412
              VAX         12       1234       78563412

      The origin term "endian" can be traced to Jonathan Swift's novel 
      "Gulliver's Travels". In one of Gulliver's adventures, he encounters 
      an island whose inhabitants bitterly argue over the correct way to open
      soft-boiled eggs - the little end or the big end. Little endians and 
      big endians are each convinced that their method is the only correct 
      method for opening an egg. 
     */
#define _ENDIAN_LITTLE_ 0x1234
    /*"Big Endian" means that most significant or high byte is stored first 
      at low address and low byte stored last at high address. This 
      architecture is used with MC680X0, SPARC, HPPA, MIPS, M88000, RS6000,
      etc.                                                                   */
#define _ENDIAN_BIG_    0x4321
    /*Byte order in PDP architecture.                                        */
#define _ENDIAN_PDP_    0x3412

/*///////////////////////////////////////////////////////////////////////////*/
/* CPU specific                                                              */
/*---------------------------------------------------------------------------*/
/*CPU: Intel x86 CPU family, MSVC++                                          */
#if _M_IX86
  #ifdef _ENDIAN_ORDER_
    #undef _ENDIAN_ORDER_
  #endif 
    /*Byte order, according to significance of bytes                         */
  #define _ENDIAN_ORDER_ _ENDIAN_LITTLE_

    /*Index of the high byte or word in arrays (1 for Little Endian architecture).

          |  WORD0    |  WORD1    |
          |BYTE0|BYTE1|BYTE0|BYTE1|                                          */
  #define _ENDIAN_HIGH_INDEX 1
    /*Index of the low byte or word in arrays (0 for Little Endian architecture).

          |  WORD0    |  WORD1    |
          |BYTE0|BYTE1|BYTE0|BYTE1|                                          */
  #define _ENDIAN_LOW_INDEX  0

  #ifndef _GET_WORD_ALIGNP
    #define _GET_WORD_ALIGNP(pBYTE) (*((WORD*)pBYTE))
  #endif

  #ifndef _GET_DWORD_ALIGNP
    #define _GET_DWORD_ALIGNP(pBYTE) (*((DWORD*)pBYTE))
  #endif

    /*High-order long for double quiet NaN (not a number)                    */
  #define NaN_DQUIET       0xFFF80000
    /*High-order long for double signaling NaN (not a number)                */
  #define NaN_DSIGNAL      0xFFF00000
    /*High-order long for double positive infinity                           */
  #define NaN_DPOSINFINITY 0x7FF00000
    /*High-order long for float quiet NaN (not a number)                     */
  #define NaN_FQUIET       0xFFC00000
    /*High-order long for float signaling NaN (not a number)                 */
  #define NaN_FDSIGNAL     0xFF800000
    /*High-order long for float positive infinity                            */
  #define NaN_FPOSINFINITY 0x7F800000

  /*Contains NaN constants.
    Presentation of NaNs according to IEC 559:

      quiet NaN         -1.#IND,
      signaling NaN     -1.#INF,
      positive infinity  1.#INF                                              */
  typedef union tagNaN_NUMBER
    {
    unsigned long llValue[2]; /*Low and high-order integers of NaN           */
    double dValue;            /*value of 'Not a Number'                      */

    #ifdef __cplusplus
        //Conversion function to modify the value
      operator  double&()
        { return  dValue;};
        //Conversion function to use the value
      operator double() const
        { return dValue;};
    #endif  /*__cplusplus                                                    */
    } NaN_NUMBER;

#endif  /*_M_IX86   Intel x86 CPU                                            */

/*---------------------------------------------------------------------------*/
/*CPU: ARM Risc CPU family, GNUC                                             */
#if (defined(__arm__) || defined(__ARMEL__))

  #ifdef _ENDIAN_ORDER_
    #undef _ENDIAN_ORDER_
  #endif 
    /*Byte order, according to significance of bytes                         */
  #define _ENDIAN_ORDER_ _ENDIAN_LITTLE_

    /*Index of the high byte or word in arrays (1 for Little Endian architecture).

          |  WORD0    |  WORD1    |
          |BYTE0|BYTE1|BYTE0|BYTE1|                                          */
  #define _ENDIAN_HIGH_INDEX 1
    /*Index of the low byte or word in arrays (0 for Little Endian architecture).

          |  WORD0    |  WORD1    |
          |BYTE0|BYTE1|BYTE0|BYTE1|                                          */
  #define _ENDIAN_LOW_INDEX  0

  #ifndef _GET_WORD_ALIGNP
  //Copy a WORD value byte by byte, becouse on some architectures (WORD*)pcHostValue
  //will round pointer to match WORD increments giving a result equal to 
  //*(WORD*)(pcHostValue/sizeof(WORD)) 
    #define _GET_WORD_ALIGNP(pBYTE) \
      ((WORD)pBYTE[0]       |  \
       (WORD)pBYTE[1] <<  8 )
  #endif

  #ifndef _GET_DWORD_ALIGNP
  //Copy a DWORD value byte by byte, becouse on some architectures (DWORD*)pcHostValue
  //will round pointer to match DWORD increments giving a result equal to 
  //*(DWORD*)(pcHostValue/sizeof(DWORD)) 
    #define _GET_DWORD_ALIGNP(pBYTE) \
      ((DWORD)pBYTE[0]       |   \
       (DWORD)pBYTE[1] <<  8 |   \
       (DWORD)pBYTE[2] << 16 |   \
       (DWORD)pBYTE[3] << 24 )
  #endif

#endif

/*///////////////////////////////////////////////////////////////////////////*/
/* Global macros                                                             */

#ifdef _ENDIAN_LITTLE_
 /*Returns 32-bit value with high word initialized with given constant.
   Low word is initialized to zero.
  */
  #define MAKEHIWORD(x) ( ((DWORD)((WORD)(x))) << 16 )

 /*Returns 32-bit value with low word initialized with given constant.
   High word is initialized to zero.
  */
  #define MAKELOWORD(x) ((DWORD)((WORD)(x)))
#else
  #define MAKEHIWORD(x) ((DWORD)((WORD)(x)))
  #define MAKELOWORD(x) ( ((DWORD)((WORD)(x))) << 16 )
#endif /*_ENDIAN_LITTLE_                                                     */
  /*Aligns to DWORD boundary                                                 */
#define ALIGNLONG(x) (((x)+3) & ~(3))
  /*Swaps tailing bytes with bytes from the beginning of the two-bytes WORD  */
#define SWAP_WORD_ENDIAN(w)  (WORD) ((WORD) ((w)<<8)|((w)>>8))

#ifndef __cplusplus
/* ///////////////////////////////////////////////////////////////////////// */
    /*Note: include in a project KProgCst.c to get NaN globals               */
  extern const NaN_NUMBER CST_dNaN;
  extern const NaN_NUMBER CST_dSNaN;
  extern const NaN_NUMBER CST_dINF;

  /* /////////////////////////////////////////////////////////////////////// */
  /* //Macros                                                                */

  /*Returns double value of NaN (not a number).
    See also: union NaN_NUMBER
   */
  #define NaN_DVALUE(NAN)   (NAN.dValue)

  /*Returnes TRUE if two float numbers are equal within an error represented
    with epsilon.
    Epsilon is defined as as the smallest positive number x, such that x+1.0
    is not equal to 1.0. FLT_EPSILON is defined in <Float.h> as 1.192092896e-07F
   */
  #define IS_EQUAL_FLOAT(a,b) (((b - FLT_EPSILON) < a) && (a <( b + FLT_EPSILON)))

  /*Returnes TRUE if two double numbers are equal within an error represented
    with epsilon.
    Epsilon is defined as as the smallest positive number x, such that x+1.0
    is not equal to 1.0. DBL_EPSILON is defined in <Float.h> as 2.2204460492503131e-016
   */
  #define IS_EQUAL_DOUBLE(a,b) (((b - DBL_EPSILON) < a) && (a <( b + DBL_EPSILON)))

/* ///////////////////////////////////////////////////////////////////////// */
/*#else / *__cplusplus                                                          * /
  #ifndef _KPROGCST_INL_
    #include  "KProgCst.inl"
  #endif*/
#endif /*__cplusplus                                                         */
/* ///////////////////////////////////////////////////////////////////////// */
#endif  /*__KPROGCST_H__                                                     */
/*****************************************************************************
 * $Log:
 *  5    Biblioteka1.4         17/08/2001 12:37:48 AMDarko           Update
 *  4    Biblioteka1.3         20/07/2001 12:58:39 AMDarko           VSS tags
 *  3    Biblioteka1.2         11/07/2001 10:52:06 PMDarko
 *  2    Biblioteka1.1         08/06/2001 11:51:16 PMDarko           VSS
 *  1    Biblioteka1.0         13/08/2000 3:56:59 PMDarko
 * $
 *****************************************************************************/
