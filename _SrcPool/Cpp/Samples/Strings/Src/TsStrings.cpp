/*$Workfile: TsStrings.cpp$: implementation file
  $Revision: 7$ $Date: 8/19/02 10:33:29 AM$
  $Author: Darko Kolakovic$

  Test for different string functions
  Copyright: CommonSoft Inc.
  Feb. 2k Darko Kolakovic
*/

// Group=Examples

#include "StdAfx.h"
#include "KStrings.h"
#include "KCharCst.h" //ASCII table

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

extern BOOL TsWriteToView(LPCTSTR lszText);
extern "C" BYTE GetLRC(BYTE* pbData,int iCount);
extern bool IsLRCValid(const BYTE chReceivedLRC,BYTE* pbData, int iCount);


//TestStrings()--------------------------------------------------------------
/*Function shows how to use different string functions.

  Returns: true if successful, otherwise returns false.

 */
BOOL TestStrings()
{
CString strText;
strText = _T("ABCDEFGH12345678\r\n");
TsWriteToView((LPCTSTR)strText);
  //Test StrToLower()
LPTSTR szText = (LPTSTR)(LPCTSTR)strText;
TCHAR* szResult= new TCHAR [strText.GetLength()+1];
if (szResult  != NULL)
  {
  StrToLower(szResult, szText);
  TsWriteToView(szResult);
  delete[] szResult;
  }

  //Test StrPCpy()
LPTSTR strTail =  StrPCpy(szText, _T("1234"));
strTail = StrPCpy(strTail,_T("$%^&"));
*strTail = _T('-');  //Concatenate 
TsWriteToView(szText);

  //Test StrCatV()
TCHAR szOutput[64];
szOutput[0] = _T('\0');  //Empty string
StrCatV(szOutput, _T("The "), _T("quick "), _T("brown "), _T("dog "),
                  _T("jumps "), _T("over "), 
                  _T("the "), _T("lazy "), _T("fox.\r\n"), 
                  0 );
TsWriteToView(szOutput);

  //Test BintoA()
DWORD dwTest = 0x0A0A0101;
strText.Format(_T("Hex %X = bin %s\r\n"), dwTest,
                BintoA(szOutput, dwTest, 32, 0, _T('1'), _T('0') ));
TsWriteToView(strText);
  //Test BintoU()
DWORD dwRes = BintoU(szOutput);
ASSERT(dwRes == dwTest);
strText = UtoDec(dwRes,szOutput);
TsWriteToView(strText);

strText = UtoDecJust(dwRes,szOutput,20,_T('-'));
TsWriteToView(strText);
TsWriteToView("\r\n");

  //Test HextoL()
long lRes = HextoL("200");
strText.Format(_T("0x200 = %u\t"), lRes);
TsWriteToView(strText);
lRes = HextoL("AB80j34");
strText.Format(_T("0xAB80|j34| = %u\r\n"), lRes);
TsWriteToView(strText);

  //Test ChtoAscii()
int ch = -1;
while (ch < 129)
  {
  strText.Format(_T("Character %d.\t%s\r\n"),ch,ChtoAscii(ch));
  TsWriteToView(strText);
  ch++;
  }
strText.Format(_T("New page (%d) is %s\r\n"),NP,ChtoAscii(NP));
TsWriteToView(strText);
strText.Format(_T("XOFF (%d) is %s\r\n"),XOFF,ChtoAscii(XOFF));
TsWriteToView(strText);

BYTE chData[10] = {STX,'1','2','3','4','5','6','7',EOT};
chData[9] = GetLRC(&chData[1],8);
if(IsLRCValid(chData[9],&chData[1],8))
   TRACE0("LRC is valid\n");
return TRUE;
}

//TestReplaceEscapeSeq()-------------------------------------------------------
/*This function shows how to replace escape sequence characters.
 */
void TestReplaceEscapeSeq()
{
TRACE0("TestReplaceEscapeSeq()\n");
TCHAR szText[32] = 
  {
  _T('0'),_T('1'),_T('\\'),_T('a'),_T('\\'),_T('5'),_T('6'),_T('\\'),_T('n'),_T('9'),
  _T('\\'),_T('1'),_T('2'),_T('A'),_T('\\'),_T('0'),_T('8'),_T('7'),_T('\\'),_T('n'),
  _T('\\'),_T('x'),_T('0'),_T('3'),_T('f'),_T('\\'),_T('\"'),_T('7'),_T('\\'),_T('r'),
  _T('\\'),_T('\0')
  };
TRACE1("  byte stream:%s\n",szText);
CString strOutput = "Testing Escape Sequence replacement\r\n";
TsWriteToView((LPCTSTR)strOutput);

TsWriteToView((LPCTSTR)szText);
ReplaceEscapeSeq(szText);

TRACE1("  result:\n%s\n",szText);
strOutput.Format("\r\nresult:\r\n%s\r\n\r\n",szText);
TsWriteToView((LPCTSTR)strOutput);

}
