/*$RCSfile: KIsDevClassInst.cpp,v $: implementation file
  $Revision: 1.1 $ $Date: 2012/05/17 21:52:41 $
  $Author: ddarko $

  Verifies if specific device class driver is installed on system with Windows OS
  Copyright: artistic license
  Jan 2010 Darko Kolakovic
 */

#include "stdafx.h"
#pragma (lib, setupapi.lib)
#include <setuapi.h>

//----------------------------------------------------------------------------
/*Returns true if driver for specified device class is available on the system.
  The installation file INF defines a new device class by its GUID. If the device
  is not installed, the device class would not be present on the mchine.

  Note: Microsoft Windows specific (Win32).
 */
bool IsDevClassInstalled(LPCTSTR szDeviceClassGuid //[in] device class GUID
                        )
{
uint32_t nLength = 0;
const int MAXSIZE = 256;
TCHAR szDeviceClassDescription[MAXSIZE];
szDeviceClassDescription[0] = _T('\0');
SetupDiGetClassDescription(deviceClassGuid, 
                           szDeviceClassDescription, 
                           MAXSIZE, &nLength);
return (strlen(szDeviceClassDescription) > 0);
}
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: KIsDevClassInst.cpp,v $
 * Revision 1.1  2012/05/17 21:52:41  ddarko
 * Created
 *
 *****************************************************************************/
