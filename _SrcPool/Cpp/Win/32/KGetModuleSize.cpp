/*$RCSfile: KGetModuleSize.cpp,v $: implementation file
  $Revision: 1.1 $ $Date: 2012/10/26 20:24:44 $
  $Author: ddarko $

  Obtain virtual size of the module image
  2010-04-24 babylonlib.sourceforge.net
 */
// Group=Windows

#ifdef _WIN32

#include "stdafx.h"
#include <winbase.h>

extern "C" DWORD GetModuleSize(LPTSTR szModule);

//-----------------------------------------------------------------------------
/*
 name of the loaded module (either
      a .dll or .exe file). If the file name extension is omitted, the default library extension .dll is appended.
  The file name string can include a trailing point character (.) to indicate 
  that the module name has no extension. The string does not have to specify
  a path. When specifying a path, be sure to use backslashes (\), not forward
  slashes (/). The name is compared (case independently) to the names of
  modules currently mapped into the address space of the calling process. 
  If this parameter is NULL, GetModuleHandle returns a handle to the file used
  to create the calling process (.exe file).

  Return the size of the module in case of success. If the function fails,
  the return value is 0. To get extended error information, call GetLastError().
 */
DWORD GetModuleSize(LPTSTR szModule //[in] name of the loaded module or NULL
                   )
{
HMODULE hModule = GetModuleHandle(szModule);
if(hModule == NULL)
  return 0;
IMAGE_DOS_HEADER* pDOSHeader = (IMAGE_DOS_HEADER*)hModule;
//Get PE header
IMAGE_NT_HEADERS* pNTHeaders =(IMAGE_NT_HEADERS*)((BYTE*)pDOSHeader + pDOSHeader->e_lfanew);
return pNTHeaders->OptionalHeader.SizeOfImage; //size of the image, in bytes, including all headers
}
///////////////////////////////////////////////////////////////////////////////
#endif //_WIN32
/*****************************************************************************
 * $Log: KGetModuleSize.cpp,v $
 * Revision 1.1  2012/10/26 20:24:44  ddarko
 * Moved to CVS
 *
 *****************************************************************************/