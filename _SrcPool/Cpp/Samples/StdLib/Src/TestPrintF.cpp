/*$RCSfile: TestCrtStrtok.c,v $: implementation file
  $Revision: 1.4 $ $Date: 2009/09/30 20:55:29 $
  $Author: ddarko $

  Test displaying formatted output.
  Copyright (c) Microsoft Corporation. All rights reserved.
  MSVC 2003 CRT
*/

// Group=Examples

#include "stdafx.h"
#include <stdio.h>  //printf()
#include "KTestLog.h" //TESTENTRY struct
extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(LPCTSTR lszText);
extern bool TsWriteToViewLn(const int& iValue);
//-----------------------------------------------------------------------------
/*Test of producing formatted output.

  Returns: true if successful, otherwise returns false.

  See also: printf()
  Microsoft C run-time libraries: printf(), wprintf()... TODO: description
 

* This program uses the printf and wprintf functions
 * to produce formatted output.
 * http://msdn.microsoft.com/library/default.asp?url=/library/en-us/vclib/html/_crt_printf.2c_.wprintf.asp

 Output
    Integer formats:
       Decimal: -9234  Justified: -009234  Unsigned: 4294958062
    Decimal -9234 as:
       Hex: FFFFDBEEh  C hex: 0xffffdbee  Octal: 37777755756
    Digits 10 equal:
       Hex: 16  Octal: 8  Decimal: 10
    Characters in field (1):
             h    h    w    w
    Characters in field (2):
             h    h    w    w
    Strings in field (1):
                     computer
                         comp
       Unicode                      Uni
    Strings in field (2):
                     computer
                         comp
       Unicode                      Uni
    Real numbers:
       251.736600 251.74 2.517366e+002 2.517366E+002

    Address as:   0012FEE0

    Display to here:
    123456789012345678901234567890
       Number displayed: 16

 printf(_T( "This is a %s" ), _T( "test." ) );
 printf(_T( "The value='%d' (should be 1234)" ),    1234 );
 printf(_T( "The value='%5d' (should be _1234)" ),    1234 );
 printf(_T( "The value='%*d' (should be _1234)" ),    5,    1234 );
 printf(_T( "The value='% 5d' (should be __1234)" ),    1234 );
 printf(_T( "The value='%-5d' (should be 1234_)" ),    1234 );
 printf(_T( "The value='%+5d' (should be +_1234)" ),    1234 );
 printf(_T( "The value='0x%x' (should be 0x4d2)" ),    1234 );
 printf(_T( "The value='0x%8x' (should be 0x_____4d2)" ),    1234 );
 printf(_T( "The value='0x%08x' (should be 0x000004d2)" ),    1234 );
 printf(_T( "The value='0x%0*x' (should be 0x000004d2)" ),    8,    1234 );
 printf(_T( "The value='0b%b' (should be 0b10011010010)" ),    1234 );
 printf(_T( "The value='0b%16b' (should be 0b_____10011010010)" ),    1234 );
 printf(_T( "The value='0b%016b' (should be 0b0000010011010010)" ),    1234 );
 printf(_T( "The value='0b%0*b' (should be 0b0000010011010010)" ),    16,    1234 );
 printf(_T( "The value='%%' (should be a quoted percent)" ) );
 printf(_T( "The value='%lx' (should be invalid)" ) );
 printf(_T( "The value='%sz' (should be 'abc')" ), _T( "abcdef" ), 3 );

 */
bool TestStdPrintF()
{
bool bRes = true;
int iRes = -1;

   char   ch = 'h', *string = "computer";
   int    count = -9234;
   double fp = 251.7366;
   wchar_t wch = L'w', *wstring = L"Unicode";

  TESTENTRY logEntry = 
  {_T("printf()"), _T("C run-time libraries"), false};
TsWriteToViewLn(_T("TestStdPrintF()"));

/*%% - % followed by another % character will write % to stdout.
 */
iRes = printf("Percent symbol: %%d.\n", 10);
//Expected result: 'Percent symbol: %d.' (value 10 should be ignored!)
bRes = (iRes == 20);

   /* Display integers. */
   printf( "Integer formats:\n"
           "   Decimal: %d  Justified: %.6d  Unsigned: %u\n",
           count, count, count, count );

   printf( "Decimal %d as:\n   Hex: %Xh  C hex: 0x%x  Octal: %o\n",
            count, count, count, count );

   /* Display in different radixes. */
   printf( "Digits 10 equal:\n   Hex: %i  Octal: %i  Decimal: %i\n",
            0x10, 010, 10 );

   /* Display characters. */

   printf("Characters in field (1):\n%10c%5hc%5C%5lc\n", ch, ch, wch, wch);
   wprintf(L"Characters in field (2):\n%10C%5hc%5c%5lc\n", ch, ch, wch, wch);

   /* Display strings. */

   printf("Strings in field (1):\n%25s\n%25.4hs\n   %S%25.3ls\n",
   string, string, wstring, wstring);
   wprintf(L"Strings in field (2):\n%25S\n%25.4hs\n   %s%25.3ls\n",
       string, string, wstring, wstring);

   /* Display real numbers. */
   printf( "Real numbers:\n   %f %.2f %e %E\n", fp, fp, fp, fp );

   /* Display pointer. */
   printf( "\nAddress as:   %p\n", &count);

printf("%.0e %.0f %.0g\n", 0.0, 0.0, 0.0);
//Result should have been: 0e+00 0 0
printf("%#.0e %#.0f %#.0g\n", 0.0, 0.0, 0.0);
//Result should have been: 0.e+00 0. 0.

/*%n - Number of characters successfully written so far to the stream or 
buffer; this value is stored in the integer whose address is given as the
argument.

Note: The %n format is inherently insecure and is disabled by default;
if %n is encountered in a format string, the invalid parameter handler is
invoked. To enable %n support, see _set_printf_count_output().
*/
TsWriteToView("Number of characters written before %%n specifier: ");
__try
  {
  if(_get_printf_count_output() == FALSE)
    {
    /*Enable support of the %n format in printf, _printf_l, 
      wprintf, _wprintf_l-family functions.

      Note: MS Visual Studio 2005 fails to enable %n format.
      MS Visual Studio 2005 SP2 fixed the issue.
     */
    _set_printf_count_output(TRUE);
    }

  printf( "%n\n", &count );
  bRes = (count == 0);
  printf( "1234567890123456%n%%n78901234567890\n", &count );
  bRes = bRes && (count == 16);
  }
__except(EXCEPTION_EXECUTE_HANDLER)
  {
  logEntry.m_bResult = bRes = false;
  unsigned long nExc = GetExceptionCode();
  TRACE1("prinf(%%n) failed with exception %u.\n", nExc);
  count = -1; //Failed test
  }

TsWriteToViewLn(count);


logEntry.m_bResult = bRes;
LogTest(&logEntry);

return bRes;
}

//-----------------------------------------------------------------------------
/*C-language wrapper for the test of printf().
  Returns: true if successful, otherwise returns false.

  See also: TestStdPrintF()
  Microsoft C run-time libraries: printf(), wprintf().
 */
extern "C"
bool TestCrtPrintF(void)
{
return TestStdPrintF();
}

//////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 *$Log: $
 *****************************************************************************/
