/*$Workfile: KVerInfo.cpp$: implementation file
  $Revision: 1.3 $ $Date: 2003/01/28 05:39:56 $
  $Author: ddarko $

  Obtains version information about a specified module.
  Copyright: CommonSoft Inc.
  May 97 Darko Kolakovic
  Jan 2k MSVC++ 6 revision D.K.
 (/ 

#include "KVerInfo.h" //CVersionInfo class

#pragma comment(lib, "Version")

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

//This makes ClassWizard happy
	//{{AFX_MSG_MAP(CVersionInfo)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP

/////////////////////////////////////////////////////////////////////////////
// CVersionInfo
//::CVersionInfo()-------------------------------------------------------------
/*Obtains version information about a module (exe or dll) with given instance
  handle. If handle is NULL, the version information for the current application
  is retrieved.

  Note:  Member m_StringFileInfo specifies a value in a language-specific structure.
  The lang-charset name is a concatenation of a language and character-set
  identifier pair found in the translation table for the resource.
  The lang-charset name must be specified as a hexadecimal string.
  */
CVersionInfo::CVersionInfo(HINSTANCE hInstance 	//handle to module to find VERSIONINFO for
                           ) :
        m_lpData(NULL),
        m_StringFileInfo(_TEXT("\\StringFileInfo\\%04lx%04lx\\%s")),
        m_nTranslationTableSize(0)
{
if (hInstance == NULL)
  hInstance = AfxGetInstanceHandle(); //Retrieve the instance handle of the current application
	//Get path of executable
TCHAR szAppName[_MAX_PATH];
VERIFY(::GetModuleFileName(hInstance, szAppName, _MAX_PATH));
  //Get version information about a current application
VERIFY(SetVersionInfo(szAppName));
}

/*Obtains version information about a specified file.
 */
CVersionInfo::CVersionInfo(LPCTSTR szFullPath //full path to module to find VERSIONINFO for
                           ) :
        m_lpData(NULL),
        m_StringFileInfo(_TEXT("\\StringFileInfo\\%04lx%04lx\\%s")),
        m_nTranslationTableSize(0)
{
if ( szFullPath != NULL )
  VERIFY(SetVersionInfo(szFullPath));
else
  {
  	//Get path of executable
  TCHAR szAppName[_MAX_PATH];
  VERIFY(::GetModuleFileName(AfxGetInstanceHandle(), szAppName, _MAX_PATH));
    //Get version information about a current application
  VERIFY(SetVersionInfo(szAppName));
  }
}


CVersionInfo::~CVersionInfo ()
{
if (m_lpData)
  delete[] (char*)m_lpData;
}

//::SetVersionInfo()-----------------------------------------------------------
void SystemErrMessage(UINT uiSystemError);
/*Obtains version information about specified file and initializes member
  m_lpData

  Note: Windows 95/98: The short path form of the specified file name must
        be less than 126 characters.
 */
BOOL CVersionInfo::SetVersionInfo(LPCTSTR szPath //module path
                                 )
{
if(szPath == NULL)
  return FALSE;

DWORD  dwHandle;
  //Size of requested information block
DWORD dwSize = ::GetFileVersionInfoSize((LPTSTR)szPath,&dwHandle);

if (dwSize)
  {
  if ( m_lpData != NULL )
    delete[] (char*)m_lpData;

  m_lpData  = (LPVOID)new char[(UINT)dwSize];  //Allocate buffer
  if (::GetFileVersionInfo((LPTSTR)szPath,
                          dwHandle, dwSize, m_lpData))
    {
    //Retrieve a pointer to an array of language and
    //character-set identifiers
    UINT nSize;
    if (!::VerQueryValue(m_lpData,
                "\\VarFileInfo\\Translation",
                (LPVOID  *)&m_lpTranslationTable,
                &nSize))
      {
      delete[] (char*)m_lpData;    //Error
      m_lpData = NULL;
      }
    else
      {
        //Get number of elements in the Translation Table
      m_nTranslationTableSize = nSize/sizeof(LANGCHARSET);
      #ifdef _DEBUG
        TRACE0("CVersionInfo::SetVersionInfo() Obtained ");
       if (nSize > sizeof(LANGCHARSET))
         TRACE1("%d different language identifiers\n",
                  nSize/sizeof(LANGCHARSET));
        else
          TRACE0("1 language identifier\n");
      #endif
      }
    }
  }
else
  {
  TRACE1("CVersionInfo::SetVersionInfo( %s ) failed!\n",szPath);
  SystemErrMessage(GetLastError());
  return FALSE;
  }

return TRUE;
}

