#pragma once
#include "Dot.h"

class Surfase
{
public:
	float xn, yn, zn;

	Surfase(Dot v1, Dot v2, Dot v3)
	{
		V1 = new Dot(v1.X, v1.Y, v1.Z);
		V2 = new Dot(v2.X, v2.Y, v2.Z);
		V3 = new Dot(v3.X, v3.Y, v3.Z);
		FindNorm();
	}

	Surfase(){}

	bool IsIn(Dot tmp, double delta)
	{
		bool v1 = (abs((*V1).X - tmp.X) < delta) && (abs((*V1).Y - tmp.Y) < delta) && (abs((*V1).Z - tmp.Z) < delta);
		bool v2 = (abs((*V2).X - tmp.X) < delta) && (abs((*V2).Y - tmp.Y) < delta) && (abs((*V2).Z - tmp.Z) < delta);
		bool v3 = (abs((*V3).X - tmp.X) < delta) && (abs((*V3).Y - tmp.Y) < delta) && (abs((*V3).Z - tmp.Z) < delta);
		return (v1 || v2 || v3);
	}

private:
	Dot* V1;
	Dot* V2;
	Dot* V3;

	void FindNorm()
	{
		double x1, x2, y1, y2, z1, z2;
		x1 = (*V2).X - (*V1).X; x2 = (*V3).X - (*V1).X;
		y1 = (*V2).Y - (*V1).Y; y2 = (*V3).Y - (*V1).Y;
		z1 = (*V2).Z - (*V1).Z; z2 = (*V3).Z - (*V1).Z;
		xn = y1 * z2 - z1 * y2;
		yn = -x1 * z2 + x2 * z1; 
		zn = x1* y2 - y1 * x2;
	}

	friend std::ostream& operator<< (std::ostream& out, const Surfase& s);
};

std::ostream& operator << (std::ostream& out, const Surfase& s)
{
	out << (*(s.V1)).X << ' ' << (*(s.V1)).Y << ' ' << (*(s.V1)).Z << '\n' << (*(s.V2)).X << ' ' << (*(s.V2)).Y << ' ' << (*(s.V2)).Z << '\n' << (*(s.V3)).X << ' ' << (*(s.V3)).Y << ' ' << (*(s.V3)).Z << '\n';
	return out;
}