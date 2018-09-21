// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
//#include <Uxtheme.h>
//#pragma comment(lib, "UxTheme.lib")

#include "Headers\Toolbar_c.h"

Toolbar::Toolbar (HWND parentHandle) {

    hwndParent = parentHandle;
    appInst = reinterpret_cast<HINSTANCE>(GetWindowLongPtrW(hwndParent,
        GWLP_HINSTANCE));

}

void Toolbar::Create(const wchar_t* bmpRcBanner, int maxBtns,
    int bmpX, int bmpY, int btnX, int btnY,
    bool alignTop, bool isVertical) {

    int forceAlign = CCS_NOPARENTALIGN;
    int isWrappable = TBSTYLE_WRAPABLE;
    if (isVertical) {
        verticalDisplay = CCS_VERT;
        isWrappable = NULL;
    }
    if (alignTop)
        forceAlign = NULL;

    hwnd = ::CreateWindowExW(NULL, TOOLBARCLASSNAMEW, NULL,
        WS_CHILD | WS_VISIBLE | CCS_NODIVIDER |
        isWrappable | TBSTYLE_TOOLTIPS | forceAlign |
        verticalDisplay | TBSTYLE_FLAT,
        0, 0, 0, 0, hwndParent, nullptr, appInst, nullptr);
    normalImageList = ::ImageList_LoadImageW(appInst,
        bmpRcBanner, bmpX, maxBtns, CLR_DEFAULT,
        IMAGE_BITMAP, LR_LOADTRANSPARENT | LR_SHARED | LR_DEFAULTSIZE |
        LR_CREATEDIBSECTION);
    ::SendMessageW(hwnd, TB_SETIMAGELIST, NULL,
        reinterpret_cast<LPARAM>(normalImageList));
    ::SendMessageW(hwnd, TB_BUTTONSTRUCTSIZE, sizeof(TBBUTTON), 0);
    ::SendMessageW(hwnd, TB_SETMAXTEXTROWS, 0, 0);

    int usedBtnX;
    int usedBtnY;
    if (btnX < bmpX)
        usedBtnX = 16;
    else
        usedBtnX = btnX;

    if (btnY < bmpY)
        usedBtnY = 16;
    else
        usedBtnY = btnY;

    ::SendMessageW(hwnd, TB_SETPADDING, 0, MAKELPARAM((usedBtnX - bmpX),
        (usedBtnY - bmpY)));

};

void Toolbar::AddButtons(TBBUTTON* buttons, int numBtns) {

    ::SendMessageW(hwnd, TB_ADDBUTTONSW, numBtns,
        reinterpret_cast<LPARAM>(buttons));

}

void Toolbar::Destroy() {

    ::DestroyWindow(hwnd);

}

int Toolbar::GetWidth() const {

    SIZE toolbarSize;
    ::SendMessageW(hwnd, TB_GETMAXSIZE, 0, reinterpret_cast<LPARAM>(
        &toolbarSize));
    return toolbarSize.cx;

}

int Toolbar::GetHeight() const {

    //DWORD iSize = ::SendMessageW(hwnd, TB_GETBUTTONSIZE, 0, 0);
    //DWORD iPadSize = ::SendMessageW(hwnd, TB_GETPADDING, 0, 0);

    //int height = HIWORD(iSize) - HIWORD(iPadSize);
    //return height;

    SIZE toolbarSize;
    ::SendMessageW(hwnd, TB_GETMAXSIZE, 0, reinterpret_cast<LPARAM>(
        &toolbarSize));
    return toolbarSize.cy;

}

int Toolbar::GetNumButtons() const {

    return (::SendMessageW(hwnd, TB_BUTTONCOUNT, 0, 0));

}