#ifndef HELPERS_H
#define HELPERS_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <commctrl.h>

#include "dataStructs.h"

#define PUSHBUTTON (WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_MULTILINE | BS_CENTER | BS_VCENTER)
#define FRAMEBUTTON (WS_CHILD | WS_VISIBLE | BS_GROUPBOX)
#define TEXTFIELD (WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER | ES_AUTOHSCROLL)
#define STATICLABEL (WS_CHILD | WS_VISIBLE)
#define SPINNERBUTTON (WS_CHILD | WS_VISIBLE | UDS_SETBUDDYINT | UDS_ARROWKEYS | UDS_NOTHOUSANDS)
#define DISPLAY (WS_CHILD | WS_VISIBLE | WS_BORDER | SS_SUNKEN)

#define BUTTON (L"BUTTON")
#define EDIT (L"EDIT")
#define STATIC (L"STATIC")
#define SPINNER (UPDOWN_CLASSW)



/*This function extracts the informaion from a windows command, and stores the info in a usable fomat
inside of a struct called a CommandInfo, which it then returns.*/
CommandInfo DecodeWmCommand(WPARAM wParam, LPARAM lParam);


/*This function is used to create each of the UI components in the program.*/
HWND CreateUiComponent(HINSTANCE hInstance, HWND parent, int controlId, const wchar_t *windowName, int x, int y, int width, int height, SpinnerConfig *configData);

#endif


