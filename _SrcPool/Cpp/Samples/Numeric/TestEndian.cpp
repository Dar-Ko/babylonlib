/*$Workfile: H:\_SrcPool\Cpp\Samples\Numeric\TestEndian.cpp$: implementation file
  $Revision: 5$ $Date: 8/3/02 7:27:38 PM$
  $Author: Darko$

  Test machine architecture
  Copyright: CommonSoft Inc.
  May 2k1 D.Kolakovic
*/

// Group=Examples

#include <IOStream>
#include <IOManip.h>  //std::endl

#define BOOL bool
#include "KProgCst.inl" //IsLittleEndian()

union Conversion32
 {
 long   m_Long;
 short  m_Short[2];
 char   m_cData[8];
 };

ostream& operator<<(ostream& cOutput,     //[in] output stream
                    const Conversion32& c32Source //[in] value output
                    )
{
cOutput << " [ ";
for(int i = 0; i < sizeof(c32Source.m_Long); i++)
  {
  cOutput << (int)(unsigned char)c32Source.m_cData[i] << ' ';
  }
cOutput << ']';

return cOutput;
}


//TestEndian()-----------------------------------------------------------------
/*Validate machine architecture.
 */
bool TestEndian()
{
cout << "\nTestEndian()" << endl;
bool bResult = true;

#ifdef _M_IX86 /*Intel x86 CPU has little endian archtecture */
  cout << "Intel x86 CPU." << endl; 
#endif

  /*Desired architecture                 */
#if _ENDIAN_ORDER_ == _ENDIAN_LITTLE_ 
  cout << "Declared Little Endian architecture." << endl; 
#endif
#if _ENDIAN_ORDER_ == _ENDIAN_BIG_
  cout << "Declared Big Endian architecture." << endl; 
#endif
#if _ENDIAN_ORDER_ == _ENDIAN_PDP_
  cout << "Declared PDP Endian architecture." << endl; 
#endif
 
  //Test architecture
if (IsLittleEndian())
  cout << "Found Little Endian architecture OK." << endl;   
else
  {
  cout << "Found Big Endian architecture." << endl;
  #ifdef _M_IX86 /*Intel x86 CPU has little endian archtecture */
    bResult = false;
  #endif
  #if _ENDIAN_ORDER_ == _ENDIAN_LITTLE_  /*Desired architecture              */
    bResult = false;
  #endif
  }

Conversion32 Test;
Test.m_Long = 0x01020304;
cout << "Order of bytes in 32-bit integer: " << Test << endl;
cout << "============================" << endl;

return bResult;
}

///////////////////////////////////////////////////////////////////////////////
