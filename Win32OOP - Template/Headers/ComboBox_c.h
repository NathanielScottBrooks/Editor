#pragma once
#ifndef H_COMBOBOX_H
#define H_COMBOBOX_H

#include <Windows.h>
#include <CommCtrl.h>

#include "Window_c.h"

class ComboBox : public Window {
public:
    ComboBox(HWND parentHandle, HINSTANCE instance); 
    ~ComboBox() = default;

    void Create(HWND parent, bool editItems);
    void AddItem(wchar_t* text);
    int SetCurrentItem(unsigned int index);
};

#endif