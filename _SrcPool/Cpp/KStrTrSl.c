/*$Workfile: KStrTrSl.c$: implementation file
  $Revision: 2$ $Date: 9/10/02 6:55:04 PM$
  $Author: Darko Kolakovic$

  Remove trailing slashes from a string
  Copyright: CommonSoft Inc.
  Oct. 2k2 Darko Kolakovic
*/

/* Group=Strings                                                             */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#include "KTChar.h"    /*TCHAR       */
#include "KStrings.h"  /*Declaration */

#ifdef _DEBUG
  static char THIS_FILE[] = __FILE__;
#endif

/*StrTrimSlash()-------------------------------------------------------------*/
/*Removes trailing slash characters ('/' and '\' ) from a string.

  Returns: source string whitout trailing slash characters, or NULL in case of 
  a failure.

  Example:
      #include <iostream>
      #include <iomanip.h>  //std::endl
      #include "KStrings.h"
      ...
      {
      LPTSTR szPath = _T("/Dir/SubDir/");
      cout << StrTrimSlash(szPath) << endl;
      ...
      }

      Output:
        /Dir/SubDir
 */
LPTSTR StrTrimSlash(LPTSTR szSource /*[in/out] zero-terminated string to be 
                                      trimmed
                                     */
              )
{
unsigned int nTail;
if ( (szSource == NULL) || (szSource[0] == _T('/0')) )
  return szSource; /*Nothing to do */

  /*Count trailing white spaces */
nTail = _tcslen(szSource) - 1;
while (nTail >= 0 && (szSource[nTail] == _T('/') || szSource[nTail] == _T('\\')))
  szSource[nTail--] = _T('\0'); /*Cut off trailing slash (single character is*/
                                /*the most often case).                      */
return szSource;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: $
 *****************************************************************************/
