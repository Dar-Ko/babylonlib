/*$RCSfile: KUsbDeviceInfo.cpp,v $: implementation file
  $Revision: 1.1 $ $Date: 2009/08/28 13:57:26 $
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


#include "KUsbDeviceInfo.h" //CUsbDeviceInfo class

///////////////////////////////////////////////////////////////////////////////
//CUsbDeviceInfo class implementation


///////////////////////////////////////////////////////////////////////////////

/*****************************************************************************
 * $Log: KUsbDeviceInfo.cpp,v $
 * Revision 1.1  2009/08/28 13:57:26  ddarko
 * Extracted from KUsbHub
 *
 *****************************************************************************/
