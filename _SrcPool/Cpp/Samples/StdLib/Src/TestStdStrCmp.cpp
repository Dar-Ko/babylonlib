/*                               -*- Mode: C -*-
 * string_test.c ---
 * Author           : Manoj Srivastava ( srivasta@glaurung.green-gryphon.com )
 * Created On       : Thu Feb 20 12:43:59 2003
 * Created On Node  : glaurung.green-gryphon.com
 * Last Modified By : Manoj Srivastava
 * Last Modified On : Thu Feb 27 17:53:16 2003
 * Last Machine Used: ember.green-gryphon.com
 * Update Count     : 285
 * Status           : Unknown, Use with caution!
 * HISTORY          :
 * Description      :
 *
 */

static const char* version =
  "$Id: TestStdStrCmp.cpp,v 1.1 2005/03/08 06:27:48 ddarko Exp $";

extern int errno;


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>


size_t manoj_strlen(const char *s);
int test_strlen(void);

char * manoj_strcpy(char *dest, const char *src);
int test_strcpy(void);

char *manoj_strncpy(char *dest, const char *src, size_t n);
int test_strncpy(void);

char *manoj_strdup(const char *s);
int test_strdup(void);

char *manoj_strcat(char *dest, const char *src);
int test_strcat(void);

char *manoj_strncat(char *dest, const char *src, size_t n);
int test_strncat(void);

int manoj_strcmp(const char *s1, const char *s2);
int test_strcmp(void);

int manoj_strncmp(const char *s1, const char *s2, size_t n);
int test_strncmp(void);


extern int strcasecmp(const char *s1, const char *s2);
int manoj_strcasecmp(const char *s1, const char *s2);
int test_strcasecmp(void);

extern int strncasecmp(const char *s1, const char *s2, size_t n);
int manoj_strncasecmp(const char *s1, const char *s2, size_t n);
int test_strncasecmp(void);

char *manoj_strchr(const char *s, int c);
int test_strchr(void);

char *manoj_strrchr(const char *s, int c);
int test_strrchr(void);

char *manoj_strtok(char *s, const char *delim);
int test_strtok(void);

extern char *strtok_r(char *s, const char *delim, char **ptrptr);
char *manoj_strtok_r(char *s, const char *delim, char **ptrptr);
int test_strtok_r(void);

char *manoj_strstr(const char *haystack, const char *needle);
int test_strstr(void);

#define      BEGIN_BLOCK     do {        /* begin macros with this */

#define      END_BLOCK       } while (0) /* end macros with this */



size_t manoj_strlen(const char *src_p)
{
  size_t i = 0;
  if(*src_p){ while(*(src_p++)) i++; }
  return i;
}

char * manoj_strcpy(char *dest_p, const char *src_p)
{
  char * ret_p = dest_p;
  while(*src_p) *(dest_p++) = *(src_p++);
  *dest_p = 0;
  return ret_p;
}

char *manoj_strncpy(char *dest_p, const char *src_p, size_t n)
{
  char * ret_p = dest_p;
  size_t j = 0;
  memset (dest_p, 0, n);
  while(j++ < n && *src_p) *(dest_p++) = *(src_p++);
  return ret_p;
}

char *manoj_strdup(const char *src_p)
{
  char *dest_p = malloc(strlen(src_p) + 1);
  if(dest_p) (void) strcpy(dest_p, src_p);
  return dest_p;
}

char *manoj_strcat(char *dest_p, const char *src_p)
{
  char * ret_p = dest_p;
  while(*(dest_p++)) ;
  dest_p--;
  while(*src_p) *(dest_p++) = *(src_p++);
  *dest_p = 0;
  return ret_p;
}

char *manoj_strncat(char *dest_p, const char *src_p, size_t n)
{
  char * ret_p = dest_p;
  size_t j = 0;
  while(*(dest_p++)) ;
  dest_p--;
  while(j++ < n && *src_p) *(dest_p++) = *(src_p++);
  return ret_p;
}

