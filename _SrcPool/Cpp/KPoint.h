/*$Workfile: KPoint.h$: header file
  $Revision: 7$ $Date: 2002-04-04 00:13:01$
  $Author: Darko$

  TPoint represents points in orthogonal coordinate system
  Copyright: CommonSoft Inc
  May 94 CPoint class created Darko Kolakovic
  Jul 95 class replaced with template TPoint D.K.
  Mar 2k added comparison operators D.K.
 */
  
// Group=Mathematics

#ifndef _KPOINT_H_
    //KPoint.h sentry
  #define _KPOINT_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
//The TPoint class represents a location in a two-dimensional Cartesian
//coordinate system.
//    {html:<BR><IMG SRC="Res/OrthoCoordinateSystem.gif" BORDER="0">}
//
//This class could be used as a base class whenever an ordered pair
//of numbers is needed.
template<class TYPE> class TPoint
{
//Construction
public:
  TPoint(const TYPE& x = 0, const TYPE& y = 0);
  TPoint(const TPoint<TYPE>& tptPoint);

  //Microsoft's MFC Utility functions
  #ifdef __AFXWIN_H__
    TPoint(CPoint const& tptPoint);
    TPoint(CSize const& tptPoint);
    operator CPoint();
  #endif //__AFXWIN_H__

      //Data
public:
  TYPE x; //Specifies the x-coordinate of the point.
  TYPE y; //Specifies the y-coordinate of the point.

    //Operations
public:
  TPoint& operator = (const TPoint<TYPE>& Point);
  TPoint& operator = (const TYPE& ptConst);
  TPoint& operator +=(const TPoint<TYPE>& Vector);
  TPoint& operator +=(const TYPE& ptConst);
  TPoint& operator -=(const TPoint<TYPE>& Vector);
  TPoint& operator -=(const TYPE& ptConst);
  TPoint& operator *=(const TPoint<TYPE>& Coeff);
  TPoint& operator *=(const TYPE& ptConst);
  TPoint& operator /=(const TPoint<TYPE>& Coeff);
  TPoint& operator /=(const TYPE& ptConst);
  TPoint  operator + (const TPoint<TYPE>& Distance) const;
  TPoint  operator - (const TPoint<TYPE>& Distance) const;
  #ifdef _DOCBROwSER //Dummy elif
  #else
  TPoint  operator -() const;
  #endif
  BOOL    operator ==(const TPoint<TYPE>& Point) const;
  BOOL    operator !=(const TPoint<TYPE>& Point) const;
  
  double  Distance() const;
  double  Angle() const;
  TPoint  polar(const TYPE& Rho, const TYPE  Angle);

// Overrides
public:
  virtual BOOL operator < (const TPoint<TYPE>& Point) const;
  virtual BOOL operator <=(const TPoint<TYPE>& Point) const;
  virtual BOOL operator >=(const TPoint<TYPE>& Point) const;
  virtual BOOL operator > (const TPoint<TYPE>& Point) const;

};


///////////////////////////////////////////////////////////////////////////////
//The fPOINT class defines the x- and y- coordinates of a point in Cartesian
//coordinate system. Coordinates of a point are stored in x and y members with
//float precision.
typedef TPoint<float> fPOINT;

///////////////////////////////////////////////////////////////////////////////
// Inlines

//::TPoint()-----------------------------------------------------------------
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
inline TPoint<TYPE>::TPoint(const TYPE& x, //= 0 the x-coordinate of the point
                            const TYPE& y  //= 0 the y-coordinate of the point
                           ):
  x(x),y(y)
  {
  }

/*Assignment constructor

    A(xa,ya) = B(xb,yb) => xa = xb and ya = yb
 */
template<class TYPE>
inline TPoint<TYPE>::TPoint(const TPoint<TYPE>& tptPoint):
  x(tptPoint.x),y(tptPoint.y)
  {
  }

