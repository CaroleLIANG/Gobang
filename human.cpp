#include "human.h"

human::human(board * myBoard)
{
	humanBoard = myBoard;		//���̸�ֵ 
	first = 1;				//����Ĭ������ 
}

void human::putChess(int x, int y)
{
	if(!humanBoard->now) return;		//������������£������������Ч 
	int index_x = 0;
	int index_y = 0;
	if(x > 50) index_x = (x-50)/40+1;
	if(y > 50) index_y = (y-50)/40+1;		//�����������λ�ã�����������ӵ��±� 
	if(humanBoard->chess[index_x][index_y] == 0)
	{
		humanBoard->chess[index_x][index_y] = first;		//����������������ǵ����� 
		humanBoard->now = !humanBoard->now;				//�ı���������״̬ 
	}
}

