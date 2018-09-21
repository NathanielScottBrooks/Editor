// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <CommCtrl.h>

#include "Headers/Window_c.h"
#include "Headers/Prototypes.h"
#include "Headers/Resource.h"

int _stdcall ::wWinMain(HINSTANCE instance, HINSTANCE prevInstance,
    wchar_t* cmdLine, int cmdShow) {

    INITCOMMONCONTROLSEX initCommCtrl;
    initCommCtrl.dwICC = ICC_WIN95_CLASSES | ICC_STANDARD_CLASSES;
    initCommCtrl.dwSize = sizeof(INITCOMMONCONTROLSEX);
    ::InitCommonControlsEx(&initCommCtrl);

    const wchar_t className[] = L"Main Instance";
    mainWindow.ConstructClass(instance, MainProcedure, className,
        ::LoadIconW(instance, MAKEINTRESOURCEW(IDI_APPLICATION)),
        ::LoadIconW(instance, MAKEINTRESOURCEW(IDI_APPLICATION)),
        nullptr, ::LoadCursorW(nullptr, MAKEINTRESOURCEW(IDC_ARROW)),
        ::CreateSolidBrush(0x2D2D30), CS_DBLCLKS | CS_VREDRAW | CS_HREDRAW);
    mainWindow.Create(SW_MAXIMIZE, WS_EX_CLIENTEDGE, className, L"Main Panel",
        WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        nullptr, nullptr, nullptr); 
    mainWindow.Redraw();
    
    MSG messageNotif;
    HACCEL mainAcceleraters = ::LoadAcceleratorsW(instance,
        MAKEINTRESOURCEW(IDA_ACCELERATOR_MAIN));
    while (::GetMessageW(&messageNotif, nullptr, 0, 0)) {
        if (!::TranslateAcceleratorW(mainWindow,
            mainAcceleraters, &messageNotif)) {
            ::TranslateMessage(&messageNotif);
            ::DispatchMessageW(&messageNotif);
        }
    }
    mainWindow.Destroy(mainAcceleraters);
    return 0;

}