/*$RCSfile: KMatrix.h,v $: header file
  $Revision: 1.2 $ $Date: 2009/07/15 16:04:45 $
  $Author: ddarko $

  Basic matrix operations
  1998-12-02 Philip J. Erdelsky
 */

#ifndef _KMATRIX_H_
    //$RCSfile: KMatrix.h,v $ sentry
  #define _KMATRIX_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#ifdef __cplusplus

#include <mem.h>

////////////////////////////////////////////////////////////////////////////////
/*This package performs all of the most common TMatrix operations for rather
  arbitrary matrices. The package is implemented as a template class, in which
  the type of the TMatrix elements is a parameter.


  To define a TMatrix, first choose a type for the TMatrix elements.
  Usually, this is float or double. It must be a type which implements
  the usual aritmetic operations: addition, subtraction, multiplication,
  division and comparison.

  Then define a TMatrix type as follows:

     general form:  typedef TMatrix<TYPE> mymatrix;

     example:       typedef TMatrix<float> mymatrix;

  There are two constructors:

     mymatrix A(height, width);

     int height;     number of rows in TMatrix
     int width ;     number of columns in TMatrix

     mymatrix A(B);

     mymatrix B;     TMatrix to be copied into A

  Notice that the dimensions of a TMatrix are determined when it is constructed
  and cannot be changed dynamically.

  The usual TMatrix operations are implemented as overloaded operators:

     A + B
     A - B
     - A
     A * B
     x * B   x is a scalar of the same type as TMatrix elements
     A = B   assignment of matrices
     A == B  comparison of matrices

  Other operations are as follows:

    A.inverse
    A.transpose
    A.height
    A.width
    A(i,j)       element in i-th row and j-th column of A, where
                 the upper left element is A(1,1)

    out << A     edit and send a TMatrix to an output stream

    in >> A      read a TMatrix from an input stream

A   static function returns an identity TMatrix of the specified size:

    mymatrix::I(N)   returns N X N identity TMatrix

  Both the input and output operations process the elements in lexicographical
  order, i.e., the order in which English text is usually read when the TMatrix
  elements are in their usual positions.

  If there is an error, the package will throw an exception called
  mymatrix::exception, which has a member that explains the error.
  You can catch the exception as follows:

     try
     {
       ...
       TMatrix operations
     }
     catch (mymatrix::exception &E)
     {
       cout << E.message;
     }

  Expressions such as A.height, A.width, A.transpose and A.inverse are
  implemented as properties. If the C++ compiler does not support properties,
  slight changes will convert them to member functions.

Parameters:
  - TYPE the type of objects stored in the matrix.

*/
template <class TYPE> class TMatrix
{
public:
  TMatrix(int height, int width);
  TMatrix(const TMatrix &);
  void operator = (TMatrix);
  ~TMatrix();
  __property int height = {read=h};
  __property int width = {read=w};
  __property TMatrix transpose = {read=trans};
  __property TMatrix inverse = {read=inv};
  TYPE & operator () (int, int) const;

private:
  TMatrix trans(void) const;
  TMatrix inv(void) const;
  static TMatrix I(int);

private:
  int h, w;
  TYPE *cells;

  class exception
    {
    public:
      const char *message;
      exception(const char *s) {message = s;}
    };
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*
 */
template <class TYPE> TMatrix<TYPE>::TMatrix(int height, int width)
{
h = height;
w = width;
int n = h*w;
cells = new TYPE[n];
}

/*
 */
template <class TYPE> TMatrix<TYPE>::TMatrix(const TMatrix<TYPE> &A)
{
h = A.height;
w = A.width;
cells = new TYPE[h*w];
memcpy(cells, A.cells, h*w*sizeof(TYPE));
}

//-----------------------------------------------------------------------------
/*
 */
template <class TYPE> TMatrix<TYPE>::~TMatrix()
{
delete cells;
}

//-----------------------------------------------------------------------------
/*
 */
template <class TYPE> void TMatrix<TYPE>::operator = (TMatrix<TYPE> A)
{
if (h != A.height || w != A.width)
  throw TMatrix<TYPE>::exception("Incompatible TMatrix dimensions");
h = A.height;
w = A.width;
memcpy(cells, A.cells, h*w*sizeof(TYPE));
}

//-----------------------------------------------------------------------------
/*
 */
template <class TYPE> TYPE &TMatrix<TYPE>::operator () (int row, int column) const
{
return cells[(row-1)*w + column - 1];
}

//-----------------------------------------------------------------------------
/*
 */
template <class TYPE> TMatrix<TYPE> TMatrix<TYPE>::trans(void) const
{
TMatrix<TYPE> TYPE(width, height);
int i;
for (i = 1; i <= TYPE.height; i++)
  {
  int j;
  for (j = 1; j <= TYPE.width; j++)
    TYPE(i,j) = (*this)(j,i);
  }
return TYPE;
}

//-----------------------------------------------------------------------------
/*
 */
template <class TYPE> TMatrix<TYPE> TMatrix<TYPE>::I(int n)
{
if (n < 1)
  n = 1;
TMatrix<TYPE> U(n, n);
int i;
for (i = 1; i <= n; i++)
  U(i,i) = 1.0;
return U;
}

//-----------------------------------------------------------------------------
/*
 */
template <class TYPE> TMatrix<TYPE> TMatrix<TYPE>::inv(void) const
{
if (height != width)
  throw exception("Inversion of non-square TMatrix");
const int N = height;
TMatrix<TYPE> B(*this), R(N,N);
R = I(N);
int k;
for (k = 1; k <= N; k++)
  {
  int pivot_row = 0;
  TYPE pivot_value;
  TYPE abs_pivot_value;
  int i;
  for (i = k; i <= N; i++)
    {
    TYPE x = B(i,k);
    TYPE absx = x;
    if (absx < 0)
      absx = -absx;
    if (pivot_row == 0 || absx > abs_pivot_value)
      {
      pivot_row = i;
      abs_pivot_value = absx;
      pivot_value = x;
      }
    if (pivot_value == 0.0)
      throw exception("Inversion of singular TMatrix");
    }
  int j;
  if (pivot_row == k)
    {
    for (j = k; j <= N; j++)
      B(k,j) = B(k,j) / pivot_value;
    for (j = 1; j <= N; j++)
      R(k,j) = R(k,j) / pivot_value;
    }
  else
    {
    for (j = k; j <= N; j++)
      {
      TYPE x = B(k,j);
      B(k,j) = B(pivot_row,j) / pivot_value;
      B(pivot_row,j) = x;
      }
    for (j = 1; j <= N; j++)
      {
      TYPE x = R(k,j);
      R(k,j) = R(pivot_row,j) / pivot_value;
      R(pivot_row,j) = x;
      }
    }
  for (i = 1; i <= N; i++)
    {
    if (i != k)
      {
      int j;
      for (j = k+1; j <= N; j++)
        B(i,j) = B(i,j) - B(i,k) * B(k,j);
      for (j = 1; j <= N; j++)
        R(i,j) = R(i,j) - B(i,k) * R(k,j);
      }
    }
  }
return R;
}

///////////////////////////////////////////////////////////////////////////////
//

//-----------------------------------------------------------------------------
/*
 */
template <class TYPE> TMatrix<TYPE> operator + (TMatrix<TYPE> A, TMatrix<TYPE> B)
{
if (A.height != B.height || A.width != B.width)
  throw TMatrix<TYPE>::exception("Incompatible TMatrix dimensions");
int i;
for (i = 1; i <= A.height; i++)
  {
  int j;
  for (j = 1; j <= A.width; j++)
    A(i,j) = A(i,j) + B(i,j);
  }
return A;
}

//-----------------------------------------------------------------------------
/*
 */
template <class TYPE> TMatrix<TYPE> operator - (TMatrix<TYPE> A)
{
int i;
for (i = 1; i <= A.height; i++)
  {
  int j;
  for (j = 1; j <= A.width; j++)
    A(i,j) = -A(i,j);
  }
return A;
}

/*
 */
template <class TYPE> TMatrix<TYPE> operator - (TMatrix<TYPE> A, TMatrix<TYPE> B)
{
if (A.height != B.height || A.width != B.width)
  throw TMatrix<TYPE>::exception("Incompatible TMatrix dimensions");
int i;
for (i = 1; i <= A.height; i++)
  {
  int j;
  for (j = 1; j <= A.width; j++)
    A(i,j) = A(i,j) - B(i,j);
  }
return A;
}

//-----------------------------------------------------------------------------
/*
 */
template <class TYPE> TMatrix<TYPE> operator * (TYPE x, TMatrix<TYPE> A)
{
int i;
for (i = 1; i <= A.height; i++)
  {
  int j;
  for (j = 1; j <= A.width; j++)
    A(i,j) = x * A(i,j);
  }
return A;
}

/*
 */
template <class TYPE> TMatrix<TYPE> operator* (TMatrix<TYPE> A, TMatrix<TYPE> B)
{
if (A.width != B.height)
  throw TMatrix<TYPE>::exception("Incompatible TMatrix dimensions");
int i;
TMatrix<TYPE> AB(A.height, B.width);
for (i = 1; i <= AB.height; i++)
  {
  int j;
  for (j = 1; j <= AB.width; j++)
    {
    AB(i,j) = 0.0;
    int k;
    for (k = 1; k <= A.width; k++)
      AB(i,j) = AB(i,j) + A(i,k) * B(k,j);
    }
  }
return AB;
}

//-----------------------------------------------------------------------------
/*
 */
template <class TYPE> bool operator == (TMatrix<TYPE> A, TMatrix<TYPE> B)
{
if (A.height != B.height || A.width != B.width)
  throw TMatrix<TYPE>::exception("Incompatible TMatrix dimensions");
int i;
for (i = 1; i <= A.height; i++)
  {
  int j;
  for (j = 1; j <= A.width; j++)
    {
    if (!(A(i,j) == B(i,j)))
      return false;
    }
  }
return true;
}

///////////////////////////////////////////////////////////////////////////////

#ifdef  _USE_STL //Standard Template Library (STL)

  #include <iostream>

  //----------------------------------------------------------------------------
  /*
   */
  template <class TYPE> istream & operator >> (istream &in, TMatrix<TYPE> &A)
  {
  for (int i = 1; i <= A.height; i++)
    {
    for (int j = 1; j <= A.width; j++)
      in >> A(i,j);
    }
  return in;
  }

  //----------------------------------------------------------------------------
  /*
   */
  template <class TYPE> ostream & operator << (ostream &out, TMatrix<TYPE> A)
  {
  int width = out.width();
  int precision = out.precision();
  long flags = out.flags();
  for (int i = 1; i <= A.height; i++)
    {
    for (int j = 1; j <= A.width; j++)
      {
      out.width(width);
      out.precision(precision);
      out.flags(flags);
      out << A(i,j);
      }
    out << endl;
    }
  return out;
  }
#endif //_USE_STL
///////////////////////////////////////////////////////////////////////////////

#endif //__cplusplus
#endif  //_KMATRIX_H_
/*****************************************************************************
 * $Log: KMatrix.h,v $
 * Revision 1.2  2009/07/15 16:04:45  ddarko
 * Reformatted code
 *
 *****************************************************************************/

/*Author: Philip J. Erdelsky; pje@acm.org; http://www.alumni.caltech.edu/~pje/
  Date:        December 2, 1998
  Usage:       Public domain; no restrictions on use
  Portability: Any C++ compiler that implements templates, exceptions and properties
  Keywords:    Matrix
  Abstract:    A C++ package to perform basic TMatrix operations
 */