int manoj_strcmp(const char *s1, const char *s2)
{
  while(*s1 && *s2 && *s1 == *s2) {s1++; s2++; };
  if(*s1)
   {
     if(*s2)
      {
        return ((*s1 < *s2) ? -1 : ((*s1 == *s2) ? 0 : 1));
      }
     else       return 1;       /* s1 is longer than s2, but identical */
   }
  else
   {
     if(*s2) return -1;         /* s1 is shorter, and hence less than s2*/
     else return 0;             /* Both strings are identical*/
   }
}


int manoj_strncmp(const char *s1, const char *s2, size_t n)
{
  size_t j = 0;
  if(n <= 0) return 0;
  while(j++ < n && *s1 && *s2 && *s1 == *s2) {s1++; s2++; };
  if(j == n) return 0;
  if(*s1)
   {
     if(*s2)
      {
        return ((*s1 < *s2) ? -1 : ((*s1 == *s2) ? 0 : 1));
      }
     else       return 1;       /* s1 is longer than s2, but identical */
   }
  else
   {
     if(*s2) return -1;         /* s1 is shorter, and hence less than s2*/
     else return 0;             /* Both strings are identical*/
   }
}

int manoj_strcasecmp(const char *s1, const char *s2)
{
  while(*s1 && *s2 && toupper(*s1) == toupper(*s2)) {s1++; s2++; };
  if(*s1)
   {
     if(*s2)
      {
        return ((toupper(*s1) < toupper(*s2)) ? -1 :
                ((toupper(*s1) ==toupper( *s2)) ? 0 : 1));
      }
     else       return 1;       /* s1 is longer than s2, but identical */
   }
  else
   {
     if(*s2) return -1;         /* s1 is shorter, and hence less than s2*/
     else return 0;             /* Both strings are identical*/
   }
}


int manoj_strncasecmp(const char *s1, const char *s2, size_t n)
{
  size_t j = 0;
  if(n <= 0) return 0;
  while(j++ < n && *s1 && *s2 && toupper(*s1) == toupper(*s2)) {s1++; s2++; } ;
  if(j == n) return 0;
  if(*s1)
   {
     if(*s2)
      {
        return ((toupper(*s1) < toupper(*s2)) ? -1 :
                ((toupper(*s1) ==toupper( *s2)) ? 0 : 1));
      }
     else       return 1;       /* s1 is longer than s2, but identical */
   }
  else
   {
     if(*s2) return -1;         /* s1 is shorter, and hence less than s2*/
     else return 0;             /* Both strings are identical*/
   }
}

char *manoj_strchr(const char *str_p, int c)
{
  char i = (char) c;
  char * j = (char *) str_p;    /* This produces a warning */
  while(*j && *j != i) j++;
  if(*j) return j;
  else   return 0;
}


char *manoj_strrchr(const char *str_p, int c)
{
  char i = (char) c;
  char * j = (char *) str_p;    /* This produces a warning */
  while(*(j++));
  j--;
  while(j >= str_p && *j != i) j--;
  if(j > str_p) return j;
  else
   {
     if(*j == i) return j;
     else        return 0;
   }
}

/*
 * The warning produced in the casts above seem to have no work
 * arounds; how can these functions return a pointrer to a mutable
 * string when the input string itself is a const string? This seems
 * like a defect in the C99 standard.
 */


char *manoj_strtok(char *str_p, const char *delim)
{
  static char * index_p;
  int i = 0;
  int j = 0;
  int k = 0;
  int l = 0;

  if(! delim) return 0;
  if(str_p)  index_p = str_p;   /* initialize, since a new string is given*/
  if(! index_p) return 0;

  j = strlen(delim);
  k = strlen(index_p);

  /* Skip over initial matches */
  for(l = 0; l < k; l++)
   {
     if(strchr(delim, index_p[l])) continue;
     index_p = index_p + l;
     break;
   }


  for(l = 0; l < k; l++)
   {
     for(i = 0; i < j; i++)
      {
        if(index_p[l] == delim[i])
         {
           char *retval_p = index_p;
           index_p[l] = 0;
           index_p = index_p + l +1;
           return retval_p;
         }
      }
   }
  return 0;                     /* found noyhing */
}

