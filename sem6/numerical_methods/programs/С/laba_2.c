#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.14159265 

//Выраженная функция
double fi_func_v12(double x)
{
    return log(5*pow(x,2)-1)/log(3);
}

//Исходня функция
double f_func_v12(double x)
{
    return pow(3,x)-5*pow(x,2)+1;
}

//Производня исходной функции
double f_derivative_v12(double x)
{
    return pow(3,x)*log(3)-10*x;
}

void fi_system_v12(double x1, double x2, double val[])
{
    val[0] = 3 + cos(x2);
    val[1] = 3 + sin(x1);
}

//Исходная система уравнений
void f_system_v12(double x1, double x2, double val[])
{
    val[0] = x1-cos(x2)-3;
    val[1] = x2-sin(x1)-3;
}

//Производная исходной системы по х1
void f_system_dx1_v12(double x1, double x2, double val[])
{
    val[0] = 1;
    val[1] = -cos(x1);
}

//Производная исходной системы по х2
void f_system_dx2_v12(double x1, double x2, double val[])
{
    val[0] = sin(x2);
    val[1] = 1;
}

//Метод простых итераций
double simple_iterations(double(*fi_func)(double a),double x0, double epsilon, double q)
{
    double prev_x;
    double x = x0;
    int k=0;
    do
    {
        printf("\nk=%d x=%lf fi_func(x)=%lf", k, x, fi_func(x));
        prev_x = x;
        x = fi_func(x);
        k++;
    }
    while((q/(1-q)) * fabs(x - prev_x) > epsilon && k<1000);
    return x;
}

//Метод Ньютона
double newton_method(double(*f_func)(double a),double(*f_derivative)(double a),double x0, double epsilon)
{
    double x = x0;
    double prev_x;
    int k=0;
    do
    {
        printf("\nk=%d x=%lf f_func(x)=%lf f_derivative(x)=%lf f_func(x)/f_derivative(x)=%lf", k, x, f_func(x), f_derivative(x), f_func(x)/f_derivative(x));
        prev_x = x;
        x-= f_func(x)/f_derivative(x);
        k++;
    }
    while(fabs(x-prev_x) >= epsilon && k<500);
    return x;
}

//Метод итераций для системы 
void simple_iterations_fs(void(*fi)(double x1, double x2, double val[]), double x0[], double epsilon, double q)
{
    double *prevu_x = malloc(2*sizeof(double));
    int k = 0;
    do
    {
        free(prevu_x);
        memcpy(prevu_x, x0, 2*sizeof(double));
        fi(x0[0], x0[1], x0);
        k++;
    }
    while(sqrt(pow(x0[0]-prevu_x[0],2)+pow(x0[1]-prevu_x[1],2))>epsilon && k<150);
    free(prevu_x);
    printf("\n%d iterations have been done",k);
}

//Метод Ньютона для системы
double newton_method_fs(void(*f)(double x1, double x2, double val[]),void(*fdx1)(double x1, double x2, double val[]),void(*fdx2)(double x1, double x2, double val[]), double x0[], double epsilon)
{
    double *prevu_x = malloc(2*sizeof(double));
    double *fm = malloc(2*sizeof(double));
    double *fdx1m = malloc(2*sizeof(double));
    double *fdx2m = malloc(2*sizeof(double));
    int k = 0;
    double e;
    do
    {
        free(prevu_x);
        memcpy(prevu_x, x0, 2*sizeof(double));
        f(prevu_x[0], prevu_x[1], fm);
        fdx1(prevu_x[0], prevu_x[1], fdx1m);
        fdx2(prevu_x[0], prevu_x[1], fdx2m);
        x0[0] -= (fm[0]*fdx2m[1]-fm[1]*fdx2m[0])/(fdx1m[0]*fdx2m[1]-fdx1m[1]*fdx2m[0]);
        x0[1] -= (fm[1]*fdx1m[0]-fdx1m[1]*fm[0])/(fdx1m[0]*fdx2m[1]-fdx1m[1]*fdx2m[0]);
        k++;
    }
    while(sqrt(pow(x0[0]-prevu_x[0],2)+pow(x0[1]-prevu_x[1],2))>epsilon && k<150);
    free(prevu_x); free(fm); free(fdx1m); free(fdx2m);
    printf("\n%d iterations have been done",k);
}

void equation_solution()
{
    double eps;
    printf("\nenter precision: ");
    scanf("%lf",&eps);
    printf("solution obtained by simple iteration method");
    printf("\nx=%lf", simple_iterations(fi_func_v12,3, eps, 0.826));
    printf("\nsolution obtained by Newton method");
    printf("\nx=%lf", newton_method(f_func_v12, f_derivative_v12, 5, eps));
}

void solution_system_of_equations()
{
    double eps;
    printf("\nenter precision: ");
    scanf("%lf",&eps);
    double x[2]={PI,2};
    simple_iterations_fs(fi_system_v12, x, eps, 0.9);
    printf("\nsolution is obtained by the method of simple iterations\nx1=%lf, x2=%lf", x[0], x[1]);//3.802 2.21
    x[0] = 4; x[1] = 2.3464;
    newton_method_fs(f_system_v12, f_system_dx1_v12, f_system_dx2_v12, x, eps);
    printf("\nsolution is obtained by Newton method\nx1=%lf, x2=%lf", x[0], x[1]);//3.802 2.21
}

int menu() //меню программы
{
	{
		int sw = 0;
		while (sw < 1 || sw > 6)
		{
			printf("\n 1. equation solution \n 2. solution system of equations \n 3. end work \n choos action : ");
			scanf("%d", &sw);
			if (sw < 1 || sw>6) printf("\n this action dosn'n exist \n");
		}
		return (sw);
	}
}

int main()
{
    int act = 42;
    while (act != 3)
		switch (act)
		{
		case 1: equation_solution(); act = 42; break;
		case 2: solution_system_of_equations(); act = 42; break;
        case 3: exit(1); break;
		default: act = menu(); break;
		}
}