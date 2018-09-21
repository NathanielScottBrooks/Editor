// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <Windows.h>

#include "Headers\Window_c.h"

void Window::Redraw() const {

    ::InvalidateRect(hwnd, nullptr,true);
    ::UpdateWindow(hwnd);

}

bool Window::Show(int showState) const {

    bool canShow = ::ShowWindow(hwnd, showState);
    if (canShow)
        return 1;
    return 0;

}

void Window::Create(int showState, DWORD exStyle, LPCWSTR className,
    LPCWSTR windowTitle, DWORD style, int xStart, int yStart, int width,
    int height, HWND parent, HMENU menu, LPVOID structure) {

    hwndParent = parent;
    hwnd = ::CreateWindowExW(exStyle, className, windowTitle,
        style, xStart, yStart, width, height, parent, menu, 
        appInst, structure);
    ::ShowWindow(hwnd, showState);

}

void Window::ConstructClass(HINSTANCE instance, WNDPROC wndProcedure, LPCWSTR className,
    HICON icon, HICON smallIcon, LPCWSTR menu, HCURSOR cursor,
    HBRUSH background, unsigned int style) {

    appInst = instance; /*reinterpret_cast<HINSTANCE>(GetWindowLongPtrW(hwnd,
        GWLP_HINSTANCE));*/

    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.lpfnWndProc = wndProcedure;
    wc.hInstance = appInst;
    wc.lpszClassName = className;
    wc.hIcon = icon;
    wc.hIconSm = smallIcon;
    wc.lpszMenuName = menu;
    wc.hCursor = cursor;
    wc.hbrBackground = background;
    wc.style = style;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;

    ::RegisterClassExW(&wc);

}

int Window::GetWidth() const {

    RECT clientRect;
    ::GetClientRect(hwnd, &clientRect);
        return (clientRect.right - clientRect.left);
    return 0;

}

int Window::GetHeight() const {

    RECT clientRect;
    ::GetClientRect(hwnd, &clientRect);
    if (::IsWindowVisible(hwnd))
        return (clientRect.bottom - clientRect.top);
    return 0;

}

HWND Window::parentHWND() const {

    return hwndParent;

}

HINSTANCE Window::instance() const {

    return appInst;

}

void Window::Destroy(HACCEL accelerators) {

    ::DestroyAcceleratorTable(accelerators);
    if (wc.cbSize != 0)
        ::UnregisterClassW(wc.lpszClassName, appInst);
    ::DestroyWindow(hwnd);

}

Window::operator HWND() const {

    return hwnd;

}