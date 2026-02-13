#define WIN32_LEAN_AND_MEAN 	//Tells windows.h to compile a smaller version of itself 
#define SHOW_CONSOLE 0		//if '1' colsole printing code compiles in, '0' to ommit entirely

#include <windows.h>	//Contains Win32 API declarations
#include <stdio.h>	//Standard C I/O
#include <stdarg.h>	//Contains 'Variadic functions' (functions containing '...' as a parameter)
#include <strsafe.h>	//Microsoft 'Safe String' helpers.


/*
 * Win32 controls usually have an integer ID, and when a control is activated (such as a button click).
 * windows will send a 'WM_COMMAND' with the ID in the message parameters. Forcing button ID's to start
 * at 1000 avoids conflicts with small common ID's
 */
enum {
    ID_BTN_HELLO = 1001,
    ID_BTN_QUIT = 1002,
    ID_BTN_TEST = 1003
};

//initalizes a handle (Kernal pointer) for the OS that represents the program.
static HINSTANCE g_hInstance = NULL;

//Creates the name for the window class so the OS can create the window later
static const wchar_t *g_mainClassName = L"SimpleWin32Class";

/* Forward Prototype for the main function, so that it can be referenced prior to initialization.
 *
 * HWND hwnd : handle to the window receiving the message.
 * UINT msg : numeric message ID (like WM_COMMAND)
 * WPARAM wParam : message-specific "word parameter" (pointer-sized)
 * LPARAM lParam : message-specific "long parameter" (pointer-sized)
 */
static LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);



//helper funtion for the logger, -Go Over Again-
static void Logfw(const wchar_t *fmt, ...) {

	wchar_t buffer[1024];	//This creates a stack array of 1024 "wide" characters to store the final formatted message.

	va_list args;		//declares the interator for going through the ... arguments.
		     
	va_start(args, fmt);	//Intitalizes "args" to point to the first variadic arguments. "fmt" is the last named parameter.
			    

	StringCchVPrintfW(buffer, 1024, fmt, args);	// -figure out-
	va_end(args);					//cleans up va_list usage (required?)

	OutputDebugStringW(buffer);//Sends the text to the debugger window if debugger is attached. (run program in IDE for easy debugger window).
	OutputDebugStringW(L"\n");

#if SHOW_CONSOLE
	fputws(buffer, stdout);
	fputws(L"\n", stdout);
	fflush(stdout);
#endif
}



/* Error helper : Win32 API often reports failure by returning NULL/0, then you call GetLastError() to
 * get an error code.
 *
 * HWND owner : the owner window for MessageBoxW (can be NULL)
 * const wchar_t *context : Is a human label such as "CreateWindowExW (Main Window)"
 */
