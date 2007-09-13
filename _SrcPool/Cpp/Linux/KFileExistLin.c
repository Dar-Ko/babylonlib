/*$Workfile: $: implementation file
  $Revision: 1.1 $ $Date: 2007/09/12 20:40:58 $
  $Author: ddarko $

  Checks if file exist.
  Jan. 1987 Darko Kolakovic
*/

/* Group=Linux                                                               */

#include <sys/stat.h>
//#include <unistd.h> POSIX?
//#include <stdio.h>
#include "KTypedef.h" /*bool typedef*/ //#include <sys/types.h>

#ifndef POSIX
//-----------------------------------------------------------------------------
/*Verifies if file exist in the current folder.

  Returns true if file exist or false if not and errno is set appropriately.

  Note: Linux specific (LINUX)
*/
bool IsFileExisting(LPCSTR szFileName //[in] null-terminated file name
                   )
{
if (szFileName != NULL)
  {
  /*Is the file one of the existing files?*/
  struct stat stTemp;

  if (stat(szFileName, &stTemp) == 0)
    /*S_IFMT  0x0170000 bitmask for the file type bitfields
      S_IFREG 0x0100000 regular file
    */
   return ((stTemp.st_mode & S_IFMT) == S_IFREG);
  }

/*If stat() returned -1 on an error, check errno.*/
return (false);
}

#else //POSIX

bool IsFileExisting(LPCSTR szFileName //[in] null-terminated file name
                   )
{
if (szFileName != NULL)
  {
  /*Is the file one of the existing files?*/
  struct stat stTemp;

  if (stat(szFileName, &stTemp) == 0)
    return (((S_ISREG(sbuf.st_mode)) > 0);
  }

/*If stat() returned -1 on an error, check errno.*/
return (false);
}
#endif //POSIX

unsigned long GetFileSize(const char *filename)
{
   struct stat sbuf;

   if (stat(filename, &sbuf) == -1)
      return(0);
   errno = 0;
   return(sbuf.st_size);
}

int IsDir(LPCSTR dirname)
{

   struct stat sbuf;

   if (stat(dirname, &sbuf) == 0)
     return  (S_ISDIR(sbuf.st_mode)); //POSIX macro
   return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
/*stat structure contains information about file.

    struct stat
      {
      dev_t         st_dev;      // device Dos
      ino_t         st_ino;      // inode Dos
      mode_t        st_mode;     // protection Dos
      nlink_t       st_nlink;    // number of hard links Dos
      uid_t         st_uid;      // user ID of owner Dos
      gid_t         st_gid;      // group ID of owner Dos
      dev_t         st_rdev;     // device type (if inode device) Dos
      off_t         st_size;     // total size, in bytes Dos
      blksize_t     st_blksize;  // blocksize for filesystem I/O Dos
      blkcnt_t      st_blocks;   // number of blocks allocated Dos
      time_t        st_atime;    // time of last access Dos
      time_t        st_mtime;    // time of last modification Dos
      time_t        st_ctime;    // time of last status change Dos
      };

*/
/*****************************************************************************
 * $Log: $
 *****************************************************************************/
