/*$Workfile: KNLSCst.h$: header file
  $Revision: 2$ $Date: 25/01/2002 3:57:19 PM$
  $Author: Darko$

  National language support constants.
  This files is largely ported from the Win32 header WinNLS.h.
 */
//TODO: move locales (LCID) & associated maros to differnt header file D.K.
 
#ifndef __KNLSCST_H__
  //KNLSCst.h sentry
  #define __KNLSCST_H__

/*
///////////////////////////////////////////////////////////////////////////////
//Primary language IDs.                                                      */

/*The following two combinations of primary language ID and sublanguage ID have
  special semantics: 

      Primary Language ID   Sublanguage ID      Result
      -------------------   ---------------     ------------------------
      LANG_NEUTRAL          SUBLANG_NEUTRAL     Language neutral
      LANG_NEUTRAL          SUBLANG_DEFAULT     Process default language
      LANG_NEUTRAL          SUBLANG_SYS_DEFAULT System default language	 
 */
#define LANG_NEUTRAL                     0x00

#define LANG_ALBANIAN                    0x1c
#define LANG_ARABIC                      0x01
#define LANG_BAHASA                      0x21
#define LANG_BULGARIAN                   0x02
#define LANG_CATALAN                     0x03
#define LANG_CHINESE                     0x04
#define LANG_CZECH                       0x05
#define LANG_DANISH                      0x06
#define LANG_DUTCH                       0x13
#define LANG_ENGLISH                     0x09
#define LANG_FINNISH                     0x0b
#define LANG_FRENCH                      0x0c
#define LANG_GERMAN                      0x07
#define LANG_GREEK                       0x08
#define LANG_HEBREW                      0x0d
#define LANG_HUNGARIAN                   0x0e
#define LANG_ICELANDIC                   0x0f
#define LANG_ITALIAN                     0x10
#define LANG_JAPANESE                    0x11
#define LANG_KOREAN                      0x12
#define LANG_NORWEGIAN                   0x14
#define LANG_POLISH                      0x15
#define LANG_PORTUGUESE                  0x16
#define LANG_RHAETO_ROMAN                0x17
#define LANG_ROMANIAN                    0x18
#define LANG_RUSSIAN                     0x19
#define LANG_CROATIAN                    0x1a
#define LANG_SLOVAK                      0x1b
#define LANG_SPANISH                     0x0a
#define LANG_SWEDISH                     0x1d
#define LANG_THAI                        0x1e
#define LANG_TURKISH                     0x1f
#define LANG_URDU                        0x20

/*
///////////////////////////////////////////////////////////////////////////////
// Sublanguage IDs. The name immediately following SUBLANG_ defines which 
// primary language ID that sublanguage ID can be combined with to form a valid
// language ID.                                                              */

#define SUBLANG_NEUTRAL                  0x00    /* language neutral */
#define SUBLANG_DEFAULT                  0x01    /* user default */
#define SUBLANG_SYS_DEFAULT              0x02    /* system default */

#define SUBLANG_CHINESE_SIMPLIFIED       0x02    /* Chinese (Simplified) */
#define SUBLANG_CHINESE_TRADITIONAL      0x01    /* Chinese (Traditional) */ 
#define SUBLANG_CHINESE_HONGKONG         0x33
#define SUBLANG_CHINESE_SINGAPORE        0x04
#define SUBLANG_DUTCH                    0x01    /* Dutch */
#define SUBLANG_DUTCH_BELGIAN            0x02    /* Dutch (Belgian) */
#define SUBLANG_ENGLISH_US               0x01    /* English (USA) */
#define SUBLANG_ENGLISH_UK               0x02    /* English (UK) */
#define SUBLANG_ENGLISH_AUS              0x03    /* English (Australian) */
#define SUBLANG_ENGLISH_CAN              0x04    /* English (Canadian) */
#define SUBLANG_ENGLISH_NZ               0x05    /* English (New Zealand) */
#define SUBLANG_ENGLISH_EIRE             0x06    /* English (Irish) */
#define SUBLANG_FRENCH                   0x01    /* French */
#define SUBLANG_FRENCH_BELGIAN           0x02    /* French (Belgian) */
#define SUBLANG_FRENCH_CANADIAN          0x03    /* French (Canadian) */
#define SUBLANG_FRENCH_SWISS             0x04    /* French (Swiss) */
#define SUBLANG_GERMAN                   0x01    /* German */
#define SUBLANG_GERMAN_SWISS             0x02    /* German (Swiss) */
#define SUBLANG_GERMAN_AUSTRIAN          0x03    /* German (Austrian) */
#define SUBLANG_ITALIAN                  0x01    /* Italian */
#define SUBLANG_ITALIAN_SWISS            0x02    /* Italian (Swiss) */
#define SUBLANG_NORWEGIAN_BOKMAL         0x01    /* Norwegian (Bokmal) */
#define SUBLANG_NORWEGIAN_NYNORSK        0x02    /* Norwegian (Nynorsk) */
#define SUBLANG_PORTUGUESE               0x02    /* Portuguese */
#define SUBLANG_PORTUGUESE_BRAZILIAN     0x01    /* Portuguese (Brazilian) */
#define SUBLANG_SERBO_CROATIAN_CYRILLIC  0x02    /* Serbo-Croatian (Cyrillic) */
#define SUBLANG_SERBO_CROATIAN_LATIN     0x01    /* Croato-Serbian (Latin) */
#define SUBLANG_SPANISH                  0x01    /* Spanish */
#define SUBLANG_SPANISH_MEXICAN          0x02    /* Spanish (Mexican) */
#define SUBLANG_SPANISH_MODERN           0x03    /* Spanish (Modern) */


