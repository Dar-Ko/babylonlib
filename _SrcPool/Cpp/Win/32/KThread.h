/*$RCSfile: KThread.h,v $: header file
  $Revision: 1.1 $ $Date: 2011/12/22 15:26:32 $
  $Author: ddarko $

  Copyright: babylonlib@sourceforge.net
  2006-01-09 Darko Kolakovic
 */
// Group=Windows

#ifndef _KTHREAD_H_
    //$RCSfile: KThread.h,v $ sentry
  #define _KTHREAD_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#ifdef _WIN32 //Windows 32-bit platform

#ifndef _USE_ATL
  #include <windows.h>
#endif
#include <setupapi.h> //Device Management Structures

///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" LPTSTR StrIStr(LPCTSTR szSource, LPCTSTR szToken);

///////////////////////////////////////////////////////////////////////////////
/*TODO:

  Note: Microsoft Windows specific (Win32).
  
  See also:
 */
class CThread
{
public:
  CThread();

  ~CThread();
  uint_fast32_t Enumerate();
  bool IsWinNt() const;
protected:
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*Default constructor
 */
inline CThread::CThread()
{
}

inline CThread::~CThread()
{
}

//-----------------------------------------------------------------------------
/*  Note: Microsoft Windows specific (Win32).
 */
inline bool CThread::IsWinNt() const
{
return (GetVersion() < 0x80000000);
}

//-----------------------------------------------------------------------------
/*
 */
inline bool CThread::IsRunning(const TCHAR* szServiceName //[in]
              ) const
{
}
///////////////////////////////////////////////////////////////////////////////
#endif //__cplusplus

#endif //_WIN32
///////////////////////////////////////////////////////////////////////////////
#endif  //_KTHREAD_H_
/*****************************************************************************
 * $Log: KThread.h,v $
 * Revision 1.1  2011/12/22 15:26:32  ddarko
 * Created infrastructure
 *
 *****************************************************************************/
