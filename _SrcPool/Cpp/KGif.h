/*$Workfile: KGif.h$: header file
  $Revision: 20$ $Date: 2005-06-28 13:37:56$
  $Author: Darko Kolakovic$

  Encapsulation of images in Graphics Interchange Format(c) GIF v89a.
  GIF and 'Graphics Interchange Format' are trademarks of CompuServe, Incorporated.
 */

/* Group=Images                                                              */

#ifndef _KGIF_H_
    //$Workfile: KGif.h$ sentry
  #define _KGIF_H_
#define HANDLE_PRAGMA_PACK_PUSH_POP //gcc 2.96.3

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#include "KTypedef.h" //ISO C99 type definitions

const uint8 GIF_EXTENSION_INTRODUCER = 0x21;  //GIF extension introducer;
                                //identifies a GIF Extension block  (0x21, '!')
const uint8 GIF_IMAGE_SEPARATOR = 0x2C; //GIF image separator identifies
                                       //begining of an Image Descriptor block
                                       //(0x2C, ',')
const uint8 GIF_TERMINATOR      = 0x3B; //GIF Terminator 0x3B (';') used to
                                       //mark end of a GIF data stream
const uint8 GIF_BLOCKTERMINATOR = 0x00; //GIF Extension Block Terminator marks
                                       //the end of a block
const uint8 GIF_EXT_PLAIN_TEXT      = 0x01; //Plain Text Extension label (0x01)
const uint8 GIF_EXT_GRAPHIC_CONTROL = 0xF9; //Graphic Control Extension label (0xF9)
const uint8 GIF_EXT_COMMENT         = 0xFE; //Comment Extension label (0xFE)
const uint8 GIF_EXT_APPLICATION     = 0xFF; //Application Extension label (0xFF)

///////////////////////////////////////////////////////////////////////////////
/*Collection of labels, tags and keywords used in various sections of
  Graphics Interchange Format(c),
 */
class CGifLabel
{
public:
  CGifLabel();
  static char* m_szSignature; //signature identifying valid GIF format
  static char* m_szFileExt  ; //common file extension used in 8.3 file
                              //systems
  static char* m_szVersion[2];//= {"87a","89a"}; //supported version numbers
  static bool  IsValid(const uint8* pData);
};

///////////////////////////////////////////////////////////////////////////////
/*Gif data sub-block
  The Block Size field in a block, counts the number of bytes remaining in the
  block, not counting the Block Size field itself, and not counting the
  Block Terminator, if one is to follow.

                           Bytes
        +------------------+---+
        |   block size n   | 0 |  n number of bytes in the data sub-block [0,255]
        +------------------+   |
        |    block data    | 1 |
        +------------------+   |
        |    block data    | 2 |  Data Values (n bytes)
        +------------------+   |
         ...
        +------------------+   |
        |    block data    |n-1|
        +------------------+   |
        |    block data    | n |
        +------------------+   |
        |    block data    |n+1|
        +------------------+---+
 */
class CGifDataSubblock
{
public:
  CGifDataSubblock();
  virtual ~CGifDataSubblock();
  uint8* Copy(const uint8* pDataSubblock);
  bool   CopyAll(uint8* pImageData);
  void   RemoveAll();
  int    GetSize() const;
  bool   SetSize(const unsigned int nNewSize);
  uint8* GetBuffer();
  uint8& operator[](int nIndex);
  uint8  operator[](int nIndex) const;
  static int GetAllSubblockLength(uint8* pSubblockData);
  static int GetAllDataLength(uint8* pSubblockData, unsigned int& nBlockCount);

private:
  unsigned int  m_nSize; //data block size in bytes [0,255]
  uint8*        m_pData; //data container
};

