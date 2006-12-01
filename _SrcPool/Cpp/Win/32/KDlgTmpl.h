/*$Workfile: KDlgTmpl.h$: header file
  $Revision: 10$ $Date: 2005-05-12 11:05:28$
  $Author: Darko Kolakovic$

  Copyright (c) 1996 Microsoft Corporation. All rights reserved.
  (see MSDN or note at the end of the file for copyright grants)
  Interface of the CDlgItemTempl and CDlgTempl classes
  Written by Sridhar Madhugiri
  of Microsoft Product Support Services, Languages Developer Support
  Mar. 98 Cosmetic changes D.K.
 */
// Group=Windows

#ifndef _KDLGTMPL_H_
  //$Workfile: KDlgTmpl.h$ sentry
  #define _KDLGTMPL_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#ifndef __AFXWIN_H__
  #include <afxwin.h>
#endif

#include "KDlgTmIt.h" //CDlgItemTempl class

/////////////////////////////////////////////////////////////////////////////
// Map functions to UNICODE or ANSI depending on the build.
// the functions with out the W or A suffix can be used and
// type of string passed in depends on the build
// The W or A function can also be called as long as the
// correct type of string is passed in.
#ifdef UNICODE
  #define SetCaption      SetCaptionW
  #define SetControlClass SetControlClassW
  #define SetCaption      SetCaptionW
  #define SetClassName    SetClassNameW
  #define SetFontInfo     SetFontInfoW
  #define SetMenuName     SetMenuNameW
#else
  #define SetCaption      SetCaptionA
  #define SetControlClass SetControlClassA
  #define SetCaption      SetCaptionA
  #define SetClassName    SetClassNameA
  #define SetFontInfo     SetFontInfoA
  #define SetMenuName     SetMenuNameA
#endif

/////////////////////////////////////////////////////////////////////////////
/* CDlgTempl class encapsulates DLGTEMPLATE structure
  The DLGTEMPLATE structure defines the dimensions and style of a dialog box.
  This structure, always the first in a dialog box template, also specifies
  the number of controls in the dialog box and therefore specifies the number
  of subsequent DLGITEMTEMPLATE structures in the template

Note:
  If your application uses MFC in a shared DLL, and your application is
  in a language other than the operating system's current language, you
  will need to copy the corresponding localized resources MFC40XXX.DLL
  from the Microsoft Visual C++ CD-ROM onto the system or system32 directory,
  and rename it to be MFCLOC.DLL.  ("XXX" stands for the language abbreviation.
  For example, MFC40DEU.DLL contains resources translated to German.)  If you
  don't do this, some of the UI elements of your application will remain in the
  language of the operating system.

      typedef struct
        {
        DWORD style;            //the dialog box style of the dialog
        DWORD dwExtendedStyle;  //extended styles for a window;
                                //not used to create dialog boxes
        WORD cdit;              //the number of items in the dialog box
        short x;                //the upper-left corner position in dialog box units
        short y;                //the upper-left corner position in dialog box units
        short cx;               //the width, in dialog box units, of the dialog box
        short cy;               //the height, in dialog box units, of the dialog box
        } DLGTEMPLATE;

  Note: uses Microsoft Foundation Library (MFC).
        Microsoft Windows specific (Win).

  TODO: DLGTEMPLATEEX

  See Also: IsDlgTemplEx
*/
class CDlgTempl : public CObject
{
public:

// Construction
public:
  CDlgTempl();
  DECLARE_SERIAL(CDlgTempl)

// Attributes
public:
protected:

