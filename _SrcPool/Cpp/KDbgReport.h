#ifdef __cplusplus
extern "C" {
#endif


#ifdef _DEBUG
  int __cdecl DbgReport(LPCTSTR szModule, LPCTSTR szFormat, ... );
#else
  __inline int __cdecl DbgReport(LPCTSTR szModule, LPCTSTR szFormat, ... ) {}
#endif

#ifdef __cplusplus
} // extern "C"
#endif