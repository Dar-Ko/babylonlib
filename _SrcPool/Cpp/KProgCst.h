/*$RCSfile: KProgCst.h$: header file
  $Revision: 28$ $Date: 2007-05-31 16:43:24$
  $Author: Darko Kolakovic$

  Constants
  Copyright: CommonSoft Inc.
  Nov. 93 D. Kolakovic
 */

#ifndef __KPROGCST_H__
    /*$RCSfile: KProgCst.h$ sentry */
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

  #define UCSURROGATE1    0xD800
  #define UCSURROGATE2    0xDC00
  #define UCSURROGATELAST 0xDFFF
  #define UCHANGUL1       0xAC00
  #define UCHANGULLAST    0xD7A3
  #define UCREPLACEMENT   0xFFFD

  /*Byte Order Mark (BOM) indicates a Unicode file. The value FFFE is not
    a character at all. If an Unicode a file begins with this mark, byte order
    (big or little endian) may be detected comparing it with with value FEFF
    which is a character 'zero width no-break space'.

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

  /*Private-use-zone mark (PUZ) is used as a sentinel separating Unicode text and
    custom data. The value FFFF is not a character at all.

    Unicode noncharacters are guaranteed not to be a Unicode character at all.
    These codes are intended for process internal uses, but are not permitted
    for interchange.

      FFFE - not a character, Byte Order Mark (BOM)
      FFFF - not a character, private-use-zone (PUZ) sentinel

    See also: {html: <a href=http://www.unicode.org/charts/PDF/UFFF0.pdf</a>}
   */
  #define UCPRIVATEUSEZONE 0xFFFF

  /*Validates if a vule is equal to Unicode Byte Order Mark (BOM) in underlaying
    architecture (big or little endian).
   */
  #define ISUCBOM(x) (UCBYTEORDERMARK == (0xFFFFU & (x)))

  /*Validates three subsequent 8-bit characters are equalt to UTF-8
    Byte Order Mark (BOM).
    UTF-8 encoded file begins with 0xEF, 0xBB, 0xBF bytes.
   */
  #define ISUTF8BOM( px )  \
     ((0xFE == ((uint8_t *)px)[0]) && \
      (0xBB == ((uint8_t *)px)[1]) && \
      (0xBF == ((uint8_t *)px)[2]))

  #ifndef MEM_OUTOFPROCESS
  /*Memory usually outside of a process ("No man's land").
    Microsoft compiler initializes certain memory blocks with specific values to
    help problem diagnostic and debugging. In debug builds every byte is set to
    certain value. These values are undocumented and subject to change.
    User should look for patterns of 4 or more bytes with specific values.

    See also: Long, Mark; "Troubleshooting Common Problems with Applications:
    Debugging in the  Real World";
    {html: <a href="msdn.microsoft.com/en-us/library/aa260966(VS.60).aspx" title="MSDN">
    Table 1. Potential patterns</a>},
    KProgCstMsvc.h, MEM_FREED, MEM_UNINITGLOBAL, MEM_UNINITLOCAL
   */
    #define MEM_OUTOFPROCESS 0xFDFDFDFD
  #endif
  #ifndef MEM_FREED
    #define MEM_FREED        0xDDDDDDDD //Freed memory previously allocated
                                        //See also: MEM_OUTOFPROCESS
  #endif
  #ifndef MEM_UNINITGLOBAL
    #define MEM_UNINITGLOBAL 0xCDCDCDCD //Uninitialized global.
                                        //See also: MEM_OUTOFPROCESS
  #endif
  #ifndef MEM_UNINITLOCAL
    #define MEM_UNINITLOCAL  0xCCCCCCCC //Uninitialized local (on the stack)
                                        //See also: MEM_OUTOFPROCESS
  #endif

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

#ifndef XOR
  /*Logical XOR operator.

     a b  XOR(a, b)
     0 0     0
     0 1     1
     1 0     1
     1 1     0

   Returns the boolean value true if either operand is non-zero but not both.
   otherwise returns false.
   */
  #define XOR(a, b) ((a || b) && !(a && b))
#endif
  /*-------------------------------------------------------------------------*/
