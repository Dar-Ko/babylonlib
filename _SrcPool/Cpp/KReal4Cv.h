/*$Workfile: KReal4Cv.h$: header file
  $Revision: 4$ $Date: 1/24/02 7:19:06 PM$
  $Author: Darko$

  Conversion helper for 4 bytes real numbers (float)
  Copyright: CommonSoft Inc
  Mar 2k. D.Kolakovic  
*/

#ifndef __KREAL4CV_H__
  /*KReal4Cv.h sentry                                                       */
  #define __KREAL4CV_H__

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
#endif  /*__KREAL4CV_H__                                                     */
