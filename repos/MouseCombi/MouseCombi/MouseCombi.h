
// MouseCombi.h : main header file for the MouseCombi application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMouseCombiApp:
// See MouseCombi.cpp for the implementation of this class
//

class CMouseCombiApp : public CWinApp
{
public:
	CMouseCombiApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMouseCombiApp theApp;
