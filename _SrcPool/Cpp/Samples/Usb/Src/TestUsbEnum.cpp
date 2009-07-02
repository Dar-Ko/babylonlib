/*$RCSfile: TestUsbEnum.cpp,v $: implementation file
  $Revision: 1.2 $ $Date: 2009/07/02 21:44:37 $
  $Author: ddarko $

  Test USB tree enumeration.
  Copyright: CommonSoft Inc.
  2009-06-26 Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"
#if !defined _KTESTLOG_H_
 #error wrong stdafx.h header is included!
 //The project options for this module have "..\..\Win\32" in 
 //additional include path
#endif
extern CTestLog g_logTest;   //general test logger

/*Note: A MSVC LNK2005 error occurs when the CRT library and MFC libraries 
  (nafxcwd.lib, libcmtd.lib) are linked in the wrong order in Visual C++
  See also: MSDN Article ID: 148652 http://support.microsoft.com/kb/148652
 */
#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;

  #ifdef _MSC_VER /*MS VC/C++ - Disable warning */
    //Fix for the warning(4786) cannot debug code with symbols longer
    //than 255 characters
  #pragma warning (disable: 4786)
  #endif
#endif

extern bool TsWriteToViewLn(LPCTSTR lszText);
extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(const unsigned int& nValue);
extern bool TsWriteToView(const unsigned int& nValue);
//#include <vector>

#if _MSC_VER < 1300
  //MSVC/C++ 6.0 or lesser
  //#pragma include_alias(<iostream>, <iomanip.h>)
#endif
//#include <iostream> //std::endl

#include "UsbVid.h"  //USB VID List
#include "KWinUsb.h" //TUsbSymbolicName template
#include "KUsbHid.h" //CUsbHid class

bool TestUsbEnum(uint16_t nVendorId = 0, uint16_t nProductId = 0);

//-----------------------------------------------------------------------------
/*Validates a method of **TODO** USB.

  Returns true if test is successful; otherwise returns false.

  Note: uses Standard Template Library (STL).

  See also: 
 */
bool TestUsbEnum(uint16_t nVendorId , //[in] = 0 USB Vendor ID (VID)
                    uint16_t nProductId  //[in] = 0 USB Product ID (PID)
                   )
{
TsWriteToViewLn(_T("Browse USB Tree"));

bool bResult = true;
try
  {
  //std::vector<tstring> listUsbNames;

  //Test log  creation
  g_logTest.m_szObjectName = _T("CUsbHid::CUsbHid()");
  #ifdef _WIN32
    g_logTest.m_szFileName   = _T("KWinUsbHid.cpp"); //function or object file name
  #endif
  g_logTest.m_bResult      = false;              //result of the test

  //Find given USB HID
  CUsbHid usbHid;

  g_logTest.LogResult(bResult); //Log object's construction
  g_logTest.m_szObjectName = _T("CUsbHid::Find(uint16_t, uint16_t)");

  TsWriteToView(_T("USB HID VID:"));
  TsWriteToView((unsigned int)nVendorId);
  TsWriteToView(_T(" PID:"));
  TsWriteToView((unsigned int)nProductId);

  bResult = usbHid.Find(nVendorId, nProductId);

  TsWriteToViewLn((bResult ? _T(" found.") : _T(" not found!")));
  g_logTest.LogResult(bResult);

  if(bResult)
    {
    //If device is found, browse its capabilities
    g_logTest.m_szObjectName = _T("CUsbHid::GetDeviceCapabilities()");

    PHIDP_CAPS pCapabilities = usbHid.GetDeviceCapabilities();
    bResult = (pCapabilities != NULL);
    g_logTest.LogResult(bResult);

    }

  g_logTest.LogResult(bResult);
  }
catch(std::out_of_range& eoor)
  {
  #if _MSC_VER == 1200
    //warning C4710: (MSVC6 STL Release build) function not inlined
    #pragma warning (push, 3)
  #endif

  std::_tcout << _T("STL out of range error occured! ") << eoor.what() << std::endl;

  #if _MSC_VER == 1200
    #pragma warning (pop)
  #endif

  bResult = false;
  }
catch(const std::exception& e)  
  {
  #if _MSC_VER == 1200
    //warning C4710: (MSVC6 STL Release build) function not inlined
    #pragma warning (disable: 4710)
  #endif

  std::_tcout << _T("STL exception error occured! ") << e.what() << std::endl;
  bResult = false;
  }
catch(...)
  {
  TsWriteToViewLn(_T("An exception error occured!"));
  bResult = false;
  }
TsWriteToViewLn(LOG_EOT);

return bResult;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 *$Log: TestUsbEnum.cpp,v $
 *Revision 1.2  2009/07/02 21:44:37  ddarko
 *Test for USB hub
 *
 *Revision 1.1  2009/06/26 21:35:35  ddarko
 *Added new test case
 *
 *Revision 1.2  2008/10/03 22:12:43  ddarko
 *USB browsing
 *
 *Revision 1.1  2008/09/26 21:36:48  ddarko
 *Added new test case
 *
 *****************************************************************************/