static void ShowLastErrorBox(HWND owner, const wchar_t *context) {
	
	DWORD err = GetLastError(); //DWORD is a 32-bit unsinged integer
	wchar_t finalMsg[1024];	//The final formatted message.
	wchar_t *sysMsg = NULL;	//pointer to system-allocated error-text buffer

	//if true it means either no error was set or the failiing function did not call SetLastError
	if (err == 0) {
		StringCchPrintfW(finalMsg, 1024, L"%s failed, but GetLastError() returned 0 (no error code).", context);
		MessageBoxW(owner, finalMsg, L"Win32 Error", MB_OK | MB_ICONERROR);
		Logfw(L"[error] %s", finalMsg);
		return;
	}


	//These flags tell FormatMessageW how to produce the error message.
	DWORD flags = FORMAT_MESSAGE_ALLOCATE_BUFFER | 	//Windows allocates the output buffer (must be freed manually)
		      FORMAT_MESSAGE_FROM_SYSTEM |	//pulls message text from the system message tables.
		      FORMAT_MESSAGE_IGNORE_INSERTS;	//tell it not to expect %1-style inserts.

	/*
	 *  The function that actually prints out the error messages.
	 *
	 *  flags : behavior of the function
	 *  NULL source : becuase it is using system messages. -Investigate further-
	 *  err : The message ID.
	 *  MAKELANGID(LANG_NEUTRAL, SUBLAND_DEFAULT) : request default language.
	 *  (LPWSTR)&sysMsg : 'sysMsg' is a wchar_t*. With ALLOCATE_BUFFER, FormatMessageW expects a pointer to a pointer so it can set it.
	 *  0 size : Windows allocated the buffer and so setting size is unneeded.
	 *  NULL arguments : no inserts.
	 */
	FormatMessageW(flags, NULL, err, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPWSTR)&sysMsg, 0, NULL);
	
	/*If FormatMessageW runs properly, sysMsg points to a system-allocated string.
	 *
	 * %s : context label
	 * %lu : error decimal
	 * 0x%08lx : error hex, padded to 8 digits.
	*/
	if (sysMsg) {
		StringCchPrintfW(finalMsg, 1024, L"%s failed.\n\nGetLastError = %lu (0x%08lx)\n\n%s", context, (unsigned long)err, (unsigned long)err, sysMsg);
		LocalFree(sysMsg);//Requireed because ALLOCATE_BUFFER uses LocalAlloc-compatible allocation.
	}
	//If sysMsg is NULL, FormatMessage failed; it prints a fallback message.
	else {
		StringCchPrintfW(finalMsg, 1024, L"%s failed.\n\nGetLastError = %lu (0x%08lx)\n\n(FormatMessageW failed.)", context, (unsigned long)err, (unsigned long)err);
	}
	
	//Function to actually show the error to the user and logs it. -Elaborate Later-
	MessageBoxW(owner, finalMsg, L"Win32 Error", MB_OK | MB_ICONERROR);
	Logfw(L"[error] %s", finalMsg);
}



/*
 * Takes msg (the numeric message code) and returns a readable string. purely for debugging.
 */
static const wchar_t *MsgName(UINT msg) {
	//switch: chooses base on integer value.
	switch (msg) {
		case WM_CREATE: 	return L"WM_CREATE";
		case WM_COMMAND:	return L"WM_COMMAND";
		case WM_DESTROY:	return L"WM_DESTROY";
		case WM_PAINT:		return L"WM_PAINT";
		case WM_SIZE:		return L"WM_SIZE";
		case WM_CLOSE:		return L"WM_CLOSE";
		case WM_MOVE:		return L"WM_MOVE";
		case WM_SETFOCUS:	return L"WM_SETFOCUS";
		case WM_KILLFOCUS:	return L"WM_KILLFOCUS";
		case WM_KEYDOWN:	return L"WM_KEYDOWN";
		case WM_KEYUP:		return L"WM_KEYUP";
		case WM_CHAR:		return L"WM_CHAR";
		case WM_LBUTTONDOWN:	return L"WM_LBUTTONDOWN";
		case WM_LBUTTONUP: 	return L"WM_LBUTTONUP";
		default:		return L"(unknown msg)";
	}
}



/*
 * Converts the numeric button ID's back into strings for logs.
 */
static const wchar_t *ControlIdName(int id) {
	switch(id) {
		case ID_BTN_HELLO:	return L"ID_BTN_HELLO";
		case ID_BTN_QUIT:	return L"ID_BTN_QUIT";
		case ID_BTN_TEST:	return L"ID_BTN_TEST";
		default:		return L"(unknown control id)";
	}
}



/*
 * BN_* codes are the button notification codes delivered through WM_COMMAND.
 */
static const wchar_t *NotifyCodeName(int code) {
	switch (code) {
		case BN_CLICKED:	return L"BN_CLICKED";
		case BN_DOUBLECLICKED:	return L"BN_DOUBLECLICKED";
		case BN_SETFOCUS:	return L"BN_SETFOCUS";
		case BN_KILLFOCUS:	return L"BN_KILLFOCUS";
		default:		return L"(unknown notify code)";
	}
}



