/*$RCSfile: KIpAddress.h,v $: header file
  $Revision: 1.3 $ $Date: 2009/05/11 14:29:50 $
  $Author: ddarko $

  IP address type definitions
  Copyright: CommonSoft Inc
  Mar. 2k2 Darko Kolakovic
 */

#ifndef _KIPADDRESS_H_
    /*RCSfile: $ sentry*/
  #define _KIPADDRESS_H_

#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
  #pragma message ("   #include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
/*Internet Protocol version 4 (IPv4) address.
 */
struct tagIPv4Address
{
union Ipv4
  {
  uint8_t  m_cOctet[4]; /**/
  uint32_t m_nAddress;  /**/
  } Ip; //IPv4 address
};

typedef struct tagIPv4Address IPv4Address;
#define IPv4Address IPv4Address

///////////////////////////////////////////////////////////////////////////////
/*Internet Protocol version 6 (IPv6) address.
  IPv6 addresses are typically composed of two logical parts:
  a 64-bit network (subnetwork) prefix and a 64-bit host part.
 */
struct tagIPv6Address
{
union Ipv6
  {
  uint8_t  m_cOctet[16];   /**/
  uint32_t m_nAddress[4];  /**/
  uint64_t m_lAddres4[2]; /**/
  } Ip; //IPv6 address
};

typedef struct tagIPv6Address IPv6Address;
#define IPv6Address IPv6Address

#ifdef __cplusplus
#pragma TODO ( CIPv4Address)

///////////////////////////////////////////////////////////////////////////////
/*
 */
class CIPv4Address : public IPv4Address
{
public:
    CIPv4Address();
    CIPv4Address(LPCTSTR szIpAddress);
    CIPv4Address(const IPv4Address& ipAddress);
    CIPv4Address(const uint32_t nIpAddress);
    CIPv4Address(const uint8_t cOctet0, const uint8_t cOctet1,
                 const uint8_t cOctet2, const uint8_t cOctet3);
    virtual ~CIPv4Address();
public:
   void Ipv4toA(LPCTSTR szIpAddress);
   CString toString();
}

///////////////////////////////////////////////////////////////////////////////
// Inlines

//------------------------------------------------------------------------------
/*
 */
inline
CIPv4Address::CIPv4Address()
{
m_nAddress = 0;
};

inline
CIPv4Address::CIPv4Address(LPCTSTR szIpAddress //[in]
                          )
{
if (szIpAddress == NULL) || szIpAddress[0] == _T('\0'))
  m_nAddress = 0;
else
   Ipv4toA(szIpAddress);
};

inline
CIPv4Address::CIPv4Address(const IPv4Address& ipAddress  //[in]
                          )
{
m_nAddress = ipAddress.m_nAddress;
};

inline
CIPv4Address::CIPv4Address(const uint32_t nIpAddress //[in]
                          )
{
m_nAddress = htonl(nIpAddress);
};

inline
CIPv4Address::CIPv4Address(const uint8_t cOctet0, //[in]
                           const uint8_t cOctet1, //[in]
                           const uint8_t cOctet2, //[in]
                           const uint8_t cOctet3  //[in]
                          )
{
m_cOctet[0] = cOctet0;
m_cOctet[1] = cOctet1;
m_cOctet[2] = cOctet2;
m_cOctet[3] = cOctet3;
};

//------------------------------------------------------------------------------
/*
 */
inline
CIPv4Address::~CIPv4Address()
{
};

//------------------------------------------------------------------------------
/*
 */
CString CIPv4Address::toString()
{
CString strResult("");
strResult=inet_ntoa(addr);
return strResult;
};

//------------------------------------------------------------------------------
/*
 */
inline
void CIPv4Address::Ipv4toA(LPCTSTR szIpAddress //[in]
                                  )
{
m_nAddress = ntohl(inet_addr(szIpAddress));
};

#endif /*__cplusplus*/
///////////////////////////////////////////////////////////////////////////////
#endif /* _KIPADDRESS_H_                                                     */
/*****************************************************************************
 * $Log:
 *  2    Biblioteka1.1         2002-05-06 15:20:56  Darko Kolakovic
 *  1    Biblioteka1.0         2002-04-09 13:18:35  Darko Kolakovic
 * $
 *****************************************************************************/

//////////////////////////////////////////////////////////////////////////////////
//
//
//   File : IPAddress.h
//
//   Created : 12-Nov-99
//   By : Patrick McDaniel
//
//   Description : This class defines an (abstract and immutable)
//                 IPAddress object.
//
//   *** Change History ***
//
//   12-Nov-99 Created File : DPM
//
//////////////////////////////////////////////////////////////////////////////////

