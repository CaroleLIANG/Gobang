#include "AI.h"

AI::AI(board* myBoard)
{
	AIBoard = myBoard;			//���̸�ֵ 
	first = -1;					//Ĭ�Ϻ��� 
	chooseX = chooseY = 7;		//Ĭ�Ϸ�����7 
}

void AI::putChess()
{
	if(AIBoard->now) return;		//����AI��ʱ������ 
	if(first == 1 && AIBoard->chess[7][7] == 0)
	{			//���ֵ�һ��ֱ�����м� 
		AIBoard->chess[7][7] = 1;
	}
	else
	{
		choose();		//ѡ��һ��λ�� 
		AIBoard->chess[chooseX][chooseY] = first;	//�����λ�÷������ǵ����� 
	}
	AIBoard->now = !AIBoard->now;		//�ı���������״̬ 
}

void AI::choose()
{
	board virtual0;		
	srand(time(0));	
	for(int i = 0; i < ROW; i++)
	{
		for(int j = 0; j < COL; j++)
			virtual0.chess[i][j] = AIBoard->chess[i][j];
	}			//����һ����������Ԥ�� 
	int MAX = -1000000;			//����ֵ����Ϊ��С 
	for(int i0 = 0; i0 < ROW; i0++)
	{
		for(int j0 = 0; j0 < COL; j0++)
		{
			if(virtual0.chess[i0][j0] == 0 && isAround(virtual0, i0, j0))
			{			//����ô�û�����ӣ�������Χ������ 
				virtual0.chess[i0][j0] = first;		//��������Ԥ�� 
				if(getGoalOfChess(virtual0,first) >= 100000) 
				{
					MAX = 1000000-rand()%100;
					chooseX = i0;
					chooseY = j0;		//����ܻ�ʤ��ֱ�ӽ�MAXֵ����� 
					virtual0.chess[i0][j0] = 0;		//ȡ���ոշ��õ����� 
				}
				int MIN = 1000000;			//��Сֵ����Ϊ��С 
				bool cut1 = false;
				for(int p0 = 0; p0 < ROW; p0++)
				{
					for(int q0 = 0; q0 < COL; q0++)
					{
						if(virtual0.chess[p0][q0] == 0 && isAround(virtual0, p0, q0))
						{
							virtual0.chess[p0][q0] = -1*first;		//����һ������ 
							if(getGoalOfChess(virtual0,-1*first) >= 100000 && getGoalOfChess(virtual0,first) < 10000) 
							{
								MIN = -1000000+rand()%100;		//������ַ���Ӯ������Сֵ��Ϊ��С 
								cut1 = true;			//�����˴�Ԥ�� 
								virtual0.chess[p0][q0] = 0;		//�ָ����� 
								break;
							}
							int MAX1 = -1000000;
							bool cut2 = false; 
							for(int i1 = 0; i1 < ROW; i1++)			//��һ�㼫��ֵ������ 
							{
								for(int j1 = 0; j1 < ROW; j1++)
								{
									if(virtual0.chess[i1][j1] == 0 && isAround(virtual0, i1, j1))
									{
										virtual0.chess[i1][j1] = first;		//Ԥ��������� 
										if(MAX1 < getGoalOfChess(virtual0,first)-getGoalOfChess(virtual0,-1*first)) 
											MAX1 = getGoalOfChess(virtual0,first)-getGoalOfChess(virtual0,-1*first);
															//�������ֵС������ʽ�����������¸�ֵ 
										virtual0.chess[i1][j1] = 0;		//�ָ����� 
									}
									if(MIN < MAX1) 		//��֦ 
									{
										cut2 = true;
										break; 		
									}	
								}
								if(cut2) break;
							} 
							if(MIN > MAX1) MIN = MAX1;	//�����Сֵ���ڵ���ֵ�����¸�ֵ 
							virtual0.chess[p0][q0]  = 0;	//�ָ����� 
						}
						if(MAX > MIN)				//��֦ 
						{
							cut1 = true;
							break;
						}
					}
					if(cut1) break;
				}
				if(MAX < MIN)		//�������ֵС�ڵ���ֵ 
				{
					MAX = MIN;		//���¸�ֵ 
					chooseX = i0;	//�ı���õ�x��y���� 
					chooseY = j0;
				}
				virtual0.chess[i0][j0] = 0;
			}
		}
	}
}

