/*$Workfile: H:\_SrcPool\Cpp\Samples\Images\TestGifConversion.cpp$: implementation file
  $Revision: 2$ $Date: 8/5/02 11:33:43 AM$
  $Author: Darko$

  Test GIF primitive conversons
  Mar 2k2 D. Kolakovic
*/

// Group=Examples

#include <iostream>
#include <iomanip.h>
#include "KProgCst.h" //_ENDIAN_ORDER_
#include "KGif.h"     //CGif class
#include "KTrace.h"   //TRACE macros

#if (_ENDIAN_ORDER_ == _ENDIAN_BIG_)
  #pragma message ("Include Big Endian Swap files")
  #include "KSwpByte.h"
#endif


#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

//TestGifConversion()---------------------------------------------------------------
/*Test of GIF primitive conversions

  Returns: true if successful, otherwise returns false
 */
bool TestGifConversion()
{
cout << "TestGifConversion()" << endl;
bool bRes = false;

//Convert CGifColor to RGBQUAD
cout << "Convert CGifColor to RGBQUAD" << endl;
CGifColor gifColor(0x10, 0x20, 0x30);
DWORD dwColorQ = (DWORD)gifColor;

if (bRes = (dwColorQ == 0x00102030))
  {
  #if (_ENDIAN_ORDER_ == _ENDIAN_BIG_)
    dwColorQ = SwapByteOrder(dwColorQ);
  #endif

  RGBQUAD* rgbColor = (RGBQUAD*)&dwColorQ;

  if (bRes = (rgbColor->rgbRed == gifColor.m_cRed))
    if (bRes = (rgbColor->rgbBlue == gifColor.m_cBlue))
      bRes = (rgbColor->rgbGreen == gifColor.m_cGreen);
  }

cout << endl << "======================" << endl;
return bRes;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 *$Log: 
 * 2    Biblioteka1.1         8/5/02 11:33:43 AM   Darko           Fixed bug in
 *      SeekImagePos
 * 1    Biblioteka1.0         8/2/02 10:25:18 PM   Darko Kolakovic 
 *$
 *****************************************************************************/
