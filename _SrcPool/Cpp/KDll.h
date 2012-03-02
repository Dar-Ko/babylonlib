/*$RCSfile: KDll.h,v $: header file
  $Revision: 1.11 $ $Date: 2012/03/02 23:29:06 $
  $Author: ddarko $

  Helper class encapsulating a dynamic-link library (DLL) loading.
  Copyright: ddarko, see GPL
  Darko Kolakovic 2002-05-05
 */

#ifndef _KDLL_H_
  //$RCSfile: KDll.h,v $ sentry
  #define _KDLL_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif


#ifdef _WIN32
  #ifndef _ASSERT
    #include <crtdbg.h>
  #endif

  #ifndef TRACE
    #ifdef _UNICODE
      #define TRACE(msg) _RPTW0(_CRT_WARN, msg)
    #else
      #define TRACE(msg) _RPT0(_CRT_WARN, msg)
    #endif
  #endif TRACE

  #ifndef TRACE1
    #ifdef _UNICODE
      #define TRACE1(msg, arg1) _RPTW1(_CRT_WARN, msg, arg1)
    #else
      #define TRACE1(msg, arg1) _RPT1(_CRT_WARN, msg, arg1)
    #endif
  #endif TRACE1

  #ifndef TRACE2
    #ifdef _UNICODE
      #define TRACE2(msg, arg1, arg2) _RPTW2(_CRT_WARN, msg, arg1, arg2)
    #else
      #define TRACE2(msg, arg1, arg2) _RPT2(_CRT_WARN, msg, arg1, arg2)
    #endif
  #endif //TRACE2

  #ifndef _T
    #define _T(Text) TEXT(Text)
  #endif

#endif //_WIN32

