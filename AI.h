#ifndef AI_H
#define AI_H
#include "board.h"
class AI
{
public:
	AI(board* myBoard);		//构造函数 
	void putChess();		//放置棋子 
	void choose();			//产生放置棋子的位置 
	int first;				//是否先手，1是先手，-1是后手 
	int chooseX;			//产生放置棋子的X坐标 
	int chooseY;			//产生放置棋子的y坐标 
private:
	board* AIBoard;		//AI的棋盘 
	int getGoalOfPoint(int *a, int color);		//计算某一点的分值 
	int getGoalOfChess(board nowBoard, int color);		//计算整个棋盘的分值 
	bool isAround(board nowBoard,int i, int j);		//判断某一点周围是否有棋子 
};

#endif
