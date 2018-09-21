#pragma once
#ifndef H_TOOLBAR_H
#define H_TOOLBAR_H

#include <Windows.h>
#include <CommCtrl.h>

#include "Window_c.h"

class Toolbar : public Window {
public:
    Toolbar(HWND parentHandle);
	Toolbar() {};
    ~Toolbar() = default;

    virtual void Create(const wchar_t* bmpRcBanner, int maxBtns, int bmpX, int bmpY,
        int btnX, int btnY,
        bool alignTop, bool isVertical);
    void AddButtons(TBBUTTON* buttons, int numBtns);
    int GetNumButtons() const;
    int GetWidth() const;
    int GetHeight() const;
    void Destroy();
protected:
    HIMAGELIST normalImageList;
private:
    int verticalDisplay;
};

#endif