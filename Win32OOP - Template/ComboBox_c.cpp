// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <Windows.h>

#include "Headers\ComboBox_c.h"

ComboBox::ComboBox(HWND parentHandle, HINSTANCE instance) {
    appInst = instance;
    hwndParent = parentHandle;
}

void ComboBox::Create(HWND parent, bool editableItems) {
    int editFlag;

    if (editableItems)
        editFlag = CBS_DROPDOWN;
    else
        editFlag = CBS_DROPDOWNLIST;
    hwnd = ::CreateWindowExW (NULL, WC_COMBOBOXW,
        nullptr, WS_CHILD | WS_VISIBLE | editFlag,
        400, 4, 100, 100, hwndParent, nullptr,
        appInst,
        nullptr);
}

void ComboBox::AddItem(wchar_t* text) {
    ::SendMessageW(hwnd, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(
        text));
}

INT ComboBox::SetCurrentItem(unsigned int index) {
    ::SendMessageW(hwnd, CB_SETCURSEL, index, NULL);
    return index;
}