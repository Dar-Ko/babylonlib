/*$Workfile: S:\_SrcPool\Cpp\KGuid.h$: header file
  $Revision: 3$ $Date: 2005-05-13 16:39:12$
  $Author: Darko Kolakovic$

  Globally Unique Identifier (GUID /UUID) definition
  Copyright: CommonSoft Inc
  <date> Darko Kolakovic
 */

#ifndef _KGUID_H_
    //$Workfile: S:\_SrcPool\Cpp\KGuid.h$ sentry
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
   */
  #define DEFINE_GUID(name, n32, a16, b16, a8, b8, c8, d8, e8, f8, g8, h8) \
     const GUID name = { (uint32_t)(n32), (uint16_t)(a16), (uint16_t)(b16), \
                         { a8, b8, c8, d8, e8, f8, g8, h8 } }

#endif /*DEFINE_GUID*/

///////////////////////////////////////////////////////////////////////////////
#if !defined(GUID) && !define(GUID_DEFINED)
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

/*Globally Unique Identifier (GUID). See also: tagUUID, tagGUID               */
typedef tagGUID  GUID;

  #define GUID GUID
  #define GUID_DEFINED GUID
#endif /*GUID*/

/*Pointer to Globally Unique Identifier (GUID). See also: tagGUID             */
typedef tagGUID* LPGUID;
typedef const tagGUID* LPCGUID;

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

/*Globally Unique Identifier (GUID). See also: tagGUID, tagUUID               */
typedef tagUUID  UUID;

/*UUID packing helper */
union _UUID
  {
  uint8_t  v[16];   /*decomposed UUID                */
  uint32_t l[4];    /*UUID packed as 32-bit integers */
  struct tagGUID a; /*unique number packed as GUID   */
  struct tagUUID b; /*unique number packed as UUID   */
  };

#ifdef __cplusplus
///////////////////////////////////////////////////////////////////////////////
/*CGuid description.
   TODO: implematation
 See also: tagGUID
 */
class CGuid: public _UUID
{
public:
  CGuid();
  CGuid(const CGuid& guidValue);
  CGuid(LPCTSTR szValue);

  virtual ~CGuid();

public:
  void Create();
  uint32_t Hash() const;
  bool IsNull() const;
public:
  CGuid& operator= (const CGuid& guidValue);
  bool   operator==(const Guid& guidValue) const;
  bool   operator!=(const Guid& guidValue) const;
public:
  virtual LPTSTR toString(LPTSTR szTarget);
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*Deafult constructor.
 */
inline CGuid::CGuid()
{
l[0] = 0;
l[1] = 0;
l[2] = 0;
l[3] = 0;
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
 */
inline CGuid::CGuid(LPCTSTR szValue //[in] value to convert
                  )
{
if ( (szValue != NULL) && (szValue[0] != _T('\0')) )
  {
  unsigned nTemp[sizeof(a.Data4)];

  _tscanf(szValue,
          _T("%08x-%04hx-%04hx-%02x%02x-%02x%02x%02x%02x%02x%02x"),
          &a.Data1,
          &a.Data2,
          &a.Data3,
          &nTemp[0], &nTemp[1], &nTemp[2], &nTemp[3],
          &nTemp[4], &nTemp[5], &nTemp[6], &nTemp[7]);
  int i = sizeof(a.Data4);
  while (--i > 0 )
    {
    ASSERT((i < 8) && (i >= 0));
    a.Data4[i] = (uint8_t)nTemp.a.Data4[i];
    }

  }
}

//-----------------------------------------------------------------------------
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
  a.Data1 = (uint_32)_ttoi(strTemp, 16);
  i += 10;
  strTemp =  strValue.mid(i, i+4);
  a.Data2 = (uint_16)_ttoi(strTemp, 16);
  i += 5;
  strTemp =  strValue.mid(i, i+4);
  a.Data3 = (uint_16)_ttoi(strTemp, 16);
  i += 5;

  strTemp =  strValue.mid(i, i+2);
  a.Data4[0] = (uint_8)_ttoi(strTemp, 16);
  i += 2;
  strTemp =  strValue.mid(i, i+2);
  a.Data4[1] = (uint_8)_ttoi(strTemp, 16);
  i += 3;

  int j = 2;
  while ( j < sizeof(a.Data4))
    {
    strTemp =  strValue.mid(i, i+2);
    a.Data4[j] = (uint_8)_ttoi(strTemp, 16);
    i += 2;
    }
  }
else
  {
  l[0] = 0;
  l[1] = 0;
  l[2] = 0;
  l[3] = 0;
  }
}

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
  l[0] = guidValue.l[0];
  l[1] = guidValue.l[1];
  l[2] = guidValue.l[2];
  l[3] = guidValue.l[3];
  }
