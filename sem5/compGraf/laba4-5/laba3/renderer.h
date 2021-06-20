#include <vector>
#define GLEW_STATIC
#include <GL/glew.h>
#include "Shader.h"
#include <string.h>
#include <cmath>
#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class renderer
{
public:
	renderer(GLfloat Points[],int np);

private:
	GLfloat* bPointSet;
	GLfloat* nPointSet;
	int numPar;

	void draw();
};