char *manoj_strtok_r(char *str_p, const char *delim, char **ptrptr)
{
  char * index_p;
  int i = 0;
  int j = 0;
  int k = 0;
  int l = 0;

  if(! delim) return 0;
  if(str_p)  (void) strcpy (*ptrptr, str_p);
  index_p = *ptrptr;
  if(! index_p) return 0;

  j = strlen(delim);
  k = strlen(index_p);
  /* Skip over initial matches */
  for(l = 0; l < k; l++)
   {
     if(strchr(delim, index_p[l])) continue;
     index_p = index_p + l;
     break;
   }

  for(l = 0; l < k; l++)
   {
     for(i = 0; i < j; i++)
      {
        if(index_p[l] == delim[i])
         {
           char *retval_p = index_p;
           index_p[l] = 0;
           *ptrptr = index_p + l +1 ;
           return retval_p;
         }
      }
   }
  return 0;                     /* found noyhing */
}

#define ASIZE 256


char *manoj_strstr(const char *haystack, const char *needle)
{
  int skip[ASIZE];
  int *shift = 0;
  int *suffix_length = 0;

  int i = 0;
  int j = 0;
  size_t right_end = 0;
  int needle_len = strlen(needle);
  /*
   * If needle[needle_len - 1] does not exist elsewhere in needle,
   * then shift by needle_len
   */

  if(!needle) return 0;

  /*
   * initialize the skip table. Chars not in the pattern slide all
   * the way forward.
   */
  for(i = 0; i < ASIZE; i++) skip[i] = needle_len;
  /*
   * Now for chars that are in the key Need to fill from left to
   * right
   */
  for(i = 0; i < needle_len - 1; i++)
    skip[ (int) needle[i] ] = needle_len -i -1;
  /* suffixes[i]=k s.t. x[i-k+1,...,i]=x[m-k,...,m-1] */

  shift = (int *) malloc(sizeof(int) * (needle_len + 1));
  if(!shift)
   {
     errno = ENOMEM;
     return 0;
   }
  suffix_length = (int *) malloc(sizeof(int) * (needle_len + 1));
  if(!suffix_length)
   {
     errno = ENOMEM;
     return 0;
   }

  /*
   * Set suffix_length[i] = number of characters right ended at needle[i]
   * which match the characters right ended at needle[needle_len - 1].
   */
  for (i = 1; i < needle_len; i++){
    for (j = 0;
         j <= i && needle[needle_len - 1 - j] == needle[i - j];
         j++);
    suffix_length[i] = j;
#ifdef LIB_DEBUG
    fprintf(stderr, "suffix_length[i(%2d)] = %2d %c\n", i, j, needle[i]);
    if(j)
     {
       int k = 0;
       fprintf(stderr, "%s\n", needle);
       for(k = 0; k <= needle_len - 1 -j; k++)
        {
          fprintf(stderr, " ");
        } /* end of for(k = 0; k < j; k++) */
       for(k = needle_len - 1 - j; k < needle_len - 1; k++)
        {
          fprintf(stderr, "|");
        } /* end of for(k = 0; k < j; k++) */
       fprintf(stderr, "\n");
       for(k = 0; k <= i -j; k++)
        {
          fprintf(stderr, " ");
        } /* end of for(k = 0; k < j; k++) */
       for(k = i - j; k < i; k++)
        {
          fprintf(stderr, "^");
        } /* end of for(k = 0; k < j; k++) */
       fprintf(stderr, "\n");
     } /* end of if(j) */
#endif
  }
  /* Zero the relevant section of the array */
  for (i = 1; i < needle_len; i++) shift[i] = 0;
  /*
   * Fix up by shifting to the rightmost occurrence of the matched
   * chars. Note that suffix_length[i] is the length of the suffix
   * matched at the point i in the pattern. So, when we have matched a
   * suffix of length suffix_length[i], a similar string is at
   * position i, and we need to shift the string by needle_len - 1 - i
   * to bring that other substring under tecurrently matched string.
   */
  for (i = 0; i <  needle_len; i++)
   {
     shift[suffix_length[i]] = needle_len - 1 - i;
#ifdef LIB_DEBUG
     fprintf(stderr, "shift[suffix_length[i](%2d)] = i(%2d);\n",
             suffix_length[i], i);
#endif
   }

  /* Let the skip array take care of the case for zero matches */
  shift[0] = 1;
  /*
   * Fix up by considering matches that would run off the end of the
   * pattern. So, things where the substring was not found, we shift
   * enough to move the window beyond the matched pattern, but no
   * more (let the minimum shift be at least 1).
   */
  for (i = 1; i < needle_len; i++)
    {
      if (shift[i] == 0)
       {
         shift[i] = (needle_len - 1 - i > 1) ?
                    needle_len - 1 - i : 1;
#ifdef LIB_DEBUG
         fprintf(stderr, "shift[i(%2d)] = max_gap(%2d);\n",
             i, shift[i]);
#endif
       }
    }

#ifdef LIB_DEBUG
  for (i = 0; i < needle_len; i++){
    fprintf(stderr, "%2d %3c %3d %3d\n", i, needle[i],
            suffix_length[i], shift[i]);
  }
#endif

  right_end = needle_len -1;
  while(right_end < strlen(haystack))
   {
     int sk = 0;
     int sh = 0;
#ifdef LIB_DEBUG
     fprintf(stderr, "\n%s\n", haystack);
     for(i = 0; i < right_end - needle_len + 1; i++)
      {
        fprintf(stderr, " ");
      } /* end of for(i = 0; i < right_end - needle_len + 1; i++) */
     fprintf(stderr, "%s\n", needle);
#endif

     for(i = 0;
         i < needle_len && haystack[right_end - i] == needle[needle_len -1 -i];
         i++);
     if(i == needle_len)
      {
#ifdef LIB_DEBUG
        fprintf(stderr, "Found at %d\n", right_end - needle_len + 1);
#endif
        return haystack + right_end - needle_len + 1;
      } /* end of if(i == needle_len) */
#ifdef LIB_DEBUG
     for(j = 0; j < right_end - i; j++)
      {
        fprintf(stderr, " ");
      } /* end of for(i = 0; i < right_end - needle_len + 1; i++) */
     fprintf(stderr, "|\n");

     fprintf(stderr,
             "Mismatch at %d == haystack[%d]=%c != needle[%d]=%c\n",
             right_end - i, right_end - i, haystack[right_end - i],
             needle_len -1 -i, needle[needle_len -1 -i]);
#endif

     sk = skip[(int)haystack[right_end - i]];
     sh = shift[i];
     right_end = (right_end - i + sk > right_end + sh) ?
                 right_end - i + sk : right_end + sh;
#ifdef LIB_DEBUG
     if(sk > sh)
      {
        fprintf(stderr, "Using skip table to shift by  %d\n",
                sk);
      } /* end of if(sk > sh) */
     else
      {
        fprintf(stderr, "Using shift table to shift by  %d\n",
                sh);
      } /* end of else */
#endif
   } /* end of while(right_end < strlen(haystack)) */
#ifdef LIB_DEBUG
  fprintf(stderr, "NOT Found\n");
#endif
  return 0;
}


