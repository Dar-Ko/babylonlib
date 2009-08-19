/*$RCSfile: TestCommonUsb.cpp,v $: implementation file
  $Revision: 1.3 $ $Date: 2009/08/19 21:09:37 $
  $Author: ddarko $

  Testing USB routines.

  Copyright: CommonSoft Inc.
  2008-09-26 Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"

//Type definition of function used in testing
typedef bool (*PFUNC_TESTUSB) (uint16_t, uint16_t);

extern bool TsWriteToViewLn(LPCTSTR lszText);
extern bool TestFindUsbHid(uint16_t nVendorId = 0, uint16_t nProductId = 0);
extern bool TestUsbEnum(uint16_t nVendorId = 0, uint16_t nProductId = 0);
extern bool TestUsbLib(uint16_t nVendorId = 0, uint16_t nProductId = 0);

int TestCommonUsb(uint16_t nVendorId = 0, uint16_t nProductId = 0);

//-----------------------------------------------------------------------------
/*Validates USB methods.
  Defines the entry point for the test.

  Returns: EXIT_SUCCESS, which represents a value of 0, if succesful. Otherwise
  a non-zero error code is returned.
 */
int TestCommonUsb(uint16_t nVendorId , //[in] = 0 USB Vendor ID (VID)
                  uint16_t nProductId  //[in] = 0 USB Product ID (PID)
                 )
{
TsWriteToViewLn(_T("Start validation of various USB methods"));
TsWriteToViewLn(_T(""));

PFUNC_TESTUSB funcTest[] =
  {
  //TODO: add Test
  TestUsbEnum,
  TestUsbLib,
  TestFindUsbHid,
  NULL
  };

int iTestCount = 0;
while (iTestCount < (sizeof(funcTest)/sizeof(PFUNC_TESTUSB)) )
  {
  if ((funcTest[iTestCount] != NULL) && funcTest[iTestCount](nVendorId, nProductId))
    {
    TsWriteToViewLn(LOG_SUCCESS);
    TsWriteToViewLn(_T(""));
    }
  else
    {
    TsWriteToViewLn(LOG_FAILURE);
    return EXIT_FAILURE + 50 + iTestCount;
    }
  iTestCount++;
  }

return EXIT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: TestCommonUsb.cpp,v $
 * Revision 1.3  2009/08/19 21:09:37  ddarko
 * Test LIBUSB-WIN32
 *
 * Revision 1.2  2009/06/26 21:35:35  ddarko
 * Added new test case
 *
 * Revision 1.1  2008/09/26 21:06:01  ddarko
 * Created
 *
 *****************************************************************************/
