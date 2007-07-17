/*$Workfile: S:\_SrcPool\Cpp\STL\KUcsToHex.cpp$: implementation file
  $Revision: 1$ $Date: 2007-07-17 12:02:07$
  $Author: Darko Kolakovic$

  Converts a 16-bit UCS-2 character to hexadecimal number
  2007-07 Darko Kolakovic
*/

/* Group=Strings                                                             */

#ifdef _DEBUG
  #ifndef _STLP_DEBUG
    #define _STLP_DEBUG 1    //Debug STLPort library
  #endif
#else
  #ifdef _STLP_DEBUG
    #undef _STLP_DEBUG
  #endif
#endif

#include "STL/KOStream.h" //tostream typedef
#include "KTChar.h" //UCS2 typedef

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif


//-----------------------------------------------------------------------------
/*Writes a UCS-4 character to output stream as a hexadecimal number.
  An Universal Character Set UCS-4 character is 32-bits wide.

  Returns: output stream.
  
  See also: ISO 10646

  Example:
      UcstoHex(std::_tcout, 0x100) << std::endl;
      UcstoHex(std::_tcout, 3435973836) << std::endl;
      Output: 0100<EOL>
              3872c4ab<EOL>

  Note: uses Standard Template Library (STL).
 */
tostream& UcstoHex(tostream& outStream, //[out] output stream
                   UCS4 ucsValue        //[in] UCS-4 character
                  )
{
using namespace std;
if (ucsValue <= 0xFFFF)
  outStream << hex << setfill(_T('0')) << setw(4) << ucsValue;
else if (ucsValue <= 0xFFFFF)
  outStream << hex << setw(5) << ucsValue;
else if (ucsValue <= 0xFFFFFF)
  outStream << hex << setw(6) << ucsValue;
else if (ucsValue <= 0xFFFFFFF)
  outStream << hex << setw(7) << ucsValue;
else
  outStream << hex << setw(8) << ucsValue;
return outStream;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2007-07-17 12:02:07  Darko Kolakovic 
 * $
 *****************************************************************************/
