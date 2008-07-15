/*$RCSfile: build_.h,v $: header file
  $Revision: 1.4 $ $Date: 2008/07/15 20:37:10 $
  $Author: ddarko $

  This source code is only intended as a supplement to the Active Template Library
  Reference and related electronic documentation provided with the library.
  See these sources for detailed information regarding the  Active Template
  Library product.
  This is a part of the Active Template Library.
  Copyright: (C) 1996-1998 Microsoft Corporation. All rights reserved.
  PSDK 2006-03 (R2 3790.2075) Win DDK 2005-03 (3790.1830)
 */
// Group=Windows
#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #ifdef _MSC_VER
    //Microsoft Visual C/C++ compiler
    #pragma message ("   #include " __FILE__ )
  #endif
#endif

// ATL Julian date build numbers (YDDD)
#define _ATL_BUILD 4245
#define _ATL_USER_BUILD "4245 bcc"
#define _ATL_PRODUCT_VERSION 6,0,0,4245
#define _ATL_FILE_VERSION 3,00
#define _ATL_USER_PRODVER "6.00.4245"
#define _ATL_USER_FILEVER "3.00.4245.001"
////////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: build_.h,v $
 * Revision 1.4  2008/07/15 20:37:10  ddarko
 * Borland CC build and fixes
 *
 * Revision 1.1.2.2  2008/07/15 15:42:57  ddarko
 * ATL 3.00 Platform SDK (R2 3790.2075) 2006-03 / Borland CC build
 *
 *****************************************************************************/
