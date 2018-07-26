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
	}				//Ϊ���������ڴ沢��ʼ�� 
	now = true;
	runState = true;		//��ʼ������ 
	RED_PEN = CreatePen(PS_SOLID, 0, RGB(255,0,0)); //�����Զ��廭�� 
}

void board::darwBroad(HDC hdc, int chooseX, int chooseY)
{
	for(int x = 0; x < ROW; x++)
	{
		MoveToEx(hdc,x*WIDTH+30,30,NULL);		//���������� 
		LineTo(hdc,x*WIDTH+30,HEIGHT*(COL-1)+30);
	}
	for(int y = 0; y < COL; y++)
	{													
		MoveToEx(hdc,30,y*HEIGHT+30,NULL);		//�����̺��� 
		LineTo(hdc,WIDTH*(ROW-1)+30,y*HEIGHT+30);
	}
	HBRUSH blackBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
	HBRUSH whiteBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);//ȡ��ϵͳ�Զ���ĺ�ɫ�Ͱ�ɫ��ˢ 
	SelectObject (hdc, blackBrush);		//ѡ���ɫ��ˢ	
	Ellipse(hdc,306,306,314,314);		//����Ԫ�� 
	for(int i = 0; i < ROW; i++)
	{
		for(int j = 0; j < COL; j++)
		{
			if(chess[i][j] == 1)				//�����������1 
			{
				SelectObject (hdc, blackBrush);
				Ellipse(hdc,i*40+15,j*40+15,i*40+45,j*40+45);		//����ɫ���� 
				if(i == chooseX && j == chooseY)
				{
					SelectObject (hdc, RED_PEN);			//ѡ���ɫ���� 
					Ellipse(hdc,i*40+15,j*40+15,i*40+45,j*40+45);		//ΪAI�����ӻ���Ȧ 
					SelectObject (hdc, (HPEN)GetStockObject( BLACK_PEN ));	//�ָ�ϵͳ�ĺ�ɫ���� 
				}
			} 
			else if(chess[i][j] == -1)			//�����������-1 
			{
				SelectObject (hdc, whiteBrush);			
				Ellipse(hdc,i*40+15,j*40+15,i*40+45,j*40+45);		//����ɫ���� 
				if(i == chooseX && j == chooseY)
				{
					SelectObject (hdc, RED_PEN);			//ѡ���ɫ���� 
					Ellipse(hdc,i*40+15,j*40+15,i*40+45,j*40+45);		//ΪAI�����ӻ���Ȧ 
					SelectObject (hdc, (HPEN)GetStockObject( BLACK_PEN ));  //�ָ�ϵͳ�ĺ�ɫ���� 
				}
			}
		}
	}
}

void board::reset()			//���ú��� 
{
	for(int i = 0; i < ROW; i++)
	{
		for(int j = 0; j < COL; j++)
			chess[i][j] = 0;			//������������λ����Ϊ0 
	}
	now = true;
	runState = true;			//�����ٶȳ�ʼ�� 
} 

int board::checkBoard(int color)		//��������Ƿ����color��ɫ��ʤ�� 
{
	int sum = 0;					//sum�����������ߵ����� 
	for(int i = 0; i < ROW; i++)
	{
		for(int j = 0; j < COL; j++)
		{
			int x1 = i, y1 = j, count1 = 0;
			int x2 = i, y2 = j, count2 = 0;
			int x3 = i, y3 = j, count3 = 0;
			int x4 = i, y4 = j, count4 = 0;		//�ĸ������x��y���� 
			if(chess[i][j] != color) continue; 		//�������㲻��colorֱ������ 
			for(int it = 0; it < 4; it++)
			{		//���ĸ����������Ĳ㣬���Ĳ㶼Ϊcolorɫ����sum++��sum>0����ʤ�� 
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


