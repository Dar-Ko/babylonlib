// Matrix.h

#ifndef H__MATRIX
#define H__MATRIX 1

#include <iostream.h>
#include <mem.h>

/*Matrix Package
Title: 
Matrix Package 
Language: 
C++ 
Author: 
Philip J. Erdelsky 
pje@acm.org 
http://www.alumni.caltech.edu/~pje/ 
Date: 
December 2, 1998 
Usage: 
Public domain; no restrictions on use 
Portability: 
Any C++ compiler that implements templates, exceptions and properties 
Keywords: 
Matrix 
Abstract: 
A C++ package to perform basic matrix operations 
Source: 
matrix.h 
This package performs all of the most common matrix operations for rather arbitrary matrices. The package is implemented as a template class, in which the type of the matrix elements is a parameter. 

The file MATRIX.H includes the entire package. It must be included in, or copied into, any source file that uses the package. 

To define a matrix, first choose a type for the matrix elements. Usually, this is float or double. It must be a type which implements the usual aritmetic operations: addition, subtraction, multiplication, division and comparison. 

Then define a matrix type as follows: 

     general form:  typedef matrix<T> mymatrix;

     example:       typedef matrix<float> mymatrix;

There are two constructors: 

     mymatrix A(height, width);

     int height;     number of rows in matrix
     int width ;     number of columns in matrix

     mymatrix A(B);

     mymatrix B;     matrix to be copied into A

Notice that the dimensions of a matrix are determined when it is constructed and cannot be changed dynamically. 

The usual matrix operations are implemented as overloaded operators: 

     A + B
     A - B
     - A
     A * B
     x * B   x is a scalar of the same type as matrix elements
     A = B   assignment of matrices
     A == B  comparison of matrices

Other operations are as follows: 

    A.inverse
    A.transpose
    A.height
    A.width
    A(i,j)       element in i-th row and j-th column of A, where
                 the upper left element is A(1,1)

    out << A     edit and send a matrix to an output stream

    in >> A      read a matrix from an input stream

A static function returns an identity matrix of the specified size: 

    mymatrix::I(N)   returns N X N identity matrix

Both the input and output operations process the elements in lexicographical order, i.e., the order in which English text is usually read when the matrix elements are in their usual positions. 

If there is an error, the package will throw an exception called mymatrix::exception, which has a member that explains the error. You can catch the exception as follows: 

     try
     {
       ...
       matrix operations
     }
     catch (mymatrix::exception &E)
     {
       cout << E.message;
     }

Expressions such as A.height, A.width, A.transpose and A.inverse are implemented as properties. If the C++ compiler does not support properties, slight changes will convert them to member functions. 
*/
template <class T> class matrix
{
  private:
    int h, w;
    T *cells;
    matrix trans(void) const;
    matrix inv(void) const;
  public:
    matrix(int height, int width);
    matrix(const matrix &);
    void operator = (matrix);
    ~matrix();
    __property int height = {read=h};
    __property int width = {read=w};
    __property matrix transpose = {read=trans};
    __property matrix inverse = {read=inv};
    T & operator () (int, int) const;
    class exception
    {
      public:
      const char *message;
      exception(const char *s) {message = s;}
    };
    static matrix I(int);
};

template <class T> istream & operator >> (istream &in, matrix<T> &A)
{
  for (int i = 1; i <= A.height; i++)
  {
    for (int j = 1; j <= A.width; j++)
      in >> A(i,j);
  }
  return in;
}

template <class T> ostream & operator << (ostream &out, matrix<T> A)
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

template <class T> matrix<T>::matrix(int height, int width)
{
  h = height;
  w = width;
  int n = h*w;
  cells = new T[n];
}

template <class T> matrix<T>::matrix(const matrix<T> &A)
{
  h = A.height;
  w = A.width;
  cells = new T[h*w];
  memcpy(cells, A.cells, h*w*sizeof(T));
}

template <class T> void matrix<T>::operator = (matrix<T> A)
{
  if (h != A.height || w != A.width)
    throw matrix<T>::exception("Incompatible matrix dimensions");
  h = A.height;
  w = A.width;
  memcpy(cells, A.cells, h*w*sizeof(T));
}

template <class T> matrix<T>::~matrix()
{
  delete cells;
}

template <class T> T &matrix<T>::operator () (int row, int column) const
{
  return cells[(row-1)*w + column - 1];
}

template <class T> matrix<T> operator + (matrix<T> A, matrix<T> B)
{
  if (A.height != B.height || A.width != B.width)
    throw matrix<T>::exception("Incompatible matrix dimensions");
  int i;
  for (i = 1; i <= A.height; i++)
  {
    int j;
    for (j = 1; j <= A.width; j++)
      A(i,j) = A(i,j) + B(i,j);
  }
  return A;
}

template <class T> bool operator == (matrix<T> A, matrix<T> B)
{
  if (A.height != B.height || A.width != B.width)
    throw matrix<T>::exception("Incompatible matrix dimensions");
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

template <class T> matrix<T> operator - (matrix<T> A)
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

template <class T> matrix<T> operator * (T x, matrix<T> A)
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

template <class T> matrix<T> operator - (matrix<T> A, matrix<T> B)
{
  if (A.height != B.height || A.width != B.width)
    throw matrix<T>::exception("Incompatible matrix dimensions");
  int i;
  for (i = 1; i <= A.height; i++)
  {
    int j;
    for (j = 1; j <= A.width; j++)
      A(i,j) = A(i,j) - B(i,j);
  }
  return A;
}

template <class T> matrix<T> operator * (matrix<T> A, matrix<T> B)
{
  if (A.width != B.height)
    throw matrix<T>::exception("Incompatible matrix dimensions");
  int i;
  matrix<T> AB(A.height, B.width);
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

template <class T> matrix<T> matrix<T>::trans(void) const
{
  matrix<T> T(width, height);
  int i;
  for (i = 1; i <= T.height; i++)
  {
    int j;
    for (j = 1; j <= T.width; j++)
      T(i,j) = (*this)(j,i);
  }
  return T;
}

template <class T> matrix<T> matrix<T>::I(int n)
{
  if (n < 1)
    n = 1;
  matrix<T> U(n, n);
  int i;
  for (i = 1; i <= n; i++)
    U(i,i) = 1.0;
  return U;
}

template <class T> matrix<T> matrix<T>::inv(void) const
{
  if (height != width)
    throw exception("Inversion of non-square matrix");
  const int N = height;
  matrix<T> B(*this), R(N,N);
  R = I(N);
  int k;
  for (k = 1; k <= N; k++)
  {
    int pivot_row = 0;
    T pivot_value;
    T abs_pivot_value;
    int i;
    for (i = k; i <= N; i++)
    {
      T x = B(i,k);
      T absx = x;
      if (absx < 0)
        absx = -absx;
      if (pivot_row == 0 || absx > abs_pivot_value)
      {
        pivot_row = i;
        abs_pivot_value = absx;
        pivot_value = x;
      }
      if (pivot_value == 0.0)
        throw exception("Inversion of singular matrix");
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
        T x = B(k,j);
        B(k,j) = B(pivot_row,j) / pivot_value;
        B(pivot_row,j) = x;
      }
      for (j = 1; j <= N; j++)
      {
        T x = R(k,j);
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

#endif

