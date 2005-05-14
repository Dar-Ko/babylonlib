/*$Workfile: KStdRes.h$: header file
  $Revision: 2$ $Date: 2004-10-06 23:27:19$
  $Author: Darko$

  Common headre files required for resource files
  CommonSoft Inc.
  2004-09-11 Darko Kolakovic
 */

//#include "olenls.h"
//MSVC7.1, MSVC6 does not require header (LANG_xx) above for console non-MFC app D.K.

#if defined(_AFXDLL) //MFC
  #include "afxres.h"
#else //SDK
  #include "winres.h"
#endif

///////////////////////////////////////////////////////////////////////////////
//Note: Microsoft resource compiler (MSVC6, MSVC7.1 Net) requires that header
//       file included in a resource (.rc) ends with an empty line (CRLF)! 
/*****************************************************************************
 * $Log: 
 *  2    Biblioteka1.1         2004-10-06 23:27:19  Darko           fixed error
 *       caused with bug in resource compiler
 *  1    Biblioteka1.0         2004-10-06 23:09:37  Darko           
 * $
 *****************************************************************************/
