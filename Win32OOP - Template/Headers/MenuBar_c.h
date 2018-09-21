#pragma once
#ifndef H_MENUBAR_H
#define H_MENUBAR_H

#include <Windows.h>
#include <CommCtrl.h>

#include "Toolbar_c.h"

class MenuBar : public Toolbar {
    public:
        MenuBar(HWND parentHandle);
        ~MenuBar() = default;

        void Create(LPCWSTR bmpRcBanner, int menuIconHeight,
            int maxBtns, int btnX, int btnY, int alignTop);
        void DisplayDropMenu(int item, HMENU dropMenu);
        void DrawItemIcon(int imageIndex, HDC destinationHDC, int xStart,
            int yStart);
    private:
        HIMAGELIST normalImageList;
        int iconHeight;
};

#endif