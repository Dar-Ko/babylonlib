/*$Workfile: KBoolStream.h$: header file
  $Revision: 3$ $Date: 2007-03-10 19:54:00$
  $Author: Darko$

  Write bool literal to the stream
  Copyright: CommonSoft Inc.
  2004-06-07 Darko Kolakovic
*/

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

#ifndef _KBOOLSTREAM_H_
    //$Workfile: KBoolStream.h$ sentry
  #define _KBOOLSTREAM_H_

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
//Class used to convert bool type to its literal presentation.
//
//Example:
//    #include "STL/KBoolStream.h" //tbool class
//    ...
//    int i = 100;
//    bool bRes = (i == 0);
//    std::_tcout << _T("i is not equal to null: ") << !(tbool)bRes << std::endl;
//    ...
//    Output: i is not equal to null: T
class tbool
{
public:
  tbool() :m_bValue(false) {};
//  tbool(const bool& bValue) :m_bValue(bValue) {};
  tbool(bool bValue) :m_bValue(bValue) {};
  bool m_bValue;
  operator bool() const
    {
    return m_bValue;
    };
  tbool operator !() const
    {
    return tbool(!m_bValue);
    };
  tbool& operator= (const bool& bValue)
    {
    m_bValue = bValue;
    };
};

///////////////////////////////////////////////////////////////////////////////
//Operator overloads

//-----------------------------------------------------------------------------
/*Writes the boolean value to output stream. Logical true is represented with
  symbol T and logical false with symbol F:

      true  T
      false F

  Example:
    #include "STL/KBoolStream.h" //tbool class
    ...
    int i = 100;
    bool bRes = (i != 0);
    std::_tcout << _T("i is equal to null: ") << (tbool)bRes << std::endl;
    ...
    Output: i is equal to null: F
 */
inline tostream& operator<<(tostream& outStream, //[out] output stream
                     const tbool bValue    //[in] value to write
                     )
{
return (outStream << (bValue ? _T('T') : _T('F')));
}

///////////////////////////////////////////////////////////////////////////////
#endif  //_KBOOLSTREAM_H_

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2004-10-01 21:51:53  Darko
 * $
 *****************************************************************************/
