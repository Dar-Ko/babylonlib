/*$RCSfile: KDbgMacrMfc.h,v $: header file
  $Revision: 1.2 $ $Date: 2008/09/18 18:30:19 $
  $Author: ddarko $

  Dumps values of some Microsoft specific predefined macros
  Copyright: CommonSoft Inc.
  Darko Kolakovic April 1988, 2008-07
*/
/* Group=Diagnostic                                                          */

#ifndef _KDBGMACRMFC_H_
    /*$RCSfile: KDbgMacrMfc.h,v $ sentry */
  #define _KDBGMACRMFC_H_

#ifdef _MSC_VER /*Microsoft Visual C/C++ Compiler pragmas                     */

  #if _MSC_VER > 1000
    #pragma once
  #endif // _MSC_VER > 1000

  #ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
    #pragma message ("   #include " __FILE__ )
  #endif

  /*Microsoft-Specific macros ---------------------------------------------- */
  #ifdef _AFX
    #pragma message ("Included Microsoft Application Framework Classes afxver_.h (AFX/MFC).")
  #endif
  #ifdef _MFC_VER
    #pragma message ("Included Microsoft Fundation Class (MFC) library.")
     /*Current version of Microsoft Fundation Class (MFC) library.
      */
    const int g__MFC_VER = _MFC_VER;
    #if _MFC_VER == 0x0320
      #pragma message ("  ver. 3.2")
      #define DBGMFC_VER 0x0320 /*Trace MFC version*/
    #endif
    #if _MFC_VER == 0x0400
      #pragma message ("  ver. 4.0")
      #define DBGMFC_VER 0x0400 /*Trace MFC version*/
    #endif
    #if _MFC_VER == 0x0410
      #pragma message ("  ver. 4.10")
      #define DBGMFC_VER 0x0410 /*Trace MFC version*/
    #endif
    #if _MFC_VER == 0x420
      #pragma message ("  ver. 4.20")
      #define DBGMFC_VER 0x0420 /*Trace MFC version*/
    #endif
    #if _MFC_VER == 0x0421
      #pragma message ("  ver. 4.21")
      #define DBGMFC_VER 0x0421 /*Trace MFC version*/
    #endif
    #if _MFC_VER == 0x0600
      #pragma message ("  ver. 6.00")
      #define DBGMFC_VER 0x0600 /*Trace MFC version*/
    #endif
    #if _MFC_VER == 0x0601
      #pragma message ("  ver. 6.01")
      #define DBGMFC_VER 0x0601 /*Trace MFC version*/
    #endif
    #if _MFC_VER == 0x0700
      #pragma message ("  ver. 7.00")
      #define DBGMFC_VER 0x0700 /*Trace MFC version*/
    #endif
    #if _MFC_VER == 0x0710
      #pragma message ("  ver. 7.10")
      #define DBGMFC_VER 0x0710 /*Trace MFC version*/
    #endif
    #if _MFC_VER == 0x0800
      #pragma message ("  ver. 8.00")
      #define DBGMFC_VER 0x0800 /*Trace MFC version*/
    #endif
    #ifndef DBGMFC_VER
      #pragma message ("  ver. unknown")
    #endif
  #endif

  #ifdef _AFXDLL
    #ifdef __cplusplus
      #pragma message ("Use MFC in a Shared DLL.")
    #else
      #pragma message (__FILE__ " : warning: Specified use of MFC in a C code.")
    #endif
  #endif


#endif /*_MSC_VER */

/* ///////////////////////////////////////////////////////////////////////// */
#endif /*_KDBGMACRMFC_H_                                                     */
/*****************************************************************************
 * $Log: KDbgMacrMfc.h,v $
 * Revision 1.2  2008/09/18 18:30:19  ddarko
 * Update patch
 *
 * Revision 1.1  2008/09/10 14:13:02  ddarko
 * Moved AFX macro dumps
 *
 *****************************************************************************/
