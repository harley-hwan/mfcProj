
// Graph.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CGraphApp:
// �� Ŭ������ ������ ���ؼ��� Graph.cpp�� �����Ͻʽÿ�.
//

class CGraphApp : public CWinApp
{
public:
	CGraphApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CGraphApp theApp;