#ifndef HUMAN_H
#define HUMAN_H
#include "board.h"
class human
{
public:
	human(board *myBoard);		//���캯�� 
	void putChess(int x, int y);	//�������� 
	board *humanBoard;		//��������� 
	int first; 				//�Ƿ����֣�1�����֣�-1�Ǻ��� 
};

#endif
