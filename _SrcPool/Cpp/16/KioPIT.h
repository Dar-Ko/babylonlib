/*$Workfile: KioPIT.h$: header file
  $Revision: 3$ $Date: 18/09/2002 5:15:06 PM$
  $Author: Darko Kolakovic$

  Programmable Interval Timer (PIT) IBM-PC 8253/8254 constants
  Copyright: CommonSoft Inc
  Sep. 2k2 D.Kolakovic
 */

#ifndef __KIOPIT_H__
  /*KioPIT.h sentry */
  #define __KIOPIT_H__

#include "KTypedef.h" //typedef uint32

#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
  #pragma message ("   #include " __FILE__ )
#endif

/* ///////////////////////////////////////////////////////////////////////// */

  /*PIT frequency. PIT is tied to 3 clock lines all generating 
    NTSC/4 = 1.19318 MHz where NTSC = 4.77272 MHz.
   */
const uint32 IOC_PIT_FREQ = 4772720 / 4;

/*Programmable Interval Timer (PIT) IBM-PC 8253/8254

  The Programmable Interval Timer IC 8253 is used on the PC and XT, while 
  the 8254 is used on the AT+. ICs are contains three 16-bit programmable timers.
  All of the timers can work as a counter, with a master clock (1.19318 MHz) 
  common to all. This frequency and the programming register addresses don't 
  vary among different platforms, assuring compatibility. Each counter can be 
  programmed in six different modes by loading the Control Register at port 43h
  and controlling its associated enable gate. Counter 2 is enabled by setting
  a flag 0 of Programmable Peripheral Interface (PPI) at port 61h, and it's value
  can be read at port 42h. Counter's default value is 0 which generates clock
  of 1193180/65536 = 18.206 Hz.

  In PC Counter 0 is tied to Programmable Interrupt Controller (PIC, 8259).
  In DOS, the PIC is programmed to call the Interrupt Service Routine (ISR), 
  at Vector 8, thus the value of Counter 0 determines how often ISR is called.
  Counter 1 is tied to 8237 refreshing RAM every 15.08 µs.
  
  Port number:
  -Port 40h, 8253 Counter 0 Time of Day Clock (write-only, normally in mode 3)
  -Port 41h, 8253 Counter 1 RAM Refresh Counter (write-only, normally in mode 2)
  -Port 42h, 8253 Counter 2 Cassette and Speaker Functions (write-only)
  -Port 43h, 8253 Mode Control Register (read and write)
 
  Mode Control Register:

      MSB    Bits   LSB
      +---+---+-----+-+ 
      |7 6|5 4|3 2 1|0|  Mode Control Register
      +---+---+-----+-+
        |   |    |   +-------- 0/1 16 binary counter/4 decade BCD counter
        |   |    +---------- counter mode bits
        |   +----------- read/write/latch format bits
        +------------- counter select bits (also 8254 read back command)
 
    Bits 7,6 Counter Select Bits
      00  select Counter 0
      01  select Counter 1
      10  select Counter 2
      11  read back command (8254 only, illegal on 8253, see below)

    Bits 5,4 Read/Write/Latch Format Bits
      00  latch present counter value
      01  read/write of Most Significant Bit (MSB) only
      10  read/write of Least Significant Bit (LSB) only
      11  read/write LSB, followed by write of MSB

    Bits 3,2,1 Counter Mode Bits
      000 mode 0, interrupt on terminal count;  
                  countdown, interrupt, then wait for a new  mode count; 
                  loading a new count in the middle of a count stops the countdown
      001 mode 1, programmable one-shot; 
                  countdown with optional restart; 
                  reloading the counter will not affect the countdown until 
                  after the following trigger 
      010 mode 2, rate generator; 
                  generate one pulse after 'count' CLK cycles; 
                  output remains high until after the new countdown has begun; 
                  reloading the count mid-period does not take affect until 
                  after the period
      011 mode 3, square wave rate generator; 
                  generate one pulse after 'count' CLK cycles;
                  output remains high until 1/2 of the next countdown;
                  it does this by decrementing by 2 until zero, at which time it 
                  lowers the output signal, reloads the counter and counts down 
                  again until interrupting at 0; 
                  reloading the count mid-period does not take affect until
                  after the period 
      100 mode 4, software triggered strobe; 
                  countdown with output high until counter zero;
                  at zero output goes low for one CLK period;
                  countdown is triggered by loading counter;
                  reloading counter takes effect on next CLK pulse
      101 mode 5, hardware triggered strobe; 
                  countdown after triggering with output high until counter zero;
                  at zero output goes low for one CLK period

  Read Back Command Format  (8254 only)  

    |7 6|5|4|3|2|1|0| Read Back Command (written to Mode Control Reg)
      |  | | | | | +--- must be zero
      |  | | | | +---- select counter 0
      |  | | | +----- select counter 1
      |  | | +------ select counter 2
      |  | +------- 0 = latch status of selected counters
      |  +-------- 0 = latch count of selected counters
      +---------- 11 = read back command
 
  Read Back Command Status (8254 only, read from counter register)
 
    |7|6|5 4|3 2 1|0|  Read Back Command Status
     | |  |    |   +--- 0/1 16 binary counter/4 decade BCD counter
     | |  |    +------ counter mode bits (see Mode Control Reg above)
     | |  +---------- read/write/latch format (see Mode Control Reg)
     | +------------ 0/1 count available/null count (no count set)
     +------------- state of OUT pin (1=high, 0=low)


  Returns: a closest integer value PIT is using to generate clock with
  given frequency.

  Example:

       //Set Counter 2 mode 
      outb(IOC_PIT_MODESELECTCOUNTER2 | //Counter 2
           IOC_PIT_MODESELECTLSBMSB   | //1st write LSB, then write MSB
           IOC_PIT_MODESELECTMODE3    | //square wave generator
           IOC_PIT_MODESELECTBIN      , //16 binary counter
           IOC_PIT_MODECTRL             //Mode Control Register port
          );
        //Set new frequency for the Counter 2
      outb( GET_PIT_FREQDIVIDER(iFreq)  & 0xFF,      IOC_PIT_COUNTER2 ); //LSB
      outb((GET_PIT_FREQDIVIDER(iFreq) >> 8) & 0xFF, IOC_PIT_COUNTER2 ); //MSB
*/
inline uint16 GET_PIT_FREQDIVIDER(const uint16 iFrequency //[in] clock frequency
                                  //in range [18, 65535] Hz. 
                                 )
  {
  if (iFrequency < 18)
    return 0; //Returns PIT default clock (1193180/65536 = 18.206 Hz)
    //Return frequency divider
  return (uint16)(IOC_PIT_FREQ / iFrequency);
  }
 
  /*PIT Counter 0 port number: Time of Day Clock (normally in mode 3)        */