///////////////////////////////////////////////////////////////////////////////
//Helper class encapsulating a Dynamic-Link Library (DLL) loading.
//
class CDll
{
public:
  CDll();
  CDll(LPCTSTR szDllName);
  ~CDll();
  bool Load(LPCTSTR szDllName);
  bool Free();
  bool IsOpen() const;
  void* GetSymbolAdr(LPCTSTR szSymbolName) const;
  operator HMODULE() const;
  void* operator() (LPCTSTR szSymbolName) const;

protected:
  HMODULE m_hLibrary; //handle to the module

private:
  CDll(const CDll&);
  CDll& operator=(const CDll&);
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*Default constructor.
 */
inline CDll::CDll() :
   m_hLibrary(NULL)
{
}

inline CDll::CDll(LPCTSTR szDllName //[in] null-terminated string that names
                                    //the DLL file.
                  ) :
   m_hLibrary(NULL)
{
Load(szDllName);
}

//-----------------------------------------------------------------------------
/*Destructor
 */
inline CDll::~CDll()
{
Free();
}

//-----------------------------------------------------------------------------
/*Returns handle to the module.
 */
inline CDll::operator HMODULE() const
{
return m_hLibrary;
}

//-----------------------------------------------------------------------------
/*Obtains the address of an exported symbol in the DLL
  Returns address of the symbol or NULL in case of failure.
  
  Example:
     #include "KDll.h"
     typedef void (*PFDLLFUNC)();
     ...
     CDll dllMyLib("DllName");
     if (dllMyLib.IsOpen())
      {
      
      PFDLLFUNC SomeFunc = (PFDLLFUNC)dllMyLib("SomeFuncName");
      if (SomeFunc != NULL)
        SomeFunc();
      dllMyLib.Free();
      }
  
 */
inline void* CDll::operator() (LPCTSTR szSymbolName //[in] null-terminated string
                                                   //containing the symbol name
                               ) const
{
return GetSymbolAdr(szSymbolName);
}

#if defined (_WIN32) || defined (_WIN16)
//-----------------------------------------------------------------------------
/*This function maps the specified DLL file into the address space of the calling
  process.

  With both implicit and explicit linking, Windows first searches for system DLLs,
  such as Kernel32.dll and User32.dll. Windows then searches for the DLLs in
  the following sequence:
    1. The absolute path, if specified by the DLL file name parameter
    2. The directory where the executable module for the current process is located.
    3. The current directory.
    4. The Windows system directory.
    5. The Windows directory.
    6. The directories listed in the PATH environment variable.

   WinCE specific:
    1. The absolute path specified by the DLL file name parameter
    2. The .exe launch directory
    3. The Windows directory
    4. ROM DLL files
    5. An OEM-specified search path,

  Returns true if the module is successfuly loaded.
 */
inline
bool CDll::Load(LPCTSTR szDllName //[in] null-terminated string that names
                                   //the DLL file.
               )
{
 //Reload the library
Free();

#if definded (_WIN16)
  //Load a 32-bit DLL within 16-bit code
  m_hLibrary = (HMODULE)::LoadLibraryEx32W(szDllName, NULL, 0);
#elif defined (_WIN32_WCE) //WinCE
  _ASSERT(sizeof(HINSTANCE) == sizeof(HMODULE));
  m_hLibrary = static_cast<HMODULE>(::LoadLibrary(szDllName));
#else  //WIN32, WIN64
  /*Note Windows Me/98/95:  If you are using LoadLibrary to load a module that
    contains a resource whose numeric identifier is greater than 0x7FFF,
    LoadLibrary fails. If you are attempting to load a 16-bit DLL directly from
    32-bit code, LoadLibrary fails. If you are attempting to load a DLL whose
    subsystem version is greater than 4.0, LoadLibrary fails.
    If your DllMain function tries to call the Unicode version of a function,
    LoadLibrary fails.
   */
  m_hLibrary = ::LoadLibrary(szDllName);
#endif

DWORD dwErr = ::GetLastError();
TRACE2(_T("  ::LoadLibrary(%s) GetLastError = 0x%X.\n"), szDllName, dwErr);

if (!IsOpen())
  {
  TRACE2(_T("CDll::Load(%s) failed (Error 0x%X)\n"), szDllName, dwErr);
  if(dwErr == ERROR_MOD_NOT_FOUND)
    {
    /*BUG: LoadLibrary and LoadLibraryEx Functions Fail If Directory Name Contains
           a Period.
      Windows specific

      The LoadLibrary or the LoadLibraryEx function may fail with error 126
      (ERROR_MOD_NOT_FOUND) if a directory name in the path contains a period.
      According to the Microsoft Platform Software Development Kit (SDK)
      documentation for LoadLibrary and LoadLibraryEx, if you do not include the
      file name extension with the file name, the system tries to load a file with
      no extension. If such a file does not exist, the .dll extension is appended
      to the file name, and the system tries to load the file again.
      The error occurs only if the directory in the path that is passed to
      LoadLibrary or LoadLibraryEx contains a period (.) and if no extension is
      appended to the .dll file name.
      To work around this problem, specify a fully qualified file name that includes
      the file name extension:
          hDll = LoadLibrary("C:\\MY.DLLs\\ABC.DLL");
      instead
          hDLL = LoadLibrary("C:\\MY.DLLs\\ABC"); //Failed with ERROR_MOD_NOT_FOUND
       Ref:. MSDN Article ID: 324468
     */
     TRACE(_T("  The specified module could not be found!\n"));
     }
  return false; //Failure
  }
else
  {
  if(dwErr == ERROR_BAD_EXE_FORMAT)
    {
    //TODO: Why some dlls return follwing status:
    //"not a valid Win32 application. 193(0x00C1)"?
    SetLastError(NO_ERROR);
    }
  return true; //Success
  }
}

//-----------------------------------------------------------------------------
/*
 */
inline bool CDll::IsOpen() const
{
return (m_hLibrary > NULL); //>= (HINSTANCE)32
}

//-----------------------------------------------------------------------------
/*Obtain the address of an exported function in the DLL.
  Because you are calling the DLL function through a pointer and there is
  no compile-time type checking, make sure that the parameters to the function
  are correct so that you do not overstep the memory allocated on the stack and
  cause an access violation.

  Returns the address of the exported function or variable, if the function succeeds.
  If the function fails, the return value is NULL. To get extended error information,
  call GetLastError().
 */
inline void* CDll::GetSymbolAdr(LPCTSTR szSymbolName //[in] function or variable name
                              //or the function's ordinal value. If this parameter is
                              //an ordinal value, it must be in the low-order word;
                              //the high-order word must be zero.
                              ) const
{
_ASSERT(IsOpen());
return (void*)::GetProcAddress(m_hLibrary, szSymbolName);
}

//-----------------------------------------------------------------------------
/*This function decrements the reference count of the loaded DLL module.
  When the reference count reaches zero, the module is unmapped from the address
  space of the calling process.
 */
inline bool CDll::Free()
{
if (IsOpen())
  {
  if (::FreeLibrary(m_hLibrary) == FALSE)
    {
    #ifdef _DEBUG
      DWORD dwError = GetLastError();
      TRACE2(TEXT("  FreeLibrary(%08X) failed 0x%08x!\n"), m_hLibrary, dwError);
    #endif
    //TODO GetLastError()
    return false;
    }
   m_hLibrary = NULL; //FixMe: Even if it is handle < 32
  }
return true;
}
#endif //_Win32 specific

//=============================================================================
#if defined(LINUX) || defined(OS_X)
  #include <dlfcn.h> //interface to dynamic linking loader

