#pragma once
#include <cmath>

class Dot
{
public:
	float X, Y, Z;
	float corM[3];

	Dot(float x, float y, float z)
	{
		X = x;
		Y = y;
		Z = z;
		CorToM();
	}

	Dot()
	{
		X = 0;
		Y = 0;
		Z = 0;
		CorToM();
	}

	void SetCord(float x, float y, float z)
	{
		X = x;
		Y = y;
		Z = z;
		CorToM();
	}

	void Normolize()
	{
		double tmp = sqrt(X * X + Y * Y + Z * Z);
		X = X / tmp;
		Y = Y / tmp;
		Z = Z / tmp;
		CorToM();
	}

	friend bool operator== (const Dot& d1, const Dot& d2);
	friend Dot operator+(const Dot& d1, const Dot& d2);

private:
	void CorToM()
	{
		corM[0] = X;
		corM[1] = Y;
		corM[2] = Z;
	}
};

bool operator== (const Dot& d1, const Dot& d2)
{
	return (abs(d1.X - d2.X)<1.0 && abs(d1.Y - d2.Y) < 1.1 && abs(d1.Z - d2.Z) < 1.1);
}

Dot operator+(const Dot& d1, const Dot& d2)
{
	return Dot(d1.X + d2.X, d1.Y + d2.Y, d1.Z + d2.Z);
}