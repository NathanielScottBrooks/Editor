// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <Windowsx.h>
#include <CommCtrl.h>

#pragma comment(lib, "ComCtl32.lib")

#include "Headers/Prototypes.h"
#include "Headers/Resource.h"

#include "Headers/Window_c.h"
#include "Headers/Toolbar_c.h"
#include "Headers/MenuBar_c.h"
#include "Headers/StatusBar_c.h"

LRESULT _stdcall MainProcedure(HWND handle, unsigned int message,
    WPARAM wParam, LPARAM lParam) {

    HINSTANCE instance = reinterpret_cast<HINSTANCE>(::GetWindowLongPtrW(
        handle, GWLP_HINSTANCE));
    static Toolbar mainFileToolbar(handle);
    static Toolbar toolPanel(handle);
    static Toolbar editContextualBar(handle);
    static StatusBar mainStatusBar(handle);
    static MenuBar mainMenu(handle);
    static HWND leftMargin;
    static HWND mainHorzScroll;
    static HWND mainVertScroll;
    static RECT editorConfines;

    switch (message) {

        HANDLE_MSG(handle, WM_CLOSE, onMainWindowClose);
        HANDLE_MSG(handle, WM_COMMAND, onMainWindowCommand);
        case WM_CTLCOLORSTATIC: {
            if (reinterpret_cast<HWND>(lParam) == leftMargin) {
                return reinterpret_cast<LRESULT>(CreateSolidBrush(
                    0x333333));
            }
            else if (reinterpret_cast<HWND>(lParam) == editorPanel) {
                return reinterpret_cast<LRESULT>(CreateSolidBrush(
                    0x1E1E1E));
            }
            break;
        }
        case WM_CREATE: {
            mainFileToolbar.Create(MAKEINTRESOURCEW(IDT_LIGHTTOOLBAR),
                22, 16, 16, 32, 32, 0, 0);
            editContextualBar.Create(MAKEINTRESOURCEW(IDT_LIGHTTOOLBAR),
                30, 16, 16, 32, 32, 0, 0);
            toolPanel.Create(MAKEINTRESOURCEW(IDT_LIGHTTOOLBAR),
                22, 16, 16, 48, 24, 0, 1);
            mainStatusBar.Create(16, 0xCC7A00);
            mainMenu.Create(MAKEINTRESOURCE(IDT_LIGHTTOOLBAR),
                16, 20, 35, 35, 0);

            TBBUTTON mainFileBtns[7];
            mainFileBtns[0].iString = reinterpret_cast<INT_PTR>(
                L"New (Ctrl+N)");
            mainFileBtns[0].iBitmap = 0;
            mainFileBtns[0].idCommand = IDM_FILE_NEW;
            mainFileBtns[0].fsStyle = BTNS_BUTTON | BTNS_AUTOSIZE;
            mainFileBtns[0].fsState = TBSTATE_ENABLED | TBSTATE_WRAP;

            mainFileBtns[1].iString = reinterpret_cast<INT_PTR>(
                L"Open (Ctrl+O)");
            mainFileBtns[1].iBitmap = 1;
            mainFileBtns[1].idCommand = IDM_FILE_OPEN;
            mainFileBtns[1].fsStyle = BTNS_BUTTON | BTNS_AUTOSIZE;
            mainFileBtns[1].fsState = TBSTATE_ENABLED | TBSTATE_WRAP;

            mainFileBtns[2].iString = reinterpret_cast<INT_PTR>(
                L"Save (Ctrl+S)");
            mainFileBtns[2].iBitmap = 2;
            mainFileBtns[2].idCommand = IDM_FILE_SAVE;
            mainFileBtns[2].fsStyle = BTNS_BUTTON | BTNS_AUTOSIZE;
            mainFileBtns[2].fsState = TBSTATE_ENABLED | TBSTATE_WRAP;

            mainFileBtns[3].fsStyle = TBSTYLE_SEP;
            mainFileBtns[3].fsState =TBSTATE_ENABLED | TBSTATE_WRAP,

            mainFileBtns[4].iString = reinterpret_cast<INT_PTR>(
                L"Print (Ctrl+P)");
            mainFileBtns[4].iBitmap = 6;
            mainFileBtns[4].idCommand = IDM_PRINT;
            mainFileBtns[4].fsStyle = BTNS_BUTTON | BTNS_AUTOSIZE;
            mainFileBtns[4].fsState = TBSTATE_ENABLED | TBSTATE_WRAP;

            mainFileBtns[5].iString = reinterpret_cast<INT_PTR>(
                L"Settings (Ctrl+T)");
            mainFileBtns[5].iBitmap = 7;
            mainFileBtns[5].idCommand = IDM_SETTINGS;
            mainFileBtns[5].fsStyle = BTNS_BUTTON | BTNS_AUTOSIZE;
            mainFileBtns[5].fsState = TBSTATE_ENABLED | TBSTATE_WRAP;

            mainFileBtns[6].iString = reinterpret_cast<INT_PTR>(L"Help (F1)");
            mainFileBtns[6].iBitmap = 11;
            mainFileBtns[6].idCommand = IDM_HELP;
            mainFileBtns[6].fsStyle = BTNS_DROPDOWN| BTNS_AUTOSIZE;
            mainFileBtns[6].fsState = TBSTATE_ENABLED | TBSTATE_WRAP;

            TBBUTTON mainToolBtns[7];
            mainToolBtns[0].iString = reinterpret_cast<INT_PTR>(
                L"New (Ctrl+N)");
            mainToolBtns[0].iBitmap = 0;
            mainToolBtns[0].idCommand = IDM_FILE_NEW;
            mainToolBtns[0].fsStyle = BTNS_BUTTON | BTNS_AUTOSIZE;
            mainToolBtns[0].fsState = TBSTATE_ENABLED | TBSTATE_WRAP;

            mainToolBtns[1].iString = reinterpret_cast<INT_PTR>(
                L"Open (Ctrl+O)");
            mainToolBtns[1].iBitmap = 1;
            mainToolBtns[1].idCommand = IDM_FILE_OPEN;
            mainToolBtns[1].fsStyle = BTNS_BUTTON | BTNS_AUTOSIZE;
            mainToolBtns[1].fsState = TBSTATE_ENABLED | TBSTATE_WRAP;

            mainToolBtns[2].iString = reinterpret_cast<INT_PTR>(
                L"Save (Ctrl+S)");
            mainToolBtns[2].iBitmap = 2;
            mainToolBtns[2].idCommand = IDM_FILE_SAVE;
            mainToolBtns[2].fsStyle = BTNS_BUTTON | BTNS_AUTOSIZE;
            mainToolBtns[2].fsState = TBSTATE_ENABLED | TBSTATE_WRAP;

            mainToolBtns[3].iString = reinterpret_cast<INT_PTR>(
                L"Print (Ctrl+P)");
            mainToolBtns[3].iBitmap = 6;
            mainToolBtns[3].idCommand = IDM_PRINT;
            mainToolBtns[3].fsStyle = BTNS_BUTTON | BTNS_AUTOSIZE;
            mainToolBtns[3].fsState = TBSTATE_ENABLED | TBSTATE_WRAP;

            mainToolBtns[4].iString = reinterpret_cast<INT_PTR>(
                L"Settings (Ctrl+T)");
            mainToolBtns[4].iBitmap = 7;
            mainToolBtns[4].idCommand = IDM_SETTINGS;
            mainToolBtns[4].fsStyle = BTNS_BUTTON | BTNS_AUTOSIZE;
            mainToolBtns[4].fsState = TBSTATE_ENABLED | TBSTATE_WRAP;

            mainToolBtns[5].iString = reinterpret_cast<INT_PTR>(L"Help (F1)");
            mainToolBtns[5].iBitmap = 11;
            mainToolBtns[5].idCommand = IDM_HELP;
            mainToolBtns[5].fsStyle = BTNS_DROPDOWN | BTNS_AUTOSIZE;
            mainToolBtns[5].fsState = TBSTATE_ENABLED | TBSTATE_WRAP;

            TBBUTTON mainMenuBtns[5];
            mainMenuBtns[0].iString = reinterpret_cast<INT_PTR>(
                L"File");
            mainMenuBtns[0].fsStyle = BTNS_DROPDOWN | BTNS_AUTOSIZE;
            mainMenuBtns[0].fsState = TBSTATE_ENABLED | TBSTATE_WRAP;

            mainMenuBtns[1].iString = reinterpret_cast<INT_PTR>(
                L"Edit");
            mainMenuBtns[1].fsStyle = BTNS_DROPDOWN| BTNS_AUTOSIZE;
            mainMenuBtns[1].fsState = TBSTATE_ENABLED | TBSTATE_WRAP;

            mainMenuBtns[2].iString = reinterpret_cast<INT_PTR>(
                L"Insert");
            mainMenuBtns[2].fsStyle = BTNS_DROPDOWN | BTNS_AUTOSIZE;
            mainMenuBtns[2].fsState = TBSTATE_ENABLED | TBSTATE_WRAP;

            mainMenuBtns[3].iString = reinterpret_cast<INT_PTR>(
                L"Draw");
            mainMenuBtns[3].fsStyle = BTNS_DROPDOWN | BTNS_AUTOSIZE;
            mainMenuBtns[3].fsState = TBSTATE_ENABLED | TBSTATE_WRAP;

            mainMenuBtns[4].iString = reinterpret_cast<INT_PTR>(
                L"View");
            mainMenuBtns[4].fsStyle = BTNS_DROPDOWN | BTNS_AUTOSIZE;
            mainMenuBtns[4].fsState = TBSTATE_ENABLED | TBSTATE_WRAP;

            mainFileToolbar.AddButtons(mainFileBtns, 7);
            editContextualBar.AddButtons(mainFileBtns, 7);
            toolPanel.AddButtons(mainToolBtns, 6);
            toolPanel.AddButtons(mainToolBtns, 6);
            mainMenu.AddButtons(mainMenuBtns, 5);

            leftMargin = ::CreateWindowExW(NULL, WC_STATICW,
                L"", SS_NOTIFY | WS_CHILD | WS_VISIBLE,
                0, 0, 0, 0, handle, nullptr, instance, nullptr);
            editorPanel.ConstructClass(instance, EditorWinProc, L"editPanel",
                nullptr, nullptr, nullptr, ::LoadCursorW(instance, IDC_IBEAM),
                CreateSolidBrush(0x1E1E1E), NULL);
            editorPanel.Create(SW_SHOW, NULL, L"editPanel", L"",
                WS_VISIBLE | WS_CHILD | WS_TABSTOP, 0, 0, 0, 0, handle,
                nullptr, nullptr);

            mainHorzScroll = CreateWindowExW(0, L"SCROLLBAR", NULL,
                WS_CHILD | WS_VISIBLE | SBS_HORZ, 0, 0, 0, 0,
                handle, NULL, instance, NULL);
            mainVertScroll = CreateWindowExW(0, L"SCROLLBAR", NULL,
                WS_CHILD | WS_VISIBLE | SBS_VERT, 0, 0, 0, 0,
                handle, NULL, instance, NULL);

            break;
        }
        HANDLE_MSG(handle, WM_DESTROY, onMainWindowDestroy);
        HANDLE_MSG(handle, WM_DRAWITEM, onMainWindowDrawItem);
        HANDLE_MSG(handle, WM_GETMINMAXINFO, onMainWindowGetMinMaxInfo);
        HANDLE_MSG(handle, WM_MEASUREITEM, onMainWindowMeasureItem);
        //HANDLE_MSG(handle, WM_NOTIFY, onMainWindowNotify);
        //case WM_NOTIFY: {

        //    LPNMHDR notifyStruct = reinterpret_cast<LPNMHDR>(lParam); 
        //    LPNMTBCUSTOMDRAW toolbarDrawStruct = reinterpret_cast<
        //        LPNMTBCUSTOMDRAW>(notifyStruct);
        //    LPNMTOOLBARW toolbarNotif = reinterpret_cast<
        //        LPNMTOOLBARW>(notifyStruct);

        //    switch (notifyStruct->code) {
        //        case NM_CUSTOMDRAW: {

        //            switch (toolbarDrawStruct->nmcd.dwDrawStage) {

        //                case CDDS_PREPAINT: {

        //                    toolbarDrawStruct->clrText = 0xF1F1F1;
        //                    return CDRF_NOTIFYITEMDRAW;

        //                }

        //                case CDDS_ITEMPREPAINT: {

        //                    toolbarDrawStruct->clrText = 0xF1F1F1;
        //                    return CDRF_NEWFONT;

        //                }

        //            }

        //            break;

        //        }
        //        case TBN_DROPDOWN: {

        //            switch (toolbarNotif->iItem) {
        //                default: {
        //                    break;
        //                }
        //            }
        //            break;

        //        }
        //        default: {

        //            break;

        //        }
        //    }

        //    break;

        //}
        case WM_PAINT: {
            PAINTSTRUCT paintStruct;
            mainWindow.mainHDC = ::BeginPaint(handle, &paintStruct);
            ::EndPaint(handle, &paintStruct);
            break;
        }
        case WM_SIZE: {
            const int captionAreaDivider = 22;

            RECT mainWinClient;
            ::GetClientRect(handle, &mainWinClient);
            ::MoveWindow(mainMenu, 0, 0, mainWinClient.right -
                mainMenu.GetWidth(), mainWinClient.bottom, TRUE);
            ::MoveWindow(editContextualBar, 0, mainFileToolbar.GetHeight(),
                mainWinClient.right, editContextualBar.GetHeight(), TRUE);
            ::MoveWindow(mainFileToolbar,
                mainWinClient.right - mainFileToolbar.GetWidth(),
                0, mainWinClient.right, mainWinClient.bottom, TRUE);
            ::MoveWindow(mainStatusBar, 0, (mainWinClient.bottom +
                mainStatusBar.GetHeight()), mainWinClient.right,
                mainStatusBar.GetHeight(), TRUE);
            ::MoveWindow(toolPanel, 0, mainMenu.GetHeight() +
                editContextualBar.GetHeight() + captionAreaDivider,
                0, toolPanel.GetHeight(), TRUE);
            const int bottomTabArea = mainStatusBar.GetHeight(); //Replace later with tab control edminsions
            ::MoveWindow(leftMargin, toolPanel.GetWidth(),
                (mainFileToolbar.GetHeight() + editContextualBar.GetHeight() + captionAreaDivider),
                captionAreaDivider,
                mainWinClient.bottom - (mainStatusBar.GetHeight() +
                mainFileToolbar.GetHeight() + editContextualBar.GetHeight() +
                bottomTabArea + captionAreaDivider),
                TRUE);

            const int rightTabArea = toolPanel.GetWidth(); //Replace later with tab control demintions

            editorConfines.top = (mainFileToolbar.GetHeight() +
                editContextualBar.GetHeight() + captionAreaDivider);
            editorConfines.bottom = mainWinClient.bottom - (mainStatusBar.GetHeight() +
                bottomTabArea + captionAreaDivider);
            editorConfines.left = toolPanel.GetWidth() + captionAreaDivider;
            editorConfines.right = (mainWinClient.right - rightTabArea -
                captionAreaDivider);
            ::MoveWindow(editorPanel, editorConfines.left, editorConfines.top,
                editorConfines.right - editorConfines.left,
                editorConfines.bottom - editorConfines.top, TRUE);

            ::MoveWindow(mainHorzScroll, toolPanel.GetWidth(),
                (mainWinClient.bottom - (mainStatusBar.GetHeight() * 2 +
                captionAreaDivider)), mainWinClient.right -
                (rightTabArea +  toolPanel.GetWidth() +
                captionAreaDivider), captionAreaDivider, TRUE);
            ::MoveWindow(mainVertScroll, (mainWinClient.right - rightTabArea -
                captionAreaDivider), editorConfines.top, captionAreaDivider,
                mainWinClient.bottom - (mainStatusBar.GetHeight() +
                mainFileToolbar.GetHeight() + editContextualBar.GetHeight() +
                bottomTabArea + captionAreaDivider), TRUE);

            break;

        }
        default:
            return ::DefWindowProcW(handle, message, wParam, lParam);
    }
    return 0;

}

