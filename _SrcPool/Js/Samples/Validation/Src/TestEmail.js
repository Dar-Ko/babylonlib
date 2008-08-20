/*$RCSfile: TestEmail.js,v $: script file
  $Revision: 1.2 $ $Date: 2008/08/20 21:34:02 $
  $Author: ddarko $

  Test eMail address validation
  Copyright: CommonSoft Inc.
  2008-08-19 Darko Kolakovic
*/

// Group=Examples
//-----------------------------------------------------------------------------
/*Function validates eMail address

  Returns: true if successful, otherwise returns false.
 */

function TestEmail()
{
//debugger;

TsWriteToViewLn("TestEmail()");
//TESTENTRY logEntry =
//  {_T("IsLeapYear()"), _T("KTime.h"), false};

var bRes = true;

try
  {
  var arrEmail = new Array();
  var arrResult = new Array();

  arrEmail [ 0] = null;  //null objectEmpty URI
  arrResult[ 0] = false;
  //arrEmail[ 1] is undefined
  arrResult[ 1] = false;
  arrEmail [ 2] = ""; //empty address
  arrResult[ 2] = false;
  arrEmail [ 3] = "bussh"; //dummy address
  arrResult[ 3] = false;
  arrEmail [ 4] = "bussh.wmd"; //dummy domain
  arrResult[ 4] = false;
  arrEmail [ 5] = "pinocchio@bussh.wmd"; //dummy address
  arrResult[ 5] = true;
  arrEmail [ 6] = "mono.clingon@ .info" //bad address
  arrResult[ 6] = false;
  arrEmail [ 7] = ".clingon@dummy.info" //bad address" //
  arrResult[ 7] = false;
  arrEmail [ 8] = "willy clingon@dummkopf.info" //malformed address
  arrResult[ 8] = false;
  arrEmail [ 9] = "willy clingon@dummkopf. " //malformed address
  arrResult[ 9] = false;
  arrEmail [10] = "willy_clingon@mon@dummkopf.info" //malformed address
  arrResult[10] = false;
  arrEmail [11] = "Orbis@urbis.va@cnn.com" //malformed address
  arrResult[11] = false;
  arrEmail [12] = "Special%char^in2$@money.tv" //good
  arrResult[12] = true;
  arrEmail [13] = "mar.sea.zee.cois@root.foot.sot.com" //good
  arrResult[13] = true;
  arrEmail [14] = "orca@sea.za" //good
  arrResult[14] = true;
  arrEmail [15] = "willy_clingon@127.0.0.69" //IP address
  arrResult[15] = true;
  arrEmail [16] = "willy.clingon@dummkopf.info" //good
  arrResult[16] = true;

  if (arrEmail.length != arrResult.length)
    {
    TsWriteToViewLn("Invalid test cases! Failed to validate function.");
    return false;
    }

  if(!isEmail)
    {
    TsWriteToViewLn("Unkonwn function isEmail()!");
    bRes = false;
    }

  var i = 0;
  while ((i < arrEmail.length) && bRes)
    {
    TsWriteToView("" + i + ". \'" + arrEmail[i] +"\' is " +
                 (arrResult[i] ? "" : "not ") + "valid: ");
    try
      {
      bRes = (isEmail(arrEmail[i]) == arrResult[i]);
      }
    catch(err)
      {
      bRes = (arrResult[i] == false);
      }

    TsWriteToViewLn("" + bRes + ".");
    i++;
    }

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
 * $Log: TestEmail.js,v $
 * Revision 1.2  2008/08/20 21:34:02  ddarko
 * *** empty log message ***
 *
 * Revision 1.1  2008/08/19 21:31:33  ddarko
 * Validate function
 *
 *****************************************************************************/
