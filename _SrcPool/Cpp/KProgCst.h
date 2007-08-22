/*$Workfile: KProgCst.h$: header file
  $Revision: 28$ $Date: 2007-05-31 16:43:24$
  $Author: Darko Kolakovic$

  Constants
  Copyright: CommonSoft Inc.
  Nov. 93 D. Kolakovic
 */

#ifndef __KPROGCST_H__
    /*$Workfile: KProgCst.h$ sentry */
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
  etc.
 */
#define _ENDIAN_BIG_    0x4321
  /*Byte order in PDP architecture.                                          */
#define _ENDIAN_PDP_    0x3412

#ifndef __cplusplus /*C compilation                                          */
  #pragma message ("   C compilation " __FILE__ )
  /*/////////////////////////////////////////////////////////////////////////*/
  /*Unicode-specific characters                                              */

  /*Byte Order Mark (BOM) indicates a Unicode file. The value FFFE is not
    a character at all. If an Unicode a file begins with this mark, byte order
    (big or little endian) may be detected comparing it with with value FEFF
    which is a character zero width no-break space.

    Unicode noncharacters are guaranteed not to be a Unicode character at all.
    These codes are intended for process internal uses, but are not permitted
    for interchange.

      FFFE - not a character, Byte Order Mark (BOM)
      FFFF - not a character, private-use-zone (PUZ) sentinel

    Table 1: Byte Order Mark for different encodings

            BOM          Encoding
           EF BB BF       UTF-8
           FF FE          UTF-16
           FF FE 00 00    UTF-32

    Note: in case of the little endian architecture, number 0xFEFF will be
    stored as 0xFF, 0xFE. If file begins with 0xFE, 0xFF, all Unicode
    characters are stored in big endian order.

    See also: {html: <a href=http://www.unicode.org/charts/PDF/UFFF0.pdf</a>}
   */
  #define UCBYTEORDERMARK 0xFEFF
  /*Private-use-zone mark is used as a sentinel separating Unicode text and
    custom data. The value FFFF is not a character at all.

    Unicode noncharacters are guaranteed not to be a Unicode character at all.
    These codes are intended for process internal uses, but are not permitted
    for interchange.

      FFFE - not a character, Byte Order Mark (BOM)
      FFFF - not a character, private-use-zone (PUZ) sentinel

    See also: {html: <a href=http://www.unicode.org/charts/PDF/UFFF0.pdf</a>}
   */
#define UCPRIVATEUSEZONE 0xFFFF

/*Binary measure units                                                       */

#ifndef KiB
  /*Unit of binary measure Kilobyte [KB] or Kibibyte (kilobinarybyte) [KiB]
    1 KiB = 1 KB= = 2^10 = 1024 bytes.
    1 Kib = 1 Kb = 1024 bits.
    See also: IEC 60027-2
   */
  #define KiB       (0x400)
#endif

#ifndef MiB
  /*Unit of binary measure Megabyte [MB] or Mebibyte [MiB]
    1 MB is 2^20 and is equal to 1,048,576 Bytes.
    1 MiB = 1 MB= = 2^20 = 1 048 576 bytes.
    1 Mib = 1 Mb = 1 048 576 bits.
    See also: IEC 60027-2
   */
  #define MiB       (0x100000UL)
#endif

#ifndef GiB
  /*Unit of binary measure Gigabyte [GB] or Gibibyte [GiB]
    1 GiB = 1 GB= = 2^30 = 1 073 741 824 bytes.
    1 Gib = 1 Gb = 1 073 741 824 bits.
    See also: IEC 60027-2
  */
  #define GiB       (0x40000000UL)
#endif
#ifndef TiB
  /*Unit of binary measure Terrabyte [TB] or Tebibyte [TiB]
    1 TiB = 1 TB= = 2^40 = 1 099 511 627 776 bytes.
    1 Tib = 1 Tb = 1 099 511 627 776 bits.
    See also: IEC 60027-2
  */
  #define TiB       (0x10000000000UL)
#endif

  /*-------------------------------------------------------------------------*/
