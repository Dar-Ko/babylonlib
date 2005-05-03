/*UDirExeN.cpp
  Get directory of from the full file path
  Darko Kolakovic
  Jan 98
*/
#include <AfxWin.h>
#include "D_Func.h"

//GetExeDirectory()------------------------------------------------------------
/*Retrieves the full path for the executable file used to create the calling 
  process.
 */
CString GetExeDirectory()
{
CString strResult;
LPSTR szBuff = strResult.GetBuffer(_MAX_PATH);
      //Get path of the current module 
VERIFY(::GetModuleFileName(NULL, szBuff, _MAX_PATH));
GetFileDirectory(szBuff,szBuff,_MAX_PATH);
strResult.ReleaseBuffer();
TRACE1("Executable Directory is %s\n",strResult);
return strResult;
}