//::GetProductName()-----------------------------------------------------------
/*If successful returns TRUE and Product Name entry, otherwise returns FALSE.
 */
BOOL CVersionInfo::GetProductName(LPTSTR &strProductName, //resulting string
                                  UINT nTransTableIndex //=0 index of Translation Table entry
                                 )
{
UINT nSize;
char subBlockName[255];
ASSERT (nTransTableIndex < m_nTranslationTableSize);

if (!IsVersionInfo())
  return FALSE;

wsprintf(subBlockName, m_StringFileInfo,
         m_lpTranslationTable[nTransTableIndex].wLanguage,
         m_lpTranslationTable[nTransTableIndex].wCharSet,
         (LPTSTR)"ProductName");

return ::VerQueryValue(m_lpData,
                       TEXT(subBlockName),
                       (LPVOID*)&strProductName,
                       &nSize);
}

BOOL CVersionInfo::GetProductName(CString& strProductName, //resulting string
                                  UINT nTransTableIndex //=0 index of Translation Table entry
                                 )
{
LPTSTR lpProductName;
if (!GetProductName(lpProductName,nTransTableIndex))
  return FALSE;
strProductName = lpProductName; //Copy requested information

return TRUE;
}

//::GetProductVersion()--------------------------------------------------------
/*If successful returns TRUE and Product Version entry, otherwise returns FALSE.

  Example:
    #include "KVerInfo.h" //CVersionInfo class
    int ShowVersion(HWND hParent)
      {
      CString strTemp;
      CString strDescription;
      strDescription = _T("C:\Windows\MSVCRT.dll");

      CVersionInfo DllVersion(strDescription);
      strDescription += _T(" v.");
      DllVersion.GetProductVersion(strTemp);
      strDescription += strTemp;
      strDescription += _T("\n");
      DllVersion.GetFileDescription(strTemp);
      strDescription += strTemp;

      return ::MessageBox(hParent,
                          strDescription,
                          _T("DLL Version"),
                          MB_OK|MB_ICONEXCLAMATION);
      }

 */
BOOL CVersionInfo::GetProductVersion(LPTSTR &strProductVersion, //resulting string
                                     UINT nTransTableIndex //=0 index of Translation Table entry
                                    )
{
UINT nSize;
char subBlockName[255];
ASSERT (nTransTableIndex < m_nTranslationTableSize);

if (!IsVersionInfo())
  return FALSE;

#ifdef _DEBUG
  CString strLan;
  VERIFY(GetLanguage(strLan));
  TRACE1("CVersionInfo::GetProductVersion() Language %s\n",strLan);
#endif

wsprintf(subBlockName, m_StringFileInfo,
         m_lpTranslationTable[nTransTableIndex].wLanguage,
         m_lpTranslationTable[nTransTableIndex].wCharSet,
         (LPTSTR)"ProductVersion");
return ::VerQueryValue(m_lpData,
                       subBlockName,
                       (LPVOID*)&strProductVersion,
                       &nSize);
}

BOOL CVersionInfo::GetProductVersion(CString& strProductVersion, //resulting string
                                     UINT nTransTableIndex //=0 index of Translation Table entry
                                    )
{
LPTSTR lpProductVersion;
if (!GetProductVersion(lpProductVersion,nTransTableIndex))
  return FALSE;
strProductVersion = lpProductVersion; //Copy requested information
return TRUE;
}

