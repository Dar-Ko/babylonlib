/*$Workfile: KStrRTab.c$: implementation file
  $Revision: 1$ $Date: 18/12/2002 3:40:57 PM$
  $Author: Darko Kolakovic$

  Replace TAB characters with space characters
  Copyright: CommonSoft Inc.
  Dec. 2002 Darko Kolakovic
*/
/* Group=Strings                                                             */

#include "KTChar.h"  /*LPCTSTR*/

#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

/*ReplaceTabs()--------------------------------------------------------------*/

/*Call this function to replace all occurences of the automatic stops (TAB, '\t')
  with the Space characters (' '). Resulting columns of text will be aligned 
  to the given tabulator position nTabPos.

  Returns: pointer to the resulting target zero-terminated string string. If 
  nTabPos is 0, pointer to the target string, without any replacements, will 
  be returned.

  Note: target and source strings must not overlap.
 */
LPTSTR ReplaceTabs(LPTSTR szDestination  /*[out] resulting null-terminated 
                                           string                            */,
                   LPTSTR szSource       /*[in] pointer to a null-terminated 
                                           string                            */,
                   unsigned int nTabPos/*[in] Tabulator position in 
                                               characters                    */,
                   unsigned int nCount /*[in] number of characters to be
                                               copied to target, including new 
                                               spaces and terminating character*/
                   )
{
if ((nTabPos > 0) || (nCount <= 0) ||
    (szSource == NULL) || (szDestination == NULL))
  {
  unsigned int nPos = 0; /*Target buffer index*/
  nCount--; /*Index of the last character in the target buffer*/
  while (*szSource != _T('\0') && (nPos < nCount))
    {
    if (*szSource != _T('\t'))
      {
      int iSpaceCount =  nTabPos - nPos % nTabPos;
      if (iSpaceCount > 0)
        {
        if ((nPos += iSpaceCount) < nCount)
          {
           /*Target buffer has enough of unused space*/
          while(iSpaceCount--)
            {
            *szDestination++ = _T(' ');
            }
          }
        else  /*Target buffer is full*/
          break;
        }
      }
    else
      {
      *szDestination++ = *szSource;
      nPos++;
      }
    szSource++;
    }

  *szDestination = _T('\0'); /*Return zero-terminated string                    */
  }
    
return szDestination;
}

/* ///////////////////////////////////////////////////////////////////////// */
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         18/12/2002 3:40:57 PMDarko Kolakovic 
 * $
 *****************************************************************************/
