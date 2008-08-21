/*$RCSfile: TestEmail.js,v $: script file
  $Revision: 1.3 $ $Date: 2008/08/21 20:16:06 $
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
  arrEmail [ 8] = "willy clingon@simple.us" //malformed address
  arrResult[ 8] = false;
  arrEmail [ 9] = "willy clingon@dummkopf.info" //malformed address
  arrResult[ 9] = false;
  arrEmail [10] = "willy clingon@dummkopf. " //malformed address
  arrResult[10] = false;
  arrEmail [11] = "willy_clingon@mon@dummkopf.info" //malformed address
  arrResult[11] = false;
  arrEmail [12] = "Orbis@urbis.va@cnn.com" //malformed address
  arrResult[12] = false;
  arrEmail [13] = "Orbis[urbis].va@cnn.com" //unacceptable characters
  arrResult[13] = false;
  arrEmail [14] = "Orbis<urbis>.va@cnn.com" //unacceptable characters
  arrResult[14] = false;
  arrEmail [15] = "Orbis(urbis).va@cnn.com" //unacceptable characters
  arrResult[15] = false;
  arrEmail [16] = "Orbis,urbis;va:all@cnn.lay" //unacceptable characters
  arrResult[16] = false;
  arrEmail [17] = "Orbis\\urbis.va@cnn.com" //unacceptable characters
  arrResult[17] = false;
  arrEmail [18] = "Special%char^in2$@money.tv" //good
  arrResult[18] = true;
  arrEmail [19] = "mar.sea.zee.cois@root.foot.sot.com" //good
  arrResult[19] = true;
  arrEmail [20] = "orca@sea.za" //good
  arrResult[20] = true;
  arrEmail [21] = "willy_clingon@127.0.0.69" //IP address
  arrResult[21] = true;
  arrEmail [22] = "willy.clingon@dummkopf.info" //good
  arrResult[22] = true;
  arrEmail [23] = "69?willy.nilly@now.hop" //good
  arrResult[23] = true;
  arrEmail [24] = "c2!.!_c-d#q$$4%&co\'lo*.uh.+-mac_yu=5?A.%^Hat~~~.`.{0|}~&@o-keff.co" //good
  arrResult[24] = true;
  arrEmail [25] = "coff@o'keff.co" //good
  arrResult[25] = true;

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
 * Revision 1.3  2008/08/21 20:16:06  ddarko
 * fixed regex
 *
 * Revision 1.2  2008/08/20 21:34:02  ddarko
 * *** empty log message ***
 *
 * Revision 1.1  2008/08/19 21:31:33  ddarko
 * Validate function
 *
 *****************************************************************************/
