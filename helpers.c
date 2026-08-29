#include "helpers.h"

CommandInfo DecodeWmCommand(WPARAM wParam, LPARAM lParam){
	CommandInfo info;

	info.controlId = (int)LOWORD(wParam);
	info.notifyCode = (int)HIWORD(wParam);
	info.controlHandle = (HWND)lParam;

	return info;
}

HWND CreateUiComponent(HINSTANCE g_hInstance, HWND parent, int controlId, const wchar_t *windowName, int x, int y, int width, int height, SpinnerConfig *configData){

	HMENU idAsMenuHandle = (HMENU)(INT_PTR)controlId;
	DWORD style = 0;
	LPCWSTR class = NULL;

	if (controlId < 2000){
		style = PUSHBUTTON;
		class = BUTTON;
	}
	else if (controlId < 3000){
		style = FRAMEBUTTON;
		class = BUTTON;
	}
	else if (controlId < 4000){
		style = TEXTFIELD;
		class = EDIT;
	}
	else if (controlId < 5000){
		style = STATICLABEL;
		class = STATIC;
	}
	else if (controlId < 6000){
		style = SPINNERBUTTON;
		class = SPINNER;
	}
	else if (controlId < 7000){
		style = DISPLAY;
		class = STATIC;
	}
	
	HWND component = CreateWindowExW(0,
					 class,
					 windowName,
					 style,
					 x, y,
					 width, height,
					 parent,
					 idAsMenuHandle,
					 g_hInstance,
					 NULL
	);

	if (component && configData){
		SendMessageW(component, UDM_SETBUDDY, (WPARAM)configData->childHWND, 0);
		SendMessageW(component, UDM_SETRANGE32, (WPARAM)configData->minVal, (LPARAM)configData->maxVal);
		SendMessageW(component, UDM_SETPOS32, 0, (LPARAM)configData->initialVal);
	}
	return component;
}























