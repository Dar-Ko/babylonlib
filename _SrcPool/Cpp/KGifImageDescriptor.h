/*$Workfile: KGifImageDescriptor.h$: header file
  $Revision: 4$ $Date: 8/19/02 10:43:54 AM$
  $Author: Darko Kolakovic$

  Describes an image enbedded in GIF(c) Data Stream.
  GIF and 'Graphics Interchange Format' are trademarks of CompuServe, 
  Incorporated.
 */ 

/* Group=Images                                                              */

#ifndef _KGIFIMAGEDESCRIPTOR_H_
    //KGifImageDescriptor.h sentry
  #define _KGIFIMAGEDESCRIPTOR_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#include "KTypedef.h" //BYTE definition
#include "KGif.h"     //CGifBlock class
///////////////////////////////////////////////////////////////////////////////
/*The Image Descriptor contains the parameters necessary to process a image 
  raster data. The coordinates given in this block refer to coordinates within 
  he Logical Screen, and are given in pixels. 
  This block is a Graphic-Rendering Block, optionally preceded by one or more 
  Control blocks such as the Graphic Control Extension, and may be optionally 
  followed by a Local Color Table; the Image Descriptor is always followed by 
  the image data.

  This block is REQUIRED for an image. Exactly one Image Descriptor must be 
  present per image in the Data Stream. An unlimited number of images may be 
  present per Data Stream.

  Note: The top and left position of the images are within the defined 
  logical screen.


         bits
         7 6 5 4 3 2 1 0 Bytes
        +-------------------+
        |     Label     | 0 | image separator (0x2C, ',') (1 byte)
        +---------------+---+
        |               | 1 |
        +- Image Left  -+   + image left position on the logical screen 
        |               | 2 | in pixels (LSB first)
        +---------------+   +
        |               | 3 |
        +-  Image Top  -+   + image top position on the logical screen 
        |               | 4 | in pixels (LSB first)
        +---------------+   +
        |               | 5 |
        +- Image Width -+   + width of the image in pixels (LSB first)
        |               | 6 |
        +---------------+   +
        |               | 7 |
        +- Image Height-+   + height of the image in pixels (LSB first)
        |               | 8 |
        +-+-----+-+-----+   + l = 1 local color table follows Descriptor
        |l|i|s|0 0| nnn | 9 | i = 1 interlaced image
        +-+-----+-+-----+---+ s = 1, local color table is sorted (89a)
                              nnn + 1 = bits/pixel in image
                              bits 3 and 4 are reserved for future use
        +-------------------+ 
        | Local Color Table | optional data block that follows Descriptor
        +-------------------+ if l = 1. Block contains color palette


  See also: CGifLogicalScreenDescriptor, 
            {HTML: <A HREF ="Res/gif89a.htm#Logical_Screen_Descriptor"> Logical Screen Descriptor</A>}
 */
class CGifImageDescriptor : protected CGifBlock
{
public:
  CGifImageDescriptor();
  virtual ~CGifImageDescriptor();
  #ifdef _DEBUG
    virtual void Dump() const;
    virtual char* Dump(char* szOutput) const;
  #endif
  bool Copy(BYTE* pBlockData);
  static const unsigned int GetLength();
  unsigned int GetBlockLength() const;
  static unsigned int GetBlockLength(BYTE* pBlockData);
  bool HasColorTable() const;
  bool IsInterlaced() const;
  bool IsColorTableSorted() const;
  static unsigned int GetColorTableSize(BYTE* pBlockData);
  unsigned int GetColorTableSize() const;
  void GetImageSize(unsigned int& nWidth, unsigned int& nHeight) const;
  unsigned int GetImageWidth() const;
  unsigned int GetImageHeight() const;
  void GetImagePos(unsigned int& nLeft, unsigned int& nTop) const;
  CGifColorTable GetColorTable() const;
  CGifColorTable& GetColorTable();
  CGifImageDescriptor& operator=(
                 const CGifImageDescriptor& gifSource);
//  int GetBlockLength(BYTE* pBlockData);

protected:
   //Turn byte alignment on
  #pragma pack(push, 1)
    WORD m_wLeftPos;      //image left position on the logical screen
    WORD m_wTopPos;       //image top position on the logical screen
    WORD m_wWidth;        //image width
    WORD m_wHeight;       //image height
    BYTE m_cControlFlags; //image control flags

  //Turn byte alignment off
  #pragma pack(pop)

  CGifColorTable m_gifLocalColorTable; //optional local color palette
};

///////////////////////////////////////////////////////////////////////////////
#endif //_KGIFIMAGEDESCRIPTOR_H_

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
 *  4    Biblioteka1.3         8/19/02 10:43:54 AM  Darko Kolakovic Added
 *       GetImageWidth()
 *  3    Biblioteka1.2         8/1/02 1:23:59 AM    Darko           CGifImageData
 *  2    Biblioteka1.1         7/31/02 4:44:07 AM   Darko           Read block
 *       sizes from a stream
 *  1    Biblioteka1.0         7/30/02 5:11:30 PM   Darko Kolakovic 
 * $
 * 2001 Initial version in Babylon Lib
 * 1990 v.89a enhanced GIF CompuServe Incorporated
 * 1987 v.87a Graphics Interchange Format (GIF) devised by the UNISYS Corp. and 
 *  Compuserve
 *****************************************************************************/

