/*$Workfile: KTypedef.h$: header file
  $Revision: 31$ $Date: 2004-11-23 15:50:37$
  $Author: Darko Kolakovic$

  Type definitions
  Copyright: CommonSoft Inc
  Feb 95 Darko Kolakovic
 */

#ifndef _KTYPEDEF_H_
  /*$Workfile: KTypedef.h$ sentry*/
  #define _KTYPEDEF_H_

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

/*---------------------------------------------------------------------------*/
/*C compiler Boolean type                                                    */
#ifndef __cplusplus
  #ifdef __STDC__
    //ANSI C conformance (C99)
    #include <stdbool.h> //_Bool, bool typedef
  #else /*!__STDC__ */

    /*Boolean type and values*/
    #ifndef _Bool
      /*Booleans are used to denote the result of a logical operation.
        A boolean can be either true or false.
        Named after Boole, George (1815-1864), a British mathematician and
        logician who developed Boolean algebra.
        Included for alignment with the ISO/IEC 9899:1999 (ISO C99) standard.
        */
      typedef int _Bool;
      #define _Bool _Bool
    #endif

    #ifndef bool
      #define bool _Bool
    #endif
    #ifndef true
        /*Boolean true is one of the two values that a Boolean can have. */
      #define true 1
    #endif
    #ifndef false
        /*Boolean false is one of the two values that a Boolean can have.*/
      #define false 0
    #endif

    #if !(__bool_true_false_are_defined)
      #ifdef bool
        /*Included for alignment with the ISO/IEC 9899:1999 (ISO C99) standard*/
        #define __bool_true_false_are_defined        1
      #endif
    #endif /*__bool_true_false_are_defined*/

  #endif /*__STDC__ */
/*---------------------------------------------------------------------------*/
/*C++ compiler Boolean type                                                  */
#else /*__cplusplus*/

  #if defined (_MSC_VER) /*Microsoft VisualStudio C++ compiler*/
    #if !defined (__bool_true_false_are_defined)
      /*The bool keyword is a built-in type. 
        Note: In Visual C++ 4.2, the Standard C++ header files contained 
        a typedef that equated bool with int. In Visual C++ 5.0 and later, 
        bool is implemented as a built-in type with a size of 1 byte. 
        That means that for Visual C++ 4.2, a call of sizeof(bool) yields 4,
        while in Visual C++ 5.0 and later, the same call yields 1. 
        This can cause memory corruption problems if you have defined structure
        members of type bool in Visual C++ 4.2 and are mixing object files 
        (OBJ) and/or DLLs built with the 4.2 and 5.0 or later compilers. 
       */
      #define bool bool
      #define true true
      #define false false
    #endif
  #endif /*_MSC_VER*/

  #if defined (__MWERKS__) /*MetroWerks CodeWarrior C++ compiler*/
    /*ISO C++ Standard bool data type is enabled.*/
    #if __option(bool)
      #define bool bool
      #define __bool_true_false_are_defined         1
    #endif
  #endif /*__MWERKS__*/

  #if !defined (__bool_true_false_are_defined) || (__bool_true_false_are_defined == 0)
    #ifndef bool
      typedef unsigned int bool;
      #define bool bool
    #endif
    #ifndef true
      #define false static_cast<bool>(0)
      #define true  static_cast<bool>(1)
      #define true true
      #define false false
      #define __bool_true_false_are_defined         1
    #endif   /* true */
  #endif /*__bool_true_false_are_defined*/

#endif /*__cplusplus*/
/*---------------------------------------------------------------------------*/


#ifndef WIDECHAR
  #define _WIDECHAR_(x) L ## x
  /*Specify a wide-character string literal (wchar_t[])

    Example:

      wchar_t wszStr[] = L"wide-character literal";
      const wchar_t *pwsz = WIDECHAR("wide-character literal");
   */
  #define WIDECHAR(x) _WIDECHAR_(x)
#endif /*WIDECHAR*/
#ifndef __WFILE__
    /*Wide string version of __FILE__
     */
  #define __WFILE__ WIDECHAR(__FILE__)
