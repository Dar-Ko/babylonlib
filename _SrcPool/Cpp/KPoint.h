/*$Workfile: KPoint.h$: header file
  $Revision: 11$ $Date: 2005-06-07 14:51:10$
  $Author: Darko Kolakovic$

  TPoint represents points in orthogonal coordinate system
  Copyright: CommonSoft Inc
  May 94 CPoint class created Darko Kolakovic
  Jul 95 class replaced with template TPoint D.K.
  Mar 2k added comparison operators D.K.
 */

// Group=Mathematics

#ifndef _KPOINT_H_
    //$Workfile: KPoint.h$ sentry
  #define _KPOINT_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
//The TPoint class represents a location in a two-dimensional Cartesian
//coordinate system.
//    {html:<br /><img src="Images/graph2DPointInOrthoSystem.gif"
//     alt="2D point in orthogonal coordinate system" border="0">}
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
  TYPE x; //specifies the x-coordinate of the point.
  TYPE y; //specifies the y-coordinate of the point.

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
  bool    operator ==(const TPoint<TYPE>& Point) const;
  bool    operator !=(const TPoint<TYPE>& Point) const;

  double  Distance() const;
  double  Angle() const;
  TPoint  polar(const TYPE& Rho, const TYPE  Angle);

// Overrides
public:
  virtual bool operator < (const TPoint<TYPE>& Point) const;
  virtual bool operator <=(const TPoint<TYPE>& Point) const;
  virtual bool operator >=(const TPoint<TYPE>& Point) const;
  virtual bool operator > (const TPoint<TYPE>& Point) const;

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
    {html:<br /><img src="Images/graph2DPointInOrthoSystem.gif"
     alt="2D point in orthogonal coordinate system" border="0">}
 */
template<class TYPE>
inline TPoint<TYPE>::TPoint(const TYPE& x, //[in]= 0 the x-coordinate of the point
                            const TYPE& y  //[in]= 0 the y-coordinate of the point
                           ):
  x(x),y(y)
  {
   /*
      Y
     y|___.P(x,y)
      |  /|
      | / |
      |/  |
      +------- X
          x
   */
  }

/*Assignment constructor

    A(xa,ya) = B(xb,yb) => xa = xb and ya = yb
 */
template<class TYPE>
inline TPoint<TYPE>::TPoint(const TPoint<TYPE>& tptPoint //[in] value to copy
                           ):
  x(tptPoint.x),y(tptPoint.y)
  {
  }

#ifdef __AFXWIN_H__ //Microsoft's MFC Utility functions

  /*Assignment constructor P(x,y) = C(x,y)
    x   specifies the x-coordinate of the point.
    y   specifies the y-coordinate of the point.

    Note: uses Microsoft Foundation Library (MFC).
   */
  template<class TYPE>
  inline TPoint<TYPE>::TPoint(CPoint const& tptPoint //[in] point to convert
                              ) :
  x((TYPE)tptPoint.x),y((TYPE)tptPoint.y)
    {
    }

  /*Assignment constructor  P(x,y) = C(cx,cy)
    cx   specifies the x-extent.
    cy   specifies the y-extent.

    Note: uses Microsoft Foundation Library (MFC).
   */
  template<class TYPE>
  inline TPoint<TYPE>::TPoint(CSize const& tptPoint //[in] dimension to convert
                             ) :
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
inline TPoint<TYPE>& TPoint<TYPE>::operator =(const TPoint<TYPE>& Point//[in]
                                              //new value to assign
                                             )
{
x = Point.x;
y = Point.y;
return (*this);
}

/*Assigns a constant to the both coordinates of the point P

     P(x,y) = C(a,a) => x = a and y = a
 */
template<class TYPE>
inline TPoint<TYPE>& TPoint<TYPE>::operator =(const TYPE& ptConst //[in]
                                              //new value to assign
                                             )
{
x = ptConst;
y =(TYPE)0;
return (*this);
}

//::operator+=()---------------------------------------------------------------
/* Translates point P by adding value of the vector V. Vector have same format
   as point, but members x and y represents intensity of the vector in X and Y
   direction.

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
inline TPoint<TYPE>& TPoint<TYPE>::operator +=(const TPoint<TYPE>& Vector //[in]
                                              //translating vector
                                              )
{
x +=Vector.x;
y +=Vector.y;
return(*this);
}

/*Offsets point P by adding a constant to both coordinates

      P + C = P(x+c,y+c)
 */
