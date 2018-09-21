#pragma once
#ifndef H_STATUSBAR_H
#define H_STATUSBAR_H

#include <Windows.h>
#include <CommCtrl.h>

#include "Window_c.h"

class StatusBar : public Window{
public:
    StatusBar(HWND parentHandle);
    ~StatusBar() = default;

    void Create(unsigned int height, COLORREF bkColor);
    void SetParts(int numberParts, int* partWidths);
    void SetItemText(bool ownerDraw, int itemIndex, wchar_t* itemText);
    void Destroy();
private:
};

#endif