#endif /*__WFILE__*/



#if ( defined(_DOS) || defined(WIN) )
  #if _MSC_VER <= 850 /*Microsoft Visual C/C++ 1.52 or less            */
    /* /////////////////////////////////////////////////////////////////////// */
    /* // MS Windows 16-bit, DOS 16-bit                                        */
    #ifndef __NATIVE_16_BIT__
      #define __NATIVE_16_BIT__ 16
    #endif
      /*For C compiler bool is already defined*/
    #ifdef __cplusplus
      #ifndef bool
      /*Booleans are used to denote the result of a logical operation.
        A boolean can be either true or false.
        Named after Boole, George (1815-1864), a British mathematician and
        logician who developed Boolean algebra.
        */
        class bool
        {
        public:
          bool();
          bool(const int iValue);
        private
          int m_iValue;
        public:
          operator int() const;
          int operator!() const;
        };

        inline bool::bool()
        {
        }
        inline bool::bool(const int iValue)
        {
        m_iValue = (iValue > 0) ? 1 : 0;
        }
        inline bool::operator int() const
        {
        return m_iValue;
        }
        inline int bool::operator!() const
        {
        return !m_iValue;
        }
        #define bool bool
          /*Boolean true is one of the two values that a Boolean can have. */
        const bool true = 1;
        #define true true
          /*Boolean false is one of the two values that a Boolean can have.*/
        const bool false = 0;
        #define false false
      #endif //~bool
    #endif /* __cplusplus*/
  #endif /*Microsoft Visual C/C++ 1.52 or less            */
#endif /* _DOS || WIN */

#ifdef _WIN32            /*32-bit Windows OS                                 */

  /* /////////////////////////////////////////////////////////////////////// */
  /* // MS Windows 32-bit                                                    */
  #ifdef _MSC_VER        /*Microsoft Visual Studio C/C++ compiler            */
    #ifndef __NATIVE_32_BIT__
      #define __NATIVE_32_BIT__ 32
    #endif
    #include "KType32.h" /*ISO C99: 7.18 Integer types included              */

    #ifndef __KMS_WTYPES_H__
         /*Included wtypes.h header                                          */
      #define __KMS_WTYPES_H__ 1
      #ifdef _DEBUG_INCL_PREPROCESS  /*Preprocessor: debugging included files*/
        #pragma message ("   #include <wtypes.h>")
      #endif
      #include <wtypes.h> /*Microsoft Windows type definitions               */
    #endif /*__KMS_WTYPES_H__*/

    #ifndef int64
      /*Declares 64-bit integer                                              */
      #define int64 __int64
    #endif

    #ifndef uint64
      /*A 64-bit unsigned integer                                            */
      typedef unsigned int64 uint64;
      #define uint64 uint64
    #endif

    #ifndef UINT64
      /*A 64-bit unsigned integer                                            */
      #define UINT64 uint64
    #endif

  #endif /*_MSC_VER                                                          */
