#pragma once
#ifndef H_PROTOTYPES_H
#define H_PROTOTYPES_H

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include "Window_c.h"

LRESULT _stdcall MainProcedure(HWND handle, unsigned int message,
    WPARAM wParam, LPARAM lParam);
LRESULT _stdcall EditorWinProc(HWND handle, unsigned int message,
    WPARAM wParam, LPARAM lParam);
BOOL _stdcall CloseDialogProc(HWND handle, unsigned int message,
    WPARAM wParam, LPARAM lParam);
BOOL _stdcall AboutDialogProc(HWND handle, UINT message,
    WPARAM wParam, LPARAM lParam);
void onMainWindowClose(HWND handle);
void onMainWindowCommand(HWND handle, int itemID, HWND ctrl,
    unsigned int ctrlNotifyCode);
BOOL onMainWindowCreate(HWND handle, CREATESTRUCT* createStr);
void onMainWindowDestroy(HWND handle);
void onMainWindowDrawItem(HWND handle, const DRAWITEMSTRUCT* drawItem);
void onMainWindowGetMinMaxInfo(HWND handle, MINMAXINFO* dimensionsDefault);
void onMainWindowMeasureItem(HWND handle, MEASUREITEMSTRUCT* itemMeasure);
LRESULT onMainWindowNotify(HWND handle, int ctrlID, NMHDR* notifyStruct);
void onMainWindowPaint(HWND handle);

static Window mainWindow;
static Window editorPanel;

#endif
