/*  We define constants for the way the current system formats filenames;
 *  we assume that the system has some type of path concept.                 */

#if (defined (WIN32))                   /*  Windows 95/NT                    */
#   define PATHSEP      ";"             /*  Separates path components        */
#   define PATHEND      '\\'            /*  Delimits directory and filename  */
#   define PATHFOLD     FALSE           /*  Convert pathvalue to uppercase?  */
#   define NAMEFOLD     FALSE           /*  Convert filenames to uppercase?  */
#   define MSDOS_FILESYSTEM             /*  MS-DOS derivative                */
#elif (defined (__MSDOS__))             /*  16-bit Windows, MS-DOS           */
#   define PATHSEP      ";"
#   define PATHEND      '\\'
#   if defined LFN                      /*  Support DRDOS long file names    */
#       define PATHFOLD FALSE
#       define NAMEFOLD FALSE
#   else
#       define PATHFOLD TRUE
#       define NAMEFOLD TRUE
#   endif
#   define MSDOS_FILESYSTEM             /*  MS-DOS derivative                */
#elif (defined (__VMS__))               /*  Digital OpenVMS                  */
#   define PATHSEP      ","             /*    We work with POSIX filenames   */
#   define PATHEND      '/'
#   define PATHFOLD     TRUE
#   define NAMEFOLD     TRUE
#elif (defined (__UNIX__))              /*  All UNIXes                       */
#   define PATHSEP      ":"
#   define PATHEND      '/'
#   define PATHFOLD     FALSE
#   define NAMEFOLD     FALSE
#elif (defined (__OS2__))               /*  OS/2 using EMX/GCC               */
#   define PATHSEP      ";"             /*  EDM 96/05/28                     */
#   define PATHEND      '\\'
#   define PATHFOLD     TRUE
#   define NAMEFOLD     FALSE
#   define MSDOS_FILESYSTEM             /*  MS-DOS derivative                */
#else
#   error "No definitions for PATH constants"
#endif

