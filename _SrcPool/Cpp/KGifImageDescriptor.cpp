/*$Workfile: KGifImageDescriptor.cpp$: implementation file
  $Revision: 4$ $Date: 8/19/02 10:43:26 AM$
  $Author: Darko Kolakovic$
  
  Describes an image enbedded in GIF(c) Data Stream.
  GIF and 'Graphics Interchange Format' are trademarks of CompuServe, 
  Incorporated.
 */ 

/* Group=Images                                                              */

#ifndef __AFX_H__ /*MFC and TRACE macros are not included */
  #include "KTrace.h" //Trace macro
#endif

#ifndef __KPROGCST_H__
  #define _ENDIAN_LITTLE_ 0x1234
    /*Byte order, according to significance of bytes                         */
  #define _ENDIAN_ORDER_ _ENDIAN_LITTLE_
   /*Swaps tailing bytes with bytes from the beginning of the two-bytes WORD  */
  #define SWAP_WORD_ENDIAN(w)  (WORD) ((WORD) ((w)<<8)|((w)>>8))
#endif

#include "KGifImageDescriptor.h"  //CGifImageDescriptor class

#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// CGifImageDescriptor
//::CGifImageDescriptor()------------------------------------------------------
/*
 */
CGifImageDescriptor::CGifImageDescriptor() :
  CGifBlock(CGifBlock::IMAGE_DESCRIPTOR),
  m_wLeftPos(0),
  m_wTopPos(0),
  m_wWidth(0),
  m_wHeight(0),
  m_cControlFlags(0)
{
}

CGifImageDescriptor::~CGifImageDescriptor()
{
}

#ifdef _DEBUG
//::Dump()---------------------------------------------------------------------
/*Dumps the content of the CGifImageDescriptor object to a standard 
  output stream.
 */
void CGifImageDescriptor::Dump() const
{
TRACE1("CGifImageDescriptor @ %p\n  {\n", this);
const int BUFFER_SIZE = 256;
char* szOutput = new char[BUFFER_SIZE];
Dump(szOutput);

if (strlen(szOutput) >= BUFFER_SIZE)
  {
    //Try to salvage something 
  TRACE1(" failure: %d bytes buffer too small\n", BUFFER_SIZE);
  }
else
  {
  TRACE1("%s",szOutput);
  }

delete[] szOutput;

if(HasColorTable())
  m_gifLocalColorTable.Dump();

}

/*Dumps the content of the GIF Logical Screen Descriptor block as formatted 
  string to the given buffer. Buffer size have to be sufficient to hold the 
  dump. There is no error checking.

  Returns pointer to the output buffer if successful, or NULL in case of failure.
 */
char* CGifImageDescriptor::Dump(char* szOutput
                                       ) const
{
if (szOutput != NULL)
  {
  sprintf(szOutput,
            "{\nm_wLeftPos = %d,\nm_wTopPos = %d,\n"
            "m_wWidth = %d,\nm_wHeight = %d,\n"
            "m_cControlFlags = 0x%x (has%s Local Color Table,\n"
            "%Sintrelaced image,\n"
            "Table is%s sorted,\n"
            "Local Color Table Size %d),\n",
            m_wLeftPos, //SWAP
            m_wTopPos,
            m_wWidth,
            m_wHeight,
          m_cControlFlags,
          HasColorTable() ? "" : " not",
          IsInterlaced() ? "" : "un",
          IsColorTableSorted() ? "" : " not",
          GetColorTableSize());
  return szOutput;
  }
return NULL;
}

#endif //_DEBUG

//::Copy()---------------------------------------------------------------------
/*Copies Image Descriptor from a data stream in Graphics Interchange
  Format.

  Returns: true if successful, or false if Block Data does not start with 
  image separator (0x2C) as a block label.
 */
