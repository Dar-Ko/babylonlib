/*$Workfile: KioPPI.h$: header file
  $Revision: 3$ $Date: 2005-04-18 10:35:39$
  $Author: Darko Kolakovic$

  Programmable Peripheral Interface (PPI) IBM-PC 8255 constants
  Copyright: CommonSoft Inc
  Sep. 2k2 D.Kolakovic
 */

/* Group=Platform                                                             */

#ifndef __KIOPPI_H__
  /*$Workfile: KioPPI.h$ sentry */
  #define __KIOPPI_H__

#include "KTypedef.h" //typedef uint32

#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
  #pragma message ("   #include " __FILE__ )
#endif

/* ///////////////////////////////////////////////////////////////////////// */
#ifdef __cplusplus

/*PPI Port A Keyboard Scan Code / System Configuration Status.

  PPI teturns keyboard scan code of the key pressed if bit 7 of Port B
  (Port A Mode) is set to 0.
  If bit 7 of Port B is set to 1, returns system configuration:

      |7 6|5 4|3 2|1|0|  System Configuration Status
        |   |   |  | +------- 1/0 has / has not Floppy Drive
        |   |   |  +----- Reserved
        |   |   +------ Banks of RAM on System Board
        |   +------ Video Mode
        +------- Number of Disk Drives

    Bits 7,6 Number of Disk Drives Bits
            00  1 disk drive
            01  2 disk drives
            10  3 disk drives
            11  4 disk drives

    Bits 4,5 Video Mode Bits
            01  Color (40 rows x 25 columns)
            10  Color (80 rows x 25 columns)
            11  Monochrome (80 row x 25 col)
   */
const int IOC_PPI_PORT_A = 0x60;
/*PPI Port C Configuration Switches Values and System Configuration Status.

      |7|6|5|4|3 2|1 0|  System Configuration Status
       | | | |  |   +----- Configuration Jumpers/Video Mode
       | | | |  +-------- Configuration Jumpers/Number of Disk Drives
       | | | +---------- PC Data from Cassette
       | | +---------- Output to PIT (IBM-PC 8253/8254)
       | +---------- Reserved
       +---------- 1/0 Parity Error / No Parity Error

    Bits 3,2,1,0 Configuration Jumpers (PC)
    If bit 2 of Port B (Port C Mode - PC) is set to 0, returns values of
    Configuration Jumpers (Switches) 4,3,2 and 1
    If bit 2 of Port B (Port C Mode - PC) is set to 1, returns values of
    Configuration Jumpers (Switches) 8,7,6 and 5
 */
const int IOC_PPI_PORT_C = 0x62;
/*PPI Programmable Peripheral Interface Mode Control Register (Port B)
  port number.

    Bits
    +-+-+-+-+-+-+-+-+
    |7|6|5|4|3|2|1|0|  Mode Control Register
    +-+-+-+-+-+-+-+-+
     | | | | | | | +------ 0/1 Disable / Enable Timer (PIT) Counter 2
     | | | | | | +------- 0/1 Disable / Enable output to PC Speaker
     | | | | | +-------- 0/1 Port C Mode (PC) Configuration Jumpers [1,4]/[5,8]
     | | | | +--------- 0/1 Port C Mode (XT) Jumpers [1,4]/System Configuration
     | | | +---------- 0/1 Enable / Disable RAM refresh
     | | +---------- Reserved
     | +---------- 0/1 Disable / Enable Keyboard Clock Signal
     +---------- 0/1 Port A Mode: Keyboard Scan Code/System Configuration
 */
const int IOC_PPI_MODECTRL = 0x61;

  /*PPI Port A Disk Drives Count flags: 1100 0000.
    Bits 7,6 Number of Disk Drives Bits

            00  1 disk drive
            01  2 disk drives
            10  3 disk drives
            11  4 disk drives
   */
const uint8 IOC_PPI_PORT_A_DISKCNT = 0xC0;
  /*PPI Port A Video Mode flags: 0011 0000.
    Bits 4,5 Video Mode Bits

            01  Color (40 rows x 25 columns)
            10  Color (80 rows x 25 columns)
            11  Monochrome (80 row x 25 col)
   */
const uint8 IOC_PPI_PORT_A_VIDEO = 0x30;
  /*PPI Port A Floppy Disk Drive flag: 0000 0001.                            */
const uint8 IOC_PPI_PORT_A_FDD = 0x01;

  /*PPI Port B PIT Counter 2 Enable flag: 0000 0001.                         */
const uint8 IOC_PPI_PITCOUNTER2= 0x01;
  /*PPI Port B PC Speaker Enable flag: 0000 0010.                            */
const uint8 IOC_PPI_PC_SPEAKER = 0x02;

