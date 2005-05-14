/*$Workfile: KColorShade.cpp$: implementation file
  $Revision: 3$ $Date: 2005-04-25 21:11:52$
  $Author: Darko$

  Defines the class behaviors for the application.
  Copyright: CommonSoft Inc.
  2003-08-25 Darko Kolakovic
 */

#ifdef _WIN32
  #ifdef _AFXDLL
    #include <afxwin.h>
  #else
    #include <windows.h>
  #endif
#endif
#ifndef UINT8_MAX
  #include "KTypedef.h" //UINT8_MAX
#endif

//-----------------------------------------------------------------------------
/*Changing the shade of a RGB color.
  When specifying an explicit RGB color, the COLORREF value has the following
  hexadecimal form: 
          0x00BBGGRR 
  where RR is relative intensity of red; the second byte GG is a value for green;
  and the third byte BB is a value for blue. The high-order byte must be zero. 
  The maximum value for a single byte is UINT8_MAX.

  Returns: new shade of the given color.
 */
COLORREF ColorShade(COLORREF crColor, //[in] RGB color; range per color component [0, 255]
                    int8 iFactor      //[in] shading factor in steps of 0.8% [-128, 127]
                    )
{
if (iFactor != 0) 
  {
  int iRed   = GetRValue(crColor);
  int iGreen = GetGValue(crColor);
  int iBlue  = GetBValue(crColor);
  if (iFactor < 0)
    {
    iRed   = ((128 + (int)iFactor)*iRed  )/128;
    iGreen = ((128 + (int)iFactor)*iGreen)/128;
    iBlue  = ((128 + (int)iFactor)*iBlue )/128;
    }
  else
    {
    iRed   += (((int)UINT8_MAX - iRed  )*(int)iFactor)/(int)INT8_MAX;
    iGreen += (((int)UINT8_MAX - iGreen)*(int)iFactor)/(int)INT8_MAX;
    iBlue  += (((int)UINT8_MAX - iBlue )*(int)iFactor)/(int)INT8_MAX;
    }
  return RGB(iRed, iGreen, iBlue);
  }
return crColor;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  3    Biblioteka1.2         2005-04-25 21:11:52  Darko            
 *  2    Biblioteka1.1         2003-09-02 01:01:43  Darko           Fixed bug for
 *       values >0
 *  1    Biblioteka1.0         2003-08-29 15:49:19  Darko           
 * $
 *****************************************************************************/
