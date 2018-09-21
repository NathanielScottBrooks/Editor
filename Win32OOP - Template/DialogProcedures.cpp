// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <Windows.h>

#include "Headers/Prototypes.h"
#include "Headers/Resource.h"

BOOL _stdcall CloseDialogProc(HWND handle, unsigned int message,
    WPARAM wParam, LPARAM lParam) {

    switch (message) {
        case WM_INITDIALOG: {
            return 1;
        }
        case WM_COMMAND: {
            switch (LOWORD(wParam)) {
                case IDYES: {
                    ::EndDialog(handle, IDYES);
                    break;
                }
                case IDNO: {
                    ::EndDialog(handle, IDNO);
                    break;
                }
                case IDCANCEL: {
                    ::EndDialog(handle, IDCANCEL);
                    break;
                }
            }
            break;
        }
        default: {
            break;
        }
    }
    return 0;

}

BOOL _stdcall AboutDialogProc(HWND handle, UINT message,
    WPARAM wParam, LPARAM lParam) {

    switch (message) {
        case WM_INITDIALOG: {
            return 1;
        }
        case WM_COMMAND: {
            switch (LOWORD(wParam)) {
                case IDFILEDIR: {
                    WCHAR exeLocation[MAX_PATH];
                    HINSTANCE instance = GetModuleHandleW(nullptr);
                    GetModuleFileNameW(instance, exeLocation, MAX_PATH);
                    MessageBoxExW(handle, exeLocation,
                        L"Executable is Currently Located in: ",
                        MB_ICONQUESTION, NULL);
                    break;
                }
                case IDCANCEL: {
                    EndDialog(handle, IDCANCEL);
                    return 0;
                }
                default: {
                    return 0;
                }
            }
        }
        default: {
            return 0;
        }
    }

}