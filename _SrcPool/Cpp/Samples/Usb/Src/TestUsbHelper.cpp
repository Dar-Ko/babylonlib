/*$RCSfile: TestUsbHelper.cpp,v $: implementation file
  $Revision: 1.2 $ $Date: 2009/09/02 17:35:33 $
  $Author: ddarko $

  Test USB helper methods
  2009-08-31 Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"
#include "KProgCst.h"
#include "KUsbDeviceInfo.h" //CUsbDeviceInfo class

extern bool TsWriteToViewLn(LPCTSTR lszText);
extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(const unsigned int& nValue);
extern bool TsWriteToView(const unsigned int& nValue);

extern CTestLog g_logTest;   //general test logger

//-----------------------------------------------------------------------------
/*Validates a various helper methods for handling USB information.

  Returns true if test is successful; otherwise returns false.

  Note: uses Standard Template Library (STL).

  See also: CUsbDeviceInfo
 */
bool TestUsbHelper(uint16_t nVendorId , //[in] = 0 USB Vendor ID (VID)
                   uint16_t nProductId  //[in] = 0 USB Product ID (PID)
                  )
{
TsWriteToViewLn(_T("Test USB Helpers"));

_UNUSED(nVendorId);
_UNUSED(nProductId);

bool& bResult = g_logTest.m_bResult;
bResult = false;

try
  {
  CUsbDeviceInfo usbDevInfo;
  struct STestPortNo
    {
    LPCTSTR szTest;
    bool    bTest;
    } arrTestPortNo[] =
      {
      NULL                    , false, // 0: F 0:0:0:0:0:0
      _T("")                  , false, // 1: F 0:0:0:0:0:0
      ALPHANUMERICSET1T       , false, // 2: F 0:0:0:0:0:0
      _T("0")                 , true , // 3: T 0:0:0:0:0:0
      _T("1")                 , true , // 4: T 1:0:0:0:0:0
      _T("0:1")               , true , // 5: T 0:0:0:0:0:0
      _T("5\t1")              , false, // 6: F 5:0:0:0:0:0
      _T("1:2:0")             , true , // 7: T 1:2:0:0:0:0
      _T("!:2:3:\05")         , false, // 8: F 0:0:0:0:0:0
      _T("9:10:11:\015")      , false, // 9: F 9:10:11:0:0:0
      _T("::12:13\0")         , false, // A: F 0:0:0:0:0:0
      _T("1:2:3:4:5:6:7:8:9") , false, // B: F 1:2:3:4:5:6
      _T("1:2G")              , false, // C: F 1:2:0:0:0:0
      _T("1:78000:2")         , false, // D: F 1:78000:0:0:0:0
      _T("21:22:23:24:25:26") ,  true  // E: T 21:22:23:24:25:26
      };

  //Test parsing device name
  g_logTest.m_szObjectName = _T("CUsbDeviceInfo::SetPortNo(LPCTSTR)");
  g_logTest.m_szFileName   = _T("KUsbDeviceInfo.cpp"); //function or object file name

  CString strPortNo;
  int i = 0;
  while (i < SIZEOFARR(arrTestPortNo))
    {
    bResult = (usbDevInfo.SetPortNo(arrTestPortNo[i].szTest) == 
               arrTestPortNo[i].bTest);
    TsWriteToViewLn(usbDevInfo.GetPortNo(strPortNo));
    if(!bResult)
      break;
    i++;
    }
  g_logTest.LogResult();
  if(bResult)
    {
    g_logTest.m_szObjectName = _T("CUsbDeviceInfo::GetPortNo(CString&)");
    g_logTest.LogResult();
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
 *$Log: TestUsbHelper.cpp,v $
 *Revision 1.2  2009/09/02 17:35:33  ddarko
 *test structure
 *
 *Revision 1.1  2009/09/01 21:52:21  ddarko
 *Validating limits of port Id
 *
 *****************************************************************************/
