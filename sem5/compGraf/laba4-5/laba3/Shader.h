#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <Windows.h>
#define GLEW_STATIC
#include <GL/glew.h>


class Shader
{
public:
	GLuint Program;

	Shader(const char* VertPath, const char* FigPath);
	void Use();
};