#ifdef __AFXWIN_H__ //Microsoft's MFC Utility functions

  /*Assignment constructor P(x,y) = C(x,y)
    x   specifies the x-coordinate of the point.
    y   specifies the y-coordinate of the point.
    
    Note: uses Microsoft Fundation Library (MFC).
   */
  template<class TYPE>
  inline TPoint<TYPE>::TPoint(CPoint const& tptPoint) :
  x((TYPE)tptPoint.x),y((TYPE)tptPoint.y)
    {
    }

  /*Assignment constructor  P(x,y) = C(cx,cy)
    cx   specifies the x-extent.
    cy   specifies the y-extent.
    
    Note: uses Microsoft Fundation Library (MFC).
   */
  template<class TYPE>
  inline TPoint<TYPE>::TPoint(CSize const& tptPoint) :
  x((TYPE)tptPoint.cx),y((TYPE)tptPoint.cy)
    {
    }

  //::operator CPoint()--------------------------------------------------------
  /*Returns coordnate pair (x,y). Values are truncated to LONG.
   */
  template<class TYPE>
  inline TPoint<TYPE>::operator CPoint()
    {
    return (CPoint((LONG)x,(LONG),y));
    }

#endif  //__AFXWIN_H__

//::operator=()----------------------------------------------------------------
/*Assignment operator

    A(xa,ya) = B(xb,yb) => xa = xb and ya = yb
 */
template<class TYPE>
inline TPoint<TYPE>& TPoint<TYPE>::operator =(const TPoint<TYPE>& Point)
{
x = Point.x;
y = Point.y;
return (*this);
}

/*Assigns a constant to the both coordinates of the point P

     P(x,y) = C(a,a) => x = a and y = a
 */
template<class TYPE>
inline TPoint<TYPE>& TPoint<TYPE>::operator =(const TYPE& ptConst)
{
x = ptConst;
y =(TYPE)0;
return (*this);
}

//::operator+=()---------------------------------------------------------------
/* Translates point P by adding value of the vector V. Vector have same format
   as point, but members x and y represents intensity of the vector in X and Y direction.

     V = X + Y;
     P(x,y)
     P + V = P(x+X,y+Y)  => x = x + X and  y = y + Y

      Y
     -|----o P(x+X,y+Y)
      |   /|
     Y|  / |
     -|-o P(x,y)
      | |  |
      +-------X
        |X |

 */
template<class TYPE>
inline TPoint<TYPE>& TPoint<TYPE>::operator +=(const TPoint<TYPE>& Vector)
{
x +=Point.x;
y +=Point.y;
return(*this);
}

/*Offsets point P by adding a constant to both coordinates

      P + C = P(x+c,y+c)
 */
template<class TYPE>
inline TPoint<TYPE>& TPoint<TYPE>::operator +=(const TYPE& ptConst)
{
x += ptConst;
return( *this );
}

//::operator-=()---------------------------------------------------------------
/* Translates point P by subtracting  value of the vector V. Vector have same format
   as point, but members x and y represents intensity of the vector in X and Y direction.

    V = X + Y;
    P(x,y)
    P - V = P(x-X,y-Y)  => x = x - X and  y = y - Y
 */
template<class TYPE>
inline TPoint<TYPE>& TPoint<TYPE>::operator -=(const TPoint<TYPE>& Vector)
{
x -=Point.x;
y -=Point.y;
return( *this );
}

/*Offsets point P by subtracting a constant to both coordinates

      P - C = P(x-c,y-c)
 */
template<class TYPE>
inline TPoint<TYPE>& TPoint<TYPE>::operator -=(const TYPE& ptConst)
{
x -= ptConst;
return( *this );
}

//::operator*=()---------------------------------------------------------------
/*Translates point P by multiplying each coordinate with translation factors.

    F = fx + fy;
    P(x,y)
    P * F = P(x*fx,y*fy)  => x = x * fx and  y = y * fy
 */
template<class TYPE>
inline TPoint<TYPE>& TPoint<TYPE>::operator *=(const TPoint<TYPE>& Coeff)
{

x *= Coeff.x;
y *= Coeff.y;
return *this;
}

/*Translates point P by scaling each coordinate with translation constant.
 */
