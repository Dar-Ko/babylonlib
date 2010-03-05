/*$RCSfile: TestTemplateSpecialization.cpp,v $: implementation file
  $Revision: 1.3 $ $Date: 2010/03/05 22:31:41 $
  $Author: ddarko $

  Test C++ compiler conformance to partial specialization of templates.
  Copyright: Blitz++, www.oonumerics.org/blitz/
  2010-02-26 Darko Kolakovic
*/

/* Group=Examples                                                            */

#ifdef _USE_ATL
  #include <iostream>
  //Active Template Libaray (ATL)
  #include <atlbase.h>
  #include "KTraceAtl.h"
#endif

#include "TestConformance.h"
#ifndef _T
  #include "KTChar.h"
#endif
#ifndef LOG_EOT
  #include "KTestLog.h"
#endif

extern bool TsWriteToViewLn(LPCTSTR lszText);

#ifndef HAS_NO_TEMPLATE_INSIDE_TEMPLATE_SUPPORT
///////////////////////////////////////////////////////////////////////////////
/*Explicit templates specialization

  17. A member or a member template may be nested within many enclosing class
  templates. If the declaration of an explicit specialization for such a member
  appears in namespace scope, the member declaration shall be preceded by
  a template<> for each enclosing class template that is explicitly specialized.

  18. In an explicit specialization declaration for a member of a class template
  or a member template that appears in namespace scope, the member template and
  some of its enclosing class templates may remain unspecialized, except that
  the declaration shall not explicitly specialize a class member template if
  its enclosing class templates are not explicitly specialized as well.
  In such explicit specialization declaration, the keyword template followed by 
  a template-parameter-list shall be provided instead of the template<>
  preceding the explicit specialization declaration of the member.
  The types of the template-parameters in the template-parameter-list shall be 
  the same as those specified in the primary template definition. 

  Specialization of inner class without specialization of its enclosing class 
  is prohibited in any case.

  Example:
      template <class T>
      class X
        {
        template <class U>
        class TNested
          {
          void Out();
          };
        };

      template<class T> 
      template<>
      void X<T>::TNested<double>::Out()
      { } //Generates an compiler error

  See also: C++ Standard 14. Templates: 14.7.3 Explicit specialization
*/
#if 0  ///!!!!!!!!!!!!!!!
template<class T> 
class A 
{
private:
  //Nested template class
  template<class U>
  class TNested
    {
      U m_uObj; //an object

    public:
      TNested();
      ~TNested();
      U& Value()
        {
        return m_uObj;
        }
      //Member function template
      template<class V> void Out(V value);
    };
public:
  A(T t)
    {
    m_oTNested.Value() = t;
    }
  void Out()
    {
    m_oTNested.Out(m_oTNested.Value());
    }
  T GetValue()
    {
    return (T)m_oTNested.Value();
    }
protected:
  TNested<T> m_oTNested; //an object
};

//=============================================================================
template<class T> 
template<class U>
A<T>::TNested<U>::TNested()
{
TRACE(_T("A<T>::TNested<U>::TNested()\n"));
m_uObj = (U)0xFFFF;
};

template <class T>
template <class U>
A<T>::TNested<U>::~TNested()
{
TRACE(_T("A<T>::TNested<U>::~TNested()\n"));
}

/*Specialization of outer class is allowed
 */
template<> 
template<class U>
class A<int>::TNested
  {
  };

template<> 
template<class U>
template <class V>
A<int>::TNested<U>::TNested() //:
//  m_uObj(10101)
{
TRACE(_T("A<int>::TNested<U>::TNested()\n"));
}

//-----------------------------------------------------------------------------
/*Generic memeber function
 */
template <class T>
template <class U>
template <class V>
void A<T>::TNested<U>::Out(V value)
{
TRACE1(_T("A<T>::TNested<U>::Out(V) = %d.\n"), (int)value);
}

/*Specialization of enclosing classes are allowed
 */
template<> 
template<> 
template<class V>
void A<int>::TNested<double>::Out(V value)
{
TRACE1(_T("A<int>::TNested<double>::Out(V) = %E.\n"), m_uObj * value);
}
#else ///!!!!!!!!!!!!!!!
//0000000000000000000000000000000000000
template<class T> 
class A 
{
public:
  template<class U> 
  class TNested
  {
  public:
    template<class V> void Out(U,V);
    void Value(U);
  };
};
 
template<class T> 
template<class U> 
template<class V>
void A<T>::TNested<U>::Out(U, V) 
{
TRACE(_T("A<T>::TNested<U>::Out(U, V)\n")); 
}
 
template<class T> 
template<class U>
void A<T>::TNested<U>::Value(U) 
{ 
TRACE(_T("A<T>::TNested<U>::Value(U)\n")); 
}
 
template<> 
template<>
void A<int>::TNested<int>::Value(int) 
{ 
TRACE(_T("A<int>::TNested<int>::Value(int)\n"));
}
 
template<> 
template<> 
template<class V>
void A<int>::TNested<int>::Out(int, V) 
{ 
TRACE(_T("A<int>::TNested<int>::Out(int, V)\n")); 
}