///////////////////////////////////////////////////////////////////////////////
/*Class CGifBlock represents a labeled Gif (Graphics Interchange Format)
  data blocks.
  Generally, a Gif file (or a data stream) consists of a sequence of data blocks
  and sub-blocks that contain various information relevant in the reproduction of
  an image.

  Some of the data blocks have fixed position in the data structure, like Header or
  Logical Screen Descriptor. Some of the blocks begin with a block separator. This
  class is a base class for the group of Gif data blocks with a block separator.
  Following is a general form of such data blocks:

                           Bytes
        +------------------+---+
        |    block label   | 0 |  Block separator (1 byte)
        +------------------+   |
        |                  | 1 |
        +                  +   |
        |    block data    | 2 |  Block parameters and data (n bytes)
        +                  +   |
         ...
        +                  +   |
        |                  | n |
        +------------------+---+

  Gif blocks can be classified into three groups: Control, Graphic-Rendering and
  Special Purpose blocks.
  Each group has a range of allowed values for the label:
    - Graphic Rendering blocks [0x00, 0x3B) and (0x3B, 0x7F]
         ([0, 127] excluding 59);
    - Control blocks [0x80, 0xF9] ([128, 249]) and 0x3B (59);
    - Special Purpose blocks [0xFA, 0xFF] ([250, 255]).


  See also: GIF Graphics Interchange Format
  {html: <a href="Documentation/gif87a.htm"> data blocks</a>}

 */
class CGifBlock
{
public:
  enum TYPE
    {
    GIF_EXTENSION    = GIF_EXTENSION_INTRODUCER,  //extension introducer
                              // identifies a GIF Extension block  (0x21, '!')
    IMAGE_DESCRIPTOR = GIF_IMAGE_SEPARATOR,  //image separator identifies an Image
                              //Descriptor block (0x2C, ',')
    TRAILER          = GIF_TERMINATOR,  //trailer identifies GIF stream terminator
                              //block (0x3B, ';')
    UNKNOWN          = 0x100  //uknown block
    };

  CGifBlock(const TYPE iBlockType);
  static TYPE GetType(uint8& cData);
  static unsigned int GetBlockLength(uint8* pBlockData);
  const unsigned int GetLength() const;

protected:
  uint8 m_cLabel;  //block indentificator

};


///////////////////////////////////////////////////////////////////////////////
/*Gif Extension blocks are extensions of the basic GIF 87a definition, adding
  new methods of an image.
  A GIF Extension block may immediately preceded any Image Descriptor or occur
  before the GIF Trailer.

         bits
         7 6 5 4 3 2 1 0 Bytes
        +---------------+---+
        |     Label     | 0 |  Extension Block Introducer (0x21, '!') (1 byte)
        +---------------+   +
        |               | 1 |
        +               +   |
        |    Function   | 2 |  Extension Function parameters and data (n bytes)
        +               +   |
         ...
        +               +   |
        |               | n |
        +---------------+---+
        |   Terminator  |n+1|  Block Terminator (0x00) (1 byte)
        +---------------+---+

  Note: All GIF decoders must be able to recognize the existence of a GIF
  Extension Blocks and ignore them if unable to handle the function embedded
  in the block.
 */
class CGifExtension : protected CGifBlock
{
public:
  enum FUNCTION
    {
    PLAIN_TEXT      = 0x01, //Plain Text Extension label (0x01)
    GRAPHIC_CONTROL = 0xF9, //Graphic Control Extension label (0xF9)
    COMMENT         = 0xFE, //Comment Extension label (0xFE)
    APPLICATION     = 0xFF, //Application Extension label (0xFF)
    UNKNOWN         = 0x100 //uknown GIF Extension function
    };

  CGifExtension(const FUNCTION iBlockType);
  static FUNCTION GetType(uint8& cData);
  static unsigned int GetBlockLength(uint8* pBlockData);

protected:
  uint8 m_cLabel;  //extension's function indentificator
};

