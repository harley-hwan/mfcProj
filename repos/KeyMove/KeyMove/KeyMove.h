
// KeyMove.h : main header file for the KeyMove application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CKeyMoveApp:
// See KeyMove.cpp for the implementation of this class
//

class CKeyMoveApp : public CWinApp
{
public:
	CKeyMoveApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CKeyMoveApp theApp;