#else /*__cplusplus  C++ compilation                                         */
  #pragma message ("   C++ compilation " __FILE__ )

  const wchar_t UCSURROGATE1    = 0xD800;
  const wchar_t UCSURROGATE2    = 0xDC00;
  const wchar_t UCSURROGATELAST = 0xDFFF;
  const wchar_t UCHANGUL1       = 0xAC00;
  const wchar_t UCHANGULLAST    = 0xD7A3;
  const wchar_t UCREPLACEMENT   = 0xFFFD;

  /*Byte Order Mark (BOM) indicates a Unicode file. The value FFFE is not
    a character at all. If an Unicode a file begins with this mark, byte order
    (big or little endian) may be detected comparing it with with value FEFF
    which is a character 'zero width no-break space'.

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

  /*Private-use-zone (PUZ) mark is used as a sentinel separating Unicode text and
    custom data. The value FFFF is not a character at all.

    Unicode noncharacters are guaranteed not to be a Unicode character at all.
    These codes are intended for process internal uses, but are not permitted
    for interchange.

      FFFE - not a character, Byte Order Mark (BOM)
      FFFF - not a character, private-use-zone (PUZ) sentinel

    See also: {html: <a href=http://www.unicode.org/charts/PDF/UFFF0.pdf</a>}
   */
  const wchar_t UCNIPRIVATEUSEZONE = 0xFFFF;

  /*Byte Order Mark (BOM) UTF-8
   */
  const uint8_t UTF8BYTEORDERMARK[] = {0xEF, 0xBB, 0xBF};

  /*Validates if a value is equal to Unicode Byte Order Mark (BOM) in underlaying
    architecture (big or little endian).
   */
inline bool ISUCBOM(const wchar_t x //[in] value to validate
                   )
  {
  return (UCBYTEORDERMARK == x);
  }

  /*Validates if a value is equal to Unicode Byte Order Mark (BOM) in little endian
    architecture.
   */
inline bool ISUCBOMLE(const uint8_t x[2] //[in] value to validate
                     )
  {
  return ((0xFF == x[0]) &&
          (0xFE == x[1]) );
  }

  /*Validates if a value is equal to Unicode Byte Order Mark (BOM) in little endian
    architecture.
   */
inline bool ISUCBOMBE(const uint8_t x[2] //[in] value to validate
                     )
  {
  return ((0xFE == x[0]) &&
          (0xFF == x[1]) );
  }

  /*Validates three subsequent 8-bit characters are equalt to UTF-8
    Byte Order Mark (BOM).
    UTF-8 encoded file begins with 0xEF, 0xBB, 0xBF bytes.
   */
inline bool ISUTF8BOM(const uint8_t x[3] //[in] value to validate
                     )
  {
  return ((UTF8BYTEORDERMARK[0] == x[0]) &&
          (UTF8BYTEORDERMARK[1] == x[1]) &&
          (UTF8BYTEORDERMARK[2] == x[2]) );
  }

#ifndef MEM_OUTOFPROCESS
  /*Memory usually outside of a process ("No man's land").
    Microsoft compiler initializes certain memory blocks with specific values to
    help problem diagnostic and debugging. In debug builds every byte is set to
    certain value. These values are undocumented and subject to change.
    User should look for patterns of 4 or more bytes with specific values.

    See also: Long, Mark; "Troubleshooting Common Problems with Applications:
    Debugging in the  Real World";
    {html: <a href="msdn.microsoft.com/en-us/library/aa260966(VS.60).aspx" title="MSDN">
    Table 1. Potential patterns</a>},
    KProgCstMsvc.h, MEM_FREED, MEM_UNINITGLOBAL, MEM_UNINITLOCAL
   */
  const unsigned int MEM_OUTOFPROCESS = 0xFDFDFDFD;
  #define MEM_OUTOFPROCESS MEM_OUTOFPROCESS
#endif
#ifndef MEM_FREED
  const unsigned int MEM_FREED        = 0xDDDDDDDD; //Freed memory previously allocated
                                                    //See also: MEM_OUTOFPROCESS
  #define MEM_FREED        MEM_FREED
#endif
#ifndef MEM_UNINITGLOBAL
  const unsigned int MEM_UNINITGLOBAL = 0xCDCDCDCD; //Uninitialized global.
                                                    //See also: MEM_OUTOFPROCESS
  #define MEM_UNINITGLOBAL MEM_UNINITGLOBAL
#endif
#ifndef MEM_UNINITLOCAL
  const unsigned int MEM_UNINITLOCAL  = 0xCCCCCCCC; //Uninitialized local (on the stack)
                                                    //See also: MEM_OUTOFPROCESS
  #define MEM_UNINITLOCAL  MEM_UNINITLOCAL
#endif

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

#ifndef XOR
  /*Logical XOR operator.

         a b  XOR(a, b)
         F F     F
         F T     T
         T F     T
         T T     F
    Returns the boolean value true if either operand is true but not both.
    otherwise returns false.
   */
  inline bool XOR(const bool a, const bool b)
    {
    return ((a || b) && !(a && b));
    }
