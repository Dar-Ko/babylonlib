/*$Workfile: TestGetLines.cpp$: implementation file
  $Revision: 4$ $Date: 2004-10-06 15:01:37$
  $Author: Darko$

  Test of the counting of the text lines.
  Copyright: CommonSoft Inc.
  2004-08-12 Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"

#pragma warning (disable : 4786) //Warning: identifier was truncated to '255' 
                                 //characters in the browser information
#include <vector>
#include <fstream>

extern CTestLog g_logTest;   //general test logger
extern bool TsWriteToViewLn(LPCTSTR lszText);
#if (defined _UNICODE)
  extern std::string WtoChar(const wchar_t* lpWideCharStr, int iLen = -1);
#endif
//-----------------------------------------------------------------------------
/*Validates GetLines() function. The function count number of the text lines in
  the given file.

  Returns true if test is successful; otherwise returns false.

  Note: uses Standard Template Library (STL).
 */
bool TestGetLines(LPCTSTR szFileName //[in] file name
                  )
{
TsWriteToViewLn(_T("TestGetLines()"));

bool GetLines(tifstream& fileSource, 
              std::vector<tstring>& arrayLine,
              int iCount = -1);

bool bResult = false; //test result

  //Test log  creation
g_logTest.m_szObjectName = _T("GetLines(tifstream, std::vector)");
g_logTest.m_szFileName   = _T("KGetLines.cpp");//function or object file name
g_logTest.m_bResult      = false;              //result of the test

std::vector<tstring> arrayLine;
  //Open source file
#ifdef _UNICODE
  #if (_MSC_VER < 1300) && (KSTL_IO <= 1201)
    /*Note: STL MSVC v6.0 implementation of wifstream uses char* for file names:
            wifstream::wifstream(const char* filename);
            The reason is that wchar_t id defined as unsigned short and could not
            be overloaded in as other primitive types.
            For KSTL_IO values see KOStream.h
     */
    std::string strFileName = WtoChar(szFileName);
    LPCSTR szaFileName = strFileName.c_str(); //SBCS (ASCII) file name
  #endif
#else   //SBCS text mapping
  LPCSTR& szaFileName = szFileName; //SBCS (ASCII) alias
#endif

tifstream fileSource(szaFileName);
if(fileSource != NULL)
  {
  //Test text line counting
  GetLines(fileSource, arrayLine);
  const int iLineCount = arrayLine.size();

  std::_tcout << _T("File ") << szFileName << _T(" has ")
    << iLineCount << ((iLineCount != 1) ? _T(" lines.") : _T(" line.")) 
    << std::endl;

  //Print first few lines
  const int OUTPUT_LIMIT = 10;
  int iCount = 0;
  while ((iCount < iLineCount) && (iCount < OUTPUT_LIMIT) )
    {
    std::_tcout << arrayLine[iCount++] <<  std::endl;
    }

  //Test reading predefined number of lines
  
/*            
  while(GetLines(fileSource, arrayLine, 7))
    {
    std::string strOutFile = arrayLine[2].substr(7);
    strOutFile = strOutFile.substr(0,strOutFile.length()-8);
    int i = 0;
    while(i < strOutFile.length())
      {
      if (strOutFile[i] == ' ')
        strOutFile.at(i) = '_';
      i++;
      }
    strOutFile += ".htm";
    std::_tcout << strOutFile << std::endl;
    std::ofstream fileOut(strOutFile.c_str());
    if(fileOut != NULL)
      {
      i = 0;
      while ( i < 7)
        {
        fileOut << arrayLine[i] << std::endl;
        i++;
        }
      fileOut.close();
      }
    arrayLine.clear();
    }
*/
  fileSource.close();
  bResult = true;
  }
else
  std::_tcout << _T("Cannot open file ") << szFileName << std::endl;

g_logTest.LogResult(bResult);
return bResult;
}

