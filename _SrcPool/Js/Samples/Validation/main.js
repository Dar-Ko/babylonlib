/*$Workfile: main.js$: script file
  $Revision: 2$ $Date: 2006-11-08 17:52:56$
  $Author: Darko Kolakovic$

  Script used to test various validation operations.
  Copyright: CommonSoft Inc
  2006-11-08 Darko Kolakovic
*/

try
  {
  // Group=Examples

  //Definition of the argument values for the exit() function
  /*const*/ var EXIT_SUCCESS = 0;
  /*const*/ var EXIT_FAILURE = 1;
  //Definition of the successful results
  /*const*/ var S_OK         = 0;
  /*const*/ var S_FALSE      = 1;
  /*const*/ var NO_ERROR     = 0;
  //Error codes
  /*const*/ var ERROR_SUCCESS = 0; //no errors
  /*const*/ var EOF = (-1); //'End of File' tags end of a stream

  eval(Include("Src/TestCommonValidation.js"));

  main(); //the test invocation
  }
catch(err)
  {
  TsWriteToView(err.name + " " +
                (err.number & 0xFFFF) + ": " +
                err.message);
  }

//main()-----------------------------------------------------------------------

/*Defines the entry point for the script that verifies various validaton
  routines.

  Returns: EXIT_SUCCESS, which represents a value of 0, if successful. Otherwise
  a non-zero error code is returned.
 */
function main()
{
TsWriteToView("Start Validation Tests");
var nRetCode = EXIT_SUCCESS;
try
  {
  nRetCode = TestCommonValidation();
  }
catch(error)
  {
  TsWriteToView("Failure " + error.name + " " +
                (error.number & 0xFFFF) + ": " + error.message);
  nRetCode = EXIT_FAILURE;
  }
return nRetCode;
}

///////////////////////////////////////////////////////////////////////////////
//Helpers
//------------------------------------------------------------------------------
/*Display a line of the text.
  Note: Microsoft Windows specific (Win32)
  Requires Microsoft Windows Script Host (WSH) engine.
 */
function TsWriteToView(szMessage //[in] text do be displayed
                      )
{
if (szMessage != undefined)
  //Outputs text to either a message box or the command console window.
  WScript.Echo(szMessage);
}

//-----------------------------------------------------------------------------
/*
  Note: Microsoft Windows specific (Win32)
  Requires Microsoft ActiveX to access the file system, JScript Host 5.0.
 */
function Include(szFileName //[in] name of the file to import
                )
{
try
  {
  if(szFileName == undefined || szFileName == "")
    {
    //error code = 5009
    var szFileName = "szFileName";
    errorObj = new Error(0x800A1391, "undefined or empty!");
    throw errorObj;
    }

  fso = new ActiveXObject("Scripting.FileSystemObject");
  fileImport = fso.OpenTextFile(szFileName);
  strImport = fileImport.ReadAll();
  fileImport.Close();
  return strImport;
  }
catch(error)
  {
  if (error instanceof Error)
    {
    if((error.number & 0xFFFF) == 76) //Path not found
      {
      SetWorkingDirectory(); //TODO: Change current directory
      }
    TsWriteToView("Include '" + szFileName +  "' " +
                 error.name + " " + (error.number & 0xFFFF) + ": " +
                 error.message );
    }
  else
    TsWriteToView("Error: " + error);
  }
}

//-----------------------------------------------------------------------------
/*Changes the current active directory if the new direcrory is specfied, 
  otherwise only displays the current active directory.
  Requires Microsoft Windows Script Host (WSH) 5.6.
 */
function SetWorkingDirectory(szWorkingDirectory //[in] new active directory
                            )
{
var objShell = WScript.CreateObject ("WScript.Shell");
TsWriteToView(objShell.CurrentDirectory); //Displays the current active directory
if ((szWorkingDirectory != undefined) && (szWorkingDirectory.length >0) )
  objShell.CurrentDirectory = szWorkingDirectory;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2006-11-08 15:46:59  Darko Kolakovic
 * $
 *****************************************************************************/
