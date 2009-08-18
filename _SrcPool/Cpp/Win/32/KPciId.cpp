/*$RCSfile: KPciId.cpp,v $: implementation file
  $Revision: 1.1 $ $Date: 2009/08/18 19:02:28 $
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

//-----------------------------------------------------------------------------
/*
  Note: Microsoft Windows 98 specific (Win9x);
        Microsoft Windows 2000 specific (Win2k).

  Returns: true

  See also:
 */
bool bool PciId(LPCTSTR szDeviceName,
                LPPCIID pPciId
               )
{
TRACE(_T("PciId()\n"));
return false;
}

///////////////////////////////////////////////////////////////////////////////
#endif //_WIN32
/*****************************************************************************
 * $Log: KPciId.cpp,v $
 * Revision 1.1  2009/08/18 19:02:28  ddarko
 * Created
 *
 *****************************************************************************/