///////////////////////////////////////////////////////////////////////////////
/*Plain Text Extension
  The Plain Text Extension contains textual data and the parameters necessary to render that data as a graphic, in a simple form. The textual data will be encoded with the 7-bit printable ASCII characters. Text data are rendered using a grid of character cells defined by the parameters in the block fields. Each character is rendered in an individual cell. The textual data in this block is to be rendered as mono-spaced characters, one character per cell, with a best fitting font and size. For further information, see the section on Recommendations below. The data characters are taken sequentially from the data portion of the block and rendered within a cell, starting with the upper left cell in the grid and proceeding from left to right and from top to bottom. Text data is rendered until the end of data is reached or the character grid is filled. The Character Grid contains an integral number of cells; in the case that the cell dimensions do not allow for an integral number, fractional cells must be discarded;
an encoder must be careful to specify the grid dimensions accurately so that this does not happen. This block requires a Global Color Table to be available; the colors used by this block reference the Global Color Table in the Stream if there is one, or the Global Color Table from a previous Stream, if one was saved. This block is a graphic rendering block, therefore it may be modified by a Graphic Control Extension. This block is OPTIONAL; any number of them may appear in the Data Stream.


 */
class CGifPlainTextExt : protected CGifExtension
{
public:
  CGifPlainTextExt();
  ~CGifPlainTextExt();
  static const unsigned int GetLength();
  static unsigned int GetBlockLength(uint8* pBlockData);

protected:
   //Turn byte alignment on
  #pragma pack(1)
    uint8 m_cSize;        //block size fixed value of 12
    uint16 m_wGridLeftPos; //text grid left position
    uint16 m_wGridTopPos;  //text grid top position
    uint16 m_wGridWidth;   //text grid width
    uint16 m_wGridHeight;  //text grid height
    uint8 m_cCellWidth;   //character cell width
    uint8 m_cCellHeight;  //character cell height
    uint8 m_cFgColor;     //text foreground color index
    uint8 m_cBkColor;     //text background color index

  //Turn byte alignment off
  #pragma pack()
};

///////////////////////////////////////////////////////////////////////////////
/*Graphic Control Extension
 */
class CGifGraphicControlExt : protected CGifExtension
{
public:
  CGifGraphicControlExt();
  ~CGifGraphicControlExt();
  static const unsigned int GetLength();
  static unsigned int GetBlockLength(uint8* pBlockData);

protected:
   //Turn byte alignment on
  #pragma pack(1)
    uint8 m_cSize;             //block size fixed value of 4
    uint8 m_cControlFlags;     //Graphic Control flags
    uint16 m_wDelayTime;        //delay time [0.01 s]
    uint8 m_cTransparentColor; //transparent color index

  //Turn byte alignment off
  #pragma pack()
};

///////////////////////////////////////////////////////////////////////////////
/*Comment Extension
 */
class CGifCommentExt : protected CGifExtension
{
public:
  CGifCommentExt();
  ~CGifCommentExt();
  static const unsigned int GetLength();
  static unsigned int GetBlockLength(uint8* pBlockData);

protected:
   //Turn byte alignment on
  #pragma pack(1)

  //Turn byte alignment off
  #pragma pack()
};

///////////////////////////////////////////////////////////////////////////////
/*Application Extension
 */
class CGifApplicationExt : protected CGifExtension
{
public:
  CGifApplicationExt();
  ~CGifApplicationExt();
  static const unsigned int GetLength();
  static unsigned int GetBlockLength(uint8* pBlockData);

protected:
   //Turn byte alignment on
  #pragma pack(1)
    uint8 m_cSize;                 //block size fixed value of 11
    char m_cAppIdentifier[8];     //application identifier (ASCII)
    uint8 m_cAppAuthentication[3]; //application authentication code

  //Turn byte alignment off
  #pragma pack()
};

