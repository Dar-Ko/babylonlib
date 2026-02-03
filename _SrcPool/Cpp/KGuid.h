/*$Workfile: KGuid.h$: header file
  $Revision: 7$ $Date: 2007-05-18 17:25:30$
  $Author: Darko Kolakovic$

  Globally Unique Identifier (GUID /UUID) definition
  Copyright: CommonSoft Inc
  Jan 97 Darko Kolakovic
 */

#ifndef _KGUID_H_
    //$Workfile: KGuid.h$ sentry
  #define _KGUID_H_

#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
  #pragma message ("   #include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// Macros

#if !defined(DEFINE_GUID)
  /*Declares Globally Unique Identifier (GUID).

    Example:
        DEFINE_GUID(MyGuid, 0x340BC870, 0xA012, 37819,
                    0x20, 57, 132, 189, 0x73, 0x4D, 0x76, 0xE7);
        ...
        TRACE((LPCTSTR)GuidToStr(MyGuid);

        Output:
          {340BC870-A012-93BB-2039-84BD734D76E7}

    Note: Microsoft compilers are using C linkage to initialize GUID numbers.
    Also INITGUID have to be defined for one-time initialization (Microsoft
    specific).
   */
  #define DEFINE_GUID(name, n32, a16, b16, a8, b8, c8, d8, e8, f8, g8, h8) \
     const GUID name = { (uint32_t)(n32), (uint16_t)(a16), (uint16_t)(b16), \
                         { a8, b8, c8, d8, e8, f8, g8, h8 } }

#endif /*DEFINE_GUID*/

///////////////////////////////////////////////////////////////////////////////

#if !defined(GUID_DEFINED) && !defined(GUID)
  /*Globally Unique Identifier (GUID) is a pseudo-random number
    "statistically guaranteed" to be unique. A GUID represents a 128-bit value.
    Number of possible keys is 2^128 (3.4028e38). The possibility of the same
    number being generated twice is virtually zero.

    The GUID is a Microsoft implementation of an Universally Unique Identifier
    (UUID), specified by the Open Software Foundation (OSF).

    See also: <basetyps.h>
   */
  struct tagGUID
    {
    uint32_t Data1;
    uint16_t Data2;
    uint16_t Data3;
    uint8_t  Data4[8];
    };

  /*Globally Unique Identifier (GUID). See also: tagUUID, tagGUID             */
  typedef tagGUID  GUID;

  #define tagGUID tagGUID
  #define GUID GUID
  #define GUID_DEFINED GUID

#endif /*GUID*/

#if defined (tagGUID)
  /*Pointer to Globally Unique Identifier (GUID). See also: tagGUID           */
  typedef tagGUID* LPGUID;

  /*Constant pointer to Globally Unique Identifier (GUID). See also: tagGUID  */
  typedef const tagGUID* LPCGUID;
#endif /*tagGUID*/

#if defined(__LPCGUID_DEFINED__) 
   /*See: Microsoft wtypes.h or PlatformSDK\Include\Guiddef.h */
  #define LPCGUID LPCGUID
#endif
            
#ifndef LPCGUID
  typedef const LPGUID LPCGUID;
#endif

#if !defined(UUID_DEFINED) && !defined(UUID)
  /*Universally Unique Identifier (UUID) is a pseudo-random number
    "statistically guaranteed" to be unique. A UUID represents a 128-bit value.
    Number of possible keys is 2^128 (3.4028e38). The possibility of the same
    number being generated twice is virtually zero.

    See also: ISO/IEC 11578:1996 - "Information technology - Open Systems
    Interconnection - Remote Procedure Call (RPC)"; ISO/IEC FDIS 9834-8.
    */
  struct tagUUID
    {
    uint32_t Data1; //time_low. See Rfc
    uint16_t Data2; //time_mid
    uint16_t Data3; //time_hi_and_version
    uint16_t Data4; //clock_seq
    uint8_t  Data5[6];
    };

  /*Globally Unique Identifier (GUID). See also: tagGUID, tagUUID             */
  typedef tagUUID  UUID;