/*
 * struct CommandInfo {...}; defines a struct type with three fields.
 * typedef ... CommandInfo; creates and alias so i can write "CommmandInfo" instead of "struct CommmandInfo".
 *
 * controlId : which control (button) triggered the command.
 * notifyCode : what happened (clicked, double clicked, focus, etc.)
 * controlHwnd : the handle of the control window itself.
 */
typedef struct CommandInfo {
	int controlId;
	int notifyCode;
	HWND controlHwnd;
} CommandInfo;
/*
 * wParam packs two 16-bit values:
 * 				low word = control ID
 * 				high word = notification code
 * LOWORD(x) : extracts the lower 16 bits.
 * HIWORD(x) : extracts the upper 16 bits.
 *
 * casts:
 * 	(int) : the macros yeald an integer-ish type and so i want "int"
 * 	(HWND)lParam : for control notifications, lParam holds the control window handle.
 */
static CommandInfo DecodeWmCommand(WPARAM wParam, LPARAM lParam) {
	CommandInfo info;
	info.controlId	= (int)LOWORD(wParam);
	info.notifyCode	= (int)HIWORD(wParam);
	info.controlHwnd = (HWND)lParam;
	return info;
}



/*
 * BOOL : Win32's integer boolean type (TRUE/FALSE).
 * WNDCLSSEXW : the "extended window class" struct (wide version).
 * ZeroMemory(&wc, sizeof(wc)) : sets all bytes to 0 to prevent "random uninitialized fields".
 *
 * cbSize : size of the struct; Windows uses this to know which version/size is being passed.
 * lpfnWndProc : pointer to the window procedure function (must match the signature).
 * hInstance : the module instance handle.
 *
 * hCursor = LoadCursor(NULL, IDC_ARROW);
 * 			LoadCursor : loads a cursor resource.
 * 			NULL : a NULL instance means "use system cursor resources".
 * 			IDC_ARROW : is the standard cursor identifier.
 *
 * hbrBackground = (HBRUSH)(COLOR_WINDOW + 1) : Win32 system color brushes are referenced as "(HBRUSH)(COLOR_* + 1)".
 * lpszClassName : the class name that will be used later in "CreateWIndowExW".
 */
static BOOL RegisterMainWindowClass(HINSTANCE hInstance){
	
	WNDCLASSEXW wc;
	ZeroMemory(&wc, sizeof(wc));

	wc.cbSize	= sizeof(wc);
	wc.lpfnWndProc 	= MainWndProc;
	wc.hInstance 	= hInstance;
	wc.hCursor 	= LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszClassName = g_mainClassName;

	//Clears the last error before calling the API. if it fails i can assume GetLastError() changed.
	SetLastError(0);
	
	//returns 0 on failure, non-zero on success.
	if (RegisterClassExW(&wc) == 0){
		return FALSE;
	}
	return TRUE;
}



/*
 * Returns HWND (handle to created control window) or NULL if failed.
 *
 * parent : the parent window (main window)
 * controlId : numeric ID for WM_COMMAND
 * text : label on button
 * x/y/width/height : client coordinates in parent
 */
static HWND CreatePushButton(HWND parent, int controlId, const wchar_t *text, int x, int y, int width, int height) {

	/*
	 * In CreateWindowExW, the parameter named hMenu is used differently depending on window type:
	 * 	>For a top-level window, its a menu handle
	 * 	>for a child control, Win32 overloads this field to carry the control ID
	 * so "int controlId" is converted in an HMENU-typed value.
	 * INT_PTR is and integer type the size of a pointer (safe on 32/64-bit).
	 */
	HMENU idAsMenuHandle = (HMENU)(INT_PTR)controlId;
	
	SetLastError(0);
	
	/*
	 * "dwExStyle =" 0 : No extended style
	 * "lpClassName =" L"BUTTON" : this is the built-in Windows button class.
	 * "lpWindowName =" text : the label on the button.
	 * "dwStyle =" WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON
	 *
	 * 				WS_CHILD : This is a child window/control (must have a parent)
	 * 				WS_VISIBLE : show immediately
	 * 				BS_PUHBUTTON : standard pushbutton behavior
	 * x/y/width/height : postion and size
	 * "hWndParent =" parent : The main window
	 * "hMenu =" idAsMenuhandle : for child controls, this becomes the control ID.
	 * "hInstance =" g_hInstance : instance handle of the module creating the window.
	 * "lpParam =" NULL : Extra creation data (unused)
	 *
	 * Returns :
	 * 	>HWND if successful
	 * 	>NULL if failed (then GetLastError() explains why)
	 */
	return CreateWindowExW(
		0,
		L"BUTTON",
		text,
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		x, y, width, height, 
		parent,
		idAsMenuHandle,
		g_hInstance,
		NULL
	);
}



