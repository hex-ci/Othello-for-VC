; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=COthelloView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Othello.h"
LastPage=0

ClassCount=5
Class1=COthelloApp
Class2=COthelloDoc
Class3=COthelloView
Class4=CMainFrame

ResourceCount=3
Resource1=IDD_ABOUTBOX
Class5=CAboutDlg
Resource2=IDR_MAINFRAME
Resource3=IDD_OPTIONBOX

[CLS:COthelloApp]
Type=0
HeaderFile=Othello.h
ImplementationFile=Othello.cpp
Filter=N
LastObject=COthelloApp
BaseClass=CWinApp
VirtualFilter=AC

[CLS:COthelloDoc]
Type=0
HeaderFile=OthelloDoc.h
ImplementationFile=OthelloDoc.cpp
Filter=N
LastObject=COthelloDoc
BaseClass=CDocument
VirtualFilter=DC

[CLS:COthelloView]
Type=0
HeaderFile=OthelloView.h
ImplementationFile=OthelloView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=ID_GAME_NEW


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame




[CLS:CAboutDlg]
Type=0
HeaderFile=Othello.cpp
ImplementationFile=Othello.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=6
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_GAME_NEW
Command2=ID_GAME_OPTION
Command3=ID_APP_EXIT
Command4=ID_VIEW_STATUS_BAR
Command5=ID_APP_ABOUT
CommandCount=5

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_GAME_NEW
CommandCount=1

[DLG:IDD_OPTIONBOX]
Type=1
Class=?
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

