/*$Workfile: KGif.cpp$: implementation file
  $Revision: 18$ $Date: 2003-11-03 12:10:06$
  $Author: Darko$
  
  Encapsulation of images in Graphics Interchange Format(c) GIF v89a.
  GIF and 'Graphics Interchange Format' are trademarks of CompuServe, Incorporated.
 */ 

/* Group=Images                                                              */

#include <memory.h> //memcpy()
#include <string.h> //strlen()
#include "KGif.h"  //CGif class
#include "KProgCst.h" //SWAP_WORD_ENDIAN macro

#ifndef __AFX_H__ /*MFC and TRACE macros are not included */
  #include "KTrace.h" //Trace macro
#endif

#ifndef __KPROGCST_H__
  #define _ENDIAN_LITTLE_ 0x1234
    /*Byte order, according to significance of bytes                         */
  #define _ENDIAN_ORDER_ _ENDIAN_LITTLE_
   /*Swaps tailing bytes with bytes from the beginning of the two-bytes uint16  */
  #define SWAP_WORD_ENDIAN(w)  (uint16) ((uint16) ((w)<<8)|((w)>>8))
#endif

#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

#if _MSC_VER >= 1300
   //Microsoft Visual Studio C++ v7.0
   //Disable warning C4127: conditional expression is constant
  #pragma warning(disable: 4127)
#endif

///////////////////////////////////////////////////////////////////////////////
// CGifLabel
CGifLabel::CGifLabel()
{
}

char* CGifLabel::m_szSignature = "GIF";
char* CGifLabel::m_szFileExt   = "gif";
char* CGifLabel::m_szVersion[2] = {"87a","89a"};

/*Returns true if data stream begins with valid tag and version number, 
  otherwise returns false.
 */
bool CGifLabel::IsValid(const uint8* pData //an encoded image in 
                                     //Graphics Interchange Format (GIF)
                       )
{
TRACE1("CGifLabel::IsValid(pData @ %p)\n", pData);
const int SIGNATURE_SIZE = 3; //field is 3 bytes long
const int VERSION_SIZE = 3;   //field is 3 bytes long
if(memcmp(pData, CGifLabel::m_szSignature, SIGNATURE_SIZE) == 0)
  {
  const unsigned char* pVersion = (unsigned char*)&pData[SIGNATURE_SIZE];
  if( (memcmp(pVersion, CGifLabel::m_szVersion[1],VERSION_SIZE) == 0) ||
    (memcmp(pVersion, CGifLabel::m_szVersion[0],VERSION_SIZE) == 0) )
    return true;
  }
return false;
}

///////////////////////////////////////////////////////////////////////////////
// CGifDataSubblock
//::CGifDataSubblock()---------------------------------------------------------
/*
 */
CGifDataSubblock::CGifDataSubblock() :
  m_nSize(0),
  m_pData(NULL)
{
}

//::~CGifDataSubblock()--------------------------------------------------------
/*
 */
CGifDataSubblock::~CGifDataSubblock()
{
if ( m_pData != NULL)
  delete[] m_pData;
}

//::Copy()---------------------------------------------------------------------
/*
 */
uint8* CGifDataSubblock::Copy(const uint8* pDataSubblock //[in] if NULL, the current
                             //data will be erased and size of the container set 
                             //to null.
                             )
{
TRACE2("CGifDataSubblock::Copy(from 0x%p %d bytes)\n", 
       pDataSubblock, 
       pDataSubblock[0]);
  //If data subblock is not initalized or if it is zero-size block
  //clear this container
if ( (pDataSubblock == NULL) || (pDataSubblock[0] == 0) )
  RemoveAll();
else //Create data container
  {
  if (SetSize(pDataSubblock[0])) //First byte in the stream is data length
    {
      //Copy usefull data
    unsigned int i = 0;
      //Note: if buffer size is sufficient to hold new data, we will just copy
      //data into it. That is faster, but we will have waste of memory.
      //All memory will be freed in the destructor D.K.
    const uint8* pData = &pDataSubblock[1];
    while ( i < m_nSize )
      {
      m_pData[i] = pData[i];
      i++;
      }
    }
  }

return m_pData; //Return data subblock container
}

//::RemoveAll()----------------------------------------------------------------
/*Removes all the data from this container. 
 */
void CGifDataSubblock::RemoveAll()
{
if ( m_pData != NULL)
  {
  delete[] m_pData;
  m_nSize = 0;
  }
}

//::GetAllSubblockLength()-----------------------------------------------------
/*Obtains total size of all sequential data sub-blocks. Total size includes sizes
  of Sub-block headers reserved for block's size information.

     +- +------------------+
   T |  |   block size i   |  i number of bytes in the data sub-block [0,255]
   o |  +------------------+
   t |  |    block data    |  Data Values (i bytes)
   a |  +------------------+
   l |  |   block size j   |  j number of bytes in the data sub-block [0,255]
     |  +------------------+
   s |  |    block data    |  Data Values (j bytes)
   i |  +------------------+
   z |  |   block size k   |  k number of bytes in the data sub-block [0,255]
   e |  +------------------+
     |  |    block data    |  Data Values (k bytes)
     |  +------------------+
     |  ...
     +- +------------------+
        | Block Terminator |
        +------------------+

  Note: a chain of data sub-blocks ends with zero-sized sub-block called 
  Block Terminator. Size of Block Terminator is not included in the sum returned
  by this method.

  Returns: the total size of all consecutive data sub-blocks or -1 if Block 
  Terminator could not be found.
 */
int CGifDataSubblock::GetAllSubblockLength(uint8* pSubblockData //[in]
                                           //int iCount //= -1 number of bytes in
        //pSubblockData to consider. If iCount is -1, methods sums

                                           )
{
unsigned int nBlockCount = 0;
int iRes = CGifDataSubblock::GetAllDataLength(pSubblockData, nBlockCount);
if ( iRes >= 0 ) //Include sub-block's headers in total size
  iRes += nBlockCount;
return iRes;
}

//::GetAllDataLength()---------------------------------------------------------
/*
 if nBlockCount is zero, pSubblockData point to Block Terminator
 */
int CGifDataSubblock::GetAllDataLength(uint8* pSubblockData, //[in]
                                           //int iCount //= -1 number of bytes in
        //pSubblockData to consider. If iCount is -1, methods sums
                                       unsigned int& nBlockCount //[out] number
                                       //of sub-blocks encountered
                                           )
{
if (pSubblockData == NULL)
  return -1;

int iRes = 0;
nBlockCount = 0;
const unsigned int BLOCKTERMINATOR = GIF_BLOCKTERMINATOR;
unsigned int nBlockSize = pSubblockData[0];

while(nBlockSize != BLOCKTERMINATOR)
  {
  iRes += nBlockSize;
     //First byte in data sub-block contains size of a sub-block
  nBlockCount += sizeof(uint8);
  nBlockSize = pSubblockData[iRes + nBlockCount];

  if (iRes > 0x100000) //TODO: error checking
    {
    iRes = -1;
    break;
    }
  }
return iRes;
}

//::GetBuffer()----------------------------------------------------------------
/*Obtains a pointer to the internal buffer for the CGifDataSubblock object. 
  The returned uint8* is not const and thus allows direct modification of 
  CGifDataSubblock contents. If size of the buffer is to be changed, m_nSize
  have to be updated accordingly.

  Returns: pointer object's internal data container. It could be NULL if
  object is not initalized.
 */
