/*$Workfile: H:\_SrcPool\Cpp\Samples\Numeric\TestSwap.cpp$: implementation file
  $Revision: 3$ $Date: 8/3/02 7:27:52 PM$
  $Author: Darko$

  Test byte flipping
  Copyright: CommonSoft Inc.
  May 2k1 D.Kolakovic
*/
// Group=Examples

#include <iostream>
#include <IOManip.h>
#include "KTrace.h"    //ASSERT macro
#include "KTypedef.h"  //DWORD typedef
#include "KSwpByte.h" 
#include "KSwpByteOrder.h"  //TSwapByteOrder
#include "KSwpElements.h"

union Conversion
 {
 char   m_Char;
 short  m_Short;
 long   m_Long;
 float  m_Float;
 double m_Double;
 char   m_cData[8];
 };

class TestArray
  {
  public:
    char m_cValue[45];
  };

//TestByteSwap()---------------------------------------------------------------
/*Test reversing order of bytes in primitive types or array elements.
 */
void TestByteSwap()
{
cout << "\nTestByteSwap()" << endl;
char szOutput[128];
szOutput[0] = '\0';

Conversion Temp;

 //Test reversing long
Temp.m_Long = 0xAABBCCDD;
sprintf(szOutput, "%X", Temp.m_Long);
cout << "long   = 0x" << szOutput;
long lResult = TSwapByteOrder<long>(Temp.m_Long);
sprintf(szOutput, "%X", lResult);
cout << " swapped = 0x" << szOutput << endl;

 //Test reversing double
Temp.m_Double = 3.1415;
cout << "double = " << Temp.m_Double << " [ ";
for(int i = 0; i < sizeof(double); i++)
  {
  cout << (int)(unsigned char)Temp.m_cData[i] << ' ';
  }
cout << ']' << endl;
Conversion Result;
Result.m_Double = TSwapByteOrder<double>(Temp.m_Double);
cout << "swapped= " << Result.m_Double << " [ ";
for(i = 0; i < sizeof(double); i++)
  {
  cout << (int)(unsigned char)Result.m_cData[i] << ' ';
  }
cout << ']' << endl;

 //Test reversing an array
sprintf(szOutput,"The quick brown fox jumps over the lazy dog.");
cout << szOutput << endl;
SwapElements(szOutput, strlen(szOutput));
cout << szOutput << endl;

 //Test reversing an array the template class
TestArray aResult;
sprintf(aResult.m_cValue,"The quick brown fox jumps over the lazy dog.");
cout << aResult.m_cValue << endl;
aResult = TSwapByteOrder<TestArray>(aResult);
for(i = 0; i < sizeof(TestArray); i++)
  {
  if (aResult.m_cValue[i] == '\0')
    cout << "[0]";
  else
    cout << aResult.m_cValue[i];
  }
cout << endl;
cout << endl << "======================" << endl;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: 
 *  3    Biblioteka1.2         8/3/02 7:27:52 PM    Darko           
 *  2    Biblioteka1.1         2/3/02 6:11:14 PM    Darko           
 *  1    Biblioteka1.0         7/26/01 9:31:37 PM   Darko           
 * $
 *****************************************************************************/
