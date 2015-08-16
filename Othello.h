// Othello.h : main header file for the OTHELLO application
//

#if !defined(AFX_OTHELLO_H__DE215BA5_F465_11D5_8C06_40644EC11002__INCLUDED_)
#define AFX_OTHELLO_H__DE215BA5_F465_11D5_8C06_40644EC11002__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// COthelloApp:
// See Othello.cpp for the implementation of this class
//

#define T_NONE  0
#define T_BLACK 1
#define T_WHITE 2
#define T_DEPTH 7

class COthelloApp : public CWinApp
{
public:
	COthelloApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COthelloApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(COthelloApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OTHELLO_H__DE215BA5_F465_11D5_8C06_40644EC11002__INCLUDED_)
