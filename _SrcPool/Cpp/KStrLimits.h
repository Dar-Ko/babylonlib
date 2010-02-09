/*$RCSfile: KStrLimits.h,v $: header file
  $Revision: 1.3 $ $Date: 2010/02/09 22:28:32 $
  $Author: ddarko $

  Maximum length of decimal number representation
  Copyright: CommonSoft Inc
  1998  D. Kolakovic
 */

#ifndef _KSTRLIMITS_H_
    //$RCSfile: KStrLimits.h,v $ sentry
  #define _KSTRLIMITS_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

//-----------------------------------------------------------------------------
// Group=Constants

///////////////////////////////////////////////////////////////////////////////
// Decimal number representation constants are maximum number of charaters
// required to represent integral data types.
//
// See also: The Integral Data Type Range Constants in <limits.h>; <climits>;
// <stdint.h>; "KType32.h"

#ifdef __cplusplus
  //Maximum number of characters required to represent signed char value;
  //INT8_MIN = –128
  const int INT8_LEN   =   4;
  //Maximum number of characters required to represent signed short value;
  //INT16_MIN = –32 768
  const int INT16_LEN  =   6;
  //Maximum number of characters required to represent signed 32-bit int value;
  //INT32_MIN = –2 147 483 648
  const int INT32_LEN  =  11;
  //Maximum number of characters required to represent signed 64-bit int value;
  //INT64_MIN = -9 223 372 036 854 775 808
  const int INT64_LEN  =  20;
  //Maximum number of characters required to represent signed 128-bit int value;
  //INT128_MIN = -170 141 183 460 469 231 731 687 303 715 884 105 728
  const int INT128_LEN =  40;

  //Maximum number of characters required to represent unsigned char value;
  //UINT8_MAX =  +255
  const int UINT8_LEN   =   4;
  //Maximum number of characters required to represent unsigned short value;
  //UINT16_MAX = +65 535
  const int UINT16_LEN  =   6;
  //Maximum number of characters required to represent unsigned 32-bit int value;
  //UINT32_MAX = +4 294 967 295
  const int UINT32_LEN  =  11;
  //Maximum number of characters required to represent unsigned 64-bit int value;
  //UINT64_MAX = +18 446 744 073 709 551 615
  const int UINT64_LEN  =  21;
  //Maximum number of characters required to represent unsigned 128-bit int value;
  //UINT128_MAX = +340 282 366 920 938 463 463 374 607 431 768 211 455
  const int UINT128_LEN =  40;

  //Maximum number of characters required to represent 32-bit float value;
  //REAL32_MAX = +3.402 823 466e+38
  const int REAL32_LEN = (39 + 40); //TODO: solve magic  (40) inhertited from <cvt.h>
  //Maximum number of characters required to represent 64-bit double value;
  //REAL64_MAX = +1.797 693 134 862 315 8e+308
  const int REAL64_LEN = (309 + 40); //TODO: solve magic  (40) inhertited from <cvt.h>

  //Maximum number of characters required to represent 64-bit fixed point currency value;
  //CY64_MIN = -922 337 203 685 477.5808
  const int CURRENCY_LEN = 21;

#else
  //Maximum number of characters required to represent signed char value;
  //INT8_MIN = –128
  #define INT8_LEN       4
  //Maximum number of characters required to represent signed short value;
  //INT16_MIN = –32 768
  #define INT16_LEN      6
  //Maximum number of characters required to represent signed 32-bit int value;
  //INT32_MIN = –2 147 483 648
  #define INT32_LEN     11
  //Maximum number of characters required to represent signed 64-bit int value;
  //INT64_MIN = -9 223 372 036 854 775 808
  #define INT64_LEN     20
  //Maximum number of characters required to represent signed 128-bit int value;
  //INT128_MIN = -170 141 183 460 469 231 731 687 303 715 884 105 728
  #define INT128_LEN    40

  //Maximum number of characters required to represent unsigned char value;
  //UINT8_MAX =  +255
  #define UINT8_LEN       4
  //Maximum number of characters required to represent unsigned short value;
  //UINT16_MAX = +65 535
  #define UINT16_LEN      6
  //Maximum number of characters required to represent unsigned 32-bit int value;
  //UINT32_MAX = +4 294 967 295
  #define UINT32_LEN     11
  //Maximum number of characters required to represent unsigned 64-bit int value;
  //UINT64_MAX = +18 446 744 073 709 551 615
  #define UINT64_LEN     21
  //Maximum number of characters required to represent unsigned 128-bit int value;
  //UINT128_MAX = +340 282 366 920 938 463 463 374 607 431 768 211 455
  #define UINT128_LEN    40

  //Maximum number of characters required to represent 32-bit float value;
  //REAL32_MAX = +3.402 823 466e+38
  #define REAL32_LEN (39 + 40) //TODO: solve magic (40) inhertited from <cvt.h>
  //Maximum number of characters required to represent  64-bit double value;
  //REAL64_MAX = +1.797 693 134 862 315 8e+308
  #define REAL64_LEN (309 + 40) //TODO: solve magic  (40) inhertited from <cvt.h>

  //Maximum number of characters required to represent 64-bit fixed point currency value;
  //CY64_MIN = -922 337 203 685 477.5808
  #define CURRENCY_LEN    21

#endif  //__cplusplus

///////////////////////////////////////////////////////////////////////////////
#endif  //_KSTRLIMITS_H_
/*****************************************************************************
 * $Log: KStrLimits.h,v $
 * Revision 1.3  2010/02/09 22:28:32  ddarko
 * Added currency struct
 *
 * Revision 1.2  2010/02/08 22:30:05  ddarko
 * added double precision
 *
 * Revision 1.1  2010/02/08 21:03:09  ddarko
 * Reassigned
 *
 *****************************************************************************/
