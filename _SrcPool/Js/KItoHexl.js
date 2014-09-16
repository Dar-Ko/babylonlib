//$RCSfile: KItoHexl.js,v $: script file
//$Revision: 1.1 $ $Date: 2014/09/16 18:22:50 $
//$Author: ddarko $
//
//Hexadecimal representation of unsigned integer
//2014-08 Darko Kolakovic

//-----------------------------------------------------------------------------
/*Returns hexadecimal representation of unsigned integer
   @param
  digits - maximum number of digits, for 32-bit integer,  number of digits is 8
  */
function getHex(value, digits) {
  /*Note: It performs faster than .toString(16) on 1-2 byte numbers and
    negative numbers, but slower on larger numbers  when  number of digits >= 6).
   */
   var hex = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'];
    var result = '';
    while (digits--) {
        result = hex[value & 0xF] + result;
        value >>= 4;
    }
    return result;
}

function toHex(value) {
  return  ("0"+(Number(value).toString(16))).slice(-2).toUpperCase()
}

function decimalToHexString(number)
{
//32-bit integer
    if (number < 0)
    {
      number = 0xFFFFFFFF + number + 1;
    }

    return number.toString(16).toUpperCase();
}

function dec2hex(i) {
   return (i+0x10000).toString(16).substr(-4).toUpperCase();
}