#include "pch.h"
#include "ServiceSocket.h"
#include "HelloServerDlg.h"

CServiceSocket::CServiceSocket(CHelloServerDlg* pHelloServerDlg)
{
	m_pHelloServerDlg = pHelloServerDlg;
}


CServiceSocket::~CServiceSocket()
{
}

void CHelloServerDlg::ProcessAccept()
{
	m_pServiceSocket = new CServiceSocket(this);
	char sndBuffer[] = "Hello, world";


	if (m_pListenSocket->Accept(*m_pServiceSocket)) {
		m_static_status.SetWindowText(_T("Acceepted"));
		m_pServiceSocket->Send(sndBuffer, (int)strlen(sndBuffer));
		m_static_status.SetWindowText(_T("Send Hello, World"));
	}
	else {
		delete m_pServiceSocket;
	}
}


void CHelloServerDlg::OnBnClickedButtonsStart()
{
	// TODO: Add your control notification handler code here
	UINT nPort = 9000;

	m_pListenSocket = new CListenSocket(this);
	m_static_status.SetWindowText(_T("Create Listen Socket"));

	if (!m_pListenSocket->Create(nPort)) {
		m_static_status.SetWindowText(_T("Cannot  Create Socket"));
		return;
	}
	else {
		m_static_status.SetWindowText(_T("Socket Create success"));
		if (!m_pListenSocket->Listen()) {
			m_static_status.SetWindowText(_T("can not listen"));
			return;
		}
	}
}