  HLOCAL m_hDlgTemplate;     //handle to store the memory allocated by LockTemplate
   void FAR* m_lpDlgTemplate; //pointer used by LockTemplate to keep track of
                             //the memory returned by LocalLock in
                             //the LockTemplate function
  CObList m_controlList;     //list of controls on the dialog
  DLGTEMPLATE m_dlgTemplate; //constant part of the dialog template
  WORD m_nPointSize;         //point size of the font
    //Length of the various variable length strings in bytes
  UINT m_nMenuNameLength;
  UINT m_nClassNameLength;
  UINT m_nCaptionLength;
  UINT m_nFaceNameLength;
    // Variable length data for the template
    // They point to NULL terminated UNICODE strings
  void* m_pMenuName;
  void* m_pClassName;
  void* m_pCaption;
  void* m_pFaceName;


// Operations
public:
      //Add controls to the template
    BOOL AddControl(WORD  x, WORD  y, WORD  cx, WORD  cy, WORD  wID, DWORD style,

      WORD controlClass, const TCHAR* szCaption = NULL, WORD nInitDataLength = 0,
      WORD* pInitData = NULL, DWORD dwExtendedStyle = 0);
    BOOL AddControl( WORD  x, WORD  y, WORD  cx, WORD  cy, WORD  wID, DWORD style,

      LPCTSTR controlClass, LPCTSTR szCaption = NULL,   WORD nInitDataLength = 0,
      WORD* pInitData = NULL, DWORD dwExtendedStyle = 0);
    BOOL AddControl( WORD  x, WORD  y, WORD  cx, WORD  cy, WORD  wID, DWORD style,
      const TCHAR* controlClass, WORD wOrd, WORD nInitDataLength = 0,
      WORD* pInitData = NULL, DWORD dwExtendedStyle = 0);
    BOOL AddControl(WORD  x, WORD  y, WORD  cx, WORD  cy, WORD  wID, DWORD style,
      WORD controlClass, WORD wOrd, WORD nInitDataLength = 0,
      WORD* pInitData = NULL, DWORD dwExtendedStyle = 0);

    // Create the template in memory so that it can be used with CreateDialogIndirect
    void* LockTemplate();

    // Remove the template from memory that was previously created by LockTemplate
    void UnlockTemplate();

    //Create the template in memory.
    BOOL CreateTemplateInMemory(void* pMemory = NULL);

    // Helper function to parse a dialog template in memory
    // This function can be directly used if a pointer a valid template in memory is passed in.
    BOOL CreateTemplateFromMemory(BYTE* p);

    // Returns the size of the template when it is created in memory
    UINT GetLength();

    // Get the length of just the dialog header without the controls
    UINT GetHeaderLength()
    {
        return AlignDWord( sizeof(DLGTEMPLATE) +
        m_nMenuNameLength
        + m_nClassNameLength
        + m_nCaptionLength
        + ((m_nFaceNameLength) ? (m_nFaceNameLength + sizeof(WORD)) : 0));
    }

    //Returns a pointer to a UNICODE string which specifies the menu.
    //if the UNICODE character is 0xFFFF then the next WORD specified is
    //the ID of the menu resource
    const WORD* GetMenuName() { return (WORD*) m_pMenuName; }

    //Returns a pointer to a UNICODE string which specifies the windows class name.
    //if the UNICODE character is 0xFFFF then the next WORD specified is
    //the atom of a registered class name
    const WCHAR* GetClassName() { return (WCHAR*) m_pClassName; }

    //Returns a pointer to a UNICODE string which specifies the windows caption.
    //if the UNICODE character is 0xFFFF then the next WORD specified is
    //the wID of the resource to be used with static controls
    const WCHAR* GetCaption() { return (WCHAR*) m_pCaption; }

    //Returns the font information used by the template. The font name is
    //returned in ppFontInfo and is a UNICODE string. The return value is the
    //point size of the font
    WORD GetFontInfo(const WCHAR** ppFontInfo)
      {ASSERT(*ppFontInfo);
      *ppFontInfo = (WCHAR*) m_pFaceName; return m_nPointSize;
      }

    LPCDLGTEMPLATE GetDlgTemplate()
      {ASSERT(m_lpDlgTemplate!=NULL);return (LPCDLGTEMPLATE)m_lpDlgTemplate;}

    BOOL SetDlgTemplate(DWORD style,
        DWORD dwExtendedStyle,
        short x, short y,
        short cx, short cy);

    BOOL SetMenuID(WORD wResourceID);
    BOOL SetMenuNameA(const char* szMenuName);
    BOOL SetMenuNameW(const WCHAR* szMenuName);

