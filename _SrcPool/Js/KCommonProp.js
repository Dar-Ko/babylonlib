//$RCSfile: KCommonProp.js,v $: script file
//$Revision: 1.1 $ $Date: 2014/07/23 19:22:27 $
//$Author: ddarko $
//
//Compare two objects for common properties
//2014-07 jfriend00

//_DEBUG = true;
//----------------------------------------------------------------------------
/*Function that recursively collects all properties in two objects and then 
  returns you an array of any common property names between them.
  If .length === 0 in the returned array, then there are no common properties.
  Otherwise, it contains the common property names. 
  History: jfriend00
*/
function findCommonProps(obj1, obj2) {
	var map1 = {}, map2 = {};
	var commonProps = [];

	function isArray(item) {
		return Object.prototype.toString.call(item) === "[object Array]";
	}

	function getProps(item, map) {
		if (typeof item === "object") {
			if (isArray(item)) {
				// iterate through all array elements
				for (var i = 0; i < item.length; i++) {
					getProps(item[i], map);
				}
			} else {
				for (var prop in item) {
					map[prop] = true;
					// recursively get any nested props
					// if this turns out to be an object or array
					getProps(item[prop], map);
				}
			}
		}
	}

	// get all properties in obj1 into a map
	getProps(obj1, map1);
	getProps(obj2, map2);
	for (var prop in map1) {
		if (prop in map2) {
			commonProps.push(prop);
		}
	}
	return commonProps;
}
