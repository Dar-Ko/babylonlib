/*$Workfile: KHexStream.h$: header file
  $Revision: 1$ $Date: 2007-03-10 19:54:26$
  $Author: Darko$

  Write hexadecimal number to the stream
  Copyright: CommonSoft Inc.
  2007-03-10 Darko Kolakovic
*/

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

#ifndef _KHEXSTREAM_H_
    //$Workfile: KHexStream.h$ sentry
  #define _KHEXSTREAM_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#ifdef _DEBUG
  #ifndef _STLP_DEBUG
    #define _STLP_DEBUG 1    //Debug STLPort library
  #endif
#else
  #ifdef _STLP_DEBUG
    #undef _STLP_DEBUG
  #endif
#endif

#include "KOStream.h" //ostream template

///////////////////////////////////////////////////////////////////////////////
/*Class used to convert an integer type to its hexadecimal presentation.

  Example:
      #include "STL/KHexStream.h" //thex class
    ...
     int i = 100;
     std::_tcout << _T("i = ") << (thex)i << std::endl;
    ...
     Output: i = 0x00000064
 */
class thex
{
public:
  thex() : m_nValue(false) {};
  thex(unsigned int nValue) :m_nValue(nValue) {};
  unsigned int m_nValue;
  operator unsigned int() const
    {
    return m_nValue;
    };
  operator int() const
    {
    return int(m_nValue);
    };
  thex& operator= (const unsigned int& nValue)
    {
    m_nValue = nValue;
    };
  thex& operator= (const int& iValue)
    {
    m_nValue = unsigned int(iValue);
    };
};

///////////////////////////////////////////////////////////////////////////////
//Operator overloads

//-----------------------------------------------------------------------------
/*Writes the hexadecimal number to output stream.

  Example:
      #include "STL/KHexStream.h" //thex class
    ...
     int i = 100;
     std::_tcout << _T("i = ") << (thex)i << std::endl;
    ...
     Output: i = 0x00000064
 */
inline tostream& operator<<(tostream& outStream, //[out] output stream
                            const thex nValue     //[in] value to write
                           )
{
outStream.unsetf(tostream::dec);
outStream.setf(tostream::hex | tostream::uppercase);
return (outStream
        << _T("0x")
        << std::setfill(_T('0'))
        << std::setw(8) //TODO: Get int width
        << nValue.m_nValue);
}

///////////////////////////////////////////////////////////////////////////////
#endif  //_KHEXSTREAM_H_

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2007-03-10 19:54:26  Darko           
 * $
 *****************************************************************************/