#endif
///////////////////////////////////////////////////////////////////////////////
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
  /*Swap values of distinct variables having the same data type without using
    a temporary variable.
    Varibles have to distinct (to be on different storage locations), otherwise
    result will be 0.
    In most practical scenarios, the trivial swap algorithm using a temporary
    variable is more efficient, in particular where CPU allows parallel 
    execution. Situations in which XOR swapping may be beneficial are:
    using microcontrollers with very limited RAM, CPU with highly optimized
    XOR swap command.
   */
#define SWAP_INT(px, py)  {  \
  if ((int*)px != (int*)py)  \
    {            \
    *px ^= *py;  \
    *py ^= *px;  \
    *px ^= *py;  \
    }            \
  }

  /*Set of wide characters representing Latin letters, digits
    and specal characters '_', ' '    */
#define ALPHANUMERICSET1W L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_ 0123456789"
  /*Set of condtional width characters representing Latin letters, digits and
    specal characters '_', ' '    */
#define ALPHANUMERICSET1T _T("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_ 0123456789")
  /*Set of Latin letters, digits and specal characters '_', ' '              */
#define ALPHANUMERICSET1   "ABCDEFGHIJKLMNOPQRSTUVWXYZ" \
                           "abcdefghijklmnopqrstuvwxyz" \
                           "_ 0123456789"

#ifndef SIZEOFARR
  #if !defined(__cplusplus)
    /*Returns number of elements in an array.

      Parameters:
        - X a static array of custom objects.

      Note: the size of the array have to be static.
      Note: if X is a pointer instead an array, C compilation will produce
      erroneous result, while C++ compilation will fail.

      Example:
          POINT ptArray[100];
          ASSERT(SIZEOFARR(ptArray) == 100);
          ASSERT((SIZEOFARR(L"0123456789") - SIZEOFARR(L"")) == 10)

     See also: ARRSIZE, _countof, NELEM, NUMBER_OF, _WSPIAPI_COUNTOF, RTL_NUMBER_OF_V1
     */
    #define SIZEOFARR(x)  (sizeof (x) / sizeof ((x)[0]))
  #else
    extern "C++"
      {
      /*Transforms an array of objects to the same length array of bytes.
        Parameters:
          - TYPE the type of objects stored in the array.
          - nCount number of elements of type TYPE stored in the array.
       */
      template <class TYPE, size_t nCount>
      char (&_ArrayCount(TYPE (&X)[nCount]))[nCount];
      /*Returns number of elements in an array.

        Parameters:
          - X a static array of custom objects.

        Note: the size of the array have to be static.
        Note: if X is a pointer instead an array, C compilation will produce
        erroneous result, while C++ compilation will fail.

        Example:
            POINT ptArray[100];
            ASSERT(SIZEOFARR(ptArray) == 100);
            ASSERT((SIZEOFARR(L"0123456789") - SIZEOFARR(L"")) == 10)

       See also: ARRSIZE, _countof, NELEM, NUMBER_OF, _WSPIAPI_COUNTOF, RTL_NUMBER_OF_V1
       */
      #define SIZEOFARR(X) sizeof(_ArrayCount(X))
      }
  #endif

  /*Synonyms for SIZEOFARR                                                    */
  #ifndef ARRSIZE
    #define ARRSIZE  SIZEOFARR
  #endif
  #ifndef _countof
    #define _countof  SIZEOFARR
  #endif
  #ifndef NELEM
    #define NELEM  SIZEOFARR
  #endif
  #ifndef NUMBER_OF
    #define NUMBER_OF  SIZEOFARR
  #endif
#endif

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

/*Verifies if one set of numbers defined with range boundaries [n1, n2] is
  included in the other. Only range boundaries are examined; it is assumed that
  set elements are within range boundaries and the boudaries are elemenets of sets.
  Returns true if one of the sets includes boundaries of the other.
 */
#define ISRANGEINCLUDED(nA1, nA2, nB1, nB2) \
    ((nA2) >= (nB1) && (nB2) >= (nA1))

/*Verifies if one set of numbers defined with range boundaries (n1, n2) is
  included in the other. Only elements within range boundaries are examined; it
  is assumed that set elements are within range boundaries.
  Returns true if one of the sets includes elements within boundaries of the other.
 */
#define ISRANGEEINCLUDED(nA1, nA2, nB1, nB2) \
    ((nA2) > (nB1) && (nB2) > (nA1))

