#include "graphics.h"
#include "log.h"

#include <windows.h>
const char WINDOWCLASSNAME[] = "HPGLClass";

LRESULT CALLBACK WindowCallback(
	HWND   handle,
	UINT   message,
	WPARAM wParam,
	LPARAM lParam
){
	LRESULT result = 0;
	switch (message)
	{
	case WM_PAINT:
		PaintWindow(handle);
		break;
	case WM_CLOSE:
		DestroyWindow(handle);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;
	default:
		result = DefWindowProc(handle, message, wParam, lParam);
		break;
	}
	return result;
}

int CALLBACK WinMain(
	HINSTANCE instance,
	HINSTANCE previous,
	LPSTR     commandLine,
	int       showCommand
) {

	// Create and register the window class
	WNDCLASS wc = {};
	wc.lpfnWndProc = WindowCallback;
	wc.lpszClassName = WINDOWCLASSNAME;

	RegisterClass(&wc);

	log_notice("Registered window class");

	HWND windowHandle = CreateWindowEx(
		0,
		WINDOWCLASSNAME,
		"HP-GL Interpreter",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,
		NULL,
		instance,
		NULL
		);
	if(!windowHandle) {
		log_error("Couldn't create window, aborting");
		return 0;
	}
	log_notice("Created window");
	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}