/*
 ####################################################################
 ####################################################################
 ####################################################################
 */

const char *strings_to_test[] =
  {
   "This ia a longish text string, but not that long, at that",
   "The long jump \0 and some trailing text at-that",
   "",
   "Some more test strings",
   "Yet another one",
   "what-finally-stops--at-at-that point",
   "aksdy923492p4  p39475 q0349750[q3hf30q79340 320496t034 03q495609324uy509y",
   "character is considered to be part of the string. The chr at-that point",
   0
  };


int test_strlen(void)
{
  int retval = 0;
  int i;

#ifdef DEBUG
  fprintf (stderr, "manoj_strlen - ");
#endif
  for(i = 0; strings_to_test[i]; i++)
   {
     if(strlen(strings_to_test[i]) != manoj_strlen(strings_to_test[i]))
      {
        retval--;
        fprintf (stderr,
                 "ERROR: manoj_strlen Failed test %d. Got %d, expected %d\n",
                 i, manoj_strlen(strings_to_test[i]),
                 strlen(strings_to_test[i]));
      }
#ifdef DEBUG
     else
      {
        fprintf (stderr, ".");
      } /* end of else */
#endif
   }
#ifdef DEBUG
  fprintf (stderr, " - done\n");
#endif
  return retval;
}

int test_strcpy(void)
{
  int retval = 0;
  char buffer[1024];
  int i = 0;

#ifdef DEBUG
  fprintf (stderr, "manoj_strcpy - ");
#endif
  for(i = 0; strings_to_test[i]; i++)
   {
     char * orig = 0;
     memset(buffer,0,1024);
     orig = manoj_strcpy(buffer, strings_to_test[i]);
     if(strcmp(orig,strings_to_test[i]))
      {
        retval--;
        fprintf (stderr,
                 "ERROR: manoj_strcpy Failed test %d. \n",
                 i);
      }
#ifdef DEBUG
     else
      {
        fprintf (stderr, ".");
      } /* end of else */
#endif
   }
#ifdef DEBUG
  fprintf (stderr, " - done\n");
#endif
  return retval;
}

