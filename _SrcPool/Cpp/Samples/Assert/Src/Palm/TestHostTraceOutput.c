/*$Workfile: TestHostTraceOutput.c$: implementation file
  $Revision: 1$ $Date: 2004-11-02 14:31:43$
  $Author: Darko Kolakovic$

  Entry point for the application.
  Copyright (c) 2001, Falch.net AS
  2004-11-01 Darko Kolakovic
 */

// Group=Examples
#ifndef _STDAFX_H_
  #include "stdafx.h"
#endif
#include <HostControl.h>
#if defined(__MWERKS__)/* Metrowerks CodeWarrior Compiler                    */
  #include <wchar_t.h>
  #include "KTChar.h" //LPCTSTR typedef
#else
  #include <tchar.h>
#endif

extern bool TsWriteToViewLn(LPCTSTR lszText);
bool TestHostTraceOutput(void);


/*----------------------------------------------------------------------------*/
/*Test host tracing. Tracing reports warnings to the Palm Reporter application.

  The Palm Reporter is a trace utility used with the Palm OS Emulator (POSE) or
  Palm OS Simulator. Applications running inside the Palm OS Emulator or
  Simulator could use the HostTrace APIs to send information in real-time to
  the Reporter.
  The Palm OS Emulator (POSE) is software that emulates the hardware of the
  various models of Palm Powered™ handhelds. It is extremely valuable for
  writing, testing and debugging applications, as it allows you to create
  virtual handhelds by running the Emulator on Windows, Mac OS, or Unix
  computers.

  To open a new Reporter window, first call HostTraceInit().

  Note: (Win32 specific) The Reporter may be started from any folder, and does
  not need to be stored in the same folder as POSE. This is not true for
  PalmTrace.dll, which should be located in the same directory as POSE.
  POSE will not be able to send traces to the Reporter if it can't find and load
  PalmTrace.dll, and it will fail silently if this happens.
  The Reporter requires some OLE related DLLs and Winsock2.

  Note: (Metrowerks CodeWarrior Specific) define REPORTER_TRACES = 1 to send
  tracing messages to the Palm Reporter.

  Returns true if test is successful; otherwise returns false.

  See also: http://www.palmos.com/dev/tools/emulator/ , Palm OS Emulator,
  Using Palm OS® Emulator: Chapter 8 Host Control API Reference,
  http://www.palmos.com/dev/support/docs/emulator/Emulator_HostControl.html

 */
bool TestHostTraceOutput()
{
bool bResult = true;
#define THTO_BUFFER_SIZE  256
unsigned char theBuffer[THTO_BUFFER_SIZE];
unsigned long theUInt32 = 0xFEDC1234;
unsigned short theUInt16 = 0xFE12;
int i;

TsWriteToViewLn(_T("TestHostTraceOutput()"));
HostTraceInit(); //Initiate a connection to the external trace reporting tool.

  //Output a text string, followed by a newline, to the external
  //trace reporting tool.
HostTraceOutputTL(appErrorClass, "This is an Int32:");
HostTraceOutputTL(appErrorClass, " unsigned (lu) [4275835444]=[%lu]", theUInt32);
HostTraceOutputTL(appErrorClass, " signed (ld) [-19131852]=[%ld]", theUInt32);
HostTraceOutputTL(appErrorClass, " hexa (lx) [fedc1234]=[%lx]", theUInt32);

HostTraceOutputTL(appErrorClass, "This is an Int16:");
HostTraceOutputTL(appErrorClass, " unsigned (hu) [65042]=[%hu]", theUInt16);
HostTraceOutputTL(appErrorClass, " signed (hd) [-494]=[%hd]", theUInt16);
HostTraceOutputTL(appErrorClass, " hexa (hX) [FE12]=[%hX]", theUInt16);

HostTraceOutputTL(appErrorClass, "This is a string (s) [Hello world]=[%s]", "Hello world");
HostTraceOutputTL(appErrorClass, "This is a char (c) [A]=[%c]", (Char)'A');

HostTraceOutputTL(appErrorClass, "This is a buffer:");

for (i = 0 ; i < THTO_BUFFER_SIZE ; i++)
  theBuffer[i] = (unsigned char) i;

  //Output a buffer of data, in hex dump format, to the external
  //trace reporting tool.
HostTraceOutputB(appErrorClass,//the ID of the Palm OS subsystem from which
                               //this output originates. You can use this with
                               //the external tracing tool to filter traces
                               //according to their origin.
                 theBuffer,    //a pointer to a buffer of raw data.
                 THTO_BUFFER_SIZE //the number of bytes of data in the buffer.
                 );

HostTraceClose(); //Close the connection to the external trace reporting tool.

TsWriteToViewLn(LOG_EOT);

return bResult;
}
/* ////////////////////////////////////////////////////////////////////////// */
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2004-11-02 14:31:43  Darko Kolakovic 
 * $
 *
 * Copyright (c) 2001, Falch.net AS
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with
 * or without modification, are permitted provided that the following conditions
 * are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * - Neither the name of Falch.net AS nor the names of its contributors
 * may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************/