#else  /*!_WIN32  */

  /* /////////////////////////////////////////////////////////////////////// */
  /* // VxWorks 32-bit                                                       */

  #ifdef VXWORKS /*32-bit VxWorks OS */
    #include <vxTypesOld.h> /*BOOL typedef */
    #if (CPU_FAMILY==ARM)
      #define __NATIVE_32_BIT__ CPU_FAMILY
    #elif (CPU_FAMILY==SIMNT)
      #define __NATIVE_32_BIT__ CPU_FAMILY
    #else
      #error Not a 32-bit system, update stdint.h
    #endif
  #endif

  /* /////////////////////////////////////////////////////////////////////// */
  /* // PalmOS 32-bit                                                        */
  #if defined(__PALMOS__) || defined (__PALMTYPES_H__) || defined (__PALMOS_H__)
    #include "Palm/KTypedefPalm.h"
  #endif

  #ifndef __KTYPEDEF_H__
  /*KTypedef.h sentry<BR>
    A <B>typedef</B> declaration introduces a name that, within its scope,
    becomes a synonym for the type given by the decl-specifiers portion of the
    declaration. In contrast to the class, struct, union, and enum declarations,
    <B>typedef</B> declarations do not introduce new types — they introduce new
    names for existing types.
   */
    #define __KTYPEDEF_H__

  #include "KTChar.h"  /*TCHAR typedef */

  #ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files   */
    #ifdef _MSC_VER
      #pragma message ("   #include " __FILE__ )
    #endif
    #ifdef __GNUC__
      #warning "  #include KTypedef.h"
    #endif
  #endif

  /* /////////////////////////////////////////////////////////////////////// */
  /* Macros                                                                  */

  #ifndef TRUE
     /*Boolean <B>true</B> is one of the two values that a Boolean can have. */
    #define TRUE 1
  #endif
  #ifndef FALSE
     /*Boolean <B>false</B> is one of the two values that a Boolean can have.*/
    #define FALSE 0
  #endif
  #ifndef NULL
       /*null pointer                                                        */
    #define NULL 0
  #endif

  /* /////////////////////////////////////////////////////////////////////// */
  /* Type definitions                                                        */
  #if defined (HAS_BOOL)
    #define BOOL BOOL      /*GNU code has typedef int BOOL                   */
    #pragma message ("HAS_BOOL")
  #endif

  #ifndef __INCvxTypesOldh /*WindRiver's VxWorks */

    #ifndef UINT
      /*An unsigned integer                                                  */
      typedef unsigned int UINT;
    #endif

  #else
    #define BOOL BOOL      /*VxWorks has typedef int BOOL in vxTypesOld.h    */
  #endif /*__INCvxTypesOldh*/

  #ifdef __INCntcontexth /**WindRiver's WxWorks simulator */
    /*VxWorks has typedef char BYTE, WORD, ... in ntcontext.h     */
    #define BYTE BYTE
    #define WORD WORD
    #define DWORD DWORD
  #endif

  #ifndef BOOL
    #ifndef __cplusplus
      /*Boolean data type containing a truth value. The two possible values
        of a boolean variable are TRUE (!= 0) and FALSE (== 0).              */
      typedef int  BOOL;
    #else
      typedef bool BOOL;
    #endif
    #define BOOL BOOL
  #endif /*BOOL*/

  #ifndef UINT64
    /*VxWorks, DOS, PalmOS have not int64*/
    #if !defined(VXWORKS) && !defined(_DOS) && !(_PALMOS)
        /*A 64-bit unsigned integer                                          */
      typedef unsigned int64 UINT64;
      #ifndef uint64
       #define uint64 UINT64
      #endif
    #endif /*VXWORKS */
  #endif

  #ifndef BYTE
    /*An 8-bit unsigned integer                                            */
    typedef unsigned char BYTE;
    #define BYTE BYTE
  #endif

  #ifndef WORD
    /*A 16-bit unsigned integer                                            */
    typedef unsigned short WORD;
    #define WORD WORD
  #endif

  #ifndef DWORD
    /*A 32-bit unsigned integer                                            */
    typedef unsigned long DWORD;
    #define DWORD DWORD
  #endif

  #ifndef LPCSTR
      /*A 32-bit pointer to a constant character string.                     */
    typedef const char* LPCSTR;
    #define LPCSTR LPCSTR
  #endif

  #ifndef LPSTR
      /*A 32-bit pointer to a character string.                              */
    typedef char* LPSTR;
    #define LPSTR LPSTR
  #endif

  #ifndef LPCTSTR
     /*A 32-bit pointer to a constant character string that is portable for
       Unicode and DBCS.                                                    */
    typedef const TCHAR*   LPCTSTR;
    #define LPCTSTR LPCTSTR
  #endif

  #ifndef LPTSTR
    /*A 32-bit pointer to a character string that is portable for
      Unicode and DBCS.                                                    */
    typedef TCHAR*   LPTSTR;
    #define LPTSTR LPTSTR
  #endif

    /*Define __cdecl for non-Microsoft compilers                             */
  #if ( !defined(_MSC_VER) && !defined(__cdecl) )
    #define __cdecl
  #endif

  /* /////////////////////////////////////////////////////////////////////// */
  #endif  /*__KTYPEDEF_H__                                                   */
