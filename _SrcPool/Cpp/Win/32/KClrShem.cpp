/*$Workfile: KClrShem.cpp$: implementation file
  $Revision: 4$ $Date: 2004-10-01 21:33:47$
  $Author: Darko$

  Implementation of the CColorScheme class
  Copyright: CommonSoft Inc.
  July '98 Darko Kolakovic
 */

#include "stdafx.h"
#include "KClrShem.h" //CColorScheme class

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorScheme

/*The name of the registry (profile) section with the default color scheme
 */
LPCTSTR CColorScheme::DEFAULT = _T(".Default");

/*The name of the registry (profile) section with the name of the current
  color scheme.
 */
LPCTSTR CColorScheme::CURRENT = _T(".Current");

//::CColorScheme()-------------------------------------------------------------
//warning C4290: C++ exception specification ignored except to indicate 
//a function is not __declspec(nothrow)
#pragma warning(disable: 4290)
/*Constructs a color array. The array grows one element at a time. 
  Throws CMemoryException.
 */
CColorScheme::CColorScheme(int iSize //[in] color array size (number of colors).
                                     //Default is 0.
                                     ) throw (CMemoryException)
{
if (iSize > 0)
  m_Color.SetSize(iSize);
}

/*Copies an array of colors to the this object.
  Throws CMemoryException.
 */
CColorScheme::CColorScheme(COLORREF* clrArray, //[in] array of colors
                           const size_t nSize   //[in] size of the array
                           ) throw (CMemoryException)
{
if (nSize > 0)
  {
  m_Color.SetSize(nSize);
  unsigned int i = 0;
  while (i < nSize)
    {
    m_Color[i] = clrArray[i];
    i++;
    }
  }
}

CColorScheme::~CColorScheme()
{
}

//-----------------------------------------------------------------------------
/*Assigns CColorScheme to the current object.
  Throws CMemoryException.

  Returns: reference to the current object.
 */
CColorScheme& CColorScheme::operator = (const CColorScheme& clrScheme
                                        ) throw (CMemoryException)
{
const unsigned int nSize = (unsigned int)clrScheme.GetSize();
m_Color.SetSize(nSize);
unsigned int i = 0;
while (i < nSize)
  {
  m_Color[i] = clrScheme[i];
  i++;
  }

return *this;
}

//-----------------------------------------------------------------------------
/*Copies an array of colors to the this object.
  Throws CMemoryException.
 */
void CColorScheme::Copy(COLORREF* clrArray, //[in] array of colors
                        const size_t nSize   //[in] size of the array
                        ) throw (CMemoryException)
{
m_Color.SetSize(nSize);
unsigned int i = 0;
while (i < nSize)
  {
  m_Color[i] = clrArray[i];
  i++;
  }
}
#pragma warning(default: 4290)

//LoadSettings()---------------------------------------------------------------
/*Retrieves the color scheme associated with the specified key in the given 
 section of the refistry (or profile) file.

  Example:
    #include "KColorCt.h" //color names
    #include "KClrShem.h" //CColorScheme class
    CMyView::OnInitialUpdate()
      {
      ...
      CColorScheme Color(3);
      Color[0] = RED;     //Default values
      Color[1] = GREEN;
      Color[2] = BLUE;
      if(!Color.LoadSettings(_T("ClrScheme"))) //Load current color scheme
        {
          //Save default color scheme
        Color.SaveSettings(_T("ClrScheme"),CColorScheme::DEFAULT);
        Color.SetCurrentName(_T("ClrScheme")); //Set ".Default" as a scheme
                                               //to be used
        } 
      ...
      }

*/
bool CColorScheme::LoadSettings(LPCTSTR szSection,//[in] address of section name 
                                LPCTSTR szTypeKey //[in]=NULL current scheme name 
                                                  //if NULL, functions loads scheme 
                                                  //under CURRENT section, and if this
                                                  //fails DEFAULT scheme is loaded
                                 
                                )
{
if (szSection == NULL)
  return false;
CString strValue;
if ((szTypeKey != NULL) && (szTypeKey[0] != _T('\0')))
  {
  strValue = AfxGetApp()->GetProfileString(szSection,szTypeKey);
  TRACE2("CColorScheme::LoadSettings( %s,%s )\n",szSection,szTypeKey);
  }

if (strValue.IsEmpty())
  {
  CString strCurrentScheme;
  TRACE2("CColorScheme::LoadSettings( %s,%s )\n",szSection,CColorScheme::CURRENT);
  strCurrentScheme = AfxGetApp()->GetProfileString(szSection,CColorScheme::CURRENT);
  if (strCurrentScheme.IsEmpty())  //Load default color scheme
    {
    strValue = AfxGetApp()->GetProfileString(szSection,CColorScheme::DEFAULT);
    if (strValue.IsEmpty())
      return false;
    }
  else  //Load current color scheme array
    {
    strValue = AfxGetApp()->GetProfileString(szSection,strCurrentScheme);
    if (strValue.IsEmpty()) //Load default color scheme
      {
      strValue = AfxGetApp()->GetProfileString(szSection,CColorScheme::DEFAULT);
      if (strValue.IsEmpty())
        return false;
      }
    }
  }

CString strToken;
int iPos = strValue.Find(_T(','));
strToken = strValue.Left(iPos);
strValue = strValue.Mid(iPos + 1);
int iCount = _ttol(strToken);
SetSize(iCount);
int i = 0;
while (i < iCount)
  {
  iPos = strValue.Find(_T(','));
  if (iPos != -1)
    {
    strToken = strValue.Left(iPos);
    strValue = strValue.Mid(iPos + 1);
    }
  else
    strToken = strValue;
  iPos = _ttol(strToken);
  m_Color[i] = iPos;
  i++;
  }

#ifdef _DEBUG
  if (afxDump.GetDepth() > 0)
    afxDump << *this;
#endif

return true;
}

