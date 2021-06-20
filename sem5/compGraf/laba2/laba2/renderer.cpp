#include "renderer.h"
#include <string.h>
#include <cmath>
#include "boost/numeric/ublas/matrix.hpp"
#include <iostream>

#define PI 3.14159265 

void window_size_callback(GLFWwindow* window, int width, int height);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
double scale, xposS, yposS, ny, nx, shift;
bool isRot;

renderer::renderer(GLdouble Points[], int np)
{
	renderer::bPointSet = Points;
	renderer::nPointSet = new GLdouble[np];
	renderer::num_pairs = np;
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
	GLFWwindow* window;
	if (!glfwInit())
		return;
	window = glfwCreateWindow(640, 640, "Yuri Mukin M80-304-18", NULL, NULL);// создаем окно 
	if (!window)
	{
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);// устанавливаем режим отрисовки полигонов линиями 
	glLineWidth(3);
	glfwSetScrollCallback(window, scroll_callback); //подписываемся на ивенты 
	glfwSetWindowSizeCallback(window, window_size_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	while (!glfwWindowShouldClose(window)) //бескончный цикл до закрытия окна 
	{
		glfwWaitEvents(); // проверяем обновление ивентов 
		renderer::newVertSet(); //персчитываем набор точек 
		glClear(GL_COLOR_BUFFER_BIT); //сбрасываем цвет (ну мало ли что)
		glEnableClientState(GL_VERTEX_ARRAY);// включаем возможность строить примитивы по массиву
		glVertexPointer(3, GL_DOUBLE, 0, renderer::nPointSet); // подгружаем массив точчек 
		glColor3ub(1, 80, 32); // задаем цвет
		for (int i = 0; i < 96; i+=3)
		{
			if (renderer::isRight(i*3))//проверяем видимость полигона 
				glDrawArrays(GL_POLYGON, i, 3); //рисуем его
		}
		glfwSwapBuffers(window); //свапаем буфер окна 
	}
}

void renderer::rotate(int of)
{
	boost::numeric::ublas::matrix<double>dot(4, 1);

	boost::numeric::ublas::matrix<double> x(4, 4);// матрица поворота относительно оси х
	x(0, 0) = 1.; x(0, 1) = 0.; x(0, 2) = 0.; x(0, 3) = 0.;
	x(1, 0) = 0.; x(1, 1) = cos(nx); x(1, 2) = -sin(nx); x(1, 3) = 0.;
	x(2, 0) = 0.; x(2, 1) = sin(nx); x(2, 2) = cos(nx); x(2, 3) = 0.;
	x(3, 0) = 0.; x(3, 1) = 0.; x(3, 2) = 0.; x(3, 3) = 1.;

	boost::numeric::ublas::matrix<double> y(4, 4);// матрица поворота относительно оси у
	y(0, 0) = cos(-ny); y(0, 1) = 0.; y(0, 2) = sin(-ny); y(0, 3) = 0.;
	y(1, 0) = 0.; y(1, 1) = 1.; y(1, 2) = 0.; y(1, 3) = 0.;
	y(2, 0) = -sin(-ny); y(2, 1) = 0.; y(2, 2) = cos(-ny); y(2, 3) = 0.;
	y(3, 0) = 0.; y(3, 1) = 0.; y(3, 2) = 0.; y(3, 3) = 1.;
	for (int i = of; i < of+9; i += 3)
	{
		dot(0, 0) = renderer::nPointSet[i]; dot(1, 0) = renderer::nPointSet[i + 1];
		dot(2, 0) = renderer::nPointSet[i + 2]; dot(3, 0) = 1;
		boost::numeric::ublas::matrix<double>dot0 = prod(x, dot);// поворачиваем относительно х, затем относительно у
		boost::numeric::ublas::matrix<double>dot1 = prod(y, dot0);
		renderer::nPointSet[i] = dot1(0,0); renderer::nPointSet[i + 1] = dot1(1,0); renderer::nPointSet[i + 2] = dot1(2,0);
	}
}

void renderer::offset(int of)
{
	boost::numeric::ublas::matrix<double>dot(4, 1);

	boost::numeric::ublas::matrix<double> shiftMatrix(4, 4);// матрица смещения 
	shiftMatrix(0, 0) = 1.; shiftMatrix(0, 1) = 0.; shiftMatrix(0, 2) = 0.; shiftMatrix(0, 3) = 0.;
	shiftMatrix(1, 0) = 0.; shiftMatrix(1, 1) = 1.; shiftMatrix(1, 2) = 0.; shiftMatrix(1, 3) = -shift;
	shiftMatrix(2, 0) = 0.; shiftMatrix(2, 1) = 0.; shiftMatrix(2, 2) = 1.; shiftMatrix(2, 3) = 0.;
	shiftMatrix(3, 0) = 0.; shiftMatrix(3, 1) = 0.; shiftMatrix(3, 2) = 0.; shiftMatrix(3, 3) = 1.;
	for (int i = of; i < of + 9; i += 3)
	{
		dot(0, 0) = renderer::nPointSet[i]; dot(1, 0) = renderer::nPointSet[i + 1];
		dot(2, 0) = renderer::nPointSet[i + 2]; dot(3, 0) = 1;
		boost::numeric::ublas::matrix<double>dot0 = prod(shiftMatrix, dot);
		renderer::nPointSet[i] = dot0(0, 0); renderer::nPointSet[i + 1] = dot0(1, 0); renderer::bPointSet[i + 2] = dot0(2, 0);
	}
}

void renderer::Scale(int of)
{
	boost::numeric::ublas::matrix<double>dot(4, 1);

	boost::numeric::ublas::matrix<double> scaleMatrix(4, 4);//матрица масштаба 
	scaleMatrix(0, 0) = scale; scaleMatrix(0, 1) = 0.; scaleMatrix(0, 2) = 0.; scaleMatrix(0, 3) = 0.;
	scaleMatrix(1, 0) = 0.; scaleMatrix(1, 1) = scale; scaleMatrix(1, 2) = 0.; scaleMatrix(1, 3) = 0.;
	scaleMatrix(2, 0) = 0.; scaleMatrix(2, 1) = 0.; scaleMatrix(2, 2) = scale; scaleMatrix(2, 3) = 0.;
	scaleMatrix(3, 0) = 0.; scaleMatrix(3, 1) = 0.; scaleMatrix(3, 2) = 0.; scaleMatrix(3, 3) = 1.;
	for (int i = of; i < of + 9; i += 3)
	{
		dot(0, 0) = renderer::nPointSet[i]; dot(1, 0) = renderer::nPointSet[i + 1];
		dot(2, 0) = renderer::nPointSet[i + 2]; dot(3, 0) = 1;
		boost::numeric::ublas::matrix<double>dot0 = prod(scaleMatrix, dot);
		renderer::nPointSet[i] = dot0(0, 0); renderer::nPointSet[i + 1] = dot0(1, 0); renderer::nPointSet[i + 2] = dot0(2, 0);
	}
}

void renderer::newVertSet()
{
	for (int i = 0; i < renderer::num_pairs; i++)
		renderer::nPointSet[i] = renderer::bPointSet[i]; //сбрасываем все изменения и просчитываем заново
	for (int i = 0; i < renderer::num_pairs; i += 9)
	{
		renderer::offset(i);
		renderer::Scale(i);
		renderer::rotate(i);
	}
}

bool renderer::isRight(int of)
{
	double x1, x2, y1, y2, z1, z2;//определяем 2 вектора на грани считаем их векторное произведение, а затем векторное с вектором наблюдения (смотрим из точки 0,0,1 в 0,0,0)
	x1 = renderer::nPointSet[of + 3] - renderer::nPointSet[of];     x2 = renderer::nPointSet[of + 6] - renderer::nPointSet[of];
	y1 = renderer::nPointSet[of + 4] - renderer::nPointSet[of + 1]; y2 = renderer::nPointSet[of + 7] - renderer::nPointSet[of + 1];
	z1 = renderer::nPointSet[of + 5] - renderer::nPointSet[of + 2]; z2 = renderer::nPointSet[of + 8] - renderer::nPointSet[of + 2];
	//xn = y1 * z2 - z1 * y2 - x1; yn = -x1 * z2 + x2 * z1; zn = x1 * y2 - x2 * y1;
	double crossProd = x1 * y2 - x2 * y1;
	return crossProd < 0;
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
		shift = 1 -(double)width / (double)height;
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
		glfwSetInputMode(window,0,0);
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
		if ((xpos / 2000<=1) && (ypos / 2000<=1))
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