//$RCSkfile: KSafeArray.js$: script file
//$Revision: 1.1 $ $Date: 2014/08/28 22:02:52 $
//$Author: ddarko $
//
//Array extensions
//2014-08-20 Darko Kolakovic

//-----------------------------------------------------------------------------
/*Erases an array
 */
Array.prototype.clear = function() {
  while (this.length > 0) {
    this.pop();
  }
};

///////////////////////////////////////////////////////////////////////////////
/*
 *$Log: KArrayExt.js,v $
 *Revision 1.1  2014/08/28 22:02:52  ddarko
 *Created
 *
 */
