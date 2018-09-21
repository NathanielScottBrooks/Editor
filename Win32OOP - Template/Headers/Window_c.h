#pragma once
#ifndef H_WINDOW_H
#define H_WINDOW_H

#include <Windows.h>

class Window {
public:
    Window() {};
    virtual ~Window() = default;

    virtual void Destroy(HACCEL accelerators);
    virtual void Create(int showState, DWORD exStyle, LPCWSTR className,
        LPCWSTR windowTitle, DWORD style, int xStart, int yStart, int width,
        int height, HWND parent, HMENU menu, LPVOID structure);
    void Redraw() const;
    bool Show(int showState) const;
    virtual int GetWidth() const;
    virtual int GetHeight() const;
    void ConstructClass(HINSTANCE instance, WNDPROC wndProcedure,
        LPCWSTR className, HICON icon, HICON smallIcon, LPCWSTR menu,
        HCURSOR cursor, HBRUSH background,
    unsigned int style);
    HWND parentHWND() const;
    HINSTANCE instance() const;
    HDC mainHDC;
    operator HWND() const;
protected:
    HINSTANCE appInst = nullptr;
    HWND hwndParent = nullptr;
    HWND hwnd = nullptr;
private:
    WNDCLASSEXW wc;
};

#endif
