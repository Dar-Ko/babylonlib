/*$Workfile: KType32.h$: header file
  $Revision: 3$ $Date: 18/01/2003 7:57:57 PM$
  $Author: Darko$

  ISO C99 type definitions ISO/IEC 9899:1999
  Copyright: CommonSoft Inc
  Feb 2000 Darko Kolakovic
 */

/*Note:  <stdint.h> should be used, if exist
 */

#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
  #pragma message ("   #include " __FILE__ )
#endif

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

#if !defined(_STDINT_H_)
  #if defined(__NATIVE_32_BIT__)
    /* Signed.  */
    #ifndef __int8_t_defined
      #define __int8_t_defined
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

    /* Types for `void *' pointers.  */
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
/*TODO: Borrowed from GNUC temporarely D.K. replace with own csts*/
/* The ISO C99 standard specifies that in C++ implementations these
   macros should only be defined if explicitly requested.  */
#if !defined __cplusplus || defined __STDC_LIMIT_MACROS

# if __WORDSIZE == 64
#  define __INT64_C(c)   c ## L
#  define __UINT64_C(c)  c ## UL
# else
#  define __INT64_C(c)   c ## LL
#  define __UINT64_C(c)  c ## ULL
# endif

/* Limits of integral types.  */

/* Minimum of signed integral types.  */
# define INT8_MIN       (-128)
# define INT16_MIN      (-32767-1)
# define INT32_MIN      (-2147483647-1)
# define INT64_MIN      (-__INT64_C(9223372036854775807)-1)
/* Maximum of signed integral types.  */
# define INT8_MAX       (127)
# define INT16_MAX      (32767)
# define INT32_MAX      (2147483647)
# define INT64_MAX      (__INT64_C(9223372036854775807))

/* Maximum of unsigned integral types.  */
# define UINT8_MAX      (255)
# define UINT16_MAX     (65535)
# define UINT32_MAX     (4294967295U)
# define UINT64_MAX     (__UINT64_C(18446744073709551615))

/* Minimum of signed integral types having a minimum size.  */
# define INT_LEAST8_MIN     (-128)
# define INT_LEAST16_MIN    (-32767-1)
# define INT_LEAST32_MIN    (-2147483647-1)
# define INT_LEAST64_MIN    (-__INT64_C(9223372036854775807)-1)
/* Maximum of signed integral types having a minimum size.  */
# define INT_LEAST8_MAX     (127)
# define INT_LEAST16_MAX    (32767)
# define INT_LEAST32_MAX    (2147483647)
# define INT_LEAST64_MAX    (__INT64_C(9223372036854775807))

/* Maximum of unsigned integral types having a minimum size.  */
# define UINT_LEAST8_MAX    (255)
# define UINT_LEAST16_MAX   (65535)
# define UINT_LEAST32_MAX   (4294967295U)
# define UINT_LEAST64_MAX   (__UINT64_C(18446744073709551615))

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


/* Values to test for integral types holding `void *' pointer.  */
#define INTPTR_MIN        (-2147483647-1)
#define INTPTR_MAX        (2147483647)
#define UINTPTR_MAX       (4294967295U)


/* Minimum for largest signed integral type.  */
# define INTMAX_MIN     (-__INT64_C(9223372036854775807)-1)
/* Maximum for largest signed integral type.  */
# define INTMAX_MAX     (__INT64_C(9223372036854775807))

/* Maximum for largest unsigned integral type.  */
# define UINTMAX_MAX    (__UINT64_C(18446744073709551615))

/* Limits of other integer types.  */

/* Limits of `ptrdiff_t' type.  */
#define PTRDIFF_MIN     (-2147483647-1)
#define PTRDIFF_MAX     (2147483647)

/* Limits of `sig_atomic_t'.  */
#define SIG_ATOMIC_MIN  (-2147483647-1)
#define SIG_ATOMIC_MAX  (2147483647)

/* Limit of `size_t' type.  */
#define SIZE_MAX        (4294967295U)

/* Limits of `wchar_t'.  */
# ifndef WCHAR_MIN
/* These constants might also be defined in <wchar.h>.  */
#  define WCHAR_MIN     __WCHAR_MIN
#  define WCHAR_MAX     __WCHAR_MAX
# endif

/* Limits of `wint_t'.  */
# define WINT_MIN       (0u)
# define WINT_MAX       (4294967295u)

#endif  /* C++ && limit macros */

/* The ISO C99 standard specifies that in C++ implementations these
   should only be defined if explicitly requested.  */
#if !defined __cplusplus || defined __STDC_CONSTANT_MACROS

/* Signed.  */
#define INT8_C(c)  c
#define INT16_C(c) c
#define INT32_C(c) c
#define INT64_C(c) c ## LL

/* Unsigned.  */
#define UINT8_C(c)    c ## U
#define UINT16_C(c)   c ## U
#define UINT32_C(c)   c ## U
#define UINT64_C(c)   c ## ULL

/* Maximal type.  */
#define INTMAX_C(c)   c ## LL
#define UINTMAX_C(c)  c ## ULL

#endif  /* C++ && constant macros */

  /* /////////////////////////////////////////////////////////////////////// */
  #endif /* __NATIVE_32_BIT__ */
#endif /* _STDINT_H_ */
/*****************************************************************************
 * $Log:
 *  2    Biblioteka1.1         10/01/2003 9:51:34 PMDarko Kolakovic conditional
 *       long long
 *  1    Biblioteka1.0         08/01/2003 3:26:29 PMDarko Kolakovic
 * $
 *****************************************************************************/
