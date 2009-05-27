/*$Workfile: KType32.h$: header file
  $Revision: 10$ $Date: 22/08/2007 7:28:13 PM$
  $Author: Darko Kolakovic$

  ISO C99 type definitions ISO/IEC 9899:1999
  Copyright: CommonSoft Inc
  Feb 2000 Darko Kolakovic
 */

#ifndef _KTYPE32_H_
    /*$Workfile: KType32.h$ sentry */
  #define _KTYPE32_H_

  #if (_MSC_VER > 1000) || (__MWERKS__ >= 0x3000)
    #pragma once
  #endif // _MSC_VER > 1000 || __MWERKS__ >= 0x3000

  #ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
    #pragma message ("   #include " __FILE__ )
  #endif

    //GNU C++ compiler
  #if defined(__GNUC__)
    #include <stdint.h> /*ISO C99: 7.18 Integer types*/
    #ifndef _STDINT_H
      /*ISO C99: 7.18 Integer types included*/
      #define _STDINT_H_   99718
    #endif
    #ifndef _STDINT_H_
      /*ISO C99: 7.18 Integer types included*/
      #define _STDINT_H_   99718
    #endif
  #endif

    //Microsoft Visual C/C++ compiler, C compiler
  #if defined _MSC_VER
    #ifdef _WIN32
  //TODO: this is quick fix for Microsoft C++; D.K.
      #ifndef __NATIVE_32_BIT__
        #define __NATIVE_32_BIT__ 32
      #endif
    #endif
  #endif

  /* /////////////////////////////////////////////////////////////////////// */
  /* Type definitions                                                        */
  /* Note:  <stdint.h> should be used, if exist                              */

  #if !defined(_STDINT_H_)
    #if defined(__NATIVE_32_BIT__)
#if _MSC_VER >= 1300     /*Microsoft Visual C++ .Net 2002, 32-bit, version 7.0*/
/*D.K. FixMe!  quick hack; requires redo  */
      /* Signed.  */
      #ifndef __int8_t_defined
        #define __int8_t_defined
        #ifndef int8_t
          typedef __int8 int8_t;
          #define int8_t int8_t
        #endif
        #ifndef int16_t
          typedef __int16  int16_t;
          #define int16_t int16_t
        #endif
        #ifndef int32_t
          typedef __int32  int32_t;
          #define int32_t int32_t
        #endif
        #ifndef int64_t
        typedef __int64  int64_t;
          #define int64_t int64_t
        #endif
      #endif

      /* Unsigned.  */
      #ifndef __uint8_t_defined
        #define __uint8_t_defined
        #ifndef uint8_t
          typedef unsigned __int8   uint8_t;
          #define uint8_t uint8_t
        #endif
        #ifndef uint16_t
          typedef unsigned __int16  uint16_t;
          #define uint16_t uint16_t
        #endif
        #ifndef uint32_t
          typedef unsigned __int32  uint32_t;
          #define uint32_t uint32_t
        #endif
        #ifndef uint64_t
          typedef unsigned __int64  uint64_t;
          #define uint64_t uint64_t
        #endif
      #endif

       /* Signed at least.*/
      #ifndef __int_least8_t_defined
        #define __int_least8_t_defined
        #ifndef int_least8_t
          typedef __int8 int_least8_t;
          #define int_least8_t int_least8_t
        #endif
        #ifndef int_least16_t
          typedef __int16  int_least16_t;
          #define int_least16_t int_least16_t
        #endif
        #ifndef int_least32_t
          typedef __int32  int_least32_t;
          #define int_least32_t int_least32_t
        #endif
        #ifndef int_least64_t
        typedef __int64  int_least64_t;
          #define int_least64_t int_least64_t
        #endif
      #endif

       /* Unsigned at least.*/
      #ifndef __uint_least8_t_defined
        #define __uint_least8_t_defined
        #ifndef uint_least8_t
          typedef __int8 uint_least8_t;
          #define uint_least8_t uint_least8_t
        #endif
        #ifndef uint_least16_t
          typedef __int16  uint_least16_t;
          #define uint_least16_t uint_least16_t
        #endif
        #ifndef uint_least32_t
          typedef __int32  uint_least32_t;
          #define uint_least32_t uint_least32_t
        #endif
        #ifndef uint_least64_t
        typedef __int64  uint_least64_t;
          #define uint_least64_t uint_least64_t
        #endif
      #endif

      /* Fast unsigned.*/
      #ifndef __uint_fast8_t_defined
        #define __uint_fast8_t_defined
        #ifndef uint_fast8_t
          typedef __int8 uint_fast8_t;
          #define uint_fast8_t uint_fast8_t
        #endif
        #ifndef uint_fast16_t
          typedef __int16  uint_fast16_t;
          #define uint_fast16_t uint_fast16_t
        #endif
        #ifndef uint_fast32_t
          typedef __int32  uint_fast32_t;
          #define uint_fast32_t uint_fast32_t
        #endif
        #ifndef uint_fast64_t
        typedef __int64  uint_fast64_t;
          #define uint_fast64_t uint_fast64_t
        #endif
      #endif