//::GetCopyright()-------------------------------------------------------------
/*If successful returns TRUE and Copyright entry, otherwise returns FALSE.
 */
BOOL CVersionInfo::GetCopyright(LPTSTR &strCopyright, //resulting string
                                UINT nTransTableIndex //=0 index of Translation Table entry
                               )
{
UINT nSize;
char subBlockName[255];
ASSERT (nTransTableIndex < m_nTranslationTableSize);

if (!IsVersionInfo())
  return FALSE;

wsprintf(subBlockName, m_StringFileInfo,
         m_lpTranslationTable[nTransTableIndex].wLanguage,
         m_lpTranslationTable[nTransTableIndex].wCharSet,
         (LPTSTR)"LegalCopyright");
return ::VerQueryValue(m_lpData,
                       subBlockName,
                       (LPVOID*)&strCopyright,
                       &nSize);
}

BOOL CVersionInfo::GetCopyright(CString& strCopyright, //resulting string
                                UINT nTransTableIndex //=0 index of Translation Table entry
                               )
{
LPTSTR lpCopyright;
if (!GetCopyright(lpCopyright,nTransTableIndex))
  return FALSE;
strCopyright = lpCopyright; //Copy requested information
return TRUE;
}

//::GetInternalName()----------------------------------------------------------
/*If successful returns TRUE and Internal Name entry, otherwise returns FALSE.
 */
BOOL CVersionInfo::GetInternalName(LPTSTR &strInternalName, //resulting string
                                   UINT nTransTableIndex //=0 index of Translation Table entry
                                  )
{
UINT nSize;
char subBlockName[255];
ASSERT (nTransTableIndex < m_nTranslationTableSize);

if (!IsVersionInfo())
  return FALSE;

wsprintf(subBlockName, m_StringFileInfo,
         m_lpTranslationTable[nTransTableIndex].wLanguage,
         m_lpTranslationTable[nTransTableIndex].wCharSet,
         (LPTSTR)"InternalName");
return ::VerQueryValue(m_lpData,
                       subBlockName,
                       (LPVOID*)&strInternalName,
                       &nSize);
}

BOOL CVersionInfo::GetInternalName(CString& strInternalName, //resulting string
                                   UINT nTransTableIndex //=0 index of Translation Table entry
                                  )
{
LPTSTR lpInternalName;
if (!GetInternalName(lpInternalName,nTransTableIndex))
  return FALSE;
strInternalName = lpInternalName; //Copy requested information
return TRUE;
}

//::GetDebug()-----------------------------------------------------------------
/*If successful returns TRUE and Product Version entry, otherwise returns FALSE.
 */
BOOL CVersionInfo::GetDebug(LPTSTR &strDebug, //resulting string
                            UINT nTransTableIndex //=0 index of Translation Table entry
                           )
{
UINT nSize = 255;
char subBlockName[255];
ASSERT (nTransTableIndex < m_nTranslationTableSize);

if (!IsVersionInfo())
  return FALSE;

wsprintf(subBlockName, m_StringFileInfo,
         m_lpTranslationTable[nTransTableIndex].wLanguage,
         m_lpTranslationTable[nTransTableIndex].wCharSet,
         (LPTSTR)"SpecialBuild");
return ::VerQueryValue(m_lpData,
                       subBlockName,
                       (void FAR* FAR*)&strDebug,
                       &nSize);
}

BOOL CVersionInfo::GetDebug(CString& strDebug, //resulting string
                            UINT nTransTableIndex //=0 index of Translation Table entry
                           )
{
LPTSTR lpDebug;
if (!GetDebug(lpDebug,nTransTableIndex))
  return FALSE;
strDebug = lpDebug; //Copy requested information
return TRUE;
}

//::GetLanguage()--------------------------------------------------------------
/*Returns TRUE and formatted string with language information,
  otherwise returns FALSE.

  Note: Any previous content of the strLanguage string will be destroyed
 */