int test_strncpy(void)
{
  int retval = 0;
  char buffer[1024];
  char copy[1024];
  int i = 0;

#ifdef DEBUG
  fprintf (stderr, "manoj_strncpy - ");
#endif
  for(i = 0; strings_to_test[i]; i++)
   {
     char * orig  = 0;
     char * dummy = 0;
     memset(buffer,0,1024);
     memset(copy,0,1024);
     orig  = manoj_strncpy(buffer, strings_to_test[i], 5);
     dummy =       strncpy(copy,   strings_to_test[i], 5);
     if(strcmp(orig,dummy))
      {
        retval--;
        fprintf (stderr,
                 "ERROR: manoj_strncpy Failed test %d. \n",
                 i);
      }
#ifdef DEBUG
     else
      {
        fprintf (stderr, ".");
      } /* end of else */
#endif
   }
#ifdef DEBUG
  fprintf (stderr, " - done\n");
#endif
  return retval;
}

int test_strdup(void)
{
  int retval = 0;
  int i = 0;

#ifdef DEBUG
  fprintf (stderr, "manoj_strdup - ");
#endif
  for(i = 0; strings_to_test[i]; i++)
   {
     char * orig = 0;
     orig = manoj_strdup(strings_to_test[i]);
     if(orig)
      {
        if(strcmp(orig,strings_to_test[i]))
          {
            retval--;
            fprintf (stderr,
                     "ERROR: manoj_strdup Failed test %d. \n",
                     i);
          }
        free(orig);
      }
     else
      {
        fprintf (stderr,
                 "ERROR: manoj_strdup Failed test %d -- failed malloc\n",
                 i);
      }
#ifdef DEBUG
     fprintf (stderr, ".");
#endif
   }
#ifdef DEBUG
  fprintf (stderr, " - done\n");
#endif
  return retval;
}



int test_strcat(void)
{
  int retval = 0;
  char buffer[1024];
  char copy[1024];
  int i = 0;

#ifdef DEBUG
  fprintf (stderr, "manoj_strcat - ");
#endif
  for(i = 0; strings_to_test[i]; i++)
   {
     char * orig = 0;
     char * dummy = 0;
     memset(buffer,0,1024);
     memset(copy,0,1024);
     (void) strcpy(buffer, "Original String ");
     (void) strcpy(copy,   "Original String ");
     orig  = manoj_strcat(buffer, strings_to_test[i]);
     dummy =       strcat(copy,   strings_to_test[i]);
     if(strcmp(orig,dummy))
      {
        retval--;
        fprintf (stderr,
                 "ERROR: manoj_strcat Failed test %d. \n",
                 i);
        fprintf (stderr,
                 "  orig (%s)\n dummy (%s)\n",
                 orig, dummy);
      }
#ifdef DEBUG
     else
      {
        fprintf (stderr, ".");
      } /* end of else */
#endif
   }
#ifdef DEBUG
  fprintf (stderr, " - done\n");
#endif
  return retval;
}

