/*$RCSfile: KBinStream.h,v $: header file
  $Revision: 1.1 $ $Date: 2011/04/28 22:00:14 $
  $Author: ddarko $

  Write binary value to the stream
  Copyright: CommonSoft Inc.
  2011-24-07 Darko Kolakovic
*/

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

#ifndef _KBINSTREAM_H_
    //$RCSfile: KBinStream.h,v $ sentry
  #define _KBINSTREAM_H_

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

//-----------------------------------------------------------------------------
/*Writes the binary value to output stream.

  Return: the output stream

  Example:
    #include "KBinStream.h"
    ...
    uint32 nValue = 0xD2E31200;

    std::_tcout << _T("value = "); 
    BintoStream<uint32>(std::_tcout, nValue) << std::endl;
 */
template <typename T>
tostream& BintoStream(tostream& outStream, //[out] output stream
                     T value    //[in] value to write
                     )
{
#ifndef CHAR_BIT
  const T CHAR_BIT = 8 ; //Number of bits in a byte
#endif
int iCount = CHAR_BIT * sizeof(value);
while (--iCount >= 0)
  {
  outStream << (((1 << iCount) & value) != 0);
  }

return outStream;
}

///////////////////////////////////////////////////////////////////////////////
#endif  //_KBINSTREAM_H_

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: KBinStream.h,v $
 * Revision 1.1  2011/04/28 22:00:14  ddarko
 * Created
 *
 *****************************************************************************/
