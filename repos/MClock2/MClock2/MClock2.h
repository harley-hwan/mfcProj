
// MClock2.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMClock2App:
// See MClock2.cpp for the implementation of this class
//

class CMClock2App : public CWinApp
{
public:
	CMClock2App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMClock2App theApp;