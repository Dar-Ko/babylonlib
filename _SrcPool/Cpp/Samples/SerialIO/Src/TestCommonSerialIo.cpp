/*$Workfile: S:\_SrcPool\Cpp\Samples\SerialIO\Src\TestCommonSerialIo.cpp$: implementation file
  $Revision: 1$ $Date: 2007-03-18 21:56:25$
  $Author: Darko$

  Test serial port I/O routines.
  Copyright: CommonSoft Inc.
  2007-02-02 Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"

extern bool TsWriteToViewLn(LPCTSTR lszText);
#ifdef _WIN32
  extern bool TestSerialIo(const unsigned int nPortNo = 1);
#endif

int TestCommonSerialIo(int argc, TCHAR* argv[]);
int TestCommonSerialIo();

//-----------------------------------------------------------------------------
/*Validates different system service (deamon) routines.
Defines the entry point for an automated test.

Returns: EXIT_SUCCESS, which represents a value of 0, if successful. Otherwise
a non-zero error code is returned.
*/
int TestCommonSerialIo()
{
return TestCommonSerialIo(0, NULL);
}

//-----------------------------------------------------------------------------
/*Validates different routines accessing serial port.
  Defines the entry point for the test.

  Returns: EXIT_SUCCESS, which represents a value of 0, if successful. Otherwise
  a non-zero error code is returned.
 */
int TestCommonSerialIo(int argc, //[in] specifies how many arguments are passed
                          // to the program from the command line. The value of
                          // argc is at least one: the program name.
                      TCHAR* argv[] //[in] the program arguments as an array of
                          //pointers to null-terminated strings. The first string
                          //(argv[0]) is the program name. The end of the array
                          //(argv[argc]) is indicated by a NULL pointer.
                      )
{
TsWriteToViewLn(_T("Validation of serial port I/O methods"));
TsWriteToViewLn(_T(""));
int iTestCount = 0;

if (TestSerialIo())
  {
  TsWriteToViewLn(LOG_SUCCESS);
  TsWriteToViewLn(_T(""));
  }
else
  {
  TsWriteToViewLn(LOG_FAILURE);
  return EXIT_FAILURE + iTestCount;
  }

return EXIT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2007-03-18 21:56:25  Darko           
 * $
 *****************************************************************************/