int test_strncat(void)
{
  int retval = 0;
  char buffer[1024];
  char copy[1024];
  int i = 0;

#ifdef DEBUG
  fprintf (stderr, "manoj_strncat - ");
#endif
  for(i = 0; strings_to_test[i]; i++)
   {
     char * orig  = 0;
     char * dummy = 0;
     memset(buffer,0,1024);
     memset(copy,0,1024);
     (void) strcpy(buffer, "Original String ");
     (void) strcpy(copy,   "Original String ");
     orig  = manoj_strncat(buffer, strings_to_test[i], 5);
     dummy =       strncat(copy,   strings_to_test[i], 5);
     if(strcmp(orig,dummy))
      {
        retval--;
        fprintf (stderr,
                 "ERROR: manoj_strncat Failed test %d. \n",
                 i);
        fprintf (stderr,
                 "  orig (%s)\n dummy (%s)\n",
                 orig, dummy);
       }
#ifdef DEBUG
     else
      {
        fprintf (stderr, ".");
      } /* end of else */
#endif
   }
#ifdef DEBUG
  fprintf (stderr, " - done\n");
#endif
  return retval;
}

#define sign(x) (x>0 ? 1 : (x<0 ? -1 : 0))

int test_strcmp(void)
{
  int retval = 0;
  int i = 0;

#ifdef DEBUG
  fprintf (stderr, "manoj_strcmp - ");
#endif
  for(i = 0; strings_to_test[i]; i++)
   {
     int m = manoj_strcmp(strings_to_test[i], "The long jump ");
     int o =       strcmp(strings_to_test[i], "The long jump ");

     if(sign(m) != sign(o))
      {
        retval--;
        fprintf (stderr,
                 "ERROR: manoj_strcmp Failed test %d. %d != %d\n",
                 i, m, o);
        fprintf (stderr,
                 "ERROR: (%s) != (The long jump )  \n",
                 strings_to_test[i]);
      }
#ifdef DEBUG
     else
      {
        fprintf (stderr, ".");
      } /* end of else */
#endif
   }
#ifdef DEBUG
  fprintf (stderr, " - done\n");
#endif
  return retval;
}

int test_strncmp(void)
{
  int retval = 0;
  int i = 0;

#ifdef DEBUG
  fprintf (stderr, "manoj_strncmp - ");
#endif
  for(i = 0; strings_to_test[i]; i++)
   {
     int m = manoj_strncmp(strings_to_test[i], "The long jump ", 5);
     int o = strncmp(strings_to_test[i], "The long jump ", 5);

     if(sign(m) != sign(o))
      {
        retval--;
        fprintf (stderr,
                 "ERROR: manoj_strncmp Failed test %d. %d != %d\n",
                 i, m, o);
        fprintf (stderr,
                 "ERROR: (The long jump ) != (%s) \n",
                 strings_to_test[i]);
       }
#ifdef DEBUG
     else
      {
        fprintf (stderr, ".");
      } /* end of else */
#endif
   }
#ifdef DEBUG
  fprintf (stderr, " - done\n");
#endif
  return retval;
}


int test_strcasecmp(void)
{
  int retval = 0;
  int i = 0;

#ifdef DEBUG
  fprintf (stderr, "manoj_strcasecmp - ");
#endif
  for(i = 0; strings_to_test[i]; i++)
   {
     int m = manoj_strcasecmp(strings_to_test[i], "The long jump ");
     int o = strcasecmp(strings_to_test[i], "The long jump ");

     if(sign(m) != sign(o))
      {
        retval--;
        fprintf (stderr,
                 "ERROR: manoj_strcasecmp Failed test %d. \n",
                 i);
      }
#ifdef DEBUG
     else
      {
        fprintf (stderr, ".");
      } /* end of else */
#endif
   }
#ifdef DEBUG
  fprintf (stderr, " - done\n");
#endif
  return retval;
}

int test_strncasecmp(void)
{
  int retval = 0;
  int i = 0;

#ifdef DEBUG
  fprintf (stderr, "manoj_strncasecmp - ");
#endif
  for(i = 0; strings_to_test[i]; i++)
   {
     int m = manoj_strncasecmp(strings_to_test[i], "The long jump ", 5);
     int o = strncasecmp(strings_to_test[i], "The long jump ", 5);

     if(sign(m) != sign(o))
      {
        retval--;
        fprintf (stderr,
                 "ERROR: manoj_strncasecmp Failed test %d. \n",
                 i);
       }
#ifdef DEBUG
     else
      {
        fprintf (stderr, ".");
      } /* end of else */
#endif
   }
#ifdef DEBUG
  fprintf (stderr, " - done\n");
#endif
  return retval;
}

