/*$Workfile: KDbgErrorLz.c$: implementation file
  $Revision: 1$ $Date: 2004-11-09 19:42:14$
  $Author: Darko Kolakovic$

  Dumps error code values
  Copyright: CommonSoft Inc.
  2004-11-01 Darko Kolakovic
 */

/* Group=Diagnostic */

#include <PalmOS.h>
#include <Lz77Mgr.h>

#ifndef TRACE1
  #include "KTrace.h"
#endif

void DbgErrorLz(const Err nErrorCode);

/*----------------------------------------------------------------------------*/
/*Dump LZ77 Compression Library error codes.
  Range of error codes is
   [lz77ErrorClass = lz77ErrNonFatalFirstErr = 0x2700, smsErrorClass = 0x2800).

  See also: Palm OS Programmer's API Reference: Appendix D. Palm OS Error Codes

  Note: Palm OS specific (PalmOS).
 */
void DbgErrorLz(const Err nErrorCode //[in] error code
               )
{
    /*Dump most of the LZ77 Compression Library error codes used
      by the Palm OS
     */
switch (nErrorCode)
  {
  case errNone:                              TRACE0(_T("errNone")        ); break;/*0x0000 No error*/
  case lz77ErrNonFatalFirstErr:              TRACE0(_T("lz77ErrNonFatalFirstErr")              ); break;/*0x2700*/
  //case lz77ErrorClass:                       TRACE0(_T("lz77ErrorClass")                       ); break;/*0x2700 LZ77 Library errors*/
  case lz77ErrNonFatalInputBufferIncomplete: TRACE0(_T("lz77ErrNonFatalInputBufferIncomplete") ); break;/*0x2701*/
  case lz77ErrNonFatalOutputBufferFull:      TRACE0(_T("lz77ErrNonFatalOutputBufferFull")      ); break;/*0x2702*/
  case lz77ErrNonFatalLastErr:               TRACE0(_T("lz77ErrNonFatalLastErr")               ); break;/*0x277f*/
  case lz77ErrFatalFirstErr:                 TRACE0(_T("lz77ErrFatalFirstErr/lz77ErrFatalUnfinishedInputBuffer")); break;/*0x2780*/
  //case lz77ErrFatalUnfinishedInputBuffer:    TRACE0(_T("lz77ErrFatalUnfinishedInputBuffer")    ); break;/*0x2780*/
  case lz77ErrFatalInputBufferIncomplete:    TRACE0(_T("lz77ErrFatalInputBufferIncomplete")    ); break;/*0x2781*/
  case lz77ErrFatalInputBufferInvalid:       TRACE0(_T("lz77ErrFatalInputBufferInvalid")       ); break;/*0x2782*/
  case lz77ErrFatalMemAllocation:            TRACE0(_T("lz77ErrFatalMemAllocation")            ); break;/*0x2783*/
  case lz77ErrFatalHandleInvalid:            TRACE0(_T("lz77ErrFatalHandleInvalid")            ); break;/*0x2784*/
  case lz77ErrFatalCantChangeToCompress:     TRACE0(_T("lz77ErrFatalCantChangeToCompress")     ); break;/*0x2785*/
  case lz77ErrFatalUnknownVersion:           TRACE0(_T("lz77ErrFatalUnknownVersion")           ); break;/*0x2786*/
  case lz77ErrFatalOutputBufferTooSmall:     TRACE0(_T("lz77ErrFatalOutputBufferTooSmall")     ); break;/*0x2787*/
  case lz77ErrFatalInvalidArgument:          TRACE0(_T("lz77ErrFatalInvalidArgument")          ); break;/*0x2788*/
  case lz77ErrFatalLastErr:                  TRACE0(_T("lz77ErrFatalLastErr")                  ); break;/*0x27ff*/
  default:                                   TRACE0(_T("Unknown error")  );
  }
TRACE1(_T(" (%d).\n"), (UInt32)nErrorCode);
}
/* ////////////////////////////////////////////////////////////////////////// */
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2004-11-09 19:42:14  Darko Kolakovic 
 * $
 *****************************************************************************/