///////////////////////////////////////////////////////////////////////////////
/*This structure describes a single color used in a GIF image.
  A GIF color consists of three byte values representing the relative
  intensities of red, green and blue color component respectively.
  A fractional intensity of the color could have any value from none (0) to
  full (255).  For display, if the device supports fewer than 8 bits per color
  component, the higher order bits of each component are used. In the creation
  of a GIF color with hardware supporting fewer than 8 bits per component, the
  component values for the hardware should be converted to the 8-bit format with
  the following calculation:

     NewComponentValue = OriginalComponentValue*255/(2**N - 1),
          where N is number of bits per color for target device.

  This assures accurate translation of colors for all displays.


         bits
         7 6 5 4 3 2 1 0  Bytes
        +---------------+---+
        | red intensity | 0 |   intensity of red color component [0,255]
        +---------------+   |
        |green intensity| 1 |   intensity of green color component [0,255]
        +---------------+   |
        | blue intensity| 2 |   intensity of blue color component [0,255]
        +---------------+---+

  See also: CGifColorTable
 */
struct CGifColor
{
  CGifColor();
  CGifColor(uint8 cRed, uint8 cGreen, uint8 cBlue);
  static const int GetLength();
  operator uint32();

   //Turn byte alignment on
//  #pragma pack(push, 1)
 #pragma pack(1)
  uint8 m_cRed;   //intensity of red color [0,255]
  uint8 m_cGreen; //intensity of green color [0,255]
  uint8 m_cBlue;  //intensity of blue color [0,255]

  //Turn byte alignment off
//  #pragma pack(pop)
  #pragma pack()
};

/*Converts color triplets to 32-bit unsigned integer.

  For machines with Little Endian byte order, colors
  are packed at following way:

        3   2   1   0
      +---+---+---+---+
      | 0 | R | G | B |
      +---+---+---+---+

 */
inline CGifColor::operator uint32()
{
return ( ( m_cBlue | ((uint16)(m_cGreen)<< 8) ) |
                    (((uint32) m_cRed)  <<16) );
}

#ifdef _DEBUG
    char* Dump(const CGifColor& gifColor, char* szOutput);
#endif

///////////////////////////////////////////////////////////////////////////////
/*CGifColorTable class contains a color palette used to render raster-based
 graphics. A color table can have one of two different scopes: global or local.
 Each color is represented with three bytes giving red, green and  blue color
 intensity. Each image pixel value received will be displayed according to its
 closest match with an available color of the display based on this color table.
 In the cases of creating GIF images from hardware without color palette
 capability, a fixed palette should be created based on the available display
 colors for that hardware.


  Gif Color Table format:

          bytes
          0   1   2  colors
        +-----------+---+
        | R | G | B | 0 |  intensity of red, green and blue color (3 bytes)
        +-----------+   +
        | R | G | B | 1 |
        +-----------+   +
        | R | G | B | 2 |
        +-----------+   +
         ...
        +-----------+   +
        | R | G | B |n-1| table size is 3 * (n + 1) bytes, where n is a
        +-----------+   + color index in range [0,255];
        | R | G | B | n | number of colors (table elements) is in range [1,256]
        +-----------+---+

  See also: CGifColor, CGifLogicalScreenDescriptor::GetGlobalColorTableSize()

  Note: color tables are optional, making it possible for a Data Stream to
  contain numerous graphics without a color table at all. In that case, the
  decoder may use a color table with as many colors as its hardware is able
  to support; it is recommended that such a table have black and white as
  its first two entries, so that monochrome images can be rendered adequately.
 */
class CGifColorTable
{
public:
  CGifColorTable();
  CGifColorTable(const uint8* pTableData, const unsigned int nTableSize);
  virtual ~CGifColorTable();
  CGifColor& operator[](unsigned int nIndex);
  CGifColor operator[](unsigned int nIndex) const;
  unsigned int GetSize() const;
  const int GetColorDepth() const;
  bool SetSize(const unsigned int nNewSize);
  void RemoveAll();
  bool Copy(const uint8* pTableData, const unsigned int nTableSize);
  CGifColorTable& operator=(const CGifColorTable& gifSource);
  #ifdef _DEBUG
    virtual void Dump() const;
  #endif
  const int GetLength() const;

private:
  CGifColor* m_pTable;  //table with colors used by an image
  unsigned int m_nSize; //number of colors [0,256]
  const unsigned int MAX_SIZE; //maximum number of colors supported by
                               //Graphics Interchange Format
};