BOOL CVersionInfo::GetLanguage(CString& strLanguage, //resulting string
                               UINT nTransTableIndex //=0 index of Translation Table entry
                               )
{
TRACE1("CVersionInfo::GetLanguage(%d)\n",nTransTableIndex);
if (nTransTableIndex < m_nTranslationTableSize)
  {
  const int MINBUFFLENGHT  = 64;
  LPTSTR  szLang = strLanguage.GetBuffer(MINBUFFLENGHT);
  //Note: VerLanguageName() is not supported under Win32s
  if (VerLanguageName((DWORD)m_lpTranslationTable[nTransTableIndex],	//Microsoft language identifier
                      szLang,             //address of buffer for language string
                     (DWORD)MINBUFFLENGHT //size of buffer
                                          ) > 0)
    {
    strLanguage.ReleaseBuffer();  //Surplus memory released
    return TRUE;
    }

  strLanguage.ReleaseBuffer();   //Surplus memory released
  }
return FALSE;
}

//::GetCharacterSet()----------------------------------------------------------
/*If successful returns character-set identifier, otherwise returns -1.
  The character-set identifier is one of the following:

     Identifier  Character Set
      0000;000   7-bit ASCII
      0932;3A4   Japan (Shift – JIS X-0208)
      0949;3B5   Korea (Shift – KSC 5601)
      0950;3B6   Taiwan (Big5)
      1200,4B0   Unicode
      1250;4E2   Latin-2 (Eastern European)
      1251;4E3   Cyrillic
      1252;4E4   Multilingual
      1253;4E5   Greek
      1254;4E6   Turkish
      1255;4E7   Hebrew
      1256;4E8   Arabic

  Example:
      //Get version information of the current application
    CVersionInfo ExeVersion;
    CString strTemp;
      //Enumerate languages
    UINT i = 0;
    while (i < ExeVersion.GetTranslationTableSize())
      {
      ExeVersion.GetLanguage(strTemp, i);
      TRACE1(_T("\t%s"),(LPCTSTR)strTemp);
        //Get character set for the neutral language
      if (ExeVersion.GetLanguageCode(i) == 0x0000)
        {
        TRACE1(_T(" %d"),ExeVersion.GetCharacterSet(i));
        }
      TRACE0(_T("\n"));
      i ++;
      }

 */
int CVersionInfo::GetCharacterSet(UINT nTransTableIndex//=0 index of Translation Table entry
                                 )
{
if (IsVersionInfo())
  {
  ASSERT (nTransTableIndex < m_nTranslationTableSize);
  return m_lpTranslationTable[nTransTableIndex].wCharSet;
  }
return -1;
}