uint8* CGifDataSubblock::GetBuffer()
{
return m_pData;
}

//::GetSize()------------------------------------------------------------------
/*Returns the size of the data container.
 */
int CGifDataSubblock::GetSize() const
{
return m_nSize;
}

//::SetSize()------------------------------------------------------------------
/*Establishes the size of an empty or existing data container and allocates 
  memory if necessary. 

  Returns: true if successful, otherwise returns false.
 */
bool CGifDataSubblock::SetSize(const unsigned int nNewSize //[in] new data container 
                                                           //size.
                               )
{
if (nNewSize == 0)
  RemoveAll();
else //Create data container
  {
  if (nNewSize > m_nSize)          //Reallocate the container
    {
    if ( m_pData != NULL)
      delete[] m_pData;
    m_pData = new uint8[nNewSize];
    if (m_pData == NULL)
      {
      m_nSize = 0;
      return false;
      }
    }
  m_nSize = nNewSize;
  }
return true;
}

//::CopyAll()------------------------------------------------------------------
/*Copies all consecutive Data Sub-blocks until Block Terminator have not been 
  reached.
  This method assumes that all data are stored in a single continuous block
  in memory.

            +----------------+
            | Data Sub-block | data (1 byte + 255 bytes of data maximum)
            +----------------+
            | Data Sub-block |
            +----------------+
            | Data Sub-block |
            +----------------+
            | Data Sub-block |
            ...
            | Data Sub-block |
            +----------------+
            |Block Terminator| 0x00 sequence end (1 byte)
            +----------------+

  Returns: true if successful, or false if failed.
 */
bool CGifDataSubblock::CopyAll(uint8* pSubblockData //[in] begining of data 
                                                   //sub-blocks
          )
{
TRACE1("CGifDataSubblock::CopyAll(from 0x%p)\n", pSubblockData);
if (pSubblockData == NULL)
  return false; //Invalid parameter

unsigned int nDummy;
int iSize = 
    CGifDataSubblock::GetAllDataLength(pSubblockData, nDummy);
if( iSize < 0)
  return false; //Data are corrupted

if (SetSize(iSize))
  {
  iSize = pSubblockData[0];
  int i = 1; //First byte is reserved for block length
  int j = 0;
  while ( iSize > GIF_BLOCKTERMINATOR )
    {
          //Copy data
    memcpy(&m_pData[j], &pSubblockData[i], iSize);
    j += iSize;
    i += iSize;
    iSize = pSubblockData[i];
    i++; //First byte in new sub-block is reserved
    }
  }

return true;
}

//::operator[]()---------------------------------------------------------------
/*
  Note: Passing a negative value or a value greater or equal than the value 
  returned by GetSize() will return an undefined result.
 */
uint8& CGifDataSubblock::operator[](int iIndex)
{
if ( m_nSize > (unsigned int) iIndex )
  return m_pData[iIndex];
return m_pData[0]; //Failure: throw an exception
}

uint8  CGifDataSubblock::operator[](int iIndex) const
{
if ( m_nSize > (unsigned int) iIndex )
  return m_pData[iIndex];
return 0x00;
}

///////////////////////////////////////////////////////////////////////////////
// CGifBlock
#include "KGifImageDescriptor.h"  //CGifImageDescriptor class

//::CGifBlock()----------------------------------------------------------------
/*
 */
CGifBlock::CGifBlock(const TYPE iBlockType)
{
switch (iBlockType)
  {
  case GIF_EXTENSION:    m_cLabel = 0x21; break;
  case IMAGE_DESCRIPTOR: m_cLabel = 0x2C; break;
  case TRAILER:          m_cLabel = 0x3B; break;
  default:               m_cLabel = 0x00; //failure
  }
}

//::GetType()------------------------------------------------------------------
/*
 */
CGifBlock::TYPE CGifBlock::GetType(uint8& cData)
{
switch(cData)
  {
  case GIF_EXTENSION_INTRODUCER: return GIF_EXTENSION   ;
  case GIF_IMAGE_SEPARATOR     : return IMAGE_DESCRIPTOR;
  case GIF_TERMINATOR          : return TRAILER         ;
  }
return UNKNOWN;
}

//::GetLength()------------------------------------------------------------------
/*Obtains length of the fixed portion of the block.

  Returns: size of the GIF header in bytes.
 */
const unsigned int CGifBlock::GetLength() const
{
return (sizeof(m_cLabel));
}

//::GetBlockLength()-----------------------------------------------------------
/*Obtains length of one of following GIF data blocks: GIF Extension, Image
  Descriptor or Trailer block. The length includes block's fixed size portion,
  sizes of any subsequent data sub-blocks and the size of associated color table
  if any.

  Returns: size of a labeled Gif block in bytes. Returns 0 if a block is not
  recognized.
 */
unsigned int CGifBlock::GetBlockLength(uint8* pBlockData //begining of labeled Gif data block
                         )
{
if (pBlockData == NULL)
  return 0;

int iResult;
  //Employ  Block Factory
switch (CGifBlock::GetType(pBlockData[0]))
  {
  case GIF_EXTENSION:
    {
    iResult = CGifExtension::GetBlockLength(pBlockData);
    }
    break;
  case IMAGE_DESCRIPTOR:
    {
    iResult = CGifImageDescriptor::GetBlockLength(pBlockData);
    }
    break;
  case TRAILER:
    {
    iResult = sizeof(GIF_TERMINATOR); //Length is 1 byte
    }
    break;
  default: iResult = 0; //Failure
  }
return iResult;
}

///////////////////////////////////////////////////////////////////////////////
// CGifExtension
//::CGifExtension()------------------------------------------------------------
/*
 */
CGifExtension::CGifExtension(const FUNCTION iBlockType) :
  CGifBlock(CGifBlock::GIF_EXTENSION)
{
switch (iBlockType)
  {
  case PLAIN_TEXT     : m_cLabel = GIF_EXT_PLAIN_TEXT     ; break;
  case GRAPHIC_CONTROL: m_cLabel = GIF_EXT_GRAPHIC_CONTROL; break;
  case COMMENT        : m_cLabel = GIF_EXT_COMMENT        ; break;
  case APPLICATION    : m_cLabel = GIF_EXT_APPLICATION    ; break;
  }
}

//::GetType()------------------------------------------------------------------
/*
 */
CGifExtension::FUNCTION CGifExtension::GetType(uint8& cData)
{
switch(cData)
  {
  case GIF_EXT_PLAIN_TEXT     : return PLAIN_TEXT     ;
  case GIF_EXT_GRAPHIC_CONTROL: return GRAPHIC_CONTROL;
  case GIF_EXT_COMMENT        : return COMMENT        ;
  case GIF_EXT_APPLICATION    : return APPLICATION    ;
  }
return UNKNOWN;
}

//::GetBlockLength()-----------------------------------------------------------
/*Obtains length of one of following GIF Extension data blocks: Plain Text 
  Extension, Graphic Control Extension, Comment Extension or Application 
  Extension. The length includes block's fixed size portion,
  sizes of any subsequent data sub-blocks.

  Returns: size of a Gif Extension block in bytes. Returns 0 if a block is not
  recognized.
 */
