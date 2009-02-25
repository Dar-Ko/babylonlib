/*$Workfile: KIpAddress.h$: header file
  $Revision: 1.1 $ $Date: 2009/02/25 19:20:38 $
  $Author: ddarko $

  IP address type definitions
  Copyright: CommonSoft Inc
  Mar. 2k2 Darko Kolakovic
 */

#ifndef _KIPADDRESS_H_
    /*Workfile: $ sentry*/
  #define _KIPADDRESS_H_

#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
  #pragma message ("   #include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
/*
 */
struct tagIPv4Address
{
union
  {
  uint8_t  m_cOctet[4]; /**/
  uint32_t m_nAddress;  /**/
  } IpAddress;
};

typedef struct tagIPv4Address IPv4Address;
#define IPv4Address IPv4Address

///////////////////////////////////////////////////////////////////////////////
/*
 */
struct tagIPv6Address
{
union
  {
  uint8_t  m_cOctet[16];   /**/
  uint32_t m_nAddress[4];  /**/
  uint64_t m_nAddres64[2]; /**/
  } IpAddress;
};

typedef struct tagIPv6Address IPv6Address;
#define IPv6Address IPv6Address

//TODO: !todo: CIPv4Address
#pragma TODO ( CIPv4Address)

///////////////////////////////////////////////////////////////////////////////
#endif /* _KIPADDRESS_H_                                                     */
/******************************************************************************
 * $Log: KIpAddress.h,v $
 * Revision 1.1  2009/02/25 19:20:38  ddarko
 * Copied from local repository
 *
 *  2    Biblioteka1.1         2002-05-06 15:20:56  Darko Kolakovic
 *  1    Biblioteka1.0         2002-04-09 13:18:35  Darko Kolakovic
 ******************************************************************************/
