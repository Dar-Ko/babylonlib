/*$Workfile: TestEndian.cpp$: implementation file
  $Revision: 8$ $Date: 2004-10-05 14:05:29$
  $Author: Darko$

  Test machine architecture
  Copyright: CommonSoft Inc.
  May 2k1 D.Kolakovic
*/

// Group=Examples

#include "stdafx.h"

#include "KProgCst.inl" //IsLittleEndian()

union Conversion32
 {
 long   m_Long;
 short  m_Short[2];
 char   m_cData[8];
 };

tostream& operator<<(tostream& coutput, //[in] output stream
                     const Conversion32& c32Source //[in] value output
                    )
{
coutput << _T(" [ ");
for(int i = 0; i < sizeof(c32Source.m_Long); i++)
  {
  coutput << (int)(unsigned char)c32Source.m_cData[i] << _T(" ");
  }
coutput << _T("]");

return coutput;
}


//TestEndian()-----------------------------------------------------------------
/*Validate machine architecture.
 */
bool TestEndian()
{
std::_tcout << _T("\nTestEndian()") << std::endl;
bool bResult = true;

#ifdef _M_IX86 /*Intel x86 CPU has little endian archtecture */
  std::_tcout << _T("Intel x86 CPU.") << std::endl; 
#endif

  /*Desired architecture                 */
#if _ENDIAN_ORDER_ == _ENDIAN_LITTLE_ 
  std::_tcout << _T("Declared Little Endian architecture.") << std::endl; 
#endif
#if _ENDIAN_ORDER_ == _ENDIAN_BIG_
  std::_tcout << _T("Declared Big Endian architecture.") << std::endl; 
#endif
#if _ENDIAN_ORDER_ == _ENDIAN_PDP_
  std::_tcout << _T("Declared PDP Endian architecture.") << std::endl; 
#endif
 
  //Test architecture
if (IsLittleEndian())
  std::_tcout << _T("Found Little Endian architecture OK.") << std::endl;   
else
  {
  std::_tcout << _T("Found Big Endian architecture.") << std::endl;
  #ifdef _M_IX86 /*Intel x86 CPU has little endian archtecture */
    bResult = false;
  #endif
  #if _ENDIAN_ORDER_ == _ENDIAN_LITTLE_  /*Desired architecture              */
    bResult = false;
  #endif
  }

Conversion32 Test;
Test.m_Long = 0x01020304;
std::_tcout << _T("Order of bytes in 32-bit integer: ") << Test << std::endl;
std::_tcout << _T("============================") << std::endl;

return bResult;
}

///////////////////////////////////////////////////////////////////////////////
