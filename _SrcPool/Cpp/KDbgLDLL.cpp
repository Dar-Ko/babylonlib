/*$Workfile: KDbgLDLL.cpp$: implementation file
  $Revision: 1.2 $ $Date: 2002/09/10 15:22:20 $
  $Author: ddarko $
  
  Dumps DLL names used by active process
  Copyright: CommonSoft Inc.
  Aug. 97 Darko Kolakovic
  Jan. 99 AFX_MODULE_STATE (MS VC/C++ 6.0) D.K.
 */
// Group=Diagnostic

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */
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

  Note: uses Microsoft Fundation Library (MFC).
        Microsoft Windows specific (Win).

  Header file:
      #include "KDbgDump.h"
 */
void DumpDLLs(CStringArray* pList /*= NULL*/)
{
TRACE0 (_T("\tDump of DLLs in resource search order\n"));
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
 *  6    Biblioteka1.5         1/29/02 11:20:20 PM  Darko           Used lbraries
 *       notes 
 *  5    Biblioteka1.4         1/29/02 3:38:46 PM   Darko           Tag update
 *  4    Biblioteka1.3         8/19/01 11:52:45 PM  Darko           Butyfier
 *  3    Biblioteka1.2         7/11/01 10:50:38 PM  Darko           
 *  2    Biblioteka1.1         6/8/01 11:50:00 PM   Darko           VSS
 *  1    Biblioteka1.0         8/13/00 3:55:54 PM   Darko           
 * $
 *****************************************************************************/