void onMainWindowClose(HWND handle) {

    int closeDlgResult = ::DialogBoxW(reinterpret_cast<HINSTANCE>(
        ::GetWindowLongPtrW(handle, GWLP_HINSTANCE)),
        MAKEINTRESOURCEW(IDD_CLOSE), handle, (DLGPROC)CloseDialogProc);

    switch (closeDlgResult) {
        case IDYES: {
            ::SendMessageW(handle, IDM_FILE_SAVE, 0, 0);
        }
        case IDNO: {
            ::SendMessageW(handle, WM_DESTROY, 0, 0);
            break;
        }
    }

}

void onMainWindowCommand(HWND handle, int itemID, HWND ctrl,
    unsigned int ctrlNotifyCode) {

    HINSTANCE instance = reinterpret_cast<HINSTANCE>(::GetWindowLongPtrW(
        handle, GWLP_HINSTANCE));

    switch (itemID/*LOWORD(wParam)*/) {
        case IDM_FILE_OPEN: {

            break;
        }
        case IDM_HELP: {
            DialogBoxW(instance, MAKEINTRESOURCEW(IDD_ABOUTPROGRAM),
                handle, (DLGPROC)AboutDialogProc);
            break;
        }
    }
    switch (ctrlNotifyCode/*HIWORD(wParam)*/) {
        default:
            break;
    }

}

