/*$Workfile: TestNetByteOrder.cpp$: implementation file
  $Revision: 5$ $Date: 2004-10-05 13:05:31$
  $Author: Darko$

  Test network byte order conversions
  Copyright: CommonSoft Inc.
  Mar 2k2 D.Kolakovic
*/
// Group=Examples

#include "stdafx.h"
#include "KTrace.h"    //ASSERT macro
#include "KTypedef.h"  //DWORD typedef
#include "KNetByte.h"  //NETDWORD typedef
#include "KProgCst.inl" //IsLittleEndian()

#ifdef WIN32
  //Ask the linker to search for the Ws2_32.lib library while linking.
  #pragma comment( lib, "ws2_32" )
#endif

//TODO: MSVC6 Fix: replace Unicode _T('c') with _T("c")

//TestNetByteOrder()---------------------------------------------------------------
/*Test cobersion to and from network byte order.
 */
bool TestNetByteOrder()
{
std::_tcout << _T("\nTestNetByteOrder()") << std::endl;
TESTENTRY logEntry =
  {_T("IsLittleEndian()"), _T("KProgCst.inl"), true};
bool bRes = true;

std::_tcout << _T("\nHost byte order is") 
     << (IsLittleEndian() ? _T("") : _T(" other than"))
     << _T(" little-endian.") << std::endl;

    //Write test log
LogTest(&logEntry);


logEntry.m_szObjectName = _T("NetWord::NetWord()");
logEntry.m_szFileName = _T("KNetByte.h");

TCHAR szOutput[128];
szOutput[0] = '\0';
NetWord netwValue;
short sInput;
int i;
std::_tcout << _T("Memory Dump:") << std::endl;

 //Test ordering a 16-bit value to network byte order
sInput = 0x0102;
std::_tcout << _T("short sInput = {");
for (i = 0; i < sizeof(WORD); i++)
  {
  _stprintf(szOutput, _T("%02X "), *((BYTE*)&sInput + i) );
  std::_tcout << szOutput;
  }
std::_tcout << _T("}");
std::_tcout.flush();

 //Test conversion to network byte order
netwValue = sInput;

std::_tcout << _T("; netwValue = sInput = {");
for (i = 0; i < sizeof(NETWORD); i++)
  {
  _stprintf(szOutput, _T("%02X "), *( (BYTE*)netwValue + i) );
  std::_tcout << szOutput;
  }
std::_tcout << _T('}') << std::endl;

 //Test ordering a 16-bit network value to host byte order
netwValue = (NetWord)0x0403;
std::_tcout << _T("netwValue = (NetWord)0x0403 = {");
for (i = 0; i < sizeof(NETWORD); i++)
  {
  _stprintf(szOutput, _T("%02X "), *( (BYTE*)netwValue + i) );
  std::_tcout << szOutput;
  }
std::_tcout << _T('}') << std::endl;

sInput = netwValue;

std::_tcout << _T("short sInput = netwValue = {");
for (i = 0; i < sizeof(WORD); i++)
  {
  _stprintf(szOutput, _T("%02X "), *((BYTE*)&sInput + i) );
  std::_tcout << szOutput;
  }
std::_tcout << _T('}') << std::endl;

 //Test intialization of a 32-bit network value
BYTE nInput[sizeof(NETDWORD)] = {0x08,0x07,0x06,0x05};
std::_tcout << "nInput[4] = {";
for (i = 0; i < sizeof(NETDWORD); i++)
  {
  _stprintf(szOutput, _T("%02X "), *( nInput + i) );
  std::_tcout << szOutput;
  }
std::_tcout << _T('}');
std::_tcout.flush();

NetDWord netdwValue(nInput);

std::_tcout << _T("; netdwValue(nInput) = {");
for (i = 0; i < sizeof(NETDWORD); i++)
  {
  _stprintf(szOutput, _T("%02X "), *( (BYTE*)netdwValue + i) );
  std::_tcout << szOutput;
  }
std::_tcout << _T('}') << std::endl;

netdwValue =  (NetDWord)0x0D0C0B0A;
std::_tcout << "netdwValue =  (NetDWord)0x0D0C0B0A = {";
for (i = 0; i < sizeof(NETDWORD); i++)
  {
  _stprintf(szOutput, _T("%02X "), *( (BYTE*)netdwValue + i) );
  std::_tcout << szOutput;
  }
std::_tcout << _T('}') << std::endl;

netdwValue = (NetDWord*)nInput;

std::_tcout << _T("netdwValue =  (NetDWord*)nInput = {");
for (i = 0; i < sizeof(NETDWORD); i++)
  {
  _stprintf(szOutput, _T("%02X "), *( (BYTE*)netdwValue + i) );
  std::_tcout << szOutput;
  }
std::_tcout << _T('}') << std::endl;

netdwValue = *(NetDWord*)nInput;

std::_tcout << _T("netdwValue =  *(NetDWord*)nInput = {");
for (i = 0; i < sizeof(NETDWORD); i++)
  {
  _stprintf(szOutput, _T("%02X "), *( (BYTE*)netdwValue + i) );
  std::_tcout << szOutput;
  }
std::_tcout << _T('}') << std::endl;

 //Test ordering a 32-bit network value to host byte order
long lInput = netdwValue;

std::_tcout << _T("long lInput = netdwValue = {");
for (i = 0; i < sizeof(long); i++)
  {
  _stprintf(szOutput, _T("%02X "), *( (BYTE*)&lInput + i ));
  std::_tcout << szOutput;
  }

  bRes = true;// Fixme!
    //Write test log
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

std::_tcout << _T('}') << std::endl;
std::_tcout << _T("============================") << std::endl;

return bRes;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: 
 *  5    Biblioteka1.4         2004-10-05 13:05:31  Darko           fixed Unicode
 *       build
 *  4    Biblioteka1.3         2004-07-07 16:42:40  Darko           returns bool
 *       instead void
 *  3    Biblioteka1.2         2002-08-03 18:27:41  Darko           
 *  2    Biblioteka1.1         2002-03-05 01:23:47  Darko           added operator
 *       BYTE*()
 *  1    Biblioteka1.0         2002-03-04 18:11:57  Darko           
 * $
 *****************************************************************************/
