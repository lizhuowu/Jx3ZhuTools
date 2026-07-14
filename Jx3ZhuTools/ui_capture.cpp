#include "stdafx.h"
#include "ui_capture.h"

BEGIN_MESSAGE_MAP(ui_capture, CStatic)
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
    ON_WM_CAPTURECHANGED()
END_MESSAGE_MAP()
