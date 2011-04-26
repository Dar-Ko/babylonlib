/*$Workfile: TestBeep.cpp$: implementation file
  $Revision: 5$ $Date: 2005-05-18 18:34:11$
  $Author: Darko Kolakovic$

  Test PC beeping
  Copyright: CommonSoft Inc.
  Aug. 2k2 Darko Kolakovic
*/

// Group=Examples

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#include "stdafx.h"

#include "KTypedef.h" //LPCTSTR typedef
#include "KBeep.h"    //CBeep class
#include "KOctave.h"  //note Ids

extern bool TsWriteToViewLn(LPCTSTR lszText);

//TestBeep()-------------------------------------------------------------------
/*Testing beep sound.

  Returns: true if successful, otherwise returns false.
 */
bool TestBeep()
{
TsWriteToViewLn(_T("TestBeep()\a"));

bool bRes = true;
if (bRes)
  {
  CBeep beepDefault;
  #ifdef _DEBUG
    beepDefault.Dump();
  #endif
  beepDefault.Start();
  }
CBeep A;
A.m_iFrequency = (int16)(g_iOctave3[ID_NOTE_A]/1000); //note A3 [Hz]
A.Start();

//Beethoven's 9th symphony "Ode an die Freude"
Note snd9thSynphony[] =
  {
    { g_iOctave3[ID_NOTE_D  ], g_nSemiBreve    }, //D3 -repeatBeg 
    { g_iOctave3[ID_NOTE_E  ], g_nSemiBreve / 2}, //E3 
    {          NOTE_REST     , g_nSemiBreve / 8}, //rest
    { g_iOctave3[ID_NOTE_C  ], g_nSemiBreve * 2}, //C3
    { g_iOctave3[ID_NOTE_G  ], g_nSemiBreve    }, //G3
    { g_iOctave3[ID_NOTE_E  ], g_nSemiBreve    }, //E3 -repeatEnd
    {          NOTE_REST     , g_nSemiBreve / 2}, //rest
    
    { g_iOctave3[ID_NOTE_F  ], g_nSemiBreve    }, //F3
    { g_iOctave3[ID_NOTE_G  ], g_nSemiBreve    }, //G3 -repeatBeg 
    { g_iOctave3[ID_NOTE_F  ], g_nSemiBreve    }, //F3
    { g_iOctave3[ID_NOTE_E  ], g_nSemiBreve    }, //E3
    { g_iOctave3[ID_NOTE_D  ], g_nSemiBreve    }, //D3
    { g_iOctave3[ID_NOTE_C  ], g_nSemiBreve    }, //C3 -repeatEnd
    { g_iOctave3[ID_NOTE_D  ], g_nSemiBreve    }, //D3
    { g_iOctave3[ID_NOTE_E  ], g_nSemiBreve    }, //E3
    { g_iOctave3[ID_NOTE_E  ], g_nSemiBreve * 2}, //E3
    { g_iOctave3[ID_NOTE_D  ], g_nSemiBreve / 2}, //D3
    { g_iOctave3[ID_NOTE_D  ], g_nSemiBreve    }  //D3
  };
 
//todo: play an array D.K.
 
TsWriteToViewLn(LOG_EOT);
return bRes;
}

//////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 *$Log:
 * 2    Biblioteka1.1         2002-09-19 01:14:40  Darko
 * 1    Biblioteka1.0         2002-09-16 17:58:56  Darko Kolakovic
 *$
 *****************************************************************************/