//::GetLanguageCode()----------------------------------------------------------
/*If successful returns language code identifier, otherwise returns -1.
  The language code identifier is one of the following:

    Identifier Language          Identifier Language           Identifier Language
      0x0000   Neutral             0x0436   Afrikaans            0x1004   Chinese (Singapore)
      0x0400   Process Default     0x0437   Georgian             0x1007   German (Luxembourg)
      0x0401   Arabic (Saudi)      0x0438   Faeroese             0x1009   English (Canada)
      0x0402   Bulgarian           0x0439   Hindi (India)        0x100a   Spanish (Guatemala)
      0x0403   Catalan (Spain)     0x043e   Malay (Malaysia)     0x100c   French (CH)
      0x0404   Chinese (Taiwan)    0x043f   Kazak (Kazakstan)    0x1401   Arabic (Algeria)
      0x0405   Czech               0x0441   Swahili (Kenya)      0x1404   Chinese (Macau)
      0x0406   Danish              0x0443   Uzbek (Latin)        0x1407   German (Liechtenstein)
      0x0407   German              0x0444   Tatar (Tatarstan)    0x1409   English (New Zealand)
      0x0408   Greek               0x0445   Bengali (India)      0x140a   Spanish (Costa Rica)
      0x0409   English (US)        0x0446   Punjabi (India)      0x140c   French (Luxembourg)
      0x040a   Spanish (Spain)     0x0447   Gujarati (India)     0x1801   Arabic (Morocco)
      0x040b   Finnish             0x0448   Oriya (India)        0x1809   English (Ireland)
      0x040c   French              0x0449   Tamil (India)        0x180a   Spanish (Panama)
      0x040d   Hebrew              0x044a   Telugu (India)       0x180c   French (Monaco)
      0x040e   Hungarian           0x044b   Kannada (India)      0x1c01   Arabic (Tunisia)
      0x040f   Icelandic           0x044c   Malayalam (India)    0x1c09   English (South Africa)
      0x0410   Italian (Italy)     0x044d   Assamese (India)     0x1c0a   Spanish (Dominican)
      0x0411   Japanese            0x044e   Marathi (India)      0x2001   Arabic (Oman)
      0x0412   Korean              0x044f   Sanskrit (India)     0x2009   English (Jamaica)
      0x0413   Dutch               0x0457   Konkani (India)      0x200a   Spanish (Venezuela)
      0x0414   Norwegian (Bokmål)  0x0800   Neutral              0x2401   Arabic (Yemen)
      0x0415   Polish              0x0801   Arabic (Iraq)        0x2409   English (Caribbean)
      0x0416   Portuguese (Brazil) 0x0804   Chinese (PRC)        0x240a   Spanish (Colombia)
      0x0418   Romanian            0x0807   German (CH)          0x2801   Arabic (Syria)
      0x0419   Russian             0x0809   English (UK)         0x2809   English (Belize)
      0x041a   Croatian            0x080a   Spanish (Mexico)     0x280a   Spanish (Peru)
      0x041b   Slovak              0x080c   French (Belgium)     0x2c01   Arabic (Jordan)
      0x041c   Albanian            0x0810   Italian (CH)         0x2c09   English (Trinidad)
      0x041d   Swedish             0x0813   Dutch (Belgium)      0x2c0a   Spanish (Argentina)
      0x041e   Thai (Thailand)     0x0814   Norwegian (Nynorsk)  0x3001   Arabic (Lebanon)
      0x041f   Turkish             0x0816   Portuguese           0x3009   English (Zimbabwe)
      0x0420   Urdu (Pakistan)     0x081a   Serbian (Latin)      0x300a   Spanish (Ecuador)
      0x0421   Indonesian          0x081d   Swedish (Finland)    0x3401   Arabic (Kuwait)
      0x0422   Ukrainian           0x0827   Lithuanian (Classic) 0x3409   English (Philippines)
      0x0423   Belarusian          0x082c   Azeri (Cyrillic)     0x340a   Spanish (Chile)
      0x0424   Slovene             0x083e   Malay (Brunei)       0x3801   Arabic (U.A.E.)
      0x0425   Estonian            0x0843   Uzbek (Cyrillic)     0x380a   Spanish (Uruguay)
      0x0426   Latvian (Latvia)    0x0c01   Arabic (Egypt)       0x3c01   Arabic (Bahrain)
      0x0427   Lithuanian          0x0c04   Chinese (Hong Kong)  0x3c0a   Spanish (Paraguay)
      0x0429   Farsi (Iran)        0x0c07   German (Austria)     0x4001   Arabic (Qatar)
      0x042a   Vietnamese          0x0c09   English (Australia)  0x400a   Spanish (Bolivia)
      0x042b   Armenian (Armenia)  0x0c0a   Spanish (Int'l)      0x440a   Spanish (El Salvador)
      0x042c   Azeri (Latin)       0x0c0c   French (Canada)      0x480a   Spanish (Honduras)
      0x042d   Basque (Spain)      0x0c1a   Serbian (Cyrillic)   0x4c0a   Spanish (Nicaragua)
      0x042f   Macedonian          0x1001   Arabic (Libya)       0x500a   Spanish (Puerto Rico)
     */
int CVersionInfo::GetLanguageCode(UINT nTransTableIndex//=0 index of Translation Table entry
                                 )
{
if (IsVersionInfo())
  {
  ASSERT (nTransTableIndex < m_nTranslationTableSize);
  return m_lpTranslationTable[nTransTableIndex].wLanguage;
  }
return -1;
}
//::GetCompanyName()-------------------------------------------------------------
/*If successful returns TRUE and Company Name entry, otherwise returns FALSE.
 */
