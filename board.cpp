#include "board.h"

board::board()
{
	chess = new int* [ROW];
	for(int i = 0; i < ROW; i++)
	{
		chess[i] = new int[COL];
	}
	for(int i = 0; i < ROW; i++)
	{
		for(int j = 0; j < COL; j++)
			chess[i][j] = 0;
	}				//为棋盘申请内存并初始化 
	now = true;
	runState = true;		//初始化变量 
	RED_PEN = CreatePen(PS_SOLID, 0, RGB(255,0,0)); //创建自定义画笔 
}

void board::darwBroad(HDC hdc, int chooseX, int chooseY)
{
	for(int x = 0; x < ROW; x++)
	{
		MoveToEx(hdc,x*WIDTH+30,30,NULL);		//画棋盘竖线 
		LineTo(hdc,x*WIDTH+30,HEIGHT*(COL-1)+30);
	}
	for(int y = 0; y < COL; y++)
	{													
		MoveToEx(hdc,30,y*HEIGHT+30,NULL);		//画棋盘横线 
		LineTo(hdc,WIDTH*(ROW-1)+30,y*HEIGHT+30);
	}
	HBRUSH blackBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
	HBRUSH whiteBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);//取得系统自定义的黑色和白色画刷 
	SelectObject (hdc, blackBrush);		//选择黑色画刷	
	Ellipse(hdc,306,306,314,314);		//画天元点 
	for(int i = 0; i < ROW; i++)
	{
		for(int j = 0; j < COL; j++)
		{
			if(chess[i][j] == 1)				//如果数组中是1 
			{
				SelectObject (hdc, blackBrush);
				Ellipse(hdc,i*40+15,j*40+15,i*40+45,j*40+45);		//画黑色棋子 
				if(i == chooseX && j == chooseY)
				{
					SelectObject (hdc, RED_PEN);			//选择红色画笔 
					Ellipse(hdc,i*40+15,j*40+15,i*40+45,j*40+45);		//为AI的落子画红圈 
					SelectObject (hdc, (HPEN)GetStockObject( BLACK_PEN ));	//恢复系统的黑色画笔 
				}
			} 
			else if(chess[i][j] == -1)			//如果数组中是-1 
			{
				SelectObject (hdc, whiteBrush);			
				Ellipse(hdc,i*40+15,j*40+15,i*40+45,j*40+45);		//画白色棋子 
				if(i == chooseX && j == chooseY)
				{
					SelectObject (hdc, RED_PEN);			//选择红色画笔 
					Ellipse(hdc,i*40+15,j*40+15,i*40+45,j*40+45);		//为AI的落子画红圈 
					SelectObject (hdc, (HPEN)GetStockObject( BLACK_PEN ));  //恢复系统的黑色画笔 
				}
			}
		}
	}
}

void board::reset()			//重置函数 
{
	for(int i = 0; i < ROW; i++)
	{
		for(int j = 0; j < COL; j++)
			chess[i][j] = 0;			//将数组中所有位置置为0 
	}
	now = true;
	runState = true;			//变量再度初始化 
} 

int board::checkBoard(int color)		//检测棋盘是否出现color颜色的胜局 
{
	int sum = 0;					//sum代表五子连线的数量 
	for(int i = 0; i < ROW; i++)
	{
		for(int j = 0; j < COL; j++)
		{
			int x1 = i, y1 = j, count1 = 0;
			int x2 = i, y2 = j, count2 = 0;
			int x3 = i, y3 = j, count3 = 0;
			int x4 = i, y4 = j, count4 = 0;		//四个方向的x，y坐标 
			if(chess[i][j] != color) continue; 		//如果这个点不是color直接跳出 
			for(int it = 0; it < 4; it++)
			{		//朝四个方向搜索四层，若四层都为color色，则sum++，sum>0则有胜局 
				y1--;
				if(y1 >= 0)
				{
					if(chess[x1][y1] == color) count1++;
					if(count1 == 4) sum++;
				} 
				x2++; y2--;
				if(y2 >= 0 && x2 < 15)
				{
					if(chess[x2][y2] == color) count2++;
					if(count2 == 4) sum++;
				} 
				x3++;
				if(x3 < 15)
				{
					if(chess[x3][y3] == color) count3++;
					if(count3 == 4) sum++;
				} 
				x4++; y4++;
				if(x4 < 15 && y4 < 15)
				{
					if(chess[x4][y4] == color) count4++;
					if(count4 == 4) sum++;
				} 
			}
		}
	}
	if(sum > 0) runState = false;
	return sum;
}


