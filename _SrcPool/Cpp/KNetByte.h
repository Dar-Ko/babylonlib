/*$Workfile: KNetByte.h$: header file
  $Revision: 6$ $Date: 2005-04-25 21:20:21$
  $Author: Darko$

  Network type definitions
  Copyright: CommonSoft Inc
  Mar. 2k2 Darko Kolakovic
 */

#ifndef _KNETBYTE_H_
    /*$Workfile: KNetByte.h$ sentry                                                  */
  #define _KNETBYTE_H_

#if _MSC_VER > 1000
  #pragma once
#endif // _MSC_VER > 1000

#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
  #pragma message ("   #include " __FILE__ )
#endif

/* ///////////////////////////////////////////////////////////////////////// */

#ifndef _NETWORD_
  /*A 16-bit unsigned integer in network byte order                          */
  typedef unsigned short NETWORD;
  /*Network byte order for the 16-bit unsigned integer.
    The network byte order is order in which the bytes of a two-byte number
    are transmitted on a network. The order is same as big-endian byte order.
    This order may be different then the order in which numbers are stored in
    memory for a particular architecture (CPU). Diverse machine architectures
    could exchange numbers or binary files only if byte order is standardized.
    See also: _ENDIAN_BIG_
   */
  #define _NETWORD_ 0x21
#endif

#ifndef _NETDWORD_
    /*A 32-bit unsigned integer in network byte order                        */
  typedef unsigned long NETDWORD;
  /*Network byte order for the 32-bit unsigned integer.
    The network byte order is order in which the bytes of a multi-byte number
    are transmitted on a network. The order is same as big-endian byte order.
    This order may be different then the order in which numbers are stored in
    memory for a particular architecture (CPU). Diverse machine architectures
    could exchange numbers or binary files only if byte order is standardized.
    See also: _ENDIAN_BIG_
   */
  #define _NETDWORD_ 0x4321
#endif

#if _M_IX86
  #ifdef _GET_WORD_ALIGNP
    #undef _GET_WORD_ALIGNP
  #endif
  #ifndef _GET_WORD_ALIGNP
    #define _GET_WORD_ALIGNP(pBYTE) (*((uint16*)pBYTE))
  #endif

  #ifdef _GET_DWORD_ALIGNP
    #undef _GET_DWORD_ALIGNP
  #endif
  #ifndef _GET_DWORD_ALIGNP
    #define _GET_DWORD_ALIGNP(pBYTE) (*((uint32*)pBYTE))
  #endif
#endif

/*CPU: ARM Risc CPU family, GNUC                                             */
#if (defined(__arm__) || defined(__ARMEL__))
  #ifdef _GET_WORD_ALIGNP
    #undef _GET_WORD_ALIGNP
  #endif
  #ifndef _GET_WORD_ALIGNP
  /*Copy a uint16 value byte by byte, because on some architectures (uint16*)
    pcHostValue
    will round pointer to match uint16 increments giving a result equal to
              *(uint16*)(pcHostValue/sizeof(uint16))
   */
    #define _GET_WORD_ALIGNP(pBYTE) \
      ((uint16)pBYTE[0]       |  \
       (uint16)pBYTE[1] <<  8 )
  #endif

  #ifdef _GET_DWORD_ALIGNP
    #undef _GET_DWORD_ALIGNP
  #endif
  #ifndef _GET_DWORD_ALIGNP
  //Copy a uint32 value byte by byte, because on some architectures (uint32*)pcHostValue
  //will round pointer to match uint32 increments giving a result equal to
  //*(uint32*)(pcHostValue/sizeof(uint32))
    #define _GET_DWORD_ALIGNP(pBYTE) \
      ((uint32)pBYTE[0]       |   \
       (uint32)pBYTE[1] <<  8 |   \
       (uint32)pBYTE[2] << 16 |   \
       (uint32)pBYTE[3] << 24 )
  #endif
#endif

/* ///////////////////////////////////////////////////////////////////////// */
#ifdef __cplusplus

#ifdef WXWORKS
  #include <netinet/in.h> //htonl(), htons()
#endif

#ifdef WIN32
  /*Windows Sockets htonl() function requires Windows Sockets 1.1 or later.
    Library used is Ws2_32.lib
   */
  #include <winsock.h>  //htonl(), htons()
#endif