BOOL CVersionInfo::GetCompanyName(LPTSTR &strCompanyName, //resulting string
                                  UINT nTransTableIndex //=0 index of Translation Table entry
                                 )
{
UINT nSize;
char subBlockName[255];
ASSERT (nTransTableIndex < m_nTranslationTableSize);

if (!IsVersionInfo())
  return FALSE;

wsprintf(subBlockName, m_StringFileInfo,
         m_lpTranslationTable[nTransTableIndex].wLanguage,
         m_lpTranslationTable[nTransTableIndex].wCharSet,
         (LPTSTR)"CompanyName");
return ::VerQueryValue(m_lpData,
                       subBlockName,
                       (LPVOID*)&strCompanyName,
                       &nSize);
}

BOOL CVersionInfo::GetCompanyName(CString& strCompanyName, //resulting string
                                  UINT nTransTableIndex //=0 index of Translation Table entry
                                 )
{
LPTSTR lpCompanyName;
if (!GetCompanyName(lpCompanyName,nTransTableIndex))
  return FALSE;
strCompanyName = lpCompanyName; //Copy requested information
return TRUE;
}

//::GetFileVersion()-----------------------------------------------------------
/*If successful returns TRUE and File Version entry, otherwise returns FALSE.
 */
BOOL CVersionInfo::GetFileVersion(LPTSTR &strFileVersion, //resulting string
                                  UINT nTransTableIndex //=0 index of Translation Table entry
                                 )
{
UINT nSize;
char subBlockName[255];
ASSERT (nTransTableIndex < m_nTranslationTableSize);

if (!IsVersionInfo())
  return FALSE;

wsprintf(subBlockName, m_StringFileInfo,
         m_lpTranslationTable[nTransTableIndex].wLanguage,
         m_lpTranslationTable[nTransTableIndex].wCharSet,
         (LPTSTR)"FileVersion");
return ::VerQueryValue(m_lpData,
                       subBlockName,
                       (LPVOID*)&strFileVersion,
                       &nSize);
}

BOOL CVersionInfo::GetFileVersion(CString& strFileVersion, //resulting string
                                  UINT nTransTableIndex //=0 index of Translation Table entry
                                 )
{
LPTSTR lpFileVersion;
if (!GetFileVersion(lpFileVersion,nTransTableIndex))
  return FALSE;
strFileVersion = lpFileVersion; //Copy requested information
return TRUE;
}

//::GetFileDescription()-------------------------------------------------------
/*If successful returns TRUE and File Description entry, otherwise returns FALSE.

  Example:
    #include "KVerInfo.h" //CVersionInfo class
    int ShowVersion(HWND hParent)
      {
      CString strTemp;
      CString strDescription;
      strDescription = _T("C:\Windows\MSVCRT.dll");

      CVersionInfo DllVersion(strDescription);
      if(DllDescription.GetTranslationTableSize() < 2)
        {
        strDescription += _T(" v.");
        DllVersion.GetProductVersion(strTemp,1);
        strDescription += strTemp;
        strDescription += _T("\n");
        DllVersion.GetFileDescription(strTemp,1);
        strDescription += strTemp;

        return ::MessageBox(hParent,
                            strDescription,
                            _T("DLL Version"),
                            MB_OK|MB_ICONEXCLAMATION);
        }
      return -1;
      }

 */
BOOL CVersionInfo::GetFileDescription(LPTSTR &strFileDescription, //resulting string
                                      UINT nTransTableIndex //=0 index of Translation Table entry
                                     )
{
UINT nSize;
char subBlockName[255];
ASSERT (nTransTableIndex < m_nTranslationTableSize);

if (!IsVersionInfo())
  return FALSE;

wsprintf(subBlockName, m_StringFileInfo,
         m_lpTranslationTable[nTransTableIndex].wLanguage,
         m_lpTranslationTable[nTransTableIndex].wCharSet,
         (LPTSTR)"FileDescription");
return ::VerQueryValue(m_lpData,
                       subBlockName,
                       (LPVOID*)&strFileDescription,
                       &nSize);
}

