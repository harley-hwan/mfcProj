#include "pch.h"
#include "ListenSocket.h"
#include "HelloServerDlg.h"

CListenSocket::CListenSocket(CHelloServerDlg* pHelloServerDlg)
{
	m_pHelloServerDlg = pHelloServerDlg;
}


CListenSocket::~CListenSocket()
{
}


void CListenSocket::OnAccept(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	m_pHelloServerDlg->ProcessAccept();

	CSocket::OnAccept(nErrorCode);
}