unsigned int CGifExtension::GetBlockLength(uint8* pBlockData //begining of Gif Extension
                                           //data block
                                          )
{
if (pBlockData == NULL)
  return 0;

int iResult;
  //Employ GIF Extension Block Factory
switch (CGifExtension::GetType(pBlockData[sizeof(GIF_EXTENSION_INTRODUCER)]))
  {
  case PLAIN_TEXT:
    {
    iResult = CGifPlainTextExt::GetBlockLength(pBlockData);
    }
    break;
  case GRAPHIC_CONTROL:
    {
    iResult = CGifGraphicControlExt::GetBlockLength(pBlockData);
    }
    break;
  case COMMENT:
    {
    iResult = CGifCommentExt::GetBlockLength(pBlockData);
    }
    break;
  case APPLICATION:
    {
    iResult = CGifApplicationExt::GetBlockLength(pBlockData);
    }
    break;
  default: iResult = 0; //Failure
  }
return iResult;
}

///////////////////////////////////////////////////////////////////////////////
// CGifPlainTextExt
//::CGifPlainTextExt()---------------------------------------------------------
/*
 */
CGifPlainTextExt::CGifPlainTextExt() :
  CGifExtension(CGifExtension::PLAIN_TEXT),
  m_cSize(0),       
  m_wGridLeftPos(0),
  m_wGridTopPos(0), 
  m_wGridWidth(0),  
  m_wGridHeight(0), 
  m_cCellWidth(0),  
  m_cCellHeight(0), 
  m_cFgColor(0),    
  m_cBkColor(0) 
{
}

//::~CGifPlainTextExt()--------------------------------------------------------
/*
 */
CGifPlainTextExt::~CGifPlainTextExt()
{
}

//::GetLength()------------------------------------------------------------------
/*Obtains length of the fixed part of the data block. Data sub-blocks are 
  following this part of the data block. 
  
  Note: Block terminator is treated as zero-sized data sub-block and it is not 
  included in the length returned by this method.

  Returns size of the header section of the extension block in bytes.
 */
const unsigned int CGifPlainTextExt::GetLength()
{
return (sizeof(GIF_EXTENSION_INTRODUCER) + 
        sizeof(GIF_EXT_PLAIN_TEXT)      + 
        sizeof(uint8) +
        sizeof(uint16) * 4 +
        sizeof(uint8) * 4 
        //Here goes variabile application data
        );
}

//::GetBlockLength()-----------------------------------------------------------
/*Obtains block's length including length of optional data sub-blocks and Block
  Terminator size.

  Returns: sum of sizes of the header and data sub-blocks in bytes.
 */
unsigned int CGifPlainTextExt::GetBlockLength(uint8* pBlockData //[in]
                                                 )
{
if (pBlockData[sizeof(GIF_EXTENSION_INTRODUCER)] == GIF_EXT_PLAIN_TEXT) 
  {
  unsigned nRes = GetLength(); //Get size of block's header
  int iSize = CGifDataSubblock::GetAllSubblockLength( &pBlockData[nRes] );
  if (iSize >= 0)
    {
    nRes +=  iSize + sizeof(GIF_BLOCKTERMINATOR);
    return nRes;
    }
  }

ASSERT(FALSE);
return 0;
}

///////////////////////////////////////////////////////////////////////////////
// CGifGraphicControlExt
//::CGifGraphicControlExt()----------------------------------------------------
/*
 */
CGifGraphicControlExt::CGifGraphicControlExt() :
  CGifExtension(CGifExtension::GRAPHIC_CONTROL), 
  m_cSize(0),
  m_cControlFlags(0),   
  m_wDelayTime(0),     
  m_cTransparentColor(0)
{
}

//::~CGifGraphicControlExt()---------------------------------------------------
/*
 */
CGifGraphicControlExt::~CGifGraphicControlExt()
{
}

//::GetLength()------------------------------------------------------------------
/*Obtains length of the fixed part of the data block. Data sub-blocks are 
  following this part of the data block. 
  
  Note: Block terminator is treated as zero-sized data sub-block and it is not 
  included in the length returned by this method.

  Returns size of the header section of the extension block in bytes.
 */
const unsigned int CGifGraphicControlExt::GetLength()
{
return (sizeof(GIF_EXTENSION_INTRODUCER) + 
        sizeof(GIF_EXT_GRAPHIC_CONTROL)      + 
        sizeof(uint8) +
        sizeof(uint8) +
        sizeof(uint16) +
        sizeof(uint8)  
        );
}

//::GetBlockLength()-----------------------------------------------------------
/*Obtains block's length including length of optional data sub-blocks and Block
  Terminator size.

  Returns: sum of sizes of the header and data sub-blocks in bytes.
 */
unsigned int CGifGraphicControlExt::GetBlockLength(uint8* pBlockData //[in]
                                                 )
{
if (pBlockData[sizeof(GIF_EXTENSION_INTRODUCER)] == GIF_EXT_GRAPHIC_CONTROL) 
  {
  return GetLength() + sizeof(GIF_BLOCKTERMINATOR);
  }

ASSERT(FALSE);
return 0;
}

///////////////////////////////////////////////////////////////////////////////
// CGifCommentExt
//::CGifCommentExt()-----------------------------------------------------------
/*
 */
CGifCommentExt::CGifCommentExt() :
  CGifExtension(CGifExtension::COMMENT)
{
}

    /* the GIF89a spec defines comment extensions to contain ASCII text,
       but doesn't specify what end-of-line delimiter is to be used.
       Most programs use DOS style (CR/LF), at least one uses CR (Graphic
       Workshop for Windows), unix programs probably use LF. We just delete
       CRs unless they are not followed by a LF, then we convert CR to LF.
       Even though 7 bit ASCII is specified, there are some GIF files with
       comments that use codepage 437 and most DOS GIF readers display this
       in the DOS charset (e.g. VPIC). We convert the characters both in
       cp437 and latin1 and try to approximate some of the box drawing chars.
    */
//see gif2png.244/gifread.c/line#288

//::~CGifCommentExt()----------------------------------------------------------
/*
 */
CGifCommentExt::~CGifCommentExt()
{
}

//::GetLength()------------------------------------------------------------------
/*Obtains length of the fixed part of the data block. Data sub-blocks are 
  following this part of the data block. 
  
  Note: Block terminator is treated as zero-sized data sub-block and it is not 
  included in the length returned by this method.

  Returns size of the header section of the extension block in bytes.
 */
const unsigned int CGifCommentExt::GetLength()
{
return (sizeof(GIF_EXTENSION_INTRODUCER) + 
        sizeof(GIF_EXT_COMMENT) 
        //Here goes variable comment data
        );
}

//::GetBlockLength()-----------------------------------------------------------
/*Obtains block's length including length of optional data sub-blocks and Block
  Terminator size.

  Returns: sum of sizes of the header and data sub-blocks in bytes.
 */
unsigned int CGifCommentExt::GetBlockLength(uint8* pBlockData //[in]
                                                 )
{
if (pBlockData[sizeof(GIF_EXTENSION_INTRODUCER)] == GIF_EXT_COMMENT) 
  {
  unsigned nRes = GetLength(); //Get size of block's header
  int iSize = CGifDataSubblock::GetAllSubblockLength( &pBlockData[nRes] );
  if (iSize >= 0)
    {
    nRes +=  iSize + sizeof(GIF_BLOCKTERMINATOR);
    return nRes;
    }
  }

ASSERT(FALSE);
return 0;
}