#else /*not MSVC 7.0 *.
      /* Signed.  */
      #ifndef int8_t
        #define int8_t int8_t
        typedef signed char   int8_t;
        typedef short int     int16_t;
        typedef long          int32_t;
        #if defined(__GNUC__)
          typedef long long int int64_t;
        #endif
      #endif

      /* Unsigned.  */
      #ifndef __uint8_t_defined
        #define __uint8_t_defined
        typedef unsigned char          uint8_t;
        #define uint8_t uint8_t
        typedef unsigned short int     uint16_t;
        typedef unsigned long          uint32_t;
        #if defined(__GNUC__)
          typedef unsigned long long int uint64_t;
        #endif
      #endif

      /*@ least*/
      /* Signed.  */
      typedef signed char   int_least8_t;
      typedef short int     int_least16_t;
      typedef int           int_least32_t;
  #if defined(__GNUC__) //TODO: MSVC
      typedef long long int int_least64_t;
  #endif
      /* Unsigned.  */
      typedef unsigned char          uint_least8_t;
      typedef unsigned short int     uint_least16_t;
      typedef unsigned int           uint_least32_t;
  #if defined(__GNUC__)
      typedef unsigned long long int uint_least64_t;
  #endif

      /* Fast types.  */
      /* Signed.  */
      typedef signed char   int_fast8_t;
      typedef int           int_fast16_t;
      typedef int           int_fast32_t;
  #if defined(__GNUC__)
      typedef long long int int_fast64_t;
  #endif
      /* Unsigned.  */
      typedef unsigned char          uint_fast8_t;
      typedef unsigned int           uint_fast16_t;
      typedef unsigned int           uint_fast32_t;
  #if defined(__GNUC__)
      typedef unsigned long long int uint_fast64_t;
  #endif

      /* Types for void * pointers.  */
      #ifndef __intptr_t_defined
        typedef int          intptr_t;
        #define __intptr_t_defined
      #endif
      typedef unsigned int uintptr_t;

      /* Largest integral types.  */
  #if defined(__GNUC__)
      typedef long long int          intmax_t;
      typedef unsigned long long int uintmax_t;
  #endif

