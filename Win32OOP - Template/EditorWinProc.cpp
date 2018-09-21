#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

#include "Headers/Prototypes.h"

// Control window procedure.
LRESULT _stdcall EditorWinProc(HWND handle, unsigned int message,
    WPARAM wParam, LPARAM lParam) {

    switch (message) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            BeginPaint(handle, &ps);
            EndPaint(handle, &ps);
            break;
        }
        case WM_NCDESTROY: {
            PostQuitMessage(0);
            break;
        }
        default:
            return DefWindowProcW(handle, message, wParam, lParam);
    }
    return 1;
}