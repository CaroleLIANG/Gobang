#include "human.h"

human::human(board * myBoard)
{
	humanBoard = myBoard;		//棋盘赋值 
	first = 1;				//人类默认先手 
}

void human::putChess(int x, int y)
{
	if(!humanBoard->now) return;		//如果不是人类下，则放置棋子无效 
	int index_x = 0;
	int index_y = 0;
	if(x > 50) index_x = (x-50)/40+1;
	if(y > 50) index_y = (y-50)/40+1;		//根据鼠标点击的位置，计算放置棋子的下标 
	if(humanBoard->chess[index_x][index_y] == 0)
	{
		humanBoard->chess[index_x][index_y] = first;		//将该坐标放置上我们的棋子 
		humanBoard->now = !humanBoard->now;				//改变下棋次序的状态 
	}
}

