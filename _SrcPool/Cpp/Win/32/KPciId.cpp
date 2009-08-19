/*$RCSfile: KPciId.cpp,v $: implementation file
  $Revision: 1.3 $ $Date: 2009/08/19 21:11:35 $
  $Author: ddarko $

  Parse Peripheral Component Interconnect (PCI) device name.

  Note: Microsoft Windows specific (Win32).

  Copyright: babylonlib.sourceforge.net
  2009-08-12 Darko Kolakovic
 */

// Group=Windows
#ifdef _WIN32

#if defined _USE_ATL || defined _USE_MFC
  //Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)
  //or preprocessor reports unpaired #endif directive

  #include "stdafx.h" //Standard system header files

#else
  #include <windows.h>
#endif

#if defined _ATL_VER
  #ifndef TRACE
    #define TRACE ATLTRACE
    #define TRACE1 ATLTRACE
    #define TRACE2 ATLTRACE
  #endif
#endif

#ifndef TRACE
  #ifndef _T
    #include "KTChar.h"
  #endif
  #include "KTrace.h"
#endif

#include "KSysPnP.h"

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif
extern "C" long HextoL(LPCTSTR szSource);

//-----------------------------------------------------------------------------
/*Parses Peripheral Component Interconnect (PCI) device identification numbers.
  The following is a list of the device identification string formats that the
  PCI bus driver uses to report hardware IDs:

    PCI\VEN_v(4)&DEV_d(4)&SUBSYS_s(4)n(4)&REV_r(2)
    PCI\VEN_v(4)&DEV_d(4)&SUBSYS_s(4)n(4)
    PCI\VEN_v(4)&DEV_d(4)&REV_r(2)
    PCI\VEN_v(4)&DEV_d(4)
    PCI\VEN_v(4)&DEV_d(4)&CC_c(2)s(2)p(2)
    PCI\VEN_v(4)&DEV_d(4)&CC_c(2)s(2)

  Note: Microsoft Windows 32-bit specific;

  Returns: true and device identification numbers if successful; otherwise
  returns false.

  Example:
  ...
  LPTSTR szDeviceName = _T("\\\\?\\pci#ven_8086&dev_24dd&subsys_017a1028&rev_02
                           #3&172e68dd&0&ef#{3abf6f2d-71c4-462a-8a92-1e6861e6af27}");
  PCIID pciId;
  PciId(szDeviceName, &pciId);
  TRACE2(_T("vendor = %0.4X, product = %0.4X"), pciId.m_wVid, pciId.m_wPid);

  See also: SYSTEMENUM_PCI, PCIID;
  MSDN: Windows Driver Kit: Device Installation
 */
bool PciId(LPCTSTR szDeviceName, //[in] system-supplied PnP enumerator name
                          //for Peripheral Component Interconnect (PCI) devices.
           LPPCIID pPciId //[out] device identification numbers.
          )
{
TRACE(_T("PciId()\n"));
bool bResult = false;

if ((szDeviceName != NULL) &&
    (szDeviceName[0] != _T('\0')) &&
    (pPciId != NULL) )
  {
  //Normalize string to lowercase
  LPTSTR szName = _tcslwr(_tcsdup(szDeviceName));

  if (szName != NULL)
    {
    const int IDLENGTH = 4;     //number of digits in the identification number
    const int IDREV    = 2;     //number of digits in the revision number
    const int IDSUBSYS = 4 + 4; //number of digits in the revision number
    TCHAR szHexNumber[IDSUBSYS + 1]; //zero-terminated identification number
    szHexNumber[IDSUBSYS] = _T('\0');
    LPTSTR szPart = _tcsstr(szName, SYSTEMENUM_PCI);
    if(szPart != NULL)
      {
      LPCTSTR szVen    = _T("ven_")    ; const int iVenLen    = 4;
      LPCTSTR szDev    = _T("&dev_")   ; const int iDevLen    = 5;
      LPCTSTR szSubsys = _T("&subsys_"); const int iSubsysLen = 8;
      LPCTSTR szRev    = _T("&rev_")   ; const int iRevLen    = 5;
      szPart = _tcsstr(szPart, szVen);
      if(szPart != NULL)
        {
        szPart += iVenLen;
        int i = 0;
        while (i < IDLENGTH)
          {
          szHexNumber[i] = szPart[i];
          i++;
          }
        szHexNumber[i] = _T('\0');
        pPciId->m_wVid = (uint16_t)HextoL(szHexNumber);
        szPart = _tcsstr(szPart, szDev);
        if(szPart != NULL)
          {
          szPart += iDevLen;
          i = 0;
          while (i < IDLENGTH)
            {
            szHexNumber[i] = szPart[i];
            i++;
            }
          pPciId->m_wDid = (uint16_t)HextoL(szHexNumber);

          //Optional identificators
          szPart = _tcsstr(szPart, szSubsys);
          if(szPart != NULL)
            {
            szPart += iSubsysLen;
            i = 0;
            while (i < IDSUBSYS)
              {
              szHexNumber[i] = szPart[i];
              i++;
              }
            pPciId->m_dwSubsystem = (uint32_t)HextoL(szHexNumber);
            }
          else
            pPciId->m_dwSubsystem = 0;

          szPart = _tcsstr(szPart, szRev);
          if(szPart != NULL)
            {
            szPart += iRevLen;
            i = 0;
            while (i < IDREV)
              {
              szHexNumber[i] = szPart[i];
              i++;
              }
            szHexNumber[i] = _T('\0');
            pPciId->m_cRev = (uint8_t)HextoL(szHexNumber);
            }
          else
            pPciId->m_cRev = 0;

          bResult = true;
          }
        }
      }
    free(szName);
    }
  }

return bResult;
}

///////////////////////////////////////////////////////////////////////////////
#endif //_WIN32
/*****************************************************************************
 * $Log: KPciId.cpp,v $
 * Revision 1.3  2009/08/19 21:11:35  ddarko
 * PCI description
 *
 * Revision 1.2  2009/08/18 21:35:55  ddarko
 * PciId
 *
 * Revision 1.1  2009/08/18 19:02:28  ddarko
 * Created
 *
 *****************************************************************************/
