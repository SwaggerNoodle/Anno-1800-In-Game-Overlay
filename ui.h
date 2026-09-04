#ifndef UI_H
#define UI_H

#include "dataStructs.h"

void CreateUiFrames(HINSTANCE hInstance, HWND hwnd, OverlayState *overlay);

void CreateUiButtons(HINSTANCE hInstance, HWND hwnd, OverlayState *overlay);

void CreateUiFields(HINSTANCE hInstance, HWND hwnd, OverlayState *overlay);

void CreateUiLabels(HINSTANCE hInstance, HWND hwnd, OverlayState *overlay);

void CreateUiSpinners(HINSTANCE hInstance, HWND hwnd, OverlayState *overlay);

void CreateUiDisplays(HINSTANCE hInstance, HWND hwnd, OverlayState *overlay);

#endif
