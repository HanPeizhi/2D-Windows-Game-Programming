// Using Menu Chapter 3.2

// INCLUDES ///////////////////////////////////////////////
#define WIN32_LEAN_AND_MEAN  // just say no to MFC

#include <windows.h>   // include all the windows headers
#include <windowsx.h>  // include useful macros
#include <mmsystem.h>  // very important and include WINMM.LIB for PlaySound() etc.
#include <stdio.h>     
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include "resource.h"

using namespace std;

// DEFINES ////////////////////////////////////////////////

// defines for windows 
#define WINDOW_CLASS_NAME1 "WINCLASS1"


// GLOBALS ////////////////////////////////////////////////
HINSTANCE hinstance_app		= NULL;		// globally track hinstance
int count					= 0;		// track number of msg's
char buffer[80];						// used to print string



// FUNCTIONS //////////////////////////////////////////////
LRESULT CALLBACK WindowProc1(HWND hwnd, 
							 UINT msgId,		// Message identifierin in msg, WM_xxx
							 WPARAM wparam,		// The ID of the menu item that was selected
							 LPARAM lparam)		// window handle that the message was sent from 
{
	// this is the main message handler of the system
	PAINTSTRUCT		ps;				// used in WM_PAINT
	HDC				hdc;			// handle to a device context
	
	

	// what is the message
	switch(msgId){	
		case WM_CREATE:{	
			// do initiization stuff here

			// only allowed to play one sound at a time with PlaySound()
			// the first sound uses SND_SYNC flag. the second sound will not stop the first one in midplay.
			PlaySound(MAKEINTRESOURCE(SOUND_ID_CREATE), hinstance_app, SND_RESOURCE | SND_SYNC);
			
			// play second sound by loop mode
			PlaySound(MAKEINTRESOURCE(SOUND_ID_MUSIC), hinstance_app, SND_RESOURCE | SND_ASYNC | SND_LOOP);

			// return success
			return(0);
		} break;

		case WM_COMMAND:{
			switch(LOWORD(wparam)){
				// handle the File menu
				case MENU_FILE_ID_OPEN:{
					// do work here				   
				} break;

				case MENU_FILE_ID_CLOSE:{
					// do work here
				} break;

				case MENU_FILE_ID_SAVE:{
					// do work here
				} break;

				case MENU_FILE_ID_EXIT:{
					PlaySound(NULL, hinstance_app, SND_PURGE);
					PostQuitMessage(0);
				} break;

				//handle the Help menu
				case MENU_HELP_ABOUT:{
					// do work herez
					sprintf(buffer,"GDI Text Demo %d times.   ", count);
					MessageBox(hwnd, buffer, buffer, MB_OK | MB_ICONEXCLAMATION);
				} break;

				case MENU_PLAY_ID_BEAM:{
                     // play the sound
                     PlaySound(MAKEINTRESOURCE(SOUND_ID_BEAM), hinstance_app, SND_RESOURCE | SND_ASYNC);
                } break;

                case MENU_PLAY_ID_TELEPORT:{
                     // play the sound
                     PlaySound(MAKEINTRESOURCE(SOUND_ID_TELEPORT), hinstance_app, SND_RESOURCE | SND_ASYNC);
                } break;

                case MENU_PLAY_ID_WARP:{
                     // play the sound
                     PlaySound(MAKEINTRESOURCE(SOUND_ID_WARP), hinstance_app, SND_RESOURCE | SND_ASYNC);
                } break;

				// play sound
				case MENU_PLAY_ID_ENERGIZE:{
					PlaySound(MAKEINTRESOURCE(SOUND_ID_ENERGIZE), hinstance_app, SND_RESOURCE | SND_ASYNC);
				} break;

				default: break;
			}
		} break;

		case WM_SIZE:{

			int width  = LOWORD(lparam);
			int height = HIWORD(lparam);

			// get a graphics context
			hdc = GetDC(hwnd);

			// set the foreground color to green
			SetTextColor(hdc, RGB(0,255,0));

			// set the background color to black
			SetBkColor(hdc, RGB(0,0,0));

			// set the transparency mode to OPAQUE
			SetBkMode(hdc, OPAQUE);

			// draw the size of the window
			sprintf(buffer,"WM_SIZE Called -  New Size = (%d,%d)", width, height);
			TextOut(hdc, 0,0, buffer, strlen(buffer));

			// release the dc back
			ReleaseDC(hwnd, hdc);
		}

		case WM_MOVE:{
			// extract the position
			int xpos = LOWORD(lparam);
			int ypos = HIWORD(lparam);

			// get a graphics context
			hdc = GetDC(hwnd);

			// set the foreground color to green
			SetTextColor(hdc, RGB(0,255,0));

			// set the background color to black
			SetBkColor(hdc, RGB(0,0,0));

			// set the transparency mode to OPAQUE
			SetBkMode(hdc, OPAQUE);

			// draw the size of the window
			sprintf(buffer,"WM_MOVE Called -  New Positition = (%d,%d)", xpos, ypos);
			TextOut(hdc, 0,0, buffer, strlen(buffer));

			// release the dc back
			ReleaseDC(hwnd, hdc);
		} break;

		case WM_PAINT:{
			// simply validate the window
			hdc = BeginPaint(hwnd,&ps);	 

			// you would do all your painting here
			EndPaint(hwnd,&ps);
			 
			// return success
			return(0);
		} break;

		case WM_CLOSE:{
			// show a message box
			int result = MessageBox(hwnd, "Are you sure you want to close this application?",
									"WM_CLOSE Message Processor", MB_YESNO | MB_ICONQUESTION);
			// change to close or not
			if(result == IDYES){
				return DefWindowProc(hwnd, msgId, wparam, lparam);
			}
			else return 0;


		} break;

		case WM_DESTROY:{
			// stop the sounds first
			PlaySound(NULL, hinstance_app, SND_PURGE);

			// kill the application, this sends a WM_QUIT message 
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
	winclass1.hIcon				= LoadIcon(hinstance, MAKEINTRESOURCE(ID_ICON1));
	winclass1.hIconSm			= LoadIcon(hinstance, MAKEINTRESOURCE(ID_ICON1));
	winclass1.hCursor			= LoadCursor(hinstance, MAKEINTRESOURCE(ID_CROSSHAIR));
	winclass1.hbrBackground		= (HBRUSH)GetStockObject(WHITE_BRUSH);
	winclass1.lpszMenuName		= NULL;
	winclass1.lpszClassName		= WINDOW_CLASS_NAME1;
	
	// save hinstance in global
	hinstance_app = hinstance;

	// register the window class 1
	if (!RegisterClassEx(&winclass1))	return(0);

	// create the first window	//since the window has been created, than can attach a new menu
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

	// load the menu resource by highest priority
	HMENU hmenuhandle = LoadMenu(hinstance, "MainMenu");
	// attach the menu to the window
	SetMenu(hwnd1, hmenuhandle);

	// load in the first string and check for error
	char load_string[80];
	if(!LoadString(hinstance, ID_STR_LOAD_GAME, load_string, 80)){
		// there's an error!
	}
	
	// get the dc and hold it
	//HDC hdc = GetDC(hwnd1);

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

		
		//////////////////////////////////////
		// main game processing goes here
		//////////////////////////////////////

		////ctrl+K+C;ctrl+K+U
		//// set the foreground color to random
		//SetTextColor(hdc, RGB(rand()%256,rand()%256,rand()%256));

		//// set the background color to black
		//SetBkColor(hdc, RGB(0,0,0));

		//// finally set the transparency mode to transparent
		//SetBkMode(hdc, TRANSPARENT);		// OPAQUE or TRANSPARENT

		//// draw some text at a random location
		//sprintf(buffer,"GDI Text Demo %d times. ", ++count);
		//TextOut(hdc,rand()%400,rand()%400, buffer, strlen(buffer));


		Sleep(10);


	} // end while

	// release the dc
	//ReleaseDC(hwnd1,hdc);

	// return to Windows like this
	return(msg.wParam);

} // end

/////////////////////////////////////////////////////////