/* ///////////////////////////////////////////////////////////////////////// */
#endif  /*!_WIN32 */


/* ========================================================================= */
#ifdef __NATIVE_64_BIT__    /*  EDM 96/05/30; Digital UNIX+Alpha             */
  #undef __NATIVE_32_BIT__
  #undef __NATIVE_16_BIT__

    /*Converts a constant to signed 64-bit integer                           */
  #define __INT64_T__(x)  x ## L
    /*Converts a constant to unsigned 64-bit integer                         */
  #define __UINT64_T__(x) x ## UL

  #ifndef int8
      /*signed 8-bit integer                                                 */
    typedef signed char          int8;
    #define  int8  int8
  #endif
  #ifndef uint8
      /*unsigned 8-bit integer                                               */
    typedef unsigned char       uint8;
    #define  uint8   uint8
  #endif
  #ifndef int16
      /*signed 16-bit integer                                                */
    typedef signed short        int16;
    #define  int16   int16
  #endif
  #ifndef uint16
      /*unsigned 16-bit integer                                              */
    typedef unsigned short     uint16;
    #define  uint16  uint16
  #endif


  #ifndef int32
      /*signed 32-bit integer                                                */
    typedef signed int           int32;
    #define  int32   int32
  #endif
  #ifndef uint32
      /*unsigned 32-bit integer                                              */
  typedef unsigned int        uint32;
    #define  uint32  uint32
  #endif
  #ifndef int64
      /*signed 64-bit integer                                                */
    typedef signed long          int64;
    #define  int64   int64
  #endif
  #ifndef uint64
      /*unsigned 64-bit integer                                              */
  typedef unsigned long       uint64;
    #define  uint64  uint64
  #endif

#endif /*__NATIVE_64_BIT__*/

/* ========================================================================= */
#ifdef __NATIVE_32_BIT__
  #undef __NATIVE_64_BIT__
  #undef __NATIVE_16_BIT__

    /*Converts a constant to signed 64-bit integer                           */
  #define __INT64_T__(x)  x ## LL
    /*Converts a constant to unsigned 64-bit integer                         */
  #define __UINT64_T__(x) x ## ULL

  #ifndef int8
      /*signed 8-bit integer                                                 */
    typedef signed char          int8;
    #define  int8  int8
  #endif
  #ifndef uint8
      /*unsigned 8-bit integer                                               */
    typedef unsigned char       uint8;
    #define  uint8   uint8
  #endif
  #ifndef int16
      /*signed 16-bit integer                                                */
    typedef signed short        int16;
    #define  int16   int16
  #endif
  #ifndef uint16
      /*unsigned 16-bit integer                                              */
    typedef unsigned short     uint16;
    #define  uint16  uint16
  #endif


  #ifndef int32
      /*signed 32-bit integer                                                */
    typedef signed long          int32;
    #define  int32   int32
  #endif
  #ifndef uint32
      /*unsigned 32-bit integer                                              */
    typedef unsigned long       uint32;
    #define  uint32  uint32
  #endif

  typedef float               real32;
  typedef double              real64;
#endif /*__NATIVE_32_BIT__*/

#ifdef __GNUC__
  typedef   signed long long   int64;
  typedef unsigned long long  uint64;
#endif

