/*$Workfile: KGetFileExtn.cpp$: implementation file
  $Revision: 2$ $Date: 2004-06-01 17:03:33$
  $Author: Darko$

  Copyright: CommonSoft Inc.
  2003-08 Darko Kolakovic
 */

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

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

//-----------------------------------------------------------------------------
/*Call this function to extract the file extension from a filename.
  For example, if the name of the file entered is DATA.TXT, GetFileExt returns
  "TXT".

  Returns: extension of the filename.

  Note: uses Standard Template Library (STL).
 */
std::string GetFileExt(std::string strFileName//[in] string with filename
                      )
{
std::string strExt = ""; //the strExt to be returned

std::string::size_type nIndex = strFileName.rfind(".");
if(nIndex != std::string::npos)
  {
  strExt = strFileName.substr(nIndex + 1);
  }

return strExt;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2003-08-19 16:13:45  Darko
 * $
 *****************************************************************************/