return *this;
}

//-----------------------------------------------------------------------------
/*
 */
inline bool CGuid::operator==(const CGuid& guidValue //[in] value to compare
                              )
{
if (this != &guidValue)
  {
  //Note: comapring byte by byte to avoid network endian issues
  int i = sizeof(_UUID);
  while (--i > 0 )
    {
    if (v[i] != guidValue.v[i])
      return false;
    }
  }
return true;
}

//-----------------------------------------------------------------------------
/*
 */
inline bool CGuid::operator!=(const CGuid& guidValue //[in] value to compare
                              )
{
return !(*this == guidValue);
}

//-----------------------------------------------------------------------------
/*Calculates hash value of larger UUID number.
  A hash value is a numeric value of a fixed length that uniquely identifies
  data.

  Returns: 32-bit hash value based on generated UUID.
 */
inline uint32_t CGuid::Hash() const
{

return (l[0] + l[1] + l[2] + l[3]);
}

//-----------------------------------------------------------------------------
/*Validates if UUID is equal to {00000000-0000-0000-0000-000000000000}.

  Returns: true if this is the null UUID; if not, return s false;
 */
bool CGuid::IsNull() const
{
return (l[0] == 0 && l[1] == 0 && l[2] == 0 && l[3] == 0 );
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
/*
 */
inline std::ostream& operator<<(std::ostream& out,
                                const GUID& guidValue
                               )
{
std::out << guidValue.toString();
return std::out;
}

//-----------------------------------------------------------------------------
/*
 */
inline std::string &operator std::string(const GUID& guidValue
                                )
{
std::stringstream stream;
stream << std::hex << std::setfill('0') << std::uppercase
       << '{'
       << std::setw(8) << guidValue.Data1 <<'-'
       << std::setw(4) << guidValue.Data2 <<'-'
       << std::setw(4) << guidValue.Data3 <<'-'
       << std::setw(2) << static_cast<int>(guidValue.Data4[0])
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
}

//-----------------------------------------------------------------------------
/*
 */
inline GUID& GetGuid(GUID& guidRes, const std::string& strGuid)
{
memset(&guidRes,0,sizeof(guidRes));

std::stringstream buffer;
ulong nTemp;

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


  In Windows NT 4.0, Windows 95, DCOM release, and Windows 98, UuidCreate()
  generates UUID based on an ethernet/token ring (IEEE 802.x) MAC address.
  In Windows XP/2000, the UuidCreate() function generates a UUID that cannot be
  traced to the ethernet/token ring address of the computer on which it was
  generated.
 */
inline void CGuid::Create()
{
#if defined(_WIN32)
  UuidCreate((UUID*) &b);

#elif defined(_LINUX)
  //Required libuuid lib
  uuid_generate((uuid_t*)&v); //Accesing byte array to store new UUID
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
 returns a unique value – no other invocation, on the same or any other system
 (networked or not), should return the same value.


 */
GUID& CreateUuid(GUID& guid)
{
GUID guid;
if (CoCreateGuid( &guid ) == S_OK)
  return guid;

return 0;
}

#endif
