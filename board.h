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
	board();		//���캯�� 
	void darwBroad(HDC hdc, int chooseX = -1, int chooseY = -1);  		//�����̣�chooseX��chooseY ΪAI�ո����ӵ�λ�� 
	void reset();		//�������� 
	int checkBoard(int color);		//��������Ƿ����һ����ʤ������color���� 
	int **chess;		//�洢������Ϣ�Ķ�ά���� 
	bool now; 			//��ǰӦ�����ӵ����֣�trueΪ�ˣ�falseΪAI 
	bool runState;		//��������״̬��false��������ѽ��� 
	HPEN RED_PEN;		//�Զ����һ������ 
};

#endif