/*
 * Creates the main window of the program.
 * (HINSTANCE hInstance): has one parameter, HINSTANCE is a handle to the program/module instance (the EXE)
 */
static HWND CreateMainWindow(HINSTANCE hInstance) {
	
	//clears the last error
	SetLastError(0);


	/*
	 * "dwExStyle =" 0 : no extended style
	 * "lpClassName =" g_mainClassName : class name of the window to be created
	 * "lpWindowName =" L"Simple Buttons (C / Win32)" : Window title text caption shown in the title bar.
	 * "dwStyle =" WS_OVERLAPPEDWINDOW : Predefined style combination for a normal top-level app window.
	 * "x =" CW_USEDEFAULT : tells Windows "pick a default position"
	 * "y =" CW_USEDEFAULT : tells windows "pick a default position"
	 * "nWidth =" 360 : Requested Window width.
	 * "nHeight =" 180 : Requested Window Height
	 * "hWndParent =" NULL : Parent window, NULL means "this is a top-level window, not a child window"
	 * "hMenu =" NULL : For a top-level window, this is a handle to a menu (HMENU), NULL means "no menu"
	 * "hInstance =" hInstance : instance handle of the module creating the window. Here "hInstance" is passed through thefuntion parameter (which came from WinMain).
	 * "lpParam =" NULL : Extra creation data (unused)
	 *
	 * Returns :
	 * 	>HWND for the main window if sucsessful
	 * 	>NULL if failed (then GetLastError() explains why)
	 */
	return CreateWindowExW(
			0,
			g_mainClassName,
			L"Simple Buttons (C / Win32)",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT,
			360, 180,
			NULL,
			NULL,
			hInstance,
			NULL
		);
}



/*
 * The event handler for the window. Whenever somthign happens to the main window, windows calls this function.
 */
static LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	/*
	 * %p : prints a pointer value.
	 * hwnd : is a handle, cast to (void*) to match %p
	 * msgName(msg) : prints the message code in hex (4 digits)
	 * wParam/lParam : integer types the size of a pointer so the code casts:
	 							(UINT_PTR)wParam then (void*) so %p is happy on 32/64 bit. -Elaborate-
	 */
	Logfw(L"[msg] hwnd=%p %s (0x%04X) wParam=0x%p lParam=0x%p", (void*)hwnd, MsgName(msg), (unsigned)msg, (void*)(UINT_PTR)wParam, (void*)(UINT_PTR)lParam);
	
	//Switch statment the depends on the message type.
	switch(msg) {
		
		//WM_CREATE indicates that windows is notifying me that a window is being created.
		case WM_CREATE: {
			
			/*
			 * HWND parent : hwnd
			 * int controlId : ID_BTN_HELLO
			 * const wchar_t *text : L"Say Hello"
			 * int x : 20
			 * int y : 20
			 * int width : 120
			 * int height : 32
			 */
			HWND btnHello	= CreatePushButton(hwnd, ID_BTN_HELLO, L"Say Hello",	20, 20, 120, 32);
			if (!btnHello){
				ShowLastErrorBox(hwnd, L"CreateWindowExW (Hello Button)");
			}

			/*
			 * HWND parent : hwnd
			 * int controlId : ID_BTN_QUIT
			 * const wchar_t *text : L"Quit"
			 * int x: 20
			 * int y: 60
			 * int width: 120
			 * int height : 32
			 */
			HWND btnQuit	= CreatePushButton(hwnd, ID_BTN_QUIT, L"Quit",		20, 60, 120, 32);
			if (!btnQuit){
				ShowLastErrorBox(hwnd, L"CreateWindowExW (Quit Button)");
			}

			/*
			 * HWND parent : hwnd
			 * int controlId : ID_BTN_TEST
			 * const wchar_t *text : L"test"
			 * int x: 20
			 * int y: 100
			 * int width: 120
			 * int height: 32
			 */
			HWND btnTest	= CreatePushButton(hwnd, ID_BTN_TEST, L"test",		20, 100, 120, 32);
			if (!btnTest){
				ShowLastErrorBox(hwnd, L"CreateWindowExW (test Button)");
			}

			//if returned 0 then WM_CREATE was handled sucsessfully
			return 0;
		}

		//WM_COMMAND happens for menu items, accelerators, controls, etc. Currently it is only for the buttons.
		case WM_COMMAND: {
			
			/*
			 * wParam : is a pointer-sized integer(WPARAM), but for WM_COMMAND is often contains two 16-bit pieces:
			 * 					>LOWORD(wParam) = control ID (ID_BTN_HELLO for example)
			 * 					>HIWORD(wParam) = the notification code (such as BN_CLICKED)
			 * lParam : is the HWND of the control that sent the notificatio (the actual button handle)
			 */
			CommandInfo ci = DecodeWmCommand(wParam, lParam);
			/* >DecodeWmCommand under the hood:
			 *
			 * ci.controlId   = (int)LOWORD(wParam);
			 * ci.notifyCode  = (int)HIWORD(wParam);
			 * ci.controlHwnd = (HWND)lParam;
			 */

			
			//this funtion simply prints a decoded snapshot of the command for logging
			Logfw(L"[cmd] controlId=%d (%s) notify=%d (%s) controlHwnd=%p", ci.controlId, ControlIdName(ci.controlId), ci.notifyCode, NotifyCodeName(ci.notifyCode), (void*)ci.controlHwnd);
			
			//Checks the notify code and returns true if its "BN_CLICKED"
			if (ci.notifyCode == BN_CLICKED) {
				//Checks the control ID and returns true if its "ID_BTN_HELLO"
				if (ci.controlId == ID_BTN_HELLO) {
					/* MessageBoxW creates a popup window based on the given parameters:
					 * "HWND hWnd =" hwnd : handle to the owner of the window of the messagebox to be created
					 * "LPCTSTR lpText =" L"Hello!" : the message to be displayed
					 * "LPCTSTR lpCaption =" L"Win32" : the dialog box title
					 * "UINT uType =" MB_OK | MB_ICONINFORMATION
					 * 			>MB_OK : The message box contains one push button: OK (the default)
					 * 			>MB_ICONINFORMATION : An icon consisting of a lowercase "i" in a circle appears in the message box
					 */
					MessageBoxW(hwnd, L"Hello!", L"Win32", MB_OK | MB_ICONINFORMATION);
					return 0;
				}
				//Checks the control ID and returns true if its "ID_BTN_QUIT"
				else if (ci.controlId == ID_BTN_QUIT) {
					//begins window destruction which will later trigger "WM_DESTROY"
					DestroyWindow(hwnd);
					return 0;
				}
				//Checks the control ID and returns true if its "ID_BTN_TEST"
				else if (ci.controlId == ID_BTN_TEST){
					/*
					 * MessageBoxW creates a popup window based on the given parameters:
					 * "HWND hwnd =" hwnd : handle to the owner of the window of the messagebox to be created
					 * "LPCTSTR lpText =" L"Test button sucsessful" : the message to be displayed 
					 * "LPCTSTR lpCaption =" L"TestWindow" : the dialog box title
					 * "UINT uType =" MB_OK | MB_ICONINFORMATION
					 * 			>MB_OK : The message box contains one push button: OK (the default)
					 * 			>MB_ICONINFORMATION : An icon consisting of a lowercase "i" in a circle appears in the message box
					 */
					MessageBoxW(hwnd, L"Test button sucsessful", L"TestWindow", MB_OK | MB_ICONINFORMATION);
					return 0;
				}
			}
			//If the command is not handled it breks out of the switch so that it will use the default handling (DefWindowProcW)
			break;
		}

		//WM_DESTROY is the event is called when the window is being closed.
		case WM_DESTROY: {
			PostQuitMessage(0);
			return 0;
		}
	}

	//If a message is not handled this function impliments normal window behaviors:
	//						>moving/resizing
	//						>painting defaults
	//						>close button behavior (generates WM_CLOSE, etc.)
	return DefWindowProcW(hwnd, msg, wParam, lParam);
}



