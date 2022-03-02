
// MouseMsg.h : main header file for the MouseMsg application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMouseMsgApp:
// See MouseMsg.cpp for the implementation of this class
//

class CMouseMsgApp : public CWinApp
{
public:
	CMouseMsgApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMouseMsgApp theApp;
