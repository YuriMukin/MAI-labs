#pragma once
#include "Cell.h"
#include <vector>
#include <list>
#include "Dot.h"

class Game_Life
{
public:
	int NumOfLive;
	int iteration;
	int border;
	Cell Field[101][101][101];
	glm::vec3* AliveArr;

	Game_Life(int Bmin, int Bmax, int Smin, int Smax, Dot inArr[], int ln, bool closed)
	{
		Beath[0] = Bmin; Beath[1] = Bmax;
		Death[0] = Smin; Death[2] = Smax;
		iteration = 1;
		if (closed)
			border = 101;
		else 
			border = 100;
		GenStart(inArr, ln);
	}

	void WhoIsAlive()//обновление поля
	{
		std::list<glm::vec3> Live;
		int Neighbors = 0;
		float norm;
		NumOfLive = 0;
		for (int x = 0; x < border; x++)
			for (int y = 0; y < border; y++)
				for (int z = 0; z < border; z++)
				{
					Neighbors = NumOfNeighbors(x, y, z);
					if (Neighbors >= Beath[0] && Neighbors <= Beath[1] && !Field[x][y][z].IsLive)
					{
						int xs = x; int ys = y; int zs = z;
						if (x < 100 && y < 100 && z < 100)
						{
							Field[x][y][z].nextS = true;
							norm = 1 / (sqrt(Neighbors * Neighbors * 3));
							Field[xs][ys][zs].collor.x = 0.001; Field[xs][ys][zs].collor.y = 0.001; Field[xs][ys][zs].collor.z = Neighbors * norm;
							Live.push_back(Field[x][y][z].position);
							NumOfLive++;
						}
						else
						{
							if (x == 100)
								xs = 0;
							if (y == 100)
								ys = 0;
							if (z == 100)
								zs = 0;
							Field[xs][ys][zs].nextS = true;
							norm = 1 / (sqrt(Neighbors * Neighbors * 3));
							Field[xs][ys][zs].collor.x = 0.001; Field[xs][ys][zs].collor.y = 0.001; Field[xs][ys][zs].collor.z = Neighbors * norm;
							Live.push_back(Field[xs][ys][zs].position);
							NumOfLive++;
						}
					}
					else if (Neighbors >= Death[0] && Neighbors <= Death[1] && Field[x][y][z].IsLive)
					{
						int xs = x; int ys = y; int zs = z;
						if (x < 100 && y < 100 && z < 100)
						{
							Field[x][y][z].nextS = true;
							norm = 1 / (sqrt(Neighbors * Neighbors * 3));
							Field[xs][ys][zs].collor.x = 0.001; Field[xs][ys][zs].collor.y = 0.001; Field[xs][ys][zs].collor.z = Neighbors * norm;
							Live.push_back(Field[x][y][z].position);
							NumOfLive++;
						}
						else
						{
							if (x == 100)
								xs = 0;
							if (y == 100)
								ys = 0;
							if (z == 100)
								zs = 0;
							Field[xs][ys][zs].nextS = true;
							norm = 1 / (sqrt(Neighbors * Neighbors * 3));
							Field[xs][ys][zs].collor.x = 0.001; Field[xs][ys][zs].collor.y = 0.001; Field[xs][ys][zs].collor.z = Neighbors * norm;
							Live.push_back(Field[xs][ys][zs].position);
							NumOfLive++;
						}
					}
					else if (Neighbors <= Death[0] && Neighbors >= Death[1] && Field[x][y][z].IsLive)
					{
						norm = 1 / (sqrt(Neighbors * Neighbors * 3));
						Field[x][y][z].collor.x = Neighbors * norm; Field[x][y][z].collor.y = 0.001; Field[x][y][z].collor.z = 0.001;
						Field[x][y][z].nextS = false;
					}
				}
		for (int x = 0; x < 100; x++)
			for (int y = 0; y < 100; y++)
				for (int z = 0; z < 100; z++)
					Field[x][y][z].IsLive = Field[x][y][z].nextS;
		delete AliveArr;
		AliveArr = new glm::vec3[NumOfLive];
		for (int l = 0; l < NumOfLive; l++)
		{
			AliveArr[l] = Live.front();
			Live.pop_front();
		}
		if (NumOfLive == 0)
		{
			iteration++;
			GenStart(NULL,0);
		}
	}

private:
	int Beath[2]; int Death[2];
	int x; int y; int z;

	void GenStart(Dot inArr[], int ln)//генирация стартового набора клеток
	{
		srand(iteration);
		int tmp;
		int count = 0;
		for (int i = 0; i < 100; i++)
			for (int j = 0; j < 100; j++)
				for (int k = 0; k < 100; k++)
				{
					if (ln == NULL)
					{
						tmp = rand() % 10;
						if (tmp > 8)
						{
							Field[i][j][k].SetPosition(i, j, k, 1);
							count++;
						}
						else
							Field[i][j][k].SetPosition(i, j, k, 0);
					}
					else
					{
						bool tm = 0;
						for (int t = 0; t < ln; t++)
						{
							tm = ((inArr[t].X == i) && (inArr[t].Y == j) && (inArr[t].Z == k));
							if (tm)
								break;
						}
						Field[i][j][k].SetPosition(i, j, k, tm);
					}
				}
	}

	int NumOfNeighbors(float x, float y, float z)//подсчет соседей 
	{
		int count = 0;
		for (int i = x - 1; i < x + 1; i++)
			for (int j = y - 1; j < y + 1; j++)
				for (int k = z - 1; k < z + 1; k++)
					if (i >= 0 && i < 100 && j >= 0 && j < 100 && k >= 0 && k < 100)
						if (Field[i][j][k].IsLive)
							count++;
		return count;
	}
};