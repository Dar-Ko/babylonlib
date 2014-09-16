/*$RCSfile: TestItoHex.js,v $: script file
  $Revision: 1.1 $ $Date: 2014/09/16 21:46:13 $
  $Author: ddarko $

  Test conversion of integer to hexadecimal number
  2014-09-16  Darko Kolakovic
*/

// Group=Examples

//-----------------------------------------------------------------------------
/*Function validates conversion of integer to hexadecimal number

  Returns: true if successful, otherwise returns false.
 */
function TestItoHex()
{
TsWriteToViewLn("TestItoHex()");
var bRes = true;   //result of the test
var bMatch = true; //result of the pattern matching
//TESTENTRY logEntry =
//  {_T("FnMatch()"), _T("KFnMatch.js"), bMatch};
//debugger;
var i = 0;
try
  {
	var arrTest = [
		    0,
		    1,
		    2,
		   10,
		  255,
		  256,
		 2048,
		 12345678129191,
		  1.5,
		   -1,
		   -2,
		  -10,
		 8000,
		80000,
		     , //undefined
		 null
	];

	/*
	0. value = 0 = 00000000 (00, 0000) TestItoHex.js:41
1. value = 1 = 00000001 (01, 0001) TestItoHex.js:41
2. value = 2 = 00000002 (02, 0002) TestItoHex.js:41
3. value = 10 = 0000000A (0A, 000A) TestItoHex.js:41
4. value = -1 = FFFFFFFF (-1, FFFF) TestItoHex.js:41
5. value = -2 = FFFFFFFE (-2, FFFE) TestItoHex.js:41
6. value = -10 = FFFFFFF6 (-A, FFF6) TestItoHex.js:41
7. value = 8000 = 00001F40 (40, 1F40) TestItoHex.js:41
8. value = 80000 = 00013880 (80, 3880) 
	 */
	while ( i < arrTest.length ) {
		var strRes = getHex(arrTest[i], 8);
		console.log('' + i + '. value = ' + arrTest[i] + ' = 0x' + strRes + ' (' + toHex(arrTest[i] ) + ', ' + decimalToHexString(arrTest[i] ) + ', ' + dec2hex(arrTest[i] ) + ')');
		i++;
	}
  }
catch(error)
  {
  TsWriteToViewLn(error.name + ": " + error.message +
               "; value " + i +  ". " + arrTest[i]);
  bRes = false;
  }

//logEntry.m_bResult = bMatch;
//LogTest(&logEntry);

TsWriteToViewLn(LOG_EOT);
return bRes;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: TestItoHex.js,v $
 * Revision 1.1  2014/09/16 21:46:13  ddarko
 * Created
 *
 *****************************************************************************/
