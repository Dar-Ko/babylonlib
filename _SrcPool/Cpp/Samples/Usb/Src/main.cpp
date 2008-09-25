/*$RCSfile: main.cpp,v $: implementation file
  $Revision: 1.2 $ $Date: 2008/09/25 21:31:36 $
  $Author: ddarko $

  Illustrates how to use handle an USB device.
  Copyright: CommonSoft Inc
  2008-09-24 Darko Kolakovic
*/

// Group=Examples

#ifdef _DEBUG
  #if _MSC_VER == 1200 /*MS VC/C++ 6.0*/
    //Fix for the warning(4786) cannot debug code with symbols longer
    //than 255 characters
  #pragma warning (disable: 4786)
  #endif
#endif

#include "stdafx.h"

#ifdef _MSC_VER
//<stdlib.h>
  /*ConvertS a character string to an integer value. The input string is 
    a sequence of characters that can be interpreted as a numerical value.
    The function stops reading the input string at the first character
    that it cannot recognize as part of a number or terminating null 
    character ('\0').
   */
  #define AtoI(s) _ttoi(s)
#endif


//main()-----------------------------------------------------------------------
/*Test USB device manipulation routines.

  Returns: EXIT_SUCCESS if succesful, otherwise returns EXIT_FAILURE.
 */
int main(int argc,     //[in] specifies how many arguments are passed to the
                       //program from the command line. The value of argc is
                       //at least one: the program name.
         TCHAR* argv[]  //[in] the program arguments as an array of pointers
                       //to null-terminated strings. The first string 
                       //  - (argv[0]) is the program name.
                       //  - (argv[1]) USB Vendor ID (VID) as decimal or 
                       //    hexadecimal value (oxnnnn)
                       //  - (argv[2]) USB Product ID (PID) as decimal or 
                       //    hexadecimal value (oxnnnn)
                       //The end of the array (argv[argc]) is indicated by 
                       //a NULL pointer.
         )
{
const int CMDLINE_VID = 1; //VID command line argument index
const int CMDLINE_PID = 2; //PID command line argument index
#define PROMPT_VID _T("Enter VID (0x0000): ") //TODO: move strings to resource file
#define PROMPT_PID _T("Enter PID (0x0000): ")

uint16_t nVendorId  = 0; //USB Vendor ID (VID)
uint16_t nProductId = 0; //USB Product ID (PID)


if(argc >= 2) //Get VID command line
  {
  if (argv[CMDLINE_VID][0] == _T('0') && argv[CMDLINE_VID][0] == _T('x'))
    {
    //Hexadecimal number oxnnnn
    }
  else //Expected decimal number
    {
    nVendorId = (uint16_t)AtoI(argv[CMDLINE_VID]);
    }
  if (argc >= 3) //Get PID command line
    {
    }
  }
else //Get VPID from the user or skip it with CR character
  {
  std::_tcout << PROMPT_VID;
  TCHAR ch;
  while (std::_tcin.get(ch) && (ch != _T('\n')))
    {
    std::_tcout.put(ch);
    //strFileName += ch;
    }
  }

return EXIT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: main.cpp,v $
 * Revision 1.2  2008/09/25 21:31:36  ddarko
 * Fixed MSVC6 warnings
 *
 *****************************************************************************/
