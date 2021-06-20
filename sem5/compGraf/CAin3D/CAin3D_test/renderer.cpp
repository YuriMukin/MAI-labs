#include "renderer.h"
#include <iostream>

#define PI 3.14159265 

void window_size_callback(GLFWwindow* window, int width, int height);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
double WIDTH, HEIGHT, scale, xposS, yposS, ny, nx;
float x, y, z;
bool isRot;

renderer::renderer(int Bmin, int Bmax, int Smin, int Smax, bool closed, Dot inArr[], int ln)
{
	WIDTH = 640;
	HEIGHT = 640;
	scale = 1;
	xposS = 0;
	yposS = 0;
	nx = 0;
	ny = 0;
	x = 140;
	y = 140;
	z = 140;
	isRot = false;
	Sourse = new Game_Life(Bmin, Bmax, Smin, Smax, inArr, ln, closed);
	renderer::gedCubArr();
	renderer::draw();
}


void renderer::draw()
{
	GLFWwindow* window;// готовим окно и компилируем шейдер 
	if (!glfwInit())
		return;
	window = glfwCreateWindow(640, 640, "Mukin Yuri M80-304-18", NULL, NULL);// создаем окно 
	if (!window)
	{
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);
	glLineWidth(3);
	glEnable(GL_DEPTH_TEST);
	Shader DifractionShader("../source/shaders/DifractionShader.vs", "../source/shaders/DifractionShader.frag");
	GLuint VBO, containerVAO;//готовим буферы
	glGenVertexArrays(1, &containerVAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 216, renderer::CellCube, GL_STATIC_DRAW);
	glBindVertexArray(containerVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
	GLuint lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	glfwSetScrollCallback(window, scroll_callback); //подписываемся на ивенты 
	glfwSetWindowSizeCallback(window, window_size_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetKeyCallback(window, key_callback);
	while (!glfwWindowShouldClose(window)) //бескончный цикл до закрытия окна 
	{
		glfwPollEvents();
		(*(renderer::Sourse)).WhoIsAlive();
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		float skf[] = { scale,0,0,0,0,scale,0,0,0,0,scale,0,0,0,0,1 };//считаем трансформации
		glm::mat4 sk = glm::make_mat4(skf);
		float rtxf[] = { 1,0,0,0,0,cos(nx),-sin(nx),0,0,sin(nx),cos(nx),0,0,0,0,1 };
		glm::mat4 rtx = glm::make_mat4(rtxf);
		float rtyf[] = { cos(-ny),0,sin(-ny),0,0,1,0,0,-sin(-ny),0,cos(-ny),0,0,0,0,1 };
		glm::mat4 rty = glm::make_mat4(rtyf);
		DifractionShader.Use(); //используем шейдер 
		GLint objectColorLoc = glGetUniformLocation(DifractionShader.Program, "objectColor");
		GLint lightColorLoc = glGetUniformLocation(DifractionShader.Program, "lightColor");
		GLint lightPosLoc = glGetUniformLocation(DifractionShader.Program, "lightPos");
		GLint viewPosLoc = glGetUniformLocation(DifractionShader.Program, "viewPos");
		glUniform3f(lightColorLoc, 0.0f, 0.5f, 0.5f);
		glUniform3f(lightPosLoc, 120.0f,  120.0f,  120.0f);
		glUniform3f(viewPosLoc, x, y, z);
		glm::mat4 view;
		view = glm::lookAt(glm::vec3(x, y, z), glm::vec3(50, 50, 50), glm::vec3(0, 1, 0));
		glm::mat4 projection = glm::perspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 1100.0f);
		GLint modelLoc = glGetUniformLocation(DifractionShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(DifractionShader.Program, "view");
		GLint projLoc = glGetUniformLocation(DifractionShader.Program, "projection");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glBindVertexArray(containerVAO);
		glm::mat4 model = sk  * rtx * rty;
		for (GLuint i = 0; i < (*(renderer::Sourse)).NumOfLive; i++)
		{
			glm::vec3 collor = (*(renderer::Sourse)).Field[(int)(*(renderer::Sourse)).AliveArr[i].x][(int)(*(renderer::Sourse)).AliveArr[i].y][(int)(*(renderer::Sourse)).AliveArr[i].z].collor;//считываем цвет клетки
			glUniform3f(objectColorLoc, collor.x,collor.y,collor.z);
			glm::mat4 model_loc = glm::translate(model, (*(renderer::Sourse)).AliveArr[i]);//задаем позиция через смещение
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model_loc));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);
		glfwSwapBuffers(window);
	}
	glfwTerminate();
}


void renderer::gedCubArr()
{
	GLfloat tmp[] = {
	 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};
	renderer::CellCube = new GLfloat[216];
	for(int i =0; i<216; i++)
		renderer::CellCube[i] = tmp[i];
}

void window_size_callback(GLFWwindow* window, int width, int height)// реагируем на изменение размеров окна 
{
	WIDTH = width;
	HEIGHT = height;
	glViewport(0, 0, width, height);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (yoffset < 0)// изменяем масштаб 1 шаг колесика мыши =  +/-10 процентов 
		scale *= 0.9;
	else
		scale *= 1.1;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)// регаируем на зажатие лкм
	{
		isRot = true;
		glfwSetInputMode(window, 0, 0);
		glfwGetCursorPos(window, &xposS, &yposS);
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		isRot = false;
		xposS = 0;
		yposS = 0;
	}
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (isRot)// если лкм зажата считаем угол поворота относительно х и у
	{
		if ((xpos / 2000 <= 1) && (ypos / 2000 <= 1))
		{
			ny += (acos(xpos / 2000) - acos(xposS / 2000)) * 180.0 / PI;
			nx += (asin(ypos / 2000) - asin(yposS / 2000)) * 180.0 / PI;
			xposS = xpos; yposS = ypos;
		}
		else
		{
			isRot = false;
			xposS = 0;
			yposS = 0;
		}
	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		x -= x * 0.05; y -= y * 0.05; z -= z * 0.05;
	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		x += x * 0.05; y += y * 0.05; z += z * 0.05;
	}
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		x += z * 0.05; z -= x * 0.05;
	}
	if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		x -= z * 0.05; z += x * 0.05;
	}
}