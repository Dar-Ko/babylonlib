/*$Workfile: KOctave.h$: header file
  $Revision: 4$ $Date: 2005-06-23 17:47:05$
  $Author: Darko Kolakovic$

  Octave constants
  Generates beep sounds
  Copyright: CommonSoft Inc
  Sep. 2k2 D.Kolakovic
 */

#ifndef _KOCTAVE_H_
  //$Workfile: KOctave.h$ sentry
  #define _KOCTAVE_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#include "KTypedef.h" //typedef uint32

///////////////////////////////////////////////////////////////////////////////
// Macros and type definitions.
{
/* Group=Constants                                                           */

#define NOTE_REST      0  //pause (silence, silenzio)

#define NOTE_A     55000  //note 0 A in first (0) octave of
                          //tempered chromatic scale [Hz/1000]
#define NOTE_Ais   58270  //note 1 A#/Bb in first (0) octave of
                          //tempered chromatic scale [Hz/1000]
#define NOTE_B     61735  //note 2 B in first (0) octave of
                          //tempered chromatic scale [Hz/1000]
#define NOTE_C     65406  //note 3 C in first (0) octave of
                          //tempered chromatic scale [Hz/1000]
#define NOTE_Cis   69296  //note 4 C#/Db in first (0) octave of
                          //tempered chromatic scale [Hz/1000]
#define NOTE_D     73416  //note 5 D in first (0) octave of
                          //tempered chromatic scale [Hz/1000]
#define NOTE_Dis   77782  //note 6 D#/Eb in first (0) octave of
                          //tempered chromatic scale [Hz/1000]
#define NOTE_E     82407  //note 7 E in first (0) octave of
                          //tempered chromatic scale [Hz/1000]
#define NOTE_F     87307  //note 8 F in first (0) octave of
                         //tempered chromatic scale [Hz/1000]
#define NOTE_Fis   92499  //note 9 F#/Gb in first (0) octave of
                          //tempered chromatic scale [Hz/1000]
#define NOTE_G     97999  //note 10 G in first (0) octave of
                          //tempered chromatic scale [Hz/1000]
#define NOTE_Gis  103826  //note 11 G#/Ab in first (0) octave of
                          //tempered chromatic scale [Hz/1000]
}

/*Index of a note in musical octaves (12-TET).

  See also: {html: <a href="Documentation/KMusicScale.htm">
  12-Note Equally Tempered Music Scale</a>}
 */
enum OCTAVE_NOTE_ID
  {
  ID_NOTE_A   =  0, //index of note A in an octave
  ID_NOTE_Ais =  1, //index of note A# in an octave
  ID_NOTE_B   =  2, //index of note B in an octave
  ID_NOTE_C   =  3, //index of note C in an octave
  ID_NOTE_Cis =  4, //index of note C# in an octave
  ID_NOTE_D   =  5, //index of note D in an octave
  ID_NOTE_Dis =  6, //index of note D# in an octave
  ID_NOTE_E   =  7, //index of note E in an octave
  ID_NOTE_F   =  8, //index of note F in an octave
  ID_NOTE_Fis =  9, //index of note F# in an octave
  ID_NOTE_G   = 10, //index of note G in an octave
  ID_NOTE_Gis = 11, //index of note G# in an octave
  OCT_SIZE    = 12, //number of notes in an octave (12-TET)
  MSCALE_SIZE = OCT_SIZE + 1   //number of notes in a musical scale
  };

#if defined __cplusplus
  const uint32 SEMIBREVE0 = 50; //duration of whole note (semibreve) [ms]
#endif

///////////////////////////////////////////////////////////////////////////////
//
/*Note describes sound with defined the pitch and duration.
  Pitch is the dominant frequency of a note produced by a musical instrument.
 */
struct Note
  {
  uint32 m_nPitch;    //dominant frequency of the note [Hz/1000]
  uint32 m_nDuration; //duration of the note [ms]
  };

///////////////////////////////////////////////////////////////////////////////
//Extern declarations

#if !defined _KOCTAVE_DECL
  /*Sound tables. See also KOctave.cpp*/
  extern uint32 g_iOctave3[OCT_SIZE];
  extern const uint32 g_nScaleC[MSCALE_SIZE];
  extern Note g_sndAlert[];
  extern Note g_sndChime[];
  extern Note g_sndBell[];
  extern Note g_sndClick[];
  extern Note g_sndUp[];
  extern Note g_sndDown[];
  extern Note g_sndQuestion[];
  extern Note g_sndWarning[];
  extern Note g_sndError[];
  extern Note g_sndInfo[];

#endif //_KOCTAVE_DECL
///////////////////////////////////////////////////////////////////////////////

#endif  //_KOCTAVE_H_
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2005-05-17 14:16:29  Darko Kolakovic
 * $
 * 0   Sep. 2k2 Darko Kolakovic
 ******************************************************************************/
