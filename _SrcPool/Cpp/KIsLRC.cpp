/*$Workfile: KIsLRC.cpp$: implementation file
  $Revision: 3$ $Date: 3/8/02 3:04:37 PM$
  $Author: Darko Kolakovic$

  Validates Longitudinal Redundancy Checksum (LRC)
  CommonSoft Inc.
  Jan. 2k Darko Kolakovic
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

#ifndef NULL
  #ifdef  __cplusplus
      //NULL pointer value
    #define NULL  0
  #else
      /*NULL pointer value */
    #define NULL  ((void *)0)
  #endif
#endif

extern "C" BYTE GetLRC(BYTE* pbData,int iCount);

//IsLRCValid()-----------------------------------------------------------------
/*Validates Longitudinal Redundancy Checksum (LRC).
   
  Returns: true if given LRC is same as calculated. If checksums are different
  or if the last byte in data array is not termination character (EOT/ETB/ETX)
  or if the length of the data is zero, returned value is false.

  Example:

      {
      ...
      BYTE chData[10] = {STX,'1','2','3','4','5','6','7',EOT};
      chData[9] = GetLRC(&chData[1],8);
      ...
      if(IsLRCValid(chData[9],&chData[1],8))
          TRACE0("LRC is valid\n");
      }
 */
bool IsLRCValid(const BYTE chReceivedLRC, //[in] value to be verified
                BYTE* pbData,             //[in] data buffer including
                                          //termination character (EOT/ETB/ETX)
                int iCount    //[in] size of data in bytes including
                              //termination character (minimm value is 1)
                )
{
if ((pbData != NULL) && (iCount > 0) )
  {
  if ((pbData[iCount - 1] == EOT) ||
      (pbData[iCount - 1] == ETB) ||
      (pbData[iCount - 1] == ETX))
    if (chReceivedLRC == GetLRC(pbData,iCount))
      return true;
  }

return false;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log:
 *  1    Biblioteka1.0         11/08/2001 1:07:06 AMDarko
 * $
 *****************************************************************************/

