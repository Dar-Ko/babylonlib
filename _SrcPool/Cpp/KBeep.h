/*$Workfile: KBeep.h$: header file
  $Revision: 2$ $Date: 16/09/2002 4:57:42 PM$
  $Author: Darko Kolakovic$

  Generates beep sounds
  Copyright: CommonSoft Inc
  Sep. 2k2 D.Kolakovic
 */

#ifndef __KBEEP_H__
  //KBeep.h sentry
  #define __KBEEP_H__

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#include "KTypedef.h" //typedef uint32

///////////////////////////////////////////////////////////////////////////////
// Generates simple tones on the speaker.
class CBeep
{
public:
  CBeep();
  CBeep(int16 iFrequency, uint32 nDuration = 800);
  virtual ~CBeep();

  void Start();
  void Stop();
  #ifdef _DEBUG
    void Dump();
  #endif

public:
  int16  m_iFrequency;  //sound frequency in range [0, 32767] [Hz] 
  uint32 m_nDuration;   //sound duration  [ms]
  uint32 m_nDelay;      //delay between sounds [ms]
  uint32 m_nCount;      //number of repetitions
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//::CBeep()--------------------------------------------------------------------
/*
 */
inline CBeep::CBeep() :
  m_iFrequency(800),
  m_nDuration(800),
  m_nDelay(0),
  m_nCount(1)
  {
  }

inline CBeep::CBeep(int16 iFrequency, //[in] sound frequency in range [0, 32767] [Hz] 
                    uint32 nDuration  //[in] = 800 ms
                    ) :
  m_iFrequency(800),
  m_nDuration(nDuration),
  m_nDelay(0),
  m_nCount(1)
  {
  if ((iFrequency >= 0) && (iFrequency <= INT16_MAX))
    m_iFrequency = iFrequency;
  }

inline CBeep::~CBeep()
  {
  Stop();
  }

//::Dump()---------------------------------------------------------------------
#ifdef _DEBUG
#include "KTrace.h" //TRACE2 macro
/*Dumps the contents of the object 
 */
inline void CBeep::Dump()
  {
  TRACE2("CBeep\n  {\n  m_iFrequency = %d Hz\n  m_nDuration = %d ms\n",
          m_iFrequency,
          m_nDuration);
  TRACE2("  m_nDelay = %d ms\n  m_nCount = %d\n  }\n",
          m_nDelay,
          m_nCount);
  }
#endif

///////////////////////////////////////////////////////////////////////////////
#endif  //__KBEEP_H__
/******************************************************************************
 *$Log: 
 * 2    Biblioteka1.1         16/09/2002 4:57:42 PMDarko Kolakovic 
 * 1    Biblioteka1.0         13/09/2002 2:39:14 PMDarko Kolakovic 
 *$
 *****************************************************************************/
