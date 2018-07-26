#include <windows.h>
#include "board.h"
#include "AI.h"
#include "human.h"
#include "resources.h"
/* This is where all the input to the window goes to */
board myBoard;
AI AIplayer(&myBoard);
human humanPlayer(&myBoard);
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	
	switch(Message) {
		HDC hdc;
		PAINTSTRUCT ps;
		
		case WM_LBUTTONDOWN:		//检测鼠标的点击消息 
		{
			hdc=GetDC(hwnd);		//获取窗口句柄 
			int winner;
			int x = LOWORD (lParam);
			int y = HIWORD (lParam);		//获取鼠标点击的位置 
			if(myBoard.runState) 			//棋局处于正常下棋状态 
			{
				humanPlayer.putChess(x,y);		//人根据坐标落子 
				myBoard.darwBroad(hdc);			//重画棋盘 
				winner = myBoard.checkBoard(humanPlayer.first);			//判断游戏是否结束 
				if(winner > 0) MessageBox(hwnd,"  你赢啦！！！","游戏结束",MB_ICONWARNING|MB_OK);
												//结束则输出提示信息 
			}
			
			if(myBoard.runState)			//棋局处于正常下棋状态 
			{
				AIplayer.putChess();		//AI落子 
				myBoard.darwBroad(hdc,AIplayer.chooseX, AIplayer.chooseY);		//重画棋盘 
				winner = myBoard.checkBoard(AIplayer.first);			//判断游戏是否结束 
				if(winner > 0) MessageBox(hwnd,"  你输咯！！！","游戏结束",MB_ICONWARNING|MB_OK);
												//结束则输出提示信息 
			} 
			
			if(!myBoard.runState) 			//如果棋局状态已经结束 
			{
				if(MessageBox(hwnd,"你要再来一次吗？","再来一次",MB_ICONQUESTION|MB_YESNO) == IDYES)
				{							//询问是否再来一次 
					myBoard.reset();			//是的话则重置棋盘 
					SendMessage(hwnd,WM_PAINT,0,0);		//发送重画棋盘的消息 
				}
				else SendMessage(hwnd,WM_DESTROY,0,0);		//否的话发送销毁窗口的消息 
				
			}
			ReleaseDC(hwnd,hdc);		//释放窗口句柄 
			return 0;
		} 
		case WM_PAINT:					
		{
			InvalidateRect (hwnd, NULL, TRUE);
			hdc = BeginPaint (hwnd, &ps);
			myBoard.darwBroad(hdc);			//画出初始棋盘 
			if(MessageBox(hwnd,"请选择是否先手（执黑子）","选择先手",MB_ICONQUESTION|MB_YESNO) == IDYES)
			{									//询问是否先手 
				myBoard.now = true;				//先手就将当前落子状态设为true 
				humanPlayer.first = 1;			//人类的first设为 1
				AIplayer.first = -1;			//AI的first设为-1 
			}
			else 
			{
				myBoard.now = false;		//后手则将 
				humanPlayer.first = -1;
				AIplayer.first = 1;
				AIplayer.putChess();
				myBoard.darwBroad(hdc,AIplayer.chooseX, AIplayer.chooseY);
			}
			EndPaint (hwnd, &ps);
			return 0;
		}
		
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(255,200,30)); 
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = NULL; /* Load a standard icon */
	wc.hIconSm		 = LoadIcon(hInstance, "A"); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","五子棋",WS_VISIBLE|WS_SYSMENU,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		630, /* width */
		650, /* height */
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
