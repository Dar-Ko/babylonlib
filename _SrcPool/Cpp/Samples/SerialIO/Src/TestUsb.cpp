/*$Workfile: S:\_SrcPool\Cpp\Samples\SerialIO\Src\TestUsb.cpp$: implementation file
  $Revision: 1$ $Date: 2007-08-24 17:31:10$
  $Author: Darko Kolakovic$

  Test USB port helpers.
  Copyright: CommonSoft Inc.
  2007-08-02 Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"

#include "KUsb.h" //USBID struct
#include "KWinUsb.h"
#include "KUsbHub.h" //CUsbHub class
#include "KUsbHid.h" //CUsbHid class
#include "Platform/UsbVid8086.h" //Intel Corp. devices
#include "Platform/UsbVid05E0.h"

extern CTestLog g_logTest;   //general test logger
extern bool TsWriteToViewLn(LPCTSTR lszText);
extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(const unsigned int& nValue);

extern uint_fast32_t EnumerateHostControllers();

//-----------------------------------------------------------------------------
/*Validates Universal Serial Bus (USB) port enumeration methods.

  Returns true if test is successful; otherwise returns false.
 */
bool TestUsbEnumeration()
{
TsWriteToViewLn(_T("TestUsbEnumeration"));

bool bResult = false; //test result
try
  {
    //Test log  creation
  g_logTest.m_szObjectName = _T("CUsbDriverKeyName::CUsbDriverKeyName()");
  g_logTest.m_szFileName   = _T("KWinUsb.h");//function or object file name
  g_logTest.m_bResult      = false;              //result of the test
  CUsbDriverKeyName usbDriverKey(255);
  const int BUFFER_SIZE = 120;
  usbDriverKey.SetSize(BUFFER_SIZE);

  bResult =  (usbDriverKey.GetSize() == BUFFER_SIZE);
  TsWriteToView(_T("Allocated space for driver key name: "));
  TsWriteToViewLn(usbDriverKey.m_pKeyName->ActualLength);
  g_logTest.LogResult(bResult);

  g_logTest.m_szObjectName = _T("EnumerateHostControllers()");
  g_logTest.m_szFileName   = _T("KUsbHub.cpp");//function or object file name

  unsigned nUsbHostControllerCount = EnumerateHostControllers();
  TsWriteToView(_T("USB Host Controllers: "));
  TsWriteToViewLn(nUsbHostControllerCount);
  bResult = true;
  g_logTest.LogResult(bResult);

  g_logTest.m_szObjectName = _T("CUsbHub::Enumerate()");
  g_logTest.m_szFileName   = _T("KUsbHub.cpp");//function or object file name

  CUsbHub usbHub;
  bResult = (usbHub.Enumerate() == nUsbHostControllerCount);
  g_logTest.LogResult(bResult);

  g_logTest.m_szObjectName = _T("CUsbHid::Find()");
  g_logTest.m_szFileName   = _T("KWinUsbHid.cpp");//function or object file name

  CUsbHid usbHid;
  bResult = usbHid.Find(USBVID_ANY, USBPID_ANY);
  if (bResult)
    {
    g_logTest.LogResult(bResult);
    TsWriteToViewLn(_T("Found a USB HID class device."));
    TsWriteToViewLn(usbHid.GetDevicePath());

    g_logTest.m_szObjectName = _T("CUsbHid::GetDeviceCapabilities()");
    g_logTest.m_szFileName   = _T("KWinUsbHid.cpp");//function or object file name
    const PHIDP_CAPS phidCapabilities = usbHid.GetDeviceCapabilities();
    bResult = (phidCapabilities != NULL);
    g_logTest.LogResult(bResult);

    g_logTest.m_szObjectName = _T("CUsbHud::GetDeviceProperty()");
    g_logTest.m_szFileName   = _T("KUsbHud.cpp");//function or object file name

    TCHAR szProperty[MAX_PATH];
    DWORD dwLen = sizeof(szProperty);
    bResult = usbHub.GetDeviceProperty(usbHid, 
                                       usbHid.GetDevInfo(), 
                                       SPDRP_HARDWAREID,
                                       szProperty,
                                       dwLen
                                       );
    if (bResult)
      {
      TsWriteToViewLn(szProperty);
      bResult = usbHub.GetDeviceProperty(usbHid, 
                                         usbHid.GetDevInfo(), 
                                         SPDRP_DEVICEDESC,
                                         szProperty,
                                         dwLen
                                         );
      if (bResult)
        {
        TsWriteToViewLn(szProperty);
        bResult = usbHub.GetDeviceProperty(usbHid, 
                                          usbHid.GetDevInfo(), 
                                          SPDRP_CLASS,
                                          szProperty,
                                          dwLen
                                          );

        }
      if (bResult)
        TsWriteToViewLn(szProperty);
      }
    g_logTest.LogResult(bResult);

    g_logTest.m_szObjectName = _T("CUsbHid::Stop()");
    g_logTest.m_szFileName   = _T("KWinUsbHid.cpp");//function or object file name

    bResult = usbHid.Start(false);  //Stop the device
    if (bResult)
      TsWriteToViewLn(_T("Stopped the device."));
    else
      TsWriteToViewLn(_T("Failed to stop the device."));
    g_logTest.LogResult(true);

    if (bResult)
      bResult = usbHid.Start();       //Start the device
    }
  else
    {
    TsWriteToViewLn(_T("Not found a single USB HID class device."));
    g_logTest.LogResult(true);
    }
  }
catch(...)
  {
  bResult = false;
  g_logTest.LogResult(bResult);
  }

return bResult;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2007-08-24 17:31:10  Darko Kolakovic 
 * $
 *****************************************************************************/
