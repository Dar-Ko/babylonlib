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
/*Validate if an object is null.
  The null value is a primitive value that represents the null, empty or
  non-existent reference.

  Returns: true if the argument passed to the function is null object;
  if the object is defined and has not null value, method returns false.

  See also: Standard ECMA-262 - 4.3.11 Null Value
 */
function isNull(oValue)
{
var oNull = null;
return (oValue===oNull);
//return (typeof oValue == 'object' && !oValue );
}

//------------------------------------------------------------------------------
/*Validate if an object is undefined (undeclared).
  The undefined value is a primitive value used when a variable has not been
  assigned a value.

  Returns: true if the argument passed to the function is an udefined object;
  if the object is defined or has null value, method returns false.

  See also: Standard ECMA-262 - 4.3.9 Undefined Value
 */
function isUndefined(oValue)
{
var oUndefined;
return (oValue===oUndefined);
//return (typeof oValue == 'undefined'); Note: slower because of string comparison
}

//------------------------------------------------------------------------------
/*Validate if the argument is a number.

  Returns: true if the argument passed to the function is a number object; if not,
  returns false.
 */
function isNumber(nValue)
{
return ((typeof nValue == 'number') || (nValue instanceof Number));
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

//------------------------------------------------------------------------------
/*Validate if the argument is a RegExp object.

  Returns: true if the argument passed to the function is a RegExp object; if not,
  returns false.
 */
function isRegexp(oRegexp)
{
return (oRegexp && (oRegexp.constructor == RegExp));
}
