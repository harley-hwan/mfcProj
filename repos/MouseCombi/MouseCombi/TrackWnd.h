#pragma once
#include <afxwin.h>
class CTrackWnd :public CWnd
{
    DECLARE_DYNAMIC(CTrackWnd)

public:
    CTrackWnd();
    virtual ~CTrackWnd();

    BOOL    m_bTrack;

    void OnMouseMove(UINT nFlags, CPoint point);

    //    DECLARE_MESSAGE_MAP()
};

