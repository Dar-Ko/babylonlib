/*$Workfile: KStrICmp.c$: implementation file
  $Revision: 1$ $Date: 27/08/2002 4:05:02 PM$
  $Author: Darko Kolakovic$

  Case-insensitive string comparision
  Copyright: CommonSoft Inc.
  Mar 1989 Darko Kolakovic
 */

/* Group=Strings                                                             */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#include "KTChar.h"  /*LPCTSTR*/

#ifndef _MSC_VER /*If not Microsoft VC/C++ compiler                          */

  #ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
  #endif

//StrICmp()--------------------------------------------------------------------
/*Compares two strings lexically to determine if they are the same. 
  The comparison is not case-sensitive. 

  Returns: zero if the strings are identical, a positive value if the string 
  szStr1 is greater than szStr2 or a negative value if the string szStr1 is less 
  than szStr2.
  
  TODO: Make comparaison locale dependent.

  Example:
    #include <StdLib.h>
    #include <tchar.h>
    #include "KStrings.h"
    void MyFunc()
      {
      TCHAR* s1 = "Hello, World!";
      TCHAR* s2 = "Hello, World!";
      int iRes;
        
      iRes = StrICmp(s1,s2);
      if(iRes == 0)
          printf("s1 and s2 are identical");
      else 
        if(iRes < 0)
          printf("s1 less than s2");
        else
          printf("s1 greater than s2");
      }

 */
int StrICmp(LPCTSTR szStr1,//[in] Address of the first zero-termianted string
                           //to be compared
            LPCTSTR szStr2//[in] Address of the second zero-termianted string
                           //to be compared
           )
{
while (_tolower((int)*s1) == _tolower((int)*s2))
  {
  if (*s1 == _T('\0'))
    return 0;
  s1++;
  s2++;
  }
return (int)( _tolower((int)*s1) - (int)_tolower((int)*s2) );
}

/* ///////////////////////////////////////////////////////////////////////// */
#else
  /*Microsoft VC/C++ compiler                                                */
  #include <tchar.h>
  int StrICmp(LPCTSTR szStr1, LPCTSTR szStr2)
  {
  return _tcsicmp(szStr1, szStr2);
  }
#endif
/*****************************************************************************
 * $Log:
 *  0    Biblioteka1.0           Mar 1989 Darko Kolakovic
 * $
 *****************************************************************************/