// *** Include Files ***

// Project Include Files
#include <String.h>

// *** Definitions ***
#define ANY_IPADDRESS (unsigned long)0x0
#define ANY_IPPORT    (unsigned short)0x0
#define A_LOCALHOST     "localhost"

// Class Definition IPAddress
class CIPv4Address : public Listable {

  public: // Public Interface

    //
    // Constructors and Destructors

    // Hostname (or dot notation) Constructor
    CIPv4Address( String & hn, unsigned short pt )
      : hostname( hn ),
        address( 0 ),
        port( pt )
    {
    }

    // Numeric Address Constructor
    CIPv4Address( unsigned long ad, unsigned short pt )
      : address( ad ),
        port( pt )
    {
    }

    // Copy Constructor
    CIPv4Address( CIPv4Address & ip )
      : hostname( ip.hostname ),
        address( ip.address ),
        port( ip.port )
    {
    }

    // Destructor
    virtual ~CIPv4Address( void )
    {
    }

    //
    // Access Methods

    // Return the hostname associated with this address
    virtual const String & Hostname( void ) const
    {
        return( hostname );
    }

    // Return the numeric address
    virtual unsigned long Address( void ) const
    {
        return( address );
    }

    // Return the port number
    virtual unsigned short Port( void ) const
    {
        return( port );
    }

    //
    // Virtual Functions

    virtual Boolean IsMulticastAddress( void ) const = 0;
      // Is this a multicast address?

    virtual Boolean IsValidAddress( void ) const  = 0;
      // Check the validity of address (to connect to)

    virtual const char * HostnameString( String & str ) const = 0;
      // Create a human readable string containing the hostname.

    virtual const char * AddressString( String & str ) const = 0;
      // Create a human readable string containing the address.

    virtual const void * GetInternalStruct( void ) const = 0;
      // Return the internal (structure) used for IP address.

    virtual void FromInternalStruct( void *ad ) = 0;
      // Set address from platform specific structure.

    //
    // Listable Functions

    // Get a hash value of the object
    virtual unsigned short hashValue( void )
    {
        return( address );
    }

    // Compare this object to one like it
    // Returns : < 0 if local less than object
    //           = 0 if local equal to object
    //           > 0 if local greater than object
    // NOTE: Just compares the pointers
    virtual int compare( Listable *obj )
    {
       return( address - ((CIPv4Address *)obj)->address );
    }

    // This object compares a listable value/identifier to the local
    // object.
    // Returns : < 0 if local less than object
    //           = 0 if local equal to object
    //           > 0 if local greater than object
    virtual int compareValue( void *val )
    {
       return( address - *(unsigned long *)val );
    }

    //
    // Member Methods

    //
    // Static Member Methods (FACTORIES)

    static CIPv4Address * IPAddressFactory( String hn, unsigned pt,
                                         Boolean res = FALSE );
      // Factory for IP addresses (by hostname)

    static CIPv4Address * IPAddressFactory( unsigned long ad, unsigned pt,
                                         Boolean res = FALSE );
      // Factory for IP addresses (by address)

    static CIPv4Address * IPAddressFactory( CIPv4Address & ip, Boolean res = FALSE );
      // Factory for IP addresses (by copy constructor)

    //
    // (Static) Local address methods

    static String & GetLocalHostname( String & ref );
      // Get the local hostname

    static unsigned long GetLocalAddress( void );
      // Get the local address (in unsigned long format)

  protected: // Protected Interface

    // Set the hostname
    void setHostname( char *hname )
    {
        hostname = hname;
    }

    // Set the address
    void setAddress( unsigned long ad )
    {
        address = ad;
    }

    // Set the port
    void setPort( unsigned short pt )
    {
        port = pt;
    }

  private: // Private Interface and Data

    //
    // Class Attributes

    String hostname;
      // This is the hostname associated with the address.

    unsigned long address;
      // This is the (network byte ordered) number associated with the
      // address.

    unsigned short port;
      // This is the port associated with the address.

};
// End Class Definition IPAddress

#endif
//////////////////////////////////////////////////////////////////////////////////
//
//
//   File : IPAddress.cpp
//
//   Created : 12-Nov-99
//   By : Patrick McDaniel
//
//   Description : (See IPAddress.h for class description)
//
//   *** Change History ***
//
//   12-Nov-99 Created File : DPM
//
//////////////////////////////////////////////////////////////////////////////////

// Include Files

// Project Include Files
#include <IPAddress.h>
#include <UnixIPAddress.h>

// Definitions

//
// Static Member Methods

