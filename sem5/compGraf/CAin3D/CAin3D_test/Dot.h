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


private:
	void CorToM()
	{
		corM[0] = X;
		corM[1] = Y;
		corM[2] = Z;
	}
};
