#include "graphics.h"

#include <windows.h>

void PaintWindow(HWND window) {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(window, &ps);
    FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_DESKTOP));
    EndPaint(window, &ps);
}