BOOL CVersionInfo::GetFileDescription(CString& strFileDescription, //resulting string
                                      UINT nTransTableIndex //=0 index of Translation Table entry
                                     )
{
LPTSTR lpFileDescription;
if (!GetFileDescription(lpFileDescription,nTransTableIndex))
  return FALSE;
strFileDescription = lpFileDescription; //Copy requested information
return TRUE;
}

//::GetFixedFileInfo()---------------------------------------------------------
/*Retrieves the VS_FIXEDFILEINFO structure for the version-information resource.
  Return TRUE if successful, otherwise returns FALSE.

    struct VS_FIXEDFILEINFO
      {
      DWORD dwSignature;        //contains the value 0xFEEFO4BD
      DWORD dwStrucVersion;     //the version number of this structure (high-order word
                                // is major number, low-order word is minor number)
      DWORD dwFileVersionMS;    //the most significant 32 bits of the file's version number
      DWORD dwFileVersionLS;    //the least significant 32 bits of the file's version number
      DWORD dwProductVersionMS; //the most significant 32 bits of the version number of
                                //the product with which this file was distributed.
      DWORD dwProductVersionLS; //the least significant 32 bits of the version number of
                                //the product with which this file was distributed.
      DWORD dwFileFlagsMask;    //a bitmask that specifies the valid bits in dwFileFlags
      DWORD dwFileFlags;        //a bitmask that specifies the Boolean attributes of the file
      DWORD dwFileOS;           //the operating system for which this file was designed
      DWORD dwFileType;         //specifies the general type of file.
      DWORD dwFileSubtype;      //Specifies the function of the file
      DWORD dwFileDateMS;       //the most significant 32 bits of the file's 64-bit
                                //creation date and time stamp
      DWORD dwFileDateLS;       //the least significant 32 bits of the file's 64-bit
                                //creation date and time stamp
      };

  Example:

      //Get fixed file information from version resource
    CVersionInfo ExeVersion;
    VS_FIXEDFILEINFO vsffiData;
    if(ExeVersion.GetFixedFileInfo(vsffiData))
      {
      if ((vsffiData.dwFileOS & VOS__WINDOWS32) == VOS__WINDOWS32)
        TRACE0(_T("Win32 API."));
      }

 */
BOOL CVersionInfo::GetFixedFileInfo(VS_FIXEDFILEINFO& vsffiData)
{
if(IsVersionInfo())
  {
  UINT nSize;
  VS_FIXEDFILEINFO* pvsffiData;
  if ( ::VerQueryValue(m_lpData,
                     _T("\\"),
                       (LPVOID*)&pvsffiData,
                       &nSize) > 0 )
    {
      //Copy file information
    vsffiData = *pvsffiData;
    return TRUE;
    }
  }
return FALSE;
}

//::GetWindowsVersion()--------------------------------------------------------
#ifdef __KWINVERS_H__ //To obtain information about OS include
                      //UWinVers.h header file  Jan 2k D.K.

  /*Returns TRUE and formatted string with version of the MS Windows OS,
    otherwise returns FALSE.

    Note: include KWinVers.h header file
  */
  BOOL CVersionInfo::GetWindowsVersion(CString& strWinVersion)
  {
  return GetWindowsVersionEx(strWinVersion);
  }
#endif //__KWINVERS_H__

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  5    Biblioteka1.4         25/01/2002 3:59:22 PMDarko           Updated
 *       comments
 *  4    Biblioteka1.3         19/08/2001 10:56:00 PMDarko           Butyfier
 *  3    Biblioteka1.2         11/07/2001 9:53:20 PMDarko           
 *  2    Biblioteka1.1         08/06/2001 10:52:19 PMDarko           VSS
 *  1    Biblioteka1.0         13/08/2000 3:02:53 PMDarko           
 * $
 *****************************************************************************/
 