//////////////////////////////////////////////////////////////////////////////////
//
// Method       : IPAddress::IPAddressFactory
// Description  : Factory for IP addresses (by hostname)
//
// Inputs       : hn - hostname
//                pt - port
// Outputs      : a platform specific IP address object

CIPv4Address * CIPv4Address::IPAddressFactory( String hn, unsigned pt, Boolean res )
{
#ifdef UNIX
    return( new UnixIPAddress( hn, pt, res ) );
#endif
}

//////////////////////////////////////////////////////////////////////////////////
//
// Method       : IPAddress::IPAddressFactory
// Description  : Factory for IP addresses (by address)
//
// Inputs       : ad - address
//                pt - port
// Outputs      : a platform specific IP address object

CIPv4Address * CIPv4Address::IPAddressFactory( unsigned long ad, unsigned pt,
                                         Boolean res )
{
#ifdef UNIX
    return( new UnixIPAddress( ad, pt, res ) );
#endif
}

//////////////////////////////////////////////////////////////////////////////////
//
// Method       : IPAddress::IPAddressFactory
// Description  : Factory for IP addresses (by copy constructor)
//
// Inputs       : ip - address to copy
// Outputs      : a platform specific IP address object

CIPv4Address * CIPv4Address::IPAddressFactory( CIPv4Address & ip, Boolean res )
{
#ifdef UNIX
    return( new UnixIPAddress( ip, res ) );
#endif
}

//
// (Static) Local address methods

//////////////////////////////////////////////////////////////////////////////////
//
// Method       : CIPv4Address::GetLocalHostname
// Description  : Get the local hostname
//
// Inputs       : ref - place to put hostname
// Outputs      : string containing hostname

String & CIPv4Address::GetLocalHostname( String & ref )
{
#ifdef UNIX
    return( UnixIPAddress::GetLocalHostname(ref) );
#endif
}

//////////////////////////////////////////////////////////////////////////////////
//
// Method       : CIPv4Address::GetLocalAddress
// Description  : Get the local address (in unsigned long format)
//
// Inputs       : none
// Outputs      : the address, or -1 if failure

unsigned long CIPv4Address::GetLocalAddress( void )
{
#ifdef UNIX
    return( UnixIPAddress::GetLocalAddress() );
#endif
}



//////////////////////////////////////////////////////////////////////////////
//
// IPMask.h : A class to represent an IP mask. A mask consists of parts of
//				an IP address and wild card characters.
//				A mask has the following parts:
//					W.X.Y.Z
//				Where W, X, Y and Z can either be numbers from 0 to 254 or
//				*.
//

#if !defined (_IPMask_h_)
#define _IPMask_h_

class IPMask
{
public:
	IPMask();
	IPMask(const char *inMask, const char *inMaskName = NULL);
	~IPMask();

	bool			IsValid(void) { return (mIsValid); }
	void			SetMask(const char *inMask, const char *inMaskName = NULL);
	const char		*GetName(void) { return (mName); }

	bool			IsMoreSpecific(IPMask &inMask);
	bool			WPartIsWild(void) { return (mWPartIsWild); }
	unsigned char	WPart(void) { return (mWPart); }
	bool			XPartIsWild(void) { return (mXPartIsWild); }
	unsigned char	XPart(void) { return (mXPart); }
	bool			YPartIsWild(void) { return (mYPartIsWild); }
	unsigned char	YPart(void) { return (mYPart); }
	bool			ZPartIsWild(void) { return (mZPartIsWild); }
	unsigned char	ZPart(void) { return (mZPart); }

protected:
	void			Reset(void);
	bool			SetWPart(const char *inAddr);
	bool			SetXPart(const char *inAddr);
	bool			SetYPart(const char *inAddr);
	bool			SetZPart(const char *inAddr);
	bool			GetPart(const char *inAddr, int inPartNum,
						unsigned char *inPartPtr, bool *inPartWildPtr);

	char			*mName;
	bool			mIsValid;
	unsigned char	mWPart;
	bool			mWPartIsWild;
	unsigned char	mXPart;
	bool			mXPartIsWild;
	unsigned char	mYPart;
	bool			mYPartIsWild;
	unsigned char	mZPart;
	bool			mZPartIsWild;
};

#endif // _IPMask_h_
//////////////////////////////////////////////////////////////////////////////
//
// IPMask.cpp :
//

#include "stdafx.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "IPMask.h"


IPMask::IPMask()
{
	Reset();
}

IPMask::IPMask(const char *inMask, const char *inName /* = NULL */)
{
	Reset();

	SetMask(inMask, inName);
}

IPMask::~IPMask()
{
	if (mName != NULL)
		free(mName);
}

