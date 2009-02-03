/*$RCSfile: KWinStrArray.h,v $: header file
  $Revision: 1.1 $ $Date: 2009/02/03 22:19:05 $
  $Author: ddarko $

  Array of CString objects.
  Note: Microsoft Windows specific (Win).
  Copyright: CommonSoft Inc
  2009-02-01 Darko Kolakovic
 */
// Group=Windows

#ifndef _KWINSTRARRAY_H_
    //$RCSfile: KWinStrArray.h,v $ sentry
  #define _KWINSTRARRAY_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#ifdef _WIN32 //Windows 32-bit platform
///////////////////////////////////////////////////////////////////////////////
//The CStringArray class supports arrays of CString objects.

  #ifndef _USE_MFC //Microsoft Fundation Classes Library (MFC)
    #include <afxcoll.h> //CStringArray class
    /*Note: CStringArray incorporates the IMPLEMENT_SERIAL macro to support
      serialization and dumping of its elements. If an array of CString objects
      is stored to an archive, either with an overloaded insertion operator or
      with the Serialize member function, each element is serialized in turn.
      CObject is the base class for MFC implementation of CStringArray.
     */
  #endif

  #ifndef _USE_ATL  //Microsoft Active Template Library (ATL)
    #include <atlcoll.h> //CAtlArray template
    /*CStringArray class supports arrays of CString objects.
      CStringT is the base class for the MFC/ATL CString class.
     */
    typedef CAtlArray<CString> CStringArray;
  #endif

#endif //_WIN32
///////////////////////////////////////////////////////////////////////////////
#endif  //_KWINSTRARRAY_H_
/*****************************************************************************
 * $Log: KWinStrArray.h,v $
 * Revision 1.1  2009/02/03 22:19:05  ddarko
 * Created
 *
 *****************************************************************************/