bool CGifImageDescriptor::Copy(BYTE* pBlockData //[in] image
          //descriptor block in Graphics Interchange Format (GIF)
          )
{
TRACE1("CGifImageDescriptor::Copy(from 0x%p)\n", pBlockData);
if ((pBlockData == NULL) || (pBlockData[0] != m_cLabel) )
  return false;

  //This is a hack to speed up copying;
  //don't change byte order, endian byte reordering is done on demand
const int LABEL_SIZE = CGifBlock::GetLength();
memcpy(&m_wLeftPos, &pBlockData[LABEL_SIZE], GetLength() - LABEL_SIZE);


if (HasColorTable())
  {
  return m_gifLocalColorTable.Copy(&pBlockData[GetLength()], GetColorTableSize());
  }
return true;
}

//::operator=()----------------------------------------------------------------
/*Assigns a new value to a Logical Screen Descriptor.
  
  Returns: A reference to the current object.
 */
CGifImageDescriptor& CGifImageDescriptor::operator=(
               const CGifImageDescriptor& gifSource 
               )
{
m_wLeftPos = gifSource.m_wLeftPos;
m_wTopPos  = gifSource.m_wTopPos;
m_wWidth   = gifSource.m_wWidth; 
m_wHeight  = gifSource.m_wHeight;
m_gifLocalColorTable  = gifSource.m_gifLocalColorTable;
return *this;
}

//::GetLength()------------------------------------------------------------------
/*Obtains length of the fixed part of the data block.

  Returns size of the section in bytes.
 */
const unsigned int CGifImageDescriptor::GetLength()
{
  //Note: calculating block size as a sum of fields prescribed by GIF allows
  //developers to add some custom members if necessary.
return (sizeof(BYTE) + sizeof(WORD)*4 + sizeof(BYTE));
}

//::GetBlockLength()-----------------------------------------------------------
/*Obtains block's length including length of optional Local Color Table.


  Returns: size of the GIF header's fixed and optional parts in bytes.
 */
unsigned int CGifImageDescriptor::GetBlockLength() const
{
if (!HasColorTable())
  return GetLength();
else
  return (GetLength() + GetColorTableSize() * CGifColor::GetLength());
}

//::GetBlockLength()-----------------------------------------------------------
/*Obtains block's length including length of optional Local Color Table and
  image raster data.

  Returns: size of the GIF header's fixed and optional parts in bytes.
 */
unsigned int CGifImageDescriptor::GetBlockLength(BYTE* pBlockData //[in]
                                                 )
{
if (pBlockData[0] == GIF_IMAGE_SEPARATOR) 
  {
  return (GetLength() + 
       CGifImageDescriptor::GetColorTableSize(pBlockData) * CGifColor::GetLength());
  }

return 0;
}

//::HasColorTable()------------------------------------------------------------
/*Validates presence of a Local Color Table. If the Local Color Table Flag is
  set, then the Local Color Table will immediately follow the Image Descriptor.
  If the flag is not set, no Local Color Table follows.

     Field format:

      7 6 5 4 3 2 1 0  bit (9th byte in Logical Screen Descriptor block)
     +---------------+
     |l|     | |     | l= 1 Local Color Table follows Image Descriptor
     +---------------+ l= 0 no Local Color Table follows

  Returns: true if a Local Color Table is present, or false if it is not.
 */
bool CGifImageDescriptor::HasColorTable() const
{
  //Valid bit is 1000 0000
return ((m_cControlFlags & 0x80) == 0x80);
}

//::IsInterlaced()-------------------------------------------------------------
/*Tests if a Local Color Table is ordered by importance. Typically, the 
  ordered tables will have the most frequent color first. This helps a decoder, 
  with fewer available colors, in choosing the best subset of colors; the decoder
  may use an initial segment of the table to render the graphic.

     Field format:

      7 6 5 4 3 2 1 0  bit (9th byte in Image Descriptor block)
     +---------------+
     | |i| |         | i = 1 image formatted in Interlaced order
     +---------------+ i = 0 image is formatted in sequential order

  Interlacing may be ignored by the browser.  
  Interlaced images are stored in a four groups producing an interlace pattern: 

      1. Every 8-th row, starting with row 0.
      2. Every 8-th row, starting with row 4.
      3. Every 4-th row, starting with row 2.
      4. Every 2-nd row, starting with row 1.

  Returns: true if an image is formatted in Interlaced order, or false
  for images sequentially stored.
 */
