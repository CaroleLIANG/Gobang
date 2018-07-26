#ifndef BOARD_H
#define BOARD_H
#include <windows.h>
#include <bits/stdc++.h>   
#define ROW 15
#define COL 15
#define WIDTH 40
#define HEIGHT 40
class board
{
public:
	board();		//构造函数 
	void darwBroad(HDC hdc, int chooseX = -1, int chooseY = -1);  		//画棋盘，chooseX，chooseY 为AI刚刚落子的位置 
	void reset();		//重置棋盘 
	int checkBoard(int color);		//检测棋盘是否出现一方获胜的现象（color方） 
	int **chess;		//存储棋盘信息的二维数组 
	bool now; 			//当前应当落子的棋手，true为人，false为AI 
	bool runState;		//棋盘运行状态，false代表棋局已结束 
	HPEN RED_PEN;		//自定义的一个画笔 
};

#endif
