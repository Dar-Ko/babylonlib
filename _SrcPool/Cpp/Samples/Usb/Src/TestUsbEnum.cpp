/*$RCSfile: TestUsbEnum.cpp,v $: implementation file
  $Revision: 1.4 $ $Date: 2009/07/08 21:50:41 $
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
#ifdef _USE_STL
//#include <iostream> //std::endl
#endif

#include "UsbVid.h"  //USB VID List
//#include "KWinUsb.h" //TUsbSymbolicName template
#include "KUsbHub.h"   //CUsbHub class
#include "KStrArray.h" //CStringArray class

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

_UNUSED(nVendorId);
_UNUSED(nProductId);

bool bResult = true;
try
  {
  //Test log  creation
  g_logTest.m_bResult = false;           //result of the test

  //Enumerate USB Host controlers
  g_logTest.m_szObjectName = _T("EnumerateHostControllers()");
  g_logTest.m_szFileName   = _T("KUsbEnumRootHub.cpp"); //function or object file name

  extern unsigned int EnumerateHostControllers(CStringArray* pList = NULL);
  unsigned nHcdCount = EnumerateHostControllers();
  bResult = true;

  TsWriteToView(_T(" Usb host controllers found: "));
  TsWriteToViewLn(nHcdCount);

  g_logTest.LogResult(bResult); //Log object's construction

  //Enumerated USB root hubs
  g_logTest.m_szObjectName = _T("EnumerateRootUsbHub()");
  g_logTest.m_szFileName   = _T("KUsbEnumRootHub.cpp"); //function or object file name

  extern unsigned int EnumerateRootUsbHub(CStringArray* pList = NULL);
  unsigned nHubCount = EnumerateRootUsbHub();

  TsWriteToView(_T(" USB root hubs found: "));
  TsWriteToViewLn(nHubCount);
  bResult = (nHcdCount == nHubCount); //Number of USB root hubs enumerated with two
                                      //different methods have to be same.
  g_logTest.LogResult(bResult);

  if(bResult)
    {
    g_logTest.m_szObjectName = _T("CUsbHostController::CUsbHostController()");
    g_logTest.m_szFileName   = _T("KUsbHub.h"); //function or object file name

    CUsbHostController usbHc;
    g_logTest.LogResult(bResult); //Log object's construction

    g_logTest.m_szObjectName = _T("CUsbHostController::FindFirst()");
    #ifdef _WIN32
      g_logTest.m_szFileName   = _T("KWinUsbHub.cpp"); //function or object file name
    #elif defined(_LINUX)
      g_logTest.m_szFileName   = _T("KLinUsbHub.cpp"); //function or object file name
    #else
      g_logTest.m_szFileName   = _T("unknown implementation");
    #endif

    usbHc.FindFirst();

    g_logTest.LogResult(bResult); //Log object's construction

//    g_logTest.m_szObjectName = _T("CUsbHub::CUsbHub()");
//    g_logTest.m_szFileName   = _T("KUsbHub.h"); //function or object file name

    //Find given USB device
//    CUsbHub usbHub;
//    g_logTest.LogResult(bResult); //Log object's construction
    }

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
 *Revision 1.4  2009/07/08 21:50:41  ddarko
 *CUsbHostController
 *
 *Revision 1.3  2009/07/06 19:00:10  ddarko
 *Tes HDC and root hubs enumeration
 *
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
