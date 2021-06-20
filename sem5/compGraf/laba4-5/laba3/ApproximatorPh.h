#pragma once
#include <GL/glew.h>
#include <iostream>
#include <glm\trigonometric.hpp>
#include "surface.h"
#include "Dot.h"

class ApproximatorPh
{
public:
	GLfloat* PointSet;
	int weight;

	ApproximatorPh(GLfloat  Rt, GLfloat  Rb, GLfloat  hu, GLfloat  hd)
	{
		Rtop = Rt;
		Rbottom = Rb;
		heghtU = hu;
		heghtD = hd;
		weight = 0;
	}

	void Approximaze(int  pr)
	{
		Dot* t = ApproximatorPh::GenCircleR(pr); // генирируем набор окружностей между 2 заданными 
		Surfase* s = new Surfase[pr * (pr - 2)*4];
		int count = 0;
		int offset = 0;
		ApproximatorPh::PointSet = new GLfloat[pr * (pr - 2) * 72];
		for (int i = 0; i < pr * (pr - 2) * 72; i++)
			PointSet[i] = 25;
		for (int j = 0; j < pr - 2; j++) // генирируем итоговую фигуру по слоям 
		{
			Dot* CrTop = ApproximatorPh::GenCircle(t[j].X, t[j].Y, pr); // выбираем 2 соседние окружности
			Dot* CrDown = ApproximatorPh::GenCircle(t[j + 1].X, t[j + 1].Y, pr);
			for (int i = 1; i <= pr; i++)
			{
				if (j == 0)
				{
					PointSet[0 + offset] = CrTop[i - 1].X; PointSet[1 + offset] = CrTop[i - 1].Y; PointSet[2 + offset] = CrTop[i - 1].Z;
					PointSet[6 + offset] = 0; PointSet[7 + offset] = CrTop[i].Y; PointSet[8 + offset] = 0;
					PointSet[12 + offset] = CrTop[i].X; PointSet[13 + offset] = CrTop[i].Y; PointSet[14 + offset] = CrTop[i].Z;
					offset += 18;
					s[count] = Surfase(CrTop[i - 1], Dot(0, CrTop[i].Y, 0), CrTop[i]);
					count += 1;
				}
				if (j == pr - 3)
				{
					PointSet[0 + offset] = 0; PointSet[1 + offset] = CrDown[i].Y; PointSet[2 + offset] = 0;
					PointSet[6 + offset] = CrDown[i - 1].X; PointSet[7 + offset] = CrDown[i - 1].Y; PointSet[8 + offset] = CrDown[i - 1].Z;
					PointSet[12 + offset] = CrDown[i].X; PointSet[13 + offset] = CrDown[i].Y; PointSet[14 + offset] = CrDown[i].Z;
					offset += 18;
					s[count] = Surfase(Dot(0, CrDown[i].Y, 0), CrDown[i - 1], CrDown[i]);
					count += 1;
				}
				PointSet[0 + offset] = CrTop[i - 1].X; PointSet[1 + offset] = CrTop[i - 1].Y; PointSet[2 + offset] = CrTop[i - 1].Z;
				PointSet[6 + offset] = CrDown[i].X; PointSet[7 + offset] = CrDown[i].Y; PointSet[8 + offset] = CrDown[i].Z;
				PointSet[12 + offset] = CrDown[i - 1].X; PointSet[13 + offset] = CrDown[i - 1].Y; PointSet[14 + offset] = CrDown[i - 1].Z;
				offset += 18;
				s[count] = Surfase(CrTop[i - 1], CrDown[i], CrDown[i - 1]);
				count += 1;

				PointSet[0 + offset] = CrTop[i - 1].X; PointSet[1 + offset] = CrTop[i - 1].Y; PointSet[2 + offset] = CrTop[i - 1].Z;
				PointSet[6 + offset] = CrTop[i].X; PointSet[7 + offset] = CrTop[i].Y; PointSet[8 + offset] = CrTop[i].Z;
				PointSet[12 + offset] = CrDown[i].X; PointSet[13 + offset] = CrDown[i].Y; PointSet[14 + offset] = CrDown[i].Z;
				offset += 18;
				s[count] = Surfase(CrTop[i - 1], CrTop[i], CrDown[i]);
				count += 1;
			}
		}
		ApproximatorPh::weight = count * 18;
		int in = 0; double delta = 0.000001; offset = 0;  Dot norm(0, 0, 0);
		for (int j = 0; j < pr - 2; j++) // генирируем итоговую фигуру по слоям 
		{
			for (int i = 1; i <= pr; i++)
			{
				if (j == 0)
				{
					norm.SetCord(0, 0, 0);
					in = 0; 
					for (int k = 0; k < count; k++)
					{
						if (s[k].IsIn(Dot(PointSet[0 + offset], PointSet[1 + offset], PointSet[2 + offset]), delta))
						{
							norm.X -= s[k].xn; norm.Y -= s[k].yn; norm.Z -= s[k].zn;
							in++;
						}
						if (in >= 5)
							break;
					}
					norm.Normolize();
					PointSet[3 + offset] = norm.X; PointSet[4 + offset] = norm.Y; PointSet[5 + offset] = norm.Z;
					norm.SetCord(0, 0, 0);
					in = 0;
					for (int k = 0; k < count; k++)
					{
						if (s[k].IsIn(Dot(PointSet[6 + offset], PointSet[7 + offset], PointSet[8 + offset]), delta))
						{
							norm.X -= s[k].xn; norm.Y -= s[k].yn; norm.Z -= s[k].zn;
							in++;
						}
						if (in >= 5)
							break;
					}
					norm.Normolize();
					PointSet[9 + offset] = norm.X; PointSet[10 + offset] = norm.Y; PointSet[11 + offset] = norm.Z;
					norm.SetCord(0, 0, 0);
					in = 0;
					for (int k = 0; k < count; k++)
					{
						if (s[k].IsIn(Dot(PointSet[12 + offset], PointSet[13 + offset], PointSet[14 + offset]), delta))
						{
							norm.X -= s[k].xn; norm.Y -= s[k].yn; norm.Z -= s[k].zn;
							in++;
						}
						if (in >= 5)
							break;
					}
					norm.Normolize();
					PointSet[15 + offset] = norm.X; PointSet[16 + offset] = norm.Y; PointSet[17 + offset] = norm.Z;
					offset += 18;
				}
				if (j == pr - 3)
				{

					norm.SetCord(0, 0, 0);
					in = 0;
					for (int k = 0; k < count; k++)
					{
						if (s[k].IsIn(Dot(PointSet[0 + offset], PointSet[1 + offset], PointSet[2 + offset]), delta))
						{
							norm.X -= s[k].xn; norm.Y -= s[k].yn; norm.Z -= s[k].zn;
							in++;
						}
						if (in >= 5)
							break;
					}
					norm.Normolize();
					PointSet[3 + offset] = norm.X; PointSet[4 + offset] = norm.Y; PointSet[5 + offset] = norm.Z;
					norm.SetCord(0, 0, 0);
					in = 0;
					for (int k = 0; k < count; k++)
					{
						if (s[k].IsIn(Dot(PointSet[6 + offset], PointSet[7 + offset], PointSet[8 + offset]), delta))
						{
							norm.X -= s[k].xn; norm.Y -= s[k].yn; norm.Z -= s[k].zn;
							in++;
						}
						if (in >= 5)
							break;
					}
					norm.Normolize();
					PointSet[9 + offset] = norm.X; PointSet[10 + offset] = norm.Y; PointSet[11 + offset] = norm.Z;
					norm.SetCord(0, 0, 0);
					in = 0;
					for (int k = 0; k < count; k++)
					{
						if (s[k].IsIn(Dot(PointSet[12 + offset], PointSet[13 + offset], PointSet[14 + offset]), delta))
						{
							norm.X -= s[k].xn; norm.Y -= s[k].yn; norm.Z -= s[k].zn;
							in++;
						}
						if (in >= 5)
							break;
					}
					norm.Normolize();
					PointSet[15 + offset] = norm.X; PointSet[16 + offset] = norm.Y; PointSet[17 + offset] = norm.Z;
					offset += 18;
				}
				norm.SetCord(0, 0, 0);
				in = 0;
				for (int k = 0; k < count; k++)
				{
					if (s[k].IsIn(Dot(PointSet[0 + offset], PointSet[1 + offset], PointSet[2 + offset]), delta))
					{
						norm.X -= s[k].xn; norm.Y -= s[k].yn; norm.Z -= s[k].zn;
						in++;
					}
					if (in >= 5)
						break;
				}
				norm.Normolize();
				PointSet[3 + offset] = norm.X; PointSet[4 + offset] = norm.Y; PointSet[5 + offset] = norm.Z;
				norm.SetCord(0, 0, 0);
				in = 0;
				for (int k = 0; k < count; k++)
				{
					if (s[k].IsIn(Dot(PointSet[6 + offset], PointSet[7 + offset], PointSet[8 + offset]), delta))
					{
						norm.X -= s[k].xn; norm.Y -= s[k].yn; norm.Z -= s[k].zn;
						in++;
					}
					if (in >= 5)
						break;
				}
				norm.Normolize();
				PointSet[9 + offset] = norm.X; PointSet[10 + offset] = norm.Y; PointSet[11 + offset] = norm.Z;
				norm.SetCord(0, 0, 0);
				in = 0;
				for (int k = 0; k < count; k++)
				{
					if (s[k].IsIn(Dot(PointSet[12 + offset], PointSet[13 + offset], PointSet[14 + offset]), delta))
					{
						norm.X -= s[k].xn; norm.Y -= s[k].yn; norm.Z -= s[k].zn;
						in++;
					}
					if (in >= 5)
						break;
				}
				norm.Normolize();
				PointSet[15 + offset] = norm.X; PointSet[16 + offset] = norm.Y; PointSet[17 + offset] = norm.Z;
				offset += 18;

				norm.SetCord(0, 0, 0);
				in = 0;
				for (int k = 0; k < count; k++)
				{
					if (s[k].IsIn(Dot(PointSet[0 + offset], PointSet[1 + offset], PointSet[2 + offset]), delta))
					{
						norm.X -= s[k].xn; norm.Y -= s[k].yn; norm.Z -= s[k].zn;
						in++;
					}
					if (in >= 5)
						break;
				}
				norm.Normolize();
				PointSet[3 + offset] = norm.X; PointSet[4 + offset] = norm.Y; PointSet[5 + offset] = norm.Z;
				norm.SetCord(0, 0, 0);
				in = 0;
				for (int k = 0; k < count; k++)
				{
					if (s[k].IsIn(Dot(PointSet[6 + offset], PointSet[7 + offset], PointSet[8 + offset]), delta))
					{
						norm.X -= s[k].xn; norm.Y -= s[k].yn; norm.Z -= s[k].zn;
						in++;
					}
					if (in >= 5)
						break;
				}
				norm.Normolize();
				PointSet[9 + offset] = norm.X; PointSet[10 + offset] = norm.Y; PointSet[11 + offset] = norm.Z;
				norm.SetCord(0, 0, 0);
				in = 0;
				for (int k = 0; k < count; k++)
				{
					if (s[k].IsIn(Dot(PointSet[12 + offset], PointSet[13 + offset], PointSet[14 + offset]), delta))
					{
						norm.X -= s[k].xn; norm.Y -= s[k].yn; norm.Z -= s[k].zn;
						in++;
					}
					if (in >= 5)
						break;
				}
				norm.Normolize();
				PointSet[15 + offset] = norm.X; PointSet[16 + offset] = norm.Y; PointSet[17 + offset] = norm.Z;
				offset += 18;
			}
		}
	}

private:
	GLfloat  Rtop, Rbottom, heghtU, heghtD;

