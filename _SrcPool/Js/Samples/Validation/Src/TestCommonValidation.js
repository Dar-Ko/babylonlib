/*$Workfile: S:\_SrcPool\Js\Samples\Validation\Src\TestCommonValidation.js$: implementation file
  $Revision: 1$ $Date: 2006-11-08 17:52:25$
  $Author: Darko Kolakovic$

  Console application used to test various validation operations.
  Copyright: CommonSoft Inc
  2006-11-08 Darko Kolakovic
*/

// Group=Examples

try
 {
  eval(Include("TestBasicTypes.js"));
    WScript.echo("eval(Include('TestStrContent.js'));");
  }
catch(err)
  {
  TsWriteToView(err.name + " " +
                (err.number & 0xFFFF) + ": " +
                err.message);
  }

//-----------------------------------------------------------------------------
/*Defines the entry point for the console application that verifies different
  validation routines.

  Returns: EXIT_SUCCESS, which represents a value of 0, if successful. Otherwise
  a non-zero error code is returned.
 */
function TestCommonValidation()
{
	if (TsWriteToView == undefined)
	 WScript.echo("TsWriteToView");
	else
TsWriteToView("Validation Tests");

var funcTest = new Array(TestBasicTypes,
                         "TestStrContent" //TODO:
                        );

var iTestCount = 0;
while (iTestCount < funcTest.length)
  {
  if ((funcTest[iTestCount] != undefined) && funcTest[iTestCount])
    /* TODO: log << LOG_SUCCESS*/ TsWriteToView("LOG_SUCCESS");
  else
    {
    TsWriteToView("LOG_FAILURE");
    return EXIT_FAILURE + 1 + iTestCount;
    }
  iTestCount++;
  }

return EXIT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2006-11-08 17:52:25  Darko Kolakovic 
 * $
 *****************************************************************************/
