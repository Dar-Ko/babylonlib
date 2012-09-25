/*U_DumpDb.h
  Debug functions
  Modules U_Dump.cpp
          D_SysErr.cpp
  2003-09-20
  D. Kolakovic
 */

#ifndef _U_DUMPFUNC_H_
  #define _U_DUMPFUNC_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

enum DUMP_MEM   //Memory dump actions
    {
    DUMP_START, //initialize memory dump state
    DUMP_STOP,  //
    DUMP_PRINT  //output memory state
    };
    
#ifdef _DEBUG
  void DumpMemory(DUMP_MEM Action);
#else
  #define DumpMemory(Action)          ((void)0)
#endif
///////////////////////////////////////////////////////////////////////////////
#endif //_U_DUMPFUNC_H_
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: KDbgMemory.h,v $
 * Revision 1.1  2012/09/25 17:24:10  ddarko
 * Extracted from U_DumpDb
 *
 * 2003-03-20 Darko Kolakovic
 *****************************************************************************/
