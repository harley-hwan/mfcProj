#include "pch.h"
#include "TrackWnd.h"


void CTrackWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_bTrack == FALSE)
	{
		TRACKMOUSEEVENT MouseEvent;
		::ZeroMemory(&MouseEvent, sizeof(MouseEvent));

		MouseEvent.cbSize = sizeof(MouseEvent);
		MouseEvent.dwFlags = TME_LEAVE;
		MouseEvent.hwndTrack = m_hWnd;
		MouseEvent.dwHoverTime = 0;

		m_bTrack = ::_TrackMouseEvent(&MouseEvent);
		if (m_bTrack) {
			SetWindowText(TEXT("Tracking!"));
		}
	}
	CWnd::OnMouseMove(nFlags, point);
}
