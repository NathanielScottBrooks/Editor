// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com


#include <Windows.h>

#include "Headers\StatusBar_c.h"
#include <Uxtheme.h>

StatusBar::StatusBar (HWND parentHandle) {

    hwndParent = parentHandle ;
    appInst = reinterpret_cast<HINSTANCE>(GetWindowLongPtrW(hwndParent,
        GWLP_HINSTANCE));

}

void StatusBar::Create (unsigned int height, COLORREF bkColor) {

    hwnd = ::CreateWindowExW(NULL, STATUSCLASSNAMEW, nullptr,
        WS_CHILD | WS_VISIBLE, 0, 0, 0, 0,
        hwndParent, nullptr, appInst, nullptr);
    ::SetWindowTheme(hwnd, L" ", L" ");
    ::SendMessageW(hwnd, SB_SETMINHEIGHT, height, 0);
    ::SendMessageW(hwnd, SB_SETBKCOLOR, 0, bkColor);

}

void StatusBar::SetParts(int numberParts, int* partWidths) {

    ::SendMessageW(hwnd, SB_SETPARTS, numberParts,
        reinterpret_cast<LPARAM>(partWidths));

}

void StatusBar::SetItemText(bool setOwnerDraw, int itemIndex,
    wchar_t* itemText) {

    int drawOwn = NULL;

    if(setOwnerDraw)
        drawOwn = SBT_OWNERDRAW;
    ::SendMessageW(hwnd, SB_SETTEXTW, itemIndex | SBT_NOBORDERS | drawOwn,
        reinterpret_cast<LPARAM>(itemText));

}

void StatusBar::Destroy() {

    ::DestroyWindow(hwnd);

}