///////////////////////////////////////////////////////////////////////////////
/*The GIF Logical Screen Descriptor describes the overall parameters for all
  GIF images following. It defines the overall dimensions of the image space
  or logical screen required, the existence of color mapping information,
  background screen color, and color depth information.

         bits
         7 6 5 4 3 2 1 0 Bytes
        +---------------+---+
        |               | 0 |
        +-Screen Width -+   + Raster width in pixels (LSB first)
        |               | 1 |
        +---------------+   +
        |               | 2 |
        +-Screen Height-+   + Raster height in pixels (LSB first)
        |               | 3 |
        +-+-----+-+-----+   + g = 1, global color table follows Descriptor
        |g| rrr |s| nnn | 4 | rrr + 1 = primary color resolution [bits/color]
        +-+-----+-+-----+   + s = 1, global color table is sorted (89a)
        |   background  | 5 | nnn + 1 = bits/pixel in image
        +---------------+   + background=Color index of screen background
        |aspect ratio f | 6 | Pixel Aspect Ratio factor(89a) or 0 (87a)
        +---------------+---+
        +-------------------+
        |Global Color Table | optional field that follows Descriptor if g = 1
        +-------------------+

  The logical screen width and height can both be larger than the physical
  display. How images larger than the physical display are handled is
  implementation dependent.
  If no Global Color Table is indicated, a default color table should be
  generated  internally. The generated table will map each possible incoming
  color index to the same hardware color index modulo n where n is the number
  of available hardware colors.

  Note: The scope of this block is the entire data stream. This block cannot
  be modified by any extension. Logical Screen Descriptor data segment is
  required and only one must be present per data stream.
 */
class CGifLogicalScreenDescriptor
{
public:
  CGifLogicalScreenDescriptor();
  CGifLogicalScreenDescriptor(const uint8* pData);
  CGifLogicalScreenDescriptor(const CGifLogicalScreenDescriptor& gifSource);
  virtual ~CGifLogicalScreenDescriptor();
  #ifdef _DEBUG
    virtual void Dump() const;
    virtual char* Dump(char* szOutput) const;
  #endif
  bool Copy(const uint8* pData);
  const unsigned int GetLength() const;
  bool HasColorTable() const;
  unsigned int  GetColorResolution() const;
  bool IsColorTableSorted() const;
  unsigned int  GetColorTableSize() const;
  double GetPixelAspectRatio() const;
  unsigned int GetBkColorIndex() const;
  void GetScreenSize(unsigned int& nWidth, unsigned int& nHeight) const;
  CGifColorTable GetColorTable() const;
  CGifColorTable& GetColorTable();
  CGifLogicalScreenDescriptor& operator=(
                 const CGifLogicalScreenDescriptor& gifSource);

private:
   //Turn byte alignment on
  // #pragma pack(push, 1)
#pragma pack(1)
  unsigned short m_wWidth;       //logical screen width
  unsigned short m_wHeight;      //logical screen height
  unsigned char  m_cControlFlags;//data block control flags
  unsigned char  m_cBkColorIndex;//background color index
  unsigned char  m_cAspectRatio; //pixel aspect ratio
  //Turn byte alignment off
  // #pragma pack(pop)
#pragma pack()

  CGifColorTable m_gifGlobalColorTable; //optional global color palette
};

