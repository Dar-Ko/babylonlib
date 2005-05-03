/*$Workfile: S:\_SrcPool\Cpp\Win\32\KDbgDump.h$: header file
  $Revision: 3$ $Date: 2005-04-28 18:11:47$
  $Author: Darko Kolakovic$

  Dumps values of some Windows-specific IDs
  Copyright: CommonSoft Inc.
  Darko Kolakovic April 1988
*/
/* Group=Diagnostic                                                          */

#ifndef __KDBGDUMP_H__
    /*$Workfile: S:\_SrcPool\Cpp\Win\32\KDbgDump.h$ sentry*/
  #define __KDBGDUMP_H__

#if _MSC_VER > 1000
  #pragma once
#endif // _MSC_VER > 1000

#if _MFC_VER == 0x600
  #pragma message ( "MFC version 4.2")
#endif

/* ///////////////////////////////////////////////////////////////////////// */
/* // Debug version                                                          */
#ifdef _DEBUG

  #ifndef _AFX_NO_OLE_SUPPORT
    #include <ShlObj.h>      // for IFileViewer
    void DumpREFIID(CDumpContext& dc, REFIID iid);
    void DumpGUID(CDumpContext& dc, const GUID GuID);
    void DumpFVSHOWINFO(LPFVSHOWINFO lpfvSI);
  #endif

/* ///////////////////////////////////////////////////////////////////////// */
/* // Release version                                                        */
#else

  #ifndef _AFX_NO_OLE_SUPPORT
    #define DumpREFIID(dc,iid)          ((void)0,(void)0)
    #define DumpGUID(dc,GuID)           ((void)0,(void)0)
    #define DumpFVSHOWINFO(lpfvSI)      ((void)0)
  #endif

#endif
/* ///////////////////////////////////////////////////////////////////////// */
#endif /*__KDBGDUMP_H__                                                      */
/******************************************************************************
 * $Log:
 *  2    Biblioteka1.1         2003-08-06 14:45:46  Darko           Updated comment
 *  1    Biblioteka1.0         2002-08-27 23:33:56  Darko
 * $
 *****************************************************************************/