  #ifndef HMODULE
    #define HMODULE void*
  #endif

//-----------------------------------------------------------------------------
/*This function maps the specified DLL file into the address space of the calling
  process.

  If the environment variable LD_LIBRARY_PATH was defined to contain
  a colon-separated list of directories, then these are searched.
  This variable is ignored for set-user-ID and set-group-ID programs.

  If szDllName is a NULL pointer, then the returned handle is for the main
  program. This handle resolves symbols in the main program, then sinbols in all 
  shared libraries loaded at program startup and then in all shared libraries loaded 
  with the flag RTLD_GLOBAL.
 
  Returns true if the module is successfuly loaded.
 */
inline
bool CDll::Load(LPCTSTR szDllName //[in] null-terminated string that names
                                   //the shared library file.
               )
{
 //Reload the library
Free();
#ifdef _UNICODE
 #error "Convert shared library name to single byte character string"
#endif
/*Perform lazy binding. Only resolve symbols as the code that references
  them is executed. If the symbol is never referenced, then it is never
  resolved. Lazy binding is only performed for function references; references
  to variables are always immediately bound when the library is loaded.
 */
m_hLibrary = dlopen(szDllName, RTLD_LAZY);

if (!IsOpen())
  {
  #ifdef _DEBUG
    LPSTR szError = dlerror(); //Get description of the most recent error
      if (szError == NULL)
    szError = const_cast<LPSTR>("");
    TRACE2(_T("CDll::Load(%s) failed: %s\n"), szDllName, szError);
  #endif
  return false; //Failure
  }
return true; //Success
}

//-----------------------------------------------------------------------------
/*
 */
inline bool CDll::IsOpen() const
{
return (m_hLibrary > NULL);
}

//-----------------------------------------------------------------------------
/*Obtain the address of an exported function in the DLL.
  Because you are calling the DLL function through a pointer and there is
  no compile-time type checking, make sure that the parameters to the function
  are correct so that you do not overstep the memory allocated on the stack and
  cause an access violation.

   Returns the address of the exported function or variable, if the function succeeds.
   If the function fails, the return value is NULL. To get extended error information,
   call dlerror().
  */
inline void* CDll::GetSymbolAdr(LPCTSTR szSymbolName //[in]
                                ) const
{
_ASSERT(IsOpen());
dlerror();    //Clear any existing error
return dlsym(m_hLibrary, szSymbolName);
}

//-----------------------------------------------------------------------------
/*This function decrements the reference count of the loaded DLL module.
  When the reference count reaches zero, then the dynamic library is unloaded.
 */
inline bool CDll::Free()
{
if (IsOpen())
  {
  if (dlclose(m_hLibrary) != 0)
    {
    #ifdef _DEBUG
      char* szError = dlerror();
    if(szError == NULL)
      szError = const_cast<LPSTR>("");
        TRACE2(TEXT("CDll::Free(0x%08X) failed: %s!\n"), (unsigned)m_hLibrary, szError);
    #endif
    return false;
    }
   m_hLibrary = NULL;
  }
return true;
}
#endif //LINUX
///////////////////////////////////////////////////////////////////////////////
#endif  //_KDLL_H_
/******************************************************************************
 *$Log: KDll.h,v $
 *Revision 1.11  2012/03/02 23:29:06  ddarko
 *Fixed warning
 *
 *Revision 1.10  2012/03/02 23:25:14  ddarko
 *Fixed warning
 *
 *Revision 1.9  2012/03/02 22:22:39  ddarko
 *Linux update
 *
 *Revision 1.7  2012/02/23 18:39:28  ddarko
 *Comment
 *
 *Revision 1.6  2012/02/23 18:11:09  ddarko
 *HMODULE
 *
 *Revision 1.5  2012/02/20 18:02:32  ddarko
 *Comment
 *
 *Revision 1.4  2012/02/20 17:23:14  ddarko
 *Linux version
 *
 *Revision 1.3  2011/09/15 21:23:19  ddarko
 *Constructor initialization
 *
 *Revision 1.2  2011/08/18 21:25:23  ddarko
 *Added quick fix for TRACE
 *
 *Revision 1.1  2011/08/09 20:34:43  ddarko
 *Commited 1st version
 *
 *****************************************************************************/
