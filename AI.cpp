#include "AI.h"

AI::AI(board* myBoard)
{
	AIBoard = myBoard;			//棋盘赋值 
	first = -1;					//默认后手 
	chooseX = chooseY = 7;		//默认放置在7 
}

void AI::putChess()
{
	if(AIBoard->now) return;		//不是AI下时，跳过 
	if(first == 1 && AIBoard->chess[7][7] == 0)
	{			//先手第一步直接下中间 
		AIBoard->chess[7][7] = 1;
	}
	else
	{
		choose();		//选择一个位置 
		AIBoard->chess[chooseX][chooseY] = first;	//将这个位置放置我们的棋子 
	}
	AIBoard->now = !AIBoard->now;		//改变下棋次序的状态 
}

void AI::choose()
{
	board virtual0;		
	srand(time(0));	
	for(int i = 0; i < ROW; i++)
	{
		for(int j = 0; j < COL; j++)
			virtual0.chess[i][j] = AIBoard->chess[i][j];
	}			//拷贝一个棋盘用来预估 
	int MAX = -1000000;			//极大值先设为最小 
	for(int i0 = 0; i0 < ROW; i0++)
	{
		for(int j0 = 0; j0 < COL; j0++)
		{
			if(virtual0.chess[i0][j0] == 0 && isAround(virtual0, i0, j0))
			{			//如果该处没有棋子，并且周围有棋子 
				virtual0.chess[i0][j0] = first;		//放置棋子预测 
				if(getGoalOfChess(virtual0,first) >= 100000) 
				{
					MAX = 1000000-rand()%100;
					chooseX = i0;
					chooseY = j0;		//如果能获胜，直接将MAX值设最大 
					virtual0.chess[i0][j0] = 0;		//取消刚刚放置的棋子 
				}
				int MIN = 1000000;			//极小值先设为最小 
				bool cut1 = false;
				for(int p0 = 0; p0 < ROW; p0++)
				{
					for(int q0 = 0; q0 < COL; q0++)
					{
						if(virtual0.chess[p0][q0] == 0 && isAround(virtual0, p0, q0))
						{
							virtual0.chess[p0][q0] = -1*first;		//放置一个棋子 
							if(getGoalOfChess(virtual0,-1*first) >= 100000 && getGoalOfChess(virtual0,first) < 10000) 
							{
								MIN = -1000000+rand()%100;		//如果对手方能赢，将极小值设为最小 
								cut1 = true;			//跳出此次预测 
								virtual0.chess[p0][q0] = 0;		//恢复棋盘 
								break;
							}
							int MAX1 = -1000000;
							bool cut2 = false; 
							for(int i1 = 0; i1 < ROW; i1++)			//又一层极大值的搜索 
							{
								for(int j1 = 0; j1 < ROW; j1++)
								{
									if(virtual0.chess[i1][j1] == 0 && isAround(virtual0, i1, j1))
									{
										virtual0.chess[i1][j1] = first;		//预测放置棋子 
										if(MAX1 < getGoalOfChess(virtual0,first)-getGoalOfChess(virtual0,-1*first)) 
											MAX1 = getGoalOfChess(virtual0,first)-getGoalOfChess(virtual0,-1*first);
															//如果极大值小于启发式函数，就重新赋值 
										virtual0.chess[i1][j1] = 0;		//恢复棋盘 
									}
									if(MIN < MAX1) 		//剪枝 
									{
										cut2 = true;
										break; 		
									}	
								}
								if(cut2) break;
							} 
							if(MIN > MAX1) MIN = MAX1;	//如果极小值大于倒推值，重新赋值 
							virtual0.chess[p0][q0]  = 0;	//恢复棋盘 
						}
						if(MAX > MIN)				//剪枝 
						{
							cut1 = true;
							break;
						}
					}
					if(cut1) break;
				}
				if(MAX < MIN)		//如果极大值小于倒推值 
				{
					MAX = MIN;		//重新赋值 
					chooseX = i0;	//改变放置的x，y坐标 
					chooseY = j0;
				}
				virtual0.chess[i0][j0] = 0;
			}
		}
	}
}

int AI::getGoalOfPoint(int *a, int color)
{
	if(a[0] == color && a[1] == color && a[2] == color && a[3] == color && a[4] == color) return 100000;  //五子 
	if(a[0] == 0 && a[1] == color && a[2] == color && a[3] == color && a[4] == color && a[5] == 0) return 10000;  //活四子 
	if(a[0] == 0 && a[1] == color && a[2] == color && a[3] == color && a[4] == 0) return 1000;				//活三子 
	if((a[0] == -1*color && a[1] == color && a[2] == color && a[3] == color && a[4] == color && a[5] == 0) ||
		(a[0] == 0 && a[1] == color && a[2] == color && a[3] == color && a[4] == color && a[5] == -1*color)) return 1000;	//死四子 
	if(a[0] == 0 && a[1] == color && a[2] == color && a[3] == 0) return 100;	//活二子 
	if((a[0] == -1*color && a[1] == color && a[2] == color && a[3] == color && a[4] == 0) ||
		(a[0] == 0 && a[1] == color && a[2] == color && a[3] == color && a[4] == -1*color)) return 100;	//死三子 
	if(a[0] == 0 && a[1] == color && a[2] == 0) return 10;	//活一子 
	if((a[0] == -1*color && a[1] == color && a[2] == color && a[3] == 0) ||
		(a[0] == 0 && a[1] == color && a[2] == color && a[3] == -1*color)) return 10;	//死二子 
	return 0; 
}

int AI::getGoalOfChess(board nowBoard, int color)
{
	int sumGoal = 0;
	for(int i = 0; i < ROW; i++)
	{
		for(int j = 0; j < COL; j++)		
		{						//扫描所有的点 
			int line[6];		//记录该点出发的线，一个六个 
			line[0] = nowBoard.chess[i][j];		//第一个是当前点 
			int x1 = i, y1 = j;
			int x2 = i, y2 = j;
			int x3 = i, y3 = j;
			int x4 = i, y4 = j;		//朝四个方向变化的x，y坐标	
			for(int it = 1; it < 6; it++)
			{
				y1--;
				if(y1 >= 0) line[it] = nowBoard.chess[i][y1];	//如果有棋子，就赋值 
				else line[it] = -2;		//没有就赋一个无效值，下同 
			}
			sumGoal += getGoalOfPoint(line,color);		//计算这一点的分值后相加 
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
{			//判断周围8个点有没有棋子，有任意一个为真，都没有为假 
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





