/*$RCSfile: KDll.h,v $: header file
  $Revision: 1.1 $ $Date: 2011/08/09 20:34:43 $
  $Author: ddarko $

  Helper class encapsulating a dynamic-link library (DLL) loading.
  Copyright: ddarko, see GPL
  Darko Kolakovic 2002-05-05
 */

#ifndef _KDLL_H_
  //KCrc32.h sentry
  #define _KDLL_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#ifndef HINSTANCE
  #define HINSTANCE int
#endif
 
///////////////////////////////////////////////////////////////////////////////
//Helper class encapsulating a Dynamic-Link Library (DLL) loading.
// 
class CDll
{
public:
  CDll();
  CDll(LPCTSTR szDllName);
  ~CDLL();
  bool Load(LPCTSTR szDllName);
  void Free();
  bool IsOpen() const;
  operator HINSTANCE() const;
protected:
  HINSTANCE m_hLibrary; //handle to the module
  
private:
  CDll(const TDll&);
  CDll& operator=(const TDll&);
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
                  ) 
{
Load(szDllName);
}

//-----------------------------------------------------------------------------
/*
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
  m_hLibrary = ::LoadLibrary(szDllName);
#else
  m_hLibrary = (HINSTANCE)::LoadLibraryEx32W(szDllName, NULL, 0);
#endif

#ifdef _DEBUG
  if (!IsOpen())
    {
    DWORD dwErr = ::GetLastError();
    TRACE2(_T("CDll::Load(%S) failed (Error 0x%X)\n"), szDllName, dwErr);
    }
#endif
return IsOpen();
}

//-----------------------------------------------------------------------------
/*
 */
inline bool CDll::IsOpen() const
{
return (m_hLibrary > NULL);
}

//-----------------------------------------------------------------------------
/*
 */
inline void Free()
{
if (m_hLibrary > NULL) //>= (HINSTANCE)32
  {
  ::FreeLibrary(m_hLibrary);
  m_hLibrary = NULL;
  }
}
#endif //_Win32 specific

///////////////////////////////////////////////////////////////////////////////
#endif  //_KDLL_H_
/******************************************************************************
 *$Log: KDll.h,v $
 *Revision 1.1  2011/08/09 20:34:43  ddarko
 *Commited 1st version
 *
 *****************************************************************************/

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
 