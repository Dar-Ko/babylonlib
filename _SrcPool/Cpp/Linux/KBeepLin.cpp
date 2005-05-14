/*$Workfile: S:\_SrcPool\Cpp\Linux\KBeepLin.cpp$: implementation file
  $Revision: 1$ $Date: 2005-04-29 01:14:07$
  $Author: Darko$

  Generates beep sounds on PC speaker
  Copyright: CommonSoft Inc.
  Darko Kolakovic Jan 98
*/
///////////////////////////////////////////////////////////////////////////////
#ifdef MSVC /*Microsoft Visual C - 4.x+ Compiler                             */
  #define _MSC_VER
#endif

#ifdef _MSC_VER
  #ifdef M_I286
    #ifndef _M_IX86
      #define _M_IX86 200 //CPU: 80286
    #endif
  #endif

  #include <conio.h>  //_outp()

#endif

//TODO: beep sounds on PC speakerLinux
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

/*Fourth octave in equal tempered chromatic scale,
  Standard pitch (A = 440 Hz).

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

 */
uint32 g_iOctave3[12] =
  {
  440000, // 0  A3 = 8*A0 [Hz * 1000]
  466164, // 1  A#3
  493883, // 2  B3
  523251, // 3  C3
  554365, // 4  C#3
  587330, // 5  D3
  622254, // 6  D#3
  659255, // 7  E3
  698456, // 8  F3
  739989, // 9  F#3
  783991, //10  G3
  830609  //11  G#3
  };

const int NOTE_A   = 0; //index of note A in an octave
const int NOTE_Ais = 1; //index of note A# in an octave
const int NOTE_B   = 2; //index of note B in an octave
const int NOTE_C   = 3; //index of note C in an octave
const int NOTE_Cis = 4; //index of note C# in an octave
const int NOTE_D   = 5; //index of note D in an octave
const int NOTE_Dis = 6; //index of note D# in an octave
const int NOTE_E   = 7; //index of note E in an octave
const int NOTE_F   = 8; //index of note F in an octave
const int NOTE_Fis = 9; //index of note F# in an octave
const int NOTE_G   =10; //index of note G in an octave
const int NOTE_Gis =11; //index of note G# in an octave

/*Musical scale of key C
 */
const uint32 g_nScale[13] =
  {
  g_iOctave3[NOTE_C  ]  , // 0 C3
  g_iOctave3[NOTE_Cis]  , // 1 C#3
  g_iOctave3[NOTE_D  ]  , // 2 D3
  g_iOctave3[NOTE_Dis]  , // 3 D#3
  g_iOctave3[NOTE_E  ]  , // 4 E3
  g_iOctave3[NOTE_F  ]  , // 5 F3
  g_iOctave3[NOTE_Fis]  , // 6 F#3
  g_iOctave3[NOTE_G  ]  , // 7 G3
  g_iOctave3[NOTE_Gis]  , // 8 G#3
  g_iOctave3[NOTE_A  ]*2, // 9 A4
  g_iOctave3[NOTE_Ais]*2, //10 A#4
  g_iOctave3[NOTE_B  ]*2, //11 B4
  g_iOctave3[NOTE_C  ]*2, //12 C4
  };

#ifdef _M_IX86 /*Intel x86 platform                                        */
  #include "KioPIT.h" //Programmable Interval Timer (PIT) IBM-PC 8253/8254
  #include "KioPPI.h" //Programmable Peripheral Interface (PPI) IBM-PC 8255

  /////////////////////////////////////////////////////////////////////////////
  // CBeep on platforms compatibile with IBM-PC architecture.
  // DOS, Win16, Win9x, Microsoft C++ compiler

  //::Start()------------------------------------------------------------------
  /*
   */
  void CBeep::Start()
  {
  TRACE0("CBeep::Start()\n");
  if (m_iFrequency <= 0)
    return; //Nothing to do; DC (0 Hz).
  //Note: Smallest clock PIT (IBM-PC) could generate is 18.206 Hz.
  //      Maximum is 1.19318 MHz.

  /*Procedure to turn on the PC speaker:
        Set PIT Counter 2 to Square Wave Generator mode;
        Set Counter 2 frequency divider
        Read PPI Port B status;
        Set PIT Timer and Speaker flags;
        Write new PPI Port B status;
   */
  uint16 nCount = GET_PIT_FREQDIVIDER(m_iFrequency);
  _outp(IOC_PIT_MODECTRL, //Port number
        IOC_PIT_MODESELECTCOUNTER2 | //Counter 2
        IOC_PIT_MODESELECTLSBMSB   | //1st write low byte, then write high byte
        IOC_PIT_MODESELECTMODE3    | //square wave generator
        IOC_PIT_MODESELECTBIN        //16 binary counter
       );
  _outp(IOC_PIT_COUNTER2, //Set Counter 2
        (nCount & 0xFF)   //low byte
       );
  _outp(IOC_PIT_COUNTER2,      //Set Counter 2
        ((nCount >> 8) & 0xFF) //high byte
       );
  _outp(IOC_PPI_MODECTRL, //Set PPI Port B
        _inp(IOC_PPI_MODECTRL) | //current Port B status
        IOC_PPI_PC_SPEAKER     | //enable PC Speaker
        IOC_PPI_PITCOUNTER2      //enable PIT counter 2
       );
  }

  //::Stop()------------------------------------------------------------------
  /*
   */
  void CBeep::Stop()
  {
  TRACE0("CBeep::Stop()\n");
  _outp(IOC_PPI_MODECTRL, //Set PPI Port B
        _inp(IOC_PPI_MODECTRL) & //current Port B status
        ~(IOC_PPI_PC_SPEAKER     | //disable PC Speaker
          IOC_PPI_PITCOUNTER2      //disable PIT counter 2
         )
       );
  }

#endif //_M_IX86

///////////////////////////////////////////////////////////////////////////////
#ifdef __GNUC__  /*GNU C/C++ Compiler                                        */

  #ifdef __linux
    #include <linux/kd.h>
  /////////////////////////////////////////////////////////////////////////////
  // CBeep on platforms compatibile with IBM-PC architecture.
  // Linux, GNU C++ compiler

  #else //DOS, Win32, GNU C++ compiler

  #endif //__linux

#endif  //__GNUC__

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  7    Biblioteka1.6         2002-10-11 13:33:30  Darko Kolakovic
 *  6    Biblioteka1.5         2002-10-10 19:26:06  Darko Kolakovic Fixed x86
 *       version (16-bit)
 *  5    Biblioteka1.4         2002-09-19 16:37:37  Darko Kolakovic
 *  4    Biblioteka1.3         2002-09-19 00:14:36  Darko
 *  3    Biblioteka1.2         2002-09-18 17:13:35  Darko Kolakovic Start() /Win9x
 *  2    Biblioteka1.1         2002-09-17 13:36:45  Darko Kolakovic Added KioPIT.h
 *  1    Biblioteka1.0         2002-09-16 16:57:06  Darko Kolakovic
 * $
 *****************************************************************************/
