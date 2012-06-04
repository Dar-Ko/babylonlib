/*$RCSfile: KEditFileOpen.h,v $: header file
  $Revision: 1.1 $ $Date: 2012/06/04 13:24:17 $
  $Author: ddarko $

  Defines the interface for a MFC control to get a filename using the file
  open/save as common dialogs
  Copyright: 1997 - 2011 by PJ Naughter
 */
// Group=Windows

////////////////////////////////// Defines ////////////////////////////////////

#pragma once

#ifndef _KEDITFILEOPEN_H_
  #define _KEDITFILEOPEN_H_

#ifndef __ATLWIN_H__
#pragma message("DDXFile as of v1.21 requires ATL support to implement its functionality. If your project is MFC only, then you need to update it to include ATL support")
#endif

#if (_MSC_VER >= 1500)
  #if WINVER < 0x0600
    #pragma message("DDXFile when compiled under VC 2008 or later should be compiled with WINVER >= 0x0600 to allow it to support full Vista style file dialog functionality")
  #endif
#endif


/////////////////////////// Includes //////////////////////////////////////////

#ifndef _SHLOBJ_H_
  #pragma message("To avoid this message, please put shlobj.h in your pre compiled header (normally stdafx.h)")
  #include <shlobj.h>
#endif


/////////////////////////// Classes ///////////////////////////////////////////

//forward declaration
class CEditFileOpen;

class CDDXFileModifyButton : public CButton
{
public:
//Constructors / Destructors
  CDDXFileModifyButton();

//Methods
  void SetBuddy(CEditFileOpen* pBuddy);

protected:
  virtual BOOL PreTranslateMessage(MSG* pMsg);

  afx_msg void OnClicked();

  DECLARE_MESSAGE_MAP()

//Member variables
  CEditFileOpen* m_pBuddy;
  BOOL                 m_bFirstPreTranslateMessageCall;
  CToolTipCtrl         m_ToolTip;
};

class  CDDXFileFileNameDialog : public CFileDialog
{
public:
//Constructors / Destructors
#if (_MSC_VER >= 1500)
  CDDXFileFileNameDialog(BOOL bOpenFileDialog, LPCTSTR lpszDefExt = NULL, LPCTSTR lpszFileName = NULL, 
                         DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, LPCTSTR lpszFilter = NULL, 
                         CWnd* pParentWnd = NULL, DWORD dwSize = 0,	BOOL bVistaStyle = TRUE);
#else
  CDDXFileFileNameDialog(BOOL bOpenFileDialog, LPCTSTR lpszDefExt = NULL, LPCTSTR lpszFileName = NULL, 
                         DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, LPCTSTR lpszFilter = NULL, 
                         CWnd* pParentWnd = NULL, DWORD dwSize = 0);
#endif

//Methods
  void SetBuddy(CEditFileOpen* pBuddy);
#if (_MSC_VER >= 1500)  
  BOOL UsingVistaStyle() const { return m_bVistaStyle; };
#endif  

protected:
	DECLARE_DYNAMIC(CDDXFileFileNameDialog)

  virtual void OnInitDone();
  virtual BOOL OnFileNameOK();
	//virtual void OnTypeChange();

  DECLARE_MESSAGE_MAP()

//Member variables
  CEditFileOpen* m_pBuddy;
  BOOL                 m_bSetOkCaption;
};

///////////////////////////////////////////////////////////////////////////////
//CEditFileOpen extends functionality of the MFC Edit class.
//
//Note: uses Microsoft Fundation Classes Library (MFC);
//      Microsoft Windows specific (Win).
class CEditFileOpen : public CEdit
{
public:
//Constructors / Destructors
  CEditFileOpen();

//Methods
  BOOL SubclassEdit(HWND hEdit, UINT nModifyButtonID = static_cast<UINT>(-1));
  CDDXFileModifyButton& GetModifyButton() { return m_ctrlModifyButton; };

//Accessors/Mutators
  //Set/Get the caption used in the common dialog
  void SetCommonDialogTitle(const CString& sTitle) { m_sCommonDialogTitle = sTitle; };
  CString GetCommonDialogTitle() const { return m_sCommonDialogTitle; };

  //Set/Get the extension filter string used in the common dialog
  void SetCommonDialogExtensionFilter(const CString& sFilter) { m_sCommonDialogExtFilter = sFilter; };
  CString GetCommonDialogExtensionFilter() const { return m_sCommonDialogExtFilter; };
  
  //Get/Set the caption used for the "Ok" button in the common dialog
  void SetCommonDialogOkCaption(const CString& sCaption) { m_sCommonDialogOkCaption = sCaption; };
  CString GetCommonDialogOkCaption() const { return m_sCommonDialogOkCaption; };

