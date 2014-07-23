//$RCSfile: KByteToStr.js,v $: script file
//$Revision: 1.1 $ $Date: 2014/07/23 19:22:27 $
//$Author: ddarko $
//
//Convert to and from an array of bytes
//2014-07

//_DEBUG = true;
//----------------------------------------------------------------------------
/*Converts an array of bytes (unsigned 8-bit characters in range [0, 255]) to string.
 */
function byteToStr(byteArray) {
	var str = "";
	for (var i = 0, len = byteArray.length; i < len; i += 2) {
		var charTmp = byteArray[i] << 8;
		if (byteArray[i + 1])
			charTmp |= byteArray[i + 1];
		str += String.fromCharCode(charTmp);
	}
	return str;
}

//----------------------------------------------------------------------------
/*Converts a string to the array of bytes (unsigned 8-bit characters).
 */
function strToByte(str) {
	var byteArray = [];
	for (var i = 0, len = str.length; i < len; i++) {
		var charTmp = str.charCodeAt(i);
		bytes.push(charTmp >>> 8, charTmp & 0xFF);
	}
	return byteArray;
}