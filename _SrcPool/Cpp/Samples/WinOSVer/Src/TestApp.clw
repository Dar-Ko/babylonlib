; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTestDoc
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "WinOSVer.h"
LastPage=0

ClassCount=4
Class1=CTestApp
Class2=CTestDoc
Class3=CAboutDlg
Class4=CMainFrame

ResourceCount=2
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame



[CLS:CAboutDlg]
Type=0
HeaderFile=testabout.h
ImplementationFile=testabout.cpp
BaseClass=CDialog
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=3
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_SAVE_AS
Command2=ID_APP_EXIT
Command3=ID_EDIT_UNDO
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_APP_ABOUT
CommandCount=7

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_EDIT_COPY
Command2=ID_EDIT_CUT
Command3=ID_EDIT_COPY
Command4=ID_EDIT_PASTE
Command5=ID_EDIT_CUT
CommandCount=5

[CLS:CTestApp]
Type=0
HeaderFile=testapp.h
ImplementationFile=testapp.cpp
BaseClass=CWinApp
LastObject=CTestApp

[CLS:CTestDoc]
Type=0
HeaderFile=testdoc.h
ImplementationFile=testdoc.cpp
BaseClass=CDocument
LastObject=CTestDoc

