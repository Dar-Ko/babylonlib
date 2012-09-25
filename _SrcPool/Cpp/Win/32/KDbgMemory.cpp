/*$RCSfile: KDbgMemory.cpp,v $: implementation file
  $Revision: 1.1 $ $Date: 2012/09/25 17:24:10 $
  $Author: ddarko $
 */
#include <afx.h>
#include "KDbgMemory.h"

 #ifdef _DEBUG
  CMemoryState g_oldMemState, g_newMemState, g_diffMemState;
#endif

#if _MFC_VER == 0x600
  #pragma message ( "MFC version 4.2") 
#endif

#ifdef _DEBUG
//DumpMemory()-----------------------------------------------------------------
/*Provides a convenient way to detect memory leaks in your program. 
  A “memory leak” occurs when memory for an object is allocated on the heap but
  not deallocated when it is no longer required. Such memory leaks can eventually
  lead to out-of-memory errors. 

  Example:
    #include "U_DumpDb.h"  //declarations
    CMyClass::CMyClass()
      {
      TRACE0("CMyClass::CMyClass()\n");
      #ifdef _DEBUG
        DumpMemory(DUMP_START);
      #endif
      }
    CMyClass::~CMyClass()
      {
      TRACE0("CMyClass::~CMyClass()\n");
      #ifdef _DEBUG
        DumpMemory(DUMP_STOP);
      #endif
      }
 */
void DumpMemory(DUMP_MEM Action)
{
switch (Action)
  {
  case DUMP_START: g_oldMemState.Checkpoint(); break;
  case DUMP_STOP:
    g_newMemState.Checkpoint();
    if( g_diffMemState.Difference( g_oldMemState, g_newMemState ) )
      {
      TRACE0("\nMemory leaked!\n");
      g_diffMemState.DumpAllObjectsSince();
      g_diffMemState.DumpStatistics();
      }
    break;
  case DUMP_PRINT:
    g_oldMemState.DumpAllObjectsSince();
    g_oldMemState.DumpStatistics();
    break;
  }

}
///////////////////////////////////////////////////////////////////////////////
#endif //_DEBUG
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: KDbgMemory.cpp,v $
 * Revision 1.1  2012/09/25 17:24:10  ddarko
 * Extracted from U_DumpDb
 *
 * 2003-03-20 Darko Kolakovic
 *****************************************************************************/

