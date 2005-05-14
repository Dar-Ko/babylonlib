/*$Workfile: KSwpByteOrder.h$: header file
  $Revision: 3$ $Date: 2004-07-07 17:49:30$
  $Author: Darko$

  Template to swap byte order of primitive types
  Copyright: CommonSoft Inc
  D. Kolakovic   May 2k1
 */

#ifndef _KSWPBYTEORDER_H_
    //$Workfile: KSwpByteOrder.h$ sentry
  #define _KSWPBYTEORDER_H_

#if _MSC_VER > 1000 /*Microsoft Visual Studio C/C++ compiler                 */
  #pragma once
#endif // _MSC_VER > 1000

///////////////////////////////////////////////////////////////////////////////
// The class swaps tailing bytes with bytes from the beginning of the object.
// The class is usually applied on primitive types to reverse byte order
// ("Little Endian" where the low byte is the first byte to "Big Endian" and
// vice versa).
//
// TODO: class copies data twice: in the constructor and in the type cast otperator.
//       Create a swap/flip method to avoid 2nd copying. D.K.
// Example:
//
//    #include <iostream>
//    #include <iomanip>
//    #include "KSwpByteOrder.h"  //TSwapByteOrder
//    void main()
//    {
//    long lTest = 0xAABBCCDD;
//    sprintf(szOutput, "%X", lTest);
//    cout << "long   = 0x" << szOutput;
//    long lResult = TSwapByteOrder<long>(lTest);
//    sprintf(szOutput, "%X", lResult);
//    cout << " swapped = 0x" << szOutput << endl;
//    }
template <class TYPE> class TSwapByteOrder
{
public:
  TSwapByteOrder(const TYPE& aValue);
  operator TYPE();

private:
   union Storage
     {
     TYPE Data;                //value as single object
     char cData[sizeof(TYPE)]; //value as byte array
     } m_Value; //Value of primitive
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//::TSwapByteOrder()-----------------------------------------------------------
/*Assignment constructor
 */
template<class TYPE>
inline TSwapByteOrder<TYPE>::TSwapByteOrder(const TYPE& aValue)
{
m_Value.Data=aValue;
}

//::operator TYPE()--------------------------------------------------------
/*Returns TYPE object with swapped byte order.
 */
template<class TYPE>
inline TSwapByteOrder<TYPE>::operator TYPE()
{
ReverseElements(m_Value.cData, sizeof(TYPE));
return m_Value.Data;
}

///////////////////////////////////////////////////////////////////////////////
// Template specialization

template< >
inline TSwapByteOrder<char>::operator char()
{
return m_Value.Data;
}

template< >
inline TSwapByteOrder<short>::operator short()
{
char cTemp[sizeof(short)];
cTemp[0] = m_Value.cData[1];
cTemp[1] = m_Value.cData[0];
return *((short*)&cTemp);
}

template< >
inline TSwapByteOrder<long>::operator long()
{
char cTemp[sizeof(long)];
cTemp[0] = m_Value.cData[3];
cTemp[1] = m_Value.cData[2];
cTemp[2] = m_Value.cData[1];
cTemp[3] = m_Value.cData[0];
return *((long*)&cTemp);
}

#ifdef _WIN32
  template< >
  inline TSwapByteOrder<int>::operator int()
    {
    return (int)(long)m_Value.Data;
    }
#endif

template< >
inline TSwapByteOrder<float>::operator float()
{
char cTemp[sizeof(float)];
cTemp[0] = m_Value.cData[3];
cTemp[1] = m_Value.cData[2];
cTemp[2] = m_Value.cData[1];
cTemp[3] = m_Value.cData[0];
return *((float*)&cTemp);
}

template< >
inline TSwapByteOrder<double>::operator double()
{
char cTemp[sizeof(double)];
cTemp[0] = m_Value.cData[7];
cTemp[1] = m_Value.cData[6];
cTemp[2] = m_Value.cData[5];
cTemp[3] = m_Value.cData[4];
cTemp[4] = m_Value.cData[3];
cTemp[5] = m_Value.cData[2];
cTemp[6] = m_Value.cData[1];
cTemp[7] = m_Value.cData[0];
return *((double*)&cTemp);
}

///////////////////////////////////////////////////////////////////////////////
#endif // _KSWPBYTEORDER_H_
/******************************************************************************
 * $Log:
 *  1    Biblioteka1.0         26/07/2001 9:31:33 PMDarko
 * $
 *****************************************************************************/
