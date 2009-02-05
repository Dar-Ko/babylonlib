*$RCSfile: KWinStrArray.h,v $: header file
  $Revision: 1.4 $ $Date: 2009/02/05 23:13:44 $
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

#ifdef _MSC_VER //Microsoft Visual Studio  Compilers
///////////////////////////////////////////////////////////////////////////////
//The CStringArray class supports arrays of CString objects.

  #ifdef _USE_MFC //Microsoft Fundation Classes Library (MFC)
    #pragma message ("  Using MFC CStringArray class")
    #include <afxcoll.h> //CStringArray class
    /*Note: CStringArray incorporates the IMPLEMENT_SERIAL macro to support
      serialization and dumping of its elements. If an array of CString objects
      is stored to an archive, either with an overloaded insertion operator or
      with the Serialize member function, each element is serialized in turn.
      CObject is the base class for MFC implementation of CStringArray.
     */
  #endif

  #ifdef _USE_ATL  //Microsoft Active Template Library (ATL)
    #include <atlcoll.h> //CAtlArray template
    /*CStringAtlArray class supports arrays of CString objects.
      CStringT is the base class for the MFC/ATL CString class.

      Note: In case that STL or ATL data containers are used to exchange data
      between dynamicaly linked library (DLL) and executibile module (EXE),
      insure that same C-Runtime library (CRT) is used in both. If such object
      is allocated in one module and freed in another one with different linkage
      to CRT (and therefore different heap), following error may occur:
          HEAP[some.exe]: Invalid Address specified to RtlValidateHeap( 003C0000, 003xxxxx )
          Windows has triggered a breakpoint in some.exe.
      Change project settings to use in both modules shared CRT library (/MD or /MDd
      for debug version). For Microsoft Visual Studio 2005 change next configuration:
          Configuration Properties | C/C++ | Code Generation | Runtime Library |
          Multi-threaded Debug DLL (/MDd) (or /MD for release build)
      Multi-threaded (/MT or /MTd for debug build) implies static linking to the
      C-Runtime library.
      Derived data types, like std::wstring or CString, manage its own memory
      management and implemetation differs from library to library.
      Better way is to use only basic types and to free objects where those are
      allocated.
     */
    typedef CAtlArray<CString> CStringAtlArray;
    #define _USE_STRINGATLARRAY 20090202 //Signals CStringAtlArray class usage

    #ifdef _USE_ATLSIMPLEARRAY
      #pragma message ("  Using ATL CSimpleArray template as CStringArray substitute.")
      #include <atlsimpcoll.h>  //CSimpleArray template
      /*CStringArray class supports arrays of CString objects.
        CStringT is the base class for the MFC/ATL CString class.

        Note: this implementation should be used when the array contains a small
        number of elements.

        See also: CSimpleArray
       */
      typedef CSimpleArray<CString> CStringArray;
    #else
      #pragma message ("  Using ATL CAtlArray template as CStringArray substitute.")
      #ifndef __ATLCOLL_H__
        #include <atlcoll.h> //CAtlArray template
      #endif
      /*CStringArray class supports arrays of CString objects.
        CStringT is the base class for the MFC/ATL CString class.

        Note: CStringArray copy construcor and assigment operator are private
        methods.

        Note: this implementation should be used when the array contains a large
        number of elements.

        See also: CAtlArray
       */
      typedef CAtlArray<CString> CStringArray;
    #endif
  #endif

#endif //_MSC_VER
///////////////////////////////////////////////////////////////////////////////
#endif  //_KWINSTRARRAY_H_
/*****************************************************************************
 * $Log: KWinStrArray.h,v $
 * Revision 1.4  2009/02/05 23:13:44  ddarko
 * Note about CRT library linkage
 *
 * Revision 1.3  2009/02/04 20:42:06  ddarko
 * CSimpleArray substitute
 *
 * Revision 1.2  2009/02/03 22:45:44  ddarko
 * Fixed preprocessor conditions
 *
 * Revision 1.1  2009/02/03 22:19:05  ddarko
 * Created
 *
 *****************************************************************************/
