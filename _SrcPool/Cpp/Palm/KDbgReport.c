/*$Workfile: KDbgReport.c$: implementation file
  $Revision: 6$ $Date: 2004-11-09 18:46:02$
  $Author: Darko Kolakovic$

  Dumps a message to the debugger
  Copyright: CommonSoft Inc.
  2004-11-04 Darko Kolakovic
 */

/* Group=Diagnostic */

#include <PalmOS.h>
#include <ErrorBase.h> /*ErrDisplayFileLineMsg()*/
#include <DebugMgr.h>  /*DbgMessage()*/
#ifdef __MWERKS__
  /*Note: StdLib include path is 
          <CodeWarrior>/Palm OS Support/Incs/Core/System/Unix
   */
  #include <unix_stdio.h> /*sprintf()*/
  #include <unix_stdarg.h>/*va_list*/
#else
  #include <StringMgr.h> /*StrVPrintF()*/
  #include <stdarg.h>    /*va_list*/
#endif
#include "KTracePalm.h"
#include "KTypedefPalm.h" /*TCHAR*/

void DbgReport( int iReportType,
                LPCTSTR szFileName,
                unsigned int nLineNumber,
                LPCTSTR szModuleName,
                LPCTSTR szMessage,
                ...);


/*----------------------------------------------------------------------------*/
/*Generates a report with a debugging message and sends the report to the
  preselected destinations.

  TODO: format message (insert line no, filename, module name)

  Note: Palm OS specific (PalmOS).
 */
void DbgReport( int iReportType,       /*[in] specifies a report type:
                                         _DBG_WARN, _DBG_ERROR or, _DBG_ASSERT.
                                        */
                LPCTSTR szFileName,       /*[in] name of source file where
                                            assert or report occurred or NULL.
                                           */
                unsigned int nLineNumber, /*[in] line number in source file
                                            where assert or report occurred or 0.
                                           */
                LPCTSTR szModuleName,     /*[in] name of application module
                                            where assert or report occurred or
                                            NULL.
                                           */
                LPCTSTR szMessage,        /*[in] formatted message to be included
                                            in the report or NULL.
                                           */
                ... //TODO:
              )
{
UInt32  nProcessorType = 0;
  /*If report format is not null, create the message*/
TCHAR temp[512];
if (szMessage != NULL)
  {
  va_list args;
  va_start( args, szMessage );
  if (szModuleName != NULL)
    StrCopy(temp, szModuleName); /*TODO:...*/
    
  #ifdef __MWERKS__
//    sprintf(temp, szMessage, args);
//  #else
    /*Note: StrVPrintF implements a subset of the ANSI C vsprintf call, which
      writes formatted output to a buffer (See PalmOS SDK).
     */
    StrVPrintF(temp, szMessage, args);
  #endif
    //...
    va_end( args );
  }

  //TODO: check and validate report destination: log, alert box, or debugger D.K.
  //TODO: create DbgSetReportMode() D.K.

  /*Send report to the debugger*/
  {
    /*If Palm OS Simulator or Palm OS Emulator (POSE) is currently active
      device, send the report to the debugger logger
     */
  if ( ((FtrGet( sysFileCSystem,       //'psys'
                sysFtrNumProcessorID,  //2
                &nProcessorType ) != ftrErrNoSuchFeature) &&
        (nProcessorType == sysFtrNumProcessorx86 ))       ||
       ( FtrGet( kPalmOSEmulatorFeatureCreator,     //'pose'
                      kPalmOSEmulatorFeatureNumber, //0
                      &nProcessorType ) != ftrErrNoSuchFeature )
     )
    {
    //TODO: format message (insert line no, filename, module name)
    UNUSED_ARG(szModuleName);
    DbgMessage(temp);

    switch(iReportType)
      {
      case _DBG_WARN:
      case _DBG_ERROR:
        break;
      case _DBG_ASSERT:
        DbgBreak();
      default:
        break;
      }
    }
  }
  /*Send report to the alert message box*/
if (0) //TODO: set a global flag in DbgSetReportMode()
  {
  ErrDisplayFileLineMsg(szFileName, nLineNumber, szMessage);
  }


}

/* ////////////////////////////////////////////////////////////////////////// */
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2004-11-04 13:18:13  Darko Kolakovic
 * $
 *****************************************************************************/
 #if 0
  UInt16 ioSrcBytes = 256;//StrLen(szMessage);
  UInt16 ioDstBytes = 256;
  Char szTarget[256];
  TxtConvertEncoding(true, //this function call is starting a new conversion
                     NULL, //no subsequent calls are planned
                     (const Char *)szMessage, //source text buffer
                     &ioSrcBytes, //length in bytes of the text and conversion result
                     charEncodingUTF8,  //source text encoding
                     szTarget, //destination text buffer or NULL
                     &ioDstBytes, //target buffer length in bytes or number of bytes required convert source
  /*Getcurrent device encoding                -> */  charEncodingAscii, //encoding to which to convert text
                     "?", //substitution for  any invalid or inconvertible characters
                     1 //number of bytes in substitution without the terminating null byte
                    );
#endif
