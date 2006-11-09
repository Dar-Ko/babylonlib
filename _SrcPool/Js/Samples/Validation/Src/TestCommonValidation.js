/*$Workfile: TestCommonValidation.js$: implementation file
  $Revision: 2$ $Date: 2006-11-09 16:58:56$
  $Author: Darko Kolakovic$

  Console application used to test various validation operations.
  Copyright: CommonSoft Inc
  2006-11-08 Darko Kolakovic
*/

// Group=Examples

try
 {
  //Include files in the  main
  eval(Include("Src/TestBasicTypes.js"));
  eval(Include("Src/TestStrContent.js"));
  }
catch(err)
  {
  TsWriteToView(err.name + " " +
                (err.number & 0xFFFF) + ": " +
                err.message);
  throw err;
  }

//-----------------------------------------------------------------------------
/*Defines the entry point for the console application that verifies different
  validation routines.

  Returns: EXIT_SUCCESS, which represents a value of 0, if successful. Otherwise
  a non-zero error code is returned.
 */
function TestCommonValidation()
{
TsWriteToView("Validation Tests");

var funcTest = new Array(TestBasicTypes,
                         TestStrContent
                        );

var iTestCount = 0;
while (iTestCount < funcTest.length)
  {
  if ((funcTest[iTestCount] != undefined) && funcTest[iTestCount]() )
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
