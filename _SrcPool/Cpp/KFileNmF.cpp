/*$Workfile: H:\_SrcPool\Cpp\KFileNmF.cpp$: implementation file
  $Revision: 1.1 $ $Date: 2002/09/06 22:14:10 $
  $Author: ddarko $

  Fit filename string
  Copyright: CommonSoft Inc.
  Darko Kolakovic May 96
 */

#include "StdAfx.h"
#ifndef WIN32    //Windows 32b application
  #pragma error ("Requred Windows 32b")
#endif

//FitFilename()----------------------------------------------------------------
/*Fit a filename within a specified space by cutting off subdirectories.

  Returns: pointer to the fitted portion of the filename string.
  
  Note: Microsoft Windows specific (Win).
 */
LPCTSTR FitFilename(HWND hWnd, //[in] window or control in which the text
                               //will be outputed
                   LPTSTR lpFileName, //[in] buffer holding the filename
                   int iWidth, //[in] desired text width[device units]; if 0
                               //filename will be fitted into client rectangle
                   LPCTSTR szPrefix //[in] text prefix (like "...\\") or NULL
                          )
{
if ( (hWnd == NULL)       || 
     (lpFileName == NULL) || 
     (lpFileName[0] == _T('\0')) )
  return NULL; //Nothing to do
else
  {
  RECT  rectClient;
  HDC   hdc;
  HFONT hfont, hfontOld;
  SIZE  sizeText;
  int   iCount = 0; 
  int   iLen;   //Filename string length
  if (iWidth == 0)  //Get fitting rectangle
	  {
	  GetClientRect(hWnd, &rectClient);
	  iWidth = rectClient.right - rectClient.left;
	  }
    //Get window's font
  hdc = GetDC(hWnd);
  if( (hfont = (HFONT)SendMessage(hWnd, WM_GETFONT, 0, 0L) ) == NULL)
    hfontOld = (HFONT)SelectObject(hdc, hfont); //Select system font
    //Get filename string extent
  iLen = _tcsclen(lpFileName);
  GetTextExtentPoint32(hdc, lpFileName, iLen, &sizeText);
  if (sizeText.cx > iWidth) //Fit the filename into given width
    {
      //Get non-zero average character width in pixels
    iCount = (sizeText.cx / iLen) + 1;
      //Subtract the width of the prefix, if any
    if ((szPrefix != NULL) && (szPrefix[0] != _T('\0')) )
      {
    	GetTextExtentPoint32(hdc, szPrefix, _tcsclen(szPrefix), &sizeText);
      iWidth -= sizeText.cx;
      }
     //Approximate position of the string portion to fit; 8 is added for good measure.
    iCount = iLen - (iWidth / iCount + 8);
    if (iCount < 0)
      iCount = 0;
      //Get a subdirectory to fit
    do
      {
      while( (lpFileName[iCount] != _T('\\')) && 
             (lpFileName[iCount] != _T('/'))  &&
             (iCount < iLen) )
        iCount++;
      if (iCount < iLen)
        {
        GetTextExtentPoint32(hdc, &lpFileName[iCount], iLen -iCount+1, &sizeText);
        if (sizeText.cx <= iWidth)
          break; //Fitted
        }
      else
        break;

      iCount++;
      } while(iCount < iLen);

    }

  if (NULL != hfont)
	  SelectObject(hdc, hfontOld);
  ReleaseDC(hWnd, hdc);

  return &lpFileName[iCount];
  }
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 *$Log: 
 * 1    Biblioteka1.0         8/27/02 5:04:55 PM   Darko Kolakovic 
 *$
 *****************************************************************************/
