/*$RCSfile: KDll.h,v $: header file
  $Revision: 1.4 $ $Date: 2012/02/20 17:23:14 $
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
  operator HINSTANCE() const;
  void* operator() (LPCTSTR szSymbolName) const;
	
protected:
  HINSTANCE m_hLibrary; //handle to the module
  
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
inline CDll::operator HINSTANCE() const
{
return m_hLibrary;
}

//-----------------------------------------------------------------------------
/*Obtains the address of an exported symbol in the DLL
  Returns address of the symbol.
 */
inline void* CDll::operator() (LPCTSTR szSymbolName //[in]
                        ) const
{
return GetSymbolAdr(szSymbolName);
}

#ifdef _WIN32
//-----------------------------------------------------------------------------
/*This function maps the specified DLL file into the address space of the calling
  process. 

  Returns true if the module is successfuly loaded.
 */
inline 
bool CDll::Load(LPCTSTR szDllName //[in] null-terminated string that names 
                                   //the DLL file. 
               ) 
{
 //Reload the library
Free();

#ifndef _WIN16
  _ASSERT(sizeof(HINSTANCE) == sizeof(HMODULE));
  m_hLibrary = static_cast<HINSTANCE>(::LoadLibrary(szDllName));
#else
  m_hLibrary = (HMODULE)::LoadLibraryEx32W(szDllName, NULL, 0);
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
 */
inline void* CDll::GetSymbolAdr(LPCTSTR szSymbolName //[in]
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

  #ifndef HINSTANCE
    #define HINSTANCE int
  #endif
  
//-----------------------------------------------------------------------------
/*This function maps the specified DLL file into the address space of the calling
  process. 

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
  LPSTR szError = dlerror(); //Get description of the most recent error
  if (szError == NULL)
    szError = "";
  TRACE2(_T("CDll::Load(%s) failed: %s\n"), szDllName, szError);
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
  if (dlclose(m_hLibrary) == FALSE)
    {
    #ifdef _DEBUG
      char* szError = dlerror();
	  if(szError == NULL)
	    szError = "";
      TRACE2(TEXT("CDll::Free(%08X) failed: %s!\n"), m_hLibrary, szError);
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