template<class TYPE>
inline TPoint<TYPE>& TPoint<TYPE>::operator *=(const TYPE& ptConst)
{
x *= ptConst;
y *= ptConst;
return(*this);
}

//::operator/=()---------------------------------------------------------------
/*Translates point P by dividing each coordinate with translation factors.

    F = fx + fy;
    P(x,y)
    P / F = P(x/fx,y/fy)  => x = x / fx and  y = y / fy
 */
template<class TYPE>
inline TPoint<TYPE>& TPoint<TYPE>::operator /=(const TPoint<TYPE>& Point)
{
x /= ptConst;
y /= ptConst;
return *this;
}

/*Translates point P by scaling each coordinate with translation constant.
 */
template<class TYPE>
inline TPoint<TYPE>& TPoint<TYPE>::operator /=(const TYPE& ptConst)
{
x /= ptConst;
y /= ptConst;
return (*this);
}

//::operator+()----------------------------------------------------------------
/*Returns new point P1 at distance D from first point P.

   P1 = P + D = P1(x + dx, y + dy)
 */
template<class TYPE>
inline TPoint<TYPE>  TPoint<TYPE>::operator +(const TPoint<TYPE>& Distance) const
{
return TPoint<TYPE>(x + Distance.x, y + Distance.y);
}

//::operator-()----------------------------------------------------------------
/*Returns new point P1 at distance D from first point P.

   P1 = P - D = P1(x - dx, y - dy)
 */
template<class TYPE>
inline TPoint<TYPE>  TPoint<TYPE>::operator -(const TPoint<TYPE>& Distance) const
{
return TPoint<TYPE>(x - Distance.x, y - Distance.y);
}

//::operator-()----------------------------------------------------------------
/*- sign unary operator returns the inversion point

      -P = P(-x, -y)
 */
template<class TYPE>
inline TPoint<TYPE> TPoint<TYPE>::operator - () const
{
return TPoint<TYPE>(-x,-y);
}

//operator==()-----------------------------------------------------------------
/*Determines whether two points are equal. Returns TRUE if points represents
  same location in two dimensional space.
 */
template<class TYPE>
inline BOOL TPoint<TYPE>::operator ==(const TPoint<TYPE>& Point) const
{
return ((x == Point.x) && (y == Point.y));
}

//operator!=()-----------------------------------------------------------------
/*Determines whether two points are not equal. Returns TRUE if points are
  different locations in two-dimensional space.
 */
template<class TYPE>
inline BOOL TPoint<TYPE>::operator !=(const TPoint<TYPE>& Point) const
{
return ((x != Point.x) || (y != Point.y));
}

//operator<()------------------------------------------------------------------
/*Compares two points. Returns TRUE if P(x) < A(x) and P(y) < A(y).
   {html:<BR><IMG SRC="Res/PTltA.gif" ALT="P(x,y) &lt A" BORDER="0">}
 */
template <class TYPE>
BOOL TPoint<TYPE>::operator < (const TPoint<TYPE>& tptPoint) const
{
return ((x < tptPoint.x) && (y < tptPoint.y));
};

//operator<=()-----------------------------------------------------------------
/*Compares two points. Returns TRUE if P(x) <= A(x) and P(y) <= A(y).
   {html:<BR><IMG SRC="Res/PTleA.gif" ALT="P(x,y) =&lt; A" BORDER="0">}
 */
template <class TYPE>
BOOL TPoint<TYPE>::operator <= (const TPoint<TYPE>& tptPoint) const
{
return ((x <= tptPoint.x) && (y <= tptPoint.y));
}

//operator>()------------------------------------------------------------------
/*Compares two points. Returns TRUE if P(x) > A(x) and P(y) > A(y).
   {html:<BR><IMG SRC="Res/PTgtA.gif" ALT="P(x,y) &gt; A" BORDER="0">}
 */
template <class TYPE>
BOOL TPoint<TYPE>::operator > (const TPoint<TYPE>& tptPoint) const
{
return ((x >  tptPoint.x) && (y > tptPoint.y));
}

