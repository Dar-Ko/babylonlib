/*$Workfile: KWn32s16.cpp$: implementation file
  $Revision: 4$ $Date: 2002-03-08 01:50:32$
  $Author: Darko Kolakovic$

  Get the version number information for Win32s
  Copyright: CommonSoft Inc
  Microsoft KB Q125014
  Jan 94 Darko Kolakovic
*/

#ifndef __AFX_H__
  #include <Windows.h>
#endif

#ifndef _WIN32 //~_Win32 for  16-bit application
               //32-bit application should use GetVersionEx()
///////////////////////////////////////////////////////////////////////////////
// 16-bit application

// The WIN32SINFO data structure contains operating system version information.
//
// Note: There is no header file in the SDK which has a definition
// for the WIN32SINFO structure.  
typedef struct _tagWIN32SINFO
  { 
  BYTE bMajor;
  BYTE bMinor;
  WORD wBuildNumber;
  BOOL fDebug;
  } WIN32SINFO, FAR * LPWIN32SINFO;


//BOOL GetWin32sVersion()------------------------------------------------------
/*Get version number information for Win32s installed on a 16-bit Windows OS.
  Win32s Release versions and corresponding build numbers: 

     Win32s version    Build
          1.1          1.1.88
          1.1a         1.1.89
          1.15         1.15.103
          1.15a        1.15.111
          1.2          1.2.123
          1.25         1.2.141
          1.25a        1.2.142
          1.30         1.2.159
          1.30a        1.2.166
          1.30c        1.2.172

  Note: Microsoft Windows 16b specific (Win16). 

  History:  
            KB Q125014
            Jan 94 D.K.
  Example:

    #include <StdIO.h>
    if(IsWin32s())
     {
     int iMajor;
     int iMinor;
     int iBuild;
     if(GetWin32sVersion(&iMajor,&iMinor,&iBuild))
       {
       wprintf("Win32s %d.%d.$d",iMajor,iMinor,iBuild);
       }
     }
 */
BOOL FAR PASCAL GetWin32sVersion(int* piMajor, //resulting major version number
                                 int* piMinor, //resulting minor version number
                                 int* piBuild  //resulting build number
                                 )

{ 

BOOL       bRes = FALSE;
FARPROC    lpfnGetWin32sInfo;
HANDLE     hDLL;
WIN32SINFO Info;

//LoadLibrary() and GetProcAddress() are used because the function GetWin32sInfo()
//did not exist in Win32s 1.0.

hDLL = LoadLibrary("W32SYS.DLL");

if (hDLL > HINSTANCE_ERROR) 
  {
  lpfnGetWin32sInfo = GetProcAddress(hDLL, "GETWIN32SINFO");
  if (lpfnGetWin32sInfo) 
    {
        // Win32s version 1.1 is installed
    if ((*lpfnGetWin32sInfo)((LPWIN32SINFO) &Info) == 0) 
      {
      //Indicates whether Win32s is loaded and Win32s VxD is functional. 
      bRes = TRUE;
      *piMajor = Info.bMajor;
      *piMinor = Info.bMinor;
      *piBuild = Info.wBuildNumber;
      }
    else
      bRes = FALSE;    //Win32s VxD not loaded.
    }
  else 
    {
        //Win32s version 1.0 is installed.
    *piMajor = 1;
    *piMinor = 0;
    *piBuild = 0;
    bRes = TRUE;
    }
  FreeLibrary(hDLL);
  } 
else   //Win32s not installed.
  bRes = FALSE;

return bRes;
};

///////////////////////////////////////////////////////////////////////////////
#else
  #pragma message (__FILE__ " GetWin32sVersion(): 32-bit application should use GetVersionEx()")
#endif  //_Win32
