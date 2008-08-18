//$Workfile: KValidate.js$: script file
//$Revision: 3$ $Date: 2007-02-23 18:14:52$
//$Author: Darko Kolakovic$
//
//Validate simple data types
//Copyright: CommonSoft Inc
//2006-10 Darko Kolakovic

//------------------------------------------------------------------------------
/*Verifies object existence.

  Returns: true if object null object or if object has no value.
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

//------------------------------------------------------------------------------
/*Validate if the argument is a string.

  Returns: true if the argument passed to the function is a string; if not,
  returns false.

  Example:
    var bRes = isString("Some text");
 */
function isString(strValue //[in] object to validate
                 )
{
if (typeof strValue == 'string')
  return true; //string constant
if (typeof strValue == 'object')
  {
  //String object
  return (strValue.constructor.toString().match(/string/i) != null);
  }
return false;
}

//------------------------------------------------------------------------------
/*Validate if the argument is an array.

  Returns: true if the argument passed to the function is an array object; if not,
  returns false.
 */
function isArray(arrValue //[in] object to validate
                )
{
if (typeof arrValue == 'object')
  {
  return (arrValue.constructor.toString().match(/array/i) != null);
  }
return false;
}

//------------------------------------------------------------------------------
/*Validate if an object is undefined (undeclared).

  Returns: true if the argument passed to the function is uan udefined object;
  if the object is defined or has null value, method returns false.
 */
function isUndefined(oValue)
{
return (typeof oValue == 'undefined');
}

//------------------------------------------------------------------------------
/*Validate if the argument is a number.

  Returns: true if the argument passed to the function is a number object; if not,
  returns false.
 */
function isNumber(nValue)
{
return (typeof nValue == 'number');
}

//------------------------------------------------------------------------------
/*Validate if the argument is a function.

  Returns: true if the argument passed to the function is a function object; if not,
  returns false.
 */
function isFunction(fValue)
{
return (typeof fValue == 'function');
}

