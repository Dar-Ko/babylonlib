//$Workfile: KSafeArray.js$: script file
//$Revision: 2$ $Date: 2006-12-13 13:20:33$
//$Author: Darko Kolakovic$
//
//Converts Visual Basic array
//Copyright: CommonSoft Inc
//2004-06-20 Darko Kolakovic

//-----------------------------------------------------------------------------
/*Converts SAFEARRAY object recived from an ActiveX control to the array object.

  Returns array with converted SAFEARRAY elements.
 */
function SafeArrayToArray(safeArray //[in] SAFEARRAY object
                         )
{
var vbArray = new VBArray(safeArray);
return vbArray.toArray();
}

///////////////////////////////////////////////////////////////////////////////
/*
 *$Log: $
 */
