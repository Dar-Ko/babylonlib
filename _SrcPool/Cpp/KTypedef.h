/*$Workfile: KTypedef.h$: header file
  $Revision: 14$ $Date: 8/19/02 10:37:20 AM$
  $Author: Darko Kolakovic$

  Type definitions
  Copyright: CommonSoft Inc
  Feb 95 Darko Kolakovic
 */


#ifdef _WIN32            /*32-bit Windows OS                                 */

  /* /////////////////////////////////////////////////////////////////////// */
  /* // MS Windows 32-bit                                                    */
  #ifdef _MSC_VER        /*Microsoft Visual Studio C/C++ compiler            */
    #ifndef __KMS_WTYPES_H__
         /*Included wtypes.h header                                          */
      #define __KMS_WTYPES_H__ 1
      #ifdef _DEBUG_INCL_PREPROCESS  /*Preprocessor: debugging included files*/
        #pragma message ("   #include <wtypes.h>")
      #endif
      #include <wtypes.h> /*Microsoft Windows type definitions               */
    #endif /*__KMS_WTYPES_H__*/

    #define __NATIVE_32_BIT__

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

    /*_MESSAGE preprocessor directive ---------------------------------------*/
    /*reserved: preprocessor needs two indirections to replace __LINE__ with
	  actual string                                                          */
    #define __MESSAGE0(Msg)     #Msg
    /*Preprocessor needs two indirections to replace __LINE__ or __FILE__ with
	  actual string.

	  Note: Microsoft Visual Studio (MSVC) specific.                         */
    #define _MESSAGE1(Msg)    __MESSAGE0(Msg)
    /*Adds the name of the source file and the line number where a preprocessor
      message has been inserted.

	  Note: Microsoft Visual Studio (MSVC) specific.

	  Example:
	     #pragma _MESSAGE(Your message)
	     Output:
	     C:\MyCode.cpp(111):Your message
	 */
    #define _MESSAGE(Msg)  message(__FILE__ "(" _MESSAGE1(__LINE__) "):" #Msg)

  #endif /*_MSC_VER                                                          */
#else  /*!_WIN32  */

  /* /////////////////////////////////////////////////////////////////////// */
  /* // VxWorks 32-bit                                                       */

  #ifdef VXWORKS /*32-bit VxWorks OS */
    #include <vxTypesOld.h> /*BOOL typedef */
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

  #define __NATIVE_32_BIT__

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
  #ifndef __INCvxTypesOldh /*VxWorks has typedef int BOOL in vxTypesOld.h    */
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

    #ifndef UINT
      /*An unsigned integer                                                  */
      typedef unsigned int UINT;
    #endif
  #endif /*__INCvxTypesOldh*/

  #ifndef UINT64
    #ifndef VXWORKS /*VxWorks has not int64*/
        /*A 64-bit unsigned integer                                          */
      typedef unsigned int64 UINT64;
      #ifndef uint64
       #define uint64 UINT64
      #endif
    #endif /*VXWORKS */
  #endif

  #ifndef __INCntcontexth /*VxWorks has typedef char BYTE in ntcontext.h     */

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

  #endif /*__INCntcontexth*/


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
  #define __INT64_T__(x)	x ## L
    /*Converts a constant to unsigned 64-bit integer                         */
  #define __UINT64_T__(x)	x ## UL

  #ifndef int8
      /*signed 8-bit integer                                                 */
    typedef signed char          int8;
    #define  int8	 int8
  #endif
  #ifndef int8
      /*unsigned 8-bit integer                                               */
    typedef unsigned char       uint8;
    #define  uint8	 uint8
  #endif
  #ifndef int16
      /*signed 16-bit integer                                                */
    typedef signed short        int16;
    #define  int16	 int16
  #endif
  #ifndef uint16
      /*unsigned 16-bit integer                                              */
    typedef unsigned short     uint16;
    #define  uint16	 uint16
  #endif


  #ifndef int32
      /*signed 32-bit integer                                                */
    typedef signed int           int32;
    #define  int32	 int32
  #endif
  #ifndef uint32
      /*unsigned 32-bit integer                                              */
  typedef unsigned int        uint32;
    #define  uint32	 uint32
  #endif
  #ifndef int64
      /*signed 64-bit integer                                                */
    typedef signed long          int64;
    #define  int64	 int64
  #endif
  #ifndef uint64
      /*unsigned 64-bit integer                                              */
  typedef unsigned long       uint64;
    #define  uint64	 uint64
  #endif

#endif /*__NATIVE_64_BIT__*/