void IPMask::SetMask(const char *inMask, const char *inName /* = NULL */)
{
	if (inMask == NULL)
		return;

	if (inName != NULL)
	{
		int		nameLen = strlen(inName);
		mName = (char *) malloc(nameLen + 1);
		strcpy(mName, inName);
	}

	if (! SetWPart(inMask))
		return;

	if (! SetXPart(inMask))
		return;

	if (! SetYPart(inMask))
		return;

	if (! SetZPart(inMask))
		return;

	mIsValid = true;
}

bool IPMask::SetWPart(const char *inMask)
{
	if (GetPart(inMask, 1, &mWPart, &mWPartIsWild))
		return (true);
	return (false);
}

bool IPMask::SetXPart(const char *inMask)
{
	if (GetPart(inMask, 2, &mXPart, &mXPartIsWild))
		return (true);
	return (false);
}

bool IPMask::SetYPart(const char *inMask)
{
	if (GetPart(inMask, 3, &mYPart, &mYPartIsWild))
		return (true);
	return (false);
}

bool IPMask::SetZPart(const char *inMask)
{
	if (GetPart(inMask, 4, &mZPart, &mZPartIsWild))
			return (true);

	return (false);
}

bool IPMask::GetPart(const char *inAddr, int inPartNum,
						unsigned char *inPartPtr, bool *inPartWildPtr)
{
	if (inPartPtr == NULL)
		return (false);
	*inPartPtr = 0;
	if (inPartWildPtr == NULL)
		return (false);
	*inPartWildPtr = false;
	if (inAddr == NULL)
		return (false);
	if ((inPartNum < 0) || (inPartNum > 4))
		return (false);

	const char	*maskPtr = inAddr;
	char	addr[4];
	int		maskPos = 0;
	int		addrPos = 0;
	int		loops = inPartNum;

	while (loops > 1)
	{
		maskPtr = strstr(maskPtr, ".");
		if (maskPtr == NULL)
			return (false);
		maskPtr++;
		loops--;
	}

	if (*maskPtr == '*')
	{
		*inPartWildPtr = true;
		return (true);
	}

	while ((maskPtr[maskPos] != '\0')
		&& (maskPtr[maskPos] != '.')
		&& (addrPos < 3))
	{
		if (! isdigit(maskPtr[maskPos]))
			return (false);

		addr[addrPos++] = maskPtr[maskPos++];
	}
	addr[addrPos] = '\0';

	// now convert the characters
	*inPartPtr = atoi(addr);

	return (true);
}


void IPMask::Reset(void)
{
	mIsValid = false;
	mWPart = 0;
	mWPartIsWild = false;
	mXPart = 0;
	mXPartIsWild = false;
	mYPart = 0;
	mYPartIsWild = false;
	mZPart = 0;
	mZPartIsWild = false;
	mName = NULL;
}

bool IPMask::IsMoreSpecific(IPMask &inMask)
{
	if (! mIsValid)
		return (false);
	if (! inMask.IsValid())
		return (false);

	if (inMask.WPartIsWild())
	{
		if (! mWPartIsWild)
			return (true);
	}
	else
	{
		if (mWPartIsWild)
			return (false);
	}

	if (inMask.XPartIsWild())
	{
		if (! mXPartIsWild)
			return (true);
	}
	else
	{
		if (mXPartIsWild)
			return (false);
	}

	if (inMask.YPartIsWild())
	{
		if (! mYPartIsWild)
			return (true);
	}
	else
	{
		if (mYPartIsWild)
			return (false);
	}

	if (inMask.ZPartIsWild())
	{
		if (! mZPartIsWild)
			return (true);
	}
	else
	{
		if (mZPartIsWild)
			return (false);
	}

	return (false);
}
///////////////////////////////////////
//
// CIPv4Address.h :
//

#if !defined (_IPAddress_h_)
#define _IPAddress_h_

#include "IPMask.h"

class CIPv4Address
{
public:
	CIPv4Address();
	~CIPv4Address();

	bool			HaveAddress(void) { return (mHaveAddress); }
	bool			IsClassA(void);
	bool			IsClassB(void);
	bool			IsClassC(void);
	const char		*GetHostName(void);
	const char		*GetHostAddrStr(void);
	bool			MatchMask(IPMask &inMask);
	bool			MatchMask(const char *inMask);

protected:
	void			Reset(void);

	char			*mHostName;
	char			*mDottedStr;
	struct in_addr	mAddress;
	bool			mHaveAddress;
	bool			mInited;
};

#endif // _IPAddress_h_