int AI::getGoalOfPoint(int *a, int color)
{
	if(a[0] == color && a[1] == color && a[2] == color && a[3] == color && a[4] == color) return 100000;  //���� 
	if(a[0] == 0 && a[1] == color && a[2] == color && a[3] == color && a[4] == color && a[5] == 0) return 10000;  //������ 
	if(a[0] == 0 && a[1] == color && a[2] == color && a[3] == color && a[4] == 0) return 1000;				//������ 
	if((a[0] == -1*color && a[1] == color && a[2] == color && a[3] == color && a[4] == color && a[5] == 0) ||
		(a[0] == 0 && a[1] == color && a[2] == color && a[3] == color && a[4] == color && a[5] == -1*color)) return 1000;	//������ 
	if(a[0] == 0 && a[1] == color && a[2] == color && a[3] == 0) return 100;	//����� 
	if((a[0] == -1*color && a[1] == color && a[2] == color && a[3] == color && a[4] == 0) ||
		(a[0] == 0 && a[1] == color && a[2] == color && a[3] == color && a[4] == -1*color)) return 100;	//������ 
	if(a[0] == 0 && a[1] == color && a[2] == 0) return 10;	//��һ�� 
	if((a[0] == -1*color && a[1] == color && a[2] == color && a[3] == 0) ||
		(a[0] == 0 && a[1] == color && a[2] == color && a[3] == -1*color)) return 10;	//������ 
	return 0; 
}

int AI::getGoalOfChess(board nowBoard, int color)
{
	int sumGoal = 0;
	for(int i = 0; i < ROW; i++)
	{
		for(int j = 0; j < COL; j++)		
		{						//ɨ�����еĵ� 
			int line[6];		//��¼�õ�������ߣ�һ������ 
			line[0] = nowBoard.chess[i][j];		//��һ���ǵ�ǰ�� 
			int x1 = i, y1 = j;
			int x2 = i, y2 = j;
			int x3 = i, y3 = j;
			int x4 = i, y4 = j;		//���ĸ�����仯��x��y����	
			for(int it = 1; it < 6; it++)
			{
				y1--;
				if(y1 >= 0) line[it] = nowBoard.chess[i][y1];	//��������ӣ��͸�ֵ 
				else line[it] = -2;		//û�о͸�һ����Чֵ����ͬ 
			}
			sumGoal += getGoalOfPoint(line,color);		//������һ��ķ�ֵ����� 
			for(int it = 1; it < 6; it++)
			{
				x2++; y2--;
				if(y2 >= 0 && x2 < 15) line[it] = nowBoard.chess[x2][y2];
				else line[it] = -2;
			}
			sumGoal += getGoalOfPoint(line,color);
			for(int it = 1; it < 6; it++)
			{
				x3++;
				if(x3 < 15) line[it] = nowBoard.chess[x3][y3];
				else line[it] = -2;
			}
			sumGoal += getGoalOfPoint(line,color);
			for(int it = 1; it < 6; it++)
			{
				x4++; y4++;
				if(x4 < 15 && y4 < 15) line[it] = nowBoard.chess[x4][y4];
				else line[it] = -2;
			}
			sumGoal += getGoalOfPoint(line,color);
		}
	}
	return sumGoal;
}

bool AI::isAround(board nowBoard,int i, int j)
{			//�ж���Χ8������û�����ӣ�������һ��Ϊ�棬��û��Ϊ�� 
	if(j-1 >= 0 && nowBoard.chess[i][j-1] != 0) return true;
	if(j-1 >= 0 && i+1 < 15 && nowBoard.chess[i+1][j-1] != 0) return true;
	if(i+1 < 15 && nowBoard.chess[i+1][j] != 0) return true;
	if(j+1 < 15 && i+1 < 15 && nowBoard.chess[i+1][j+1] != 0) return true;
	if(j+1 < 15 && nowBoard.chess[i][j+1] != 0) return true;
	if(i-1 >= 0 && j+1 < 15 && nowBoard.chess[i-1][j+1] != 0) return true;
	if(i-1 >= 0 && nowBoard.chess[i-1][j] != 0) return true;
	if(i-1 >= 0 && j-1 >= 0 && nowBoard.chess[i-1][j-1] != 0) return true;
	return false;
}





