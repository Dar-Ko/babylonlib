/*$Workfile: KDbgMacrAtl.h$: header file
  $Revision: 1.3 $ $Date: 2008/09/09 18:18:48 $
  $Author: dkolakovic $

  Dumps values of some Microsoft specific predefined macros
  Copyright: CommonSoft Inc.
  Darko Kolakovic April 1988, 2008-07
*/
/* Group=Diagnostic                                                          */

#ifndef _KDBGMACRATL_H_
    /*$Workfile: KDbgMacrAtl.h$ sentry */
  #define _KDBGMACRATL_H_

#ifdef _MSC_VER /*Microsoft Visual C/C++ Compiler pragmas                     */

  #if _MSC_VER > 1000
    #pragma once
  #endif // _MSC_VER > 1000

  #ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
    #pragma message ("   #include " __FILE__ )
  #endif


  /*List Microsoft  Active Template Library macros*/
  #ifdef _ATL
    #pragma message ("Included Active Template Library atldef.h (ATL).")
  #endif
  #ifdef _ATL_VER
    #ifdef __cplusplus
      #pragma message ("Included Active Template Library (ATL).")
    #else
      #pragma message (__FILE__ " : warning: Specified use of ATL in a C code.")
    #endif

     /*Current version of Active Template Library (ATL).
       See also: atldef.h
      */
    const int g__ATL_VER = _ATL_VER;
    #if _ATL_VER == 0x0100 /*Active Template Library version 1.0*/
      #pragma message ("  ver. 1.00")
      #define DBGATL_VER 0x0100 /*Trace ATL version*/
    #endif
    #if _ATL_VER == 0x0200 /*Active Template Library version 2.0*/
      #pragma message ("  ver. 2.00")
      #define DBGATL_VER 0x0200 /*Trace ATL version*/
    #endif
    #if _ATL_VER == 0x0300 /*Active Template Library version 3.0*/
      #pragma message ("  ver. 3.00")
      #define DBGATL_VER 0x0300 /*Trace ATL version*/
    #endif
    #if _ATL_VER == 0x0301 /*Active Template Library version 3.0 Win64 build*/
      #pragma message ("  ver. 3.00/64-bit")
      #define DBGATL_VER 0x0301 /*Trace ATL version*/
    #endif
    #if _ATL_VER == 0x0700
      #pragma message ("  ver. 7.00")
      #define DBGATL_VER 0x0700 /*Trace ATL version*/
    #endif
    #if _ATL_VER == 0x0710
      #pragma message ("  ver. 7.10")
      #define DBGATL_VER 0x0710 /*Trace ATL version*/
    #endif
    #if _ATL_VER == 0x0800
      #pragma message ("  ver. 8.00")
      #define DBGATL_VER 0x0800 /*Trace ATL version*/
    #endif
    #ifndef DBGATL_VER
      #pragma message ("  ver. unknown")
    #endif
  #endif

  #ifdef _ATL_DLL
    #pragma message ("Dynamic Link to ATL.")
  #endif
  #ifdef _ATL_STATIC_REGISTRY
    #pragma message ("Static Link to ATL.")
  #endif

  #ifdef _ATL_SINGLE_THREADED
    #pragma message ("ATL Single-threaded.")
  #endif

  #ifdef _ATL_APARTMENT_THREADED
    #pragma message ("ATL Apartment-threaded.")
  #endif

  #ifdef _ATL_FREE_THREADED
    #pragma message ("ATL Free-threaded.")
  #endif

#endif /*_MSC_VER */

/* ///////////////////////////////////////////////////////////////////////// */
#endif /*_KDBGMACRATL_H_                                                     */
/*****************************************************************************
 * $Log: KDbgMacrAtl.h,v $
 *****************************************************************************/

