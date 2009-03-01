/*$RCSfile: KVerComCtl32.h,v $: header file
  $Revision: 1.2 $ $Date: 2009/03/01 03:40:27 $
  $Author: ddarko $

  Obtains version information about a specified module
  Copyright: CommonSoft Inc
  2003-02-17 Darko Kolakovic
 */
// Group=Windows

#ifndef __KVERCOMCTL32_H__
  //$RCSfile: KVerComCtl32.h,v $ sentry
  #define __KVERCOMCTL32_H__

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif


//-----------------------------------------------------------------------------
/*Obtains version of Common Controls module comctl32.dll.

  Returns module's minor and major version number as lower and higher WORD.
  Default version number returned is 4.0.
 */
DWORD GetVersionComCtl32()
{

HMODULE hModule = ::GetModuleHandleA("Comctl32.dll");
ASSERT(hModule != NULL);

DLLGETVERSIONPROC pfDllGetVersion =
   reinterpret_cast<DLLGETVERSIONPROC>(::GetProcAddress(hModule,
                                                        "DllGetVersion"));
DWORD dwVersion = MAKELONG(0, 4); //default result

if(pfDllGetVersion != NULL)
  {
  DLLVERSIONINFO dvi = { sizeof(DLLVERSIONINFO), 0, 0, 0, 0 };
  HRESULT hr = (*pfDllGetVersion)(&dvi);
  if(SUCCEEDED(hr))
    {
    ASSERT(dvi.dwMajorVersion <= 0xFFFF);
    ASSERT(dvi.dwMinorVersion <= 0xFFFF);
    dwVersion = MAKELONG(dvi.dwMinorVersion, dvi.dwMajorVersion);
    }
  }
return dwVersion;
}

#endif //__KVERCOMCTL32_H__
/////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: KVerComCtl32.h,v $
 * Revision 1.2  2009/03/01 03:40:27  ddarko
 * formatting
 *
 * Revision 1.1  2009/03/01 03:38:42  ddarko
 * Created
 *
 *****************************************************************************/