///////////////////////////////////////////////////////////////////////////////
// CGifApplicationExt
//::CGifApplicationExt()-------------------------------------------------------
/*
 */
CGifApplicationExt::CGifApplicationExt() :
  CGifExtension(CGifExtension::APPLICATION), 
  m_cSize(0)
{
memset(m_cAppIdentifier, 0, sizeof(m_cAppIdentifier));
memset(m_cAppAuthentication, 0, sizeof(m_cAppAuthentication));
}

//::~CGifApplicationExt()------------------------------------------------------
/*
 */
CGifApplicationExt::~CGifApplicationExt()
{
}

//::GetLength()------------------------------------------------------------------
/*Obtains length of the fixed part of the data block. Data sub-blocks are 
  following this part of the data block. 
  
  Note: Block terminator is treated as zero-sized data sub-block and it is not 
  included in the length returned by this method.

  Returns size of the header section of the extension block in bytes.
 */
const unsigned int CGifApplicationExt::GetLength()
{
return (sizeof(GIF_EXTENSION_INTRODUCER) + 
        sizeof(GIF_EXT_APPLICATION)      + 
        sizeof(uint8) +
        sizeof(uint8) * 8 +
        sizeof(uint8) * 3 
        //Here goes variable application data
        );
}

//::GetBlockLength()-----------------------------------------------------------
/*Obtains block's length including length of optional data sub-blocks and Block
  Terminator size.

  Returns: sum of sizes of the header and data sub-blocks in bytes.
 */
unsigned int CGifApplicationExt::GetBlockLength(uint8* pBlockData //[in]
                                                 )
{
if (pBlockData[sizeof(GIF_EXTENSION_INTRODUCER)] == GIF_EXT_APPLICATION) 
  {
  unsigned nRes = GetLength(); //Get size of block's header
  int iSize = CGifDataSubblock::GetAllSubblockLength( &pBlockData[nRes] );
  if (iSize >= 0)
    {
    nRes +=  iSize + sizeof(GIF_BLOCKTERMINATOR);
    return nRes;
    }
  }

ASSERT(FALSE);
return 0;
}

///////////////////////////////////////////////////////////////////////////////
// CGifColorTable
//::CGifColorTable()-----------------------------------------------------------
/*Default constructor
 */
CGifColorTable::CGifColorTable() :
  m_nSize(0),
  m_pTable(NULL),
  MAX_SIZE(256)
{
}

/*Copies color table section from a data stream in Graphics Interchange Format
 */
CGifColorTable::CGifColorTable(const uint8* pTableData, //color table section 
                               //of a data stream in Graphics Interchange Format (GIF)
                               const unsigned int nTableSize //size of the table 
                               //(number of colors) [0,256]
                               ) :
  MAX_SIZE(256)
{
Copy(pTableData, nTableSize);
}

CGifColorTable::~CGifColorTable()
{
if (m_pTable != NULL)
  delete[] m_pTable;
}

#ifdef _DEBUG
//::Dump()---------------------------------------------------------------------
/*Dumps the content of the CGifColorTable object to a standard 
  output stream.
 */
void CGifColorTable::Dump() const
{
TRACE2("CGifColorTable @ %p has %d colors\n", this, GetSize());
unsigned int nIndex = 0;
if (GetSize() > 0)
  {
  TRACE0(" {\n");
  }

while (nIndex < GetSize())
  {
  char szOutput[64];
  ::Dump(m_pTable[nIndex], szOutput);
  TRACE2("  %d. %s\n",nIndex, szOutput);
  nIndex++;
  }
TRACE0(" }\n\n");
}

#endif //_DEBUG

#ifdef _DEBUG
//DumpGifColorTable()----------------------------------------------------------
/*
  Example:
    DumpGifColorTable(this, stdout);
 */
void DumpGifColorTable(CGifColorTable* pObject, 
                       FILE* fileStream
                       )
{
if (pObject)
  {
  unsigned i, j;
  unsigned nSize = pObject->GetSize();

  for (i = 0; i < nSize; i+=4)
    {
    for (j = 0; j < 4 && j < nSize; j++)
      {
      fprintf(fileStream,
              "%3d: %02x %02x %02x   ", i + j,
             (*pObject)[i + j].m_cRed,
             (*pObject)[i + j].m_cGreen,
             (*pObject)[i + j].m_cBlue);
      }
    fprintf(fileStream, "\n");
    }
  }
}
#endif /* _DEBUG */

//::Copy()---------------------------------------------------------------------
/*Copies color table section from a data stream in Graphics Interchange Format.

  Returns: true if successful. In case of memory allocation failure or if 
  nTableSize is out of range, returns false.
 */
bool CGifColorTable::Copy(const uint8* pTableData, //[in] color table section 
                          //of a data stream in Graphics Interchange Format (GIF)
                          const unsigned int nTableSize //[in] size of the table 
                          //(number of colors). If size is zero, the table would
                          //be erased. Valid range is [0,256].
                         )
{
TRACE2("CGifColorTable::Copy(from 0x%p, %d colors)\n",
       pTableData,
       nTableSize);

if (nTableSize == 0) //Erase current table
  {
  RemoveAll();
  return true; 
  }

if (pTableData == NULL)
  {
  TRACE0("  Failure: invalid data.\n");
  return false;
  }

if (nTableSize <= MAX_SIZE)
  {
  //If new table could not fit in the space of previous table, create
  //bigger table. Actual size of allocated buffer is not stored, 
  //resulting in unnecessary reallocation in some situations.
  if (nTableSize > m_nSize)
    {
    RemoveAll();
    m_pTable = new CGifColor[nTableSize];
    }
  if (m_pTable != NULL)
    {
    memcpy(m_pTable,pTableData,nTableSize*m_pTable->GetLength());
    m_nSize = nTableSize;
    return true;
    }
  }

return false;
}

//::operator=()----------------------------------------------------------------
/*Assigns a new value to a GIF Color Table.
  
  Returns: A reference to the current object.
 */
CGifColorTable& CGifColorTable::operator=(const CGifColorTable& gifSource 
                                         )
{
RemoveAll(); //Clean this object

m_nSize = gifSource.GetSize();
m_pTable = new CGifColor[m_nSize];
if (m_pTable != NULL)
  {
  memcpy(m_pTable,gifSource.m_pTable,m_nSize*m_pTable->GetLength());
  }
else
  m_nSize = 0; //Memory allocation failure

return *this;
}

//::GetSize()------------------------------------------------------------------
/*Obtains the size of the table. Since indexes are zero-based, the size is 1 
  greater than the largest index. Size of the table in bytes is three times of
  number of elements.

  See also: CGifColor

  Returns: number of elements (colors) size of the table.
 */
unsigned int CGifColorTable::GetSize() const
{
return m_nSize;
}

//::GetColorDepth()------------------------------------------------------------
/*
  Returns: number of bits per pixel. Valid range is [1,8]
 */
