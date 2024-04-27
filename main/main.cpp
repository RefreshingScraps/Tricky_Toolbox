#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include "..\include\include.h"
using namespace std;
/* This is where all the input to the window goes to */
HWND Extract_Sound,_Play_Sound,Full_Volume,BSOD,all,
screen_drawico,screen_enlarge,screen_tunnel;
int x=GetSystemMetrics(SM_CXSCREEN);
int y=GetSystemMetrics(SM_CYSCREEN);
HINSTANCE hInst;

LRESULT CALLBACK WndProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam){
	POINT pt;
	switch(Message){
		case WM_CREATE:{
			Extract_Sound		=		CreateWindow("button","释放音乐",WS_CHILD|WS_VISIBLE,0,0,100,25,hwnd,(HMENU)1,hInst,NULL);
			_Play_Sound			=		CreateWindow("button","播放阴乐",WS_CHILD|WS_VISIBLE,100,0,100,25,hwnd,(HMENU)2,hInst,NULL);
			Full_Volume			=		CreateWindow("button","调大音量",WS_CHILD|WS_VISIBLE,200,0,100,25,hwnd,(HMENU)3,hInst,NULL);
			BSOD				=		CreateWindow("button","蓝屏钙",WS_CHILD|WS_VISIBLE,300,0,100,25,hwnd,(HMENU)4,hInst,NULL);
			all					=		CreateWindow("button","全家桶",WS_CHILD|WS_VISIBLE,400,0,100,25,hwnd,(HMENU)5,hInst,NULL);
			
			screen_drawico		=		CreateWindow("button","画图标",WS_CHILD|WS_VISIBLE,0,300,150,30,hwnd,(HMENU)6,hInst,NULL);
			screen_enlarge		=		CreateWindow("button","屏幕放大",WS_CHILD|WS_VISIBLE,0,100,100,25,hwnd,(HMENU)7,hInst,NULL);
			screen_tunnel		=		CreateWindow("button","屏幕隧道",WS_CHILD|WS_VISIBLE,0,100,100,25,hwnd,(HMENU)8,hInst,NULL);
			break;
		}//StretchBlt(GetDC(0),50,50,GetSystemMetrics(SM_CXSCREEN)-100,GetSystemMetrics(SM_CYSCREEN)-100,GetDC(0),0,0,GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN),SRCCOPY);

		case WM_COMMAND:{
			switch(wParam){
				case 1:{
					Extrcat_File("deathscream.mp3");
					break;
				}
				case 2:{
					Set_Sound_Name(".\\deathscream.mp3");
					Play_Sound();
					break;
				}
				case 3:{
					Mute_state(FALSE);
					Set_Volume(1.0F);
					break;
				}
				case 4:{
					BSOD_Custom(0xc0000094);
					break;
				}
				case 5:{
					Extrcat_File("deathscream.mp3");
					Mute_state(FALSE);
					Set_Volume(1.0F);
					Set_Sound_Name(".\\deathscream.mp3");
					Play_Sound();
					Sleep(1000);
					BSOD_Custom(0xc0000094);
					break;
				}
				case 6:{
//					MoveWindow(drawico, rand()%640, rand()%480, 100, 50, true); // 将按钮移动到(x=50, y=50)位置，宽度和高度不变
					while(true){
						GetCursorPos(&pt);
						DrawIcon(GetDC(hwnd),pt.x,pt.y,LoadIcon(hInst,"A"));
					}
					break;
				}
				case 7:{
					StretchBlt(GetDC(0),-60,-60,x+120,y+120,GetDC(0),0,0,x,y,13369376); 
					break;
				}
				default:{
					return DefWindowProc(hwnd,Message,wParam,lParam);
					break;
				}
			}
			break;
		}
		case WM_DESTROY:{
            PostQuitMessage(0);
			break;
		}
		default:{
			return DefWindowProc(hwnd,Message,wParam,lParam);
			break;
		}
	}
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	hInst=hInstance; 
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	memset(&wc,0,sizeof(wc));
 	wc.cbSize        = sizeof(WNDCLASSEX);
	wc.style         = 0;
	wc.lpfnWndProc   = WndProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hInstance;
	wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszMenuName  = "MAINMENU";
	wc.lpszClassName = "WindowClass";
	wc.hIconSm       = LoadIcon(hInstance,"A"); /* A is name used by project icons */
	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}
 
	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","Caption",WS_VISIBLE|WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		640, /* width */
		480, /* height */
		NULL,NULL,hInstance,NULL);
 
	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}
 
	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
