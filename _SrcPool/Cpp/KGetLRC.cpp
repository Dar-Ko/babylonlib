/*$Workfile: KGetLRC.cpp$: implementation file
  $Revision: 3$ $Date: 1/29/02 3:40:00 PM$
  $Author: Darko$

  Longitudinal Redundancy Checksum (LRC)
  Copyright: CommonSoft Inc.
  4.5.1989 Darko Kolakovic (original C version)
 */

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#ifndef _KCHARCST_H_
  #include "KCharCst.h" //ETX
#endif

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

#ifndef BYTE
  #define BYTE unsigned char
#endif

extern "C" BYTE GetLRC(BYTE* pbData,int iCount);

//GetLRC()---------------------------------------------------------------------
/*Calculates one byte Longitudinal Redundancy Checksum (LRC). The LRC is an 
  exclusive-or calculation on all data bytes. The LRC is calculated from the 
  begining of data buffer to the termination character, including termination 
  character itself. 

  Returns: Longitudinal Redundancy Checksum (LRC).


          +---+
          |STX|  Start of Text [1 Byte]
       /--+---+--
       |  | D |  Data [N bytes]
       L  | a |
       R  | t |
       C  | a |
          +---+
       s  |ETX|
       u  |ETB|  Termination Character [1 Byte]
       m  |EOT|
       \--+---+--
          |LRC|  Longitudinal Redundancy Checksum [1 Byte]
          +---+
                 iCount = N+1 [byte]

 */
BYTE GetLRC(BYTE* pbData, //[in] data buffer including 
                          //termination character (ETB/ETX/EOT)
            int iCount    //[in] size of data in bytes including
                          //termination character
            )
{
BYTE chLRC = 0;
while(iCount > 0)
  {
  chLRC ^= *pbData++;
  iCount--;
  }

return chLRC;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: 
 *  3    Biblioteka1.2         1/29/02 3:40:00 PM   Darko           Tag update
 *  2    Biblioteka1.1         10/5/01 10:16:55 AM  Darko           Comments
 *  1    Biblioteka1.0         8/11/01 1:07:03 AM   Darko           
 * $
 *
 * Revision 0  1989 D.K.  Created
 * *****************************************************************************/

