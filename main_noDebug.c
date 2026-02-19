#define WIN32_LEAN_AND_MEAN
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

#include <windows.h>
#include <stdio.h>
#include <stdarg.h>
#include <strsafe.h>
#include <commctrl.h>


enum {
	ID_BTN_TEST = 1001,
	ID_BTN_FarmerBlockInc = 1002,
	ID_BTN_FarmerBlockDec = 1003,

	ID_FRM_SetHousingFrame = 2001,
	ID_FRM_AdjustHousingFrame = 2002,
	ID_FRM_ResourceReqFrame = 2003,

	ID_FLD_HousingWidth = 3001,
	ID_FLD_HousingLength = 3002,

	ID_LBL_HousingWidth = 4001,
	ID_LBL_HousingLength = 4002,

	ID_SPN_HousingWidth = 5001,
	ID_SPN_HousingLength = 5002,

	ID_DSP_Fish = 6001,
	ID_DSP_Clothes = 6002,
	ID_DSP_Schnnaps = 6003
};


static HINSTANCE g_hInstance = NULL;


static const wchar_t *g_mainClassName = L"Anno1800OverlayClass";


/* Forward Prototype for the main function, so that it can be referenced prior to initialization.
 *
 * HWND hwnd : handle to the window reciving the message
 * UINT msg : numeric message ID
 * WPARAM wParam : message-specific "word parameter" (pointer-sized)
 * LPARAM lParam : message-specific "long parameter" (pointer-sized)
 */
static LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);


/* Defines a struct that contains the decoded information from a Windows Command.
 *
 * controlId : which control (button) triggered the command.
 * notifyCode : what happened (clicked, double clicked, focus, etc.)
 * controlHwnd : the handle of the control window itself.
 */
typedef struct CommandInfo{
	int controlId;
	int notifyCode;
	HWND controlHwnd;
} CommandInfo;

typedef struct buddyInfo{
	HWND buddyHWND;
	int minVal;
	int maxVal;
	int initialVal;
} BuddyInfo;

/* When Windows creates/sends a command it stres the information for the command in WPARAM and LPARAM.
 * The DecodeWmCommand takes these two parameters, extracts the information and then stores it in the 
 * CommandInfo stuct.
 *
 * WPARAM contains two 16-bit values:
 * 				lowWord = the control ID
 * 				high word = notification code
 * 	LOWORD(x) : extracts the lower 16 bits.
 * 	HIWORD(x) : extracts the upper 16 bits.
 *
 * LPARAM contains the info for the main window handle
 *
 * casts:
 * 	(int) : the macros yeild an integer type and so i want "int"
 * 	(HWND)lParam : for control notifications, lParam holds the control window handle.
 */
static CommandInfo DecodeWmCommand(WPARAM wParam, LPARAM lParam){
	CommandInfo info;
	info.controlId  = (int)LOWORD(wParam);
	info.notifyCode = (int)HIWORD(wParam);
	info.controlHwnd = (HWND)lParam;
	return info;
}


/* Registers the main window with the Windows OS so that the OS knows how to create the window.
 *
 * BOOL : Win32's integer boolean type (TRUE/FALSE)
 * WNDCLASSEXW : the "extended window class" struct (wide version)
 * ZeroMemory(&wc, sizeof(wc)) : sets all bytes of the struct to 0 before setting fields to prevent "random uninitialized fields".
 * 
 * wc.cbSize : size of the struct; Windows uses this to know which version/size is being passed.
 * wc.lpfnWndProc : pointer to the window procedure function (must match the signature)
 * wc.hInstance : the module instance handle
 * wc.hCursor : the cursor used when mouse is inside the window space.
 * 		>LoadCursor(NULL, IDC_ARROW) : creates the actual cursor resource to be used.
 * 			NULL : a NULL instance here means "use the system cursor resources"
 * 			IDC_ARROW : the standard cursor identifier
 * wc.hbrBackground : stores the settings for how the OS actually displays the window on the screen.
 * 		>(HBRUSH)(COLOR_WINDOW + 1) : the settings themselves
 * 			(HBRUSH) : Win32 Handle type for a "brush" (how the window is drawn)
 * 			(COLOR_WINDOW + 1) : the "system color index" for the window background color
 * wc.lpszClassName : the class name to be used when actually created the main window.
 */
