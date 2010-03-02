/*$RCSfile: TestTemplateNestingS.cpp,v $: implementation file
  $Revision: 1.1 $ $Date: 2010/03/02 23:02:15 $
  $Author: ddarko $

  Test C++ compiler conformance of nesting template classes.
  MSDN: http://msdn.microsoft.com/en-us/library/71dw8xzh.aspx
  2010-03-92 Darko Kolakovic
*/

/* Group=Examples                                                            */

#include "TestConformance.h"
#ifndef _T
  #include "KTChar.h"
#endif
#ifndef LOG_EOT
  #include "KTestLog.h"
#endif

extern bool TsWriteToViewLn(LPCTSTR lszText);

///////////////////////////////////////////////////////////////////////////////
// Nested class template inside an ordinary class.
//
class X
{
  template <class T>
  struct Y
    {
      T m_t;
      Y(T t):
        m_t(t)
        {
        }
    };

public:
  Y<int>  yInt;
  Y<char> yChar;

public:
  X(int i, char c) :
    yInt(i), yChar(c)
    {
    }
  void Out()
    {
    TRACE2(_T("[%d, %d]\n"), yInt.m_t, yChar.m_t);
    }
};


/*Templates can be defined within classes or class templates, in which case they
  are referred to as member templates.
  Member templates that are classes are referred to as nested class templates.
  Nested class templates are declared as class templates inside the scope of
  the outer class. They can be defined inside or outside of the enclosing class.
 */

/*---------------------------------------------------------------------------*/
/*Validates C++ compiler conformance.
  Returns: true if test is successful; otherwise returns false.
 */
bool TestTemplateSimpleNesting()
{
bool bResult = false;
X x(101, 'a');
x.Out();

bResult = bResult && (x.yInt == 101);
bResult = bResult && (x.yChar == 'a');
return bResult;
}

/* ////////////////////////////////////////////////////////////////////////// */
/******************************************************************************
 * $Log: TestTemplateNestingS.cpp,v $
 * Revision 1.1  2010/03/02 23:02:15  ddarko
 * Nested template classes
 *
 *****************************************************************************/

