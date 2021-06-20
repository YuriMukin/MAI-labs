#include <vector>
#define GLEW_STATIC
#include <GL/glew.h>
#include "Shader.h"
#include <string.h>
#include <cmath>
#include <iostream>
#include <GLFW/glfw3.h>
#include "game_life.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Dot.h"

class renderer
{
public:
	renderer(int Bmin, int Bmax, int Smin, int Smax, bool closed, Dot inArr[], int ln);

private:
	GLfloat* CellCube;
	Game_Life* Sourse;

	void gedCubArr();

	void draw();
};