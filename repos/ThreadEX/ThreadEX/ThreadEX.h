
// ThreadEX.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CThreadEXApp:
// See ThreadEX.cpp for the implementation of this class
//

class CThreadEXApp : public CWinApp
{
public:
	CThreadEXApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CThreadEXApp theApp;