const int CGifColorTable::GetColorDepth() const
{
int iColorDepth;
for (iColorDepth = 1; iColorDepth <= 8; iColorDepth++)
  if ((1 << iColorDepth) >= (int)m_nSize)
    break;

return iColorDepth; //Return smallest bitfield size n will fit in 
}

//::SetSize()------------------------------------------------------------------
/*Establishes the size of an empty or existing table; allocates memory 
  if necessary. If the new size is smaller than the old size, then the table 
  is truncated and all unused memory is released. 
  Use this function to set the size of your table before you begin using 
  the table.

  Returns: true if successful or false if memory allocation failure or if
  new size is out of prescribed range for color table.
 */
bool CGifColorTable::SetSize(const unsigned int nNewSize //new table size 
                             //(number of colors). Must in range [0, 256].
                            )
{

if (nNewSize > MAX_SIZE)
  return false;

if (nNewSize == 0) //Delete color table
  {
  RemoveAll();
  }
else //Expand or truncate old color table
  {
  CGifColor* pNewTable = new CGifColor[nNewSize];
  if (pNewTable == NULL)
    return false;

  if( m_pTable != NULL) //Copy old content
    {
    if (nNewSize <= m_nSize)
      memcpy(pNewTable,m_pTable,nNewSize*m_pTable->GetLength());
    else
      memcpy(pNewTable,m_pTable,m_nSize*m_pTable->GetLength());

    delete[] m_pTable; //Free old table
    }
  
  m_pTable = pNewTable;
  m_nSize = nNewSize;
  }
return true;
}

//::RemoveAll()----------------------------------------------------------------
/*Removes all the elements from this table. 
 */
void CGifColorTable::RemoveAll()
{
if( m_pTable != NULL)
  {
  delete[] m_pTable;
  m_pTable = NULL;
  }
m_nSize = 0;
}

//::operator[]-----------------------------------------------------------------
/*Sets or gets the element at the specified index. The parameter nIndex must be 
  greater than or equal to 0 and less than the value returned by GetSize().
  
  Returns: a reference to the specified element within the color table.
 */
CGifColor& CGifColorTable::operator[](unsigned int nIndex //zero-based index 
                                      //of the element to be accessed
                                      )
{
ASSERT(nIndex < m_nSize);
return m_pTable[nIndex];
}

/*Returns: the color value at the specified index.
 */
CGifColor CGifColorTable::operator[](unsigned int nIndex //zero-based index 
                                     //of the color table item
                                     ) const
{
ASSERT(nIndex < m_nSize);
return m_pTable[nIndex];
}

//::GetLength()------------------------------------------------------------------
/*Obtains length of the GIF color table.

  Returns: size of the GIF color table in bytes.
 */
const int CGifColorTable::GetLength() const
{
return ( GetSize() * sizeof(CGifColor) );
}

///////////////////////////////////////////////////////////////////////////////
// CGifColor
//:CGifColor()-----------------------------------------------------------------
/*Default constructor uses black as default color ( RGB[0,0,0] )
 */
CGifColor::CGifColor():
  m_cRed(0),
  m_cGreen(0),
  m_cBlue(0)
{
}

CGifColor::CGifColor(uint8 cRed,   //[in] intensity of red color [0,255]
                     uint8 cGreen, //[in] intensity of green color [0,255]
                     uint8 cBlue   //[in] intensity of blue color [0,255]
                     ) :
  m_cRed(cRed),
  m_cGreen(cGreen),
  m_cBlue(cBlue)
{
}

#ifdef _DEBUG
//::Dump()---------------------------------------------------------------------
/*Dumps the content of the GIF color as formatted string to the given buffer. 
  Buffer size have to be sufficient to hold the dump. There is no error checking.

  Returns pointer to the output buffer if successful, or NULL in case of failure.
 */
char* Dump(const CGifColor& gifColor, 
           char* szOutput
           )
{
if (szOutput != NULL)
  {
  sprintf(szOutput,"[%3d,%3d,%3d]",gifColor.m_cRed, gifColor.m_cGreen, gifColor.m_cBlue);
  return szOutput;
  }
return NULL;
}

#endif //_DEBUG

//::GetLength()------------------------------------------------------------------
/*Obtains length of the GIF color data.

  Returns: size of the GIF color in bytes.
 */
const int CGifColor::GetLength()
{
return 3; //(sizeof(CGifColor::m_cRed) + 
          //sizeof(CGifColor::m_cGreen) + 
          //sizeof(CGifColor::m_cBlue))
}

///////////////////////////////////////////////////////////////////////////////
// CGifLogicalScreenDescriptor
//::CGifLogicalScreenDescriptor()----------------------------------------------
/*Default constructor
 */
CGifLogicalScreenDescriptor::CGifLogicalScreenDescriptor() :
  m_wWidth(0),
  m_wHeight(0),
  m_cControlFlags(0),
  m_cBkColorIndex(0),
  m_cAspectRatio(0)
{
}

/*Copies Logical Screen Descriptor from a data stream in Graphics Interchange
  Format.
 */
CGifLogicalScreenDescriptor::CGifLogicalScreenDescriptor(const uint8* pData //logical
          //screen descriptor block in Graphics Interchange Format (GIF)
          )
{
TRACE1("CGifLogicalScreenDescriptor::CGifLogicalScreenDescriptor(pData @ %p)\n",
       pData);
Copy(pData);
}

/*
 */
CGifLogicalScreenDescriptor::CGifLogicalScreenDescriptor(const CGifLogicalScreenDescriptor& gifSource  //an encoded image in 
                                  //Graphics Interchange Format (GIF)
           )
{
m_wWidth              = gifSource.m_wWidth;
m_wHeight             = gifSource.m_wHeight;
m_cControlFlags           = gifSource.m_cControlFlags;
m_cBkColorIndex       = gifSource.m_cBkColorIndex;
m_cAspectRatio        = gifSource.m_cAspectRatio;
m_gifGlobalColorTable = gifSource.m_gifGlobalColorTable;
}

CGifLogicalScreenDescriptor::~CGifLogicalScreenDescriptor()
{
}

#ifdef _DEBUG
//::Dump()---------------------------------------------------------------------
/*Dumps the content of the CGifLogicalScreenDescriptor object to a standard 
  output stream.
 */
void CGifLogicalScreenDescriptor::Dump() const
{
TRACE1("CGifLogicalScreenDescriptor @ %p\n  {\n", this);
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
  m_gifGlobalColorTable.Dump();

}

/*Dumps the content of the GIF Logical Screen Descriptor block as formatted 
  string to the given buffer. Buffer size have to be sufficient to hold the 
  dump. There is no error checking.

  Returns pointer to the output buffer if successful, or NULL in case of failure.
 */
char* CGifLogicalScreenDescriptor::Dump(char* szOutput
                                       ) const
{
if (szOutput != NULL)
  {
  sprintf(szOutput,
            "{\nm_wWidth = %d,\nm_wHeight = %d,\n"
            "m_cControlFlags = 0x%x (has%s Global Color Table,\n"
            "Color Resolution %d bits,\n"
            "Table is%s sorted,\n"
            "Global Color Table Size %d),\n"
            "m_cBkColorIndex = %d,\n"
            "m_cAspectRatio = %d\n}\n",
          m_wWidth,
          m_wHeight,
          m_cControlFlags,
          HasColorTable() ? "" : " not",
          GetColorResolution(),
          IsColorTableSorted() ? "" : " not",
          GetColorTableSize(),
          m_cBkColorIndex,
          m_cAspectRatio);
  return szOutput;
  }
return NULL;
}