template<> 
template<> 
template<class V>
void A<char>::TNested<double>::Out(double, V) 
{ 
TRACE(_T("A<char>::TNested<double>::Out(double, V)\n")); 
}

template<> 
template<> 
template<>
void A<int>::TNested<int>::Out<int>(int, int) 
{
TRACE(_T("A<int>::TNested<int>::Out<int>(int, int)\n")); 
}


#endif ///!!!!!!!!!!!!!!!
#endif //HAS_NO_TEMPLATE_INSIDE_TEMPLATE_SUPPORT

///////////////////////////////////////////////////////////////////////////////
/*Partial Template Specialization
  If a class template has more than one template parameter, you can specialize
  the class template for one or a set of particular parameterized values or types.
  That is, you might want to provide a template that matches a general template
  except that some of the template parameters have been replaced by actual types
  or values.
  The definition of a partial specialization is completely disjointed from
  the definition of the general template. The partial specialization may have
  a completely different set of members from the generic class template.
  A class template partial specialization must have its own definitions for its
  member functions, static data members, and nested types, the same as for
  a class template specialization. The generic definitions for the members of
  a class template are never used to instantiate the members of the class
  template partial specialization.

  No partial specialization for member functions of class templates is allowed.

  See also: {html: <a href="http://msdn.microsoft.com/en-us/magazine/cc163754.aspx"
  Generic Programming: Template Specialization by Stanley B. Lippman</a>}
 */
template<class TYPE, int NUMBER>
class TPartialSpecialization
{
public:
  enum bar { z = 0 };
};

#ifndef HAS_NO_TEMPLATE_PARTIAL_SPECIALIZATION
//==============================================================================
/*Partial specialization of TYPE argument
 */
template<int NUMBER>
class TPartialSpecialization<double, NUMBER>
{
public:
  enum bar { z = 1 };
};

/*Partial specialization of NUMBER argument
 */
template<class TYPE>
class TPartialSpecialization<TYPE, 2>
{
public:
  enum bar { z = 2 };
};

#endif //HAS_NO_TEMPLATE_PARTIAL_SPECIALIZATION

/*---------------------------------------------------------------------------*/
/*Validates C++ compiler conformance. Compiler will report an error
  "overloaded function differs only by return type" if could not distinguish
   between coercion operators.

  Returns: true if test is successful; otherwise returns false.
 */
bool TestTemplateSpecialization()
{
bool bResult = false;
#ifndef HAS_NO_TEMPLATE_INSIDE_TEMPLATE_SUPPORT
  A<int>::TNested<int> a;
  A<char>::TNested<char> b;
  A<char>::TNested<double> c;

  a.Out(1, 2);    //Use specialization
  a.Out(3, 'x');  //Use specialized inner class
  a.Value(3);     //Use specialized member
  b.Out('x', 'y');//use generic class
  b.Value('z');    //Use generalized member
  c.Out('d', 3.14); //Use specialized inner class
  c.Out(2, 3);    //Use specialized inner class becouse of implict casting
  c.Value(2.78);  //Use generalized member

/*
  A<char> aChar('d'); //Use generic class
  aChar.Out();
  bResult = (aChar.GetValue() == (int)'c');

  A<int> aInt(202); //Use specialized class
  aInt.Out();
  bResult = bResult && (aInt.GetValue() == 101);
*/

#else //Embrdded templates are not supported
  TRACE(_T("HAS_NO_TEMPLATE_INSIDE_TEMPLATE_SUPPORT\n"));
  TsWriteToViewLn(_T("HAS_NO_TEMPLATE_INSIDE_TEMPLATE_SUPPORT\n"));
  bResult = true;
#endif //HAS_NO_TEMPLATE_INSIDE_TEMPLATE_SUPPORT

if (TPartialSpecialization<int, 3>::z == 0)
  {
  #ifndef HAS_NO_TEMPLATE_PARTIAL_SPECIALIZATION
    if( (TPartialSpecialization<double, 3>::z == 1)  &&
        (TPartialSpecialization<float,  2>::z == 2) )
      bResult = bResult && true;
  #else //Specialization is not supported
    TRACE(_T("HAS_NO_TEMPLATE_PARTIAL_SPECIALIZATION\n"));
    TsWriteToViewLn(_T("HAS_NO_TEMPLATE_PARTIAL_SPECIALIZATION\n"));
    return bResult = bResult && true;;
  #endif //HAS_NO_TEMPLATE_PARTIAL_SPECIALIZATION

  }
return bResult;
}

/* ////////////////////////////////////////////////////////////////////////// */
/******************************************************************************
 * $Log: TestTemplateSpecialization.cpp,v $
 * Revision 1.3  2010/03/05 22:31:41  ddarko
 * *** empty log message ***
 *
 * Revision 1.2  2010/03/05 15:31:28  ddarko
 * Adjusted test result
 *
 * Revision 1.1  2010/02/26 22:20:39  ddarko
 * Template Conformance Test; www.oonumerics.org/blitz/
 *
 *****************************************************************************/

/*define BZ_PARTIAL_SPECIALIZATION
 The "Blitz++ Artistic License"
 */