//operator>=()-----------------------------------------------------------------
/*Compares two points. Returns TRUE if P(x) >= A(x) and P(y) >= A(y)
   {html:<BR><IMG SRC="Res/PTgeA.gif" ALT="P(x,y) &gt;= A" BORDER="0">}
 */
template <class TYPE>
BOOL TPoint<TYPE>::operator >= (const TPoint<TYPE>& tptPoint) const
{
return ((x >=  tptPoint.x) && (y >= tptPoint.y));
}

//::Distance()-----------------------------------------------------------------
#include "KMathCst.h" //Absolute
/*Returns distance between point P(x2,y2) and origin O(x1=0, y1=0).
  {html:<BR><IMG SRC="Res/eqDistance2Pt2D.gif" BORDER="0">}

      Y
      |___.P(x2,y2)
      |  /|
      |d/ |
      |/  |
      +-------X
     0(x1,y1)

    d = sqrt(x2**2+y2**2)

  Example:
      #include "KPoint.h"  //TPoint template

      //Calculate distance between two points
      int GetDistance()
        {
        TPoint<int> A(150, 250);
        TPoint<int> B(-40,  50);
        B =- A;       //Get difference between points
        return Double2Int(B.Distance()); //Return rounded value
        }
*/
template<class TYPE>
inline double TPoint<TYPE>::Distance() const
{
if (x == (TYPE)0)
  return Absolute(y);
if (y == (TYPE)0)
  return Absolute(x);

return sqrt(SQUARE((double)x) + SQUARE((double)y));
}

//::Angle()--------------------------------------------------------------------
/*Return: angle in radians between the line from the origin to the point and
  the x-axis.
  {html:<BR><IMG SRC="Res/eqOrtho2Polar.gif" BORDER="0">}

     theta = atan(y/x);

 See also: polar().

 Note: If x coordinate is 0, function returns 0.

 Example:
    #include "KPoint.h"  //TPoint template
    //Convert Cartesian coordinates to polar system
    TPoint<double> GetPolar(const TPoint<double>& Point)
      {
        //Return ordered pair (rho, theta)
      return TPoint<double>(Point.Distance(),Point.Angle());
      }

*/
template<class TYPE>
inline double TPoint<TYPE>::Angle() const
{
return atan2((double)y, (double)x);
}

//polar()----------------------------------------------------------------------
/*Converts a point in polar coordinate system represented by an ordered pair
 (rho,theta) into Cartesian coordinates.
     {html:<BR><IMG SRC="Res/PolarCoordinateSystem.gif" BORDER="0">}
     {html:<BR><IMG SRC="Res/eqPolar2Ortho.gif" ALT= "x = r cos(t), y = r sin(t)" BORDER="0">}
 */
template <class TYPE>
inline TPoint<TYPE> TPoint<TYPE>::polar(const TYPE& Rho,   //distance from the origin
                                        const TYPE  Angle  //=0 angle [rad] between the line
                                                           //from the origin to the point and
                                                           //the x-axis.
                          )
{
return  (Angle ==  (TYPE)0) ?
        TPoint<TYPE>(Rho, (TYPE)0) :
        TPoint<TYPE>(Rho * ::cos(Angle), Rho * ::sin(Angle));
}

///////////////////////////////////////////////////////////////////////////////
#endif  //_KPOINT_H_

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: 
 *  7    Biblioteka1.6         2002-04-04 00:13:01  Darko           Documenation
 *       update
 *  6    Biblioteka1.5         2002-01-29 22:21:33  Darko           Used lbraries
 *       notes 
 *  5    Biblioteka1.4         2002-01-25 15:57:34  Darko           Updated
 *       comments
 *  4    Biblioteka1.3         2001-07-19 23:58:35  Darko           VSS tags
 *  3    Biblioteka1.2         2001-07-11 21:52:03  Darko           
 *  2    Biblioteka1.1         2001-06-08 22:51:14  Darko           VSS
 *  1    Biblioteka1.0         2000-08-13 14:56:57  Darko           
 * $
 *****************************************************************************/
