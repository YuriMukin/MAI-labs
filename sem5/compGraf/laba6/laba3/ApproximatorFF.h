#pragma once
#include <GL/glew.h>
#include <iostream>
#include <glm\trigonometric.hpp>
#include "surface.h"
#include "Dot.h"

class ApproximatorFF
{
public:
	GLfloat* PointSet;
	int weight;

	ApproximatorFF(GLfloat  Rt, GLfloat  Rb, GLfloat  hu, GLfloat  hd)
	{
		Rtop = Rt;
		Rbottom = Rb;
		heghtU = hu;
		heghtD = hd;
		weight = 0;
	}

	void Approximaze(int  pr)
	{
		ApproximatorFF::PointSet = new GLfloat[pr * 72 * (pr - 2)];// определяем размер выходного массива
		ApproximatorFF::weight = pr * 72 * (pr - 2);
		Dot* t = ApproximatorFF::GenCircleR(pr); // генирируем набор окружностей между 2 заданными 
		int offset = 0;
		for (int j = 0; j < pr - 2; j++) // генирируем итоговую фигуру по слоям 
		{
			Dot* CrTop = ApproximatorFF::GenCircle(t[j].X, t[j].Y, pr); // выбираем 2 соседние окружности
			Dot* CrDown = ApproximatorFF::GenCircle(t[j + 1].X, t[j + 1].Y, pr);
			for (int i = 1; i <= pr; i++)
			{
				if (j == 0)
				{
					GLfloat  tmp0[] = { CrTop[i - 1].X, CrTop[i - 1].Y, CrTop[i - 1].Z, CrTop[i].X, CrTop[i].Y, CrTop[i].Z, 0, CrTop[i].Y, 0 };
					Dot norm0 = ApproximatorFF::GetNorm(tmp0); // изем нормаль поверности (необходимо для расчета освещения)
					norm0.Normolize();
					PointSet[0 + offset] = CrTop[i - 1].X; PointSet[1 + offset] = CrTop[i - 1].Y; PointSet[2 + offset] = CrTop[i - 1].Z;
					PointSet[3 + offset] = norm0.X; PointSet[4 + offset] = norm0.Y; PointSet[5 + offset] = norm0.Z;
					PointSet[6 + offset] = CrTop[i].X; PointSet[7 + offset] = CrTop[i].Y; PointSet[8 + offset] = CrTop[i].Z;
					PointSet[9 + offset] = norm0.X; PointSet[10 + offset] = norm0.Y; PointSet[11 + offset] = norm0.Z;
					PointSet[12 + offset] = 0; PointSet[13 + offset] = CrTop[i].Y; PointSet[14 + offset] = 0;
					PointSet[15 + offset] = norm0.X; PointSet[16 + offset] = norm0.Y; PointSet[17 + offset] = norm0.Z;
					offset += 18;
				}
				if (j == pr - 3)
				{
					GLfloat  tmp1[] = { CrDown[i].X, CrDown[i].Y, CrDown[i].Z, CrDown[i - 1].X, CrDown[i - 1].Y, CrDown[i - 1].Z,0, CrDown[i].Y, 0 };
					Dot norm1 = ApproximatorFF::GetNorm(tmp1);
					norm1.Normolize();
					PointSet[0 + offset] = CrDown[i - 1].X; PointSet[1 + offset] = CrDown[i - 1].Y; PointSet[2 + offset] = CrDown[i - 1].Z;
					PointSet[3 + offset] = norm1.X; PointSet[4 + offset] = norm1.Y; PointSet[5 + offset] = norm1.Z;
					PointSet[6 + offset] = CrDown[i].X; PointSet[7 + offset] = CrDown[i].Y; PointSet[8 + offset] = CrDown[i].Z;
					PointSet[9 + offset] = norm1.X; PointSet[10 + offset] = norm1.Y; PointSet[11 + offset] = norm1.Z;
					PointSet[12 + offset] = 0; PointSet[13 + offset] = CrDown[i].Y; PointSet[14 + offset] = 0;
					PointSet[15 + offset] = norm1.X; PointSet[16 + offset] = norm1.Y; PointSet[17 + offset] = norm1.Z;
					offset += 18;
				}
				GLfloat  tmp2[] = { CrTop[i].X,CrTop[i].Y,CrTop[i].Z, CrTop[i - 1].X,CrTop[i - 1].Y,CrTop[i - 1].Z, CrDown[i].X, CrDown[i].Y, CrDown[i].Z };
				Dot norm2 = ApproximatorFF::GetNorm(tmp2);
				norm2.Normolize();
				PointSet[0 + offset] = CrTop[i - 1].X; PointSet[1 + offset] = CrTop[i - 1].Y; PointSet[2 + offset] = CrTop[i - 1].Z;
				PointSet[3 + offset] = norm2.X; PointSet[4 + offset] = norm2.Y; PointSet[5 + offset] = norm2.Z;
				PointSet[6 + offset] = CrTop[i].X; PointSet[7 + offset] = CrTop[i].Y; PointSet[8 + offset] = CrTop[i].Z;
				PointSet[9 + offset] = norm2.X; PointSet[10 + offset] = norm2.Y; PointSet[11 + offset] = norm2.Z;
				PointSet[12 + offset] = CrDown[i].X; PointSet[13 + offset] = CrDown[i].Y; PointSet[14 + offset] = CrDown[i].Z;
				PointSet[15 + offset] = norm2.X; PointSet[16 + offset] = norm2.Y; PointSet[17 + offset] = norm2.Z;
				offset += 18;
				GLfloat  tmp3[] = { CrDown[i - 1].X, CrDown[i - 1].Y, CrDown[i - 1].Z, CrDown[i].X, CrDown[i].Y, CrDown[i].Z, CrTop[i - 1].X, CrTop[i - 1].Y, CrTop[i - 1].Z };
				Dot norm3 = ApproximatorFF::GetNorm(tmp3);
				norm3.Normolize();
				PointSet[0 + offset] = CrTop[i - 1].X; PointSet[1 + offset] = CrTop[i - 1].Y; PointSet[2 + offset] = CrTop[i - 1].Z;
				PointSet[3 + offset] = norm3.X; PointSet[4 + offset] = norm3.Y; PointSet[5 + offset] = norm3.Z;
				PointSet[6 + offset] = CrDown[i - 1].X; PointSet[7 + offset] = CrDown[i - 1].Y; PointSet[8 + offset] = CrDown[i - 1].Z;
				PointSet[9 + offset] = norm3.X; PointSet[10 + offset] = norm3.Y; PointSet[11 + offset] = norm3.Z;
				PointSet[12 + offset] = CrDown[i].X; PointSet[13 + offset] = CrDown[i].Y; PointSet[14 + offset] = CrDown[i].Z;
				PointSet[15 + offset] = norm3.X; PointSet[16 + offset] = norm3.Y; PointSet[17 + offset] = norm3.Z;
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
			if (abs(x) < 0.001)
				x = 0;
			if (abs(z) < 0.001)
				z = 0;
			vert[i].SetCord(x, y, z);
		}
		return vert;
	}

	Dot* GenCircleR(int  pr)// генирируем набор окружностей между 2 заданными 
	{
		int k = pr / 2 - 1;
		Dot* res = new Dot[pr - 1];
		float tmp = heghtU / k;
		for (int i = 0; i < k; i++)
			res[k - i].SetCord(sin(acos(tmp * i)), tmp * i, 0);
		tmp = heghtD / k;
		for (int i = 1; i < k; i++)
			res[k + i].SetCord(sin(acos(tmp * i)), tmp * i, 0);
		res[0].SetCord(Rtop, heghtU, 0);
		res[pr - 2].SetCord(Rbottom, heghtD, 0);
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