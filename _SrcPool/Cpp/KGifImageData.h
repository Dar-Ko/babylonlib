/*$Workfile: KGifImageData.h$: header file
  $Revision: 3$ $Date: 2003-09-30 11:09:58$
  $Author: Darko$

  Container for GIF(c) image raster data.
  GIF and 'Graphics Interchange Format' are trademarks of CompuServe, 
  Incorporated.
 */ 

/* Group=Images                                                              */

#ifndef _KGIFIMAGEDATA_H_
    //*$Workfile: KGifImageData.h$ sentry
  #define _KGIFIMAGEDATA_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#include "KTypedef.h" //uint8 definition
#include "KGif.h"     //CGifBlock class
///////////////////////////////////////////////////////////////////////////////
/*The image data consists of a sequence of sub-blocks containing an index into 
  the active color table, for each pixel in the image. Pixel indices are in 
  order of left to right and from top to bottom. Each index must be within the 
  range of the size of the active color table, starting at 0. The sequence of 
  indices is encoded using the LZW Algorithm with variable-length code.
  Each data sub-blocks have size at most 255 bytes.

                          Bytes
        +------------------+---+
        |   LZW Code Size  | 0 | LZW Minimum Code Size (1 byte)
        +------------------+---+
        |  Data Sub-block  | i | i [0,255] Image Compressed Data 
        +------------------+---+
        ...
        +------------------+---+ 
        |  Data Sub-block  | j | j [0,255] Image Compressed Data 
        +------------------+---+
        |  LZW Terminator  | n | LZW Compression Terminator (2^LZWMinCode +1)
        +------------------+---+
        ...
        +------------------+---+
        |     Terminator   | n | Block Terminator (0x00) (1 byte)
        +------------------+---+

  See also: CGifDataSubblock
 */
class CGifImageData
{
public:
  CGifImageData();
  virtual ~CGifImageData();
  bool Copy(uint8* pImageData);
  bool CopyAll(uint8* pImageData);

//protected:
  uint8 m_cLzwSize; //initial number of bits used for the compression codes
  CGifDataSubblock m_gifImage;
};

///////////////////////////////////////////////////////////////////////////////
#endif //_KGIFIMAGEDATA_H_

/*CompuServe legal stuff
  June 15, 1987 (c)1987,1988,1989,1990
  GIF format (c) CompuServe Incorporated, 1987 All rights reserved.
  Graphics Interchange Format (GIF) devised by the UNISYS Corp. and Compuserve.

  While this document describing GIF format is copyrighted, the information 
  contained within is made available for use in computer software without
  royalties, or licensing restrictions.

  The Graphics Interchange Format(c) is the copyright property of 
  CompuServe Incorporated. Only CompuServe Incorporated is authorized to define, 
  redefine, enhance, alter, modify or change in any way the definition of 
  the format.

  CompuServe Incorporated hereby grants a limited, non-exclusive, royalty-free 
  license for the use of the Graphics Interchange Format(sm) in computer software;
  computer software utilizing GIF(sm) must acknowledge ownership of the Graphics 
  Interchange Format and its Service Mark by CompuServe Incorporated, in User and
  Technical Documentation. Computer software utilizing GIF, which is distributed 
  or may be distributed without User or Technical Documentation must display to 
  the screen or printer a message acknowledging ownership of the Graphics 
  Interchange Format and the Service Mark by CompuServe Incorporated; 
  in this case, the acknowledgement may be displayed in an opening screen or
  leading banner, or a closing screen or trailing banner. A message such as the 
  following may be used: 
  "The Graphics Interchange Format(c) is the Copyright property of 
  CompuServe Incorporated. 
  GIF(sm) is a Service Mark property of CompuServe Incorporated." 
 */

/*****************************************************************************
 * $Log: 
 *  3    Biblioteka1.2         2003-09-30 11:09:58  Darko           Replaced DWORD,
 *       WORD with uint32, uint16
 *  2    Biblioteka1.1         2002-08-01 14:58:41  Darko Kolakovic 
 *  1    Biblioteka1.0         2002-08-01 01:23:05  Darko           
 * $
 * 2001 Initial version in Babylon Lib
 * 1990 v.89a enhanced GIF CompuServe Incorporated
 * 1987 v.87a Graphics Interchange Format (GIF) devised by the UNISYS Corp. and 
 *  Compuserve
 *****************************************************************************/
