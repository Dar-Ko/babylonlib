//$Workfile: KValidate.js$: script file
//$Revision: 2$ $Date: 2006-11-29 13:09:32$
//$Author: Darko Kolakovic$
//
//Validate simple data types
//Copyright: CommonSoft Inc
//2006-10 Darko Kolakovic

//------------------------------------------------------------------------------
/*Verifies object existence.

  Returns: true if object not exist or if object has no value.
  Otherwise returns false.
 */
function isBlank(oValue //[in] object to validate
                )
{
return ((oValue == null) || (oValue.length == 0));
}

//------------------------------------------------------------------------------
/*Verifies if a character is a digit.

  Returns: true if the character is a digit. Otherwise returns false.
 */
function isDigit(cValue //[in] character to validate
                )
{
if ((cValue != null) && (cValue.length == 1))
  {
   //Same as ((cValue.charAt(0) >= "0") && (cValue.charAt(0) <= "9"))
  var arrayValidChars="0123456789";
  if (arrayValidChars.indexOf(cValue)!=-1)
    {
    return true;
    }
  }
return false;
}

//------------------------------------------------------------------------------
/*Verifies if a character is a letter from the English alphabet.

  Returns: true if the character is a letter from the English alphabet.
  Otherwise returns false.
 */
function isLetter(cValue  //[in] character to validate
                 )
{
if ((cValue != null) && (cValue.length == 1))
  {
  var arrayValidChars="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  if (arrayValidChars.indexOf(cValue)!=-1)
    {
    return true;
    }
  }
return false;
}