/* ========================================================================= */
#ifdef __NATIVE_16_BIT__ /* Win3.1, MS-DOS, BD211*/
  #undef __NATIVE_64_BIT__
  #undef __NATIVE_32_BIT__

  #ifndef int8
      /*signed 8-bit integer                                                 */
    typedef signed char          int8;
    #define  int8  int8
  #endif
  #ifndef uint8
      /*unsigned 8-bit integer                                               */
    typedef unsigned char       uint8;
    #define  uint8   uint8
  #endif
  #ifndef int16
      /*signed 16-bit integer                                                */
    typedef signed int        int16;
    #define  int16   int16
  #endif
  #ifndef uint16
      /*unsigned 16-bit integer                                              */
    typedef unsigned int     uint16;
    #define  uint16  uint16
  #endif

  #ifndef int32
      /*signed 32-bit integer                                                */
    typedef signed long          int32;
    #define  int32   int32
  #endif
  #ifndef uint32
      /*unsigned 32-bit integer                                              */
    typedef unsigned long       uint32;
    #define  uint32  uint32
  #endif

  #ifndef bool
    typedef int bool;
    #define bool bool
  #endif
  #ifndef true
    #define true 1
  #endif
  #ifndef false
    #define false 0
  #endif

#endif /*__NATIVE_16_BIT__*/


/* ///////////////////////////////////////////////////////////////////////// */
/* // Common definitions                                                     */

/*The data type constants listed below give the ranges for the integral data
  types.
 */

#ifndef INT8_MAX
    /*Maximum value of 8-bit integer is 0x7F (127)                           */
  #define INT8_MAX  0x7F /*127 */
#endif
#ifndef INT8_MIN
    /*Minimum value of 8-bit integer is -128                                 */
  #define INT8_MIN  (- INT8_MAX - 1)
#endif
#ifndef UINT8_MAX
    /*Maximum value of 8-bit unsigned integer is 0xFF (255)                  */
  #define UINT8_MAX (2U * INT8_MAX + 1)
#endif
#ifndef UINT8_MIN
    /*Minimum value of 8-bit unsigned integer is 0                           */
  #define UINT8_MIN 0
#endif



#ifndef INT16_MAX
    /*Maximum value of 16-bit integer is 0x7FFF (32 767)                     */
  #define INT16_MAX 0x7FFF  /*32767 */
#endif
#ifndef INT16_MIN
    /*Minimum value of 16-bit integer is –32 768                             */
  #define INT16_MIN (- INT16_MAX - 1)
#endif
#ifndef UINT16_MAX
    /*Maximum value of 16-bit unsigned integer is 0xFFFF (65 535)            */
  #define UINT16_MAX  (2U * INT16_MAX + 1)
#endif
#ifndef UINT16_MIN
    /*Minimum value of 16-bit unsigned integer is 0                          */
  #define UINT16_MIN  0
#endif


#ifndef INT32_MAX
    /*Maximum value of 32-bit integer is 0x7FFF FFFF (2 147 483 647)         */
  #define INT32_MAX 0x7FFFFFFF  /*2 147 483 647*/
#endif
#ifndef INT32_MIN
    /*Minimum value of 32-bit integer is –2 147 483 648                      */
  #define INT32_MIN (- INT32_MAX - 1)
#endif
#ifndef UINT32_MAX
    /*Maximum value of 32-bit unsigned integer is 0xFFFF FFFF (4 294 967 295)*/
  #define UINT32_MAX  (2U * INT32_MAX + 1)
#endif
#ifndef UINT32_MIN
    /*Minimum value of 32-bit unsigned integer is 0                          */
  #define UINT32_MIN  0
#endif


#ifndef INT64_MAX
    /*Maximum value of 64-bit integer is 0x7FFF FFFF FFFF FFFF (9 223 372 036 854 775 807)*/
  #define INT64_MAX __INT64_T__(0x7FFFFFFFFFFFFFFF)  /*9 223 372 036 854 775 807*/
#endif
#ifndef INT64_MIN
    /*Minimum value of 64-bit integer is –9 223 372 036 854 775 808          */
  #define INT64_MIN (- INT64_MAX - 1)
#endif
#ifndef UINT64_MAX
    /*Maximum value of 64-bit unsigned integer is 0xFFFF FFFF FFFF FFFF (18 446 744 073 709 551 615)*/
  #define UINT64_MAX  (__UINT64_C(2) * INT64_MAX + 1)