template<class TYPE>
inline TPoint<TYPE>& TPoint<TYPE>::operator +=(const TYPE& ptConst//[in]
                       //translating vector with equal components C(x=c, y=c)
                                              )
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
inline TPoint<TYPE>& TPoint<TYPE>::operator -=(const TPoint<TYPE>& Vector//[in]
                                              //translating vector
                                              )
{
x -=Point.x;
y -=Point.y;
return( *this );
}

/*Offsets point P by subtracting a constant to both coordinates

      P - C = P(x-c,y-c)
 */
template<class TYPE>
inline TPoint<TYPE>& TPoint<TYPE>::operator -=(const TYPE& ptConst//[in]
                       //translating vector with equal components C(x=c, y=c)
                                              )
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
inline TPoint<TYPE>& TPoint<TYPE>::operator *=(const TPoint<TYPE>& Coeff//[in]
                                              //translating vector
                                              )
{

x *= Coeff.x;
y *= Coeff.y;
return *this;
}

/*Translates point P by scaling each coordinate with translation constant.
 */
template<class TYPE>
inline TPoint<TYPE>& TPoint<TYPE>::operator *=(const TYPE& ptConst //[in]
                       //translating vector with equal components C(x=c, y=c)
                                              )
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
inline TPoint<TYPE>& TPoint<TYPE>::operator /=(const TPoint<TYPE>& Point//[in]
                                              //translating vector
                                              )
{
x /= ptConst;
y /= ptConst;
return *this;
}

/*Translates point P by scaling each coordinate with translation constant.
 */
template<class TYPE>
inline TPoint<TYPE>& TPoint<TYPE>::operator /=(const TYPE& ptConst//[in]
                       //translating vector with equal components C(x=c, y=c)
                                              )
{
x /= ptConst;
y /= ptConst;
return (*this);
}

//::operator+()----------------------------------------------------------------
/*Returns new point P1 at distance D from first point P.

  We defined addition as,
     {x, {x,y}}+{c, {c,d}}={x+c, {x+c, y+d}},
          (x,y) +(c,d) =(x+c, y+d) .

 The later could, for a particular representation, be written as
      P1 = P + D = P1(x + dx, y + dy)
 */
template<class TYPE>
inline TPoint<TYPE> TPoint<TYPE>::operator +(const TPoint<TYPE>& Distance//[in]
                                             //translation distance
                                            ) const
{
return TPoint<TYPE>(x + Distance.x, y + Distance.y);
}

//::operator-()----------------------------------------------------------------
/*Returns new point P1 at distance D from first point P.

   P1 = P - D = P1(x - dx, y - dy)
 */
template<class TYPE>
inline TPoint<TYPE> TPoint<TYPE>::operator -(const TPoint<TYPE>& Distance//[in]
                                             //translation distance
                                            ) const
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
/*Determines whether two points are equal.
  Two ordered pairs  representing points(x, y) and (a, b) are equal if
  and only if x = a and y = b.
  Returns: true if the points represents same location in two dimensional space.
 */
template<class TYPE>
inline bool TPoint<TYPE>::operator ==(const TPoint<TYPE>& Point //[in] point to
                                     //compare with
                                     ) const
{
return ((x == Point.x) && (y == Point.y));
}

//operator!=()-----------------------------------------------------------------
/*Determines whether two points are not equal.
  Returns: true if points are
  different locations in two-dimensional space.
 */
template<class TYPE>
inline bool TPoint<TYPE>::operator !=(const TPoint<TYPE>& Point//[in] point to
                                     //compare with
                                     ) const
{
return ((x != Point.x) || (y != Point.y));
}

//operator<()------------------------------------------------------------------
/*Compares two points.
  Returns: true if P(x) < A(x) and P(y) < A(y).
   {html:<br /><img src="Images/graphPTltA.gif" alt="P(x,y) &lt A" border="0">}
 */
template <class TYPE>
bool TPoint<TYPE>::operator < (const TPoint<TYPE>& tptPoint//[in] point to
                                     //compare with
                               ) const
{
return ((x < tptPoint.x) && (y < tptPoint.y));
};

//operator<=()-----------------------------------------------------------------
/*Compares two points.

  Returns: true if P(x) <= A(x) and P(y) <= A(y).
   {html:<br /><img src="Images/graphPTleA.gif" alt="P(x,y) =&lt; A" border="0">}
 */
