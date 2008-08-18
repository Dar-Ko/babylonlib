/*$Workfile: TestBasicTypes.js$: script file
  $Revision: 1$ $Date: 2006-11-09 17:58:29$
  $Author: Darko Kolakovic$

  Test basic types validation
  Copyright: CommonSoft Inc.
  2006-11-09 Darko Kolakovic
*/

// Group=Examples
//-----------------------------------------------------------------------------
/*Function validates basic types

  Returns: true if successful, otherwise returns false.
 */

function TestBasicTypes()
{
//debugger;

TsWriteToViewLn("TestBasicTypes()");
//TESTENTRY logEntry =
//  {_T("IsLeapYear()"), _T("KTime.h"), false};

var bRes = true;

try
  {
  var strText = null;
  TsWriteToView("isBlank(strText = " + strText + ")");
  bRes = isBlank(strText);
  TsWriteToViewLn(" = " + bRes);

  if(bRes)
    {
    try
      {
      //Defined as null
      TsWriteToView("isString(strText = " + strText + ")");
      bRes = isString(strText);
      TsWriteToViewLn(" = " + bRes);
      }
    catch(error)
      {
      TsWriteToView(" -> exception ");
      TsWriteToViewLn(error.name + ": " + error.message);
      bRes = true; //Proceed with testing
      }
    }
  else
    return false;

  if(bRes)
    {
    //Defined as an empty string
    strText = "";
    bRes = isBlank(strText);
    TsWriteToViewLn("isBlank(strText = \"\") = " + bRes);
    }
  else
    return false;

  if(bRes)
    {
    //Defined as an empty string
    bRes = isString(strText);
    TsWriteToViewLn("isString(strText = \"\") = " + bRes);
    }
  else
    return false;

  if(bRes)
    {
    //Defined as a string
    strText = "Some text";
    bRes = isBlank(strText);
    TsWriteToViewLn("isBlank(strText = \"" + strText + "\") = " + bRes);

    }
  else
    return false;

  if(!bRes)
    {
   //Defined as a string
    bRes = isString(strText);
    TsWriteToViewLn("isString(strText = \"" + strText + "\") = " + bRes);
    }
  else
    return false;

  if(bRes)
    {
    //Defined as a string
    bRes = isNumber(strText);
    TsWriteToViewLn("isNumber(strText = \"" + strText + "\") = " + bRes);
    }
  else
    return false;

  var d180;
  if(!bRes)
    {
    //Undefined variable
    bRes = isUndefined(d180);
    TsWriteToViewLn("isUndefined(" + d180 + ") = " + bRes);
    }
  else
    return false;

  if(bRes)
    {
    //Defined as a number
    d180 = 3.14/2.0;
    bRes = isUndefined(d180);
    TsWriteToViewLn("isUndefined(" + d180 + ") = " + bRes);
    }
  else
    return false;

  if(!bRes)
    {
    //Defined as a number
    bRes = isNumber(d180);
    TsWriteToViewLn("isNumber(" + d180 + ") = " + bRes);
    }
  else
    return false;

  if(bRes)
    {
    //Defined as null object
    strText = null;
    bRes = isUndefined(strText);
    TsWriteToViewLn("isUndefined(\"" + strText + "\") = " + bRes);
    }
  else
    return false;

  if(!bRes)
    {
    try
      {
      //Defined as null object
      TsWriteToView("isArray(\"" + strText + "\")");
      bRes = isArray(strText);
      TsWriteToViewLn(" = " + bRes);
      }
    catch(error)
      {
      TsWriteToView(" -> exception ");
      TsWriteToViewLn(error.name + ": " + error.message);
      bRes = false; //Proceed with testing
      }
    }
  else
    return false;

  var arrValue = new Array();
  if(!bRes)
    {
    try
      {
      //Defined as an array
      TsWriteToView("isArray(arrValue.length = " + arrValue.length + ")");
      bRes = isArray(arrValue);
      TsWriteToViewLn(" = " + bRes);
      }
    catch(error)
      {
      TsWriteToView(" -> exception ");
      TsWriteToViewLn(error.name + ": " + error.message);
      bRes = true; //Proceed with testing
      }
    }
  else
    return false;

  if (bRes)
    return true; //Successful test
  else
    return false; //Failed test

  bRes = true; //Successful test
  }
catch(error)
  {
  TsWriteToViewLn(error.name + ": " + error.message);
  bRes = false; //Failed test
  }

//logEntry.m_bResult = bHasSpace;
//LogTest(&logEntry);

TsWriteToViewLn(LOG_EOT);
return bRes;

}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2006-11-09 17:58:29  Darko Kolakovic
 * $
 *****************************************************************************/