/*Verfies if an array is an empty or insignificant set.

  Example:
      char* szVec = "123456";
      if(!ISEMPTY(szVec))
        printf(szVec);

  Returns true if the array is NULL pointer or if first element is zero;
  otherwise returns false.
 */
#define ISEMPTY(pVec) ((pVec == NULL) || (pVec[0] == 0))

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
/* Compiler specific constants                                               */
#ifdef _MSC_VER /*Microsoft Visual C/C++ Compiler                            */
  #include "KProgCstMsvc.h"
#endif /*_MSC_VER*/
#if defined(__GNUC__) /*GNU C/C++ Compiler                                   */
  //#include "KProgCstGnuc.h" TODO:
#endif
#if defined(__MWERKS__) /*Metrowerks Code Warrior C/C++ Compiler             */
  //#include "KProgCstMwcw.h" TODO:
#endif

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

#ifndef UNUSED_ARG
  #if defined(__GNUC__) //TODO: Move to KProgCstGnuc.h D.K.
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
#endif /* UNUSED_ARG */

#ifndef UNUSED
  /*Resolves the compiler warning about unused arguments.
    Synonim to _UNUSED, UNUSED_ARG.
   */
  #define UNUSED _UNUSED
#endif
#ifndef UNUSED_ARG
  /*Resolves the compiler warning about unused arguments.
    Synonim to _UNUSED, UNUSED.
   */
  #define UNUSED_ARG _UNUSED
#endif

#ifndef _KEXPORTDECL
  /*This storage-class specification explicitly define the DLL’s interface to
    its client, which can be the executable file or another DLL. The attribute
    allows the compiler to generate the export names automatically and place
    them in a library (.lib) file.
    When building your DLL, you typically create a header file that contains
    the function prototypes and/or classes you are exporting, and add
    the _KEXPORTDECL specification to the declarations in the header file.
    This modifiers are used to export classes, functions, and data.

    Examples:
        class _KINEXDECL <class name>
        return_type _KINEXDECL <function name>
        data_type _KINEXDECL <data name>

    Note: ANSI compatibility compiler option disables __declspec.

    See also: _KIMPORTDECL, _KINEXDECL,._USE_EXPORT, __declspec, dllexport
   */
  #define _KEXPORTDECL  __declspec(dllexport)
#endif
#ifndef _KIMPORTDECL
  /*This storage-class specification explicitly define the object as external to
    DLL's client, which can be the executable file or another DLL.

    Note: ANSI compatibility compiler option disables __declspec.

    See also: _KEXPORTDECL, _KINEXDECL,._USE_EXPORT, __declspec, dllimport
   */
   #define _KIMPORTDECL  __declspec(dllimport)
#endif

//Export declartion; to declare class neither exported nor imported,
//undefine _PREMIUM_EXPORT and _PREMIUM_INEX
#ifndef _KINEXDECL
  #ifdef _USE_EXPORT
    /*Command the linker to enter an object name into an export table for the
      module.
      When building your DLL, you typically create a header file that contains
      the function prototypes and/or classes you are exporting, add
      the _KINEXDECL specification to the declarations in the header file and
      define _USE_EXPORT. Undefined _USE_EXPORT implies import specification.
      This modifiers are used to export classes, functions, and data.

      Examples:
          class _KINEXDECL <class name>
          return_type _KINEXDECL <function name>
          data_type _KINEXDECL <data name>

      See also: _KEXPORTDECL, _KIMPORTDECL,._USE_EXPORT, __declspec, dllexport,
      dllimport
     */
    #define _KINEXDECL _KEXPORTDECL
  #else /*!_USE_EXPORT*/
    #define _KINEXDECL _KIMPORTDECL
  #endif /*_USE_EXPORT*/
#endif

/* ///////////////////////////////////////////////////////////////////////// */
#endif  /*__KPROGCST_H__                                                     */
/*****************************************************************************
 * $Log: $
 *  5    Biblioteka1.4         17/08/2001 12:37:48 AMDarko           Update
 *  4    Biblioteka1.3         20/07/2001 12:58:39 AMDarko           VSS tags
 *  3    Biblioteka1.2         11/07/2001 10:52:06 PMDarko
 *  2    Biblioteka1.1         08/06/2001 11:51:16 PMDarko           VSS
 *  1    Biblioteka1.0         13/08/2000 3:56:59 PMDarko
 * Dec. 99 NaN constants D.K.
 * Jan. 96 IS_EQUAL D.K.
 * Nov. 93 D. Kolakovic
 *****************************************************************************/
