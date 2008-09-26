/*$RCSfile: TestFindUsbHid.cpp,v $: implementation file
  $Revision: 1.1 $ $Date: 2008/09/26 21:36:48 $
  $Author: ddarko $

  Test file names handling
  Copyright: CommonSoft Inc.
  2008-09-26 Darko Kolakovic
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

//#include <vector>

#if _MSC_VER < 1300
  //MSVC/C++ 6.0 or lesser
  //#pragma include_alias(<iostream>, <iomanip.h>)
#endif
//#include <iostream> //std::endl

#include "KUsbHid.h" //CUsbHid

#define VID_MS 0x045E //(Microsoft Corporation)
#define PID_MS 0x0083 //Basic Optical Mouse - generic HID

bool TestFindUsbHid(uint16_t nVendorId = 0, uint16_t nProductId = 0);

//-----------------------------------------------------------------------------
/*Test finding USB HID.

  Returns true if test is successful; otherwise returns false.

  Note: uses Standard Template Library (STL).
 */
bool TestFindUsbHid(uint16_t nVendorId , //[in] = 0 USB Vendor ID (VID)
                    uint16_t nProductId  //[in] = 0 USB Product ID (PID)
                   )
{
TsWriteToViewLn(_T("Browse USB HID Tree"));

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
  TsWriteToViewLn(_T("USB HID"));
  bResult = usbHid.Find(nVendorId, nProductId);

  g_logTest.LogResult(bResult);
  }
catch(std::out_of_range& eoor)
  {
  std::_tcout << _T("STL out of range error occured! ") << eoor.what() << std::endl;
  bResult = false;
  }
catch(const std::exception& e)  
  {
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
 *$Log: TestFindUsbHid.cpp,v $
 *Revision 1.1  2008/09/26 21:36:48  ddarko
 *Added new test case
 *
 *****************************************************************************/