/* >Main Program entry point< (GUI subsystem Windows apps traditionally use WinMain instead of main)
 * 
 * HINSTANCE hInstance : The apps instance handle
 * HINSTANCE hPrevInstance : legacy parameter, no meaning
 * LPSTR lpCmdLine : command line as ANSI string (not included in program name
 * int nCmdShow : How windows suggest the window is shown (normal/minimized/etc.)
 */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	//Intentionally useing these variables to silence unused parameter warnings
	(void)hPrevInstance;
	(void)lpCmdLine;
		
	//SetupConsoleForLogging(): -impliment later if standalone needed, otherwise use IDE console-

	//this stores hInstance as a global variable
	g_hInstance = hInstance;

	//logging of startup info
	Logfw(L"[startup] hInstance=%p nCmdShow=%d", (void*)hInstance, nCmdShow);
	
	//registers the window class
	if (!RegisterMainWindowClass(hInstance)) {
		//if registration fails, shows the error box
		ShowLastErrorBox(NULL, L"RegisterClassExW");
		//exits the program
		return 0;
	}

	//creates the main window itself by calling CreateMainWindow funtion created earlier
	HWND hwnd = CreateMainWindow(hInstance);
	//if creating the main window fails, print error and quit
	if (!hwnd) {
		ShowLastErrorBox(NULL, L"CreateWindowExW (Main Window)");
		return 0;
	}

	//ShowWindow funtion makes the window visible on the screen
	ShowWindow(hwnd, nCmdShow);
	//UpdateWindow forces an immediate paint if needed.
	UpdateWindow(hwnd);
	
	//this is a struct that holds a message (type, parameters, cursor, pos, time, etc.)
	MSG msg;
	/* Here is what the MSG struct parameters look like:
	 *
	 * msg.hwnd : The window the message is for
	 * msg.message : The message ID (such as WM_COMMAND, etc)
	 * msg.wParam : extra data (message dependent)
	 * msg.lParam : extra data (message dependent)
	 * msg.time : timestamp message was made
	 * msg.pt : cursor position when message made
	 */

	//this while loop runs after program startup and continues while the program is being run
	while(1) {
		SetLastError(0);
		
		/*
		 * "LPMSG lpMsg =" &msg : long pointer to the message struct:
		 * "HWND hwnd =" NULL : the window handle the message belongs to
		 * "UINT wMsgFilterMin =" 0 :
		 * "UINT wMsgFilterMax =" 0 : 
		 * 			>both of these parameters filter which messages come thorugh, by settting it
		 * 			>to zero all messages are passed through.
		 */
		int ret = GetMessage(&msg, NULL, 0, 0);
		
		//if ret is more than zero then a normal message was recieved
		if (ret > 0) {
			
			//translateMessage first examines the message
			TranslateMessage(&msg);
			//DispatchMessageW looks at the parameters of the MSG struct and then calls WindowProc with the data
			DispatchMessageW(&msg);
		}
		//If ret is exactly 0 then the message was to quit and close the window
		else if (ret == 0) {
			Logfw(L"[loop] WM_QUIT received. Exiting Message loop,");
			break;
		}
		//if not 0 or greater it generates an error message
		else {
			ShowLastErrorBox(NULL, L"GetMessageW");
			break;
		}
	}
	return (int)msg.wParam;
}
