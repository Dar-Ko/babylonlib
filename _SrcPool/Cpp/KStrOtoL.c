/*$Workfile: KStrOtoL.c$: implementation file
  $Revision: 3$ $Date: 2002-08-19 09:39:43$
  $Author: Darko Kolakovic$
 
  Converts octal string to long integer
  Jan. 96 Darko Kolakovic
*/

/* Group=Strings                                                             */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#include "KTChar.h" /*LPCTSTR typedef*/

#ifdef _DEBUG
  static char THIS_FILE[] = __FILE__;
#endif

/*OcttoL()-------------------------------------------------------------------*/

/*Convert octal string to long integer. 
  The scan ends when a non-octal character is hit.

  Example:
     char* szTemp = "567745516123476412444";
     long lResult = OcttoL(szTemp);
     cout << "octal " << szTemp << " = " << lResult << endl;
     if (lResult != -1661332188)
       return false;

*/
long OcttoL(LPCTSTR szSource /*[in] zero-terminated string representing a 
                                    octal number                             */
            )
{
register long lResult = 0;

while( (*szSource >= _T('0')) && (*szSource <= _T('7')) )
  {
  lResult = (lResult << 3) + (*szSource++ - _T('0'));
  }
return lResult;
}

/* ///////////////////////////////////////////////////////////////////////// */
/******************************************************************************
 *$Log: 
 * 3    Biblioteka1.2         2002-08-19 09:39:43  Darko Kolakovic 
 * 2    Biblioteka1.1         2002-07-16 00:41:27  Darko           Fixed VSS Log 
 *      tag
 * 1    Biblioteka1.0         2002-03-07 16:03:47  Darko           
 *$
 *****************************************************************************/
