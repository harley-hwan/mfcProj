#include "stdafx.h"
#include "ServiceSocket.h"
#include "HelloServerDlg.h"

CServiceSocket::CServiceSocket(CHelloServerDlg* pHelloServerDlg)
{
	m_pHelloServerDlg = pHelloServerDlg;
}


CServiceSocket::~CServiceSocket()
{
}