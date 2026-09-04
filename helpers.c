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
		style = FRAMEBUTTON;
		class = BUTTON;
	}
	else if (controlId < 3000){
		style = PUSHBUTTON;
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

void ButtonClicked(int ButtonID, IslandData *island){
	
	switch(ButtonID){
		case ID_BTN_FarmerBlockInc:
			island->islandPopulation.farmerHCount += island->islandBlockSize.houseNum;
			break;
		case ID_BTN_FarmerBlockDec:
			island->islandPopulation.farmerHCount -= island->islandBlockSize.houseNum;
			break;
		case ID_BTN_WorkerBlockInc:
			island->islandPopulation.workerHCount += island->islandBlockSize.houseNum;
			island->islandPopulation.farmerHCount -= island->islandBlockSize.houseNum;
			break;
		case ID_BTN_WorkerBlockDec:
			island->islandPopulation.workerHCount -= island->islandBlockSize.houseNum;
			break;
		default:
			break;
	}
}

void SetDisplay(HWND display, const wchar_t *label, int value){

	wchar_t text[128];

	StringCchPrintfW(text,
			 128,
			 L"%s\r\n%d",
			 label,
			 value);

	SetWindowTextW(display, text);
}

int GetValueFromSpinner(HWND spinnerHandle){

	wchar_t buffer[32];

	GetWindowTextW(spinnerHandle, buffer, 32);

	int value = _wtoi(buffer);

	return value;
}


















