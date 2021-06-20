#pragma once
#include <glm/glm.hpp>

class Cell
{
public:
	bool IsLive, nextS;
	glm::vec3 position;
	glm::vec3 collor;
	float X, Y, Z;

	Cell(float x, float y, float z, bool il)
	{
		Cell::position = glm::vec3(x, y, z);
		Cell::collor = glm::vec3(0, 0, 0);
		X = x; Y = y; Z = z;
		Cell::IsLive = il;
	}

	Cell()
	{
		Cell::position = glm::vec3(0, 0, 0);
		Cell::collor = glm::vec3(0, 0, 0);
		X = 0; Y = 0; Z = 0;
		Cell::IsLive = false;
	}

	void SetPosition(float x, float y, float z, bool il)
	{
		Cell::position = glm::vec3(x, y, z);
		X = x; Y = y; Z = z;
		Cell::IsLive = il;
	}
};