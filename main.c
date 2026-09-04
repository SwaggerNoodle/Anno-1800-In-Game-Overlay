#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <stdlib.h>
#include <commctrl.h>

#include "helpers.h"
#include "dataStructs.h"
#include "ui.h"
#include "mathFunctions.h"



/*Globals*/
static HINSTANCE g_hInstance = NULL;
static const wchar_t *g_mainClassName = L"Anno1800OverlayClass";
static OverlayState overlay = {0};
/*Forward Declarations*/
static LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);




/*Registers main window with the OS so that it knows how to create the window.*/
static BOOL RegisterMainWindowClass(HINSTANCE hInstance){
	
	//WNDCLASSEXW = WindowClassExtendedWide
	WNDCLASSEXW wc;
	ZeroMemory(&wc, sizeof(wc));

	wc.cbSize 	 = sizeof(wc);
	wc.lpfnWndProc 	 = MainWndProc;
	wc.hInstance 	 = hInstance;
	wc.hCursor 	 = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszClassName = g_mainClassName;

	if (RegisterClassExW(&wc) == 0){
		return FALSE;
	}
	return TRUE;
}




/*Function to actually create the main program window*/
static HWND CreateMainWindow(HINSTANCE hInstance){

	DWORD exStyle = WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TOOLWINDOW;
	DWORD style = WS_POPUP;
	
	HWND hwnd = CreateWindowExW(exStyle,
				    g_mainClassName,
				    L"Anno 1800 In Game Overlay",
				    style,
				    100,
				    100,
				    380,
				    430,
				    NULL,
				    NULL,
				    hInstance,
				    NULL
	);

	if (hwnd){
		SetLayeredWindowAttributes(hwnd, 0, 230, LWA_ALPHA);
	}
	return hwnd;
}




static LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
	switch(msg){


		case WM_CREATE:
		
			CreateUiFrames(g_hInstance, hwnd, &overlay);
			CreateUiButtons(g_hInstance, hwnd, &overlay);
			CreateUiFields(g_hInstance, hwnd, &overlay);
			CreateUiLabels(g_hInstance, hwnd, &overlay);
			CreateUiSpinners(g_hInstance, hwnd, &overlay);
			CreateUiDisplays(g_hInstance, hwnd, &overlay);

			return 0;



		case WM_COMMAND:
			
			CommandInfo ci = DecodeWmCommand(wParam, lParam);
			if (ci.notifyCode == BN_CLICKED){
				if (ci.controlId == ID_BTN_Close){
					DestroyWindow(hwnd);
					return 0;
				}
				else if(ci.controlId == ID_BTN_CapitalIslandSel){
					overlay.data.currentIsland = 0;
					RecalculateBlockSize(&overlay.data.capital, &overlay.ui);
                                        RecalculateDisplayValues(&overlay.data.capital, &overlay.ui);
				}
				else if(ci.controlId == ID_BTN_Island1Sel){
					overlay.data.currentIsland = 1;
					RecalculateBlockSize(&overlay.data.island1, &overlay.ui);
                                        RecalculateDisplayValues(&overlay.data.island1, &overlay.ui);
				}
				else if(ci.controlId == ID_BTN_Island2Sel){
					overlay.data.currentIsland = 2;
					RecalculateBlockSize(&overlay.data.island2, &overlay.ui);
                                        RecalculateDisplayValues(&overlay.data.island2, &overlay.ui);
				}
				else if(ci.controlId == ID_BTN_Island3Sel){
					overlay.data.currentIsland = 3;
					RecalculateBlockSize(&overlay.data.island3, &overlay.ui);
                                        RecalculateDisplayValues(&overlay.data.island3, &overlay.ui);

				}
				else {
					switch(overlay.data.currentIsland){
						case 1:
							RecalculateBlockSize(&overlay.data.island1, &overlay.ui);
							ButtonClicked(ci.controlId, &overlay.data.island1);
                                        		RecalculateDisplayValues(&overlay.data.island1, &overlay.ui);
							break;
						case 2:
							RecalculateBlockSize(&overlay.data.island2, &overlay.ui);
							ButtonClicked(ci.controlId, &overlay.data.island2);
							RecalculateDisplayValues(&overlay.data.island2, &overlay.ui);
							break;
						case 3:
							RecalculateBlockSize(&overlay.data.island3, &overlay.ui);
							ButtonClicked(ci.controlId, &overlay.data.island3);
		                                        RecalculateDisplayValues(&overlay.data.island3, &overlay.ui);
							break;
						default:
							RecalculateBlockSize(&overlay.data.capital, &overlay.ui);
							ButtonClicked(ci.controlId, &overlay.data.capital);
		                                        RecalculateDisplayValues(&overlay.data.capital, &overlay.ui);
							break;
					}
				}

			}
			
			return 0;



		case WM_NCHITTEST:
			
			LRESULT hit = DefWindowProcW(hwnd, msg, wParam, lParam);

			if (hit == HTCLIENT){
				POINT pt;
				pt.x = GET_X_LPARAM(lParam);
				pt.y = GET_Y_LPARAM(lParam);
	
				ScreenToClient(hwnd, &pt);

				if (pt.y >= 0 && pt.y < 10){
					return HTCAPTION;
				}
			}
			return hit;



		case WM_DESTROY:
			
			PostQuitMessage(0);
			return 0;
	}
	return DefWindowProcW(hwnd, msg, wParam, lParam);
}




					      				 






int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){

	(void)hPrevInstance;
	(void)lpCmdLine;

	g_hInstance = hInstance;	

	INITCOMMONCONTROLSEX icc;
	ZeroMemory(&icc, sizeof(icc));
	icc.dwSize = sizeof(icc);
	icc.dwICC = ICC_UPDOWN_CLASS;
	InitCommonControlsEx(&icc);

	if (!RegisterMainWindowClass(hInstance)){
		return 0;
	}

	HWND hwnd = CreateMainWindow(hInstance);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	MSG msg;

	while(1){

		int ret = GetMessage(&msg, NULL, 0, 0);

		if (ret > 0){
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
		else{
			break;
		}
	}
	return (int)msg.wParam;
}








































