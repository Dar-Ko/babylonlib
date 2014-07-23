//$RCSfile: KParseCvsLine.js,v $: script file
//$Revision: 1.1 $ $Date: 2014/07/23 19:22:27 $
//$Author: ddarko $
//
//Compare two objects for common properties
//2009 Brian Huisman http://www.greywyvern.com/?post=258

//_DEBUG = true;
//----------------------------------------------------------------------------
/*Parse single line of values separated with comma or other character.
  A value containing the separator itself have to to be quoted.
  
  History: Brian Huisman, http://www.greywyvern.com/?post=258
  
  Example:
    var test = ['id,f\r\n'], ['10,Christopher'],['12,"John, Little"'];
    values = test[2].parseCvsLine();
 */
 String.prototype.parseCvsLine = function(sep) {
	console.log("parseCvsLine()");

	for (var foo = this.split(sep = sep || ","), x = foo.length - 1, tl; x >= 0; x--) {
		console.log(JSON.stringify(foo));
		console.log("foo[" + x + "]" + foo[x].replace(/"\s+$/, '"'));
		if (foo[x].replace(/"\s+$/, '"').charAt(foo[x].length - 1) == '"') {
			//Split on separators first, then bind together quoted values.
			if ((tl = foo[x].replace(/^\s+"/, '"')).length > 1 && tl.charAt(0) == '"') {
				foo[x] = foo[x].replace(/^\s*"|"\s*$/g, '').replace(/""/g, '"');
			} 
			else if (x) {
				foo.splice(x - 1, 2, [foo[x - 1], foo[x]].join(sep));
			} 
			else {
				foo = foo.shift().split(sep).concat(foo);
			}

		} 
		else 
			foo[x].replace(/""/g, '"');
	};
  return foo;
};