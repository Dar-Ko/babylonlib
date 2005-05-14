/*$Workfile: KPair.h$: header file
  $Revision: 9$ $Date: 2005-04-21 03:20:41$
  $Author: Darko$

  Ordered number pairs
  Copyright: CommonSoft Inc
  Mar 2k TPair template class created Darko Kolakovic
 */
// Group=Mathematics

#ifndef _KPAIR_H_
    //KPair.h sentry
  #define _KPAIR_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#include "KPoint.h" //TPoint template

///////////////////////////////////////////////////////////////////////////////
/*The TPair class is used to compare ordered pair of numbers (x,y)={x, {x,y}}.
  An ordered pair is a set of a pair of objects with an order associated with
  them.

  Note: Comparison is along x-axis.
 */
template<class TYPE> class TPair: public TPoint<TYPE>
{
//Construction
public:
  TPair(const TYPE& a = 0, const TYPE& b = 0);
  TPair(const TPoint<TYPE>& tptPoint);

    //Operations
public:
  bool operator < (const TPair<TYPE>& Point) const;
  bool operator <=(const TPair<TYPE>& Point) const;
  bool operator >=(const TPair<TYPE>& Point) const;
  bool operator > (const TPair<TYPE>& Point) const;
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*Default constructor
  P = (x,y)
 */
template<class TYPE>
inline TPair<TYPE>::TPair(const TYPE& a, //[in]= 0 first element of the setr
                          const TYPE& b  //[in]= 0 second element of the set
                         ):
  TPoint<TYPE>(a,b)
{
}

/*
    A(xa,ya) = B(xb,yb) => xa = xb and ya = yb
 */
template<class TYPE>
inline TPair<TYPE>::TPair(const TPoint<TYPE>& tptPoint//[in] point to convert
                         ):
  TPoint<class TYPE>(tptPoint)
{
}

//-----------------------------------------------------------------------------
/*Orders two points along x-axis.
  Returns: true if P(x) < A(x) or point P is on
  semi-segment  P(y) < A(y) and P(x) = A(x).
   {html:<br /><img src="Images/graphPltA.gif" alt="P(x,y) &lt A" border="0">}
 */
template <class TYPE>
bool TPair<TYPE>::operator < (const TPair<TYPE>& tptPoint //[in] value to compare
                             ) const
{
return ((x <  tptPoint.x) || (x == tptPoint.x && y < tptPoint.y));
}

//-----------------------------------------------------------------------------
/*Orders two points along x-axis.
  Returns: true if P(x) < A(x) or point P is on semi-segment
      P(y) <= A(y) and P(x) = A(x).
  {html:<br /><img src="Images/graphPleA.gif" alt="P(x,y) =&lt; A" border="0">}
 */
template <class TYPE>
bool TPair<TYPE>::operator <= (const TPair<TYPE>& tptPoint//[in] value to compare
                              ) const
{
return ((x <  tptPoint.x) || (x == tptPoint.x && y <= tptPoint.y));
}

//-----------------------------------------------------------------------------
/*Orders two points along x-axis.
  Returns: true if P(x) > A(x) or point P is on
  semi-segment  P(y) > A(y) and P(x) = A(x).
   {html:<br /><img src="Images/graphPgtA.gif" alt="P(x,y) &gt; A" border="0">}
 */
template <class TYPE>
bool TPair<TYPE>::operator > (const TPair<TYPE>& tptPoint//[in] value to compare
                             ) const
{
return ((x >  tptPoint.x) || (x == tptPoint.x && y > tptPoint.y));
}

//-----------------------------------------------------------------------------
/*Orders two points along x-axis.
  Returns: true if P(x) > A(x) or point P is on
  semi-segment  P(y) >= A(y) and P(x) = A(x).
   {html:<br /><img src="Images/graphPgeA.gif" alt="P(x,y) &gt;= A" border="0">}
 */
template <class TYPE>
bool TPair<TYPE>::operator >= (const TPair<TYPE>& tptPoint//[in] value to compare
                              ) const
{
return ((x >  tptPoint.x) || (x == tptPoint.x && y >= tptPoint.y));
}

///////////////////////////////////////////////////////////////////////////////
#endif  //_KPAIR_H_

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log:
 *  4    Biblioteka1.3         7/19/01 11:58:32 PM  Darko           VSS tags
 *  3    Biblioteka1.2         7/7/01 11:10:30 PM   Darko           $Revision: 9$
 *       inserted
 *  2    Biblioteka1.1         6/8/01 10:51:09 PM   Darko           VSS
 *  1    Biblioteka1.0         8/13/00 2:56:52 PM   Darko
 * $
 *****************************************************************************/
