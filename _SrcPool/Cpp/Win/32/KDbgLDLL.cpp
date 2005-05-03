/*$Workfile: KDbgLDLL.cpp$: implementation file
  $Revision: 10$ $Date: 2005-04-26 11:29:12$
  $Author: Darko Kolakovic$
  
  Dumps DLL names used by active process
  Copyright: CommonSoft Inc.
  Aug. 97 Darko Kolakovic
  Jan. 99 AFX_MODULE_STATE (MS VC/C++ 6.0) D.K.
 */
// Group=Diagnostic

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */
#include <AfxWin.h>

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;

///////////////////////////////////////////////////////////////////////////////

//DumpDLLs()-------------------------------------------------------------------
#ifndef _AFX_NO_OLE_SUPPORT
  #include <AfxDisp.h>
#endif
/*Dumps DLL names used by active process.

  Note: uses Microsoft Foundation Library (MFC).
        Microsoft Windows specific (Win).

  Header file:
      #include "KDbgDump.h"
 */
void DumpDLLs(CStringArray* pList /*= NULL*/)
{
TRACE0 ("\tDump of DLLs in resource search order\n");
if (pList)
  pList->Add(_T("Dump of DLLs in resource search order\n"));

#if _MFC_VER >= 0x0600 //MFC v4.2 r6.0 11.01.2000 D.K.
  AFX_MODULE_STATE* pState = AfxGetModuleState();
#elif  _MFC_VER < 0x0420 //MFC v4.0
  AFX_MODULE_PROCESS_STATE* pState = AfxGetModuleProcessState();
#else
  #pragma message ("Unsupported MFC version")
#endif

for (CDynLinkLibrary* pDLL = pState->m_libraryList; pDLL != NULL;
                             pDLL = pDLL->m_pNextDLL)
  {
  TCHAR szName[64]; //Get module name
  GetModuleFileName(pDLL->m_hModule, szName, sizeof(szName));
  TCHAR szT[256];

  int nClasses = 0; //Count classes
  for (CRuntimeClass* pClass = pDLL->m_classList; pClass != NULL;
                             pClass = pClass->m_pNextClass)
    nClasses++;

  int nFactories = 0; //Count factories
  #ifndef _AFX_NO_OLE_SUPPORT
    for (COleObjectFactory* pFactory = pDLL->m_factoryList;pFactory != NULL;
                            pFactory = pFactory->m_pNextFactory)
      nFactories++;
  #endif

  wsprintf(szT, _T("Module %s has %d classes and %d factories"),
    szName, nClasses, nFactories);
  TRACE1("\t%s\n",szT);
  if (pList)
    pList->Add(szT);
  }
TRACE0("\n");
}

///////////////////////////////////////////////////////////////////////////////
#endif  //_DEBUG
/*****************************************************************************
 * $Log: 
 *  10   Biblioteka1.9         2005-04-26 11:29:12  Darko Kolakovic Document groups
 *       and typo fixes
 *  9    Biblioteka1.8         2004-10-01 22:34:21  Darko           stdafx.h
 *  8    Biblioteka1.7         2003-08-17 02:13:33  Darko           Unicode
 *  7    Biblioteka1.6         2003-08-13 10:52:33  Darko           formatting
 *  6    Biblioteka1.5         2002-01-29 23:20:20  Darko           Used lbraries
 *       notes 
 *  5    Biblioteka1.4         2002-01-29 15:38:46  Darko           Tag update
 *  4    Biblioteka1.3         2001-08-19 23:52:45  Darko           Butyfier
 *  3    Biblioteka1.2         2001-07-11 22:50:38  Darko           
 *  2    Biblioteka1.1         2001-06-08 23:50:00  Darko           VSS
 *  1    Biblioteka1.0         2000-08-13 15:55:54  Darko           
 * $
 *****************************************************************************/
