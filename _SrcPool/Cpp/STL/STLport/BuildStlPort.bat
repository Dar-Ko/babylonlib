REM Visual Studio 2003 v7.1 build

REM Builds Release - stlport_vc71_static.lib
REM        DebugSTL - stlport_vc71_stldebug_static.lib
REM        ReleaseD - stlport_vc7146.dll; stlport_vc71.lib; stlport_vc71.exp
REM        DebugSTLD - stlport_vc71_stldebug46.dll; stlport_vc71_stldebug.lib; stlport_vc71_stldebug.exp

nmake /f src\vc71.mak clean all

REM install does the following :
REM  - copies STLport headers in "stlport" subdirectory of your compiler's INCLUDE directory;
REM  - copies STLport .lib files in your compiler's LIB directory;
REM  - copies STLport DLLs to Windows system directory so they can be found at runtime.

REM nmake -f src\vc71.mak clean install