#endif //_DEBUG

//::Copy()---------------------------------------------------------------------
/*Copies Logical Screen Descriptor from a data stream in Graphics Interchange
  Format.
 */
bool CGifLogicalScreenDescriptor::Copy(const uint8* pData //logical
          //screen descriptor block in Graphics Interchange Format (GIF)
          )
{
TRACE1("CGifLogicalScreenDescriptor::Copy(from 0x%p)\n",pData);
if (pData == NULL)
  return false;
  //This is a hack to speed up copying
memcpy(&m_wWidth, pData, GetLength());
if (HasColorTable())
  {
  return m_gifGlobalColorTable.Copy(&pData[GetLength()], GetColorTableSize());
  }
return true;
}

//::operator=()----------------------------------------------------------------
/*Assigns a new value to a Logical Screen Descriptor.
  
  Returns: A reference to the current object.
 */
CGifLogicalScreenDescriptor& CGifLogicalScreenDescriptor::operator=(
               const CGifLogicalScreenDescriptor& gifSource 
               )
{
m_wWidth              = gifSource.m_wWidth;
m_wHeight             = gifSource.m_wHeight;
m_cControlFlags       = gifSource.m_cControlFlags;
m_cBkColorIndex       = gifSource.m_cBkColorIndex;
m_cAspectRatio        = gifSource.m_cAspectRatio;
m_gifGlobalColorTable = gifSource.m_gifGlobalColorTable;
return *this;
}

//::GetLength()------------------------------------------------------------------
/*Obtains length of the data block.

  Returns size of the data block in bytes.
 */
const unsigned int CGifLogicalScreenDescriptor::GetLength() const
{
  //Note: calculating block size as a sum of fields prescribed by GIF allows
  //developers to add some custom members if necessary.
return (sizeof(m_wWidth)        + 
        sizeof(m_wHeight)       + 
        sizeof(m_cControlFlags) + 
        sizeof(m_cBkColorIndex) + 
        sizeof(m_cAspectRatio)  );
}

//::HasColorTable()------------------------------------------------------------
/*Validates presence of a Global Color Table. If the Global Color Table Flag is
  set, then the Global Color Table will immediately follow the Logical Screen 
  Descriptor and the value of the Background Color Index field should be used
  as the table index of the background color. If the flag is not set, no Global
  Color Table follows, the Background Color Index field is meaningless.

     Field format:

      7 6 5 4 3 2 1 0  bit (4th byte in Logical Screen Descriptor block)
     +---------------+
     |g|     | |     | g = 1 Global Color Table follows Logical Screen Descriptor
     +---------------+ g = 0 no Global Color Table follows

  Returns: true if a Global Color Table is present, or false if it is not.
 */
bool CGifLogicalScreenDescriptor::HasColorTable() const
{
  //Valid bit is 1000 0000
return ((m_cControlFlags & 0x80) == 0x80);
}

//::GetColorResolution()-------------------------------------------------------
/*Retrieves number of bits per primary color. This value represents the size 
  of the entire palette from which the colors in the graphic were selected.
  The value of the rrr field has range [0,7], which represents 1 to 8 bits per 
  primary color per each color that the palette of the original image had.

     Field format:

      7 6 5 4 3 2 1 0  bit (4th byte in Logical Screen Descriptor block)
     +---------------+
     | |r r r| |     | rrr + 1 = number of bits per primary color
     +---------------+

  Returns: number of bits per primary color.
 */
unsigned int CGifLogicalScreenDescriptor::GetColorResolution() const
{
  //Valid bits are 0111 0000
return ((m_cControlFlags & 0x70) >> 4) + 1;
}

//::IsColorTableSorted()-------------------------------------------------------
/*Tests if a Global Color Table is ordered by importance. Typically, the 
  ordered tables will have the most frequent color first. This helps a decoder, 
  with fewer available colors, in choosing the best subset of colors; the decoder
  may use an initial segment of the table to render the graphic.

     Field format:

      7 6 5 4 3 2 1 0  bit (4th byte in Logical Screen Descriptor block)
     +---------------+
     | |     |s|     | s = 1 color palette is sorted (v. 89a)
     +---------------+ s = 0 color palette is not sorted  (v. 89a)
                       s = 0 reserved  (v. 87a)

  Returns: true if Global Color Table is sorted, in order of decreasing 
  importance. If table is not sorted, false is returned.
 */
bool CGifLogicalScreenDescriptor::IsColorTableSorted() const
{
  //Valid bit is 0000 1000
return ((m_cControlFlags & 0x08) == 0x08);
}

//::GetColorTableSize()--------------------------------------------------------
/*Retrieves the number of elements of a Global Color Table. 
  Global Color Table is a color palette used for all the images without Local 
  Color Table in data stream and size of the Global Color Table corresponds 
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
        GlobalColorTableSize = 3 * NumberOfTableElements [bytes]
        GlobalColorTableSize = 3 * (2^(nnn+1)) [bytes]

     Field format:

      7 6 5 4 3 2 1 0  bit (4th byte in Logical Screen Descriptor block)
     +---------------+
     | |     | |n n n| nnn + 1 = number of bits per pixel
     +---------------+

  Returns: maximum number of colors within color table (palette) used for 
  an image.

  Note: if Global Color Table flag g is set to zero (HasColorTable() method 
  returned false), actual size of the color table is zero and the table is
  omitted from the data stream.

  See Also: CGifColor, HasColorTable()
 */
unsigned int CGifLogicalScreenDescriptor::GetColorTableSize() const
{
  //Valid bits are 0000 0111
return 1 << ((m_cControlFlags & 0x07) + 1);
}

//::GetPixelAspectRatio()------------------------------------------------------
/*Retrieves Pixel Aspect Ratio used to compute an approximation of the aspect 
  ratio of the pixel in the original image. 
  The Pixel Aspect Ratio is defined to be the quotient of the pixel's width x
  over its height y. The value range in this field allows specification of 
  the widest pixel of 4:1 to the tallest pixel of 1:4 in increments of 1/64th.
  
  If the value of the field is not 0, this approximation of the aspect ratio is 
  computed based on the formula: 

    PixelAspectRatio = (AspectRatioFactor + 15.0) / 64.0 
    AspectRatioFactor Range [1,255] (89a) or 0 (87a)

  Returns: pixels aspect ratio x : y (89a) or 1.0 (87a).
 */
double CGifLogicalScreenDescriptor::GetPixelAspectRatio() const
{
  //If aspect ratio is not given (as in v.87a), assume 1:1 ratio
if (m_cAspectRatio == 0)
  return 1.0;
return ((double)m_cAspectRatio + 15.0) / 64.0;
}

//::GetBkColorIndex()----------------------------------------------------------
/*Retrieves index into the Global Color Table for the Background Color. 
  The Background Color is the color used for those pixels on the screen that 
  are not covered by an image. 
  
  Note: Value is valid only if the Global Color Table Flag is set.
  If Global Color Table Flag is not set, this field should be zero and should 
  be ignored.

  Returns: background color index.
 */
