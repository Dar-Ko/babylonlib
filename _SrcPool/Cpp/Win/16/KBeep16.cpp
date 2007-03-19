/*$Workfile: KBeep16.cpp$: implementation file
  $Revision: 11$ $Date: 2005-05-18 18:34:43$
  $Author: Darko Kolakovic$

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

///////////////////////////////////////////////////////////////////////////////
#ifdef __GNUC__  /*GNU C/C++ Compiler                                        */

  #include <sys/io.h>     //outb()
  #include <sys/unistd.h> //ioperm(), usleep()
  #define _outp(iPortNo, iValue) outb(iValue, iPortNo)
  #define _inp(iPortNo) inb(iPortNo)

#endif  //__GNUC__

///////////////////////////////////////////////////////////////////////////////

#include "KBeep.h" //CBeep class

#ifdef _M_IX86 /*Intel x86 platform                                        */
  #include "KioPIT.h" //Programmable Interval Timer (PIT) IBM-PC 8253/8254
  #include "KioPPI.h" //Programmable Peripheral Interface (PPI) IBM-PC 8255

  /////////////////////////////////////////////////////////////////////////////
  // CBeep on platforms compatibile with IBM-PC architecture.
  // DOS, Win16, Win9x, Microsoft C++ compiler

  //::Start()------------------------------------------------------------------
  /*Begin emitting predefined sound.

    Example:
      #include "KBeep.h"    //CBeep class
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
        _inp(IOC_PPI_MODECTRL) | //current Port B status (speaker control state)
        IOC_PPI_PC_SPEAKER     | //enable PC Speaker
        IOC_PPI_PITCOUNTER2      //enable PIT counter 2
       );
  }

  //::Stop()------------------------------------------------------------------
  /*Stop emitting predefined sound.
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
/*****************************************************************************
 * $Log: 
 *  11   Biblioteka1.10        2005-05-18 18:34:43  Darko Kolakovic comment
 *  10   Biblioteka1.9         2005-05-17 14:14:50  Darko Kolakovic Extrected
 *       Octave and Scale constants
 *  9    Biblioteka1.8         2005-05-16 14:25:39  Darko Kolakovic Comments
 *  8    Biblioteka1.7         2005-04-28 21:00:33  Darko           
 *  7    Biblioteka1.6         2002-10-11 14:33:30  Darko Kolakovic 
 *  6    Biblioteka1.5         2002-10-10 20:26:06  Darko Kolakovic Fixed x86
 *       version (16-bit)
 *  5    Biblioteka1.4         2002-09-19 17:37:37  Darko Kolakovic 
 *  4    Biblioteka1.3         2002-09-19 01:14:36  Darko           
 *  3    Biblioteka1.2         2002-09-18 18:13:35  Darko Kolakovic Start() /Win9x
 *  2    Biblioteka1.1         2002-09-17 14:36:45  Darko Kolakovic Added KioPIT.h
 *  1    Biblioteka1.0         2002-09-16 17:57:06  Darko Kolakovic 
 * $
 *****************************************************************************/
