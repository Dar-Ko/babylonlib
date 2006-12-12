//$Workfile: KWndSize.js$: script file
//$Revision: 1$ $Date: 2004-10-01 22:10:34$
//$Author: Darko$
//
//Opens a new window with standardized dimensions
//Copyright: CommonSoft Inc
//2004-06-18 Darko Kolakovic

//-----------------------------------------------------------------------------
//Opens parent document in a new window with standard dimensions:
//          W x H
//  1. PC  640x480
//  2. PC  800x600
//    Netscape default with; height depends of the screen dimensions:
//     480, 600 and 768 gives window heights 300, 430 and 600
//  3. PC  580x600
//  4. Mac 470x600
function OpenWndStd(nType)
  {
  var strLookAndFeel = 'toolbar=yes,status=yes,scrollbars=yes,location=yes,menubar=yes,directories=yes';
  if(nType == 4)
    {
    strLookAndFeel = strLookAndFeel + ',width=470,height=600';
    window.open(document.location.toString(), //URL
                'WndSize4',                   //target attribute
                strLookAndFeel                //chrome and size
                )
    }
  else if(nType == 3)
    {
    strLookAndFeel = strLookAndFeel + ',width=580,height=600';
    window.open(document.location.toString(), //URL
                'WndSize3',                   //target attribute
                strLookAndFeel                //chrome and size
                )
    }
  else if(nType == 2)
    {
    strLookAndFeel = strLookAndFeel + ',width=800,height=600';
    window.open(document.location.toString(), //URL
                'WndSize2',                   //target attribute
                strLookAndFeel                //chrome and size
                )
    }
  else  //Default window size
    {
    strLookAndFeel = strLookAndFeel ;
    window.open(document.location.toString(), //URL
                'WndSize1',                   //target attribute
                strLookAndFeel + ',width=640,height=480'   //chrome and size
                )
    }
  }
//-----------------------------------------------------------------------------
//$Log: 
// 1    Biblioteka1.0         2004-10-01 22:10:34  Darko           
//$
