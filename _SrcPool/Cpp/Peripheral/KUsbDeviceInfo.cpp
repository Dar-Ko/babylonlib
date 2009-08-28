/*$RCSfile: KUsbDeviceInfo.cpp,v $: implementation file
  $Revision: 1.2 $ $Date: 2009/08/28 21:08:01 $
  $Author: ddarko $

  USB (Universal Serial Bus) device information container
  Copyright:  CommonSoft Inc.
  2009-08-28 Darko Kolakovic
 */

#if defined _ATL_VER
  #ifndef _USE_ATL
    #define _USE_ATL
  #endif
#endif

#ifdef _USE_ATL
  //Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)
  //or preprocessor reports unpaired #endif directive

  #include "stdafx.h" //Standard system header files
  #include "KTraceAtl.h"
#else
  #include <windows.h>
#endif

#ifndef TRACE
  #ifndef _T
    #include "KTChar.h"
  #endif
  #include "KTrace.h"
#endif
#include <ctype.h> //_iswspace
#include "KUsbDeviceInfo.h" //CUsbDeviceInfo class

///////////////////////////////////////////////////////////////////////////////
//CUsbDeviceInfo class implementation

//-----------------------------------------------------------------------------
/*Converts the USB port numbers to the formatted string.
  Because USB uses a tiered topology, identifying a device requires the port
  numbers of the all hubs in the chain. The maximum number of the chained hubs
  is USB_TOPLEVEL - 1. Each level will be represent with decimal port number
  within range [1, USB_MAXCOUNT], separated with the column ':' character.
  Zero (0) signifies the node level (USB tier) with no device attached.
  The first number represents the sequential number of the USB host controller
  on the system.

      USB port numbering format example:
      H:I:J:K   H       - host controller sequential number
                I, J, K - hub port numbers

  Returns pointer to the formatted string representing node (port) numbers
  of the USB tiered topology.

  See also: "Universal Serial Bus Specification Revision 1.1";
  USB_TOPLEVEL, CUsbTree, CUsbDeviceInfo::SetPortNo;
 */
LPCTSTR CUsbDeviceInfo::GetPortNo(CString& strPortId //[out] formatted
                                 //USB port numbering
                                 ) const
{
const TCHAR SEPARATOR = _T(':');
#ifndef INT32_LEN
  const int INT32_LEN = 11; //maximum number of characters representing
                            //signed 32-bit integer
#endif
TCHAR szPortId[INT32_LEN + 1 + 1];
//Note: root hub ID is not limited to USB_MAXCOUNT in order to simplify the code
strPortId = _itot(m_nPortNo[USB_ROOTLEVEL - 1], szPortId, 10);

szPortId[0] = SEPARATOR;
int i = 1;
while(i < (USB_TOPLEVEL - 1))
  {
  if ((m_nPortNo[i] > 0) && (m_nPortNo[i] <= USB_MAXCOUNT))
    {
    _itot(m_nPortNo[i], &szPortId[1], 10);
    strPortId += szPortId;
    }
  i++;
  }
return (LPCTSTR)strPortId;
}

//-----------------------------------------------------------------------------
/*Converts formatted USB port numbering to the array of USB node IDs, where
  each ID number represent a hub port number at the dusting USB tier level.

      USB port numbering format example:
      H:I:J:K:0:0   H       - host controller sequential number
                    I, J, K - hub port numbers

  See also: "Universal Serial Bus Specification Revision 1.1";
  USB_TOPLEVEL, CUsbTree, CUsbDeviceInfo::GetPortNo;
 */
bool CUsbDeviceInfo::SetPortNo(LPCTSTR szPortId //[in] formatted
                                 //USB port numbering
                                 )
{
bool bResult = false;
const TCHAR SEPARATOR = _T(':');
const TCHAR TERMINATOR = _T('\0');

#ifndef UINT32_LEN
  const int UINT32_LEN = 10; //maximum number of characters representing
                             //signed 32-bit integer
#endif
TCHAR szValue[UINT32_LEN + 1];

ZeroPortNo(); //Set node level to USB_ROOTLEVEL and node Ids to zero.

int k = 0;
while (m_nTierLevel <= (USB_TOPLEVEL - 1))
  {
  //Find the token
  int i = 0;
  while(_istdigit(szPortId[k]) && 
        (i <= UINT32_LEN))
    {
    szValue[i] = szPortId[k];
    i++;
    k++;
    }
  //Get the numeric value
  szValue[i] = TERMINATOR;
  m_nPortNo[m_nTierLevel - 1] = _ttoi(szValue);

  if (szPortId[k] != SEPARATOR)
    {
    if (szPortId[k] == TERMINATOR)
      {
      //Obtained the last element
      bResult = true;
      }
    break;
    }
  m_nTierLevel++;
  }

return bResult;
}

///////////////////////////////////////////////////////////////////////////////

/*****************************************************************************
 * $Log: KUsbDeviceInfo.cpp,v $
 * Revision 1.2  2009/08/28 21:08:01  ddarko
 * SetPortNo
 *
 * Revision 1.1  2009/08/28 13:57:26  ddarko
 * Extracted from KUsbHub
 *
 *****************************************************************************/