#else /*__cplusplus  C++ compilation                                         */
  #pragma message ("   C++ compilation " __FILE__ )
  /*Byte Order Mark (BOM) indicates a Unicode file. The value FFFE is not
    a character at all. If an Unicode a file begins with this mark, byte order
    (big or little endian) may be detected comparing it with with value FEFF
    which is a character zero width no-break space.

    Unicode noncharacters are guaranteed not to be a Unicode character at all.
    These codes are intended for process internal uses, but are not permitted
    for interchange.

      FFFE - not a character, Byte Order Mark (BOM)
      FFFF - not a character, private-use-zone (PUZ) sentinel

    Table 1: Byte Order Mark for different encodings

            BOM          Encoding
           EF BB BF       UTF-8
           FF FE          UTF-16
           FF FE 00 00    UTF-32

    Note: in case of the little endian architecture, number 0xFEFF will be
    stored as 0xFF, 0xFE. If file begins with 0xFE, 0xFF, all Unicode
    characters are stored in big endian order.

    See also: {html: <a href=http://www.unicode.org/charts/PDF/UFFF0.pdf</a>}
   */
const wchar_t UCBYTEORDERMARK = 0xFEFF;
  /*Private-use-zone mark is used as a sentinel separating Unicode text and
    custom data. The value FFFF is not a character at all.

    Unicode noncharacters are guaranteed not to be a Unicode character at all.
    These codes are intended for process internal uses, but are not permitted
    for interchange.

      FFFE - not a character, Byte Order Mark (BOM)
      FFFF - not a character, private-use-zone (PUZ) sentinel

    See also: {html: <a href=http://www.unicode.org/charts/PDF/UFFF0.pdf</a>}
   */
const wchar_t UCNIPRIVATEUSEZONE = 0xFFFF;

/*Binary measure units                                                       */

  /*Unit of binary measure Kilobyte [KB] or Kibibyte (kilobinarybyte) [KiB]
    1 KiB = 1 KB= = 2^10 = 1024 bytes.
    1 Kib = 1 Kb = 1024 bits.
    See also: IEC 60027-2
   */
const unsigned int KiB = 0x400;
  /*Unit of binary measure Megabyte [MB] or Mebibyte [MiB]
    1 MB is 2^20 and is equal to 1,048,576 Bytes.
    1 MiB = 1 MB= = 2^20 = 1 048 576 bytes.
    1 Mib = 1 Mb = 1 048 576 bits.
    See also: IEC 60027-2
   */
const unsigned int MiB = 0x100000UL;
  /*Unit of binary measure Gigabyte [GB] or Gibibyte [GiB]
    1 GiB = 1 GB= = 2^30 = 1 073 741 824 bytes.
    1 Gib = 1 Gb = 1 073 741 824 bits.
    See also: IEC 60027-2
  */
const unsigned long GiB = 0x40000000UL;
  #ifdef uint64
    /*Unit of binary measure Terrabyte [TB] or Tebibyte [TiB]
      1 TiB = 1 TB= = 2^40 = 1 099 511 627 776 bytes.
      1 Tib = 1 Tb = 1 099 511 627 776 bits.
      See also: IEC 60027-2
    */
    const uint64 TiB = 0x10000000000UL;
  #endif //uint64
#endif /*!__cplusplus                                                        */

#ifndef NaN_NUMBER
 #pragma message ("   8 byte double " __FILE__ )
  //TODO: FixMe! valid for 8 byte long doubles D.K.
  /*Contains NaN constants.
    Presentation of NaNs according to IEC 559:

      quiet NaN         -1.#IND,
      signaling NaN     -1.#INF, //TODO: Check this D.K.
      positive infinity  1.#INF
   */
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

    #define NaN_NUMBER NaN_NUMBER
 #endif /*NaN_NUMBER*/

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

    /*QNaN High-order long for double quiet NaN (not a number)
      denotes indeterminate operations.

      See also: CST_dQNaN
     */
  #define NaN_DQUIET       0xFFF80000
    /*SNaN High-order long for double signaling NaN (not a number)
      denotes invalid operations.

      See also: CST_dSNaN
     */
  #define NaN_DSIGNAL      0xFFF00000
    /*High-order long for double positive infinity.

      See also: CST_dINF
     */
  #define NaN_DPOSINFINITY 0x7FF00000
    /*High-order long for double negative infinity.
      The sign bit distinguishes between negative infinity and positive infinity.
     */
  #define NaN_DNEGINFINITY (-NaN_DPOSINFINITY)

    /*High-order long for float quiet NaN (not a number)                     */
  #define NaN_FQUIET       0xFFC00000
    /*High-order long for float signaling NaN (not a number)                 */
  #define NaN_FDSIGNAL     0xFF800000
    /*High-order long for float positive infinity                            */
  #define NaN_FPOSINFINITY 0x7F800000
  #define NaN_FNEGINFINITY (-NaN_FPOSINFINITY)

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

