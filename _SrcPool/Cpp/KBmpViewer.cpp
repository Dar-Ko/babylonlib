/***********************************************************************
 $RCSfile: BmpViewer.cpp,v $
 $Revision: 3$   $Date: 10/10/2002 7:26:53 PM$
 $Author: Darko Kolakovic$

 Copyright © 2000-2001 All rights reserved. MIST Inc.
 Translates a bitmap content to ZafBitmapStruct
***********************************************************************/
//#include <zaf.hpp>
//#include <ugl/ugldib.h>
#include "KTrace.h"     //TRACE1 macro
#include "KBmpViewer.h"

///////////////////////////////////////////////////////////////////////////////
// CBmpLabel
WORD  CBmpLabel::m_wSignature = BMP_SIGNATURE; //'BM'
char* CBmpLabel::m_szFileExt   = "bmp";

/*Returns true if data stream begins with valid tag, 
  otherwise returns false.
 */
bool CBmpLabel::IsValid(const BYTE* pData //an encoded image in 
                                     //bitmap format
                       )
{
TRACE2("CBmpLabel::IsValid(pData @ %p) is %s.\n", 
		pData,
		( (pData[0] == 'B') && (pData[1] == 'M') ) ?
		"true" : "false");
//return ( *(WORD*)pData == (WORD)BMP_SIGNATURE );
return ( (pData[0] == 'B') && (pData[1] == 'M') );
}


///////////////////////////////////////////////////////////////////////////////
// CBmpViewer

//::CBmpViewer()---------------------------------------------------------------
/*
 */
CBmpViewer::CBmpViewer() :
	ZafImageData(NULL),
	m_bValid(false)
{
}

/*Conversion constructor
 */
CBmpViewer::CBmpViewer(BYTE* pData, const unsigned int nSize):
	ZafImageData(NULL),
	m_bValid(false)
{
Load(pData, nSize);
}

/*
CBmpViewer::CBmpViewer(const BYTE* pData, const unsigned int nSize):
	ZafImageData(NULL),
	m_bValid(false)
{
Load(pData, nSize);
}
*/

//::~CBmpViewer()--------------------------------------------------------------
/*
 */
CBmpViewer::~CBmpViewer()
{
}

//::IsValid()------------------------------------------------------------------
/*Validates data signature.

  Returns true if data begins with valid tag and version number, 
  otherwise returns false.
 */
bool CBmpViewer::IsValid() const
{
return m_bValid;
}

//::Load()---------------------------------------------------------------------
//TODO: Replace this with Kernal version
/*extern "C"*/ 
extern UGL_STATUS uglBMPToDDBFromMemory(void *handle, char *data, 
																						unsigned int len,
                                 UGL_DDB_ID *pDdbId, UGL_RECT *pSrcRect,
                                 UGL_POS dstX, UGL_POS dstY);
/*Loads an image from a data stream. If data are properly formatted,
  method converts the image to a Zaf bitmap.

  Returns true if image is successfully loaded. If data stream is not in 
  GIF format, false is returned.
 */
bool CBmpViewer::Load( BYTE* pData, //[in] data stream
						const unsigned int nSize //[in]
                      )
{
	if ( (m_bValid = CBmpLabel::IsValid( pData )) )
	{
			//Let UGL allocate a bitmap for us.
		imageBuffer = UGL_NULL;
		m_bValid = (::uglBMPToDDBFromMemory(((ZafScreenDisplay *)zafDisplay)->devID, 
											pData,
											nSize,
											&imageBuffer,
											UGL_NULL, 0, 0) == UGL_STATUS_OK);
		if (m_bValid)
		{
			width = ImageID()->width;
			height = ImageID()->height;
			#ifdef _DEBUG
				extern void DumpZafImageData(const ZafImageData& zafObject);
				DumpZafImageData(*this);
			#endif
		}
	}
	return m_bValid;
}

//-----------------------------------------------------------------------------
/*Converts an image to the Zaf bitmap.

	Returns true if successful, otherwise returns false.
 */
bool CBmpViewer::GetBitmap(ZafBitmapStruct*& pzafBmpResult //[out] image converted to a
							                               //bitmap
							 )
{
	TRACE0("CBmpViewer::GetBitmap()\n");
	if ( IsValid() )
	{
		if (!imageBuffer)
			return false;

 	 	pzafBmpResult = ConvertToOSBitmap();
    //SetStaticImageID(false);
			return true;

	}
	return false;
}

//::GetScreenSize()------------------------------------------------------------
/*Retrieves dimensions of an image in pixels.

  Returns: true if successful; false if data stream is not in valid format.
 */
bool CBmpViewer::GetSize(unsigned int& nWidth, 
               unsigned int& nHeight) const
{
	if ( IsValid() )
	{
		TRACE0("CBmpViewer::GetSize()");
		UGL_SIZE iWidth, iHeight;
		if (uglBitmapSizeGet(imageBuffer, &iWidth, &iHeight) == 
				UGL_STATUS_OK)
		{
			nWidth = (unsigned int) iWidth;
			nHeight = (unsigned int) iHeight;
			TRACE2("  = %dx%d.\n", iWidth, iHeight);
			return true;
		}
		else
		{
			TRACE0(" failed!\n");
			nWidth = nHeight = 0;
		}
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  3    Biblioteka1.2         10/10/2002 7:26:53 PMDarko Kolakovic 
 *  2    Biblioteka1.1         13/08/2002 8:12:46 AMDarko Kolakovic 
 *  1    Biblioteka1.0         06/08/2002 3:34:19 PMDarko Kolakovic 
 * $
 * Revision 1.3  2002/08/02 17:11:31  dkolaCVS
 * Commented out cause of memory leak
 *
 * Revision 1.1  2002/07/26 23:40:56  dkolaCVS
 * Created
 *
 *****************************************************************************/
