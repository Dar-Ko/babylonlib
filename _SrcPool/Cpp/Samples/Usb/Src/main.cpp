/*$RCSfile: main.cpp,v $: implementation file
  $Revision: 1.4 $ $Date: 2009/05/05 18:27:30 $
  $Author: ddarko $

  Illustrates how to handle an USB device.
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

extern int TestCommonUsb(uint16_t nVendorId = 0, uint16_t nProductId = 0);
extern int32_t StrToInt(LPCTSTR szNumber);

//main()-----------------------------------------------------------------------
/*Test USB device manipulation routines.

  Returns: EXIT_SUCCESS if succesful, otherwise returns EXIT_FAILURE.
 */
int _tmain(int argc,   //[in] specifies how many arguments are passed to the
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
uint16_t nVendorId  = 0; //USB Vendor ID (VID)
uint16_t nProductId = 0; //USB Product ID (PID)

//Parse command line input
const int CMDLINE_VID = 1; //VID command line argument index
const int CMDLINE_PID = 2; //PID command line argument index
#define PROMPT_VID _T("Enter VID (0x0000): ") //TODO: move strings to resource file
#define PROMPT_PID _T("Enter PID (0x0000): ")

TCHAR ch = _T('\0'); //keyboard echo

if(argc >= (CMDLINE_VID + 1)) //Get VID command line
  {
  nVendorId = (uint16_t)StrToInt(argv[CMDLINE_VID]);
  if (argc >= (CMDLINE_PID + 1)) //Get PID command line
    {
    nProductId = (uint16_t)StrToInt(argv[CMDLINE_PID]);
    }
  }
else //Get VID from the user or skip it with CR character
  {
  tstring strInput;    //user's input
  std::_tcout << PROMPT_VID;
  while (std::_tcin.get(ch) && (ch != _T('\n')))
    {
    std::_tcout.put(ch);
    strInput += ch;
    }
  nVendorId = (uint16_t)StrToInt(strInput.c_str());
  }

if (argc < (CMDLINE_PID + 1))
  {
  //Get PID from the user or skip it with CR character
  tstring strInput;    //user's input
  std::_tcout << PROMPT_PID;
  while (std::_tcin.get(ch) && (ch != _T('\n')))
    {
    std::_tcout.put(ch);
    strInput += ch;
    }
  nProductId = (uint16_t)StrToInt(strInput.c_str());
  }

return TestCommonUsb(nVendorId, nProductId); //Run predefined test cases
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: main.cpp,v $
 * Revision 1.4  2009/05/05 18:27:30  ddarko
 * Comment
 *
 * Revision 1.3  2008/09/26 21:36:48  ddarko
 * Added new test case
 *
 * Revision 1.2  2008/09/25 21:31:36  ddarko
 * Fixed MSVC6 warnings
 *
 *****************************************************************************/