/*---------------------------------------------------------------------------*/
/*Metrowerks CodeWarrior Compiler                                            */
#if defined(__MWERKS__)/* Metrowerks CodeWarrior Compiler                    */
  #if __option (little_endian)
    /*Byte order, according to significance of bytes                         */
    #define _ENDIAN_ORDER_ _ENDIAN_LITTLE_
  #else
    /*Byte order, according to significance of bytes                         */
    #define _ENDIAN_ORDER_ _ENDIAN_BIG_
  #endif

  #ifndef _ENDIAN_ORDER_
    #ifdef _MSL_LITTLE_ENDIAN
      #if (_MSL_LITTLE_ENDIAN == 1)
        #define _ENDIAN_ORDER_ _ENDIAN_LITTLE_
      #elif (_MSL_LITTLE_ENDIAN == 0)
        #define _ENDIAN_ORDER_ _ENDIAN_BIG_
      #else
        #pragma message ("_MSL_: Unknown Endian byte order.")
      #endif
    #endif /*_MSL_LITTLE_ENDIAN*/
  #endif /*_ENDIAN_ORDER_*/

#endif /*__MWERKS__                                                          */

/*///////////////////////////////////////////////////////////////////////////*/
/* Global macros                                                             */
  /*Aligns to DWORD boundary                                                 */
#define ALIGNLONG(x) (((x)+3) & ~(3))

  /*Swaps tailing two bytes with bytes from the beginning of the 32-bit integer*/
#define SWAP_DWORD(dw)       ((DWORD) ((dw >> 16) | (dw << 16)))
  /*Swaps tailing bytes with bytes from the beginning of the 16-bit integer  */
#define SWAP_WORD_ENDIAN(w)  ((WORD) ((WORD) ((w)<<8)|((w)>>8)))
  /*Swaps tailing nibble with nibble from the beginning of the byte          */
#define SWAP_BYTE( ch )  (( ( (ch) << 4 ) | ( (ch) >> 4 ) ))


  /*Set of ASCII letters, digits and specal characters '_', ' '              */
#define ALPHANUMERICSET1 "ABCDEFGHIJKLMNOPQRSTUVWXYZ" \
                         "abcdefghijklmnopqrstuvwxyz" \
                         "_" "0123456789"
  /*Returns number of elements in an array                                   */
#define SIZEOFARR(x)  (sizeof (x) / sizeof ((x)[0]))


#ifndef _UNUSED
  /*Resolves the compiler warning about unused arguments

    Example:
        void main (int x, int y)
        {
        _UNUSED(y);
        x = 3;
        ...
        }
   */
  #define _UNUSED(x) ((void)x)
#endif

#ifndef UNUSED
  #define UNUSED _UNUSED
#endif

#ifndef UNUSED_ARG
  #if defined(__GNUC__)
    /*GNU C/C++ */
    #if !defined(__cplusplus)
      /*Attribute of unused function arguments */
      #define UNUSED_ARG(param) param __attribute__((__unused__))
    #else
      //GNU C++ doesn't support this attribute
      #define UNUSED_ARG
    #endif
  #endif /*__GNUC__*/
//  #define UNUSED_ARG(param) do {/* null */} while (&param == 0)
//  #define UNUSED_ARG(param) param = *(&param);
  #if defined(__MWERKS__)
    /*Metrowerks Code Warrior*/
    #define UNUSED_ARG(param)    &(param)
  #endif

  #if defined(_MSC_VER)
    /*Microsoft Visual C/C++*/
    #define UNUSED_ARG _UNUSED
  #endif

#endif /* UNUSED_ARG */


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


#ifndef __cplusplus
/* ///////////////////////////////////////////////////////////////////////// */
    /*Note: include in a project KProgCst.inl to get NaN globals               */
 // extern const NaN_NUMBER CST_dNaN;
 // extern const NaN_NUMBER CST_dSNaN;
 // extern const NaN_NUMBER CST_dINF;

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
 * Dec. 99 NaN constants D.K.
 * Jan. 96 IS_EQUAL D.K.
 * Nov. 93 D. Kolakovic
 *****************************************************************************/