/* ///////////////////////////////////////////////////////////////////////// */
/* //Country Codes.                                                          */

#define CTRY_DEFAULT                     0       /* non-specified country */
#define CTRY_AUSTRALIA                   61      /* Australia */
#define CTRY_AUSTRIA                     43      /* Austria */
#define CTRY_BELGIUM                     32      /* Belgium */
#define CTRY_BRAZIL                      55      /* Brazil */
#define CTRY_CANADA                      2       /* Canada */
#define CTRY_DENMARK                     45      /* Denmark */
#define CTRY_FINLAND                     358     /* Finland */
#define CTRY_FRANCE                      33      /* France */
#define CTRY_GERMANY                     49      /* Germany */
#define CTRY_ICELAND                     354     /* Iceland */
#define CTRY_IRELAND                     353     /* Ireland */
#define CTRY_ITALY                       39      /* Italy */
#define CTRY_JAPAN                       81      /* Japan */
#define CTRY_MEXICO                      52      /* Mexico */
#define CTRY_NETHERLANDS                 31      /* Netherlands */
#define CTRY_NEW_ZEALAND                 64      /* New Zealand */
#define CTRY_NORWAY                      47      /* Norway */
#define CTRY_PORTUGAL                    351     /* Portugal */
#define CTRY_PRCHINA                     86      /* PR China */
#define CTRY_SOUTH_KOREA                 82      /* South Korea */
#define CTRY_SPAIN                       34      /* Spain */
#define CTRY_SWEDEN                      46      /* Sweden */
#define CTRY_SWITZERLAND                 41      /* Switzerland */
#define CTRY_TAIWAN                      886     /* Taiwan */
#define CTRY_UNITED_KINGDOM              44      /* United Kingdom */
#define CTRY_UNITED_STATES               1       /* United States */


/* ///////////////////////////////////////////////////////////////////////// */
/* //Typedefs                                                                */

#ifndef _LCID_DEFINED
  #define _LCID_DEFINED

  /*Locale ID is a DWORD value which is the combination of a language ID 
    and a reserved area.  The bits are allocated as follows:

        +-----------------------+-------------------------+
        |       Reserved        |      Language ID        |
        +-----------------------+-------------------------+
         31                   16 15                      0   bit
  */
  typedef unsigned long  LCID;

  /*Language ID is a WORD value which is the combination of a
  primary language ID and a secondary language ID.  The bits are
  allocated as follows:

        +-----------------------+-------------------------+
        |      Sublanguage ID   |   Primary Language ID   |
        +-----------------------+-------------------------+
         15                   10 9                       0   bit
  */
  typedef unsigned short LANGID;

#endif /*_LCID_DEFINED                                                       */

/* 
///////////////////////////////////////////////////////////////////////////////
// NLS component Macros                                                      */

  //Construct language ID from primary language ID and sublanguage ID.
#define MAKELANGID(primL, subL)   ((((unsigned short)(subL)) << 10) | (unsigned short)(primL))
  //Extract primary language ID from a language ID.
#define PRIMARYLANGID(lgid)    ((unsigned short)(lgid) & 0x3FF)
  //Extract sublanguage ID from a language ID.
#define SUBLANGID(lgid)        ((unsigned short)(lgid) >> 10)
  //Create locale ID from a language ID.
#define MAKELCID(lgid)         ((unsigned long)(((unsigned short)(lgid)) | (((unsigned long)((unsigned short)(0))) << 16)))
  //Get the language id from a locale id.
#define LANGIDFROMLCID(lcid)   ((unsigned short)(lcid))
 //Default System ID for language.
#define LANG_SYSTEM_DEFAULT    (MAKELANGID(LANG_NEUTRAL, SUBLANG_SYS_DEFAULT))
 //Default User IDs for language.
#define LANG_USER_DEFAULT      (MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT))
 //Default System ID for locale.
#define LOCALE_SYSTEM_DEFAULT  (MAKELCID(LANG_SYSTEM_DEFAULT))
 //Default User IDs for locale.
#define LOCALE_USER_DEFAULT    (MAKELCID(LANG_USER_DEFAULT))

///////////////////////////////////////////////////////////////////////////////
#endif //__KNLSCST_H__
/*****************************************************************************
 * $Log: 
 *  2    Biblioteka1.1         25/01/2002 3:57:19 PMDarko           Updated
 *       comments
 *  1    Biblioteka1.0         15/10/2001 10:38:03 AMDarko           
 * $
 * D.K. 2k This files is largely ported from the Win32 header WinNLS.h.
 *****************************************************************************/