//SaveSettings()---------------------------------------------------------------
/*Copies a color scheme into the specified section of the registry
  (or profile) file as a string.

  Returns: true if successful; otherwise returns false;

  TODO: replace WriteProfileString with WriteProfileBinary D.K. 
*/
bool CColorScheme::SaveSettings(LPCTSTR szSection,  //[in] the section name 
                                LPCTSTR szTypeKey   //[in]=NULL name of the color
                                //scheme; if it is NULL, sheme is stored
                                // as ".Default" scheme
                                )
{
ASSERT((szSection != NULL) && (szSection[0] != _T('\0')));
if( (szSection == NULL) || (szSection[0] == _T('\0')))
   return false;

LPTSTR szSchemeName;
if ((szTypeKey == NULL) || (szTypeKey[0] == _T('\0')))
  szSchemeName = const_cast<LPTSTR>(CColorScheme::DEFAULT);
else
  szSchemeName = const_cast<LPTSTR>(szTypeKey);

TRACE2("CColorScheme::SaveSettings( %s,%s )\n",szSection,szSchemeName);
CString strValue;
strValue << *this;

if(!AfxGetApp()->WriteProfileString(szSection,szSchemeName,(LPCTSTR)strValue))
  {
  TRACE1("\t saving registry \"%s\" failed.\n",szSection);
  return false;
  }

return true;
}

//::SetCurrentName()-----------------------------------------------------------
/*Enables given color scheme name as the currently active scheme.
  Following sections are used in the registry file:

    HKEY_CURRENT_USER\Software\<AppName>\<szSection>\.Default=<Colors>
    HKEY_CURRENT_USER\Software\<AppName>\<szSection>\<szName>=<Colors>
    HKEY_CURRENT_USER\Software\<AppName>\<szSection>\.Current=<szName>

  Note: to store values in registry use SaveSettings().

  Returns: true if successful; otherwise returns false;

  Example:
        CColorScheme Color(clrArray, 3);
          //Save default color scheme
        Color.SaveSettings(_T("ClrScheme"), _T("MyScheme"));
          //Set "MyScheme" as a scheme to be used
        Color.SetCurrentName(_T("ClrScheme"), _T("MyScheme"));
        ...
        Color.LoadSettings(_T("ClrScheme")); //Load "MyScheme" colors

  See also: SaveSettings(), LoadSettings()
 */
bool CColorScheme::SetCurrentName(LPCTSTR szSection, //[in] the section name
                                  LPCTSTR szName //[in]= NULL, color scheme name,
                                                 //if NULL, the DEFAULT name is stored
                                                 //as current color scheme name
                                  )
{
if(szSection == NULL)
  {
  TRACE0("CColorScheme::SetCurrentName() szSection is NULL!\n");
  return false;
  }
LPTSTR szSchemeName;
if ((szName == NULL) || (szName[0] == _T('\0')))
  szSchemeName = const_cast<LPTSTR>(CColorScheme::DEFAULT);
else
  szSchemeName = const_cast<LPTSTR>(szName);

if(!AfxGetApp()->WriteProfileString(szSection,CColorScheme::CURRENT,szSchemeName))
  {
  TRACE1("\t saving registry \"%s\" failed.\n",szSection);
  return false;
  }

return true;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  4    Biblioteka1.3         2004-10-01 21:33:47  Darko           stdafx.h
 *  3    Biblioteka1.2         2003-09-04 14:51:25  Darko           Assigment
 *       operators added
 *  2    Biblioteka1.1         2003-09-03 22:35:55  Darko           Prepared for
 *       VC++ v7.1
 *  1    Biblioteka1.0         2003-09-03 19:10:00  Darko           
 * $
 *****************************************************************************/