//////////////////////////////////////////////////////////////////////////////
//
// CIPv4Address.cpp :
//

#include "stdafx.h"
#include <winsock.h>
#include <stdlib.h>
#include <string.h>

#include "CIPv4Address.h"
#include "IPMask.h"

/*
 $Log:
  2    Biblioteka1.1         2002-05-06 15:20:56  Darko Kolakovic
  1    Biblioteka1.0         2002-04-09 13:18:35  Darko Kolakovic
 $
 Revision 1.1  1999/11/18 14:43:13  chuck
 no message

*/

CIPv4Address::CIPv4Address()
{
	WSADATA		wsaData;
	int			err;

	Reset();

	err = WSAStartup(MAKEWORD(1, 1), &wsaData);
	if (err != 0)
		return;

	mInited = true;

	char	nameBuffer[256];
	int		nameLen;

	memset(nameBuffer, 0, sizeof (nameBuffer));
	nameLen = sizeof (nameBuffer);

	err = gethostname(nameBuffer, nameLen);
	if (err == 0)
	{
		// got the name, get the fully qualified one
		struct hostent	*hostEnt = NULL;

		hostEnt = gethostbyname(nameBuffer);
		if (hostEnt != NULL)
		{
			int			hostNameLen;

			hostNameLen = strlen(hostEnt->h_name);
			mHostName = (char *) malloc(hostNameLen + 1);
			strcpy(mHostName, hostEnt->h_name);

			mAddress.S_un.S_un_b.s_b1 = hostEnt->h_addr_list[0][0];
			mAddress.S_un.S_un_b.s_b2 = hostEnt->h_addr_list[0][1];
			mAddress.S_un.S_un_b.s_b3 = hostEnt->h_addr_list[0][2];
			mAddress.S_un.S_un_b.s_b4 = hostEnt->h_addr_list[0][3];

			char	*addrPtr = NULL;

			// get the dotted address string
			addrPtr = inet_ntoa(mAddress);
			if (addrPtr != NULL)
			{
				int		dottedStrLen;

				dottedStrLen = strlen(addrPtr);
				mDottedStr = (char *) malloc(dottedStrLen + 1);
				strcpy(mDottedStr, addrPtr);

				mHaveAddress = true;
			}
		}
	}
}

CIPv4Address::~CIPv4Address()
{
	if (mInited)
		WSACleanup();

	if (mHostName != NULL)
		free(mHostName);

	if (mDottedStr != NULL)
		free(mDottedStr);
}


void CIPv4Address::Reset(void)
{
	mInited = false;
	mHaveAddress = false;
	mHostName = NULL;
	mDottedStr = NULL;
	memset(&mAddress, 0, sizeof(struct in_addr));
}

bool CIPv4Address::IsClassA(void)
{
	if (mHaveAddress)
		if (mAddress.S_un.S_un_b.s_b1 <= 126)
			return (true);
	return (false);
}

bool CIPv4Address::IsClassB(void)
{
		if (mHaveAddress)
		if ((mAddress.S_un.S_un_b.s_b1 >= 128)
			&& (mAddress.S_un.S_un_b.s_b1 <= 191))
			return (true);
	return (false);
}

bool CIPv4Address::IsClassC(void)
{
		if (mHaveAddress)
		if ((mAddress.S_un.S_un_b.s_b1 >= 192)
			&& (mAddress.S_un.S_un_b.s_b1 <= 223))
			return (true);
	return (false);
}

const char *CIPv4Address::GetHostName(void)
{
	if (mHaveAddress)
		return (mHostName);
	return (NULL);
}

const char *CIPv4Address::GetHostAddrStr(void)
{
	if (mHaveAddress)
		return (mDottedStr);
	return (NULL);
}

bool CIPv4Address::MatchMask(IPMask &inMask)
{
	bool		retValue = false;

	if (inMask.IsValid())
	{
		if (inMask.WPartIsWild())
			return (true);
		if (mAddress.S_un.S_un_b.s_b1 != inMask.WPart())
			return (false);
		if (inMask.XPartIsWild())
			return (true);
		if (mAddress.S_un.S_un_b.s_b2 != inMask.XPart())
			return (false);
		if (inMask.YPartIsWild())
			return (true);
		if (mAddress.S_un.S_un_b.s_b3 != inMask.YPart())
			return (false);
		if (inMask.ZPartIsWild())
			return (true);
		if (mAddress.S_un.S_un_b.s_b4 == inMask.ZPart())
			return (true);
	}

	return (false);
}

bool CIPv4Address::MatchMask(const char *inMask)
{
	IPMask		ipMask(inMask);

	return (MatchMask(ipMask));
}



