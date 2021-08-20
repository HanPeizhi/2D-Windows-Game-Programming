// Creates two windows based on the same 
// window class

// INCLUDES ///////////////////////////////////////////////
#define WIN32_LEAN_AND_MEAN  // just say no to MFC

#include <windows.h>   // include all the windows headers
#include <windowsx.h>  // include useful macros
#include <stdio.h>     
#include <math.h>
//#include "resource.h"


// DEFINES ////////////////////////////////////////////////

// defines for windows 
#define WINDOW_CLASS_NAME1 "WINCLASS1"
#define WINDOW_CLASS_NAME2 "WINCLASS2"

// GLOBALS ////////////////////////////////////////////////
UINT check1;
UINT check2;


// FUNCTIONS //////////////////////////////////////////////
LRESULT CALLBACK WindowProc1(HWND hwnd, 
							 UINT msgId, 
							 WPARAM wparam, 
							 LPARAM lparam)
{
	// this is the main message handler of the system
	PAINTSTRUCT		ps;		// used in WM_PAINT
	HDC				hdc;	// handle to a device context

	// what is the message 
	switch(msgId){	
		case WM_CREATE:{
			// do initialization stuff here

			// return success
			return(0);
		} break;

		case WM_PAINT:{
			// simply validate the window
			hdc = BeginPaint(hwnd,&ps);	 
			// you would do all your painting here
			EndPaint(hwnd,&ps);
			 
			// return success
			return(0);
		} break;

		case WM_DESTROY:{
			// kill the application, this sends a WM_QUIT message 
			check1 = msgId;
			if(check1 == check2)
				PostQuitMessage(0);

			// return success
			return(0);
			
		} break;

	default:break;

	} // end switch

	// process any messages that we didn't take care of 
	return (DefWindowProc(hwnd, msgId, wparam, lparam));

} // end WinProc



LRESULT CALLBACK WindowProc2(HWND hwnd, 
							 UINT msgId, 
							 WPARAM wparam, 
							 LPARAM lparam)
{
	// this is the main message handler of the system
	PAINTSTRUCT		ps;		// used in WM_PAINT
	HDC				hdc;	// handle to a device context

	// what is the message 
	switch(msgId){	
		case WM_CREATE:{
			// do initialization stuff here

			// return success
			return(0);
		} break;

		case WM_PAINT:{
			// simply validate the window
			hdc = BeginPaint(hwnd,&ps);	 
			// you would do all your painting here
			EndPaint(hwnd,&ps);

			// return success
			return(0);
		} break;

		case WM_DESTROY:{
			// kill the application, this sends a WM_QUIT message 
			check2 = msgId;
			if(check1 == check2)
				PostQuitMessage(0);

			// return success
			return(0);
			
		} break;

	default:break;

	} // end switch

	// process any messages that we didn't take care of 
	return (DefWindowProc(hwnd, msgId, wparam, lparam));

} // end WinProc



// WINMAIN ////////////////////////////////////////////////
int WINAPI WinMain(	HINSTANCE hinstance,
					HINSTANCE hprevinstance,
					LPSTR lpcmdline,
					int ncmdshow)
{

	WNDCLASSEX winclass1;		// this will hold the class we create
	HWND	   hwnd1;			// generic window handle 1
	MSG		   msg;				// generic message

	// first fill in the window class stucture
	winclass1.cbSize			= sizeof(WNDCLASSEX);
	winclass1.style				= CS_DBLCLKS | CS_OWNDC | 
								  CS_HREDRAW | CS_VREDRAW;
	winclass1.lpfnWndProc		= WindowProc1;
	winclass1.cbClsExtra		= 0;
	winclass1.cbWndExtra		= 0;
	winclass1.hInstance			= hinstance;
	winclass1.hIcon				= LoadIcon(NULL, IDI_APPLICATION);
	winclass1.hCursor			= LoadCursor(NULL, IDC_ARROW);
	winclass1.hbrBackground		= (HBRUSH)GetStockObject(BLACK_BRUSH);
	winclass1.lpszMenuName		= NULL;
	winclass1.lpszClassName		= WINDOW_CLASS_NAME1;
	winclass1.hIconSm			= LoadIcon(NULL, IDI_APPLICATION);


	WNDCLASSEX winclass2;		// this will hold the class we create
	HWND	   hwnd2;			// generic window handle 2

	// first fill in the window class stucture
	winclass2.cbSize			= sizeof(WNDCLASSEX);
	winclass2.style				= CS_DBLCLKS | CS_OWNDC | 
								  CS_HREDRAW | CS_VREDRAW;
	winclass2.lpfnWndProc		= WindowProc2;
	winclass2.cbClsExtra		= 0;
	winclass2.cbWndExtra		= 0;
	winclass2.hInstance			= hinstance;
	winclass2.hIcon				= LoadIcon(NULL, IDI_APPLICATION);
	winclass2.hCursor			= LoadCursor(NULL, IDC_ARROW);
	winclass2.hbrBackground		= (HBRUSH)GetStockObject(BLACK_BRUSH);
	winclass2.lpszMenuName		= NULL;
	winclass2.lpszClassName		= WINDOW_CLASS_NAME2;
	winclass2.hIconSm			= LoadIcon(NULL, IDI_APPLICATION);


	// register the window class 1
	if (!RegisterClassEx(&winclass1))
		return(0);

	// create the first window
	if (!(hwnd1 = CreateWindowEx(NULL,										// extended style
								 WINDOW_CLASS_NAME1,						// class
								 "Window 1 Based on WINCLASS1",				// title
								 WS_OVERLAPPEDWINDOW | WS_VISIBLE,
								 0,0,										// initial x,y
								 400,400,									// initial width, height
								 NULL,										// handle to parent 
								 NULL,										// handle to menu
								 hinstance,									// instance of this application
								 NULL)))									// extra creation parms
		return(0);


	// register the window class 2
	if (!RegisterClassEx(&winclass2))
		return(0);

	// create the second window
	if (!(hwnd2 = CreateWindowEx(NULL,										// extended style
								 WINDOW_CLASS_NAME2,						// class
								 "Window 2 Based on WINCLASS2",				// title
								 WS_OVERLAPPEDWINDOW | WS_VISIBLE,
								 100,100,									// initial x,y
								 400,400,									// initial width, height
								 NULL,										// handle to parent 
								 NULL,										// handle to menu
								 hinstance,									// instance of this application
								 NULL)))									// extra creation parms
		return(0);

	// enter main event loop, but this time we use PeekMessage()
	// instead of GetMessage() to retrieve messages
	while(TRUE)
	{
		// test if there is a message in queue, if so get it
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE)){ 
			// test if this is a quit
			if (msg.message == WM_QUIT)
				break;

			// translate any accelerator keys
			TranslateMessage(&msg);

			// send the message to the window proc
			DispatchMessage(&msg);
		} // end if

		// main game processing goes here

	} // end while

	// return to Windows like this
	return(msg.wParam);

} // end WinMain

///////////////////////////////////////////////////////////