#pragma warning (default  : 4786)

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: 
 *  4    Biblioteka1.3         2004-10-06 15:01:37  Darko           Unicode mapping
 *  3    Biblioteka1.2         2004-09-30 14:47:52  Darko           inserted global
 *       CTestLog
 *  2    Biblioteka1.1         2004-09-29 12:23:27  Darko           improved tests
 *  1    Biblioteka1.0         2004-09-28 12:59:56  Darko           
 * $
 *****************************************************************************/

/*-------------------------- functions ------------------------------*/
/** getline
 *  lesen einer Zeile aus stdin. Zeile wird passend alloziert und
 *  zurückgeliefert.
 *  NULL bei EOF oder Fehler
 */
char* GetLine()
{
#define  MAX 80

   char* buf = (char*) malloc(sizeof(char)*MAX);
   char *bhelp;
   char c;
   int size = MAX;   /* allozierte Größe */
   int anz = 0;      /* gelesene Zeichen */
   static int eof = 0;

   if (eof)    /* das letzte Mal ist EOF aufgetreten */
   {
      if (buf)
         free(buf);
      return NULL;
   }
   if (buf)    /* genug Speicher da */
   {
      while ((c = getchar()) != EOF && c != '\n' /* && anz < size-1 */)
      {
         buf[anz++] = c;
         if (anz >= size - 1)    /* Buffer voll */
         {                       /* vergrößern */
            if (bhelp = (char*)malloc(sizeof(char) * (size + MAX)))
            {
               strncpy(bhelp, buf, size);
               free(buf);
               buf = bhelp;
               size = size + MAX;
            }
            else
            {
               free(buf);
               fprintf(stderr, "getline() FATAL: out of memory\n");
               return NULL;
            }
         }
      }
      if (c == EOF)
      {
         eof = 1;
         if (!anz)   /* EOF als erstes Zeichen, also Buffer freigeben */
         {
            free(buf);
            return NULL;
         }
      }
      buf[anz] = '\0';  /* String abschliessen */
      return buf;
   }
   else 
   {
      fprintf(stderr, "getline() FATAL: out of memory\n");
      return NULL;
   }
}


/* getline.c -- Replacement for GNU C library function getline

Copyright (C) 1993, 1996, 1997, 1998 Free Software Foundation, Inc.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the
License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA. */

/* Written by Jan Brittenson, bson@gnu.ai.mit.edu.  */

#if HAVE_CONFIG_H
# include <config.h>
#endif

/* The `getdelim' function is only declared if the following symbol
   is defined.  */
#ifndef _GNU_SOURCE
# define _GNU_SOURCE 1
#endif

#include <stdio.h>
#include <sys/types.h>

#if defined __GNU_LIBRARY__ && HAVE_GETDELIM

int
getline (char **lineptr, size_t *n, FILE *stream)
{
  return getdelim (lineptr, n, '\n', stream);
}


#else /* ! have getdelim */

//# define NDEBUG
# include <assert.h>

# if STDC_HEADERS
#  include <stdlib.h>
# else
char *malloc (), *realloc ();
# endif

/* Always add at least this many bytes when extending the buffer.  */
# define MIN_CHUNK 64

/* Read up to (and including) a TERMINATOR from STREAM into *LINEPTR
   + OFFSET (and null-terminate it). *LINEPTR is a pointer returned from
   malloc (or NULL), pointing to *N characters of space.  It is realloc'd
   as necessary.  Return the number of characters read (not including the
   null terminator), or -1 on error or EOF.  */

