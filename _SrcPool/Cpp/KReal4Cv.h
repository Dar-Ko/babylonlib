/*$Workfile: KReal4Cv.h$: header file
  $Revision: 6$ $Date: 2004-06-01 16:52:46$
  $Author: Darko$

  Conversion helper for 4 bytes real numbers (float)
  Copyright: CommonSoft Inc
  Mar 2k. D.Kolakovic  
*/

#ifndef _KREAL4CV_H_
  /*$Workfile: KReal4Cv.h$ sentry                                                      */
  #define _KREAL4CV_H_

#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
  #pragma message ("   #include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
/*UReal4Conversion objects are used to expand float point numbers into 
  implicit form. This object handles numbers 4 bytes long.
 */
union UReal4Conversion
  {
  float  fReal;             /*32-bit float point number                */
  long   lDWord;            /*binary presentation of 32-bit float point*/
  unsigned char uByte[4];   /*byte array                               */

  #ifdef __cplusplus
      //Constructon
    UReal4Conversion();
    UReal4Conversion(const float& fValue);
    UReal4Conversion(const long&  lValue);
       //Operators
    UReal4Conversion& operator  =(const long&  lValue);
    UReal4Conversion& operator |=(const long&  lValue);
    operator float() const;
    operator long() const;
  #endif /*__cplusplus                                                       */
  };

#ifdef __cplusplus
///////////////////////////////////////////////////////////////////////////////
// Inlines

//::UReal4Conversion()---------------------------------------------------------
/*Default constructor
 */
inline UReal4Conversion::UReal4Conversion() :
  lDWord(0)
{
}

/*Assignment constructor
 */
inline UReal4Conversion::UReal4Conversion(const float& fValue) :
  fReal(fValue)
{
}

inline UReal4Conversion::UReal4Conversion(const long&  lValue) :
  lDWord(lValue)
{
}

//::operator =()---------------------------------------------------------------
/*
 */
inline UReal4Conversion& UReal4Conversion::operator =(const long&  lValue)
{
lDWord = lValue;
return (*this);
}

//::operator |=()---------------------------------------------------------------
/*
 */
inline UReal4Conversion& UReal4Conversion::operator |=(const long&  lValue)
{
lDWord |= lValue;
return (*this);
}

//::operator float()------------------------------------------------------------
/*
 */
inline UReal4Conversion::operator float() const
{
return fReal;
}

//::operator long()------------------------------------------------------------
/*
 */
inline UReal4Conversion::operator long() const
{
return lDWord;
}

#endif  /*__cplusplus                                                        */
/*///////////////////////////////////////////////////////////////////////////*/
#endif  /*_KREAL4CV_H_                                                       */
/*****************************************************************************
 * $Log: 
 *  6    Biblioteka1.5         2004-06-01 16:52:46  Darko           time sync
 *  5    Biblioteka1.4         2003-09-30 09:44:33  Darko           formatting
 *  4    Biblioteka1.3         2002-01-24 18:19:06  Darko           Updated
 *       comments
 *  3    Biblioteka1.2         2001-07-11 21:52:23  Darko           
 *  2    Biblioteka1.1         2001-06-08 22:51:30  Darko           VSS
 *  1    Biblioteka1.0         2000-08-13 14:57:13  Darko           
 * $
 *****************************************************************************/
