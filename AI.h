#ifndef AI_H
#define AI_H
#include "board.h"
class AI
{
public:
	AI(board* myBoard);		//���캯�� 
	void putChess();		//�������� 
	void choose();			//�����������ӵ�λ�� 
	int first;				//�Ƿ����֣�1�����֣�-1�Ǻ��� 
	int chooseX;			//�����������ӵ�X���� 
	int chooseY;			//�����������ӵ�y���� 
private:
	board* AIBoard;		//AI������ 
	int getGoalOfPoint(int *a, int color);		//����ĳһ��ķ�ֵ 
	int getGoalOfChess(board nowBoard, int color);		//�����������̵ķ�ֵ 
	bool isAround(board nowBoard,int i, int j);		//�ж�ĳһ����Χ�Ƿ������� 
};

#endif
