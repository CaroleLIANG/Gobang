#ifndef HUMAN_H
#define HUMAN_H
#include "board.h"
class human
{
public:
	human(board *myBoard);		//构造函数 
	void putChess(int x, int y);	//放置棋子 
	board *humanBoard;		//人类的棋盘 
	int first; 				//是否先手，1是先手，-1是后手 
};

#endif
