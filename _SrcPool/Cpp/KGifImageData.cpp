/*$Workfile: KGifImageData.cpp$: implementation file
  $Revision: 4$ $Date: 8/2/02 10:26:50 PM$
  $Author: Darko Kolakovic$
  
  Container for GIF(c) image raster data.
  GIF and 'Graphics Interchange Format' are trademarks of CompuServe, 
  Incorporated.
 */ 

/* Group=Images                                                              */

#ifndef __AFX_H__ /*MFC and TRACE macros are not included */
  #include "KTrace.h" //Trace macro
#endif

#include "KGifImageData.h"  //CGifImageData class

#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// CGifImageData
//::CGifImageData()------------------------------------------------------
/*
 */
CGifImageData::CGifImageData() :
  m_cLzwSize(0)
{
}

CGifImageData::~CGifImageData()
{
}

//::CopyAll()------------------------------------------------------------------
/*Copies all Image Raster Data from a data stream in Graphics Interchange Format.
  This method assumes that all image data are stored in a single continuous block
  in memory. 

  Returns: true if successful, or false if failed.
 */
bool CGifImageData::CopyAll(BYTE* pImageData //[in] image
          //data
          )
{
TRACE1("CGifImageData::CopyAll(from 0x%p)\n", pImageData);
if (pImageData == NULL)
  return false;

m_cLzwSize = pImageData[0];

  //Get all sub-blocks
return (m_gifImage.CopyAll(&pImageData[sizeof(m_cLzwSize)]));
}

//::Copy()---------------------------------------------------------------------
/*Copies a single Image Raster Data sub-block from a data stream in Graphics 
  Interchange Format.

  Returns: true if successful, or false if failed.
 */
bool CGifImageData::Copy(BYTE* pImageData //[in] image
          //data
          )
{
TRACE1("CGifImageData::Copy(from 0x%p)\n", pImageData);
if (pImageData == NULL)
  return false;

m_cLzwSize = pImageData[0];
  //Get first sub-block
m_gifImage.Copy(&pImageData[sizeof(m_cLzwSize)]);

return true;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  4    Biblioteka1.3         8/2/02 10:26:50 PM   Darko Kolakovic 
 *  3    Biblioteka1.2         8/2/02 12:36:05 AM   Darko           CopyAll()
 *       sub-blocks
 *  2    Biblioteka1.1         8/1/02 2:58:37 PM    Darko Kolakovic 
 *  1    Biblioteka1.0         8/1/02 1:23:00 AM    Darko           
 * $
 * 2001 Initial version in Babylon Lib
 * 1990 v.89a enhanced GIF CompuServe Incorporated
 * 1987 v.87a Graphics Interchange Format (GIF) devised by the UNISYS Corp. and 
 *  Compuserve
 *****************************************************************************/
