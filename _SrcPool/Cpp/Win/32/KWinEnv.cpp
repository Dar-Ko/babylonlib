/*$RCSfile: KWinEnv.cpp,v $: implementation file
  $Revision: 1.2 $ $Date: 2009/07/02 19:38:39 $
  $Author: ddarko $

  MS Windows Environment Variable Handler
  2007-07-30
 */
#ifdef _WIN32

  #ifdef _USE_ATL
    //Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)
    //or preprocessor reports unpaired #endif directive

    #include "stdafx.h" //Standard system header files
  #else
    #include <windows.h>
  #endif

  #if defined _ATL_VER
    #include "KTraceAtl.h"
  #endif

  #ifndef TRACE
    #ifndef _T
      #include "KTChar.h"
    #endif
      #include "KTrace.h"
  #endif

//------------------------------------------------------------------------------
/*Return value of an enviroment variable not larger than CATENVMAX characters.
 */
CString GetEnvVariable(LPCTSTR szName //[in] name of the enviroment variable
                       )
{
const int ENVMAXLENGTH = 512;
CString strResult;
if (szName != NULL)
  {
  TCHAR lpBuffer[ENVMAXLENGTH];     //buffer that receives required environment variable
  unsigned int nSize; //size of the buffer

  nSize = GetEnvironmentVariable(szName, lpBuffer, ENVMAXLENGTH);
  if (nSize == 0)
    strResult = ""; //Buffer is too small. TODO: dynamic buffer
  else
    {
    strResult = lpBuffer;
    }
  }
return strResult;
}

#endif //_WIN32

///////////////////////////////////////////////////////////////////////////////
/*******************************************************************************
 *$Log: KWinEnv.cpp,v $
 *Revision 1.2  2009/07/02 19:38:39  ddarko
 *Replaced TRACE with ATL header
 *
 *Revision 1.1  2009/03/02 17:47:57  ddarko
 *Moved from local repository
 *
 ******************************************************************************/
