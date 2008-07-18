/*$Workfile: KGetPrTy.cpp$: implementation file
  $Revision: 1.2 $ $Date: 2008/07/18 21:31:36 $
  $Author: ddarko $

  Retrieve current state of a scripting engine
  Copyright: CommonSoft Inc.
  Darko Kolakovic 2008-07-18
 */

#include "stdafx.h"
#include "KHresult.h" //CHresult class

#if !defined(_ATL_VER)
  #error ERROR: This method requires ATL!
#endif


// Group=Windows
#if _MSC_VER < 1300
  //Microsoft Visual C/C++ 6.0
  #pragma warning(disable: 4290) //warning C4290: C++ Exception Specification ignored
#endif

//-----------------------------------------------------------------------------
/*Obtains the state of a scripting engine (for example jscript or vbscript).
  This enumeration is used by the IActiveScript::GetScriptState ,
  IActiveScript::SetScriptState , and IActiveScriptSite::OnStateChange methods.

      typedef enum tagSCRIPTSTATE {
        SCRIPTSTATE_UNINITIALIZED = 0, //Script has just been created, but has not
          //yet been initialized using an IPersist* interface and
          //IActiveScript::SetScriptSite .
        SCRIPTSTATE_INITIALIZED   = 5, //Script has been initialized, but is not
          //running (connecting to other objects or sinking events) or executing
          //any code. Code can be queried for execution by calling
          //the IActiveScriptParse::ParseScriptText method.
        SCRIPTSTATE_STARTED       = 1, //Script can execute code, but is not yet
          //sinking the events of objects added by
          //the IActiveScript::AddNamedItem method.
        SCRIPTSTATE_CONNECTED     = 2, //Script is loaded and connected for
          //sinking events.
        SCRIPTSTATE_DISCONNECTED  = 3, //Script is loaded and has a run-time
          //execution state, but is temporarily disconnected from sinking events.
        SCRIPTSTATE_CLOSED        = 4  //Script has been closed. The scripting
          //engine no longer works and returns errors for most methods.
        } SCRIPTSTATE;

  The IActiveScript interface provides the methods necessary to initialize the
  scripting engine. The scripting engine must implement the IActiveScript
  interface.

  - If _ATL_NO_EXCEPTIONS is not defined in an MFC project, this function throws
    a CMemoryException or a COleException based on the value of the HRESULT.
  - If _ATL_NO_EXCEPTIONS is not defined in an ATL project, the function throws
    a CAtlException.
  - If _ATL_NO_EXCEPTIONS is defined, the function causes an assertion failure
    instead of throwing an exception.
  - In all cases, this function traces the HRESULT to the debugger.

  Returns: current state of a scripting engine.

  See also: IActiveScript interface

  Note:  Microsoft Windows specific (Win32)
         and uses Active Template Library (ATL).
 */
SCRIPTSTATE GetScriptState(IActiveScriptPtr pActiveScript //[in]
                          ) throw(CException)
{
TRACE("Active Script state: ");
SCRIPTSTATE ssResult;
CHresult hResult(S_OK);
if(pActiveScript != NULL)
  {
  /*IActiveScript::GetScriptState retrieves the current state of the scripting
    engine.
    This method can be called from non-base threads without resulting in
    a non-base callout to host objects or to the IActiveScriptSite interface.
    Returns S_OK if successful, or E_POINTER if an invalid pointer was specified.
  */
  hResult = pActiveScript->GetScriptState(&ssResult);
  #ifdef _DEBUG
    switch (ssResult)
      {
      case SCRIPTSTATE_UNINITIALIZED: TRACE("  SCRIPTSTATE_UNINITIALIZED\n"); break;
      case SCRIPTSTATE_INITIALIZED  : TRACE("  SCRIPTSTATE_INITIALIZED\n"  ); break;
      case SCRIPTSTATE_STARTED      : TRACE("  SCRIPTSTATE_STARTED\n"      ); break;
      case SCRIPTSTATE_CONNECTED    : TRACE("  SCRIPTSTATE_CONNECTED\n"    ); break;
      case SCRIPTSTATE_DISCONNECTED : TRACE("  SCRIPTSTATE_DISCONNECTED\n" ); break;
      case SCRIPTSTATE_CLOSED       : TRACE("  SCRIPTSTATE_CLOSED\n"       ); break;
      default:  TRACE("  uknown state (%d)\n", (int)ssResult);
      }
  #endif
  }
else
  {
  TRACE("  undefined. IActiveScriptPtr is invalid!\n");
  ASSERT(pActiveScript != NULL);
  ssResult = SCRIPTSTATE(-1);
  hResult = E_POINTER;
  }
return ssResult;
}
///////////////////////////////////////////////////////////////////////////////
#if _MSC_VER < 1300
  //Microsoft Visual C/C++ 6.0
  #pragma warning(default: 4290) //warning C4290: C++ Exception Specification ignored
#endif

/*****************************************************************************
 * $Log: KGetScriptState.cpp,v $
 * Revision 1.2  2008/07/18 21:31:36  ddarko
 * ATL 3.0
 *
 * Revision 1.1  2008/07/17 21:38:22  ddarko
 * MSVC6.0 build
 *
 *****************************************************************************/
