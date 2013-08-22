/*$RCSfile: WinCeGetChE.cpp,v $: implementation file
  $Revision: 1.1 $ $Date: 2013/08/22 15:18:01 $
  $Author: ddarko $
  Get a single character from the console with echo
  Copyright: CommonSoft Inc.
*/

#include "stdafx.h"

#ifdef WINCE
#include <winioctl.h>
#include <console.h>

#define _getche GetChE
extern "C" int GetChE();

//---------------------------------------------------------------------------
/*Read a single character from the console with echo, meaning that the character
  is displayed at the console.
  When reading a function key or an arrow key, each function must be called twice;
  the first call returns 0 or 0xE0, and the second call returns the actual key code.
  
  Returns the character read. There is no error return.
 */
int GetChE()
{
  USE_CONIOCTL_CALLS
  const DWORD  dwMode = CECONSOLE_MODE_PROCESSED_OUTPUT |
                        CECONSOLE_MODE_ECHO_INPUT       ;
                        //CECONSOLE_MODE_LINE_INPUT       ; //wait until CR (ENTER key) or line terminator.
  CeSetConsoleMode (_fileno(stdin),dwMode);

  return _fgettc(stdin);
}
///////////////////////////////////////////////////////////////////////////////
#endif