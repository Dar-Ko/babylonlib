/*$Workfile: KStrFit.cpp$: implementation file
  $Revision: 7$ $Date: 2004-06-01 16:53:12$
  $Author: Darko$

  Fit a string
  Copyright: CommonSoft Inc.
  Darko Kolakovic  March 99
 */ 
/* Group=Strings                                                             */

//#include "stdafx.h"
#include <afxwin.h>
#include "KStrExt.h" //FitString()

//A mark to indicate an ommission of letters or words
LPCTSTR g_szEllipsis = _T("...");

//FitString()----------------------------------------------------------------
/*Fit a string within a specified space by cutting off tailing characters.
  If original string could not fit in the given space, a szSuffix will be
  appended.
  Returns: pointer to the fitted string or empty string if the given width is
  too small even for the szSuffix only.

  Note: uses Microsoft Fundation Library (MFC).

  Example:
    #include "KStrExt.h" //FitString()
    extern LPCTSTR g_szEllipsis;
    ...
    {
    ...
    CClientDC dc(this);
    CString strText("This is some text");
    strText = FitString(&dc,strText,20,g_szEllipsis);
    TRACE1("Fitted Text = %s\n",strText);
    ...
    }

  TODO: replace MFC D.K.
 */
CString FitString(CDC* pDC, //[in] device context in which the text will be outputed
                  CString strText, //[out] buffer holding the text to fit
                  int iWidth,      //[in] desired text width[device units]
                  LPCTSTR szSuffix //[in] text suffix (like "...") or NULL
                  )
{
if (!strText.IsEmpty())
  {
  SIZE  sizeText;
  int   iLen;   //String length
    //Get string extent
  iLen = strText.GetLength();
  GetTextExtentPoint32(pDC->GetSafeHdc(), strText, iLen, &sizeText);
  int   iCount = 0;
  if (sizeText.cx > iWidth) //Fit the string into given width
    {
      //Get non-zero average character width in pixels
    iCount = (sizeText.cx / iLen) + 1;
      //Subtract the width of the suffix, if any
    if ((szSuffix != NULL) && (szSuffix[0] != _T('\0')) )
      {
      GetTextExtentPoint32(pDC->GetSafeHdc(), szSuffix, (int)_tcsclen(szSuffix), &sizeText);
      iWidth -= sizeText.cx;
      if (iWidth < 0)
        {
        TRACE1("Suffix %s too long!\n",szSuffix);
        strText.Empty();
        return strText;
        }
      }

      //Approximate position of the string portion to fit
    iCount = iWidth / iCount;
    if (iCount < 0)
      iCount = 0;
    else   //Get a portion of the string
      while(iCount > 0)
        {
        GetTextExtentPoint32(pDC->GetSafeHdc(), strText, iCount, &sizeText);
        if (sizeText.cx <= iWidth)
          break; //Fitted
        iCount --;
        }
    strText = strText.Left(iCount); //Cut leftmost portion
    strText += szSuffix;
    }
  }
return strText;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         18/08/2001 2:47:10 PMDarko
 * $
 *****************************************************************************/
