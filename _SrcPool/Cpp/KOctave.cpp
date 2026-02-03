/*$Workfile: KOctave.cpp$: implementation file
  $Revision: 5$ $Date: 2005-06-24 20:14:52$
  $Author: Darko Kolakovic$

  Octave constants
  Copyright: CommonSoft Inc.
  Sep. 2k2 Darko Kolakovic
*/


#define _KOCTAVE_DECL 20050518  //Extern declaration sentry
#include "KOctave.h" //note Ids

///////////////////////////////////////////////////////////////////////////////

/*Fourth octave in equal tempered chromatic scale,
  Standard pitch (A = 440 Hz).

  A note is a unit of fixed pitch and defined duration (breve).
  Pitch is the dominant frequency of a note produced by a musical instrument.
  English notation assigns letter names: A, B, C, D, E, F and G for seven notes.
  {html: With two modifiers sharp &#9839; and flat &#9837; it is possible to
  represent 12 notes of diatonic octave. }
  Sharp raises and flat lowers the pitch of a note by a semitone.
  Each note symbol have a specific pitch regardless of the octave in which
  the pitch resides.

  Calculation for Equal-Tempered tuning (12-TET).
  Equal-tempered tuning is a musical tuning in which the octave is divided
  into twelve equal half-steps and it is usually used on piano, harp, guitar,
  and pitched percussion instruments.

  In an equal-tempered tuning, every note is 2^(1/12) times the frequency of
  the note a semitone lower. Thus twelve equal-tempered semitones make
  exactly one octave, although all the intermediate intervals are slightly
  out of tune.

      Octave 0:
         Note    Frequency [Hz]
       0  A          55.000
       1  A#/Bb      58.270         Octave(N) = Octave(0)*2^N
       2  B          61.735         A3 = A0*2^3 = 55*8 = 440 Hz
       3  C          65.406
       4  C#/Db      69.296         Note(M) = Note(M-1)*2^(1/12)
       5  D          73.416
       6  D#/Eb      77.782
       7  E          82.407
       8  F          87.307
       9  F#/Gb      92.499
      10  G          97.999
      11  G#/Ab     103.826

  Frequency values in the table are rounded to closest integer and unit is
  [mHz = Hz/1000].

  See also: {html: <a href="Documentation/KMusicScale.htm">
  12-Note Equally Tempered Music Scale</a>}, Note structure, OCTAVE_NOTE_ID
 */
uint32 g_iOctave3[OCT_SIZE] =
  {
  440000, // 0 note A3 = 8*A0 [mHz = Hz/1000]
  466164, // 1 note A#3
  493883, // 2 note B3
  523251, // 3 note C3
  554365, // 4 note C#3
  587330, // 5 note D3
  622254, // 6 note D#3
  659255, // 7 note E3
  698456, // 8 note F3
  739989, // 9 note F#3
  783991, //10 note G3
  830609  //11 note G#3
  };


/*{html: Musical scale (12-TET) of key C. Values in the table are
  in mHz (Hz/1000).

  The tonic is the first note of a musical scale, in this case note C.
  <img src="Images/diagC12TetScale.gif" border="0" alt="chromatic C scale"><br />

  See also: <a href="Documentation/KMusicScale.htm">
  12-Note Equally Tempered Music Scale</a>
 }
 */
const uint32 g_nScaleC[MSCALE_SIZE] =
  {
  g_iOctave3[ID_NOTE_C  ]  , // 0 C3
  g_iOctave3[ID_NOTE_Cis]  , // 1 C#3
  g_iOctave3[ID_NOTE_D  ]  , // 2 D3
  g_iOctave3[ID_NOTE_Dis]  , // 3 D#3
  g_iOctave3[ID_NOTE_E  ]  , // 4 E3
  g_iOctave3[ID_NOTE_F  ]  , // 5 F3
  g_iOctave3[ID_NOTE_Fis]  , // 6 F#3
  g_iOctave3[ID_NOTE_G  ]  , // 7 G3
  g_iOctave3[ID_NOTE_Gis]  , // 8 G#3
  g_iOctave3[ID_NOTE_A  ]*2, // 9 A4
  g_iOctave3[ID_NOTE_Ais]*2, //10 A#4
  g_iOctave3[ID_NOTE_B  ]*2, //11 B4
  g_iOctave3[ID_NOTE_C  ]*2, //12 C4
  };

  //duration of whole note (semibreve) [ms]