	Dot* GenCircle(GLfloat  R, GLfloat  y, int nVert)// аппроксимируем окружность до описанного многогранника 
	{
		float alpha = 6.28318530718 / nVert;
		Dot* vert = new Dot[nVert + 1];
		double x, z;
		for (int i = 0; i <= nVert; i++)
		{
			x = R * sin(alpha * i);
			z = R * cos(alpha * i);
			if (abs(x) < 0.0000001)
				x = 0;
			if (abs(z) < 0.0000001)
				z = 0;
			vert[i].SetCord(x, y, z);
		}
		return vert;
	}

	Dot* GenCircleR(int  pr)// генирируем набор окружностей между 2 заданными 
	{
		int k = pr / 2 - 1;
		Dot* res = new Dot[pr-1];
		float tmp = heghtU / k;
		for (int i = 0; i < k ; i++)
			res[k-i].SetCord(sin(acos(tmp*i)), tmp * i, 0);
		tmp = heghtD / k;
		for (int i = 1; i < k; i++)
			res[k + i].SetCord(sin(acos(tmp * i)), tmp * i, 0);
		res[0].SetCord(Rtop, heghtU, 0);
		res[pr-2].SetCord(Rbottom, heghtD, 0);
		for (int i = 0; i < pr; i++)
		return res;
	}

	Dot GetNorm(GLfloat  points[])// вычисляем нормаль по 3-м точкам 
	{
		GLfloat x1, x2, y1, y2, z1, z2;
		x1 = points[3] - points[0]; x2 = points[6] - points[0];
		y1 = points[4] - points[1]; y2 = points[7] - points[1];
		z1 = points[5] - points[2]; z2 = points[8] - points[2];
		GLfloat x, y, z;
		x = y1 * z2 - z1 * y2;
		y = -x1 * z2 + x2 * z1;
		z = x1 * y2 - y1 * x2;
		return Dot(x, y, z);
	}
};