static BOOL RegisterMainWindowClass(HINSTANCE hInstance){

	WNDCLASSEXW wc;
	ZeroMemory(&wc, sizeof(wc));

	wc.cbSize	= sizeof(wc);
	wc.lpfnWndProc	= MainWndProc;
	wc.hInstance	= hInstance;
	wc.hCursor	= LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground= (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszClassName= g_mainClassName;

	if (RegisterClassExW(&wc) == 0){
		return FALSE;
	}
	return TRUE;
}


/* The function that is used to create the buttons inside of the main window. Returns the handle to
 * the parent window (HWND) or NULL if button creation failed.
 *
 * HWND parent : the parent window to the button (usually main window)
 * int controlId : the numeric id to identify the button. (used with WM_COMMAND)
 * text : The label on the button itself
 * int x : the x-axis coordinate for the button origin (top left corner)
 * int y : the y-axis coordinate for the button origin (top left corner)
 * int width : the width of the button itself
 * int height : the height of the button itself
 */
static HWND CreateButton(HWND parent, int controlId, const wchar_t *text, int x, int y, int width, int height, BuddyInfo *buddy){
	
	/* Int the CreateWindowExW function, the parameter HMENU is used differently depending on window type;
	 * 	>For a top-level window, HMENU is its menu handle.
	 * 	>for a child-level window, Win32 overloads the field to carry the control ID
	 * Therefore, "int controlID" is converted into an HMENU-typed value.
	 * INT_PTR : iteger type the size of a pointer (safe on 32/64-bit)
	 */
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

	
	HWND button = CreateWindowExW(
	
	/*"dwExStyle   = */ 0,					
	/*"lpClassName = */ class, //macro
	/*"lpWindowName= */ text,
	/*"dwStyle     = */ style, //macro
	/*"x           = */ x,
	/*"y           = */ y,
	/*"width       = */ width,
	/*"height      = */ height,
	/*"hwndParent  = */ parent,
	/*"hMenu       = */ idAsMenuHandle,
	/*"hInstance   = */ g_hInstance,
	/*"lpParam     = */ NULL
	);

	if (buddy){
		SendMessageW(button, UDM_SETBUDDY, (WPARAM)buddy->buddyHWND, 0);
		SendMessageW(button, UDM_SETRANGE32, (WPARAM)buddy->minVal, (LPARAM)buddy->maxVal);
		SendMessageW(button, UDM_SETPOS32, 0, (LPARAM)buddy->initialVal);
	}

	return button;
}


static HWND CreateMainWindow(HINSTANCE hInstance){

	return CreateWindowExW(

	/*"dwExStyle   =*/ 0,
	/*"lpClassName =*/ g_mainClassName,
	/*"lpWindowName=*/ L"Anno 1800 Ingame Overlay",
	/*"dwStyle     =*/ WS_OVERLAPPEDWINDOW,
	/*"x	       =*/ CW_USEDEFAULT,
	/*"y	       =*/ CW_USEDEFAULT,
	/*"width       =*/ 380,
	/*"height      =*/ 430,
	/*"hwndParent  =*/ NULL,
	/*"hMenu       =*/ NULL,
	/*"hInstance   =*/ hInstance,
	/*"lpParam     =*/ NULL
			);
}


/* The event handler for the main window. Whenever an action/event happens inside the window it calls this function.
 */
static LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
	
	switch(msg){

		
		//This msg indicates that a window needs to be created
		case WM_CREATE:{
			
			/*HWND hwnd_ = CreateButton(*/
                        /*"HWND parent        ="*/ 
                        /*"int controlId      ="*/ 
                        /*"const wchar_t *text="*/ 
                        /*"int x              ="*/ 
                        /*"int y              ="*/ 
                        /*"int width          ="*/ 
                        /*"int height         ="*/ 
                        /*"BuddyInfo *buddy   ="*/

			/* HWND parent : hwnd
			 * int controlId : ID_BTN_TEST
			 * const wchar_t *text : L"Test Button"
			 * int x : 20
			 * int y : 20
			 * int width : 100
			 * int height : 32
			 */
			//CreateButton(hwnd, ID_BTN_TEST, L"Test Button", 20, 20, 120, 32, NULL);
			
			HWND hwnd_SetHousingFrame = CreateButton(
			/*"HWND parent        ="*/ hwnd, 
			/*"int controlId      ="*/ ID_FRM_SetHousingFrame, 
			/*"const wchar_t *text="*/ NULL, 
			/*"int x 	      ="*/ 15, 
			/*"int y 	      ="*/ 10, 
			/*"int width 	      ="*/ 110, 
			/*"int height 	      ="*/ 90,//100 
			/*"BuddyInfo *buddy   ="*/ NULL);
			
			HWND hwnd_AdjustHousingFrame = CreateButton(
                        /*"HWND parent        ="*/ hwnd,
                        /*"int controlId      ="*/ ID_FRM_AdjustHousingFrame,
                        /*"const wchar_t *text="*/ NULL,
                        /*"int x              ="*/ 15,
                        /*"int y              ="*/ 110,
                        /*"int width          ="*/ 330,
                        /*"int height         ="*/ 120,//230
                        /*"BuddyInfo *buddy   ="*/ NULL);

			HWND hwnd_ResourceReqFrame = CreateButton(
                        /*"HWND parent        ="*/ hwnd,
                        /*"int controlId      ="*/ ID_FRM_ResourceReqFrame,
                        /*"const wchar_t *text="*/ NULL,
                        /*"int x              ="*/ 15,
                        /*"int y              ="*/ 240,
                        /*"int width          ="*/ 330,
                        /*"int height         ="*/ 120,//360
                        /*"BuddyInfo *buddy   ="*/ NULL);





			/*HWND hwnd_FarmerBlockInc = */CreateButton(
                        /*"HWND parent        ="*/ hwnd_AdjustHousingFrame,
                        /*"int controlId      ="*/ ID_BTN_FarmerBlockInc,
                        /*"const wchar_t *text="*/ L"Farmer Block\r\n+1",
                        /*"int x              ="*/ 10,
                        /*"int y              ="*/ 20,
                        /*"int width          ="*/ 100,
                        /*"int height         ="*/ 40,
                        /*"BuddyInfo *buddy   ="*/ NULL);

			/*HWND hwnd_FarmerBlockDec = */CreateButton(
                        /*"HWND parent        ="*/ hwnd_AdjustHousingFrame,
                        /*"int controlId      ="*/ ID_BTN_FarmerBlockDec,
                        /*"const wchar_t *text="*/ L"Farmer Block\r\n-1",
                        /*"int x              ="*/ 10,
                        /*"int y              ="*/ 60,
                        /*"int width          ="*/ 100,
                        /*"int height         ="*/ 40,
                        /*"BuddyInfo *buddy   ="*/ NULL);
			
			
			

			HWND hwnd_HousingWidth = CreateButton(
			/*"HWND parent        ="*/ hwnd_SetHousingFrame, 
			/*"int controlId      ="*/ ID_FLD_HousingWidth,
        		/*"const wchar_t *text="*/ L"Width",
			/*"int x              ="*/ 15,
                        /*"int y              ="*/ 40,
                        /*"int width          ="*/ 30,
                        /*"int height         ="*/ 20,
                        /*"BuddyInfo *buddy   ="*/ NULL);


			HWND hwnd_HousingLength = CreateButton(
	      		/*"HWND parent        ="*/ hwnd_SetHousingFrame,
                        /*"int controlId      ="*/ ID_FLD_HousingLength,
                        /*"const wchar_t *text="*/ L"Length",
                        /*"int x              ="*/ 65,
                        /*"int y              ="*/ 40,
                        /*"int width          ="*/ 30,
                        /*"int height         ="*/ 20,
                        /*"BuddyInfo *buddy   ="*/ NULL);





                        BuddyInfo SPN_HousingWidth;

			SPN_HousingWidth.buddyHWND = hwnd_HousingWidth;
			SPN_HousingWidth.minVal = 1;
			SPN_HousingWidth.maxVal = 2;
			SPN_HousingWidth.initialVal = 1;
	
			/*HWND hwnd_HousingWidthSPN = */CreateButton(
	                /*"HWND parent        ="*/ hwnd_SetHousingFrame,
                        /*"int controlId      ="*/ ID_SPN_HousingWidth,
                        /*"const wchar_t *text="*/ NULL,
                        /*"int x              ="*/ 20,
                        /*"int y              ="*/ 60,
                        /*"int width          ="*/ 50,
                        /*"int height         ="*/ 20,
                        /*"BuddyInfo *buddy   ="*/ &SPN_HousingWidth);


			BuddyInfo SPN_HousingLength;

			SPN_HousingLength.buddyHWND = hwnd_HousingLength;
			SPN_HousingLength.minVal = 1;
			SPN_HousingLength.maxVal = 12;
			SPN_HousingLength.initialVal = 8;

			/*HWND hwnd_HousingLengthSPN = */CreateButton(
                        /*"HWND parent        ="*/ hwnd_SetHousingFrame,
                        /*"int controlId      ="*/ ID_SPN_HousingLength,
                        /*"const wchar_t *text="*/ NULL,
                        /*"int x              ="*/ 70,
                        /*"int y              ="*/ 60,
                        /*"int width          ="*/ 50,
                        /*"int height         ="*/ 20,
                        /*"BuddyInfo *buddy   ="*/ &SPN_HousingLength);




			
			/*HWND hwnd_HousingWidthLBL = */CreateButton(
			/*"HWND parent        ="*/ hwnd_SetHousingFrame,
                        /*"int controlId      ="*/ ID_LBL_HousingWidth,
                        /*"const wchar_t *text="*/ L"Width",
                        /*"int x              ="*/ 10,
                        /*"int y              ="*/ 20,
                        /*"int width          ="*/ 40,
                        /*"int height         ="*/ 20,
                        /*"BuddyInfo *buddy   ="*/ NULL);
			
			
			/*HWND hwnd_HousingLengthLBL = */CreateButton(
                        /*"HWND parent        ="*/ hwnd_SetHousingFrame,
                        /*"int controlId      ="*/ ID_LBL_HousingLength,
                        /*"const wchar_t *text="*/ L"Length",
                        /*"int x              ="*/ 60,
                        /*"int y              ="*/ 20,
                        /*"int width          ="*/ 45,
                        /*"int height         ="*/ 20,
                        /*"BuddyInfo *buddy   ="*/ NULL);






 		        /*HWND hwnd_Fish = */CreateButton(
                        /*"HWND parent        ="*/ hwnd_ResourceReqFrame,
                        /*"int controlId      ="*/ ID_DSP_Fish,
                        /*"const wchar_t *text="*/ L"Required Fish:",
                        /*"int x              ="*/ 10,
                        /*"int y              ="*/ 20,
                        /*"int width          ="*/ 100,//110
                        /*"int height         ="*/ 40,
                        /*"BuddyInfo *buddy   ="*/ NULL);

			/*HWND hwnd_Clothes = */CreateButton(
                        /*"HWND parent        ="*/ hwnd_ResourceReqFrame,
                        /*"int controlId      ="*/ ID_DSP_Clothes,
                        /*"const wchar_t *text="*/ L"Required Clothes:",
                        /*"int x              ="*/ 115,
                        /*"int y              ="*/ 20,
                        /*"int width          ="*/ 100,//215
                        /*"int height         ="*/ 40,
                        /*"BuddyInfo *buddy   ="*/ NULL);
			
			/*HWND hwnd_Schnnaps = */CreateButton(
                        /*"HWND parent        ="*/ hwnd_ResourceReqFrame,
                        /*"int controlId      ="*/ ID_DSP_Schnnaps,
                        /*"const wchar_t *text="*/ L"Required Fish:",
                        /*"int x              ="*/ 220,
                        /*"int y              ="*/ 20,
                        /*"int width          ="*/ 100,//320
                        /*"int height         ="*/ 40,
                        /*"BuddyInfo *buddy   ="*/ NULL);

			return 0;
		}
		

		case WM_COMMAND:{
			
			/* ci.controlId   = (int)LOWORD(wParam)
			 * ci.notifyCode  = (int)HIWORD(wParam)
			 * ci.controlHwnd = (HWND)lParam
			 */
			CommandInfo ci = DecodeWmCommand(wParam, lParam);
			
			if (ci.notifyCode == BN_CLICKED){
	
				if (ci.controlId == ID_BTN_TEST){
					MessageBoxW(hwnd, L"Test Sucsessful", L"Test Notification", MB_OK | MB_ICONINFORMATION);
					return 0;
				}
			}	
			break;
		}

		case WM_DESTROY: {
			PostQuitMessage(0);
			return 0;
		}
	}
	
	/* If a message is not handled this line impliments normal window behaviors.
	 */
	return DefWindowProcW(hwnd, msg, wParam, lParam);
}


/* "Main" function equivelent (GUI subsystem Windows aps traditionally use WinMain instead of main)
 *
 * HINSTANCE hInstance : The main windows instance handle
 * HINSTANCE hPrevInstance : legacy parameter, no meaning
 * LPSTR lpCmdLine : command line as ANSI string (not included in program name
 * ind nCmdShow : how windows suggests the window is shown (normal, minimized, etc)
 */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	
	//intentionally use variables to silence unused parameter warnings.
	(void)hPrevInstance;
	(void)lpCmdLine;

	//Stores hInstance as a global variable.
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


