/*$Workfile: KVerInfo.h$: header file
  $Revision: 1.1 $ $Date: 2002/09/06 22:22:42 $
  $Author: ddarko $
  
  Obtains version information about a specified module
  Copyright: CommonSoft Inc
  May 97 Darko Kolakovic
  Jan 2k MSVC++ 6 revision D.K.
 */

#ifndef __KVERINFO_H__
  //KVerInfo.h sentry
  #define __KVERINFO_H__

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#ifndef __AFX_H__
  #include <AfxWin.h>
#endif

#ifdef _DEBUG
  CDumpContext& AFXAPI operator << (CDumpContext& dc, VS_FIXEDFILEINFO const& vffiSrc);
#endif

///////////////////////////////////////////////////////////////////////////////
//CVersionInfo class encapsulates VERSIONINFO structure and Obtains version
//information about a specified file or current module. Reading the VERSIONINFO
//resource works only with Win32 file images. It does not work with 16-bit
//Windows file images.
//The Win32 API contains the following predefined version information strings:
//
//    CompanyName
//    FileDescription
//    FileVersion
//    InternalName
//    LegalCopyright
//    OriginalFilename
//    ProductName
//    ProductVersion
//
//Note: The version information functions work only with Win32 file images.
//      They do not work with 16-bit Windows file images.
//      Microsoft Windows specific (Win) and uses Microsoft Fundation Library (MFC).
class CVersionInfo : public CObject
{
// Construction
public:
	CVersionInfo(HINSTANCE hInstance = NULL);
  CVersionInfo(LPCTSTR szFullPath);
private:
    //Don't allow this object to be copied.
  CVersionInfo (const CVersionInfo &);
  CVersionInfo & operator =(const CVersionInfo &);

// Attributes
public:
    //Translation Table
  struct LANGCHARSET
    {
    WORD wLanguage;//language identifier
    WORD wCharSet; //character-set identifier
    operator DWORD() const
      {return MAKELONG(wLanguage,wCharSet);}
    };
protected:
    //The translation table in the variable information structure.
  LANGCHARSET*  m_lpTranslationTable;
  UINT    m_nTranslationTableSize; //Size of the translation table
  LPVOID  m_lpData;  //Pointer to buffer to receive file-version info.
private:
  LPCTSTR m_StringFileInfo; //Specifies a value in a language-specific structure
// Operations
public:
  BOOL IsVersionInfo();
  UINT GetTranslationTableSize() const;
  BOOL SetVersionInfo    (LPCTSTR szFullPath);
  BOOL GetProductName    (LPTSTR& strProductName, UINT nTransTableIndex = 0);
  BOOL GetProductVersion (LPTSTR& strProductVersion, UINT nTransTableIndex = 0);
  BOOL GetCopyright      (LPTSTR& strCopyright, UINT nTransTableIndex = 0);
  BOOL GetInternalName   (LPTSTR& strInternalName, UINT nTransTableIndex = 0);
  BOOL GetDebug          (LPTSTR& strDebug, UINT nTransTableIndex = 0);
  BOOL GetCompanyName    (LPTSTR& strCompanyName, UINT nTransTableIndex = 0);
  BOOL GetFileDescription(LPTSTR& strFileDescription, UINT nTransTableIndex = 0);
  BOOL GetFileVersion    (LPTSTR& strFileVersion, UINT nTransTableIndex = 0);
  BOOL GetProductName    (CString& strProductName, UINT nTransTableIndex = 0);
  BOOL GetProductVersion (CString& strProductVersion, UINT nTransTableIndex = 0);
  BOOL GetCopyright      (CString& strCopyright, UINT nTransTableIndex = 0);
  BOOL GetInternalName   (CString& strInternalName, UINT nTransTableIndex = 0);
  BOOL GetDebug          (CString& strDebug, UINT nTransTableIndex = 0);
  BOOL GetLanguage       (CString& strLanguage, UINT nTransTableIndex = 0);
  BOOL GetCompanyName    (CString& strCompanyName, UINT nTransTableIndex = 0);
  BOOL GetFileDescription(CString& strFileDescription, UINT nTransTableIndex = 0);
  BOOL GetFileVersion    (CString& strFileVersion, UINT nTransTableIndex = 0);
  int GetCharacterSet(UINT nTransTableIndex = 0);
  int GetLanguageCode(UINT nTransTableIndex = 0);
  BOOL GetFixedFileInfo(VS_FIXEDFILEINFO& vsffiData);
  #ifdef __KWINVERS_H__ //To obtain information about OS include
                        //KWinVers.h header file
    BOOL GetWindowsVersion (CString& strWinVersion);
  #endif //__KWINVERS_H__

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVersionInfo)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CVersionInfo();

	// Generated message map functions
protected:
	//{{AFX_MSG(CVersionInfo)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
};

///////////////////////////////////////////////////////////////////////////////
// Inlines


//::IsVersionInfo()------------------------------------------------------------
/*Returns TRUE if version information is available
 */
inline BOOL CVersionInfo::IsVersionInfo()
{
return (m_lpData != NULL);
}

//::GetTranslationTableSize()--------------------------------------------------
/*Returns number of entries in Translation Table.
 */
inline UINT CVersionInfo::GetTranslationTableSize() const
{
return m_nTranslationTableSize;
}

/////////////////////////////////////////////////////////////////////////////
#endif //__KVERINFO_H__
/*****************************************************************************
 * $Log: 
 *  5    Biblioteka1.4         1/24/02 6:22:29 PM   Darko           Updated
 *       comments
 *  4    Biblioteka1.3         8/19/01 10:56:07 PM  Darko           Butyfier
 *  3    Biblioteka1.2         7/11/01 9:53:23 PM   Darko           
 *  2    Biblioteka1.1         6/8/01 10:52:22 PM   Darko           VSS
 *  1    Biblioteka1.0         8/13/00 3:03:19 PM   Darko           
 * $
 *****************************************************************************/
