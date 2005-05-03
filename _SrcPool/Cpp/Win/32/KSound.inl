/*$Workfile: KSound.inl$: header file
  $Revision: 3$ $Date: 2003-08-25 02:55:14$
  $Author: Darko$

  Sound helper
  Copyright: CommonSoft Inc.
  Jan 97  1st Version D.Kolakovic
 */

#ifndef _KSOUND_INL_
    //KSound.inl sentry
  #define _KSOUND_INL_


#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

 //Command to linker to search for WinMM.lib
#pragma comment( lib, "WinMM" )

  //Disable  warning C4201: nonstandard extension used : nameless struct/union
#pragma warning( disable : 4201)
#include <MMSystem.h>
#include "KFindRes.h" //FindResourceHandle()

#pragma warning( default : 4201)
BOOL PlaySound(const UINT nIDS,HINSTANCE hInst = NULL);
//PlaySound()------------------------------------------------------------------
/*Plays .Wav sound from the resource. The sound specified by pszSound must fit 
  into available physical memory and be playable by an installed waveform-audio
  device driver.

  Returns: TRUE if successful or FALSE otherwise.

  Note: in Win32s SND_ALIAS, SND_FILENAME, and SND_NOWAIT flags are not supported.

  Note: Microsoft Windows specific (Win).
 */
inline BOOL PlaySound(const UINT nIDS,HINSTANCE hInst)
{
LPCTSTR lpszResource = (LPCTSTR) MAKEINTRESOURCE(nIDS);
if (hInst == NULL)
  hInst = FindResourceHandle(lpszResource, // address of resource name  
                             _T("WAVE"));
#ifdef _DEBUG
  if (::FindResource(hInst,         // resource-module handle 
                     lpszResource,  // address of resource name  
                     _T("WAVE"))    // address of resource type 
                      == NULL)
    {
    TRACE1("PlaySound(%d) failure!\n",nIDS);
    ASSERT(FALSE);
    return FALSE;
    }
#endif

return (::PlaySound(lpszResource, hInst, SND_RESOURCE | SND_ASYNC)); 
};

///////////////////////////////////////////////////////////////////////////////
#endif //_KSOUND_INL_
