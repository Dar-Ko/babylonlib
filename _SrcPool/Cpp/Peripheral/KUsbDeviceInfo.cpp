/*$RCSfile: KUsbDeviceInfo.cpp,v $: implementation file
  $Revision: 1.5 $ $Date: 2009/09/03 19:47:13 $
  $Author: ddarko $

  USB (Universal Serial Bus) device information container
  Copyright:  CommonSoft Inc.
  2009-08-28 Darko Kolakovic
 */

#ifdef WIN32
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
    #include <tchar.h> //_istdigit()
    /*Note: Apparently if <tchar.h> header file is included before <windows.h>,
      the Microsoft C++ compiler v7.1 or lesser in multithreaded Unicode environment
      instantiates wtype inline functions (_iswdigit, _iswspace, etc.), resulting
      in multiple definitions and linker error LNK2005.
      See also: _FIXLNK2005WTYPE
     */
  #endif
#endif

#include "KUsbDeviceInfo.h" //CUsbDeviceInfo class
#include "KProgCst.inl"     //IsEmpty()

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
  on the system. Trailing zeroes are not presented, except for the root level.

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
#if defined(_MSC_VER) && (_MSC_VER >= 1400)
  //Microsoft Visual C/C++ 2005, version 8.0
  #define ItoS(value, buffer, size, radix) _itot_s(value, buffer, size, radix)
#else
  #define ItoS(value, buffer, size, radix) _itot(value, buffer, radix)
#endif
const TCHAR SEPARATOR = _T(':');
#ifndef INT32_LEN
  const int INT32_LEN = 11; //maximum number of characters representing
                            //signed 32-bit integer
#endif
TCHAR szPortId[INT32_LEN + 1 + 1];
//Note: root hub ID is not limited to USB_MAXCOUNT in order to simplify the code
ItoS(m_nPortNo[USB_ROOTLEVEL - 1], szPortId, SizeOfArray(szPortId), 10);
strPortId = szPortId;

szPortId[0] = SEPARATOR;
int i = 1;
while(i < (USB_TOPLEVEL - 1))
  {
  if ((m_nPortNo[i] <= 0) || (m_nPortNo[i] > USB_MAXCOUNT))
    break;

  ItoS(m_nPortNo[i], &szPortId[1], SizeOfArray(szPortId) - 1, 10);
  strPortId += szPortId;
  i++;
  }
return (LPCTSTR)strPortId;
}

//-----------------------------------------------------------------------------
/*Set a tiered, one-based port (hub node) index for the current tier level.
  Because USB uses a tiered topology, identifying a device requires the port
  number and tier level. The tier level is maintained by m_nTierLevel field.

  Note: if tier level is out of proper range, the port index is not set.

  See also: USB_MAXCOUNT, USB_TOPLEVEL
 */
void CUsbDeviceInfo::SetPortNo(const int iPortId //[in] hub port number
                                      //in the range [1, n]
                                     )
{
#pragma warning (disable: 4127)
  ASSERT((m_nTierLevel >= USB_ROOTLEVEL) && (m_nTierLevel <= (USB_TOPLEVEL - 1)));
#pragma warning (default: 4127)
if ((m_nTierLevel >= USB_ROOTLEVEL) && (m_nTierLevel <= (USB_TOPLEVEL - 1)))
  m_nPortNo[m_nTierLevel - 1] = iPortId;
}

/*Set a tiered, one-based port (hub node) index for the given tier level.
  If tier level is out of proper range, the port index is not set.
 */
void CUsbDeviceInfo::SetPortNo(const unsigned int nTier, //[in] USB tier
                                      //level [USB_ROOTLEVEL, USB_TOPLEVEL - 1]
                                      const int iPortId //[in] hub port number
                                      //in the range [1, n]
                                     )
{
#pragma warning (disable: 4127)
  ASSERT((nTier >= USB_ROOTLEVEL) && (nTier <= (USB_TOPLEVEL - 1)));
#pragma warning (default: 4127)
if ((nTier >= USB_ROOTLEVEL) && (nTier <= (USB_TOPLEVEL - 1)))
  m_nPortNo[nTier - 1] = iPortId;
}

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
if(!IsEmpty(szPortId))
  {
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

    if ((m_nPortNo[m_nTierLevel - 1] > USB_MAXCOUNT) ||
        (m_nPortNo[m_nTierLevel - 1] < 0 ) )
      break; //Out of range error

    if (szPortId[k] != SEPARATOR)
      {
      if (szPortId[k] == TERMINATOR)
        {
        //Obtained the last element
        bResult = true;
        }
      break;
      }
    else
      {
      k++; //Move to next value
      if (szPortId[k] == SEPARATOR)
        {
        //Found two consecutive separators
        break;
        }
      }

    m_nTierLevel++;
    }

  if(bResult)
    {
    //Recount tier level in order to cut off any zeroes in the middle
    k = 0;
    while(k < (USB_TOPLEVEL - 1))
      {
      if (m_nPortNo[k] <= 0)
        break;
      k++;
      }
    m_nTierLevel = (k == 0)? USB_ROOTLEVEL : k; //Set one-based level index
    while( k < (USB_TOPLEVEL - 1))
      {
      m_nPortNo[k] = 0;
      k++;
      }
    }
  }

return bResult;
}

///////////////////////////////////////////////////////////////////////////////

/*****************************************************************************
 * $Log: KUsbDeviceInfo.cpp,v $
 * Revision 1.5  2009/09/03 19:47:13  ddarko
 * Fixed potential overun
 *
 * Revision 1.4  2009/09/02 21:51:59  ddarko
 * MSVC++ 8.0
 *
 * Revision 1.3  2009/09/01 21:52:02  ddarko
 * Validating limits of port Id
 *
 * Revision 1.2  2009/08/28 21:08:01  ddarko
 * SetPortNo
 *
 * Revision 1.1  2009/08/28 13:57:26  ddarko
 * Extracted from KUsbHub
 *
 *****************************************************************************/
