/******************************************************************************
  $RCSfile: BmpViewer.h,v $: header file
  $Revision: 3$ $Date: 10/10/2002 7:26:58 PM$
  $Author: Darko Kolakovic$

  Copyright © 2000-2001 All rights reserved. MIST Inc.
  Encapsulation of images in DIB Format.
 *****************************************************************************/ 
#ifndef _BMPVIEWER_H_
  #define _BMPVIEWER_H_

#define HANDLE_PRAGMA_PACK_PUSH_POP //gcc 2.96.3 

#include "KTypedef.h" //BYTE definition
#include "bmp.h"

///////////////////////////////////////////////////////////////////////////////
/*Collection of labels, tags and keywords used in various sections of 
  bitmap image
 */
class CBmpLabel
{
public:
  static WORD  m_wSignature; //signature identifying valid bitmap format
  static char* m_szFileExt  ; //common file extension used in 8.3 file 
                              //systems
  static bool  IsValid(const BYTE* pData);
};

///////////////////////////////////////////////////////////////////////////////
// Bmp decoder and converter
class CBmpViewer : public ZafImageData
{
public:
	CBmpViewer();
	CBmpViewer(BYTE* pData, const unsigned int nSize);
//	CBmpViewer(const BYTE* pData, const unsigned int nSize);
	virtual ~CBmpViewer();
	bool    Load(BYTE* pData, const unsigned int nSize);
	bool	GetBitmap(ZafBitmapStruct*& pzafBmpResult);
	bool	GetSize(unsigned int& nWidth, 
               unsigned int& nHeight) const;
	bool	IsValid() const;
private:
	bool	m_bValid; //true of bitmap is in proper format
};

///////////////////////////////////////////////////////////////////////////////
#endif //_BMPVIEWER_H_

/*****************************************************************************
 * $Log: 
 *  3    Biblioteka1.2         10/10/2002 7:26:58 PMDarko Kolakovic 
 *  2    Biblioteka1.1         13/08/2002 8:12:50 AMDarko Kolakovic 
 *  1    Biblioteka1.0         06/08/2002 3:34:26 PMDarko Kolakovic 
 * $
 * Revision 1.1  2002/07/26 23:40:56  dkolaCVS
 * Created
 *
 *****************************************************************************/
