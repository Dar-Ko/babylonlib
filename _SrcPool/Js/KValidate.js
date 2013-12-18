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

/*
function isBlank(oValue)
{
  if (oValue)
  {
    return false
  }
  return true
}
*/

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

function isValidCommonURL(a)
{
  if (a === undefined)
  {
    return false
  }
  if (a.length > 256)
  {
    return false
  }
  if (null == a.match(/^(https?)(:\/\/[-_.!~*\'()a-zA-Z0-9;\/?:\@&=+\$,%#]+)$/))
  {
    return false
  }
  return true
}

function isValidDeviceID(b)
{
  var a = true;
  if (!(b.match(/^[-0-9A-Za-z_\.]{1,30}$/)))
  {
    a = false
  }
  return a
}

function isValidIPAddress(b)
{
  if (b.match(/^\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}$/) == null)
  {
    return false
  }
  var a = b.split(".");
  if (!((0 <= a[0] && a[0] <= 255) && (0 <= a[1] && a[1] <= 255) && (0 <= a[2] && a[2] <= 255) && (0 <= a[3] && a[3] <= 255)))
  {
    return false
  }
  for (i = 0; i < 4; i++)
  {
    a[i] = parseInt(a[i], 10)
  }
  var c = "" + a[0] + "." + a[1] + "." + a[2] + "." + a[3];
  if (0 == a[0])
  {
    return false
  }
  if ("127.0.0.1" == c)
  {
    return false
  }
  if ("255.255.255.255" == c)
  {
    return false
  }
  if (224 <= a[0] && a[0] <= 239)
  {
    return false
  }
  if (240 <= a[0] && a[0] <= 255)
  {
    return false
  }
  if (255 == a[3])
  {
    return false
  }
  return true
}

function isValidRetryInterval(b)
{
  var a = true;
  if (!((100 <= Number(b)) && (Number(b) <= 60000)) || !b.match(/^-?[0-9]+$/))
  {
    a = false
  }
  return a
}

function isValidHour(a)
{
  if (0 == a.length)
  {
    return false
  }
  if (!((0 <= Number(a)) && (Number(a) <= 23)))
  {
    return false
  }
  return true
}

function isValidMinute(a)
{
  if (0 == a.length)
  {
    return false
  }
  if (!((0 <= Number(a)) && (Number(a) <= 59)))
  {
    return false
  }
  return true
}

function isValidDelayTime(b)
{
  var a = true;
  if (!((0 <= Number(b)) && (Number(b) <= 24)))
  {
    a = false
  }
  else
  {
    if (!(b.length <= 2))
    {
      a = false
    }
  }
  return a
}

function isValidFileURL(a)
{
  return isValidCommonURL(a)
}

function isZip(b)
{
  var a = true;
  if (!(b.match(/.+\.(zip)$/i)))
  {
    a = false
  }
  return a
}

function isBin(b)
{
  var a = true;
  if (!(b.match(/.+\.(bin)$/i)))
  {
    a = false
  }
  return a
}

function isValidProxy(a)
{
  return isValidCommonURL(a)
}

function isValidID(b)
{
  var a = true;
  if (!(b.match(/^[-0-9A-Za-z_\.]{0,30}$/)))
  {
    a = false
  }
  return a
}

function isValidIDLength(b)
{
  var a = true;
  if (!((0 <= b.length) && (b.length <= 30)))
  {
    a = false
  }
  return a
}

function isValidPassword(b)
{
  var a = true;
  if (!(b.match(/^[-0-9A-Za-z_\.]{0,30}$/)))
  {
    a = false
  }
  return a
}

function isValidPasswordLength(b)
{
  var a = true;
  if (!((0 <= b.length) && (b.length <= 30)))
  {
    a = false
  }
  return a
}

function isValidURL(a)
{
  return isValidCommonURL(a)
}

function isValidInterval(b)
{
  var a = true;
  if (!(b.match(/^\d{1,5}$/)))
  {
    a = false
  }
  else
  {
    if (!((1 <= Number(b)) && (Number(b) <= 86400)))
    {
      a = false
    }
  }
  return a
}

function isValidSettingsFileURL(a)
{
  return isValidCommonURL(a)
}

function isValidUpdateFileURL(a)
{
  return isValidCommonURL(a)
}

function isValidAdministrator(b)
{
  var a = true;
  if (!(b.match(/^[^\t\n\r\f\v]*$/)))
  {
    a = false
  }
  return a
}

function isValidAdministratorLength(b)
{
  var a = true;
  if (!((0 <= b.length) && (b.length <= 255)))
  {
    a = false
  }
  return a
}

function isValidLocation(b)
{
  var a = true;
  if (!(b.match(/^[^\t\n\r\f\v]*$/)))
  {
    a = false
  }
  return a
}

function isValidLocationLength(b)
{
  var a = true;
  if (!((0 <= b.length) && (b.length <= 255)))
  {
    a = false
  }
  return a
}

function isValidDigestPassword(c)
{
  var b = true;
  if (!(c.match(/^[a-zA-Z0-9]*$/)))
  {
    b = false
  }
  else
  {
    if (!(a(c)))
    {
      b = false
    }
  }
  return b;

  function a(e)
  {
    var d = true;
    if (!(e.length <= 30))
    {
      d = false
    }
    return d
  }
}

function isJavascript(c)
{
  var a = true;
  if (!(b(c)))
  {
    a = false
  }
  else
  {
    if (!(c.match(/.+\.(js)$/i)))
    {
      a = false
    }
  }
  return a;

  function b(e)
  {
    var d = true;
    if (e.length == 0)
    {
      d = false
    }
    return d
  }
}

function SanitizeUrl(c)
{
  var d = c;
  var a;
  if ((d.match(/^http/) == null) && (d.match(/^https/) == null) && (d.match(/^ftp/) == null))
  {
    a = 0
  }
  else
  {
    var b = RegExp("[a-zA-Z0-9;/?:@&=+$,-_.!~*'()%]+$");
    if (d.match(b) == null)
    {
      a = 0
    }
    else
    {
      a = 1
    }
  } if (1 == a)
  {
    return c
  }
  else
  {
    return ""
  }
}

function isWindows()
{
  return (-1 != navigator.platform.indexOf("Win"))
}

function isNumeric(a)
{
  if (a.match(/[^0-9]/g) != null)
  {
    return false
  }
  return true
}

function isValidProxyURL(a)
{
  return isValidCommonURL(a)
}

function isIos()
{
  if (navigator.userAgent.match(/iPhone/i) || navigator.userAgent.match(/iPad/i) || navigator.userAgent.match(/iPod/i))
  {
    return true
  }
  return false
}

function isAndroid()
{
  if (navigator.userAgent.match(/Android/i))
  {
    return true
  }
  return false
}

function isValidNetMask(d)
{
  if (d.match(/^([01]?\d\d?|2[0-4]\d|25[0-5])\.(([01]?\d\d?|2[0-4]\d|25[0-5])\.){2}([01]?\d\d?|2[0-4]\d|25[0-5])$/) == null)
  {
    return false
  }
  var c = d.split(".");
  for (i = 0; i < 4; i++)
  {
    c[i] = parseInt(c[i], 10)
  }
  if (a(String(c[0]), String(c[1]), String(c[2]), String(c[3])) == false)
  {
    return false
  }
  var b = "" + c[0] + "." + c[1] + "." + c[2] + "." + c[3];
  if ("0.0.0.0" == b)
  {
    return false
  }
  if ("127.0.0.1" == b)
  {
    return false
  }
  if ("255.255.255.255" == b)
  {
    return false
  }
  if ("255.0.255.0" == b)
  {
    return false
  }
  return true;

  function a(j, g, f, e)
  {
    var h = true;
    if (j.match(/^(0|128|192|224|240|248|252|254|255)$/) == null)
    {
      h = false
    }
    if (Number(j) == 255)
    {
      if (g.match(/^(0|128|192|224|240|248|252|254|255)$/) == null)
      {
        h = false
      }
    }
    else
    {
      if (g.match(/^(0)$/) == null)
      {
        h = false
      }
    } if (Number(g) == 255)
    {
      if (f.match(/^(0|128|192|224|240|248|252|254|255)$/) == null)
      {
        h = false
      }
    }
    else
    {
      if (f.match(/^(0)$/) == null)
      {
        h = false
      }
    } if (Number(f) == 255)
    {
      if (e.match(/^(0|128|192|224|240|248|252|254|255)$/) == null)
      {
        h = false
      }
    }
    else
    {
      if (e.match(/^(0)$/) == null)
      {
        h = false
      }
    }
    return h
  }
}

function isValidGateway(a)
{
  return isValidIPAddress(a)
}

function isValidDNSServer(a)
{
  return isValidIPAddress(a)
}

function isValidSSID(a)
{
  return (a.match(/^[\x21\x24-\x7E]{1,32}$/) != null)
}

function isValidWepKey(a)
{
  return ((a.match(/^[\x21-\x7E]{5}$/) != null) || (a.match(/^[\x21-\x7E]{10}$/) != null) || (a.match(/^[\x21-\x7E]{13}$/) != null) || (a.match(/^[\x21-\x7E]{26}$/) != null))
}

function isValidPreSharedKey(a)
{
  return ((a.match(/^[\x21-\x7E]{8,63}$/) != null) || (a.match(/^[\x21-\x7E]{64}$/) != null))
};
