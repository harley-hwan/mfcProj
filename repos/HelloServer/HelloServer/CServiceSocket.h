#pragma once
#include "afxsock.h"

class CHelloServerDlg;
class CServiceSocket :
	public CSocket
{
public:
	CServiceSocket(CHelloServerDlg* pHelloServerDlg);
	~CServiceSocket();

	CHelloServerDlg* m_pHelloServerDlg;
};