#endif /*UUID*/

/*UUID packing helper */
union _UUID
  {
  uint8_t  v[16];   /*decomposed UUID                */
  uint32_t l[4];    /*UUID packed as 32-bit integers */
  GUID a;           /*unique number packed as GUID   */
  UUID b;           /*unique number packed as UUID   */
  };

struct SUuidPack
  {
  union _UUID m_uPack;
  };

#ifdef __cplusplus
///////////////////////////////////////////////////////////////////////////////
/*CGuid description.
   TODO: implementation

 Note: No standard exist for binary representation of a UUID. Only string
 format is standardized.

 See also: tagGUID
 */
class CGuid: public SUuidPack
{
public:
  CGuid();
  CGuid(const CGuid& guidValue);
  CGuid(const UUID& uuidValue); //Note: Win32: UUID = GUID!
  CGuid(LPCTSTR szValue);

  virtual ~CGuid();

public:
  void Create();
  uint32_t Hash() const;
  bool IsNull() const;
public:
  CGuid& operator= (const CGuid& guidValue);
  bool   operator==(const CGuid& guidValue) const;
  bool   operator!=(const CGuid& guidValue) const;
  operator GUID() const;
  //operator UUID() const;

public:
  //virtual LPTSTR toString(LPTSTR szTarget);
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*Default constructor.
 */
inline CGuid::CGuid()
{
m_uPack.l[0] = 0;
m_uPack.l[1] = 0;
m_uPack.l[2] = 0;
m_uPack.l[3] = 0;
}

//-----------------------------------------------------------------------------
/*Copy constructor.
 */
inline CGuid::CGuid(const CGuid& guidValue //[in] value to copy
                  )
{
*this = guidValue;
}

//-----------------------------------------------------------------------------
/*
 * /TODO: if UUID <> GUID (Win32 UUID = GUID!)
inline CGuid::CGuid(const UUID& uuidValue //[in] value to convert
                  )
{
m_uPack.b.Data1 = uuidValue.Data1;
m_uPack.b.Data2 = uuidValue.Data2;
m_uPack.b.Data3 = uuidValue.Data3;
m_uPack.b.Data4 = uuidValue.Data4;
int j = 0;
while ( j < sizeof(m_uPack.b.Data5))
  {
  m_uPack.b.Data5[j] = uuidValue.Data5[j];
  j++;
  }
}*/

//TODO : Move to Win/32/KGuidWin.cpp (Note: Win32 UUID = GUID!)
inline CGuid::CGuid(const GUID& guidValue //[in] value to convert
                  )
{
m_uPack.a.Data1 = guidValue.Data1;
m_uPack.a.Data2 = guidValue.Data2;
m_uPack.a.Data3 = guidValue.Data3;
int j = 0;
while ( j < sizeof(m_uPack.a.Data4))
  {
  m_uPack.a.Data4[j] = guidValue.Data4[j];
  j++;
  }
}

//-----------------------------------------------------------------------------
#include <stdio.h> //scanf()
/*
 */
inline CGuid::CGuid(LPCTSTR szValue //[in] value to convert
                  )
{
if ( (szValue != NULL) && (szValue[0] != _T('\0')) )
  {
  unsigned nTemp[sizeof(m_uPack.a.Data4)];
  LPCTSTR szGuid;
  if (szValue[0] == _T('{'))
    szGuid = &szValue[1];
  else
    szGuid = szValue;

  if (_stscanf(szGuid,
          _T("%08x-%04hx-%04hx-%02x%02x-%02x%02x%02x%02x%02x%02x"),
          &m_uPack.a.Data1,
          &m_uPack.a.Data2,
          &m_uPack.a.Data3,
          &nTemp[0], &nTemp[1], &nTemp[2], &nTemp[3],
          &nTemp[4], &nTemp[5], &nTemp[6], &nTemp[7]) == 11 )
    {
    int i = sizeof(m_uPack.a.Data4);
    while (--i >= 0 )
      {
      ASSERT((i < 8) && (i >= 0));
      m_uPack.a.Data4[i] = (uint8_t)nTemp[i];
      }
    }
  else
    {
    ASSERT(false); //Input string is not parsed properly
    m_uPack.l[0] = 0;
    m_uPack.l[1] = 0;
    m_uPack.l[2] = 0;
    m_uPack.l[3] = 0;
    }

  }
}

//-----------------------------------------------------------------------------
#if defined (_AFX) //TODO: remove AFX::CString dependency
/*
 */
inline CGuid::CGuid(CString& strValue //[in] value to convert
                  )
{
if ( (!strValue.IsEmpty() )
  {
  int i = 0;
  if (strValue[0] = _T('{'))
    i++;
  CString strTemp =  strValue.mid(i, i+8);
  m_uPack.a.Data1 = (uint_32)_ttoi(strTemp, 16);
  i += 10;
  strTemp =  strValue.mid(i, i+4);
  m_uPack.a.Data2 = (uint_16)_ttoi(strTemp, 16);
  i += 5;
  strTemp =  strValue.mid(i, i+4);
  m_uPack.a.Data3 = (uint_16)_ttoi(strTemp, 16);
  i += 5;

  strTemp =  strValue.mid(i, i+2);
  m_uPack.a.Data4[0] = (uint_8)_ttoi(strTemp, 16);
  i += 2;
  strTemp =  strValue.mid(i, i+2);
  m_uPack.a.Data4[1] = (uint_8)_ttoi(strTemp, 16);
  i += 3;

  int j = 2;
  while ( j < sizeof(m_uPack.a.Data4))
    {
    strTemp =  strValue.mid(i, i+2);
    m_uPack.a.Data4[j] = (uint_8)_ttoi(strTemp, 16);
    i += 2;
    }
  }
else
  {
  m_uPack.l[0] = 0;
  m_uPack.l[1] = 0;
  m_uPack.l[2] = 0;
  m_uPack.l[3] = 0;
  }
}
#endif //_AFX

//-----------------------------------------------------------------------------
/*Destructor.
 */
inline CGuid::~CGuid()
{
}

//-----------------------------------------------------------------------------
/*
 */
inline CGuid& CGuid::operator=(const CGuid& guidValue //[in] value to assign
                              )
{
if (this != &guidValue)
  {
  m_uPack.l[0] = guidValue.m_uPack.l[0];
  m_uPack.l[1] = guidValue.m_uPack.l[1];
  m_uPack.l[2] = guidValue.m_uPack.l[2];
  m_uPack.l[3] = guidValue.m_uPack.l[3];
  }
return *this;
}

//-----------------------------------------------------------------------------
/*
 */
inline bool CGuid::operator==(const CGuid& guidValue //[in] value to compare
                              ) const
{
if (this != &guidValue)
  {
  //Note: comapring byte by byte to avoid network endian issues
  int i = sizeof(_UUID);
  while (--i > 0 )
    {
    if (m_uPack.v[i] != guidValue.m_uPack.v[i])
      return false;
    }
  }
return true;
}

//-----------------------------------------------------------------------------
/*
 */
inline bool CGuid::operator!=(const CGuid& guidValue //[in] value to compare
                              ) const
{
return !(*this == guidValue);
}

//-----------------------------------------------------------------------------
/*Converts this object to Globally Unique Identifier (GUID).

  Returns: Globally Unique Identifier (GUID).
 */
inline CGuid::operator GUID() const
{
return m_uPack.a;
}

//-----------------------------------------------------------------------------
/*Converts this object to Universally Unique Identifier (UUID).

  Returns: Universally Unique Identifier (UUID).
 * /
inline CGuid::operator UUID() const
{
return m_uPack.b;
}*/

//-----------------------------------------------------------------------------
/*Calculates hash value of larger UUID number.
  A hash value is a numeric value of a fixed length that uniquely identifies
  data.

  Returns: 32-bit hash value based on generated UUID.
 */
inline uint32_t CGuid::Hash() const
{
return (m_uPack.l[0] + m_uPack.l[1] + m_uPack.l[2] + m_uPack.l[3]);
}

//-----------------------------------------------------------------------------
/*Validates if UUID is equal to {00000000-0000-0000-0000-000000000000}.

  Returns: true if this is the null UUID; if not, return s false;
 */
inline bool CGuid::IsNull() const
{
return (m_uPack.l[0] == 0 &&
        m_uPack.l[1] == 0 &&
        m_uPack.l[2] == 0 &&
        m_uPack.l[3] == 0 );
}

///////////////////////////////////////////////////////////////////////////////
#if defined (_STL) || defined (_USE_STL)
//-----------------------------------------------------------------------------
/*
 */
inline std::ostream& operator<<(std::ostream& out,
                                const GUID& guidValue
                               )
{
extern CString GuidToStr( const UUID& iid );
out << GuidToStr(guidValue);
return out;
}

//-----------------------------------------------------------------------------
/*
 * /
inline CGuid::operator std::string(const GUID& guidValue
                           )
{
std::stringstream stream;
stream << std::hex << std::setfill('0') << std::uppercase
       << '{'
       << std::setw(8) << guidValue.Data1 <<'-'
       << std::setw(4) << guidValue.Data2 <<'-'
       << std::setw(4) << guidValue.Data3 <<'-'
       << std::setw(2) << static_cast<int>(guidValue.m_uPack.Data4[0])
       << std::setw(2) << static_cast<int>(guidValue.Data4[1])
       << '-'
       << std::setw(2) << static_cast<int>(guidValue.Data4[2])
       << std::setw(2) << static_cast<int>(guidValue.Data4[3])
       << std::setw(2) << static_cast<int>(guidValue.Data4[4])
       << std::setw(2) << static_cast<int>(guidValue.Data4[5])
       << std::setw(2) << static_cast<int>(guidValue.Data4[6])
       << std::setw(2) << static_cast<int>(guidValue.Data4[7])
       << '}';

  return stream.str();
}*/

//-----------------------------------------------------------------------------
#include <sstream>
/*
 */
inline GUID& GetGuid(GUID& guidRes, const std::string& strGuid)
{
memset(&guidRes,0,sizeof(guidRes));

std::stringstream buffer;
uint32_t nTemp;

buffer<<"0x"<<std::string(strGuid,1,8)<<'\n';
buffer>>std::hex>>guidRes.Data1;

buffer<<"0x"<<std::string(strGuid,10,4)<<'\n';
buffer>>std::hex>>guidRes.Data2;

buffer<<"0x"<<std::string(strGuid,15,4)<<'\n';
buffer>>std::hex>>guidRes.Data3;

buffer<<"0x"<<std::string(strGuid,20,2)<<'\n';
buffer>>std::hex>>nTemp;
guidRes.Data4[0]=nTemp;

buffer<<"0x"<<std::string(strGuid,22,2)<<'\n';
buffer>>std::hex>>nTemp;
guidRes.Data4[1]=nTemp;;

buffer<<"0x"<<std::string(strGuid,25,2)<<'\n';
buffer>>std::hex>>nTemp;
guidRes.Data4[2]=nTemp;

buffer<<"0x"<<std::string(strGuid,27,2)<<'\n';
buffer>>std::hex>>nTemp;
guidRes.Data4[3]=nTemp;

buffer<<"0x"<<std::string(strGuid,29,2)<<'\n';
buffer>>std::hex>>nTemp;
guidRes.Data4[4]=nTemp;

buffer<<"0x"<<std::string(strGuid,31,2)<<'\n';
buffer>>std::hex>>nTemp;
guidRes.Data4[5]=nTemp;

buffer<<"0x"<<std::string(strGuid,33,2)<<'\n';
buffer>>std::hex>>nTemp;
guidRes.Data4[6]=nTemp;

buffer<<"0x"<<std::string(strGuid,35,2)<<'\n';
buffer>>std::hex>>nTemp;
guidRes.Data4[7]=nTemp;
}
#endif //_STL

#endif //__cplusplus
///////////////////////////////////////////////////////////////////////////////
#endif  //_KGUID_H_
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2005-05-12 17:35:34  Darko Kolakovic
 * $
 *****************************************************************************/

#if defined(_WIN32)
  #include <rpc.h> //<rpcdce.h> Rpcrt4.lib.
  //#pragma comment(lib, "rpcrt4") !todo: check

#elif defined(_LINUX)
  #include <uuid.h> //<sys/uuid.h>
#endif

//-----------------------------------------------------------------------------
/*Creates a new UUID.


  Generators for versions 1,3,4 and 5 UUID's are provided.


  UUID version 4
The version 4 UUID is UUID based on random bytes. We fill the 128-bits with random bits (6 of the bits are correspondingly set to flag the version and variant of the UUID). No special configuration or implementation decisions are required to generate version 4 UUID's.

  UUID version 3
Version 3 UUIDs are initialized using a name, a namespace, and the MD5 hashing algorithm.

  UUID version 5
Version 5 UUIDs are initialized using a name, a namespace, and the SHA-1 hashing algorithm.

  UUID version 1
The version 1 UUID is a combination of node identifier (MAC address), timestamp and a random seed.

  In Windows NT 4.0, Windows 95, DCOM release, and Windows 98, UuidCreate()
  generates UUID based on an ethernet/token ring (IEEE 802.x) MAC address.
  In Windows XP/2000, the UuidCreate() function generates a UUID that cannot be
  traced to the ethernet/token ring address of the computer on which it was
  generated.
 */
inline void CGuid::Create()
{
#if defined(_WIN32)
  UuidCreate((UUID*) &m_uPack.b);

#elif defined(_LINUX)
  //Required libuuid lib
  uuid_generate((uuid_t*)&m_uPack.v); //Accessing byte array to store new UUID
#else

  {
  /*Generates a new UUID of based on EmbeddedPOSIX DCE Security with Random type.
    Uses srand() pseudo-random generator.
   */
    static const int iBitCount = sizeof(int)*8;
    static int i = 0;

    if ( !i )
      {
      int iLimit = RAND_MAX;
      do
        {
        ++i;
        } while ( (iLimit = iLimit >> 1) );
      srand( (UINT)((time_t)GetCurrentDateTime()) );
      rand(); //omit 1
      }

     //Fill data
    int j =  sizeof(_UUID) / sizeof(unsigned int);
    while ( j-- )
      {
      unsigned int randNumber = 0;
      for ( int filled = 0; filled < iBitCount; filled += i )
        randNumber |= rand() << filled;
      l[j] = randNumber;
      }

    Data4[0] = (Data4[0] & 0x3F) | 0x80;  //DCE version
    Data3 = (Data3 & 0x0FFF) | 0x4000;  //Random type

  }


#endif

}

#ifdef _WIN32
#include <objbase.h> //CoCreateGuid()
/*Creates a GUID, a unique 128-bit integer used for CLSIDs and interface identifiers.
  The CoCreateGuid function calls the RPC function UuidCreate, which creates a GUID,
  a globally unique 128-bit integer. Use the CoCreateGuid function when you need
  an absolutely unique number that you will use as a persistent identifier in
  a distributed environment.To a very high degree of certainty, this function
  returns a unique value � no other invocation, on the same or any other system
  (networked or not), should return the same value.

  Returns a GUID, a unique 128-bit integer or 0 in case of failure.
 */
inline GUID& CreateUuid(GUID& guid //[in/out] reference to the requested GUID
                       )
{
if (CoCreateGuid(&guid) != S_OK)
  {
  guid.Data1 = 0;
  guid.Data2 = 0;
  guid.Data3 = 0;
  guid.Data4[0] = 0;
  guid.Data4[1] = 0;
  guid.Data4[2] = 0;
  guid.Data4[3] = 0;
  guid.Data4[4] = 0;
  guid.Data4[5] = 0;
  guid.Data4[6] = 0;
  guid.Data4[7] = 0;
  }
return guid;
}

#endif //_WIN32
///////////////////////////////////////////////////////////////////////////////
/*$Log: $
 */
