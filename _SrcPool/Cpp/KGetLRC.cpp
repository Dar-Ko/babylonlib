/*$Workfile: KGetLRC.cpp$: implementation file
  $Revision: 4$ $Date: 2004-06-01 17:50:31$
  $Author: Darko$

  Longitudinal Redundancy Checksum (LRC)
  Copyright: CommonSoft Inc.
  4.5.1989 Darko Kolakovic (original C version)
 */

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

#ifndef _KCHARCST_H_
  #include "KCharCst.h" //ETX
#endif

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

#ifndef uint8_t
  #include "KTypedef.h"
#endif

extern "C" uint8_t GetLRC(uint8_t* pbData,int iCount);

//GetLRC()---------------------------------------------------------------------
/*Calculates one byte Longitudinal Redundancy Checksum (LRC). The LRC is an
  exclusive-or calculation on all data bytes. While is possible to obtain
  the checksum of any array of bytes, the LRC is usually calculated from the
  beginning of data buffer to the termination character, including termination
  character itself.
  The termination character for data transfer is either end of text (ETX),
  end of transmission block (ETB) or end of transmission (EOT) character.

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
uint8_t GetLRC(uint8_t* pbData, //[in] data buffer including
                          //termination character (ETB/ETX/EOT)
              int iCount  //[in] size of data in bytes including
                          //termination character
              )
{
uint8_t chLRC = 0;
while(iCount > 0)
  {
  chLRC ^= *pbData++;
  iCount--;
  }

return chLRC;
}

//TODO: test
uint32_t GetLRC(uint32_t* pnData, //[in] data buffer
                uint32_t nCount   //[in] number of data elements
               )
{
uint32_t nLRC = 0xAAAAAAAA;
const int INT_SIZE = 32; //data size in bits
while(nCount > 0)
  {
  nLRC ^= *pbData++;
  if ( nLRC != 0 )
    {
    while((nLRC != 0) &&
           (((1L << (INT_SIZE - 1)) & nLRC) != 0) )
      {
      //if the last bit is 1, double the value
      nLRC <<= 1;
      }
    }
   nCount--;
  }

return nLRC;
}
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log:
 *  4    Biblioteka1.3         2004-06-01 17:50:31  Darko           time sync
 *  3    Biblioteka1.2         2002-01-29 15:40:00  Darko           Tag update
 *  2    Biblioteka1.1         2001-10-05 10:16:55  Darko           Comments
 *  1    Biblioteka1.0         2001-08-11 01:07:03  Darko
 * $
 *
 * Revision 0  1989 D.K.  Created
 ******************************************************************************/
DWORD test_checksum( const DWORD * buffer, DWORD number_of_entries )
{
#if ! defined( BITBOOL )
#define BITBOOL(x) (!(!(x)))
#endif

#if ! defined( bit_test )
#define bit_test(  arg, posn ) BITBOOL((arg) & (1L << (posn)))
#endif

   DWORD checksum = 0xAAAAAAAA; // Initialize the checksum

   DWORD loop_index = 0;

   while( loop_index < number_of_entries )
   {
      checksum ^= buffer[ loop_index ];

      if ( checksum != 0 )
      {
         while( bit_test( checksum, 31 ) == 1 && checksum != 0 )
         {
            checksum <<= 1;
         }
      }

      loop_index++;
   }

   return( checksum );
}