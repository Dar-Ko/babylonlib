/*$Workfile: KDbgFILE.c$: implementation file
  $Revision: 5$ $Date: 2005-06-21 10:11:26$
  $Author: Darko Kolakovic$

  Dumps the current device-context attributes
  Copyright: CommonSoft Inc.
  D.Kolakovic Jan. 2k
 */

/* Group=Diagnostic                                                          */

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#ifdef _DEBUG
  #ifdef _MSC_VER
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
  #endif

#include <StdIO.h>    /*FILE struct*/
#ifndef TRACE
  #include "KTrace.h" /*TRACE macro*/
#endif


#ifdef _MSC_VER /*Microsoft Visual Studio*/
  #ifdef  _WIN32
    #pragma message( "Compiling for Win32 " __FILE__ )
  #endif
  #define _DUMPFILE_TYPE    100
#elif __GNUC__  /*GNU C  Mingw32 package */
  #define _DUMPFILE_TYPE    100
#else  /*Unsupported structure */
  #define _DUMPFILE_TYPE 0
#endif

#ifdef __GNUC__  /*WindRiver+GNU C VXWORKS_VERSION*/
  #ifdef __INCstdioh
    #ifdef _DUMPFILE_TYPE
      #undef _DUMPFILE_TYPE
    #endif
    #define _DUMPFILE_TYPE    101
    #warning "Compiling for vxWorks."
  #endif
#endif
/* ////////////////////////////////////////////////////////////////////////// */

/*DumpFILE()----------------------------------------------------------------- */
/*Dumps the contents of FILE structure.
  FILE structure stores information about current state of stream. It is used
  in all stream I/O operations.

  Note: (ANSI C) FILE is an object type capable of recording all the information
  needed to control a stream, including its file position indicator, a pointer
  to its associated buffer (if any), an error indicator that records whether a
  read/write error has occured, and an end-of-file indicator that records
  whether the end of file has been reached.

  Win OS
    typedef struct _iobuf
      {
      char*   _ptr;
      int     _cnt;
      char*   _base;
      int     _flag;
      int     _file;
      int     _charbuf;
      int     _bufsiz;
      char*   _tmpfname;
    } FILE;
 */
void DumpFILE(FILE* fileStream /*[in] pointer to FILE structure*/)
{

#if _DUMPFILE_TYPE == 100 /*Microsoft, GNU */
  if (fileStream == NULL)
    TRACE0("FILE* fileStream = NULL;\n");
  else
    {
    TRACE1("FILE* @$%X\n\t{\n",fileStream);
    TRACE1("\t_ptr     = 0x%08lx\n", fileStream->_ptr     );
    TRACE1("\t_cnt     = %d\n"     , fileStream->_cnt     );
    TRACE1("\t_base    = %p\n"     , fileStream->_base    );
    TRACE1("\t_flag    = %d\n"     , fileStream->_flag    );
    TRACE1("\t_file    = %d\n"     , fileStream->_file    );
    TRACE1("\t_charbuf = %d\n"     , fileStream->_charbuf );
    TRACE1("\t_bufsiz  = %d\n"     , fileStream->_bufsiz  );
    TRACE1("\t_tmpfname= %s\n\t}\n", fileStream->_tmpfname);
    }
#endif

#if _DUMPFILE_TYPE == 101 /*WindRiver+GNU C VxWorks*/
  if (fileStream == NULL)
    TRACE0("FILE* fileStream = NULL;\n");
  else
    {
    TRACE1("FILE* @$%X\n  {\n",(unsigned int)fileStream);
    TRACE1("  Cur.pos  _p     = 0x%08lx\n", (unsigned long)fileStream->_p);
    TRACE1("  Buf.base _bf    = %p\n"     , fileStream->_bf._base );
    TRACE1("  Buf.Siz  _bf    = %d\n"     , fileStream->_bf._size );
    TRACE1("  Flags    _flags = %d\n"     , fileStream->_flags    );
    TRACE1("  Offset   _offset= %d\n"     , fileStream->_offset   );
    TRACE1("  Owner    taskId = %d\n  }\n", fileStream->taskId    );
    }
#endif

}

/*DumpFILEOrigin()----------------------------------------------------------------- */

/*Dumps textual presentation of different origin flags used by fseek().
  The argument origin must be one of the following constants, defined in StdIO.h:

    SEEK_CUR  Current position of file pointer
    SEEK_END  End of file
    SEEK_SET  Beginning of file

  Remarks
  The fseek function moves the file pointer (if any) associated with stream to a new
  location that is offset bytes from origin. The next operation on the stream takes
  place at the new location. On a stream open for update, the next operation can be
  either a read or a write.
  You can use fseek to reposition the pointer anywhere in a file. The pointer can also
  be positioned beyond the end of the file. fseek clears the end-of-file indicator and
  negates the effect of any prior ungetc calls against stream.

  When a file is opened for appending data, the current file position is determined by
  the last I/O operation, not by where the next write would occur. If no I/O operation
  has yet occurred on a file opened for appending, the file position is the start of
  the file.

  For streams opened in text mode, fseek has limited use, because carriage
  return—linefeed translations can cause fseek to produce unexpected results. The only
  fseek operations guaranteed to work on streams opened in text mode are:

  Seeking with an offset of 0 relative to any of the origin values.
  Seeking from the beginning of the file with an offset value returned from
  a call to ftell.

  A binary stream does not meaningfully support fseek( ) calls with a <I>whence</I>
  value of SEEK_END, because some implementations have padding zeroes at the end
  of a file.

  Also in text mode, CTRL+Z is interpreted as an end-of-file character on input.
  In files opened for reading/writing, fopen and all related routines check for
  a CTRL+Z at the end of the file and remove it if possible. This is done because
  using fseek and ftell to move within a file that ends with a CTRL+Z may cause
  fseek to behave improperly near the end of the file.
 */
