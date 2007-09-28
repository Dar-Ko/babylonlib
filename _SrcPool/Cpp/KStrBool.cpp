/*$Workfile: KBoolStream.h$: header file
  $Revision: 3$ $Date: 2007-03-10 19:54:00$
  $Author: Darko$

  Converts a boolean number to the string.
  Copyright: CommonSoft Inc.
  2004-10-01 Darko Kolakovic
*/

/* Group=Strings                                                             */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#include "KTypedef.h"
#include "KTChar.h"

LPCTSTR BooltoA(const bool bValue, LPCTSTR szTrue = NULL, LPCTSTR szFalse = NULL);

//-----------------------------------------------------------------------------
/*Obtains textual representation of a boolean value.
  Default representation for logical true is the symbol T and for logical false
  is the symbol F:

      true  T
      false F

  Example:
    ...
    int i = 100;
    bool bRes = (i != 0);
    std::_tcout << _T("i is equal to null: ") 
                << BooltoA(bRes, _T("Yes"), _T("No")) 
                << std::endl;
    ...
    Output: i is equal to null: Yes
 */
LPCTSTR BooltoA(const bool bValue,    //[in] value to write
               LPCTSTR szTrue, //[in] = NULL representation for logical true
               LPCTSTR szFalse //[in] = NULL representation for logical false
               )
{
if (bValue)
  return ((szTrue == NULL) ? _T("T") : szTrue);
else
  return ((szFalse == NULL) ? _T("F") : szFalse);
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2004-10-01 21:51:53  Darko
 * $
 *****************************************************************************/