/*Programmable Peripheral Interface (PPI) IBM-PC 8255

  Port number:
  -Port 60h, Port A Keyboard Scan Code / System Configuration Status (read-only)
  -Port 61h, Port B Mode Control Register (read and write)
  -Port 62h, Port C Status Register (read-only)

  Port A Keyboard Scan Code / System Configuration Status:

  Returns keyboard scan code of the key pressed if bit 7 of Port B
  (Port A Mode) is set to 0.
  If bit 7 of Port B is set to 1, returns system configuration:

      |7 6|5 4|3 2|1|0|  System Configuration Status
        |   |   |  | +------- 1/0 Floppy Drive available / not available
        |   |   |  +----- Reserved
        |   |   +------ Banks of RAM on System Board
        |   +------ Video Mode
        +------- Number of Disk Drives

    Bits 7,6 Number of Disk Drives Bits
            00  1 disk drive
            01  2 disk drives
            10  3 disk drives
            11  4 disk drives

    Bits 4,5 Video Mode Bits
            01  Color (40 rows x 25 columns)
            10  Color (80 rows x 25 columns)
            11  Monochrome (80 row x 25 col)

  Port B Mode Control Register:

      MSB    Bits   LSB
      +-+-+-+-+-+-+-+-+
      |7|6|5|4|3|2|1|0|  Mode Control Register
      +-+-+-+-+-+-+-+-+
       | | | | | | | +------- 0/1 Disable / Enable Timer (PIT) Counter 2
       | | | | | | +------- 0/1 Disable / Enable output to PC Speaker
       | | | | | +-------- 0/1 Port C Mode (PC) Configuration Jumpers [1,4]/[5,8]
       | | | | +--------- 0/1 Port C Mode (XT) Jumpers [1,4]/System Configuration
       | | | +---------- 0/1 Enable / Disable RAM refresh
       | | +---------- Reserved
       | +---------- 0/1 Disable / Enable Keyboard Clock Signal
       +---------- 0/1 Port A Mode: Keyboard Scan Code/System Configuration

    MSB = Most Significant Bit
    LSB = Least Significant Bit

  Port C Configuration Switches Values and System Configuration Status:

      |7|6|5|4|3 2|1 0|  System Configuration Status
       | | | |  |   +----- Configuration Jumpers/Video Mode
       | | | |  +-------- Configuration Jumpers/Number of Disk Drives
       | | | +---------- PC Data from Cassette
       | | +---------- Output to PIT (IBM-PC 8253/8254)
       | +---------- Reserved
       +---------- 1/0 Parity Error / No Parity Error

  Bits 3,2,1,0 Configuration Jumpers (PC)
  If bit 2 of Port B (Port C Mode - PC) is set to 0, returns values of
  Configuration Jumpers (Switches) 4,3,2 and 1.
  If bit 2 of Port B (Port C Mode - PC) is set to 1, returns values of
  Configuration Jumpers (Switches) 8,7,6 and 5.

  Bits 1,0 Video Mode Bits (XT)
  If bit 3 of Port B (Port C Mode - XT) is set to 1, returns Video Mode Status:

          01  Color (40 rows x 25 columns)
          10  Color (80 rows x 25 columns)
          11  Monochrome (80 row x 25 col)
  If bit 3 of Port B (Port C Mode - XT) is set to 0, returns values of
  Configuration Jumpers (Switches) 2 and 1.

  Bits 3,2 Number of Disk Drives Bits (XT)
  If bit 3 of Port B (Port C Mode - XT) is set to 1, returns Number of Disk Drives:

          00  1 disk drive
          01  2 disk drives
          10  3 disk drives
          11  4 disk drives
  If bit 3 of Port B (Port C Mode - XT) is set to 0, returns values of
  Configuration Jumpers (Switches) 4 and 3.

 */
inline int GET_PPI_DISKCNT(const uint8 cStatusA //[in] PPI Port A Status
                          )
  {
  return (int)((cStatusA & IOC_PPI_PORT_A_DISKCNT) >> 6) + 1;
  }

//HAS_PPI_FDD()----------------------------------------------------------------
/*Validates Floppy Drive flag on Port A of PPI IC.

  Returns: true if PC has floppy disk drive or false if floppy drive is
  not installed.

  Note: IBM-PC
 */
inline bool HAS_PPI_FDD(const uint8 cStatusA //[in] PPI Port A Status
                       )
  {
  return ((cStatusA & IOC_PPI_PORT_A_FDD) == IOC_PPI_PORT_A_FDD);
  }

#endif /*__cplusplus*/

/* ///////////////////////////////////////////////////////////////////////// */
#endif  //__KIOPPI_H__
/******************************************************************************
 *$Log: 
 * 3    Biblioteka1.2         2005-04-18 10:35:39  Darko Kolakovic Comment
 * 2    Biblioteka1.1         2005-04-18 10:27:55  Darko Kolakovic __cplusplus
 *      sentry
 * 1    Biblioteka1.0         2002-09-18 18:12:32  Darko Kolakovic 
 *$
 *****************************************************************************/