#endif /* _MSC_VER >= 1300 */

  /*TODO: Borrowed from GNUC temporarely D.K. replace with own csts*/
  /* The ISO C99 standard specifies that in C++ implementations these
    macros should only be defined if explicitly requested.  */
  #if !defined __cplusplus || defined __STDC_LIMIT_MACROS

  #if __WORDSIZE == 64
  #define __INT64_C(c)   c ##L
  #define __UINT64_C(c)  c ##UL
  #else
  #define __INT64_C(c)   c ##LL
  #define __UINT64_C(c)  c ##ULL
  #endif

  /* Limits of integral types.  */

  /* Minimum of signed integral types.  */
  #define INT8_MIN       (-128)
  #define INT16_MIN      (-32767-1)
  #define INT32_MIN      (-2147483647-1)
  #define INT64_MIN      (-__INT64_C(9223372036854775807)-1)
  /* Maximum of signed integral types.  */
  #define INT8_MAX       (127)
  #define INT16_MAX      (32767)
  #define INT32_MAX      (2147483647)
  #define INT64_MAX      (__INT64_C(9223372036854775807))

  /* Maximum of unsigned integral types. Minimum is 0 */
  #define UINT8_MAX      (255)
  #define UINT16_MAX     (65535)
  #define UINT32_MAX     (4294967295U)
  #define UINT64_MAX     (__UINT64_C(18446744073709551615))

  /* Minimum of signed integral types having a minimum size.  */
  #define INT_LEAST8_MIN     (-128)
  #define INT_LEAST16_MIN    (-32767-1)
  #define INT_LEAST32_MIN    (-2147483647-1)
  #define INT_LEAST64_MIN    (-__INT64_C(9223372036854775807)-1)
  /* Maximum of signed integral types having a minimum size.  */
  #define INT_LEAST8_MAX     (127)
  #define INT_LEAST16_MAX    (32767)
  #define INT_LEAST32_MAX    (2147483647)
  #define INT_LEAST64_MAX    (__INT64_C(9223372036854775807))

  /* Maximum of unsigned integral types having a minimum size.  */
  #define UINT_LEAST8_MAX    (255)
  #define UINT_LEAST16_MAX   (65535)
  #define UINT_LEAST32_MAX   (4294967295U)
  #define UINT_LEAST64_MAX   (__UINT64_C(18446744073709551615))

  /* Minimum of fast signed integral types having a minimum size.  */
  #define INT_FAST8_MIN      (-128)
  #define INT_FAST16_MIN    (-2147483647-1)
  #define INT_FAST32_MIN    (-2147483647-1)
  #define INT_FAST64_MIN     (-__INT64_C(9223372036854775807)-1)

  /* Maximum of fast signed integral types having a minimum size.  */
  #define INT_FAST8_MAX      (127)
  #define INT_FAST16_MAX    (2147483647)
  #define INT_FAST32_MAX    (2147483647)
  #define INT_FAST64_MAX     (__INT64_C(9223372036854775807))

  /* Maximum of fast unsigned integral types having a minimum size.  */
  #define UINT_FAST8_MAX     (255)
  #define UINT_FAST16_MAX    (4294967295U)
  #define UINT_FAST32_MAX    (4294967295U)
  #define UINT_FAST64_MAX    (__UINT64_C(18446744073709551615))


  /* Values to test for integral types holding void * pointer.  */
  #define INTPTR_MIN        (-2147483647-1)
  #define INTPTR_MAX        (2147483647)
  #define UINTPTR_MAX       (4294967295U)


  /* Minimum for largest signed integral type.  */
  #define INTMAX_MIN     (-__INT64_C(9223372036854775807)-1)
  /* Maximum for largest signed integral type.  */
  #define INTMAX_MAX     (__INT64_C(9223372036854775807))

  /* Maximum for largest unsigned integral type.  */
  #define UINTMAX_MAX    (__UINT64_C(18446744073709551615))

  /* Limits of other integer types.  */

  /* Limits of ptrdiff_t type.  */
  #define PTRDIFF_MIN     (-2147483647-1)
  #define PTRDIFF_MAX     (2147483647)

  /* Limits of sig_atomic_t.  */
  #define SIG_ATOMIC_MIN  (-2147483647-1)
  #define SIG_ATOMIC_MAX  (2147483647)

  /* Limit of size_t type.  */
  #ifndef SIZE_MAX
    #define SIZE_MAX        (4294967295U)
  #endif

  /* Limits of wchar_t.  */
  /*Defined also in Microsoft <wchar.h> */
  #ifndef _MSC_VER
    #ifndef _INC_WCHAR
      #ifndef WCHAR_MIN
        #define WCHAR_MIN     __WCHAR_MIN
        #define WCHAR_MAX     __WCHAR_MAX
      #endif
    #endif
  #endif

  /* Limits of wint_t.  */
  #define WINT_MIN       (0u)
  #define WINT_MAX       (4294967295u)

  #endif  /* C++ && limit macros */

  /* The ISO C99 standard specifies that in C++ implementations these
    should only be defined if explicitly requested.  */
  #if !defined __cplusplus || defined __STDC_CONSTANT_MACROS

  /* Signed.  */
  #define INT8_C(c)  c
  #define INT16_C(c) c
  #define INT32_C(c) c
  #define INT64_C(c) c ##LL

  /* Unsigned.  */
  #define UINT8_C(c)    c ##U
  #define UINT16_C(c)   c ##U
  #define UINT32_C(c)   c ##U
  #define UINT64_C(c)   c ##ULL

  /* Maximal type.  */
  #define INTMAX_C(c)   c ##LL
  #define UINTMAX_C(c)  c ##ULL

  #endif  /* C++ && constant macros */

    #endif /* __NATIVE_32_BIT__ */
  #endif /* _STDINT_H_ */
  /* /////////////////////////////////////////////////////////////////////// */
#endif /*_KTYPE32_H_*/
/*****************************************************************************
 * $Log:
 *  2    Biblioteka1.1         10/01/2003 9:51:34 PMDarko Kolakovic conditional
 *       long long
 *  1    Biblioteka1.0         08/01/2003 3:26:29 PMDarko Kolakovic
 * $
 *****************************************************************************/
