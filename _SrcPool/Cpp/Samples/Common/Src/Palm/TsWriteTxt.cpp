/*$Workfile: TsWriteTxt.cpp$: implementation file
  $Revision: 3$ $Date: 2004-11-12 14:02:54$
  $Author: Darko Kolakovic$

  Outputs text to the PalmOS window
  Copyright: CommonSoft Inc.
  2004-11-06 Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"


#ifdef __PALMOS__

extern FieldType* GetActiveField(FormType* formOwner);

bool TsWriteToView(LPCTSTR lszText);
bool TsWriteToViewLn(LPCTSTR lszText);
bool TsWriteToView(const int& iValue);
bool TsWriteToViewLn(const int& iValue);

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

//Fixme! Moves one line down
return FldInsert(GetActiveField(NULL),
                 szDefault,
                 StrLen(szDefault) //string length in bytes, without terminating null.
                 );
}

//-----------------------------------------------------------------------------
/*Writes a line of the text to the active field of the main form.. New line
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

//#include "KTime.h"  //_DATE_FORMAT_STD
/*
bool TsWriteToViewLn(const tm& tmTime  //[in] date and time to output
                     )
{
std::_tcout << tmTime.tm_year + YEAR_EPOCH_TM << _T('-')
            << tmTime.tm_mon + 1 << _T('-')
            << tmTime.tm_mday << _T('T')
            << tmTime.tm_hour << _T(':')
            << tmTime.tm_min << _T(':')
            << tmTime.tm_sec << std::endl;
return true;
}
*/
bool TsWriteToViewLn(const int& iValue  //[in] integer number to output
                     )
{
iValue;
//std::_tcout << iValue << std::endl;
return true;
}

//-----------------------------------------------------------------------------
/*Writes an integer as decimal number to the active field of the main form.

  Returns: true if the number was successfully written. Returns false if:
  the text is 0 characters long or the active field is not editable or
  field's text buffer is exhausted. Field has size limit of the maxChars
  bytes.

  Note: Palm OS specific (PalmOS).
 */
bool TsWriteToView(const int& iValue  //[in] integer number to output
                     )
{
TCHAR szValue[32];
StrIToA(szValue, iValue); //Convert the integer to decimal number string
//Fixme! Moves one line down
return FldInsert(GetActiveField(NULL),
                 szValue,
                 StrLen(szValue)//string length in bytes, without terminating null.
                 );

}

#ifdef HAS_FLOAT_POINT
/*TODO: float-point support
bool TsWriteToViewLn(const double& dValue  //[in] real number to output
                     )
{
std::_tcout << dValue << std::endl;
return true;
}

bool TsWriteToView(const double& dValue  //[in] real number to output
                     )
{
std::_tcout << dValue;
return true;
}

*/
#endif
///////////////////////////////////////////////////////////////////////////////
#endif //__PALMOS__
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2004-11-08 13:19:13  Darko Kolakovic
 * $
 *****************************************************************************/