bool CGifImageDescriptor::IsInterlaced() const
{
  //Valid bit is 0100 0000
return ((m_cControlFlags & 0x40) == 0x40);
}

//::IsColorTableSorted()-------------------------------------------------------
/*Tests if a Local Color Table is ordered by importance. Typically, the 
  ordered tables will have the most frequent color first. This helps a decoder, 
  with fewer available colors, in choosing the best subset of colors; the decoder
  may use an initial segment of the table to render the graphic.

     Field format:

      7 6 5 4 3 2 1 0  bit (9th byte in Image Descriptor block)
     +---------------+
     | | |s|         | s = 1 color palette is sorted (v. 89a)
     +---------------+ s = 0 color palette is not sorted  (v. 89a)
                       s = 0 reserved  (v. 87a)

  Returns: true if Local Color Table is sorted, in order of decreasing 
  importance. If table is not sorted, false is returned.
 */
bool CGifImageDescriptor::IsColorTableSorted() const
{
  //Valid bit is 0010 0000
return ((m_cControlFlags & 0x20) == 0x20);
}

//::GetColorTableSize()--------------------------------------------------------
/*Retrieves the number of elements of a Local Color Table. 
  Local Color Table is a color palette used for the image following the Local 
  Color Table in data stream and size of the Local Color Table corresponds 
  to number of colors (elements) in the palette. 
  Each color is represented with 3 bytes (RGB bytes). Number of bits allowed 
  for each pixel is in field is stored in the 3 least significant bits of the 
  fourth byte. The value of the nnn field has range [0,7], which represents 
  1 to 8 bits per each pixel. To obtain actual number of elements of the color 
  table, raise 2 to [the value of the field + 1]. As consequence of this, valid
  numbers of colors are [2, 4, 8, 16, 32, 64, 128, 256].
  
  Therefore size of the table in bytes is:

        Range of nnn is [0,7]
        NumberOfBitsPerPixel = nnn + 1
        NumberOfTableElements = 2 ^ NumberOfBitsPerPixel
        NumberOfColors = NumberOfTableElements
        NumberOfColors Range is [2, 256] 
        LocalColorTableSize = 3 * NumberOfTableElements [bytes]
        LocalColorTableSize = 3 * (2^(nnn+1)) [bytes]

     Field format:

      7 6 5 4 3 2 1 0  bit (9th byte in Image Descriptor block)
     +---------------+
     | |     | |n n n| nnn + 1 = number of bits per pixel
     +---------------+

  Returns: maximum number of colors within color table (palette) used for 
  an image.

  Note: if Local Color Table flag l is set to zero (HasColorTable() method 
  returned false), actual size of the color table is zero and the table is
  omitted from the data stream.

  See Also: CGifColor, HasColorTable()
 */
unsigned int CGifImageDescriptor::GetColorTableSize() const
{
  //Valid bits are 0000 0111
return 1 << ((m_cControlFlags & 0x07) + 1);
}

unsigned int CGifImageDescriptor::GetColorTableSize(BYTE* pBlockData//[in]
                                                    )
{
ASSERT(pBlockData != NULL);
const int BLOCK_SIZE = sizeof(BYTE) + sizeof(WORD)*4;
BYTE& cControlFlags = pBlockData[BLOCK_SIZE];
if ((cControlFlags & 0x80) == 0x80)
  return 1 << ((cControlFlags & 0x07) + 1);
return 0;
}

