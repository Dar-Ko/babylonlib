/*$RCSfile: KGetChecksum.cpp,v $: implementation file
  $Revision: 1.1 $ $Date: 2012/01/28 00:24:19 $
  $Author: ddarko $

  Calculates a checksum
  Copyright: CommonSoft Inc
  Apr. 2k2 D.Kolakovic
 */

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */
#ifndef uint8_t
  #include "KTypedef.h"
#endif
#ifdef _USE_ATL
  #define ASSERT ATLASSERT
#endif
#ifndef ASSERT
  #include "KTrace.h"
#endif

//-----------------------------------------------------------------------------
/*Calculates a checksum based on a given array of bytes.

  Returns the checksum of the data.
 */
uint16_t GetChecksum(uint8_t* pData, int nSize //buffer size in bytes
                    )
{
uint16_t* pwTemp = (uint16_t*)pData;
uint32_fast nResult = 0; //sum of data elements
//Sum all 16 bit long elements
while (nSize > 1)
  {
  nResult += *pwTemp++;
  nSize -= sizeof(uint16_t);
  }
//Add single leftover byte, if there is any
if (nSize == 1)
  nResult += *(uint8_t*)pwTemp;
//Add all bits over lower word to the lower word
nResult  = HIWORD(nResult) + LOWORD(nResult);
nResult += HIWORD(nResult);
return (uint16_t)(~nResult); //Truncate to 16 bits
}
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 *$Log: KGetChecksum.cpp,v $
 *Revision 1.1  2012/01/28 00:24:19  ddarko
 *Moved from StarTeam repository
 *
 *****************************************************************************/
