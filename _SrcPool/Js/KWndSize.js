//$Workfile: KWndSize.js$: script file
//$Revision: 2$ $Date: 2006-12-13 13:20:33$
//$Author: Darko Kolakovic$
//
//Opens a new window with standardized dimensions
//Copyright: CommonSoft Inc
//2004-06-18 Darko Kolakovic

//-----------------------------------------------------------------------------
/*Opens parent document in a new window with standard dimensions:
            W x H
    1. PC  640x480
    2. PC  800x600
      Netscape default with; height depends of the screen dimensions:
       480, 600 and 768 gives window heights 300, 430 and 600
    3. PC  580x600
    4. Mac 470x600

  Returns a reference to the new window object.
 */
function OpenWndStd(nType, //=1 [in] one of predefined window size types [1, 4]
                    strUrl //[in] URL of the document to display. If no URL is
                           //specified, a new window with current document
                           //is displayed.
                   )
  {
  if (nType == null)
    nType = 1;
  if (strUrl == null)
    strUrl = document.location.toString();
  var strLookAndFeel = 'toolbar=yes,status=yes,scrollbars=yes,location=yes,menubar=yes,directories=yes';
  if(nType == 4)
    {
    return window.open(strUrl,       //URL
                       'WndSize4',   //target name
                       strLookAndFeel + ',width=470,height=600'//style and size
                       );
    }
  else if(nType == 3)
    {
    return window.open(strUrl,       //URL
                       'WndSize3',   //target name
                       strLookAndFeel + ',width=580,height=600'//style and size
                       );
    }
  else if(nType == 2)
    {
    return window.open(strUrl,       //URL
                       'WndSize2',   //target name
                       strLookAndFeel + ',width=800,height=600'//style and size
                       );
    }
  else  //Default window size
    {
    return window.open(strUrl,       //URL
                       'WndSize1',   //target name
                       strLookAndFeel + ',width=640,height=480'//style and size
                       );
    }
  }
///////////////////////////////////////////////////////////////////////////////
/*$Log: 
/* 2    Biblioteka1.1         2006-12-13 13:20:33  Darko Kolakovic strUrl argument
/* 1    Biblioteka1.0         2004-10-01 23:10:34  Darko           
/*$
 */