template <class TYPE>
bool TPoint<TYPE>::operator <= (const TPoint<TYPE>& tptPoint//[in] point to
                                     //compare with
                                ) const
{
return ((x <= tptPoint.x) && (y <= tptPoint.y));
}

//operator>()------------------------------------------------------------------
/*Compares two points.
  Returns: true if P(x) > A(x) and P(y) > A(y).
   {html:<br /><img src="Images/graphPTgtA.gif" alt="P(x,y) &gt; A" border="0">}
 */
template <class TYPE>
bool TPoint<TYPE>::operator > (const TPoint<TYPE>& tptPoint//[in] point to
                                     //compare with
                              ) const
{
return ((x >  tptPoint.x) && (y > tptPoint.y));
}

//operator>=()-----------------------------------------------------------------
/*Compares two points.
  Returns: true if P(x) >= A(x) and P(y) >= A(y)
   {html:<br /><img src="Images/graphPTgeA.gif" alt="P(x,y) &gt;= A" border="0">}
 */
template <class TYPE>
bool TPoint<TYPE>::operator >= (const TPoint<TYPE>& tptPoint//[in] point to
                                     //compare with
                                ) const
{
return ((x >=  tptPoint.x) && (y >= tptPoint.y));
}

//::Distance()-----------------------------------------------------------------
#include "KMathCst.h" //Absolute
/*{html:
   Returns distance between point P(x2,y2) and origin O(x1=0, y1=0).

  <br />
  <img src="Images/eqDistance2PtNdim.gif"    alt="d = sqrt(&Sigma;|a-b|**2)">
  <br />
  <img src="Images/eqDistance2Pt2D.gif"    alt="d = sqrt((x2-x1)**2+(y2-y1)**2)">
  <br />
  <img src="Images/graphDistance0Pt2D.gif" alt="Distance to 2D point"> <br />
  <img src="Images/eqDistance0Pt2D.gif"    alt="d = sqrt(x2**2+y2**2)">
  }

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

/*   Y
      |___.P(x2,y2)
      |  /|
      |d/ |
      |/  |
      +-------X
     0(x1,y1)
 */
return sqrt(SQUARE((double)x) + SQUARE((double)y));
}

//::Angle()--------------------------------------------------------------------
/*Returns: angle in radians between the line from the origin to the point and
  the x-axis.
  {html:<br /><img src="Images/eqOrtho2Polar.gif" border="0"
              alt="&rho;^2=x^2+y^d, tan(&theta;)=y/x">

     <img src="Images/eqPolarAngle.gif" border="0"
             alt="&theta; = atan(y/x)">;
  }

 See also: polar().

 Note: If x coordinate is 0, function returns 0.

 Example:
    {html: <pre><code>

    #include "KPoint.h"  //TPoint template
    //Convert Cartesian coordinates to polar system
    TPoint<double> GetPolar(const TPoint<double>& Point)
      {
        //Return ordered pair (&rho;, &theta;)
      return TPoint<double>(Point.Distance(),Point.Angle());
      }

   </code></pre>}
*/
template<class TYPE>
inline double TPoint<TYPE>::Angle() const
{
return atan2((double)y, (double)x);
}

//polar()----------------------------------------------------------------------
/*{html:
  Converts a point in polar coordinate system represented by an ordered pair
  (&rho;,&theta;) into Cartesian coordinates.

       <br /><img src="Images/graph2DPointInPolarSystem.gif" border="0"
               alt="Polar Coordinate system">
       <br /><img src="Images/eqPolar2Ortho.gif"  border="0"
               alt="x = r cos(t), y = r sin(t)">
  }
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
 *  7    Biblioteka1.6         4/4/2002 1:13:01 AM  Darko           Documenation
 *       update
 *  6    Biblioteka1.5         1/29/2002 11:21:33 PMDarko           Used lbraries
 *       notes
 *  5    Biblioteka1.4         1/25/2002 4:57:34 PM Darko           Updated
 *       comments
 *  4    Biblioteka1.3         7/20/2001 12:58:35 AMDarko           VSS tags
 *  3    Biblioteka1.2         7/11/2001 10:52:03 PMDarko
 *  2    Biblioteka1.1         6/8/2001 11:51:14 PM Darko           VSS
 *  1    Biblioteka1.0         8/13/2000 3:56:57 PM Darko
 * $
 *****************************************************************************/