unsigned int CGifLogicalScreenDescriptor::GetBkColorIndex() const
{
return m_cBkColorIndex;
}

//::GetScreenSize()------------------------------------------------------------
/*Retrieves dimensions of a Logical Screen in pixels. The Logical Screen Width
  and Height define the viewport area of the display device within which the 
  images will be rendered.
  The logical screen width and height can both be larger than the physical 
  display. 

  Note: Values are stored in 'Little Endian' byte order (the Least Significant 
  Byte (LSB) first).
 */
void CGifLogicalScreenDescriptor::GetScreenSize(unsigned int& nWidth, //[out] 
                                                //logical screen width [pixel]
                                                unsigned int& nHeight //[out] 
                                                //logical screen height [pixel]
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

//::GetColorTable()------------------------------------------------------
/*Obtains global color palette used by all those graphics in the Data Stream 
  which do not have a Local Color Table associated with them. 

  Returns: Global Color Table used to render graphics.
 */
CGifColorTable CGifLogicalScreenDescriptor::GetColorTable() const
{
return m_gifGlobalColorTable;
}

CGifColorTable& CGifLogicalScreenDescriptor::GetColorTable()
{
return m_gifGlobalColorTable;
}

///////////////////////////////////////////////////////////////////////////////
// CGifHeader
//::CGifHeader()---------------------------------------------------------------
/*Default constructor
 */
CGifHeader::CGifHeader()
{
memcpy(m_cSignature, CGifLabel::m_szSignature,  sizeof(m_cSignature));
memcpy(m_cVersion,   CGifLabel::m_szVersion[1], sizeof(m_cVersion));
}

/*
 */
CGifHeader::CGifHeader(uint8* pData //an encoded image in Graphics Interchange Format (GIF)
                      )
{
Copy(pData);
}

/*
 */
CGifHeader::CGifHeader(const CGifHeader& gifSource  //an encoded image in 
                                  //Graphics Interchange Format (GIF)
           )
{
memcpy(m_cSignature, gifSource.m_cSignature, sizeof(m_cSignature));
memcpy(m_cVersion, gifSource.m_cVersion, sizeof(m_cVersion));
m_gifScreenDescriptor = gifSource.m_gifScreenDescriptor;
}

CGifHeader::~CGifHeader()
{
}

//::Copy()---------------------------------------------------------------------
/*Copies a header section of data stream in Graphics Interchange Format.

  Returns: true if successful, otherwise returns false.
 */
bool CGifHeader::Copy(const uint8* pData //[in] a data stream in Graphics
                          //Interchange Format (GIF)
               )
{
TRACE1("CGifHeader::Copy(0x%p)\n", pData);
if ( pData != NULL)
  {
  //Copy header of data stream assuming that fields are sequentially ordered.
  const int iLen = (sizeof(m_cSignature) + sizeof(m_cVersion));
  memcpy(m_cSignature, pData, iLen);
  return m_gifScreenDescriptor.Copy(&pData[iLen]);
  }
return false;
}

#ifdef _DEBUG
//::Dump()---------------------------------------------------------------------
/*Dumps the content of the CGifHeader object to a standard output stream.
 */
void CGifHeader::Dump() const
{
TRACE1("CGifHeader @ %p\n", this);
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

if(m_gifScreenDescriptor.HasColorTable())
  m_gifScreenDescriptor.GetColorTable().Dump();

}

/*Dumps the content of the CGifHeader object as formatted string to the given
  buffer. Buffer size have to be sufficient to hold the dump. There is no error
  checking.

  Returns pointer to the output buffer if successful, or NULL in case of failure.
 */
char* CGifHeader::Dump(char* szOutput
                               ) const
{
if (szOutput != NULL)
  {
  char szSignature[4];
  szSignature[0] = m_cSignature[0];
  szSignature[1] = m_cSignature[1];
  szSignature[2] = m_cSignature[2];
  szSignature[3] = '\0';

  char szVersion[4];
  szVersion[0] = m_cVersion[0];
  szVersion[1] = m_cVersion[1];
  szVersion[2] = m_cVersion[2];
  szVersion[3] = '\0';

  sprintf(szOutput,
         "{\nm_cSignature = %s,\nm_cVersion = %s,\nm_gifScreenDescriptor = ",
          szSignature,
          szVersion);
  if (m_gifScreenDescriptor.Dump(&szOutput[strlen(szOutput)]) == NULL)
    return NULL;
  sprintf(&szOutput[strlen(szOutput)], "}\n");
  return szOutput;
  }
return NULL;
}

#endif //_DEBUG

//::IsValid()------------------------------------------------------------------
/*Validates data signature and supported GIF versions.

  Returns true if this data block has valid tag and supported version number, 
  otherwise returns false.
 */
bool CGifHeader::IsValid() const
{
if(memcmp(m_cSignature, CGifLabel::m_szSignature,sizeof(m_cSignature)) == 0)
  {
  if( (memcmp(m_cVersion, CGifLabel::m_szVersion[1],sizeof(m_cVersion)) == 0) ||
    (memcmp(m_cVersion, CGifLabel::m_szVersion[0],sizeof(m_cVersion)) == 0) )
    return true;
  }
return false;
}

/*Returns true if data stream begins with valid tag and version number, 
  otherwise returns false.
 */
bool CGifHeader::IsValid(const uint8* pData //an encoded image in 
                                           //Graphics Interchange Format (GIF)
                         ) const
{
return CGifLabel::IsValid(pData);
}

//::GetLength()------------------------------------------------------------------
/*Obtains length of the fixed portion of the header section of the GIF data stream.

  Note: header length is a sum of Signature field length, Version field length and
  Logical Screen Descriptor block length. Length of the optional Global Color Table
  is not included.

  Returns: size of the GIF header in bytes.
 */
const unsigned int CGifHeader::GetLength() const
{
  //Note: calculating block size as a sum of field sizes prescribed by GIF allows
  //developers to add some custom members if necessary.
return (sizeof(m_cSignature) + sizeof(m_cVersion)) + 
        m_gifScreenDescriptor.GetLength();
}

//::GetBlockLength()-----------------------------------------------------------
/*Obtains block's length including length of optional Global Color Table.


  Returns: size of the GIF header's fixed and optional parts in bytes.
 */
unsigned int CGifHeader::GetBlockLength() const
{
if (!m_gifScreenDescriptor.HasColorTable())
  return GetLength();
else
  return (GetLength() + 
          m_gifScreenDescriptor.GetColorTableSize() * CGifColor::GetLength());
}

//::GetLogicalScreenDescriptor()-----------------------------------------------
/*Retrieves Logical Screen Descriptor data block.
  Logical Screen Descriptor is required data segment for a GIF image.

  Returns: Logical Screen Descriptor
 */
CGifLogicalScreenDescriptor& CGifHeader::GetLogicalScreenDescriptor()
{
return m_gifScreenDescriptor;
}

CGifLogicalScreenDescriptor CGifHeader::GetLogicalScreenDescriptor() const
{
return m_gifScreenDescriptor;
}

/////////////////////////////////////////////////////////////////////////////
// CGif
//::CGif()---------------------------------------------------------------------
/*Default constructor
 */
CGif::CGif()
{
}

/*Copies an image in Graphics Interchange Format (GIF)
 */
CGif::CGif(uint8* pData //an encoded image in Graphics Interchange Format (GIF)
          )
{
Copy(pData);
}

CGif::CGif(const uint8* pData //an encoded image in Graphics Interchange Format (GIF)
          )
{
Copy(pData);
}

/*
 */
CGif::CGif(const CGif& gifSource  //an encoded image in 
                                  //Graphics Interchange Format (GIF)
           )
{
m_gifHeader = gifSource.m_gifHeader;
}

CGif::~CGif()
{
}

#ifdef _DEBUG
//::Dump()---------------------------------------------------------------------
/*Dumps the content of the CGif object to a standard output stream.
 */
void CGif::Dump()
{
TRACE1("CGif @ %p\n  {\n", this);
const int BUFFER_SIZE = 256+64;
char* szOutput = new char[BUFFER_SIZE];
m_gifHeader.Dump(szOutput);

int iActualSize;
if ((iActualSize = (int)strlen(szOutput)) >= BUFFER_SIZE)
  {
    //Try to salvage something
  iActualSize++;
  TRACE2(" failure: %d bytes buffer too small for %d string\n", 
         BUFFER_SIZE, iActualSize);
  }
else
  {
  TRACE1("  m_gifHeader = %s\n  }\n",szOutput);
  }
delete[] szOutput;

if(HasGlobalColorTable())
  m_gifHeader.GetLogicalScreenDescriptor().GetColorTable().Dump();
}
#endif //_DEBUG

//::IsValid()------------------------------------------------------------------
/*Validates data signature and supported GIF versions.

  Returns true if data begins with valid tag and version number, 
  otherwise returns false.
 */
bool CGif::IsValid() const
{
return m_gifHeader.IsValid();
}

/*Returns true if data stream begins with valid tag and version number, 
  otherwise returns false.
 */
bool CGif::IsValid(const uint8* pData //an encoded image in 
                                     //Graphics Interchange Format (GIF)
                  ) const
{
return m_gifHeader.IsValid(pData);
}

//::HasGlobalColorTable()------------------------------------------------------
/*Validates presence of a Global Color Table.

  See also: CGifLogicalScreenDescriptor, CGifColorTable
  Returns: true if a Global Color Table is present, or false if it is not.
 */
bool CGif::HasGlobalColorTable()
{
return m_gifHeader.GetLogicalScreenDescriptor().HasColorTable();
}

//::GetHeader()----------------------------------------------------------------
/*Obtains header of data stream in Graphics Interchange Format (GIF).

  Returns: GIF header
 */
CGifHeader CGif::GetHeader() const
{
return m_gifHeader;
}

CGifHeader& CGif::GetHeader()
{
return m_gifHeader;
}

//::GetGlobalColorTable()------------------------------------------------------
/*
  Returns: Global Color Table used ...
 */
CGifColorTable& CGif::GetGlobalColorTable()
{
return GetHeader().GetLogicalScreenDescriptor().GetColorTable();
}

//::GetScreenSize()------------------------------------------------------------
/*Retrieves dimensions of an image in pixels.
  The image width and height can both be larger than the physical display. 

  See also: CGifLogicalScreenDescriptor::GetScreenSize

  Returns: true if successful; false if data stream is not in valid format.
 */
bool CGif::GetSize(const uint8* pData,//[in] an encoded image in Graphics
                                     //Interchange Format (GIF)
                   unsigned int& nWidth, //[out] image width [pixel]
                   unsigned int& nHeight //[out] image height [pixel]
                                                ) const
{
if (IsValid(pData))
  {
  ((CGifHeader*)pData)->
    GetLogicalScreenDescriptor().GetScreenSize(nWidth, nHeight);
  return true;
  }
return false;
}

bool CGif::GetSize(unsigned int& nWidth, //[out] image width [pixel]
                   unsigned int& nHeight //[out] image height [pixel]
                                                ) const
{
if (IsValid())
  {
  m_gifHeader.GetLogicalScreenDescriptor().GetScreenSize(nWidth, nHeight);
  return true;
  }
return false;
}

//::Copy()---------------------------------------------------------------------
/*Copies a data stream in Graphics Interchange Format to image container.

  Returns: true if successful, otherwise returns false.
 */
bool CGif::Copy(const uint8* pData //[in] a data stream in Graphics
                          //Interchange Format (GIF)
               )
{
TRACE1("CGif::Copy(0x%p)\n", pData);
if ( pData != NULL)
  {
  //Copy header of data stream assuming that fields are sequentially ordered.
  return m_gifHeader.Copy(pData);
  }
return false;
}

///////////////////////////////////////////////////////////////////////////////
#if _MSC_VER >= 1300
   //Microsoft Visual Studio C++ v7.0
   //Enable warning C4127: conditional expression is constant
  #pragma warning( default: 4127)
#endif
/*****************************************************************************
 * $Log: 
 *  18   Biblioteka1.17        2003-11-03 12:10:06  Darko           MSVC 7.0
 *       pragmas
 *  17   Biblioteka1.16        2003-09-30 10:00:25  Darko           Replaced DWORD,
 *       WORD with uint32, uint16
 *  16   Biblioteka1.15        2002-10-10 19:32:52  Darko Kolakovic
 *       m_gifHeader.GetLogicalScreenDescriptor().GetScreenSize
 *  15   Biblioteka1.14        2002-08-23 14:27:10  Darko Kolakovic
 *       CGifColorTable::Copy reallocation
 *  14   Biblioteka1.13        2002-08-02 21:26:30  Darko Kolakovic 
 *  13   Biblioteka1.12        2002-08-01 23:35:46  Darko           CopyAll()
 *       sub-blocks
 *  12   Biblioteka1.11        2002-08-01 13:58:27  Darko Kolakovic 
 *  11   Biblioteka1.10        2002-08-01 00:23:47  Darko           CGifImageData
 *  10   Biblioteka1.9         2002-07-31 16:30:07  Darko Kolakovic
 *       SeekImageDescriptor inserted
 *  9    Biblioteka1.8         2002-07-31 03:43:53  Darko           Read block
 *       sizes from a stream
 *  8    Biblioteka1.7         2002-07-30 16:12:22  Darko Kolakovic
 *       CGifImageDescriptor
 *  7    Biblioteka1.6         2002-07-29 13:09:34  Darko Kolakovic
 *       CGifLabel::IsValid() added
 *  6    Biblioteka1.5         2002-07-28 23:45:18  Darko           Added Gif Data
 *       Sub-block
 *  5    Biblioteka1.4         2002-07-17 18:30:03  Darko Kolakovic Added
 *       CGifExtension
 *  4    Biblioteka1.3         2002-07-16 19:53:33  Darko Kolakovic Added
 *       CGifHeader::Copy()
 *  3    Biblioteka1.2         2002-07-16 00:43:26  Darko           Added operator
 *       =()
 *  2    Biblioteka1.1         2002-07-15 18:45:05  Darko           Color Table
 *       added
 *  1    Biblioteka1.0         2002-07-12 17:17:08  Darko Kolakovic 
 * $
 * 2001 Initial version in Babylon Lib
 * 1990 v.89a enhanced GIF CompuServe Incorporated
 * 1987 v.87a Graphics Interchange Format (GIF) devised by the UNISYS Corp. and 
 *  Compuserve
 *****************************************************************************/

