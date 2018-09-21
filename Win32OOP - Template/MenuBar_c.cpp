// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <Uxtheme.h>
#pragma comment(lib, "UxTheme.lib")

#include "Headers\MenuBar_c.h"

MenuBar::MenuBar(HWND parentHandle) {

    hwndParent = parentHandle;
    appInst = reinterpret_cast<HINSTANCE>(GetWindowLongPtrW(hwndParent,
        GWLP_HINSTANCE));

}

void MenuBar::Create (LPCWSTR bmpRcBanner, int menuIconHeight,
    int maxBtns, int btnX, int btnY, int alignTop) {

    int forceAlign = CCS_NOPARENTALIGN;

    if (alignTop)
        forceAlign = NULL;
    hwnd = ::CreateWindowExW(NULL, TOOLBARCLASSNAMEW, NULL,
        WS_CHILD | TBSTYLE_WRAPABLE | WS_VISIBLE | forceAlign |
        TBSTYLE_LIST | CCS_NODIVIDER | TBSTYLE_FLAT, 0, 0, 0, 0,
        hwndParent, nullptr, appInst, nullptr);
    /*::SetWindowTheme(hwnd, L" ", L" ");*/

    normalImageList = ::ImageList_LoadImageW(appInst,
        bmpRcBanner, menuIconHeight, maxBtns, CLR_DEFAULT,
        IMAGE_BITMAP, LR_LOADTRANSPARENT | LR_SHARED | LR_DEFAULTSIZE |
        LR_CREATEDIBSECTION);
    ::SendMessageW(hwnd, TB_BUTTONSTRUCTSIZE,
        sizeof (TBBUTTON), 0);

};

void MenuBar::DrawItemIcon(int imageIndex, HDC destinationHDC, int xStart,
    int yStart) {

    DWORD padding = SendMessageW(hwnd, TB_GETPADDING, 0, 0);
    ::ImageList_Draw(normalImageList, imageIndex, destinationHDC,
    LOWORD(padding), HIWORD(padding), ILD_TRANSPARENT);

}

void MenuBar::DisplayDropMenu (int item, HMENU dropMenu) {

    RECT menuRect;
    ::SendMessageW(hwnd, TB_GETRECT,
        static_cast<WPARAM>(item),
        reinterpret_cast<LPARAM>(&menuRect));
    ::MapWindowPoints(hwnd, HWND_DESKTOP,
        reinterpret_cast<LPPOINT>(&menuRect), 2);
    TPMPARAMS popupInfo;
    popupInfo.cbSize = sizeof(TPMPARAMS);
    popupInfo.rcExclude = menuRect;
    ::TrackPopupMenu(dropMenu, TPM_RIGHTBUTTON |
        TPM_LEFTALIGN | TPM_VERTICAL, menuRect.left,
        menuRect.bottom, 0, hwnd, NULL);

}