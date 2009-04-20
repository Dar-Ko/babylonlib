// TsVerInfo.cpp
// Module version information
//
// Darko Kolakovic
// Jan. 2k

#include "StdAfx.h"
#include "KVerInfo.h" //CVersionInfo class

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
  #ifdef _USE_MFC //Microsoft Fundation Classes Library (MFC)
    extern CDumpContext& AFXAPI operator <<(CDumpContext& dc,
                                          VS_FIXEDFILEINFO const& vffiSrc);
  #endif
#endif

extern BOOL TsWriteToView(LPCTSTR lszText);

//TestVerInfo()--------------------------------------------------------------
/*Function displays file version information.
 */
BOOL TestVerInfo()
{
CString strText;
CString strTemp;

TsWriteToView(_T("\r\n"));
#if _MSC_VER == 600
  strText += _T("Mfc42d.dll");
#else
  #if _MSC_VER == 1310
    strText += _T("mfc71enu.dll");
  #else
    #if _MSC_VER == 1400
      strText += _T("user32.dll");
      //strText += _T("mfc80.dll"); //assembly is not in the search path
    #else
      strText += _T("user32.dll");
    #endif
  #endif
#endif

CVersionInfo DllVersion(strText);
extern void SystemErrMessage(UINT uiSystemError);
SystemErrMessage(GetLastError());

strText += _T("  v.");
DllVersion.GetProductVersion(strTemp);
strText += strTemp;
strText += _T("\r\n");
DllVersion.GetFileDescription(strTemp);
strText += strTemp;
strText += _T("\r\n");
DllVersion.GetCopyright(strTemp);
strText += strTemp;
strText += _T("\r\n\r\n");
TsWriteToView((LPCTSTR)strText);

//Get version information from the current application
strText.Empty();
TsWriteToView(_T("VerInfoTest.exe\tv."));
CVersionInfo ExeVersion;
ExeVersion. GetFileVersion(strTemp);
strText += strTemp;
strText += _T("\r\n");
ExeVersion.GetFileDescription(strTemp);
strText += strTemp;
strText += _T("\r\n");
TsWriteToView((LPCTSTR)strText);
  //Enumerate languages
UINT i = 0;
TsWriteToView(_T("\t"));
while (i < ExeVersion.GetTranslationTableSize())
  {
  ExeVersion.GetLanguage(strTemp, i);
    //Get character set for the neutral language
  if (ExeVersion.GetLanguageCode(i) == 0x0000)
    {
    strText.Format(_T(" %d"),ExeVersion.GetCharacterSet(i));
    strTemp += strText;
    }
  strTemp += _T("\r\n\t");
  TsWriteToView((LPCTSTR)strTemp);
  i++;
  }
TsWriteToView(_T("\r\n"));

  //Get fixed file information from version resource
VS_FIXEDFILEINFO vsffiData;
if(ExeVersion.GetFixedFileInfo(vsffiData))
  {
  #ifdef _DEBUG
    #ifdef _USE_MFC //Microsoft Fundation Classes Library (MFC)
      afxDump << vsffiData;
    #endif
  #endif
  TsWriteToView(_T("\tdesigned for "));
  if (vsffiData.dwFileOS == VOS_UNKNOWN)
    TsWriteToView(_T("unknown system."));
  else
    {
    if ((vsffiData.dwFileOS & VOS_DOS) == VOS_DOS)
      TsWriteToView(_T("MS-DOS."));
    if ((vsffiData.dwFileOS & VOS_NT) == VOS_NT)
      TsWriteToView(_T("Windows NT/Windows 2000."));
    if ((vsffiData.dwFileOS & VOS__WINDOWS16) == VOS__WINDOWS16)
      TsWriteToView(_T("16-bit Windows."));
    if ((vsffiData.dwFileOS & VOS__WINDOWS32) == VOS__WINDOWS32)
      TsWriteToView(_T("Win32 API."));
    if ((vsffiData.dwFileOS & VOS_OS216) == VOS_OS216)
      TsWriteToView(_T("16-bit OS/2."));
    if ((vsffiData.dwFileOS & VOS_OS232) == VOS_OS232)
      TsWriteToView(_T("32-bit OS/2."));
    if ((vsffiData.dwFileOS & VOS__PM16) == VOS__PM16)
      TsWriteToView(_T("16-bit Presentation Manager."));
    if ((vsffiData.dwFileOS & VOS__PM32) == VOS__PM32)
      TsWriteToView(_T("32-bit Presentation Manager."));
    }

  }

return TRUE;
}