/* ========================================================================= */
#ifdef __NATIVE_32_BIT__
  #undef __NATIVE_64_BIT__
  #undef __NATIVE_16_BIT__

    /*Converts a constant to signed 64-bit integer                           */
  #define __INT64_T__(x)	x ## LL
    /*Converts a constant to unsigned 64-bit integer                         */
  #define __UINT64_T__(x)	x ## ULL

  #ifndef int8
      /*signed 8-bit integer                                                 */
    typedef signed char          int8;
    #define  int8	 int8
  #endif
  #ifndef int8
      /*unsigned 8-bit integer                                               */
    typedef unsigned char       uint8;
    #define  uint8	 uint8
  #endif
  #ifndef int16
      /*signed 16-bit integer                                                */
    typedef signed short        int16;
    #define  int16	 int16
  #endif
  #ifndef uint16
      /*unsigned 16-bit integer                                              */
    typedef unsigned short     uint16;
    #define  uint16	 uint16
  #endif


  #ifndef int32
      /*signed 32-bit integer                                                */
    typedef signed long          int32;
    #define  int32	 int32
  #endif
  #ifndef uint32
      /*unsigned 32-bit integer                                              */
    typedef unsigned long       uint32;
    #define  uint32	 uint32
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
    #define  int8	 int8
  #endif
  #ifndef int8
      /*unsigned 8-bit integer                                               */
    typedef unsigned char       uint8;
    #define  uint8	 uint8
  #endif
  #ifndef int16
      /*signed 16-bit integer                                                */
    typedef signed int        int16;
    #define  int16	 int16
  #endif
  #ifndef uint16
      /*unsigned 16-bit integer                                              */
    typedef unsigned int     uint16;
    #define  uint16	 uint16
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
  #define INT8_MAX	0x7F /*127 */
#endif
#ifndef INT8_MIN
    /*Minimum value of 8-bit integer is -128                                 */
  #define INT8_MIN	(- INT8_MAX - 1)
#endif
#ifndef UINT8_MAX
    /*Maximum value of 8-bit unsigned integer is 0xFF (255)                  */
  #define UINT8_MAX	(2U * INT8_MAX + 1)
#endif
#ifndef UINT8_MIN
    /*Minimum value of 8-bit unsigned integer is 0                           */
  #define UINT8_MIN	0
#endif



#ifndef INT16_MAX
    /*Maximum value of 16-bit integer is 0x7FFF (32 767)                     */
  #define INT16_MAX	0x7FFF  /*32767 */
#endif
#ifndef INT16_MIN
    /*Minimum value of 16-bit integer is –32 768                             */
  #define INT16_MIN	(- INT16_MAX - 1)
#endif
#ifndef UINT16_MAX
    /*Maximum value of 16-bit unsigned integer is 0xFFFF (65 535)            */
  #define UINT16_MAX	(2U * INT16_MAX + 1)
#endif
#ifndef UINT16_MIN
    /*Minimum value of 16-bit unsigned integer is 0                          */
  #define UINT16_MIN	0
#endif


#ifndef INT32_MAX
    /*Maximum value of 32-bit integer is 0x7FFF FFFF (2 147 483 647)         */
  #define INT32_MAX	0x7FFFFFFF  /*2 147 483 647*/
#endif
#ifndef INT32_MIN
    /*Minimum value of 32-bit integer is –2 147 483 648                      */
  #define INT32_MIN	(- INT32_MAX - 1)
#endif
#ifndef UINT32_MAX
    /*Maximum value of 32-bit unsigned integer is 0xFFFF FFFF (4 294 967 295)*/
  #define UINT32_MAX	(2U * INT32_MAX + 1)
#endif
#ifndef UINT32_MIN
    /*Minimum value of 32-bit unsigned integer is 0                          */
  #define UINT32_MIN	0
#endif


#ifndef INT64_MAX
    /*Maximum value of 64-bit integer is 0x7FFF FFFF FFFF FFFF (9 223 372 036 854 775 807)*/
  #define INT64_MAX	__INT64_T__(0x7FFFFFFFFFFFFFFF)  /*9 223 372 036 854 775 807*/
#endif
#ifndef INT64_MIN
    /*Minimum value of 64-bit integer is –9 223 372 036 854 775 808          */
  #define INT64_MIN	(- INT64_MAX - 1)
#endif
#ifndef UINT64_MAX
    /*Maximum value of 64-bit unsigned integer is 0xFFFF FFFF FFFF FFFF (18 446 744 073 709 551 615)*/
  #define UINT64_MAX	(__UINT64_C(2) * INT64_MAX + 1)
#endif
#ifndef UINT64_MIN
    /*Minimum value of 64-bit unsigned integer is 0                          */
  #define UINT64_MIN	0
#endif


#ifdef _MSC_VER        /*Microsoft Visual Studio C/C++ compiler              */
  #include <limits.h>  /*Ranges for the integral data types used by MS VC++  */
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



#ifndef _UNUSED
  #define _UNUSED(x) ((void)x)
#endif

/*****************************************************************************
 * $Log:
 *  0 Created   Feb 95 Darko Kolakovic
 * $
 *****************************************************************************/
