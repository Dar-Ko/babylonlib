/*$Workfile: H:\_SrcPool\Cpp\Samples\Numeric\TestNetByteOrder.cpp$: implementation file
  $Revision: 3$ $Date: 8/3/02 7:27:41 PM$
  $Author: Darko$

  Test network byte order conversions
  Copyright: CommonSoft Inc.
  Mar 2k2 D.Kolakovic
*/
// Group=Examples

#include <IOStream>
#include <IOManip.h>
#include "KTrace.h"    //ASSERT macro
#include "KTypedef.h"  //DWORD typedef
#include "KNetByte.h"  //NETDWORD typedef
#include "KProgCst.inl" //IsLittleEndian()

#ifdef WIN32
	//Ask the linker to search for the Ws2_32.lib library while linking.
  #pragma comment( lib, "ws2_32" )
#endif

//TestNetByteOrder()---------------------------------------------------------------
/*Test cobersion to and from network byte order.
 */
void TestNetByteOrder()
{
cout << "\nTestNetByteOrder()" << endl;
cout << "\nHost byte order is" 
     << (IsLittleEndian() ? "" : " other than")
	 << " little-endian." << endl;

char szOutput[128];
szOutput[0] = '\0';
NetWord netwValue;
short sInput;
int i;
cout << "Memory Dump:" << endl;

 //Test ordering a 16-bit value to network byte order
sInput = 0x0102;
cout << "short sInput = {";
for (i = 0; i < sizeof(WORD); i++)
  {
  sprintf(szOutput, "%02X ", *((BYTE*)&sInput + i) );
  cout << szOutput;
  }
cout << '}';
cout.flush();

 //Test conversion to network byte order
netwValue = sInput;

cout << "; netwValue = sInput = {";
for (i = 0; i < sizeof(NETWORD); i++)
  {
  sprintf(szOutput, "%02X ", *( (BYTE*)netwValue + i) );
  cout << szOutput;
  }
cout << '}' << endl;

 //Test ordering a 16-bit network value to host byte order
netwValue = (NetWord)0x0403;
cout << "netwValue = (NetWord)0x0403 = {";
for (i = 0; i < sizeof(NETWORD); i++)
  {
  sprintf(szOutput, "%02X ", *( (BYTE*)netwValue + i) );
  cout << szOutput;
  }
cout << '}' << endl;

sInput = netwValue;

cout << "short sInput = netwValue = {";
for (i = 0; i < sizeof(WORD); i++)
  {
  sprintf(szOutput, "%02X ", *((BYTE*)&sInput + i) );
  cout << szOutput;
  }
cout << '}' << endl;

 //Test intialization of a 32-bit network value
BYTE nInput[sizeof(NETDWORD)] = {0x08,0x07,0x06,0x05};
cout << "nInput[4] = {";
for (i = 0; i < sizeof(NETDWORD); i++)
  {
  sprintf(szOutput, "%02X ", *( nInput + i) );
  cout << szOutput;
  }
cout << '}';
cout.flush();

NetDWord netdwValue(nInput);

cout << "; netdwValue(nInput) = {";
for (i = 0; i < sizeof(NETDWORD); i++)
  {
  sprintf(szOutput, "%02X ", *( (BYTE*)netdwValue + i) );
  cout << szOutput;
  }
cout << '}' << endl;

netdwValue =  (NetDWord)0x0D0C0B0A;
cout << "netdwValue =  (NetDWord)0x0D0C0B0A = {";
for (i = 0; i < sizeof(NETDWORD); i++)
  {
  sprintf(szOutput, "%02X ", *( (BYTE*)netdwValue + i) );
  cout << szOutput;
  }
cout << '}' << endl;

netdwValue = (NetDWord*)nInput;

cout << "netdwValue =  (NetDWord*)nInput = {";
for (i = 0; i < sizeof(NETDWORD); i++)
  {
  sprintf(szOutput, "%02X ", *( (BYTE*)netdwValue + i) );
  cout << szOutput;
  }
cout << '}' << endl;

netdwValue = *(NetDWord*)nInput;

cout << "netdwValue =  *(NetDWord*)nInput = {";
for (i = 0; i < sizeof(NETDWORD); i++)
  {
  sprintf(szOutput, "%02X ", *( (BYTE*)netdwValue + i) );
  cout << szOutput;
  }
cout << '}' << endl;

 //Test ordering a 32-bit network value to host byte order
long lInput = netdwValue;

cout << "long lInput = netdwValue = {";
for (i = 0; i < sizeof(long); i++)
  {
  sprintf(szOutput, "%02X ", *( (BYTE*)&lInput + i ));
  cout << szOutput;
  }
cout << '}' << endl;
cout << "============================" << endl;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: 
 *  3    Biblioteka1.2         8/3/02 7:27:41 PM    Darko           
 *  2    Biblioteka1.1         3/5/02 2:23:47 AM    Darko           added operator
 *       BYTE*()
 *  1    Biblioteka1.0         3/4/02 7:11:57 PM    Darko           
 * $
 *****************************************************************************/
