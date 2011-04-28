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
  //Test log creation
TESTENTRY logEntry =
{_T("CBeep::CBeep()"), _T("KBeep.h"), false};

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

const uint32 nMeasureNote = 200;
//Beethoven's 9th symphony "Ode an die Freude"
Note snd9thSynphony[] =
  {
    { g_iOctave3[ID_NOTE_D  ], nMeasureNote    }, //D3 -repeatBeg
    { g_iOctave3[ID_NOTE_E  ], nMeasureNote / 2}, //E3
    //{          NOTE_REST     , nMeasureNote / 8}, //rest
    { g_iOctave3[ID_NOTE_C  ], nMeasureNote * 2}, //C3
    { g_iOctave3[ID_NOTE_G  ], nMeasureNote    }, //G3
    { g_iOctave3[ID_NOTE_E  ], nMeasureNote    }, //E3 -repeatEnd
    //{          NOTE_REST     , nMeasureNote / 2}, //rest

    { g_iOctave3[ID_NOTE_F  ], nMeasureNote    }, //F3
    { g_iOctave3[ID_NOTE_G  ], nMeasureNote    }, //G3 -repeatBeg
    { g_iOctave3[ID_NOTE_F  ], nMeasureNote    }, //F3
    { g_iOctave3[ID_NOTE_E  ], nMeasureNote    }, //E3
    { g_iOctave3[ID_NOTE_D  ], nMeasureNote    }, //D3
    { g_iOctave3[ID_NOTE_C  ], nMeasureNote    }, //C3 -repeatEnd
    { g_iOctave3[ID_NOTE_D  ], nMeasureNote    }, //D3
    { g_iOctave3[ID_NOTE_E  ], nMeasureNote    }, //E3
    { g_iOctave3[ID_NOTE_E  ], nMeasureNote * 2}, //E3
    { g_iOctave3[ID_NOTE_D  ], nMeasureNote / 2}, //D3
    { g_iOctave3[ID_NOTE_D  ], nMeasureNote    }  //D3
  };

//todo: play an array D.K. 
//todo: play pause D.K.
int i = 0;
while (i < 16)
 {
 A.m_iFrequency = (int16)(snd9thSynphony[i].m_nPitch/1000);
 A.m_nDuration  = snd9thSynphony[i].m_nDuration;
 A.Start();
 i++;
 }
  //Write test log
logEntry.m_bResult = bRes;
LogTest(&logEntry);

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
