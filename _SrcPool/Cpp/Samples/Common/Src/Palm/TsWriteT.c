/*$Workfile: TsWriteT.c$: implementation file
  $Revision: 2$ $Date: 2004-11-23 15:57:35$
  $Author: Darko Kolakovic$

  Outputs text to active form
  Copyright: CommonSoft Inc.
  2004-11-22 Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"

#ifdef __PALMOS__

extern FieldType* GetActiveField(FormType* formOwner);

bool TsWriteToView(LPCTSTR lszText);
bool TsWriteToViewLn(LPCTSTR lszText);

//-----------------------------------------------------------------------------
/*Writes a character string to the active field of the main form.

  Returns: true if the text was successfully written. Returns false if:
  the text is 0 characters long or the active field is not editable or
  field's text buffer is exhausted. Field has size limit of the maxChars
  bytes.

  Note: Palm OS specific (PalmOS).
 */
bool TsWriteToView(LPCTSTR lszText //[in] text to output or NULL
                   )
{
LPCTSTR szDefault;
if (lszText != NULL)
  szDefault = lszText;
else
  szDefault = _T("<null>");

//printf(lszText);
//Fixme!
return true;
}

//-----------------------------------------------------------------------------
/*Writes a line of the text to the active field of the main form. New line
  delimiter (EOL) is appended to the end of the text.

  Returns: true if the text was successfully written. Returns false if:
  the text is 0 characters long or the active field is not editable or
  field's text buffer is exhausted. Field has size limit of the maxChars
  characters.

  Note: Palm OS specific (PalmOS).
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
#endif //__PALMOS__
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2004-11-22 18:47:23  Darko Kolakovic
 * $
 *****************************************************************************/