const int IOC_PIT_COUNTER0 = 0x40;
  /*PIT Counter 1 port number: RAM Refresh Counter (normally in mode 2)      */
const int IOC_PIT_COUNTER1 = 0x41;
  /*PIT Counter 2 port number: Cassette and Speaker controls                 */
const int IOC_PIT_COUNTER2 = 0x42;
  /*PIT Programmable Interval Timer Mode Control Register port number
    
      Bits
      +---+---+-----+-+ 
      |7 6|5 4|3 2 1|0|  Mode Control Register
      +---+---+-----+-+
        |   |    |   +-------- counter type bit
        |   |    +---------- counter mode bits
        |   +----------- read/write/latch format bits
        +------------- counter select bits (also 8254 read back command)
   */
const int IOC_PIT_MODECTRL = 0x43;
  
  /*PIT Counter Select flag: 0000 0000 - select Counter 0                    */
const uint8 IOC_PIT_MODESELECTCOUNTER0 = 0x00;
  /*PIT Counter Select flag: 0100 0000 - select counter 1                    */
const uint8 IOC_PIT_MODESELECTCOUNTER1 = 0x40;
  /*PIT Counter Select flag: 1000 0000 - select counter 2                    */
const uint8 IOC_PIT_MODESELECTCOUNTER2 = 0x80;
  /*PIT Read Back flag: 1100 0000 - (8254 only)                              */
const uint8 IOC_PIT_MODESELECTREADBACK = 0xC0;

  /*PIT Format flag: 0000 0000 - latch current counter value                 */
const uint8 IOC_PIT_MODESELECTLATCH    = 0x00;
  /*PIT Format flag: 0001 0000 - read/write of MSB only                      */
const uint8 IOC_PIT_MODESELECTMSB      = 0x10;
  /*PIT Format flag: 0010 0000 - read/write of LSB only                      */
const uint8 IOC_PIT_MODESELECTLSB      = 0x20;
  /*PIT Format flag: 0011 0000 - read/write LSB, followed by write of MSB    */
const uint8 IOC_PIT_MODESELECTLSBMSB   = 0x30;

  /*PIT Counter Mode flag: 0000 0000 - mode 0, interrupt on terminal count   */
const uint8 IOC_PIT_MODESELECTMODE0    = 0x00;
  /*PIT Counter Mode flag: 0000 0010 - mode 1, programmable one-shot         */
const uint8 IOC_PIT_MODESELECTMODE1    = 0x02;
  /*PIT Counter Mode flag: 0000 0100 - mode 2, rate generator                */
const uint8 IOC_PIT_MODESELECTMODE2    = 0x04;
  /*PIT Counter Mode flag: 0000 0110 - mode 3, square wave rate generator    */
const uint8 IOC_PIT_MODESELECTMODE3    = 0x06;
  /*PIT Counter Mode flag: 0000 1000 - mode 4, software triggered strobe     */
const uint8 IOC_PIT_MODESELECTMODE4    = 0x08;
  /*PIT Counter Mode flag: 0000 1010 - mode 5, hardware triggered strobe     */
const uint8 IOC_PIT_MODESELECTMODE5    = 0x0A;

  /*PIT Counter Type flag: 0000 0000 - 16 binary counter                     */
const uint8 IOC_PIT_MODESELECTBIN      = 0x00;
  /*PIT Counter Type flag: 0000 0001 - 4 decade BCD counter                  */
const uint8 IOC_PIT_MODESELECTBCD      = 0x01;

/* ///////////////////////////////////////////////////////////////////////// */
#endif  //__KIOPIT_H__
/******************************************************************************
 *$Log: 
 * 3    Biblioteka1.2         18/09/2002 5:15:06 PMDarko Kolakovic IOC_PIT_FREQ
 * 2    Biblioteka1.1         17/09/2002 1:38:03 PMDarko Kolakovic
 *      GET_PIT_FREQDIVIDER()
 * 1    Biblioteka1.0         16/09/2002 4:57:10 PMDarko Kolakovic 
 *$
 *****************************************************************************/
