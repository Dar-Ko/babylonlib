/*$RCSfile: MFCUsr32.h,v $: header file
  $Revision: 1.1 $ $Date: 2009/04/16 21:46:42 $
  $Author: ddarko $

  Fix up for the User32.dll memory leaks
  Article: MSDN Q184807,Q189383
  Darko Kolakovic
  Jan 99
  */

// Group=Windows

#ifndef _MFC_USER32DLL_H_
    //$RCSfile: MFCUsr32.h,v $ sentry
  #define _MFC_USER32DLL_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#define _MFCUSER32DLL 1 //include Bug Fix

#ifdef _MFCUSER32DLL
/*This is a fix for the User32.dll memory leaks (Articles Q184807, Q189383)
  Win95, WinNT 4.0. and for the GDI32.dll, AdvAPI32.dll (Q171145, WinNT 4.0).
  Insert this class as memeber of the CMyApp or as global on the begining of
  the code.

  1) An increasing amount of memory appears to be consumed by an application
     that repeatedly loads and unloads the User32.dll. This may be caused by
     the application or a DLL used by the application that loads and unloads
     the User32.dll multiple times. If the User32.dll is loading and unloading
     several times, a message box might appear stating an error occurred.
  2) An ASSERT can occur when a non-MFC application tries to load, free, and
     again load an MFC Regular DLL. The assert occurs in the Auxdata.cpp file
     as a result of a failed call to GetSysColorBrush. (MFC5.0)
 */
class FixUser32DLL
{
public:
  FixUser32DLL();
  ~FixUser32DLL();
  int LoadLibrary();
  HINSTANCE m_hInstanceUser32;
  HINSTANCE m_hInstanceGDI32;
  friend int FixLoadUser32Library();
};

inline FixUser32DLL::FixUser32DLL() :
  m_hInstanceUser32(NULL),
  m_hInstanceGDI32(NULL)
  {
  }

inline FixUser32DLL::~FixUser32DLL()
  {
  if (m_hInstanceUser32 != NULL)
    ::FreeLibrary(m_hInstanceUser32);
  }

inline int FixUser32DLL::LoadLibrary()
  {
  int iRes = 0;
  m_hInstanceUser32 = ::LoadLibrary("User32.dll");
  if (m_hInstanceUser32 != NULL)
    iRes++;
  m_hInstanceGDI32 = ::LoadLibrary("GDI32.dll");
  if (m_hInstanceGDI32 != NULL)
    iRes++;
  return iRes;
  }

///////////////////////////////////////////////////////////////////////////////
#endif //_MFCUSER32DLL

  //Loads User32.dll just once to prevent memory leaks
FixUser32DLL g_FixUser32DLL;
inline int FixLoadUser32Library()
  {
  return g_FixUser32DLL.LoadLibrary();
  }

///////////////////////////////////////////////////////////////////////////////
#endif //_MFC_USER32DLL_H_
/*****************************************************************************
 * $Log: MFCUsr32.h,v $
 * Revision 1.1  2009/04/16 21:46:42  ddarko
 * Moved from old repository
 *
 *****************************************************************************/
