/*$Workfile: S:\_SrcPool\Cpp\KCmdLineParser.cpp$: implementation file
  $Revision: 1$ $Date: 2005-03-11 17:05:36$
  $Author: Darko Kolakovic$

  Defines the class behavior.
  Copyright: CommonSoft Inc.
  <date> Darko Kolakovic
 */

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

#ifdef _MSC_VER //Micorsoft Visual Studio C++ compiler
  #ifdef _UNICODE
    #ifndef UNICODE
      //To enable Unicode for some Microsoft Visual C/C++ header files,
      //the UNICODE definition is required
      #define UNICODE
    #endif
  #endif
#endif  //_MSC_VER

#include "KCmdLineParser.h"  //CCmdLineParser class
#ifndef ASSERT
  #include "KTrace.h"
#endif
//#include "KTChar.h"    //TCHAR typedef

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// CCmdLineParser class

//-----------------------------------------------------------------------------
/*Default constructor
 */
CCmdLineParser::CCmdLineParser()
{
}


//-----------------------------------------------------------------------------
/*Destructor
 */
CCmdLineParser::~CCmdLineParser()
{
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2005-03-11 17:05:36  Darko Kolakovic 
 * $
 *****************************************************************************/