int test_strchr(void)
{
  int retval = 0;
  int i = 0;

#ifdef DEBUG
  fprintf (stderr, "manoj_strchr - ");
#endif
  for(i = 0; strings_to_test[i]; i++)
   {
     if(manoj_strchr(strings_to_test[i], 'j') !=
        strchr(strings_to_test[i], 'j'))
      {
        retval--;
        fprintf (stderr,
                 "ERROR: manoj_strchr Failed test %d. \n",
                 i);
       }
#ifdef DEBUG
     else
      {
        fprintf (stderr, ".");
      } /* end of else */
#endif
   }
#ifdef DEBUG
  fprintf (stderr, " - done\n");
#endif
  return retval;
}

int test_strrchr(void)
{
  int retval = 0;
  int i = 0;

#ifdef DEBUG
  fprintf (stderr, "manoj_strrchr - ");
#endif
  for(i = 0; strings_to_test[i]; i++)
   {
     if(manoj_strrchr(strings_to_test[i], 'j') !=
        strrchr(strings_to_test[i], 'j'))
      {
        retval--;
        fprintf (stderr,
                 "ERROR: manoj_strrchr Failed test %d. \n",
                 i);
       }
#ifdef DEBUG
     else
      {
        fprintf (stderr, ".");
      } /* end of else */
#endif
   }
#ifdef DEBUG
  fprintf (stderr, " - done\n");
#endif
  return retval;
}

int test_strtok(void)
{
  int            retval   = 0;
  int            i        = 0;
  char          *buffer_p = 0;
  char          *copy_p   = 0;
  const char    *delim_p  = " eta";
  char          *tok1     = 0;
  char          *tok2     = 0;


#ifdef DEBUG
  fprintf (stderr, "manoj_strtok - ");
#endif

  buffer_p = malloc(128);
  if(! buffer_p) return -1;

  copy_p = malloc(128);
  if(! copy_p) return -1;

  (void) strcpy(buffer_p, "The quick brown fox jumps over the lazy dog");
  (void) strcpy(copy_p,   "The quick brown fox jumps over the lazy dog");

  tok1 = manoj_strtok(buffer_p, delim_p);
  tok2 =       strtok(copy_p,   delim_p);
  if(strcmp(tok1, tok2))
   {
     retval--;
     fprintf (stderr,
              "ERROR: manoj_strtok Failed test %d. Got (%s), expected (%s)\n",
              i++, tok1, tok2);
   }
#ifdef DEBUG
  else
   {
     fprintf (stderr, ".");
   }
#endif

  while((tok1 =  manoj_strtok(0, delim_p)))
   {
     tok2 = strtok(0, delim_p);
     if(strcmp(tok1, tok2))
      {
        retval--;
        fprintf(stderr,
                "ERROR: manoj_strtok Failed test %d. Got (%s), expected (%s)\n",
                 i++, tok1, tok2);
      }
#ifdef DEBUG
     else
      {
        fprintf (stderr, ".");
      }
#endif
   }
#ifdef DEBUG
  fprintf (stderr, " - done\n");
#endif
  return retval;
}


int test_strtok_r(void)
{
  int            retval   = 0;
  int            i        = 0;
  char          *orig_p   = 0;
  char          *buffer_p = 0;
  char          *copy_p   = 0;
  const char    *delim_p  = " eta";
  char          *tok1     = 0;
  char          *tok2     = 0;


#ifdef DEBUG
  fprintf (stderr, "manoj_strtok_r - ");
#endif

  orig_p = malloc(128);
  if(! orig_p) return -1;

  buffer_p = malloc(128);
  if(! buffer_p) return -1;

  copy_p = malloc(128);
  if(! copy_p) return -1;

  (void) strcpy(orig_p, "The quick brown fox jumps over the lazy dog");

  tok1 = manoj_strtok_r(orig_p, delim_p, &buffer_p);
  tok2 =       strtok_r(orig_p, delim_p, &copy_p);
  if(strcmp(tok1, tok2))
   {
     retval--;
     fprintf (stderr,
              "ERROR: manoj_strtok_r Failed test %d. Got (%s), expected (%s)\n",
              i++, tok1, tok2);
   }
#ifdef DEBUG
  else
   {
     fprintf (stderr, ".");
   }
#endif

  while((tok1 =  manoj_strtok_r(0, delim_p, &buffer_p)))
   {
     tok2 = strtok_r(0, delim_p, &copy_p);
     if(strcmp(tok1, tok2))
      {
        retval--;
        fprintf (stderr,
                 "ERROR: manoj_strtok_r Failed test %d. Got (%s), expected (%s)\n",
                 i++, tok1, tok2);
      }
#ifdef DEBUG
     else
      {
        fprintf (stderr, ".");
      }
#endif
   }
#ifdef DEBUG
  fprintf (stderr, " - done\n");
#endif
  return retval;
}

