/*$RCSfile: KMutexSimple.h,v $: header file
  $Revision: 1.2 $ $Date: 2009/03/01 06:12:21 $
  $Author: ddarko $

  Single instance Windows application
  2k9-02-28 Darko Kolakovic
  January 9, 2006 MSDN Article ID: 243953 - Revision: 7.0
 */
// Group=Windows

//$RCSfile: KMutexSimple.h,v $ sentry
#ifndef __KWINMUTEX_H__
  #define __KWINMUTEX_H__

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#include <windows.h>

////////////////////////////////////////////////////////////////////////////////
/*

  Note: In Visual C++ 2005, you must add the common language runtime support
  compiler option (/clr:oldSyntax) to successfully compile:
    click on Project | Properties | Configuration Properties | General
    select Common Language Runtime Support | Old Syntax (/clr:oldSyntax).

  Example:
    //Use named mutex to create single instance of a MFC appplication
    #include "KMutexSimple.h"
    CMutexSimple g_SingleInstanceObj(TEXT("Global\\{05CA3573-B449-4e0b-83F5-7FD612E378E9}"));
    ...
    BOOL CMyDlgApp::InitInstance()
    {
    if (g_SingleInstanceObj.IsCreated())
      return FALSE;
    //...
    }
    //Use named mutex to create single instance of a Console appplication
    CMutexSimple g_SingleInstanceObj(TEXT("Global\\{9DA0BEED-7248-450a-B27C-C0409BDC377D}"));
    ...
    int _tmain(int argc, TCHAR* argv[])
    {
    if (g_SingleInstanceObj.IsCreated())
      return EXIT_FAILURE;
    //...
    }
    //Use named mutex to create single instance of a Win32 SDK appplication
    CMutexSimple g_SingleInstanceObj(TEXT("Global\\{2194ABA1-BFFA-4e6b-8C26-D191BB16F9E6}"));

    int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                       LPSTR lpCmdLine, int cmdShow)
    {
    if (g_SingleInstanceObj.IsCreated())
      return 0;
    //...
    }


  See also: MSDN Q243953 "How to limit 32-bit applications to one instance in
  Visual C+"
 */
class CMutexSimple
{
private:
  CMutexSimple()
  {
  }

public:
  CMutexSimple(TCHAR* szMutexName);
  virtual ~CMutexSimple();
//Operations
  bool IsCreated();

protected:
  DWORD  m_dwLastError;  //mutex creation status
  HANDLE m_hMutex;       //handle to mutex

};
///////////////////////////////////////////////////////////////////////////////
// Inlines

//------------------------------------------------------------------------------
/*Creates a named mutex.
  To create single instance of mutex in a single user session, prefix mutex
  name with "Local\". To make single mutex instance for multiple terminal
  sessions, use "Global\" prefix. Adding "Global\" will guarantee that there is
  only one instance of the application on a computer. Not adding a prefix will
  guarantee one instance per Terminal Services session.

  Example:

      CMutexSimple g_SingleInstanceObj(_T("Global\\MY_GLOBAL_MUTEX"));
      CMutexSimple g_SingleInstanceObj(_T("Local\\MY_LOCAL_MUTEX"));

 */
inline CMutexSimple::CMutexSimple(TCHAR* szMutexName //[in] case-sensitive mutex
                                                     //name
                                  )
{
ASSERT((szMutexName != NULL) && (szMutexName[0] != _T('\0')));

SetLastError(NO_ERROR);
m_hMutex = CreateMutex(NULL, FALSE, strMutexName);
m_dwLastError = GetLastError();
  //Note: the system closes the mutex handle automatically when the process
  //terminates
}

inline CMutexSimple::~CMutexSimple()
{
if (m_hMutex!= NULL)
  {
  CloseHandle(m_hMutex);
  m_hMutex = NULL;
  }
}

//------------------------------------------------------------------------------
/*
 */
bool CMutexSimple::IsCreated()
{
  //If mutex is already created error is ERROR_ALREADY_EXISTS; if mutex is
  //created  with NULL security descriptor, error is ERROR_ACCESS_DENIED.
if((m_dwLastError == ERROR_ALREADY_EXISTS) ||
   (m_dwLastError == ERROR_ACCESS_DENIED))
  {
  return true;
  }
return false;

}

///////////////////////////////////////////////////////////////////////////////
#endif //__KWINMUTEX_H__
/*****************************************************************************
 * $Log: KMutexSimple.h,v $
 * Revision 1.2  2009/03/01 06:12:21  ddarko
 * Created
 *
 * Revision 1.1  2009/03/01 04:22:51  ddarko
 * Created
 *
 * Revision 1.1  2009/03/01 04:19:48  ddarko
 * *** empty log message ***
 *
 *****************************************************************************/

