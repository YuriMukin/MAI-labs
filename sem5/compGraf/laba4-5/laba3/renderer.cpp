#include "renderer.h"

#define PI 3.14159265 

void window_size_callback(GLFWwindow* window, int width, int height);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
double WIDTH, HEIGHT, scale, xposS, yposS, ny, nx, shift;
bool isRot;

renderer::renderer(GLfloat Points[], int np)
{
	renderer::bPointSet = new float[np];
	for (int i = 0; i < np; i++)
		renderer::bPointSet[i] = Points[i];
	renderer::numPar = np;
	WIDTH = 640;
	HEIGHT = 640;
	scale = 1;
	xposS = 0;
	yposS = 0;
	shift = 0;
	nx = 0;
	ny = 0;
	isRot = false;
	renderer::draw();
}


void renderer::draw()
{
	GLFWwindow* window;// готовим окно и компилируем шейдер 
	if (!glfwInit())
		return;
	window = glfwCreateWindow(640, 640, "Yuri Mukin M80-304-18", NULL, NULL);// создаем окно 
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)* renderer::numPar, renderer::bPointSet, GL_STATIC_DRAW);
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
	//glPolygonMode(GL_FRONT, GL_LINE);
	//glPolygonMode(GL_BACK, GL_POINT);
	glfwSetScrollCallback(window, scroll_callback); //подписываемся на ивенты 
	glfwSetWindowSizeCallback(window, window_size_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	double X, Z;
	while (!glfwWindowShouldClose(window)) //бескончный цикл до закрытия окна 
	{
		glfwPollEvents();
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		float skf[] = { scale,0,0,0,0,scale,0,0,0,0,scale,0,0,0,0,1 };//считаем все трансформации
		glm::mat4 sk = glm::make_mat4(skf);
		float rtxf[] = { 1,0,0,0,0,cos(nx),-sin(nx),0,0,sin(nx),cos(nx),0,0,0,0,1 };
		glm::mat4 rtx = glm::make_mat4(rtxf);
		float rtyf[] = { cos(-ny),0,sin(-ny),0,0,1,0,0,-sin(-ny),0,cos(-ny),0,0,0,0,1 };
		glm::mat4 rty = glm::make_mat4(rtyf);
		float shf[] = { 1,0,0,0,0,1,0,shift,0,0,1,0,0,0,0,1 };
		glm::mat4 sh = glm::make_mat4(shf);
		DifractionShader.Use(); //используем шейдер 
		GLint objectColorLoc = glGetUniformLocation(DifractionShader.Program, "objectColor");
		GLint lightColorLoc = glGetUniformLocation(DifractionShader.Program, "lightColor");
		GLint lightPosLoc = glGetUniformLocation(DifractionShader.Program, "lightPos");
		GLint viewPosLoc = glGetUniformLocation(DifractionShader.Program, "viewPos");
		X = 3;
		Z = 3;
		glUniform3f(objectColorLoc, 0.001f, 0.001f, 0.9f);
		glUniform3f(lightColorLoc, 1.0f, 0.001f, 0.001f);
		glUniform3f(lightPosLoc, X, 1, Z);
		glUniform3f(viewPosLoc, 0, 0, 3);
		glm::mat4 view;
		view = glm::lookAt(glm::vec3(0,0,3), glm::vec3(0,0,0), glm::vec3(0,1,0));
		glm::mat4 projection = glm::perspective(45.0f, 1.0f, 0.1f, 100.0f);
		GLint modelLoc = glGetUniformLocation(DifractionShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(DifractionShader.Program, "view");
		GLint projLoc = glGetUniformLocation(DifractionShader.Program, "projection");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glBindVertexArray(containerVAO);
		glm::mat4 model = sk * sh * rtx * rty;
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, renderer::numPar/6); //рисуем 
		glBindVertexArray(0);
		glfwSwapBuffers(window);
	}
	glfwTerminate();
}


void window_size_callback(GLFWwindow* window, int width, int height)// реагируем на изменение размеров окна 
{
	glfwGetFramebufferSize(window, &width, &height);
	if (width > height)// чтобы не нарушать пропорции рисуем на квадратном полотне с стороной равной большей стороны окна 
	{
		glViewport(0, 0, width, width);
		shift = 1 - (double)height / (double)width; // смещаем фигуру для компенсации разности размеров 
	}
	else
	{
		glViewport(0, 0, height, height);
		shift = 1 - (double)width / (double)height;
	}
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