void DumpFILEOrigin(long offset, /*[in] number of bytes from origin*/
                    int  origin  /*[in] initial position           */
                   )
{

TRACE1("Move file pointer %ld bytes from the ",offset);
switch (origin)
  {
  case SEEK_SET: /*Beginning of file               */
    TRACE0("beginning of file\n");
    break;
  case SEEK_CUR: /*Current position of file pointer*/
    TRACE0("current position\n");
    break;
  case SEEK_END: /*End of file                     */
    TRACE0("end of file\n");
    break;
  default:       /*error                           */
    TRACE0("uknown origin\n");
   }
}

/* ////////////////////////////////////////////////////////////////////////// */
#endif  /*_DEBUG */

/*Various definitions follows:

  Microsoft (source file VC98\Include\STDIO.H)
  #ifdef _MSC_VER
    #ifndef _INC_STDIO
      #ifdef  _WIN32
        #define SEEK_SET    0
        #define SEEK_CUR    1
        #define SEEK_END    2
        #ifndef _FILE_DEFINED
          struct _iobuf
            {
            char *_ptr;
            int   _cnt;
            char *_base;
            int   _flag;
            int   _file;
            int   _charbuf;
            int   _bufsiz;
            char *_tmpfname;
            };
          typedef struct _iobuf FILE;
          #define _FILE_DEFINED
        #endif
      #endif
    #endif
  #endif

  GNU Mingw32 package (source file mingw32\sys-include\StdIO.h)
  #ifdef __GNUC__
    #ifndef _STDIO_H_
       struct _iobuf
         {
         char *_ptr;
         int   _cnt;
         char *_base;
         int   _flag;
         int   _file;
         int   _charbuf;
         int   _bufsiz;
         char *_tmpfname;
         } FILE;
    #endif
  #endif

  WindRiver Systems vxWorks  (source file target\h\StdIO.h)
  #ifdef __GNUC__
    #ifndef __INCstdioh
      typedef struct obj_core		/ * OBJ_CORE * /
        {
        struct obj_class *pObjClass;	/ * pointer to object's class * /
        } OBJ_CORE;
      struct __sbuf          / *stdio buffers * /
        {
        uchar_t * _base;     / *base address of {std,unget,line} buffer * /
        int	      _size;     / *size of the buffer * /
        };
      typedef struct __sFILE
        {
        OBJ_CORE objCore;   / *file pointer object core           * /
        uchar_t* _p;        / *current position in (some) buffer  * /
        int      _r;        / *read space left for getc()         * /
        int      _w;        / *write space left for putc()        * /
        short    _flags;    / *flags, below;this FILE is free if 0* /
        short    _file;     / *fileno, if Unix descriptor, else -1* /
        struct __sbuf _bf;  / *buffer (at least 1 byte,if !NULL)  * /
        int      _lbfsize;  / *0 or -_bf._size, for inline putc   * /
        struct __sbuf _ub;  / *ungetc buffer                      * /
        uchar_t* _up;       / *old _p if _p is doing ungetc data  * /
        int      _ur;       / *old _r if _r counting ungetc data  * /
        uchar_t  _ubuf[3];  / *guarantee an ungetc() buffer       * /
        uchar_t  _nbuf[1];  / *guarantee a getc() buffer          * /
        struct __sbuf _lb;  / *buffer for fgetline()              * /
        int      _blksize;  / *stat.st_blksize (may be!=_bf._size)* /
        int      _offset;   / *current lseek offset               * /
        int      taskId;    / *task that owns this file pointer   * /
        } FILE;
    #endif
  #endif

 */

/*****************************************************************************
 *$Log: 
 * 5    Biblioteka1.4         2005-06-21 10:11:26  Darko Kolakovic Example
 * 4    Biblioteka1.3         2005-04-29 00:11:26  Darko           Comment
 * 3    Biblioteka1.2         2002-01-29 22:20:13  Darko           Used lbraries
 *      notes 
 * 2    Biblioteka1.1         2001-07-11 21:50:31  Darko           
 * 1    Biblioteka1.0         2001-06-08 23:01:43  Darko           
 *$$
 * Version 2 User: Dkolakovic   Date: 4/11/01    Time: 6:31p Comments
 * Version 1 User: Dkolakovic   Date: 4/11/01    Time: 10:55a  Dump VxWorks FILE struct
 * Apr. 2k1 verified with GNU D.K.
 * Jan. 95 created D.K.
 *****************************************************************************/
