/*$Workfile: TsWriteT.c$: implementation file
  $Revision: 2$ $Date: 2004-11-23 15:57:37$
  $Author: Darko Kolakovic$

  Outputs text to standard output stream.
  Copyright: CommonSoft Inc.
  2004-11-22 Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"
#include <stdio.h>

bool TsWriteToView(LPCTSTR lszText);
bool TsWriteToViewLn(LPCTSTR lszText);

//-----------------------------------------------------------------------------
/*Writes a character string to the standard output stream.

  Returns: true if the text was successfully written; otherwise returns false.
 */
bool TsWriteToView(LPCTSTR lszText //[in] text to output or NULL
                   )
{
LPCTSTR szDefault;
if (lszText != NULL)
  szDefault = lszText;
else
  szDefault = _T("<null>");

_ftprintf(stdout, lszText);

return true;
}

//-----------------------------------------------------------------------------
/*Writes a line of the text to the standard output stream. New line
  delimiter (EOL) is appended to the end of the text.

  Returns: true if the text was successfully written; otherwise returns false.
 */
bool TsWriteToViewLn(LPCTSTR lszText //[in] line of text to output
                     )
{

if (lszText[0] != _T('\0'))
  if(!TsWriteToView(lszText))
    return false;
return TsWriteToView(_T("\n"));
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2004-11-23 15:52:04  Darko Kolakovic
 * $
 *****************************************************************************/
