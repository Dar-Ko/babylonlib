/*$Workfile: KStrCtoA.c$: implementation file
  $Revision: 9$ $Date: 8/19/02 10:41:58 AM$
  $Author: Darko Kolakovic$

  Converts a character to descriptive string
  Jun 1990 Darko Kolakovic
*/

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#include "KTChar.h"  /*TCHAR*/

#ifdef _DEBUG
  static char THIS_FILE[] = __FILE__;
#endif

#ifndef UINT
  typedef  unsigned int UINT;
#endif
/* ///////////////////////////////////////////////////////////////////////// */
/* Group=Strings                                                             */

/*ChtoAscii()----------------------------------------------------------------*/
/*The ChtoAscii function converts a character from the American Standard Code 
  for Information Interchange (ASCII) Table to a descriptive string representing 
  its value. Characters have to be in range [0,127], if not the Out of Range 
  string "<?>" is returned.

  Example:
    #include <StdIO.h>
    #include "KStrings.h"
    void  main(void)
      {
      int cValue = -1;
      while (cValue < 129)
        {
        printf("%s\n",ChtoAscii(cValue));
        cValue ++;
        }
      }

  See also: {HTML: <A HREF ="Res/ASCIICharTable.htm"> ASCII Character Table </A>}

  Returns: zero-terminated string containing ASCII representation of 
  a character.
 */
TCHAR* ChtoAscii(int cValue /*[in] value of a character to convert [0,127]   */
                 )
{
#ifndef DEL
  #define DEL  0x7F /*DELETE is the last character in the ASCII table (127)*/
#endif

  /*Table with control characters descriptions (0x00 – 0x1F or 0x7F)   */
static TCHAR szChar[2] ={_T('!'),_T('\0')};
static TCHAR* szControlChar[ ] =
    {
    /*String    ASCII value   Escape sequence       */
  _T("<NUL>"), /*   0                               */
  _T("<SOH>"), /*   1                               */
  _T("<STX>"), /*   2                               */
  _T("<ETX>"), /*   3                               */
  _T("<EOT>"), /*   4                               */
  _T("<ENQ>"), /*   5                               */
  _T("<ACK>"), /*   6                               */
  _T("<BEL>"), /*   7         \a    Alert/bell      */
  _T("<BS>") , /*   8         \b    Backspace       */
  _T("<HT>") , /*   9         \t    Horizontal tab  */
  _T("<LF>") , /*  10         \n    Newline         */
  _T("<VT>") , /*  11         \v    Vertical tab    */
  _T("<FF>") , /*  12         \f    Formfeed        */
  _T("<CR>") , /*  13         \r    Carriage return */
  _T("<SO>") , /*  14                               */
  _T("<SI>") , /*  15                               */
  _T("<DLE>"), /*  16                               */
  _T("<DCl>"), /*  17                               */
  _T("<DC2>"), /*  18                               */
  _T("<DC3>"), /*  19                               */
  _T("<DC4>"), /*  20                               */
  _T("<NAK>"), /*  21                               */
  _T("<SYN>"), /*  22                               */
  _T("<ETB>"), /*  23                               */
  _T("<CAN>"), /*  24                               */
  _T("<EM>") , /*  25                               */
  _T("<SUB>"), /*  26                               */
  _T("<ESC>"), /*  27                               */
  _T("<FS>") , /*  28                               */
  _T("<GS>") , /*  29                               */
  _T("<RS>") , /*  30                               */
  _T("<US>") , /*  31                               */
    /*printabile character                          */
  _T("<sp>")   /*  32         space                 */
  };

if (cValue & ~DEL)                /*Out of ASCII range                       */
  {
  return  _T("<?>");              /*Out of Range error                       */
  }
else                              /*An ASCII character                       */
  {
  if (cValue == DEL)
    {
    return  _T("<DEL>");   /*127 Under MS-DOS this code (Ctrl-BKSP) have     */
                           /*same effect as BS                               */
    }
  else if ((UINT)cValue > ' ')    /*Printable non-space character            */
    {
    szChar[0] = (TCHAR)cValue;    /*Copy actual character to placeholder     */
    return szChar;
    }
  else                            /*Control character or space               */
    return szControlChar[cValue];
  }
}

/* ///////////////////////////////////////////////////////////////////////// */
/******************************************************************************
 * $Log:
 *  5    Biblioteka1.4         03/08/2001 12:21:05 AMDarko           Return value
 *       for chars > 32
 *  4    Biblioteka1.3         02/08/2001 10:09:58 PMDarko           Comment
 *  3    Biblioteka1.2         11/07/2001 10:52:46 PMDarko
 *  2    Biblioteka1.1         08/06/2001 11:51:53 PMDarko           VSS
 *  1    Biblioteka1.0         21/09/2000 1:13:17 AMDarko
 * $
 *****************************************************************************/
