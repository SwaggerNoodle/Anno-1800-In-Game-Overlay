#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <stdlib.h>
#include <commctrl.h>

#include "helpers.h"
#include "dataStructs.h"




/*Globals*/
static HINSTANCE g_hInstance = NULL;
static const wchar_t *g_mainClassName = L"Anno1800OverlayClass";
static AppData mainData;
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

		case WM_CREATE:{


			      HWND hwnd_SetHousingFrame = CreateUiComponent(g_hInstance,
					      				    hwnd,
					     				    ID_FRM_SetHousingFrame,
									    NULL,
									    15,
									    10,
									    110,
									    90,
									    NULL);
			      HWND hwnd_AdjustHousingFrame = CreateUiComponent(g_hInstance,
					      				       hwnd,
					       				       ID_FRM_AdjustHousingFrame,
									       NULL,
									       15,
									       110,
									       330,
									       120,
									       NULL);
			      HWND hwnd_ResourceReqFrame = CreateUiComponent(g_hInstance,
					      				     hwnd,
					      				     ID_FRM_ResourceReqFrame,
									     NULL,
									     15,
									     240,
									     330,
									     120,
									     NULL);


			      HWND hwnd_FarmerBlockInc = CreateUiComponent(g_hInstance,
					      				   hwnd_AdjustHousingFrame,
					      				   ID_BTN_FarmerBlockInc,
									   L"Farmer Block\r\n+1",
									   10,
									   20,
									   100,
									   40,
									   NULL);
			      HWND hwnd_FarmerBlockDec = CreateUiComponent(g_hInstance,
					      				   hwnd_AdjustHousingFrame,
					      				   ID_BTN_FarmerBlockDec,
									   L"Farmer Block\r\n-1",
									   10,
									   60,
									   100,
									   40,
									   NULL);
			      

			      HWND hwnd_HousingWidth = CreateUiComponent(g_hInstance,
					      				 hwnd_SetHousingFrame,
					      				 ID_FLD_HousingWidth,
									 L"Width",
									 15,
									 40,
									 30,
									 20,
									 NULL);
			      HWND hwnd_HousingLength = CreateUiComponent(g_hInstance,
					 				  hwnd_SetHousingFrame,
					      				  ID_FLD_HousingLength,
									  L"Length",
									  65,
									  40,
									  30,
									  20,
									  NULL);



			      SpinnerConfig SPN_HousingWidth;
			      SPN_HousingWidth.childHWND = hwnd_HousingWidth;
			      SPN_HousingWidth.minVal = 1;
			      SPN_HousingWidth.maxVal = 2;
			      SPN_HousingWidth.initialVal = 1;
			      HWND hwnd_HousingWidthSPN = CreateUiComponent(g_hInstance,
					      				    hwnd_SetHousingFrame,
					      				    ID_SPN_HousingWidth,
									    NULL,
									    20,
									    60,
									    50,
									    20,
									    &SPN_HousingWidth);
			      SpinnerConfig SPN_HousingLength;
			      SPN_HousingLength.childHWND = hwnd_HousingLength;
			      SPN_HousingLength.minVal = 1;
			      SPN_HousingLength.maxVal = 12;
			      SPN_HousingLength.initialVal = 8;
			      HWND hwnd_HousingLengthSPN = CreateUiComponent(g_hInstance,
					      				     hwnd_SetHousingFrame,
					      				     ID_SPN_HousingLength,
									     NULL,
									     70,
									     60,
									     50,
									     20,
									     &SPN_HousingLength);



			      HWND hwnd_HousingWidthLBL = CreateUiComponent(g_hInstance,
					      				    hwnd_SetHousingFrame,
					      				    ID_LBL_HousingWidth,
									    L"Width",
									    10,
									    20,
									    40,
									    20,
									    NULL);
			      HWND hwnd_HousingLengthLBL = CreateUiComponent(g_hInstance,
					      				     hwnd_SetHousingFrame,
					      				     ID_LBL_HousingLength,
									     L"Length",
									     60,
									     20,
									     45,
									     20,
									     NULL);
			      HWND hwnd_DragBar = CreateUiComponent(g_hInstance,
					      			    hwnd,
								    ID_LBL_DragBar,
								    NULL,
								    0,
								    0,
								    200,
								    10,
								    NULL);



			      HWND hwnd_Fish = CreateUiComponent(g_hInstance,
					      			 hwnd_ResourceReqFrame,
					      			 ID_DSP_Fish,
								 L"Required Fish",
								 10,
								 20,
								 100,
								 40,
								 NULL);
			      HWND hwnd_Clothes = CreateUiComponent(g_hInstance,
					      			    hwnd_ResourceReqFrame,
					      			    ID_DSP_Clothes,
								    L"Required Clothes",
								    115,
								    20,
								    100,
								    40,
								    NULL);
			      HWND hwnd_Schnnaps = CreateUiComponent(g_hInstance,
					      			     hwnd_ResourceReqFrame,
					      			     ID_DSP_Schnnaps,
								     L"Required Schnnaps",
								     220,
								     20,
								     100,
								     40,
								     NULL);



			      HWND hwnd_CloseWindowBtn = CreateUiComponent(g_hInstance,
					      				   hwnd,
									   ID_BTN_Close,
									   L"X",
									   350,
									   5,
									   25,
									   25,
									   NULL);




			      return 0;
		}

		case WM_COMMAND:{

				CommandInfo ci = DecodeWmCommand(wParam, lParam);

				if (ci.notifyCode == BN_CLICKED){
					if (ci.controlId == ID_BTN_Close){
						DestroyWindow(hwnd);
						return 0;
					}
				}

				else if (ci.notifyCode == EN_CHANGE){
				}

				break;
		}

		case WM_NCHITTEST:{

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
		}

		case WM_DESTROY:{

				PostQuitMessage(0);
				return 0;
		}
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






































