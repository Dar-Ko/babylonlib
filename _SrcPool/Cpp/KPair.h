/*$Workfile: KPair.h$: header file
  $Revision: 8$ $Date: 2003-08-22 14:59:17$
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
//The TPair class is used to compare ordered pair of numbers (x,y).
//Comparison is along x-axis.
template<class TYPE> class TPair: public TPoint<TYPE>
{
//Construction
public:
  TPair(const TYPE& x = 0, const TYPE& y = 0);
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

      Y
     y|___.P(x,y)
      |  /|
      | / |
      |/  |
      +------- X
          x

 */
template<class TYPE>
inline TPair<TYPE>::TPair(const TYPE& x, //= 0 the x-coordinate of the point
                          const TYPE& y  //= 0 the y-coordinate of the point
                         ):
  TPoint<TYPE>(x,y)
{
}

/*
    A(xa,ya) = B(xb,yb) => xa = xb and ya = yb
 */
template<class TYPE>
inline TPair<TYPE>::TPair(const TPoint<TYPE>& tptPoint):
  TPoint<class TYPE>(tptPoint)
{
}

//-----------------------------------------------------------------------------
/*Orders two points along x-axis. Returns TRUE if P(x) < A(x) or point P is on
  semi-segment  P(y) < A(y) and P(x) = A(x).
   {html:<BR><IMG SRC="Res/PltA.gif" ALT="P(x,y) &lt A" BORDER="0">}
 */
template <class TYPE>
bool TPair<TYPE>::operator < (const TPair<TYPE>& tptPoint) const
{
return ((x <  tptPoint.x) || (x == tptPoint.x && y < tptPoint.y));
}

//-----------------------------------------------------------------------------
/*Orders two points along x-axis. Returns TRUE if P(x) < A(x) or point P is on
  semi-segment  P(y) <= A(y) and P(x) = A(x).
   {html:<BR><IMG SRC="Res/PleA.gif" ALT="P(x,y) =&lt; A" BORDER="0">}
 */
template <class TYPE>
bool TPair<TYPE>::operator <= (const TPair<TYPE>& tptPoint) const
{
return ((x <  tptPoint.x) || (x == tptPoint.x && y <= tptPoint.y));
}

//-----------------------------------------------------------------------------
/*Orders two points along x-axis. Returns TRUE if P(x) > A(x) or point P is on
  semi-segment  P(y) > A(y) and P(x) = A(x).
   {html:<BR><IMG SRC="Res/PgtA.gif" ALT="P(x,y) &gt; A" BORDER="0">}
 */
template <class TYPE>
bool TPair<TYPE>::operator > (const TPair<TYPE>& tptPoint) const
{
return ((x >  tptPoint.x) || (x == tptPoint.x && y > tptPoint.y));
}

//-----------------------------------------------------------------------------
/*Orders two points along x-axis. Returns TRUE if P(x) > A(x) or point P is on
  semi-segment  P(y) >= A(y) and P(x) = A(x).
   {html:<BR><IMG SRC="Res/PgeA.gif" ALT="P(x,y) &gt;= A" BORDER="0">}
 */
template <class TYPE>
bool TPair<TYPE>::operator >= (const TPair<TYPE>& tptPoint) const
{
return ((x >  tptPoint.x) || (x == tptPoint.x && y >= tptPoint.y));
}

///////////////////////////////////////////////////////////////////////////////
#endif  //_KPAIR_H_

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: 
 *  4    Biblioteka1.3         7/19/01 11:58:32 PM  Darko           VSS tags
 *  3    Biblioteka1.2         7/7/01 11:10:30 PM   Darko           $Revision: 8$
 *       inserted
 *  2    Biblioteka1.1         6/8/01 10:51:09 PM   Darko           VSS
 *  1    Biblioteka1.0         8/13/00 2:56:52 PM   Darko           
 * $
 *****************************************************************************/