#endif
#ifndef UINT64_MIN
    /*Minimum value of 64-bit unsigned integer is 0                          */
  #define UINT64_MIN  0
#endif


#ifdef _MSC_VER        /*Microsoft Visual Studio C/C++ compiler              */
  #include <limits.h>  /*Ranges for the integral data types used by MS VC++  */
#endif
#ifdef __MWERKS__      /*Metrowerks CodeWarrior C/C++ compiler               */
  #include <limits.h>  /*Ranges for the integral data types used by MW CW    */
#endif

  /*Check compiler data type sizes                                           */
#if (UCHAR_MAX != 0xFF)
  #error "Change definition of 'BYTE'1"
#endif
#if (USHRT_MAX != 0xFFFFU)
  #error "Change definition of 'WORD'!"
#endif

#ifdef __NATIVE_64_BIT__
  #if (UINT_MAX != 0xFFFFFFFFU)
   #error "Change definition of 'DWORD'1"
  #endif
#else
  /*Native 32-bit or less */
  #if (ULONG_MAX != 0xFFFFFFFFUL)
    #error "Change definition of 'DWORD'!"
  #endif
#endif

/* ///////////////////////////////////////////////////////////////////////// */
#endif /*_KTYPEDEF_H_*/
/*****************************************************************************
 * $Log:
 *  24   Biblioteka1.23        07/07/2004 5:50:00 PMDarko           sentry
 *  23   Biblioteka1.22        23/09/2003 5:11:22 PMDarko           bool class
 *  22   Biblioteka1.21        22/09/2003 10:27:25 PMDarko           formatting
 *  21   Biblioteka1.20        21/08/2003 3:16:50 PMDarko           UNSUSED moved
 *       to KPrgmCst.inl
 *  20   Biblioteka1.19        14/08/2003 5:12:10 AMDarko
 *  19   Biblioteka1.18        14/08/2003 5:07:52 AMDarko           _MESSAGE0
 *       renamed
 *  18   Biblioteka1.17        10/01/2003 10:51:40 PMDarko Kolakovic conditional
 *       long long
 *  17   Biblioteka1.16        08/01/2003 4:31:56 PMDarko Kolakovic Added C99
 *       stdint.h
 *  16   Biblioteka1.15        10/10/2002 8:36:00 PMDarko Kolakovic Fixed 16-bit
 *       version
 *  15   Biblioteka1.14        18/09/2002 6:14:14 PMDarko Kolakovic uint8 fixed
 *  14   Biblioteka1.13        19/08/2002 10:37:20 AMDarko Kolakovic
 *  13   Biblioteka1.12        13/08/2002 6:52:38 PMDarko Kolakovic
 *  12   Biblioteka1.11        29/07/2002 12:47:16 AMDarko           Inserted data
 *       type limits
 *  11   Biblioteka1.10        19/07/2002 1:54:29 AMDarko           typedef uint32
 *  10   Biblioteka1.9         18/07/2002 9:59:50 PMDarko Kolakovic Added compiler
 *       data type validation
 *  9    Biblioteka1.8         08/03/2002 11:27:26 AMDarko Kolakovic added notes
 *  8    Biblioteka1.7         12/02/2002 5:42:40 PMDarko           GNU issues
 *  7    Biblioteka1.6         12/02/2002 10:56:09 AMDarko           GNU and
 *       VxWorks issues
 *  6    Biblioteka1.5         04/02/2002 6:37:08 PMDarko
 *  5    Biblioteka1.4         03/02/2002 6:07:54 PMDarko           int64
 *  4    Biblioteka1.3         24/01/2002 7:22:25 PMDarko           Updated
 *       comments
 *  3    Biblioteka1.2         23/12/2001 1:25:57 AMDarko           UINT
 *  2    Biblioteka1.1         05/11/2001 3:38:29 PMDarko           VSS tags
 *  1    Biblioteka1.0         19/08/2001 11:37:07 PMDarko
 * $
 *  0 Created   Feb 95 Darko Kolakovic
 *****************************************************************************/