void onMainWindowDestroy (HWND handle) {

    ::PostQuitMessage(0);

}

void onMainWindowDrawItem(HWND handle, const DRAWITEMSTRUCT* drawItem) {



}

void onMainWindowMeasureItem (HWND handle, MEASUREITEMSTRUCT* itemMeasure) {

    switch (itemMeasure->CtlType) {
        default: {
            break;
        }
    }

}

void onMainWindowGetMinMaxInfo (HWND handle, MINMAXINFO* dimensionsDefault) {

    dimensionsDefault->ptMinTrackSize.x = 400;
    dimensionsDefault->ptMinTrackSize.y = 300;

}

//LRESULT onMainWindowNotify(HWND handle, int ctrlID, NMHDR* notifyStruct) {
//
//    switch (notifyStruct->code) {
//        case NM_CUSTOMDRAW: {
//            /*Draw stages*/
//            break;
//        }
//        case TBN_DROPDOWN: {
//            LPNMTOOLBARW toolbarNotif = reinterpret_cast<
//                LPNMTOOLBARW>(notifyStruct);
//            switch (toolbarNotif->iItem) {
//                default: {
//                    break;
//                }
//            }
//            break;
//        }
//        default: {
//            break;
//        }
//    }
//    return 0;
//
//}

//void onMainWindowPaint(HWND handle) {
//
//    PAINTSTRUCT paintStruct;
//    mainWindow.mainHDC = ::BeginPaint(handle, &paintStruct);
//    ::FillRect(mainWindow.mainHDC, &editorConfines);
//    ::EndPaint(handle, &paintStruct);
//
//}