    BOOL SetClassAtom(WORD wClassAtom);
    BOOL SetClassNameA(const char* szClassName);
    BOOL SetClassNameW(const WCHAR* szClassName);
      //Sets the caption for the dialog
    BOOL SetCaptionA(const char* szCaption);
    BOOL SetCaptionW(const WCHAR* szCaption);

    BOOL SetFontInfoA(WORD wPointSize, const char* szFaceName);
    BOOL SetFontInfoW(WORD wPointSize, const WCHAR* szFaceName);

    void ResetAll(BOOL bWarn = TRUE);

    enum {byItemID, byItemPosition};

    CDlgItemTempl* FindControl(UINT nID, UINT nFlag = byItemID);
    UINT FindControlByID(UINT wID);
    CDlgItemTempl* FindControlByPosition(UINT position);
      //Removes a control from the template
    BOOL RemoveControl(UINT wID, UINT nFlags, BOOL bDelete = TRUE, CDlgItemTempl** ppControl = NULL);
      //Changes the TAB order of the control
    BOOL MoveControl(UINT wID, UINT nFlags, UINT nPosition);
    BOOL FromResource(UINT nIDTemplate);
    BOOL FromResource(LPCTSTR lpszTemplateName);

// Implementation
public:
  virtual ~CDlgTempl();

public:
  virtual void Serialize( CArchive& ar );
#ifdef _DEBUG
    void Dump( CDumpContext& dc ) const;
#endif


protected:
  ULONG AlignDWord(ULONG uLong) {  return ((uLong + 3) & ~3); }

};

///////////////////////////////////////////////////////////////////////////////
  // Following makes ClassWizard happy
  //{{AFX_VIRTUAL(CDlgTempl)
  //}}AFX_VIRTUAL
  //{{AFX_MSG(CDlgTempl)
    // NOTE - the ClassWizard will add and remove member functions here.
  //}}AFX_MSG

///////////////////////////////////////////////////////////////////////////////
// Inlines


//::FromResource()-------------------------------------------------------------
/*Initializes the object with the resource template
 */
inline BOOL CDlgTempl::FromResource(UINT nIDTemplate)
{
return FromResource(MAKEINTRESOURCE(nIDTemplate));
}

/////////////////////////////////////////////////////////////////////////////
// Extended dialog templates (new in Win95) See AfxImpl.h

#pragma pack(push, 1)

/*The DLGTEMPLATEEX structure is not defined in any standard header file.

    typedef struct
      {
      WORD      dlgVer;          //the version number of the extended dialog box template. This member must be 1.
      WORD      signature;       //specifies type of a template; if it is 0xFFFF, this is an extended dialog box template.
      DWORD     helpID;          //the help context identifier
      DWORD     exStyle;         //extended windows styles
      DWORD     style;           //the style of the dialog box
      WORD      cDlgItems;       //the number of controls in the dialog box
      short     x;               //the x-coordinate, in dialog box units, of the upper-left corner of the dialog box
      short     y;               //the y-coordinate, in dialog box units, of the upper-left corner of the dialog box
      short     cx;              //the width, in dialog box units, of the dialog box
      short     cy;              //the height, in dialog box units, of the dialog box
      sz_Or_Ord menu;            //a variable-length array of 16-bit elements that identifies a menu resource for the dialog box
      sz_Or_Ord windowClass;     //a variable-length array of 16-bit elements that identifies the window class of the dialog box
      WCHAR     title[titleLen]; //a null-terminated Unicode string that contains the title of the dialog box

      //The following members exist only if the style member is set to DS_SETFONT or DS_SHELLFONT.
      WORD     pointsize;          //the point size of the font to use for the text in the dialog box and its controls
      WORD     weight;             //the weight of the font in the range 0 through 1000
      BYTE     italic;             //if this value is TRUE, the font is italic
      BYTE     charset;            //indicates the character set to use
      WCHAR    typeface[stringLen];//a null-terminated Unicode string that contains the name of the typeface for the font
      } DLGTEMPLATEEX;

  Note: Microsoft Windows specific (Win).

*/
typedef struct
  {
  WORD dlgVer;
  WORD signature;
  DWORD helpID;
  DWORD exStyle;
  DWORD style;
  WORD cDlgItems;
  short x;
  short y;
  short cx;
  short cy;
  } DLGTEMPLATEEX;

