/*$RCSfile: KStrToInt.cpp,v $: implementation file
  $Revision: 1.1 $ $Date: 2008/09/26 20:27:40 $
  $Author: ddarko $

  Convert a character string to an integer value.
  2008-09-26 Darko Kolakovic
*/
/* Group=Strings                                                             */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#include "KTChar.h"
#ifdef _MSC_VER
    #pragma include_alias( "KTChar.h", "tchar.h" )  //LPCTSTR typedef
    #pragma include_alias( <KTChar.h>, <tchar.h> )  //LPCTSTR typedef
  /*Converts a character string to an integer value. The input string is
    a sequence of characters that can be interpreted as a numerical value.
    The function stops reading the input string at terminating null character
    ('\0') or at the first character that it cannot recognize as part of
    a number.
   */
  #define AtoI(s) _ttoi(s)
#endif



/*Convert hexadecimal string to long integer.
  The scan ends when a non-hexadecimal character is hit.
 */
extern "C" long HextoL(LPCTSTR szSource);

//-----------------------------------------------------------------------------
/*Converts a character string to an integer value. The input string is
  a sequence of characters that can be interpreted as a numerical value.
  The function stops reading the input string at terminating null character
  ('\0') or at the first character that it cannot recognize as part of
  a number.
  Hexadecimal numbers have to be prefixed with '0x':
        0xHHHHHHHH

  Returns: number converted from input string. If the input string is NULL,
  function returns 0.
 */
int32_t StrToInt(LPCTSTR szNumber //[in] zero-terminated string representing
                //decimal or hexadecimal number.
                )
{
int32_t iResult = 0;
if ((szNumber != NULL) && (szNumber[0] != _T('\0')))
  {
  if ( (szNumber[0] == _T('0')) && (szNumber[1] == _T('x')) )
    {
    //Hexadecimal number 0xHHHHHHHH
    iResult = HextoL(&szNumber[2]);
    }
  else //Decimal number expected
    {
    iResult = AtoI(szNumber);
    }
  }
return iResult;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: KStrToInt.cpp,v $
 * Revision 1.1  2008/09/26 20:27:40  ddarko
 * Created
 *
 *****************************************************************************/
