/*$Workfile: KDbgLDLL.cpp$: implementation file
  $Revision: 1.3 $ $Date: 2003/01/28 05:35:50 $
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
 *  6    Biblioteka1.5         29/01/2002 10:20:20 PMDarko           Used lbraries
 *       notes 
 *  5    Biblioteka1.4         29/01/2002 2:38:46 PMDarko           Tag update
 *  4    Biblioteka1.3         19/08/2001 10:52:45 PMDarko           Butyfier
 *  3    Biblioteka1.2         11/07/2001 9:50:38 PMDarko           
 *  2    Biblioteka1.1         08/06/2001 10:50:00 PMDarko           VSS
 *  1    Biblioteka1.0         13/08/2000 2:55:54 PMDarko           
 * $
 *****************************************************************************/
