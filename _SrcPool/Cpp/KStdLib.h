/*$Workfile: S:\_SrcPool\Cpp\KStdLib.h$: header file
  $Revision: 2$ $Date: 2004-12-06 16:21:55$
  $Author: Darko Kolakovic$

  ANSI Standard header file impostor.
  Declares a set of general utilities and defines attending macros and
  data types.
  Darko Kolakovic 2004-12-02
 */

#ifndef _KSTDLIB_H_
    /*$Workfile: S:\_SrcPool\Cpp\KStdLib.h$ sentry */
  #define _KSTDLIB_H_

#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files*/
  #pragma message ("   #include " __FILE__ )
#endif

/*///////////////////////////////////////////////////////////////////////////*/

#ifndef size_t
  #if sizeof((char *)0 - (char *)0) == sizeof(int)
    typedef unsigned int size_t;
  #else
    typedef unsigned long size_t;
  #endif
  #define size_t size_t
#endif

#ifndef div_t
  typedef struct
    {
    int quot;
    int rem;
    } div_t;
  #define div_t div_t
#endif

#ifndef ldiv_t
  typedef struct
    {
    long quot;
    long rem;
    } ldiv_t;
  #define ldiv_t ldiv_t
#endif

#ifndef NULL
  /*The manifest constant called 'null pointer' is a pointer initialized to zero.
    A manifest constant is a constant that is given a name so it can be defined
    differently under different computing environments.

    Note: In C++ the null pointer is guaranteed to compare unequal to a pointer
    to any valid object or function (except for pointers to based objects, which
    can have the same offset and still point to different objects).

    See also: ANSI 4.1.5, stddef.h
   */
  #define  NULL  ((void*) 0)
#endif

#ifndef EXIT_SUCCESS
  /*A manifest constant used as an argument to the function exit(), to indicate
    that the program executed successfully. The C standard does not define any
    particular value for this macro and the value defined does not necessarily
    correspond directly to the value returned by a program to the system.

    See also: stdlib.h
   */
  #define EXIT_SUCCESS    0
#endif

#ifndef EXIT_FAILURE
  /*A manifest constant used as an argument to the function exit(), to indicate
    that the program failed to execute properly. The C standard does not define
    any particular value for this macro and the value defined does not necessarily
    correspond directly to the value returned by a program to the system.

    See also: stdlib.h
   */
  #define EXIT_FAILURE    1
#endif

/*A manifest constant that indicates the largest pseudo-random number that
  can be returned by the function rand().
  The value defined here is 32767.

  See also: stdlib.h
*/
#define RAND_MAX 0x7FFF

/*Type definition of function passed to atexit() to be executed when the program
  terminates normally. This callback function cannot take parameters.
 */
typedef void (* PFUNC_ATEXIT)(void);

void    abort  (void);
int     abs    (int x);
int     atexit (PFUNC_ATEXIT pfAtExit);
double  atof   (const char* s);
int     atoi   (const char* s);
long    atol   (const char* s);
void*   bsearch(const void* key,
                const void* base,
                size_t nelem,
                size_t width,
                int (*fcmp)(/* const void*, const void* */));
void*   calloc (size_t nitems, size_t size);
div_t   div    (int numer, int denom);
void    exit   (int status);
void    free   (void* block);
char*   getenv (const char* name);
long    labs   (long x);
ldiv_t  ldiv   (long numer, long denom);
void*   malloc (size_t size);
void    qsort  (void *base,
                size_t nelem,
                size_t width,
                int (*fcmp)(/* const void *, const void * */));
int     rand   (void);
void*   realloc(void* block, size_t size);
void    srand  (unsigned seed);
double  strtod (const char* s, char** endptr);
long    strtol (const char* s, char** endptr, int radix);
unsigned long strtoul (const char* s, char** endptr, int radix);
int     system (const char* command);

/*///////////////////////////////////////////////////////////////////////////*/
/* Non-standard extensions

   Note: Macro __STDC__ expands to the constant 1, to signify that this is
         ANSI Standard C. (Whether that is actually true depends on what
         C compiler will operate on the output from the preprocessor.)
 */
#ifndef __STDC__

  #ifndef max
    /*Compares two values and returns the larger one.
      See also: KMathCst.h
     */
    #define max(a,b) (((a) > (b)) ? (a) : (b))
  #endif
  #ifndef min
    /*Compares two values and returns the smaller one.
      See also: KMathCst.h
     */
    #define min(a,b) (((a) < (b)) ? (a) : (b))
  #endif
#endif /*!__STDC__*/


/*///////////////////////////////////////////////////////////////////////////*/
#endif /*_KSTDLIB_H_                                                         */
/*****************************************************************************
 * $Log:
 *  6    Biblioteka1.5         2003-09-30 10:15:56  Darko           formatting
 *  5    Biblioteka1.4         2002-01-25 16:56:07  Darko           Updated
 *       comments
 *  4    Biblioteka1.3         2001-08-19 23:51:30  Darko           Butyfier
 *  3    Biblioteka1.2         2001-07-11 22:50:12  Darko
 *  2    Biblioteka1.1         2001-06-08 23:49:08  Darko           VSS
 *  1    Biblioteka1.0         2000-08-13 15:55:31  Darko
 * $
 *****************************************************************************/

/*DOS extension
#if !__STDC__


    #ifndef NULL
      #if defined(__TINY__) || defined(__SMALL__) || defined(__MEDIUM__)
        #define NULL    0
      #else
        #define NULL    0L
      #endif
    #endif

    / * Variables * /
    extern  int             _doserrno;
    extern  char**          environ;
    extern  int             errno;
    extern  int             _fmode;
    extern  unsigned char   _osmajor;
    extern  unsigned char   _osminor;
    extern  unsigned        _psp;
    extern  char*           sys_errlist[];
    extern  int             sys_nerr;
    extern  unsigned int    _version;

    int     __abs__(int x);          / * This is an in-line function * /
    #define abs(x)          __abs__(x)
    #define atoi(s)         ((int) atol (s))

    #define random(num)     (rand() % (num))
    #define randomize()     srand((unsigned)time(NULL))

    char* ecvt     (double value, int ndig, int* dec, int* sign);
    void  _exit    (int status);
    char* fcvt     (double value, int ndig, int* dec, int* sign);
    char* gcvt     (double value, int ndec, char* buf);
    char* itoa     (int value, char* string, int radix);
    void* lfind    (const void* key, const void* base,
                             size_t* num, size_t width,
                             int (*fcmp)(/ * const void*, const void* * /));

    unsigned long _lrotl(unsigned long val, int count);
    unsigned long _lrotr(unsigned long val, int count);

    void*   lsearch  (const void* key, void* base,
                             size_t* num, size_t width,
                             int (*fcmp)(/ * const void* , const void* * /));
    char*   ltoa     (long value, char* string, int radix);
    int     putenv   (const char* name);

    unsigned _rotl   (unsigned value, int count);
    unsigned _rotr   (unsigned value, int count);

    void    swab     (char* from, char* to, int nbytes);
    char*   ultoa    (unsigned long value, char* string, int radix);
#endif / *!__STDC__* /
*/