/*$RCSfile: KGetFileName.cpp$: implementation file
  $Revision: 3$ $Date: 2007-07-10 17:54:01$
  $Author: Darko Kolakovic$

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
/*Extracts the file name from a file path.

  Returns: file name.

  Note: uses Standard Template Library (STL).
 */
std::string GetFileName(std::string strFilePath//[in] fully-qualified filename
                        )
{
//search right for the last first / (the least one in the path)
std::string strPath = ""; //Result

  //TODO: Find last \ or /
std::string::size_type nIndex = strFilePath.rfind("/");
if(strFilePath.rfind(".") != std::string::npos && strFilePath.rfind(".") > nIndex)
  {
  if(nIndex != std::string::npos)
    {
    strPath = strFilePath.substr(nIndex+1);
    }
  }
return strPath;
}

//-----------------------------------------------------------------------------
/*Extracts the file name and extension from a file path.

  Returns: file title.

  Note: uses Standard Template Library (STL).
 */
std::string GetFileTitle(std::string strFilePath//[in] fully-qualified filename
                        )
{
std::string strResult = "";

std::string::size_type nIndex = strFilePath.rfind("/");
if(nIndex != std::string::npos)
  {
  //Return substring from the current position to the end
  strResult = strFilePath.substr(nIndex+1); 
  }
return strResult;
}

//-----------------------------------------------------------------------------
/*Extracts the path to a file from a file path.

  Returns: directory path.

  Note: uses Standard Template Library (STL).
 */
std::string GetFilePath(std::string strPath//[in] fully-qualified filename
                        )
{
std::string strResult = "";
size_t nPos = strPath.rfind(".");
if(nPos != std::string::npos)
  {
  nPos = strPath.rfind("/");
  if(nPos != std::string::npos)
    strResult = strPath.substr(0, nPos);
  }
return strResult;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2003-08-19 16:13:46  Darko
 * $
 *****************************************************************************/
