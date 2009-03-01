/*$RCSfile: KMutexSimple.h,v $: header file
  $Revision: 1.1 $ $Date: 2009/03/01 04:22:51 $
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
   
  ~CMutexSimple() 
  {
    if (m_hMutex)  //Do not forget to close handles.
    {
       CloseHandle(m_hMutex); //Do as late as possible.
       m_hMutex = NULL; //Good habit to be in.
    }
  }

  BOOL IsAnotherInstanceRunning() 
  {
    return (ERROR_ALREADY_EXISTS == m_dwLastError);
  }

protected:
  DWORD  m_dwLastError;  //mutex creation status
  HANDLE m_hMutex;       //handle to mutex

};
///////////////////////////////////////////////////////////////////////////////
// Inlines

//------------------------------------------------------------------------------
/*
  */
inline CMutexSimple::CMutexSimple(TCHAR* szMutexName //[in] 
                                  )
{
ASSERT((szMutexName != NULL) && (szMutexName[0] != _T('\0')));
  //Make sure that you use a name that is unique for this application otherwise
  //two apps may think they are the same if they are using same name for
  //3rd parm to CreateMutex
  m_hMutex = CreateMutex(NULL, FALSE, strMutexName); //do early
  m_dwLastError = GetLastError(); //save for use later...
} 
 
///////////////////////////////////////////////////////////////////////////////
#endif //__KWINMUTEX_H__
/*****************************************************************************
 * $Log: KMutexSimple.h,v $
 * Revision 1.1  2009/03/01 04:22:51  ddarko
 * Created
 *
 * Revision 1.1  2009/03/01 04:19:48  ddarko
 * *** empty log message ***
 *
 *****************************************************************************/

