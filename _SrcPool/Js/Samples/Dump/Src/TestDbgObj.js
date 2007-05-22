/*$Workfile: TestDbgObj.js$: script file
  $Revision: 1$ $Date: 2006-11-23 19:17:41$
  $Author: Darko Kolakovic$

  Test object dump
  Copyright: CommonSoft Inc.
  2006-11-23  Darko Kolakovic
*/

// Group=Examples
function TsWriteToView(str)
{
  //tmp; delete after debugging;
}
//-----------------------------------------------------------------------------
/*Function validates a object dump function

  Returns: true if successful, otherwise returns false.
 */
function TestDbgObj()
{

TsWriteToView("TestDbgObj()");
var bRes = true;
//TESTENTRY logEntry =
//  {_T("AtoI()"), _T("KStrAtoI.cpp"), bRes};

//Test cases
var aVariable;             //0. undefined: null
var bVariable = true;      //1. boolean: true
var strVariable = "Text";  //2. string: Text
var iVariable = 299792458; //4. number: 299792458

var arrTmp  = new Array();
arrTmp[0] = "abc";
arrTmp[1] = 123;
var arrVariable = new Array(aVariable, iVariable, arrTmp);//6. Array:

var fVariable = writeResult;  //7. function: function
var fAnonymous = function(strText){ alert(strText); };
var oVariable;                //8. object:
if (typeof ActiveXObject != 'undefined') //Microsoft IE shell
  {
  oVariable = new ActiveXObject("Microsoft.XMLHTTP");
  //IE: ActiveXObject doesn't have constructor
  }
else if (typeof XMLHttpRequest != 'undefined')  //Mozilla
  oVariable =  new XMLHttpRequest();

var arrTest = new Array();
                    //(Test value,  expected,  result)
arrTest[0] = new Array(aVariable  ,"undefined",false);
arrTest[1] = new Array(bVariable  ,"boolean"  ,false);
arrTest[2] = new Array(strVariable,"string"   ,false);
arrTest[3] = new Array(""         ,"string"   ,false);
arrTest[4] = new Array(iVariable  ,"number"   ,false);
arrTest[5] = new Array(new Array(),"Array"    ,false);
arrTest[6] = new Array(arrVariable,"Array"    ,false);
arrTest[7] = new Array(fVariable  ,"function" ,false);
arrTest[8] = new Array(fAnonymous ,"function" ,false);
arrTest[9] = new Array(oVariable  ,"object"   ,false);

//Run the test
var i = 0;
while (i < arrTest.length)
  {
  var strOutput = dbgObj(arrTest[i][0]);
  var bResult = (strOutput.substring(0,arrTest[i][1].length) == arrTest[i][1]);
  arrTest[i][2] = bResult; //Store result for the particular test
      document.writeln("<dt>" + i + ". " + arrTest[i][1] + ": <b style=\"color:" +
                       (bResult? "blue;\">" : "red;\">") +  bResult +
                       "</b></dt><dd>" + strOutput + "</dd>");


//  writeResult(dbgObj, arrTest[i], i);
  i++;
  }


//logEntry.m_bResult = bRes;
//LogTest(&logEntry);

TsWriteToView("LOG_EOT");
return bRes;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2006-11-23 19:17:41  Darko Kolakovic 
 * $
 *****************************************************************************/
