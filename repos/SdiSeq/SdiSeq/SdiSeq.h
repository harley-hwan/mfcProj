
// SdiSeq.h : main header file for the SdiSeq application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CSdiSeqApp:
// See SdiSeq.cpp for the implementation of this class
//

class CSdiSeqApp : public CWinApp
{
public:
	CSdiSeqApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	int Run();
};

extern CSdiSeqApp theApp;
