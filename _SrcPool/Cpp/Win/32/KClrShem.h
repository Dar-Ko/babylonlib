/*$Workfile: KClrShem.h$: header file
  $Revision: 4$ $Date: 2005-04-26 11:28:29$
  $Author: Darko Kolakovic$

  Serialization of a color array
  Copyright: CommonSoft Inc
  July '98 Darko Kolakovic
 */

#ifndef  _KCLRSCHEM_H_
    //KClrShem.h sentry
  #define _KCLRSCHEM_H_ 

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#ifndef __AFXWIN_H__
  #include <AfxWin.h>         // MFC core and standard components
#endif

#ifndef __AFXTEMPL_H__
  #include <AfxTempl.h> //CArray template
#endif

/////////////////////////////////////////////////////////////////////////////
//CColorScheme gives a serialization and registry support to an array of
//colors. Following sections are created in the registry file:
//
//    HKEY_CURRENT_USER\Software\<AppName>\<Scheme>\.Default=<Colors>
//    HKEY_CURRENT_USER\Software\<AppName>\<Scheme>\.Current=<Scheme>
//
//Note: Microsoft Windows specific (Win) 
//      and uses Microsoft Foundation Library (MFC).
class CColorScheme : public CObject
{
// Construction
public:
  CColorScheme(int iSize = 0);
  CColorScheme(COLORREF* clrArray, const size_t nSize);

// Attributes
public:
  CArray <COLORREF,COLORREF> m_Color; //array with RGB colors
  static LPCTSTR DEFAULT;             //the name of the default registry section
  static LPCTSTR CURRENT;             //the name of the current registry section
// Operations
public:
  int GetSize() const;
  COLORREF& operator [](int iIndex );
  COLORREF  operator [](int iIndex ) const;
  CColorScheme& operator = (const CColorScheme& clrScheme);
  void SetSize(int nNewSize, int nGrowBy = -1);
  bool SetCurrentName(LPCTSTR szSection, LPCTSTR szName = NULL);
  void Copy(COLORREF* clrArray, const size_t nSize);

// Overrides
  virtual bool LoadSettings(LPCTSTR szSection,LPCTSTR szTypeKey = NULL); 
  virtual bool SaveSettings(LPCTSTR szSection,LPCTSTR szTypeKey = NULL); 

// Implementation
public:
  virtual ~CColorScheme();

};

// This makes ClassWizard very happy
//{{AFX_VIRTUAL(CColorScheme)
//}}AFX_VIRTUAL
//{{AFX_MSG(CColorScheme)
//}}AFX_MSG
//{{AFX_MSG_MAP(CColorScheme)
//}}AFX_MSG_MAP

///////////////////////////////////////////////////////////////////////////////
//Inlines

//::operator []()--------------------------------------------------------------
/*Sets or gets the color at the specified index.
 */
inline COLORREF  CColorScheme::operator[](int iIndex) const
{
return m_Color.GetAt(iIndex);
}
inline COLORREF& CColorScheme::operator[](int iIndex)
{
return m_Color.ElementAt(iIndex);
}

//::SetSize()------------------------------------------------------------------
/*Establishes the size of an empty or existing array; allocates memory if necessary. 
  If the new size is smaller than the old size, then the array is truncated and 
  all unused memory is released. Throws CMemoryException.
 */
inline void CColorScheme::SetSize(int nNewSize, //[in] the new array size (number of 
                                                //elements). Must be greater than
                                                //or equal to 0.
                                  int nGrowBy   //[in]= –1 The minimum number of element
                                                //slots to allocate if a size increase
                                                //is necessary
                                  )
{
m_Color.SetSize(nNewSize,nGrowBy);
}

//::GetSize()------------------------------------------------------------------
/*Returns the size of the array. Since indexes are zero-based, the size is 1 
  greater than the largest index.
 */
inline int CColorScheme::GetSize() const
{
return (int)m_Color.GetSize();
}

///////////////////////////////////////////////////////////////////////////////
// Helpers

//operator<<()-----------------------------------------------------------------
/*Inserts color scheme array to a CString object.
  First item is number of elements in the colore array. 

  Returns: a CString reference. Using the return value, you can write
  multiple insertions on a single line of source code.

  Note: Microsoft Windows specific (Win) 
        and uses Microsoft Foundation Library (MFC).
 */
inline CString& AFXAPI operator<<(CString& strDestination, //[out] string object
                                  CColorScheme& cclrsSource//[in] color array
                                  )
{
TCHAR szTemp[48];
const int& iCount = cclrsSource.GetSize();
strDestination += _ltot(iCount,szTemp,10);
int i = 0;
while(i < iCount)
  {
  strDestination += _T(',');
  strDestination += _itot(cclrsSource[i],szTemp,10);
  i++;
  }

return strDestination;
}

#ifdef _DEBUG
//operator<<()-----------------------------------------------------------------
/*Outputs the CColorScheme object to the dump context.

  Returns: a CDumpContext reference. Using the return value, you can write
  multiple insertions on a single line of source code.

  Note: Microsoft Windows specific (Win) 
        and uses Microsoft Foundation Library (MFC).
*/
inline CDumpContext& AFXAPI operator<<(CDumpContext& dc, //[out] dump context
                                       const CColorScheme& cclrsSource //[in] color array
                                       )
{
dc << _T("CColorScheme @") << (void*)&cclrsSource << _T("\n");
int i = 0;
while (i < cclrsSource.GetSize())
  {
  COLORREF clrTmp = cclrsSource[i];
  dc << i <<  _T(".\t") << &clrTmp << _T("\n");
  i++;
  }
return dc;
}
#endif //_DEBUG
///////////////////////////////////////////////////////////////////////////////
#endif //_KCLRSCHEM_H_
/*****************************************************************************
 * $Log: 
 *  4    Biblioteka1.3         2005-04-26 11:28:29  Darko Kolakovic Document groups
 *       and typo fixes
 *  3    Biblioteka1.2         2003-09-04 15:51:28  Darko           Assigment
 *       operators added
 *  2    Biblioteka1.1         2003-09-03 23:35:57  Darko           Prepared for
 *       VC++ v7.1
 *  1    Biblioteka1.0         2003-09-03 20:10:02  Darko           
 * $
 *****************************************************************************/
