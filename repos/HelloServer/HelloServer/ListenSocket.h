#pragma once
#include "afxsock.h"

class CHelloServerDlg;

class CListenSocket :
	public CSocket
{
public:
	CListenSocket(CHelloServerDlg* pHelloServerDlg);
	~CListenSocket();

	CHelloServerDlg* m_pHelloServerDlg;
public:
	virtual void OnAccept(int nErrorCode); // 속성창을 이용하면 자동으로 함수 등록가능 
};