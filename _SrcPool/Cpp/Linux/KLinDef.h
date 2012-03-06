/*$RCSfile: KLinDef.h,v $: header file
  $Revision: 1.1 $ $Date: 2012/03/06 20:20:15 $
  $Author: ddarko $

  Constants used in conjuncture with Linux environment
  Copyright: D. Kolakovic
  2012-03-06
 */

#ifndef __KLINDEF_H__
  /*$RCSfile: KLinDef.h,v $ sentry */
  #define __KLINDEF_H__

  #ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files*/
    #warning ("   #include " __FILE__ )
  #endif

  #ifndef _KLINUX
    #if defined(linux) || defined(__linux) || defined(__linux__)
      /*Defined when target is Linux OS family. */
      #define _KLINUX  20120306
    #endif
  #endif  /*_KLINUX*/

#ifdef __cplusplus
extern "C"
{
#endif
//TODO: move to generic wdefs.h file
typedef float                 FLOAT;
typedef float*               PFLOAT;

#ifndef __int64
  typedef long long __int64;       // uint64_t
  #define __int64 __int64
#endif

typedef unsigned long         ULONG;
typedef unsigned long*       PULONG;
#ifndef DWORD
  typedef uint32_t            DWORD;
  #define DWORD DWORD
#endif
typedef uint32_t*            PDWORD;
typedef uint32_t*           LPDWORD;

typedef long*                LPLONG;

typedef unsigned int           UINT;
typedef unsigned int*          PUINT;

typedef int                     INT;
typedef int*                   PINT;
typedef int*                  LPINT;

typedef unsigned short       USHORT;
typedef unsigned short*     PUSHORT;
#ifndef WORD
typedef uint16_t               WORD;
  #define WORD WORD
#endif
typedef uint16_t*             PWORD;
typedef uint16_t*            LPWORD;

typedef uint8_t               UCHAR;
typedef uint8_t*             LPBYTE;
typedef uint8_t*             PUCHAR;
#ifndef BYTE
  typedef uint8_t              BYTE;
  #define BYTE BYTE
#endif
typedef uint8_t*              PBYTE;
typedef char*                   PSZ;
#ifndef LPSTR
  typedef char*               LPSTR;
  #define LPSTR LPSTR
#endif
#ifndef LPCSTR
  typedef const char*        LPCSTR;
  #define LPCSTR LPCSTR
#endif


#ifndef BOOL
  /*Boolean variable (TRUE or FALSE). */
  typedef int                  BOOL;
  #define BOOL BOOL
#endif

typedef int*                  PBOOL;
typedef int*                 LPBOOL;

typedef void*                LPVOID;
typedef const void*         LPCVOID;

/*Polymorphic Types */
typedef unsigned int*         WPARAM;
typedef unsigned long*        LPARAM;
typedef unsigned long*       LRESULT;

#define CALLBACK   /*Calling convention for callback functions. */
typedef int (CALLBACK *PROC)();

typedef uint32_t            COLORREF;
typedef uint32_t*         LPCOLORREF;

typedef int                    HFILE;

#ifndef HANDLE
  typedef int                 HANDLE;              // int32_f
  #define HANDLE HANDLE
#endif

#ifndef HINSTANCE
  typedef void*            HINSTANCE;
  #define HINSTANCE HINSTANCE
#endif

#ifndef HMODULE
  typedef void*              HMODULE;
  #define HMODULE HMODULE
#endif

#ifdef __cplusplus
}
#endif
/* ///////////////////////////////////////////////////////////////////////// */
#endif  /*__KLINDEF_H__*/
/*****************************************************************************
 * $Log: KLinDef.h,v $
 * Revision 1.1  2012/03/06 20:20:15  ddarko
 * Created
 *
 *****************************************************************************/
