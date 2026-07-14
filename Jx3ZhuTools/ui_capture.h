#pragma once
#include "Resource.h"
#include "common.h"
#include <set>

inline HWND ui_capture_GetWindowFromPointEx(POINT pt)
{
    HWND hWnd = ::WindowFromPoint(pt);
    if(hWnd)
    {
        POINT ptClient;
        POINT ptOrigin;
        ptOrigin.x = ptOrigin.y = 0;

        ::ClientToScreen(hWnd, &ptOrigin);
        ptClient.x = pt.x - ptOrigin.x;
        ptClient.y = pt.y - ptOrigin.y;

        HWND hChild = ::ChildWindowFromPoint(hWnd, ptClient);
        if(hChild)
            hWnd = hChild;
    }
    if(hWnd == NULL)
        return NULL;

    LPARAM lParam = MAKELPARAM(pt.x, pt.y);
    ULONG_PTR result = 0;
    DWORD style = ::GetWindowLong(hWnd, GWL_STYLE);
    if((style & WS_CHILDWINDOW) != 0 &&
        ::SendMessageTimeout(hWnd, WM_NCHITTEST, 0, lParam, SMTO_ABORTIFHUNG, 1000, &result) &&
        result == HTTRANSPARENT)
    {
        HWND hParent = ::GetParent(hWnd);
        if(hParent)
            hWnd = hParent;
    }
    return hWnd;
}

class ui_capture : public CStatic
{
public:
    ui_capture();
    virtual ~ui_capture();

    void AddRecvWnd(HWND hWnd);
    void RemoveRecvWnd(HWND hWnd);

protected:
    virtual void PreSubclassWindow();

    void Init();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnCaptureChanged(CWnd* pWnd);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    VOID FrameWindow(HWND hWnd);
    void DrawFrame(POINT pt);

private:
    HICON m_hIcon;
    bool m_bTracking;
    HWND m_hLastWnd;
    HPEN m_hPen;
    HCURSOR cursor_sys;
    std::set<HWND> m_recvWnd;

    DECLARE_MESSAGE_MAP()
};

inline ui_capture::ui_capture()
    : m_hIcon(NULL)
    , m_bTracking(false)
    , m_hLastWnd(NULL)
    , m_hPen((HPEN)::GetStockObject(WHITE_PEN))
    , cursor_sys(NULL)
{
}

inline ui_capture::~ui_capture()
{
    if(m_hIcon)
        DestroyIcon(m_hIcon);
}

inline void ui_capture::PreSubclassWindow()
{
    CStatic::PreSubclassWindow();
    Init();
}

inline void ui_capture::Init()
{
    ModifyStyle(0, 0x50001103 | SS_ICON | SS_CENTERIMAGE);
    ModifyStyleEx(0, 0x20004);

    m_hIcon = (HICON)::LoadImage(AfxGetResourceHandle(),
        MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 32, 32, 0);
    SetIcon(m_hIcon);
}

inline void ui_capture::OnLButtonDown(UINT nFlags, CPoint point)
{
    if(m_bTracking)
        return;

    std::set<HWND>::const_iterator si = m_recvWnd.begin();
    for(; si != m_recvWnd.end(); ++si)
    {
        ::SendMessage(*si, WM_SPY_START, 0, NULL);
    }

    m_bTracking = true;
    SetCapture();
    SetIcon(NULL);
    if(m_hIcon)
        cursor_sys = ::SetCursor((HCURSOR)m_hIcon);

    CStatic::OnLButtonDown(nFlags, point);
}

inline void ui_capture::OnLButtonUp(UINT nFlags, CPoint point)
{
    if(!m_bTracking)
    {
        CStatic::OnLButtonUp(nFlags, point);
        return;
    }

    ::ReleaseCapture();

    POINT pt;
    pt.x = point.x;
    pt.y = point.y;
    ClientToScreen(&pt);
    HWND hWnd = ui_capture_GetWindowFromPointEx(pt);

    std::set<HWND>::const_iterator si = m_recvWnd.begin();
    for(; si != m_recvWnd.end(); ++si)
    {
        ::PostMessage(*si, WM_SPY, (WPARAM)hWnd, NULL);
    }

    CStatic::OnLButtonUp(nFlags, point);
}

inline void ui_capture::OnCaptureChanged(CWnd* pWnd)
{
    if(m_bTracking)
    {
        m_bTracking = false;
        if(cursor_sys)
            ::SetCursor(cursor_sys);
        SetIcon(m_hIcon);
        if(m_hLastWnd)
            FrameWindow(m_hLastWnd);
        m_hLastWnd = NULL;
    }

    CStatic::OnCaptureChanged(pWnd);
}

inline void ui_capture::OnMouseMove(UINT nFlags, CPoint point)
{
    if(m_bTracking == true && (nFlags & MK_LBUTTON))
    {
        POINT pt;
        pt.x = point.x;
        pt.y = point.y;
        ClientToScreen(&pt);
        DrawFrame(pt);
    }

    CStatic::OnMouseMove(nFlags, point);
}

inline void ui_capture::DrawFrame(POINT pt)
{
    HWND hWnd = ui_capture_GetWindowFromPointEx(pt);
    if(hWnd == m_hLastWnd)
        return;
    if(m_hLastWnd)
        FrameWindow(m_hLastWnd);
    if(hWnd)
        FrameWindow(hWnd);
    m_hLastWnd = hWnd;
}

inline VOID ui_capture::FrameWindow(HWND hWnd)
{
    if(!::IsWindow(hWnd))
        return;

    RECT rc;
    if(!::GetWindowRect(hWnd, &rc))
        return;
    int w = rc.right - rc.left - 1;
    int h = rc.bottom - rc.top - 1;
    HDC hDC = ::GetWindowDC(hWnd);
    if(!hDC)
        return;
    ::SetROP2(hDC, R2_XORPEN);
    HPEN hOldPen = (HPEN)::SelectObject(hDC, m_hPen);
#define BB 4
    for(int i = 0; i < 4; ++i)
    {
        ::MoveToEx(hDC, 0, i, 0); ::LineTo(hDC, w + 1, i);
        ::MoveToEx(hDC, 0, h - i, 0); ::LineTo(hDC, w + 1, h - i);
        ::MoveToEx(hDC, i, BB, 0); ::LineTo(hDC, i, h - BB + 1);
        ::MoveToEx(hDC, w - i, BB, 0); ::LineTo(hDC, w - i, h - BB + 1);
    }
    ::SelectObject(hDC, hOldPen);
    ::ReleaseDC(hWnd, hDC);
}

inline void ui_capture::AddRecvWnd(HWND hWnd)
{
    m_recvWnd.insert(hWnd);
}

inline void ui_capture::RemoveRecvWnd(HWND hWnd)
{
    m_recvWnd.erase(hWnd);
}
