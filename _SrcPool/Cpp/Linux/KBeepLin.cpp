/*$RCSfile: KBeepLin.cpp$: implementation file
  $Revision: 2$ $Date: 2005-05-18 18:32:31$
  $Author: Darko Kolakovic$

  Generates beep sounds on PC speaker
  Copyright: CommonSoft Inc.
  2k2 Darko Kolakovic
*/

// Group=Linux

///////////////////////////////////////////////////////////////////////////////
#ifdef __GNUC__  /*GNU C/C++ Compiler                                        */

  #include <sys/io.h>     //outb()
  #include <sys/unistd.h> //ioperm(), usleep()
  #define _outp(iPortNo, iValue) outb(iValue, iPortNo)
  #define _inp(iPortNo) inb(iPortNo)

  #ifdef linux
    #ifndef __linux
      #define __linux
    #endif
  #endif
  #ifdef __linux__
    #ifndef __linux
      #define __linux
    #endif
  #endif

#endif  //__GNUC__

///////////////////////////////////////////////////////////////////////////////

#include "KBeep.h" //CBeep class

#ifdef __linux

/////////////////////////////////////////////////////////////////////////////
// CBeep on platforms compatible with IBM-PC architecture.
// Linux, GNU C++ compiler

#include <linux/kd.h>

//-----------------------------------------------------------------------------
/*TODO: Begin emitting predefined sound.

  Example:
      #include "KBeep.h"   //CBeep class
      #include "KOctave.h" //note Ids
      void MyFunc()
      {
      CBeep A; //note A3 [Hz]
      A.m_iFrequency = (int16)(g_iOctave3[ID_NOTE_A]/1000);
      A.Start();
      ...
      }
 */
void CBeep::Start()
{
TRACE(_T("CBeep::Start()\n"));
}

//-----------------------------------------------------------------------------
/*TODO: Stop emitting predefined sound.
 */
void CBeep::Stop()
{
TRACE(_T("CBeep::Stop()\n"));
}
#endif //__linux

#endif  //__GNUC__

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log:
 *  2    Biblioteka1.1         2005-05-18 18:32:31  Darko Kolakovic Comment
 *  1    Biblioteka1.0         2005-04-29 01:14:07  Darko
 * $
 ******************************************************************************/
