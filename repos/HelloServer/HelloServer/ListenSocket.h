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
	virtual void OnAccept(int nErrorCode); // �Ӽ�â�� �̿��ϸ� �ڵ����� �Լ� ��ϰ��� 
};