///////////////////////////////////////////////////////////////////////////////
// The class NetWord converts a uint16 value from host byte order to network byte
// order and coverts given network uint32 value to host byte ordered value.
// The network byte order is same as big-endian byte order.
// See also: NetDWord, _ENDIAN_BIG_, htonl(), ntohl()
class NetWord
{
public:
  NetWord();
  NetWord(const uint16& wHostValue);
  NetWord(const BYTE* pcHostValue);
  NetWord(const NetWord& wNetworkValue);
  NetWord(const NetWord* pcNetworkValue);
  ~NetWord();
  operator uint16() const;
  operator BYTE*() const;
private:
  NETWORD m_netValue;
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//::NetWord()------------------------------------------------------------------
/* Default constructor
 */
inline NetWord::NetWord()
{
}

inline NetWord::NetWord(const NetWord& wNetworkValue) :
  m_netValue(wNetworkValue.m_netValue)
{
}

/*Copies array of bytes ordered in network byte order.
 */
inline NetWord::NetWord(const NetWord* pcNetworkValue) :
  m_netValue(pcNetworkValue->m_netValue)
{
}

/*Converts first two bytes of an array to the value in network byte order.
 */
inline NetWord::NetWord(const BYTE* pcHostValue)
{
m_netValue = htons(_GET_WORD_ALIGNP(pcHostValue));
}

/*Conversion constructor takes a 16-bit number in host byte order and stores it
  in the network byte order. The network byte order is same as big-endian byte
  order.
  See also: htons(), NETWORD
 */
inline NetWord::NetWord(const uint16& wHostValue)
{
m_netValue = htons(wHostValue);
}

//::~NetWord()-----------------------------------------------------------------
/*
 */
inline NetWord::~NetWord()
{
}

//::operator uint16()------------------------------------------------------------
/*Type conversion operator converts a 16-bit number from network order to
  host byte order. Depending of architecture, host byte order could be
  big-endian, little-endian or PDP-endian.
  See also: ntohs(), NETWORD, _ENDIAN_LITTLE_, _ENDIAN_BIG_
 */
inline NetWord::operator uint16() const
{
return ntohs(m_netValue);
}

//::operator BYTE*()-----------------------------------------------------------
/*Returns pointer to the internal data container.
 */
inline NetWord::operator BYTE*() const
{
return (BYTE*)(&m_netValue);
}

///////////////////////////////////////////////////////////////////////////////
// The class NetDWord converts a uint32 value from host byte order to network byte
// order and coverts given network uint32 value to host byte ordered value.
// The network byte order is same as big-endian byte order.
// See also: NETWORD, _ENDIAN_BIG_, htonl(), ntohl()
class NetDWord
{
public:
  NetDWord();
  NetDWord(const uint32& dwHostValue);
  NetDWord(const BYTE* pcHostValue);
  NetDWord(const NetDWord& dwNetworkValue);
  NetDWord(const NetDWord* pcNetworkValue);
  ~NetDWord();
  operator uint32() const;
  operator BYTE*() const;
private:
  NETDWORD m_netValue;
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//::NetDWord()-----------------------------------------------------------------
/* Default constructor
 */
inline NetDWord::NetDWord()
{
}

/*Copies a value in network byte order.

  Example:
    NetDWord netdwValue =  (NetDWord)0x0D0C0B0A;

    Memory Dump:
    netdwValue =  (NetDWord)0x0D0C0B0A = {0D 0C 0B 0A}
 */
inline NetDWord::NetDWord(const NetDWord& dwNetworkValue) :
  m_netValue(dwNetworkValue.m_netValue)
{
}

/*Copies array of bytes ordered in network byte order.

  Example:
      //Assume array in network byte order
    BYTE nInput[sizeof(NETDWORD)] = {0x08,0x07,0x06,0x05};
    NetDWord netdwValue(nInput); //Note: invokes NetDWord::~NetDWord()
    netdwValue = *(NetDWord*)nInput;

    Memory Dump:
    nInput[4] = {08 07 06 05};
    netdwValue =  (NetDWord*)nInput = {08 07 06 05}
    netdwValue =  *(NetDWord*)nInput = {08 07 06 05}
 */
inline NetDWord::NetDWord(const NetDWord* pcNetworkValue) :
  m_netValue(pcNetworkValue->m_netValue)
{
}

/*Converts first four bytes of an array to the value in network byte order.

  Example:
      //Host byte order is little-endian.
    BYTE nInput[sizeof(NETDWORD)] = {0x08,0x07,0x06,0x05};
    NetDWord netdwValue(nInput);

    Memory Dump:
    nInput[4] = {08 07 06 05}; netdwValue(nInput) = {05 06 07 08}
 */
inline NetDWord::NetDWord(const BYTE* pcHostValue)
{
m_netValue = htonl(_GET_DWORD_ALIGNP(pcHostValue));
}


/*Conversion constructor takes a 32-bit number in host byte order and stores it
  as a number in the network byte order. The network byte order is same as
  big-endian byte order.
  See also: htonl(), NETDWORD
 */
inline NetDWord::NetDWord(const uint32& dwHostValue)
{
m_netValue = htonl(dwHostValue);
}

//::~NetDWord()----------------------------------------------------------------
/*
 */
inline NetDWord::~NetDWord()
{
}

//::operator uint32()-----------------------------------------------------------
/*Type conversion operator converts a 32-bit number from network order to
  host byte order. Depending of architecture, host byte order could be
  big-endian, little-endian or PDP-endian.

  See also: ntohl(), NETDWORD, _ENDIAN_LITTLE_, _ENDIAN_BIG_

  Example:
      //Host byte order is little-endian.
    NetDWord netdwValue =  (NetDWord)0x0D0C0B0A;
    long lInput = netdwValue;

    Memory Dump:
    netdwValue =  (NetDWord)0x0D0C0B0A = {0D 0C 0B 0A}
    long lInput = {0A 0B 0C 0D}
 */
inline NetDWord::operator uint32() const
{
return ntohl(m_netValue);
}

//::operator BYTE*()-----------------------------------------------------------
/*Returns pointer to the internal data conatiner.
 */
inline NetDWord::operator BYTE*() const
{
return (BYTE*)(&m_netValue);
}


///////////////////////////////////////////////////////////////////////////////
#endif /* __cplusplus                                                        */

/* ///////////////////////////////////////////////////////////////////////// */
#endif /* _KNETBYTE_H_                                                       */
/*****************************************************************************
 * $Log:
 *  5    Biblioteka1.4         2004-07-07 17:46:33  Darko           sentry
 *  4    Biblioteka1.3         2002-04-09 13:24:01  Darko Kolakovic
 *  3    Biblioteka1.2         2002-03-07 17:08:30  Darko           Added pointer
 *       aligment macro
 *  2    Biblioteka1.1         2002-03-05 02:23:28  Darko           added operator
 *       BYTE*()
 *  1    Biblioteka1.0         2002-03-04 19:11:39  Darko
 * $
 *****************************************************************************/
