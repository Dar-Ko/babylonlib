/*$RCSfile: TestTemplateNesting.cpp,v $: implementation file
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
// Nested template classes
//
template <class T>
class X
{
private:
  //Nested template class
  template <class U>
  class TNested
    {
      U m_uObj; //an object

    public:
      TNested();
      ~TNested();
      U&   Value();
      void Out();
    };

public:
  X(T t)
    {
    m_intTNested.Value() = t;
    }
  void Out()
    {
    m_intTNested.Out();
    }
  int GetValue()
    {
    return (int)m_intTNested.Value();
    }

protected:
  TNested<int> m_intTNested; //an integer object

};

//=============================================================================
/*When nested class templates are defined outside of their enclosing class,
  they must be prefaced by the template parameters for both the class template
  (if they are members of a class template) and template parameters for
  the member template.
  Local classes are not allowed to have member templates.
 */

template <class T>
template <class U>
X<T>::TNested<U>::TNested()
{
TRACE(_T("X<T>::TNested<U>::TNested()\n"));
m_uObj = (U)0xFFFF;
}

template <class T>
template <class U>
U& X<T>::TNested<U>::Value()
{
return m_uObj;
}

template <class T>
template <class U>
void X<T>::TNested<U>::Out()
{
TRACE1(_T("X<T>::TNested<U>::Out() = %d.\n"), (int)this->Value());
}

template <class T>
template <class U>
X<T>::TNested<U>::~TNested()
{
TRACE(_T("X<T>::TNested<U>::~TNested()\n"));
}

/*---------------------------------------------------------------------------*/
/*Validates C++ compiler conformance on template classes nested inside of
  a template.

  Returns: true if test is successful; otherwise returns false.
 */
bool TestTemplateNesting()
{
bool bResult = false;
X<int> xInt(101);
xInt.Out();
bResult = (xInt.GetValue() == 101);

X<char> xChar('c');
xChar.Out();
bResult = bResult && (xInt.GetValue() == (int)'c');
return bResult;
}

/* ////////////////////////////////////////////////////////////////////////// */
/******************************************************************************
 * $Log: TestTemplateNesting.cpp,v $
 * Revision 1.1  2010/03/02 23:02:15  ddarko
 * Nested template classes
 *
 *****************************************************************************/

