/*$Workfile: KUsbHub.h$: header file
  $Revision: 1.2 $ $Date: 2009/07/02 21:44:13 $
  $Author: ddarko $

  Universal Serial Bus (USB) Host Controller
  Copyright: CommonSoft Inc
  2004-03-09 Darko Kolakovic
 */

#ifndef _KUSBHUB_H_
    //$Workfile: KUsbHub.h$ sentry
  #define _KUSBHUB_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif


///////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
//extern "C" LPTSTR StrIStr(LPCTSTR szSource, LPCTSTR szToken);

//LPCTSTR GetDeviceDesc(LPCTSTR szDriverRegistryName);

///////////////////////////////////////////////////////////////////////////////
/*Handles the USB hub.
  A USB hub is a device that allows many USB devices to be connected to a
  single USB port on the host computer or another hub.

  See also:
 */
class CUsbHub
{
public:
  CUsbHub();

  ~CUsbHub();
  uint_fast32_t Enumerate();

#ifdef WIN_SPECIFIC
//  Note: Microsoft Windows specific (Win32).
  bool IsWinNt() const;
  bool GetDeviceProperty(HDEVINFO hDevInfo,SP_DEVINFO_DATA* psdiDevinfo,
                         const DWORD dwProperty, TCHAR* szBuff, DWORD& dwLen);
protected:
  bool IsRootHub(const TCHAR* szUsbDriverKeyName) const;
#endif
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

#ifdef WIN_SPECIFIC ////////////TODO: remove D.K.

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
#endif   //////////////////////////End TODO

///////////////////////////////////////////////////////////////////////////////
#endif //__cplusplus

///////////////////////////////////////////////////////////////////////////////
#endif  //_KUSBHUB_H_
/*****************************************************************************
 * $Log: KUsbHub.h,v $
 * Revision 1.2  2009/07/02 21:44:13  ddarko
 * Excluded some Windows specifics
 *
 * Revision 1.1  2009/07/02 20:31:15  ddarko
 * Moved from platform specific directory
 *
 *****************************************************************************/