uint32 g_nSemiBreve = SEMIBREVE0;


///////////////////////////////////////////////////////////////////////////////
//Sound tables

//Alert sound
Note g_sndAlert[] =
  {
    { g_iOctave3[ID_NOTE_A  ]*2, g_nSemiBreve    },  //A4
    { g_iOctave3[ID_NOTE_A]    , g_nSemiBreve    }   //A3
  };

//Chime sound. Chime is a percussion instrument consisting of vertical metal
//tubes of different lengths that are struck with a hammer.
Note g_sndChime[] =
 {
    { g_iOctave3[ID_NOTE_A  ]*2, g_nSemiBreve / 4},  //A4
    { g_iOctave3[ID_NOTE_Gis]  , g_nSemiBreve    }   //G#3
  };

//Bell sound.
Note g_sndBell[] =
  {
    { g_iOctave3[ID_NOTE_B  ]*2, g_nSemiBreve / 4},  //B4
    { g_iOctave3[ID_NOTE_Ais]*2, g_nSemiBreve    },  //A#4
    { g_iOctave3[ID_NOTE_A  ]*2, g_nSemiBreve    }   //A4
  };

//Clicking sound.
Note g_sndClick[] =
  {
    { g_iOctave3[ID_NOTE_A  ]*2, g_nSemiBreve / 4}  //A4
  };

//Winding Up sound
Note g_sndUp[] =
  {
    { g_iOctave3[ID_NOTE_A  ]  , g_nSemiBreve    },  //A3
    { g_iOctave3[ID_NOTE_Ais]  , g_nSemiBreve    },  //A#3
    { g_iOctave3[ID_NOTE_B  ]  , g_nSemiBreve    },  //B3
    { g_iOctave3[ID_NOTE_C  ]  , g_nSemiBreve    },  //C3
    { g_iOctave3[ID_NOTE_D  ]  , g_nSemiBreve    }   //D3
  };

//Unwinding sound
Note g_sndDown[] =
  {
    { g_iOctave3[ID_NOTE_D  ]  , g_nSemiBreve    },  //D3
    { g_iOctave3[ID_NOTE_C  ]  , g_nSemiBreve    },  //C3
    { g_iOctave3[ID_NOTE_B  ]  , g_nSemiBreve    },  //B3
    { g_iOctave3[ID_NOTE_Ais]  , g_nSemiBreve    },  //A#3
    { g_iOctave3[ID_NOTE_A  ]  , g_nSemiBreve    }   //A3
  };

//Prompt Message sound
Note g_sndQuestion[] =
  {
    { g_iOctave3[ID_NOTE_A  ]*2, g_nSemiBreve / 2},  //A4
    { g_iOctave3[ID_NOTE_Ais]*2, g_nSemiBreve / 2},  //A#4
    { g_iOctave3[ID_NOTE_B  ]*2, g_nSemiBreve / 2},  //B4
  };

//Warning Message sound
Note g_sndWarning[] =
  {
    { g_iOctave3[ID_NOTE_A  ]*2, g_nSemiBreve / 2},  //A4
    {            NOTE_REST     , g_nSemiBreve / 2},  //rest
    { g_iOctave3[ID_NOTE_A  ]*2, g_nSemiBreve / 2}   //A4
  };

//Error Message sound
Note g_sndError[] =
  {
    { g_iOctave3[ID_NOTE_B  ]*2, g_nSemiBreve    },  //B4
    {            NOTE_REST     , g_nSemiBreve / 2},  //rest
    { g_iOctave3[ID_NOTE_B  ]*2, g_nSemiBreve    }   //B4
  };

//Information Message sound
Note g_sndInfo[] =
  {
    { g_iOctave3[ID_NOTE_A  ]*2, g_nSemiBreve    }  //A4
  };

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2005-05-17 14:16:27  Darko Kolakovic
 * $
 * 0   Sep. 2k2 Darko Kolakovic
 ******************************************************************************/
