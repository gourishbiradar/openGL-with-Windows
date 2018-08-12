
#define WIN32_LEAN_AND_MEAN
#pragma comment(linker,"/subsystem:windows")
#include "stdafx.h"
#include <windows.h>


LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT paintStruct;
	HDC hDC;
	char string[] = "Hello,World!";
	switch (message)
	{
		//make new window
	case WM_CREATE:
		return 0;
		break;
		//close current window
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
		break;
		//update display of current window
	case WM_PAINT:
		//start painting
		hDC = BeginPaint(hwnd, &paintStruct);
		//set display text to blue color or some other color to your liking RGB is used here
		SetTextColor(hDC, COLORREF(0x00FF00FF));
		//print out the text to display
		TextOut(hDC, 300, 300, string, sizeof(string)-1);
		//end the painting
		EndPaint(hwnd, &paintStruct);
		return 0;
		break;
	default:
		//no action set.. can be used later to display errors
		break;
	}
	return (DefWindowProc(hwnd, message, wParam, lParam));
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//MessageBox(NULL, "\tHello World!", "My first window app!", NULL); //standard display window *use for testing*
	WNDCLASSEX windowClass; //a standard window class predefined in windows.h
	HWND hwnd; //window handle pointer unique to each open window of a certain class
	MSG msg; //message, it is a struct and you need to read about it before dismissing it as a char*
	bool done; //a flag to check state of window
	//fill out the window class struct
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = WndProc; //event callback handler
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = hInstance; //bind the object to current window
	windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = "MyClass";
	windowClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
	// register window class
	if (!RegisterClassEx(&windowClass))
		return 0;
	// class registerd so we can create our window
	hwnd = CreateWindowEx(NULL, //extended style
		"MyClass", //class name
		"A Real Windows application", //app name
		WS_OVERLAPPEDWINDOW | //window style
		WS_VISIBLE |
		WS_SYSMENU,
		150, 150, //x,y cords
		500, 500, //width,height
		NULL, //handle to parent
		NULL, //handle to menu
		hInstance, //application instance
		NULL //no extra parameters
	);
	if (!hwnd) //faied to create window?
		return 0;
	done = false; //loop condition variable initialization

	//main message loop
	while (!done)
	{
		PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE);
		if (msg.message == WM_QUIT) //check for quit message
		{
			done = true; // if found, quit the loop
		}
		else
		{
			//Translate and dispatch given message to event queue
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return msg.wParam;
}