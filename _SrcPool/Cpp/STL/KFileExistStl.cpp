/*$Workfile: $: implementation file
  $Revision: 1.3 $ $Date: 2007/09/13 21:42:52 $
  $Author: ddarko $

  Checks if file exist.
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

#include "KTString.h" //tstring typedef
#include "KOStream.h" //tfstream typedef

#if defined _UNICODE || defined UNICODE
  extern std::string WtoChar(const wchar_t* lpWideCharStr, int iLen = -1);
#endif

using namespace std;

//-----------------------------------------------------------------------------
/*Verifies if file exist in the current folder.

  Returns true if file exist or false if not.

  Note: Unicode file name will be reduced to single byte (ASCII) name.
  This limitation is imposed by underlining basic_fstream constructor.

  Note: uses Standard Template Library (STL).
 */
bool IsFileExisting(tstring strFileName //[in] file name
                   )
{
if (strFileName.length() > 0 )
  {
  //Is the file one of the existing files?
  #if defined _UNICODE || defined UNICODE
    string strFileNameA = WtoChar(strFileName.c_str());
    tfstream fsFile(strFileNameA.c_str(), ios::in);
  #else
    tfstream fsFile(strFileName.c_str(), ios::in);
  #endif

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
 * Revision 1.3  2007/09/13 21:42:52  ddarko
 * IsFileExisting
 *
 * Revision 1.1  2007/09/12 20:40:58  ddarko
 * Moved IsFileExisting()
 *
 ******************************************************************************/