int
getstr (char **lineptr, size_t *n, FILE *stream, char terminator, size_t offset)
{
  int nchars_avail;		/* Allocated but unused chars in *LINEPTR.  */
  char *read_pos;		/* Where we're reading into *LINEPTR. */
  int ret;

  if (!lineptr || !n || !stream)
    return -1;

  if (!*lineptr)
    {
      *n = MIN_CHUNK;
      *lineptr = (char*) malloc (*n);
      if (!*lineptr)
	return -1;
    }

  nchars_avail = *n - offset;
  read_pos = *lineptr + offset;

  for (;;)
    {
      register int c = getc (stream);

      /* We always want at least one char left in the buffer, since we
	 always (unless we get an error while reading the first char)
	 NUL-terminate the line buffer.  */

      assert(*n - nchars_avail == read_pos - *lineptr);
      if (nchars_avail < 2)
	{
	  if (*n > MIN_CHUNK)
	    *n *= 2;
	  else
	    *n += MIN_CHUNK;

	  nchars_avail = *n + *lineptr - read_pos;
	  *lineptr = (char*)realloc (*lineptr, *n);
	  if (!*lineptr)
	    return -1;
	  read_pos = *n - nchars_avail + *lineptr;
	  assert(*n - nchars_avail == read_pos - *lineptr);
	}

      if (c == EOF || ferror (stream))
	{
	  /* Return partial line, if any.  */
	  if (read_pos == *lineptr)
	    return -1;
	  else
	    break;
	}

      *read_pos++ = c;
      nchars_avail--;

      if (c == terminator)
	/* Return the line.  */
	break;
    }

  /* Done - NUL terminate and return the number of chars read.  */
  *read_pos = '\0';

  ret = read_pos - (*lineptr + offset);
  return ret;
}

int
getline (char **lineptr, size_t *n, FILE *stream)
{
  return getstr (lineptr, n, stream, '\n', 0);
}

int
getdelim (char **lineptr, size_t *n, int delimiter, FILE *stream)
{
  return getstr (lineptr, n, stream, delimiter, 0);
}
#endif



/**************************************************************
Usage:

char *line;

while ((line = getline(fp)) != NULL) {
    ...
    free(line);
}
**************************************************************/
char *getline(FILE *fp)
{
    char *buffer;
    int capacity = 0;

    buffer = (char *)malloc(BUFSIZ);
    capacity = BUFSIZ;

    if (NULL == fgets(buffer, capacity, fp)) {
        free(buffer);
        return NULL;
    }

    while (1) {
        int length;
        length = strlen(buffer);
        if (length < capacity -1 || buffer[length-1] == '\n')
            break;
        capacity = (capacity * 2 + BUFSIZ - 1) / BUFSIZ * BUFSIZ;
        buffer = (char *)realloc(buffer,capacity);
        if (NULL == fgets(buffer + length, capacity - length, fp))
            break;
    }
    return buffer;
}
        
/*

// File: getline.cpp
// getline: get line into s, return length
// Uses the global variable inFile, which 
// must be declared elsewhere
The function getline is standard fare in C++ progrmming. 
It returns the length of the line read, and places the characters in the line 
into the array s. The variable lim is the line length of the longest allowable line. 
#include "stsearch.h"
extern tifstream inFile;

int getline(char s[], int lim) {
  int i = 0; 
  char c;
  while (--lim > 0 && inFile.get(c) && c != '\n')
    s[i++] = c;
  if (c == '\n')
    s[i++] = c;
  s[i] = '\0';
  return i;
}

#ifndef SAFE_STL

#include <string>
#ifdef USE_DOT_H
    #include <iostream.h>
#else
    #include <iostream>
    using namespace std;
#endif


#if !defined( __BORLANDC__ ) || __BORLANDC__ < 0x0530


// The recent compilers don't seem to have this working correctly.
// So here's my own. Use this on Borland 5.0 and Visual.
// You can remove these lines of code when the compilers catch up.
istream & getline( istream & in, string & str, char delim )
{
    char ch;
    str = "";     // empty string, will build one char at-a-time
    
    while( in.get( ch ) && ch != delim )
        str += ch;
    
    return in;
}

istream & getline( istream & in, string & str )
{
    return getline( in, str, '\n' );
}

#endif

#endif
*/

