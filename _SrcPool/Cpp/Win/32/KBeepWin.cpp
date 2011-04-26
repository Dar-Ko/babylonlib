/*$Workfile: KBeepWin.cpp$: implementation file
  $Revision: 2$ $Date: 2005-05-18 18:35:31$
  $Author: Darko Kolakovic$

  Generates beep sounds on PC speaker.
  Copyright: CommonSoft Inc.
  2005-05-17 Darko Kolakovic
 */

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */


#include "stdafx.h"
#include "KBeep.h" //CBeep class

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

#if defined(_WIN95)
  #inclide "Win/16/KBeep16.cpp"
#endif

#if defined (_WIN32) && !defined(_WIN95)

///////////////////////////////////////////////////////////////////////////////
// CBeep class
// Win98, WinMe,  WinNT, Win2k, Microsoft C++ compiler

//-----------------------------------------------------------------------------
/*Begin emitting predefined sound.
  
  Example:
      #include "KBeep.h"    //CBeep class
      #include "KOctave.h"  //note Ids
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
/*The Beep function generates simple tones on the speaker.
  The function is synchronous; it does not return control to its caller until
  the sound finishes.
 */
uint32 iCount = 0;
while(iCount < m_nCount)
  {
  if ( !::Beep(m_iFrequency, m_nDuration) )
    {
    extern void SystemErrMessage(UINT uiSystemError);
    SystemErrMessage(GetLastError());
    break;
    }
  iCount++;
  }
}


//-----------------------------------------------------------------------------
/*Stop emitting predefined sound.
 */
void CBeep::Stop()
{
TRACE(_T("CBeep::Stop()\n"));
if ( !::Beep(0, 0) )
  {
  extern void SystemErrMessage(UINT uiSystemError);
  SystemErrMessage(GetLastError());
  }
}

///////////////////////////////////////////////////////////////////////////////
#endif //_WIN32 && !_WIN95
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2005-05-16 14:25:53  Darko Kolakovic
 * $
 *****************************************************************************/