///////////////////////////////////////////////////////////////////////////////
/*CGifHeader class identifies GIF ( Graphics Interchange Format(c) ) data stream
  and general display device parameters. Exactly one header must be present per
  data stream. The scope of this block is the entire data stream. This block
  cannot be modified by any format extension. This data container is compliant
  with format versions 87a and 89a.

  - The GIF Signature identifies the data following as a valid GIF image stream.
  The Signature field marks the beginning of the data stream and contains the
  fixed value 'GIF'.
  - The version number in the header of a data stream identifies the minimum set
  of capabilities required of a decoder. Version numbers are ordered numerically
  increasing on the first two number characters starting with 87 [87,...99) and
  alphabetically increasing on the third character [a,z]. An encoder should use
  the earliest possible version number that includes all the blocks used in the
  data stream. The unnecessary use of later version numbers will hinder processing
  by some decoders. Most decoders are compliant with versions '87a' (May 1987)
  and '89a' (July 1989).


  GIF header file format:

        +-------------------+
        |   GIF Signature   | required field (3 bytes) 'GIF'
        +-------------------+
        |      Version      | required field (3 bytes) '87a' or '89a'
        +-------------------+
        | Screen Descriptor | required field (7 bytes)
        +-------------------+
        +-------------------+
        |Global Color Table | optional field that follows Descriptor
        +-------------------+

  Note: The scope of this block is the entire data stream. This block cannot
  be modified by any extension. The Header data segment is required and only
  one must be present per data stream.
 */
class CGifHeader
{
public:
  CGifHeader();
  CGifHeader(uint8* pData);
  CGifHeader(const CGifHeader& gifSource);
  virtual ~CGifHeader();
  #ifdef _DEBUG
    virtual void Dump() const;
    virtual char* Dump(char* szOutput) const;
  #endif
  bool IsValid() const;
  bool IsValid(const uint8* pData) const;
  const unsigned int GetLength() const;
  unsigned int GetBlockLength() const;
  CGifLogicalScreenDescriptor& GetLogicalScreenDescriptor();
  CGifLogicalScreenDescriptor GetLogicalScreenDescriptor() const;
  bool Copy(const uint8* pData);

private:
    //Turn byte alignment on
  // #pragma pack(push, 1)
#pragma pack(1)
  char m_cSignature[3]; //data stream signature identifying valid GIF format
  char m_cVersion[3];   //version number indefies the minimum set of capabilities
                        //required of a decoder in order to fully process
                        //data stream
  CGifLogicalScreenDescriptor m_gifScreenDescriptor; //logical screen descriptor
    //Turn byte alignment off
  // #pragma pack(pop)
#pragma pack()

public:
};

///////////////////////////////////////////////////////////////////////////////
/*This class encapsulates images in Graphics Interchange Format(c) (GIF) devised
  initially for transmitting graphical images over phone lines via modems.
  Size of an image file is reduced by the Lempel-Ziv Welch (LZW) algorithm,
  derived from Huffman Coding compression. LZW algorithm is modified to acomodate
  image scan line packets.
  GIF format supports up to 256 (8-bit) colors per color palette and it is most
  suitable for images with few distinctive colors (e.g., graphics drawing).
  This data container is compliant with image formats versions 87a and 89a.

  A GIF data stream is a sequence of data blocks and sub-blocks representing
  a collection of graphics. Each block contains variuos parameters and data
  relevant in reproduction of an image.

  In order to provide a synchronization for the termination of a GIF image file,
  a GIF decoder will process the end of GIF mode when the GIF Terminator is found
  after an image has been processed.

  General file format:

        +-------------------+ <--+
        |   GIF Signature   |    |
        +-------------------+    |
        |      Version      |    |- Header (13 bytes)
        +-------------------+    |  required fields
        | Screen Descriptor |    |
        +-------------------+ <--+
        | Global Color Table|       optional field
        +-------------------+
        .                   .
        +-------------------+
        |  Extension Block  |       optional field
        +-------------------+ <--+
        |  Image Descriptor |    |
        +-------------------+    |
        | Local Color Table |    |- Repeated 1 to n times
        +-------------------+    |
        |    Raster Data    |    |
        +-------------------+ <--+
        .                   .
        +-------------------+
        |  Extension Block  |       optional field
        +-------------------+
        |   GIF Terminator  |  required field [0x3B (';')] (1 byte)
        +-------------------+


  {html:<br><img src="Images/diagGIFFormat.gif" border="0"
             alt="Graphics Interchange Format">}
  See also: GIF Graphics Interchange Format version
            {html: <a href="Documentation/gif87a.htm">87a </a>,
                   <a href="Documentation/gif89a.htm">89a</a>}.

  Note: default byte order of multi-byte numeric fields is 'Little Endian'
  (the Least Significant Byte (LSB) first).
 */
