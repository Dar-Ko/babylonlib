/*$Workfile: H:\_SrcPool\Cpp\KWinVerG.inl$: header file
  $Revision: 1.1 $ $Date: 2002/09/06 22:22:42 $
  $Author: ddarko $

  Detect operating system and Windows platform version using GetVersion()
  function.
  Copyright: CommonSoft Inc.
  Jan 97 D.Kolakovic
 */

#ifndef __KWINVERG_INL__
  //KWinVerG.inl sentry
  #define __KWINVERG_INL__

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

//#include <AfxWin.h>
#include <Windows.h>

  //Mask used to extract high order bit from dwVersion variable
  //
  //Note: Microsoft Windows specific (Win).
const unsigned long CST_MASKHIGHBIT = 0x80000000L;

//IsWinNT()--------------------------------------------------------------------
/*Returns TRUE if windows version is WinNT or Win2k.
  Different operating system platforms are using the high order bit and 
  the low order byte as shown in the following table:

    Platform  | High-order Remaining bits      Low-order byte  
              |  bit       in the high-order   (major number)
              |            word
    ----------+----------------------------------------------
    Win2k     |    0       build number              5 
    WinNT     |    0       build number           3 or 4 
    Win95/98  |    1       reserved                  4 
    Win32s    |    1       build number              3 
    
  Note: Microsoft Windows specific (Win).  
 */
inline BOOL IsWinNT(DWORD& dwVersion)
  {
  return ((dwVersion & CST_MASKHIGHBIT) == FALSE);
  }
inline BOOL IsWinNT()
  { 
  DWORD dwVersion = ::GetVersion();
  return IsWinNT(dwVersion);
  }

//IsWin32s()-------------------------------------------------------------------
/*Returns TRUE if windows version is Win32s.

  Note: Microsoft Windows specific (Win).
 */
inline BOOL IsWin32s(DWORD& dwVersion)
  { 
  //If the highbit returned from GetVersion is 1, then it's either Win32s or 
  //Win9x.
  //To distinguish Win32s from Win9x, check major version number (in the
  //LOBYTE of the LOWORD is 3 for the Win32s).
  return((BOOL)(!(IsWinNT(dwVersion)) && (LOBYTE(LOWORD(dwVersion))==3)));
  }
inline BOOL IsWin32s()
  { 
  DWORD dwVersion = ::GetVersion();
  return IsWin32s(dwVersion);
  }

//IsWin9x()--------------------------------------------------------------------
/*Returns TRUE if windows version is Win95 or Win98.

  Note: Microsoft Windows specific (Win).
 */
inline BOOL IsWin9x(DWORD& dwVersion)
  { return ((BOOL)(!(IsWinNT(dwVersion) && !(IsWin32s(dwVersion)))) ); }
inline BOOL IsWin9x()
  {
  DWORD dwVersion = ::GetVersion();
  return IsWin9x(dwVersion);
  }

///////////////////////////////////////////////////////////////////////////////
#endif  //__KWINVERS_H__
