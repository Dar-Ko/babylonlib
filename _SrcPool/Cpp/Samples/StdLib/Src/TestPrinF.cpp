// crt_printf.c

#include <stdio.h>

/* This program uses the printf and wprintf functions
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
bool TestPrintF( void )
{
   char   ch = 'h', *string = "computer";
   int    count = -9234;
   double fp = 251.7366;
   wchar_t wch = L'w', *wstring = L"Unicode";

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

   /* Count characters printed. */
   printf( "\nDisplay to here:\n" );
   printf( "1234567890123456%n78901234567890\n", &count );
   printf( "   Number displayed: %d\n\n", count );
}


int main(argc, argv)
        int argc;
        char **argv;
{

printf("%.0e %.0f %.0g\n", 0.0, 0.0, 0.0);
//Result should have been: 0e+00 0 0
printf("%#.0e %#.0f %#.0g\n", 0.0, 0.0, 0.0);
//Result should have been: 0.e+00 0. 0.
exit(0);
}
