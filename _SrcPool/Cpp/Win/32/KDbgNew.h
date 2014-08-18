#include <malloc.h> //Note: include before crtdbg.h
#include <stdlib.h>

#ifdef __MSVC
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h> //_malloc_dbg and _free_dbg

/*you can dump memory leak information by including the following statement in
  your program, typically immediately before the program exits:
      _CrtDumpMemoryLeaks();
 If your program can exit from multiple locations, instead of putting a call
 to _CrtDumpMemoryLeaks at each possible exit, you can include the following
 call at the beginning of your program:
      _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
 This statement automatically calls _CrtDumpMemoryLeaks when your program exits.
 If you use a library, it may reset the output to another location. In that
 case, you can set the output location back to the Output window using the
 following statement:
      _CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_DEBUG );

*/

#endif

#ifdef __cplusplus

#include <stdlib.h>
#include <iostream>

void* operator new(size_t sz, char* szFileName, int nLine);
void* operator new(size_t sz, wchar_t* szFileName, int nLine);

//-----------------------------------------------------------------------------
/*
  Ref.: "Memory Leak Detection Enabling" http://msdn.microsoft.com/en-us/library/e5ewb1h3(v=VS.90).aspx
  "Finding Memory Leaks Using the CRT Library" http://msdn.microsoft.com/en-us/library/x98tx3cf.aspx




 */
inline void* operator new(size_t sz, char* szFileName, int nLine)
{
void *pObj = malloc(sz);
// do something with file and line maybe
std::cout << "File is " << lpszFileName << "    Line is " << nLine << std::endl;
return pObj;
}

//-----------------------------------------------------------------------------
/*
 */
inline void* operator new(size_t sz, wchar_t* szFileName, int nLine)
{
void *pObj = malloc(sz);
// do something with file and line maybe
std::cout << L"File is " << lpszFileName << L"    Line is " << nLine << std::endl;
return pObj;
}

//-----------------------------------------------------------------------------
/*
The calls you are looking for (that MFC wraps) are in <crtdbg.h>

explicit call to _CrtDumpMemoryLeaks(...)

or 

_CrtSetDbgFlag(...) turning on _CRTDBG_LEAK_CHECK_DF 
 */
inline void operator delete(void* p)
{
free(p);
}

#define DEBUG_NEW new(__FILE__, __LINE__)
#define new DEBUG_NEW


#ifdef _DEBUG   
  #ifndef DBG_NEW
    #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
    #define new DBG_NEW
  #endif
#endif  // _DEBUG  MSDN

int main()
{
  int *p = new int;  // for example
  delete p;
}

#endif //__colusplus
