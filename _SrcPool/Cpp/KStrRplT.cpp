/*$Workfile: H:\_SrcPool\Cpp\KStrRplT.cpp$: implementation file
  $Revision: 3$ $Date: 1/29/02 10:22:05 PM$
  $Author: Darko$

  Replace TAB characterts in CString with spaces
  May '97 Darko Kolakovic
*/
/* Group=Strings                                                             */

#include "StdAfx.h"
//#include "KStrExt.h"  //Declarations

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

//Functions using MFC
#ifdef __AFXWIN_H__

//ReplaceTabs()----------------------------------------------------------------
/*Call this function to replace all occurences of the automatic stops (TAB)
  with the Space characters. Resulting columns of text will be aligned to the
  give tabulator postion iTabPos.

  Returns: source string with replaced characters.

  Note: uses Microsoft Fundation Library (MFC).

  Example:
     CString strTest("Summer\ttime\tis the\tbest");
     TRACE((LPTSTR)ReplaceTabs(strTest,4);

     Output:
     Summer  time    is the  best
     ^   ^   ^   ^   ^   ^   ^    - automatic stops
 */
CString& ReplaceTabs(CString& strSource, //[in/out] string to be replaced
                     const int iTabPos   //[in] Tabulator position in characters
                     )
{
TCHAR* szSeparation = new TCHAR[iTabPos+1];
int iPos;
while ((iPos = strSource.Find(_T('\t'))) >= 0)
  {
  int i =  iTabPos - iPos % iTabPos;
  szSeparation[i] = _T('\0');
  while (i > 0)
    szSeparation[i--] = _T(' ');
	strSource = strSource.Left(iPos) + szSeparation + strSource.Mid(iPos + 1);
  }

delete[] szSeparation;
return strSource;
}

///////////////////////////////////////////////////////////////////////////////
#endif //__AFXWIN_H__

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  0    Biblioteka0           Darko Kolakovic  May '97
 * $
 *****************************************************************************/