int test_strstr(void)
{
  int            retval   = 0;
  int            i        = 0;

#ifdef DEBUG
  fprintf (stderr, "manoj_strstr - ");
#endif
  for(i = 0; strings_to_test[i]; i++)
   {
     if(manoj_strstr(strings_to_test[i], "at-that") !=
        strstr(strings_to_test[i], "at-that"))
      {
        retval--;
        fprintf (stderr,
                 "ERROR: manoj_strstr Failed test %d. \n",
                 i);
       }
#ifdef DEBUG
     else
      {
        fprintf (stderr, ".");
      } /* end of else */
#endif
   }
#ifdef DEBUG
  fprintf (stderr, " - done\n");
#endif
  return retval;
}


int main(void)
{
  int   retval   = 0;
  int   retval1  = 0;
  int   retval2  = 0;
  int   retval3  = 0;
  int   retval4  = 0;
  int   retval5  = 0;
  int   retval6  = 0;
  int   retval7  = 0;
  int   retval8  = 0;
  int   retval9  = 0;
  int   retval10 = 0;
  int   retval11 = 0;
  int   retval12 = 0;
  int   retval13 = 0;
  int   retval14 = 0;

  fprintf (stderr, "stringtest Version %s\n\n", version);

  retval = test_strlen();
  if(retval)   fprintf (stderr, "strlen Test Failed\n");

  retval1 = test_strcpy();
  if(retval1)  fprintf (stderr, "strcpy Test Failed\n");

  retval2 = test_strncpy();
  if(retval2)  fprintf (stderr, "strncpy Test Failed\n");

  retval3 = test_strdup();
  if(retval3)  fprintf (stderr, "strdup Test Failed\n");

  retval4 = test_strcat();
  if(retval4)  fprintf (stderr, "strcat Test Failed\n");

  retval5 = test_strncat();
  if(retval5)  fprintf (stderr, "strncat Test Failed\n");

  retval6 = test_strcmp();
  if(retval6)  fprintf (stderr, "strncmp Test Failed\n");

  retval7 = test_strncmp();
  if(retval7)  fprintf (stderr, "strncmp Test Failed\n");

  retval8 = test_strcasecmp();
  if(retval8)  fprintf (stderr, "strcat Test Failed\n");

  retval9 = test_strncasecmp();
  if(retval9)  fprintf (stderr, "strncasecmp Test Failed\n");

  retval10 = test_strchr();
  if(retval10)  fprintf (stderr, "strchr Test Failed\n");

  retval11 = test_strrchr();
  if(retval11)  fprintf (stderr, "strrchr Test Failed\n");

  retval12 = test_strtok();
  if(retval12)  fprintf (stderr, "strtok Test Failed\n");

  retval13 = test_strtok_r();
  if(retval13)  fprintf (stderr, "strtok_r Test Failed\n");

  retval14 = test_strstr();
  if(retval14)  fprintf (stderr, "strstr Test Failed\n");

  if(!(retval   + retval1  + retval2  + retval3  + retval4  + retval5  +
       retval6  + retval7  + retval8  + retval9  + retval10 + retval11 +
       retval12 + retval13 + retval14))
   {
     fprintf (stderr, "\n\tSuccess\n");
      exit (EXIT_SUCCESS);
   }
  exit (EXIT_FAILURE);
}