//::GetImageSize()-------------------------------------------------------------
/*Retrieves dimensions of an image in pixels.

  Note: Values are stored in 'Little Endian' byte order (the Least Significant 
  Byte (LSB) first).
 */
void CGifImageDescriptor::GetImageSize(unsigned int& nWidth, //[out] 
                                                //image width [pixel]
                                                unsigned int& nHeight //[out] 
                                                //image height [pixel]
                                                ) const
{
//Note: values are stored in '"Little Endian" order
#if ( _ENDIAN_ORDER_ ==  _ENDIAN_LITTLE_) //CPU _M_IX86, __arm__
  nWidth  = m_wWidth;
  nHeight = m_wHeight;
#else
  nWidth  = SWAP_WORD_ENDIAN(m_wWidth);
  nHeight = SWAP_WORD_ENDIAN(m_wHeight);
#endif
}

//::GetImageWidth()------------------------------------------------------------
/*
 */
unsigned int CGifImageDescriptor::GetImageWidth() const
{
//Note: values are stored in '"Little Endian" order
#if ( _ENDIAN_ORDER_ ==  _ENDIAN_LITTLE_) //CPU _M_IX86, __arm__
  return m_wWidth;
#else
  return SWAP_WORD_ENDIAN(m_wWidth);
#endif
}

//::GetImageHeight()-----------------------------------------------------------
/*
 */
unsigned int CGifImageDescriptor::GetImageHeight() const
{
//Note: values are stored in '"Little Endian" order
#if ( _ENDIAN_ORDER_ ==  _ENDIAN_LITTLE_) //CPU _M_IX86, __arm__
  return m_wHeight;
#else
  return SWAP_WORD_ENDIAN(m_wHeight);
#endif
}

//::GetImagePos()--------------------------------------------------------------
/*Retrieves position of an image on the Logical Screen in pixels. 
  The Logical Screen defines the viewport area of the display device within
  which the images will be rendered.
  The logical screen width and height can both be larger than the physical 
  display. 

  Note: Values are stored in 'Little Endian' byte order (the Least Significant 
  Byte (LSB) first).
 */
void CGifImageDescriptor::GetImagePos(unsigned int& nLeft, //[out] 
                                                //... [pixel]
                                      unsigned int& nTop //[out] 
                                                //... [pixel]
                                                ) const
{
//Note: values are stored in '"Little Endian" order
#if ( _ENDIAN_ORDER_ ==  _ENDIAN_LITTLE_) //CPU _M_IX86, __arm__
  nLeft = m_wLeftPos;
  nTop  = m_wTopPos;
#else
  nLeft = SWAP_WORD_ENDIAN(m_wLeftPos);
  nTop  = SWAP_WORD_ENDIAN(m_wTopPos);
#endif
}

//::GetColorTable()------------------------------------------------------
/*Obtains local color palette used by an image following the Local 
  Color Table in Gif data stream. 

  Returns: Local Color Table used to render graphics.
 */
CGifColorTable CGifImageDescriptor::GetColorTable() const
{
return m_gifLocalColorTable;
}

CGifColorTable& CGifImageDescriptor::GetColorTable()
{
return m_gifLocalColorTable;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  4    Biblioteka1.3         8/19/02 10:43:26 AM  Darko Kolakovic Added
 *       GetImageWidth()
 *  3    Biblioteka1.2         8/1/02 1:23:56 AM    Darko           CGifImageData
 *  2    Biblioteka1.1         7/31/02 4:44:04 AM   Darko           Read block
 *       sizes from a stream
 *  1    Biblioteka1.0         7/30/02 5:11:24 PM   Darko Kolakovic 
 * $
 * 2001 Initial version in Babylon Lib
 * 1990 v.89a enhanced GIF CompuServe Incorporated
 * 1987 v.87a Graphics Interchange Format (GIF) devised by the UNISYS Corp. and 
 *  Compuserve
 *****************************************************************************/
