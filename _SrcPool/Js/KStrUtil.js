//$RCSfile: KStrUtil.js,v $: script file
//$Revision: 1.1 $ $Date: 2014/07/24 13:40:10 $
//$Author: ddarko $
//
//String extensions
//2014-06 Darko Kolakovic

//--------------------------------------------------------------------------
/*Replaces all occurrences of a token
 */
String.prototype.replaceAll = function (source, token, replace) {
	return source.replace(new RegExp(token, 'g'), replace);
}

//-----------------------------------------------------------------------------
//Retuns date and time in the ISO 8601 format
function iso8601Date(date) {
	var year = date.getFullYear();
	var month = ("0" + (date.getMonth() + 1)).slice(-2);
	var day = ("0" + date.getDate()).slice(-2);
	var hour = ("0" + date.getHours()).slice(-2);
	var minute = ("0" + date.getMinutes()).slice(-2);
	var strDate = year + "-" + month + "-" + day + " " + hour + ":" + minute;
	return strDate;
}
