/*$Workfile: KFileRead.cpp$: implementation file
  $Revision: 1.1 $ $Date: 2007/09/12 20:40:58 $
  $Author: ddarko $

  Checks if file exist.
  Reads text files.
  Copyright: CommonSoft Inc.
  Dec. 2k1 Darko Kolakovic
*/

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#ifdef _DEBUG
  #ifndef _STLP_DEBUG
    #define _STLP_DEBUG 1    //Debug STLPort library
  #endif
#else
  #ifdef _STLP_DEBUG
    #undef _STLP_DEBUG
  #endif
#endif

#include <string>
#include <fstream>  //std::fstream

#ifndef _T
  #include "KTChar.h" //_T macro
#endif

//#include <new>      //std::nothrow

using namespace std;

//-----------------------------------------------------------------------------
/*Verifies if file exist in the current folder.

  Returns true if file exist or false if not.

  Note: uses Standard Template Library (STL).
 */
bool IsFileExisting(string strFileName //[in] file name
                   )
{
if (strFileName.length() > 0 )
  {
  fstream fsFile(strFileName.c_str(), ios::in);
  if(fsFile.is_open())
    {
    fsFile.close();
    return true;
    }
  }
return false;
}

#include "KTString.h"
bool IsFileExisting(tstring strFileName //[in] file name
                   )
{
if (strFileName.length() > 0 )
  {
  fstream fsFile(strFileName.c_str(), ios::in);
  if(fsFile.is_open())
    {
    fsFile.close();
    return true;
    }
  }
return false;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: KFileExistStl.cpp,v $
 * Revision 1.1  2007/09/12 20:40:58  ddarko
 * Moved IsFileExisting()
 *
 ******************************************************************************/