class CGif
{
public:
  CGif();
  CGif(uint8* pData);
  CGif(const uint8* pData);
  CGif(const CGif& gifSource);
  virtual ~CGif();

  bool IsValid() const;
  bool IsValid(const uint8* pData) const;
  bool GetSize(const uint8* pData,
               unsigned int& nWidth,
               unsigned int& nHeight) const;
  bool GetSize(unsigned int& nWidth,
               unsigned int& nHeight) const;
  bool HasGlobalColorTable();
  CGifHeader GetHeader() const;
  CGifHeader& GetHeader();
  CGifColorTable&GetGlobalColorTable();
  bool Copy(const uint8* pData);
  #ifdef _DEBUG
    virtual void Dump();
  #endif

private:
  #pragma pack(1)   //turn byte alignment on

  CGifHeader  m_gifHeader; //GIF data stream header identifies format and general
                           //display device parameters

  #pragma pack() // turn byte alignment off

};

///////////////////////////////////////////////////////////////////////////////
#endif //_KGIF_H_

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
 *  17   Biblioteka1.16        2003-09-30 11:00:28  Darko           Replaced DWORD,
 *       WORD with uint32, uint16
 *  16   Biblioteka1.15        2002-10-10 20:30:31  Darko Kolakovic Replaced push
 *       and pack pragmas
 *  15   Biblioteka1.14        2002-08-02 22:26:40  Darko Kolakovic
 *  14   Biblioteka1.13        2002-08-02 00:35:57  Darko           CopyAll()
 *       sub-blocks
 *  13   Biblioteka1.12        2002-08-01 17:47:33  Darko Kolakovic delete virtual
 *       CGifBlock:GetLength()
 *  12   Biblioteka1.11        2002-08-01 14:58:32  Darko Kolakovic
 *  11   Biblioteka1.10        2002-08-01 01:23:52  Darko           CGifImageData
 *  10   Biblioteka1.9         2002-07-31 17:30:12  Darko Kolakovic
 *       SeekImageDescriptor inserted
 *  9    Biblioteka1.8         2002-07-31 04:44:00  Darko           Read block
 *       sizes from a stream
 *  8    Biblioteka1.7         2002-07-30 17:12:26  Darko Kolakovic
 *       CGifImageDescriptor
 *  7    Biblioteka1.6         2002-07-29 14:09:42  Darko Kolakovic
 *       CGifLabel::IsValid() added
 *  6    Biblioteka1.5         2002-07-29 00:45:24  Darko           Added Gif Data
 *       Sub-block
 *  5    Biblioteka1.4         2002-07-17 19:30:07  Darko Kolakovic Added
 *       CGifExtension
 *  4    Biblioteka1.3         2002-07-16 20:53:38  Darko Kolakovic Added
 *       CGifHeader::Copy()
 *  3    Biblioteka1.2         2002-07-16 01:43:29  Darko           Added operator
 *       =()
 *  2    Biblioteka1.1         2002-07-15 19:45:09  Darko           Color Table
 *       added
 *  1    Biblioteka1.0         2002-07-12 18:17:15  Darko Kolakovic
 * $
 * 2001 Initial version in Babylon Lib
 * 1990 v.89a enhanced GIF CompuServe Incorporated
 * 1987 v.87a Graphics Interchange Format (GIF) devised by the UNISYS Corp. and
 *  Compuserve
 *****************************************************************************/