typedef struct
  {
  DWORD helpID;
  DWORD exStyle;
  DWORD style;
  short x;
  short y;
  short cx;
  short cy;
  DWORD id;
  } DLGITEMTEMPLATEEX;

#pragma pack(pop)

///////////////////////////////////////////////////////////////////////////////
// Helpers

//IsDlgTemplEx()---------------------------------------------------------------
/*Returns TRUE if a template is an extended dialog box template.  In this case,
  the DLGTEMPLATEEX::dlgVer member specifies the template version number.
  If a template is a standard dialog box template, function returns FALSE.

  Note: Extended dialog box template has signature equal to 0xFFFF.

  Note: Microsoft Windows specific (Win).
 */
inline BOOL IsDlgTemplEx(const DLGTEMPLATE* pTemplate)
{
return ((DLGTEMPLATEEX*)pTemplate)->signature == 0xFFFF;
}

///////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif  //_KDLGTMPL_H_

/*Microsoft legal stuff
THE INFORMATION AND CODE PROVIDED HEREUNDER (COLLECTIVELY REFERRED TO
AS "SOFTWARE") IS PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND, EITHER
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. IN
NO EVENT SHALL MICROSOFT CORPORATION OR ITS SUPPLIERS BE LIABLE FOR
ANY DAMAGES WHATSOEVER INCLUDING DIRECT, INDIRECT, INCIDENTAL,
CONSEQUENTIAL, LOSS OF BUSINESS PROFITS OR SPECIAL DAMAGES, EVEN IF
MICROSOFT CORPORATION OR ITS SUPPLIERS HAVE BEEN ADVISED OF THE
POSSIBILITY OF SUCH DAMAGES. SOME STATES DO NOT ALLOW THE EXCLUSION OR
LIMITATION OF LIABILITY FOR CONSEQUENTIAL OR INCIDENTAL DAMAGES SO THE
FOREGOING LIMITATION MAY NOT APPLY.

This Software may be copied and distributed royalty-free subject to
the following conditions:

1. You must copy all Software without modification and must include
   all pages, if the Software is distributed without inclusion in your
   software product. If you are incorporating the Software in
   conjunction with and as a part of your software product which adds
   substantial value, you may modify and include portions of the
   Software.

2. You must place all copyright notices and other protective
   disclaimers and notices contained on the Software on all copies of
   the Software and your software product.

3. Unless the Software is incorporated in your software product which
   adds substantial value, you may not distribute this Software for
   profit.

4. You may not use Microsoft's name, logo, or trademarks to market
   your software product.

5. You agree to indemnify, hold harmless, and defend Microsoft and its
   suppliers from and against any claims or lawsuits, including
   attorneys' fees, that arise or result from the use or distribution
   of your software product and any modifications to the Software.

*/

/*****************************************************************************
 * $Log:
 *  9    Biblioteka1.8         2005-04-26 11:29:42  Darko Kolakovic Document groups
 *       and typo fixes
 *  8    Biblioteka1.7         2003-09-22 22:26:11  Darko           formatting
 *  7    Biblioteka1.6         2002-03-12 23:03:19  Darko
 *  6    Biblioteka1.5         2002-01-29 23:20:53  Darko           Used lbraries
 *       notes
 *  5    Biblioteka1.4         2002-01-25 16:57:05  Darko           Updated
 *       comments
 *  4    Biblioteka1.3         2001-08-19 23:53:38  Darko           Butyfier
 *  3    Biblioteka1.2         2001-07-11 22:51:24  Darko
 *  2    Biblioteka1.1         2001-06-08 23:50:39  Darko           VSS
 *  1    Biblioteka1.0         2000-08-13 15:56:27  Darko
 * $
 *****************************************************************************/
