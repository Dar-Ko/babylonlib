/*$Workfile: KBitmap.h$: header file
  $Revision: 4$ $Date: 2005-05-24 11:33:19$
  $Author: Darko Kolakovic$

  Bitmap data structures, Microsoft DIB Format
 */

/* Group=Images                                                              */


#ifndef _BITMAPSTRUCT_H_
  #define _BITMAPSTRUCT_H_

#define HANDLE_PRAGMA_PACK_PUSH_POP //gcc 2.96.3

#include "KTypedef.h" //BYTE

#pragma pack(1)

/* ///////////////////////////////////////////////////////////////////////// */
/*Microsoft - GDI procedure declarations, constant definitions and macros    */
#ifndef _WINGDI_ /* wingdi.h sentry */
/*BITMAPFILEHEADER defines a single bitmap image.  Its analogue in the
  Windows SDK is the BITMAPFILEHEADER. Its analogues in the OS/2 Toolkit are
  the BITMAPFILEHEADER and BITMAPFILEHEADER2 structures.

  A BITMAPHEADER structure is always concatenated to the end of a
  BITMAPFILEHEADER structure.
 */
typedef struct tagBITMAPFILEHEADER
{
  WORD  bfType;       /*Specifies the type of file. This member must
                             be BM. */
  DWORD bfSize;       /*Specifies the size of the file, in bytes. */
  WORD  bfReserved1;  /*Reserved; must be set to zero. */
  WORD  bfReserved2;  /*Reserved; must be set to zero. */
  DWORD bfOffBits;    /*Specifies the byte offset from the
                        BITMAPFILEHEADER structureto the actual bitmap
                        data in the file. */

} BITMAPFILEHEADER;

/*BITMAPHEADER defines the properties of a bitmap.  Its analogues in the
  Windows SDK are the BITMAPCOREINFOHEADER and BITMAPINFOHEADER structures.
  Its analogues in the OS/2 Toolkit are the BITMAPINFOHEADER and
  BITMAPINFOHEADER2 structures.

  A color table is concatenated to this structure.  The number of elements in
  the color table determined by the bit-depth of the image.

  Note, that if the field "size" is 12 or less, then the width and height
  fields should be read as UINT16's instead of UINT32's.

  Also note that if the field "size" is greater than 12, then the color table
  will have an extra byte of padding between each structures (to longword
  align it)

  The different sizes for the width, height, and color table are the only
  differences between the "old" and "new" bitmap file formats.
 */
typedef struct tagBITMAPINFOHEADER
{
  DWORD biSize;          /*Specifies the number of bytes required by the
                           BITMAPINFOHEADER structure. */
  DWORD biWidth;         /*Specifies the pixel width of the bitmap. */
  DWORD biHeight;        /*Specifies the pixel height of the bitmap. */

  WORD  biPlanes;        /*Specifies the number of planes for the target
                           device. This member must be set to 1. */

  WORD  biBitCount;      /*Specifies the color depth in number of bits per pixel.
                           This value must be 1, 4, 8, or 24 corresponding to
                           2, 16, 256 or 16.7 million colors*/

  DWORD biCompression;   /*Specifies the type of compression for a
                           compressed bitmap. */

  DWORD biSizeImage;     /*Specifies the size, in bytes, of the image.
                           It is valid to set this member to zero if the
                           bitmap is in the BI_RGB format. */

  DWORD biXPelsPerMeter; /*Specifies the horizontal resolution, in pixels
                           per meter, of the target device for the bitmap.
                           An application can use this value to select
                           a bitmap from a resource group that best
                           matches the characteristics of the current
                           device. */

  DWORD biYPelsPerMeter; /*Specifies the vertical resolution, in pixels
                           per meter, of the target device for the
                           bitmap. */

  DWORD biClrUsed;       /*Specifies the number of color indexes in the
                           color table actually used by the bitmap. If
                           this value is zero, the bitmap uses the
                           maximum number of colors corresponding to the
                           value of the biBitCount member. */

  DWORD biClrImportant;  /*Specifies the number of color indexes that
                           are considered important for displaying the
                           bitmap. If this value is zero, all colors
                           are important. */

} BITMAPINFOHEADER;


/*The RGBQUAD structure describes a color consisting of relative intensities
  of red, green, and blue.
  The bmiColors member of the BITMAPINFO structure consists of an array
  of RGBQUAD structures.

 */
typedef struct tagRGBQUAD
  {
  BYTE    rgbBlue;   /*Specifies the intensity of blue in the color.*/
  BYTE    rgbGreen;  /*Specifies the intensity of green in the color. */
  BYTE    rgbRed;    /*Specifies the intensity of red in the color. */
  BYTE    rgbReserved; /*Reserved; must be zero.*/
  } RGBQUAD;

/* ///////////////////////////////////////////////////////////////////////// */
#endif /*_WINGDI_*/

/* ///////////////////////////////////////////////////////////////////////// */
/*Windows bitmap files are stored in a device-independent bitmap (DIB) format
  that allows Windows to display the bitmap on any type of display device.
  The term "device independent" means that the bitmap specifies pixel color in a
  form independent of the method used by a display to represent color.

  General file format:

     +------------------+
     | BITMAPFILEHEADER | Header (14 bytes)
     +------------------+
     | BITMAPINFOHEADER | image parameters (40 bytes)
     +------------------+
     |     RGBQUAD[]    | Palette (RGB quad) (n bytes) optional field
     +------------------+
     |       BYTE[]     | image data (m bytes)
     +------------------+


 */

typedef struct tagDIBITMAP
{
  BITMAPFILEHEADER m_bmpHeader;
  BITMAPINFOHEADER m_bmpDescriptor;
  RGBQUAD*         m_bmpColorTable;
  BYTE*            m_bmpImage;
} DIBITMAP;

/*BITMAPARRAYHEADER is used to establish a linked list of BITMAPFILEHEADER
  structures for a bitmap file with multiple images in it.  There is no
  equivalent structure in the Windows SDK.  Its analogues in the OS/2 toolkit
  are the BITMAPARRAYFILEHEADER and BITMAPARRAYFILEHEADER2 structures.

  A BITMAPFILEHEADER structure is always concatenated to the end of a
  BITMAPARRAYHEADER structure.
 */
typedef struct BITMAPARRAYHEADER
{
    uint16    type;
    uint32    size;
    uint32    next;
    uint16    screenWidth;
    uint16    screenHeight;
} BITMAPARRAYHEADER;


#pragma pack()

/* ///////////////////////////////////////////////////////////////////////// */
#endif //_BITMAPSTRUCT_H_

/*****************************************************************************
 * $Log:
 *  3    Biblioteka1.2         2002-08-19 10:45:08  Darko Kolakovic
 *  2    Biblioteka1.1         2002-08-05 11:33:33  Darko           Fixed bug in
 *       SeekImagePos
 *  1    Biblioteka1.0         2002-08-02 22:24:59  Darko Kolakovic
 * $
 * Revision 1.1  2002/07/26 23:40:56  dkolaCVS
 * Created
 *
 *****************************************************************************/
