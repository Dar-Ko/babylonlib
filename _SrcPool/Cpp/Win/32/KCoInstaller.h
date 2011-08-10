/*$RCSfile: KCoInstaller.h,v $: header file
  $Revision: 1.1 $ $Date: 2011/08/10 18:53:33 $
  $Author: ddarko $

  Microsoft Windows Windows NT Setup and Device Installer services DLL helper.
  Copyright: Darko Kolakovic
  Darko Kolakovic  2010-01-15
*/
// Group=Windows

#ifndef _KCOINSTALLER_H_
  //$RCSfile: KCoInstaller.h,v $ sentry
  #define _KCOINSTALLER_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#include <setupapi.h>

#ifndef CALLBACK
  #define CALLBACK    __stdcall
#endif

///////////////////////////////////////////////////////////////////////////////
/*
  Co-installers are called by Setup API when installing the device for which 
  the co-installer is registered.

  Note: Microsoft Windows specific (Win32).

  See also: Setup API; ""
  {html:<a href="http://msdn.microsoft.com/en-us/library/ff540146%28VS.85%29.aspx" title="MSDN">
  MSDN: Co-installer Operation  </a>}
 
 */
typedef DWORD (CALLBACK* COINSTALLER_PROC) (
    DI_FUNCTION  difInstallFunction,   //[in] device installation request code
    HDEVINFO  hDeviceInfoSet,          //[in] handle to a device information set
    PSP_DEVINFO_DATA pDeviceInfoData,  //[in] device-specific information or NULL
    PCOINSTALLER_CONTEXT_DATA  Context //[in/out] installation request description
    );

///////////////////////////////////////////////////////////////////////////////
#endif  //_KCOINSTALLER_H_
/*****************************************************************************
 * $Log: KCoInstaller.h,v $
 * Revision 1.1  2011/08/10 18:53:33  ddarko
 * Moved from C Setup
 *
 *****************************************************************************/