  //Get/Set the size used for the common dialog structure (Defaults to 0 which means use the OS default value)
  void SetCommonDialogSize(DWORD dwSize) { m_dwCommonDialogSize = dwSize; };
  DWORD GetCommonDialogSize() const { return m_dwCommonDialogSize; };

#if (_MSC_VER >= 1500)
  //Get/Set whether Vista style common dialogs are used (This is only available for VC 2008 or later and when running on Vista or later)
  void SetCommonVistaStyle(BOOL bVistaStyle) { m_bVistaStyle = bVistaStyle; };
  BOOL GetCommonVistaStyle() const { return m_bVistaStyle; };
#endif
  
  //Get/Set the Modify button caption 
  void SetModifyButtonCaption(const CString& sCaption) { m_sModifyButtonCaption = sCaption; };
  CString GetModifyButtonCaption() const { return m_sModifyButtonCaption; };

  //Get/Set the ToolTip text for the edit button
  void SetModifyButtonToolTipText(const CString& sText) { m_sModifyButtonToolTipText = sText; };
  CString GetModifyButtonToolTipText() const { return m_sModifyButtonToolTipText; };
  
  //Get/Set the common dialog flags value
  void SetCommonDialogFlags(DWORD dwFlags) { m_dwCommonDialogFlags = dwFlags; };
  DWORD GetCommonDialogFlags() const { return m_dwCommonDialogFlags; };

  //Auto completion settings
  void SetAutoComplete(BOOL bAutoComplete);
  BOOL GetAutoComplete() const { return m_bAutoComplete; };
  void SetAutoCompleteFlags(DWORD dwFlags) { m_dwAutoCompleteFlags = dwFlags; };
  DWORD GetAutoCompleteFlags() const { return m_dwAutoCompleteFlags; };
  
//Misc virtual functions
  virtual CString GetOverwritePromptString(const CString& sFilename);
  virtual void Edit();   //Bring up the file picker dialog
  
protected:
  afx_msg void OnEnable(BOOL bEnable);

  DECLARE_MESSAGE_MAP()

//Misc virtual functions
  virtual BOOL AddModifyButton(UINT nModifyButtonID);
  virtual BOOL LoadStringResources();
  virtual HRESULT InitializeAutoComplete();

//Member variables
  CDDXFileModifyButton         m_ctrlModifyButton;
  CString                      m_sCommonDialogTitle;
  CString                      m_sCommonDialogExtFilter;
  CString                      m_sCommonDialogOkCaption;
  CString                      m_sModifyButtonCaption;
  CString                      m_sModifyButtonToolTipText;
  DWORD                        m_dwCommonDialogFlags;
  DWORD                        m_dwCommonDialogSize; 
#if (_MSC_VER >= 1500)
  BOOL                         m_bVistaStyle;  
#endif
  BOOL                         m_bAutoComplete;
  DWORD                        m_dwAutoCompleteFlags;
  ATL::CComPtr<IAutoComplete2> m_pAutoCompleteObject;
  ATL::CComPtr<IACList2>       m_pAutoCompleteSourceObject;
};

/////////////// MFC Data exchange routines //////////////////////////

void DDX_FilenameControl(CDataExchange* pDX, int nIDC, CEditFileOpen& rControl, UINT nModifyButtonID = static_cast<UINT>(-1));
void DDX_FilenameValue(CDataExchange* pDX, CEditFileOpen& rControl, CString& sFile);
void DDV_FilenameControlNotFolder(CDataExchange* pDX, CEditFileOpen& rControl, UINT nFailureResourceID, UINT nHelpID = static_cast<UINT>(-1));
void DDV_FilenameControlMustExist(CDataExchange* pDX, CEditFileOpen& rControl, UINT nFailureResourceID, UINT nHelpID = static_cast<UINT>(-1));
void DDV_FilenameControlOverwritePrompt(CDataExchange* pDX, CEditFileOpen& rControl, UINT nHelpID = static_cast<UINT>(-1));
void DDV_FilenameControlNotEmpty(CDataExchange* pDX, CEditFileOpen& rControl, UINT nFailureResourceID, UINT nHelpID = static_cast<UINT>(-1));
///////////////////////////////////////////////////////////////////////////////
#endif //_KEDITFILEOPEN_H_
/*****************************************************************************
 * $Log: KEditFileOpen.h,v $
 * Revision 1.1  2012/06/04 13:24:17  ddarko
 * Created
 *
 * Created: PJN / 19-03-1997
 *
 *****************************************************************************
/*Copyright (c) 1997 - 2011 by PJ Naughter (Web: www.naughter.com, 
  Email: pjna@naughter.com)
  All rights reserved.

  Copyright / Usage Details:
  You are allowed to include the source code in any product (commercial,
  shareware, freeware or otherwise)   when your product is released in binary
  form. You are allowed to modify the source code in any way you want except
  you cannot modify the copyright details at the top of each module.
 */
