/*$Workfile: KUsbHub.h$: header file
  $Revision: 1.1 $ $Date: 2009/07/02 20:31:15 $
  $Author: ddarko $

  USB Hub handler
  Note: Microsoft Windows specific (Win).
  Copyright: CommonSoft Inc
  2004-03-09 Darko Kolakovic
 */
// Group=Windows

#ifndef _KUSBHUB_H_
    //$Workfile: KUsbHub.h$ sentry
  #define _KUSBHUB_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#ifdef _WIN32 //Windows 32-bit platform

#ifndef _USE_ATL
  #include <windows.h>
#endif
#include <setupapi.h> //Device Management Structures

///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" LPTSTR StrIStr(LPCTSTR szSource, LPCTSTR szToken);

LPCTSTR GetDeviceDesc(LPCTSTR szDriverRegistryName);

///////////////////////////////////////////////////////////////////////////////
/*Handles the USB hub.
  A USB hub is a device that allows many USB devices to be connected to a
  single USB port on the host computer or another hub.

  Note: Microsoft Windows specific (Win32).

  See also:
 */
class CUsbHub
{
public:
  CUsbHub();

  ~CUsbHub();
  uint_fast32_t Enumerate();
  bool IsWinNt() const;
  bool GetDeviceProperty(HDEVINFO hDevInfo,SP_DEVINFO_DATA* psdiDevinfo,
                         const DWORD dwProperty, TCHAR* szBuff, DWORD& dwLen);
protected:
  bool IsRootHub(const TCHAR* szUsbDriverKeyName) const;
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*Default constructor
 */
inline CUsbHub::CUsbHub()
{
}

inline CUsbHub::~CUsbHub()
{
}

//-----------------------------------------------------------------------------
/*
 */
inline bool CUsbHub::IsWinNt() const
{
return (GetVersion() < 0x80000000);
}

//-----------------------------------------------------------------------------
/*
 */
inline bool CUsbHub::IsRootHub(const TCHAR* szUsbDriverKeyName //[in]
              ) const
{
if ((szUsbDriverKeyName != NULL) && (szUsbDriverKeyName[0] != '\0'))
  {
  return (StrIStr(szUsbDriverKeyName, USB_ROOTHUBNAME) != NULL);
  }
return false;
}
///////////////////////////////////////////////////////////////////////////////
#endif //__cplusplus

#endif //_WIN32
///////////////////////////////////////////////////////////////////////////////
#endif  //_KUSBHUB_H_
/*****************************************************************************
 * $Log: KUsbHub.h,v $
 * Revision 1.1  2009/07/02 20:31:15  ddarko
 * Moved from platform specific directory
 *
 *****************************************************************************/
